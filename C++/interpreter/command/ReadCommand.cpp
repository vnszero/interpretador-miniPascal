#include "ReadCommand.h"


ReadCommand::ReadCommand(int line)
	: Command(line) {
}

ReadCommand::~ReadCommand() {
}

void ReadCommand::addVariable(Variable* var) {
	m_vars.push_back(var);
}

void ReadCommand::execute() {

	for (std::list<Variable*>::iterator it = m_vars.begin(),
	     ed = m_vars.end(); it != ed; it++) {

		Variable* var = *it;
		std::string value;
		std::cin >> value;

		bool is_n_int = false;
		char type_discover = 's'; //'s' string, 'i' integer, 'f' real
		int letra_anterior = 65;
		int letra_atual = 65;
		for(std::string::iterator letra = value.begin(),
			fim = value.end(); letra != fim; letra++){

			letra_atual = (int) *letra;
			if(letra_atual == '.' && isdigit(letra_anterior)) {
				type_discover = 'f';
				is_n_int = true;
			} else if (isalpha(letra_atual) || letra_atual == '\'') {
				is_n_int = true;
				type_discover = 's';
			} else if (isdigit(letra_atual) && is_n_int == false) {
				type_discover = 'i';
			}
			letra_anterior = letra_atual;
		}
		if (type_discover == 'f') {
			double double_value = atof(value.c_str());
			RealValue* rv = new RealValue(double_value);
			var->setValue(rv);
		} else if (type_discover == 'i') {
			int integer_value = atoi(value.c_str());
			IntegerValue* iv = new IntegerValue(integer_value);
			var->setValue(iv);
		} else {
			int qtd = strlen(value.c_str());
			if (value[qtd-1] == ('\'')){
				value[qtd-1] = '\0';
			}
			if (value[0] == ('\'')) {
				value.erase(0, value.find_first_not_of("\'"));
			}
			StringValue* sv = new StringValue(value);
			var->setValue(sv);
		}
	}
}
