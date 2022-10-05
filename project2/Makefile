CXX=		g++ $(CCFLAGS)
REG=	reg.o
OBJS =		$(REG) 

LIBS=		-pthread

CCFLAGS= -g -Wall

all:	reg

reg:	$(REG)
		$(CXX) -o run $(REG) $(LIBS)


clean:
		rm -f $(OBJS) $(OBJS:.o=.d)
		rm -f run


# These lines ensure that dependencies are handled automatically.
%.d:	%.cpp
	$(SHELL) -ec '$(CC) -M $(CPPFLAGS) $< \
		| sed '\''s/\($*\)\.o[ :]*/\1.o $@ : /g'\'' > $@; \
		[ -s $@ ] || rm -f $@'

include	$(OBJS:.o=.d)


