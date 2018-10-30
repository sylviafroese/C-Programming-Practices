//------------------------------------------------------------------------
// NAME: Sylvia Froese
// STUDENT NUMBER: 6203180
// COURSE: COMP 2160, SECTION A02
// INSTRUCTOR: Yang Wang
// ASSIGNMENT: Assignment 1, Question 2
//
// REMARKS: The purpose of the program is to read in text
// line by line and output the word with the largest total of ascii values
// for that line of text.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100 // max length of input line to be read into a character array

int main()
	{

	char inputLine[MAX];  // this is the character line of input we are reading in
	char* currWord;  // this pointer keeps track of the current word we are working with
	char* word;  // this pointer is the word that has been tokenized out of the line of text
	char* bigWord;  // this pointer is the word with the biggest weight so far in our line of text
	

	int line = 0;  //this keeps track of line numbers for each line of text we read in
	int bigWeight;  // this holds the biggest weight for that line of text
	int weight = 0; //this keeps the current weight for a character
	int index;  // this lets us index through a word
	int wordWeight; //this is the weight of the word
	long wordLen;  // this is the length of a word

	// Prompt the user for a line of text input
	printf("Type in a line of text (press Cntl-D to stop):\n");

        // do the following for each line of text being read in until End of File marker is reached
          while (fgets (inputLine, 99, stdin) != NULL)  // read first line of text

   	     {
             
	     word = strtok ( inputLine, " ");  // tokenize the word from the current line of text
	     
	     line++;  // update line number
        
	     bigWord = NULL;  // initialize the biggest word to NULL
	     bigWeight = 0;   // initialize the biggest weight of that word to 0

	     while ( (word != NULL) && ( *word != '\n') && ( *word != '\t') ) //working through one line of text at a time
	         {

	         weight = (int) *word; // weight of 1 char in the word  (casts the ascii value of the character to an integer)
                 currWord = word; // keep track of the current word that we are working on

 	         index = 0; // initialize index to 0 for the following while loop

	         wordWeight = weight;  // keep track of the weight of the word

	         wordLen = strlen(word);  // keep track of the length of the word


	         /* index through the word (character by character) and get the weight of each character 
		    and keep a sum of the total weights for each character */
	         while (index < wordLen)
	            {

		    word++; // point to next character in the word

		    weight = (int) *word; // weight of a char in word

		    wordWeight += weight;  // add the current character weight to the accumulating total weight of the word

		    index++; //	update the index of the word
	            } // end for inner-most while

	         /* if the weight of the current word is bigger than the biggest weight so far, 
                    then the new word is the biggest Word in the line of text and the token 
                    weight is the biggest Weight in the line of text */

	        if (wordWeight > bigWeight)
		    {
		    bigWord = currWord;
		    bigWeight = wordWeight;
		    }	

	        word = strtok(NULL, " ");  // grab next word in the line of text
	        } // end for middle while

               // If a word with the largest weight exists for a given line of text, then print out the word with the largest weight for that line of text
	       // A word with the largest weight will not be printed if a line of text has no words in it

	       if (bigWord != NULL) 

	          {
	          printf("line %d\'s word: %s\n",line, bigWord);
	          }

     
     // prompt user for the next line of input
     printf("Type in a line of text (press Cntl-D to stop):\n");


     } // end for outer-most while

     printf("\n\nProgram completed normally.\n\n");

     return EXIT_SUCCESS;

 } // end main
