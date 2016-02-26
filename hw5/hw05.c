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
// Valid grade input: A+, A, A-, B+, B, B-, ...
// Valid education level input : f, so, j, or s.
// All input will be a valid length and no more than the allowed number of students will be added to the list

/* **** Compiled and tested using GCC **** */

#include <stdio.h>   
#include <string.h>
#include <ctype.h>



typedef enum { freshman = 0, sophomore, junior, senior } education; // enumeration type education level

struct student {
	char firstName[100];
	char lastName[100];
	char grade[30];
	education level;
};

int count = 0; // the amount of students currently stored in the list (initialized at 0)

struct student list[30]; // initialize list of students

// forward declaration of functions
void flush();
void branching(char);
void read();
void add(char*, char*, char*, char*, struct student*);
void display();
void save(char* fileName);
void load(char* fileName);

int main()
{
	load("Student_List.txt"); // load list of students from file

	char ch = 'i';
	printf("Student Roster:\n");

	do
	{
		printf("Please enter your selection:\n");
		printf("\ta: add a new student\n");
		printf("\td: display students\n");
		printf("\tq: quit and save your list\n");
		ch = tolower(getchar());
		flush();
		branching(ch);
	} while (ch != 'q');

	save("Student_List.txt"); // save list of students to file
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
	switch (c)
	{
	case 'a': read(); break;
	case 'd': display(); break;
	case 'q': break;
	default: printf("Invalid input!\n");
	}
}

// This function is already implemented for you. It prompts for and stores a student along with their grade and education level.
// It then calls the add() function (which is to be implemented) sending over those parameters (along with list).
void read()
{
	char student_firstName[100];
	char student_lastName[100];
	char student_grade[30];
	char student_level[100];

	printf("\nEnter the student's first name:\n");
	fgets(student_firstName, sizeof(student_firstName), stdin);

	printf("\nEnter the student's last name:\n");
	fgets(student_lastName, sizeof(student_lastName), stdin);

	printf("\nEnter the student's grade (A+,A,A-,...):\n");
	fgets(student_grade, sizeof(student_grade), stdin);

	printf("\nEnter the student's education level (f/so/j/s):\n");
	fgets(student_level, sizeof(student_level), stdin);

	
	// discard '\n' chars attached to input; NOTE: If you are using GCC, you may need to comment out these 4 lines
	student_firstName[strlen(student_firstName) - 1] = '\0';
	student_lastName[strlen(student_lastName) - 1] = '\0';
	student_grade[strlen(student_grade) - 1] = '\0';
	student_level[strlen(student_level) - 1] = '\0';
	

	add(student_firstName, student_lastName, student_grade, student_level, list);
	printf("\n"); // newline for formatting
}

