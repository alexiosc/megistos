include ../../../CONFIG/Make.config

# We purposefully don't link against the BBS library -- we want this
# to be independent and this is a good way to enforce such a feature.
LIBS	      	= -ltyphoon $(ZLIB)

BASENAME	= metaservices
BINARY		= rpc.metabbs
CFILES		= main.c register.c register_non_megistos.c request_info.c \
		  distclub.c request_ihave_list.c request_message.c
RPCSTUFF_C	= $(BASENAME)_clnt.c
RPCSTUFF_S	= $(BASENAME)_svc.c
RPCSTUFF_X	= $(BASENAME)_xdr.c
CFILES         += $(RPCSTUFF_C) $(RPCSTUFF_S) $(RPCSTUFF_X)
#DEFINES       += -DDEBUG
RPCSTUFF	= $(BASENAME).h $(RPCSTUFF_C)
RPCGENFLAGS_A	= -IK -1
RPCGENFLAGS_S	= -mIK -1

SCRIPT		= -- '{if($$1=="result"&&$$NF=="rqstp);") printf\
		  ("\t__CALL_PREAMBLE__\n%s\n\t__CALL_POSTAMBLE__\n",$$0);\
		  else print;}'

$(TARGET):	$(RPCSTUFF) $(OFILES) $(AFILES)
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
		$(RM) $(OFILES) $(RPCSTUFF) $(RPCSTUFF_C) $(RPCSTUFF_X) $(BASENAME).h $(RPCSTUFF_S)
		> $(BASENAME).h
		touch $(BASENAME).x

$(BASENAME)_clnt.o:$(BASENAME)_clnt.c

$(BASENAME)_svc.o:$(BASENAME)_svc.c

$(BASENAME)_xdr.o:$(BASENAME)_xdr.c

$(RPCSTUFF):	$(BASENAME).x
		$(RM) $(RPCSTUFF_C) $(RPCSTUFF_X) $(BASENAME).h
		$(RPCGEN) $(RPCGENFLAGS_A) $<
		$(RM) $(RPCSTUFF_S)
		$(RPCGEN) $(RPCGENFLAGS_S) $< -o $(BASENAME)_svc.c
		$(AWK) <$(BASENAME)_svc.c >$(BASENAME)_svc.c-kludged $(SCRIPT)
		$(MV) $(BASENAME)_svc.c-kludged $(BASENAME)_svc.c

include .depend


include $(CONFIGDIR)/Make.RCS
