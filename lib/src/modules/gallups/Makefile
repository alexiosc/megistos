include ../../CONFIG/Make.config

CFILES		= gallups.c io.c crc.c
BINARY		= gallups

DOCSRC		= GALLUPS.DOC
FRMSRC		= FORMAT.DOC
SECSRC		= SECURITY.DOC

DOCTRG		= $(BBSDOC)/gallups.doc
FRMTRG		= $(BBSDOC)/gformat.doc
SECTRG		= $(BBSDOC)/gsecure.doc


$(TARGET):	msgidx $(OFILES) $(AFILES)
		$(LD) $(OFILES) $(AFILES) -o $(BINARY) $(DEFINES) $(CFLAGS) $(LIBS)
		$(STRIP) $(BINARY)
		$(CHMOD) $(ACCESS) $(BINARY)
		$(CHOWN) $(OWNER).$(GROUP) $(BINARY)
		$(MV) $(BINARY) $(BINDIR)/
		$(BINDIR)/$(BINARY) --install >.tmpinst
		. .tmpinst
		$(RM) .tmpinst

.depend\
depend dep:				
		$(CPP) -M $(CFILES) > .tmpdepend
		$(MV) .tmpdepend .depend
		$(MAKE) -C gsc dep
		
gsc:
	$(MAKE) -C gsc all
	
gstat:
	$(MAKE) -C gstat all


clean:	
		$(RM) $(OFILES) $(BINARY)

cleanall: clean
		$(MAKE) -C gsc clean
		$(MAKE) -C gstat clean

msgidx:
		$(BINDIR)/msgidx gallups.msg

docs:
	$(CP) $(DOCSRC) $(DOCTRG)
	$(CP) $(FRMSRC) $(FRMTRG)
	$(CP) $(SECSRC) $(SECTRG)

cleandocs:
	$(RM) $(DOCTRG) $(FRMTRG) $(SECTRG)


include .depend

include $(CONFIGDIR)/Make.RCS
