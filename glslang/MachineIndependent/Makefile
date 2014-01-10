INCLUDE = -I. -I.. -I../.. -I../Include -I../Public -I../OSDependent/Linux -I../../OGLCompilersDLL
CC=g++
INCPREPROCESSOR=./preprocessor
INCCODEGEN=./../GenericCodeGen
INCOSDEPENDENT=./../OSDependent/Linux/
INCINITIALISATION=./../../OGLCompilersDLL/
LIBPREPROCESSOR=./preprocessor/libPreprocessor.a
LIBOSDEPENDENT=./../OSDependent/Linux/libOssource.a
LIBINITIALISATION=./../../OGLCompilersDLL/libInitializeDll.a
LIBCODEGEN=./../GenericCodeGen/libCodeGen.a
OBJECTS= Initialize.o IntermTraverse.o \
	Intermediate.o ParseHelper.o PoolAlloc.o \
	RemoveTree.o ShaderLang.o intermOut.o parseConst.o SymbolTable.o \
	InfoSink.o Versions.o Constant.o Scan.o limits.o linkValidate.o reflection.o

SRCS= gen_glslang_tab.cpp Initialize.cpp IntermTraverse.cpp \
	Intermediate.cpp ParseHelper.cpp PoolAlloc.cp \
	RemoveTree.cpp ShaderLang.cpp SymbolTable.cpp intermOut.cpp \
	parseConst.cpp InfoSink.cpp Versions.cpp Constant.cpp Scan.cpp
CPPFLAGS=$(DEFINE) $(INCLUDE) -fPIC
SHAREDOBJECT=./lib/libglslang.so

default: all

all: $(SHAREDOBJECT)

$(SHAREDOBJECT): gen_glslang_tab.o $(OBJECTS) $(LIBPREPROCESSOR) $(LIBCODEGEN) $(LIBOSDEPENDENT) $(LIBINITIALISATION)
	$(CC) -fPIC -shared -o $@ -rdynamic -Wl,-whole-archive $(OBJECTS) $(LIBPREPROCESSOR) $(LIBCODEGEN) $(LIBOSDEPENDENT) $(LIBINITIALISATION) gen_glslang_tab.o -Wl,-no-whole-archive
	cp $@ ../../Test
	cp $@ ../../Install/Linux

gen_glslang_tab.o : gen_glslang_tab.cpp 
	$(CC) -fPIC -c $(INCLUDE) gen_glslang_tab.cpp -o $@

gen_glslang_tab.cpp glslang_tab.h: glslang.y
	@echo Generating gen_glslang_tab.cpp
	@dos2unix glslang.y
	bison -t -v -d glslang.y
	@unix2dos glslang.y
	mv glslang.tab.c gen_glslang_tab.cpp
	mv glslang.tab.h glslang_tab.cpp.h

%.o : %.cpp
	$(CC) $(CPPFLAGS) -c $<

$(LIBPREPROCESSOR):
	cd $(INCPREPROCESSOR); make 

$(LIBCODEGEN):
	cd $(INCCODEGEN); make 

$(LIBINITIALISATION):
	cd $(INCINITIALISATION); make 

$(LIBOSDEPENDENT):
	cd $(INCOSDEPENDENT); make 

depend:
	cd $(INCPREPROCESSOR); make depend
	cd $(INCCODEGEN); make depend
	cd $(INCINITIALISATION); make depend
	cd $(INCOSDEPENDENT); make depend
	makedepend -Y -- $(CPPFLAGS) -- $(SRCS) 
