#include "AssignCommand.h"

AssignCommand::AssignCommand(int line, Variable* left, Expr* right)
	: Command(line), m_left(left), m_right(right) {
}

AssignCommand::~AssignCommand() {
	delete m_left;
	delete m_right;
}

void AssignCommand::execute() {
	Type* value = m_right->expr();
	m_left->setValue(value);
}
