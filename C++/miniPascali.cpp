#include <iostream>
#include <stdlib.h>
#include "lexical/LexicalAnalysis.h"

int main(int argc, char* argv[]){
    if(argc != 2){
        printf("Usage: %s [miniPascal program]\n", argv[0]);
        exit(1);
    }

	try{
		Lexeme lex;
		LexicalAnalysis l(argv[1]);

		while ((lex = l.nextToken()).type > 0){
			std::cout << lex.str() << std::endl;
		}

		std::cout << lex.str() << std::endl;
	} catch (const std::string& error) {
		std::cerr << error << std::endl;
	}
    return 0;
}
