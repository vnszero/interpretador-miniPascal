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
	procProgram();
	eat(TT_END_OF_FILE);
	//return cmd;
}

void SyntaticAnalysis::advance() {
	m_current = m_lex.nextToken();
}

void SyntaticAnalysis::eat(enum TokenType type) {
	//*
	std::cout << "Expected (..., " << tt2str(type)
	          <<  "), found (\"" + m_current.token << "\", "
			  << tt2str(m_current.type) << ")" << std::endl;
	//*/
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
1 - ok			5 -	ok			9 -	ok				13 - ok				17 - ok
2 - ok			6 -	ok			10 - ok				14 - ok				18 - ok
3 - ok			7 -	ok			11 - ok				15 - ok				19 - ok
4 - ok			8 -	ok			12 - ok				16 - ok				20 - ok
*/



// // <program>   ::= program <id> ;
	//				[ const <const> { <const> } ]
	// 				[ var <var> { <var> } ]
	//				<block> '.'
// Command* SyntaticAnalysis::procProgram() {
void SyntaticAnalysis::procProgram() { // 1
	eat(TT_PROGRAM);
	procId();
	eat(TT_SEMICOLON);
	if (m_current.type == TT_CONST) {
		eat(TT_CONST);
		procConst();
		while (m_current.type == TT_ID) {
			procConst();
		}

	}
	if (m_current.type == TT_VAR) {
		eat(TT_VAR);
		procVar();
		while (m_current.type == TT_ID) {
			procVar();
		}
	}
	procBlock();
	eat(TT_DOT);
}

// // <const> ::= <id> '=' <value> ';'
// ConstIntExpr* SyntaticAnalysis::procConst() {
void SyntaticAnalysis::procConst() { // 2
	procId();
	eat(TT_EQUAL);
	procValue();
	eat(TT_SEMICOLON);
}

// // <var> ::= <id> { ',' <id> } [ '=' <value> ] ';'
// Variable* SyntaticAnalysis::procVar() {
void SyntaticAnalysis::procVar() { // 3
	procId();
	while (m_current.type == TT_COMMA) {
		eat(TT_COMMA);
		procId();
	}
	if (m_current.type == TT_EQUAL) {
		eat(TT_EQUAL);
		procValue();
	}
	eat(TT_SEMICOLON);
}

// //<body> ::= <block> | <cmd>
void SyntaticAnalysis::procBody() { // 4
	if (m_current.type == TT_BEGIN) {
		procBlock();
	} else if (m_current.type == TT_ID ||
					m_current.type == TT_IF ||
					m_current.type == TT_CASE ||
					m_current.type == TT_WHILE ||
					m_current.type == TT_FOR ||
					m_current.type == TT_REPEAT ||
					m_current.type == TT_WRITE ||
					m_current.type == TT_WRITELN ||
					m_current.type == TT_READLN) {
		procCmd();
	}
}

// //<block> ::= begin [ <cmd> { ';' <cmd> } ] end
void SyntaticAnalysis::procBlock() { // 5
	eat(TT_BEGIN);
	if (m_current.type == TT_ID ||
		m_current.type == TT_IF ||
		m_current.type == TT_CASE ||
		m_current.type == TT_WHILE ||
		m_current.type == TT_FOR ||
		m_current.type == TT_REPEAT ||
		m_current.type == TT_WRITE ||
		m_current.type == TT_WRITELN ||
		m_current.type == TT_READLN) {
		procCmd();
		while (m_current.type == TT_SEMICOLON) {
			eat(TT_SEMICOLON);
			procCmd();
		}
	}
	eat(TT_END);
}

// // <cmd> ::= <assign> | <if> | <case> | <while> | <for> | <repeat> | <write> | <read>
// Command* SyntaticAnalysis::procCmd() {
void SyntaticAnalysis::procCmd() { // 6
	if (m_current.type == TT_ID) {
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
	procId();
	eat(TT_ASSIGN);
	procExpr();
}

// // <if> ::= if <boolexpr> then <body> [ else <body> ]
// IfCommand* SyntaticAnalysis::procIf() {
void SyntaticAnalysis::procIf() { // 8
	eat(TT_IF);
	procBoolExpr();
	eat(TT_THEN);
	procBody();
	if (m_current.type == TT_ELSE) {
		eat(TT_ELSE);
		procBody();
	}
}

// //<case> ::= case <expr> of { <value> ':' <body> ';' } [ else <body> ';' ] end
void SyntaticAnalysis::procCase() { // 9
	eat(TT_CASE);
	procExpr();
	eat(TT_OF);
	while (m_current.type == TT_INTEGER ||
		m_current.type == TT_REAL ||
		m_current.type == TT_STRING){

		procValue();
		eat(TT_COLON);
		procBody();
		eat(TT_SEMICOLON);
	}
	if (m_current.type == TT_ELSE) {
		eat(TT_ELSE);
		procBody();
		eat(TT_SEMICOLON);
	}
	eat(TT_END);
}

// // <while> ::= while <boolexpr> do <body>
// WhileCommand* SyntaticAnalysis::procWhile() {
void SyntaticAnalysis::procWhile() { // 10
	eat(TT_WHILE);
	procBoolExpr();
	eat(TT_DO);
	procBody();
}

// // <repeat> ::= repeat [ <cmd> { ';' <cmd> } ] until <boolexpr>
void SyntaticAnalysis::procRepeat() { // 11
	eat(TT_REPEAT);
	if (m_current.type == TT_ID ||
		m_current.type == TT_IF ||
		m_current.type == TT_CASE ||
		m_current.type == TT_WHILE ||
		m_current.type == TT_FOR ||
		m_current.type == TT_REPEAT ||
		m_current.type == TT_WRITE ||
		m_current.type == TT_WRITELN ||
		m_current.type == TT_READLN) {
			procCmd();
			while (m_current.type == TT_SEMICOLON) {
				eat(TT_SEMICOLON);
				procCmd();
			}
	}
	eat(TT_UNTIL);
	procBoolExpr();
}

// // <for> ::= for <id> ':=' <expr> to <expr> do <body>
void SyntaticAnalysis::procFor() { // 12
	eat(TT_FOR);
	procId();
	eat(TT_ASSIGN);
	procExpr();
	eat(TT_TO);
	procExpr();
	eat(TT_DO);
	procBody();
}

// // <write> ::= (write | writeln) '(' [ <expr> { ',' <expr> } ] ')'
void SyntaticAnalysis::procWrite() { // 13
	if (m_current.type == TT_WRITE) {
		eat(TT_WRITE);
	} else if (m_current.type == TT_WRITELN) {
		eat(TT_WRITELN);
	} else {
		showError();
	}
	eat(TT_LEFT_PARENTHESES);
	if (m_current.type == TT_INTEGER ||
		m_current.type == TT_REAL ||
		m_current.type == TT_STRING ||
		m_current.type == TT_ID) {
		procExpr();
		while (m_current.type == TT_COMMA) {
			eat(TT_COMMA);
			procExpr();
		}
	}
	eat(TT_RIGHT_PARENTHESES);
}

// // <read> ::= readln '(' <id> { ',' <id> } ')'
void SyntaticAnalysis::procRead() { // 14
	eat(TT_READLN);
	eat(TT_LEFT_PARENTHESES);
	procId();
	while(m_current.type == TT_COMMA) {
		eat(TT_COMMA);
		procId();
	}
	eat(TT_RIGHT_PARENTHESES);
}

// // <boolexpr> ::= [ not ] <cmpexpr> [ (and | or) <boolexpr> ]
// BoolExpr* SyntaticAnalysis::procBoolExpr() {
void SyntaticAnalysis::procBoolExpr() { // 15
	if (m_current.type == TT_NOT) {
		eat(TT_NOT);
	}
	procCmpExpr();
	if (m_current.type == TT_AND || m_current.type == TT_OR) {
		if (m_current.type == TT_AND) {
			eat(TT_AND);
		} else if (m_current.type == TT_OR) {
			eat(TT_OR);
		} else {
			showError();
		}
		procBoolExpr();
	}
}

// // <cmpexpr> ::= <expr> ('=' | '<>' | '<' | '>' | '<=' | '>=') <expr>
void SyntaticAnalysis::procCmpExpr(){ // 16
	procExpr();
	if (m_current.type == TT_EQUAL) {
		eat(TT_EQUAL);
	} else if (m_current.type == TT_NOT_EQUAL) {
		eat(TT_NOT_EQUAL);
	} else if (m_current.type == TT_LOWER) {
		eat(TT_LOWER);
	} else if (m_current.type == TT_GREATER) {
		eat(TT_GREATER);
	} else if (m_current.type == TT_LOWER_EQUAL) {
		eat(TT_LOWER_EQUAL);
	} else if (m_current.type == TT_GREATER_EQUAL) {
		eat(TT_GREATER_EQUAL);
	} else {
		showError();
	}
	procExpr();
}

// // <expr> ::= <term> { ('+' | '-') <term> }
void SyntaticAnalysis::procExpr() { // 17
	procTerm();
	while (m_current.type == TT_ADD || m_current.type == TT_SUB) {
		if (m_current.type == TT_ADD) {
			eat(TT_ADD);
		} else if (m_current.type == TT_SUB) {
			eat(TT_SUB);
		} else {
			showError();
		}
		procTerm();
	}
}

// // <term> ::= <factor> { ('*' | '/' | '%') <factor> }
void SyntaticAnalysis::procTerm() { // 18
	procFactor();
	while (m_current.type == TT_MUL ||
			m_current.type == TT_DIV ||
			m_current.type == TT_MOD) {

		if (m_current.type == TT_MUL) {
			eat(TT_MUL);
		} else if (m_current.type == TT_DIV) {
			eat(TT_DIV);
		} else if (m_current.type == TT_MOD) {
			eat(TT_MOD);
		} else {
			showError();
		}
		procFactor();
	}
}

// // <factor> ::= <value> | <id> | '(' <expr> ')'
void SyntaticAnalysis::procFactor() { // 19
	if (m_current.type == TT_INTEGER ||
		m_current.type == TT_REAL ||
		m_current.type == TT_STRING) {
		procValue();
	} else if (m_current.type == TT_ID) {
		procId();
	} else if (m_current.type == TT_LEFT_PARENTHESES) {
		eat(TT_LEFT_PARENTHESES);
		procExpr();
		eat(TT_RIGHT_PARENTHESES);
	}
}

// // <value> ::= <integer> | <real> | <string>
// IntExpr* SyntaticAnalysis::procIntTerm() {
void SyntaticAnalysis::procValue() { // 20
	if (m_current.type == TT_INTEGER) {
		procInteger();
	} else if (m_current.type == TT_REAL) {
		procReal();
	} else if (m_current.type == TT_STRING) {
		procString();
	}
}

void SyntaticAnalysis::procId(){
	eat(TT_ID);
}
void SyntaticAnalysis::procInteger(){
	eat(TT_INTEGER);
}
void SyntaticAnalysis::procReal(){
	eat(TT_REAL);
}
void SyntaticAnalysis::procString(){
	eat(TT_STRING);
}
