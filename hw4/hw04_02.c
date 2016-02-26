/*
 * Reads an input for the user's full name and prints their initials.
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_DATA 64

char *full_name = NULL;

void get_user_full_name()
{
	full_name = (char *)malloc(MAX_DATA * sizeof(char));

	printf("Please enter your full name:\t");
	if(gets(full_name) == NULL)
		printf("Error\n");
}



int main(void)
{
	get_user_full_name();
	printf("%s\n", full_name);

	int i = 0;

	printf("Initials: %c. ", *(full_name));
	while(*(full_name + i) != '\0')
	{
		if(*(full_name + i) == ' ')
		{
			i++;
			printf("%c. ", *(full_name + i));
		}
		i++;
	}
	putc('\n', stdout);

	free(full_name);

	return 0;
}
