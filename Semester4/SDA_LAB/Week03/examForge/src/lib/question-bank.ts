import { supabase } from "./supabase";
import type {
  ClassRow,
  SubjectRow,
  ChapterRow,
  TopicRow,
  QuestionTypeRow,
  DifficultyRow,
  QuestionRow,
  McqOptionRow,
} from "./supabase";

/* ----------------------- In-memory lookup caches ----------------------- */

type Lookups = {
  types: QuestionTypeRow[];
  difficulties: DifficultyRow[];
  byType: Record<string, string>; // id -> name
  byDifficulty: Record<string, string>; // id -> name
  typeIdByName: Record<string, string>; // name -> id
  difficultyIdByName: Record<string, string>; // name -> id
};

let lookupsCache: Lookups | null = null;

export async function getLookups(): Promise<Lookups> {
  if (lookupsCache) return lookupsCache;
  const [typesRes, diffRes] = await Promise.all([
    supabase.from("question_types").select("*"),
    supabase.from("difficulty_levels").select("*"),
  ]);
  const types = (typesRes.data as QuestionTypeRow[]) ?? [];
  const difficulties = (diffRes.data as DifficultyRow[]) ?? [];
  lookupsCache = {
    types,
    difficulties,
    byType: Object.fromEntries(types.map((t) => [t.id, t.name])),
    byDifficulty: Object.fromEntries(difficulties.map((d) => [d.id, d.name])),
    typeIdByName: Object.fromEntries(types.map((t) => [t.name, t.id])),
    difficultyIdByName: Object.fromEntries(difficulties.map((d) => [d.name, d.id])),
  };
  return lookupsCache;
}

/* ----------------------------- Hierarchy ------------------------------- */

export async function getClasses(): Promise<ClassRow[]> {
  const { data, error } = await supabase
    .from("classes")
    .select("*")
    .order("class_name", { ascending: true });
  if (error) throw new Error(error.message);
  return (data as ClassRow[]) ?? [];
}

export async function getSubjectsByClass(classId: string): Promise<SubjectRow[]> {
  const { data, error } = await supabase
    .from("subjects")
    .select("*")
    .eq("class_id", classId)
    .order("subject_name", { ascending: true });
  if (error) throw new Error(error.message);
  return (data as SubjectRow[]) ?? [];
}

export async function getSubjects(): Promise<SubjectRow[]> {
  const { data, error } = await supabase
    .from("subjects")
    .select("*")
    .order("subject_name", { ascending: true });
  if (error) throw new Error(error.message);
  return (data as SubjectRow[]) ?? [];
}

export async function getChapters(subjectId: string): Promise<ChapterRow[]> {
  const { data, error } = await supabase
    .from("chapters")
    .select("*")
    .eq("subject_id", subjectId)
    .order("chapter_number", { ascending: true });
  if (error) throw new Error(error.message);
  return (data as ChapterRow[]) ?? [];
}

export async function getTopics(chapterIds: string[]): Promise<TopicRow[]> {
  if (chapterIds.length === 0) return [];
  const { data, error } = await supabase
    .from("topics")
    .select("*")
    .in("chapter_id", chapterIds)
    .order("topic_article_no", { ascending: true });
  if (error) throw new Error(error.message);
  return (data as TopicRow[]) ?? [];
}

/* ----------------------------- Questions ------------------------------- */

export type QuestionFilter = {
  subjectId?: string;
  chapterIds?: string[];
  topicIds?: string[];
  questionTypeId?: string;
  difficultyId?: string;
};

