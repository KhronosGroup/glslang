INCLUDE = -I../

CXXFLAGS=$(DEFINE) $(INCLUDE) -fPIC

SRCS := PpAtom.cpp PpScanner.cpp PpTokens.cpp Pp.cpp PpContext.cpp PpMemory.cpp PpSymbols.cpp
OBJECTS := $(SRCS:.cpp=.o)
DEPS := $(addprefix ., $(SRCS:.cpp=.d))

all : libPreprocessor.a

libPreprocessor.a : $(OBJECTS)
	$(AR) rvu $@ $(OBJECTS)
	ranlib $@

-include $(DEPS)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -MF $(addprefix ., $(<:.cpp=.d)) -c -o $@ $<

#
# Cleanup
#
.PHONY : clean
clean :
	$(RM) *.o *.a
