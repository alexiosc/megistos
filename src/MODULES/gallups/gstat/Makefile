include ../../../CONFIG/Make.config


DEFINES		+= -D__USE_GNU
IOCFILE		= ../io.c
IOOFILE		= ../io.o

CFILES		= gstat.c $(IOCFILE) tree.c handler.c templates.c \
		selout.c comout.c \
		gprintf.c 

BINARY		= gstat
LIBS		+= -lm


INCLUDES	+= -I..

all: rmioofile $(TARGET)

$(TARGET):	msgidx $(OFILES) $(AFILES)
		$(LD) $(OFILES) $(AFILES) -o $(BINARY) $(DEFINES) $(CFLAGS) $(LIBS)
		$(STRIP) $(BINARY)
		$(CHMOD) $(ACCESS) $(BINARY)
		$(CHOWN) $(OWNER).$(GROUP) $(BINARY)
#		$(MV) $(BINARY) $(BINDIR)/
		$(CP) $(BINARY) $(BINDIR)/
		$(RM) $(IOOFILE)

rmioofile:
	$(RM) $(IOOFILE)

msgidx:
	$(BINDIR)/msgidx gstat.msg

.depend\
depend dep:				
		$(CPP) -M $(CFILES) > .tmpdepend
		$(MV) .tmpdepend .depend

clean:	
		$(RM) $(OFILES) $(BINARY)

include .depend

include $(CONFIGDIR)/Make.RCS
