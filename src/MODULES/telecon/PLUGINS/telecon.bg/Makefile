include ../../../../CONFIG/Make.config

BINARY		= telecon.bg
INCLUDES       += -I$(BBSSRC)/MODULES/telecon
AFILES		= $(LIBDIR)/libplugin.a
CFILES		= plugin.c main.c roll.c subs.c board.c

all:		$(TARGET)

$(TARGET):	$(OFILES) $(AFILES)
		$(LD) $(OFILES) $(AFILES) -o $(BINARY) $(DEFINES) $(CFLAGS) $(LIBS)
		$(STRIP) $(BINARY)
		$(CHMOD) $(ACCESS) $(BINARY)
		$(CHOWN) $(OWNER).$(GROUP) $(BINARY)
		$(MV) $(BINARY) $(BINDIR)/$(BINARY)

.depend\
depend dep:				
		$(CPP) -M *.c > .tmpdepend
		$(MV) .tmpdepend .depend

clean:	
		$(RM) $(OFILES)

include .depend

include $(CONFIGDIR)/Make.RCS
