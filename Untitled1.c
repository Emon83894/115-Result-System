#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// structure for storing student marks
struct stuMarks
{
    char sub[30];
    float quiz, assignment, mid, final, total;
    char grade[5];
};

// structure for storing student data with marks
struct StudentData
{
    char fname[30], lname[30], dept[20];
    int id, m_id;
    float cgpa;
    struct stuMarks marks[30];
};

// declared a array of Studentdata
struct StudentData student[100];
int sno = 0; // that keep tracks of student array

// Function to save student information to a file
void saveStudentDataToFile()
{
    FILE *file = fopen("student_data.txt", "w");
    if (file == NULL)
    {
        printf("Error opening student_data.txt\n");
        return;
    }

    for (int i = 0; i < sno; i++)
    {
        fprintf(file, "%d %s %s %s %.2f %d\n", student[i].id, student[i].fname, student[i].lname, student[i].dept, student[i].cgpa, student[i].m_id);
    }

    fclose(file);
}

// Function to save student marks information to a file
void saveStudentMarksToFile()
{
    FILE *file = fopen("student_marks.txt", "w");
    if (file == NULL)
    {
        printf("Error opening student_marks.txt\n");
        return;
    }

    for (int i = 0; i < sno; i++)
    {
        for (int j = 0; j < student[i].m_id; j++)
        {
            fprintf(file, "%d %s %.2f %.2f %.2f %.2f %.2f %s\n", student[i].id, student[i].marks[j].sub, student[i].marks[j].quiz, student[i].marks[j].assignment, student[i].marks[j].mid, student[i].marks[j].final, student[i].marks[j].total, student[i].marks[j].grade);
        }
    }

    fclose(file);
}

// Function to load student information from a file
void loadStudentDataFromFile()
{
    FILE *file = fopen("student_data.txt", "r");
    if (file == NULL)
    {
        printf("Error opening student_data.txt");
        return;
    }

    int id, m_id;
    float cgpa;
    char fname[30], lname[30], dept[20];

    while (fscanf(file, "%d %s %s %s %f %d", &id, fname, lname, dept, &cgpa, &m_id) != EOF)
    {
        student[sno].id = id;
        strcpy(student[sno].fname, fname);
        strcpy(student[sno].lname, lname);
        strcpy(student[sno].dept, dept);
        student[sno].cgpa = cgpa;
        student[sno].m_id = m_id;
        sno++;
    }

    fclose(file);
}

// Function to load student marks information from a file
void loadStudentMarksFromFile()
{
    FILE *file = fopen("student_marks.txt", "r");
    if (file == NULL)
    {
        perror("Error opening student_marks.txt");
        return;
    }

    int id;
    float quiz, assignment, mid, final, total;
    char sub[30], grade[5];

    while (fscanf(file, "%d %s %f %f %f %f %f %s", &id, sub, &quiz, &assignment, &mid, &final, &total, grade) != EOF)
    {
        int ind = -1;
        for (int i = 0; i < sno; i++)
        {
            if (student[i].id == id)
            {
                ind = i;
                break;
            }
        }

        if (ind != -1 && student[ind].m_id < 30)
        {
            strcpy(student[ind].marks[student[ind].m_id].sub, sub);
            student[ind].marks[student[ind].m_id].quiz = quiz;
            student[ind].marks[student[ind].m_id].assignment = assignment;
            student[ind].marks[student[ind].m_id].mid = mid;
            student[ind].marks[student[ind].m_id].final = final;
            student[ind].marks[student[ind].m_id].total = total;
            strcpy(student[ind].marks[student[ind].m_id].grade, grade);
            student[ind].m_id++;
        }
    }

    fclose(file);
}
// inserting student data
void insertStuData()
{
    printf("Enter student ID: ");
    scanf("%d", &student[sno].id);
    printf("First name: ");
    scanf("%s", student[sno].fname);
    printf("Last name: ");
    scanf("%s", student[sno].lname);
    printf("Department: ");
    scanf("%s", student[sno].dept);
    printf("CGPA: ");
    scanf("%f", &student[sno].cgpa);
    sno++;
    saveStudentDataToFile();
    clearWindow();
}

