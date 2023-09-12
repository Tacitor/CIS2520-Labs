#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h> /** for toupper() */

#include "word_extractor.h"

/** set up our default length */
#define	DEFAULT_WORD_EXTRACTOR_MAX_LENGTH	64
#define	DEFAULT_PRINT_LENGTH	4

/**
 *	Force a string to uppercase, in place
 */
void
makeUpper(char *s)
{
	/* loop until the end of the string, making each character
	 * the uppercase version of itself (if there is one) */
	while (*s != '\0') {
		*s = toupper(*s);
		s++;
	}
}

/**
 *	Force a string to lowercase, in place
 */
void
makeLower(char *s)
{
	/* loop until the end of the string, making each character
	 * the lowercase version of itself (if there is one) */
	while (*s != '\0') {
		*s = tolower(*s);
		s++;
	}
}

/**
 * Process the given file, writing the words of the indicated length
 * only to the indicated file pointer
 */
static int
processWordsInFile(
		FILE *outputFP,
		char *filename,
		int wordExtractorMaximumLength,
		int wordLengthToPrint,
		int forceUppercase,
		int forceLowercase)
{
	struct WordExtractor *wordExtractor = NULL;
	char *aWord = NULL;

	// create the extractor and open the file
	wordExtractor = weCreateExtractor(filename, wordExtractorMaximumLength);

	if (wordExtractor == NULL) {
		fprintf(stderr, "Failed creating extractor for '%s'\n", filename);
		return 0;
	}

	// read each word from the file using the WordExtractor,
	// and print it out

	while (weHasMoreWords(wordExtractor)) {
		aWord = weGetNextWord(wordExtractor);

		if (strlen(aWord) == wordLengthToPrint) {
			if (forceUppercase) {
				makeUpper(aWord);
			}
			if (forceLowercase) {
				makeLower(aWord);
			}
			printf("%s\n", aWord);
		}
	}

	// Close the file when we are done
	weDeleteExtractor(wordExtractor);

	return 1;
}

static void
printHelp()
{
	fprintf(stderr, "Prints out words of a given length to the indicated output stream.\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "Options:\n");
	fprintf(stderr, " -o <FILENAME> : Place output in filename instead of stdout\n");
	fprintf(stderr, " -W <SIZE>     : Use <SIZE> as the maximum word size instead\n");
	fprintf(stderr, "               : of the default size of %d\n",
			DEFAULT_WORD_EXTRACTOR_MAX_LENGTH);
	fprintf(stderr, " -l <SIZE>     : Use <SIZE> as the length of word to print\n");
	fprintf(stderr, "               : instead of the default size of %d\n",
			DEFAULT_PRINT_LENGTH);

	fprintf(stderr, " -U            : Force output words into UPPER CASE\n");
	fprintf(stderr, " -L            : Force output words into lower case\n");
	fprintf(stderr, " -h            : Print this help.\n");
	exit(1);
}

/**
 * Program mainline
 */
int
main(int argc, char **argv)
{
	FILE *outputFP = stdout;
	int wordExtractorMaxLength = DEFAULT_WORD_EXTRACTOR_MAX_LENGTH;
	int filesProcessed = 0;


	// Change this to be your own code.
	//
	// Take a look at processWordsInFile() to actually do the
	// work -- it is defined above.
	printf("I don't know what to do!  Please help me!\n");


	if ( filesProcessed == 0) {
		fprintf(stderr,
				"No data processed! "
				"Did you forget to tell me what file to look at?\n");
		printHelp();
	}

	return 0;
}
