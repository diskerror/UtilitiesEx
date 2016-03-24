# PHP Utilities Extension

DEPRECATED experiments with porting PHP objects into C++. The PHP-CPP library is useful but does not yield the best execution times compared to Zephir for the same routines.

*Registry* is a singleton implementing *ArrayAccess* and object access with **LIFO**, Last-In-First-Out behavior.

*RegexReplace* uses the C++11 standard regular expression library. It turns out that even with precompiling regular expression it is slower that the built in PHP regular expression API.