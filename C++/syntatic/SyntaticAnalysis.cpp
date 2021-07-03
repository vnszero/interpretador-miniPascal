#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <string>

#include "SyntaticAnalysis.h"

#include "../interpreter/command/AssignCommand.h"
#include "../interpreter/command/BlocksCommand.h"
#include "../interpreter/command/CaseCommand.h"
#include "../interpreter/command/CaseOption.h"
#include "../interpreter/command/Command.h"
#include "../interpreter/command/ForCommand.h"
#include "../interpreter/command/IfCommand.h"
#include "../interpreter/command/ReadCommand.h"
#include "../interpreter/command/RepeatCommand.h"
#include "../interpreter/command/WhileCommand.h"
#include "../interpreter/command/WriteCommand.h"

#include "../interpreter/expr/BinaryExpr.h"
#include "../interpreter/expr/BoolExpr.h"
#include "../interpreter/expr/CompositeBoolExpr.h"
#include "../interpreter/expr/ConstExpr.h"
#include "../interpreter/expr/Expr.h"
#include "../interpreter/expr/NotBoolExpr.h"
#include "../interpreter/expr/SingleBoolExpr.h"
#include "../interpreter/expr/Variable.h"

#include "../interpreter/value/IntegerValue.h"
#include "../interpreter/value/RealValue.h"
#include "../interpreter/value/StringValue.h"

SyntaticAnalysis::SyntaticAnalysis(LexicalAnalysis& lex) :
	m_lex(lex), m_current(lex.nextToken()) {
}

SyntaticAnalysis::~SyntaticAnalysis() {
}

Command* SyntaticAnalysis::start() {
	Command* cmd = procProgram();
	eat(TT_END_OF_FILE);
	return cmd;
}

void SyntaticAnalysis::advance() {
	m_current = m_lex.nextToken();
}

