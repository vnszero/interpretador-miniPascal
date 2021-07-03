#include "Variable.h"


Variable::Variable(int line, const std::string& name)
	: Expr(line), m_name(name) {
}

Variable::~Variable() {
}

Type* Variable::expr() {
	try{
		return Memory::read(m_name);
	} catch(const std::string& error) {
		std::cout << std::setw(2) << std::setfill('0') << line() << ": ";
		std::cerr << "Variable '" << m_name << "' " << error << std::endl;
		exit(1);
		return NULL;
	}
}

void Variable::setValue(Type* value, bool flag) {
	try{
		Memory::write(m_name, value, flag);
	} catch(const std::string& error) {
		std::cout << std::setw(2) << std::setfill('0') << line() << ": ";
		std::cerr << "Constant '" << m_name << "' " << error << std::endl;
		exit(1);
	}
}
