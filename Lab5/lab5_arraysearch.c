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
 * on the common name in a simple pointer
 */
static int
structComporator_CommonName(const void *vKey, const void *vData)
{
	FruitData *fruitData = NULL;
    char *key = NULL;
    int result;

	printf(" = = structComporator_CommonName: vKey = %p, vData = %p\n", vKey, vData);


	// Get the key and data from the void pointers.  Keep in mind the
	// data is now a "pointer to pointer"

	key  = (char *) vKey;
	fruitData = (FruitData *) vData;


	// Compare the key to the "common" field in the data referenced
	// by the pointer that the *data" passed in here *contains directly*
	//
	// That is, the data in the struct pointed to *directly by the
	// data pointer*.

	printf(" = = structComporator_CommonName: key = %s\n", key);
	printf(" = = structComporator_CommonName: fruit = %s, %s\n",
            fruitData->common, fruitData->latin);

	result = strcmp(key, fruitData->common);
	printf(" = = structComparator_CommonName: comparison of (%s/%s) returns %d\n",
            key, fruitData->latin, result);
            
    return result;
}

void 
searchInCommonName(const FruitData *fruitDataArray, int nFruits, char *key)
{
	FruitData *arrayResult = NULL;
	int arrayIndex;

	printf("Common names in array of %d structs:\n", nFruits);
	printDataArray(fruitDataArray, nFruits);


	printf("Demonstration of comparator (comparing first data element):\n");
	structComporator_CommonName(key, fruitDataArray);


	printf("Entering binary search.\n");
	arrayResult = binarysearch(
			key, fruitDataArray, nFruits, sizeof(FruitData),
			structComporator_CommonName);
	if (arrayResult != NULL) {
		arrayIndex = arrayResult - fruitDataArray;
		printf("Common name search using '%s' returned:\n\t", key);
		printFuitWithID(arrayResult, arrayIndex);
	} else {
		printf("Common name search using '%s' FAILED\n", key);
	}
}

