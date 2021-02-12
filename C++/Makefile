CXX=g++
CXXFLAGS=-g -ggdb -O2 -Wall

TARGET=miniPascali

OBJS=miniPascali.o lexical/SymbolTable.o lexical/LexicalAnalysis.o \
	syntatic/SyntaticAnalysis.o

all: $(TARGET)

clean:
	rm -rf $(TARGET) $(OBJS)

miniPascal.o:

lexical/SymbolTable.o: lexical/TokenType.h

lexical/LexicalAnalysis.o: lexical/Lexeme.h lexical/SymbolTable.h

syntatic/SyntaticAnalysis.o: syntatic/SyntaticAnalysis.h

$(TARGET):	$(OBJS)
			$(CXX) -o $(TARGET) $(OBJS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<