include ../../CONFIG/Make.config

BINARY		= bbsconsole
DEFINES		=
CFILES		= $(shell echo *.c)

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
		$(RM) $(OFILES) $(HNAME1) $(HNAME2) *.dbd

include .depend

include $(CONFIGDIR)/Make.RCS
