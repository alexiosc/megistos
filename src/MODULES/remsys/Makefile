include ../../CONFIG/Make.config

BINARY		= remsys
CFILES		= remsys.c classkey.c filing.c miscfuncs.c users.c channels.c \
		  statistics.c

# The remote sysop global commands (/invis, /l, /@, /audit)

GCSNAME		= remsys
GCSPRIORITY	= 50

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

gcs $(GCS):	gcs_$(GCSNAME).o
		$(GCSCC) $<

.depend\
depend dep:				
		$(CPP) -M $(CFILES) > .tmpdepend
		$(MV) .tmpdepend .depend

clean:	
		$(RM) $(OFILES)

include .depend


include $(CONFIGDIR)/Make.RCS
