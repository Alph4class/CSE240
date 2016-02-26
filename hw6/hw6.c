// READ BEFORE YOU START:
// You are given a partially completed program that creates a roster of students for a class.
// Each student has the corresponding information: grade in the class and education level.
// To begin, you should trace through the given code and understand how it works.
// Please read the instructions above each required function and follow the directions carefully.
// If you modify any of the given code, the return types, or the parameters, you risk failing the automated test cases.
//
// You are to assume that all input is valid:
// Valid first name: String containing alphabetical letters beginning with a capital letter
// Valid last name: String containing alphabetical letters beginning with a capital letter
// Valid grade input: any integer value between 1 and 100 (error handling is implemented)
// Valid education level input : f, so, j, or s. (error handling is implemented)
// All input will be a valid length and no more than the allowed amount of memory will be input

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef enum { freshman = 0, sophomore, junior, senior } education; // enumeration type education level

struct student {
	char firstName[100];
	char lastName[100];
	education level;
	int grade;
	struct student* next;
} *list = NULL;

// forward declarations
void flush();
void branching(char c);
void helper(char c);

// These have been ordered in a way of suggested completion. 
//You will need to complete search() before you start delete_one()
int add(struct student*);						// 15 points
double average();								// 10 points
struct student* search(struct student*);		// 10 points
void delete_one(struct student*);				// 15 points

int main()
{
	char ch = 'i';
	printf("Student Roster:\n");

	do {
		printf("Please enter your selection\n");
		printf("\ta: add a new student to the list\n");
		printf("\td: delete a student from the list\n");
		printf("\ts: search for student by name\n");
		printf("\tr: determine the class average\n");
		printf("\tq: quit \n");
		ch = tolower(getchar());
		flush();
		branching(ch);
	} while (ch != 'q');

	return 0;
}

// consume leftover '\n' characters
void flush()
{
	int c;
	do c = getchar(); while (c != '\n' && c != EOF);
}

// branch to different tasks
void branching(char c)
{
	switch (c) {
	case 'a':
	case 'd':
	case 's':
	case 'r':
		helper(c);
		break;
	case 'q':
		break;
	default:
		printf("\nInvalid input!\n\n");
	}
}

// The helper function is used to determine how much information is needed and which function to send that information to.
// It uses pointers that are returned from some functions to produce the correct ouput.
// There is no implementation needed here, but you should study this function and know how it works.
// It is always helpful to understand how the code works before implementing new features.
// Do not change anything in this function or you risk failing the automated test cases.
void helper(char c) {

	char student_firstName[100];
	char student_lastName[100];
	char* student_level = (char*)malloc(100);

	int valid_level = -1; // used to determine if the input education level is acceptable
	int tempI; // temporary integer
	double tempD; // temporary double

	// create new temporary pointers
	struct student *ptr = (struct student *)malloc(sizeof(struct student));

	if (c == 'r')
	{
		tempD = average(); // compute class average
		if (tempD < 0) // tempD should equal -1 if the list is empty
		{
			printf("\nThere are no students on the list.\n\n");
			return;
		}
		printf("\nThe class average is: %.2f\n\n", tempD);
		return;
	}
	else if (c == 'a')
	{
		printf("\nEnter the student's first name:\n");
		fgets(student_firstName, sizeof(student_firstName), stdin);

		printf("\nEnter the student's last name:\n");
		fgets(student_lastName, sizeof(student_lastName), stdin);

		// discard '\n' chars attached to input; NOTE: If you are using GCC, you may need to comment out these 2 lines
		student_firstName[strlen(student_firstName) - 1] = '\0';
		student_lastName[strlen(student_lastName) - 1] = '\0';

		// stores the first name and last name of the student into pointer
		strcpy(ptr->firstName, student_firstName);
		strcpy(ptr->lastName, student_lastName);

		printf("\nEnter the student's grade:\n");
		tempI = -1;
		while (tempI < 0 || tempI > 100)
		{
			scanf("%d", &tempI);

			if (tempI >= 0 && tempI <= 100)
				ptr->grade = tempI; // stores the grade of the student into pointer
			else
				printf("Please enter a grade between 0 and 100.\n");
		}

		printf("\nEnter the student's education level (f/so/j/s):\n");

		// stores the education level of the student into pointer
		while (valid_level < 0)
		{
			scanf("%s", student_level);

			if (strcmp(student_level, "f") == 0)
			{
				valid_level++;
				ptr->level = freshman;
			}
			else if (strcmp(student_level, "so") == 0)
			{
				valid_level++;
				ptr->level = sophomore;
			}
			else if (strcmp(student_level, "j") == 0)
			{
				valid_level++;
				ptr->level = junior;
			}
			else if (strcmp(student_level, "s") == 0)
			{
				valid_level++;
				ptr->level = senior;
			}
			else printf("Please enter a valid education level (f/so/j/s).\n"); // error handling
		}

		// always set next equal to NULL before adding to a list
		// if it is placed at the end of the list, you know where to stop traversing
		ptr->next = NULL;
		tempI = add(ptr); // add student (should return 0 if the student is already on the list)
		if (tempI == 0) printf("\n%s is already on the list.\n\n", student_lastName);
		else printf("\n%s added to the list.\n\n", student_lastName);
		flush();
	}
	else
	{
		printf("\nEnter the student's last name:\n");
		fgets(student_lastName, sizeof(student_lastName), stdin);

		// discard '\n' char attached to input; NOTE: If you are using GCC, you may need to comment out this line
		student_lastName[strlen(student_lastName) - 1] = '\0';

		// stores the last name of the student into pointer
		strcpy(ptr->lastName, student_lastName);

		struct student *temp = search(ptr); // search for student in list
		if (temp == NULL) // student not found
		{
			printf("\n%s not found.\n\n", student_lastName);
			return;
		}
		if (c == 's')
		{
			printf("\nCurrent grade for %s: %d\n\n", temp->lastName, temp->grade);
			return;
		}
		delete_one(ptr); // delete student
		printf("\n%s deleted from the list.\n\n", student_lastName);
		return;
	}
}

