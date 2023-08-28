/*------------------------------------------------------------------*/
/* DEVELOPER: Gali Aviyam                                           */
/* DATE MODIFIED: 27.11.2022                                        */
/* WORKSHEET NAME: serialization                                    */
/* GDB + Valgrind tested                                            */
/* Reviewer: Ariel Biton                                            */
/*------------------------------------------------------------------*/

#include "serialize_structs.h"
#include <stdio.h> /*size_t*/
#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/

void InitStudent(student_t *student)
{
	student->first_name = "noa";
	student->last_name = "kirel";
	
	student->student_grades.h_grades.sociology = 99;
	student->student_grades.h_grades.psychology = 98;
	student->student_grades.h_grades.literature = 97;
	
	student->student_grades.r_grades.physics = 77;
	student->student_grades.r_grades.math = 80;
	
	student->student_grades.sports_grade = 76.8;
}

int WriteStructToFile(const void *student, char *filename)
{
	FILE *fp = NULL;
	assert(NULL != filename);

	fp = fopen(filename, "wb");
	if (fp == NULL)
	{
		return FAIL;
	}
	
	fwrite(student, sizeof(student_t), 1, fp);
	
	if(0 != fclose(fp))
	{
		return FAIL;
	}
	
	fp = NULL;
	return SUCCESS;
}

int ReadStructFromFile(void *student, char *filename)
{
	FILE *fp = NULL;
	assert(NULL != filename);
		
	fp = fopen (filename, "rb");
	if (fp == NULL)
	{
		return FAIL;
	}
	
	fread(student, sizeof(student_t), 1, fp);
	
	if(0 != fclose(fp))
	{
		return FAIL;
	}
	
	fp = NULL;
    return SUCCESS;
}
