#include "IfCommand.h"


IfCommand::IfCommand(int line, BoolExpr* cond, Command* thenCmds, Command* elseCmds)
	: Command(line), m_cond(cond), m_thenCmds(thenCmds), m_elseCmds(elseCmds) {
}

IfCommand::~IfCommand() {
	delete m_cond;
	delete m_thenCmds;
	if (m_elseCmds)
		delete m_elseCmds;
}

void IfCommand::ElseCommands(Command* elseCmds){
	m_elseCmds = elseCmds;
}

void IfCommand::execute() {
	if (m_cond->expr())
		m_thenCmds->execute();
	else {
		if (m_elseCmds != 0)
			m_elseCmds->execute();
	}
}
