#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include <string.h> /* strlen */

int IsRotation (const char *s1, const char *s2)
{
	int s1_len = 0;
	int s2_len = 0;
	const char *s2_runner = NULL;	

	assert (NULL != s1);
	assert (NULL != s2);
	
	s2_runner = s2;	
	
	s1_len = strlen(s1);
	s2_len = strlen(s2);
	
	if (s1_len != s2_len)
	{
		return (0);
	}
	
	while (NULL != s2_runner)
	{
		s2_runner = strchr(s2_runner, *s1);
		
		if (NULL == s2_runner)
		{
			return 0;
		}
		
		if (0 == strncmp(s1, s2_runner, strlen(s2_runner)) && 
		0 == strncmp(s2, s1 + strlen(s2_runner), s1_len - strlen(s2_runner)))
		{
			return 1;
		}
		
		++s2_runner;
		s2_runner = strchr(s2_runner, *s1);
	}
	
	return 0;
}

int main()
{
	char s1[] = "12345";
	char s2[] = "45123";
	char s3[] = "121234";
	char s4[] = "123412";
	char s5[] = "121234";
	char s6[] = "123418";

	printf("%s and %s: %d\n",s1, s2, IsRotation(s1, s2));
	printf("%s and %s: %d\n", s3, s4, IsRotation(s3, s4));
	printf("%s and %s: %d\n", s5, s6, IsRotation(s5, s6));
	
	return 0;
}
