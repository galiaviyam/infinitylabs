/*------------------------------------------------------------------*/
/* DEVELOPER: Gali Aviyam                                           */
/* DATE MODIFIED: 27.11.2022                                        */
/* WORKSHEET NAME: serialization                                    */
/* GDB + Valgrind tested                                            */
/* Reviewer: Ariel Biton                                            */
/*------------------------------------------------------------------*/

#include <stdio.h>
#include "serialize_structs.h"


int main(void)
{
	student_t student_1 = {0};
	student_t student_2 = {0};
	
	InitStudent(&student_1);
	printf("**********student before serialization**********\n");
	PrintStudent(&student_1);
	
	WriteStructToFile((const void *)&student_1, "student_1.dat");
	
	printf("**********student after serialization**********\n");
	ReadStructFromFile((void *)&student_2, "student_1.dat");
	PrintStudent(&student_2);
	
	return 0;
}

void PrintStudent(student_t *student)
{
	printf("First name: %s\n", student->first_name);
	printf("Last name: %s\n", student->last_name);
	
	printf("\nHumanistic Grades:\n");
	printf("Sociology: %ld\n", student->student_grades.h_grades.sociology);
	printf("psychology: %ld\n", student->student_grades.h_grades.psychology);
	printf("literature: %ld\n", student->student_grades.h_grades.literature);

	printf("\nReal Grades:\n");
	printf("physics: %ld\n", student->student_grades.r_grades.physics);
	printf("math: %ld\n", student->student_grades.r_grades.math);
	
	printf("\nSports Grade:\n%.2f\n", student->student_grades.sports_grade);
}