//	Q1: add (40)
//	This function is used to insert a new student into the roster.
//	Your list should be sorted alphabetically by last name, so you need to search for the correct index to add into your list.
//  If a student already exists with the same last name, then you will need to sort them by their first names.
//  Do not allow for the same student to be added to the list multiple times. (same first name and same last name).
//
//  NOTE: You must convert the char pointer "student_level" to an enum type and store it in the list. This will be tested.
//  (You must store all of the required information correctly to pass all of the test cases)
//  NOTE: You should not allow for the same student to be added twice, you will lose points if you do not account for this.
//  (That means that students on the list are allowed to have the same first names OR the same last names, but not both)
//  Again, you will lose points if you do not account for these cases.
//
//  It may be helpful to print "Student added!" or "This student is already on the list!" at the correct places for debugging purposes.
//
//  You are not required to use pointer operations for your list but you may do so if you'd like. 
//	'list' is passed to this function for testing purposes only, it is global
void add(char* student_firstName, char* student_lastName, char* student_grade, char* student_level, struct student* list)
{
	int i, j;
	struct student tmp;
	i = j = 0;

	if(count == 30)
	{
		printf("Roster full\n");
		return;
	}

	int l = 0;
	education edulevel;

	if(strcmp(student_level, "f") == 0)
		edulevel = 0;
	else if(strcmp(student_level, "so") == 0)
		edulevel = 1;
	else if(strcmp(student_level, "j") == 0)
		edulevel = 2;
	else if(strcmp(student_level, "s") == 0)
		edulevel = 3;

	// checking to double addition
	for(i = 0; i < 30; i++)
	{
		if(strcmp(list[i].firstName, student_firstName) == 0 && strcmp(list[i].lastName, student_lastName) == 0)
		{
			printf("Student already exists\n");
			return;
		}
	}


	// adding
	strcpy(list[count].firstName, student_firstName);
	strcpy(list[count].lastName, student_lastName);
	strcpy(list[count].grade, student_grade);
	list[count].level = edulevel;

	
	printf("student added\n");

	// sorting

	for(i = 0; i < 30; i++)
	{
		for(j = i; j < 30; j++)
		{
			if(strcmp(list[i].firstName, list[j].firstName) > 0)
			{
				strcpy(tmp.firstName, list[i].firstName);
				strcpy(tmp.lastName, list[i].lastName);
				strcpy(tmp.grade, list[i].grade);
				tmp.level = list[i].level;

				strcpy(list[i].firstName, list[j].firstName);
				strcpy(list[i].lastName, list[j].lastName);
				strcpy(list[i].grade, list[j].grade);
				list[i].level = list[j].level;

				strcpy(list[j].firstName, tmp.firstName);
				strcpy(list[j].lastName, tmp.lastName);
				strcpy(list[j].grade, tmp.grade);
				list[j].level = tmp.level;
			}

			if(strcmp(list[i].firstName, list[j].firstName) == 0)
			{

				if(strcmp(list[i].lastName, list[j].lastName) > 0)
				{
					strcpy(tmp.firstName, list[i].firstName);
					strcpy(tmp.lastName, list[i].lastName);
					strcpy(tmp.grade, list[i].grade);
					tmp.level = list[i].level;

					strcpy(list[i].firstName, list[j].firstName);
					strcpy(list[i].lastName, list[j].lastName);
					strcpy(list[i].grade, list[j].grade);
					list[i].level = list[j].level;

					strcpy(list[j].firstName, tmp.firstName);
					strcpy(list[j].lastName, tmp.lastName);
					strcpy(list[j].grade, tmp.grade);
					list[j].level = tmp.level;
				}
			}
		}
	}

	count++;

}

//  Q2: display (10)
//	Traverse your list and print the students the required format; see word document for output format.
//  Your output must match the expected output format or you risk losing points.
//  If the list is empty, print: "There are no students on this roster!\n"
//	(hint: Use can use your global integer value "count" to see how many students are in your list)
void display()
{
	if(count == 0)
		printf("Nothing to print\n");

	int i = 0;
	for(i = 30 - count; i < 30; i++)
	{
		printf("%s, %s\n", list[i].lastName, list[i].firstName);

		// education level
		if(list[i].level == 0)
			printf("Education level: freshmen\n");
		else if(list[i].level == 1)
			printf("Education level: sophomore\n");
		else if(list[i].level == 2)
			printf("Education level: junior\n");
		else if(list[i].level == 3)
			printf("Education level: senior\n");

		printf("Grade:\t%s\n", list[i].grade);

		putc('\n', stdout);
	}



}

// This function saves the array of structures to file. It is already implemented for you.
// You should understand how this code works so that you know how to use it for future assignments.
void save(char* fileName)
{
	FILE* file;

	file = fopen(fileName, "wb");
	if (file == NULL)
	{
		return;
	}
	else
	{
		fwrite(&count, sizeof(count), 1, file);
		for (int i = 0; i < count; i++)
		{
			fwrite(list[i].firstName, sizeof(list[i].firstName), 1, file);
			fwrite(list[i].lastName, sizeof(list[i].lastName), 1, file);
			fwrite(list[i].grade, sizeof(list[i].grade), 1, file);
			fwrite(&list[i].level, sizeof(list[i].level), 1, file);
		}
		fclose(file);
	}
}

// This function loads the array of structures from file. It is already implemented for you.
// You should understand how this code works so that you know how to use it for future assignments.
void load(char* fileName)
{
	FILE* file;

	file = fopen(fileName, "rb");
	if (file == NULL)
	{
		return;
	}
	else
	{
		fread(&count, sizeof(count), 1, file);
		for (int i = 0; i < count; i++)
		{
			fread(list[i].firstName, sizeof(list[i].firstName), 1, file);
			fread(list[i].lastName, sizeof(list[i].lastName), 1, file);
			fread(list[i].grade, sizeof(list[i].grade), 1, file);
			fread(&list[i].level, sizeof(list[i].level), 1, file);
		}
		fclose(file);
	}
}
