#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H

#include <string>

enum TokenType {
	// Specials
	TT_UNEXPECTED_EOF = -2,
	TT_INVALID_TOKEN  = -1,
	TT_END_OF_FILE    =  0,

	// Symbols
	TT_SEMICOLON,    	 	// ;
	TT_ASSIGN,        		// :=/=
	TT_DOT, 		  		// .
	TT_COLON,      	  		// :
	TT_COMMA,				// ,
	TT_LEFT_PARENTHESES,	// (
	TT_RIGHT_PARENTHESES,	// )

	// Logic operators
	TT_EQUAL,         // =
	TT_NOT_EQUAL,     // <>
	TT_LOWER,         // <
	TT_LOWER_EQUAL,   // <=
	TT_GREATER,       // >
	TT_GREATER_EQUAL, // >=

	// Arithmetic operators
	TT_ADD,           // +
	TT_SUB,           // -
	TT_MUL,           // *
	TT_DIV,           // /
	TT_MOD,           // %

	// Keywords
	TT_PROGRAM,       // program
	TT_WHILE,         // while
	TT_DO,            // do
	TT_IF,            // if
	TT_THEN,          // then
	TT_ELSE,          // else
	TT_NOT,           // not
	TT_AND,		 	  // and
	TT_OR, 			  // or
	TT_READLN,        // readln
	TT_WRITE,	  	  // write
	TT_WRITELN,		  // writeln
	TT_REPEAT,		  // repeat
	TT_UNTIL, 		  // until
	TT_BEGIN,		  // begin
	TT_END,			  //end
	TT_CASE,		  //case
	TT_OF,			  //of
	TT_FOR,			  //for
	TT_TO, 			  //to
	TT_VAR,           // var
	TT_CONST,		  // const

	// Others
	TT_ID,
	TT_INTEGER,		  // integer
	TT_REAL,		  // real
	TT_STRING		  // string
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
			return "ASSIGN";
		case TT_DOT:
			return "DOT";
		case TT_COLON:
			return "COLON";
		case TT_COMMA:
			return "COMMA";
		case TT_LEFT_PARENTHESES:
			return "LEFT_PARENTHESES";
		case TT_RIGHT_PARENTHESES:
			return "RIGHT_PARENTHESES";

		// Logic operators
		case TT_EQUAL:
			return "EQUAL";
		case TT_NOT_EQUAL:
			return "NOT_EQUAL";
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
			return "AND";
		case TT_OR:
			return "OR";
		case TT_READLN:
			return "READLN";
		case TT_WRITE:
			return "WRITE";
		case TT_WRITELN:
			return "WRITELN";
		case TT_REPEAT:
			return "REPEAT";
		case TT_UNTIL:
			return "UNTIL";
		case TT_BEGIN:
			return "BEGIN";
		case TT_END:
			return "END";
		case TT_CASE:
			return "CASE";
		case TT_OF:
			return "OF";
		case TT_FOR:
			return "FOR";
		case TT_TO:
			return "TO";
		case TT_VAR:
			return "VAR";
		case TT_CONST:
			return "CONST";

		// Others
		case TT_ID:
			return "ID";
		case TT_INTEGER:
			return "INTEGER";
		case TT_REAL:
			return "REAL";
		case TT_STRING:
			return "STRING";

		default:
			throw std::string("invalid token type");
	}
}
#endif
