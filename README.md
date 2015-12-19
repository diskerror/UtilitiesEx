# PHP Utilities Extension

Experiments with porting PHP objects into C++.

*Registry* is a singleton implementing *ArrayAccess* and object access with **LIFO**, Last-In-First-Out behavior.

*RegexReplace* uses the C++11 standard regular expression library. It turns out that even with precompiling it is slower that the built in PHP regular expression API. Usage of PCRE2 is being investigated.