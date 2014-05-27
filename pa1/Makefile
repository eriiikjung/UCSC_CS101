#Rahul Palamutta, rpalamut@unix.ic.ucsc.edu
#Assignment 1 : Lex
# $Id: Makefile,v 1.2 2014-01-14 19:50:01-08 - - $
#------------------------------------------------------------------------------
#  Makefile for CMPS 101 pa1 
#  Compiles all .java files in the current directory and creates an executable
#  jar file called Lex.  See the following for a short description of makefiles
#
#            http://ic.ucsc.edu/~ptantalo/cmps12b/Summer13/lab1.pdf
#
#------------------------------------------------------------------------------ 

MAINCLASS  = Lex
JAVAC      = javac 
JAVASRC    = $(wildcard *.java)
SOURCES    = $(JAVASRC) Makefile README
CLASSES    = $(patsubst %.java, %.class, $(JAVASRC))
JARCLASSES = $(patsubst %.class, %*.class, $(CLASSES))
JARFILE    = $(MAINCLASS) 

all: $(JARFILE)

$(JARFILE): $(CLASSES)
	echo Main-class: $(MAINCLASS) > Manifest
	jar cvfm $(JARFILE) Manifest $(JARCLASSES)
	chmod +x $(JARFILE)
	rm Manifest

%.class: %.java
	$(JAVAC) $<

clean:
	rm -f *.class $(JARFILE)
submit: 
	submit cmps101-pt.w14 pa1 $(SOURCES)

