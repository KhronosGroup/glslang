CC = g++

OBJECTS = CodeGen.o Link.o
AR=ar

SRCS=CodeGen.cpp Link.cpp

default : all
all : libCodeGen.a

libCodeGen.a : $(OBJECTS)
	$(AR) rvu $@ $(OBJECTS)
	ranlib $@

%.o : %.cpp
	$(CC) -c $<

#
# Cleanup
#
.PHONY : clean
clean :
	$(RM) *.o *.a

depend:
	makedepend -- $(CFLAGS) -- $(SRCS)
# DO NOT DELETE

CodeGen.o: ../Include/Common.h ../Include/PoolAlloc.h ../Include/ShHandle.h
CodeGen.o: ../Public/ShaderLang.h
CodeGen.o: ../Include/InfoSink.h
Link.o: ../Include/Common.h ../Include/PoolAlloc.h ../Include/ShHandle.h
Link.o: ../Public/ShaderLang.h
Link.o: ../Include/InfoSink.h
