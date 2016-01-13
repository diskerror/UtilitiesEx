
NAME			= diskerror_utilities

PHPE			= /etc/php5
INI_DIR			= $(PHPE)/mods-available/
EXTENSION_DIR	= $(shell php-config --extension-dir)
EXTENSION 		= $(NAME).so
INI 			= $(NAME).ini

COMPILER		= g++
LINKER			= g++
COMPILER_FLAGS	= -Wall -c -O2 -std=c++11 -fpic
LINKER_FLAGS	= -shared

LDLIBS = \
	-lphpcpp

CPP	= $(COMPILER) $(COMPILER_FLAGS) -include "precompile.hpp" $<

OBJECTS = \
	Regex.o \
	RegexReplace.o \
	Registry.o \
	main.o


all: $(EXTENSION)

pre: cleanpre \
	precompile.o

$(EXTENSION): $(OBJECTS) precompile.o
	$(LINKER) $(OBJECTS) $(LINKER_FLAGS) $(LDLIBS) -o $@

precompile.o: precompile.hpp
	$(COMPILER) $(COMPILER_FLAGS) -I/usr/include $< -o $@


Regex.o: Regex.cp Regex.h
	$(CPP)

RegexReplace.o: RegexReplace.cp RegexReplace.h
	$(CPP)

Registry.o: Registry.cp Registry.h
	$(CPP)

main.o: main.cp Registry.h RegexReplace.h
	$(CPP)


install:
	cp -f $(EXTENSION) $(EXTENSION_DIR)
	chmod 644 $(EXTENSION_DIR)/$(EXTENSION)
	echo "extension = "$(EXTENSION)"\n" > $(INI_DIR)$(INI)
	chmod 644 $(INI_DIR)$(INI)
	if [ -d $(PHPE)/apache2/conf.d/ ]; then \
		ln -sf $(INI_DIR)$(INI) $(PHPE)/apache2/conf.d/;\
	fi
	if [ -d $(PHPE)/cli/conf.d/ ]; then \
		ln -sf $(INI_DIR)$(INI) $(PHPE)/cli/conf.d/;\
	fi
	if [ -d $(PHPE)/cgi/conf.d/ ]; then \
		ln -sf $(INI_DIR)$(INI) $(PHPE)/cgi/conf.d/;\
	fi

uninstall:
	rm -f $(EXTENSION_DIR)/$(EXTENSION) \
		$(INI_DIR)$(INI) \
		$(PHPE)/apache2/conf.d/$(INI) \
		$(PHPE)/cli/conf.d/$(INI) \
		$(PHPE)/cgi/conf.d/$(INI)

				
clean:
	rm -f $(EXTENSION) $(OBJECTS)

cleanpre:
	rm -f precompile.o
