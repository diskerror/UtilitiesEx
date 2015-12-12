
#include "Regex.h"
// #include <iostream>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////
Regex::Regex(Php::Parameters &params)
{
	if ( params.size() ) {
		this->set(params);
	}
}

Regex::~Regex()
{
}

void Regex::set(Php::Parameters &params)
{
	string expression = params[0];
	regex_constants::syntax_option_type flag = params[1];
	
	this->_regex.assign(expression, flag);
}


////////////////////////////////////////////////////////////////////////////////////////////////////
Php::Value Regex::match(Php::Parameters &params)
{
	string str = params[0];
	return regex_match(str, this->_match, this->_regex);
}

Php::Value Regex::search(Php::Parameters &params)
{
	string str = params[0];
	return regex_search(str, this->_match, this->_regex);
}

Php::Value Regex::replace(Php::Parameters &params)
{
	string str = params[0];
	return regex_replace(str, this->_regex, this->_replace);
}
