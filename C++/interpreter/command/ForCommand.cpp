#include "ForCommand.h"

ForCommand::ForCommand(int line, Variable* var, Expr* src, Expr* dst, Command* cmd)
	: Command(line), m_var(var), m_src(src), m_dst(dst), m_cmd(cmd) {
}

ForCommand::~ForCommand() {
	delete m_var;
	delete m_src;
	delete m_dst;
	delete m_cmd;
}

void ForCommand::execute() {
	Type* src = m_src->expr();
	Type* dst = m_dst->expr();
	if(src->IntegerType == src->type() && dst->IntegerType == dst->type()){
		IntegerValue* sr = (IntegerValue*) src;
		IntegerValue* ds = (IntegerValue*) dst;
		int v;
		int s = sr->value();
		int d = ds->value();
		int i;
		if (s > d) {
			i = -1;
		} else {
			i = 1;
		}
		for(v = s; v != d; v += i){
			m_var->setValue(new IntegerValue(v));
			m_cmd->execute();
		}
		m_var->setValue(new IntegerValue(v));
	} else {
		std::cout << std::setfill ('0') << std::setw (2) << ForCommand::line();
		std::cout << ": For command only accept integers" << std::endl;
	}

}
