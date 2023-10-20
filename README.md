
# CIS*2520 F23 Week 6 Lab

When we have a list of records that have multiple values that
might be used as keys, we frequently want access to this list
of records in different orders for different queries using
these keys.

It is very costly to keep re-sorting the data every time we
want to consider a different key.

It is also very costly in term of memory to keep multiple copies
of an entire array of records just to have access to them in
different orders.

What we will consider in this lab is that a simple array of
**pointers to records** can be used to refer to the underlying
array of full records, and that this array of pointers can be
sorted in a completely independent order.


## Lab Objective:

In this lab we will write code to perform quicksort on both
an array of records and an array of record pointers.  We will
use the system implementation of this algorithm, through
the `qsort(3)` function.

You have been provided a data file full of made up "employee"
records.  This file is available as
```
/home/courses/cis2520/data/employees.tsv
```

This file consists of a set of text records that will be loaded
into a data structure with the following fields:
```
typedef struct EMPLOYEErecord {
	int id;
	char dob[EMPLOYEE_DOB_MAX + 1];	// EMPLOYEE_DOB_MAX is 10 chars
	char doe[EMPLOYEE_DOB_MAX + 1];
	char gender;
	char givenname[EMPLOYEE_NAME_MAX];
	char surname[EMPLOYEE_NAME_MAX]; // EMPLOYEE_NAME_MAX is 16 chars
} EMPLOYEErecord;
```

Code has been provided to load this data into an array of records
based on the `struct EMPLOYEErecord` type above, and into an array
of pointers to these records (which simply point at the records
in the first array).

We will use the `qsort(3)` function to sort them.  This function
has this signature:
```
void
	qsort(void *base, size_t nel, size_t width,
		int (*compar)(const void *, const void *));
```

Note that the `compar` argument will be presented with the two
elements to be compared as the two arguments.  Our discussion
of the C implementation of "bubble sort" in class used a comparator
function of exactly the same form.
(Note there is no "user data" pointer here.)



## Lab Activities

Clone the `Lab6` project from `gitlab` as per usual.

There are several files in this lab, but they fall into two groups:

1) code relevant to loading the employee records into the two array types:

	* `employee.h` and `employee_read.c`: reads the records from the file
	* `lists.h` and `list_tools.c`: places the records into and array,
			and builds an array of pointers; also provides code to print
			out the array of records and array of pointers

2) code holding the mainline, which calls for the loading and sorting
	to occur -- this is where you will do your edits:

	* `lab6_main.c` look for "TODO" for markers where additional code
		is needed.

Your lab activity is to look at the code in `lab6_main.c` and provide
the missing comparators and calls to `qsort(3)`

## Command line

This program takes three flags and the names of files to run:

* `-N <N>`: read only `<N>` records, rather than the whole employee file
* `-n <N>`: print only `<N>` records (or pointers to records) in the
	output summary.  The beginning and end of the list together will
	total `<N>` with half of the values coming from the beginning of
	the sequence and the rest from the end.
* `-R <N>`: repeat the sorting `<N>` times

This program is written using `getopt(3)`, a standard utility to help
process the command line.  Among other things, this means that it
does not need arguments between the flag name and its value.  For
example `-N 1000` and `-N1000` are equivalent.

## Output tools

The function
`printEmployeeRecordArraySummary(EMPLOYEErecord *, int)`
will print out the contents of an array of `EMPLOYEErecord` structures, and
`printEmployeePointerArraySummary(EMPLOYEErecord **, int)`
will do the same for an array of pointers to these structures.

As the arrays may be quite large, only the first and last few elements
will be printed, as controlled by the `-n` option on the command line
as described above.

Printing the first and last 5 values for the first 1000 **records** should
produce this output for the array of records when correctly sorted:
```
Array of 1000 RECORDS (10 printed)
EMP rec    0:   Acton, Zorica (M, born 1962-08-30, employed 1989-08-05), ID 10695
EMP rec    1:   Adachi, Eran (M, born 1962-10-01, employed 1993-08-01), ID 10967
EMP rec    2:   Aingworth, Eben (M, born 1952-08-29, employed 1990-12-19), ID 10106
EMP rec    3:   Aingworth, Divine (M, born 1961-06-17, employed 1987-06-29), ID 10994
EMP rec    4:   Aingworth, Munehiro (M, born 1957-05-22, employed 1993-05-21), ID 10991
   ...
   990 records skipped 
   ...
EMP rec  995:   Zyda, Remko (M, born 1952-05-25, employed 1991-05-24), ID 10944
EMP rec  996:   Zyda, Zhonghui (F, born 1957-03-29, employed 1990-09-13), ID 10118
EMP rec  997:   d'Astous, Patricia (M, born 1964-05-19, employed 1989-03-14), ID 10786
EMP rec  998:   d'Astous, Shalesh (M, born 1963-09-16, employed 1988-08-24), ID 10362
EMP rec  999:   d'Astous, Hauke (M, born 1963-01-12, employed 1990-06-30), ID 10545
```

Similarly, the first and last 5 values for the first 1000 **pointers
to records** should produce this output for the array of records when
correctly sorted:
```
Array of 1000 POINTERS (10 printed)
EMP rec    0:   Nyanchama, Zvonko (M, born 1952-06-29, employed 1989-03-31), ID 10047
EMP rec    1:   Salinas, Zsolt (F, born 1964-11-12, employed 1985-02-21), ID 10253
EMP rec    2:   Acton, Zorica (M, born 1962-08-30, employed 1989-08-05), ID 10695
EMP rec    3:   Cusworth, Zongyan (M, born 1959-01-14, employed 1990-04-24), ID 10685
EMP rec    4:   Minakawa, Zita (F, born 1954-01-11, employed 1985-09-01), ID 10726
   ...
   990 records skipped 
   ...
EMP rec  995:   Beutelspacher, Abdulla (F, born 1963-06-30, employed 1992-06-14), ID 10931
EMP rec  996:   Thibadeau, Abdulah (F, born 1957-01-17, employed 1990-12-12), ID 10154
EMP rec  997:   Riesenhuber, Abdelwaheb (F, born 1953-10-03, employed 1990-02-23), ID 10509
EMP rec  998:   Bisiani, Abdelaziz (M, born 1961-03-03, employed 1988-09-16), ID 10674
EMP rec  999:   Radwan, Aamod (M, born 1963-01-29, employed 1987-01-27), ID 10346
```

Notice that the records are in ascending order by surname, and the
pointers to records in descending order by given name.

Note that the print statements in the program are already provided for you.


# Lab code submission

As with our previous work, we are simply going to `commit` and `push`
our code into `gitlab`.

## Validate your submission

Be sure to verify that your lab was submitted properly,
as was described last time.

