/*
 * Simple binary search of an array of floats
 * presented as a generic array of void *
 * containing print statements indicating
 * the search state as we proceed
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "bsearch-verbose.h"
#include "FruitData.h"


#define	NUMBER_OF_FRUITS	8
#define	LATIN_KEY	"Ficus"
#define	COMMON_KEY	"fig"

#define	ACTION_COMMON	1
#define	ACTION_LATIN	2
#define	ACTION_BOTH		(ACTION_COMMON|ACTION_LATIN)


void
usage(char *programname, const FruitData *dataArray, int datalength)
{
	fprintf(stderr, "Demonstrate binary search on a fixed data set.  Can be\n");
	fprintf(stderr, "searched using one of two fields.\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "Usage:\n");
	fprintf(stderr, "%s [ <options> ] [ <key> ]\n", programname);
	fprintf(stderr, "\n");
	fprintf(stderr, "Options:\n");
	fprintf(stderr, "-C  : search on the common name key only\n");
	fprintf(stderr, "-L  : search on the latin name key only\n");
	fprintf(stderr, "-B  : search on the both keys (default)\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "If supplied, the key replaces the default key '%s'/'%s'\n",
			COMMON_KEY, LATIN_KEY);
	fprintf(stderr, "\n");
	fprintf(stderr, "Below is the data set in common key order.\n");
	fprintf(stderr, "\n");

	printDataArray(dataArray, datalength);

	exit(1);
}

/**
 * main function
 */
int
main(int argc, char **argv)
{
	FruitData dataArray[] = {
		{	"apple", "Malus", 3 },
		{	"banana", "Musa", 4 },
		{	"cherry", "Prunus avium", 5 },
		{	"durian", "Durio", 1 },
		{	"elderberry", "Sambucus", 6 },
		{	"fig", "Ficus", 2 },
		{	"grape", "Vitus", 7 },
		{	"honeydew", "Cucumis melo", 0 },
		{	NULL, NULL, -1 } };

	FruitData *dataPointers[NUMBER_OF_FRUITS] = { NULL };	// initialize all to NULL

	char *latinKey = LATIN_KEY;
	char *commonKey = COMMON_KEY;

	int action = ACTION_BOTH;
	int i;

	// check that our arrays match in size
	assert(dataArray[NUMBER_OF_FRUITS].common == NULL);

	// stitch the pointers together based on index numbers we hardcoded above
	for (i = 0; i < NUMBER_OF_FRUITS; i++) {
		dataPointers[ dataArray[i].latinIndex ] = &dataArray[i];
	}

	// process command line
	for (i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			if (argv[i][1] == 'L')	action = ACTION_LATIN;
			else if (argv[i][1] == 'C')	action = ACTION_COMMON;
			else if (argv[i][1] == 'B')	action = ACTION_BOTH;
			else {
				usage(argv[0], dataArray, NUMBER_OF_FRUITS);
			}
				
		} else {
			latinKey = commonKey = argv[i];
		}
	}


	printf("Size of array of %d structures: %ld\n",
			NUMBER_OF_FRUITS, NUMBER_OF_FRUITS * sizeof(FruitData));
	printf("Size of array of %d pointers to structures: %ld\n",
			NUMBER_OF_FRUITS, NUMBER_OF_FRUITS * sizeof(FruitData *));
	printf("\n\n");


	// do the searches
	if (action & ACTION_COMMON)
		searchInCommonName(dataArray, NUMBER_OF_FRUITS, commonKey);

	if (action & ACTION_LATIN)
		searchInLatinName(dataPointers, NUMBER_OF_FRUITS, latinKey);

	return 0;
}
