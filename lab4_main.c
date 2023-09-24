/**
 *  This file provides the example that we went through in class.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "LLGeneric.h"

/** define the maximum length of a line that we can read */
#define	LINE_BUFFER_SIZE	1024

/**
 * We can use this as our "user data" to help us calculate the maximum
 * length string
 *
 * Add anything else to this structure that you wish
 */
struct maxData {
	size_t maxLenSoFar;
	char *maxStringSoFar;
};

/**
 * our "user function" or "callback" for printing.
 *
 * We know what "void *userdata" is going to be because it is
 * simply what we pass in at the call below, so it is safe to
 * cast back to a FILE * as that is what we passed it.
 *
 * This is called a "callback" as it "call back into" our own
 * code from within a generic routine.
 */
int myFindLongestStringNode(GenericListNode *node, int index, void *userdata)
{
	/**
	 * Add more code here.  You will need to:
	 * - convert the GenericListNode payload in the field "data" to your
	 *   known (char *) type
	 * - conver the (void *) userdata into your known (struct maxData *)
	 *   type
	 * - use the fact that you can examine and store the values provided
	 *   through the userdata to see what has been calculated by earlier
	 *   calls to this function and update based on what you see here,
	 *   in order to determine what the longest string is in the whole
	 *   set of nodes.
	 */

	return 1;
}

int
doListActivities(GenericListNode *list)
{
	/** create an instance of our structure for use as the user data */
	struct maxData maxDataWorkingStruct;
	int nProcessed = 0;

	/** initialize our structure -- if you added fields, set them up here */
	maxDataWorkingStruct.maxLenSoFar = 0;
	maxDataWorkingStruct.maxStringSoFar = NULL;

	/**
	 * TO DO: Iterate using the callback, which should calculate what
	 * the longest string in the list is
	 */
	nProcessed = lstPerformIterativeAction(
			list, /* pointer to the first list node */
			myFindLongestStringNode, /* pointer to our function */
			(void *) &maxDataWorkingStruct);

	/** print out the result */
	printf("The longest string has %ld characters\n",
			maxDataWorkingStruct.maxLenSoFar);
	printf("The longest string is: %s\n",
			maxDataWorkingStruct.maxStringSoFar);

	return nProcessed;
}



/**
 **		Tools provided below here you won't need to edit -- they
 **		simply process the command line, and load and free the
 **		generic linked list and the strings we put into it
 **/

/** Some prototypes for the load/cleanup functions.  Normally
 ** we would put all the code below into its own file.
 **
 ** These are declared static simply because they are only
 ** declared and used within this file.
 **/
static GenericListNode *loadListWithLinesFromFile(const char *filename);
static void cleanupList(GenericListNode *list);

/**
 * Program mainline
 */
int
main(int argc, char **argv)
{
	GenericListNode *list = NULL;
	int i;

	for (i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			fprintf(stderr, "Error: unknown flag '%s'\n", argv[i]);
			return -1;
		} else {
			list = loadListWithLinesFromFile(argv[i]);

			if (list == NULL) {
				fprintf(stderr, "Error: loading '%s' failed\n", argv[i]);
				return -1;
			}

			// do all the work with this list (code is above)
			doListActivities(list);

			// get rid of the list memory (code is below)
			cleanupList(list);
		}
	}

	return 0;
}



/**
 * Tools below simply load and clean up the data from main
 */

/**
 * Process the given file, reading in lines and adding them
 * to the generic linked list as strings.
 *
 * ** This is where we are defining what the type is of our
 * ** "generic" (void *) data by supplying it with a string
 * ** that we have allocated using strdup() (internally, malloc())
 */
static GenericListNode *
loadListWithLinesFromFile(const char *filename)
{
	char linebuffer[LINE_BUFFER_SIZE];
	FILE *ifp = NULL;
	GenericListNode *headOfGenericLinkedList = NULL;
	GenericListNode *newNode = NULL;

	ifp = fopen(filename, "r");
	if (ifp == NULL) {
		fprintf(stderr, "Error: Cannot open input file '%s' : %s\n",
				filename, strerror(errno));
		return NULL;
	}

	/** process each line from the file */
	while (fgets(linebuffer, LINE_BUFFER_SIZE, ifp) != NULL) {

		/* create a node, giving an allocated copy of the input line */
		newNode = lstCreateNode(strdup(linebuffer));

		/* append this new node to the list it do the list */
		headOfGenericLinkedList = lstAppend(
				headOfGenericLinkedList, newNode);
	}


	fclose(ifp);
	return headOfGenericLinkedList;
}

static void
deleteStringInGenericNode(GenericListNode *node, void *userdata)
{
	/** we don't even need to cast this -- just free it */
	free(node->data);

	// cast here is just to suppress the compiler warning about
	// userdata not being used within this function.
	(void) userdata;
}

static void
cleanupList(GenericListNode *list)
{
	// use our callback just above to delete the strings while
	// cleaning up the list
	lstDestroyList(list, deleteStringInGenericNode, NULL);
}
