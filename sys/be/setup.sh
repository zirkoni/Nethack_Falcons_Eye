#!/bin/sh
# Copy files to their correct locations.
#

# Were we started from the top level?  Cope.
if [ -f sys/be/Makefile.top ]; then cd sys/be; fi

#
#	Otherwise...

echo "Copying Makefiles."
cp Makefile.top ../../Makefile
cp Makefile.dat ../../dat/Makefile
cp Makefile.doc ../../doc/Makefile
cp Makefile.src ../../src/Makefile
cp Makefile.utl ../../util/Makefile

#
#	Copy the ready-made lexical parser files,
#	since lex/yacc doesn't come with BeOS

#echo "Copying parser files."
#cp ../../sys/share/dgn_comp.h ../../include/
#cp ../../sys/share/lev_comp.h ../../include/
#cp ../../sys/share/dgn_lex.c ../../util/
#cp ../../sys/share/dgn_yacc.c ../../util/
#cp ../../sys/share/lev_lex.c ../../util/
#cp ../../sys/share/lev_yacc.c ../../util/
