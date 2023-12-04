/*
 * Simple binary search of an array of floats
 * presented as a generic array of void *
 * containing print statements indicating
 * the search state as we proceed
 */
#include <stdio.h>
#include <string.h> // for strcmp()

#include "bsearch-verbose.h"
#include "FruitData.h"


/**
 * Comparator function for generic search based
 * on the latin name in a pointer to pointer
 */
static int
pointerComparator_LatinName(const void *vKey, const void *vData)
{
	FruitData **fruitData = NULL;
    char *key = NULL;
    int result;

	printf(" = = pointerComporator_LatinName: vKey = %p, vData = %p\n", vKey, vData);


	// Get the key and data from the void pointers.  Keep in mind the
	// data is now a "pointer to pointer"
	key  = (char *) vKey;
	fruitData = (FruitData **) vData;


	// Compare the key to the "latin" field in the data referenced
	// by the pointer that the *data" passed in here *points at*.
	//
	// That is, the data in the struct pointed to by the pointer
	// *the data pointer is pointing at*.
	//
	// It probably will help if you first print out the key and
	// the data fields first, so you know that you have the dereferencing
	// correct.
	printf(" = = structComporator_CommonName: key = %s\n", key);
	printf(" = = structComporator_CommonName: fruit = %s, %s\n",
            (*fruitData)->common, (*fruitData)->latin);

	//
	// Hint: it may be clearer to you if you dereference the pointer
	// iyou get (i.e.; with a '*') and store that value before trying
	// to deference it to get at a field.
	//
	// Feel free to add as many variables as you like to track the
	// pstages of the dereferencing.
	//
	// If you are having trouble, consider the memory addresses values
	// you see in the vKey and vData above.
	result = strcmp(key, (*fruitData)->latin);
	printf(" = = structComparator_CommonName: comparison of (%s/%s) returns %d\n",
            key, (*fruitData)->common, result);


    return result;
}

void 
searchInLatinName(FruitData * const *fruitDataPointers, int nFruits, char *key)
{
	FruitData **pointerResult = NULL;
	int arrayIndex;

	printf("Latin names in array of %d pointers to structs:\n", nFruits);
	printDataPointerArray(fruitDataPointers, nFruits);


	printf("Demonstration of comparator (comparing key to first data element):\n");
	pointerComparator_LatinName(key, fruitDataPointers);


	printf("Entering binary search.\n");

	// Call the binary search with the array of pointers to pointers
	// to the data, the appropriate size, and the comparator above
	pointerResult = binarysearch(
			key, fruitDataPointers, nFruits, sizeof(FruitData *),
			pointerComparator_LatinName);

	if (pointerResult != NULL) {
		arrayIndex = pointerResult - fruitDataPointers;
		printf("Latin name search using '%s' returned:\n\t", key);
		printFuitWithID(*pointerResult, arrayIndex);
	} else {
		printf("Latin name search using '%s' FAILED\n", key);
	}
}

