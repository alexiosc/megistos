include ../../../CONFIG/Make.config

BINARY		= listdownload
CFILES		= listdownload.c

$(TARGET):	$(OFILES) $(AFILES)
		$(LD) $(OFILES) $(AFILES) -o $(BINARY) $(DEFINES) $(CFLAGS) $(LIBS)
		$(STRIP) $(BINARY)
		$(MV) $(BINARY) $(BINDIR)/

.depend\
depend dep:				
		$(CPP) -M $(CFILES) > .tmpdepend
		$(MV) .tmpdepend .depend

clean:	
		$(RM) $(OFILES)

include .depend


include $(CONFIGDIR)/Make.RCS
