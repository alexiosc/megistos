include ../../CONFIG/Make.config

BINARY		= fixemail
CFILES		= fixemail.c
CFLAGS+=-g

$(TARGET):	$(OFILES) $(AFILES)
		$(LD) $(OFILES) $(AFILES) -o $(BINARY) $(DEFINES) $(CFLAGS) $(LIBS)
#		$(STRIP) $(BINARY)
		$(CHMOD) $(ACCESS) $(BINARY)
		$(CHOWN) $(OWNER).$(GROUP) $(BINARY)
#		$(MV) $(BINARY) $(BINDIR)/

.depend\
depend dep:				
		$(CPP) -M $(CFILES) > .tmpdepend
		$(MV) .tmpdepend .depend

clean:	
		$(RM) $(OFILES)

include .depend

include $(CONFIGDIR)/Make.RCS
