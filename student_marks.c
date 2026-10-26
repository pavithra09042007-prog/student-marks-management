/*
 * Student Marks Management System
 * Language: C (C99)
 * Features: Add students, display records, search by roll number,
 * calculate total/average/grade/result, and save records to a text file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define SUBJECTS 3
#define NAME_LEN 60
#define DATA_FILE "students.txt"

typedef struct {
    int rollNo;
    char name[NAME_LEN];
    int marks[SUBJECTS];
} Student;

static Student students[MAX_STUDENTS];
static int studentCount = 0;

static void clearInput(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) { }
}

static int readInt(const char *prompt, int min, int max) {
    int value;
    int result;

    for (;;) {
        printf("%s", prompt);
        result = scanf("%d", &value);

        if (result == 1 && value >= min && value <= max) {
            clearInput();
            return value;
        }

        printf("Invalid input. Enter a number from %d to %d.\n", min, max);
        clearInput();
    }
}

static void readName(char name[], size_t size) {
    for (;;) {
        printf("Enter student name: ");
        if (fgets(name, (int)size, stdin) == NULL) {
            name[0] = '\0';
            return;
        }

        name[strcspn(name, "\n")] = '\0';
        if (name[0] != '\0') {
            return;
        }
        printf("Name cannot be empty.\n");
    }
}

static int findStudentIndex(int rollNo) {
    int i;
    for (i = 0; i < studentCount; i++) {
        if (students[i].rollNo == rollNo) {
            return i;
        }
    }
    return -1;
}

static int totalMarks(const Student *s) {
    return s->marks[0] + s->marks[1] + s->marks[2];
}

static double averageMarks(const Student *s) {
    return totalMarks(s) / (double)SUBJECTS;
}

static const char *gradeFor(const Student *s) {
    double avg = averageMarks(s);

    if (s->marks[0] < 35 || s->marks[1] < 35 || s->marks[2] < 35) {
        return "F";
    }
    if (avg >= 90) return "A+";
    if (avg >= 80) return "A";
    if (avg >= 70) return "B";
    if (avg >= 60) return "C";
    if (avg >= 50) return "D";
    return "E";
}

static const char *resultFor(const Student *s) {
    return (s->marks[0] >= 35 && s->marks[1] >= 35 && s->marks[2] >= 35)
           ? "PASS" : "FAIL";
}

static void saveRecords(void) {
    FILE *fp = fopen(DATA_FILE, "w");
    int i;

    if (fp == NULL) {
        printf("Warning: Could not save records to %s.\n", DATA_FILE);
        return;
    }

    for (i = 0; i < studentCount; i++) {
        fprintf(fp, "%d|%s|%d|%d|%d\n",
                students[i].rollNo, students[i].name,
                students[i].marks[0], students[i].marks[1],
                students[i].marks[2]);
    }

    fclose(fp);
}

static void loadRecords(void) {
    FILE *fp = fopen(DATA_FILE, "r");
    char line[256];

    if (fp == NULL) {
        return; /* First run: the file does not exist yet. */
    }

    while (studentCount < MAX_STUDENTS && fgets(line, sizeof(line), fp) != NULL) {
        Student s;
        char *token;

        token = strtok(line, "|");
        if (token == NULL) continue;
        s.rollNo = atoi(token);

        token = strtok(NULL, "|");
        if (token == NULL) continue;
        strncpy(s.name, token, sizeof(s.name) - 1);
        s.name[sizeof(s.name) - 1] = '\0';
        s.name[strcspn(s.name, "\r\n")] = '\0';

        token = strtok(NULL, "|");
        if (token == NULL) continue;
        s.marks[0] = atoi(token);

        token = strtok(NULL, "|");
        if (token == NULL) continue;
        s.marks[1] = atoi(token);

        token = strtok(NULL, "|\r\n");
        if (token == NULL) continue;
        s.marks[2] = atoi(token);

        if (s.rollNo > 0 && s.marks[0] >= 0 && s.marks[0] <= 100 &&
            s.marks[1] >= 0 && s.marks[1] <= 100 &&
            s.marks[2] >= 0 && s.marks[2] <= 100 &&
            findStudentIndex(s.rollNo) == -1) {
            students[studentCount++] = s;
        }
    }

    fclose(fp);
}

static void addStudent(void) {
    Student s;
    int i;

    if (studentCount >= MAX_STUDENTS) {
        printf("Student list is full (maximum %d students).\n", MAX_STUDENTS);
        return;
    }

    printf("\n--- Add Student ---\n");
    s.rollNo = readInt("Enter roll number (1-999999): ", 1, 999999);

    if (findStudentIndex(s.rollNo) != -1) {
        printf("A student with this roll number already exists.\n");
        return;
    }

    readName(s.name, sizeof(s.name));

    for (i = 0; i < SUBJECTS; i++) {
        char prompt[80];
        snprintf(prompt, sizeof(prompt), "Enter marks for Subject %d (0-100): ", i + 1);
        s.marks[i] = readInt(prompt, 0, 100);
    }

    students[studentCount++] = s;
    saveRecords();
    printf("Student record added and saved successfully.\n");
    printf("Total: %d | Average: %.2f | Grade: %s | Result: %s\n",
           totalMarks(&s), averageMarks(&s), gradeFor(&s), resultFor(&s));
}

static void printHeader(void) {
    printf("\n%-8s %-22s %7s %7s %7s %7s %9s %-7s %-6s\n",
           "Roll No", "Name", "Sub 1", "Sub 2", "Sub 3",
           "Total", "Average", "Grade", "Result");
    printf("-----------------------------------------------------------------------------------------------\n");
}

static void printStudent(const Student *s) {
    printf("%-8d %-22.22s %7d %7d %7d %7d %9.2f %-7s %-6s\n",
           s->rollNo, s->name, s->marks[0], s->marks[1], s->marks[2],
           totalMarks(s), averageMarks(s), gradeFor(s), resultFor(s));
}

static void displayStudents(void) {
    int i;

    printf("\n--- All Student Records ---\n");
    if (studentCount == 0) {
        printf("No student records found. Add a student first.\n");
        return;
    }

    printHeader();
    for (i = 0; i < studentCount; i++) {
        printStudent(&students[i]);
    }
}

static void searchStudent(void) {
    int rollNo, index;

    printf("\n--- Search Student ---\n");
    rollNo = readInt("Enter roll number to search: ", 1, 999999);
    index = findStudentIndex(rollNo);

    if (index == -1) {
        printf("No student found with roll number %d.\n", rollNo);
        return;
    }

    printHeader();
    printStudent(&students[index]);
}

int main(void) {
    int choice;

    loadRecords();

    printf("========================================\n");
    printf("   STUDENT MARKS MANAGEMENT SYSTEM\n");
    printf("========================================\n");
    printf("Loaded %d saved student record(s).\n", studentCount);

    do {
        printf("\nMAIN MENU\n");
        printf("1. Add student record\n");
        printf("2. Display all student records\n");
        printf("3. Search student by roll number\n");
        printf("4. Save records\n");
        printf("0. Exit\n");

        choice = readInt("Choose an option: ", 0, 4);

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                saveRecords();
                printf("Records saved to %s.\n", DATA_FILE);
                break;
            case 0:
                saveRecords();
                printf("Records saved. Thank you for using the system!\n");
                break;
            default:
                /* readInt prevents values outside the menu range. */
                break;
        }
    } while (choice != 0);

    return 0;
}
