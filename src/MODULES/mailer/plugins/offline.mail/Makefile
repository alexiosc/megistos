include ../../../../CONFIG/Make.config

BINARY		= offline.mail
LIBS 	       += -ltyphoon $(LINK_ZLIB)
CFILES		= offline.mail.c setup.c qsc.c funcs.c clubhdr.c download.c \
		  qwkout.c request.c attachments.c upload.c clubid.c \
		  controlmsg.c reqman.c
AFILES		= ../../usr.o ../../../clubs/database.o ../../../clubs/dbnum.o \
		  ../../../clubs/dbto.o ../../../clubs/funcs.o ../../cksum.o \
		  ../../xlate.o

DBBASE		= request
DDLNAME		= $(DBBASE).ddl
HNAME		= $(DBBASE).h
HTARGET		= $(BBSSRC)/INCLUDE/$(HNAME)
DBDNAME		= $(DBBASE).dbd
DBDDIR		= $(BBSDATA)/mailer/requests
DBDTARGET	= $(DBDDIR)/$(DBDNAME)

all:		$(TARGET) $(DBDTARGET) $(HNAME)

$(TARGET):	$(OFILES) $(AFILES)
		$(LD) $(OFILES) $(AFILES) -o $(BINARY) $(DEFINES) $(CFLAGS) $(LIBS)
		$(STRIP) $(BINARY)
		$(CHMOD) $(ACCESS) $(BINARY)
		$(CHOWN) $(OWNER).$(GROUP) $(BINARY)
		$(MV) $(BINARY) $(BINDIR)/$(BINARY)
		$(BINDIR)/$(BINARY) --install >.tmpinst
		. .tmpinst
		$(RM) .tmpinst

$(HNAME) $(DBDTARGET) $(DBDNAME): $(DDLNAME)
		$(DDLP) $(DDLNAME)
		$(CP) $(DBDNAME) $(DBDTARGET)
		$(CHOWN) $(DBDOWNER) $(DBDTARGET)
		$(CHMOD) $(DBDACCESS) $(DBDTARGET)

#$(HTARGET): $(DBDNAME) $(HNAME)
#		$(CP) $(HNAME) $(HTARGET)


.depend\
depend dep:	
		$(CPP) -M *.c > .tmpdepend
		$(MV) .tmpdepend .depend

clean:	
		$(RM) $(OFILES) *.dbd

include .depend

include $(CONFIGDIR)/Make.RCS
