/*
 * Homework 2 question 1
 */

#include <stdio.h>
#include <time.h>

void timer(int t)
{
	/* create two variables of type time_t */
	time_t end, current;
	/* create and intialize a variable called temp */
	int temp = 0;
	/* pass the address of the variable end to the function 'time'
	 * that will encode the time in a time_t format
	 */
	 time(&end);
	 /* update the value of end by adding the number passed */
	 end += t;

	 do
	 {
		 /* pass the address of the variable current to the time 
		  * function 
		  */
		  time(&current);

		  /* if the value of temp isn't equal to the value of current
		   * then set the value ot temp to the value of current
		   * and print the decremented value of 't'
		   */
		   if(temp != current)
		   {
			   temp = current;
			   printf("%d\n", t--);
		   }

		   /* do this loop as long as the value of of end is greater than current */
	 } while(end > current);
}

int main()
{
	int t;
	printf("Enter an integer: ");
	scanf("%d", &t);
	timer(t);
	printf("Times up!");

	return 0;
}
