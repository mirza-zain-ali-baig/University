import { NextResponse } from "next/server";
import { supabase } from "@/lib/supabase";
import { getLookups, getMcqOptions } from "@/lib/question-bank";
import type { QuestionRow } from "@/lib/supabase";

export const dynamic = "force-dynamic";

/**
 * GET /api/questions
 * DB-side filtering + pagination + exact count in a single query.
 *
 * Query params:
 *  - subjectId
 *  - chapterIds (comma separated)
 *  - topicIds (comma separated)
 *  - questionType (name: MCQ|Short|Long)
 *  - difficulty (name: Easy|Medium|Hard)
 *  - search (case-insensitive across question_text / tags / blooms_taxonomy)
 *  - limit (default 50, max 100)
 *  - offset (default 0)
 */
export async function GET(request: Request) {
  try {
    const { searchParams } = new URL(request.url);
    const subjectId = searchParams.get("subjectId") ?? undefined;
    const chapterIds = searchParams.get("chapterIds")?.split(",").filter(Boolean);
    const topicIds = searchParams.get("topicIds")?.split(",").filter(Boolean);
    const typeName = searchParams.get("questionType") ?? undefined;
    const diffName = searchParams.get("difficulty") ?? undefined;
    const search = searchParams.get("search")?.trim() || undefined;
    const limit = Math.min(
      Math.max(parseInt(searchParams.get("limit") ?? "50", 10) || 50, 1),
      100
    );
    const offset = Math.max(parseInt(searchParams.get("offset") ?? "0", 10) || 0, 0);

    const lookups = await getLookups();
    const questionTypeId = typeName ? lookups.typeIdByName[typeName] : undefined;
    const difficultyId = diffName ? lookups.difficultyIdByName[diffName] : undefined;

    let q = supabase
      .from("questions")
      .select("*", { count: "exact" });

    if (subjectId) q = q.eq("subject_id", subjectId);
    if (chapterIds && chapterIds.length) q = q.in("chapter_id", chapterIds);
    if (topicIds && topicIds.length) q = q.in("topic_id", topicIds);
    if (questionTypeId) q = q.eq("question_type_id", questionTypeId);
    if (difficultyId) q = q.eq("difficulty_level_id", difficultyId);
    if (search) {
      // case-insensitive OR across three text columns
      const term = search.replace(/,/g, "\\,").replace(/%/g, "\\%");
      q = q.or(
        `question_text.ilike.%${term}%,tags.ilike.%${term}%,blooms_taxonomy.ilike.%${term}%`
      );
    }

    q = q.order("created_at", { ascending: true }).range(offset, offset + limit - 1);

    const { data, count, error } = await q;
    if (error) throw new Error(error.message);

    const rows = (data as QuestionRow[]) ?? [];
    const enriched = await enrichPage(rows, lookups);

    return NextResponse.json({
      questions: enriched,
      total: count ?? 0,
      limit,
      offset,
    });
  } catch (e) {
    return NextResponse.json(
      { error: e instanceof Error ? e.message : "Unknown error" },
      { status: 500 }
    );
  }
}

async function enrichPage(
  rows: QuestionRow[],
  lookups: Awaited<ReturnType<typeof getLookups>>
) {
  // resolve topic + chapter names for this page
  const topicIds = [...new Set(rows.map((r) => r.topic_id))];
  const chapterIds = [...new Set(rows.map((r) => r.chapter_id))];
  const [topicsRes, chaptersRes] = await Promise.all([
    topicIds.length
      ? supabase.from("topics").select("id,topic_name").in("id", topicIds)
      : Promise.resolve({ data: [], error: null }),
    chapterIds.length
      ? supabase.from("chapters").select("id,chapter_name").in("id", chapterIds)
      : Promise.resolve({ data: [], error: null }),
  ]);
  const topicMap = new Map(
    ((topicsRes.data as { id: string; topic_name: string }[]) ?? []).map((t) => [
      t.id,
      t.topic_name,
    ])
  );
  const chapterMap = new Map(
    ((chaptersRes.data as { id: string; chapter_name: string }[]) ?? []).map((c) => [
      c.id,
      c.chapter_name,
    ])
  );

  // MCQ options
  const mcqIds = rows
    .filter((r) => lookups.byType[r.question_type_id] === "MCQ")
    .map((r) => r.id);
  const options = await getMcqOptions(mcqIds);
  const optByQ = new Map(options.map((o) => [o.question_id, o]));

  return rows.map((r) => ({
    id: r.id,
    question_text: r.question_text,
    type_name: lookups.byType[r.question_type_id] ?? "Unknown",
    difficulty_name: lookups.byDifficulty[r.difficulty_level_id] ?? "Unknown",
    marks: r.marks,
    blooms_taxonomy: r.blooms_taxonomy ?? null,
    tags: r.tags ?? null,
    topic_name: topicMap.get(r.topic_id) ?? null,
    chapter_name: chapterMap.get(r.chapter_id) ?? null,
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
}
