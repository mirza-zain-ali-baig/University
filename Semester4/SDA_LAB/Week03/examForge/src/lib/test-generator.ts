import { supabase } from "./supabase";
import { getLookups, getMcqOptions } from "./question-bank";
import { generateAIQuestions } from "./ai-questions";
import type {
  GenerateTestRequest,
  GeneratedTest,
  GeneratedQuestion,
  TestSection,
  QuestionTypeName,
  DifficultyName,
} from "./types";
import type { QuestionRow, ChapterRow, TopicRow } from "./supabase";

const TYPE_ORDER: QuestionTypeName[] = ["MCQ", "Short", "Long"];
const DIFF_ORDER: DifficultyName[] = ["Easy", "Medium", "Hard"];

function shuffleArray<T>(arr: T[]): T[] {
  const a = [...arr];
  for (let i = a.length - 1; i > 0; i--) {
    const j = Math.floor(Math.random() * (i + 1));
    [a[i], a[j]] = [a[j], a[i]];
  }
  return a;
}

/**
 * Fetch all questions in a single blueprint cell (type × difficulty × scope),
 * paginating past Supabase's 1000-row hard cap so shuffling covers the full pool.
 * When `questionSources` is provided, results are filtered to those
 * `question_from` values only (NULL/empty list => all sources).
 */
async function fetchBankCellPaged(opts: {
  subjectId: string;
  typeId: string;
  diffId: string;
  chapterIds: string[];
  topicIds: string[];
  questionSources?: string[];
}): Promise<QuestionRow[]> {
  const PAGE = 1000;
  let offset = 0;
  const out: QuestionRow[] = [];
  const sourceFilter =
    opts.questionSources && opts.questionSources.length > 0
      ? opts.questionSources
      : null;
  while (true) {
    let q = supabase
      .from("questions")
      .select("*")
      .eq("subject_id", opts.subjectId)
      .eq("question_type_id", opts.typeId)
      .eq("difficulty_level_id", opts.diffId);
    if (opts.chapterIds.length) q = q.in("chapter_id", opts.chapterIds);
    if (opts.topicIds.length) q = q.in("topic_id", opts.topicIds);
    if (sourceFilter) q = q.in("question_from", sourceFilter);
    q = q.order("id", { ascending: true }).range(offset, offset + PAGE - 1);
    const { data, error } = await q;
    if (error) throw new Error(error.message);
    const rows = (data as QuestionRow[]) ?? [];
    out.push(...rows);
    if (rows.length < PAGE) break;
    offset += PAGE;
  }
  return out;
}

function shuffleOptions(q: GeneratedQuestion): GeneratedQuestion {
  if (!q.options) return q;
  const labels = ["A", "B", "C", "D"] as const;
  const entries = [
    { label: "A", text: q.options.option_a },
    { label: "B", text: q.options.option_b },
    { label: "C", text: q.options.option_c },
    { label: "D", text: q.options.option_d },
  ];
  const shuffled = shuffleArray(entries);
  const correctText =
    q.options[
      `option_${q.options.correct_option.toLowerCase()}` as
        | "option_a"
        | "option_b"
        | "option_c"
        | "option_d"
    ];
  const newCorrectIndex = shuffled.findIndex((e) => e.text === correctText);
  return {
    ...q,
    options: {
      option_a: shuffled[0].text,
      option_b: shuffled[1].text,
      option_c: shuffled[2].text,
      option_d: shuffled[3].text,
      correct_option: labels[newCorrectIndex],
    },
  };
}

/**
 * Core generator. Selects questions from the Supabase bank according to the
 * blueprint, and optionally fills shortfalls with AI-generated questions.
 */
