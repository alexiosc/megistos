include ../../CONFIG/Make.config

BINARY		= msged
INCLUDES       += -I/usr/include/ncurses
LIBS 	       += -lncurses
CFILES		= msged.c windows.c parse.c funcs.c

$(TARGET):	$(OFILES) $(AFILES)
		$(LD) $(OFILES) $(AFILES) -o $(BINARY) $(DEFINES) $(CFLAGS) $(LIBS)
		$(STRIP) $(BINARY)
		$(CHMOD) $(ACCESS) $(BINARY)
		$(CHOWN) $(OWNER).$(GROUP) $(BINARY)
		$(MV) $(BINARY) $(BINDIR)/

.depend\
depend dep:				
		for i in *.c;do echo -n "";$(CPP) -M $$i;done > .tmpdepend
		$(MV) .tmpdepend .depend

clean:	
		$(RM) $(OFILES)

include .depend


include $(CONFIGDIR)/Make.RCS
