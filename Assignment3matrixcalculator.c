/* 	C Programming – ACS126-006
	Assignment 3 - Assignment3.c - A program to allow the user to input two square matrices (with dimensions from 1 to 10), and adds and multiplies them together if possible.
	By: Rory Charlesworth */

#include <stdio.h>

struct matrix
	{
	 float mValues[10][10]; // to hold the values in the matrix, for up to 10 rows x 10 columns
	 int nrows; // to hold the number of rows in mValues
	 int ncols; // to hold the number of columns in mValues
	};

//Declare function prototypes:
void matrixInput(struct matrix *mat);
void matrixDisplay(struct matrix mat);
int matrixAdd(struct matrix A, struct matrix B, struct matrix *C);
int matrixMultiply(struct matrix A, struct matrix B, struct matrix *C);

int main()
{
	struct matrix A, B, C; //Declare all three matrices to work with.
	
	printf("For matrix A:\n");
	matrixInput(&A);	//Run matrixInput for A, allowinguser to input number of rows, columns and array contents.
	
	printf("For matrix B:\n");
	matrixInput(&B);	//Run matrixInput for B, allowinguser to input number of rows, columns and array contents.
	
	
	printf("\nContents of matrix A (2d.p.):\n");
	matrixDisplay(A);	//Display matrix A.
	
	printf("\nContents of matrix B (2d.p.):\n");
	matrixDisplay(B);	//Display matrix B.
	
	if(matrixAdd(A, B, &C)==0){		//Check that matrices are add-able, and if so display the result of A+B as matrix C.
		printf("\n\nMatrix A + Matrix B = \n");
		matrixDisplay(C);
	}else{
		printf("\nSize of matrix A does not equal that of matrix B. Cannot Sum.\n");	//Show error message if A and B are not add-able.
	}
	
	if(matrixMultiply(A, B, &C)==0){	//Check that matrices are multiply-able, and if so display the result of A*B as matrix C.
		printf("\n\nMatrix A * Matrix B = \n");
		matrixDisplay(C);
	}else{
		printf("\nColumns of matrix A do not equal rows of matrix B. Cannot multiply.\n");	//Show error message if A and B are not multiply-able.
	}
	
	system("pause");	//Pause to allow user to view output.
}

void matrixInput(struct matrix *mat)
{
	int rowcount, colcount;	//Declare counter variables.
	
	while(1)
	{
		printf("Please input the number of rows for a square matrix that is between 1 and 10 (inclusive).\n");
		scanf("%d", &(*(mat)).nrows);	//Write input number of rows to nrows in given matrix.
		printf("Please input the number of columns for a square matrix that is between 1 and 10 (inclusive).\n");
		scanf("%d", &(*(mat)).ncols);	//Write input number of columns to ncols in given matrix.
		if((*mat).nrows == (*mat).ncols){	//Check if matrix is square.
			if((*mat).nrows <= 10 && (*mat).nrows >= 1 && (*mat).ncols <= 10 && (*mat).ncols >= 1){	//Check if no. of matrix rows and no. of matrix columns are between 1 and 10 (inclusive).
				break;	//If all conditions satisfied, break from loop.
			}else{
				printf("One of your values was not in-range. Please re-enter.\n");
			}
		}else{
			printf("No. of rows entered does not match no. of columns. Please re-enter.\n");
		}	//Give error message if one or the other (or both) conditions are not satisfied, and run through the loop again to allow the user to re-enter the information.
	}
	
	printf("--------\nMatrix has %d row(s) and %d column(s).\n--------\n", (*mat).nrows, (*mat).ncols);		//Verify the user's input by re-outputting it to the screen.
	
	for(rowcount = 0; rowcount < (*mat).nrows; rowcount++)	//Loop through rows and columns of matrix.
	{
		printf("Please enter the contents of row %d, one number at a time, pressing enter between each.\n", rowcount+1);
		for(colcount = 0; colcount < (*mat).ncols; colcount++)
		{
			scanf("%f", &(*(mat)).mValues[rowcount][colcount]);	//Allow the user to input the current element of the matrix.
		}
	}
}

void matrixDisplay(struct matrix mat)
{
	int rowcount, colcount;	//Declare counter variables.
	
	printf("\n[----------]\n");
	for(rowcount = 0; rowcount < mat.nrows; rowcount++)	//Loop through rows and columns of matrix.
	{
		for(colcount = 0; colcount < mat.ncols; colcount++)
		{
			printf("%.2f ", mat.mValues[rowcount][colcount]);	//Print the current element of the given matrix at index [rowcount][colcount].
		}
		printf("\n");	//Move on to next line after printing entire row.
	}
	printf("[----------]\n");
}

int matrixAdd(struct matrix A, struct matrix B, struct matrix *C)
{
	int rowcount, colcount;	//Declare counter variables.
	
	if(A.nrows == B.nrows && A.ncols == B.ncols)	//Check that matrices are the same size before addition.
	{
		(*C).nrows = A.nrows;	//Set size of resultant matrix C equal to rows and columns of A.
		(*C).ncols = A.ncols;
		for(rowcount = 0; rowcount < A.nrows; rowcount++)	//Loop through rows and columns of matrix C.
		{
			for(colcount = 0; colcount < A.ncols; colcount++)
			{
				(*C).mValues[rowcount][colcount] = A.mValues[rowcount][colcount] + B.mValues[rowcount][colcount];	//Set current element of resultant matrix C to A+B.
			}
		}
		return 0;	//Return error value of 0 for success.
	}else{
		return 1;	//Return error value of 1 if size of A != size of B.
	}
}

int matrixMultiply(struct matrix A, struct matrix B, struct matrix *C)
{
	int rowcount, colcount, conscount;	//Declare counter variables.
	float currentvalue;	//The current part-calculation of one element of C (to be added together).
	
	if(A.ncols == B.nrows)	//Check that matrices are multiply-able by assuring no. of columns of A = no. of columns of B.
	{
		(*C).nrows = A.nrows;	//Set size of resultant matrix C equal to rows of A and columns of B.
		(*C).ncols = B.ncols;
		for(rowcount = 0; rowcount < (*C).nrows; rowcount++)	//Loop through rows and columns of matrix C.
		{
			for(colcount = 0; colcount < (*C).ncols; colcount++)
			{
				currentvalue = 0;
				for(conscount = 0; conscount < A.ncols; conscount++)	//Count through each term of the current element of C to be added together (eg. A11*B11 + A12*B21 + A13*B31).
				{
					currentvalue += A.mValues[rowcount][conscount] * B.mValues[conscount][colcount];
				}
				(*C).mValues[rowcount][colcount] = currentvalue; //Make the current value of the resultant matrix C equal to the sum of the looped terms.
			}
		}
		return 0;	//Return error value of 0 for success.
	}else{
		return 1;	//Return error value of 1 if columns of A != no. of columns of B.
	}
}
