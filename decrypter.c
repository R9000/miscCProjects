/* 	C Programming – ACS126-005
	Assignment 2 - decrypter.c - A program to decrypt lines of a message from message.txt that were encrypted by encripter.c, and print them to the screen.
	By: Rory Charlesworth */

#include <stdio.h>
#include <string.h>

//Declare the function prototype for the decrypt function.
void decrypt(char currentLine[1000], char charString[62], char cypherString[124], char outputLine[500]);

int main() {
	int i, iCount = 0; //Declare i and iCount, for counting through a for loop, and the indices of cypherString respectively. 
	//Declare all necessary character variables for this program. All are arrays used to manage the input, output, and processing strings for the message. Here, currentLine is twice the size of outputLine, as the decryption is a 2 to 1 character method.
	char currSet[2], charString[62], cypherString[124], currentLine [1000], outputLine[500];
	FILE *cF, *mF;//Declare the two FILE pointers to be used here. cF is for cypher.txt and mF is for message.txt.
	cF = fopen("cypher.txt", "r"); //First open cypher.txt in read-only mode.
	
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
	
	mF = fopen("message.txt", "r"); //Open message.txt in write-only mode.
	
	while(fgets(currentLine, 1000, mF)) //Scan through message.txt, line by line with fgets, until EOF is reached. Place each line in currentLine when it is scanned.
	{
		decrypt(currentLine, charString, cypherString, outputLine); //Run encrypt on the current line of message.txt, passing all necessary parameters to the function.
		printf("%s\n", outputLine); //Use the output string from decrypt to print out the decrypted line to the screen.
		memset(currentLine, 0, 500); //Clear currentLine and outputLine, to ensure that no characters remain for the next decryption.
		memset(outputLine, 0, 1000);
	}
	
	fclose(mF); //When the EOF has been reached, close message.txt and print out a termination message to let the user know the program has finished.
	printf("\n------------\nEntire message decrypted and displayed above.\n");
	system("pause"); //Pause before the program exits.
}

//decrypt function body. decrypt takes the currently scanned line of message.txt, the pointer to the empty output array, and the character and corresponding cypher strings.
void decrypt(char currentLine[1000], char charString[62], char cypherString[124], char outputLine[500])
{
	int i, j, ccindex, outputIndex = 0; //Declare i and j for loop counting, ccindex to keep track of the encrypted character's index in the cypherString, and outputIndex to keep track of our current index position in outputLine.
	char currChar1, currChar2; //currChar1 and 2 allow us to sample a character from the string and its neighbor, allowing us to compare both parts of the 2-character encryption.
	
	for(i = 0; i<strlen(currentLine+1); i++) //Scan through the string currentLine its no. of characters+1 times, to allow for the end of string character.
	{
		currChar1 = *(currentLine+i); //Take in the current character from currentLine according to the loop counter i.
		currChar2 = *(currentLine+i + 1); //Take in the next character in currentLine.
		
		if(currChar1 >64 && currChar1 < 75){ //If the character is A to F (the only characters used for the encryption), scan through cypherString in pairs of values (j increases by 2 every time) until the given code and the characters in the array match.
			for(j = 0; j<124; j+=2)
			{
				if(currChar1 == cypherString[j] && currChar2 == cypherString[j+1])
				{
					ccindex = j/2; //Divide the index by 2 to get the index of charString at which the decrypted character resides.
					outputLine[outputIndex] = charString[ccindex]; //Add this decrypted character from charString to the output array.
					outputIndex++; //Add one to the outputIndex to ensure we will now edit the next value along.
					i++; //Add 1 to i (in addition to the 1 that the loop adds) in order to jump over the next character in the array to the next pair (or non-alphanumeric character).
					break; //Break out of the for loop to avoid unnecessary computations after result has been found.
				}
			}
		}else{
			//If the character is not A to F, simply add currChar1 to the output array, and ad 1 ot the outputIndex to ensure we edit the next element of the array next time.
			//Notice that we do not add 1 to i this time, and this is because we only needed to add a character to add to the outputArray. Consequently, the next 'currChar1' will be the character in currChar2's current index, only one more character along.
			outputLine[outputIndex] = currChar1;
			outputIndex++;
		}
	}
}
