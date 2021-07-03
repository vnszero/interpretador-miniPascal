#include "WriteCommand.h"

WriteCommand::WriteCommand(int line, bool writeln)
	: Command(line), m_writeln(writeln) {
}

WriteCommand::~WriteCommand() {
}

void WriteCommand::addExpr(Expr* expr) {
	 m_exprs.push_back(expr);
}

void WriteCommand::execute() {
	for (std::list<Expr*>::iterator it = m_exprs.begin(),
	    	 ed = m_exprs.end(); it != ed; it++) {
			Expr* expr = *it;
			Type* type = expr->expr();
			if (type->type() == Type::IntegerType) {
				IntegerValue* iv = (IntegerValue*) type;
				int tmp = iv->value();
				std::cout << tmp << " ";
			} else if (type->type() == Type::RealType) {
				RealValue* rv = (RealValue*) type;
				double tmp = rv->value();
				std::cout << tmp << " ";
			} else {
				StringValue* sv = (StringValue*) type;
				std::string tmp = sv->value();
				std::cout << tmp << " ";
			}
		}
	if (m_writeln) {
		std::cout << std::endl;
	}
}