void SyntaticAnalysis::eat(enum TokenType type) {
	/*
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
	<program> ::= program <id> ;
				[ const <const> { <const> } ]
				[ var <var> { <var> } ]
				<block> '.'
*/
BlocksCommand* SyntaticAnalysis::procProgram() {
	eat(TT_PROGRAM);
	eat(TT_ID);
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
	BlocksCommand* block = procBlock();
	eat(TT_DOT);
	return block;
}

// <const> ::= <id> '=' <value> ';'
void SyntaticAnalysis::procConst() {
	int line = m_lex.line();
	std::string name = m_current.token;
	eat(TT_ID);
	eat(TT_EQUAL);
	ConstExpr* expr = procValue();
	eat(TT_SEMICOLON);
	Variable* constant =  new Variable(line, name);
	constant->setValue(expr->expr(), true);
}

// <var> ::= <id> { ',' <id> } [ '=' <value> ] ';'
void SyntaticAnalysis::procVar() {
	int line = m_lex.line();
	std::string name = m_current.token;
	eat(TT_ID);
	Variable* var = new Variable(line, name);
	var->setValue();
	while (m_current.type == TT_COMMA) {
		line = m_lex.line();
		eat(TT_COMMA);
		name = m_current.token;
		eat(TT_ID);
		var = new Variable(line, name);
		var->setValue();
	}
	if (m_current.type == TT_EQUAL) {
		eat(TT_EQUAL);
		ConstExpr* expr = procValue();
		var->setValue(expr->expr());
	}
	eat(TT_SEMICOLON);
}

// <body> ::= <block> | <cmd>
Command* SyntaticAnalysis::procBody() {
	if (m_current.type == TT_BEGIN) {
		Command* block = (Command*) procBlock();
		return block;
	} else if (m_current.type == TT_ID ||
					m_current.type == TT_IF ||
					m_current.type == TT_CASE ||
					m_current.type == TT_WHILE ||
					m_current.type == TT_FOR ||
					m_current.type == TT_REPEAT ||
					m_current.type == TT_WRITE ||
					m_current.type == TT_WRITELN ||
					m_current.type == TT_READLN) {
		Command* cmd = procCmd();
		return cmd;
	}
	return 0;
}

// <block> ::= begin [ <cmd> { ';' <cmd> } ] end
BlocksCommand* SyntaticAnalysis::procBlock() {
	eat(TT_BEGIN);
	int line = m_lex.line();
	BlocksCommand* block = new BlocksCommand(line);
	if (m_current.type == TT_ID ||
		m_current.type == TT_IF ||
		m_current.type == TT_CASE ||
		m_current.type == TT_WHILE ||
		m_current.type == TT_FOR ||
		m_current.type == TT_REPEAT ||
		m_current.type == TT_WRITE ||
		m_current.type == TT_WRITELN ||
		m_current.type == TT_READLN) {

		Command* cmd = procCmd();
		block->addCommand(cmd);
		while (m_current.type == TT_SEMICOLON) {
			eat(TT_SEMICOLON);
			cmd = procCmd();
			if(cmd!=0){
				block->addCommand(cmd);
			} else {
				showError(); //; antes do end
			}
		}
	}
	eat(TT_END);
	return block;
}

// <cmd> ::= <assign> | <if> | <case> | <while> | <for> | <repeat> | <write> | <read>
Command* SyntaticAnalysis::procCmd() {
	Command* cmd = 0;
	if (m_current.type == TT_ID) {
		cmd = procAssign();
	} else if (m_current.type == TT_IF) {
		cmd = procIf();
	} else if (m_current.type == TT_CASE) {
		cmd = procCase();
	} else if (m_current.type == TT_WHILE) {
		cmd = procWhile();
	} else if (m_current.type == TT_FOR) {
		cmd = procFor();
	} else if (m_current.type == TT_REPEAT) {
		cmd = procRepeat();
	} else if (m_current.type == TT_WRITE || m_current.type == TT_WRITELN) {
		cmd = procWrite();
	} else if (m_current.type == TT_READLN) {
		cmd = procRead();
	}
	return cmd;
}

// <assign> ::= <id> ':=' <expr>
AssignCommand* SyntaticAnalysis::procAssign() {
	int line = m_lex.line();
	Variable* var = procId();
	eat(TT_ASSIGN);
	Expr* expr = procExpr();
	AssignCommand* cmd = new AssignCommand(line, var, expr);
	return cmd;
}

// <if> ::= if <boolexpr> then <body> [ else <body> ]
IfCommand* SyntaticAnalysis::procIf() {
	int line = m_lex.line();
	eat(TT_IF);
	BoolExpr* cond = procBoolExpr();
	eat(TT_THEN);
	Command* thenCmds = procBody();
	IfCommand* cmd = new IfCommand(line, cond, thenCmds);
	if (m_current.type == TT_ELSE) {
		eat(TT_ELSE);
		Command* elseCmds = procBody();
		cmd->ElseCommands(elseCmds);
	}
	return cmd;
}

// <case> ::= case <expr> of { <value> ':' <body> ';' } [ else <body> ';' ] end
CaseCommand* SyntaticAnalysis::procCase() {
	int line = m_lex.line();
	eat(TT_CASE);
	Expr* expr = procExpr();
	eat(TT_OF);
	CaseCommand* cmd = new CaseCommand(line, expr);
	while (m_current.type == TT_INTEGER ||
		m_current.type == TT_REAL ||
		m_current.type == TT_STRING){

		ConstExpr* cexpr = procValue();
		eat(TT_COLON);
		Command* cmds = procBody();
		eat(TT_SEMICOLON);
		Type* value = cexpr->expr();
		cmd->addOption(value, cmds);
	}
	if (m_current.type == TT_ELSE) {
		eat(TT_ELSE);
		Command* cmds = procBody();
		eat(TT_SEMICOLON);
		cmd->setOtherwise(cmds);
	}
	eat(TT_END);
	return cmd;
}

// <while> ::= while <boolexpr> do <body>
WhileCommand* SyntaticAnalysis::procWhile() {
	eat(TT_WHILE);
	int line = m_lex.line();
	BoolExpr* cond = procBoolExpr();
	eat(TT_DO);
	Command* cmds = procBody();
	WhileCommand* cmd = new WhileCommand(line, cond, cmds);
	return cmd;
}

// <repeat> ::= repeat [ <cmd> { ';' <cmd> } ] until <boolexpr>
RepeatCommand* SyntaticAnalysis::procRepeat() {
	eat(TT_REPEAT);
	int line = m_lex.line();
	std::list<Command*> cmds;
	if (m_current.type == TT_ID ||
		m_current.type == TT_IF ||
		m_current.type == TT_CASE ||
		m_current.type == TT_WHILE ||
		m_current.type == TT_FOR ||
		m_current.type == TT_REPEAT ||
		m_current.type == TT_WRITE ||
		m_current.type == TT_WRITELN ||
		m_current.type == TT_READLN) {

			Command* cmd = procCmd();
			cmds.push_back(cmd);
			while (m_current.type == TT_SEMICOLON) {
				eat(TT_SEMICOLON);
				cmd = procCmd();
				cmds.push_back(cmd);
			}
	}
	eat(TT_UNTIL);
	BoolExpr* cond = procBoolExpr();
	RepeatCommand* rcmd = new RepeatCommand(line, cmds, cond);
	return rcmd;
}

// <for> ::= for <id> ':=' <expr> to <expr> do <body>
ForCommand* SyntaticAnalysis::procFor() {
	eat(TT_FOR);
	int line = m_lex.line();
	Variable* var = procId();
	eat(TT_ASSIGN);
	Expr* src = procExpr();
	eat(TT_TO);
	Expr* dst = procExpr();
	eat(TT_DO);
	Command* cmds = procBody();
	ForCommand* cmd = new ForCommand(line, var, src, dst, cmds);
	return cmd;
}

// <write> ::= (write | writeln) '(' [ <expr> { ',' <expr> } ] ')'
WriteCommand* SyntaticAnalysis::procWrite() {
	int line = m_lex.line();
	bool writeln = false;
	if (m_current.type == TT_WRITE) {
		eat(TT_WRITE);
	} else if (m_current.type == TT_WRITELN) {
		eat(TT_WRITELN);
		writeln = true;
	} else {
		showError();
	}
	eat(TT_LEFT_PARENTHESES);
	WriteCommand* cmd = new WriteCommand(line, writeln);
	if (m_current.type == TT_INTEGER ||
		m_current.type == TT_REAL ||
		m_current.type == TT_STRING ||
		m_current.type == TT_ID) {

		Expr* expr = procExpr();
		cmd->addExpr(expr);
		while (m_current.type == TT_COMMA) {
			eat(TT_COMMA);
			expr = procExpr();
			cmd->addExpr(expr);
		}
	}
	eat(TT_RIGHT_PARENTHESES);
	return cmd;
}

// <read> ::= readln '(' <id> { ',' <id> } ')'
ReadCommand* SyntaticAnalysis::procRead() {
	int line = m_lex.line();
	eat(TT_READLN);
	ReadCommand* cmd = new ReadCommand(line);
	eat(TT_LEFT_PARENTHESES);
	Variable* var = procId();
	cmd->addVariable(var);
	while(m_current.type == TT_COMMA) {
		eat(TT_COMMA);
		Variable* var = procId();
		cmd->addVariable(var);
	}
	eat(TT_RIGHT_PARENTHESES);
	return cmd;
}

// <boolexpr> ::= [ not ] <cmpexpr> [ (and | or) <boolexpr> ]
BoolExpr* SyntaticAnalysis::procBoolExpr() {
	int line = m_lex.line();
	bool flag = false;
	if (m_current.type == TT_NOT) {
		eat(TT_NOT);
		flag = true;
	}
	BoolExpr* left = procCmpExpr();
	if (flag == true) {
		NotBoolExpr* notcmp = new NotBoolExpr(line, left);
		left = (BoolExpr*) notcmp;
	}
	if (m_current.type == TT_AND || m_current.type == TT_OR) {
		CompositeBoolExpr::BoolOp op;
		if (m_current.type == TT_AND) {
			eat(TT_AND);
			op = CompositeBoolExpr::AND;
		} else if (m_current.type == TT_OR) {
			eat(TT_OR);
			op = CompositeBoolExpr::OR;
		} else {
			showError();
		}
		BoolExpr* right = procBoolExpr();
		CompositeBoolExpr* composite = new CompositeBoolExpr(line, left, op, right);
		left = (BoolExpr*) composite;
	}
	return left;
}

// <cmpexpr> ::= <expr> ('=' | '<>' | '<' | '>' | '<=' | '>=') <expr>
SingleBoolExpr* SyntaticAnalysis::procCmpExpr() {
	int line = m_lex.line();
	Expr* left = procExpr();
	SingleBoolExpr::RelOp op;
	if (m_current.type == TT_EQUAL) {
		eat(TT_EQUAL);
		op = SingleBoolExpr::EQUAL;
	} else if (m_current.type == TT_NOT_EQUAL) {
		eat(TT_NOT_EQUAL);
		op = SingleBoolExpr::NOT_EQUAL;
	} else if (m_current.type == TT_LOWER) {
		eat(TT_LOWER);
		op = SingleBoolExpr::LOWER_THAN;
	} else if (m_current.type == TT_GREATER) {
		eat(TT_GREATER);
		op = SingleBoolExpr::GREATER_THAN;
	} else if (m_current.type == TT_LOWER_EQUAL) {
		eat(TT_LOWER_EQUAL);
		op = SingleBoolExpr::LOWER_EQUAL;
	} else if (m_current.type == TT_GREATER_EQUAL) {
		eat(TT_GREATER_EQUAL);
		op = SingleBoolExpr::GREATER_EQUAL;
	} else {
		showError();
	}
	Expr* right = procExpr();
	SingleBoolExpr* expr = new SingleBoolExpr(line, left, op, right);
	return expr;
}

// <expr> ::= <term> { ('+' | '-') <term> }
Expr* SyntaticAnalysis::procExpr() {
	int line = m_lex.line();
	Expr* left = procTerm();
	while (m_current.type == TT_ADD || m_current.type == TT_SUB) {
		BinaryExpr::BinaryOp op;
		if (m_current.type == TT_ADD) {
			eat(TT_ADD);
			op = BinaryExpr::ADD_OP;
		} else if (m_current.type == TT_SUB) {
			eat(TT_SUB);
			op = BinaryExpr::SUB_OP;
		} else {
			showError();
		}
		Expr* right = procTerm();
		BinaryExpr* bExpr = new BinaryExpr(line, left, op, right);
		left = (Expr*) bExpr;
	}
	return left;
}

// <term> ::= <factor> { ('*' | '/' | '%') <factor> }
Expr* SyntaticAnalysis::procTerm() {
	int line = m_lex.line();
	Expr* left = procFactor();
	while (m_current.type == TT_MUL ||
			m_current.type == TT_DIV ||
			m_current.type == TT_MOD) {

		BinaryExpr::BinaryOp op;
		if (m_current.type == TT_MUL) {
			eat(TT_MUL);
			op = BinaryExpr::MUL_OP;
		} else if (m_current.type == TT_DIV) {
			eat(TT_DIV);
			op = BinaryExpr::DIV_OP;
		} else if (m_current.type == TT_MOD) {
			eat(TT_MOD);
			op = BinaryExpr::MOD_OP;
		} else {
			showError();
		}
		Expr* right = procFactor();
		BinaryExpr* bExpr = new BinaryExpr(line, left, op, right);
		left = (Expr*) bExpr;
	}
	return left;
}

// <factor> ::= <value> | <id> | '(' <expr> ')'
Expr* SyntaticAnalysis::procFactor() {
	Expr* expr = 0;
	if (m_current.type == TT_INTEGER ||
		m_current.type == TT_REAL ||
		m_current.type == TT_STRING) {
		expr = procValue();
	} else if (m_current.type == TT_ID) {
		expr = procId();
	} else if (m_current.type == TT_LEFT_PARENTHESES) {
		eat(TT_LEFT_PARENTHESES);
		expr = procExpr();
		eat(TT_RIGHT_PARENTHESES);
	}
	return expr;
}

// <value> ::= <integer> | <real> | <string>
ConstExpr* SyntaticAnalysis::procValue() {
	int line = m_lex.line();
	Type* value = 0;
	if (m_current.type == TT_INTEGER) {
		value = procInteger();
	} else if (m_current.type == TT_REAL) {
		value = procReal();
	} else if (m_current.type == TT_STRING) {
		value = procString();
	}
	ConstExpr* expr = new ConstExpr(line, value);
	return expr;
}

Variable* SyntaticAnalysis::procId() {
	int line = m_lex.line();
	std::string name = m_current.token;
	eat(TT_ID);
	Variable* id = new Variable(line, name);
	id->expr();	//essa chamadda verifica se a variavel existe na memoria
	return id;
}

IntegerValue* SyntaticAnalysis::procInteger() {
	std::string tmp = m_current.token;
	eat(TT_INTEGER);
	int value = atoi(tmp.c_str());
	IntegerValue* iv = new IntegerValue(value);
	return iv;
}

RealValue* SyntaticAnalysis::procReal() {
	std::string tmp = m_current.token;
	eat(TT_REAL);
	double value = atof(tmp.c_str());
	RealValue* rv = new RealValue(value);
	return rv;
}
StringValue* SyntaticAnalysis::procString() {
	std::string value =  m_current.token;
	eat(TT_STRING);
	StringValue* sv = new StringValue(value);
	return sv;
}
