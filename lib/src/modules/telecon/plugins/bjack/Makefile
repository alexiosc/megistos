# BlackJack Makefile
# Original Makefile bbs/src/MODULES/telecon/PLUGINS/telecon.test/Makefile
# editor : Valis	Summer/Autumn, 1999
# additions/mods by: Alexios Chouchoulas, Summer 2000


include ../../../../CONFIG/Make.config

# BlackJack version
MAJ_VER=0
MIN_VER=7

RCSAUTHOR	= valis
BINARY		= bjack
DEFINES		+= -DMEGISTOS_BBS
INCLUDES	+= -I$(BBSSRC)/MODULES/telecon
CFILES		= bjack.c bjglob.c bjutil.c bjcmd.c bjintrfc.c cards.c
AFILES		= $(LIBDIR)/libplugin.a -lm

MAKENUMBER	= $(shell cat version.mk)
TARFILE		= bjack-$(MAJ_VER).$(MIN_VER).$(MAKENUMBER).tgz
TFLAGS		= --exclude "bjack/RCS/*" --exclude "bjack/misc/*"

all: mkversion $(TARGET)

$(TARGET):	$(OFILES) $(AFILES)
		$(LD) $(OFILES) $(AFILES) -o $(BINARY) $(DEFINES) $(CFLAGS) $(LIBS)
		$(STRIP) $(BINARY)
		$(CHMOD) $(ACCESS) $(BINARY)
		$(CHOWN) $(OWNER).$(GROUP) $(BINARY)
		$(MV) $(BINARY) $(BINDIR)/

mkversion:
	./mkversion.sh $(MAJ_VER) $(MIN_VER)
	@echo 'Version make-number '`cat version.mk`


.depend\
depend dep:
		$(CPP) -M $(CFILES) > .tmpdepend
		$(MV) .tmpdepend .depend

clean:	
		$(RM) $(OFILES)

tar:
#		@$(RM) ../bjack-*.tgz
		@echo Creating $(TARFILE)
		cd .. ; tar cvzf $(TARFILE) $(TFLAGS) bjack/* ; cp $(TARFILE) /tmp


include $(CONFIGDIR)/Make.RCS

include .depend

