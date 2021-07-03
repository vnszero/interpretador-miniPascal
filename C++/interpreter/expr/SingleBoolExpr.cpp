#include "SingleBoolExpr.h"

SingleBoolExpr::SingleBoolExpr(int line, Expr* left, enum SingleBoolExpr::RelOp op, Expr* right)
	: BoolExpr(line), m_left(left), m_op(op), m_right(right) {
}

SingleBoolExpr::~SingleBoolExpr() {
	delete m_left;
	delete m_right;
}

bool SingleBoolExpr::expr() {
	Type* val1 = m_left->expr();
	Type* val2 = m_right->expr();

	if (Type::IntegerType == val1->type() && Type::IntegerType == val2->type()) {
		IntegerValue* v1 = (IntegerValue*) val1;
		IntegerValue* v2 = (IntegerValue*) val2;

		switch (m_op) {
			case SingleBoolExpr::EQUAL:
				return v1->value() == v2->value();
			case SingleBoolExpr::NOT_EQUAL:
				return v1->value() != v2->value();
			case SingleBoolExpr::LOWER_THAN:
				return v1->value() < v2->value();
			case SingleBoolExpr::LOWER_EQUAL:
				return v1->value() <= v2->value();
			case SingleBoolExpr::GREATER_THAN:
				return v1->value() > v2->value();
			case SingleBoolExpr::GREATER_EQUAL:
			default:
				return v1->value() >= v2->value();
		}
	} else if (Type::RealType == val1->type() && Type::RealType == val2->type()) {
		RealValue* v1 = (RealValue*) val1;
		RealValue* v2 = (RealValue*) val2;

		switch (m_op) {
			case SingleBoolExpr::EQUAL:
				return v1->value() == v2->value();
			case SingleBoolExpr::NOT_EQUAL:
				return v1->value() != v2->value();
			case SingleBoolExpr::LOWER_THAN:
				return v1->value() < v2->value();
			case SingleBoolExpr::LOWER_EQUAL:
				return v1->value() <= v2->value();
			case SingleBoolExpr::GREATER_THAN:
				return v1->value() > v2->value();
			case SingleBoolExpr::GREATER_EQUAL:
			default:
				return v1->value() >= v2->value();
		}
	} else if (Type::RealType == val1->type() && Type::IntegerType == val2->type()) {
		RealValue* v1 = (RealValue*) val1;
		IntegerValue* v2 = (IntegerValue*) val2;

		switch (m_op) {
			case SingleBoolExpr::EQUAL:
				return v1->value() == (double) v2->value();
			case SingleBoolExpr::NOT_EQUAL:
				return v1->value() != (double) v2->value();
			case SingleBoolExpr::LOWER_THAN:
				return v1->value() < (double) v2->value();
			case SingleBoolExpr::LOWER_EQUAL:
				return v1->value() <= (double) v2->value();
			case SingleBoolExpr::GREATER_THAN:
				return v1->value() > (double) v2->value();
			case SingleBoolExpr::GREATER_EQUAL:
			default:
				return v1->value() >= (double) v2->value();
		}
	} else if (Type::IntegerType == val1->type() && Type::RealType == val2->type()) {
		IntegerValue* v1 = (IntegerValue*) val1;
		RealValue* v2 = (RealValue*) val2;

		switch (m_op) {
			case SingleBoolExpr::EQUAL:
				return (double) v1->value() == v2->value();
			case SingleBoolExpr::NOT_EQUAL:
				return (double) v1->value() != v2->value();
			case SingleBoolExpr::LOWER_THAN:
				return (double) v1->value() < v2->value();
			case SingleBoolExpr::LOWER_EQUAL:
				return (double) v1->value() <= v2->value();
			case SingleBoolExpr::GREATER_THAN:
				return (double) v1->value() > v2->value();
			case SingleBoolExpr::GREATER_EQUAL:
			default:
				return (double) v1->value() >= v2->value();
		}
	} else if (Type::StringType == val1->type() && Type::StringType == val2->type()) {
		StringValue* v1 = (StringValue*) val1;
		StringValue* v2 = (StringValue*) val2;

		switch (m_op) {
			case SingleBoolExpr::EQUAL:
				return v1->value() == v2->value();
			case SingleBoolExpr::NOT_EQUAL:
				return v1->value() != v2->value();
			default:
				std::cout << std::setfill ('0') << std::setw (2) << SingleBoolExpr::line();
				std::cout << ": Operacao nao suportada para strings" << std::endl;
				exit(1);
				return false;
		}
	} else {
		std::cout << std::setfill ('0') << std::setw (2) << SingleBoolExpr::line();
		std::cout << ": Operacao logica entre tipos diferentes nao suportada" << std::endl;
		exit(1);
		return false;
	}
}
