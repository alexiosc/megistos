include ../../CONFIG/Make.config

DDLNAME		= ecdb.ddl
HNAME		= ecdb.h
HTARGET		= $(BBSSRC)/INCLUDE/ecdb.h
DBDNAME		= ecdb.dbd
DBDTARGET	= $(BBSDATA)/msgs/.ecdb.dbd

DDLNAME2	= ihavedb.ddl
HNAME2		= ihavedb.h
HTARGET2	= $(BBSSRC)/INCLUDE/ihavedb.h
DBDNAME2	= ihavedb.dbd
DBDTARGET2	= $(BBSDATA)/msgs/..ihave/ihavedb.dbd

DEFINES		=

CLUBS 		= Makefile.clubs
EMAIL		= Makefile.email

all:	email clubs $(DBDTARGET) $(DBDTARGET2)

clean:
	$(MAKE) -f $(EMAIL) clean
	$(MAKE) -f $(CLUBS) clean

.depend \
depend dep:
	$(RM) -f .tmpdepend
	$(CPP) -M $(CFILES) >> .tmpdepend
	$(MV) .tmpdepend .depend

email:	
	$(MAKE) -f $(EMAIL)

clubs:
	$(MAKE) -f $(CLUBS)

$(HNAME) $(HTARGET) $(DDLTARGET) $(DBDTARGET): $(DDLNAME)
	$(DDLP) $(DDLNAME)
	$(CP) $(DBDNAME) $(DBDTARGET)
	$(CHOWN) $(DBDOWNER) $(DBDTARGET)
	$(CHMOD) $(DBDACCESS) $(DBDTARGET)
	$(CP) $(HNAME) $(HTARGET)

$(HNAME2) $(HTARGET2) $(DDLTARGET2) $(DBDTARGET2): $(DDLNAME2)
	$(DDLP) $(DDLNAME2)
	$(CP) $(DBDNAME2) $(DBDTARGET2)
	$(CHOWN) $(DBDOWNER) $(DBDTARGET2)
	$(CHMOD) $(DBDACCESS) $(DBDTARGET2)
	$(CP) $(HNAME2) $(HTARGET2)

include $(CONFIGDIR)/Make.RCS
