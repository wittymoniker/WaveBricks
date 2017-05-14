## GNU makefile for Linux.
##
## Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
## Creation Date: Sun Feb  3 10:15:51 PST 2002
## Last Modified: Sun Feb  3 10:15:54 PST 2002
## Filename:      ...soundfile/Makefile
##
## Description: This Makefile can create the soundfile library or example 
##              programs which use the soundfile library in linux using 
##              gcc 2.7.2 or higher.
##
## To run this makefile, type (without quotes)
## (1)  "make library"    -- to compile sig library (into soundfile/lib)
## (2)  "make examples"   -- to compile example programs (into soundfile/bin)
##

# MAKE stores the name of the makefile program:
MAKE = make

# commands which do not refer to actual files:
.PHONY: all clean lib library examples example

###########################################################################
#                                                                         #
#                                                                         #

all:
	@echo ""
	@echo This makefile will create either the soundfile library,
	@echo or will compile the soundfile example programs.  You will
	@echo have to make the library first if it does not exist
	@echo \(lib/libsoundfile.a\).  Type one of the following commands:
	@echo ""
	@echo "$(MAKE) library"
	@echo "   To create the soundfile library for use with other programs."
	@echo ""
	@echo "$(MAKE) examples"
	@echo "   To compile all example programs."
	@echo ""
	@echo "$(MAKE) <example-program>"
	@echo "   To compile a particular example programs."
	@echo ""

lib: library
library:
	$(MAKE) -f Makefile.library

clean:
	$(MAKE) -f Makefile.library clean

example: examples
examples: 
	$(MAKE) -f Makefile.examples

%: 
	@echo compiling file $@
	$(MAKE) -f Makefile.examples $@

#                                                                         #
#                                                                         #
###########################################################################



