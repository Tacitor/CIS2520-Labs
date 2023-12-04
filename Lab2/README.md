
# CIS*2520 F23 Week 2 Lab

In this lab we will experiment with command line options.

## Lab Objective:

We want to write a program that prints out all the words of a given
length from one or more input files.

Our program must support the following command line options:

* `-h` : Print the help.
* `-L` : Force output words into lower case
* `-U` : Force output words into UPPER CASE
* `-l` *`<`SIZE`>`* : Use <SIZE> as the length of word to print instead of the default size of 4 
* `-W` *`<`SIZE`>`* : Use <SIZE> as the maximum word size instead of the default size of 64 


Additionally, for one bonus point on this lab (out of 10), the program
can support this additional command line option:

* `-o` *`<`FILENAME`>`* : Place output in filename instead of stdout


To implement the program, we can use the `WordExtractor` tool that we are using in Assignment 1.

**Note:** *there is a **space** between any flag and the data value associated with a flag in this design.  That means that there is a space between the `-l` option and its value, and between the `-W` option and its value.* (And between `-o` and its value, if you implement that.)

This means that the value will *always* be in the argv string that *follow* the flag. (A "flag" in a UNIX command line program is an argument beginning with a `-` character -- flags modify how a program works.  Arguments to command line programs that are not data values that accompany flags are usually file names.)

# Lab Activities

Clone the `Lab2` project from `gitlab` using the same procedure that you used last week for `Lab1` and for `A1`.

Once you have done this, you will see that you have some of the same
text files as in the assignment, as well as the same `WordExtractor`
header and source file.

What we need to do in this lab is write code in the `lab2_main.c` file
to actually process the command line as described above.

Your code should **check for errors**, such as missing or nonsensical
values given as command line arguments.



# Command line parsing C code example

Remember that in the course directory `/home/courses/cis2520`
on the `linux.socs.uoguelph.ca` machines there is an
example of parsing the command line which you can refer to in the directory `command-line`.

In this example we will need to convert a command line argument string to
a number.  There are three common ways to do this:

* using `sscanf(3)`
* using `atoi(3)`
* using `strtol(3)`

Choose one of these and implement your solution in this way.

# Lab code submission

As with Lab 1, we are simply going to `commit` and `push` our code.

## Validate your submission

It is **always** a very good idea to make sure that what you submitted
is what you actually wanted to submit, so once you think you have pushed
your code properly, do this:

* make a new directory somewhere else on your system
	* choose a place outside your CIS2520 working space, otherwise it
		is very easy to get confused
	* a good choice might be a directory called "`validate`" in your HOME directory
* in this new "`validate`" directory:
	* clone your Lab2 project again
	* look at what you got out -- is it what you want?
		* are all the files there?
		* does it build properly?
	* if it is not what you want, you can "commit" and "push" the missing
		files from your regular workspace directory
	* doing a "git pull" here will update this workspace now that you have
		*cloned* it.

You should do this kind of validation for each lab and assignment.

## Validation Cleanup

Once you have made sure that you have actually put everything you want
into gitlab, you can delete the `validate` directory


