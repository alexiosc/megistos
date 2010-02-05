# -*- makefile -*-
#
# $Id: Makefile,v 2.0 2004/09/13 19:44:57 alexios Exp $
#
# $Log: Makefile,v $
# Revision 2.0  2004/09/13 19:44:57  alexios
# Stepped version to recover CVS repository after near-catastrophic disk
# crash.
#
# Revision 1.2  2004/02/29 12:01:31  alexios
# Complete rewrite for the new infrastructure.
#

BBSDIR		= ../..
BINDIR		= $(BBSDIR)/bin
DATADIR		= $(BBSDIR)/data
MBKDIR		= $(DATADIR)/prompts
BBSPREFIX	= $(shell cd ../..; pwd)
MSGIDX		= BBSPREFIX=$(BBSPREFIX) $(BINDIR)/msgidx

include .depend

.depend\
dep\
depend:
	(echo -n "all:"; \
	for a in *msg; do \
		echo -en ' \\\n\t'`echo $$a | sed -e 's/^/$$(MBKDIR)\//' -e 's/msg$$/mbk/'`; \
	done; \
	echo; echo; \
	for a in *msg; do \
		echo `echo $$a | sed -e 's/^/$$(MBKDIR)\//' -e 's/msg$$/mbk/'`: $$a; \
		echo -e '\t@$(MSGIDX) $$<'; \
		echo; \
	done; \
	) > .depend

#	echo -ne "all:" >.tmpall ; \
#	ls *.msg | gawk >>.tmpall -- \
#		'{ MBK=$$0 ; gsub(".msg",".mbk",MBK) ; \
#		printf "\\\n\t\t$(MSGDIR)/%s ",MBK }' ; \
#	echo -e "\n\t\t@echo Done!\n" >>.tmpall; \
#	ls *.msg | fgrep -v "sysvar.msg" | gawk >.tmpdepend -- \
#		'{ MBK=$$0 ; gsub(".msg",".mbk",MBK) ; \
#		printf "$(MSGDIR)/%s:\t%s\n\t\t\t@$(COMPILER) %s\n" \
#			,MBK,$$0,$$0 }' ;\
#	echo -e "$(MSGDIR)/sysvar.mbk:\tsysvar.msg \
#		\n\t\t\t@$(COMPILER) sysvar.msg ; $(MKSYSVAR)" >>.tmpdepend ; \
#	cat .tmpall .tmpdepend >.depend ;\
#	rm -f .tmpall .tmpdepend
#	@echo
#	@echo
#	@echo Phew! That was one LONG command! :-\)
#	@echo

#relink:
#	@./RELINK
#
clean:	
	rm -f .tmpall .tmpdepend .all .depend DEADJOE

test:
	@echo MBKDIR=$(MBKDIR)
	@echo BBSPREFIX=$(BBSPREFIX)

%.mbk:	%.msg
	$(MSGIDX) $<

# End of file.
