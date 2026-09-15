import { boolean, integer, numeric, pgTable, serial, text, timestamp, varchar } from "drizzle-orm/pg-core";

export const users = pgTable("users", {
  id: serial("id").primaryKey(),
  username: varchar("username", { length: 60 }).notNull().unique(),
  password: varchar("password", { length: 255 }).notNull(),
  role: varchar("role", { length: 20 }).notNull(),
  createdAt: timestamp("created_at").defaultNow().notNull()
});

export const students = pgTable("students", {
  id: serial("id").primaryKey(),
  registrationNumber: varchar("registration_number", { length: 30 }).notNull().unique(),
  name: varchar("name", { length: 120 }).notNull(),
  department: varchar("department", { length: 120 }).notNull(),
  semester: integer("semester").notNull(),
  section: varchar("section", { length: 8 }).notNull(),
  email: varchar("email", { length: 150 }).notNull(),
  phone: varchar("phone", { length: 30 }).notNull(),
  cgpa: numeric("cgpa", { precision: 3, scale: 2 }).notNull(),
  photoUrl: text("photo_url"),
  active: boolean("active").default(true).notNull(),
  createdAt: timestamp("created_at").defaultNow().notNull()
});

export const courses = pgTable("courses", {
  id: serial("id").primaryKey(),
  code: varchar("code", { length: 20 }).notNull().unique(),
  title: varchar("title", { length: 160 }).notNull(),
  credits: integer("credits").notNull(),
  department: varchar("department", { length: 120 }).notNull()
});

export const attendanceRecords = pgTable("attendance_records", {
  id: serial("id").primaryKey(),
  studentId: integer("student_id").notNull().references(() => students.id, { onDelete: "cascade" }),
  courseId: integer("course_id").notNull().references(() => courses.id, { onDelete: "cascade" }),
  status: varchar("status", { length: 10 }).notNull(),
  recordedOn: timestamp("recorded_on").defaultNow().notNull(),
  facultyUsername: varchar("faculty_username", { length: 60 }).notNull()
});
