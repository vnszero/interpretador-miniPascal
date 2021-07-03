#include "Memory.h"

std::map<std::string, Type*> Memory::m_memory;
std::set<std::string> Memory::m_set;

void Memory::registryVariable(const std::string& name, Type* value){
	Memory::m_memory.insert(std::pair<std::string, Type*>(name, value));
}

void Memory::registryConstant(const std::string& name, Type* value){
	Memory::m_set.insert(name);
	Memory::m_memory.insert(std::pair<std::string, Type*>(name, value));
}

Type* Memory::read(const std::string& name) {
	if(Memory::m_memory.find(name) == Memory::m_memory.end()){
		//not found in memory
		throw std::string( "undeclared");
		return NULL;
	} else {
		return Memory::m_memory[name];
	}
}

void Memory::write(const std::string& name, Type* value, bool flag) {
	if(Memory::m_memory.find(name) == Memory::m_memory.end()){
		//not found in memory
		if(flag == true){
			//constant
			Memory::registryConstant(name, value);
		} else {
			//variable
			Memory::registryVariable(name, value);
		}
	} else {
		//Found in memory
		if(Memory::m_set.find(name) == Memory::m_set.end()){
			Memory::m_memory[name] = value;
		} else {
			//it's a constant
			throw std::string( " cannot change the value");
		}
	}
}
