#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h> /** for toupper() */

#include "word_extractor.h"

/** set up our default length */
#define DEFAULT_WORD_EXTRACTOR_MAX_LENGTH 64
#define DEFAULT_PRINT_LENGTH 4

/**
 *	Force a string to uppercase, in place
 */
void makeUpper(char *s)
{
	/* loop until the end of the string, making each character
	 * the uppercase version of itself (if there is one) */
	while (*s != '\0')
	{
		*s = toupper(*s);
		s++;
	}
}

/**
 *	Force a string to lowercase, in place
 */
void makeLower(char *s)
{
	/* loop until the end of the string, making each character
	 * the lowercase version of itself (if there is one) */
	while (*s != '\0')
	{
		*s = tolower(*s);
		s++;
	}
}

/**
 * Process the given file, writing the words of the indicated length
 * only to the indicated file pointer
 */
static int processWordsInFile(
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

	if (wordExtractor == NULL)
	{
		fprintf(stderr, "Failed creating extractor for '%s'\n", filename);
		return 0;
	}

	// read each word from the file using the WordExtractor,
	// and print it out

	while (weHasMoreWords(wordExtractor))
	{
		aWord = weGetNextWord(wordExtractor);

		if (strlen(aWord) == wordLengthToPrint)
		{
			if (forceUppercase)
			{
				makeUpper(aWord);
			}
			if (forceLowercase)
			{
				makeLower(aWord);
			}
			printf("%s\n", aWord);
		}
	}

	// Close the file when we are done
	weDeleteExtractor(wordExtractor);

	return 1;
}

static void printHelp()
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
int main(int argc, char **argv)
{
	FILE *outputFP = stdout;
	int wordExtractorMaxLength = DEFAULT_WORD_EXTRACTOR_MAX_LENGTH;
	int filesProcessed = 0;

	// Self declared variables
	int forceUppercase = 0;
	int forceLowercase = 0;
	int wordLengthToPrint = DEFAULT_PRINT_LENGTH;

	// loop thorugh the arguments
	// NOTE: Much of this code was copied and adapted from my submission for A1
	for (int i = 1; i < argc; i++)
	{
		// check to see if the arg starts with a "-"
		if (argv[i][0] == '-')
		{
			// check for the next char of the flag
			if (argv[i][1] == 'h')
			{
				// Help
				printHelp();

				// don't run the rest of the program
				exit(1);
			}
			else if (argv[i][1] == 'L')
			{
				// Lower case
				forceLowercase = 1;
			}
			else if (argv[i][1] == 'U')
			{
				// Upper case
				forceUppercase = 1;
			}
			else if (argv[i][1] == 'l')
			{
				// length of word to print
				// error check the next arg
				for (int j = 0; argv[i + 1][j] != '\0'; j++)
				{
					// test for number
					if (!isdigit(argv[i + 1][j]))
					{
						printf("Bad argument for -l\n");
						return -1; // exit(-1)
					}
				}
				wordLengthToPrint = atoi(argv[i + 1]);
				// increment to the next arg so it doesn't get processed as a file
				i++;
			}
			else if (argv[i][1] == 'W')
			{
				// maximum word size
				// error check the next arg
				for (int j = 0; argv[i + 1][j] != '\0'; j++)
				{
					// test for number
					if (!isdigit(argv[i + 1][j]))
					{
						printf("Bad argument for -W\n");
						return -1; // exit(-1)
					}
				}
				wordExtractorMaxLength = atoi(argv[i + 1]);
				// increment to the next arg so it doesn't get processed as a file
				i++;
			}
		}
		else
		{
			// file to process

			// Take a look at processWordsInFile() to actually do the
			// work -- it is defined above.
			processWordsInFile(NULL,
							   argv[i],
							   wordExtractorMaxLength,
							   wordLengthToPrint,
							   forceUppercase,
							   forceLowercase);

			// count the file
			filesProcessed++;
		}
	}

	// debug the acceptance of command line args
	// printf("wordExtractorMaxLength: %d\n", wordExtractorMaxLength);
	// printf("filesProcessed: %d\n", filesProcessed);
	// printf("forceUppercase: %d\n", forceUppercase);
	// printf("forceLowercase: %d\n", forceLowercase);
	// printf("wordLengthToPrint: %d\n", wordLengthToPrint);

	if (filesProcessed == 0)
	{
		fprintf(stderr,
				"No data processed! "
				"Did you forget to tell me what file to look at?\n");
		printHelp();
	}

	return 0;
}
