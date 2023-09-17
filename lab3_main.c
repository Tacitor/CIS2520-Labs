#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


static void
printLineLeader(int lineNumber)
{
	printf("\n%4d >:", lineNumber);
	/**
	 * fflush() makes sure that the characters printed so far on
	 * the current line are pushed to the output device (the terminal)
	 * even though there is no newline at the end of the above output
	 * string.
	 */
	fflush(stdout);
}

/**
 * Process the given file, writing the the converted version on
 * standard output
 *
 * Input characters should be transferred directly, except for the
 * following two cases:
 * - non-escaped actual newline characters in the input should cause
 *   the "line leader" to be printed out and the line number incremented
 * - any character following the escape character '\' may have a
 *   special meaing as follows:
 *      n : generate a "new line" character (with no "line leader")
 *      t : generate a tab character
 *      ' : generate a single quote character
 *     \n : (an actual newline character) in this case,
 *          generate nothing -- that is, the input should be as though
 *          this escaped end-of-line character never existed
 *      \ : (i.e.; the escape character itself) this should
 *          generate a '\' character
 *        : any other escaped character simply has it "unescaped" meaning,
 *          for example the sequence "\Q" would simply output a "Q"
 */
static int
convertLinesInFile(char *filename)
{
	FILE *ifp;
	int c, lineNumber = 0, isInEscape = 0;

	ifp = fopen(filename, "r");
	if (ifp == NULL) {
		fprintf(stderr, "Error: cannot open '%s' : %s\n",
				filename, strerror(errno));
		return -1;
	}

	printLineLeader(++lineNumber);

	/** loop, reading one character at a time, until we get
	 * to the end of the file */
	while ((c = getc(ifp)) != EOF) {
		if (c == '\\') {
			/** flag that we just saw an escape character */
			isInEscape = 1;
		} else {

			/**
			 *  TO DO -- add your code here.
			 */
			
			putc(c, stdout);
		}
	}

	printf("\n\nDONE\n");

	fclose(ifp);
	return 0;
}

/**
 * Program mainline
 */
int
main(int argc, char **argv)
{
	int i;

	for (i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			fprintf(stderr, "Error: unknown flag '%s'\n", argv[i]);
			return -1;
		} else if (convertLinesInFile(argv[i]) < 0) {
			fprintf(stderr, "Error: conversion of '%s' failed\n", argv[i]);
			return -1;
		}
	}
	return 0;
}

