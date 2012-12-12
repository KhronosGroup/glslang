CC = gcc

OBJECTS = atom.o cpp.o cppstruct.o memory.o scanner.o symbols.o tokens.o
AR=ar
SRCS=scanner.c atom.c memory.c tokens. cpp.c cppstruct.c symbols.c

default: all
all : libPreprocessor.a
libPreprocessor.a : $(OBJECTS)
	$(AR) rvu $@ $(OBJECTS)
	ranlib $@

%.o : %.c
	$(CC) -c $<

#
# Cleanup
#
.PHONY : clean
clean :
	$(RM) *.o *.a

depend:
	makedepend  -Y -- $(SRCS)

# DO NOT DELETE

scanner.o: slglobals.h memory.h atom.h scanner.h parser.h cpp.h tokens.h
scanner.o: symbols.h compile.h
atom.o: slglobals.h memory.h atom.h scanner.h parser.h cpp.h tokens.h
atom.o: symbols.h compile.h
memory.o: memory.h
cpp.o: slglobals.h memory.h atom.h scanner.h parser.h cpp.h tokens.h
cpp.o: symbols.h compile.h
cppstruct.o: slglobals.h memory.h atom.h scanner.h parser.h cpp.h tokens.h
cppstruct.o: symbols.h compile.h
symbols.o: slglobals.h memory.h atom.h scanner.h parser.h cpp.h tokens.h
symbols.o: symbols.h compile.h
