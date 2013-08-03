CC=g++
OBJECTPATH=./../glslang/MachineIndependent
LIBPATH=./../glslang/MachineIndependent/lib
SRCS=StandAlone.cpp

TARGETOBJECT=StandAlone.o

default: all

all: glslangValidator

glslangValidator: $(TARGETOBJECT) SHAREDOBJECT
	$(CC) -g -o $@ $(TARGETOBJECT) -L $(LIBPATH) -lglslang -lpthread -lm -lstdc++
	cp $@ ../Test
	cp $@ ../Install/Linux

SHAREDOBJECT:
	cd $(OBJECTPATH); make all

%.o : %.cpp
	$(CC) -g -c -I../glslang/OSDependent/Linux $<

#
# Cleanup
#
.PHONY : clean
clean :
	$(RM) *.o glslangValidator ../Install/Linux/glslangValidator
	cd $(OBJECTPATH); make clean

depend:
	cd $(OBJECTPATH); make depend
	makedepend -Y -- $(SRCS)
# DO NOT DELETE

StandAlone.o: ./../glslang/Include/ShHandle.h
StandAlone.o: ./../glslang/Public/ShaderLang.h
StandAlone.o: ./../glslang/Include/InfoSink.h ./../glslang/Include/Common.h
StandAlone.o: ./../glslang/Include/PoolAlloc.h
StandAlone.o: ./../glslang/Public/ShaderLang.h
StandAlone.o: Worklist.h
