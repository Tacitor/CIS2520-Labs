
##
## This file builds lab 2
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
EXE = lab3

## define the set of object files we need to build each executable
OBJS		= lab3_main.o


##
## TARGETS: below here we describe the target dependencies and rules
##

$(EXE) : $(OBJS)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJS)

## convenience target to remove the results of a build
clean :
	- rm -f $(OBJS) $(EXE)

