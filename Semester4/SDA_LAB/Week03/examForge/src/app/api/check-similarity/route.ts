import { NextResponse } from "next/server";
import ZAI from "z-ai-web-dev-sdk";
import type { GeneratedQuestion } from "@/lib/types";

export const dynamic = "force-dynamic";
export const maxDuration = 60;

/**
 * POST /api/check-similarity
 * Body: { questions: GeneratedQuestion[] }
 * Returns: { pairs: [{ a, b, aText, bText, similarity: "high"|"medium"|"low", reason }] }
 *
 * Uses the LLM to detect near-duplicate or overly similar questions within a test.
 * This helps teachers avoid asking the same thing twice with different wording.
 */
export async function POST(request: Request) {
  try {
    const body = (await request.json()) as {
      questions: GeneratedQuestion[];
    };

    if (!body.questions || body.questions.length < 2) {
      return NextResponse.json({ pairs: [] });
    }

    // Limit to first 30 questions to keep the prompt manageable
    const qs = body.questions.slice(0, 30);

    const zai = await ZAI.create();

    // Build a compact list of questions for the LLM
    const questionList = qs
      .map((q, i) => `${i + 1}. [${q.type_name}/${q.difficulty_name}] ${q.question_text}`)
      .join("\n");

    const prompt = `You are an expert exam reviewer. Analyze the following ${qs.length} exam questions and identify pairs that are near-duplicates or overly similar (i.e., testing the same concept with very similar wording or asking essentially the same thing).

Questions:
${questionList}

Rules:
- Only flag pairs with meaningful similarity (not just sharing a keyword).
- "high" = near-duplicate (same question rephrased), "medium" = significant overlap in concept/answer, "low" = related but acceptable.
- Return at most 8 pairs, prioritized by similarity level.
- If no similar pairs exist, return an empty array.

Return STRICT JSON ONLY (no markdown, no commentary) in this exact shape:
{"pairs":[{"a":1,"b":2,"similarity":"high","reason":"Both ask about the definition of an operating system"}]}

The "a" and "b" values are the 1-based question numbers from the list above.`;

    const completion = await zai.chat.completions.create({
      messages: [
        {
          role: "assistant",
          content:
            "You are a precise JSON generator for exam quality analysis. Output only valid JSON.",
        },
        { role: "user", content: prompt },
      ],
      thinking: { type: "disabled" },
    });

    const raw = completion.choices[0]?.message?.content ?? "";
    const parsed = safeParse(raw);

    if (!parsed?.pairs || !Array.isArray(parsed.pairs)) {
      return NextResponse.json({ pairs: [] });
    }

    // Map back to question IDs and texts
    const pairs = parsed.pairs
      .filter(
        (p: { a?: number; b?: number }) =>
          p.a >= 1 && p.a <= qs.length && p.b >= 1 && p.b <= qs.length
      )
      .map((p: { a: number; b: number; similarity?: string; reason?: string }) => ({
        a: qs[p.a - 1].id,
        b: qs[p.b - 1].id,
        aIndex: p.a - 1,
        bIndex: p.b - 1,
        aText: qs[p.a - 1].question_text,
        bText: qs[p.b - 1].question_text,
        similarity: (p.similarity ?? "medium") as "high" | "medium" | "low",
        reason: p.reason ?? "Similar question content",
      }));

    return NextResponse.json({ pairs });
  } catch (e) {
    return NextResponse.json(
      { error: e instanceof Error ? e.message : "Unknown error" },
      { status: 500 }
    );
  }
}

function safeParse(raw: string): { pairs?: unknown[] } | null {
  let text = raw.trim();
  const fence = text.match(/```(?:json)?\s*([\s\S]*?)```/i);
  if (fence) text = fence[1].trim();
  const first = text.indexOf("{");
  const last = text.lastIndexOf("}");
  if (first !== -1 && last !== -1 && last > first) {
    text = text.slice(first, last + 1);
  }
  try {
    return JSON.parse(text);
  } catch {
    return null;
  }
}
