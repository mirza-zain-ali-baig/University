import { NextResponse } from "next/server";
import { generateBatch } from "@/lib/test-generator";
import type { GenerateTestRequest } from "@/lib/types";

export const dynamic = "force-dynamic";
export const maxDuration = 300; // allow up to 5 min for multi-variant + AI fill

/**
 * POST /api/generate-batch
 * Body: { request: GenerateTestRequest, variantCount: number }
 * Returns: { variants: GeneratedTest[] }
 *
 * Generates `variantCount` disjoint variants of the same blueprint. Bank
 * questions are not reused across variants. If the bank runs out, AI fill is
 * used (when source != "bank").
 */
export async function POST(request: Request) {
  try {
    const body = (await request.json()) as {
      request: GenerateTestRequest;
      variantCount: number;
    };

    if (!body.request?.classId || !body.request?.subjectId) {
      return NextResponse.json(
        { error: "classId and subjectId are required" },
        { status: 400 }
      );
    }
    const variantCount = Math.max(
      1,
      Math.min(parseInt(String(body.variantCount ?? "1"), 10) || 1, 6)
    );

    // Normalize optional questionSources filter on the nested request.
    if (Array.isArray(body.request.questionSources)) {
      body.request.questionSources = body.request.questionSources
        .map((s) => (typeof s === "string" ? s.trim() : ""))
        .filter((s) => s.length > 0);
      if (body.request.questionSources.length === 0) {
        delete body.request.questionSources;
      }
    }

    const variants = await generateBatch(body.request, variantCount);
    return NextResponse.json({ variants });
  } catch (e) {
    return NextResponse.json(
      { error: e instanceof Error ? e.message : "Unknown error" },
      { status: 500 }
    );
  }
}
