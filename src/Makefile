EXEC=a.out

CC=g++
CPPFLAGS=-c -g -std=c++14 -O2 -flto -Wall -Wextra -Werror \
-Wno-unused-parameter -Wno-unused-result -Wno-unused-variable -Wno-unused-but-set-variable \
-Wconversion
DEPFLAGS=-M
LDFLAGS=-lboost_system -lpthread -O2 -flto

ROOTDIR=..
BUILDDIR=$(ROOTDIR)/work
DEPDIR=$(BUILDDIR)/dep
OBJDIR=$(BUILDDIR)/obj
EXEDIR=$(ROOTDIR)

SOURCES=$(wildcard *.cpp)
DEPS=$(SOURCES:.cpp=.d)
OBJS=$(SOURCES:.cpp=.o)
DEPSFP=$(patsubst %, $(DEPDIR)/%, $(DEPS))
OBJSFP=$(patsubst %, $(OBJDIR)/%, $(OBJS))


$(shell mkdir -p $(DEPDIR) > /dev/null)
$(shell mkdir -p $(OBJDIR) > /dev/null)
$(shell mkdir -p $(EXEDIR) > /dev/null)



$(EXEDIR)/$(EXEC): $(OBJSFP)
	$(CC) $^ -o $(EXEDIR)/$(EXEC) $(LDFLAGS)

$(DEPDIR)/%.d: %.cpp
	@set -e; rm -f $@; \
	$(CC) $(DEPFLAGS) $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*, $(OBJDIR)/$(@F:.d=.o) $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$
.PRECIOUS: $(DEPDIR)/%.d

-include $(DEPSFP)
$(OBJDIR)/%.o: %.cpp $(DEPDIR)/%.d
	$(CC) $(CPPFLAGS) $< -o $@
.PRECIOUS: $(OBJDIR)/%.o

.PHONY: exe
exe: $(EXEDIR)/$(EXEC)


.PHONY: obj
obj: $(OBJSFP)

.PHONY: dep
dep: $(DEPSFP)

.PHONY: clean
clean:
	rm -rf ./$(DEPDIR)/*.d \
	rm -rf ./$(OBJDIR)/*.o \
	rm -rf ./$(EXEDIR)/$(EXEC)
