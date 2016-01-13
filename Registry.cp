
#include "Registry.h"
// #include <iostream>

using namespace std;

thread_local Registry*		Registry::_instance			= nullptr;
thread_local Php::Object*	Registry::_phpInstance		= nullptr;
thread_local bool			Registry::_fromGetInstance	= false;

////////////////////////////////////////////////////////////////////////////////////////////////////
Registry::Registry()
{
// 	this->_lifo.reserve(1024);		//	make this run-time or ini settable
// 	this->_registry.reserve(1024);	//	make this run-time or ini settable
	
	//	When "getInstance" or "set" creates a PHP object we will have a
	//		pointer to the C++ version of the same object.
	if ( _fromGetInstance ) {
		_instance = this;
		_fromGetInstance = false;
	}
}

Registry::~Registry()
{
}

void Registry::__construct(){}

void Registry::__destruct()
{
	while ( !this->_lifo.empty() ) {
		this->_registry.erase( this->_lifo.back() );
		this->_lifo.pop_back();
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////
Php::Value Registry::getInstance()
{
	if ( _instance == nullptr ) {
		_fromGetInstance = true;
		_phpInstance = new Php::Object("Diskerror\\Utilities\\Registry");
	}
	
	return *_phpInstance;
}

Php::Value Registry::get(Php::Parameters& params)
{
	if ( _instance == nullptr ) {
		throw Php::Exception("No values have been set.");
	}
	
	return _instance->offsetGet(params[0]);
}

void Registry::set(Php::Parameters& params)
{
	if ( _instance == nullptr ) {
		_fromGetInstance = true;
		_phpInstance = new Php::Object("Diskerror\\Utilities\\Registry");
	}
	
	_instance->offsetSet(params[0], params[1]);
}

void Registry::clear()
{
// 	Php::out << "clear here!\n";
// 	if ( _fromGetInstance ) {
// 		delete _instance;
// 		_instance = nullptr;
// 		delete _phpInstance;
// 		_phpInstance = nullptr;
// 		_fromGetInstance = false;
// 	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////
long Registry::count()
{
	return this->_registry.size();
}

Php::Value Registry::offsetGet(const Php::Value &key)
{
	string sKey = key;
	return this->_registry.at(sKey);
}
Php::Value Registry::__get(const Php::Value &key)
{
	string sKey = key;
	return this->_registry.at(sKey);
}

void Registry::offsetSet(const Php::Value &key, const Php::Value &value)
{
	//	null becomes "" (empty valid string)
	//	zero (0) becomes "0" (string with a zero character)
	string sKey = key;	//	uses PHP style "__toString"
	
	//	Cannot update an existing key.
	if ( this->_registry.find(sKey) != this->_registry.end() ) {
		throw Php::Exception("Key already exists.");
	}
	
	this->_lifo.push_back(sKey);
	this->_registry[sKey] = value;
}
void Registry::__set(const Php::Value &key, const Php::Value &value)
{
	this->offsetSet(key, value);
}

bool Registry::offsetExists(const Php::Value &key)
{
	string sKey = key;
	return ( this->_registry.find(sKey) != this->_registry.end() );
}
bool Registry::__isset(const Php::Value &key)
{
	return this->offsetExists(key);
}

void Registry::offsetUnset(const Php::Value &)
{
	throw Php::Exception("Cannot unset a member.");
}
void Registry::__unset(const Php::Value &)
{
	throw Php::Exception("Cannot unset a member.");
}

Php::Value Registry::pop()
{
	if ( this->_lifo.empty() ) {
		return nullptr;
	}
	
	string lastKey = this->_lifo.back();
	this->_lifo.pop_back();
	
	auto val = this->_registry.at( lastKey );
	this->_registry.erase( lastKey );
	
	return val;
}
