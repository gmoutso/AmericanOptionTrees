# to avoid trouble on systems where the SHELL variable might be inherited from the environment. (This is never a problem with GNU make.)

SHELL = /bin/sh

# The first line clears out the suffix list, the second introduces all suffixes which may be subject to implicit rules

CXX=g++
RM=rm -f
RMDIR=rm -rf

# not all systems have -p 

MKDIR_P = mkdir -p 

# Directories
IDIR=include
OBJDIR=tmp
BINDIR=bin
MAKEDIRS=$(OBJDIR) $(BINDIR)
# Targets in Project
ALLTARGETS=$(BINDIR)/americancalc


vpath %.cpp source mains

CXXFLAGS=-g -Wl,--no-as-needed -std=c++11 $(LDFLAGS) -MMD -MP 
LDFLAGS=-I$(IDIR)
LDLIBS=-lm

all: $(ALLTARGETS)

$(BINDIR)/americancalc: $(addprefix $(OBJDIR)/, AmericanCalc.o americanbinomial.o payoffs.o simplebinomial.o) | $(BINDIR)
	$(LINK.cpp) $^ $(LOADLIBES) $(LDLIBS) -o $@

$(OBJDIR)/%.o : %.cpp | $(OBJDIR)
	$(COMPILE.cpp) $(OUTPUT_OPTION) $<

-include $(OBJDIR)/*.d

.PHONY: directories clean

$(MAKEDIRS):
	$(MKDIR_P) $@

.PHONY: clean

GARBAGE := $(foreach DIR,$(MAKEDIRS),$(DIR)/*)
clean:
	$(RM) $(GARBAGE)
	$(RMDIR) $(MAKEDIRS)

