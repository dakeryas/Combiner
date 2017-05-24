ODIR := ./objects
SDIR := ./src
IDIR := ./include
MAIN := Combiner.cpp
EXECUTABLE := $(patsubst %.cpp,%, $(MAIN))
DESTDIR := /usr/local

MAKEFLAGS := -j$(shell nproc)

CPPFLAGS += -I$(IDIR)
CPPFLAGS += -I$(BOOST_ROOT)/include

OPTFLAGS :=  -O3
CXXFLAGS += -Wall -Wextra -MMD -MP -std=c++14 $(OPTFLAGS)

LDFLAGS += -L$(BOOST_ROOT)/lib -lboost_filesystem -lboost_system -lboost_program_options

OBJS := $(patsubst %.cpp,%.o,$(addprefix $(ODIR)/,$(wildcard *.cpp)))
OBJS += $(patsubst $(SDIR)/%.cpp,$(ODIR)/%.o,$(wildcard $(SDIR)/*.cpp))

DEPS := $(patsubst %.o,%.d, $(OBJS))

.PHONY: all debug install clean

all: $(EXECUTABLE)  

debug: OPTFLAGS := -O0 -g -DDEBUG
debug: all

install: $(EXECUTABLE)
	mkdir -p $(DESTDIR)/bin
	cp $< $(DESTDIR)/bin

$(OBJS): | $(ODIR)
$(ODIR):
	mkdir -p $(ODIR)

$(ODIR)/$(MAIN:.cpp=.o): $(MAIN)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

$(ODIR)/%.o:$(SDIR)/%.cpp $(IDIR)/%.hpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<
	
$(EXECUTABLE):$(OBJS)
	$(CXX) -o $@  $^ $(LDFLAGS)

clean:
	rm -f $(ODIR)/*.o $(DEPS) $(SDIR)/*~ $(IDIR)/*~ $(EXECUTABLE) *~
	
-include $(DEPS)





