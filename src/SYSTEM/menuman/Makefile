include ../../CONFIG/Make.config

BINARY		= menuman
TARGET		= $(BINDIR)/$(BINARY)
CFILES		= menuman.c

GCSNAME		= go
GCSPRIORITY	= 05

all:		$(TARGET) $(GCS)

$(TARGET):	$(OFILES) $(AFILES)
		$(LD) $(OFILES) $(AFILES) -o $(BINARY) $(DEFINES) $(CFLAGS) $(LIBS)
		$(STRIP) $(BINARY)
		$(CHMOD) $(ACCESS) $(BINARY)
		$(CHOWN) $(OWNER).$(GROUP) $(BINARY)
		$(MV) $(BINARY) $(BINDIR)/

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
