#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 200
#define MAX_NAME 100

typedef struct {
    int month;
    int date;
} BirthdayType;

typedef struct {
    char name[MAX_NAME];
    BirthdayType birthday;
} StudentType;

StudentType students[MAX_STUDENTS];

int main(void)
{
    strcpy(students[0].name, "kangminsung");
    students[0].birthday.month = 7;
    students[0].birthday.date = 10;
    
    printf("%s의 생일은 %d월 %d일 입니다.\n",students[0].name, students[0].birthday.month, students[0].birthday.date);
    
}

