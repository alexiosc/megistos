include ../../CONFIG/Make.config

BINARY		= cookie
CFILES		= cookie.c

# The /cookie global command

GCSNAME		= cookie
GCSPRIORITY	= 90

all:		$(TARGET) $(GCS)

$(TARGET):	$(OFILES) $(AFILES)
		$(LD) $(OFILES) $(AFILES) -o $(BINARY) $(DEFINES) $(CFLAGS) $(LIBS)
		$(STRIP) $(BINARY)
		$(CHMOD) $(ACCESS) $(BINARY)
		$(CHOWN) $(OWNER).$(GROUP) $(BINARY)
		$(MV) $(BINARY) $(BINDIR)/
		$(BINDIR)/$(BINARY) --install >.tmpinst
		. .tmpinst
		$(RM) .tmpinst


$(GCS):		gcs_$(GCSNAME).o
		$(GCSCC) $<

.depend\
depend dep:				
		$(CPP) -M $(CFILES) > .tmpdepend
		$(MV) .tmpdepend .depend

clean:	
		$(RM) *.o

include .depend

include $(CONFIGDIR)/Make.RCS
