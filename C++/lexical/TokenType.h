//falta apagar comentarios

#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H

#include <string>

enum TokenType {
	// Specials
	TT_UNEXPECTED_EOF = -2,
	TT_INVALID_TOKEN  = -1,
	TT_END_OF_FILE    =  0,

	// Symbols
	TT_SEMICOLON,    	 	// ;				ok
	TT_ASSIGN,        		// :=/= 			- modified
	TT_DOT, 		  		// .				- new
	TT_COLON,      	  		// : 				- new
	TT_COMMA,				// ,				- new
	TT_LEFT_PARENTHESES,	// (				- new
	TT_RIGHT_PARENTHESES,	// )				- new

	// Logic operators
	TT_EQUAL,         // = 				- modified
	TT_NOT_EQUAL,     // <> 			- modified
	TT_LOWER,         // < 				ok
	TT_LOWER_EQUAL,   // <= 			ok
	TT_GREATER,       // > 				ok
	TT_GREATER_EQUAL, // >=				ok

	// Arithmetic operators
	TT_ADD,           // + 				ok
	TT_SUB,           // - 				ok
	TT_MUL,           // * 				ok
	TT_DIV,           // / 				ok
	TT_MOD,           // % 				ok

	// Keywords
	TT_PROGRAM,       // program 		ok
	TT_WHILE,         // while 			ok
	TT_DO,            // do
	//TT_DONE,          // done			- no longer a token
	TT_IF,            // if				ok
	TT_THEN,          // then			ok
	TT_ELSE,          // else			ok
	//TT_OUTPUT,        // output 		- no longer a token
	//TT_TRUE,          // true			- no longer a token
	//TT_FALSE,         // false		- no longer a token
	//TT_READ			// read			- no longer a token
	TT_NOT,           // not 			ok
	TT_AND,		 	  // and 			- new
	TT_OR, 			  // or 			- new
	TT_READLN,        // readln 		- new
	TT_WRITE,	  	  // write 			- new
	TT_WRITELN,		  // writeln		- new
	TT_REPEAT,		  // repeat 		- new
	TT_UNTIL, 		  // until			- new
	TT_BEGIN,		  // begin			- new
	TT_END,			  //end 			- new
	TT_CASE,		  //case			- new
	TT_OF,			  //of				- new
	TT_FOR,			  //for				- new
	TT_TO, 			  //to				- new 18

	// Others
	//TT_NUMBER,      // number			- no longer a token
	TT_VAR,           // var			ok
	TT_CONST,		  // const 			new
	TT_ID,
	TT_INTEGER,		  // integer		new
	TT_REAL,		  // real 			new
	TT_STRING		  // string			new
};

inline std::string tt2str(enum TokenType type) {
	switch (type) {
		// Specials
		case TT_UNEXPECTED_EOF:
			return "UNEXPECTED_EOF";
		case TT_INVALID_TOKEN:
			return "INVALID_TOKEN";
		case TT_END_OF_FILE:
			return "END_OF_FILE";

		// Symbols
		case TT_SEMICOLON:
			return "SEMICOLON";
		case TT_ASSIGN:
			return "ASSIGN";				//modified
		case TT_DOT:
			return "DOT";					//new
		case TT_COLON:
			return "COLON";      	  		//new
		case TT_COMMA:
			return "COMMA";					//new
		case TT_LEFT_PARENTHESES:
			return "LEFT_PARENTHESES";		//new
		case TT_RIGHT_PARENTHESES:
			return "RIGHT_PARENTHESES";		//new

		// Logic operators
		case TT_EQUAL:
			return "EQUAL";					//modified
		case TT_NOT_EQUAL:
			return "NOT_EQUAL";				//modified
		case TT_LOWER:
			return "LOWER";
		case TT_LOWER_EQUAL:
			return "LOWER_EQUAL";
		case TT_GREATER:
			return "GREATER";
		case TT_GREATER_EQUAL:
			return "GREATER_EQUAL";

		// Arithmetic operators
		case TT_ADD:
			return "ADD";
		case TT_SUB:
			return "SUB";
		case TT_MUL:
			return "MUL";
		case TT_DIV:
			return "DIV";
		case TT_MOD:
			return "MOD";

		// Keywords
		case TT_PROGRAM:
			return "PROGRAM";
		case TT_WHILE:
			return "WHILE";
		case TT_DO:
			return "DO";
		case TT_IF:
			return "IF";
		case TT_THEN:
			return "THEN";
		case TT_ELSE:
			return "ELSE";
		case TT_NOT:
			return "NOT";
		case TT_AND:
			return "AND";			//new
		case TT_OR:
			return "OR";			//new
		case TT_READLN:
			return "READLN";		//new
		case TT_WRITE:
			return "WRITE";			//new
		case TT_WRITELN:
			return "WRITELN";		//new
		case TT_REPEAT:
			return "REPEAT";		//new
		case TT_UNTIL:
			return "UNTIL";			//new
		case TT_BEGIN:
			return "BEGIN";			//new
		case TT_END:
			return "END";			//new
		case TT_CASE:
			return "CASE";			//new
		case TT_OF:
			return "OF";			//new
		case TT_FOR:
			return "FOR";			//new
		case TT_TO:
			return "TO";			//new 18

		// Others
		case TT_VAR:
			return "VAR";
		case TT_CONST:
			return "CONST";			//new
		case TT_INTEGER:
			return "INTEGER";		//new
		case TT_REAL:
			return "REAL";			//new
		case TT_ID:
			return "ID";
		case TT_STRING:
			return "STRING";		//new

		default:
			throw std::string("invalid token type");
	}
}
#endif