export async function getQuestions(
  filter: QuestionFilter
): Promise<QuestionRow[]> {
  let q = supabase.from("questions").select("*");
  if (filter.subjectId) q = q.eq("subject_id", filter.subjectId);
  if (filter.chapterIds && filter.chapterIds.length)
    q = q.in("chapter_id", filter.chapterIds);
  if (filter.topicIds && filter.topicIds.length)
    q = q.in("topic_id", filter.topicIds);
  if (filter.questionTypeId) q = q.eq("question_type_id", filter.questionTypeId);
  if (filter.difficultyId) q = q.eq("difficulty_level_id", filter.difficultyId);
  q = q.order("created_at", { ascending: true }).limit(1000);
  const { data, error } = await q;
  if (error) throw new Error(error.message);
  return (data as QuestionRow[]) ?? [];
}

/**
 * Fetch ALL question keys (id + foreign keys) for the given subjects,
 * paginating past Supabase's 1000-row hard cap. Used for accurate counts.
 */
export async function fetchAllQuestionKeys(subjectIds: string[]): Promise<
  { id: string; subject_id: string; chapter_id: string; topic_id: string }[]
> {
  if (subjectIds.length === 0) return [];
  const PAGE = 1000;
  let offset = 0;
  const out: {
    id: string;
    subject_id: string;
    chapter_id: string;
    topic_id: string;
  }[] = [];
  while (true) {
    const { data, error } = await supabase
      .from("questions")
      .select("id,subject_id,chapter_id,topic_id")
      .in("subject_id", subjectIds)
      .order("id", { ascending: true })
      .range(offset, offset + PAGE - 1);
    if (error) throw new Error(error.message);
    const rows =
      (data as {
        id: string;
        subject_id: string;
        chapter_id: string;
        topic_id: string;
      }[]) ?? [];
    out.push(...rows);
    if (rows.length < PAGE) break;
    offset += PAGE;
  }
  return out;
}

export async function countQuestions(filter: QuestionFilter): Promise<number> {
  let q = supabase.from("questions").select("id", { count: "exact", head: true });
  if (filter.subjectId) q = q.eq("subject_id", filter.subjectId);
  if (filter.chapterIds && filter.chapterIds.length)
    q = q.in("chapter_id", filter.chapterIds);
  if (filter.topicIds && filter.topicIds.length)
    q = q.in("topic_id", filter.topicIds);
  if (filter.questionTypeId) q = q.eq("question_type_id", filter.questionTypeId);
  if (filter.difficultyId) q = q.eq("difficulty_level_id", filter.difficultyId);
  const { count, error } = await q;
  if (error) throw new Error(error.message);
  return count ?? 0;
}

export async function getMcqOptions(questionIds: string[]): Promise<McqOptionRow[]> {
  if (questionIds.length === 0) return [];
  const { data, error } = await supabase
    .from("mcq_options")
    .select("*")
    .in("question_id", questionIds);
  if (error) throw new Error(error.message);
  return (data as McqOptionRow[]) ?? [];
}

/* ----------------------- Enriched question shape ----------------------- */

export type EnrichedQuestion = QuestionRow & {
  type_name: string;
  difficulty_name: string;
  options: McqOptionRow | null;
  topic_name: string | null;
  chapter_name: string | null;
};

export async function enrichQuestions(
  questions: QuestionRow[],
  topicMap?: Map<string, TopicRow>,
  chapterMap?: Map<string, ChapterRow>
): Promise<EnrichedQuestion[]> {
  const lookups = await getLookups();
  const mcqIds = questions
    .filter((q) => lookups.byType[q.question_type_id] === "MCQ")
    .map((q) => q.id);
  const options = await getMcqOptions(mcqIds);
  const optByQ = new Map(options.map((o) => [o.question_id, o]));

  return questions.map((q) => ({
    ...q,
    type_name: lookups.byType[q.question_type_id] ?? "Unknown",
    difficulty_name: lookups.byDifficulty[q.difficulty_level_id] ?? "Unknown",
    options: optByQ.get(q.id) ?? null,
    topic_name: topicMap?.get(q.topic_id)?.topic_name ?? null,
    chapter_name: chapterMap?.get(q.chapter_id)?.chapter_name ?? null,
  }));
}
