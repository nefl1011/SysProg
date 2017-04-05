# Definition der Variablen

# enthaelt die Header Files
HEADERDIR = includes

# enthaelt die Source Files
SRCDIR = src

# enthaelt die Obj Files zum Testen
OBJDIR = objs

# enthaelt das ausfuehrbare File zum Testen
BINDIRTEST = debug


## hier alle Object Files eintragen, ausser das File mit der Mainmethode
## darauf achten, dass letzte Zeile ohne "\" eingetragen wird

OBJS = $(OBJDIR)/Automat.o \
	$(OBJDIR)/Token.o
	#$(OBJDIR)/xxn.o


#
#		Targets zum Bauen des Tests
#

# Variante mit geringen Makefile-Kenntnissen

## Linken der Object-Files
#makeTestAutomat: $(OBJDIR)/Automat.o $(OBJDIR)/TestAutomat.o
#	g++ -g $(OBJDIR)/Automat.o $(OBJDIR)/TestAutomat.o -o $(BINDIR)/AutomatTest
#   cp $(OBJDIR)/Automat.o ../projectOBJs
#
#	
## compilieren der Source-files
#
#$(OBJDIR)/Automat.o :  $(SRCDIR)/Automat.cpp $(HEADERDIR)/Automat.h
#	@echo "g++ $*.cpp"
#	g++ -g  -c -Wall  -o $(OBJDIR)/Automat.o  $(SRCDIR)/Automat.cpp
#
#
#$(OBJDIR)/TestAutomat.o :  $(SRCDIR)/TestAutomat.cpp $(SRCDIR)/Automat.h
#	@echo "g++ $*.cpp"
#	g++ -g  -c -Wall  -o $(OBJDIR)/TestAutomat.o  $(SRCDIR)/TestAutomat.cpp
#


# Variante mit guten Makefile-Kenntnissen

makeTestAutomat: AutomatTarget TestAutomatTarget
	g++ -g $(OBJDIR)/*.o $(BINDIRTEST)/TestAutomat.o  -o $(BINDIRTEST)/AutomatTest

AutomatTarget: $(OBJS)

# $@ name des object files = name auf der linken Seite vom Doppelpunkt des Targets
# $< erste abhaengigkeit, $< das erste Element in der Liste der Abhaengigkeiten
# $@ --> linke Seite vom Doppelpunkt
# $^ --> rechte Seite vom Doppelpunkt

$(OBJDIR)/%.o :  $(SRCDIR)/%.cpp $(HEADERDIR)/%.h
	g++ -g  -c -Wall  $<  -o $@



TestAutomatTarget: $(SRCDIR)/TestAutomat.cpp $(HEADERDIR)/Automat.h
	g++ -g  -c -Wall $(SRCDIR)/TestAutomat.cpp -o $(BINDIRTEST)/TestAutomat.o  
	


# loeschen aller files im verzeichnis $(OBJDIR) und $(BINDIRTEST) und neu compilieren

cleanAutomat:
	rm -rf $(OBJDIR)/*.o
	rm -rf $(BINDIRTEST)/*
	$(MAKE) makeTestAutomat
	
	
	
## objs fuer GesamtProjekt neu erzeugen
AutomatOBJTarget:
	$(MAKE) AutomatTarget

	