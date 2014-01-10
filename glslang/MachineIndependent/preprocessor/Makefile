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

PpAtom.o: PpContext.h ../ParseHelper.h ../Versions.h ../../Include/ShHandle.h
PpAtom.o: ../../Public/ShaderLang.h ../../Include/ResourceLimits.h
PpAtom.o: ../../MachineIndependent/Versions.h ../../Include/InfoSink.h
PpAtom.o: ../../Include/Common.h ../../Include/PoolAlloc.h ../SymbolTable.h
PpAtom.o: ../../Include/intermediate.h ../../Include/Types.h
PpAtom.o: ../../Include/BaseTypes.h ../../Include/ConstantUnion.h
PpAtom.o: ../../Include/InfoSink.h ../localintermediate.h ../Scan.h
PpAtom.o: PpTokens.h
PpScanner.o: PpContext.h ../ParseHelper.h ../Versions.h
PpScanner.o: ../../Include/ShHandle.h ../../Public/ShaderLang.h
PpScanner.o: ../../Include/ResourceLimits.h
PpScanner.o: ../../MachineIndependent/Versions.h ../../Include/InfoSink.h
PpScanner.o: ../../Include/Common.h ../../Include/PoolAlloc.h
PpScanner.o: ../SymbolTable.h ../../Include/intermediate.h
PpScanner.o: ../../Include/Types.h ../../Include/BaseTypes.h
PpScanner.o: ../../Include/ConstantUnion.h ../../Include/InfoSink.h
PpScanner.o: ../localintermediate.h ../Scan.h PpTokens.h
PpTokens.o: PpContext.h ../ParseHelper.h ../Versions.h
PpTokens.o: ../../Include/ShHandle.h ../../Public/ShaderLang.h
PpTokens.o: ../../Include/ResourceLimits.h
PpTokens.o: ../../MachineIndependent/Versions.h ../../Include/InfoSink.h
PpTokens.o: ../../Include/Common.h ../../Include/PoolAlloc.h ../SymbolTable.h
PpTokens.o: ../../Include/intermediate.h ../../Include/Types.h
PpTokens.o: ../../Include/BaseTypes.h ../../Include/ConstantUnion.h
PpTokens.o: ../../Include/InfoSink.h ../localintermediate.h ../Scan.h
PpTokens.o: PpTokens.h
Pp.o: PpContext.h ../ParseHelper.h ../Versions.h ../../Include/ShHandle.h
Pp.o: ../../Public/ShaderLang.h ../../Include/ResourceLimits.h
Pp.o: ../../MachineIndependent/Versions.h ../../Include/InfoSink.h
Pp.o: ../../Include/Common.h ../../Include/PoolAlloc.h ../SymbolTable.h
Pp.o: ../../Include/intermediate.h ../../Include/Types.h
Pp.o: ../../Include/BaseTypes.h ../../Include/ConstantUnion.h
Pp.o: ../../Include/InfoSink.h ../localintermediate.h ../Scan.h PpTokens.h
PpContext.o: PpContext.h ../ParseHelper.h ../Versions.h
PpContext.o: ../../Include/ShHandle.h ../../Public/ShaderLang.h
PpContext.o: ../../Include/ResourceLimits.h
PpContext.o: ../../MachineIndependent/Versions.h ../../Include/InfoSink.h
PpContext.o: ../../Include/Common.h ../../Include/PoolAlloc.h
PpContext.o: ../SymbolTable.h ../../Include/intermediate.h
PpContext.o: ../../Include/Types.h ../../Include/BaseTypes.h
PpContext.o: ../../Include/ConstantUnion.h ../../Include/InfoSink.h
PpContext.o: ../localintermediate.h ../Scan.h
PpMemory.o: PpContext.h ../ParseHelper.h ../Versions.h
PpMemory.o: ../../Include/ShHandle.h ../../Public/ShaderLang.h
PpMemory.o: ../../Include/ResourceLimits.h
PpMemory.o: ../../MachineIndependent/Versions.h ../../Include/InfoSink.h
PpMemory.o: ../../Include/Common.h ../../Include/PoolAlloc.h ../SymbolTable.h
PpMemory.o: ../../Include/intermediate.h ../../Include/Types.h
PpMemory.o: ../../Include/BaseTypes.h ../../Include/ConstantUnion.h
PpMemory.o: ../../Include/InfoSink.h ../localintermediate.h ../Scan.h
PpSymbols.o: PpContext.h ../ParseHelper.h ../Versions.h
PpSymbols.o: ../../Include/ShHandle.h ../../Public/ShaderLang.h
PpSymbols.o: ../../Include/ResourceLimits.h
PpSymbols.o: ../../MachineIndependent/Versions.h ../../Include/InfoSink.h
PpSymbols.o: ../../Include/Common.h ../../Include/PoolAlloc.h
PpSymbols.o: ../SymbolTable.h ../../Include/intermediate.h
PpSymbols.o: ../../Include/Types.h ../../Include/BaseTypes.h
PpSymbols.o: ../../Include/ConstantUnion.h ../../Include/InfoSink.h
PpSymbols.o: ../localintermediate.h ../Scan.h
