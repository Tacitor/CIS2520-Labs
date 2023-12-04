/**
 * Header file for definitions of macros and function protypes.
 */

#ifndef __GENERIC_LINKED_LIST_HEADER__
#define __GENERIC_LINKED_LIST_HEADER__

/**
 ** TYPE DEFINITIONS
 **/

typedef struct GenericListNode {
	struct GenericListNode *next;
	void *data;
} GenericListNode;

/**
 ** FUNCTION PROTOTYPES
 **/

/* create and initialize node data */
GenericListNode *lstCreateNode(void *value);

void lstDestroyList(
		struct GenericListNode *list,
		void (*useraction)(GenericListNode *, void *),
		void *userData
	);

int lstPerformIterativeAction(
		GenericListNode *list,
		int (*action)(GenericListNode *, int, void *),
		void *userdata
	);

/* lstPrepend: add newp to front of list */
GenericListNode *lstPrepend(GenericListNode *listp, GenericListNode *newp);

/* lstAppend: add newp to end of listp */
GenericListNode *lstAppend(GenericListNode *listp, GenericListNode *newp);


#endif /* __GENERIC_LINKED_LIST_HEADER__ */
