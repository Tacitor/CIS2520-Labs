#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> /* for getopt() */
#include <time.h>
#include <errno.h>

#include "employee.h"


/**
 * TODO:
 * qsort comparator for two records based on the surname field
 * in ascending order
 */
int recordCompare(const void *a, const void *b)
{
}

/**
 * TODO:
 * qsort comparator for two record pointers based on the given name
 * field in descending order
 *
 * HINT: you will need to take into account that the void * arguments
 * are passing you a pointer TO a pointer
 */



/**
 * a simple function to time the sorting of the records
 * when sorted using the system qsort(1) implementation
 */
double
timeSortingOfRecords(EMPLOYEErecord *records, int nRecords)
{
	clock_t startTime, endTime;
	double recordSortTimeInSeconds = 0;

	// TODO: set up a timer using the clock(3) function wrapped
	// around a call to qsort(3) to sort the array of records
	// in ascending order by surname.
	// HINT: you will use the comparator you wrote above

	return recordSortTimeInSeconds;
}

/**
 * a simple function to time the sorting of the record pointers
 * when sorted using the system qsort(1) implementation
 */
double
timeSortingOfPointers(EMPLOYEErecord **recordPointers, int nRecords)
{
	clock_t startTime, endTime;
	double pointerSortTimeInSeconds = 0;

	// TODO: set up a timer using the clock(3) function wrapped
	// around a call to qsort(3) to sort the array of records
	// in ascending order by surname.
	// HINT: you will use the comparator you wrote above
	// ANOTHER HINT: be sure you have the right tile size

	return pointerSortTimeInSeconds;
}

/**
 * Allocate and load up the arrays, and call for the above sorting
 * to happen
 */
int
loadAndRunSortingRepeats(
		char *filename,
		int nRepeatsRequested,
		int nRecordsToLoad,
		int nRecordsToPrint
	)
{
	double recordSortTimeInSeconds, pointerSortTimeInSeconds;
	double totalRecordSortTimeInSeconds = 0,
			totalPointerSortTimeInSeconds = 0;
	EMPLOYEErecord *records = NULL, **recordPointers = NULL;
	int nRecords;
	long i;

	if (nRecordsToLoad < 0) nRecordsToLoad = EMPLOYEE_MAX_REC;


	/** allocate a huge array that is big enough for the whole data set */
	records = (EMPLOYEErecord *)
			malloc(nRecordsToLoad * sizeof(EMPLOYEErecord));
	if (records == NULL) {
		fprintf(stderr, "Cannot allocate %d records\n", nRecordsToLoad);
		return -1;
	}

	/** load the array, recording how many were actually used */
	if ((nRecords = loadEmployeeArray(records,
			nRecordsToLoad, filename)) < 0) {
		fprintf(stderr, "Failed on load\n");
		return -1;
	}

	/** create the pointers to the records */
	recordPointers = createPointersToListRecords(records, nRecords);

	printf("Record size %ld bytes, pointer size %ld bytes\n",
			sizeof(EMPLOYEErecord),
			sizeof(EMPLOYEErecord *));

	printf(" -=-=-=- ORIGINAL ORDERING -=-=-=-\n");
	printEmployeeRecordArraySummary(records,
			nRecords, nRecordsToPrint);
	printf("\n");
	printEmployeePointerArraySummary(recordPointers,
			nRecords, nRecordsToPrint);
	printf("\n\n");


	printf("Sorting...\n");
	for (i = 0; i < nRepeatsRequested; i++) {

		/** time the record based sorting */
		recordSortTimeInSeconds = timeSortingOfRecords(records, nRecords);

		pointerSortTimeInSeconds =
				timeSortingOfPointers(recordPointers, nRecords);

		/** add to the total */
		totalRecordSortTimeInSeconds += recordSortTimeInSeconds;
		totalPointerSortTimeInSeconds += pointerSortTimeInSeconds;
	}

	printf("\n\n");

	printf(" -=-=-=- FINAL ORDERING -=-=-=-\n");
	printf("Records - by surname\n");
	printEmployeeRecordArraySummary(records,
			nRecords, nRecordsToPrint);
	printf("\n");
	printf("Pointers - by given name (reverse)\n");
	printEmployeePointerArraySummary(recordPointers,
			nRecords, nRecordsToPrint);

	printf("Average times:\n");
	printf("  records : %lf\n",
			(totalRecordSortTimeInSeconds / (double) nRepeatsRequested));
	printf("  pointers: %lf\n",
			(totalPointerSortTimeInSeconds / (double) nRepeatsRequested));

	/** clean up memory -- only two big chunks */
	free(recordPointers);
	free(records);

	return 1;
}

void usage(char *progname)
{
	fprintf(stderr, "%s [<OPTIONS>] <file> [ <file> ...]\n", progname);
	fprintf(stderr, "\n");
	fprintf(stderr, "Prints timing of loading and storing EMPLOYEE records.\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "Options: \n");
	fprintf(stderr, "-R <REPEATS> : Number of times to repeat load.\n");
	fprintf(stderr, "             : Time reported will be average time.\n");
	fprintf(stderr, "\n");
}

/**
 * Program mainline
 */
int
main(int argc, char **argv)
{
	int i, filesProcessed = 0;
	int nRepeatsRequested = 1, nRecordsToLoad = -1, nRecordsToPrint = -1;
	char *programname = NULL;
	int c;


	/* save program name before calling getopt() */
	programname = argv[0];

	/** use getopt(3) to parse command line */
	while ((c = getopt(argc, argv, "hN:R:n:")) != -1) {
		if (c == 'R') {
			if (sscanf(optarg, "%d", &nRepeatsRequested) != 1) {
				fprintf(stderr,
						"Error: cannot parse repeats requested from '%s'\n",
						optarg);
				return 1;
			}
		} else if (c == 'N') {
			if (sscanf(optarg, "%d", &nRecordsToLoad) != 1) {
				fprintf(stderr,
						"Error: cannot parse num records"
								" requested from '%s'\n",
						optarg);
				return 1;
			}
		} else if (c == 'n') {
			if (sscanf(optarg, "%d", &nRecordsToPrint) != 1) {
				fprintf(stderr,
						"Error: cannot parse num records"
								" to print from '%s'\n",
						optarg);
				return 1;
			}
		} else if (c == 'h') {
			usage(programname);
		}
	}

	/** update argc + argv to skip past flags */
	argc -= optind;
	argv += optind;

	/** getopt leaves us only "file" arguments left in argv */
	for (i = 0; i < argc; i++) {
		if (loadAndRunSortingRepeats(argv[i],
					nRepeatsRequested, nRecordsToLoad,
					nRecordsToPrint) < 0) {
			fprintf(stderr, "Error: failed processing '%s'\n", argv[i]);
			exit (1);
		}
		filesProcessed++;
	}


	if ( filesProcessed == 0 ) {
		fprintf(stderr,
				"No data processed -- provide the name of"
				" a file on the command line\n");
		usage(argv[0]);
		return 1;
	}

	return 0;
}