export async function generateTest(
  req: GenerateTestRequest
): Promise<GeneratedTest> {
  const lookups = await getLookups();

  // Resolve topic/chapter names for context (used by AI fill + labels)
  const { data: chData } = await supabase
    .from("chapters")
    .select("*")
    .in("id", req.chapterIds);
  const chapters = (chData as ChapterRow[]) ?? [];
  const chapterMap = new Map(chapters.map((c) => [c.id, c]));

  const { data: tData } = await supabase
    .from("topics")
    .select("*")
    .in("chapter_id", req.chapterIds);
  const allTopics = (tData as TopicRow[]) ?? [];
  const topicMap = new Map(allTopics.map((t) => [t.id, t]));

  // Effective topic filter
  const effectiveTopicIds =
    req.topicIds.length > 0 ? req.topicIds : allTopics.map((t) => t.id);

  const sections: TestSection[] = [];
  const shortfalls: GeneratedTest["meta"]["shortfalls"] = [];
  let fromBank = 0;
  let fromAI = 0;
  let requestedTotal = 0;

  for (const typeName of TYPE_ORDER) {
    const typeCfg = req.blueprint[typeName];
    if (!typeCfg) continue;
    const typeId = lookups.typeIdByName[typeName];
    const collected: GeneratedQuestion[] = [];

    for (const diffName of DIFF_ORDER) {
      const need = typeCfg.difficulties[diffName] ?? 0;
      if (need <= 0) continue;
      requestedTotal += need;
      const diffId = lookups.difficultyIdByName[diffName];

      // Query bank — paginate past Supabase's 1000-row cap for full randomness
      let bankQs: QuestionRow[] = [];
      if (req.source !== "ai") {
        bankQs = await fetchBankCellPaged({
          subjectId: req.subjectId,
          typeId,
          diffId,
          chapterIds: req.chapterIds,
          topicIds: effectiveTopicIds,
          questionSources: req.questionSources,
        });
      }

      // Exclude questions already used by earlier variants (batch mode)
      const excludeSet = new Set(req.excludeQuestionIds ?? []);
      if (excludeSet.size > 0) {
        bankQs = bankQs.filter((q) => !excludeSet.has(q.id));
      }

      const picked = shuffleArray(bankQs).slice(0, need);
      const bankGot = picked.length;

      if (bankGot < need && req.source !== "bank") {
        // AI fill the remainder
        const shortfall = need - bankGot;
        const aiQs = await generateAIQuestions({
          subjectName: req.subjectName,
          className: req.className,
          chapterName: chapters[0]?.chapter_name,
          topicName: topicMap.get(effectiveTopicIds[0] ?? "")?.topic_name,
          typeName,
          difficultyName: diffName,
          count: shortfall,
          marks: typeCfg.marksPerQuestion,
        });
        picked.push(...toGenerated(aiQs));
      }

      // Record a shortfall only if the FINAL count is still below the request
      // (i.e. AI could not fully fill the gap, or source was "bank" with no stock)
      const finalGot = picked.length;
      if (finalGot < need) {
        shortfalls.push({
          type: typeName,
          difficulty: diffName,
          requested: need,
          got: finalGot,
        });
      }

      // Enrich bank picks with options + names
      const enrichedBank = await enrichBankPicks(picked, lookups, topicMap, chapterMap, typeCfg.marksPerQuestion, typeName, diffName);
      collected.push(...enrichedBank);
    }

    if (collected.length === 0) continue;
    const ordered = req.shuffle ? shuffleArray(collected) : collected;
    const sectionMarks = ordered.reduce((s, q) => s + q.marks, 0);
    sections.push({
      type_name: typeName,
      marksPerQuestion: typeCfg.marksPerQuestion,
      questions: ordered.map((q) =>
        req.shuffle ? shuffleOptions(q) : q
      ),
      sectionMarks,
    });
    fromBank += collected.filter((q) => q.source === "bank").length;
    fromAI += collected.filter((q) => q.source === "ai").length;
  }

  const totalMarks = sections.reduce((s, sec) => s + sec.sectionMarks, 0);
  const totalQuestions = sections.reduce((s, sec) => s + sec.questions.length, 0);

  return {
    title: req.title || `${req.subjectName} Examination`,
    className: req.className,
    subjectName: req.subjectName,
    subjectId: req.subjectId,
    durationMins: req.durationMins,
    instructions: req.instructions ?? "",
    totalMarks,
    totalQuestions,
    source: req.source,
    generatedAt: new Date().toISOString(),
    sections,
    meta: {
      requested: requestedTotal,
      fromBank,
      fromAI,
      shortfalls,
    },
  };
}

function toGenerated(aiQs: GeneratedQuestion[]): GeneratedQuestion[] {
  return aiQs;
}

async function enrichBankPicks(
  picks: QuestionRow[] | GeneratedQuestion[],
  lookups: Awaited<ReturnType<typeof getLookups>>,
  topicMap: Map<string, TopicRow>,
  chapterMap: Map<string, ChapterRow>,
  marks: number,
  typeName: QuestionTypeName,
  diffName: DifficultyName
): Promise<GeneratedQuestion[]> {
  // Separate real bank rows from already-generated AI items
  const bankRows = picks.filter(
    (p): p is QuestionRow => "question_type_id" in p
  );
  const aiItems = picks.filter(
    (p): p is GeneratedQuestion => "source" in p && p.source === "ai"
  );

  // Fetch MCQ options for bank rows of MCQ type
  const mcqBankIds = bankRows
    .filter((r) => lookups.byType[r.question_type_id] === "MCQ")
    .map((r) => r.id);
  const options = await getMcqOptions(mcqBankIds);
  const optByQ = new Map(options.map((o) => [o.question_id, o]));

  const enriched: GeneratedQuestion[] = bankRows.map((r) => ({
    id: r.id,
    source: "bank",
    question_text: r.question_text,
    type_name: typeName,
    difficulty_name: diffName,
    marks,
    blooms_taxonomy: r.blooms_taxonomy ?? null,
    tags: r.tags ?? null,
    topic_name: topicMap.get(r.topic_id)?.topic_name ?? null,
    chapter_name: chapterMap.get(r.chapter_id)?.chapter_name ?? null,
    options: optByQ.get(r.id)
      ? {
          option_a: optByQ.get(r.id)!.option_a,
          option_b: optByQ.get(r.id)!.option_b,
          option_c: optByQ.get(r.id)!.option_c,
          option_d: optByQ.get(r.id)!.option_d,
          correct_option: optByQ.get(r.id)!.correct_option,
        }
      : null,
  }));

  return [...enriched, ...aiItems];
}

/**
 * Generate multiple variants of the same test. All variants use the SAME
 * questions (equal marks) — the only difference is question order (shuffle).
 * This ensures variants are comparable for different student groups.
 */
export async function generateBatch(
  req: GenerateTestRequest,
  variantCount: number
): Promise<GeneratedTest[]> {
  if (variantCount <= 0) return [];

  // Generate the base test once
  const baseTest = await generateTest(req);

  if (variantCount === 1) {
    return [baseTest];
  }

  const variants: GeneratedTest[] = [baseTest];

  // Create additional variants by shuffling questions within each section
  for (let i = 1; i < variantCount; i++) {
    const shuffledSections = baseTest.sections.map((sec) => {
      const shuffledQuestions = shuffleArray(sec.questions);
      // Also shuffle MCQ options if the shuffle flag is on
      return {
        ...sec,
        questions: req.shuffle
          ? shuffledQuestions.map((q) => shuffleOptions(q))
          : shuffledQuestions,
      };
    });

    variants.push({
      ...baseTest,
      title: `${req.title} — Variant ${String.fromCharCode(65 + i)}`,
      sections: shuffledSections,
      generatedAt: new Date().toISOString(),
    });
  }

  return variants;
}
