export type Student = {
  id: string;
  name: string;
  department: string;
  semester: number;
  section: string;
  attendance: number;
  cgpa: number;
  email: string;
  phone: string;
  image: string;
};

const names = [
  "Aarav Sharma", "Ananya Reddy", "Vihaan Kapoor", "Ishita Verma", "Arjun Mehta", "Saanvi Nair", "Aditya Rao", "Kavya Iyer", "Rohan Malhotra", "Meera Joshi",
  "Yash Gupta", "Diya Menon", "Kabir Singh", "Aditi Kulkarni", "Reyansh Das", "Nisha Patel", "Aryan Chawla", "Priya Shah", "Dhruv Bansal", "Tanya Sethi",
  "Dev Arora", "Riya Bose", "Manav Jain", "Sneha Pillai", "Krish Agarwal", "Nandini Roy", "Siddharth Khanna", "Pooja Desai", "Karan Sood", "Ayesha Khan",
  "Ritvik Tiwari", "Shruti Sinha", "Neil Fernandes", "Maya Krishnan", "Harsh Vardhan", "Zoya Ali", "Ishan Pandey", "Anika Bhat", "Raghav Bedi", "Mitali Ghosh",
  "Varun Saxena", "Aanya Kapoor", "Samar Dutta", "Neha Kumari", "Pranav Batra", "Tanvi Rao", "Rudra Bhatt", "Siya Thomas", "Akshay Chopra", "Rhea Nambiar",
  "Om Prakash", "Kritika Suri", "Parth Mittal", "Sakshi Arora", "Anirudh Nanda", "Vaishnavi Pai", "Arnav Gupta", "Bhavya Jain", "Nikhil Sethi", "Muskan Kaur",
  "Atharv Joshi", "Naina Yadav", "Aman Srivastava", "Mansi Bansal", "Rishabh Goel", "Ira Mukherjee", "Vivaan Suri", "Simran Gill", "Sahil Anand", "Apeksha Raut",
  "Tushar Bhatia", "Ritika Das", "Kunal Shetty", "Aarohi Naik", "Mohit Arora", "Esha Kapoor", "Aviral Mishra", "Navya Singhal", "Gautam Goyal", "Jhanvi Sood",
  "Lakshya Anand", "Pallavi Dey", "Anshuman Rathi", "Nitya Nair", "Rajat Malhotra", "Kashish Gupta", "Sourav Ghosh", "Tanya Arora", "Rohan Shekhar", "Divya Sinha",
  "Naveen Nair", "Madhavi Iyer", "Chirag Jain", "Sana Sheikh", "Himanshu Rana", "Kaveri Shah", "Aakash Verma", "Isha Bansal", "Abhinav Kapoor", "Reema Dutta"
];

const departments = ["Computer Science & Engineering", "Information Technology", "Electronics & Communication", "Mechanical Engineering", "Business Administration"];
const avatars = [12, 32, 44, 47, 49, 57, 60, 65, 68, 70];

export const students: Student[] = names.map((name, index) => ({
  id: `24CSE${String(1001 + index).padStart(4, "0")}`,
  name,
  department: index < 56 ? "Computer Science & Engineering" : departments[index % departments.length],
  semester: index % 3 === 0 ? 6 : 5,
  section: ["A", "B", "C"][index % 3],
  attendance: 56 + ((index * 7) % 42),
  cgpa: Number((6.4 + ((index * 13) % 34) / 10).toFixed(1)),
  email: `${name.toLowerCase().replace(/[^a-z]/g, ".").replace(/\.+/g, ".").replace(/^\.|\.$/g, "")}@students.aurora.edu`,
  phone: `+91 98${String(10000000 + index * 7291).slice(-8)}`,
  image: `https://i.pravatar.cc/160?img=${avatars[index % avatars.length]}`
}));

export const activeStudent = {
  ...students[0],
  id: "12345678",
  name: "Aarav Sharma",
  department: "Computer Science & Engineering",
  semester: 6,
  section: "A",
  attendance: 82.4,
  cgpa: 8.6,
  email: "aarav.sharma@students.aurora.edu",
  phone: "+91 98765 43210",
  image: "https://i.pravatar.cc/240?img=12"
};

export const subjectAttendance = [
  { code: "CSE401", subject: "Data Structures & Algorithms", faculty: "Dr. Nisha Mehta", present: 29, absent: 4, total: 33 },
  { code: "CSE402", subject: "Database Management Systems", faculty: "Prof. R. K. Sharma", present: 26, absent: 5, total: 31 },
  { code: "CSE403", subject: "Operating Systems", faculty: "Dr. Aman Srivastava", present: 24, absent: 6, total: 30 },
  { code: "CSE404", subject: "Computer Networks", faculty: "Ms. Divya Rani", present: 27, absent: 4, total: 31 },
  { code: "CSE405", subject: "Design & Analysis of Algorithms", faculty: "Dr. Nisha Mehta", present: 25, absent: 4, total: 29 },
  { code: "CSE406", subject: "DSA Laboratory", faculty: "Mr. Kunal Gupta", present: 30, absent: 2, total: 32 }
];

export const academicSubjects = [
  { subject: "Data Structures & Algorithms", credits: 4, internal: 27, assignment: 9, final: 46, grade: "A" },
  { subject: "Database Management Systems", credits: 4, internal: 25, assignment: 9, final: 42, grade: "A-" },
  { subject: "Operating Systems", credits: 4, internal: 24, assignment: 8, final: 44, grade: "A-" },
  { subject: "Computer Networks", credits: 3, internal: 28, assignment: 10, final: 45, grade: "A" },
  { subject: "Design & Analysis of Algorithms", credits: 3, internal: 26, assignment: 9, final: 40, grade: "B+" },
  { subject: "Professional Ethics", credits: 2, internal: 29, assignment: 10, final: 47, grade: "A+" }
];

export const timetable = [
  { day: "Monday", sessions: ["DSA · 09:00", "DBMS · 10:00", "OS · 12:00", "DAA · 14:00"] },
  { day: "Tuesday", sessions: ["CN · 09:00", "DSA Lab · 11:00", "DBMS · 14:00", "Library · 16:00"] },
  { day: "Wednesday", sessions: ["OS · 09:00", "DAA · 10:00", "CN · 12:00", "DSA · 14:00"] },
  { day: "Thursday", sessions: ["DBMS Lab · 09:00", "DSA · 11:00", "OS · 14:00", "Mentoring · 16:00"] },
  { day: "Friday", sessions: ["DAA · 09:00", "CN · 10:00", "DSA Lab · 12:00", "Seminar · 14:00"] },
  { day: "Saturday", sessions: ["Aptitude · 10:00", "Club Hour · 12:00", "Project Lab · 14:00"] }
];
