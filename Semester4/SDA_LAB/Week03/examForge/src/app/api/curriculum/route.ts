import { NextResponse } from "next/server";
import { supabase } from "@/lib/supabase";
import { fetchAllQuestionKeys } from "@/lib/question-bank";
import type {
  ClassRow,
  SubjectRow,
  ChapterRow,
  TopicRow,
} from "@/lib/supabase";

export const dynamic = "force-dynamic";

/**
 * GET /api/curriculum
 * Optional query: ?classId=...&subjectId=...
 * Returns the class → subject → chapter → topic tree, with per-leaf question counts.
 */
export async function GET(request: Request) {
  try {
    const { searchParams } = new URL(request.url);
    const classId = searchParams.get("classId") ?? undefined;
    const subjectId = searchParams.get("subjectId") ?? undefined;

    // Classes
    let classQ = supabase.from("classes").select("*").order("class_name");
    if (classId) classQ = classQ.eq("id", classId);
    const { data: classData, error: ce } = await classQ;
    if (ce) throw new Error(ce.message);
    const classes = (classData as ClassRow[]) ?? [];

    // Subjects
    let subjQ = supabase.from("subjects").select("*").order("subject_name");
    if (classId) subjQ = subjQ.eq("class_id", classId);
    if (subjectId) subjQ = subjQ.eq("id", subjectId);
    const { data: subjData, error: se } = await subjQ;
    if (se) throw new Error(se.message);
    const subjects = (subjData as SubjectRow[]) ?? [];

    // Chapters for those subjects
    const subjectIds = subjects.map((s) => s.id);
    let chapters: ChapterRow[] = [];
    if (subjectIds.length) {
      const { data: chData, error: che } = await supabase
        .from("chapters")
        .select("*")
        .in("subject_id", subjectIds)
        .order("chapter_number");
      if (che) throw new Error(che.message);
      chapters = (chData as ChapterRow[]) ?? [];
    }

    // Topics for those chapters
    const chapterIds = chapters.map((c) => c.id);
    let topics: TopicRow[] = [];
    if (chapterIds.length) {
      const { data: tData, error: te } = await supabase
        .from("topics")
        .select("*")
        .in("chapter_id", chapterIds)
        .order("topic_article_no");
      if (te) throw new Error(te.message);
      topics = (tData as TopicRow[]) ?? [];
    }

    // Question counts per subject / chapter / topic (batched via one fetch)
    let countsByTopic: Record<string, number> = {};
    let countsByChapter: Record<string, number> = {};
    let countsBySubject: Record<string, number> = {};
    if (subjectIds.length) {
      // Paginated fetch to bypass Supabase's 1000-row cap → accurate counts
      const qData = await fetchAllQuestionKeys(subjectIds);
      for (const q of qData) {
        countsByTopic[q.topic_id] = (countsByTopic[q.topic_id] ?? 0) + 1;
        countsByChapter[q.chapter_id] = (countsByChapter[q.chapter_id] ?? 0) + 1;
        countsBySubject[q.subject_id] = (countsBySubject[q.subject_id] ?? 0) + 1;
      }
    }

    // Assemble tree
    const topicsByChapter = new Map<string, TopicRow[]>();
    for (const t of topics) {
      const arr = topicsByChapter.get(t.chapter_id) ?? [];
      arr.push(t);
      topicsByChapter.set(t.chapter_id, arr);
    }
    const chaptersBySubject = new Map<string, ChapterRow[]>();
    for (const c of chapters) {
      const arr = chaptersBySubject.get(c.subject_id) ?? [];
      arr.push(c);
      chaptersBySubject.set(c.subject_id, arr);
    }
    const subjectsByClass = new Map<string, SubjectRow[]>();
    for (const s of subjects) {
      const arr = subjectsByClass.get(s.class_id) ?? [];
      arr.push(s);
      subjectsByClass.set(s.class_id, arr);
    }

    const tree = classes.map((c) => ({
      ...c,
      questionCount: 0,
      subjects: (subjectsByClass.get(c.id) ?? []).map((s) => ({
        ...s,
        questionCount: countsBySubject[s.id] ?? 0,
        chapters: (chaptersBySubject.get(s.id) ?? []).map((ch) => ({
          ...ch,
          questionCount: countsByChapter[ch.id] ?? 0,
          topics: (topicsByChapter.get(ch.id) ?? []).map((t) => ({
            ...t,
            questionCount: countsByTopic[t.id] ?? 0,
          })),
        })),
      })),
    }));

    return NextResponse.json({ tree });
  } catch (e) {
    return NextResponse.json(
      { error: e instanceof Error ? e.message : "Unknown error" },
      { status: 500 }
    );
  }
}
