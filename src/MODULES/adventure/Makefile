include ../../CONFIG/Make.config

BINARY		= adventure
ZIPBINARY	= infoint
ZIPTARGET	= $(BINDIR)/$(ZIPBINARY)
ZIPOFILES	= control.o extern.o fileio.o input.o interpre.o math.o \
		  memory.o object.o operand.o osdepend.o property.o screen.o \
		  text.o unixio.o variable.o zip.o
OFILES		= adventure.o

all:		$(ZIPTARGET) $(TARGET)

$(TARGET):	$(OFILES) $(AFILES)
		$(LD) $(OFILES) $(AFILES) -o $(BINARY) $(DEFINES) $(CFLAGS) $(LIBS)
		$(STRIP) $(BINARY)
		$(CHMOD) $(ACCESS) $(BINARY)
		$(CHOWN) $(OWNER).$(GROUP) $(BINARY)
		$(MV) $(BINARY) $(BINDIR)/
		$(BINDIR)/$(BINARY) --install >.tmpinst
		. .tmpinst
		$(RM) .tmpinst

$(ZIPTARGET):	$(ZIPOFILES) $(AFILES)
		$(LD) $(ZIPOFILES) $(AFILES) -o $(ZIPBINARY) $(DEFINES) $(CFLAGS) $(LIBS)
		$(STRIP) $(ZIPBINARY)
		$(CHMOD) $(ACCESS) $(ZIPBINARY)
		$(CHOWN) $(OWNER).$(GROUP) $(ZIPBINARY)
		$(MV) $(ZIPBINARY) $(BINDIR)/

.depend\
depend dep:				
		$(CPP) -M $(CFILES) > .tmpdepend
		$(MV) .tmpdepend .depend

clean:	
		$(RM) *.o

include .depend

include $(CONFIGDIR)/Make.RCS
