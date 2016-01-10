
#include "RegexReplace.h"
// #include <iostream>

using namespace std;

/**
 * Set regular expression object and replacement string.
 *
 * @param string expression
 * @param string replacement
 * @param integer syntax_option
 * @param integer match_flag
 */
void RegexReplace::set(Php::Parameters &params)
{
	string expression = "";
	this->_replace = "";
	regex_constants::syntax_option_type syntax_option = regex::ECMAScript|regex::optimize;
	this->_match_flag = regex_constants::match_default;
	
	switch ( params.size() ) {
		default:
		this->_match_flag = (regex_constants::match_flag_type) (long) params[3];
		
		case 3:
		syntax_option = (regex_constants::syntax_option_type) (long) params[2];
		
		case 2: {
		string rep = params[1];
		this->_replace = rep;
		}
		
		case 1: {
		string exp = params[0];
		expression = exp;
		}
		
		case 0:
		break;
	}
	
	this->_regex.assign(expression, syntax_option);
}


////////////////////////////////////////////////////////////////////////////////////////////////////
Php::Value RegexReplace::exec(Php::Parameters &params)
{
	string str = params[0];
	return regex_replace(str, this->_regex, this->_replace, this->_match_flag);
}

Php::Value RegexReplace::__invoke(Php::Parameters &params)
{
	return this->exec(params);
}
