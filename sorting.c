#include "sorting.h"

// Funciton to lead data from a file

int power(int base, int power)
{
	if(power == 0)
	{
		return 1;
	}
	int counter = 0;
	int number = base;
	for(counter = 0; counter < power - 1; counter++)
	{
		number *= base;
	}
	return number;
}

long *Load_From_File(char *Filename, int *Size)
{
	FILE *readptr;
	long *elements = NULL;
	// reading the file
	
	readptr = fopen(Filename, "rb");
	if(readptr == NULL)
	{
		fprintf(stderr, "The file could not be opened\n");
		return NULL;
	}

	// Determing the size of the file
	
	fseek(readptr, 0, SEEK_END);
	*Size = ftell(readptr) / sizeof(long);
	fseek(readptr, 0, SEEK_SET);
	
	// Allocating memory for the numbers
	
	elements = malloc(*Size * sizeof(elements));
	if(elements == NULL)
	{
		fprintf(stderr,"Malloc fail");
		return NULL;
	}

	//Reading the elements
	
	fread(elements,sizeof(elements),*Size,readptr);
	
	fclose(readptr);
	return elements;
}

// Function to write the sorted array into a file

int Save_To_File(char *Filename, long *Array, int Size)
{
	// Variable declaration
	
	FILE *writeptr;
	int returnValue = 0;   // Stores the return value	
	// Reading the file 
	
	writeptr = fopen(Filename, "wb");
	
	if(writeptr == NULL)
	{
		fprintf(stderr, "The file could not be opened");	
		return 0;
	}

	//Wrtie to the output file
	
	returnValue = fwrite(Array,sizeof(Array),Size,writeptr);
	
	// Releasing the heap memory
	
	free(Array);
	return returnValue;
}

// Helper fucntion to generate the sequence

int *SeqCreate(int *size)
{
	int p = 0;				// Power of 2 in the sequence 
	int q = 0;				// Power of 3 in the sequence 
	int endPower = 0;		// Power of the last row the number is in
	int numberofelements;   // Number of elements to be allocated
	int lastnumber = 0;
	
	// Calculating the last rows maxuimum power
	
	while (power(3,endPower) < *size)
	{
		endPower++;
	}
	numberofelements = endPower * (endPower + 1) / 2;
	p = endPower;
	
	// Calculating the last element
	
	while ((power(2,p) * power(3,q)) < *size)
	{
		lastnumber = (int)(power(2,p) * power(3,q));
		if(p > 0)
		{
			p--; 			// P cannot fall below 0
		}
		q++;
		numberofelements++;
	}

	//Allocating space for the array sequence
	
	int *prattSeq = malloc(numberofelements * sizeof(* prattSeq));
	if(prattSeq == NULL)
	{
		fprintf(stderr, "Malloc fail");
		return NULL;
	}
	// Calculating the sequence
	
	int highestPower = 0;
	int i;					  // Element number in the sequence
	p = 0;
	for(i = 0; i < numberofelements; i++)
	{
		if(p == -1)
		{
			highestPower++;
			p = highestPower;
		}
		prattSeq[i] = (int)(power(2,p) * power(3,highestPower - p));
		p--;
	}
	*size = numberofelements;
	return prattSeq;
}

int Print_Seq(char *Filename, int Size)
{
	// Generating the sequence
	
	int orginalSize = Size;
	int *prattVect = SeqCreate(&Size);

	// Copy the sequence into a file
	
	FILE *wfile;
	wfile = fopen(Filename, "wb");
	int i;
	
	for(i = 0; i < Size; i++)
	{
		fprintf(wfile, "%i\n", prattVect[i]);
	}
	
	//Releasing heap memory
	
	free(prattVect);
	fclose(wfile);
	return i;
}

void Shell_Insertion_Sort(long *Array, int Size, double *N_Comp, double *N_Move)
{
	// Generating the gap sequence and the size of the gap sequence
	
	int originalSize = Size;
	int *kArray = SeqCreate(&Size);  // Array that stores the length of the subarrays
	
	// Variable declaration
	
	int loopCounter = 0;
	int subArrayLength = 0;
	int temp = 0;
	int check = 0;
	int shellCounter = 0;
	// Shell Insertion Sort
	
	for(loopCounter = Size - 1; loopCounter >= 0; loopCounter--)
	{
		subArrayLength = kArray[loopCounter];

		for(shellCounter = subArrayLength; shellCounter < originalSize; shellCounter++)
		{
			temp = Array[shellCounter];
			*N_Move += 1;
			check = shellCounter;
			
			while((check >= subArrayLength) && (Array[check-subArrayLength] > temp))
			{
				Array[check] = Array[check - subArrayLength];
				check -= subArrayLength;
				*N_Comp += 2;
				*N_Move += 1;
			}
			
			Array[check] = temp;
			*N_Move += 1;
		}
	}
	free(kArray);
}

void Shell_Selection_Sort(long *Array, int Size, double *N_Comp, double *N_Move)
{
	// Generating Gap Sequence and the size of the gap Sequence
	
	int originalSize = Size;
	int *kArray = SeqCreate(&Size);

	// Local Variable Declaration
	
	int loopCounter = 0;
	int subArrayLength = 0;
	int temp = 0;
	int check = 0;
	int shellCounter = 0;
	int compare = 0;

	// Shell Selection Sort
	
	for (loopCounter = Size - 1; loopCounter >= 0; loopCounter--)
 	{
		subArrayLength = kArray[loopCounter];
		for(check = subArrayLength - 1; check < originalSize; check++)
		{
			for(shellCounter = check, compare = check; shellCounter < originalSize; shellCounter++)
			{
				*N_Comp += 1;
				if(Array[shellCounter] < Array[compare])
				{
					compare = shellCounter;
				}
			}
			temp = Array[check];
			Array[check] = Array[compare];
			Array[compare] = temp;
			*N_Move += 3;		
		}
	}
	free(kArray);
}

