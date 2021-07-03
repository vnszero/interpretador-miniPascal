#include "CaseCommand.h"

CaseCommand::CaseCommand(int line, Expr* expr)
	: Command(line), m_expr(expr) {

}

CaseCommand::~CaseCommand(){
	delete m_expr;
	delete m_otherwise;
}

void CaseCommand::addOption(Type* value, Command* cmd){
	CaseOption* cp = new CaseOption();
	cp->m_value = value;
	cp->m_cmd = cmd;
	m_options.push_back(cp);
}

void CaseCommand::setOtherwise(Command* cmd){
	m_otherwise = cmd;
}

void CaseCommand::execute(){
	Type* val_switch = m_expr->expr();
	if (val_switch->IntegerType == val_switch->type()) {
		IntegerValue* v_switch = (IntegerValue*) val_switch;
		for (std::list<CaseOption*>::iterator it = m_options.begin(),
			ed = m_options.end(); it != ed; it++) {

				CaseOption* cp = *it;
				Type* val_option = cp->m_value;
				if(val_option->IntegerType == val_option->type()){
					IntegerValue* v_option = (IntegerValue*) val_option;
					if (v_option->value() == v_switch->value()) {
						Command* cmd = cp->m_cmd;
						cmd->execute();
						return;
					}
				}
		}
		//caso padrao
		m_otherwise->execute();
	} else if (val_switch->RealType == val_switch->type()) {
		RealValue* v_switch = (RealValue*) val_switch;
		for (std::list<CaseOption*>::iterator it = m_options.begin(),
			ed = m_options.end(); it != ed; it++) {

				CaseOption* cp = *it;
				Type* val_option = cp->m_value;
				if(val_option->RealType == val_option->type()){
					RealValue* v_option = (RealValue*) val_option;
					if (v_option->value() == v_switch->value()) {
						Command* cmd = cp->m_cmd;
						cmd->execute();
						return;
					}
				}
		}
		//caso padrao
		m_otherwise->execute();
	} else if (val_switch->StringType == val_switch->type()) {
		StringValue* v_switch = (StringValue*) val_switch;
		for (std::list<CaseOption*>::iterator it = m_options.begin(),
			ed = m_options.end(); it != ed; it++) {

				CaseOption* cp = *it;
				Type* val_option = cp->m_value;
				if(val_option->StringType == val_option->type()){
					StringValue* v_option = (StringValue*) val_option;
					if (v_option->value() == v_switch->value()) {
						Command* cmd = cp->m_cmd;
						cmd->execute();
						return;
					}
				}
		}
		//caso padrao
		m_otherwise->execute();
	}
}
