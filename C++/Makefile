CXX=g++
CXXFLAGS=-g -ggdb -O2 -Wall

TARGET=miniPascali

OBJS=miniPascali.o lexical/SymbolTable.o \
		lexical/LexicalAnalysis.o \
		syntatic/SyntaticAnalysis.o \
		interpreter/command/AssignCommand.o \
		interpreter/command/BlocksCommand.o \
		interpreter/command/CaseCommand.o \
		interpreter/command/CaseOption.o \
		interpreter/command/ForCommand.o \
		interpreter/command/IfCommand.o \
		interpreter/command/ReadCommand.o \
		interpreter/command/RepeatCommand.o \
		interpreter/command/WhileCommand.o \
		interpreter/command/WriteCommand.o \
		interpreter/expr/BinaryExpr.o \
		interpreter/expr/CompositeBoolExpr.o \
		interpreter/expr/ConstExpr.o \
		interpreter/expr/NotBoolExpr.o \
		interpreter/expr/SingleBoolExpr.o \
		interpreter/expr/Variable.o \
		interpreter/util/Memory.o \
		interpreter/value/IntegerValue.o \
		interpreter/value/RealValue.o \
		interpreter/value/StringValue.o

all: $(TARGET)

clean:
	rm -rf $(TARGET) $(OBJS)

miniPascal.o:

lexical/SymbolTable.o: lexical/TokenType.h

lexical/LexicalAnalysis.o: lexical/Lexeme.h lexical/SymbolTable.h

syntatic/SyntaticAnalysis.o: syntatic/SyntaticAnalysis.h

interpreter/command/AssignCommand.o: interpreter/command/AssignCommand.h interpreter/command/Command.h

interpreter/command/BlocksCommand.o: interpreter/command/BlocksCommand.h interpreter/command/Command.h

interpreter/command/CaseCommand.o: interpreter/command/CaseCommand.h interpreter/command/Command.h

interpreter/command/CaseOption.o: interpreter/command/CaseOption.h interpreter/command/Command.h

interpreter/command/ForCommand.o: interpreter/command/ForCommand.h interpreter/command/Command.h

interpreter/command/IfCommand.o: interpreter/command/IfCommand.h interpreter/command/Command.h

interpreter/command/ReadCommand.o: interpreter/command/ReadCommand.h interpreter/command/Command.h

interpreter/command/RepeatCommand.o: interpreter/command/RepeatCommand.h interpreter/command/Command.h

interpreter/command/WhileCommand.o: interpreter/command/WhileCommand.h interpreter/command/Command.h

interpreter/command/WriteCommand.o: interpreter/command/WriteCommand.h interpreter/command/Command.h

interpreter/expr/BinaryExpr.o: interpreter/expr/BinaryExpr.h interpreter/expr/Expr.h

interpreter/expr/CompositeBoolExpr.o: interpreter/expr/CompositeBoolExpr.h interpreter/expr/Expr.h

interpreter/expr/ConstExpr.o: interpreter/expr/ConstExpr.h interpreter/expr/Expr.h

interpreter/expr/NotBoolExpr.o: interpreter/expr/NotBoolExpr.h interpreter/expr/Expr.h

interpreter/expr/SingleBoolExpr.o: interpreter/expr/SingleBoolExpr.h interpreter/expr/Expr.h

interpreter/expr/Variable.o: interpreter/expr/Variable.h interpreter/expr/Expr.h

interpreter/util/Memory.o: interpreter/util/Memory.h

interpreter/value/IntegerValue.o: interpreter/value/IntegerValue.h interpreter/value/Type.h interpreter/value/Value.h

interpreter/value/RealValue.o: interpreter/value/RealValue.h interpreter/value/Type.h interpreter/value/Value.h

interpreter/value/StringValue.o: interpreter/value/StringValue.h interpreter/value/Type.h interpreter/value/Value.h

$(TARGET):	$(OBJS)
			$(CXX) -o $(TARGET) $(OBJS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<
