#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#include "employee.h"


/**
 * Allocate a list of records and a list of pointers,
 * populating the record list from the EMPLOYEE file, and
 * the pointers from the records
 */
EMPLOYEErecord **
createPointersToListRecords(EMPLOYEErecord *sourceRecords, int nRecords)
{
	EMPLOYEErecord **recordPointers = NULL;
	int i;

	recordPointers = malloc(nRecords * sizeof(EMPLOYEErecord *));
	for (i = 0; i < nRecords; i++) {
		recordPointers[i] = &sourceRecords[i];
	}

	return recordPointers;
}

/**
 * Load a set of records into a given array
 */
int
loadEmployeeArray(EMPLOYEErecord *list, int maxRecords, char *filename)
{
	int recordNumber = 0, status;
	int keepReading = 1;
	FILE *fp;

	fp = fopen(filename, "r");
	if (fp == NULL) {
		fprintf(stderr, "Failure opening %s : %s\n",
				filename, strerror(errno));
		return -1;
	}

	do {
		// print a '.' every 10,000 records so
		// we know something is happening
		if ((recordNumber % 10000) == 0) {
			printf(".");
			fflush(stdout);
		}

		status = employeeReadRecord(fp, &list[recordNumber]);
		if (status <= 0) {
			keepReading = 0;
		} else {
			/* record read successfully, so increment counter */
			recordNumber++;
		}

	} while ( (keepReading) && (recordNumber < maxRecords));

	if (status < 0) {
		fprintf(stderr, "Error: failure record %d in '%s'\n",
					recordNumber, filename);
		return -1;
	}

	if (recordNumber == maxRecords) {
		printf(" Stopping after %d EMPLOYEE records loaded\n", recordNumber);
	} else {
		printf(" %d EMPLOYEE records loaded\n", recordNumber);
	}

	fclose(fp);

	return recordNumber;
}

/**
 * Clear a set of records loaded into a given array
 */
void
clearEmployeeArray(EMPLOYEErecord *list, int maxRecords)
{
	int i;

	for (i = 0; i < maxRecords; i++) {
		employeeClearRecord(&list[i]);
	}
}


/**
 * Print out a summary of records
 */
void
printEmployeeRecordArraySummary(EMPLOYEErecord *list, int nRecords, int nToPrint)
{
	int i, restartIndex;

	if (nToPrint < 0)	nToPrint = 10;

	if (nRecords < nToPrint) {
		printf("Array of %d RECORDS (all printed)\n", nRecords);
		for (i = 0; i < nRecords; i++) {
			employeePrintRecord(stdout, &list[i], i);
		}
	} else {
		printf("Array of %d RECORDS (%d printed)\n", nRecords, nToPrint);
		for (i = 0; i < nToPrint/2; i++) {
			employeePrintRecord(stdout, &list[i], i);
		}
		restartIndex = nRecords - (nToPrint - (nToPrint/2));
		printf("   ...\n   %d records skipped \n   ...\n",
				restartIndex - (nToPrint/2));
		for (i = restartIndex; i < nRecords; i++) {
			employeePrintRecord(stdout, &list[i], i);
		}
	}
}


/**
 * Print out a summary of records
 */
void
printEmployeePointerArraySummary(EMPLOYEErecord **list, int nRecords, int nToPrint)
{
	int i, restartIndex;

	if (nToPrint < 0)	nToPrint = 10;

	if (nRecords < nToPrint) {
		printf("Array of %d POINTERS (all printed)\n", nRecords);
		for (i = 0; i < nRecords; i++) {
			employeePrintRecord(stdout, list[i], i);
		}
	} else {
		printf("Array of %d POINTERS (%d printed)\n", nRecords, nToPrint);
		for (i = 0; i < nToPrint/2; i++) {
			employeePrintRecord(stdout, list[i], i);
		}
		restartIndex = nRecords - (nToPrint - (nToPrint/2));
		printf("   ...\n   %d records skipped \n   ...\n",
				restartIndex - (nToPrint/2));
		for (i = restartIndex; i < nRecords; i++) {
			employeePrintRecord(stdout, list[i], i);
		}
	}
}

