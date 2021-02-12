//falta apagar comentario

#include "SymbolTable.h"

SymbolTable::SymbolTable() {
	// Symbols
	m_symbols[";"] = TT_SEMICOLON;
	m_symbols[":="] = TT_ASSIGN;			//modified???
	m_symbols["."] = TT_DOT;				//new
	m_symbols[":"] = TT_COLON;      	  	//new
	m_symbols[","] = TT_COMMA;				//new
	m_symbols["("] = TT_LEFT_PARENTHESES;	//new
	m_symbols[")"] = TT_RIGHT_PARENTHESES;	//new

	// Logic operators
	m_symbols["="] = TT_EQUAL;				//modified
	m_symbols["<>"] = TT_NOT_EQUAL;			//modified
	m_symbols["<"] = TT_LOWER;
	m_symbols["<="] = TT_LOWER_EQUAL;
	m_symbols[">"] = TT_GREATER;
	m_symbols[">="] = TT_GREATER_EQUAL;

	// Arithmetic operators
	m_symbols["+"] = TT_ADD;
	m_symbols["-"] = TT_SUB;
	m_symbols["*"] = TT_MUL;
	m_symbols["/"] = TT_DIV;
	m_symbols["%"] = TT_MOD;

	// Keywords
	m_symbols["program"] = TT_PROGRAM;
	m_symbols["while"] = TT_WHILE;
	m_symbols["do"] = TT_DO;
	//m_symbols["done"] = TT_DONE;			//no longer a token
	m_symbols["if"] = TT_IF;
	m_symbols["then"] = TT_THEN;
	m_symbols["else"] = TT_ELSE;
	//m_symbols["output"] = TT_OUTPUT;		//no longer a token
	//m_symbols["true"] = TT_TRUE;			//no longer a token
	//m_symbols["false"] = TT_FALSE;		//no longer a token
	//m_symbols["read"] = TT_READ;			//no longer a token
	m_symbols["not"] = TT_NOT;
	m_symbols["and"] = TT_AND;		 	   			// new
	m_symbols["or"] = TT_OR; 			   			// new
	m_symbols["readln"] = TT_READLN;         		// new
	m_symbols["write"] = TT_WRITE;	  	   	 		// new
	m_symbols["writeln"] = TT_WRITELN;				// new
	m_symbols["repeat"] = TT_REPEAT;		   		// new
	m_symbols["until"] = TT_UNTIL; 		  			//new
	m_symbols["begin"] = TT_BEGIN;		  			//new
	m_symbols["end"] = TT_END;			  			//new
	m_symbols["case"] = TT_CASE;		  			//new
	m_symbols["of"] = TT_OF;			  			//new
	m_symbols["for"] = TT_FOR;						//new
	m_symbols["to"] = TT_TO;						//new 18
	m_symbols["var"] = TT_VAR;
	m_symbols["const"] = TT_CONST;
}

SymbolTable::~SymbolTable() {
}

bool SymbolTable::contains(const std::string& token) const {
	return m_symbols.find(token) != m_symbols.end();
}

enum TokenType SymbolTable::find(const std::string& token) {
	return this->contains(token) ?
				m_symbols[token] : TT_ID;
}
