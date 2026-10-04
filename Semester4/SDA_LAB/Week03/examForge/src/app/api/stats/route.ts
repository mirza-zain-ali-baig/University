import { NextResponse } from "next/server";
import { supabase } from "@/lib/supabase";

export const dynamic = "force-dynamic";

/**
 * GET /api/stats
 * Aggregated dashboard statistics from the Supabase question bank.
 */
export async function GET() {
  try {
    const [classes, subjects, chapters, topics, questions, types, diffs] =
      await Promise.all([
        supabase.from("classes").select("*", { count: "exact", head: true }),
        supabase.from("subjects").select("*", { count: "exact", head: true }),
        supabase.from("chapters").select("*", { count: "exact", head: true }),
        supabase.from("topics").select("*", { count: "exact", head: true }),
        supabase.from("questions").select("*", { count: "exact", head: true }),
        supabase.from("question_types").select("*"),
        supabase.from("difficulty_levels").select("*"),
      ]);

    const error =
      classes.error ||
      subjects.error ||
      chapters.error ||
      topics.error ||
      questions.error ||
      types.error ||
      diffs.error;
    if (error) throw new Error(error.message);

    const typeRows = (types.data as { id: string; name: string }[]) ?? [];
    const diffRows = (diffs.data as { id: string; name: string }[]) ?? [];

    const [byType, byDifficulty, byBloom] = await Promise.all([
      Promise.all(
        typeRows.map(async (t) => {
          const { count } = await supabase
            .from("questions")
            .select("*", { count: "exact", head: true })
            .eq("question_type_id", t.id);
          return { name: t.name, count: count ?? 0 };
        })
      ),
      Promise.all(
        diffRows.map(async (d) => {
          const { count } = await supabase
            .from("questions")
            .select("*", { count: "exact", head: true })
            .eq("difficulty_level_id", d.id);
          return { name: d.name, count: count ?? 0 };
        })
      ),
      (async () => {
        const { data } = await supabase
          .from("questions")
          .select("blooms_taxonomy");
        const map = new Map<string, number>();
        for (const r of data ?? []) {
          const k =
            (r as { blooms_taxonomy: string | null }).blooms_taxonomy ??
            "Unspecified";
          map.set(k, (map.get(k) ?? 0) + 1);
        }
        return Array.from(map.entries())
          .map(([name, count]) => ({ name, count }))
          .sort((a, b) => b.count - a.count);
      })(),
    ]);

    return NextResponse.json({
      counts: {
        classes: classes.count ?? 0,
        subjects: subjects.count ?? 0,
        chapters: chapters.count ?? 0,
        topics: topics.count ?? 0,
        questions: questions.count ?? 0,
      },
      byType,
      byDifficulty,
      byBloom,
    });
  } catch (e) {
    return NextResponse.json(
      { error: e instanceof Error ? e.message : "Unknown error" },
      { status: 500 }
    );
  }
}
