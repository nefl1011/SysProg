# Definition der Variablen

# enthaelt die Header Files
HEADERDIR = includes

# enthaelt die Source Files
SRCDIR = src

# enthaelt die Obj Files zum Testen
OBJDIR = objs

# enthaelt das ausfuehrbare File zum Testen
BINDIRTEST = debug


AUTOMATDIR = ../Automat

BUFFERDIR = ../Buffer

SYMBOLTABLEDIR = ../Symboltable

SCANNERDIR = ../Scanner

## hier alle Object Files eintragen, ausser das File mit der Mainmethode
## darauf achten, dass letzte Zeile ohne "\" eingetragen wird

OBJS = $(OBJDIR)/Parser.o \
	$(OBJDIR)/ParseTree.o \
	$(OBJDIR)/Node.o \
	$(OBJDIR)/CodeGenerator.o \
	$(OBJDIR)/TypeChecker.o
	#$(OBJDIR)/NodeType.o \
	#$(OBJDIR)/RuleType.o
	#$(OBJDIR)/xxn.o

# Variante mit guten Makefile-Kenntnissen

makeTestParser: $(OBJS) ParserTest

#ParserTarget: $(OBJS)

# $@ name des object files = name auf der linken Seite vom Doppelpunkt des Targets
# $< erste abhaengigkeit, $< das erste Element in der Liste der Abhaengigkeiten
# $@ --> linke Seite vom Doppelpunkt
# $^ --> rechte Seite vom Doppelpunkt

#$(OBJDIR)/%.o :  $(SRCDIR)/%.cpp $(HEADERDIR)/%.h
#	g++ -g  -c -Wall  $<  -o $@

$(OBJDIR)/%.o :  $(SRCDIR)/%.cpp $(HEADERDIR)/%.h
	@echo "g++ $*.cpp"
	g++ -g  -c -Wall  -o $@  $<

ParserTest: $(SRCDIR)/TestParser.cpp $(HEADERDIR)/ParseTree.h
	g++ -g  -c -Wall src/TestParser.cpp -o $(BINDIRTEST)/TestParser.o  
	g++ -g $(BINDIRTEST)/TestParser.o $(OBJDIR)/*.o $(AUTOMATDIR)/$(OBJDIR)/*.o $(BUFFERDIR)/$(OBJDIR)/*.o $(SYMBOLTABLEDIR)/$(OBJDIR)/*.o $(SCANNERDIR)/$(OBJDIR)/*.o -o $(BINDIRTEST)/ParserTest


# loeschen aller files im verzeichnis $(OBJDIR) und $(BINDIRTEST) und neu compilieren

cleanParser:
	rm -rf $(OBJDIR)/*.o
	rm -rf $(BINDIRTEST)/*
	$(MAKE) makeTestParser
	
	
	
## objs fuer GesamtProjekt neu erzeugen
#ParserOBJTarget:
#	$(MAKE) ParserTarget

	