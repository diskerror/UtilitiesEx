
#ifndef DISKERROR_REGEX_H
#define DISKERROR_REGEX_H
#pragma once

#include <phpcpp.h>
#include <regex>

class Regex : public Php::Base
{
public:
	
		Regex();
		virtual ~Regex();
	
	virtual void	__construct(Php::Parameters &);
	virtual void	set(Php::Parameters &) = 0;
	
	virtual Php::Value	exec(Php::Parameters &) = 0;
	virtual Php::Value	__invoke(Php::Parameters &) = 0;
		
	
protected:
	std::regex	_regex;
	std::regex_constants::match_flag_type _match_flag;
};

#endif	//	DISKERROR_REGEX_H
