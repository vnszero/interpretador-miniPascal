#ifndef IF_COMMAND_H
#define IF_COMMAND_H

#include "../expr/BoolExpr.h"
#include "Command.h"

class BoolExpr;

class IfCommand : public Command {
	public:
		IfCommand(int line, BoolExpr* cond, Command* thenCmds, Command* elseCmds = 0);
		virtual ~IfCommand();
		void ElseCommands(Command* elseCmds);
		virtual void execute();

	private:
		BoolExpr* m_cond;
		Command* m_thenCmds;
		Command* m_elseCmds;

};

#endif
