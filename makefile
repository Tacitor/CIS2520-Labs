
##
## This file builds lab 4
##

##
## Some macros (makefile 'variables') are defined by default
## by make(1).  The ones relevant to C compiling are:
##  CC     : the name of the compiler (defaults to system compiler)
##  CFLAGS : the flags (options) to pass to the compiler
##
## There are similar macros for other languages, for example C++ uses
##  CXX      : the name of the c++ compiler (defaults to system compiler)
##  CXXFLAGS : the flags (options) to pass to the c++ compiler


## explicitly add debugger support to each file compiled,
## and turn on all warnings.  If your compiler is surprised by your
## code, you should be too.
CFLAGS = -g -Wall

## uncomment/change this next line if you need to use a non-default compiler
#CC = cc


##
## We can define variables for values we will use repeatedly below
##

## define the two executables we want to build
LAB_EXE = lab4
EXAMPLE_EXE = example

## define the set of object files we need to build each executable
LAB_OBJS		= lab4_main.o LLGeneric.o
EXAMPLE_OBJS	= example_main.o LLGeneric.o


##
## TARGETS: below here we describe the target dependencies and rules
##
all: $(EXAMPLE_EXE) $(LAB_EXE)

$(LAB_EXE) : $(LAB_OBJS)
	$(CC) $(CFLAGS) -o $(LAB_EXE) $(LAB_OBJS)

$(EXAMPLE_EXE) : $(EXAMPLE_OBJS)
	$(CC) $(CFLAGS) -o $(EXAMPLE_EXE) $(EXAMPLE_OBJS)

## convenience target to remove the results of a build
clean :
	- rm -f $(LAB_OBJS) $(LAB_EXE)
	- rm -f $(EXAMPLE_OBJS) $(EXAMPLE_EXE)

