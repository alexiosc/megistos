include ../../CONFIG/Make.config

BINARY		= telecon
CFILES		= telecon.c init.c channel.c usr.c broadcast.c talk.c \
		  utils.c editprefs.c misc.c accesses.c scan.c \
		  chanusr.c invitations.c chat.c actions.c \
		  substvars.c plugins.c
OFILES  	= telecon.o editprefs.o invitations.o chat.o actions.o \
		  substvars.o

LIBNAME		= $(LIBDIR)/libplugin.a

LIBOFILES	= init.o channel.o usr.o broadcast.o talk.o utils.o misc.o \
		  accesses.o scan.o chanusr.o plugins.o ../clubs/clubhdr.o

AFILES		= $(LIBNAME)

MKACTIONC	= mkaction.c
MKACTIONO	= mkaction.o
MKACTIONB	= mkaction
MKACTIONT	= $(BINDIR)/$(MKACTIONB)

MKPLUGINC	= mkplugin.c
MKPLUGINO	= mkplugin.o
MKPLUGINB	= mkplugin
MKPLUGINT	= $(BINDIR)/$(MKPLUGINB)

all:		$(TARGET) $(MKACTIONT) $(MKPLUGINT) $(LIBNAME)

$(TARGET):	$(OFILES) $(AFILES) $(LIBNAME)
		$(LD) $(OFILES) $(AFILES) -o $(BINARY) $(DEFINES) $(CFLAGS) $(LIBS)
		$(STRIP) $(BINARY)
		$(CHMOD) $(ACCESS) $(BINARY)
		$(CHOWN) $(OWNER).$(GROUP) $(BINARY)
		$(MV) $(BINARY) $(BINDIR)/$(BINARY)
		$(BINDIR)/$(BINARY) --install >.tmpinst
		. .tmpinst
		$(RM) .tmpinst

$(MKACTIONT):	$(MKACTIONO)
		$(LD) $(MKACTIONO) -o $(MKACTIONB) $(DEFINES) $(CFLAGS) $(LIBS)
		$(STRIP) $(MKACTIONB)
		$(CHMOD) $(ACCESS) $(MKACTIONB)
		$(CHOWN) $(OWNER).$(GROUP) $(MKACTIONB)
		$(MV) $(MKACTIONB) $(BINDIR)/$(MKACTIONB)

$(MKPLUGINT):	$(MKPLUGINO)
		$(LD) $(MKPLUGINO) -o $(MKPLUGINB) $(DEFINES) $(CFLAGS) $(LIBS)
		$(STRIP) $(MKPLUGINB)
		$(CHMOD) $(ACCESS) $(MKPLUGINB)
		$(CHOWN) $(OWNER).$(GROUP) $(MKPLUGINB)
		$(MV) $(MKPLUGINB) $(BINDIR)/$(MKPLUGINB)

$(LIBNAME):	$(LIBOFILES)
		$(AR) rcs $(LIBNAME) $(LIBOFILES)
		$(CHMOD) $(LIBACCESS) $(LIBNAME)
		$(CHOWN) $(OWNER).$(GROUP) $(LIBNAME)

.depend\
depend dep:				
		$(CPP) -M *.c > .tmpdepend
		$(MV) .tmpdepend .depend

clean:	
		$(RM) *.o *~ $(LIBNAME)

include .depend

include $(CONFIGDIR)/Make.RCS
