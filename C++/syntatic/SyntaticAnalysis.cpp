#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>

#include "SyntaticAnalysis.h"

// #include "../interpreter/expr/IntExpr.h"
// #include "../interpreter/expr/BinaryIntExpr.h"
// #include "../interpreter/expr/ConstIntExpr.h"
// #include "../interpreter/expr/NegIntExpr.h"
// #include "../interpreter/expr/ReadIntExpr.h"
// #include "../interpreter/expr/Variable.h"
// #include "../interpreter/expr/BoolExpr.h"
// #include "../interpreter/expr/ConstBoolExpr.h"
// #include "../interpreter/expr/NotBoolExpr.h"
// #include "../interpreter/expr/SingleBoolExpr.h"
// #include "../interpreter/command/Command.h"
// #include "../interpreter/command/AssignCommand.h"
// #include "../interpreter/command/BlocksCommand.h"
// #include "../interpreter/command/IfCommand.h"
// #include "../interpreter/command/OutputCommand.h"
// #include "../interpreter/command/WhileCommand.h"

SyntaticAnalysis::SyntaticAnalysis(LexicalAnalysis& lex) :
	m_lex(lex), m_current(lex.nextToken()) {
}

SyntaticAnalysis::~SyntaticAnalysis() {
}

//Command* SyntaticAnalysis::start() {
void SyntaticAnalysis::start() {
	//Command* cmd = procProgram();
	//eat(TT_END_OF_FILE);
	//return cmd;
}

void SyntaticAnalysis::advance() {
	m_current = m_lex.nextToken();
}

void SyntaticAnalysis::eat(enum TokenType type) {
	// std::cout << "Expected (..., " << tt2str(type)
	//           <<  "), found (\"" + m_current.token << "\", "
	// 		  << tt2str(m_current.type) << ")" << std::endl;
	if (type == m_current.type) {
		advance();
	} else {
		showError();
	}
}

void SyntaticAnalysis::showError() {
	std::cout << std::setw(2) << std::setfill('0') << m_lex.line() << ": ";

	switch (m_current.type) {
		case TT_INVALID_TOKEN:
			std::cout << "Lexema inválido [" << m_current.token << "]" << std::endl;
			break;
		case TT_UNEXPECTED_EOF:
		case TT_END_OF_FILE:
			std::cout << "Fim de arquivo inesperado" << std::endl;
			break;
		default:
			std::cout << "Lexema não esperado [" << m_current.token << "]" << std::endl;
			break;
	}

    exit(1);
}

/*
1 - 			5 -				9 -					13 -				17 -
2 - P			6 -	ok			10 - OK				14 -				18 -
3 - 			7 -				11 -				15 -				19 -
4 - 			8 -				12 - ok				16 -				20 - /k
*/



// // <program>   ::= program <id> ;
	//				[ const <const> { <const> } ]
	// 				[ var <var> { <var> } ]
	//				<block> '.'
// Command* SyntaticAnalysis::procProgram() {
void SyntaticAnalysis::procProgram() { // 1
}

// // <const> ::= <id> '=' <value> ';'
// ConstIntExpr* SyntaticAnalysis::procConst() {
void SyntaticAnalysis::procConst() { // 2 procId pendente
	//procId();
	eat(TT_EQUAL);
	procValue();
	eat(TT_SEMICOLON);
}

// // <var> ::= <id> { ',' <id> } [ '=' <value> ] ';'
// Variable* SyntaticAnalysis::procVar() {
void SyntaticAnalysis::procVar() { // 3
}

// //<body> ::= <block> | <cmd>
void SyntaticAnalysis::procBody() { // 4

}

// //<block> ::= begin [ <cmd> { ';' <cmd> } ] end
void SyntaticAnalysis::procBlock() { // 5
}

