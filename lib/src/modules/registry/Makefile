include ../../CONFIG/Make.config

BINARY		= registry
TARGET		= $(BINDIR)/$(BINARY)
CFILES		= registry.c

# The /r global command

GCSNAME		= registry
GCSPRIORITY	= 40


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
		$(RM) $(OFILES)

include .depend

include $(CONFIGDIR)/Make.RCS
