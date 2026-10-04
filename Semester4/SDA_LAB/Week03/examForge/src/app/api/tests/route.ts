import { NextResponse } from "next/server";
import { db } from "@/lib/db";
import type { GeneratedTest } from "@/lib/types";

export const dynamic = "force-dynamic";

/**
 * GET /api/tests            — list saved tests
 * POST /api/tests           — save a generated test
 */
export async function GET() {
  try {
    const tests = await db.generatedTest.findMany({
      orderBy: { createdAt: "desc" },
    });
    return NextResponse.json({ tests });
  } catch (e) {
    return NextResponse.json(
      { error: e instanceof Error ? e.message : "Unknown error" },
      { status: 500 }
    );
  }
}

export async function POST(request: Request) {
  try {
    const body = (await request.json()) as {
      test: GeneratedTest;
      source?: string;
    };
    if (!body.test) {
      return NextResponse.json({ error: "test is required" }, { status: 400 });
    }
    const t = body.test;
    const created = await db.generatedTest.create({
      data: {
        title: t.title || "Untitled Test",
        className: t.className,
        subjectName: t.subjectName,
        totalMarks: t.totalMarks,
        durationMins: t.durationMins,
        instructions: t.instructions ?? "",
        testJson: JSON.stringify(t),
        source: body.source ?? t.source,
      },
    });
    return NextResponse.json({ test: created });
  } catch (e) {
    return NextResponse.json(
      { error: e instanceof Error ? e.message : "Unknown error" },
      { status: 500 }
    );
  }
}
