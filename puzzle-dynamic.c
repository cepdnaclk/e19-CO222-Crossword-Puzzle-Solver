
/* A C program to solve a crossword puzzle (puzzle-static.c)

Group No. 01

Authors -- E/19/166 - Jayathunga W.W.K.
        -- E/19/324 - Rathnayake R.M.B.D.K.
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>


//Introduce a structure for the puzzle
struct puzzle {
    char matrix[100][100];
};

// Declare prototypes of the functions
void print(char puzzle[100][100]);
struct puzzle checkVertical(int horizontalPosition, int verticalPosition, struct puzzle myMatrix, char *currentWord);
struct puzzle checkHorizontal(int horizontalPosition, int verticalPosition, struct puzzle myMatrix, char *currentWord);
void printValidPuzzle(struct puzzle solution, int gridLength);
void fillWords(struct puzzle myPuzzle, char **words, int wordIndex, int gridLength);

int main() {

    // Declare required variables
    int rowNum = 0, rows = -1, invalidcount = 0, puzzlechars = 0, invalid = 0, blankLine = 0, wordNum = 0, impossible = 0;
    int wordcount = -1;

    // Allocate memory for the puzzle dynamically for rows and columns
    char **puzzle1 = malloc(sizeof(char *) * 100);
    for(int i=0;i<100;i++){
        puzzle1[i]=malloc(sizeof(char)*100);
    }

    // Allocate memory for the input words dynamically for rows and columns
    char **words = malloc(sizeof(char *) * 100);
    for(int i=0;i<100;i++){
        words[i]=malloc(sizeof(char)*100);
    }

    // Introduce a while loop to get inputs iteratively and print the puzzle
    while(1) {

        // Introduce condition to get the puzzle as user inputs
        if(blankLine == 0) {

            gets(puzzle1[rowNum]);
        
        
            rows++;

            // If the first row of the puzzle is null then it counts a invalid input
            if((rows == 0) && (strlen(puzzle1[rowNum]) == 0)) {
                invalid=1;

            // If the other line is a blank, it finishes taking the inputs for the puzzle
            } else if(strlen(puzzle1[rowNum]) == 0) {
                blankLine=1;

            // Check the current row of the puzzle if there are invalid characters
            } else if(strlen(puzzle1[rowNum])) {

                // Direct along the row
                for(int columnIndex = 0; columnIndex < strlen(puzzle1[rowNum]); columnIndex++) {

                    // Introduce condition to identify invlid characters
                    if(((puzzle1[rowNum][columnIndex] != '#') && (puzzle1[rowNum][columnIndex] != '*')) && (isalpha(puzzle1[rowNum][columnIndex]) == 0)) {
                        invalidcount++;
                    }

                    // Count for hash signes
                    if(puzzle1[rowNum][columnIndex] == '#') {
                        puzzlechars++;
                    }
                }
                // Counts an invalid input
                if(invalidcount > 0) {
                    invalid = 1;
                }
            }
            // Increase the number of rows
            rowNum++;
        }

        // Introduce condition to take the words as the input
        if(blankLine == 1) {

            gets(words[wordNum]);
            wordcount++;

            // If the word count is zero, then it is an invalid input
            if((wordcount == 0) && (strlen(words[wordNum]) == 0)) {
                invalid = 1;

            // If a blank line is given, it stops taking inputs 
            } else if((strlen(words[wordNum]) == 0) && (wordcount > 0)) {
                blankLine = 2;

            // Introduce condition to check for invalid word inputs
            } else if(strlen(words[wordNum])) {

                // Direct along the word length
                for(int wordIndex = 0; wordIndex < strlen(words[wordNum]); wordIndex++) {
                    if(isalpha(words[wordNum][wordIndex]) == 0) {
                        invalidcount++;
                    }
                }

                // Counts for invalid inputs
                if(invalidcount > 0) {
                    invalid = 1;
                }
            }
            wordNum++;
        }
        // Introduce condition to stop taking inputs
        else if(blankLine == 2) {

            // Introduce condition to recognize invalid inputs
            if(invalid == 1) {
                printf("INVALID INPUT");
                break;
            }

            // Introduce condition to recognize impossible to fill state
            else if(impossible == 1) {
                printf("IMPOSSIBLE");
                break;

            // Introduce condition to recognize possible to fill state
            } else if((rows) && (invalid==0)) {

                // Declare required variables for filling the puzzle
                struct puzzle draftPuzzle;
                int iteration1;
                int iteration2;

                // Check the puzzle character by character
                for(iteration1 = 0; iteration1 < 100; iteration1++) {
                    for(iteration2 = 0; iteration2 < 100; iteration2++) {
                        draftPuzzle.matrix[iteration1][iteration2] = puzzle1[iteration1][iteration2];
                    }
                }
               
                // By trying the all combinations, fill the pizzle
                fillWords(draftPuzzle, words, 0, strlen(puzzle1[0]));

                // Release the dynamically allocated memory after using it
                 free(puzzle1);
                free(words);

                printf("IMPOSSIBLE");

                return 0;

             } else {

                // If all the above are not satisfied, finally program reaches here
                printf("INVALID INPUT");

                return 0;
            }
        }
    }
    
    return 0;
}

// A function to print the puzzle
void print(char puzzle[100][100]) {

    // Direct along the current row 
    for(int row = 0; row < 10; row++) {

        // Break when the rows of the puzzle are finished
        if(strlen(puzzle[row]) == 0) {
            break;

        // Introduce the procedure to print the puzzle otherwise
        } else {

            // Direct along the current column
            for(int column = 0; column <strlen(puzzle[0]); column++) {
                printf("%c", puzzle[row][column]);
            }
        }
        printf("\n");
    }
}

// A function to check if the current word can be filled vertically 
struct puzzle checkVertical(int horizontalPosition, int verticalPosition, struct puzzle myMatrix, char *currentWord) {
    
    // Declare variables to search verttically
    int lengthOfWord = strlen(currentWord);
    int currentIndex;
    
    // Direct along the current word
    for (currentIndex = 0; currentIndex < lengthOfWord; currentIndex++) {

        // Introduce conditions to fill characters of the word in the puzzle
        if (myMatrix.matrix[horizontalPosition + currentIndex][verticalPosition] == '#' || myMatrix.matrix[horizontalPosition + currentIndex][verticalPosition] == currentWord[currentIndex]) {

            // Fill the characters
            myMatrix.matrix[horizontalPosition + currentIndex][verticalPosition] = currentWord[currentIndex];
        } else {
            
            // Introduce a condition to search for unfilled words
            // the can't fill state can be checked with this
            myMatrix.matrix[0][0] = '@';

            return myMatrix;
        }
    }

    return myMatrix;
}

// A function to check if the current word can be filled horizontally
struct puzzle checkHorizontal(int horizontalPosition, int verticalPosition, struct puzzle myMatrix, char *currentWord) {
    
    // Declare variables to search horizontally
    int lengthOfWord = strlen(currentWord);
    int currentIndex;
    
    // Direct along the current word
    for (currentIndex = 0; currentIndex < lengthOfWord; currentIndex++) {

        // Introduce conditions to fill characters of the word in the puzzle
        if (myMatrix.matrix[horizontalPosition][verticalPosition + currentIndex] == '#' || myMatrix.matrix[horizontalPosition][verticalPosition + currentIndex] == currentWord[currentIndex]) {
            
            // Fill the characters
            myMatrix.matrix[horizontalPosition][verticalPosition + currentIndex] = currentWord[currentIndex];
        } else {
            
            // Introduce a condition to search for unfilled words
            // the can't fill state can be checked with this
            myMatrix.matrix[0][0] = '@';
            
            return myMatrix;
        }
    }
    
    return myMatrix;
}

// A function to print the puzzle if it is completelly filled
void printValidPuzzle(struct puzzle solution, int gridLength) {

    // Declare required variables to search characters in the puzzle one by one
    int row;
    int column;

    // Direct along the row
    for(row = 0; row < gridLength; row++) {

        // Direct along the column
        for(column = 0; column < gridLength; column++) {

            // Introduce the condition to check if the function is incomplete
            if(solution.matrix[row][column] == '#') {
            
            // when the puzzle is incomplete it doesn't print
                return;

            }
        }
    }

    // If the puzzle is completely filled then it will print
    print(solution.matrix);

    // This avoids the other combinations of complete puzzle being printed by recursive operation
    exit(0);

}

void fillWords(struct puzzle myPuzzle, char **words, int wordIndex, int gridLength) {

    // Declare required variables to fill the words
    char *word=malloc(10*sizeof(char));
    
    // Copy word to new variable 
    strcpy(word, words[wordIndex]);
    
    // Get the length of the words
    int wordLen = strlen(word);
    
    // Introduce conditions to take words only
    if (wordLen>0) {
        
        int maxLen = gridLength - wordLen;

        // Use for loop to fill the words vertically
        // Direct along the column
        for (int horizontal = 0; horizontal < gridLength; horizontal++) {

            // Direct along the row
            for (int vertical = 0; vertical <= maxLen; vertical++) {

                // check the vertical possible words
                struct puzzle temp = checkVertical(vertical, horizontal, myPuzzle, word);
                
                // Check if the puzzle is compatible to be filled
                if (temp.matrix[0][0] != '@') {
                    
                    // Fill the characters to the suitable positions
                    fillWords(temp, words, wordIndex + 1, gridLength);
                }
            }
        }
        // Use a for loop to check whether a word can be filled horizontally
        // Direct along the row
        for (int row = 0; row < gridLength; row++) {

            // Direct along the column
            for (int column = 0; column <= maxLen; column++) {


                // check the horizontal possible words
                struct puzzle temp = checkHorizontal(row, column, myPuzzle, word);

                // Check if the puzzle is compatible to be filled
                if (temp.matrix[0][0] != '@') {
                    
                    // Fill the characters to the suitable positions
                    fillWords(temp, words, wordIndex + 1, gridLength);
                }
            }
        }
    free(word);
    } else {
        
        // Call the print function to check the completeness of the puzzle and print if it is complete
        printValidPuzzle(myPuzzle, gridLength);
        
        return;

    }
}
