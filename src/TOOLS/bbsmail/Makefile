include ../../CONFIG/Make.config

BINARY		= bbsmail
TARGET		= $(BINDIR)/$(BINARY)
DUMPIHAVE	= $(BINDIR)/dump-ihave
LIBS 	       += -ltyphoon
CFILES		= bbsmail.c netmail.c utils.c resolve.c msghdr.c \
		  msgnum.c database.c bbsmail_run.c
LDPATH		= LD_RUN_PATH=/lib:/bbslib

all:		$(TARGET) $(DUMPIHAVE)

$(DUMPIHAVE):	dump-ihave.o
		$(LDPATH) $(LD) dump-ihave.o -o dump-ihave $(LDFLAGS) $(AFILES) $(LIBS)
		$(STRIP) dump-ihave
		$(CHMOD) $(ACCESS) dump-ihave
		$(CHOWN) $(OWNER).$(GROUP) dump-ihave
		mkdir -p $(BBSDATA)/msgs/..ihave/
		$(CP) dump-ihave $(BBSDATA)/msgs/..ihave/
		$(MV) dump-ihave $(DUMPIHAVE)

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
