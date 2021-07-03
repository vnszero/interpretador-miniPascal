#include "RepeatCommand.h"

RepeatCommand::RepeatCommand(int line, std::list<Command*> cmds, BoolExpr* cond)
	: Command(line), m_cmds(cmds), m_cond(cond) {
}

RepeatCommand::~RepeatCommand() {
	delete m_cond;
}

void RepeatCommand::execute() {
	do {
		for (std::list<Command*>::iterator it = m_cmds.begin(),
	     ed = m_cmds.end(); it != ed; it++) {
			Command* cmd = *it;
			cmd->execute();
		}
	} while (!m_cond->expr());
}
