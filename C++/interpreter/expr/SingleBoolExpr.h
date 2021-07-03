#ifndef SINGLE_BOOL_EXPR_H
#define SINGLE_BOOL_EXPR_H

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include "Expr.h"
#include "BoolExpr.h"
#include "../value/Type.h"
#include "../value/IntegerValue.h"
#include "../value/RealValue.h"
#include "../value/StringValue.h"

class Expr;
class Type;

class SingleBoolExpr : public BoolExpr {
	public:
		enum RelOp {
			EQUAL,
			NOT_EQUAL,
			LOWER_THAN,
			GREATER_THAN,
			LOWER_EQUAL,
			GREATER_EQUAL
		};

		SingleBoolExpr(int line, Expr* left, enum RelOp op, Expr* right);
		virtual ~SingleBoolExpr();

		virtual bool expr();

	private:
		Expr* m_left;
		enum RelOp m_op;
		Expr* m_right;

};

#endif
