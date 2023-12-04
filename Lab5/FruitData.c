/*
 * Simple binary search of an array of floats
 * presented as a generic array of void *
 * containing print statements indicating
 * the search state as we proceed
 */
#include <stdio.h>

#include "FruitData.h"


/* Print a single Fruit element */
void
printFuitWithID(const FruitData *element, int id)
{
	printf("   %2d : '%s' is '%s'\n", id, element->common, element->latin);
}

/* Print out an array of Fruit pointers */
void
printDataPointerArray(FruitData * const *dataPtrArray, int datalength)
{
	int i;

	printf("Data contains %d elements:\n", datalength);
	for (i = 0; i < datalength; i++) {
		printFuitWithID(dataPtrArray[i], i);
	}
}

/* Print out an array of Fruit elements */
void
printDataArray(const FruitData *dataArray, int datalength)
{
	int i;

	printf("Data contains %d elements:\n", datalength);
	for (i = 0; i < datalength; i++) {
		printFuitWithID(&dataArray[i], i);
	}
}

