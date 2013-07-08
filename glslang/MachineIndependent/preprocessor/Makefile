INCLUDE = -I../
CC = gcc

CPPFLAGS=$(DEFINE) $(INCLUDE) -fPIC

OBJECTS = PpAtom.o PpScanner.o PpTokens.o Pp.o PpContext.o PpMemory.o PpSymbols.o
AR=ar
SRCS = PpAtom.cpp PpScanner.cpp PpTokens.cpp Pp.cpp PpContext.cpp PpMemory.cpp PpSymbols.cpp


default: all
all : libPreprocessor.a
libPreprocessor.a : $(OBJECTS)
	$(AR) rvu $@ $(OBJECTS)
	ranlib $@

%.o : %.c
	$(CC) -c $(CPPFLAGS) $<

#
# Cleanup
#
.PHONY : clean
clean :
	$(RM) *.o *.a

depend:
	makedepend  -Y -- $(SRCS)

# DO NOT DELETE

PpAtom.o: PpContext.h PpToken.h
PpScanner.o: PpContext.h PpToken.h
PpTokens.o: PpContext.h PpToken.h
Pp.o: PpContext.h PpToken.h
PpContext.o: PpContext.h PpToken.h
PpMemory.o: PpContext.h PpToken.h
PpSymbols.o: PpContext.h PpToken.h
