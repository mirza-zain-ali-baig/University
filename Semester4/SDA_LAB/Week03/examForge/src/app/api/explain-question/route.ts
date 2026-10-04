import { NextResponse } from "next/server";
import ZAI from "z-ai-web-dev-sdk";
import type { GeneratedQuestion } from "@/lib/types";

export const dynamic = "force-dynamic";
export const maxDuration = 60;

/**
 * POST /api/explain-question
 * Body: { question: GeneratedQuestion, className, subjectName }
 * Returns: { explanation: string }
 *
 * Uses the LLM to generate a teaching explanation for why the correct answer
 * is correct — useful for answer keys, self-study, and teacher review.
 */
export async function POST(request: Request) {
  try {
    const body = (await request.json()) as {
      question: GeneratedQuestion;
      className?: string;
      subjectName?: string;
    };

    if (!body.question) {
      return NextResponse.json(
        { error: "question is required" },
        { status: 400 }
      );
    }

    const q = body.question;
    const zai = await ZAI.create();

    let prompt: string;
    if (q.options) {
      // MCQ explanation
      const correctText =
        q.options[
          `option_${q.options.correct_option.toLowerCase()}` as
            | "option_a"
            | "option_b"
            | "option_c"
            | "option_d"
        ];
      prompt = `You are an expert teacher. Explain why the correct answer to this MCQ is correct, in 2-3 sentences suitable for a student.

Question: ${q.question_text}
A. ${q.options.option_a}
B. ${q.options.option_b}
C. ${q.options.option_c}
D. ${q.options.option_d}
Correct answer: ${q.options.correct_option}. ${correctText}

Context: ${body.className ?? ""} ${body.subjectName ?? ""}

Write a clear, concise explanation. Do NOT repeat the question or options. Start directly with the explanation.`;
    } else {
      // Written answer explanation / model answer guidance
      prompt = `You are an expert teacher. Provide a brief teaching note (2-3 sentences) for this ${q.type_name} question, explaining what a good answer should cover.

Question: ${q.question_text}
${q.model_answer ? `Model answer: ${q.model_answer}` : ""}

Context: ${body.className ?? ""} ${body.subjectName ?? ""}

Write a clear, concise teaching note. Do NOT repeat the question. Start directly with the note.`;
    }

    const completion = await zai.chat.completions.create({
      messages: [
        {
          role: "assistant",
          content:
            "You are an expert educator who writes clear, concise teaching explanations.",
        },
        { role: "user", content: prompt },
      ],
      thinking: { type: "disabled" },
    });

    const explanation = completion.choices[0]?.message?.content?.trim() ?? "";

    if (!explanation) {
      return NextResponse.json(
        { error: "AI could not generate an explanation. Please try again." },
        { status: 500 }
      );
    }

    return NextResponse.json({ explanation });
  } catch (e) {
    return NextResponse.json(
      { error: e instanceof Error ? e.message : "Unknown error" },
      { status: 500 }
    );
  }
}
