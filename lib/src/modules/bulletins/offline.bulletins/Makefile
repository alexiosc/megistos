include ../../../../CONFIG/Make.config

BINARY		= offline.bulletins
LIBS 	       += -ltyphoon
CFILES		= offline.bulletins.c setup.c download.c upload.c
AFILES		= ../../usr.o ../../xlate.o \
		  ../offline.mail/request.o \
		  ../../../bulletins/db.o \
		  ../../../clubs/clubhdr.o
DBBASE		= request
DDLNAME		= $(DBBASE).ddl
HNAME		= $(DBBASE).h
HTARGET		= $(BBSSRC)/INCLUDE/$(HNAME)
DBDNAME		= $(DBBASE).dbd
DBDDIR		= $(BBSDATA)/mailer/requests
DBDTARGET	= $(DBDDIR)/$(DBDNAME)

all:		$(TARGET)

$(TARGET):	$(OFILES) $(AFILES)
		$(LD) $(OFILES) $(AFILES) -o $(BINARY) $(DEFINES) $(CFLAGS) $(LIBS)
		$(STRIP) $(BINARY)
		$(CHMOD) $(ACCESS) $(BINARY)
		$(CHOWN) $(OWNER).$(GROUP) $(BINARY)
		$(MV) $(BINARY) $(BINDIR)/$(BINARY)
		$(BINDIR)/$(BINARY) --install >.tmpinst
		. .tmpinst
		$(RM) .tmpinst

#$(HNAME) $(DBDTARGET) $(DBDNAME): $(DDLNAME)
#		$(DDLP) $(DDLNAME)
#		$(CP) $(DBDNAME) $(DBDTARGET)
#		$(CHOWN) $(DBDOWNER) $(DBDTARGET)
#		$(CHMOD) $(DBDACCESS) $(DBDTARGET)

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
