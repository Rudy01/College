/**********************************************************************
Program: Program2B
Author: Jason Downing
Date: 4/14/2014
Time spent: 5 Hours
Purpose:	This program uses the char_vector object type to store characters.
    		It does so in order to solve the "parenthesis checker problem". I
    		decided to solve this problem by using the char_vector object as a
    		stack and I only stored the left brackets. Each time the program
	     finds a right bracket, it checks the stack and sees if it can pop
		off a left bracket. If it can, it does. If it can't, it makes sure
		the problem variable is equal to 0. In reality the only time the
		program will find a string to be correct is if the stack has a size of
		zero. This is because only left brackets should be on the stack.
		And a correct string will leave no left brackets in the object.
		Note: I used the my_vector object to store the results of the tests.
	
		I used the following code to compile:
		gcc -o program2 program2b.c char_vector.c my_vector.c

**********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "char_vector.h"		// Used for the string comparision
#include "my_vector.h"		// Used to keep track of Yes and Nos

#define TRUE 1
#define FALSE 0

void run_tests(MY_VECTOR hVector, int n);
char get_user(void);
void print_vector(MY_VECTOR hVector, int n);

int main(int argc, char* argv[])
{
	MY_VECTOR hVector;
	int n;
	
	// Create a my_vector object - to hold the YES/NO values
	hVector = my_vector_init_default();
	
	// Make sure it allocated.
	if(hVector == NULL)
	{
		// It did not - print an error and exit.
		printf("Failed allocate space for the vector object!\n");
		exit(1);
	}

	// Get user input for how many strings to test
	printf("Enter a number, followed by that number of strings. -> ");
	scanf("%d%*c", &n);	// The %*c should eat any left over newlines!
	
	//printf("%d", n);
	printf("\n");
	
	// Run the tests
	run_tests(hVector, n);
	
	// Print out the Yes/No's
	print_vector(hVector, n);
	
	// Destroy the my_vector object
	my_vector_destroy(&hVector);
	
	return 0;
}

// Pre-Condition: No input has been gotten from the user
//Post-Condition: 1 char has been recieved from the user
char get_user(void)
{
	char input;			// Basic idea of this function is:
	input = getchar();		// Get ONE char from the user.
	return input;			// RETURN just that char to run_tests
}

// Pre-Condition: No output to the screen in the form of 'yes/no's
//Post-Condition: Yes/no's have been printed to the screen.
void print_vector(MY_VECTOR hVector, int n)
{
	int i;
	
	// Print out 'n' number of YES/NOs
	for(i = 0; i < n; i++)
	{
		if( *(my_vector_at(hVector, i) ) == TRUE)	// TRUE is 1 / YES
			printf("%d Yes \n", i+1);
		else									// FALSE / NO
			printf("%d No \n", i+1);
	}
}

// Pre-Condition: no string tests have been run
//Post-Condition: n number of strings has been tested
void run_tests(MY_VECTOR hVector, int n)
{
	CHAR_VECTOR hChar;	
	char *temp = NULL;
	char input = '\0', test = '\0';
	int i, problem;
	int count;

	// Run 'n' number of vector tests
	for(i = 0; i < n; i++)	
	{
		count = 0;
		problem = 0;
		test = '\0';
		
		// Create a char_vector object
		hChar = char_vector_init_default();
		
		// Make sure it allocated.
		if(hChar == NULL)
		{
			//It did not - print an error and exit.
			printf("Failed allocate space for the vector object!\n");
			exit(1);
		}
		
		// Take user input in the form of a do / while loop
		do{
			test = '\0';			// Make test 0.
			input = get_user();
			
			// Check and see if we have a left bracket
			if(input == '[' || input == '{' || input == '(') 
			{
				// If we do, add it to the vector!
				if(char_vector_push_back(hChar, input) == FAILURE) 
				{
					// Error message if we fail to add to the vector.
					printf("Failed to push to the vector!\n");
					exit(1);
				}
			}
			
			// If we do not, then we have a right bracket.
			if(input == ']' || input == '}' || input == ')') 
			{
				// First check the last item in the vector.
				temp = char_vector_at(hChar, char_vector_size(hChar) - 1 );
					if(temp != NULL) 	// Make sure there wasn't a problem.
						test = *temp;	// Store temp's char in test
			
				// Then test and see if it is a match to the left facing bracket.
				if(test == '[' && input == ']') 
				{	 
					// MATCH - pop off the last item.
					char_vector_pop_back(hChar);
				}
			
				if(test == '{' && input == '}') 
				{ 
					// MATCH - pop off the last item.
					char_vector_pop_back(hChar);
				}
			
				if(test == '(' && input == ')') 
				{ 
					// MATCH - pop off the last item.
					char_vector_pop_back(hChar);
				}

				if(test == '\0')
				{
					// Failure - can't have ] be a valid string
					problem = 2;
				}
			}

			count++;
			
			// Run until an 'enter' is pressed.
			// Or until we hit EOF if using redirection.
		}while(input != '\n' && input != EOF);	

		// Check  to see if the vector is empty & and that we did not find any problems.
		if(char_vector_size(hChar) == 0 && problem != 2) 
		{
			// Vector is empty & last value was left bracket.
			problem = 1;	// String is valid.
		}
		
		// The string wasn't valid if we found problems.
		if(problem == 2)
			problem = 0;	// So make sure to note this.
		
		// Store either 0 or 1 for No or Yes
		if( (my_vector_push_back(hVector, problem)) == FAILURE)
		{
			// Error message if we fail to add to the vector.
			printf("Failed to push to the vector!\n");
			exit(1);
		}
		
		// Destroy the char_vector object after each round
		char_vector_destroy(&hChar);
	}
	
}
