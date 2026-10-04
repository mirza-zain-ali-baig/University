import { NextResponse } from "next/server";
import { db } from "@/lib/db";
import type { GeneratedTest } from "@/lib/types";

export const dynamic = "force-dynamic";

/**
 * GET /api/history
 * Aggregates saved-test history for the analytics dashboard:
 * - total tests, total questions, total marks
 * - generation trend (last 14 days)
 * - source breakdown (bank / hybrid / ai)
 * - class/subject distribution
 * - marks-per-test distribution
 */
export async function GET() {
  try {
    const tests = await db.generatedTest.findMany({
      orderBy: { createdAt: "desc" },
    });

    let totalQuestions = 0;
    let totalMarks = 0;
    const sourceCount: Record<string, number> = { bank: 0, hybrid: 0, ai: 0 };
    const classCount: Record<string, number> = {};
    const subjectCount: Record<string, number> = {};
    const marksBuckets: { range: string; count: number }[] = [
      { range: "1-10", count: 0 },
      { range: "11-25", count: 0 },
      { range: "26-50", count: 0 },
      { range: "51-100", count: 0 },
      { range: "100+", count: 0 },
    ];

    // Last 14 days trend
    const trend: { date: string; label: string; count: number }[] = [];
    const now = new Date();
    for (let i = 13; i >= 0; i--) {
      const d = new Date(now);
      d.setDate(d.getDate() - i);
      d.setHours(0, 0, 0, 0);
      const dateStr = d.toISOString().slice(0, 10);
      const label = d.toLocaleDateString(undefined, { month: "short", day: "numeric" });
      trend.push({ date: dateStr, label, count: 0 });
    }
    const trendMap = new Map(trend.map((t) => [t.date, t]));

    for (const t of tests) {
      try {
        const parsed = JSON.parse(t.testJson) as GeneratedTest;
        totalQuestions += parsed.totalQuestions;
        totalMarks += parsed.totalMarks;
        sourceCount[t.source] = (sourceCount[t.source] ?? 0) + 1;

        const ck = parsed.className || "Unknown";
        classCount[ck] = (classCount[ck] ?? 0) + 1;

        const sk = parsed.subjectName || "Unknown";
        subjectCount[sk] = (subjectCount[sk] ?? 0) + 1;

        // Marks buckets
        const m = parsed.totalMarks;
        if (m <= 10) marksBuckets[0].count++;
        else if (m <= 25) marksBuckets[1].count++;
        else if (m <= 50) marksBuckets[2].count++;
        else if (m <= 100) marksBuckets[3].count++;
        else marksBuckets[4].count++;

        // Trend
        const dateStr = t.createdAt.toISOString().slice(0, 10);
        const trendEntry = trendMap.get(dateStr);
        if (trendEntry) trendEntry.count++;
      } catch {
        // skip corrupted
      }
    }

    const bySource = Object.entries(sourceCount)
      .filter(([, c]) => c > 0)
      .map(([name, count]) => ({ name, count }));

    const byClass = Object.entries(classCount)
      .map(([name, count]) => ({ name, count }))
      .sort((a, b) => b.count - a.count);

    const bySubject = Object.entries(subjectCount)
      .map(([name, count]) => ({ name, count }))
      .sort((a, b) => b.count - a.count);

    return NextResponse.json({
      totalTests: tests.length,
      totalQuestions,
      totalMarks,
      trend,
      bySource,
      byClass,
      bySubject,
      marksBuckets,
      avgMarks: tests.length > 0 ? Math.round(totalMarks / tests.length) : 0,
      avgQuestions: tests.length > 0 ? Math.round(totalQuestions / tests.length) : 0,
    });
  } catch (e) {
    return NextResponse.json(
      { error: e instanceof Error ? e.message : "Unknown error" },
      { status: 500 }
    );
  }
}
