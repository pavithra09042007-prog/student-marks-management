# Student Marks Management System (C)

A beginner-friendly console application written in C. It stores student details and marks for three subjects, calculates total, average, grade and pass/fail result, and saves records in `students.txt`.

## Features
- Add a student record
- Validate roll numbers and marks
- Prevent duplicate roll numbers
- Display all saved records
- Search by roll number
- Calculate total and average
- Assign a grade and PASS/FAIL result
- Save and reload records using a text file

## Grade rules
- If any subject mark is below 35: `F` and `FAIL`
- Otherwise, grade is based on average:
  - 90–100: A+
  - 80–89.99: A
  - 70–79.99: B
  - 60–69.99: C
  - 50–59.99: D
  - Below 50: E

These are sample project rules and can be changed to match your institution's grading system.

## Compile and run

### GCC (Linux, macOS, or Windows with GCC installed)
```bash
gcc student_marks.c -o student_marks
./student_marks
```

On Windows Command Prompt:
```bat
gcc student_marks.c -o student_marks.exe
student_marks.exe
```

You can also paste the code into an online C compiler that supports C99. For persistent storage, run it in a folder where the program can create `students.txt`.

## Sample test
Choose `1`, then enter:
- Roll number: `101`
- Name: `Anu`
- Subject 1: `90`
- Subject 2: `85`
- Subject 3: `95`

Expected calculation:
- Total: `270`
- Average: `90.00`
- Grade: `A+`
- Result: `PASS`

Then choose `2` to display records, `3` to search, and `0` to exit.

## Files
- `student_marks.c` — source code
- `PROJECT_REPORT.md` — short project report
- `README.md` — instructions and GitHub description
- `students_sample.txt` — example record format (optional reference)

## GitHub upload
1. Sign in to GitHub and create a new repository named `student-marks-management-system`.
2. Upload `student_marks.c`, `README.md`, `PROJECT_REPORT.md`, and optionally `students_sample.txt`.
3. Commit the files.
4. Copy the repository URL and submit that URL in GCR.

Do not upload private student data. Use only fictional sample records in a public repository.
