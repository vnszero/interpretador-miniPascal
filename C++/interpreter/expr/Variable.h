#ifndef VARIABLE_H
#define VARIABLE_H

#include <map>
#include <iomanip>
#include <string>
#include "Expr.h"
#include "../util/Memory.h"

class Type;

class Variable : public Expr {
	public:
		Variable(int line, const std::string& name);
		virtual ~Variable();

		virtual Type* expr();
		void setValue(Type* value = NULL, bool flag = false);
		const std::string& name() const { return m_name; }

	private:
		const std::string m_name;

};

#endif
