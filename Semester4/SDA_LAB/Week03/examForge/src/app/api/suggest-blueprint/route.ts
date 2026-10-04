import { NextResponse } from "next/server";
import ZAI from "z-ai-web-dev-sdk";
import type { Blueprint, QuestionTypeName, DifficultyName } from "@/lib/types";

export const dynamic = "force-dynamic";
export const maxDuration = 60;

/**
 * POST /api/suggest-blueprint
 * Body: { totalMarks, difficultyTarget, className, subjectName, chapters }
 * Returns: { blueprint: Blueprint, rationale: string }
 *
 * Uses the LLM to suggest an optimal blueprint (question counts per type×difficulty
 * and marks per question) given a target total marks and difficulty profile.
 */
export async function POST(request: Request) {
  try {
    const body = (await request.json()) as {
      totalMarks: number;
      difficultyTarget: "easy" | "balanced" | "hard" | "exam";
      className: string;
      subjectName: string;
      chapters?: string[];
    };

    if (!body.totalMarks || body.totalMarks < 1) {
      return NextResponse.json(
        { error: "totalMarks must be >= 1" },
        { status: 400 }
      );
    }

    const zai = await ZAI.create();

    const profiles: Record<string, { label: string; desc: string }> = {
      easy: { label: "Easy-leaning", desc: "Mostly Easy questions for practice/revision (≈60% Easy, 30% Medium, 10% Hard)" },
      balanced: { label: "Balanced", desc: "Even mix of difficulties (≈40% Easy, 40% Medium, 20% Hard)" },
      hard: { label: "Rigorous", desc: "Challenging exam with emphasis on analysis (≈20% Easy, 30% Medium, 50% Hard)" },
      exam: { label: "Board Exam Style", desc: "Standard board exam distribution with MCQ, Short, and Long sections" },
    };
    const profile = profiles[body.difficultyTarget] ?? profiles.balanced;

    const prompt = `You are an expert examination designer for school-level computer science.
Design a test blueprint for the following:

Class: ${body.className}
Subject: ${body.subjectName}
Target total marks: ${body.totalMarks}
Difficulty profile: ${profile.label} — ${profile.desc}

Rules:
- Use three question types: MCQ (1 mark each), Short (3 marks each), Long (5 marks each).
- Distribute the total marks across types and difficulties so the SUM of all (count × marksPerQuestion) equals exactly ${body.totalMarks}.
- For a board-exam style, aim for roughly 40% MCQ, 30% Short, 30% Long marks. For others, prioritize the difficulty profile.
- Counts must be non-negative integers.
- Difficulty names are exactly: Easy, Medium, Hard.

Return STRICT JSON ONLY (no markdown, no commentary) in this exact shape:
{
  "blueprint": {
    "MCQ": { "marksPerQuestion": 1, "difficulties": { "Easy": 0, "Medium": 0, "Hard": 0 } },
    "Short": { "marksPerQuestion": 3, "difficulties": { "Easy": 0, "Medium": 0, "Hard": 0 } },
    "Long": { "marksPerQuestion": 5, "difficulties": { "Easy": 0, "Medium": 0, "Hard": 0 } }
  },
  "rationale": "1-2 sentence explanation of the distribution choice"
}`;

    const completion = await zai.chat.completions.create({
      messages: [
        {
          role: "assistant",
          content:
            "You are a precise JSON generator for exam blueprints. Output only valid JSON.",
        },
        { role: "user", content: prompt },
      ],
      thinking: { type: "disabled" },
    });

    const raw = completion.choices[0]?.message?.content ?? "";
    const parsed = safeParse(raw);

    if (!parsed?.blueprint) {
      return NextResponse.json(
        { error: "AI could not generate a valid blueprint. Please try again." },
        { status: 500 }
      );
    }

    // Validate and clamp
    const bp = normalizeBlueprint(parsed.blueprint);
    return NextResponse.json({
      blueprint: bp,
      rationale: parsed.rationale ?? "AI-suggested distribution.",
    });
  } catch (e) {
    return NextResponse.json(
      { error: e instanceof Error ? e.message : "Unknown error" },
      { status: 500 }
    );
  }
}

function safeParse(raw: string): {
  blueprint?: Blueprint;
  rationale?: string;
} | null {
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

function normalizeBlueprint(bp: Partial<Blueprint>): Blueprint {
  const types: QuestionTypeName[] = ["MCQ", "Short", "Long"];
  const diffs: DifficultyName[] = ["Easy", "Medium", "Hard"];
  const defaultMarks: Record<QuestionTypeName, number> = {
    MCQ: 1,
    Short: 3,
    Long: 5,
  };
  const out = {} as Blueprint;
  for (const t of types) {
    const cfg = bp[t] ?? { marksPerQuestion: defaultMarks[t], difficulties: {} };
    out[t] = {
      marksPerQuestion: Math.max(1, cfg.marksPerQuestion ?? defaultMarks[t]),
      difficulties: {
        Easy: clamp(diffs[0], cfg.difficulties),
        Medium: clamp(diffs[1], cfg.difficulties),
        Hard: clamp(diffs[2], cfg.difficulties),
      },
    };
  }
  return out;
}

function clamp(d: DifficultyName, obj?: Partial<Record<DifficultyName, number>>): number {
  const v = obj?.[d] ?? 0;
  const n = Math.round(Number(v));
  return Number.isFinite(n) && n >= 0 ? n : 0;
}
