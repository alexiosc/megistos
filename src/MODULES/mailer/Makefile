include ../../CONFIG/Make.config

BINARY		= mailer
LIBS 	       += -ltyphoon
CFILES		= mailer.c plugindef.c setup.c usr.c download.c upload.c \
		  cksum.c xlate.c

#DBBASE		= bltidx
#DDLNAME	= $(DBBASE).ddl
#HNAME		= $(DBBASE).h
#HTARGET	= $(BBSSRC)/INCLUDE/$(HNAME)
#DBDNAME	= $(DBBASE).dbd
#DBDDIR		= $(BBSDATA)/msgs/..bltdb
#DBDTARGET	= $(DBDDIR)/$(DBDNAME)

all:		$(TARGET) $(DBDTARGET) $(HTARGET) $(HNAME)

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
