
#ifndef DISKERROR_REGEX_H
#define DISKERROR_REGEX_H
#pragma once

#include <phpcpp.h>

class RegexMatch : public Regex
{
public:
	
		Regex(Php::Parameters &);
		virtual ~Regex() override;
	
	void	set(Php::Parameters &) = 0;
	
	Php::Value	exec(Php::Parameters &) = 0;
	Php::Value	__invoke(Php::Parameters &) = 0;
		
	
protected:
	std::smatch	_match;
};

#endif	//	DISKERROR_REGEX_H
