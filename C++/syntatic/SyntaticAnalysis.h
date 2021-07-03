#ifndef SYNTATIC_ANALYSIS_H
#define SYNTATIC_ANALYSIS_H

#include "../lexical/LexicalAnalysis.h"

class AssignCommand;
class BlocksCommand;
class CaseCommand;
class CaseOption;
class Command;
class ForCommand;
class IfCommand;
class ReadCommand;
class RepeatCommand;
class WhileCommand;
class WriteCommand;

class BinaryExpr;
class BoolExpr;
class CompositeBoolExpr;
class ConstExpr;
class Expr;
class NotBoolExpr;
class SingleBoolExpr;
class Variable;

class IntegerValue;
class RealValue;
class StringValue;

class SyntaticAnalysis {
 	public:
 		SyntaticAnalysis(LexicalAnalysis& lex);
 		virtual ~SyntaticAnalysis();

 		Command* start();

 	private:
 		LexicalAnalysis& m_lex;
 		Lexeme m_current;

		void advance();
		void eat(enum TokenType type);
		void showError();

		BlocksCommand* procProgram();
		void procConst();
		void procVar();
		BlocksCommand* procBlock();
		Command* procBody();
		Command* procCmd();
		AssignCommand* procAssign();
		IfCommand* procIf();
		CaseCommand* procCase();
		WhileCommand* procWhile();
		RepeatCommand* procRepeat();
		ForCommand* procFor();
		WriteCommand* procWrite();
		ReadCommand* procRead();
		BoolExpr* procBoolExpr();
		SingleBoolExpr* procCmpExpr();
		Expr* procExpr();
		Expr* procTerm();
		Expr* procFactor();
		ConstExpr* procValue();
		Variable* procId();
		IntegerValue* procInteger();
		RealValue* procReal();
		StringValue* procString();

};

#endif
