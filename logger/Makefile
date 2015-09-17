#Compiler Directives
CXX=g++
CPPFLAGS=
LDFLAGS=
LIBS=#-lsomething
#Directories
IDIR=include
LDIR=lib
ODIR=obj
#Files
BINFILE= log parse
LSRC= logger.cpp \
 	log_main.cpp
PSRC= parser.cpp \
	parse_main.cpp
_POBJ=$(PSRC:.cpp=.o)
POBJ=$(patsubst %,$(ODIR)/%,$(_POBJ))
_PDEPS= parser.h config.h logstuff.h
PDEPS=$(patsubst %,$(IDIR)/%,$(_PDEPS))

_LOBJ=$(LSRC:.cpp=.o)
LOBJ=$(patsubst %,$(ODIR)/%,$(_LOBJ))
_LDEPS= logger.h config.h logstuff.h
LDEPS=$(patsubst %,$(IDIR)/%,$(_LDEPS))

DEPS=$(LDEPS) $(PDEPS)

#Flag Handling
ifdef DEBUG
CPPFLAGS := $(CPPFLAGS) -g
endif
ifdef VERBOSE
	Q =
	E = @true 
else
	Q = @
	E = @echo 
endif

.PHONY: all help clean

all: $(BINFILE)
help:
	$(E)
	$(E)Helpful Comments
	$(E)

$(ODIR)/%.o: $(LDIR)/%.cpp $(DEPS)
	$(E)C++-compiling $<
	$(Q)if [ ! -d `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(Q)$(CXX) -o $@ -c $< $(CPPFLAGS) -I$(IDIR)

log: $(LOBJ) $(LDEPS)
	$(E)Linking $@
	$(Q)$(CXX) -o $@ $^ $(CPPFLAGS) $(LIBS) $(LDFLAGS)

parse: $(POBJ) $(PDEPS)
	$(E)Linking $@
	$(Q)$(CXX) -o $@ $^ $(CPPFLAGS) $(LIBS) $(LDFLAGS)

arduino:
	$(E) Making a directory for arduino
	$(Q)cp $(IDIR)/logger.h arduino/logger.h
	$(Q)cp $(IDIR)/config.h arduino/config.h
	$(Q)cp $(IDIR)/logstuff.h arduino/logstuff.h
	$(Q)cp $(LDIR)/logger.cpp arduino/logger.cpp

clean:
	$(E)Removing Files
	$(Q)rm -f $(ODIR)/*.o $(BINFILE)
	$(Q)if [ -d $(ODIR) ]; then rmdir $(ODIR); fi
