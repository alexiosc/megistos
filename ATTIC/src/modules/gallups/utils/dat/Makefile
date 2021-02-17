include ../../../../CONFIG/Make.config

CFILES		= cnvdat.c
BINARY		= cnvdat
INCLUDES	+= -I../../

$(TARGET):	$(OFILES) $(AFILES)
		$(LD) $(OFILES) $(AFILES) -o $(BINARY) $(DEFINES) $(CFLAGS) $(LIBS)
#		$(STRIP) $(BINARY)
		$(CHMOD) $(ACCESS) $(BINARY)
		$(CHOWN) $(OWNER).$(GROUP) $(BINARY)
#		$(MV) $(BINARY) $(BINDIR)/
#		$(BINDIR)/$(BINARY) --install >.tmpinst
#		. .tmpinst
#		$(RM) .tmpinst

.depend\
depend dep:				
		$(CPP) -M $(CFILES) > .tmpdepend
		$(MV) .tmpdepend .depend

clean:	
		$(RM) $(OFILES) $(BINARY)

include .depend

include $(CONFIGDIR)/Make.RCS
