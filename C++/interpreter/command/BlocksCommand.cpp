#include "BlocksCommand.h"

BlocksCommand::BlocksCommand(int line)
	: Command(line) {
}

BlocksCommand::~BlocksCommand() {
}

void BlocksCommand::addCommand(Command* cmd) {
	m_cmds.push_back(cmd);
}

void BlocksCommand::execute() {
	for (std::list<Command*>::iterator it = m_cmds.begin(),
	     ed = m_cmds.end(); it != ed; it++) {
		Command* cmd = *it;
		cmd->execute();
	}
}
