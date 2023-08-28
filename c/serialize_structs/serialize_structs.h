/*------------------------------------------------------------------*/
/* DEVELOPER: Gali Aviyam                                           */
/* DATE MODIFIED: 27.11.2022                                        */
/* WORKSHEET NAME: serialization                                    */
/* GDB + Valgrind tested                                            */
/* Reviewer: Ariel Biton                                            */
/*------------------------------------------------------------------*/

#include <stdio.h>
#define MAX_NAME_LEN 80

enum status {FAIL = -1, SUCCESS = 0};

typedef struct real_grades
{
	size_t physics;
	size_t math;
}real_grades_t;

typedef struct human_grades
{
	size_t sociology;
	size_t psychology;
	size_t literature;
}human_grades_t;

typedef struct grades
{
	human_grades_t h_grades;
	real_grades_t r_grades;
	float sports_grade;
}grades_t;

typedef struct student
{
	char *first_name;
	char *last_name;
	grades_t student_grades;
}student_t;

void InitStudent(student_t *student);
void PrintStudent(student_t *student);
int WriteStructToFile(const void *student, char *filename);
int ReadStructFromFile(void *student, char *filename);
