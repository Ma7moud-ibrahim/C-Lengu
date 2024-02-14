#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct student {
    int id;
    char fname[10];
    char lname[10];
    char phoneno[11];
    char email[20];
    float gpa;
};

int isValidEmail(const char *email) {
    int atCount = 0, dotCount = 0;
    for (int i = 0; email[i] != '\0'; i++) {
        if (email[i] == '@') {
            atCount++;
        } else if (email[i] == '.') {
            dotCount++;
        }
    }
    return (atCount == 1 && dotCount >= 1);
}

int isValidPhoneNumber(const char *phone) {
    for (int i = 0; phone[i] != '\0'; i++) {
        if (!isdigit(phone[i])) {
            return 0;
        }
    }
    return 1;
}

int isValidGPA(float gpa) {
    return (gpa >= 0.0 && gpa <= 4.0);
}

void Add(struct student s, FILE *fptr) {
    fwrite(&s, sizeof(struct student), 1, fptr);
}

void AddStudent(FILE *fptr) {
    struct student s = {0, "", "", "", "", 0.0};
    printf("\t\t\t\tPlease Enter Student Info :\n");
    
    while (1) {
        printf("\t\t\t\tID : ");
        scanf("%d", &s.id);

        printf("\t\t\t\tFirst Name : ");
        scanf("%s", s.fname);

        printf("\t\t\t\tLast Name : ");
        scanf("%s", s.lname);

        printf("\t\t\t\tPhone Number : ");
        scanf("%s", s.phoneno);
        if (!isValidPhoneNumber(s.phoneno)) {
            system("cls");
            printf("\t\t\t\tInvalid phone number format. Please enter a valid phone number.\n");
            getchar(); 
        }

        printf("\t\t\t\tEmail : ");
        scanf("%s", s.email);
        if (!isValidEmail(s.email)) {
            system("cls");
            printf("\t\t\t\tInvalid email format. Please enter a valid email address.\n");
            getch(stdin);
            continue;
        }

        printf("\t\t\t\tGPA : ");
        scanf("%f", &s.gpa);
        if (!isValidGPA(s.gpa)) {
            system("cls");
            printf("\t\t\t\tInvalid GPA. Please enter a GPA between 0.0 and 4.0.\n");
            getch(stdin);
            continue;
        }

        Add(s, fptr);
        system("cls");
        printf("\t\t\t\tStudent Added Successfully.\n");
        getch(stdin);
        system("cls");
        break;
    }
}

void DisplayStudent(FILE *fptr) {
    printf("%5s %10s %10s %20s %10s %6s\n", "ID", "First Name", "Last Name", "Email", "Phone", "GPA");
    struct student s_temp;
    rewind(fptr);
    while (fread(&s_temp, sizeof(struct student), 1, fptr) == 1) {
        printf("%5d %10s %10s %20s %10s %.2f\n", s_temp.id, s_temp.fname, s_temp.lname, s_temp.email, s_temp.phoneno, s_temp.gpa);
    }
    getch(stdin);
}

void DeleteStudent(FILE *fptr) {
    rewind(fptr);
    printf("\t\t\tPlease Enter Student ID to Delete: ");
    int id_temp;
    scanf("%d", &id_temp);

    struct student s_temp;
    int found = 0;
    FILE *tempFile = fopen("temp.txt", "wb"); 

    while (fread(&s_temp, sizeof(struct student), 1, fptr) == 1) {
        if (id_temp != s_temp.id) {
            fwrite(&s_temp, sizeof(struct student), 1, tempFile); 
        } else {
            found = 1;
        }
    }

    fclose(tempFile);
    fclose(fptr);
    remove("Students.txt"); 
    rename("temp.txt", "Students.txt"); 

    if (found) {
        printf("\t\t\tStudent Deleted Successfully...!!!\n");
    } else {
        printf("\t\t\tStudent Not Found...!!!\n");
    }
}

void UpdateStudent(FILE *fptr) {
    rewind(fptr);
    printf("\t\t\tPlease Enter Student ID: ");
    int id_temp;
    scanf("%d", &id_temp);

    struct student s_temp;
    int found = 0;
    FILE *tempFile = fopen("temp.txt", "wb"); 

    while (fread(&s_temp, sizeof(struct student), 1, fptr) == 1) {
        if (id_temp == s_temp.id) {
            found = 1;
            printf("\t\t\t\tFirst Name : ");
            scanf("%s", s_temp.fname);
            printf("\t\t\t\tLast Name : ");
            scanf("%s", s_temp.lname);
            printf("\t\t\t\tPhone Number : ");
            scanf("%s", s_temp.phoneno);
            printf("\t\t\t\tEmail : ");
            scanf("%s", s_temp.email);
            printf("\t\t\t\tGPA : ");
            scanf("%f", &s_temp.gpa);
        }
        fwrite(&s_temp, sizeof(struct student), 1, tempFile); 
    }

    fclose(tempFile);
    fclose(fptr);
    remove("Students.txt"); 
    rename("temp.txt", "Students.txt"); 

    if (found) {
        printf("\t\t\tStudent Updated Successfully...!!!\n");
    } else {
        printf("\t\t\tStudent Not Found...!!!\n");
    }
}

void Menu(FILE *fptr) {
    system("Color 30");
    system("cls");
    printf("\t\t\t***********************************\n");
    printf("\t\t\t*  Student Management System      *\n");
    printf("\t\t\t*  1- Display Students            *\n");
    printf("\t\t\t*  2- Add Student                 *\n");
    printf("\t\t\t*  3- Delete Student              *\n");
    printf("\t\t\t*  4- Update Student              *\n");
    printf("\t\t\t*  5- Exit                        *\n");
    printf("\t\t\t***********************************\n\t\t\t\t");
    int c;
    scanf("%d", &c);
    switch (c) {
        case 1:
            system("cls");
            DisplayStudent(fptr);
            system("cls");
            break;
        case 2:
            system("cls");
            AddStudent(fptr);
            break;
        case 3:
            system("cls");
            DeleteStudent(fptr);
            break;
        case 4:
            system("cls");
            UpdateStudent(fptr);
            break;
        case 5:
                    exit(1);
        default:
            system("cls");
            printf("\t\t\t\tWrong Input.....\n");
            getch(stdin);
    }
}

int main() {
    while (1) {
        FILE *fptr = fopen("Students.txt", "ab+");
        if (fptr == NULL) {
            printf("Error opening file.\n");
            return 1;
        }
        Menu(fptr);
        fclose(fptr);
    }
    return 0;
}

