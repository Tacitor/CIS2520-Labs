
# CIS*2520 F23 Week 5 Lab

Frequently when we have a data set in memory we want to be able
to consider it as ordered on different fields within the same
records.  If the data set is large, we don't want to have to
completely duplicate the data set just to consider it in a different
order.

## Lab Objective:

In this lab we will consider a sequence of records (in this case
stored as an array of structs) for which we want to have a
*secondary index* -- that is a second field for which the data
is also "in order" when considered a different way.

Our data will be a set of seven fruits, that have both common
and Latin names.  When ordered by common name, this is the list:

    0 : 'apple' is 'Malus'
    1 : 'banana' is 'Musa'
    2 : 'cherry' is 'Prunus avium'
    3 : 'durian' is 'Durio'
    4 : 'elderberry' is 'Sambucus'
    5 : 'fig' is 'Ficus'
    6 : 'grape' is 'Vitus'
    7 : 'honeydew' is 'Cucumis melo'

When ordered by Latin name, this same list become this

    0 : 'honeydew' is 'Cucumis melo'
    1 : 'durian' is 'Durio'
    2 : 'fig' is 'Ficus'
    3 : 'apple' is 'Malus'
    4 : 'banana' is 'Musa'
    5 : 'cherry' is 'Prunus avium'
    6 : 'elderberry' is 'Sambucus'
    7 : 'grape' is 'Vitus'

To support this second ordering, we will have an *array of pointers*
to the data, and set up this *array of pointers* so that they are
ordered by our Latin name.

As you can imagine, if the structures are large, this can save a **lot**
of memory, as we only need one pointer per entry to represent it in this
second list.



## Lab Activities

Clone the `Lab5` project from `gitlab` as per usual.

There are several files in this lab, but they fall into three groups:

1) code relevant to searching either the array of structs or the array of pointers to structs:

	* `lab5_arraysearch.c` and `lab5_pointersearch.c`

2) code to load and print the structures:

	* `FruitData.h`, `FruitData.c` and `dataload_main.c`

3) the binary search code from the course directory with lots of debugging
	`printf()` statements added to help you see what the current activity
	in the code is in case there is a crash:

	* `bsearch-verbose.h` and `bsearch-verbose.c`


Your lab activity is to look at the code in `lab5_arraysearch.c` which
successfully applies binary search to an ordered array of structs, and
adapt this in `lab5_pointersearch.c` so that you can apply binary search
to an ordered array of **pointers to structs**.

Things to keep in mind:

* pointers are **not** the same size as the structs
* you can turn a *pointer to pointer* into a more manageable *pointer* using a temporary variable

	* for example, using these variables

	```c
    struct Something **pointerToPointer;
    struct Something *simplePointer;
    char *aName;
	```

	* you can access field "name" within the data in either of these ways:

	```c
    aName = (*pointerToPointer)->name

    simplePointer = *pointerToPointer;
    aName = simplePointer->name
	```

	* you may well find the second formulation easier to keep track of.  Your compiler won't care which one you use (they will be just as fast as each other, too.)

# Lab code submission

As with our previous work, we are simply going to `commit` and `push`
our code into `gitlab`.

## Validate your submission

Be sure to verify that your lab was submitted properly,
as was described last time.

