INCLUDE = -I. -I.. -I../.. -I../Include -I../Public -I../OSDependent/Linux -I../../OGLCompilersDLL
INCPREPROCESSOR=./preprocessor
INCCODEGEN=./../GenericCodeGen
INCOSDEPENDENT=./../OSDependent/Linux/
INCINITIALISATION=./../../OGLCompilersDLL/
LIBPREPROCESSOR=./preprocessor/libPreprocessor.a
LIBOSDEPENDENT=./../OSDependent/Linux/libOssource.a
LIBINITIALISATION=./../../OGLCompilersDLL/libInitializeDll.a
LIBCODEGEN=./../GenericCodeGen/libCodeGen.a

CXXFLAGS += $(DEFINE) $(INCLUDE) -fPIC
SHAREDOBJECT=./lib/libglslang.so

SRCS= gen_glslang_tab.cpp Initialize.cpp IntermTraverse.cpp \
	Intermediate.cpp ParseHelper.cpp PoolAlloc.cpp limits.cpp \
	RemoveTree.cpp ShaderLang.cpp SymbolTable.cpp intermOut.cpp \
	parseConst.cpp InfoSink.cpp Versions.cpp Constant.cpp Scan.cpp \
	linkValidate.cpp reflection.cpp
OBJECTS := $(SRCS:.cpp=.o)
DEPS := $(addprefix ., $(SRCS:.cpp=.d))

all: $(SHAREDOBJECT)

$(SHAREDOBJECT): $(OBJECTS) $(LIBPREPROCESSOR) $(LIBCODEGEN) $(LIBOSDEPENDENT) $(LIBINITIALISATION)
	$(CXX) -fPIC -shared -o $@ -rdynamic -Wl,-whole-archive $(OBJECTS) $(LIBPREPROCESSOR) $(LIBCODEGEN) $(LIBOSDEPENDENT) $(LIBINITIALISATION) -Wl,-no-whole-archive
	cp $@ ../../Test
	cp $@ ../../Install/Linux

gen_glslang_tab.o : gen_glslang_tab.cpp 
	$(CXX) -fPIC -c $(INCLUDE) gen_glslang_tab.cpp -o $@

gen_glslang_tab.cpp glslang_tab.h: glslang.y
	@echo Generating gen_glslang_tab.cpp
	bison -t -v -d glslang.y
	mv glslang.tab.c gen_glslang_tab.cpp
	mv glslang.tab.h glslang_tab.cpp.h

-include $(DEPS)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -MF $(addprefix ., $(<:.cpp=.d)) -c -o $@ $<

$(LIBPREPROCESSOR):
	$(MAKE) -C $(INCPREPROCESSOR)

$(LIBCODEGEN):
	$(MAKE) -C $(INCCODEGEN)

$(LIBINITIALISATION):
	$(MAKE) -C $(INCINITIALISATION)

$(LIBOSDEPENDENT):
	$(MAKE) -C $(INCOSDEPENDENT)

#
# Cleanup
#
clean :
	$(RM) *.o *.a gen_glslang_tab.cpp glslang_tab.cpp glslang_tab.cpp.h glslang_tab.h glslang.output
	$(RM) ./lib/*.so
	$(MAKE) -C $(INCPREPROCESSOR) clean
	$(MAKE) -C $(INCCODEGEN) clean
	$(MAKE) -C $(INCINITIALISATION) clean
	$(MAKE) -C $(INCOSDEPENDENT) clean

.PHONY : clean $(LIBPREPROCESSOR) $(LIBCODEGEN) $(LIBOSDEPENDENT) $(LIBINITIALISATION)