// // <cmd> ::= <assign> | <if> | <case> | <while> | <for> | <repeat> | <write> | <read>
// Command* SyntaticAnalysis::procCmd() {
void SyntaticAnalysis::procCmd() { // 6
	if (m_current.type == TT_ASSIGN) {
		procAssign();
	} else if (m_current.type == TT_IF) {
		procIf();
	} else if (m_current.type == TT_CASE) {
		procCase();
	} else if (m_current.type == TT_WHILE) {
		procWhile();
	} else if (m_current.type == TT_FOR) {
		procFor();
	} else if (m_current.type == TT_REPEAT) {
		procRepeat();
	} else if (m_current.type == TT_WRITE || m_current.type == TT_WRITELN) {
		procWrite();
	} else if (m_current.type == TT_READLN) {
		procRead();
	}
}

// // <assign> ::= <id> ':=' <expr>
// AssignCommand* SyntaticAnalysis::procAssign() {
void SyntaticAnalysis::procAssign() { // 7
}

// // <if> ::= if <boolexpr> then <body> [ else <body> ]
// IfCommand* SyntaticAnalysis::procIf() {
void SyntaticAnalysis::procIf() { // 8
}

// //<case> ::= case <expr> of { <value> ':' <body> ';' } [ else <body> ';' ] end
void SyntaticAnalysis::procCase() { // 9
}

// // <while> ::= while <boolexpr> do <body>
// WhileCommand* SyntaticAnalysis::procWhile() {
void SyntaticAnalysis::procWhile() { // 10 ok
	eat(TT_WHILE);
	procBoolExpr();
	eat(TT_DO);
	procBody();
}

// // <repeat> ::= repeat [ <cmd> { ';' <cmd> } ] until <boolexpr>
void SyntaticAnalysis::procRepeat() { // 11
}

// // <for> ::= for <id> ':=' <expr> to <expr> do <body>
void SyntaticAnalysis::procFor() { // 12
	eat(TT_FOR)
	//procId();
	eat(TT_ASSIGN);
	procExpr();
	eat(TT_TO)
	procExpr();
	eat(TT_DO);
	procBody();
}

// // <write> ::= (write | writeln) '(' [ <expr> { ',' <expr> } ] ')'
void SyntaticAnalysis::procWrite() { // 13
}

// // <read> ::= readln '(' <id> { ',' <id> } ')'
void SyntaticAnalysis::procRead() { // 14
	procRead();
	eat(TT_LEFT_PARENTHESES);
	//procId();
	while(m_current.type == TT_COMMA) {
		eat(TT_COMMA);
		//procId();
	}
}

// // <boolexpr> ::= [ not ] <cmpexpr> [ (and | or) <boolexpr> ]
// BoolExpr* SyntaticAnalysis::procBoolExpr() {
void SyntaticAnalysis::procBoolExpr() { // 15
}

// // <cmpexpr> ::= <expr> ('=' | '<>' | '<' | '>' | '<=' | '>=') <expr>
void SyntaticAnalysis::procCmpExpr(){ // 16
}

// // <expr> ::= <term> { ('+' | '-') <term> }
void SyntaticAnalysis::procExpr() { // 17
}

// // <term> ::= <factor> { ('*' | '/' | '%') <factor> }
void SyntaticAnalysis::procTerm() { // 18
	procFactor();
	while (m_current.type == TT_MUL ||
			m_current.type == TT_DIV ||
			m_current.type == TT_MOD ||
			m_current.type == TT_INTEGER ||
			m_current.type == TT_REAL ||
			m_current.type == TT_STRING ||
			m_current.type == TT_VAR ||
			m_current.type == TT_CONST) {

	}
}

// // <factor> ::= <value> | <id> | '(' <expr> ')'
void SyntaticAnalysis::procFactor() { // 19
}

// // <value> ::= <integer> | <real> | <string>
// IntExpr* SyntaticAnalysis::procIntTerm() {
void SyntaticAnalysis::procValue() { // 20
	if (m_current.type == TT_INTEGER) {
		//procInteger();
	} else if (m_current.type == TT_REAL) {
		//procReal();
	} else if (m_current.type == TT_STRING) {
		//procString();
	}
}

void SyntaticAnalysis::procId(){
	eat(TT_ID);
}
