include ../../CONFIG/Make.config

BINARY		= notify
LIBS 	       += -ltyphoon

all:		$(TARGET) $(DBDTARGET) $(HTARGET) $(HNAME)

$(TARGET):	$(OFILES) $(AFILES)
		$(LD) $(OFILES) $(AFILES) -o $(BINARY) $(DEFINES) $(CFLAGS) $(LIBS)
		$(STRIP) $(BINARY)
		$(CHMOD) $(ACCESS) $(BINARY)
		$(CHOWN) $(OWNER).$(GROUP) $(BINARY)
		$(MV) $(BINARY) $(BINDIR)/$(BINARY)
		$(BINDIR)/$(BINARY) --install >.tmpinst
		. .tmpinst
		$(RM) .tmpinst

.depend\
depend dep:	
		$(CPP) -M *.c > .tmpdepend
		$(MV) .tmpdepend .depend

clean:	
		echo $(RM) $(OFILES) *.dbd

include .depend

include $(CONFIGDIR)/Make.RCS
