include ../../CONFIG/Make.config

BINARY		= regcnv
CFILES		= $(shell echo *.c)
CPPFLAGS       += -I$(BBSSRC)/MODULES/registry
CFLAGS	       += -I$(BBSSRC)/MODULES/registry

all:		$(TARGET)

$(TARGET):	$(OFILES) $(AFILES)
		$(LD) $(OFILES) $(AFILES) -o $(BINARY) $(DEFINES) $(CFLAGS) $(LIBS)
		$(STRIP) $(BINARY)
		$(CHMOD) $(ACCESS) $(BINARY)
		$(CHOWN) $(OWNER).$(GROUP) $(BINARY)
		$(CP) $(BINARY) $(BINDIR)

.depend\
depend dep:	
		$(CPP) $(CPPFLAGS) -M *.c > .tmpdepend
		$(MV) .tmpdepend .depend

clean:	
		$(RM) $(OFILES) *.dbd

include .depend

include $(CONFIGDIR)/Make.RCS
