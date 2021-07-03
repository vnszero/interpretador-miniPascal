#include "CompositeBoolExpr.h"

CompositeBoolExpr::CompositeBoolExpr(int line, BoolExpr* left, enum CompositeBoolExpr::BoolOp op, BoolExpr* right)
	: BoolExpr(line), m_left(left), m_op(op), m_right(right) {
}

CompositeBoolExpr::~CompositeBoolExpr() {
	delete m_left;
	delete m_right;
}

bool CompositeBoolExpr::expr() {
	bool v1 = m_left->expr();
	bool v2 = m_right->expr();

	switch (m_op) {
		case CompositeBoolExpr::AND:
			return v1 && v2;
		case CompositeBoolExpr::OR:
		default:
			return v1 || v2;
	}
}