// deleting a data
void deleteStuData()
{
    int c;
    printf("Enter 0 to show data or Student ID to delete the data: ");
    scanf("%d", &c);
    if (c == 0)
    {
        showStuData();
        printf("Which ID you want to delete [enter 0 to skip delete]: ");
        scanf("%d", &c);
        if (c == 0)
            return;
    }
    struct StudentData temp;
    for (int i = 0; i < sno; i++)
    {
        if (student[i].id == c)
        {
            for (int j = i; j < sno; j++)
                student[i] = student[i + 1];
            break;
        }
    }
    sno--;

    printf("\nEnter any key to continue...");
    if (_getch())
    {
        clearWindow();
    }
}

// showing the stored data
void showStuData()
{
    printf("Student Information\n\n");
    printf("Id \t Name \t\t\t Department \t\t CGPA\n");

    for (int i = 0; i < sno; i++)
    {
        printf("%d \t %s %s \t\t %s \t\t\t %.2f\n", student[i].id, student[i].fname, student[i].lname, student[i].dept, student[i].cgpa);
    }

    printf("\nEnter any key to continue...");
    if (_getch())
    {
        clearWindow();
    }
}

// updating a data
void updateStuData()
{
    showStuData();
    printf("Select an ID to update: ");
    int id_no, t_sno;
    scanf("%d", &id_no);
    for (int i = 0; i < sno; i++)
    {
        if (student[i].id == id_no)
        {
            t_sno = i;
        }
    }

    int c;
    printf("Update Info [enter 1 to 'yes' or 0 to 'no']\n");
    printf("Do you want to update First Name? [ %s ]:", student[t_sno].fname);
    scanf("%d", &c);
    if (c == 1)
    {
        printf("Enter updated first name: ");
        scanf("%s", &student[t_sno].fname);
    }
    printf("Do you want to update last Name? [%s]:", student[t_sno].lname);
    scanf("%d", &c);
    if (c == 1)
    {
        printf("Enter updated last name: ");
        scanf("%s", &student[t_sno].lname);
    }
    printf("Do you want to update Department? [%s]:", student[t_sno].dept);
    scanf("%d", &c);
    if (c == 1)
    {
        printf("Enter updated department: ");
        scanf("%s", &student[t_sno].dept);
    }

    printf("Do you want to update CGPA? [%.2f]:", student[t_sno].cgpa);
    scanf("%d", &c);
    if (c == 1)
    {
        printf("Enter updated CGPA: ");
        scanf("%f", &student[t_sno].cgpa);
    }

    clearWindow();
}

// adding marks of students
void addMarks(int ind)
{
    int sub_id = student[ind].m_id;

    printf("Subject: ");
    scanf("%s", &student[ind].marks[sub_id].sub);
    printf("Quiz marks: ");
    scanf("%f", &student[ind].marks[sub_id].quiz);
    printf("Assignment marks: ");
    scanf("%f", &student[ind].marks[sub_id].assignment);
    printf("Mid marks: ");
    scanf("%f", &student[ind].marks[sub_id].mid);
    printf("Final marks: ");
    scanf("%f", &student[ind].marks[sub_id].final);

    float total;
    total = student[ind].marks[sub_id].quiz + student[ind].marks[sub_id].assignment + student[ind].marks[sub_id].mid + student[ind].marks[sub_id].final;
    student[ind].marks[sub_id].total = total;
    if (total >= 93)
        strcpy(student[ind].marks->grade, "A");
    else if (total < 93 && total >= 90)
        strcpy(student[ind].marks[sub_id].grade, "A-");
    else if (total < 90 && total >= 87)
        strcpy(student[ind].marks[sub_id].grade, "B+");
    else if (total < 87 && total >= 83)
        strcpy(student[ind].marks[sub_id].grade, "B");
    else if (total < 83 && total >= 80)
        strcpy(student[ind].marks[sub_id].grade, "B-");
    else if (total < 80 && total >= 77)
        strcpy(student[ind].marks[sub_id].grade, "C+");
    else if (total < 77 && total >= 73)
        strcpy(student[ind].marks[sub_id].grade, "C");
    else if (total < 73 && total >= 70)
        strcpy(student[ind].marks[sub_id].grade, "C-");
    else if (total < 70 && total >= 67)
        strcpy(student[ind].marks[sub_id].grade, "D+");
    else if (total < 67 && total >= 60)
        strcpy(student[ind].marks[sub_id].grade, "D");
    else if (total < 60)
        strcpy(student[ind].marks[sub_id].grade, "F");

    student[ind].m_id++;

    printf("\nDo you want to add another subject\n");
    printf("1. YES\n2. NO\n");
    printf("Choice: ");
    int c;
    scanf("%d", &c);
    if (c == 1)
    {
        addMarks(ind);
    }
    else
        return;
}

