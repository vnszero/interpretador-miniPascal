#ifndef BINARY_EXPR_H
#define BINARY_EXPR_H

#include <iomanip>
#include <iostream>
#include "Expr.h"
#include "../value/Type.h"
#include "../value/IntegerValue.h"
#include "../value/RealValue.h"
#include "../value/StringValue.h"

class Type;

class BinaryExpr : public Expr {
	public:
		enum BinaryOp {
			ADD_OP,
			SUB_OP,
			MUL_OP,
			DIV_OP,
			MOD_OP
		};

		BinaryExpr(int line, Expr* left, enum BinaryOp op, Expr* right);
		virtual ~BinaryExpr();

		virtual Type* expr();

	private:
		Expr* m_left;
		enum BinaryOp m_op;
		Expr* m_right;

};

#endif
