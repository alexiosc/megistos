include ../../../CONFIG/Make.config

BINARY		= bbsd
#CFILES		= bbsd.c channels.c respawn.c commands.c shm.c misc.c \
#		  charge.c events.c

METABBS_DIR	= ../rpc.metabbs

ifeq ($(shell [ -e $(METABBS_DIR) ] && echo yes),yes)
#DEFINES       += -DHAVE_METABBS
INCLUDES       += -I $(METABBS_DIR)
AFILES	       += $(METABBS_DIR)/metaservices_clnt.o \
		  $(METABBS_DIR)/metaservices_xdr.o
endif

$(TARGET):	$(AFILES) $(OFILES)
		$(LD) $(OFILES) $(AFILES) -o $(BINARY) $(DEFINES) $(CFLAGS) $(LIBS)
		$(STRIP) $(BINARY)
		$(CHMOD) $(ACCESS) $(BINARY)
		$(CHOWN) $(OWNER).$(GROUP) $(BINARY)
		$(MV) $(BINARY) $(BINDIR)/

ifeq ($(shell [ -e $(METABBS_DIR) ] && echo yes),yes)
$(AFILES):	
		cd $(METABBS_DIR);$(MAKE)
endif

.depend\
depend dep:				
		$(CPP) -M $(CFILES) > .tmpdepend
		$(MV) .tmpdepend .depend

clean:	
		$(RM) $(OFILES)

include .depend


include $(CONFIGDIR)/Make.RCS
