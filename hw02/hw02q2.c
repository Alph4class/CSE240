/* 
 * Homework 2 Question 2
 */

#include <stdio.h>
#include <time.h>

void termination(int n)
{
	while(n != 1)
	{
		if(n % 2 == 0)
			n = n / 2;
		else
			n = 3 *n + 1;
	}
}

int main(void)
{
	clock_t start = clock();
	int n;
	printf("Input and integer: ");
	scanf("%d", &n);
	termination(n);
	clock_t end = clock();
	float r;
	r = end - start;
	printf("Time elapsed: %f s\n", r);

	return 0;
}
