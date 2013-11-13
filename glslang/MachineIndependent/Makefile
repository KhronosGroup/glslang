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
.PHONY : clean
clean :
	$(RM) *.o *.a gen_glslang_tab.cpp glslang_tab.cpp glslang_tab.cpp.h glslang_tab.h glslang.output
	$(RM) ./lib/*.so
	cd $(INCPREPROCESSOR); make clean
	cd $(INCCODEGEN); make clean
	cd $(INCINITIALISATION); make clean
	cd $(INCOSDEPENDENT); make clean
	
# DO NOT DELETE

gen_glslang_tab.o: SymbolTable.h ../Include/Common.h
gen_glslang_tab.o: ../Include/intermediate.h ../Include/Common.h
gen_glslang_tab.o: ../Include/PoolAlloc.h ../Include/Types.h
gen_glslang_tab.o: ../Include/BaseTypes.h ../Include/ConstantUnion.h
gen_glslang_tab.o: ../Include/InfoSink.h ParseHelper.h ../Include/ShHandle.h
gen_glslang_tab.o: ../Public/ShaderLang.h
gen_glslang_tab.o: ../Include/InfoSink.h localintermediate.h
gen_glslang_tab.o: ../Include/intermediate.h ../Public/ShaderLang.h
Initialize.o: ../Include/intermediate.h Initialize.h
Initialize.o: ../Include/ResourceLimits.h ../Include/Common.h
Initialize.o: ../Include/PoolAlloc.h ../Include/ShHandle.h
Initialize.o: ../Public/ShaderLang.h
Initialize.o: ../Include/InfoSink.h SymbolTable.h ../Include/Common.h
Initialize.o: ../Include/intermediate.h ../Include/Types.h
Initialize.o: ../Include/BaseTypes.h ../Include/ConstantUnion.h
Initialize.o: ../Include/InfoSink.h
IntermTraverse.o: ../Include/intermediate.h
Intermediate.o: ../Include/ShHandle.h
Intermediate.o: ../Public/ShaderLang.h ../Include/InfoSink.h
Intermediate.o: ../Include/Common.h ../Include/PoolAlloc.h
Intermediate.o: localintermediate.h ../Include/intermediate.h
Intermediate.o: ../Public/ShaderLang.h SymbolTable.h ../Include/Common.h
Intermediate.o: ../Include/intermediate.h ../Include/Types.h
Intermediate.o: ../Include/BaseTypes.h ../Include/ConstantUnion.h
Intermediate.o: ../Include/InfoSink.h RemoveTree.h
ParseHelper.o: ParseHelper.h ../Include/ShHandle.h
ParseHelper.o: ../Public/ShaderLang.h ../Include/InfoSink.h
ParseHelper.o: ../Include/Common.h ../Include/PoolAlloc.h SymbolTable.h
ParseHelper.o: ../Include/Common.h ../Include/intermediate.h
ParseHelper.o: ../Include/Types.h ../Include/BaseTypes.h
ParseHelper.o: ../Include/ConstantUnion.h ../Include/InfoSink.h
ParseHelper.o: localintermediate.h ../Include/intermediate.h
ParseHelper.o: ../Public/ShaderLang.h
ParseHelper.o: ../OSDependent/Linux/osinclude.h
ParseHelper.o: ../Include/InitializeGlobals.h ../Include/PoolAlloc.h
Scan.o: Scan.h
Scan.o: ParseHelper.h SymbolTable.h
Scan.o: glslang_tab.cpp.h
Scan.o: ../Include/Types.h
Scan.o: ScanContext.h preprocessor/PpContext.h preprocessor/PpTokens.h
RemoveTree.o: ../Include/intermediate.h RemoveTree.h
ShaderLang.o: SymbolTable.h ../Include/Common.h ../Include/intermediate.h
ShaderLang.o: ../Include/Common.h ../Include/PoolAlloc.h ../Include/Types.h
ShaderLang.o: ../Include/BaseTypes.h ../Include/ConstantUnion.h
ShaderLang.o: ../Include/InfoSink.h ParseHelper.h ../Include/ShHandle.h
ShaderLang.o: ../Public/ShaderLang.h
ShaderLang.o: ../Include/InfoSink.h localintermediate.h
ShaderLang.o: ../Include/intermediate.h ../Public/ShaderLang.h
ShaderLang.o: ../Include/ResourceLimits.h Initialize.h
SymbolTable.o: SymbolTable.h ../Include/Common.h ../Include/intermediate.h
SymbolTable.o: ../Include/Common.h ../Include/PoolAlloc.h ../Include/Types.h
SymbolTable.o: ../Include/BaseTypes.h ../Include/ConstantUnion.h
SymbolTable.o: ../Include/InfoSink.h
intermOut.o: localintermediate.h ../Include/intermediate.h
intermOut.o: ../Public/ShaderLang.h SymbolTable.h ../Include/Common.h
intermOut.o: ../Include/intermediate.h ../Include/Common.h
intermOut.o: ../Include/PoolAlloc.h ../Include/Types.h ../Include/BaseTypes.h
intermOut.o: ../Include/ConstantUnion.h ../Include/InfoSink.h
intermOut.o: ../Include/ShHandle.h
intermOut.o: ../Public/ShaderLang.h ../Include/InfoSink.h
parseConst.o: ParseHelper.h ../Include/ShHandle.h
parseConst.o: ../Public/ShaderLang.h ../Include/InfoSink.h
parseConst.o: ../Include/Common.h ../Include/PoolAlloc.h SymbolTable.h
parseConst.o: ../Include/Common.h ../Include/intermediate.h
parseConst.o: ../Include/Types.h ../Include/BaseTypes.h
parseConst.o: ../Include/ConstantUnion.h ../Include/InfoSink.h
parseConst.o: localintermediate.h ../Include/intermediate.h
parseConst.o: ../Public/ShaderLang.h
InfoSink.o: ../Include/InfoSink.h
Versions.o: ParseHelper.h  Versions.h ../Include/ShHandle.h SymbolTable.h localintermediate.h
Constant.o: localintermediate.h ../Include/intermediate.h ../Public/ShaderLang.h SymbolTable.h Versions.h
limits.o:  ParseHelper.h
linkValidate.o: localintermediate.h
reflection.o: ../Include/Common.h reflection.h localintermediate.h gl_types.h
