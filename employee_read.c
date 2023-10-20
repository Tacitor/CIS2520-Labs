#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>

#include "employee.h"

/**
 * Read in a EMPLOYEE record, allocating memory for the fields.
 */
int
employeeReadRecord(FILE *ifp, EMPLOYEErecord *eRecord)
{
	char linebuffer[BUFSIZ], *token = NULL, *lastPtr = NULL;
	int lineLen;


	/** Load the line into the buffer -- if EOF return 0 */
	if (fgets(linebuffer, BUFSIZ, ifp) == NULL)
		return 0;
		
	/* check if we have overflow */
	lineLen = strlen(linebuffer);
	if (linebuffer[lineLen - 1] != '\n') {
		fprintf(stderr, "Error: EMPLOYEE parser read"
				" line greater than %d characters\n",
				BUFSIZ);
		return -1;
	}
	linebuffer[lineLen - 1] = '\0';

	/**
	 * break the line into fields using strtok_r(3)
	 */

	// first call sets up the parser
	lastPtr = NULL;
	token = strtok_r(linebuffer, "\t", &lastPtr);
	if (token == NULL) {
		fprintf(stderr, "Error: employee line error -- cannot set ID\n");
		return -1;
	}
	if (sscanf(token, "%d", &eRecord->id) != 1) {
		fprintf(stderr,
				"Error: employee line error -- cannot set ID from '%s'\n",
				token);
		return -1;
	}

	// now pull out the date of birth -- all but first strtok() calls
	// use NULL to process the same string
	token = strtok_r(NULL, "\t", &lastPtr);
	if (token == NULL) {
		fprintf(stderr, "Error: employee line error -- cannot set DOB\n");
		return -1;
	}
	if (strlen(token) != EMPLOYEE_DOB_MAX) {
		fprintf(stderr,
				"Error: employee line error -- cannot set DOB from '%s'\n",
				token);
		return -1;
	}
	strcpy(eRecord->dob, token);


	// now pull out the given name
	token = strtok_r(NULL, "\t", &lastPtr);
	if (token == NULL) {
		fprintf(stderr, "Error: employee line error -- cannot set name\n");
		return -1;
	}
	if (strlen(token) > EMPLOYEE_NAME_MAX) {
		fprintf(stderr,
				"Error: employee line error -- cannot set name from '%s'\n",
				token);
		return -1;
	}
	strcpy(eRecord->givenname, token);

	// now pull out the surname
	token = strtok_r(NULL, "\t", &lastPtr);
	if (token == NULL) {
		fprintf(stderr, "Error: employee line error -- cannot set surname\n");
		return -1;
	}
	if (strlen(token) > EMPLOYEE_NAME_MAX) {
		fprintf(stderr,
				"Error: employee line error -- cannot set surname from '%s'\n",
				token);
		return -1;
	}
	strcpy(eRecord->surname, token);

	// now pull out the gender
	token = strtok_r(NULL, "\t", &lastPtr);
	if (token == NULL) {
		fprintf(stderr, "Error: employee line error -- cannot set gender\n");
		return -1;
	}
	if (strlen(token) != 1) {
		fprintf(stderr,
				"Error: employee line error -- cannot set gender from '%s'\n",
				token);
		return -1;
	}
	eRecord->gender = token[0];

	// now pull out the date of employment
	token = strtok_r(NULL, "\t", &lastPtr);
	if (token == NULL) {
		fprintf(stderr, "Error: employee line error -- cannot set DOB\n");
		return -1;
	}
	if (strlen(token) != EMPLOYEE_DOB_MAX) {
		fprintf(stderr,
				"Error: employee line error -- cannot set DOB from '%s'\n",
				token);
		return -1;
	}
	strcpy(eRecord->doe, token);

	return 1;
}


int
employeePrintRecord(FILE *ofp, EMPLOYEErecord *eRecord, int index)
{
	fprintf(ofp, "EMP rec %4d:", index);
	fprintf(ofp, "   %s, %s (%c, born %s, employed %s), ID %d\n",
			eRecord->surname,
			eRecord->givenname,
			eRecord->gender,
			eRecord->dob,
			eRecord->doe,
			eRecord->id);

	return 1;
}

/**
 * Allocate and initialize a new EMPLOYEE record
 */
void
employeeInitializeRecord(EMPLOYEErecord *eRecord)
{
	memset(eRecord, 0, sizeof(EMPLOYEErecord));
}

/**
 * Allocate and initialize a new EMPLOYEE record
 */
EMPLOYEErecord *
employeeAllocateRecord()
{
	EMPLOYEErecord *eRecord = NULL;
	
	eRecord = (EMPLOYEErecord *) malloc(sizeof(EMPLOYEErecord));

	employeeInitializeRecord(eRecord);

	return eRecord;
}

/**
 * clear the record but do not free the eRecord pointer
 */
void
employeeClearRecord(EMPLOYEErecord *eRecord)
{
	memset(eRecord, 0, sizeof(EMPLOYEErecord));
}

/**
 * deallocate
 */
void
employeeDeallocateRecord(EMPLOYEErecord *eRecord)
{
	employeeClearRecord(eRecord);
	free(eRecord);
}

