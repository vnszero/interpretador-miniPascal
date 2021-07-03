#include "BinaryExpr.h"

BinaryExpr::BinaryExpr(int line, Expr* left, enum BinaryExpr::BinaryOp op, Expr* right)
	: Expr(line), m_left(left), m_op(op), m_right(right) {
}

BinaryExpr::~BinaryExpr() {
	delete m_left;
	delete m_right;
}

Type* BinaryExpr::expr() {
	Type* val1 = m_left->expr();
	Type* val2 = m_right->expr();

	if (Type::IntegerType == val1->type() && Type::IntegerType == val2->type()) {
		IntegerValue* v1 = (IntegerValue*) val1;
		IntegerValue* v2 = (IntegerValue*) val2;
		IntegerValue* result;
		switch (m_op) {
			case BinaryExpr::ADD_OP:
				result = new IntegerValue(v1->value() + v2->value());
				return result;
			case BinaryExpr::SUB_OP:
				result = new IntegerValue(v1->value() - v2->value());
				return result;
			case BinaryExpr::MUL_OP:
				result = new IntegerValue(v1->value() * v2->value());
				return result;
			case BinaryExpr::DIV_OP:
				result = new IntegerValue(v1->value() / v2->value());
				return result;
			case BinaryExpr::MOD_OP:
			default:
				result = new IntegerValue(v1->value() % v2->value());
				return result;
		}
	} else if (Type::RealType == val1->type() && Type::RealType == val2->type()) {
		RealValue* v1 = (RealValue*) val1;
		RealValue* v2 = (RealValue*) val2;
		RealValue* result;
		switch (m_op) {
			case BinaryExpr::ADD_OP:
				result = new RealValue(v1->value() + v2->value());
				return result;
			case BinaryExpr::SUB_OP:
				result = new RealValue(v1->value() - v2->value());
				return result;
			case BinaryExpr::MUL_OP:
				result = new RealValue(v1->value() * v2->value());
				return result;
			case BinaryExpr::DIV_OP:
				result = new RealValue(v1->value() / v2->value());
				return result;
			default:
				std::cout << std::setfill ('0') << std::setw (2) << BinaryExpr::line();
				std::cout << ": Operacao % nao suportada para reais" << std::endl;
				exit(1);
				return new IntegerValue(0);
		}
	} else if (Type::RealType == val1->type() && Type::IntegerType == val2->type()) {
		RealValue* v1 = (RealValue*) val1;
		IntegerValue* v2 = (IntegerValue*) val2;
		RealValue* result;
		switch (m_op) {
			case BinaryExpr::ADD_OP:
				result = new RealValue(v1->value() + (double) v2->value());
				return result;
			case BinaryExpr::SUB_OP:
				result = new RealValue(v1->value() - (double) v2->value());
				return result;
			case BinaryExpr::MUL_OP:
				result = new RealValue(v1->value() * (double) v2->value());
				return result;
			case BinaryExpr::DIV_OP:
				result = new RealValue(v1->value() / (double) v2->value());
				return result;
			default:
				std::cout << std::setfill ('0') << std::setw (2) << BinaryExpr::line();
				std::cout << ": Operacao % nao suportada para reais" << std::endl;
				exit(1);
				return new IntegerValue(0); //para evitar falha de segmentacao
		}
	} else if (Type::IntegerType == val1->type() && Type::RealType == val2->type()) {
		IntegerValue* v1 = (IntegerValue*) val1;
		RealValue* v2 = (RealValue*) val2;
		RealValue* result;
		switch (m_op) {
			case BinaryExpr::ADD_OP:
				result = new RealValue((double) v1->value() + v2->value());
				return result;
			case BinaryExpr::SUB_OP:
				result = new RealValue((double) v1->value() - v2->value());
				return result;
			case BinaryExpr::MUL_OP:
				result = new RealValue((double) v1->value() * v2->value());
				return result;
			case BinaryExpr::DIV_OP:
				result = new RealValue((double) v1->value() / v2->value());
				return result;
			default:
				std::cout << std::setfill ('0') << std::setw (2) << BinaryExpr::line();
				std::cout << ": Operacao % nao suportada para reais" << std::endl;
				exit(1);
				return new IntegerValue(0);
		}
	} else {
		std::cout << std::setfill ('0') << std::setw (2) << BinaryExpr::line();
		std::cout << ": Operacao nao suportada para string" << std::endl;
		exit(1);
		return new IntegerValue(0);
	}
}
