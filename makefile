
NAME			= diskerror_utilities

INI_DIR			= /etc/php5/mods-available/
EXTENSION_DIR	= $(shell php-config --extension-dir)
EXTENSION 		= ${NAME}.so
INI 			= ${NAME}.ini

COMPILER		= g++
LINKER			= g++
COMPILER_FLAGS	= -Wall -c -O2 -std=c++11 -fpic
LINKER_FLAGS	= -shared

LDLIBS = \
	-lphpcpp

CPP	= ${COMPILER} ${COMPILER_FLAGS} -include "precompile.hpp" $<

RM		= rm -f
CP		= cp -f
MKDIR	= mkdir -p


OBJECTS = \
	Registry.o \
	main.o


all: ${EXTENSION}

pre: cleanpre \
	precompile.o

${EXTENSION}: ${OBJECTS} precompile.o
	${LINKER} ${LDLIBS} ${OBJECTS} ${LINKER_FLAGS} -o $@

precompile.o: precompile.hpp
	${COMPILER} ${COMPILER_FLAGS} -I/usr/include $< -o $@



Registry.o: Registry.cp Registry.h
	$(CPP)

main.o: main.cp Registry.h
	$(CPP)



install:
	${CP} ${EXTENSION} ${EXTENSION_DIR}
	chmod 755 ${EXTENSION_DIR}/${EXTENSION}
	echo "extension = "${EXTENSION}"\n" > ${INI_DIR}${INI}
	chmod 644 ${INI_DIR}${INI}
	ln -sf ${INI_DIR}${INI} /etc/php5/apache2/conf.d/
	ln -sf ${INI_DIR}${INI} /etc/php5/cli/conf.d/

uninstall:
	$(RM) ${EXTENSION_DIR}/${EXTENSION} ${INI_DIR}${INI} /etc/php5/apache2/conf.d/${INI} /etc/php5/cli/conf.d/${INI}

				
clean:
	${RM} ${EXTENSION} ${OBJECTS} precompile.o

cleanpre:
	$(RM) precompile.o
