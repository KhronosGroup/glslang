SRCS := StandAlone.cpp
OBJECTS := $(SRCS:.cpp=.o)
DEPS := $(addprefix ., $(SRCS:.cpp=.d))

OBJECTPATH=./../glslang/MachineIndependent
LIBPATH=./../glslang/MachineIndependent/lib
SRCS=StandAlone.cpp

CXXFLAGS += -fPIC -I../glslang/OSDependent/Linux

all: glslangValidator

glslangValidator: $(OBJECTS) regenlib
	$(CC) -g -o $@ $(OBJECTS) -L $(LIBPATH) -lglslang -lpthread -lm -lstdc++
	cp $@ ../Test
	cp $@ ../Install/Linux

-include $(DEPS)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -MF $(addprefix ., $(<:.cpp=.d)) -c -o $@ $<

regenlib:
	$(MAKE) -C $(OBJECTPATH)

#
# Cleanup
#
.PHONY : clean glslangValidator regenlib
clean :
	$(RM) *.o glslangValidator ../Install/Linux/glslangValidator
	$(MAKE) -C $(OBJECTPATH) clean
