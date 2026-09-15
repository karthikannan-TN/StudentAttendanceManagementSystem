import { NextRequest } from "next/server";

const demoAccounts = [
  { username: "12345678", password: "student123", role: "student", name: "Aarav Sharma" },
  { username: "faculty01", password: "faculty123", role: "faculty", name: "Dr. Neha Verma" },
  { username: "admin", password: "admin123", role: "admin", name: "Administrator" }
] as const;

export async function POST(request: NextRequest) {
  const body = await request.json().catch(() => null) as { username?: string; password?: string } | null;
  if (!body?.username || !body.password) {
    return Response.json({ message: "Username and password are required." }, { status: 400 });
  }

  const account = demoAccounts.find((item) => item.username === body.username && item.password === body.password);
  if (!account) {
    return Response.json({ message: "Invalid credentials. Use one of the demo accounts." }, { status: 401 });
  }

  return Response.json({ ok: true, user: { username: account.username, role: account.role, name: account.name } });
}
