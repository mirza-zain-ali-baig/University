import { NextResponse } from "next/server";
import { generateAIQuestions } from "@/lib/ai-questions";
import type { QuestionTypeName, DifficultyName } from "@/lib/types";

export const dynamic = "force-dynamic";
export const maxDuration = 60;

/**
 * POST /api/regenerate-question
 * Body: { subjectName, className, chapterName?, topicName?, typeName, difficultyName, marks }
 * Returns: { question: GeneratedQuestion }
 *
 * Generates a single fresh AI question to replace an existing one in a test.
 */
export async function POST(request: Request) {
  try {
    const body = (await request.json()) as {
      subjectName: string;
      className: string;
      chapterName?: string;
      topicName?: string;
      typeName: QuestionTypeName;
      difficultyName: DifficultyName;
      marks: number;
    };

    if (!body.subjectName || !body.className || !body.typeName || !body.difficultyName) {
      return NextResponse.json(
        { error: "subjectName, className, typeName and difficultyName are required" },
        { status: 400 }
      );
    }

    const questions = await generateAIQuestions({
      subjectName: body.subjectName,
      className: body.className,
      chapterName: body.chapterName,
      topicName: body.topicName,
      typeName: body.typeName,
      difficultyName: body.difficultyName,
      count: 1,
      marks: body.marks,
    });

    if (questions.length === 0) {
      return NextResponse.json(
        { error: "AI could not generate a question. Please try again." },
        { status: 500 }
      );
    }

    return NextResponse.json({ question: questions[0] });
  } catch (e) {
    return NextResponse.json(
      { error: e instanceof Error ? e.message : "Unknown error" },
      { status: 500 }
    );
  }
}