// Q1: add (15)
// Similar to hw05, you will be inserting into a list of students sorted by their last name.
// Differing from hw05, there is no limit to how many students can be in this list.
// For this assignment, you can also assume that no 2 students will have the same last name.
// NOTE: You still need to check if the input student already exists on the list,
// however, no 2 students will have the same last name and differing first names.
//
// This means that if the last name of the "new_student" matches the last name of a student on the list,
// then it is enough to assume that the student is already on the list and should not be added.
// To clarify, you will be tested to assure that a student is not added to the list twice.
//
// If the student is already on the list, return the integer value 0.
// If the student is not on the list, add the student to the list and return the integer value 1.
//
// "list" is initialized as NULL. Use this as your 'head' of the list and insert into it accordingly. 
// There are 4 possibilities for inserting into the list:
//	- inserting into an empty list
//	- inserting at the beginning of the list
//	- inserting inbetween 2 nodes in the list
//	- inserting at the end of the list
int add(struct student* new_student)
{
	struct student* follow = list;
	struct student *temp, *trav = list;

	//inserting into an empty list
	if(follow == NULL)
	{
		new_student->next = NULL;
		list = new_student;
		return 1;
	}

	//checking for duplication
	if(strcmp(new_student->lastName, follow->lastName) == 0)
	{
		printf("Student already exists\n");
		return 0;
	}

	/*

	//adding at the beginning of the list
	if(strcmp(new_student->lastName, list->lastName) < 0)
	{
		new_student->next = follow;
		follow = new_student;
		return 1;
	}

	//inserting between 2 nodes
	while(trav->next != NULL)
	{
		if(strcmp(trav->next->lastName, new_student->lastName) > 0)
		{
			new_student->next = trav->next;
			trav->next = new_student;
		}

		trav = trav->next;
		return 1;
	}
	*/


	while(follow->next != NULL)
	{
		follow = follow->next;
	}

	//adding at the end
	new_student->next = NULL;
	follow->next  = new_student;

	return 1;
}

// Q2: search (10)
// In this function, you are passed a struct student* parameter named 'student' to find their current grade.
// Stored inside this pointer, is the last name of the student that you want to find in your list (student->lastName)
// You need to return a pointer to a node in your list that contains that student's information (that will include student->grade)
// To find that pointer, you need to traverse your lise. If that student does not exist in your list, you must return NULL.
// (You must return a pointer to a node in your list. Do not create a pointer that just includes the grade, you will risk losing points)
// (Remember that it is enough search for a student by their last name since no 2 students will have the same last name)
struct student* search(struct student* student)
{
	struct student* temp = list;

	while(temp != NULL)
	{
		if(strcmp(temp->lastName, student->lastName) == 0)
		{
			return temp;
		}

		temp = temp->next;
	}

	temp = NULL;
	return temp;
}

// Q3: average (10)
// In this function, you need to return the average of all of the students' grades that exist on the list.
// To do this you will need to traverse your list and access each student's grade.
// If there are no students on the list, you should return -1 (this will be tested).
double average()
{
	double average, count;
	struct student* temp = list;

	if(temp == NULL)
		return -1;
	
	while(temp != NULL)
	{
		average = average + temp->grade;
		count++;
		temp = temp->next;
	}

	average = average / count;

	return average;


}

// Q4: delete_one (15)
// In this function, you are passed a struct student* parameter named 'student' to delete the corresponding student on your list.
// Stored inside this pointer, is the last name of the student that you want to find in your list (student->lastName)
// The search function is called before this function to check if the student exists, you can assume that the student is on the list.
// You will need to find the student and delete it using proper memory management to ensure no memory leaks.
// (Remember that it is enough search for a student by their last name since no 2 students will have the same last name)
void delete_one(struct student* student)
{
	struct student *tmp, *trav;
	tmp = trav = list;

	//deleting first node
	while(strcmp(trav->lastName, student->lastName) == 0)
	{
		free(trav);
		trav = NULL;

		return;
	}

	while(trav->next != NULL)
	{
		// deleting between nodes
		if(strcmp(trav->next->lastName, student->lastName) == 0)
		{
			tmp = trav->next->next;
			free(trav->next);
			trav->next = tmp;
		}

		return;

	}

	//deleting node at the end
	while(trav->next->next != NULL)
	{
		trav = trav->next;
	}
	tmp = trav->next;
	free(tmp);
	trav->next = NULL;

}
