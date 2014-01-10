CC = g++

OBJECTS = CodeGen.o Link.o
AR=ar

SRCS=CodeGen.cpp Link.cpp

CPPFLAGS = -fPIC

default : all
all : libCodeGen.a

libCodeGen.a : $(OBJECTS)
	$(AR) rvu $@ $(OBJECTS)
	ranlib $@

%.o : %.cpp
	$(CC) -c $(CPPFLAGS) $<

#
# Cleanup
#
.PHONY : clean
clean :
	$(RM) *.o *.a

depend:
	makedepend -- $(CFLAGS) -- $(SRCS)
# DO NOT DELETE

CodeGen.o: ../Include/Common.h /usr/include/stdint.h /usr/include/features.h
CodeGen.o: /usr/include/stdc-predef.h /usr/include/bits/predefs.h
CodeGen.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
CodeGen.o: /usr/include/gnu/stubs.h /usr/include/bits/wchar.h
CodeGen.o: /usr/include/stdio.h /usr/include/bits/types.h
CodeGen.o: /usr/include/bits/typesizes.h /usr/include/libio.h
CodeGen.o: /usr/include/_G_config.h /usr/include/wchar.h
CodeGen.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
CodeGen.o: /usr/include/assert.h ../Include/PoolAlloc.h /usr/include/string.h
CodeGen.o: /usr/include/xlocale.h ../Include/ShHandle.h
CodeGen.o: ../Public/ShaderLang.h ../Include/ResourceLimits.h
CodeGen.o: ../MachineIndependent/Versions.h ../Include/InfoSink.h
CodeGen.o: /usr/include/math.h /usr/include/bits/huge_val.h
CodeGen.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
CodeGen.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
CodeGen.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
Link.o: ../Include/Common.h /usr/include/stdint.h /usr/include/features.h
Link.o: /usr/include/stdc-predef.h /usr/include/bits/predefs.h
Link.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
Link.o: /usr/include/gnu/stubs.h /usr/include/bits/wchar.h
Link.o: /usr/include/stdio.h /usr/include/bits/types.h
Link.o: /usr/include/bits/typesizes.h /usr/include/libio.h
Link.o: /usr/include/_G_config.h /usr/include/wchar.h
Link.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
Link.o: /usr/include/assert.h ../Include/PoolAlloc.h /usr/include/string.h
Link.o: /usr/include/xlocale.h ../Include/ShHandle.h ../Public/ShaderLang.h
Link.o: ../Include/ResourceLimits.h ../MachineIndependent/Versions.h
Link.o: ../Include/InfoSink.h /usr/include/math.h
Link.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
Link.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
Link.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
Link.o: /usr/include/bits/mathcalls.h
