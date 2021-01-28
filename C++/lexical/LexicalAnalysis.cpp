//arquivo pendente de revisao
#include <iostream>

#include <string>
#include <cctype>
#include "LexicalAnalysis.h"

LexicalAnalysis::LexicalAnalysis(const char* filename) : m_line(1) {
	m_input = fopen(filename, "r");
}

LexicalAnalysis::~LexicalAnalysis() {
	if (m_input != nullptr)
		fclose(m_input);
}

Lexeme LexicalAnalysis::nextToken() {
	int state;
	Lexeme lex;

	state = 1;
	while (state != 12 && state != 13) {
		int c = fgetc(m_input);

		/*
		std::cout << "[" << state << ", " << c
		           << " ('" << (char) c << "')]" << std::endl;
		//*/

		switch (state) {
			case 1: //pronto
				if (c == ' ' || c == '\t' || c == '\r') {
					state = 1;
				} else if (c == '\n') {
					m_line++; //\n exige atualizacao do numero da linha
					state = 1;
				} else if (c == '(') {
					lex.token = (char) c; //pode nao ser comentario
					state = 2;
				} else if (c == '<'){
					lex.token = (char) c;
					state = 5;
				} else if (c == '>'){
					lex.token = (char) c;
					state = 6;
				} else if (c ==':'){
					lex.token = (char) c;
					state = 7;
				} else if (c == '_' || isalpha(c)) {
					lex.token += (char) c;
					state = 8;
				} else if (isdigit(c)) {
					lex.token += (char) c;
					state = 9;
				} else if (c == '\''){
					lex.token += (char) c;
					state = 11;
				} else if (c == '.' || c == ',' || c == ';' ||
						c == '=' || c == '+' || c == '-' ||
						c == '*' || c == '/' || c == '%' || c == ')') { //ok
					lex.token += (char) c;
					state = 12;
				} else {
					if (c == -1) {
						lex.type = TT_END_OF_FILE;
						state = 13;
					} else {
						lex.token += (char) c;
						lex.type = TT_INVALID_TOKEN;
						state = 13;
					}
				}
				break;
			case 2: //ok
				if (c == '*') {
					lex.token = ""; //limpar '(' do lex.token
					state = 3; //comentario
				} else {
					if (c != -1)
						ungetc(c, m_input); //1st

					state = 12;
				}
				break;
			case 3: //ok
				if (c == '*') {
					state = 4;
				} else if (c == '\n'){
					m_line++;
					state = 3;
				} else if (c == -1) {
					lex.type = TT_END_OF_FILE;
					state = 13;
				} else {
					state = 3;
				}
				break;
			case 4: //ok
				if (c == ')') {
					state = 1;
				} else if (c == '*'){
					state = 4;
				} else if (c == '\n'){
					m_line++;
					state = 3;
				} else if (c == -1) {
					lex.type = TT_END_OF_FILE;
					state = 13;
				} else {
					state = 3;
				}
				break;
			case 5: //ok
				if (c == '>' || c == '=') {
					lex.token += (char) c;
					state = 12;
				} else {
					if (c != -1)
						ungetc(c, m_input); //2nd

					state = 12;
				}
				break;
			case 6: //ok
				if (c == '=') {
					lex.token += (char) c;
					state = 12;
				} else {
					if (c != -1)
						ungetc(c, m_input); //3rd

					state = 12;
				}
				break;
			case 7: //atribuicao
				if (c == '='){
					lex.token += (char) c;
					state = 12;
				}else{
					if (c != -1)
						ungetc(c, m_input); //4th

					state = 12;
				}
				break;
			case 8: //ok
				if (c == '_' || isalpha(c) || isdigit(c)) {
					lex.token += (char) c;
					state = 8;
				} else {
					if (c != -1)
						ungetc(c, m_input); //5th

					state = 12;
				}
				break;
			case 9: //int
				if (isdigit(c)) {
					lex.token += (char) c;
					state = 9;
				} else if (c == '.'){
					lex.token += (char) c;
					state = 10;
				} else {
					if (c != -1)
						ungetc(c, m_input); //6th

					lex.type = TT_INTEGER;
					state = 13;
				}
				break;
			case 10: //real
				if (isdigit(c)) {
					lex.token += (char) c;
					state = 10;
				} else {
					if (c != -1)
						ungetc(c, m_input); //7th

					lex.type = TT_REAL;
					state = 13;
				}
				break;
			case 11: //string pronto
				if (c != '\''){
					if (c == -1) {
						lex.type = TT_UNEXPECTED_EOF;
						state = 13;
					} else {
						lex.token += (char) c;
						state = 11;
					}
				} else {
					lex.token += (char) c; //fechando a string
					lex.type = TT_STRING;
					state = 13;
				}
				break;
			default:
				throw std::string("invalid state");
		}
	}

	if (state == 12)
		lex.type = m_st.find(lex.token);

	return lex;
}
