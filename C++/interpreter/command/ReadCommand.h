#ifndef READ_COMMAND_H
#define READ_COMMAND_H

#include "Command.h"
#include "../expr/Variable.h"
#include "../value/IntegerValue.h"
#include "../value/RealValue.h"
#include "../value/StringValue.h"
#include <list>
#include <cctype>
#include <cstring>
#include <stdlib.h>

class Variable;
class IntegerValue;
class RealValue;
class StringValue;

class ReadCommand : public Command {
	public:
		ReadCommand(int line);
		virtual ~ReadCommand();

		void addVariable(Variable* var);
		virtual void execute();
	private:
		std::list<Variable*> m_vars;
};

#endif
