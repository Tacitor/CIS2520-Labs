
# CIS*2520 F23 Week 4 Lab

Given a *generic* linked list implementation, where the *payload*
data is accessed using a `(void *)` we want to write our own
callback to calculate something based on our definition of what
the payload is.

We will use the **iterator** provided in the **library code** in
`LLGeneric.c`.

## Lab Objective:

In this case, the *payload* is simply a `(char *)` to an allocated
string.  We can therefore do any of the regular string operations
once we cast the `data` field (which is a `void *`) to a `(char *)`
variable of our own.

In class, we looked at an example that did this for purposes of
printing.  Here we will extend this idea to calculate the longest
string.

### Printing using the callback

Remember what we saw in class (which is reproduced in `example_main.c`):

* **defining** a callback: it **must** have the *signature* that
	the *library code* *has defined it will take*:

	```c
	int myPrintNode(GenericListNode *node, int index, void *userdata)
	{
		FILE *ourFP = NULL; // we will put **OUR** userdata here
		char *ourNodeData = NULL; // we will put **OUR** payload here

		ourFP = (FILE *) userdata;
		ourNodeData = (char *) node->data;
		
		return fputs(ourNodeData, ourFP);
	}
	```

	* we know we will get called for each node in the list
	* we know that whatever ***WE*** passed as the "*user data*" when
		calling the iterator will appear here as the `userdata` value,
		so we can cast it back to whatever type it really was when
		we made the call to the iterator
	* we know what data ***WE*** put into the `node->data` field
		--- that is, the
		address of a string that we allocated



* **using** a callback:  making the call into the iterator
	(`lstPerformIterativeAction()`) passing in our callback function
	and our **user data**:

	```c
	int
	doListActivities(GenericListNode *list)
	{
		int nProcessed;

		nProcessed = lstPerformIterativeAction(
				list, /* pointer to the first list node */
				myPrintNode, /* pointer to **OUR** function */
				(void *) stdout); /* pointer to **OUR** user supplied data */

		printf("We processed %d nodes!\n", nProcessed);

		return nProcessed;
	}
	```

* (The code below this function in `example_main.c` loads and cleans up
	the generic list -- you won't need to edit it for this lab, but if
	you want to see yet another example of a callback, look at the very
	end of the file where we use a callback to delete the strings that
	we allocated and hung in `node->data`)

### Designing a new callback

To calculate the maximum string length we need to write a new
callback function that will use a different **user data** structure.

The callback can **do** whatever we want, but it must have the
**same signature** as in the example.

The data passed to our callback is:

* a `node` containing the `node->data` pointer that will hold our string
* a `userdata` argument -- of type `(void *)` -- that will hold ***whatever
	we want***.  We have total control of what is at that pointer location,
	because it will be whatever value we passed.  We can therefore:

		* make a structure holding whatever important values we need
		* pass the address of that structure into the function

The key to this lab is to think about what fields you want to have in
that structure, and how to use those fields to update your idea of what
the maximum string seen so far is as the iterator takes you through each
node.

You want to **update your answer so far** within the user data that you
have passed yourself in the callback.



# Lab Activities

Clone the `Lab4` project from `gitlab` as per usual.

Examine `example_main.c` and `lab4_main.c`.  The *example* file has the
printing example we saw in class.  The *lab4* file needs you to fill
in the missing code (look for "TO DO") to complete this lab.

# Lab code submission

As with our previous work, we are simply going to `commit` and `push`
our code into `gitlab`.

## Validate your submission

Be sure to verify that your lab was submitted properly,
as was described last time.

