/*
 * Simple binary search of an array of floats
 * presented as a generic array of void *
 * containing print statements indicating 
 * the search state as we proceed
 */
#include <stdio.h>
#include "bsearch-verbose.h"

/**
 * Print out what our state is as we traverse
 * the data array
 */
static void
printSearchState(
	int iteration, char *tag,
	int left, int right, int middle)
{
	printf(" @ step %3d %-7s : L=%d R=%d, middle=%d\n",
		iteration, tag, left, right,
		middle);
}

/**
 * The classic binary search algorithm implementation
 */
void *
binarysearch(
		const void *key, const void *vData, int n, int tilesize,
		int (*comparator)(const void *, const void *)
		)
{
		// initial values required for algorithm
	int left = 0;
	int right = n - 1;
	int c;

        // move from void * to pointer to bytes
    char *cData = (char *) vData;

	int middle;
	int loopCounter = 0;

		// print out our state at the start
	printf("   Search list len %d\n", n);
	printSearchState(-1, "START", left, right, -1);

	/** loop until search range collapses */
	while (left <= right) {

		/** calculate half way, round down */
		middle = (int) ( (left + right) / 2);

		printSearchState(++loopCounter, "IN LOOP",
			left, right, middle);

		printf(" . . bsearch Debug: Calling into comparator\n");
		c = (*comparator)(key, &cData[middle*tilesize]);
		printf(" . . bsearch Debug: Comparator returned value %d\n", c);
		if (c > 0) { /** too low */
			left = middle + 1;

		} else if (c < 0) { /** too high */
			right = middle - 1;

		} else {
			printSearchState(loopCounter, "FOUND",
					left, right, middle);
			return &cData[middle*tilesize];
		}
	}

	printSearchState(loopCounter, "FAILED",
			left, right, middle);
	return NULL;
}

