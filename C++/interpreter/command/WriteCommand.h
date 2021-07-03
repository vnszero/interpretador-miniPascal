#ifndef WRITE_COMMAND_H
#define WRITE_COMMAND_H

#include "Command.h"
#include <list>
#include <iostream>
#include "../expr/Expr.h"
#include "../value/IntegerValue.h"
#include "../value/RealValue.h"
#include "../value/StringValue.h"
#include "../value/Type.h"

class Expr;

class WriteCommand : public Command {
	public:
		WriteCommand(int line, bool writeln = false);
		virtual ~WriteCommand();

		void addExpr(Expr* expr);
		virtual void execute();
	private:
		bool m_writeln;
		std::list<Expr*> m_exprs;
};

#endif
