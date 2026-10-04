import { NextResponse } from "next/server";
import { supabase } from "@/lib/supabase";

export const dynamic = "force-dynamic";

/**
 * GET /api/question-sources
 * Returns the distinct `question_from` values and their counts, scoped by the
 * given subject/chapter/topic filter. Used by the Blueprint step to render
 * source-filter checkboxes with live count badges.
 *
 * Query params:
 *  - subjectId (required)
 *  - chapterIds (comma separated, optional)
 *  - topicIds (comma separated, optional)
 *
 * Returns:
 *   { sources: { name: string; count: number }[], total: number, nullCount: number }
 */
export async function GET(request: Request) {
  try {
    const { searchParams } = new URL(request.url);
    const subjectId = searchParams.get("subjectId") ?? undefined;
    const chapterIds = searchParams
      .get("chapterIds")
      ?.split(",")
      .filter(Boolean);
    const topicIds = searchParams
      .get("topicIds")
      ?.split(",")
      .filter(Boolean);

    if (!subjectId) {
      return NextResponse.json(
        { error: "subjectId is required" },
        { status: 400 }
      );
    }

    // Paginate past Supabase's 1000-row hard cap so counts are accurate even for
    // large subjects. We only need the `question_from` column.
    const PAGE = 1000;
    let offset = 0;
    const counts = new Map<string, number>();
    let nullCount = 0;
    let total = 0;

    while (true) {
      let q = supabase
        .from("questions")
        .select("question_from")
        .eq("subject_id", subjectId);
      if (chapterIds && chapterIds.length) q = q.in("chapter_id", chapterIds);
      if (topicIds && topicIds.length) q = q.in("topic_id", topicIds);
      q = q.order("id", { ascending: true }).range(offset, offset + PAGE - 1);
      const { data, error } = await q;
      if (error) throw new Error(error.message);
      const rows = (data as { question_from: string | null }[]) ?? [];
      for (const r of rows) {
        total += 1;
        if (r.question_from == null || r.question_from === "") {
          nullCount += 1;
        } else {
          counts.set(
            r.question_from,
            (counts.get(r.question_from) ?? 0) + 1
          );
        }
      }
      if (rows.length < PAGE) break;
      offset += PAGE;
    }

    const sources = Array.from(counts.entries())
      .map(([name, count]) => ({ name, count }))
      .sort((a, b) => b.count - a.count);

    return NextResponse.json({
      sources,
      total,
      nullCount,
    });
  } catch (e) {
    return NextResponse.json(
      { error: e instanceof Error ? e.message : "Unknown error" },
      { status: 500 }
    );
  }
}
