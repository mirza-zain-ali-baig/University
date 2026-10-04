import { NextResponse } from "next/server";
import { db } from "@/lib/db";
import type { GeneratedTest } from "@/lib/types";

export const dynamic = "force-dynamic";

/**
 * GET /api/test-overlap
 * Analyzes all saved tests and reports question-overlap between every pair.
 * Returns: { pairs: [{ a, b, aTitle, bTitle, shared, sharedIds }], maxShared }
 */
export async function GET() {
  try {
    const tests = await db.generatedTest.findMany({
      orderBy: { createdAt: "desc" },
    });

    const parsed = tests
      .map((t) => {
        try {
          const p = JSON.parse(t.testJson) as GeneratedTest;
          const ids = new Set(
            p.sections.flatMap((s) => s.questions.map((q) => q.id))
          );
          return { id: t.id, title: t.title, ids };
        } catch {
          return null;
        }
      })
      .filter((x): x is { id: string; title: string; ids: Set<string> } => !!x);

    const pairs: {
      a: string;
      b: string;
      aTitle: string;
      bTitle: string;
      shared: number;
      sharedIds: string[];
    }[] = [];

    let maxShared = 0;

    for (let i = 0; i < parsed.length; i++) {
      for (let j = i + 1; j < parsed.length; j++) {
        const a = parsed[i];
        const b = parsed[j];
        const sharedIds = [...a.ids].filter((id) => b.ids.has(id));
        if (sharedIds.length > 0) {
          pairs.push({
            a: a.id,
            b: b.id,
            aTitle: a.title,
            bTitle: b.title,
            shared: sharedIds.length,
            sharedIds,
          });
          if (sharedIds.length > maxShared) maxShared = sharedIds.length;
        }
      }
    }

    pairs.sort((x, y) => y.shared - x.shared);

    return NextResponse.json({ pairs, maxShared, totalTests: parsed.length });
  } catch (e) {
    return NextResponse.json(
      { error: e instanceof Error ? e.message : "Unknown error" },
      { status: 500 }
    );
  }
}
