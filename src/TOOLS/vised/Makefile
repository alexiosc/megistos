include ../../CONFIG/Make.config

BINARY		= vised
INCLUDES       += -I/usr/include/ncurses
LIBS 	       += -lncurses
CFILES		= vised.c display.c edit.c utils.c format.c blocks.c find.c \
		  exit.c

$(TARGET):	$(OFILES) $(AFILES)
		$(LD) $(OFILES) $(AFILES) -o $(BINARY) $(DEFINES) $(CFLAGS) $(LIBS)
		$(STRIP) $(BINARY)
		$(CHMOD) $(ACCESS) $(BINARY)
		$(CHOWN) $(OWNER).$(GROUP) $(BINARY)
		$(MV) $(BINARY) $(BINDIR)/

.depend\
depend dep:				
		$(CPP) -M $(CFILES) > .tmpdepend
		$(MV) .tmpdepend .depend

clean:	
		$(RM) $(OFILES)

include .depend

include $(CONFIGDIR)/Make.RCS