#
# Cleanup
#
.PHONY : clean $(LIBPREPROCESSOR) $(LIBCODEGEN) $(LIBOSDEPENDENT) $(LIBINITIALISATION)
clean :
	$(RM) *.o *.a gen_glslang_tab.cpp glslang_tab.cpp glslang_tab.cpp.h glslang_tab.h glslang.output
	$(RM) ./lib/*.so
	cd $(INCPREPROCESSOR); make clean
	cd $(INCCODEGEN); make clean
	cd $(INCINITIALISATION); make clean
	cd $(INCOSDEPENDENT); make clean
	
# DO NOT DELETE

gen_glslang_tab.o: SymbolTable.h ../Include/Common.h ../Include/PoolAlloc.h
gen_glslang_tab.o: ../Include/intermediate.h ../Include/Types.h
gen_glslang_tab.o: ../Include/BaseTypes.h ../Include/ConstantUnion.h
gen_glslang_tab.o: ../Include/InfoSink.h ParseHelper.h Versions.h
gen_glslang_tab.o: ../Include/ShHandle.h ../Public/ShaderLang.h
gen_glslang_tab.o: ../Include/ResourceLimits.h
gen_glslang_tab.o: ../MachineIndependent/Versions.h ../Include/InfoSink.h
gen_glslang_tab.o: localintermediate.h Scan.h
Initialize.o: ../Include/intermediate.h ../Include/Common.h
Initialize.o: ../Include/PoolAlloc.h ../Include/Types.h
Initialize.o: ../Include/BaseTypes.h ../Include/ConstantUnion.h Initialize.h
Initialize.o: ../Include/ResourceLimits.h ../Include/ShHandle.h
Initialize.o: ../Public/ShaderLang.h ../MachineIndependent/Versions.h
Initialize.o: ../Include/InfoSink.h SymbolTable.h ../Include/InfoSink.h
Initialize.o: Versions.h
IntermTraverse.o: ../Include/intermediate.h ../Include/Common.h
IntermTraverse.o: ../Include/PoolAlloc.h ../Include/Types.h
IntermTraverse.o: ../Include/BaseTypes.h ../Include/ConstantUnion.h
Intermediate.o: localintermediate.h ../Include/intermediate.h
Intermediate.o: ../Include/Common.h ../Include/PoolAlloc.h ../Include/Types.h
Intermediate.o: ../Include/BaseTypes.h ../Include/ConstantUnion.h
Intermediate.o: ../Public/ShaderLang.h ../Include/ResourceLimits.h Versions.h
Intermediate.o: RemoveTree.h SymbolTable.h ../Include/InfoSink.h
ParseHelper.o: ParseHelper.h Versions.h ../Include/ShHandle.h
ParseHelper.o: ../Public/ShaderLang.h ../Include/ResourceLimits.h
ParseHelper.o: ../MachineIndependent/Versions.h ../Include/InfoSink.h
ParseHelper.o: SymbolTable.h ../Include/Common.h ../Include/PoolAlloc.h
ParseHelper.o: ../Include/intermediate.h ../Include/Types.h
ParseHelper.o: ../Include/BaseTypes.h ../Include/ConstantUnion.h
ParseHelper.o: ../Include/InfoSink.h localintermediate.h Scan.h
ParseHelper.o: ../OSDependent/Linux/osinclude.h preprocessor/PpContext.h
ParseHelper.o: ParseHelper.h
RemoveTree.o: ../Include/intermediate.h ../Include/Common.h
RemoveTree.o: ../Include/PoolAlloc.h ../Include/Types.h
RemoveTree.o: ../Include/BaseTypes.h ../Include/ConstantUnion.h RemoveTree.h
ShaderLang.o: SymbolTable.h ../Include/Common.h ../Include/PoolAlloc.h
ShaderLang.o: ../Include/intermediate.h ../Include/Types.h
ShaderLang.o: ../Include/BaseTypes.h ../Include/ConstantUnion.h
ShaderLang.o: ../Include/InfoSink.h ParseHelper.h Versions.h
ShaderLang.o: ../Include/ShHandle.h ../Public/ShaderLang.h
ShaderLang.o: ../Include/ResourceLimits.h ../MachineIndependent/Versions.h
ShaderLang.o: ../Include/InfoSink.h localintermediate.h Scan.h ScanContext.h
ShaderLang.o: ../../OGLCompilersDLL/InitializeDll.h
ShaderLang.o: ../OSDependent/Linux/osinclude.h preprocessor/PpContext.h
ShaderLang.o: ParseHelper.h reflection.h Initialize.h ../Include/revision.h
SymbolTable.o: SymbolTable.h ../Include/Common.h ../Include/PoolAlloc.h
SymbolTable.o: ../Include/intermediate.h ../Include/Types.h
SymbolTable.o: ../Include/BaseTypes.h ../Include/ConstantUnion.h
SymbolTable.o: ../Include/InfoSink.h
intermOut.o: localintermediate.h ../Include/intermediate.h
intermOut.o: ../Include/Common.h ../Include/PoolAlloc.h ../Include/Types.h
intermOut.o: ../Include/BaseTypes.h ../Include/ConstantUnion.h
intermOut.o: ../Public/ShaderLang.h ../Include/ResourceLimits.h Versions.h
intermOut.o: ../Include/InfoSink.h
parseConst.o: ParseHelper.h Versions.h ../Include/ShHandle.h
parseConst.o: ../Public/ShaderLang.h ../Include/ResourceLimits.h
parseConst.o: ../MachineIndependent/Versions.h ../Include/InfoSink.h
parseConst.o: SymbolTable.h ../Include/Common.h ../Include/PoolAlloc.h
parseConst.o: ../Include/intermediate.h ../Include/Types.h
parseConst.o: ../Include/BaseTypes.h ../Include/ConstantUnion.h
parseConst.o: ../Include/InfoSink.h localintermediate.h Scan.h
InfoSink.o: ../Include/InfoSink.h ../Include/Common.h ../Include/PoolAlloc.h
Versions.o: ParseHelper.h Versions.h ../Include/ShHandle.h
Versions.o: ../Public/ShaderLang.h ../Include/ResourceLimits.h
Versions.o: ../MachineIndependent/Versions.h ../Include/InfoSink.h
Versions.o: SymbolTable.h ../Include/Common.h ../Include/PoolAlloc.h
Versions.o: ../Include/intermediate.h ../Include/Types.h
Versions.o: ../Include/BaseTypes.h ../Include/ConstantUnion.h
Versions.o: ../Include/InfoSink.h localintermediate.h Scan.h
Constant.o: localintermediate.h ../Include/intermediate.h ../Include/Common.h
Constant.o: ../Include/PoolAlloc.h ../Include/Types.h ../Include/BaseTypes.h
Constant.o: ../Include/ConstantUnion.h ../Public/ShaderLang.h
Constant.o: ../Include/ResourceLimits.h Versions.h
Scan.o: ../Include/Types.h ../Include/Common.h ../Include/PoolAlloc.h
Scan.o: ../Include/BaseTypes.h SymbolTable.h ../Include/intermediate.h
Scan.o: ../Include/ConstantUnion.h ../Include/InfoSink.h glslang_tab.cpp.h
Scan.o: ParseHelper.h Versions.h ../Include/ShHandle.h ../Public/ShaderLang.h
Scan.o: ../Include/ResourceLimits.h ../MachineIndependent/Versions.h
Scan.o: ../Include/InfoSink.h localintermediate.h Scan.h ScanContext.h
Scan.o: preprocessor/PpContext.h ParseHelper.h preprocessor/PpTokens.h
