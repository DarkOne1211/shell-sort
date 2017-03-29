#include "sorting.h"

int main(int argc, char **argv)
{
	if(argc != 5)
	{
		fprintf(stdout, "Insufficient input(s).\n");
		return EXIT_FAILURE;
	}

	// Variable declaration
	int Size = 0;
	long *Array = NULL;
	double N_Comp = 0;
	double N_Move = 0;
	int numberStored = 0;
	int sequenceLength = 0;
	clock_t IOStart, IOStop, SortStart, SortStop;

	// Starting IO timer 
	
	IOStart = clock();

	// Reading from the given file
	
	Array = Load_From_File(argv[2], &Size);
	if(Array == NULL)
	{
		fprintf(stdout, "The file could not be read correctly due to corrupt data or invalid filename.");
		return EXIT_FAILURE;
	}
	
	//Performing the sorting
	
	SortStart = clock();

	if(argv[1][0] == 's')
	{
		Shell_Selection_Sort(Array, Size, &N_Comp, &N_Move);
	}
	else if(argv[1][0] == 'i')
	{
		Shell_Insertion_Sort(Array, Size, &N_Comp, &N_Move);
	}
	else
	{
		fprintf(stdout, "Invalid input for sorting type");
		return EXIT_FAILURE;
	}

	SortStop = clock();

	// Writing the array into the given file
	
	numberStored = Save_To_File(argv[4], Array, Size);

	// Storing the array
	
	sequenceLength = Print_Seq(argv[3], Size);

	// Stoping IO time 
	
	IOStop = clock();

	// Screen dump output
	
	printf("Number of long integers read: %d\n", Size);
	printf("Number of long integers stored: %d\n", numberStored);
	printf("Length of Sequence: %d\n", sequenceLength);
	printf("Number of comparisons: %le\n", N_Comp);
	printf("Number of moves: %le\n", N_Move);
	printf("I/O time: %le\n", (float)((IOStop - IOStart) - (SortStop - SortStart))/CLOCKS_PER_SEC);
	printf("Sorting time: %le\n", (float)(SortStop - SortStart)/CLOCKS_PER_SEC);
	return EXIT_SUCCESS;
}
