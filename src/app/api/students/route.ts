import { db } from "@/db";
import { students } from "@/db/schema";
import { asc, desc, eq, ilike, or } from "drizzle-orm";
import { NextRequest } from "next/server";

export async function GET(request: NextRequest) {
  const search = request.nextUrl.searchParams.get("search")?.trim();
  const sort = request.nextUrl.searchParams.get("sort") ?? "registration";
  const order = sort === "name" ? asc(students.name) : sort === "cgpa" ? desc(students.cgpa) : asc(students.registrationNumber);
  const where = search
    ? or(
        ilike(students.registrationNumber, `%${search}%`),
        ilike(students.name, `%${search}%`),
        ilike(students.department, `%${search}%`)
      )
    : undefined;

  const rows = await db.select().from(students).where(where).orderBy(order).limit(150);
  return Response.json(rows);
}

export async function POST(request: NextRequest) {
  const body = await request.json() as {
    registrationNumber: string; name: string; department: string; semester: number; section: string;
    email: string; phone: string; cgpa?: number; photoUrl?: string;
  };
  if (!body.registrationNumber || !body.name || !body.department || !body.email) {
    return Response.json({ message: "Registration number, name, department, and email are required." }, { status: 400 });
  }
  const [created] = await db.insert(students).values({
    registrationNumber: body.registrationNumber,
    name: body.name,
    department: body.department,
    semester: Number(body.semester),
    section: body.section || "A",
    email: body.email,
    phone: body.phone || "",
    cgpa: String(body.cgpa ?? 0),
    photoUrl: body.photoUrl || null
  }).returning();
  return Response.json(created, { status: 201 });
}

export async function PATCH(request: NextRequest) {
  const body = await request.json() as { id?: number; name?: string; department?: string; semester?: number; section?: string; email?: string; phone?: string; cgpa?: number };
  if (!body.id) return Response.json({ message: "Student id is required." }, { status: 400 });
  const { id, cgpa, ...values } = body;
  const [updated] = await db.update(students).set({ ...values, ...(cgpa !== undefined ? { cgpa: String(cgpa) } : {}) }).where(eq(students.id, id)).returning();
  return updated ? Response.json(updated) : Response.json({ message: "Student not found." }, { status: 404 });
}

export async function DELETE(request: NextRequest) {
  const id = Number(request.nextUrl.searchParams.get("id"));
  if (!id) return Response.json({ message: "Student id is required." }, { status: 400 });
  const [deleted] = await db.delete(students).where(eq(students.id, id)).returning();
  return deleted ? Response.json({ ok: true }) : Response.json({ message: "Student not found." }, { status: 404 });
}
