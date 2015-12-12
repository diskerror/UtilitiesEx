
#ifndef DISKERROR_REGEXREPLACE_H
#define DISKERROR_REGEXREPLACE_H
#pragma once

#include "Regex.h"

class RegexReplace : public Regex
{
public:
	
// 		RegexReplace(Php::Parameters &);
// 		virtual ~RegexReplace() override;
	
	virtual void	set(Php::Parameters &) override;
	
	virtual Php::Value	exec(Php::Parameters &);
	virtual Php::Value	__invoke(Php::Parameters &);
		
	
protected:
	std::string	_replace;
};

#endif	//	DISKERROR_REGEXREPLACE_H
