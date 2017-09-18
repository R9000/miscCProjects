/* 	C Programming – ACS126-005
	Assignment 2 - encrypter.c - A program to encrypt lines of a user's input and write to a message.txt file, given a lookup table, cypher.txt.
	By: Rory Charlesworth */

#include <stdio.h>
#include <string.h> //Include the string library because otherwise the IDE complains about implicit function calls.

//Declare the function prototype for the encrypt function.
void encrypt(char currentLine[500], char outputLine[1000], char charString[62], char cypherString[124], FILE *pointer);

int main(){
	//Declare all necessary character variables for this program. All are arrays used to manage the input, output, and processing strings for the message.
	char currSet[2], charString[62], cypherString[124], currentLine [500], outputLine[1000];
	int i, iCount = 0; //Declare i and iCount, for counting through a for loop, and the indices of cypherString respectively. 
	FILE *cF, *mF; //Declare the two FILE pointers to be used here. cF is for cypher.txt and mF is for message.txt.
	cF = fopen ("cypher.txt", "r"); //First open cypher.txt in read-only mode.
	
	//Use iCount and a for loop to assign the characters from the two columns in cypher.txt to charString and cypherString. iCount allows us to keep track of the current index to be used of cypherString, independently of the loop.
	//fscanf() is used to extract each individual 'string', or group of characters.
	for(i = 0; i < 62; i++)
	{
		fscanf(cF, "%s", &charString[i]);
		fscanf(cF, "%s", currSet);
		cypherString[iCount] = currSet[0];
		cypherString[iCount+1] = currSet[1];
		iCount+=2;
	}
	
	fclose(cF); //Close cypher.txt.
	
	//Display a message to tell the user how to input their text for encryption, and how to end text entry.
	printf ("Please input your message for encryption, pressing enter for each new line.\nWhen finished, simply type the code: +++++ (5 plus symbols) on a new line, and\nthen press enter to exit.\n");
	
	mF = fopen ("message.txt", "w"); //Open message.txt in write-only mode.
	
	while(1) //Infinite while loop to allow practically infinite lines of text entry.
	{
		fgets(currentLine, 500, stdin); //Get an entire line of the user's input after they press enter, using fgets. This is limited to 500 characters per line.
		
		if (strcmp (currentLine, "+++++\n") == 0) {
			fclose(mF); //When the string "+++++" is detected alone, we close message.txt, print that we have exited, and break out of the infinite loop.
			printf ("Message encrypted and exited.\n"); 
			break;
		}
		encrypt(currentLine, outputLine, charString, cypherString, mF); //Run encrypt on the current input line, passing all necessary parameters to the function.
		fflush(stdin); //Flush both stdin and mF between lines of entry to ensure nothing is carried through in the buffer from the previous line.
		fflush(mF);
	}
		system ("pause"); //Pause before the program exits.
}
	
	
	//encrypt function body. encrypt takes the currently scanned line of text, the pointer to the empty output array, the character and corresponding cypher strings, and the message.txt file pointer to allow the encrypted output to be written to the file.
	void encrypt(char currentLine[500], char outputLine[1000], char charString[62], char cypherString[124], FILE *pointer){
		int i, j, ccindex, outputIndex = 0; //Declare i and j for loop counting, ccindex to keep track of the encrypted character's index in the cypherString, and outputIndex to keep track of our current index position in outputLine.
		char currChar; //currChar allows us to scan the current char of a string once, then use it in several different calculations.
		for(i = 0; i < strlen(currentLine) +1; i++) //Scan through the string currentLine its no. of characters+1 times, to allow for the end of string character.
		{
			currChar = *(currentLine+i); //Take in the current character from currentLine according to the loop counter i.
			if ((currChar < 123 && currChar >96)||(currChar < 91 && currChar >64)||(currChar < 58 && currChar >47))
			{
				for(j = 0; j<62; j++)
				{	//If the character is alphanumeric, loop through all terms of charString to find the correspondng index. 2 times this index is the encrypted value's index in cypherString, as cypherString is twice as long.
					if(currChar == charString[j])
					{
						ccindex = j*2; //Store the character's cypherString index in ccindex.
						break; //Break out of the for loop to avoid unnecessary computations after result has been found.
					}
				}
				outputLine[outputIndex] = cypherString[ccindex]; //Add the first character of the encripted value to the current outputIndex in the output array.
				outputLine[outputIndex+1] = cypherString[ccindex+1]; //Add the second character of the encripted value to the index after the current outputIndex in the output array.
				outputIndex += 2; //Add 2 to the outputIndex to show that we need to place new values 2 more positions along in the array.
			}else{
				//If currChar is not alphanumeric, simply add it to the output array (as it does not require encryption), and add 1 to the outputIndex.
				outputLine[outputIndex] = currChar;
				outputIndex++;
			}
		}
		fprintf (pointer, outputLine); //Print the output array to a line of message.txt
		memset(currentLine, 0, 500); //Clear currentLine and outputLine, to ensure that no characters remain for the next encryption.
		memset(outputLine, 0, 1000);
		}
