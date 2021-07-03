#ifndef CASE_COMMAND_H
#define CASE_COMMAND_H

#include <list>
#include "Command.h"
#include "CaseOption.h"
#include "../expr/Expr.h"
#include "../value/Type.h"
#include "../value/IntegerValue.h"
#include "../value/RealValue.h"
#include "../value/StringValue.h"

class Expr;
class CaseOption;
class Type;
class IntegerValue;
class RealValue;
class StringValue;

class CaseCommand : public Command {
	public:
		CaseCommand(int line, Expr* expr);
		virtual ~CaseCommand();

		void addOption(Type* value, Command* cmd);
		void setOtherwise(Command* cmd);
		void execute();

	private:
		Expr* m_expr;
		std::list<CaseOption*> m_options;
		Command* m_otherwise;
};

#endif
