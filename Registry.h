
#ifndef DISKERROR_REGISTRY_H
#define DISKERROR_REGISTRY_H
#pragma once

#include <phpcpp.h>

Php::Value getInstance();
void sSet(Php::Parameters&);
Php::Value sGet(Php::Parameters&);

class Registry : public Php::Base, public Php::Countable, public Php::ArrayAccess
{
protected:
	static thread_local	Registry	*_instance;
	static thread_local	Php::Object	*_phpInstance;
	static thread_local	bool		_fromGetInstance;

	std::unordered_map<std::string, Php::Value> _registry;
	std::vector<std::string> _lifo;

public:
	
		Registry();
		virtual ~Registry() override;
	
	void	__construct();
	void	__destruct();
		
	static	Php::Value	getInstance();
	static	Php::Value	get(Php::Parameters&);
	static	void		set(Php::Parameters&);
	static	void		clear();
	
	virtual long 		count() override;
	
	virtual Php::Value	offsetGet(const Php::Value &) override;
			Php::Value	__get(const Php::Value &);
	virtual void		offsetSet(const Php::Value &, const Php::Value &) override;
			void		__set(const Php::Value &, const Php::Value &);
	virtual bool		offsetExists(const Php::Value &) override;
			bool		__isset(const Php::Value &);
	virtual void		offsetUnset(const Php::Value &) override;
			void		__unset(const Php::Value &);
	
	Php::Value	pop();
	
};

#endif	//	DISKERROR_REGISTRY_H
