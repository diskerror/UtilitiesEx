
#include "Regex.h"
// #include <iostream>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////
Regex::Regex()
{
}

void Regex::__construct(Php::Parameters &params)
{
	if ( params.size() ) {
		this->set(params);
	}
}

Regex::~Regex()
{
}
