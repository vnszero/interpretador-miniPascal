#ifndef CASE_OPTION_H
#define CASE_OPTION_H

#include <list>
#include "Command.h"
#include "../value/Type.h"

class Type;

class CaseOption {
	public:
		CaseOption();
		~CaseOption();
		Type* m_value;
		Command* m_cmd;
};

#endif
