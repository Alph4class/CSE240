#include <stdio.h>
#include <string.h>


// Read before you start:
// Do not modify any part of this program that you are given. Doing so may cause you to fail automated test cases.
// You are given a partially complete program. Your job is to complete the functions in order for this program to work successfully.
// All instructions are given above the required functions, please read them and follow them carefully. 
// If you modify the function return types or parameters, you will fail the automated test cases.
// You can assume that all inputs are valid. Ex: If prompted for an integer, an integer will be input.


// Forward Declarations
void encryption(char[], int);
void decryption(char[], int);
void sortStrings(char[5][32]);
void matrix(int[50][50]);
void printMultiplicationTable(int[50][50], int);

// Problem 1: (5 points)
// hw04 update: Rewrite this function to perform the same task, using only pointer operations.
// You must use pointer operations only. If you use array operations, you will recieve no credit for this part.
// You may modify the code you submitted for hw03
//
// In order to encrypt the input array of characters, we will shift those characters forward alphabetically by the integer value 'e'
// If the input string is "hello" and e = 2, we will shift those characters forward alphabecially by 2 and the result will be "jgnnq"
// Hint: Use strlen() to find the amount of characters in the array
void encryption(char input[], int e)
{
	char* t = input;
	int i = 0;
	for(; i < strlen(input); i++)
	{
		*(t + i) = *(t + i) + e;
	}


}


// Problem 2: (5 points)
// hw04 update: Rewrite this function to perform the same task, using only pointer operations.
// You must use pointer operations only. If you use array operations, you will recieve no credit for this part.
// You may modify the code you submitted for hw03
//
// In order to decrypt the input array of characters, we will shift those characters backwards alphabetically by the integer value 'd'
// If the input string is "jgnnq" and d = 2, we will shift those characters back alphabecially by 2 and the result will be "hello"
// Hint: this should be very similar to your encryption function
void decryption(char input[], int d)
{
	char* t = input;
	int i = 0;
	for(; i < strlen(input); i++)
	{
		*(t + i) = *(t + i) - d;
	}

}


void swapStrings(char string1[], char string2[])
{
	char temp[32];
	strcpy(temp, string1);
	strcpy(string1, string2);
	strcpy(string2, temp);
}


// Problem 3: (10 points)
// hw04 update: Rewrite this function to perform the same task, using only pointer operations.
// You must use pointer operations only. If you use array operations, you will recieve no credit for this part.
// You can use the swapStrings() function if you'd like, but are not required to do so.
// You may modify the code you submitted for hw03 or the solution code.
//
// Use any sorting algorithm to alphabetically sort the strings in the 2D character array "strings".
// NOTE: 'A' and 'a' should be considered alphabetically equivalent.
// See output provided in word document for hw03 for example input and output.
void sortStrings(char strings[5][32])
{
	char *t, *s;
	t = s = NULL;

	int i = 0, j;

	/* Insertion sort */
	for(i = 0; i < 5; i++)
	{
		t = strings[i];
		for(j = i; j < 5; j++)
		{
			s = strings[j];
			if(strcmp(t, s) > 0)
			{
				swapStrings(t, s);
			}
		}
	}


}

// Problem 4: (10 points)
// hw04 update: Rewrite this function to perform the same task, using only pointer operations.
// You must use pointer operations only. If you use array operations, you will recieve no credit for this part.
// You may modify the code you submitted for hw03
//
// Using the 2D integer array "input", you are to fill the array with a multiplication table for the integer "num"
// For example: if num = 2, your output 2D array should contain:
// input[0][0] = 1
// input[0][1] = 2
// input[1][0] = 2
// input[1][1] = 4
// See output provided in word document for further clarification
void multiplicationTable(int input[50][50], int num)
{
	int *t = NULL;
	int i, j;

	for(i = 0; i < num; i++)
	{
		t = input[i];
		for(j = 0; j < num; j++)
		{
			*(t + j) = (i + 1) * (j + 1);
		}
	}

}

// Problem 5: (5 points)
// hw04 update: Rewrite this function to perform the same task, using only pointer operations.
// You must use pointer operations only. If you use array operations, you will recieve no credit for this part.
// You may modify the code you submitted for hw03
//
// Print the 2D array in the following format:
//  1	2
//	2	4
// Use '\t' to print a tab after each index and '\n' to print a newline after each line
// Hint: this should be very similar to your multiplicationTable function
// See ouptut provided in word document for further clarification
void printMultiplicationTable(int input[50][50], int num)
{
	int *t = NULL;
	int i, j;

	for(i = 0; i < num; i++)
	{
		t = input[i];
		for( j = 0; j < num; j++)
		{
			printf("%d\t",*(t + j ));
		}
		putc('\n', stdout);
	}

}



// You should study and understand how this main function works.
// Do not modify it in any way, there is no implementation needed here.
void main()
{
	int selection; // used for program selection

	char input[32]; // used for encryption
	int encrypt; // used for encryption

	char strings[5][32]; // used for sorting

	int num; // used for multiplication table
	int mt[50][50]; // used for multiplication table

	printf("Select one of the following:\n"); // prompt for program selection integer
	printf("1: Encryption\n");
	printf("2. Sorting\n");
	printf("3. Multiplication Table\n");
	scanf("%d", &selection); // store program selection integer

	getchar(); // consume '\n' char; NOTE: If you are using GCC, you may need to comment out this line
	printf("\n"); // newline

	switch (selection)
	{
	case 1:

		printf("Enter a string up to 20 characters long: "); // prompt for string
		fgets(input, sizeof(input), stdin); // store string
		input[strlen(input) - 1] = '\0'; // discard '\n' char; NOTE: If you are using GCC, you may need to comment out this line

		printf("Enter an Integer value for Encryption: "); // prompt for integer
		scanf("%d", &encrypt); // store integer

		encryption(input, encrypt); // encrypt string
		printf("\nEncrypted String: %s\n", input); // print encrypted string

		decryption(input, encrypt); // encrypt string
		printf("Decrypted String: %s\n", input); // print decrypted string

		break;

	case 2:

		printf("Enter the first String: "); // prompt for string
		fgets(strings[0], sizeof(strings[0]), stdin); // store string

		printf("Enter the second String: ");
		fgets(strings[1], sizeof(strings[1]), stdin);

		printf("Enter the third String: ");
		fgets(strings[2], sizeof(strings[2]), stdin);

		printf("Enter the fourth String: ");
		fgets(strings[3], sizeof(strings[3]), stdin);

		printf("Enter the fifth String: ");
		fgets(strings[4], sizeof(strings[4]), stdin);

		sortStrings(strings); // call sorting function

		// print strings in sorted order
		printf("\nSorted Strings:\n%s%s%s%s%s", strings[0], strings[1], strings[2], strings[3], strings[4]);

		break;

	case 3:

		printf("Enter an integer 1-50 for a multiplication table: "); // prompt for integer
		scanf("%d", &num); // store integer

		multiplicationTable(mt, num); // create multiplication table
		printf("\n"); // newline
		printMultiplicationTable(mt, num); // print multiplication table
	}
}
