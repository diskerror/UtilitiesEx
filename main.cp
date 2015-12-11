
#include <phpcpp.h>

#include "Registry.h"

using namespace std;


extern "C" {

/**
 *  Function that is called by PHP right after the PHP process
 *  has started, and that returns an address of an internal PHP
 *  strucure with all the details and features of your extension
 *
 *  @return void*   a pointer to an address that is understood by PHP
 */
PHPCPP_EXPORT void *get_module() 
{
	// static(!) Php::Extension object that should stay in memory
	// for the entire duration of the process (that's why it's static)
	static Php::Extension extension("diskerror_utilities", "0.1");
	
	//	Registry
	Php::Class<Registry> registry("Diskerror\\Utilities\\Registry");

	registry.method("getInstance", &Registry::getInstance, Php::Static, {});

	registry.method("get", &Registry::get, Php::Static, {
		Php::ByVal("value", Php::Type::String, true)
	});
	
	registry.method("set", &Registry::set, Php::Static, {
		Php::ByVal("key", Php::Type::String, true),
		Php::ByVal("value", Php::Type::Null, true)
	});

	registry.method("pop", &Registry::pop, {});

	extension.add(std::move(registry));
	
// 	extension.onIdle([]() {
// 		Registry::clear();
// 	});
	
	// return the extension
	return extension;
}


}
