include ../CONFIG/Make.config
CFLAGS+=-g
LD_LIBRARY_PATH	= /usr/lib:/lib:./
MAJOR		= $(MAJORVERSION)
MINOR		= $(MINORVERSION)
PATCH		= $(PATCHLEVEL)
VERSION		= $(MAJOR).$(MINOR).$(PATCH)
IMAGE		= libbbs
DLLNAME		= $(IMAGE).so.$(VERSION)
LIBDIR		= $(BBS)/lib
LIBS 		= 

DLLFLAGS	= -shared #-version-info $(MAJOR):$(MINOR):$(shell cat version.mk)
LDFLAGS	       -= -R$(LIBDIR)
LDFLAGS	       += -rpath $(LIBDIR)
LTLINKCMD	= $(CC) $(DLLFLAGS) $(LDFLAGS) -o $(DLLNAME) $(OFILES)
LTCOMPILECMD	= $(CC) $(CFLAGS)

# The built-in global commands

GCSNAME		= builtin
GCSPRIORITY	= 90
#GCS		= $(GCSDIR)/gcs_10_builtin.so

all:            mkversion $(IMAGE).a dll $(GCS)

install:	$(IMAGE).a dll

mkversion:	
		./mkversion.sh $(MAJOR) $(MINOR) $(PATCH)
		touch version.c

dll shared:	$(DLLNAME)
		$(RM) -f $(LIBDIR)/$(DLLNAME)
		$(CP) $(IMAGE).so* $(LIBDIR)
		(cd $(LIBDIR);$(LN) $(DLLNAME) $(IMAGE).so)
		(cd $(LIBDIR);$(LN) $(DLLNAME) $(IMAGE).so.$(MAJOR))
		$(CHOWN) $(OWNER).$(GROUP) $(LIBDIR)/$(IMAGE).s*
		$(CHMOD) $(LIBACCESS) $(LIBDIR)/$(IMAGE).s*

image:		$(LIBDIR)/$(DLLNAME) $(DLLNAME)

$(GCS):		gcs_$(GCSNAME).o
		$(GCSCC) $<

$(DLLNAME):	$(OFILES)
#		$(CC) -shared -Wl,-soname,$(IMAGE).so.$(MAJOR) -o $(DLLNAME) $(OFILES)
		$(LIBTOOL) --mode=link $(LTLINKCMD)


$(IMAGE).a:	$(OFILES)
		$(AR) rcs $(IMAGE).a $(OFILES)

.c.o:
	        $(LIBTOOL) --mode=compile $(LTCOMPILECMD) -c $<

.depend\
depend dep:				
		$(CPP) -M $(CFILES) >.tmpdepend
		$(MV) .tmpdepend .depend

clean:		
		$(RM) -f .depend *.[oa] *.lo core a.out *.sa $(DLLNAME)

include .depend

.PHONY:		clean depend dep image dll shared mkversion install all

include $(CONFIGDIR)/Make.RCS