void addStudentMarks()
{
    int t_id;
    printf("Enter ID whose marks you want to add: ");
    scanf("%d", &t_id);
    int ind, found = 0;
    for (int i = 0; i < sno; i++)
    {
        if (t_id == student[i].id)
        {
            ind = i;
            found = 1;
            break;
        }
    }

    if (found == 1)
    {
        addMarks(ind);
        clearWindow();
    }
    else
    {
        printf("Invalid Id\n");
        printf("\nEnter any key to continue...");
        if (_getch())
        {
            clearWindow();
        }
    }
}

// showing student marks
void showStudentMarks()
{
    int id, ind;
    printf("Enter the id: ");
    scanf("%d", &id);

    for (int i = 0; i < sno; i++)
    {
        if (student[i].id == id)
        {
            ind = i;
            break;
        }
    }

    printf("\nMarks of %s %s\n\n", student[ind].fname, student[ind].lname);
    printf("Subject\tAssignments\tQuiz\tMid\tFinal\ttotal\tGrade\n");
    for (int i = 0; i < student[ind].m_id; i++)
    {
        printf("%s\t%.2f\t\t%.2f\t%.2f\t%.2f\t%.2f\t%s\n", student[ind].marks[i].sub, student[ind].marks[i].assignment, student[ind].marks[i].quiz, student[ind].marks[i].mid, student[ind].marks[i].final, student[ind].marks[i].total, student[ind].marks[i].grade);
    }
    printf("\nEnter any key to continue...");
    if (_getch())
    {
        clearWindow();
    }
}

// clearing the window
void clearWindow()
{
    system("cls");
}

// starting of Admin window
void Admin()
{
    int run = 1;
    while (run)
    {
        int choice;
        printf("Select any of 6\n");
        printf("1. Insert a student information\n");
        printf("2. Update a student information\n");
        printf("3. Delete a student information\n");
        printf("4. Show Student information\n");
        printf("5. Add Student Marks\n");
        printf("6. Show Student Marks\n");
        printf("7. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            insertStuData();
            break;
        case 2:
            updateStuData();
            break;
        case 3:
            deleteStuData();
            break;
        case 4:
            showStuData();
            break;
        case 5:
            addStudentMarks();
            break;
        case 6:
            showStudentMarks();
            break;
        default:
            run = 0;
        }
        clearWindow();
    }
}

void Student()
{
    int id, found_at = -1;
    printf("Enter your ID: ");
    scanf("%d", &id);

    for (int i = 0; i < sno; i++)
    {
        if (student[i].id == id)
        {
            found_at = i;
            break;
        }
    }

    if (found_at == -1)
    {
        printf("Student Info Not found :(\n");
        return;
    }

    printf("\nMarks of %s %s\n\n", student[found_at].fname, student[found_at].lname);
    printf("Subject\tAssignments\tQuiz\tMid\tFinal\ttotal\tGrade\n");
    for (int i = 0; i < student[found_at].m_id; i++)
    {
        printf("%s\t%.2f\t\t%.2f\t%.2f\t%.2f\t%.2f\t%s\n", student[found_at].marks[i].sub, student[found_at].marks[i].assignment, student[found_at].marks[i].quiz, student[found_at].marks[i].mid, student[found_at].marks[i].final, student[found_at].marks[i].total, student[found_at].marks[i].grade);
    }
    printf("\nEnter any key to continue...");
    if (_getch())
    {
        clearWindow();
    }
}

int main()
{
    int run = 1;
    loadStudentDataFromFile();
    loadStudentMarksFromFile();
    while (run)
    {
        int who;
        printf("\nWhat is your role?\n\nInstruction:\nFor Teacher Enter-1\nFor Student Enter-2\n To Exit    Enter-3   \n");
        printf("\n1. Teacher\n");
        printf("2. Student\n");
        printf("3. Exit\n\n");
        printf("Input: ");
        scanf("%d", &who);
        switch (who)
        {
        case 1:
            Admin();
            break;
        case 2:
            Student();
            break;
        default:
            run = 0;
        }
    }
    saveStudentDataToFile();
    saveStudentMarksToFile();

    return 0;
}
