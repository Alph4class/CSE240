#include <stdio.h>
#include <time.h>

#define max(x, y) (x > y) ? x : y
#define mac(a, b) (a*a + b*b - 2 * a*b)
int func(int a, int b) { return (a*a + b*b - 2 * a*b); }

// Part 1: (10 points)
// The correct answer should be 6, why is it printing that the answer is 7? Correct the error. (5 points)
void part1(int x, int y) {
	int i = x, j = y, result;

	result = max(i, j++);
	printf("max(%d,%d) = %d\n\n\n", x, (++y), result);

	// Why did this error occur? Please provide the answer in your own words below following "Explanation Part 1:" (5 points)
	printf("Explanation Part 1:The use of prefix incrementation, increments the value and then sets it the assigned variable, and in this case that the reason why it's returning 7 as opposed to the correct value of 6         \n\n");
}


// Part 2: (15 points)
// Run this program in Visual Studio and then again in GCC. Take note of the output values for func(x,y) and mac(x,y).
void part2(int x, int y) {
	int i, j, s, t;

	s = i = x;	// initialize variables with value from x
	t = j = y;  // initialize variables with value from y

	printf("func(x, y) = %d\nmac(x, y) = %d\n\n", func(++i, ++j), mac(++s, ++t));

	// Replace the 4 '_' spaces below with respect to the actual output observed when running the code in VS and GCC.
	printf("In VS : the result of func(x, y) = 1 and mac(x, y) = 1\n"); // (5 points)
	printf("In GCC: the result of func(x, y) = 1 and mac(x, y) = -27\n\n"); // (5 points)

	// Explain why Visual Studio and GCC programming environments could possibly produce a different y value for the same program and for the same input. (5 points)
	printf("Explanation Part 2:Do to the use of diferrent compilers it is appearant that each is optimized in it's own way to deal with different variables and espically macros differently. VS uses it's own compiler that takes the same code, but do to the compiling process being different also produces different results.          \n\n");
}


// Do not edit any of the following code  
int main()
{
	int x = 4, y = 5;

	printf("Part 1:\n\n");
	part1(x, y);
	printf("Part 2:\n\n");
	part2(x, y);

	return 0;
}
