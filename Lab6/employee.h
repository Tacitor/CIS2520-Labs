#ifndef	__EMPLOYEE_RECORD_TOOLS_HEADER__
#define	__EMPLOYEE_RECORD_TOOLS_HEADER__


#define EMPLOYEE_NAME_MAX	64
#define EMPLOYEE_DOB_MAX	10
#define EMPLOYEE_MAX_REC	500000

typedef struct EMPLOYEErecord {
	int id;
	char dob[EMPLOYEE_DOB_MAX + 1];
	char doe[EMPLOYEE_DOB_MAX + 1];
	char gender;
	char givenname[EMPLOYEE_NAME_MAX];
	char surname[EMPLOYEE_NAME_MAX];
} EMPLOYEErecord;

int  employeeReadRecord(FILE *ifp, EMPLOYEErecord *fRecord);
void employeeInitializeRecord(EMPLOYEErecord *fRecord);
EMPLOYEErecord * employeeAllocateRecord();
int  employeePrintRecord(FILE *ofp, EMPLOYEErecord *fRecord, int index);
void employeeClearRecord(EMPLOYEErecord *fRecord);
void employeeDeallocateRecord(EMPLOYEErecord *fRecord);

int loadEmployeeArray(EMPLOYEErecord *list, int maxRecords, char *filename);
EMPLOYEErecord **createPointersToListRecords(
		EMPLOYEErecord *sourceRecords, int nRecords);
void printEmployeeRecordArraySummary(EMPLOYEErecord *list,
		int nRecords, int nToPrint);
void printEmployeePointerArraySummary(EMPLOYEErecord **list,
		int nRecords, int nToPrint);

#endif /* __EMPLOYEE_RECORD_TOOLS_HEADER__ */
