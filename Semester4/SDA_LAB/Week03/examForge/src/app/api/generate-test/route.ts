import { NextResponse } from "next/server";
import { generateTest } from "@/lib/test-generator";
import type { GenerateTestRequest } from "@/lib/types";

export const dynamic = "force-dynamic";

/**
 * POST /api/generate-test
 * Body: GenerateTestRequest
 * Returns: { test: GeneratedTest }
 */
export async function POST(request: Request) {
  try {
    const body = (await request.json()) as GenerateTestRequest;

    // Basic validation
    if (!body.classId || !body.subjectId) {
      return NextResponse.json(
        { error: "classId and subjectId are required" },
        { status: 400 }
      );
    }
    if (!body.blueprint) {
      return NextResponse.json(
        { error: "blueprint is required" },
        { status: 400 }
      );
    }
    const totalRequested = Object.values(body.blueprint).reduce(
      (s, t) =>
        s +
        (t.difficulties.Easy + t.difficulties.Medium + t.difficulties.Hard),
      0
    );
    if (totalRequested <= 0) {
      return NextResponse.json(
        { error: "Request at least one question in the blueprint" },
        { status: 400 }
      );
    }

    // Normalize optional questionSources filter: drop empty/null entries.
    // Empty array => use all sources (no filter).
    if (Array.isArray(body.questionSources)) {
      body.questionSources = body.questionSources
        .map((s) => (typeof s === "string" ? s.trim() : ""))
        .filter((s) => s.length > 0);
      if (body.questionSources.length === 0) {
        delete body.questionSources;
      }
    }

    const test = await generateTest(body);
    return NextResponse.json({ test });
  } catch (e) {
    return NextResponse.json(
      { error: e instanceof Error ? e.message : "Unknown error" },
      { status: 500 }
    );
  }
}
