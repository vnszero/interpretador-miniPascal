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
		//nao existe na memoria
		throw std::string( "nao declarada");
		return NULL;
	} else {
		return Memory::m_memory[name];
	}
}

void Memory::write(const std::string& name, Type* value, bool flag) {
	if(Memory::m_memory.find(name) == Memory::m_memory.end()){
		//nao existe na memoria
		if(flag == true){
			//declaracao de constante
			Memory::registryConstant(name, value);
		} else {
			//declaracao de variavel
			Memory::registryVariable(name, value);
		}
	} else {
		//existe na memoria
		if(Memory::m_set.find(name) == Memory::m_set.end()){
			Memory::m_memory[name] = value;
		} else {
			//Eh constante
			throw std::string( " nao pode ter valor alterado");
		}
	}
}
