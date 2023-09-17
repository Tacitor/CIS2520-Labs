
# CIS*2520 F23 Week 3 Lab

In this lab we will experiment with escape characters in input, of
the form that are handled by the C compiler, `make(1)`, and many other
tools

## Lab Objective:

We want to write a simple program that read data one character at a
time from a file, and translates that data, including any "escaped"
characters into the appropriate output data.

We will simply write on standard output (`stdout`).

Input characters should be transferred directly, except for the
following two cases:

* non-escaped actual newline characters in the input should cause
  the "line leader" to be printed out and the line number incremented
* any character following the escape character '`\`' may have a
  special meaing as follows:
  	* `n` : generate a "new line" character (with no "line leader")
	* `t` : generate a tab character
    * `'` : generate a single quote character
    * `\n` : (an actual newline character) in this case,
		generate nothing -- that is, the input should be as though
		this escaped end-of-line character never existed
    * `\` : (*i.e.;* the escape character itself) this should
			generate a '`\`' character
	* : any other escaped character simply has it "unescaped" meaning,
         for example the sequence "`\Q`" would simply output a "`Q`"


# Lab Activities

Clone the `Lab3` project from `gitlab` as per usual.

The only files in this lab are the `lab3_main.c` file and some
sample data files, along with the `makefile` and this `README.md` file.

There should be no allocation or deallocation of memory in this lab
so there is no `valgrind(1)` script.  (As you are only processing
data one character at a time, there is nothing that requires storage.)

# Lab code submission

As with our previous work, we are simply going to `commit` and `push`
our code into `gitlab`.

## Validate your submission

Be sure to verify that your lab was submitted properly,
as was described last time.

