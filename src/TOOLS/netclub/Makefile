include ../../CONFIG/Make.config

METABBSDIR	= ../../SYSTEM/daemons/rpc.metabbs
BINARY		= netclub
TARGET		= $(BINDIR)/$(BINARY)
LIBS 	       += -ltyphoon $(ZLIB)
INCLUDES       += -I $(METABBSDIR)
AFILES	       += $(METABBSDIR)/metaservices_clnt.o \
		  $(METABBSDIR)/metaservices_xdr.o


all:		$(TARGET)

$(TARGET):	$(OFILES) $(AFILES)
		$(LD) $(OFILES) $(AFILES) -o $(BINARY) $(DEFINES) $(CFLAGS) $(LIBS)
		$(STRIP) $(BINARY)
		$(CHMOD) $(ACCESS) $(BINARY)
		$(CHOWN) $(OWNER).$(GROUP) $(BINARY)
		$(MV) $(BINARY) $(BINDIR)/

.depend\
depend dep:				
		$(CPP) -M *.c > .tmpdepend
		$(MV) .tmpdepend .depend

clean:	
		$(RM) $(OFILES) *.o

include .depend

include $(CONFIGDIR)/Make.RCS
