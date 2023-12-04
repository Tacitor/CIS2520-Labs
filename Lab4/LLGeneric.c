#include <stdio.h>  /* I/O routines */
#include <stdlib.h> /* for malloc() */
#include <string.h> /* for strdup() */
#include <errno.h>	/* for errno */

#include "LLGeneric.h"	/* include our macros and prototypes */


/**
 * Process this list using the user's supplied function and data,
 * returning the number of nodes processed, or a negative value
 * on error
 */
int
lstPerformIterativeAction(
		GenericListNode *list,
		int (*action)(GenericListNode *, int, void *),
		void *userdata
	)
{
	GenericListNode *curNode = NULL;
	int nodeCount, status;

	curNode = list;
	nodeCount = 0;

	while (curNode != NULL) {
		status = (*action)(curNode, nodeCount++, userdata);
		if (status < 0)	return status;
		curNode = curNode->next;
	}

	return nodeCount;
}


/**
 * Allocate memory for only the node -- the user is responsible
 * for managing whatever data is passed in themselves
 */
GenericListNode *
lstCreateNode(void * const userdata)
{
	GenericListNode *newNode = NULL;

	newNode = (GenericListNode *) malloc(sizeof(GenericListNode));
	newNode->next = NULL;
	newNode->data = userdata;
	return newNode;
}

/**
 * Chase through the list, freeing all memory it contains.
 */
void
lstDestroyList(
		GenericListNode *list,
		void (*useraction)(GenericListNode *, void *),
		void *userdata
	)
{
	GenericListNode *nextNode = NULL, *curNode = NULL;

	curNode = list;
	while (curNode != NULL) {
		nextNode = curNode->next;
		(*useraction)(curNode, userdata);
		free(curNode);
		curNode = nextNode;
	}
}


/*
 * lstAppend: add newp to end of listp
 *
 * as above, we always return the value that
 * should be the new head of the list 
 */
GenericListNode *
lstAppend(GenericListNode *listp, GenericListNode *newp)
{
	GenericListNode *p;

	if (listp == NULL)
		return newp;

	for (p = listp; p->next; p = p->next)
		;

	p->next = newp;
	return listp;
}


/*
 * lstPrepend: add newp to front of list
 *
 * by returning ourselves, we give back the
 * value that should be the new head of the list
 */
GenericListNode *
lstPrepend(GenericListNode *listp, GenericListNode *newp)
{
	newp->next = listp;
	return newp;
}


