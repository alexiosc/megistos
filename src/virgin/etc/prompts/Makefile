BBSDIR		= ../..
BINDIR		= $(BBSDIR)/bin
LIBDIR		= $(BBSDIR)/lib
COMPILER	= $(BINDIR)/msgidx
MSGDIR		= $(LIBDIR)/prompts
MKSYSVAR	= $(BINDIR)/mksysvar
MSGS		= $(shell echo *.msg)
MBKS		= $(MSGS:.msg=.mbk)

include .depend

.depend\
dep\
depend:	
	@./RELINK
	echo -ne "all:" >.tmpall ; \
	ls *.msg | gawk >>.tmpall -- \
		'{ MBK=$$0 ; gsub(".msg",".mbk",MBK) ; \
		printf "\\\n\t\t$(MSGDIR)/%s ",MBK }' ; \
	echo -e "\n\t\t@echo Done!\n" >>.tmpall; \
	ls *.msg | fgrep -v "sysvar.msg" | gawk >.tmpdepend -- \
		'{ MBK=$$0 ; gsub(".msg",".mbk",MBK) ; \
		printf "$(MSGDIR)/%s:\t%s\n\t\t\t@$(COMPILER) %s\n" \
			,MBK,$$0,$$0 }' ;\
	echo -e "$(MSGDIR)/sysvar.mbk:\tsysvar.msg \
		\n\t\t\t@$(COMPILER) sysvar.msg ; $(MKSYSVAR)" >>.tmpdepend ; \
	cat .tmpall .tmpdepend >.depend ;\
	rm -f .tmpall .tmpdepend
	@echo
	@echo
	@echo Phew! That was one LONG command! :-\)
	@echo

relink:
	@./RELINK

clean:	
	rm -f .tmpall .tmpdepend .all .depend DEADJOE
	cd $(MSGDIR); rm $(MBKS)
