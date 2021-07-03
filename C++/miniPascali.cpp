#include <iostream>
#include <stdlib.h>
#include "lexical/LexicalAnalysis.h"
#include "syntatic/SyntaticAnalysis.h"
#include "interpreter/command/Command.h"

int main(int argc, char* argv[]){
    if(argc != 2){
        printf("Usage: %s [miniPascal program]\n", argv[0]);
        exit(1);
    }

	try{
		Lexeme lex;
		LexicalAnalysis l(argv[1]);
		///*
		SyntaticAnalysis s(l);
		Command* cmd = s.start();
		cmd->execute();
		//*/

		/* turn /* into a line comment by add an /, comment cmd->execute() and watch it works
		while ((lex = l.nextToken()).type > 0){
			std::cout << lex.str() << std::endl;
		}
		std::cout << lex.str() << std::endl;

		// I used this to simulate the tokens consumption
		//*/

	} catch (const std::string& error) {
		std::cerr << error << std::endl;
	}
    return 0;
}
