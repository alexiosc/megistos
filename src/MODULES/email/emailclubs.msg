LEVEL2 {}


ENTRYKEY {Key required to enter the E-mail area: 0} N 0 129

SOPKEY {Key required for privileged E-mail access: 128} N 0 129

WRTKEY {Key required to write E-mail messages: 2} N 0 129

NETKEY {Key required to send network mail messages: 2} N 0 129

RRRKEY {Key required to request return receipts: 2} N 0 129

ATTKEY {Key required to upload file attachments: 2} N 0 129

AFWKEY {Key required to set autoforwarding: 2} N 0 129

SIGCKEY {Key required to change/install signature: 2} N 0 129

DLKEY {Key required to setup/use distribution lists: 5} N 0 129

MSSKEY {Key required to use mass distribution lists: 128} N 0 129

EMCMSG {Can personal club messages be read from the E-mail area: YES} B

DNLCHG {Credit charge for downloading E-mail attachments: 0} N -32767 32767

WRTCHG {Credit charge for writing E-mail messages: 0} N -32767 32767

NETCHG {Credit surcharge for dispatching a message to the network: 3} N -32767 32767

RRRCHG {Credit charge for requesting return receipts: 1} N -32767 32767

ATTCHG {Credit charge for uploading a file attachment: 1} N -32767 32767

SIGCHG {Credits charged for signature change: 5} N -32767 32767

MKAUDD {Make Audit Trail entry for each E-mail download? YES} B

MKAUDU {Make Audit Trail entry for each E-mail upload? YES} B

MAXCCS {Maximum number of carbon copies of a message: 5} N 0 32767


 Electronic Mail messages have a limited lifetime.  This is
 the number of days that a message will be kept on file
 after it is written.

 Type "-1" here to keep all messages around forever.

EMLLIF {Lifetime (days) of each E-Mail message (-1=forever): 20} N -1 32767

MSGLEN {Maximum length of message body (Kbytes): 64} N 1 256

SENDMAIL {/usr/sbin/sendmail} S 30 Binary used to send net mail.

EATTUPL {E-mail attachment file} S 50 File upload description

TMREIDX {Minutes between re-indexing of the message bases: 2880} N 5 32767

TMNETML {Minutes between looking for incoming netmail: 5} N 5 32767

SIGBMAX {Maximum allowed size (bytes) of users' signatures: 256} N 16 1024

SIGLMAX {Maximum number of lines for users' signatures: 4} N 1 32

MAXBNCE {Maximum number of bounces for an autoforwarded message: 10} N 1 100

MAXDLM {Maximum number of members in a distribution list: 10} N 2 256




CLNTRKEY {Key required for entry to the Clubs module: 0} N 0 129

CLSOPKEY {Key required for privileged access to the Clubs module: 10} N 0 129

TLCKEY {Key required to enter Teleconferences from Clubs: 0} N 0 129

BLTKEY {Key required to enter the Club's Bulletin reader: 0} N 0 129

CLBWCHG {Default charge for posting a Club message: 0} N -32767 32767

CLBUCHG {Default charge for uploading a file to a Club: 0} N -32767 32767

CLBDCHG {Default charge for downloading a file from a Club: 0} N -32767 32767

CLBRATE {Credit consumption rate (creds/100 mins) for new clubs (-1=default): -1} N -32767 32767

CLBLIF {Default life (in days) of Club messages (0=forever) 60} N 0 32767

CDNLAUD {Make Audit Trail entry for each Club download? YES} B

CUPLAUD {Make Audit Trail entry for each Club upload? YES} B

DRDAXKEY {Default read access key for new clubs? 0} N 0 129

DDLAXKEY {Default download access key for new clubs? 2} N 0 129

DWRAXKEY {Default write access key for new clubs? 2} N 0 129

DULAXKEY {Default upload access key for new clubs? 2} N 0 129

DEFCLUB {/Megistos} S 15 Default Club for users when first online

MODAXKEY {Key required to modify Club accesses: 128} N 0 129

MODCHKEY {Key required to modify Club charges: 128} N 0 129

MODHDKEY {Key required to modify Club banners/descriptions: 128} N 0 129

TLCPAG {TELE} S 15 Menuman page of Teleconferences

BLTPAG {BULLETINS} S 15 Menuman page of Bulletin reader


ADDNEW {Automatically add new clubs to all user's quickscans: YES} B




LEVEL3 {}


HISTCC {АдлхЪиШнж лжм %s} S 50 Message history: carbon copy


HISTCP {АдлхЪиШнж Шзц %s} S 50 Message history: message copy


HISTFW {ПижрЯуЯЮбЬ Шзц %s} S 50 Message history: forward


HISTNM {Internet mail} S 50 Message history: netmail


HISTRRR {АзцЫЬаеЮ ШдсЪдрйЮк лжм %s} S 50 Message history: return receipt


HISTREP {АзсдлЮйЮ йлж %s} S 50 Message history: reply


HISTAFW {АмлцгШлЮ гЬлШЩхЩШйЮ Шзц %s} S 50 Message history: autoforward


HISTDST {ГаШдЬгЮгтдж} S 50 Message history: distributed


HISTOLR {Off-line} S 50 Message history: off-line


HISTNET {Лтйр Ыаблчжм Шзц %s} S 50 Message history: via network



TIMEOUT1 {
!J[0;1;33mЕЮлжчгЬ ймЪЪдщгЮ ЪаШ лЮд бШЯмйлтиЮйЮ, Шввс лж йчйлЮгШ
ШдШЫЮгажмиЪЬх жиайгтдШ Шзц лШ ШиоЬхШ лжм вцЪр йнсвгШлжк. Ийрк оиЬаШйлЬх дШ
зЬиагтдЬлЬ вхЪж ШбцгЮ...!)
[0;1m} T bbsmail: timed out waiting for message number lock (1)


TIMEOUT2 {
!J[0;1;31mСмЪЪдщгЮ, Шввс Ю бШлсйлШйЮ всЯжмк ЫЬд тоЬа ЫажиЯрЯЬх ШбцгШ.
Ж ШзжЯубЬмйЮ лжм гЮдчгШлжк гШлШащдЬлШа ШдШЪбШйлабс.!)
[0;1m} T bbsmail: timed out waiting for message number lock (2)


NMSGHDR {From: %s <%s>
Subject: %s
Organization: @BBS@ BBS
Content-Transfer-Encoding: 8bit
X-Mailer: @VERSION@
X-MsgHdr-History: %s
X-MsgHdr-FileAttached: %s
X-MsgHdr-LocalMsgNo: %ld
X-MsgHdr-RRR: %s
X-MsgLen: %d

} T bbsmail: net mail header







NEWUEM {***
ЛЮдмгШ лжм дтжм оиуйлЮ "%s".
} T Electronic Mail alert to Sysop of new-user mail


CLUBINFO {[0;1m
!JЖ @BBS@ тоЬа гаШ гЬЪсвЮ ймввжЪу [32m"ЬаЫабщд зЬиажощд"[37m (clubs, SIGs
у forums) зжм навжеЬджчд ймЭЮлуйЬак ЪаШ ц,ла гзжиЬхлЬ дШ нШдлШйлЬхлЬ. ЛаШ
бШа Шмлу ЬхдШа Ю зищлЮ йШк нжис йлЮ ЩсйЮ, йШк ЪиснжмгЬ ШмлцгШлШ йЬ цвШ лШ
clubs.!)

!JЛзжиЬхлЬ дШ ЫЬхлЬ лШ дтШ гЮдчгШлШ цврд лрд clubs зжм тоЬлЬ йлЮ вхйлШ
ЪиуЪжиЮк ШдходЬмйук йШк (ЫЮвШЫу Шмлс йлШ жзжхШ тоЬлЬ "ЬЪЪиШнЬх") гЬ
лЮд Ьдлжву [33mQ[37m Шзц лж бЬдлиабц гЬджч (у [33m/GO CRQS[37m Шзц
жзжмЫузжлЬ йлЮ ЩсйЮ). Ад ЯтвЬлЬ дШ зижйЯШнШаитйЬлЬ clubs йлЮ вхйлШ ЪиуЪжиЮк
ШдходЬмйЮк ("quickscan"), ЫщйлЬ [33mCRQC[37m Шзц лж бЬдлиабц гЬджч (у
[33m/GO CRQC[37m Шзц жзжмЫузжлЬ йлЮ ЩсйЮ).!)

!JСЬ Шмлу лЮ йчдЫЬйу йШк заЯШдцлШлШ ЫЬд ЯШ ЫЬхлЬ дтШ гЮдчгШлШ, Шввс Шзц
Шчиаж лж "quickscan" ЯШ йШк зШижмйасйЬа цвШ лШ дтШ гЮдчгШлШ цврд лрд clubs
зжм йШк ЬдЫаШнтижмд.!)
[0;1m} T User is new, created a fresh quickscan config with ALL clubs.


CHKNCLB {[s[0;1;35mЛаШ йлаЪгу зШиШбШвщ, ЬиЬмдщ лШ clubs...}


NNEWCLB {[u[0;1m[K
[0;1m} T Clubs, no new messages found


NEWCLUB {[u[0;1m[K
!W[5m██[0;1m  !iУзсиожмд [5mдтШ[0;1m гЮдчгШлШ ЪаШ йШк йлак ЬаЫабтк зЬиажотк
(clubs).!)
!0l[0;1m} T Clubs, new mail waiting alert


NEWMAIL {[0;1m
!W[5m██[0;1m  !iУзсиожмд [5mдтШ[0;1m зижйрзабс гЮдчгШлШ йлж ЮвЬближдабц лШомЫижгЬхж ЪаШ йШк.!)
!0l[0;1m} T E-Mail new private mail waiting alert


OLDMAIL {[0;1;32m
!WУзсиожмд зШвас зижйрзабс гЮдчгШлШ йлж ЮвЬближдабц лШомЫижгЬхж ЪаШ йШк.!)
[0;1m} T E-Mail old private mail waiting alert


HOW2READ {[0;1;32m
!WВаШ дШ лШ ЫаШЩсйЬлЬ, ЫщйлЬ [33mERT[32m
([[33mE[32m]mail [[33mR[32m]ead [[33mT[32m]o you)
Шзц лж бЬдлиабц гЬджч.!)
[0;1m} T E-Mail post-alert recommendation


ASKRDNOW {[0;1m
!WЗтвЬлЬ дШ лШ ЫаШЩсйЬлЬ лщиШ; [[33mY[37m]yes=дШа / [[33mN[37m]o=цоа) } T Ask if user wants to read E-mail now

ASKRDERR {[0;1;31m
КмзсгШа, Шмлу Ю ЬзавжЪу ЫЬд ЬхдШа ЫмдШлу.
[0;1m} T Invalid selection for ASKRDNOW

ASKRDDEF {[Enter=[33mN[37m]!) [0m} T Default answer to ASKRDNOW


NOENTRY {[0;1;31m
КмзсгШа, ЫЬд тоЬлЬ зицйЩШйЮ йлж ЖвЬближдабц ТШомЫижгЬхж.
[0;1m} T User does not have access to the E-mail module


EMMNU {[2J[0m[47;1;37m ┌─────────────────────────────────────────────────────────[0;30;47m┐ [40m
[47;1;37m │  [0;47;30m               ЖвЬближдабц ТШомЫижгЬхж                 [0;47;30m│ [40m
[47;1;37m │  [0;47;30m─────────────────────────────────────────────────────  [0;47;30m│ [40m
[47;1;37m │  [0;31;47mA[30mbout E-mail . . . . . . . . . .  ВЬдабтк ПвЮижнжихЬк  [30m│ [40m
[47;1;37m │  [0;31;47mR[30mead your mail  . . . . . . . . .  АдсЪдрйЮ гЮдмгслрд  [30m│ [40m
[47;1;37m │  [0;31;47mW[30mrite message  . . . . . . . . . . Азжйлжву гЮдчгШлжк  [30m│ [40m
[47;1;37m │  [0;31;47mM[30modify message  . . . . . . . . . .  АввШЪу гЮдчгШлжк  [30m│ [40m
[47;1;37m │  [0;31;47mP[30mreferences . . . . . . . . .  Пижйрзабтк зижлагуйЬак  [30m│ [40m
[47;1;37m │  [0;31;47mD[30mistribution list  . . . . . КхйлШ ЫаШджгук гЮдмгслрд  [30m│ [40m
[47;1;37m │                                                         [0;47;30m│ [40m
[47;1;37m │ [0;30;47me[31mX[30mit  . . . . . . . . . . . . . . . . . . . . . ДежЫжк  [30m│ [40m
[47;1;37m └[0;30;47m─────────────────────────────────────────────────────────┘ [0;1m

ЖвЬближдабц лШомЫижгЬхж
ПШиШбШвщ ЫщйлЬ лЮд ЬзавжЪу йШк: [0m} T Electronic mail menu


SHEMMNU {[0;1m
ЖвЬближдабц лШомЫижгЬхж
!WГщйлЬ лЮд ЬзавжЪу йШк ([33mA[37m,[33mR[37m,[33mW[37m,[33mM[37m,[33mP[37m,[33mD[37m,[33mX[37m ЪаШ тежЫж, у [33m?[37m ЪаШ лж гЬджч): !)[0m} T Electronic mail short menu


ERRSEL {[0;1;31m
КмзсгШа, ЫЬд мзсиоЬа Ю ЬзавжЪу "%c".
[0;1m} T Invalid option selection


NOAXES {[0;1;31m
КмзсгШа, ЫЬд тоЬлЬ зицйЩШйЮ йЬ Шмлу лЮд ЬзавжЪу.
[0;1;31m} T User has no access to chosen area


EMLEAVE {[0;1m
ДежЫжк Шзц лж ЖвЬближдабц ТШомЫижгЬхж.
} T Exiting from the Electronic Mail module


ABOUT {[0;1m

!JЛтйр лжм ЮвЬближдабжч лШомЫижгЬхжм гзжиЬхлЬ дШ йлЬхвЬлЬ бШа дШ ЫаШЩсйЬлЬ
лжзабс бШа зШЪбцйгаШ (Internet) гЮдчгШлШ Шзц бШа зижк Ьйск.!)

!JАд оиЮйагжзжаЬхлЬ лЮд зЬиажоу Шмлу ЪаШ зищлЮ нжис, ЫщйлЬ лЮд ЬзавжЪу
[33mP[37m (Preferences, зижлагуйЬак) ЪаШ дШ имЯгхйЬлЬ лак ЫмдШлцлЮлЬк лжм
ШдШЪдрйлЮихжм гЮдмгслрд йчгнрдШ гЬ лак зижйрзабтк йШк зижлагуйЬак.!)

!JЛзжиЬхлЬ дШ ЫаШЩсйЬлЬ гЮдчгШлШ (Ьдлжву [[33mR[37m]ead) бШа дШ йлЬхвЬлЬ
тдШ гудмгШ у гЮдчгШлШ ([[33mW[37m]rite).!)

!JЛзжиЬхлЬ ЬзхйЮк дШ ШввсеЬлЬ лж бЬхгЬдж Ьдцк гЮдчгШлцк йШк (гЬ
[[33mM[37m]odify), у дШ ЫаШЪиспЬлЬ тдШ гудмгШ [[33mM[37m]odify). Амлтк
жа Ычж Ьдлжвтк вЬалжмиЪжчд гцдж йЬ лжзабс гЮдчгШлШ. ГЬд гзжиЬхлЬ дШ
гЬлШЩсвЬлЬ у дШ ЫаШЪиспЬлЬ Internet гЮдчгШлШ зжм тожмд уЫЮ ШзжйлШвЬх.!)

!JТтвжк, гЬ лЮд Ьдлжву [[33mP[37m]references гзжиЬхлЬ дШ имЯгхйЬлЬ лак
зижйрзабтк йШк зижлагуйЬак, Ьдщ гЬ [[33mD[37m]istribution list тоЬлЬ лЮд
ЫмдШлцлЮлШ дШ жихйЬлЬ гхШ вхйлШ Шзц оиуйлЬк/ЫаЬмЯчдйЬак зжм ЯШ
оиЮйагжзжаЬхлШа ЪаШ ЫаШдЬгЮгтдШ гЮдчгШлШ.!)

[0;1m} T About the email module


PMENU {[2J[0m[47;1;37m ┌───────────────────────────────────────────────────────────────────[0;30;47m┐ [40m
[47;1;37m │  [0;47;30m             ПижлагуйЬак ЖвЬближдабжч ТШомЫижгЬхжм               [0;47;30m│ [40m
[47;1;37m │  [0;47;30m───────────────────────────────────────────────────────────────  [0;47;30m│ [40m
[47;1;37m │  [0;31;47m1[30m . . . .  АмлцгШлЮ гЬлШЩхЩШйЮ гЮдмгслрд йЬ бсзжажд сввж оиуйлЮ  [30m│ [40m
[47;1;37m │  [0;31;47m2[30m  . . . . . . . . .  ДайШЪрЪу (quoting) зижЮЪжчгЬджм гЮдчгШлжк  [30m│ [40m
[47;1;37m │  [0;31;47m3[30m . . . . . ДаЫжзжхЮйЮ ЪаШ дтШ гЮдчгШлШ Шгтйрк гЬлс лЮд йчдЫЬйЮ  [30m│ [40m
[47;1;37m │  [0;31;47m4[30m  . . . . . . . . . .  АввШЪу зижйрзабук мзжЪиШнук (signature)  [30m│ [40m
[47;1;37m │                                                                   [0;47;30m│ [40m
[47;1;37m │ [0;30;47me[31mX[30mit  . . . . . . . . . . . . . . . . . . . . . . . . . . ДежЫжк  [30m│ [40m
[47;1;37m └[0;30;47m───────────────────────────────────────────────────────────────────┘ [0;1m
[0;1m} T Preferences, menu


PMENUS {[0;1m
ПижлагуйЬак ЖвЬближдабжч ТШомЫижгЬхжм
!WГщйлЬ лЮд ЬзавжЪу йШк ([33m1[37m,[33m2[37m,[33m3[37m,[33m4[37m,[33mX[37m ЪаШ тежЫж, у [33m?[37m ЪаШ лж гЬджч): !)[0m} T Preferences, short menu


PQUEST1A {[0;1m

!WГщйлЬ лж пЬмЫщдмгж лжм оиуйлЮ ЪаШ лжд жзжхж ЯШ жихйЬлЬ ШмлцгШлЮ
гЬлШЩхЩШйЮ.!) } T Preferences, question 1A, sysop access


PQUEST1IA {[0;1;32m
!JТШ гЮдчгШлШ гЬлШЩаЩсЭждлШа ШмлцгШлШ зижк [37m%s[32m.!)
[0;1m} T Preferences, autoforwarding information 1


PQUEST1IB {[0;1;32m
!JТШ гЮдчгШлШ ЫЬд гЬлШЩаЩсЭждлШа ШмлцгШлШ Шмлу лЮд йлаЪгу.!)
[0;1m} T Preferences, autoforwarding information 2


PQUEST1B {[0;1m

!JАд ЯтвЬлЬ, гзжиЬхлЬ дШ жихйЬлЬ лж пЬмЫщдмгж Ьдцк оиуйлЮ йлжд жзжхж ЯШ
гЬлШЩаЩсЭждлШа ШмлцгШлШ цвШ лШ гЮдчгШлШ зижк Ьйск. Амлц ЬхдШа оиуйагж йЬ
зЬиазлщйЬак зжм оиЬасЭЬлШа дШ ШзжмйасйЬлЬ Шзц лЮд ЩсйЮ ЪаШ гЬЪсвж оиждабц
ЫасйлЮгШ. ГЬд гзжиЬхлЬ дШ гЬлШЩаЩсйЬлЬ лШ гЮдчгШлс йШк гтйр Internet.!)

!JПижйжоу: йЬ зЬихзлрйЮ бмбвабщд гЬлШЩаЩсйЬрд (зо ж А гЬлШЩаЩсЭЬа йлжд Б
бШа ж Б йлжд А), лж йчйлЮгШ ЯШ йлШгШлуйЬа лЮд гЬлШЩхЩШйЮ бШа ЯШ зШиШЫщйЬа лж
гудмгШ йлжд Шиоабц лжм зШиШвузлЮ.!)

!WГщйлЬ лж пЬмЫщдмгж лжм оиуйлЮ, у [33mEnter[37m ЪаШ дШ ШзЬдЬиЪжзжауйЬлЬ лЮд
ШмлцгШлЮ гЬлШЩхЩШйЮ!) } T Preferences, question 1B


PQUEST1D {[Enter=[33m%s[37m] [0m} T Preferences, default value for PQUEST1A


PQUEST1N {[0;1;32m

!JКмзсгШа, гцдж ж оЬаиайлук ймйлугШлжк гзжиЬх дШ жихйЬа ШмлцгШлЮ
гЬлШЩхЩШйЮ. ПШиШбШвжчгЬ йлЬхвлЬ гудмгШ зижк [37mSysop[32m гЬ лж пЬмЫщдмгц
йШк бШа лж пЬмЫщдмгж йлж жзжхж ЯтвЬлЬ дШ гЬлШЩаЩсЭЬлЬ лШ гЮдчгШлс йШк.!)
[0;1m} T Preferences, question 1, no access



PQUEST1U {[0;1;31m
!JКмзсгШа, Шмлцк ж оиуйлЮк ЫЬд мзсиоЬа йлж йчйлЮгШ.!)
[0;1m} T Preferences, question 1, unknown user


PQUEST1O {[0;1;32m
!JЙШвщк, йлж Ьеук цвШ лШ гЮдчгШлШ ЯШ гЬлШЩаЩсЭждлШа йлж гтвжк [37m%s[32m.!)
[0;1m} T Preferences, question 1, autoforwarding set


PQUEST1Y {[0;1;32m
!JЙШвщк, йлж Ьеук лШ гЮдчгШлс ЫЬд ЯШ гЬлШЩаЩсЭждлШа.!)
[0;1m} T Preferences, question 1, autoforwarding disabled


PQUEST2 {[0;1m

!JОлШд ШзШдлслЬ йЬ тдШ гудмгШ, зжввтк нжитк ЯШ ЯтвЬлЬ дШ ЬайсЪЬлЬ
(quote) гтижк лжм зижЮЪжчгЬджм гЮдчгШлжк. ДЫщ гзжиЬхлЬ дШ имЯгхйЬлЬ Шд
ЯтвЬлЬ дШ ймгЩШхдЬа Шмлц. Оа Ьеук ЬзавжЪтк ЬхдШа ЫмдШлтк:!)

  [33m1[37m . .  Тж гудмгШ йлж жзжхж ШзШдлслЬ ЫЬд ЯШ ЬайсЪЬлШа йлЮд ШзсдлЮйЮ.
  [33m2[37m  . . . . . . . . . . . . .  Тж гудмгШ ЯШ ЬайсЪЬлШа йлЮд ШзсдлЮйЮ.
  [33m3[37m . . . . . Тж йчйлЮгШ ЯШ йШк ирлсЬа Шд ЯтвЬлЬ дШ ЪхдЬа Ю ЬайШЪрЪу.

[0;1m} T Preferences, question 2


PQUEST2S {[0;1m
!WГщйлЬ лЮд ЬзавжЪу йШк ([33m1[37m,[33m2[37m,[33m3[37m, у [33mX[37m ЪаШ ШзжЯубЬмйЮ бШа тежЫж):!) [0m} T Preferences, question 2, short menu


PQUEST2R {[0;1;31m
КмзсгШа, ЫЬд мзсиоЬа Шмлу Ю ЬзавжЪу.
[0;1m} T Preferences, question 2, bad option



PQUEST3 {[0;1m

!JАгтйрк Шнжч ймдЫЬЯЬхлЬ, Ю ЩсйЮ йШк ЬдЮгЬищдЬа ЪаШ лмоцд дтШ
гЮдчгШлШ зижк Ьйск. Ад ЯтвЬлЬ, гзжиЬхлЬ дШ ЫаШЩсйЬлЬ лШ дтШ гЮдчгШлс йШк
ЬбЬхдЮ лЮд йлаЪгу, у дШ ймдЫЬЯЬхлЬ бШдждабс йлЮд ЩсйЮ. ДоЬлЬ лак Ьеук
ЬзавжЪтк:!)

  [33m1[37m . . . . Тж йчйлЮгШ Шзвщк йШк ЬдЮгЬищдЬа ЪаШ лмоцд дтШ гЮдчгШлШ.
  [33m2[37m  . . . . . .  Ад мзсиожмд дтШ гЮдчгШлШ, ЯШ лШ ЫаШЩсйЬлЬ Шгтйрк.
  [33m3[37m . .  Тж йчйлЮгШ ЯШ йШк ирлсЬа Шд ЯтвЬлЬ дШ лШ ЫаШЩсйЬлЬ Шгтйрк.

[0;1m} T Preferences, question 3


PQUEST3S {[0;1m
!WГщйлЬ лЮд ЬзавжЪу йШк ([33m1[37m,[33m2[37m,[33m3[37m, у [33mX[37m ЪаШ ШзжЯубЬмйЮ бШа тежЫж):!) [0m} T Preferences, question 3, short menu


PQUEST3R {[0;1;31m
КмзсгШа, ЫЬд мзсиоЬа Шмлу Ю ЬзавжЪу.
[0;1m} T Preferences, question 3, bad option


NOAXSIG {[0;1;31m
!JКмзсгШа, лж ЬзхзЬЫж зицйЩШйук йШк ЫЬд ЬзалитзЬа лЮд ШввШЪу лЮк мзжЪиШнук йШк.!)
[0;1m} T Preferences, access to signature editor denied


CRDSNG {Ш} T Credits, singular form
CRDPLR {Ьк} T Credits, plural form


NOCRSIG {[0;1;31m
!JКмзсгШа, Шввс ЫЬд тоЬлЬ ШибЬлтк гждсЫЬк ЪаШ дШ ШввсеЬлЬ лЮд мзжЪиШну йШк.
Ж ШввШЪу мзжЪиШнук оиЬщдЬлШа [37m%d[31m гждсЫ%s.!)
[0;1m} T Preferences, not enough credits to change signature


SIGCCAN {[0;1;33m
!JЖ ЫаШЫабШйхШ ШбмищЯЮбЬ. Ж мзжЪиШну йШк ЫЬд сввШеЬ.!)
[0;1m} T Preferences, signature not changed


LINSNG {у} T Lines, singular form
LINPLR {тк} T Lines, plural form


SIGLIN {[0;1;33m
!JЖ мзжЪиШну йШк улШд гЬЪШвчлЬиЮ Шзц [37m%d[33m ЪиШгг%s. Оа Ьзазвтжд ЪиШггтк бцзЮбШд.!)
[0;1m} T Preferences, signature truncated


SIGOK {[0;1;32m
!JЖ мзжЪиШну йШк ЬЪбШлШйлсЯЮбЬ, бШа оиЬрЯубШлЬ [37m%d[32m гждсЫ%s.!)
[0;1m} T signature installed, you have been charged


OPONLY {[0;1;33m
!JСмЪЪдщгЮ, лж ЬзхзЬЫж зицйЩШйук йШк ЫЬд ЬзалитзЬа дШ ЪиспЬлЬ гудмгШ зШис
гцдж [37mзижк лжд ХЬаиайлу СмйлугШлжк[33m (Sysop). Ад ЫЬд ЯтвЬлЬ дШ йлЬхвЬлЬ гудмгШ
зижк лжд [37mSysop[33m, ЫщйлЬ X лщиШ.!)
[0;1m} T Write email: can only send email to Sysop


WENCRDS {[0;1;31m
!JГЬд тоЬлЬ ШибЬлтк гждсЫЬк оиуйЮк ЪаШ дШ йлЬхвЬлЬ гЮдчгШлШ ЮвЬближдабжч
лШомЫижгЬхжм. ЛзжиЬхлЬ дШ ШнуйЬлЬ гудмгШ [5mгцдж[0;1;31m йлжд
ХЬаиайлу СмйлугШлжк (Sysop).!)
[0;1m
!JАд ЫЬд ЯтвЬлЬ дШ ШнуйЬлЬ гудмгШ, ЫщйлЬ e[[33mX[0;1m~]it йлЮд ЬзцгЬдЮ ЬищлЮйЮ.!)
} T Write email: not enough credits


WEWHO {[0;1m
ВисплЬ пЬмЫщдмгж у club зжм ЯШ йлЬхвЬлЬ лж гудмгШ
([33m?[37m ЪаШ ЩжуЯЬаШ) [Enter=Sysop]: [0m} T Write email: get recipient of message


WEWHOC {[0;1m
ВисплЬ пЬмЫщдмгж у club зжм ЯШ ШдлаЪиспЬлЬ лж гудмгШ
([33m?[37m ЪаШ ЩжуЯЬаШ) [Enter=Sysop]: [0m} T Write email: get recipient of copied message


WEUNKID {[0;1;31m
!JКмзсгШа, Шмлц лж пЬмЫщдмгж ЫЬд мзсиоЬа.!)
[0;1m} T Write email: unknown user ID


WEHELP1 {[0;1m

!JЛзжиЬхлЬ дШ ЫщйЬлЬ лжд зШиШвузлЮ лжм гЮдчгШлцк йШк рк Ьеук:!)

1. !i!JГщйлЬ лж пЬмЫщдмгж Ьдцк гтвжмк. ЛзжиЬхлЬ дШ ЫщйЬлЬ лж пЬмЫщдмгж
жвцбвЮиж, у дШ ЪиспЬлЬ лжмвсоайлжд лШ зищлШ лихШ ЪисггШлШ. Тж йчйлЮгШ ЯШ
ШдШвсЩЬа лШ мзцвжазШ.!)
!0l
2. !i!JГщйлЬ [33mEnter[37m ЪаШ дШ йлЬхвЬлЬ гудмгШ йлжд Sysop.
ГЬд ЯШ оиЬрЯЬхлЬ ЪаШ Шмлц лж гудмгШ.!)
!0l
3. !i!JГщйлЬ гхШ Internet ЫаЬчЯмдйЮ (user@@host.domain) ЪаШ дШ йлЬхвЬлЬ
гудмгШ йлж Ыхблмж. Ж Ьзазвтжд оитрйЮ Ъа'Шмлу лЮд мзЮиЬйхШ ЬхдШа
[32m%d гждсЫ%s[37m.!)
!0l
4. !i!JГщйлЬ '/' бШа лж цджгШ Ьдцк Club ЪаШ дШ йлЬхвЬлЬ гудмгШ зижк цвжмк
йЬ Шмлц лж Club. Ж оитрйЮ Ъа'Шмлу лЮд мзЮиЬйхШ ЬеШилслШа Шзц лж Club зжм ЯШ
всЩЬа лж гудмгс йШк. ВаШ зЬиаййцлЬиЬк звЮижнжихЬк ШзжлШдЯЬхлЬ йлЮд Ьдлжву
[33mI[37mnformation Шзц лж гЬджч лрд ДаЫабщд ПЬиажощд (Clubs).!)
!0l
5. !i!JХиЮйагжзжауйлЬ лж йоугШ [33m/Club -User[37m ЪаШ дШ йлЬхвЬлЬ гудмгШ
йЬ тдШ ймЪбЬбиагтдж оиуйлЮ User гтйШ йлж club Club. ЛЬ [33m/Club -All[37m
йлтвдЬлЬ лж гудмгШ зижк цвжмк лжмк оиуйлЬк лжм club Club, цзрк ШбиаЩщк бШа
йлЮд зШиШзсдр йчдлШеЮ (4).!)
!0l
[0;1m} T Write email: help for unprivileged users


WEHELP2 {[0;1m6. !i!JГщйлЬ лж цджгШ гаШк вхйлШк ЫаШджгук ЪаШ дШ йлЬхвЬлЬ
ШдлхЪиШнж лжм гЮдчгШлжк йЬ бсЯЬ гтвжк лЮк вхйлШк. Узсиожмд жа Ьеук
вхйлЬк ЫаШджгук:!)
!0l
} T Write email: help on distribution lists, footer


WEHELP3 {      !%s
} T Write email: help on distribution lists


WEHELP4 {} T Write email: help on distribution lists, footer


WEFCAU {[0;1m
!WПШиШбШвщ ЫщйлЬ лж пЬмЫщдмгж Ьдцк гтвжмк, у [33mALL[37m ЪаШ цвжмк:!) [0m} T Write email: forward/copy club/user question


WEFCAUR {[0;1;31m
!JАмлц лж пЬмЫщдмгж ЫЬд мзсиоЬа. ПШиШбШвщ еШдШЫжбагсйлЬ, у ЫщйлЬ [33mX[31m ЪаШ тежЫж.!)
[0;1m} T Write email: forward/copy club/user error


WERNNET {[0;1;31m
!JКмзсгШа, ЫЬд тоЬлЬ зицйЩШйЮ йЬ Шмлу лЮд мзЮиЬйхШ.!)
[0;1m} T Write email: access to netmail denied


WERNNET2 {[0;1;31m
!JКмзсгШа, ЫЬд тоЬлЬ ШибЬлц оицдж оиуйЮк ЪаШ дШ оиЮйагжзжауйЬлЬ Шмлу лЮд
мзЮиЬйхШ.!)
[0;1m} T Write email: not enough credits to send netmail


WERLNEC {[0;1;31m
!JКмзсгШа, ЫЬд тоЬлЬ ШибЬлц оицдж оиуйЮк ЪаШ дШ ймдЬохйЬлЬ лЮд ЫаШджгу
лжм гЮдчгШлжк.!)
[0;1m} T Write email: not enough credits to continue distribution


WERNEC {[0;1;31m
!JКмзсгШа, ЫЬд тоЬлЬ ШибЬлц оицдж оиуйЮк ЪаШ дШ йлЬхвЬлЬ лж гудмгШ.!)
[0;1m} T Write email: not enough credits to send message


WERCLUB {[0;1;31m
!JКмзсгШа, лж ЬзхзЬЫж зицйЩШйук йШк йлж club [37m%s[31m ЫЬд йШк
ЬзалитзЬа лЮд Шзжйлжву гЮдмгслрд.!)
[0;1m} T Write email: club message, access denied


MSGSNG {гудмгШ} T Messages, singular form
MSGPLR {гЮдчгШлШ} T Messages, plural form


DISTBEG {[0;1;32m
!JДббхдЮйЮ ЫаШджгук. ЛзжиЬхлЬ дШ йлШгШлуйЬлЬ лЮд ЫаШджгу затЭждлШк
[33mEnter[32m.!)
[0;1m} T Write email: beginning of distribution


DISTINFO {[0;1;32m
!JТтвжк ЫаШджгук гЮдчгШлжк. СлЬхвШлЬ [37m%d[32m %s.!)
[0;1m} T Write email: distribution information


WECAN {[0;1;31m
!JАбчирйЮ ЫаШЫабШйхШк.!)
[0;1m} T Write email: distribution stoppep prematurely


EWRLERR {[0;1;31m
!JАЪдрйлж цджгШ вхйлШк ЫаШджгук. ГщйлЬ [33m?[31m ЪаШ дШ ЫЬхлЬ лак
мзсиожмйЬк вхйлЬк.!)
[0;1m} T Write email: unknown distribution list name


WERCPOK {[0;1;32m
!JПШиШвузлЮк лжм гЮдчгШлцк йШк ЯШ ЬхдШа лж гтвжк [37m%s[32m.!)
[0;1m} T Write email: confirming recipient of message


WERCPOKN {[0;1;32m
!JТж гудмгс йШк ЯШ йлШвЬх гтйр Internet Mail йлЮд ЫаЬчЯмдйЮ [37m%s[32m.!)
[0;1m} T Write email: confirming recipient of message, net mail


WERCPOKL {[0;1;32m
!JТж гудмгс йШк ЯШ ЫаШдЬгЮЯЬх йлШ гтвЮ лЮк вхйлШк [37m%s[32m.!)
[0;1m} T Write email: confirming recipient of message, dist list


WERCPOKC {[0;1;32m
!JТж гудмгс йШк ЯШ йлШвЬх йлж Club [37m%s[32m, зижк цвжмк.!)
[0;1m} T Write email: confirming recipient of message, club message


WERCPOKU {[0;1;32m
!JТж гудмгс йШк ЯШ йлШвЬх йлж Club [37m%s[32m, зижк [37m%s[32m.!)
[0;1m} T Write email: confirming recipient of message, club message to user


ASKSUBJ {[0;1m
!JГщйлЬ лж ЯтгШ лжм гЮдчгШлцк йШк (63 оШиШблуиЬк): !)[0m} T Asking for the subject of a message


CRDSING {Ш} T 'Credits', singular form

CRDPLUR {Ьк} T 'Credits', plural form


WEATT {[0;1m
!WЗтвЬлЬ дШ ЬзаймдспЬлЬ тдШ ШиоЬхж йЬ Шмлц лж гудмгШ;
(Ж оитрйЮ ЪаШ Шмлу лЮд мзЮиЬйхШ ЬхдШа [32m%d гждсЫ%s[37m)
([[33mУ[0;1m]es=дШа / [[33mN[0;1m]o=цоа):!) [0m} T Write email: ask if file attachment required


WERRR {[0;1m
!WЗтвЬлЬ "ШзцЫЬаеЮ зШиШвШЩук" цлШд Шмлц лж гудмгШ ЫаШЩШйлЬх;
(Ж оитрйЮ ЪаШ Шмлу лЮд мзЮиЬйхШ ЬхдШа [32m%d гждсЫ%s[37m)
([[33mY[0;1m]es=дШа / [[33mN[0;1m]o=цоа):!) [0m} T Write email: ask if return receipt required


WECC {[0;1m
!WЗтвЬлЬ дШ йлЬхвЬлЬ ШдлхЪиШнж йЬ сввж оиуйлЮ;
(Ж оитрйЮ ЪаШ Шмлу лЮд мзЮиЬйхШ ЬхдШа [32m%d гждсЫ%s[37m Шдс ШдлхЪиШнж)
([[33mY[0;1m]es=дШа / [[33mN[0;1m]o=цоа):!) [0m} T Write email: ask if carbon copies required


WEQNCRD {[0;1;31m
!JКмзсгШа, ЫЬд тоЬлЬ звтжд ШибЬлтк гждсЫЬк оиуйЮк ЪаШ дШ ЭЮлуйЬлЬ Шмлу лЮд
мзЮиЬйхШ.!)
[0;1m} T Write email: ran out of credits


WECCAN {[0;1;31m
!WПШиШбШвщ ЬзаЩЬЩШащйлЬ цла ЯтвЬлЬ дШ [37mосйЬлЬ[31m лж гудмгс йШк.!)
[0;1m([[33mY[0;1m]es=дШа / [[33mN[0;1m]o=цоа): [0m} T Write email: ask for confirmation before exiting


WECCND {} T Write email: default answer string for WECCAN


WERRSEL {[0;1;31m
!WПШиШбШвщ ЫщйлЬ [33mY[31m у [33mN[31m.!)
[0;1m} T Write email: invalid answer to question


WEXFERR {[0;1;31m
!JТж ШиоЬхж йШк осЯЮбЬ вцЪр всЯжмк ЬЪЪиШнук/ШдсЪдрйЮк. ПШиШбШвжчгЬ
ЬаЫжзжауйлЬ лжд оЬаиайлу ймйлугШлжк ЪаШ лак ймдЯубЬк зжм жЫуЪЮйШд й'Шмлц лж
всЯжк.!)
[0;1m} T Write email: I/O error, attachment was lost


WEXFER2 {[0;1;33m
!JАзжйлЬхвШлЬ зсдр Шзц тдШ ШиоЬхж. Лцдж лж зищлж ШиоЬхж ЯШ ЬзаймдШнЯЬх йлж
гудмгШ.!)
[0;1m} T Write email: >1 files uploaded; only first file will be attached


WENOATT {[0;1;33m
!JЙШвщк, лж гудмгШ ЯШ зШиШгЬхдЬа орихк ймдЮггтдж ШиоЬхж.!)
[0;1m} T Write email: leaving message without an attached file


WEREEFN {[0;1;37m
Титожд цджгШ ШиоЬхжм: [32m%s[37m

ЗтвЬлЬ дШ ЫщйЬлЬ цджгШ йЬ Шмлц лж ШиоЬхж;

!JАд ШзШдлуйЬлЬ [33mY[37mes (дШа) бШа ЫщйЬлЬ тдШ цджгШ ШиоЬхжм (цзрк з.о.
"FILENAME.EXT"), лцлЬ Шмлц лж цджгШ ШиоЬхжм ЯШ оиЮйагжзжаЮЯЬх бШлс лЮд вупЮ
лжм. Ад ШзШдлуйЬлЬ [33mN[37mo (цоа), лж литожд цджгШ лжм ШиоЬхжм ЯШ
зШиШгЬхдЬа. (АввсЭждлШк лж цджгШ лжм ШиоЬхжм ЫЬд ШввсЭЬлЬ ЙАИ лж ЯтгШ
лжм гЮдчгШлжк)!)

!WЗтвЬлЬ дШ еШдШЫщйЬлЬ лж цджгШ лжм ШиоЬхжм;!)
[0;1m([[33mY[0;1m]es=дШа / [[33mN[0;1m]o=цоа): [0m} T Write email: change/enter filename?


WEFFN {[0;1m
Мтж цджгШ ШиоЬхжм (15 оШиШблуиЬк): [0m} T Write email: reenter filename


WEFFNR {[0;1;31m
!JТж цджгШ лжм ШиоЬхжм зЬиатоЬа гЮ ШзжЫЬблжчк оШиШблуиЬк. ХШиШблуиЬк зжм ЪхдждлШа
ЫЬблжх ЬхдШа оШиШблуиЬк лжм вШладабжч ШвнШЩулжм, ШиаЯгжх, бШа лШ Ьеук йчгЩжвШ:
@ # % ^ ( ) - _ + = [ ] .!)
[0;1m} T Write email: bad characters in filename


WEDFFN {[0;1m
ДдлсеЬа, лж ШиоЬхж йШк ЯШ жджгсЭЬлШа "[32m%s[37m".
Тж ЯтгШ лжм гЮдчгШлжк зШиШгтдЬа "[32m%s[37m".
[0;1m
} T Write email: displaying filename


WECONFS {[0;1;32m
ДзаЩЬЩШащЯЮбЬ: лж гудмгШ [37m%s/%d[32m ШзжЯЮбЬчлЮбЬ.
[0;1m
} T Write email: message written to disk


WECONFC {[0;1;32m
!JДзаЩЬЩШащЯЮбЬ: лж гудмгШ [37m%s/%d[32m ШдлаЪиснЯЮбЬ йлж [37m%s/%d[32m
бШа ЬйлсвЮ зижк [37m%s[32m.!)
[0;1m
} T Write email: message copied


WEALL {Овжмк} T Write email: 'all' string


WECONFL {[0;1;32m!JГаШджгу: лж гудмгШ [37m%d[32m ЬйлсвЮ зижк [37m%s[32m.!)
[0;1m} T Write email: message distributed


WELUNKU {[0;1;31m
!JАдчзШиблжк оиуйлЮк: [37m%s[31m.!)
[0;1m} T Write email: unknown user in distribution list


WENOTFD {[0;1m
!JТж гтвжк [32m%s[37m ЬхдШа ймдЫЬЫЬгтдж, бШа ЬаЫжзжауЯЮбЬ.!)
[0;1m
} T Write email: recipient is online and has been notified


WERNOT {[0;1m***

!JТж гтвжк [32m%s[37m гцвак йШк тйлЬавЬ гудмгШ гЬ ЯтгШ "[32m%s[37m".
ЛзжиЬхлЬ дШ лж ЫаШЩсйЬлЬ ЫхдждлШк Шзц лж бЬдлиабц гЬджч:!)

([33mE[37m)mail = ЮвЬближдабц лШомЫижгЬхж
([33mR[37m)ead  = ШдсЪдрйЮ
([33mT[37m)o    = зицк Ьйск

!J'H ЪиснждлШк [33m/GO ERT[37m Шзц жзжмЫузжлЬ йлЮд ЩсйЮ.!)
[0;1m} T Write email: notification for recipient


WERNOTC {[0;1m***

!JТж гтвжк [32m%s[37m гцвак йШк ШдлтЪиШпЬ гудмгШ гЬ ЯтгШ "[32m%s[37m".
ЛзжиЬхлЬ дШ лж ЫаШЩсйЬлЬ ЫхдждлШк Шзц лж бЬдлиабц гЬджч:!)

([33mE[37m)mail = ЮвЬближдабц лШомЫижгЬхж
([33mR[37m)ead  = ШдсЪдрйЮ
([33mT[37m)o    = зицк Ьйск

!J'H ЪиснждлШк [33m/GO ERT[37m Шзц жзжмЫузжлЬ йлЮд ЩсйЮ.!)
[0;1m} T Write email: notification for recipient, copied message


WERNOTCC {[0;1m***

!JТж гтвжк [32m%s[37m гцвак йШк ШдлтЪиШпЬ йлж club [32m%s[37m
гудмгШ гЬ ЯтгШ "[32m%s[37m".!)
[0;1m} T Write email: notification for recipient, copied message (to club)


WERNOTFW {[0;1m***
!JТж гтвжк [32m%s[37m гцвак йШк зижщЯЮйЬ йлж club [32m%s[37m
гудмгШ гЬ ЯтгШ "[32m%s[37m".!)
[0;1m} T Clubs: notification for recipient, forwarded message (to club)








RDWHAT {[0;1m
!WЗтвЬлЬ дШ ЫаШЩсйлЬ гЮдчгШлШ зжм ЬхдШа:!)

[33mТ[0;1mo  . . . . . . . . . . . . . . . . . . Пицк Ьйск,
[33mP[0;1mrivate  . . .  зижйрзабс (Ьблцк clubs) зицк Ьйск,
[33mF[0;1mrom . . . . . . . . . . . . . . . . . . Азц Ьйск,

!WГщйлЬ лЮд ЬзавжЪу йШк:!) [0m} T Read mail submenu


RDWHATR {[0;1;31m
!WКмзсгШа, ЫЬд мзсиоЬа Шмлу Ю ЬзавжЪу.!)
[0;1m} T Read mail, invalid selection


RDASKNO {[0;1m
!JГщйлЬ лжд ШиаЯгц гЮдчгШлжк Шзц цзжм ЯШ ШиохйЬлЬ, [[33mF[37m]irst
(Пищлж) ЪаШ лж зищлж мзсиожд гудмгШ, [[33mL[37m]ast (ТЬвЬмлШхж)
ЪаШ лж лЬвЬмлШхж гудмгШ, [33mEnter[37m ЪаШ лж литожд гудмгШ
([32m#%ld[37m), у [33m?[0;1m ЪаШ ЩжуЯЬаШ.!)

!WАзц зжаж гудмгШ дШ еЬбадуйЬа Ю ШдсЪдрйЮ; !) [0m} T Read Mail, asking for message number


RDASKNOR {[0;1;31m
!WКмзсгШа, ЫЬд мзсиоЬа Шмлу Ю ЬзавжЪу.!)
[0;1m} T Read mail, error while asking for message number


RDASKH {[0;1m
!JАд зШлуйЬлЬ Шзвщк [33mEnter[37m, ЯШ ШиохйЬлЬ Шзц лж зищлж дтж гудмгШ.
Ад ЫЬд мзсиожмд дтШ гЮдчгШлШ, лцлЬ Ю ШдсЪдрйЮ ЯШ еЬбадуйЬа гЬ лж лЬвЬмлШхж
Шзц лШ зШвас. Ж лЬвЬхШ ([33m.[37m) ЬхдШа айжЫчдШгЮ гЬ лж [33mEnter[37m, 
Шд оиЮйагжзжаЬхлЬ ймдлгуйЬак. ГЮвШЫу Ю Ьдлжву [33mERT.[37m Шзц лж бЬдлиабц
гЬджч йЮгШхдЬа "сгЬйЮ ШдсЪдрйЮ цврд лрд дтрд гЮдмгслрд зижк Ьйск".!)

!JГхдждлШк [33mF[37m (First), ЯШ ШиохйЬлЬ лЮд ШдсЪдрйЮ Шзц лж зШвацлЬиж
ЫаШЯтйагж гудмгШ.!)

!JГхдждлШк [33mL[37m (Last), ЯШ ШиохйЬлЬ лЮд ШдсЪдрйЮ Шзц лж заж зицйнШлж
гудмгШ зжм ЪиснлЮбЬ.!)

!JГщйлЬ [33mX[37m (eXit) Шд ЯтвЬлЬ дШ ЩЪЬхлЬ, Швващк ЫщйлЬ лжд ШиаЯгц лжм
гЮдчгШлжк Шзж лж жзжхж ЯтвЬлЬ дШ ШиохйЬлЬ. Ад ЫЬд мзсиоЬа гудмгШ гЬ Шмлцд лжд
ШиаЯгц лцлЬ ЯШ оиЮйагжзжаЮЯЬх лж зищлж гудмгШ гЬ ШиаЯгц гЬЪШвчлЬиж Шзц Шмлцд
зжм ЫщйШлЬ.!)
[0;1m} T Read Mail, help for RDASKNO


RDNOMSGT {[0;1;33m
!JСмЪЪдщгЮ, ЫЬд мзсиожмд гЮдчгШлШ зицк Ьйск йлж ЖвЬближдабц ТШомЫижгЬхж.!)
[0;1m} T Read mail, no messages to you


RDNOMSGP {[0;1;33m
!JСмЪЪдщгЮ, ЫЬд мзсиожмд зижйрзабс гЮдчгШлШ зицк Ьйск.!)
[0;1m} T Read Mail, no private messages to you


RDNOMSGF {[0;1;33m
!JСмЪЪдщгЮ, ЫЬд мзсиожмд гЮдчгШлШ Шзц Ьйск йлж ЖвЬближдабц ТШомЫижгЬхж.!)
[0;1m} T Read mail, no messages from you


RDTRCLUB {[0;1;32m
!JДиЬмджчгЬ ЪаШ гЮдчгШлШ [37mзижк Ьйск[32m йлШ Clubs.!)
[0;1m} T Read mail, looking for matching messages in the clubs


RDMISS {[0;1m
Тж гудмгШ [32m%d[37m ЫЬд ЩитЯЮбЬ. ДзавтоЯЮбЬ лж звЮйатйлЬиж:
[0;1m} T Read Mail, message number not found


RDSCNM {[0;1m
[[33mN[37m]ext . . . . . . . ДзцгЬдж гудмгШ   [[33mP[37m]revious . . . ПижЮЪжчгЬдж гудмгШ
[[33mR[37m]ead  . . . . . . . . .  АдсЪдрйЮ   [[33m#[37m] . . . . . . АвгШ йЬ сввж гудмгШ
[[33mC[37m]lubs  . . . . ЛЮдчгШлШ йлШ Clubs   e[[33mX[37m]it . . . . . . . . . . . ДежЫжк

Ж ЬзавжЪу йШк ([33m?[37m ЪаШ ЩжуЯЬаШ); } T Read Mail, choices while scanning messages


RDSCNMH {[0;1m

!JЛзжиЬхлЬ дШ ЫщйЬлЬ лак Ьеук Ьдлжвтк йЬ Шмлц лж йЮгЬхж:!)

!W[33mN[37mext:     !iЛЬлШнтиЬйлЬ йлж ЬзцгЬдж гудмгШ, орихк дШ ЫаШЩсйЬлЬ лж литожд.
ЛзжиЬхлЬ дШ оиЮйагжзжауйЬлЬ Шмлу лЮд Ьдлжву ЪаШ тдШ ЬхЫжк Шзвук ШдходЬмйЮк лрд гЮдмгслрд.
ГщйлЬ зжввтк нжитк лЮд Ьдлжву N рк йчдлгЮйЮ, бШа лж йчйлЮгШ ЯШ зижориуйЬа ЬгнШдхЭждлск йШк
лак ЬзабЬнШвхЫЬк (headers) лрд гЮдмгслрд зжм зЬидсЬа. Длйа, гЬ лЮд Ьдлжву [33mNNNN[37m,
Ю ЩсйЮ ЯШ йШк ЫЬхеЬа лак ЬзабЬнШвхЫЬк лрд ЬзцгЬдрд лЬййсирд гЮдмгслрд, бШа ЯШ йлШгШлуйЬа йлж лЬвЬмлШхж.!)
!0l
!W[33mP[37mrevious: !iЛЬлШнтиЬйлЬ йлж зижЮЪжчгЬдж гудмгШ. КЬалжмиЪЬх цзрк ШбиаЩщк бШа Ю зижЮЪжчгЬдЮ Ьдлжву.!)
!0l
!W[33m#[37m:        !iТж йчйлЮгШ ЯШ йШк ЭЮлуйЬа тдШд ШиаЯгц гЮдчгШлжк йлж жзжхж ЯШ гЬлШЩЬхлЬ.
Ад лж гудмгШ ЫЬд ЩиЬЯЬх, ЯШ лжзжЯЬлЮЯЬхлЬ йлж бждладцлЬиж гудмгШ. ЛзжиЬхлЬ бШа ЬЫщ дШ оиЮйагжзжауйЬлЬ
ймдлгуйЬак: Ю Ьдлжву [33m#1000[37m ЯШ йШк зсЬа бШлЬмЯЬхШд йлж гудмгШ 1000.!)
!0l
!W[33mR[37mead:     !iАдсЪдрйЮ лжм литождлжк гЮдчгШлжк. ЛЬлс лЮд ШдсЪдрйЮ тоЬлЬ Ьзазвтжд
ЫмдШлцлЮлЬк оЬаиайгжч лжм гЮдчгШлжк.!)
!0l
[0;1m} T Read Mail, help about scanning commands


RDSCNR {[0;1;31m
КмзсгШа, Шмлу Ю ЬзавжЪу ЫЬд ЬхдШа ЫмдШлу.
[0;1m} T Read Mail, invalid selection from scan menu


RDDEF {[Enter=[33m%c[37m]: [0m} T Read Mail, default value for menus


RDGOHLP {[0;1m
!JЛзжиЬхлЬ дШ гЬлШбадЮЯЬхлЬ йЬ бсзжаж ймЪбЬбиагтдж гудмгШ ЫхдждлШк ЬЫщ
лжд ШиаЯгц лжм. О ШиаЯгцк ЫЬд ЬхдШа ШдсЪбЮ дШ ШдубЬа йЬ мзсиожд гудмгШ:
Шд лж ймЪбЬбиагтдж гудмгШ ЫЬд ЩиЬЯЬх, ЯШ ЩиЬЯЬхлЬ йлж бждладцлЬиж гудмгШ.
ГхдждлШк [33mF[37m (First) ЯШ гЬлШЩЬхлЬ йлж зищлж гудмгШ, Ьдщ гЬ
[33mL[37m (Last) гЬлШбадЬхйлЬ йлж лЬвЬмлШхж гудмгШ.
ВаШ заж ЪиуЪжиШ, гзжиЬхлЬ дШ оиЮйагжзжауйЬлЬ лЮд йчдлгЮйЮ лЮк гжинук
[33m#123[37m Шзц лж зижЮЪжчгЬдж гЬджч, зжм ЯШ йШк зижрЯуйЬа бШлЬмЯЬхШд
йлж гудмгШ 123.!)
[0;1m} T Read Mail, help on '#' command


RDGONUM {[0;1m
!WГщйлЬ лжд ШиаЯгц гЮдчгШлжк зжм ЯШ зижрЯЮЯЬхлЬ, [33mF[37m ЪаШ лж зищлж
гудмгШ, [33mL[37m ЪаШ лж лЬвЬмлШхж, [33m?[37m ЪаШ ЩжуЯЬаШ, у
[33mX[0;1m ЪаШ ШбчирйЮ:!)[0m } T Read Mail, goto what message?


RDBEG {[0;1;33m
ФлсйШлЬ йлЮд Шиоу лрд гЮдмгслрд.
[0;1m} T Read Mail, reached beginning of messages


RDEND {[0;1;33m
ФлсйШлЬ йлж лтвжк лрд гЮдмгслрд.
[0;1m} T Read Mail, reached end of messages


RDDEL {[0;1;31m
!JЕЮлжчгЬ ймЪЪдщгЮ, Шввс лж гудмгШ Шмлц гцвак ЫаЬЪиснЮ.!)
[0;1m} T Read Mail, message has just been deleted, can't read


RDIOERR {[0;1;31m
!JУзуиеЬ йнсвгШ ЬЪЪиШнук/ШдсЪдрйЮк бШлс лЮд ШдсЪдрйЮ лжм гЮдчгШлжк.
ПШиШбШвжчгЬ ЬаЫжзжауйлЬ лжд ХЬаиайлу СмйлугШлжк ЪаШ лак ймдЯубЬк
зжм жЫуЪЮйШд йЬ Шмлц лж всЯжк.!)
[0;1m} T Read Mail, I/O error while reading message


RDRMNU1 {[0;1m
[[33mN[37m]ext . . . . . . . ДзцгЬдж гудмгШ   [[33mP[37m]revious . . . ПижЮЪжчгЬдж гудмгШ
[[33mE[37m]rase . . . .  ГаШЪиШну гЮдчгШлжк   [[33mC[37m]opy  . . . . АдлаЪиШну гЮдчгШлжк
[[33mF[37m]orward  . . ЛЬлШЩхЩШйЮ гЮдчгШлжк   [[33mR[37m]eply  . . . . . . . . . АзсдлЮйЮ
e[[33mX[37m]it  . . . . . . . . . .  ДежЫжк

Ж ЬзавжЪу йШк ([33m?[37m ЪаШ ЩжуЯЬаШ); } T Read Mail, choices after reading message


RDRMNU1H {[0;1m

!JЛзжиЬхлЬ дШ ЫщйЬлЬ лак Ьеук Ьдлжвтк йЬ Шмлц лж йЮгЬхж:!)

!W[33mN[37mext:     !iЛЬлШнтиЬйлЬ йлж ЬзцгЬдж гудмгШ.
ЛзжиЬхлЬ дШ оиЮйагжзжауйЬлЬ Шмлу лЮд Ьдлжву ЪаШ тдШ ЬхЫжк Шзвук ШдходЬмйЮк лрд гЮдмгслрд.
ГщйлЬ зжввтк нжитк лЮд Ьдлжву N рк йчдлгЮйЮ, бШа лж йчйлЮгШ ЯШ зижориуйЬа ЬгнШдхЭждлск йШк
лак ЬзабЬнШвхЫЬк (headers) лрд гЮдмгслрд зжм зЬидсЬа. Длйа, гЬ лЮд Ьдлжву [33mNNNN[37m,
Ю ЩсйЮ ЯШ йШк ЫЬхеЬа лак ЬзабЬнШвхЫЬк лрд ЬзцгЬдрд лЬййсирд гЮдмгслрд, бШа ЯШ йлШгШлуйЬа йлж лЬвЬмлШхж.!)
!0l
!W[33mP[37mrevious: !iЛЬлШнтиЬйлЬ йлж зижЮЪжчгЬдж гудмгШ. КЬалжмиЪЬх цзрк ШбиаЩщк бШа Ю зижЮЪжчгЬдЮ Ьдлжву.!)
!0l
!W[33m#[37m:        !iТж йчйлЮгШ ЯШ йШк ЭЮлуйЬа тдШд ШиаЯгц гЮдчгШлжк йлж жзжхж ЯШ гЬлШЩЬхлЬ.
Ад лж гудмгШ ЫЬд ЩиЬЯЬх, ЯШ лжзжЯЬлЮЯЬхлЬ йлж бждладцлЬиж гудмгШ. ЛзжиЬхлЬ бШа ЬЫщ дШ оиЮйагжзжауйЬлЬ
ймдлгуйЬак: Ю Ьдлжву [33m#1000[37m ЯШ йШк зсЬа бШлЬмЯЬхШд йлж гудмгШ 1000.!)
!0l
!W[33mE[37mrase:    !iГаШЪиШну лжм литождлжк гЮдчгШлжк. ГДМ ЯШ мзсиеЬа ЬзаЩЬЩШхрйЮ. Тж гудмгШ
ЫаШЪиснЬлШа Шгтйрк.!)
!0l
!W[33mC[37mopy:     !iАдлаЪиШну лжм гЮдчгШлжк йЬ бсзжажд сввж зШиШвузлЮ. ВаШ ЩжуЯЬаШ зсдр
йлШ ЬхЫЮ зШиШвузлЮ, ЫщйлЬ [33mC?[37m.!)
!0l
!W[33mF[37morward:  !iПижщЯЮйЮ лжм гЮдчгШлжк йЬ бсзжажд сввж зШиШвузлЮ. Тж гудмгШ ШдлаЪиснЬлШа йлЮд дтШ
ЫаЬчЯмдйЮ. Тж Ыабц йШк ШдлхЪиШнж ЫаШЪиснЬлШа.!)
!0l
!W[33mR[37meply:    !iГЮгажмиЪЬхлШа гудмгШ-ШзсдлЮйЮ зижк лж литожд гудмгШ.!)
!0l
[0;1m} T Read Mail, help about reading messages, version 1


RDRMNU2 {[0;1m
[[33mN[37m]ext . . . . . . . ДзцгЬдж гудмгШ   [[33mP[37m]revious . . . ПижЮЪжчгЬдж гудмгШ
[[33mE[37m]rase . . . .  ГаШЪиШну гЮдчгШлжк   [[33mC[37m]opy  . . . . АдлаЪиШну гЮдчгШлжк
[[33mF[37m]orward  . . ЛЬлШЩхЩШйЮ гЮдчгШлжк   [[33mR[37m]eply  . . . . . . . . . АзсдлЮйЮ
[[33mB[37m]acktrack . . . .  ПШлиабц гудмгШ   e[[33mX[37m]it  . . . . . . . . . .  ДежЫжк

Ж ЬзавжЪу йШк ([33m?[37m ЪаШ ЩжуЯЬаШ); } T Read Mail, menu with backtrack command

                                             
RDRMNU2H {[0;1m

!JЛзжиЬхлЬ дШ ЫщйЬлЬ лак Ьеук Ьдлжвтк йЬ Шмлц лж йЮгЬхж:!)

!W[33mN[37mext:      !iЛЬлШнтиЬйлЬ йлж ЬзцгЬдж гудмгШ.
ЛзжиЬхлЬ дШ оиЮйагжзжауйЬлЬ Шмлу лЮд Ьдлжву ЪаШ тдШ ЬхЫжк Шзвук ШдходЬмйЮк лрд гЮдмгслрд.
ГщйлЬ зжввтк нжитк лЮд Ьдлжву N рк йчдлгЮйЮ, бШа лж йчйлЮгШ ЯШ зижориуйЬа ЬгнШдхЭждлск йШк
лак ЬзабЬнШвхЫЬк (headers) лрд гЮдмгслрд зжм зЬидсЬа. Длйа, гЬ лЮд Ьдлжву [33mNNNN[37m,
Ю ЩсйЮ ЯШ йШк ЫЬхеЬа лак ЬзабЬнШвхЫЬк лрд ЬзцгЬдрд лЬййсирд гЮдмгслрд, бШа ЯШ йлШгШлуйЬа йлж лЬвЬмлШхж.!)
!0l
!W[33mP[37mrevious:  !iЛЬлШнтиЬйлЬ йлж зижЮЪжчгЬдж гудмгШ. КЬалжмиЪЬх цзрк ШбиаЩщк бШа Ю зижЮЪжчгЬдЮ Ьдлжву.!)
!0l
!W[33m#[37m:         !iТж йчйлЮгШ ЯШ йШк ЭЮлуйЬа тдШд ШиаЯгц гЮдчгШлжк йлж жзжхж ЯШ гЬлШЩЬхлЬ.
Ад лж гудмгШ ЫЬд ЩиЬЯЬх, ЯШ лжзжЯЬлЮЯЬхлЬ йлж бждладцлЬиж гудмгШ. ЛзжиЬхлЬ бШа ЬЫщ дШ оиЮйагжзжауйЬлЬ
ймдлгуйЬак: Ю Ьдлжву [33m#1000[37m ЯШ йШк зсЬа бШлЬмЯЬхШд йлж гудмгШ 1000.!)
!0l
!W[33mE[37mrase:     !iГаШЪиШну лжм литождлжк гЮдчгШлжк. ГДМ ЯШ мзсиеЬа ЬзаЩЬЩШхрйЮ. Тж гудмгШ
ЫаШЪиснЬлШа Шгтйрк.!)
!0l
!W[33mC[37mopy:      !iАдлаЪиШну лжм гЮдчгШлжк йЬ бсзжажд сввж зШиШвузлЮ. ВаШ ЩжуЯЬаШ зсдр
йлШ ЬхЫЮ зШиШвузлЮ, ЫщйлЬ [33mC?[37m.!)
!0l
!W[33mF[37morward:   !iПижщЯЮйЮ лжм гЮдчгШлжк йЬ бсзжажд сввж зШиШвузлЮ. Тж гудмгШ ШдлаЪиснЬлШа йлЮд дтШ
ЫаЬчЯмдйЮ. Тж Ыабц йШк ШдлхЪиШнж ЫаШЪиснЬлШа.!)
!0l
!W[33mR[37meply:     !iГЮгажмиЪЬхлШа гудмгШ-ШзсдлЮйЮ зижк лж литожд гудмгШ.!)
!0l
!W[33mB[37macktrack: !iТж литожд гудмгШ ЬхдШа ШзсдлЮйЮ зижк бсзжаж сввж.
ЛЬ Шмлу лЮд Ьдлжву гЬлШнтиЬйлЬ йлж гудмгШ лж жзжхж ШзШдлсЬа лж литожд гудмгШ.!)
!0l
[0;1m} T Read Mail, help about reading messages, version 2


RDRMNU3 {[0;1m
[[33mN[37m]ext . . . . . . . ДзцгЬдж гудмгШ   [[33mP[37m]revious . . . ПижЮЪжчгЬдж гудмгШ
[[33mE[37m]rase . . . .  ГаШЪиШну гЮдчгШлжк   [[33mC[37m]opy  . . . . АдлаЪиШну гЮдчгШлжк
[[33mF[37m]orward  . . ЛЬлШЩхЩШйЮ гЮдчгШлжк   [[33mR[37m]eply  . . . . . . . . . АзсдлЮйЮ
[[33mD[37m]elete user . . . ГаШЪиШну оиуйлЮ   e[[33mX[37m]it  . . . . . . . . . .  ДежЫжк

Ж ЬзавжЪу йШк ([33m?[37m ЪаШ ЩжуЯЬаШ); } T Read Mail, menu with delete user command
                                             

RDRMNU3H {[0;1m

!JЛзжиЬхлЬ дШ ЫщйЬлЬ лак Ьеук Ьдлжвтк йЬ Шмлц лж йЮгЬхж:!)

!W[33mN[37mext:        !iЛЬлШнтиЬйлЬ йлж ЬзцгЬдж гудмгШ.
ЛзжиЬхлЬ дШ оиЮйагжзжауйЬлЬ Шмлу лЮд Ьдлжву ЪаШ тдШ ЬхЫжк Шзвук ШдходЬмйЮк лрд гЮдмгслрд.
ГщйлЬ зжввтк нжитк лЮд Ьдлжву N рк йчдлгЮйЮ, бШа лж йчйлЮгШ ЯШ зижориуйЬа ЬгнШдхЭждлск йШк
лак ЬзабЬнШвхЫЬк (headers) лрд гЮдмгслрд зжм зЬидсЬа. Длйа, гЬ лЮд Ьдлжву [33mNNNN[37m,
Ю ЩсйЮ ЯШ йШк ЫЬхеЬа лак ЬзабЬнШвхЫЬк лрд ЬзцгЬдрд лЬййсирд гЮдмгслрд, бШа ЯШ йлШгШлуйЬа йлж лЬвЬмлШхж.!)
!0l
!W[33mP[37mrevious:    !iЛЬлШнтиЬйлЬ йлж зижЮЪжчгЬдж гудмгШ. КЬалжмиЪЬх цзрк ШбиаЩщк бШа Ю зижЮЪжчгЬдЮ Ьдлжву.!)
!0l
!W[33m#[37m:           !iТж йчйлЮгШ ЯШ йШк ЭЮлуйЬа тдШд ШиаЯгц гЮдчгШлжк йлж жзжхж ЯШ гЬлШЩЬхлЬ.
Ад лж гудмгШ ЫЬд ЩиЬЯЬх, ЯШ лжзжЯЬлЮЯЬхлЬ йлж бждладцлЬиж гудмгШ. ЛзжиЬхлЬ бШа ЬЫщ дШ оиЮйагжзжауйЬлЬ
ймдлгуйЬак: Ю Ьдлжву [33m#1000[37m ЯШ йШк зсЬа бШлЬмЯЬхШд йлж гудмгШ 1000.!)
!0l
!W[33mE[37mrase:       !iГаШЪиШну лжм литождлжк гЮдчгШлжк. ГДМ ЯШ мзсиеЬа ЬзаЩЬЩШхрйЮ. Тж гудмгШ
ЫаШЪиснЬлШа Шгтйрк.!)
!0l
!W[33mC[37mopy:        !iАдлаЪиШну лжм гЮдчгШлжк йЬ бсзжажд сввж зШиШвузлЮ. ВаШ ЩжуЯЬаШ зсдр
йлШ ЬхЫЮ зШиШвузлЮ, ЫщйлЬ [33mC?[37m.!)
!0l
!W[33mF[37morward:     !iПижщЯЮйЮ лжм гЮдчгШлжк йЬ бсзжажд сввж зШиШвузлЮ. Тж гудмгШ ШдлаЪиснЬлШа йлЮд дтШ
ЫаЬчЯмдйЮ. Тж Ыабц йШк ШдлхЪиШнж ЫаШЪиснЬлШа.!)
!0l
!W[33mR[37meply:       !iГЮгажмиЪЬхлШа гудмгШ-ШзсдлЮйЮ зижк лж литожд гудмгШ.!)
!0l
!W[33mD[37melete user: !iТж литожд гудмгШ зЬиатоЬа лШ йлжаоЬхШ Ьдцк дтжм
оиуйлЮ. ЛЬ Шмлу лЮд Ьдлжву ЫаШЪиснЬлЬ лжд оиуйлЮ. ГДМ ЯШ мзсиеЬа ЬзаЩЬЩШхрйЮ лрд зижЯтйЬщд йШк.
О вжЪШиаШйгцк ЯШ гзжиЬх дШ ЬзШдтвЯЬа йЬ оиуйЮ гцдж гЬ оиуйЮ лЮк Ьдлжвук [33mDELETE[37m лжм гЬджч оЬаиайлщд,
бШа гцдж гтоиа лж ЬиоцгЬдж cleanup.!)
!0l
[0;1m} T Read Mail, help about reading messages, version 3


RDRMNU4 {[0;1m
[[33mN[37m]ext . . . . . . . ДзцгЬдж гудмгШ   [[33mP[37m]revious . . . ПижЮЪжчгЬдж гудмгШ
[[33mE[37m]rase . . . .  ГаШЪиШну гЮдчгШлжк   [[33mC[37m]opy  . . . . АдлаЪиШну гЮдчгШлжк
[[33mF[37m]orward  . . ЛЬлШЩхЩШйЮ гЮдчгШлжк   [[33mR[37m]eply  . . . . . . . . . АзсдлЮйЮ
[[33mS[37m]top autofw . АбчирйЮ гЬлШЩхЩШйЮк   e[[33mX[37m]it  . . . . . . . . . .  ДежЫжк

Ж ЬзавжЪу йШк ([33m?[37m ЪаШ ЩжуЯЬаШ); } T Read Mail, menu with stop autofw command
                                             

RDRMNU4H {[0;1m

!JЛзжиЬхлЬ дШ ЫщйЬлЬ лак Ьеук Ьдлжвтк йЬ Шмлц лж йЮгЬхж:!)

!W[33mN[37mext:        !iЛЬлШнтиЬйлЬ йлж ЬзцгЬдж гудмгШ.
ЛзжиЬхлЬ дШ оиЮйагжзжауйЬлЬ Шмлу лЮд Ьдлжву ЪаШ тдШ ЬхЫжк Шзвук ШдходЬмйЮк лрд гЮдмгслрд.
ГщйлЬ зжввтк нжитк лЮд Ьдлжву N рк йчдлгЮйЮ, бШа лж йчйлЮгШ ЯШ зижориуйЬа ЬгнШдхЭждлск йШк
лак ЬзабЬнШвхЫЬк (headers) лрд гЮдмгслрд зжм зЬидсЬа. Длйа, гЬ лЮд Ьдлжву [33mNNNN[37m,
Ю ЩсйЮ ЯШ йШк ЫЬхеЬа лак ЬзабЬнШвхЫЬк лрд ЬзцгЬдрд лЬййсирд гЮдмгслрд, бШа ЯШ йлШгШлуйЬа йлж лЬвЬмлШхж.!)
!0l
!W[33mP[37mrevious:    !iЛЬлШнтиЬйлЬ йлж зижЮЪжчгЬдж гудмгШ. КЬалжмиЪЬх цзрк ШбиаЩщк бШа Ю зижЮЪжчгЬдЮ Ьдлжву.!)
!0l
!W[33m#[37m:           !iТж йчйлЮгШ ЯШ йШк ЭЮлуйЬа тдШд ШиаЯгц гЮдчгШлжк йлж жзжхж ЯШ гЬлШЩЬхлЬ.
Ад лж гудмгШ ЫЬд ЩиЬЯЬх, ЯШ лжзжЯЬлЮЯЬхлЬ йлж бждладцлЬиж гудмгШ. ЛзжиЬхлЬ бШа ЬЫщ дШ оиЮйагжзжауйЬлЬ
ймдлгуйЬак: Ю Ьдлжву [33m#1000[37m ЯШ йШк зсЬа бШлЬмЯЬхШд йлж гудмгШ 1000.!)
!0l
!W[33mE[37mrase:       !iГаШЪиШну лжм литождлжк гЮдчгШлжк. ГДМ ЯШ мзсиеЬа ЬзаЩЬЩШхрйЮ. Тж гудмгШ
ЫаШЪиснЬлШа Шгтйрк.!)
!0l
!W[33mC[37mopy:        !iАдлаЪиШну лжм гЮдчгШлжк йЬ бсзжажд сввж зШиШвузлЮ. ВаШ ЩжуЯЬаШ зсдр
йлШ ЬхЫЮ зШиШвузлЮ, ЫщйлЬ [33mC?[37m.!)
!0l
!W[33mF[37morward:     !iПижщЯЮйЮ лжм гЮдчгШлжк йЬ бсзжажд сввж зШиШвузлЮ. Тж гудмгШ ШдлаЪиснЬлШа йлЮд дтШ
ЫаЬчЯмдйЮ. Тж Ыабц йШк ШдлхЪиШнж ЫаШЪиснЬлШа.!)
!0l
!W[33mR[37meply:       !iГЮгажмиЪЬхлШа гудмгШ-ШзсдлЮйЮ зижк лж литожд гудмгШ.!)
!0l
!W[33mS[37mtop autofw: !iТж литожд гудмгШ йШк тоЬа гЬлШЩаЩШйлЬх (forward) ШмлцгШлШ Шзц бсзжажд
оиуйлЮ. ОвШ лШ гЮдчгШлШ зижк Шмлц лжд оиуйлЮ ЯШ гЬлШЩаЩсЭждлШа ШмлцгШлШ зижк Ьйск. Дсд Шмлц йШк ЬхдШа ЬджовЮлабц,
оиЮйагжзжауйлЬ Шмлу лЮд Ьдлжву ЪаШ дШ ШбмищйЬлЬ лЮд ШмлцгШлЮ гЬлШЩхЩШйЮ лжм ймЪбЬбиагтджм оиуйлЮ зижк Ьйск. ПШиШбШвжчгЬ
ЬаЫжзжауйлЬ лжд оиуйлЮ ЪаШ Шмлу лЮд ЬдтиЪЬаШ.!)
!0l
[0;1m} T Read Mail, help about reading messages, version 4


RDMNUR {[0;1;31m
!JКмзсгШа, Шмлу Ю ЬзавжЪу ЫЬд ЬхдШа ЫмдШлу.!)
[0;1m} T Read Mail, invalid selection from read menu


RDSAR1 {[0;1;31m
!JКмзсгШа, Шмлц лж гудмгШ ЫЬд тоЬа гЬлШЩаЩШйлЬх ШмлцгШлШ зижк Ьйск.!)
[0;1m} T Read Mail, stop autofw, message has not been autofw'ed


RDSAR2 {[0;1;31m
!JТж гтвжк [37m%s[31m тоЬа ЫаШЪиШнЬх.!)
[0;1m} T Read Mail, stop autofw, user not found


RDSAR3 {[0;1;31m
!JКмзсгШа, лж гтвжк [37m%s[31m ЫЬд гЬлШЩаЩсЭЬа звтжд лШ гЮдчгШлс лжм зижк Ьйск.!)
[0;1m} T Read Mail, stop autofw, user does not forward any more


RDSAI {[0;1m
!JОвШ лШ гЮдчгШлШ зижк [32m%s[37m гЬлШЩаЩсЭждлШа ШмлцгШлШ зижк Ьйск.
АзШдлщдлШк бШлШнШлабс йлЮд ЬзцгЬдЮ ЬищлЮйЮ,
ШбмищдЬлЬ лЮд Ьдлжву ШмлцгШлЮк гЬлШЩхЩШйЮк зижк Ьйск.!)
[0;1m} T Read Mail, stop autofw, information


RDSAQ {[0;1m
!WЗтвЬлЬ дШ йлШгШлуйЬлЬ лЮд ШмлцгШлЮ зижщЯЮйЮ лрд гЮдмгслрд лжм
зШиШзсдр гтвжмк зижк Ьйск; [[33mY[37m]yes=дШа / [[33mN[37m]o=цоа)!) [0m} T Read Mail, stop autofw question


RDSAQR {[0;1;31m
!JАмлу Ю ЬзавжЪу ЫЬд ЬхдШа ЫмдШлу.!)
[0;1m} T Read Mail, stop autofw, invalid response


RDSAC {[0;1;32m
!JЖ ШмлцгШлЮ гЬлШЩхЩШйЮ ЫЬд ШбмищЯЮбЬ.!)
[0;1m} T Read Mail, stop autofw, autoforwarding not stopped


RDSAS {[0;1;32m
!JЖ ШмлцгШлЮ гЬлШЩхЩШйЮ ШбмищЯЮбЬ.!)
[0;1m} T Read Mail, stop autofw, autoforwarding stopped


RDMSGHDR {[0m
} T Read Mail, body of message, header


RDMSGFTR {} T Read Mail, body of message, footer


DUERR {[0;1;31m
!JКмзсгШа, ж оиуйлЮк ЫЬд мзсиоЬа звтжд.!)
[0;1m} T Delete user, user does not exist


DUDEL {[0;1;31m
!JКмзсгШа, ж оиуйлЮк тоЬа уЫЮ йЮгЬарЯЬх ЪаШ ЫаШЪиШну. ЛзжиЬхлЬ дШ лжд ШдШйлуйЬлЬ ЫхдждлШк лЮд Ьдлжву DELETE Шзц лж гЬджч лрд оЬаиайлщд, зиад лж ЬиоцгЬдж cleanup.!)
[0;1m} T Delete user, user is already marked for deletion


DUOK {[0;1;31m
!JДдлсеЬа, ж оиуйлЮк ЫаЬЪиснЮ. ЛзжиЬхлЬ дШ лжд ШдШйлуйЬлЬ ЫхдждлШк лЮд Ьдлжву DELETE Шзц лж гЬджч лрд оЬаиайлщд, зиад лж ЬиоцгЬдж cleanup.!)
[0;1m} T Delete user, user deleted


DUXM {[0;1;31m
!JГЬд гзжиЬхлЬ дШ ЫаШЪиспЬлЬ Шмлц лжд оиуйлЮ.!)
[0;1m} T Delete user, can't delete this user



QMASK {[0;1m
!WЗтвЬлЬ дШ ЬайсЪЬлЬ (quote) лж зижк ШзсдлЮйЮ гудмгШ йлЮд ШзсдлЮйу йШк;
[[33mY[37m]yes=дШа / [[33mN[37m]o=цоа):!) [0m} T Quote message question


QMERR {[0;1;31m
!JПШиШбШвщ ШзШдлуйлЬ йлЮд ЬищлЮйЮ гЬ [33mY[31m (дШа), у [33mN[31m
(цоа), у ЫщйлЬ [33mX[31m ЪаШ ШбчирйЮ лЮк ШзсдлЮйЮк.!)
[0;1m} T Quote message, invalid answer


MMINFO {[0;1m
!JЛЬ Шмлу лЮд Ьдлжву гзжиЬхлЬ дШ ШввсеЬлЬ лШ зЬиаЬоцгЬдШ Ьдцк гЮдчгШлжк зжм
тоЬлЬ уЫЮ йлЬхвЬа.!)

!JСЮгЬащйлЬ цла, Ьдщ гзжиЬхлЬ дШ ШввсеЬлЬ лШ зЬиаЬоцгЬдШ
Ьдцк гЮдчгШлжк зжм тоЬа ЫаШЩаЩШйлЬх гтйр Internet Mail, Шмлц зжм ШввсЭЬлЬ
ЬхдШа ЛОМО лж лжзабц ШдлхЪиШнж лжм гЮдчгШлжк. Тж хЫаж лж гудмгШ тоЬа уЫЮ
ШзжйлШввЬх бШа ЫЬд гзжиЬх дШ ШввШоЯЬх.!)
[0;1m} T Modify Message, information


MMASK {[0;1m
!WПжаж гудмгШ ЯтвЬлЬ дШ гЬлШЩсввЬлЬ; ГщйлЬ лжд ШиаЯгц лжм гЮдчгШлжк
([33m%d[37m-[33m%d[37m):!) [0m} T Modify Message, question


MMERR1 {[0;1;31m
!JКмзсгШа, лж гудмгШ [37m%d[31m ЫЬд мзсиоЬа у ЫЬд лж тоЬлЬ йлЬхвЬа
ЬйЬхк.!)
[0;1m} T Modify Message, can't use that message number


MMERR2 {[0;1;31m
!JКмзсгШа, ЫЬд гзжиЬхлЬ дШ гЬлШЩсввЬлЬ Шмлц лж гудмгШ.!)
[0;1m} T Modify Message, can't modify this message


MMERR3 {[0;1;31m
!JГщйлЬ тдШд ШиаЯгц гЬлШеч [37m%d[31m бШа [37m%d[31m.!)
[0;1m} T Modify Message, message number out of bounds


EMERR {[0;1;31m
!JКмзсгШа, ЫЬд гзжиЬхлЬ дШ ЫаШЪиспЬлЬ Шмлц лж гудмгШ.!)
[0;1m} T Erase Message, can't erase this message


EMXMPT {[0;1;31m
!JКмзсгШа, Шмлц лж гудмгШ ЬхдШа гЮ ЫаШЪиспагж (exempt).!)
[0;1m} T Erase Message, can't erase this message



USING {[0;1;31m
!JЙсзжажк сввжк оиуйлЮк ЬиЪсЭЬлШа гЬ Шмлц лж гудмгШ.
ПШиШбШвщ зЬиагтдЬлЬ вхЪЮ щиШ зиад еШдШзижйзШЯуйЬлЬ.!)
} T Can't mess with message due to conflicts


MMVT {[0;30;47m ┌─────────────────────────── [34mЛЬлШЩжву гЮдчгШлжк[0;30;47m ───────────────────────────[0;1;37;47m┐ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │  ЗтгШ . . . . . . . . . . [1;44;37m@63;43;0s[0;1;47;37m  │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │  АиоЬхж  . . . . . . . .  [1;44;37m@16;16;0s[0;1;47;37m                             │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │  АзцЫЬаеЮ АдсЪдрйЮк . . . [0;30;46m [@"X "t] [1;47;37m                                          │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │  Ctrl-R ЪаШ ЩжуЯЬаШ                                                      [1;37m│ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │             [0;1;42;33m@14;"ЙЬхгЬдж"b[0;47;30m▄    [0;1;42;33m@14;"OK"b[0;47;30m▄    [0;1;41;33m@14;"Абмиж"b[0;47;30m▄  [0;1;47;37m│ [0m
[30;47m │              ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀     ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀     ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀  [0;1;47;37m│ [0m
[30;47m └[0;1;37;47m──────────────────────────────────────────────────────────────────────────┘ [0m} T Message edit visual template


MMWARN1 {[0;1;33m
!JТж гудмгШ ЫЬд тоЬа ймдЮггтдж ШиоЬхж.
ГЬд мзуиоЬ вцЪжк дШ ШввсеЬлЬ лж цджгШ лжм ШиоЬхжм.!)
[0;1m} T Modify message, warning 1: no attached file, filename not changed


MMWARN2 {[0;1;33m
!JТж цджгШ лжм ШиоЬхжм зЬиаЬхоЬ гЮ ШзжЫЬблжчк оШиШблуиЬк.
Тж тожмгЬ ШввсеЬа йЬ "[37m%s[37m".!)
[0;1m} T Modify message, warning 2: bad characters in filename


MMWARN3 {[0;1;31m
!JТж ЬзхзЬЫж зицйЩШйук йШк ЫЬд йШк ЬзалитзЬа дШ ЭЮлуйЬлЬ ШзцЫЬаеЮ ШдсЪдрйЮк.!)
[0;1m} T Modify message, warning 3: can't request return receipt


MMWARN4 {[0;1;31m
!JГЬд тоЬлЬ ШибЬлц оицдж оиуйЮк ЪаШ дШ ЭЮлуйЬлЬ ШзцЫЬаеЮ ШдсЪдрйЮк.!)
[0;1m} T Modify message, warning 4: not enough credits for return receipt


MMINFO1 {[0;1;32m
!JЕЮлуЯЮбЬ ШзцЫЬаеЮ ШдсЪдрйЮк, бШа оиЬрЯубШлЬ [32m%d гждсЫ%s[32m.!)
[0;1m} T Modify message, return receipt requested


MMCAN {[0;1;33m
!JЖ ЫаШЫабШйхШ ШбмищЯЮбЬ. Тж гудмгШ ЫЬд гЬлШЩвуЯЮбЬ.!)
[0;1m} T Modify message, abort message


MMLT {[2J[0;30;47m ┌─────────────────────────── [34mЛЬлШЩжву гЮдчгШлжк[0;30;47m ───────────────────────────[0;1;37;47m┐ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ [31m1[30m. ЗтгШ . . . . [34m@63;56;0s[0;1;47;37m │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ [31m2[30m. АиоЬхж  . . . . . . . . . . . . . . . . . . . . . .  [34m@16;16;0s[0;1;47;37m │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ [31m3[30m. АзцЫЬаеЮ АдсЪдрйЮк . . . . . . . . . . . . . . . . . . . . . . .  [34m@"X "t[0;1;47;37m │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ [31m4[30m. ЛЬлШЩжву бЬагтджм гЮдчгШлжк@1;"4Edit"b                                         [1;37m  │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m └[0;1;37;47m──────────────────────────────────────────────────────────────────────────┘ [0;1m
} T Modify message, linear template


NEWSUBJ {[0;1m
!WГщйлЬ лж дтж ЯтгШ лжм гЮдчгШлцк йШк.!)
} T Modify message, new subject


NEWATTN {[0;1m
!WГщйлЬ лж дтж цджгШ лжм ймдЮггтджм ШиоЬхжм. Ад ШнуйЬлЬ лж цджгШ бЬдц,
ЯШ ЬзШдтвЯЬа ШмлцгШлШ йлж бШлс ймдЯубЮ цджгШ, xxx.att, цзжм xxx ж ШиаЯгцк
лжм гЮдчгШлжк. Амлц лж зЬЫхж ЯШ ШЪджЮЯЬх Шд ЫЬд тоЬлЬ ЬзаймдспЬа ШиоЬхж йлж
гудмгс йШк.!)
} T Modify message, new filename




RRRSUBJ {<<АзцЫЬаеЮ зШиШвШЩук ЪаШ лж гудмгШ %s/%d>>} T Return Receipt message subject


RRRBODY {[0;1;36m

██  АПОГДИНЖ ПАРАКАБЖС

%s %s тоЬа ЫаШЩсйЬа лж гудмгШ %s/%ld зжм
йлЬхвШлЬ лЮд %s, %d %s %d, йлак %s.   [0;1m

██  Амлу Ю ШзцЫЬаеЮ зШиШвШЩук ЫЮгажмиЪуЯЮбЬ ШмлцгШлШ,
    цзрк ЬхоШлЬ ЭЮлуйЬа бШлс лЮд Шзжйлжву лжм гЮдчгШлжк.

} T Return Receipt message body (no formatting)


SEXMALE {О} T Masculine article
SEXFEM {Ж} T Feminine article


RRRGEN {[0;1;36m
!W██  !iГЮгажмиЪуЯЮбЬ [37mШзцЫЬаеЮ зШиШвШЩук[36m
цзрк ЬхоЬ ЭЮлЮЯЬх Шзц лжд ШзжйлжвтШ.!)
!0l[0;1m} T Return Receipt generated


RRRINJ {[0;1m***

!JТж гтвжк [32m%s[37m гцвак ЫасЩШйЬ лж гЮдмгс йШк,
бШа ЫЮгажмиЪуЯЮбЬ ШзцЫЬаеЮ зШиШвШЩук.!)
} T Return Receipt notification for receipt recipient


RRRNOT {[0;1m
!W██  !iТж гтвжк [32m%s[37m ЬхдШа ймдЫЬЫЬгтдж бШа ЬаЫжзжауЯЮбЬ
ЪаШ лЮд ШзцЫЬаеЮ зШиШвШЩук.!)
!0l[0;1m} T Return Receipt notification for receipt sender




ATTNF {[0;1;31m
!JАмлц лж гудмгШ ЯШ тзиЬзЬ дШ тоЬа тдШ ШиоЬхж ймдЮггтдж,
Шввс лж ШиоЬхж вЬхзЬа! ПШиШбШвжчгЬ ЬаЫжзжауйлЬ гШк ЪаШ лж гудмгШ [33m%s/%d[31m!
ЕЮлсгЬ ймЪЪдщгЮ бШа ЯШ бсджмгЬ лж зШд ЫмдШлц ЪаШ дШ йщйжмгЬ лж ШиоЬхж.!)
[0;1m} T File Attachment missing


ATTIO {[0;1;31m
!JЖ вупЮ лжм ШиоЬхжм гШлШащЯЮбЬ вцЪр всЯжмк ЬЪЪиШнук/ШдсЪдрйЮк. ПШиШбШвщ
ЬаЫжзжауйлЬ лжд ХЬаиайлу СмйлугШлжк ЪаШ лак ймдЯубЬк зжм жЫуЪЮйШд йЬ Шмлц лж
всЯжк.!)
[0;1m} T Can't link file attachment for downloading


ATTMNT1 {[0;1;32m
!JАмлц лж гудмгШ тоЬа тдШ ШиоЬхж губжмк [37m%d bytes[32m ймдЮггтдж.!)
[0;1m} T File Attachment information, no filename


ATTMNT2 {[0;1;32m
!JАиоЬхж гЬ цджгШ "[37m%s[32m" бШа губжк [37m%d bytes[32m
ЬхдШа ймдЮггтдж йлж гудмгШ.!)
[0;1m} T File Attachment information with filename


ATTDNL {[0;1m
ЗтвЬлЬ дШ ЫЬхлЬ у дШ всЩЬлЬ лж ШиоЬхж лщиШ; ([[33mY[37m]es=дШа / [[33mN[37m]o=цоа) } T File Attachment, download question


ATTDEF {[Enter=[33mN[37m]: [0m} T File Attachment, default answer to ATTDNL


ATTERR {[0;1;31m
!JПШиШбШвщ ШзШдлуйлЬ йлЮд ЬищлЮйЮ гЬ [[33mY[31m]es=дШа у [[33mN[31m]o=цоа.!)
[0;1m} T File Attachment, wrong answer to download question

         
ATTDESC {ДзайчдШпЮ гЮдчгШлжк %s/%d} S 49 File Attachment Download description


DNLNCRD {[0;1;31m
!JКмзсгШа, ЫЬд тоЬлЬ ШибЬлтк гждсЫЬк ЪаШ дШ всЩЬлЬ лж ймдЮггтдж ШиоЬхж.!)
[0;1m} T File Attachment download, not enough credits


CPNOAXES {[0;1;31m
!JКмзсгШа, ЫЬд тоЬлЬ зицйЩШйЮ йЬ Шмлу лЮд ЬзавжЪу.!)
[0;1m} T Copy message, access denied


CPWHO {[0;1m
ВисплЬ пЬмЫщдмгж у club зжм ЯШ ШдлаЪиспЬлЬ лж гудмгШ
([33m?[37m ЪаШ ЩжуЯЬаШ) [Enter=Sysop]: [0m} T Copy message, ask for recipient


CPERR {[0;1;31m
!JКмзсгШа, ЫЬд гзжиЬхлЬ дШ оиЮйагжзжауйЬлЬ вхйлЬк ЫаШджгук йЬ Шмлц
йЮгЬхж.!)
[0;1m} T Copy message, can't use distribution lists here


CPCERR {[0;1;31m
!JКмзсгШа, лж ЬзхзЬЫж зицйЩШйук йШк йлж club [37m%s[31m ЫЬд ЬзалитзЬа
лЮд Шзжйлжву гЮдмгслрд.!)
[0;1m} T Copy message, no WRITE access to target club


CPCERR2 {[0;1;31m
!JКмзсгШа, лж ЬзхзЬЫж зицйЩШйук йШк йлж club [37m%s[31m ЫЬд ЬзалитзЬа
лЮд Шзжйлжву ймдЮггтдрд ШиоЬхрд. Тж ймдЮггтдж йЬ Шмлц лж гудмгШ ШиоЬхж
ЫЬд ЯШ ШдлаЪиШнЬх.!)
[0;1m} T Copy message, no UPLOAD access to target club


CPRCPOK {[0;1;32m
!JПШиШвузлЮк лжм ШдлхЪиШнжм ЯШ ЬхдШа лж гтвжк [37m%s[32m.!)
[0;1m} T Copy message: confirming recipient of message


CPRCPOKN {[0;1;32m
!JТж ШдлхЪиШнж ЯШ йлШвЬх гтйр Internet Mail йлЮд ЫаЬчЯмдйЮ [37m%s[32m.!)
[0;1m} T Copy message: confirming recipient of message, net mail


CPIO {[0;1;31m
!JУзуиеЬ всЯжк ЬЪЪиШнук/ШдсЪдрйЮк бШлс лЮд ШдлаЪиШну лжм гЮдчгШлжк.
ПШиШбШвжчгЬ ЬаЫжзжауйлЬ лжд оЬаиайлу ймйлугШлжк ЪаШ лак ймдЯубЬк зжм жЫуЪЮйШд
йлж всЯжк.!)
[0;1m} T Copy message: I/O error




FWNOAXES {[0;1;31m
!JКмзсгШа, ЫЬд тоЬлЬ зицйЩШйЮ йЬ Шмлу лЮд ЬзавжЪу.!)
[0;1m} T Forward message, access denied


FWWHO {[0;1m
ВисплЬ пЬмЫщдмгж у club зжм ЯШ зижрЯуйЬлЬ лж гудмгШ
([33m?[37m ЪаШ ЩжуЯЬаШ) [Enter=Sysop]: [0m} T Forward message, ask for recipient


FWERR {[0;1;31m
!JКмзсгШа, ЫЬд гзжиЬхлЬ дШ оиЮйагжзжауйЬлЬ вхйлЬк ЫаШджгук йЬ Шмлц
йЮгЬхж.!)
[0;1m} T Forward message, can't use distribution lists here


FWCERR {[0;1;31m
!JКмзсгШа, лж ЬзхзЬЫж зицйЩШйук йШк йлж club [37m%s[31m ЫЬд ЬзалитзЬа
лЮд Шзжйлжву гЮдмгслрд.!)
[0;1m} T Forward message, no WRITE access to target club


FWCERR2 {[0;1;31m
!JКмзсгШа, лж ЬзхзЬЫж зицйЩШйук йШк йлж club [37m%s[31m ЫЬд ЬзалитзЬа
лЮд Шзжйлжву ймдЮггтдрд ШиоЬхрд. Тж ймдЮггтдж йЬ Шмлц лж гудмгШ ШиоЬхж
ЫЬд гзжиЬх дШ зижрЯЮЯЬх. Ж зижщЯЮйЮ лжм гЮдчгШлжк йлШгШлсЬа
ЪаШ дШ гЮд осйЬлЬ лж ймдЮггтдж ШиоЬхж.!)
[0;1m} T Forward message, no UPLOAD access to target club


FWRCPOK {[0;1;32m
!JПШиШвузлЮк лжм гЮдчгШлжк ЯШ ЬхдШа лж гтвжк [37m%s[32m.!)
[0;1m} T Forward message: confirming recipient of message


FWRCPOKN {[0;1;32m
!JТж гудмгШ ЯШ зижрЯЮЯЬх гтйр Internet Mail йлЮд ЫаЬчЯмдйЮ [37m%s[32m.!)
[0;1m} T Forward message: confirming recipient of message, net mail



FWIO {[0;1;31m
!JУзуиеЬ всЯжк ЬЪЪиШнук/ШдсЪдрйЮк бШлс лЮд зижщЯЮйЮ лжм гЮдчгШлжк.
ПШиШбШвжчгЬ ЬаЫжзжауйлЬ лжд оЬаиайлу ймйлугШлжк ЪаШ лак ймдЯубЬк зжм жЫуЪЮйШд
йлж всЯжк.!)
[0;1m} T Forward message: I/O error


FWCONF {[0;1;31m
!JЙсзжажк сввжк оиуйлЮк ЬиЪсЭЬлШа гЬ Шмлц лж гудмгШ.
Тж гЬлШЩаЩШйгтдж гудмгШ ЫЬд гзжиЬх дШ ЫаШЪиШнЬх лщиШ,
ШиЪцлЬиШ зсдлрк гзжиЬхлЬ дШ лж йЩуйЬлЬ гцджк йШк, Шд
ЯтвЬлЬ. ПШи'цвШ Шмлс лж гудмгШ тоЬа зижрЯЮЯЬх.!)
[0;1m} T Forward message: cant' erase due to conflicts


BKERR {[0;1;31m
!JКмзсгШа, лж гудмгШ ЫЬд ЬхдШа ШзЬмЯЬхШк ШзсдлЮйЮ йЬ бсзжаж сввж.!)
[0;1m} T Backtrack: message is not a reply


DLMNU {[2J[0m[47;1;37m ┌───────────────────────────────────────────────────────────────────[0;30;47m┐ [40m
[47;1;37m │  [0;47;30m                    КхйлШ ГаШджгук ЛЮдмгслрд                     [0;47;30m│ [40m
[47;1;37m │  [0;47;30m───────────────────────────────────────────────────────────────  [0;47;30m│ [40m
[47;1;37m │  [0;31;47mH[30melp . . . . . . . . . . . . .  БжуЯЬаШ ЪаШ лак вхйлЬк ЫаШджгук  [30m│ [40m
[47;1;37m │  [0;31;47mL[30mist addresses. . . . . . ЙШлсвжЪжк ЫаЬмЯчдйЬрд вхйлШк ЫаШджгук  [30m│ [40m
[47;1;37m │  [0;31;47mA[30mdd address. . . . . . . .  ПицйЯЬйЮ гаШк ЫаЬчЯмдйЮк йлЮд вхйлШ  [30m│ [40m
[47;1;37m │  [0;31;47mD[30melete address  . . . .  ГаШЪиШну гаШк ЫаЬчЯмдйЮк Шзц лЮд вхйлШ  [30m│ [40m
[47;1;37m │                                                                   [0;47;30m│ [40m
[47;1;37m │ [0;30;47me[31mX[30mit  . . . . . . . . . . . . . . . . . . . . . . . . . . ДежЫжк  [30m│ [40m
[47;1;37m └[0;30;47m───────────────────────────────────────────────────────────────────┘ [0;1m
[0;1m} T Distribution list, menu


DLMNUS {[0;1m
КхйлШ ГаШджгук ЛЮдмгслрд
!WГщйлЬ лЮд ЬзавжЪу йШк ([33mH[37m,[33mL[37m,[33mA[37m,[33mD[37m,[33mX[37m ЪаШ тежЫж, у [33m?[37m ЪаШ лж гЬджч): !)[0m} T Distribution list, short menu


DLSMNU {[2J[0m[47;1;37m ┌───────────────────────────────────────────────────────────────────[0;30;47m┐ [40m
[47;1;37m │  [0;47;30m                    КхйлШ ГаШджгук ЛЮдмгслрд                     [0;47;30m│ [40m
[47;1;37m │  [0;47;30m───────────────────────────────────────────────────────────────  [0;47;30m│ [40m
[47;1;37m │  [0;31;47mH[30melp . . . . . . . . . . . . .  БжуЯЬаШ ЪаШ лак вхйлЬк ЫаШджгук  [30m│ [40m
[47;1;37m │  [0;31;47mL[30mist addresses. . . . . . ЙШлсвжЪжк ЫаЬмЯчдйЬрд вхйлШк ЫаШджгук  [30m│ [40m
[47;1;37m │  [0;31;47mA[30mdd address. . . . . . . .  ПицйЯЬйЮ гаШк ЫаЬчЯмдйЮк йлЮд вхйлШ  [30m│ [40m
[47;1;37m │  [0;31;47mD[30melete address  . . . .  ГаШЪиШну гаШк ЫаЬчЯмдйЮк Шзц лЮд вхйлШ  [30m│ [40m
[47;1;37m │  [0;31;47mP[30mrotect distribution list  . . . . .  ПижйлШйхШ вхйлШк ЫаШджгук  [30m│ [40m
[47;1;37m │  [0;31;47mS[30melect distribution list . . . . . . .  ДзавжЪу вхйлШк ЫаШджгук  [30m│ [40m
[47;1;37m │  [0;31;47mK[30mill current list . . . . . . . . . . ГаШЪиШну литожмйШк вхйлШк  [30m│ [40m
[47;1;37m │                                                                   [0;47;30m│ [40m
[47;1;37m │ [0;30;47me[31mX[30mit  . . . . . . . . . . . . . . . . . . . . . . . . . . ДежЫжк  [30m│ [40m
[47;1;37m └[0;30;47m───────────────────────────────────────────────────────────────────┘ [0;1m
[0;1m} T Distribution list, menu


DLSMNUS {[0;1m
КхйлШ ГаШджгук ЛЮдмгслрд (литожмйШ вхйлШ: [32m!%s[37m)
!WГщйлЬ лЮд ЬзавжЪу йШк ([33mH[37m,[33mL[37m,[33mA[37m,[33mD[37m,[33mP[37m,[33mS[37m,[33mK[37m,[33mX[37m ЪаШ тежЫж, у [33m?[37m ЪаШ лж гЬджч): !)[0m} T Distribution list, short menu


DLNOAX {[0;1;31m
КмзсгШа, ЫЬд тоЬлЬ зицйЩШйЮ йЬ Шмлу лЮд ЬзавжЪу.
[0;1;31m} T Distribution list, access denied


DLERRS {[0;1;31m
!JКмзсгШа, Шмлу Ю ЬзавжЪу ЫЬд ЬхдШа ЫмдШлу.!)
[0;1m} T Distribution List, invalid selection


DLHELP {[0;1m

!JДЫщ гзжиЬхлЬ дШ жихйЬлЬ гтоиа %d ЫаЬмЯчдйЬак (ЬхлЬ лжзабтк, ЬхлЬ Internet)
йлак жзжхЬк гзжиЬхлЬ дШ йлтвдЬлЬ ЫаШдЬгЮгтдШ гЮдчгШлШ. ВаШ дШ йлЬхвЬлЬ тдШ
ЫаШдЬгЮгтдж гудмгШ, ЫщйлЬ '!' Шдлх ЪаШ зШиШвузлЮ лжм гЮдчгШлжк.!)

!JЛЬ лЮд Ьдлжву [33mL[37m гзжиЬхлЬ дШ ЫЬхлЬ лак ЫаЬмЯчдйЬак зжм зЬиавШгЩсдЬа
Ю вхйлШ Шмлу лЮд йлаЪгу. ЛЬ [33mA[37m гзжиЬхлЬ дШ зижйЯтйЬлЬ гхШ ЫаЬчЯмдйЮ
йлЮд вхйлШ. ЛЬ [33mD[37m ЫаШЪиснЬлЬ гхШ ЫаЬчЯмдйЮ.!)

!JЖ оитрйЮ Шзжйлжвук Ьдцк ЫаШдЬгЮгтджм гЮдчгШлжк айжчлШа гЬ лж
сЯижайгШ лЮк оитрйЮк ЪаШ лЮд Шзжйлжву ШдлхЪиШнжм лжм гЮдчгШлжк йЬ бсЯЬ гтвжк
лЮк вхйлШк. ЛзжиЬхлЬ дШ ЫЬхлЬ зцйж ЯШ йШк бжйлхйЬа тдШ ЫаШдЬгЮгтдж гудмгШ гЬ
лЮд Ьдлжву [33mL[37m.!)

[0;1m} T Distribution List, help


DLHELPS {[0;1m

!JДЫщ гзжиЬхлЬ дШ жихйЬлЬ гтоиа %d ЫаЬмЯчдйЬак (ЬхлЬ лжзабтк, ЬхлЬ Internet)
йлак жзжхЬк гзжиЬхлЬ дШ йлтвдЬлЬ ЫаШдЬгЮгтдШ гЮдчгШлШ. ВаШ дШ йлЬхвЬлЬ тдШ
ЫаШдЬгЮгтдж гудмгШ, ЫщйлЬ '!' бШа лж цджгШ лЮк вхйлШк Шдлх ЪаШ зШиШвузлЮ лжм гЮдчгШлжк.
О зШиШбслр зхдШбШк ЫхдЬа лак ЫаснжиЬк вхйлЬк бШа зщк ймдлсйждлШа.!)

!C┌───────────┬────────────────────────────────────────────────────────┐
│ [33m!.Sysop   [37m│ [32mЖ зижйрзабу вхйлШ лжм оиуйлЮ Sysop                     [37m│
│ [33m!         [37m│ [32mСмдщдмгж гЬ лЮд зижйрзабу йШк вхйлШ                    [37m│
│ [33m!mass     [37m│ [32mОКОИ жа оиуйлЬк.                                       [37m│
│ [33m!all      [37m│ [32mТж хЫаж.                                               [37m│
│ [33m!!<class> [37m│ [32mОвжа жа оиуйлЬк гхШк бвсйЮк (з.о. !!DEMO у !!OPERATOR) [37m│
│ [33m!listname [37m│ [32mЖ вхйлШ ЫаШджгук гЬ цджгШ listname.                    [37m│
└───────────┴────────────────────────────────────────────────────────┘!)

!JОа ЫаШнжитк бЬнШвШхрд/габищд ЫЬд зШхЭжмд ицвж.!)

!JЛЬ лЮд Ьдлжву [33mL[37m гзжиЬхлЬ дШ ЫЬхлЬ лак ЫаЬмЯчдйЬак зжм зЬиавШгЩсдЬа
Ю вхйлШ Шмлу лЮд йлаЪгу. ЛЬ [33mA[37m гзжиЬхлЬ дШ зижйЯтйЬлЬ гхШ ЫаЬчЯмдйЮ
йлЮд вхйлШ. ЛЬ [33mD[37m ЫаШЪиснЬлЬ гхШ ЫаЬчЯмдйЮ. ЛЬ [33mP[37m гзжиЬхлЬ дШ
зЬиажихйЬлЬ лЮд оиуйЮ лЮк вхйлШк Шзц сввжмк. Ттвжк, гЬ [33mS[37m нжилщдЬлЬ
гхШ сввЮ вхйлШ.!)

!JЖ оитрйЮ Шзжйлжвук Ьдцк ЫаШдЬгЮгтджм гЮдчгШлжк айжчлШа гЬ лж
сЯижайгШ лЮк оитрйЮк ЪаШ лЮд Шзжйлжву ШдлхЪиШнжм лжм гЮдчгШлжк йЬ бсЯЬ гтвжк
лЮк вхйлШк. ЛзжиЬхлЬ дШ ЫЬхлЬ зцйж ЯШ йШк бжйлхйЬа тдШ ЫаШдЬгЮгтдж гудмгШ гЬ
лЮд Ьдлжву [33mL[37m.!)

[0;1m} T Distribution List, help for the privileged


DLLISTH {[0;1m

КхйлШ:  [32m!%s[37m
ЙвЬаЫх: [32m%d[37m

ЛтвЮ вхйлШк:

[0;1;32m} T Distribution list, address list header


DLLISTL {%3d. %s
} T Distribution list, address list

DLLISTF {[0;1m
Йцйлжк гЮдчгШлжк: [32m%d гждсЫ%s[37m
[0;1m} T Distribution list, address list footer


DLAR1 {[0;1;31m
!JКмзсгШа, ЫЬд гзжиЬхлЬ дШ зижйЯтйЬлЬ зсдр Шзц [37m%d[31m
гтвЮ йлЮд вхйлШ.!)
[0;1m} T Distribution list, add, too many members


DLANNET {[0;1;31m
!JКмзсгШа, лж ЬзхзЬЫж зицйЩШйук йШк ЫЬд йШк ЬзалитзЬа дШ тоЬлЬ
ЫаЬмЯчдйЬак Internet рк гтвЮ лЮк вхйлШк ЫаШджгук йШк.!)
[0;1m} T Distribution list, add, can't specify net address


DLAUNKID {[0;1;31m
!JГЬд мзсиоЬа оиуйлЮк "[37m%s[31m".!)
[0;1m} T Distribution list, add, unknown user


DLADUPL {[0;1;31m
!JАмлу Ю ЫаЬчЯмдйЮ мзсиоЬа уЫЮ йлЮ вхйлШ.!)
[0;1m} T Distribution list, add, duplicate address


DLAWHO {[0;1m
!WГщйлЬ лЮ ЫаЬчЯмдйЮ зжм ЯтвЬлЬ дШ зижйЯтйЬлЬ йлЮд вхйлШ ([33m?[37m ЪаШ бШлсвжЪж гЬвщд):!) [0m} T Distribution list, add, whom?


DLDR1 {[0;1;31m
!JЖ вхйлШ ЬхдШа уЫЮ бЬду.!)
[0;1m} T Distribution list, delete, list is empty


DLDASK {[0;1m
!WГщйлЬ лжд ШиаЯгц лЮк ЫаЬчЯмдйЮк зжм ЯтвЬлЬ дШ ШнШаитйЬлЬ ([33m%d[37m-[33m%d[37m, у [33m?[37m ЪаШ бШлсвжЪж гЬвщд):!) [0m} T Distribution list, delete, whom?


DLDERR {[0;1;31m
!JГщйлЬ тдШд ШиаЯгц йлж ЫасйлЮгШ [33m%d[37m-[33m%d[37m.!)
[0;1m} T Distribution list, delete, error


DLPASK {[0;1m
!WГщйлЬ лж бвЬаЫх зжм ШзШалЬхлШа ЪаШ зицйЩШйЮ йЬ Шмлу лЮд вхйлШ ([33m0[37m = орихк
зижйлШйхШ, [33m1[37m-[33n128[37m = бвЬаЫх, [33m129[37m = гцдж лж пЬмЫщдмгж Sysop):!) [0m} T Distribution list, set protection


DLPERR {[0;1;31m
!JПШиШбШвщ ЫщйлЬ тдШд ШиаЯгц Шзц [37m%d[31m рк [37m%d[31m. СЮгЬащйлЬ цла гцдж лж
пЬмЫщдмгж [37mSysop[31m гзжиЬх дШ ЭЮлуйЬа лж бвЬаЫх 129.!)
[0;1m} T Distribution list, set protection, error


DLSASK {[0;1m
!WГщйлЬ лж цджгШ лЮк вхйлШк зжм ЯтвЬлЬ дШ нжилщйЬлЬ ([33m?[37m ЪаШ бШлсвжЪж):!) [0m} T Distribution list, select list


DLSERR1 {[0;1;31m
!JПШиШбШвщ ЫщйлЬ лж звуиЬк цджгШ лЮк вхйлШк, гШЭх гЬ лж '!'.!)
[0;1m} T Distribution list, select list, bad list name


DLSERR2 {[0;1;31m
!JТж цджгШ зжм ЫщйШлЬ зЬиатоЬа гЮ ШзжЫЬблжчк оШиШблуиЬк.!)
[0;1m} T Distribution list, select list, bad characters in name


DLSERR3 {[0;1;31m
!JКмзсгШа, ЫЬд гзжиЬхлЬ дШ лЮд ШввсеЬлЬ лЮд вхйлШ "%s".!)
[0;1m} T Distribution list, select list, access denied


DLKASK {[0;1m
!WЗтвЬлЬ йхЪжмиШ дШ ЫаШЪиспЬлЬ лЮд литожмйШ вхйлШ; [[33mY[37m]yes=дШа / [[33mN[37m]o=цоа)!) [0m} T Distribution list, kill list?


DLKERR {[0;1;31m
!JПШиШбШвщ ШзШдлуйлЬ гЬ [33mY[31m у [33mN[31m.!)
[0;1m} T Distritbution list, kill list, error


LSTLSTH {[0;1m

УПАРХОУСДС КИСТДС ГИАМОЛЖС:
!F─
[32m} T List of lists, header


LSTLST {!%s
} T List of lists, table entry


LSTLSTF {[0;1m!F─
} T List of lists, footer







MSGHDR1 {
[0;1;32m%s/%d  %s
ЖЛ/МИА: [36m%-38.38s[32m  %31.31s
АПО:    [36m%-42.42s  [32m%s
ПРОС:   [36m%s%-48.48s  [0;1;32m%21.21s
ЗДЛА:   [36m%-54.54s  [32m%15.15s
} T Message header, top part


MSGHDR2 {АРХДИО: [36m%-52s  [32m%17s
} T Message header, optional file attachment part


MSGHDR3 {} T Message header, bottom part


MHFORU {[5m} T Message header, message for you (clubs only)


MHALL {Овжмк} T Message header, string for 'All'


MHDAY0 {ЙмиаШбу} T Message header, string for Sunday
MHDAY1 {ГЬмлтиШ} T Message header, string for Monday
MHDAY2 {ТихлЮ} T Message header, string for Tuesday
MHDAY3 {ТЬлсилЮ} T Message header, string for Wednesday
MHDAY4 {ПтгзлЮ} T Message header, string for Thursday
MHDAY5 {ПШиШйбЬму} T Message header, string for Friday
MHDAY6 {СсЩЩШлж} T Message header, string for Saturday


MHJAN {ИШджмШихжм} T Message header, string for January
MHFEB {ФЬЩижмШихжм} T Message header, string for February
MHMAR {ЛШилхжм} T Message header, string for March
MHAPR {Азиавхжм} T Message header, string for April
MHMAY {ЛШфжм} T Message header, string for May
MHJUN {Ижмдхжм} T Message header, string for June
MHJUL {Ижмвхжм} T Message header, string for July
MHAUG {АмЪжчйлжм} T Message header, string for August
MHSEP {СЬзлЬгЩихжм} T Message header, string for September
MHOCT {ОблрЩихжм} T Message header, string for October
MHNOV {МжЬгЩихжм} T Message header, string for November
MHDEC {ГЬбЬгЩихжм} T Message header, string for December

MHPERIOD {ПЬиажЫабц, Шдс %d Югти%s} T Message header, string for 'periodic'

MHXMPT {ЛЮ ЫаШЪиспагж} T Message header, string for 'exempt'

MHRRR {ЕЮлуЯЮбЬ ШзцЫЬаеЮ ШдсЪдрйЮк} T Message header, string for 'return receipt requested'
        
MHTMRD {ГаШЩсйлЮбЬ %d нжи%s} T Message header, string for 'read x times'

MHNREP {%d %s} T Message header, string for 'x replies'

MHNDNL {ДвунЯЮ %d нжи%s} T Message header, string for 'downloaded x times'


TIMSNG {с} T 'Times', singular form
TIMPLR {тк} T 'Times', plural form

REPSNG {ШзсдлЮйЮ} T 'Reply', singular form
REPPLR {ШзШдлуйЬак} T 'Replies', plural form


















CLNONTR {[0;1;31m
КмзсгШа, ЫЬд тоЬлЬ зицйЩШйЮ йлак ДаЫабтк ПЬиажотк (Clubs).
[0;1m} T User does not have access to the Clubs module


BANNERH {[2J} T Club banner header

BANNERF {} T Club banner footer


CLMNU1 {[2J[0m[47;1;37m ┌─────────────────────────────────────────────────────────[0;30;47m┐ [0m
[47;1;37m │  [0;47;30m              ДаЫабтк ПЬиажотк (Clubs)                 [0;47;30m│ [0m
[47;1;37m │  [0;47;30m─────────────────────────────────────────────────────  [0;47;30m│ [0m
[47;1;37m │  [0;31;47mH[30melp  . . . . . . . . . . . . . . ВЬдабтк ПвЮижнжихЬк  [30m│ [0m
[47;1;37m │  [0;31;47mI[30mnformation  . . . . . . . .  ПвЮижнжихЬк ЪаШ лж club  [30m│ [0m
[47;1;37m │  [0;31;47mL[30mist clubs . . . . . . . . . . . . .  ЙШлсвжЪжк clubs  [30m│ [0m
[47;1;37m │  [0;31;47mR[30mead messages . . . . . . . . . .  АдсЪдрйЮ гЮдмгслрд  [30m│ [0m
[47;1;37m │  [0;31;47mW[30mrite message  . . . . . . . . . . Азжйлжву гЮдчгШлжк  [30m│ [0m
[47;1;37m │  [0;31;47mD[30mownload file . . . . . . . . . . . . .  КупЮ ШиоЬхжм  [30m│ [0m
[47;1;37m │  [0;31;47mT[30meleconference . . . .  ЙШдсва лЮвЬймджгавщд лжм Club  [30m│ [0m
[47;1;37m │  [0;31;47mB[30mulletins . . . . . . .  АдШЪдрйлуиаж сиЯирд лжм Club  [30m│ [0m
[47;1;37m │  [0;31;47mS[30melect club  . . . . . . . . . . . . . . ДзавжЪу club  [30m│ [0m
[47;1;37m │                                                         [0;47;30m│ [0m
[47;1;37m │ [0;30;47me[31mX[30mit . . . . . . . . . . . . . . . . . . . . .  ДежЫжк  [30m│ [0m
[47;1;37m └[0;30;47m─────────────────────────────────────────────────────────┘ [0;1m

ДаЫабтк зЬиажотк (Clubs)
!WБихйбЬйлЬ йлж club [32m@CLUB@: @CLUBDESC@[37m.!)
ПШиШбШвщ ЫщйлЬ лЮд ЬзавжЪу йШк: [0m} T Club main menu, non-privileged version


SHCLMNU1 {[0;1m
!WБихйбЬйлЬ йлж club [32m@CLUB@: @CLUBDESC@[37m.!)
!WГщйлЬ лЮд ЬзавжЪу йШк ([33mH[37m,[33mI[37m,[33mL[37m,[33mR[37m,[33mW[37m,[33mD[37m,[33mT[37m,[33mB[37m,[33mS[37m,[33mX[37m ЪаШ тежЫж, у [33m?[37m ЪаШ лж гЬджч): !)[0m} T Club short menu, non-privileged version


CLMNU2 {[2J[0m[47;1;37m ┌─────────────────────────────────────────────────────────[0;30;47m┐ [0m
[47;1;37m │  [0;47;30m              ДаЫабтк ПЬиажотк (Clubs)                 [0;47;30m│ [0m
[47;1;37m │  [0;47;30m─────────────────────────────────────────────────────  [0;47;30m│ [0m
[47;1;37m │  [0;31;47mH[30melp  . . . . . . . . . . . . . . ВЬдабтк ПвЮижнжихЬк  [30m│ [0m
[47;1;37m │  [0;31;47mI[30mnformation  . . . . . . . .  ПвЮижнжихЬк ЪаШ лж club  [30m│ [0m
[47;1;37m │  [0;31;47mL[30mist clubs . . . . . . . . . . . . .  ЙШлсвжЪжк clubs  [30m│ [0m
[47;1;37m │  [0;31;47mR[30mead messages . . . . . . . . . .  АдсЪдрйЮ гЮдмгслрд  [30m│ [0m
[47;1;37m │  [0;31;47mW[30mrite message  . . . . . . . . . . Азжйлжву гЮдчгШлжк  [30m│ [0m
[47;1;37m │  [0;31;47mD[30mownload file . . . . . . . . . . . . .  КупЮ ШиоЬхжм  [30m│ [0m
[47;1;37m │  [0;31;47mT[30meleconference . . . .  ЙШдсва лЮвЬймджгавщд лжм Club  [30m│ [0m
[47;1;37m │  [0;31;47mB[30mulletins . . . . . . .  АдШЪдрйлуиаж сиЯирд лжм Club  [30m│ [0m
[47;1;37m │  [0;31;47mA[30mpprove files  . . . ДЪбиайЮ ШиоЬхрд ([31m%03d[30m Ьд ШдШгжду)  [30m│ [0m
[47;1;37m │  [0;31;47mS[30melect club . . . . . . . . . . . . . .  ДзавжЪу club  [30m│ [0m
[47;1;37m │                                                         [0;47;30m│ [0m
[47;1;37m │ [0;30;47me[31mX[30mit  . . . . . . . . . . . . . . . . . . . . . ДежЫжк  [30m│ [0m
[47;1;37m └[0;30;47m─────────────────────────────────────────────────────────┘ [0;1m

ДаЫабтк зЬиажотк (Clubs)
!WЙШврйувЯШлЬ, жиЪШдрлс, йлж club [32m@CLUB@: @CLUBDESC@[37m.!)
ПШиШбШвщ ЫщйлЬ лЮд ЬзавжЪу йШк: [0m} T Club main menu, co-op version


SHCLMNU2 {[0;1m
!WЙШврйувЯШлЬ, жиЪШдрлс, йлж club [32m@CLUB@: @CLUBDESC@[37m.!)
!WГщйлЬ лЮд ЬзавжЪу йШк ([33mH[37m,[33mI[37m,[33mL[37m,[33mR[37m,[33mW[37m,[33mD[37m,[33mT[37m,[33mB[37m,[33mA[37m,[33mS[37m,[33mX[37m
ЪаШ тежЫж, у [33m?[37m ЪаШ лж гЬджч): !)[0m} T Club short menu, co-op version


CLMNU3 {[2J[0m[47;1;37m ┌─────────────────────────────────────────────────────────[0;30;47m┐ [0m
[47;1;37m │  [0;47;30m              ДаЫабтк ПЬиажотк (Clubs)                 [0;47;30m│ [0m
[47;1;37m │  [0;47;30m─────────────────────────────────────────────────────  [0;47;30m│ [0m
[47;1;37m │  [0;31;47mH[30melp . . . . . . . . . . . . . .  ВЬдабтк ПвЮижнжихЬк  [30m│ [0m
[47;1;37m │  [0;31;47mI[30mnformation . . . . . . . . . ПвЮижнжихЬк ЪаШ лж club  [30m│ [0m
[47;1;37m │  [0;31;47mL[30mist clubs . . . . . . . . . . . . .  ЙШлсвжЪжк clubs  [30m│ [0m
[47;1;37m │  [0;31;47mR[30mead messages . . . . . . . . . .  АдсЪдрйЮ гЮдмгслрд  [30m│ [0m
[47;1;37m │  [0;31;47mW[30mrite message  . . . . . . . . . . Азжйлжву гЮдчгШлжк  [30m│ [0m
[47;1;37m │  [0;31;47mD[30mownload file . . . . . . . . . . . . .  КупЮ ШиоЬхжм  [30m│ [0m
[47;1;37m │  [0;31;47mT[30meleconference  . . . . ЙШдсва лЮвЬймджгавщд лжм Club  [30m│ [0m
[47;1;37m │  [0;31;47mB[30mulletins  . . . . . . . АдШЪдрйлуиаж сиЯирд лжм Club  [30m│ [0m
[47;1;37m │  [0;31;47mA[30mpprove files . . .  ДЪбиайЮ ШиоЬхрд ([31m%03d[30m Ьд ШдШгжду)  [30m│ [0m
[47;1;37m │  [0;31;47mO[30mptions . . . . . . . . . . Ддлжвтк жиЪШдрлу/оЬаиайлу  [30m│ [0m
[47;1;37m │  [0;31;47mN[30metworking . . . . . . . . ГаШджгу clubs гтйр Ыаблчжм  [30m│ [0m
[47;1;37m │  [0;31;47mS[30melect club . . . . . . . . . . . . . .  ДзавжЪу club  [30m│ [0m
[47;1;37m │                                                         [0;47;30m│ [0m
[47;1;37m │ [0;30;47me[31mX[30mit . . . . . . . . . . . . . . . . . . . . .  ДежЫжк  [30m│ [0m
[47;1;37m └[0;30;47m─────────────────────────────────────────────────────────┘ [0;1m

ДаЫабтк зЬиажотк (Clubs)
!WЙШврйувЯШлЬ, жиЪШдрлс, йлж club [32m@CLUB@: @CLUBDESC@[37m.!)
ПШиШбШвщ ЫщйлЬ лЮд ЬзавжЪу йШк: [0m} T Club main menu, club-op/privileged version


SHCLMNU3 {[0;1m
!WЙШврйувЯШлЬ, жиЪШдрлс, йлж club [32m@CLUB@: @CLUBDESC@[37m.!)
!WГщйлЬ лЮд ЬзавжЪу йШк ([33mH[37m,[33mI[37m,[33mL[37m,[33mR[37m,[33mW[37m,[33mU[37m,[33mT[37m,[33mB[37m,[33mA[37m,[33mO[37m,[33mS[37m,[33mX[37m
ЪаШ тежЫж, у [33m?[37m ЪаШ лж гЬджч): !)[0m} T Club short menu, club-op/privileged version


CLLEAVE {[0;1m
ДежЫжк Шзц лак ДаЫабтк ПЬиажотк.
} T Exiting from Clubs module


CLABOUT {[0;1m

!JОа ДаЫабтк ПЬиажотк ЬхдШа йчджвШ ЫЮгцйард звЮижнжиащд (гЮдмгслрд, ШиоЬхрд
бШа сиЯирд). Лтйр Шмлжч лжм гЬджч гзжиЬхлЬ дШ оЬаиайлЬхлЬ гхШ ЬаЫабу зЬиажоу
(club).!)

!JВаШ дШ зсиЬлЬ звЮижнжихЬк ЪаШ лж литожд club, ЫщйлЬ лЮд Ьдлжву
[33mI[37mnformation. ВаШ дШ ЬзавтеЬлЬ гаШ сввЮ ЬаЫабу зЬиажоу, ЫщйлЬ
[33mS[37melect. ЛзжиЬхлЬ дШ ЫЬхлЬ тдШд йчдлжгж бШлсвжЪж лрд clubs гЬ лЮд
Ьдлжву [33mS?[37m, у тдШд зЬиаЬблабцлЬиж бШлсвжЪж гЬ [33mL[37mist
clubs.!)

!JВаШ дШ ЫаШЩсйЬлЬ лШ ЫЮгцйаШ гЮдчгШлШ лжм Club, оиЮйагжзжауйлЬ лЮд Ьдлжву
[33mR[37mead messages, бШа ШбжвжмЯуйлЬ лак ЬбЬх жЫЮЪхЬк. ВаШ дШ ЪиспЬлЬ
гЮдчгШлШ, оиЮйагжзжауйлЬ лЮд Ьдлжву [33mW[37mrite. ВаШ дШ ЫаШЩсйЬлЬ бШа дШ
ЪиспЬлЬ ШзжбвЬайлабс бШа гцдж гЮдчгШлШ гЬ ймдЮггтдШ ШиоЬхШ, оиЮйагжзжауйлЬ
лак Ьдлжвтк [33mD[37mownload бШа [33mU[37mpload file ШдлхйлжаоШ.
КЬалжмиЪжчд ШбиаЩщк цзрк бШа жа Read бШа Write message. ТШ ШиоЬхШ зжм
йлтвдЬлЬ оиЬасЭждлШа тЪбиайЮ Шзц лжд ОиЪШдрлу зиад Ъхджмд ЫаШЯтйагШ йлШ гтвЮ
лжм Club.!)

!JЙсЯЬ Club тоЬа бШа тдШ Ыабц лжм бШдсва йлак лЮвЬймджгавхЬк, гЬ ЯтгШ лж
ЯтгШ лжм Club. ДбЬх ЪхдждлШа жа йоЬлабтк гЬ лж Club ймЭЮлуйЬак. ЛЬ лЮд
Ьдлжву [33mT[37meleconference гЬлШнтиЬйлЬ Шмлжгслрк йЬ Шмлц лж бШдсва лрд
лЮвЬймджгаващд.!)

!JЛзжиЬхлЬ дШ ЫаШЩсйЬлЬ лШ сиЯиШ лжм литождлжк Club гЬ лЮд Ьдлжву
[33mB[37mulletins, зжм йШк гЬлШнтиЬа йлж АдШЪдрйлуиаж АиЯирд. Лцдж ж
ОиЪШдрлук лжм club гзжиЬх дШ гЬлШнтиЬа тдШ гудмгШ йлж АдШЪдрйлуиаж. ВаШ дШ
ЪиспЬлЬ тдШ сиЯиж, Шзвщк йлЬхвлЬ рк гудмгШ, у рк ШиоЬхж ймдЮггтдж йЬ тдШ
гудмгШ лжм club. О ОиЪШдрлук ЯШ ШдШвсЩЬа лШ мзцвжазШ.!)

ДзхзЬЫШ зицйЩШйЮк:

!JУзсиожмд зтдлЬ ЬзхзЬЫШ зицйЩШйЮк йлШ clubs:!)

!WZero:     !10iЛЮЫЬдабу зицйЩШйЮ. О оиуйлЮк ЫЬд гзжиЬх дШ зижйзЬвсйЬа бШггхШ
Шзц лак мзжзЬиажотк лжм club.!)
!0l
!WRead:     !10iПицйЩШйЮ ШдсЪдрйЮк гцдж. О оиуйлЮк гзжиЬх дШ ЫаШЩсйЬа
гЮдчгШлШ бШа сиЯиШ, Шввс ЫЬд гзжиЬх дШ всЩЬа ШиоЬхШ.!)
!0l
!WDownload: !10iПицйЩШйЮ вупЮк ШиоЬхрд. О оиуйлЮк гзжиЬх дШ ЫаШЩсйЬа
гЮдчгШлШ бШа сиЯиШ бШа дШ всЩЬа ШиоЬхШ. ГЬд гзжиЬх дШ ЪиспЬа гЮдчгШлШ у дШ
йлЬхвЬа ШиоЬхШ.!)
!0l
!WWrite:    !10iПицйЩШйЮ Шзжйлжвук гЮдмгслрд. Озрк бШа Ю Download
зицйЩШйЮ, Шввс ж оиуйлЮк гзжиЬх бШа дШ ЪиспЬа гЮдчгШлШ.!)
!0l
!WUpload:   !10iПицйЩШйЮ Шзжйлжвук ШиоЬхрд. Озрк бШа Ю Write зицйЩШйЮ,
Шввс ж оиуйлЮк гзжиЬх бШа дШ йлЬхвЬа ШиоЬхШ йлж club.!)
!0l
[0;1m} T Clubs, about the module


CLINFO {
[0;36m██  [1mПвЮижнжихЬк ЪаШ лж club @CLUB@  [46m[K[0;1m

ОиЪШдрлук . . . . . . . . . . . @CLUBOP@
ГЮгажмиЪуЯЮбЬ  . . . . . . . .  @CLUBCRDATE@, @CLUBCRTIME@
ЛЮдчгШлШ  . . . . . . . . . . . @CLUBMSGS@
АиоЬхШ . . . . . . . . . . . .  @CLUBFILES@
АиЯиШ . . . . . . . . . . . . . @CLUBBLTS@
ХитрйЮ . . . . . . . . . . . .  @CHARGE@ credits/вЬзлц
ХитрйЮ Шзжйлжвук гЮдчгШлжк  . . @CLUBPOSTCHG@ credit(s)
ХитрйЮ Шзжйлжвук ШиоЬхжм . . .  @CLUBUPLCHG@ credit(s)
ХитрйЮ вупЮк ШиоЬхжм  . . . . . @CLUBDNLCHG@ credit(s)

[46m[K[0;1m
} T Club information



OPMNU {[2J[0m[47;1;37m ┌─────────────────────────────────────────────────────────[0;30;47m┐ [0m
[47;1;37m │  [0;47;30m           Ддлжвтк ХЬаиайлу/ОиЪШдрлу Club              [0;47;30m│ [0m
[47;1;37m │  [0;47;30m─────────────────────────────────────────────────────  [0;47;30m│ [0m
[47;1;37m │  [0;31;47mH[30melp  . . . . . . . . . . . . . . ВЬдабтк ПвЮижнжихЬк  [30m│ [0m
[47;1;37m │  [0;31;47mN[30mew club . . . . . . . . . . . . . .  ГЮгажмиЪхШ club  [30m│ [0m
[47;1;37m │  [0;31;47mD[30melete club . . . . . . . . . . . . . . ГаШЪиШну club  [30m│ [0m
[47;1;37m │  [0;31;47mE[30mdit club  . . . . . . . . . . АввШЪу зШиШгтлирд club  [30m│ [0m
[47;1;37m │  [0;31;47mA[30mccess levels . . . . . . . АввШЪу ЬзазтЫрд зицйЩШйЮк  [30m│ [0m
[47;1;37m │  [0;31;47mM[30modify charges . . . . . . . . . . .  АввШЪу оиЬщйЬрд  [30m│ [0m
[47;1;37m │  [0;31;47mC[30monfigure user  . . . . . .  АввШЪу зицйЩШйЮк оиЮйлщд  [30m│ [0m
[47;1;37m │                                                         [0;47;30m│ [0m
[47;1;37m │ [0;30;47me[31mX[30mit . . . . . . . . . . . . . . . . . . . . .  ДежЫжк  [30m│ [0m
[47;1;37m └[0;30;47m─────────────────────────────────────────────────────────┘ [0;1m

БихйбЬйлЬ йлж Club [32m@CLUB@: @CLUBDESC@[37m.
[0;1m} T Club operation menu, long version


SHOPMNU {[0;1m
!WГщйлЬ лЮд ЬзавжЪу йШк ([33mH[37m,[33mN[37m,[33mD[37m,[33mE[37m,[33mA[37m,[33mM[37m,[33mC[37m,[33mX[37m
ЪаШ тежЫж, у [33m?[37m ЪаШ лж гЬджч): !)[0m} T Club operation menu, short version



OPHELP {[2J[0;1m
!JЛЬ лЮд ЩжуЯЬаШ Шмлжч лжм гЬджч гзжиЬхлЬ дШ бсдЬлЬ лШ Ьеук
(йЮгЬащйлЬ цла ШдсвжЪШ гЬ лж ЬзхзЬЫж зицйЩШйук йШк, жиайгтдЬк Ьдлжвтк гзжиЬх дШ гЮд
ЬхдШа ЫаШЯтйагЬк):!)

!JЛЬ лЮд Ьдлжву New Club гзжиЬхлЬ дШ ЫЮгажмиЪуйЬлЬ тдШ дтж club.
ЛЬ лЮд Ьдлжву Delete Club гзжиЬхлЬ дШ ЫаШЪиспЬлЬ тдШ club.!)

!JЛЬ лЮд Ьдлжву Edit Club тоЬлЬ лЮд ЫмдШлцлЮлШ дШ ШввсеЬлЬ жиайгтдЬк
зШиШгтлижмк лжм литождлжк club, цзрк лЮд зЬиаЪиШну лжм, лЮд ЫасибЬаШ
Эрук лрд гЮдмгслрд, бШа лж йугШ (banner) лжм. Ж Ьдлжву Access levels
ЬзалитзЬа дШ жихйЬлЬ лЮд зицйЩШйЮ лрд оиЮйлщд йлж литожд club. ЛЬ лЮд
ЬзцгЬдЮ Ьдлжву, Modify charges, ЬвтЪоЬлЬ лЮд оитрйЮ лрд оиЮйлщд зжм
ЫаШЩсЭжмд лж club. Ттвжк, гЬ лЮд Ьдлжву Configure user гзжиЬхлЬ дШ жихйЬлЬ
лж ЬзхзЬЫж зицйЩШйЮк Ьдцк ймЪбЬбиагтджм оиуйлЮ йлж литожд club.!)

[0;1m} T Club operation menu help





ECVT {[0;30;47m ┌───────────────────────────── [34mПШисгЬлижа Club[0;30;47m ────────────────────────────[0;1;37;47m┐ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │  ПЬиаЪиШну club . . . . . [1;44;37m@63;43;0s[0;1;47;37m  │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │  ГасибЬаШ гЮдмгслрд  . .  [1;44;37m@5;0;32767;0n[0;30;47m  ЮгтиЬк        (0-32767, 0=ЪаШ зсдлШ)[1;37m  │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │  Ctrl-R ЪаШ ЩжуЯЬаШ                                                      [1;37m│ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │             [0;1;42;33m@14;"СугШ"b[0;47;30m▄    [0;1;42;33m@14;"OK"b[0;47;30m▄    [0;1;41;33m@14;"Абмиж"b[0;47;30m▄  [0;1;47;37m│ [0m
[30;47m │              ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀     ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀     ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀  [0;1;47;37m│ [0m
[30;47m └[0;1;37;47m──────────────────────────────────────────────────────────────────────────┘ [0m} T Edit club, visual template


ECLT {[2J[0;30;47m ┌───────────────────────────── [34mПШисгЬлижа club[0;30;47m ────────────────────────────[0;1;37;47m┐ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ [31m1[30m. ПЬиаЪиШну club  . . . .  [34m@63;43;0s[0;1;47m  │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ [31m2[30m. ГасибЬаШ гЮдмгслрд  . .  [34m@5;0;32767;0n[30m (ЮгтиЬк, 0=ЪаШ зсдлШ)                  [1;37;47m│ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ [31m3[30m. ЛЬлШЩжву йугШлжк (banner)@1;"3Edit"b                                           [1;37m  │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m └[0;1;37;47m──────────────────────────────────────────────────────────────────────────┘ [0;1m
} T Edit club, linear template


ECFLD1 {[0;1m
!JПШиШбШвщ ЫщйлЬ лЮ дтШ зЬиаЪиШну лжм club.!)
[0;1m} T Edit club, linear template, field 1


ECFLD2 {[0;1m
!JПШиШбШвщ ЫщйлЬ лЮ дтШ ЫасибЬаШ Эрук лрд гЮдмгслрд лжм club йЬ ЮгтиЬк.
Тж зЬЫхж ЫтоЬлШа лагтк Шзц 0 рк 32767. Ад ЫщйЬлЬ 0, лШ гЮдчгШлШ лжм club ЯШ ЫаШлЮижчдлШа
Ьз'Шциайлжд.!)
[0;1m} T Edit club, linear template, field 2


ECCAN {[0;1;31m
!JЖ гЬлШЩжву лжм club ШбмищЯЮбЬ.!)
[0;1m} T Edit club, edit aborted


ECDONE {[0;1;32m
!JЖ гЬлШЩжву лжм club лтвЬарйЬ гЬ ЬзалмохШ.!)
[0;1m} T Edit club, edit successful




AXLVT {[0;30;47m ┌───────────────────────── [34mДзхзЬЫШ зицйЩШйЮк Club[0;30;47m ─────────────────────────[0;1;37;47m┐ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │  АзШалжчгЬдж бвЬаЫх ЪаШ READ зицйЩШйЮ йлж club  . . . . [1;44;37m@3;0;129;1n[0;47;30m  (0..129)  [1;37m│ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │  АзШалжчгЬдж бвЬаЫх ЪаШ DOWNLOAD зицйЩШйЮ йлж club . .  [1;44;37m@3;0;129;1n[0;47;30m  (0..129)  [1;37m│ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │  АзШалжчгЬдж бвЬаЫх ЪаШ WRITE зицйЩШйЮ йлж club . . . . [1;44;37m@3;0;129;1n[0;47;30m  (0..129)  [1;37m│ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │  АзШалжчгЬдж бвЬаЫх ЪаШ UPLOAD зицйЩШйЮ йлж club . . .  [1;44;37m@3;0;129;1n[0;47;30m  (0..129)  [1;37m│ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │  (ТШ ЬзхзЬЫШ  CO-OP бШа CLUB-OP ЫЬд гзжижчд дШ ЫрЯжчд  гШЭабс. ХиЮйагж-  [1;37m│ [0m
[30;47m │  зжауйлЬ лЮд Ьдлжву [1;33mC[0;30;47monfigure user ЪаШ дШ ЫщйЬлЬ Шмлс лШ ЬзхзЬЫШ йЬ гЬ-  [1;37m│ [0m
[30;47m │  гжджгтджмк оиуйлЬк).                                                    [1;37m│ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │  Ctrl-R ЪаШ ЩжуЯЬаШ                                                      [1;37m│ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │                                  [0;1;42;33m@14;"OK"b[0;47;30m▄    [0;1;41;33m@14;"Абмиж"b[0;47;30m▄  [0;1;47;37m│ [0m
[30;47m │                                   ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀     ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀  [0;1;47;37m│ [0m
[30;47m └[0;1;37;47m──────────────────────────────────────────────────────────────────────────┘ [0m} T Club Access levels, visual template


AXLLT {[2J[0;30;47m ┌───────────────────────── [34mДзхзЬЫШ зицйЩШйЮк Club[0;30;47m ─────────────────────────[0;1;37;47m┐ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ [31m1[30m. АзШалжчгЬдж бвЬаЫх ЪаШ READ зицйЩШйЮ йлж club  . . . . . . . . . [34m@3;0;129;1n[0;1;47m  │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ [31m2[30m. АзШалжчгЬдж бвЬаЫх ЪаШ DOWNLOAD зицйЩШйЮ йлж club . . . . . . .  [34m@3;0;129;1n[0;1;47m  │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ [31m3[30m. АзШалжчгЬдж бвЬаЫх ЪаШ WRITE зицйЩШйЮ йлж club . . . . . . . . . [34m@3;0;129;1n[0;1;47m  │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ [31m4[30m. АзШалжчгЬдж бвЬаЫх ЪаШ UPLOAD зицйЩШйЮ йлж club . . . . . . . .  [34m@3;0;129;1n[0;1;47m  │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │  (ТШ ЬзхзЬЫШ  CO-OP бШа CLUB-OP ЫЬд гзжижчд дШ ЫрЯжчд  гШЭабс. ХиЮйагж-  [1;37m│ [0m
[30;47m │  зжауйлЬ лЮд Ьдлжву [1;33mC[0;30;47monfigure user ЪаШ дШ ЫщйЬлЬ Шмлс лШ ЬзхзЬЫШ йЬ гЬ-  [1;37m│ [0m
[30;47m │  гжджгтджмк оиуйлЬк).                                                    [1;37m│ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m └[0;1;37;47m──────────────────────────────────────────────────────────────────────────┘ [0;1m
} T Club Access levels, linear template


AXLF1 {[0;1m
!JОа оиуйлЬк гЬ READ зицйЩШйЮ гзжижчд дШ Ыжмд лж club бШа дШ ЫаШЩсйжмд лШ гЮдчгШлс лжм.
ГЬд гзжижчд цгрк дШ всЩжмд ШиоЬхШ, дШ Ъиспжмд гЮдчгШлШ у дШ йлЬхвжмд ШиоЬхШ.
ГщйлЬ лж бвЬаЫх зжм
ШзШалЬхлШа ЪаШ дШ тоЬа тдШк оиуйлЮк READ зицйЩШйЮ йЬ Шмлц лж club.!)
[0;1m} T Club Access levels, linear template field 1


AXLF2 {[0;1m
!JОа оиуйлЬк гЬ DOWNLOAD зицйЩШйЮ гзжижчд дШ Ыжмд лж club,
дШ ЫаШЩсйжмд лШ гЮдчгШлс лжм,
бШа дШ всЩжмд лШ ШиоЬхШ лжм. ГЬд гзжижчд дШ Ъиспжмд гЮдчгШлШ
у дШ йлЬхвжмд ШиоЬхШ. ГщйлЬ лж бвЬаЫх зжм
ШзШалЬхлШа ЪаШ дШ тоЬа тдШк оиуйлЮк DOWNLOAD зицйЩШйЮ йЬ Шмлц лж club.!)
[0;1m} T Club Access levels, linear template field 2


AXLF3 {[0;1m
!JОа оиуйлЬк гЬ WRITE зицйЩШйЮ гзжижчд дШ Ыжмд лж club,
дШ ЫаШЩсйжмд бШа дШ Ъиспжмд гЮдчгШлШ, бШа дШ всЩжмд ШиоЬхШ.
ГЬд гзжижчд гцдж дШ йлЬхвжмд ШиоЬхШ.
ГщйлЬ лж бвЬаЫх зжм ШзШалЬхлШа ЪаШ дШ тоЬа тдШк оиуйлЮк
WRITE зицйЩШйЮ йЬ Шмлц лж club.!)
[0;1m} T Club Access levels, linear template field 3


AXLF4 {[0;1m
!JОа оиуйлЬк гЬ UPLOAD зицйЩШйЮ гзжижчд дШ Ыжмд лж club,
дШ ЫаШЩсйжмд бШа дШ Ъиспжмд гЮдчгШлШ,
бШа дШ всЩжмд бШа дШ ШзжйлЬхвжмд ШиоЬхШ.
ГщйлЬ лж бвЬаЫх зжм
ШзШалЬхлШа ЪаШ дШ тоЬа тдШк оиуйлЮк UPLOAD зицйЩШйЮ йЬ Шмлц лж club.!)
[0;1m} T Club Access levels, linear template field 4


WRNDEFC {[0;1;33m
!JАмлц ЬхдШа лж default club, йлж жзжхж зитзЬа дШ тожмд зицйЩШйЮ цвжа жа
оиуйлЬк. Тж бвЬаЫх ШдсЪдрйЮк лжм club тЪадЬ бШа ЯШ зШиШгЬхдЬа [37m0[33m.!)
[0;1m} T Club Access levels, the default club has to be readable by all







CHVT {[0;30;47m ┌───────────────────────────── [34mХиЬщйЬак Club[0;30;47m ──────────────────────────────[0;1;37;47m┐ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │  ХитрйЮ ЪаШ лЮд ЬЪЪиШну гЮдчгШлжк . . . . . . [1;44;37m@6;-30000;30000;1n[0;47;30m  (-30000..30000)  [1;37m│ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │  ХитрйЮ ЪаШ лЮд Шзжйлжву ШиоЬхжм . . . . . .  [1;44;37m@6;-30000;30000;1n[0;47;30m  (-30000..30000)  [1;37m│ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │  ХитрйЮ ЪаШ лЮд вупЮ ШиоЬхжм  . . . . . . . . [1;44;37m@6;-30000;30000;1n[0;47;30m  (-30000..30000)  [1;37m│ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │  ЙШлШдсврйЮ credits (credits/100 вЬзлс)  . .  [1;44;37m@6;-30000;30000;1n[0;47;30m  (-30000..30000)  [1;37m│ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │  (Ж бШлШдсврйЮ credits ЬхдШа йЬ credits Шдс 100 вЬзлс.  ГЮвШЫу, ЪаШ бШ-  [1;37m│ [0m
[30;47m │  лШдсврйЮ 1  credit/вЬзлц, ЫщйлЬ  лЮд лагу 100.  ГщйлЬ -1 ЪаШ лЮд  бШлс  [1;37m│ [0m
[30;47m │  ймдЯубЮ бШлШдсврйЮ йлак ДаЫабтк ПЬиажотк)                               [1;37m│ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │  Ctrl-R ЪаШ ЩжуЯЬаШ                                                      [1;37m│ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │                                  [0;1;42;33m@14;"OK"b[0;47;30m▄    [0;1;41;33m@14;"Абмиж"b[0;47;30m▄  [0;1;47;37m│ [0m
[30;47m │                                   ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀     ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀  [0;1;47;37m│ [0m
[30;47m └[0;1;37;47m──────────────────────────────────────────────────────────────────────────┘ [0m} T Club charges, visual template


CHLT {[2J[0;30;47m ┌───────────────────────── [34mДзхзЬЫШ зицйЩШйЮк Club[0;30;47m ─────────────────────────[0;1;37;47m┐ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ [31m1[30m. ХитрйЮ ЪаШ лЮд ЬЪЪиШну гЮдчгШлжк  . . . . . . . . . . . . . . [34m@6;-30000;30000;1n[0;1;47m  │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ [31m2[30m. ХитрйЮ ЪаШ лЮд Шзжйлжву ШиоЬхжм  . . . . . . . . . . . . . .  [34m@6;-30000;30000;1n[0;1;47m  │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ [31m3[30m. ХитрйЮ ЪаШ лЮд вупЮ ШиоЬхжм . . . . . . . . . . . . . . . . . [34m@6;-30000;30000;1n[0;1;47m  │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ [31m4[30m. ЙШлШдсврйЮ credits (credits/100 вЬзлс)  . . . . . . . . . . . [34m@6;-30000;30000;1n[0;1;47m  │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │  (Ж бШлШдсврйЮ credits ЬхдШа йЬ credits Шдс 100 вЬзлс.  ГЮвШЫу, ЪаШ бШ-  [1;37m│ [0m
[30;47m │  лШдсврйЮ 1  credit/вЬзлц, ЫщйлЬ  лЮд лагу 100.  ГщйлЬ -1 ЪаШ лЮд  бШлс  [1;37m│ [0m
[30;47m │  ймдЯубЮ бШлШдсврйЮ йлак ДаЫабтк ПЬиажотк)                               [1;37m│ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m └[0;1;37;47m──────────────────────────────────────────────────────────────────────────┘ [0;1m
} T Club charges, linear template


CHLTF1 {[0;1m
!JГщйлЬ лж зжйц гждсЫрд зжм ЯШ оиЬщдЬлШа ж оиуйлЮк бсЯЬ нжис зжм ЯШ ЪиснЬа тдШ гудмгШ йлж club.!)
[0;1m} T Club charges, linear template, field 1


CHLTF2 {[0;1m
!JГщйлЬ лж зжйц гждсЫрд зжм ЯШ оиЬщдЬлШа ж оиуйлЮк бсЯЬ нжис зжм ЯШ йлтвдЬа тдШ ШиоЬхж йлж club.!)
[0;1m} T Club charges, linear template, field 2


CHLTF3 {[0;1m
!JГщйлЬ лж зжйц гждсЫрд зжм ЯШ оиЬщдЬлШа ж оиуйлЮк бсЯЬ нжис зжм ЯШ вШгЩсдЬа тдШ ШиоЬхж Шзц лж club.!)
[0;1m} T Club charges, linear template, field 3


CHLTF4 {[0;1m
!JЙсЯЬ club гзжиЬх дШ тоЬа ЫаШнжиЬлабу оижджоитрйЮ. СЬ Шмлц лж зЬЫхж жихЭЬлЬ зцйЬк гждсЫЬк ЯШ ШнШаижчдлШа Шзц
лжд оиуйлЮ Шдс 100 вЬзлс зШижмйхШк йлж club. Длйа, ЪаШ лЮд бШдждабу оитрйЮ лжм 1 credit / вЬзлц, ЫщйлЬ йлж
зЬЫхж лЮд лабу 100 (100 credits / 100 вЬзлс = 1 credit / вЬзлц). Ад ЯтвЬлЬ лж club дШ тоЬа лЮд бШлс ймдЯубЮ
оитрйЮ лрд ЬаЫабщд зЬиажощд, ЫщйлЬ йлж зЬЫхж лЮд лагу -1.!)
[0;1m} T Club charges, linear template, field 4






CUASK {[0;1m
!WГщйлЬ лж цджгШ лжм оиуйлЮ лжм жзжхжм ЯтвЬлЬ дШ гЬлШЩсввЬлЬ лж ЬзхзЬЫж:!)[0m } T Configure user access, which user?


CUERR1 {[0;1;31m
!WКмзсгШа, Шмлцк ж оиуйлЮк ЫЬд мзсиоЬа.!)
[0;1m} T Configure user access, unknown user


CUERR2 {[0;1;31m
!WСаЪс, зЬихгЬдЬ... ГЬд гзжижчгЬ дШ зЬиажихйжмгЬ лж ЬзхзЬЫж лжм йчйжзШ! Амлцк тоЬа зсдлШ ймйжзабу зицйЩШйЮ!!)
[0;1m} T Configure user access, can't modify Sysop


CUHLP {[0;1m

Узсиожмд лШ Ьеук ЬзхзЬЫШ:

Default    !i!WЖ цзжаШ ЬаЫабу зицйЩШйЮ ШнШаиЬхлШа, бШа ж оиуйлЮк
Шзжблс лЮд бШлс ймдЯубЮ зицйЩШйЮ лжм club зжм лжм ШдШвжЪЬх,
цзрк Шмлу жихЭЬлШа гтйр лЮк Ьдлжвук [33mM[37m.!)
!0l
Zero       !i!WО оиуйлЮк ЫЬд ЩвтзЬа лж club, бШа ЫЬд тоЬа бШггхШ зицйЩШйЮ й'Шмлц.!)
!0l
Read       !i!WО оиуйлЮк гзжиЬх гцдж дШ ЫаШЩсйЬа гЮдчгШлШ.!)
!0l
Download   !i!WО оиуйлЮк гзжиЬх дШ ЫаШЩсйЬа гЮдчгШлШ бШа дШ всЩЬа ШиоЬхШ.!)
!0l
Write      !i!WО оиуйлЮк гзжиЬх дШ ЫаШЩсйЬа гЮдчгШлШ, дШ ЪиспЬа гЮдчгШлШ, бШа дШ всЩЬа ШиоЬхШ.!)
!0l
Upload     !i!WОзрк лж Write, Шввс ж оиуйлЮк гзжиЬх бШа дШ йлЬхвЬа ШиоЬхШ.!)
!0l
Co-op      !i!WО оиуйлЮк ЬхдШа жиЪШдрлук лжм club. ДоЬа звуиЮ зицйЩШйЮ йлж club, бШа гзжиЬх
дШ йлтвдЬа ШиоЬхШ зжм ЫЬд оиЬасЭждлШа тЪбиайЮ, дШ ЬЪбихдЬа ШиоЬхШ, бвз.!)
!0l
Club-op    !i!WО оиуйлЮк ЬхдШа ж ЩШйабцк жиЪШдрлук лжм club. ДоЬа лак хЫаЬк ЫмдШлцлЮлЬк гЬ
лжд ймджиЪШдрлу (Co-op), гЬ гцдЮ ЫаШнжис цла тоЬа лж ЫабШхргШ дШ ШввсеЬа лЮд зицйЩШйЮ
оиЮйлщд йлж club. ЛзжиЬх дШ мзсиоЬа гцдж тдШк ЩШйабцк жиЪШдрлук, жзцлЬ, Шд жихйЬлЬ сввж
жиЪШдрлу ЪаШ лж литожд club, ж мзсиорд жиЪШдрлук ЬблжзхЭЬлШа. Лцдж ж оЬаиайлук (sysop) гзжиЬх
дШ жихйЬа жиЪШдрлу ЪаШ тдШ club.!)
!0l
} T Configure user access, help on access levels


CUCUR {[0;1;32m
!WТж литожд ЬзхзЬЫж лжм гтвжмк [37m%s[32m ЬхдШа [37m%s[32m.!)
[0;1m} T Configure user access, current level of user


CULVL0 {Zero} T Configure user access, 'zero' level

CULVL1 {Read} T Configure user access, 'read' level

CULVL2 {Download} T Configure user access, 'download' level

CULVL3 {Write} T Configure user access, 'write' level

CULVL4 {Upload} T Configure user access, 'upload' level

CULVL5 {Co-op} T Configure user access, 'co-op' level

CULVL6 {Club-op} T Configure user access, 'club-op' level

CULVL7 {Operator} T Configure user access, 'operator' level


CUSYSW {[0;1;33m
!JУз'цпад: лж гтвжк Шмлц тоЬа зиждцгаШ Sysop йлак ДаЫабтк ПЬиажотк. Длйа
тоЬа зсдлШ бШа зШдлжч зицйЩШйЮ. Тж ЬзхзЬЫж зжм ЯШ имЯгхйЬлЬ лщиШ ЯШ айочйЬа
гцдж Шд ШнШаиЬЯжчд лШ зиждцгаШ оЬаиайлу Шзц лжд оиуйлЮ.!)
[0;1m} T Configure user access, warning about privileged user


CUMNU {[0;1m
ПШиШбШвщ ЫщйлЬ лЮд дтШ зицйЩШйЮ лжм оиуйлЮ:
!10l
D. Default
0. Zero
1. Read
2. Download
3. Write
4. Upload
5. Co-op
6. Club-op
!0l[0;1m} T Configure user access, level menu


CUSMNU {[0;1m
!WГщйлЬ лЮд ЬзавжЪу йШк ([33mD[37m,[33m0[37m-[33m6[37m,[33mX[37m ЪаШ тежЫж, у [33m?[37m ЪаШ ЩжуЯЬаШ):!) [0m} T Configure user access, short level menu


CUMNUR {[0;1;31m
!WКмзсгШа, Шмлу Ю ЬзавжЪу ЫЬд мзсиоЬа. ГщйлЬ [33m?[31m ЪаШ ЩжуЯЬаШ.!)
[0;1m} T Configure user access, invalid selection


CUMNUR1 {[0;1;31m
!WКмзсгШа, гцдж ж ХЬаиайлук гзжиЬх дШ жихйЬа ОиЪШдрлтк ЪаШ лШ Clubs.
ГщйлЬ [33m?[31m ЪаШ ЩжуЯЬаШ.!)
[0;1m} T Configure user access, only privileged users can set club-ops


CUMNUR2 {[0;1;31m
!WКмзсгШа, гцдж ж зирлШиоабцк жиЪШдрлук у ж ХЬаиайлук гзжиЬх дШ жихйЬа
oиЪШдрлтк ЪаШ лШ Clubs. ГщйлЬ [33m?[31m ЪаШ ЩжуЯЬаШ.!)
[0;1m} T Configure user access, only club-ops can set co-club-ops


CUMNUR3 {[0;1;33m
!JГЬд гзжиЬхлЬ дШ ШзжбвЬхйЬлЬ оиуйлЬк Шзц лж default club.!)
[0;1m} T Configure user access, the default club has to be readable by all



CUCHG {[0;1m
!WТж ЬзхзЬЫж лжм гтвжмк [32m%s[37m йлж club @CLUB@ сввШеЬ Ьзалмощк.!)
[0;1m} T Configure user access, user level set successfully


CUDIS {[0;1m
!WТж гтвжк [32m%s[37m осдЬа лЮд ЯтйЮ лжм жиЪШдрлу лжм club @CLUB@.!)
[0;1m} T Configure user access, current club operator lost their place


CUCNOT {[0;1;35m***
!JО ХЬаиайлук СмйлугШлжк гцвак йШк
тбШдЬ жиЪШдрлу лжм [37m%s[35m Club!
СмЪоШиЮлуиаШ бШа бШву ЬзалмохШ.!)
[0;1m} T Configure user access, notify new co-op/club-op









CRCASK {[0;1m
!WГщйЬ лж цджгШ лжм Club гЬЪсвЬ ЫЮгажмиЪт ([33m?[37m ЪаШ бШлсвжЪж):!)[0m } T Create club, ask name


CRERR {[0;1;31m
!JОоа, оШиалргтдЬ гжм, ЫЬд гзжиЬхк дШ нласеЬак club гЬ лтлжаж цджгШ!
Тж жджгШлсба лжм гзжиЬх дШ'оЬа гтоиа бШа 15 оШиШблуиЬк, бШа дШ зЬиавШгЩсдЬа
ШвнШиаЯгЮлабжчк оШиШблуиЬк, у лжмк Ьеук: # % ^ ( ) - _ + = [ ] .!)
[0;1m} T Create club, malformed club name


CRCXST {[0;1;31m
!JЛШдсиа гжм Ьйч... УзсиоЬа [5mуЫЮ[0;31;1m Шмлц лж Club огггггггггг!
(ЙсдЬ бШа бШдтдШ CRQS зцлЬ зцлЬ)!)
[0;1m} T Create club, club already exists


CRCCNF {[0;1m
!JЛс'йлШ... ФласолЮбЬ бШа лж "%s" Club.
АдлЬ лщиШ бШа йжмвжчзрйт лж гЬ лак Ьдлжвтк
[33mE[37m, [33mA[37m бШа [33mM[37m, ЬдлсеЬа;!)
[0;1m} T Create club, confirm creation




DCASK {[0;1m
!WПжаШджч нлрожч лж Club ЯЬк дШ йнсеЬак; ([33m?[37m ЪаШ бШлсвжЪж):!)[0m } T Delete Club, what club?


DCUNK {[0;1;31m
!JГЬд мзсиоЬа Шмлц лж Club... Тйб лйб лйб...!)
[0;1m} T Delete Club, unknown club


DCERR1 {[0;1;31m
!JЙжхлШ иЬ зжм зсЬа дШ нсЬа Club зжч тоЬа бцйгж гтйШ...
СЩуйЬ бШвчлЬиШ лЮд @BBS@ зжм ЬхдШа сЫЬаШ иЬ ШЫЬинсба...
ТщиШ зсва Шд Ьйч тоЬак бжввуйЬа бШа Ятк Шмлу дШ бсдЬак бШвжбШаиаду йщдЬа
бШа бШвс, бШвчлЬиШ ЯШ улШд дШ зЬихгЬдЬк гтоиа дШ нчЪжмд цвжа Шзц гтйШ...!)
} T Delete Club, Club is in use


DCERR2 {[0;1;31m
!JА лж бШЮгтдж... ДирлЬмгтдж ЬхдШа...
ЛШ бШвс, ЬхйШа йжЩШицк лщиШ;;;
Тж default Club зШк дШ йЩуйЬак;
АдлЬ циайЬ сввж зищлШ бШа гЬлс лШ втгЬ...
(Аввжк зсва бШа Шмлцк...
Бит зжм зтйШгЬ...)!)
} T Delete Club, can't delete default club


DCINFO {[0;1;32m
ОджгШ  . . . . . . . .  [37m@CLUB@[32m
ПЬиаЪиШну . . . . . . . [37m@CLUBDESC@[32m
ОиЪШдрлук  . . . . . .  [37m@CLUBOP@[32m
ЛЮдчгШлШ  . . . . . . . [37m@CLUBMSGS@[32m
АиоЬхШ . . . . . . . .  [37m@CLUBFILES@[32m
АиЯиШ . . . . . . . . . [37m@CLUBBLTS@[32m
[0;1m} T Delete Club, club information


DCCONF {[0;1;31m
!W[5m██[0;1;31m  ПРОСОХЖ: !iАзШдлщдлШк YES йлЮд зШиШбслр
ЬищлЮйЮ лж йчйлЮгШ ЯШ ЫаШЪиспЬа:!)
!W- Тж хЫаж лж Club!)
!W- ТШ гЮдчгШлШ, лШ ШиоЬхШ бШа лШ сиЯиШ лжм!)
!W- ОвШ лШ йоЬлабс directories!)
!0l[0;1m
!WДхйШа йхЪжмижк цла ЯтвЬак дШ лж йнсеЬак [[33mY[37m]yes=дШа / [[33mN[37m]o=цоа);!)[0m } T Delete Club, ask for confirmation


DCCR {[0;1;31m
!JПШиШбШвщ ШзШдлуйлЬ йлЮд ЬищлЮйЮ гЬ [33mY[31m у [33mN[31m.!)
[0;1m} T Delete Club, invalid answer


DCSNUK {[0;1;31m
!JТщиШ гсвайлШ... АдлЬ дШ зсиЬак вШоЬхж дШ звжмлхйЬа ж вШоЬажзщвЮк...
Йсзжажк гзубЬ гтйШ йлж Club цйж ЩШйсдаЭЬк йлж гмШвц йжм лж ЫхвЮггШ
лЮк Эрук бШа лжм ЯШдслжм лжм.
СмдтоайЬ дШ лж ЩШйШдхЭЬак бШа Шд ЬхдШа дШ лж
ЯспЬак твШ цлШд ЯШ тоЬа нчЪЬа...

(ЙШа йжм'вЬЪШ Ър йЩуйЬ лЮд @BBS@ зжм ЬхдШа сЫЬаШ...)!)
[0;1m} T Delete Club, someone just entered the Club


DCWAIT {[0;1;32;5m
ПШиШбШвщ зЬиагтдЬлЬ, цвШ лШ йнсЭр цвШ лШ еЬбжавасЭр...[30m[K} T Delete Club, please wait


DCOK {[0;1;32m


ПсЬа лж Club, зсдЬ бШа лШ directories зжм лжм ШдубШд.
[0;1m} T Delete Club, club deleted





LCHDR {[0;1m
[33mClub            ХЬаиайлук  ПЬиаЪиШну Club[37m
─────────────────────────────────────────────────────────────────────────────
[0m} T Short club list, header


LCTAB {%-15s %-10s %-50.50s
} T Short club list, table line


LCFTR {[0;1m─────────────────────────────────────────────────────────────────────────────

} T Short club list, footer


LC2HDR {[0;1m
       ┌──────────┬────────┬───────┬────────────┐
┌──────│ [33mЛЮдчгШлШ[37m │ [33mАиоЬхШ[37m │ [33mАиЯиШ[37m │ [33mГЮгажмиЪхШ[37m │────┬───────────────────────┐
│      └────────┐ └──┐    ┌┘   ┌───┘     ┌──────┘    │                       │
│ [33mClub[37m          │    │    │    │         │ [33mОиЪШдрлук[37m │ [33mПЬиаЪиШну[37m             │
├───────────────┼────┼────┼────┼─────────┼───────────┼───────────────────────┤
[0;1m} T Long club list, header


LC2TAB {│[0m%-15s[1m│[0m%4d[1m│[0m%4d[1m│[0m%4d[1m│[0m%-9s[1m│[0m%-11s[1m│[0m%-23.23s[1m│
} T Long club list, table line


LC2FTR {[0;1m└───────────────┴────┴────┴────┴─────────┴───────────┴───────────────────────┘

} T Long club list, footer



SCASK {[0;1m
!WГщйлЬ лж цджгШ лжм дтжм Club у [33m?[37m ЪаШ бШлсвжЪж:!)[0m } T Select new club, what club?


SCERR {[0;1;31m
!JСмЪЪдщгЮ, ЫЬд мзсиоЬа лтлжаж Club.
ГщйлЬ [33mX[31m (eXit) жзжаШЫузжлЬ йлаЪгу ЪаШ Ьзайлижну
йлж бЬдлиабц гЬджч лрд Clubs.!)
[0;1m} T Select new club, club does not exist


SCADD {[0;1;32m
!JТж club [37m%s[32m зижйлтЯЮбЬ йлЮд ЪиуЪжиЮ ШдходЬмйу йШк.!)
[0;1m} T Select new club, the club was added to your quickscan configuration







NETMNU {[2J[0m[47;1;37m ┌─────────────────────────────────────────────────────────[0;30;47m┐ [0m
[47;1;37m │  [0;47;30m           ГаШджгу гЮдмгслрд гтйр Ыаблчжм              [0;47;30m│ [0m
[47;1;37m │  [0;47;30m─────────────────────────────────────────────────────  [0;47;30m│ [0m
[47;1;37m │  [0;31;47mH[30melp  . . . . . . . . . . . . . . ВЬдабтк ПвЮижнжихЬк  [30m│ [0m
[47;1;37m │  [0;31;47mD[30mefine import BBSs . . . .  ПЮЪтк ЬайШЪрЪук гЮдмгслрд  [30m│ [0m
[47;1;37m │  [0;31;47mI[30mmport clubs  . . .  ДайШЪрЪу гЮдмгслрд Шзц лж Ыхблмж  [30m│ [0m
[47;1;37m │  [0;31;47mE[30mxport clubs . . . . ДеШЪрЪу гЮдмгслрд зижк лж Ыхблмж  [30m│ [0m
[47;1;37m │  [0;31;47mS[30mtatus  . . . . .  ЙШлсйлШйЮ ЬайШЪрЪщд Шмлжч лжм club  [30m│ [0m
[47;1;37m │                                                         [0;47;30m│ [0m
[47;1;37m │ [0;30;47me[31mX[30mit . . . . . . . . . . . . . . . . . . . . .  ДежЫжк  [30m│ [0m
[47;1;37m └[0;30;47m─────────────────────────────────────────────────────────┘ [0;1m

[0;1m} T Networking menu, long version


SHNETMNU {[0;1m
!WГщйлЬ лЮд ЬзавжЪу йШк
([33mH[37m,[33mD[37m,[33mI[37m,[33mE[37m,[33mC[37m,[33mS[37m,[33mX[37m
ЪаШ тежЫж, у [33m?[37m ЪаШ лж гЬджч): !)[0m} T Networking menu, short version



NETHELP {[0;1m
!JТШ гЮдчгШлШ лрд clubs гзжижчд дШ ЫаШдЬгЮЯжчд гтйр Ыаблчжм. Амлц ЬдджЬх лЮд
ЬайШЪрЪу гЮдмгслрд Шзц сввЬк ЩсйЬак, Шввс бШа лЮд ЬеШЪрЪу лжмк.!)

!JВаШ лЮд ЬайШЪрЪу гЮдмгслрд зитзЬа дШ жихйжмгЬ (гЬ лЮд Ьдлжву
[33mD[37mefine import BBSs) лШ ждцгШлШ лрд ймйлЮгслрд Шзц лШ жзжхШ ЯШ
ЬайсЪжмгЬ гЮдчгШлШ бШЯщк бШа лж оиждабц ЫасйлЮгШ зжм ЯШ гЬйжвШЩЬх гЬлШеч
лрд ЬайШЪрЪщд зШбтлрд гЮдмгслрд.!)

!JЛЬлс гзжижчгЬ дШ жихйжмгЬ лжд зхдШбШ ЬайШЪрЪук clubs. О зхдШбШк тоЬа Ычж
йлувЬк: лж ЫаШдЬгЮгтдж club Шз'лж жзжхж ЬайсЪжмгЬ гЮдчгШлШ бШа лж лжзабц club
йлж жзжхж лШ ШзжЯЮбЬчжмгЬ. Тж лжзабц club нмйабс ЪиснЬлШа йШд [32m/Club[37m.
Тж ЫаШдЬгЮгтдж club тоЬа ШибЬлс ЫаШнжиЬлабу йчдлШеЮ. Дзх зШиШЫЬхЪгШла:!)

!C[32mhost.domain.tld/BBSNAME/Club[37m!)

!JТж зищлж гтижк ЬхдШа Ю звуиЮк Internet ЫаЬчЯмдйЮ лжм гЮоШдугШлжк зжм
навжеЬдЬх лЮд ЩсйЮ. АбжвжмЯЬх ж брЫабцк ЫаблчрйЮк лЮк ЩсйЮк (BBSNAME) бШа
лтвжк лж цджгШ лжм club. Пиад зижйЯтйЬлЬ ЬайШЪцгЬдШ clubs Шзц гхШ сввЮ ЩсйЮ,
зитзЬа дШ тоЬлЬ ЫЮвщйЬа лж цджгШ (host.domain.tld/BBSNAME) лжм ШзжгШбимйгтджм
ймйлугШлжк гЬ лЮд Ьдлжву [33mD[37m (зШиШзсдр).!)

!JВаШ дШ ЬесЪжмгЬ clubs йЬ сввЬк ЩсйЬак, ШибЬх дШ оиЮйагжзжауйжмгЬ лЮд Ьдлжву
[33mE[37mxport clubs ЪаШ дШ жихйжмгЬ зжаШ Шзц лШ clubs
гШк ЬхдШа лжзабс бШа зжаШ цоа.!)

!JТтвжк, гЬ лЮд Ьдлжву [33mS[37mtatus гзжижчгЬ дШ ЫжчгЬ зжаШ clubs ЬайсЪжмд
гЮдчгШлШ Шзц зжаШ ймйлугШлШ.!)
[0;1m} T Network menu help




DIPMNU {[0;1m
!WЗтвЬлЬ дШ зижйЯтйЬлЬ ([[33mA[37m]dd), дШ гЬлШЩсввЬлЬ
([[33mM[37m]odify), у дШ ЫаШЪиспЬлЬ ([[33mD[37m]elete) тдШ йчйлЮгШ; ГщйлЬ
[33mA[37m, [33mM[37m, [33mD[37m, [33mX[37m ЪаШ тежЫж у [33m?[37m ЪаШ
бШлсвжЪж мзШиоцдлрд ймйлЮгслрд:!)[0m } T Networking, operations on import points


DIPADD {[0;1m
!JГщйлЬ лж цджгШ лжм ймйлугШлжк зжм ЯтвЬлЬ дШ зижйЯтйЬлЬ, йлЮ гжину
[32mhost.domain.tld/BBSCODE[37m. ЙЬнШвШхШ бШа габис
ЫЬд ЫаШнтижмд. ЛзжиЬхлЬ дШ оиЮйагжзжауйЬлЬ лЮд
ШиаЯгЮлабу IP ЫаЬчЯмдйЮ лжм ймйлугШлжк Шд ЯтвЬлЬ. Авващк, зитзЬа дШ ЫщйЬлЬ лЮд
звуиЮ ЫаЬчЯмдйЮ лжм ШзжгШбимйгтджм ймйлугШлжк. Тж цджгШ ЫЬд ЬвтЪоЬлШа Шзц лж
йчйлЮгШ: зижйжоу йлШ всЯЮ!!)

!WОджгШ дтжм ймйлугШлжк Шз'цзжм ЯШ ЬайсЪжмгЬ гЮдчгШлШ:!)[0m } T Networking, add import point


DIPADR {[0;1;31m
!JЖ ЫаЬчЯмдйЮ лжм ймйлугШлжк ЫЬд ЫЬходЬа йрйлу. ПитзЬа дШ ЬхдШа йлЮ
гжину [37mhost.domain.tld/BBSCODE[31m у, Шд ЫЬд ЪдрихЭЬлЬ лж ШвнШЩЮлабц
цджгШ лжм ймйлугШлжк, [37mwww.xxx.yyy.zzz/BBSCODE[31m.!)
[0;1m} T Networking, incorrect remote BBS address


DIPADX {[0;1;31m
!JТж йчйлЮгШ [37m%s[31m тоЬа уЫЮ ЫЮврЯЬх.[31m!)
[0;1m} T Networking, system name already exists


DIPADT {[0;1m
!JТщиШ зитзЬа дШ жихйЬлЬ бсЯЬ зцлЬ ЯШ ЬайсЪжмгЬ гЮдчгШлШ Шзц лж зШиШзсдр
йчйлЮгШ. ГщйлЬ тдШд ШиаЯгц ЮгЬищд гЬЪШвчлЬиж лжм гЮЫтд, у тдШд ШиаЯгц
ШбжвжмЯжчгЬдж Шзц лж ЬзхЯЬгШ [33mm[37m (minutes, вЬзлс) у [33mh[37m
(hours, щиЬк). Дзх зШиШЫЬхЪгШла, ЫхдждлШк Шзвс "1" жихЭжмгЬ цла Ю ЬайШЪрЪу ЯШ
ЬзаоЬаиЬхлШа Шдс гхШ гтиШ. ГхдждлШк "15m", Шмлц ЯШ ЪхдЬлШа Шдс 15 вЬзлс.!)

!WДвсоайлж оиждабц ЫасйлЮгШ гЬлШеч ЬдЮгЬищйЬрд:!)[0m } T Networking, asking for time between updates

DIPADTR {[0;1;31m
!JСмЪЪдщгЮ, ЫЬд ШдШЪдрихйШгЬ лж ЬзхЯЬгШ зжм оиЮйагжзжауйШлЬ.!)
[0;1m} T Networking, time specification suffix was invalid


DIPADDOK {[0;1;32m
!JЙШвщк, лж йчйлЮгШ [37m%s[32m ЫЮвщЯЮбЬ Ьзалмощк. ЛЮдчгШлШ ЯШ ЬайсЪждлШа
бсЯЬ [37m%d[32m ЫЬмлЬицвЬзлШ.!)
[0;1m} T Networking, system added




DIPDEL {[0;1m
!JГщйлЬ лж цджгШ лжм ймйлугШлжк зжм ЯтвЬлЬ дШ ЫаШЪиспЬлЬ, у [33m?[37m ЪаШ
бШлсвжЪж ймйлЮгслрд:!) [0m} T Networking, delete import point


DIPDELX {[0;1;31m
!JАмлц лж йчйлЮгШ ЫЬд тоЬа ЫЮврЯЬх.!)
[0;1m} T Networking, delete import point, system doesn't exist


DIPDELOK {[0;1;32m
!JДдлсеЬа, лж йчйлЮгШ [37m%s[32m ЫаЬЪиснЮ.!)
[0;1m} T Networking, system deleted



DIPMOD {[0;1m
!JГщйлЬ лж цджгШ лжм ймйлугШлжк зжм ЯтвЬлЬ дШ гЬлШЩсвЬлЬ, у [33m?[37m ЪаШ
бШлсвжЪж ймйлЮгслрд:!) [0m} T Networking, modify import point


DIPMODX {[0;1;31m
!JАмлц лж йчйлЮгШ ЫЬд тоЬа ЫЮврЯЬх.!)
[0;1m} T Networking, modify import point, system doesn't exist.


DIPMODT {[0;1;32m
!JДайсЪжмгЬ гЮдчгШлШ Шзц лж йчйлЮгШ [37m%s[32m бсЯЬ [37m%d[32m гтиЬк,
[37m%d[32m щиЬк бШа [37m%d[32m вЬзлс.!)
[0;1m} T Networking, modify import point, show refresh time


DIPMODA {[0;1m
!JАд ЯтвЬлЬ д'ШввсеЬлЬ лж зШиШзсдр, ЫщйлЬ тдШд ШиаЯгц ЮгЬищд гЬЪШвчлЬиж лжм
гЮЫтд, у тдШд ШиаЯгц ШбжвжмЯжчгЬдж Шзц лж ЬзхЯЬгШ [33mm[37m (minutes, вЬзлс)
у [33mh[37m (hours, щиЬк). Дзх зШиШЫЬхЪгШла, ЫхдждлШк Шзвс "1" жихЭжмгЬ цла
Ю ЬайШЪрЪу ЯШ ЬзаоЬаиЬхлШа Шдс гхШ гтиШ. ГхдждлШк "15m", Шмлц ЯШ ЪхдЬлШа Шдс
15 вЬзлс.!)

!WДвсоайлж оиждабц ЫасйлЮгШ гЬлШеч ЬдЮгЬищйЬрд: [[33mEnter[37m=цоа ШввШЪу]!)[0m } T Networking, asking for new time between updates


DIPMODOK {[0;1;32m
!JДдлсеЬа, Ю бШлШощиЮйЮ лжм ймйлугШлжк [[37m%s[[32m гЬлШЩвуЯЮбЬ.!)
[0;1m} T Networking, system updated






IMPCLUB {[0;1m
!JПШиШбШвщ ЫщйлЬ лж цджгШ лжм ШзжгШбимйгтджм club Шзц лж жзжхж ЯШ ЬайсЪжмгЬ
гЮдчгШлШ. Ж йчдлШеЮ лжм ШзжгШбимйгтджм club ЬхдШа
[32mhost.domain.tld/BBSCODE/Club[37m. Пижйжоу: зтиШд лжм ймдлШдлабжч
ЬвтЪожм, Ю жиЯцлЮлШ лжм ШзжгШбимйгтджм club ЫЬд гзжиЬх дШ ЬвЬЪоЯЬх! ОджгШ
ШзжгШбимйгтджм club: !)[0m } T Networking, asking for name of remote club


IMPCLBR {[0;1;31m
!JТж цджгШ лжм ШзжгШбимйгтджм club ЫЬд ЬхдШа ймдлШблабс йрйлц!!)
[0;1m} T Networking, invalid remote club path


IMPCLBS {[0;1;31m
!JТж цджгШ лжм ШзжгШбимйгтджм ймйлугШлжк ЫЬд тоЬа ЫЮврЯЬх ШбцгШ!
ХиЮйагжзжауйлЬ лЮд Ьдлжву [33mD[31m ЪаШ дШ лж зижйЯтйЬлЬ.!)
[0;1m} T Networking, system name hasn't been declared


IMPLOCC {[0;1m
!JСЬ зжаж лжзабц club дШ ЬдШзжЯтйжмгЬ лШ ЬайШЪцгЬдШ гЮдчгШлШ; ГщйлЬ
[33m?[37m ЪаШ бШлсвжЪж, у [33m-[37m ЪаШ дШ ШбмищйЬлЬ лЮд ЬайШЪрЪу
лжм ШзжгШбимйгтджм club:!)[0m } T Networking, asking for name of local club


IMPLOCR {[0;1;31m
!JГЬд мзсиоЬа Шмлц лж лжзабц Club... ГжбагсйлЬ [33m?[31m ЪаШ дШ ЫЬхлЬ
лжд бШлсвжЪж лрд clubs лЮк ЩсйЮк.!)
[0;1m} T Networking, unknown local club


IMPOK {[0;1;32m
!JДдлсеЬа, лШ гЮдчгШлШ лжм ШзжгШбимйгтджм club [37m%s[32m ЯШ ЬайсЪждлШа йлж
лжзабц club [37m%s[32m.!)
[0;1m} T Networking, added import entry

IMPDISP {[0;1;33m
!JТШ гЮдчгШлШ лжм ШзжгШбимйгтджм club [37m%s[33m ЯШ ЬайсЪждлШа йлж
лжзабц club [37m%s[33m. СЮгЬхрйЮ: жихЭждлШк Шмлу лЮд ШдлайлжаохШ,
бШлШиЪуйШгЬ лЮд зижшзсиожмйШ, зжм ЬдШзцЯЬлЬ лШ гЮдчгШлШ йлж лжзабц club
[37m%s[33m.!)
[0;1m} T Networking, added import entry, displaced previous one






DIPLSTH {[0;1;32m
                                             ДайШЪрЪу бсЯЬ:
АзжгШбимйгтдж йчйлЮгШ                     ЖгтиЬк  ЧиЬк  КЬзлс  ДайШЪцгЬдШ clubs
!F─
} T Networking, remote system list header


DIPLSTL {[0;1m%-40.40s    %2s     %2s     %2s        %4d
} T Networking, remote system list item


DIPLSTF {[0;1;32m!F─
[0;1m} T Networking, remote system list footer




EXPLSTH {[0;1m
Тжзабц club      Тжзабц/[32mДзалитзжмгЬ[37m/[31mАзШЪжиЬчжмгЬ[37m
!F─
} T Networking, list of exported clubs, header


EXPLSTL {[0;1m%-15.15s  !W!i} T Networking, list of exported clubs, entry part 1

EXPLSTL2 {Тжзабц Club!)
!0l} T Networking, list of exported clubs, local club

EXPLSTL3 {Аджаблц ЪаШ цвШ лШ ймйлугШлШ!)
!0l} T Networking, list of exported clubs, open to all

EXPLSTL4 {[0;1;32m%s } T Networking, list of exported clubs, ALLOW string

EXPLSTL5 {[0;1;31m%s } T Networking, list of exported clubs, DENY string

EXPLSTL6 {!)
!0l} T Networking, list of exported clubs, ALLOW/DENY end of line


EXPLSTF {[0;1m!F─
[0;1m} T Networking, list of exported clubs, footer



EXPASK {[0;1m
!JГщйлЬ лж цджгШ лжм лжзабжч club лжм жзжхжм лЮд бШлсйлШйЮ ЯтвЬлЬ дШ
ШввсеЬлЬ, у [33mALL[37m ЪаШ цвШ лШ clubs, у [33m?[37m ЪаШ бШлсвжЪж:!) [0m} T  Networking, export status change, ask for club name


EXPCLBR {[0;1;31m
!JСмЪЪдщгЮ, ЫЬд мзсиоЬа Шмлц лж club. ГщйлЬ [33m?[31m ЪаШ бШлсвжЪж.!)
[0;1m} T Networking, export status change, unknown club


EXPSPEC {[0;1m
!JТщиШ зитзЬа дШ жихйЬлЬ лак зижйЩсйЬак етдрд ймйлЮгслрд й'Шмлц лж club.
ЛзжиЬхлЬ дШ ЫщйЬлЬ [33m-[37m ЪаШ дШ ШзШЪжиЬчйЬлЬ йЬ цвжмк лЮд зицйЩШйЮ
(лжзабц club), [33m+[37m ЪаШ дШ ЬзалитпЬлЬ лЮд ЬеШЪрЪу лжм club йЬ цвШ лШ
ймйлугШлШ. ЛзжиЬхлЬ ЬзхйЮк дШ ЫщйЬлЬ гхШ вхйлШ ймйлЮгслрд (зо host.domain.tld
у host.domain.tld/BBSCODE) ориайгтдрд гЬ ЫаШйлугШлШ. Ж зицйЩШйЮ ЯШ ЬзалитзЬлШа
гцдж й'Шмлс лШ ймйлугШлШ. Ад ж зищлжк оШиШблуиШк лЮк вхйлШк ЬхдШа "-", лцлЬ Ю
зицйЩШйЮ ЯШ ЬзалитзЬлШа йЬ цвжмк ДЙТОС Шзц лШ ймйлугШлШ зжм ЯШ ШдШнтиЬлЬ.!)

!WГщйлЬ лЮд вхйлШ зицйЩШйЮк ЪаШ лж зШиШзсдр club, у [33m?[37m ЪаШ бШлсвжЪж
лрд clubs бШа лрд зижйЩсйЬщд лжмк:!) [0m} T Networking, asking for export access list



NETST1 {[0;1m
!WЙШлсйлШйЮ ЬайШЪрЪщд гЮдмгслрд:!)
[0;1m} T Networking, import status


NETST2 {[0;1;32m
!WАзц лж йчйлЮгШ [37m%s[32m:!)
[37m!F─
[0;1m} T Networking, import, system name


NETST3 {[0;1;32m    %-55.55s -> %-16.16s
} T Networking, import, list item


NETST4 {[0;1m!F─
[0;1m} T Networking, import, list footer








WCNAXES {[0;1;31m
!JСмЪЪдщгЮ, ЫЬд тоЬлЬ ЬзхзЬЫж зжм дШ йШк ЬзалитзЬа
лЮд Шзжйлжву гЮдмгслрд йлж Club @CLUB@.!)
[0;1m} T Write Club message, you don't have write access


WCCLUBR {[0;1;31m
!JСмЪЪдщгЮ, Шмлц лж Club ЫЬд мзсиоЬа.!)
[0;1m} T Write Club message, club does not exist


WCNCRDS {[0;1;31m
!JГЬд тоЬлЬ ШибЬлтк гждсЫЬк оиуйЮк ЪаШ дШ йлЬхвЬлЬ гудмгШ йлж Club @CLUB@.!)
[0;1m} T Write Club message: not enough credits, while asking


WCRNEC {[0;1;31m
!JГЬд тоЬлЬ заШ ШибЬлтк гждсЫЬк оицджм оиуйЮк ЪаШ дШ йлЬхвЬлЬ Шмлц лж гудмгШ
йлж Club @CLUB@.!)
[0;1m} T Write Club message: not enough credits to send


WCWHO {[0;1m
!WГщйлЬ лжд зШиШвузлЮ лжм гЮдчгШлжк
([33m?[37m ЪаШ ЩжуЯЬаШ) [Enter=Овжа]:!) [0m} T Write Club message: get recipient of message


WCHELP {[0;1m

!JЛзжиЬхлЬ дШ ЫщйЬлЬ лжд зШиШвузлЮ лжм гЮдчгШлцк йШк рк Ьеук:!)

1. !i!JГщйлЬ лж пЬмЫщдмгж Ьдцк гтвжмк. ЛзжиЬхлЬ дШ ЫщйЬлЬ лж пЬмЫщдмгж
жвцбвЮиж, у дШ ЪиспЬлЬ лжмвсоайлжд лШ зищлШ лихШ ЪисггШлШ. Тж йчйлЮгШ ЯШ
ШдШвсЩЬа лШ мзцвжазШ.!)
!0l
2. !i!JГщйлЬ [33mEnter[37m ЪаШ дШ йлЬхвЬлЬ гудмгШ зижк цвжмк.!)
!0l
[0;1m} T Write Club message: help


WCUNKID {[0;1;31m
!JКмзсгШа, Шмлц лж пЬмЫщдмгж ЫЬд мзсиоЬа.!)
[0;1m} T Write Club message: unknown user ID


WCRCPOK {[0;1;32m
!JПШиШвузлЮк лжм гЮдчгШлцк йШк ЯШ ЬхдШа лж гтвжк [37m%s[32m.!)
[0;1m} T Write Club message: confirming recipient of message


WCRCPALL {[0;1;32m
!JТж гудмгс йШк ЯШ йлШвЬх зижк [37mОвжмк[32m.!)
[0;1m} T Write Club message: confirming recipient of message is 'All'


WCATT {[0;1m
!WЗтвЬлЬ дШ ЬзаймдспЬлЬ тдШ ШиоЬхж йЬ Шмлц лж гудмгШ;
(Ж оитрйЮ ЪаШ Шмлу лЮд мзЮиЬйхШ ЬхдШа [32m%d гждсЫ%s[37m)
([[33mУ[0;1m]es=дШа / [[33mN[0;1m]o=цоа):!) [0m} T Write Club message: ask if file attachment required


WCRRSEL {[0;1;31m
!WПШиШбШвщ ЫщйлЬ [33mY[31m у [33mN[31m.!)
[0;1m} T Write Club message: invalid answer to question


WCATTAPP {[0;1;32m
██  !W!iЖ гЬлШнжис лжм ймдЮггтджм ШиоЬхжм тЪадЬ ШмлцгШлШ ЬзалиЬзлу йлж Club.!)
!0l[0;1m} T Write Club message: attachment auto-approved


WCATTNAP {[0;1;33m
██  !W!iЖ гЬлШнжис лжм ймдЮггтджм ШиоЬхжм ЯШ ЪхдЬа
ЬзалиЬзлу Шнжч лж ЬвтЪеЬа ж ОиЪШдрлук лжм Club.!)
!0l[0;1m} T Write Club message: attachment needs approval


WCRNOT {[0;1m***

!JТж гтвжк [32m%s[37m гцвак йШк тйлЬавЬ гудмгШ йлж Club
[32m%s[37m гЬ ЯтгШ "[32m%s[37m".!)
[0;1m
} T Write Club message: notification for recipient


WCRNOTC {[0;1m***

!JТж гтвжк [32m%s[37m гцвак йШк ШдлтЪиШпЬ гудмгШ йлж Club [32m%s[37m
гЬ ЯтгШ "[32m%s[37m".!)
[0;1m
} T Write Club message: notification for recipient, copied message






RCMNU {[0;1m
!JЛзжиЬхлЬ дШ ЫаШвтеЬлЬ лШ гЮдчгШлШ зжм
ЯтвЬлЬ дШ ЫаШЩсйЬлЬ гЬ лжмк Ьеук лицзжмк:!)@CLUB@

  [[33mS[37m~]can . . . . . . АдходЬмйЮ гЮдмгслрд тдШ зицк тдШ
  [[33mL[37m~]ist  . . . . . . . СмдЬоцгЬдЮ ЬзхЫЬаеЮ гЮдмгслрд
  [[33mT[37m~]o You . . . . . .  АдходЬмйЮ гЮдмгслрд зижк Ьйск
  [[33mF[37m~]rom You  . . . . .  АдходЬмйЮ гЮдмгслрд Шзц Ьйск
  [[33mK[37m~]ey  . .  АдходЬмйЮ гЮдмгслрд щк зицк втеЮ бвЬаЫх

  [[33mQ[37m~]uick . . . . . . . . . ЛЬджч ЪиуЪжиЮк ШдходЬмйЮк

!WГщйлЬ лЮд ЬзавжЪу йШк ([33m?[37m ЪаШ ЩжуЯЬаШ) } T Read Club messages, method menu


RCMNUD {[Enter=[33m%c[37m]:[0m!) } T Read Club messages, default value


RCMNUR {[0;1;31m
!JАмлу Ю ЬзавжЪу ЫЬд ЬхдШа ЫмдШлу.!)
[0;1m} T Read Club messages, invalid selection in method menu


RCMNUH {[0;1m

!JУзсиожмд зжввжх лицзжа ЬзавжЪук ШдсЪдрйЮк гЮдмгслрд Ьдцк Club:!)

!W[[33mS[37m]can:     !12iЛзжиЬхлЬ Шзвщк дШ лШ ЫаШлитеЬлЬ,
лж жзжхж йЮгШхдЬа цла еЬбадслЬ Шзц лж зищлж гудмгШ
(у жзжажЫузжлЬ ЯЬвуйЬлЬ) бШа ШиохЭЬлЬ дШ ЫаШЩсЭЬлЬ.
ЛзжиЬхлЬ дШ "ШбжвжмЯЬхлЬ" ЫаШвцЪжмк блв.!)
!0l 
!W[[33mT[37m]o you:   !12iОзрк бШа Ю зШиШзсдр гтЯжЫжк ШдсЪдрйЮк,
Шввс ЬгнШдхЭждлШа гцдж лШ гЮдчгШлШ зжм зижжихЭждлШа зижк Ьйск.!)
!0l 
!W[[33mF[37m]rom you: !12iТж хЫаж, Шввс ЬгнШдхЭждлШа гцдж лШ
гЮдчгШлШ зжм тоЬлЬ ЪиспЬа ЬйЬхк.!)
!0l 
!W[[33mL[37m]ist:     !12iЛзжиЬхлЬ дШ зсиЬлЬ тдШ бШлсвжЪж
гЮдмгслрд Ьдцк Club йЬ гаШ Шзц лак ШбцвжмЯЬк гжинтк: ПЬиаЪиШну, Тхлвжк,
ПвуиЬк бЬхгЬдж. ЙсЯЬ зЬиаЪиШну ШбжвжмЯЬхлШа Шзц лжд ШиаЯгц лжм
гЮдчгШлжк тлйа щйлЬ дШ гзжиЬхлЬ ШиЪцлЬиШ дШ ШиохйЬлЬ Шз'Шмлц.!)
!0l
!W[[33mK[37m]ey:      !12iMзжиЬхлЬ дШ ЫщйЬлЬ гаШ у зЬиаййцлЬиЬк
"втеЬак бвЬаЫаШ". Ж ШдходЬмйЮ зжм ЯШ ЪхдЬа йчгнрдШ гЬ Шмлтк лак втеЬак
бвЬаЫас ЯШ тоЬа щк ШзжлтвЬйгШ дШ ЬгнШдайлжчд ЛОМО лШ гЮдчгШлШ
лрд жзжхрд Ю зЬиаЪиШну ЬгзЬиатоЬа лЮд у лак втеЬак бвЬаЫас.!)
!0l
!W[[33mQ[37m]uick:    !12iЛзжиЬхлЬ дШ бсдЬлЬ жлаЫузжлЬ Шзц лШ зШиШзсдр
йЬ гаШ жгсЫШ Clubs зжм йШк ЬдЫаШнтиЬа, бШлЬмЯЬхШд, Шзж лж лЬвЬмлШхж
гудмгШ зжм тоЬлЬ ЫаШЩсйЬа.!)
!0l
[0;1m
} T Read Club messages, help on method menu


DNLNAX {[0;1;31m
!JКмзсгШа, лж ЬзхзЬЫж зицйЩШйук йШк ЫЬд йШк ЬзалитзЬа лЮд вупЮ ШиоЬхрд Шзц
лж club [37m@CLUB@[31m.!)
[0;1m} T Download Club files, access denied


DMNU {[0;1m
!JЛзжиЬхлЬ дШ ЫаШвтеЬлЬ лШ гЮдчгШлШ гЬ ймдЮггтдШ ШиоЬхШ зжм ЯШ
ЫЬхлЬ гЬ лжмк Ьеук лицзжмк:!)

  [[33mS[37m~]can . . . . . . . АдходЬмйЮ ШиоЬхрд тдШ зицк тдШ
  [[33mT[37m~]o You . . . . . . .  АдходЬмйЮ ШиоЬхрд зижк Ьйск
  [[33mF[37m~]rom You  . . . . . .  АдходЬмйЮ ШиоЬхрд Шзц Ьйск
  [[33mL[37m~]ist . . . . . . . .  СмдЬоцгЬдЮ ЬзхЫЬаеЮ ШиоЬхрд
  [[33mK[37m~]ey . . . . АдходЬмйЮ ШиоЬхрд рк зицк втеЮ бвЬаЫх

  [[33mQ[37m~]uick . . . . . . . . . ЛЬджч ЪиуЪжиЮк ШдходЬмйЮк

!WГщйлЬ лЮд ЬзавжЪу йШк ([33m?[37m ЪаШ ЩжуЯЬаШ) } T Download Club files, method menu


DMNUD {[Enter=[33m%c[37m]:[0m!) } T Download Club files, default value


DMNUR {[0;1;31m
!JАмлу Ю ЬзавжЪу ЫЬд ЬхдШа ЫмдШлу.!)
[0;1m} T Download Club files, invalid selection in method menu

DMNUH {[0;1m

!JЛЬ Шмлу лЮд ЬзавжЪу гзжиЬхлЬ дШ ЬеЬлсйЬлЬ гцдж лШ гЮдчгШлШ лжм
club зжм тожмд бсзжаж ймдЮггтдж ШиоЬхж. ЛзжиЬхлЬ нмйабс дШ всЩЬлЬ бШа лШ
ШиоЬхШ. Узсиожмд жа Ьеук лицзжа ЬетлШйЮк лрд гЮдмгслрд/ШиоЬхрд:!)

!W[[33mS[37m]can:     !12iЛзжиЬхлЬ Шзвщк дШ лШ ЫаШлитеЬлЬ,
лж жзжхж йЮгШхдЬа цла еЬбадслЬ Шзц лж зищлж гудмгШ
(у жзжажЫузжлЬ ЯЬвуйЬлЬ) бШа ШиохЭЬлЬ дШ ЫаШЩсЭЬлЬ.
ЛзжиЬхлЬ дШ "ШбжвжмЯЬхлЬ" ЫаШвцЪжмк блв.!)
!0l
!W[[33mT[37m]o you:   !12iОзрк бШа Ю зШиШзсдр гтЯжЫжк ШдсЪдрйЮк,
Шввс ЬгнШдхЭждлШа гцдж лШ гЮдчгШлШ зжм зижжихЭждлШа зижк Ьйск.!)
!0l 
!W[[33mF[37m]rom you: !12iТж хЫаж, Шввс ЬгнШдхЭждлШа гцдж лШ
гЮдчгШлШ зжм тоЬлЬ ЪиспЬа ЬйЬхк.!)
!0l 
!W[[33mL[37m]ist:     !12iЛзжиЬхлЬ дШ зсиЬлЬ тдШ бШлсвжЪж
гЮдмгслрд Ьдцк Club йЬ гаШ Шзц лак ШбцвжмЯЬк гжинтк: ПЬиаЪиШну, Тхлвжк,
ПвуиЬк бЬхгЬдж. ЙсЯЬ зЬиаЪиШну ШбжвжмЯЬхлШа Шзц лжд ШиаЯгц лжм
гЮдчгШлжк тлйа щйлЬ дШ гзжиЬхлЬ ШиЪцлЬиШ дШ ШиохйЬлЬ Шз'Шмлц.!)
!0l
!W[[33mK[37m]ey:      !12iMзжиЬхлЬ дШ ЫщйЬлЬ гаШ у зЬиаййцлЬиЬк
"втеЬак бвЬаЫаШ". Ж ШдходЬмйЮ зжм ЯШ ЪхдЬа йчгнрдШ гЬ Шмлтк лак втеЬак
бвЬаЫас ЯШ тоЬа щк ШзжлтвЬйгШ дШ ЬгнШдайлжчд ЛОМО лШ гЮдчгШлШ
лрд жзжхрд Ю зЬиаЪиШну ЬгзЬиатоЬа лЮд у лак втеЬак бвЬаЫас.!)
!0l
!W[[33mQ[37m]uick:    !12iЛзжиЬхлЬ дШ бсдЬлЬ жлаЫузжлЬ Шзц лШ зШиШзсдр
йЬ гаШ жгсЫШ Clubs зжм йШк ЬдЫаШнтиЬа, бШлЬмЯЬхШд, Шзж лж лЬвЬмлШхж
гудмгШ зжм тоЬлЬ ЫаШЩсйЬа.!)
!0l
[0;1m
} T Download Club files, help on method menu


FSCCAN {[0;1;31m
!JАбчирйЮ ЫаШЫабШйхШк.!)
[0;1m} T File scan aborted


RQMNU {[0;1m
ЛтЯжЫжа ЪиуЪжиЮк ШдходЬмйЮк:

  [[33mS[37m]can . . . . . . . АдходЬмйЮ гЮдмгслрд у/бШа ШиоЬхрд тдШ зицк тдШ
  [[33mT[37m]o You . . . . . . .  АдходЬмйЮ гЮдмгслрд у/бШа ШиоЬхрд зижк Ьйск
  [[33mF[37m]rom You  . . . . . .  АдходЬмйЮ гЮдмгслрд у/бШа ШиоЬхрд Шзц Ьйск
  [[33mL[37m]ist  . . . . . . . . . . . . .  ЙШлсвжЪжк бЬагтдрд у/бШа ШиоЬхрд
  [[33mK[37m]ey  . . . . . . . . АдходЬмйЮ лрд гЮдмгслрд гтйр втеЬрк бвЬаЫажч

  [[33mC[37m]onfigure . . . . . . . . . . . .  ГаШгцинрйЮ ЪиуЪжиЮк ШдходЬмйЮк

!WГаШвтелЬ гтЯжЫж ШдходЬмйЮк ([33m?[37m ЪаШ ЩжуЯЬаШ } T Read club messages, Quick method menu


RQMNUH {[0;1m

!JЖ ЬзавжЪу ([[33mQ[37m]uick=ЪиуЪжиЮ ШдходЬмйЮ) ЬхдШа лж зижйрзабц йШк ЬиЪШвЬхж
гЬ лж жзжхж гзжиЬхлЬ дШ ЫаШлитеЬлЬ лШ дтШ гЮдчгШлШ лжм бсЯЬ ЬзавЬЪгтджм
Club, Шзц лж йЮгЬхж зжм ЬхоШлЬ гЬхдЬа лЮд лЬвЬмлШхШ нжис.!)

!W[[33mS[37m]can:      !13iЛзжиЬхлЬ Шзвщк дШ ЫаШлитеЬлЬ лШ ЬзавЬЪгтдШ йШк Club, еЬбадщдлШк
Шзц ЬбЬх зжм ЬхоШлЬ гЬхдЬа, ЫаШЩсЭждлШк гЮдчгШлШ, "ШбжвжмЯщдлШк" ЫаШвцЪжмк блв.!)
!0l
!W[[33mT[37m]o you:    !13iОзрк бШа Ю зШиШзсдр гтЯжЫжк ШдсЪдрйЮк,
Шввс ЬгнШдхЭждлШа гцдж лШ гЮдчгШлШ зжм зижжихЭждлШа зижк Ьйск.!)
!0l 
!W[[33mF[37m]rom you:  !13iТж хЫаж, Шввс ЬгнШдхЭждлШа гцдж лШ
гЮдчгШлШ зжм тоЬлЬ ЪиспЬа ЬйЬхк.!)
!0l 
!W[[33mL[37m]ist:      !13iЛзжиЬхлЬ дШ ЬгнШдхйЬлЬ лШ дтШ гЮдчгШлШ йлШ ЬзавЬЪгтдШ Clubs гЬ
бсзжаШ Шзц лак лиЬхк гЬЯцЫжмк: ПЬиаЪиШну, Тхлвжк, ПвуиЬк бЬхгЬдж.!)
!0l
!W[[33mK[37m]ey:       !13iЛзжиЬхлЬ дШ псеЬлЬ лШ дтШ гЮдчгШлШ лрд ЬзавЬЪгтдрд Clubs ЪаШ
гхШ у зЬиаййцлЬиЬк втеЬак бвЬаЫас зжм ЯШ жихйЬлЬ.!)
!0l
!W[[33mC[37m]onfigure: !13iГаШгцинрйЮ ЪиуЪжиЮк ШдходЬмйЮк. ДЫщ жихЭЬлЬ лШ Clubs зжм ЯШ
зЬиавШгЩсдждлШа йлЮд ЪиуЪжиЮ ШдходЬмйЮ.!)
!0l
[0;1m} T Read club messages, Quick method help


RQCFH {[0;1m

!JЛаШ бШа Шмлу ЬхдШа Шмлу Ю зищлЮ нжис зжм оиЮйагжзжаЬхлЬ лЮд
ЪиуЪжиЮ ШдходЬмйЮ йШк гЬлШнтижмгЬ бШлЬмЯЬхШд йлж ЬиЪШвЬхж ЫаШгцинрйЮк
лЮк ШдходЬмйЮк. ГаШгжинщдждлШк лЮд ЪиуЪжиЮ ШдходЬмйЮ жихЭЬлЬ зжаШ Clubs
ЯШ ЫаШЩсЭЬлЬ/ШдаодЬчЬлЬ ШиЪцлЬиШ.!)

!JТж йчйлЮгШ "ЯмгслШа" лж лЬвЬмлШхж гудмгШ зжм тоЬлЬ ЫаШЩсйЬа йЬ бсЯЬ Club,
тлйа щйлЬ бсЯЬ ШдходЬмйЮ дШ ЪхдЬлШа гцдж йлШ гЮдчгШлШ зжм тожмд йлШвЬх
гЬлс лЮд лЬвЬмлШхШ йШк ШдсЪдрйЮ.!)

!JАиоабс цвШ лШ Clubs зЬиавШгЩсдждлШа йлЮ ЪиуЪжиЮ ШдходЬмйЮ (бШа йлШ QWK
зШбтлШ зжм гзжиЬхлЬ дШ всЩЬлЬ гтйр лжм Off-Line Mailer), Шввс гзжиЬхлЬ дШ
ШнШаитйЬлЬ тдШ ЫхдждлШк "[33m-/ОджгШClub[37m", у дШ зижйЯтйЬлЬ тдШ
ЫхдждлШк "[33m+/ОджгШClub[37m". ВаШ дШ ЫЬхлЬ тдШ бШлсвжЪж цврд лрд Clubs
гзжиЬхлЬ дШ ЫщйЬлЬ "[33m+?[37m". ВаШ дШ ймгзЬиавсЩЬлЬ цвШ лШ Clubs ЫщйлЬ
"[33m+ALL[37m" бШа ЪаШ дШ лШ ЫаШЪиспЬлЬ цвШ, "[33m-ALL[37m".
ВаШ дШ ЯЬриЮЯжчд цвШ лШ гЮдчгШлШ Ьдцк Club уЫЮ ЫаШЩШйгтдШ ЫщйлЬ
"[33m+/OджгШClub[37m" Ычж нжитк. ГЮвШЫу, Шд ЫщйЬлЬ "[33m+ALL +ALL[37m",
лж йчйлЮгШ ЯШ ЯЬриуйЬа цвШ лШ гЮдчгШлШ цврд лрд Clubs уЫЮ ЫаШЩШйгтдШ.
Длйа, лЮд ЬзцгЬдЮ нжис зжм ЯШ ймдЫЬЯЬхлЬ ЯШ гзжитйЬлЬ гЬ лЮд Ьдлжву [33mCRQS[37m дШ ЫаШЩсйЬлЬ
цвШ лШ дтШ гЮдчгШлШ.!)
} T Read Club messages, Quick Configure help


RQCLH {[0;1;32m
Ж ЪиуЪжиЮ ШдходЬмйу йШк ЪхдЬлШа йлс Ьеук Club(s):

[0m} T Read Club messages, Quick Configure, club list header


RQLCE {[0;1;31m
!JЙШдтдШ club ЫЬд зЬиавШгЩсдЬлШа йлЮд ЪиуЪжиу йШк ШдходЬмйЮ.!)
[0m} T Read Club messages, Quick Configure, no clubs



RQCLF {[0;1m
} T Read Club messages, Quick Configure, club list footer


RQCMNU {[0;1m
   [33m+[37m  . . . . . . . . . . . .  ПижйЯтйлЬ тдШ Club
   [33m-[37m . . . . . . . . . . . . . АнШаитйлЬ тдШ Club
   [33mV[37miew . . ДгнсдайЮ лрд Club зжм ЯШ ШдаодЬчждлШа

!WДсд тоЬлЬ ЫщйЬа уЫЮ лЮд Ьдлжву [33m+ALL +ALL[37m ЫщйлЬ e[33mX[37mit.!)

!WГщйлЬ лЮд ЬзавжЪу йШк ([33mV[37m,[33m+[37m,[33m-[37m,[33m?[37m ЪаШ ЩжуЯЬаШ, у [33mX[37m ЪаШ лтвжк:!)[0m } T Read Club messages, Quick Configure, menu


RQCHELP {[0;1m

!JГаШгжинщдждлШк лЮ ЪиуЪжиЮ ШдходЬмйЮ жихЭЬлЬ зжард Clubs лШ гЮдчгШлШ
ЯШ ЫаШЩсЭЬлЬ/ШдаодЬчЬлЬ ШиЪцлЬиШ гЬ лЮд Ьдлжву [33mCRQS[37m.!)

!JТж йчйлЮгШ "ЯмгслШа" лж лЬвЬмлШхж гудмгШ зжм тоЬлЬ ЫаШЩсйЬа йЬ бсЯЬ Club,
тлйа щйлЬ бсЯЬ ШдходЬмйЮ дШ ЪхдЬлШа гцдж йлШ гЮдчгШлШ зжм тожмд йлШвЬх
гЬлс лЮд лЬвЬмлШхШ йШк ШдсЪдрйЮ.!)

!JАиоабс цвШ лШ Clubs зЬиавШгЩсдждлШа йлЮ ЪиуЪжиЮ ШдходЬмйЮ, Шввс гзжиЬхлЬ дШ
ШнШаитйЬлЬ тдШ ЫхдждлШк "[33m-/ОджгШClub[37m", у дШ зижйЯтйЬлЬ тдШ
ЫхдждлШк "[33m+/ОджгШClub[37m". ВаШ дШ ЫЬхлЬ тдШ бШлсвжЪж цврд лрд Clubs
гзжиЬхлЬ дШ ЫщйЬлЬ "[33m+?[37m". ВаШ дШ ймгзЬиавсЩЬлЬ цвШ лШ Clubs ЫщйлЬ
"[33m+ALL[37m" бШа ЪаШ дШ лШ ЫаШЪиспЬлЬ цвШ, "[33m-ALL[37m".
ВаШ дШ ЯЬриЮЯжчд цвШ лШ гЮдчгШлШ Ьдцк Club уЫЮ ЫаШЩШйгтдШ ЫщйлЬ
"[33m+/OджгШClub[37m" Ычж нжитк. ГЮвШЫу, Шд ЫщйЬлЬ "[33m+ALL +ALL[37m",
лж йчйлЮгШ ЯШ ЯЬриуйЬа цвШ лШ гЮдчгШлШ цврд лрд Clubs уЫЮ ЫаШЩШйгтдШ.
Длйа, лЮд ЬзцгЬдЮ нжис зжм ЯШ ймдЫЬЯЬхлЬ ЯШ гзжитйЬлЬ гЬ лЮд Ьдлжву [33mCRQS[37m дШ ЫаШЩсйЬлЬ
цвШ лШ дтШ гЮдчгШлШ.!)
[0;1m
} T Read Club messages, Quick Configure help #2


RQCADD {[0;1m
!WГщйлЬ Club зжм ЯШ ймгзЬиавсЩЬлЬ йлЮд ЪиуЪжиЮ ШдходЬмйЮ ([33m?[37m ЪаШ бШлсвжЪж):!)[0m } T Read Club messages, Quick Configure, add club


RQCCR {[0;1;31m
!JГЬд мзсиоЬа Шмлц лж Club.!)
} T Read Club messages, Quick Configure, add, unknown club


RQCDEL {[0;1m
!WГщйлЬ Club зжм ЯШ ЫаШЪиспЬлЬ Шзц лЮд ЪиуЪжиЮ ШдходЬмйЮ ([33m?[37m ЪаШ бШлсвжЪж):!)[0m } T Read Club messages, Quick Configure, delete club


RQCDR {[0;1;31m
!JГЬд мзсиоЬа лтлжаж Club йлжд бШлсвжЪж лрд ШдаодЬмжгтдрд Club.
ГщйлЬ [33mX[31m (eXit) жзжаШЫузжлЬ йлаЪгу ЪаШ дШ ЬзайлитпЬлЬ йлж
бЬдлиабц гЬджч лрд Club.!)
} T Read Club messages, Quick Configure, delete, unknown club


RLMNU {[0;1m
Оа гтЯжЫжа ймдЬоцгЬдЮк ЬзхЫЬаеЮк ЬхдШа:

  [[33mB[37m]rief . . . . ПЬиаЪиШну, гаШ ЪиШггу ЪаШ бсЯЬ гудмгШ у ШиоЬхж
  [[33mT[37m]itle  . . . .  Тхлвжк, ЬзабЬнШвхЫШ гЮдчгШлжк, 5 у 6 ЪиШггтк
  [[33mF[37m]ull  . . . . . . . . . . . . ДзабЬнШвхЫШ бШа звуиЬк бЬхгЬдж

!WГаШвтелЬ гхШ Шзц лак зШиШзсдр гЬЯцЫжмк ([33m?[0;1m ЪаШ ЩжуЯЬаШ)!)[0m } T List Club messages, method menu


RLMNUR {[0;1;31m
!WАмлу Ю ЬзавжЪу ЫЬд ЬхдШа ЫмдШлу. ГщйлЬ [33m?[31m ЪаШ ЩжуЯЬаШ.!)
[0;1m} T List Club messages, invalid selection


RLMNUH {[0;1m

!JЖ ЬзавжЪу [33mL[37mist Шзвщк ЬгнШдхЭЬа звЮижнжихЬк ЪаШ бсЯЬ гудмгШ йлЮд жЯцдЮ
йШк. Оа ЬзцгЬдЬк гтЯжЫжа ЬгнсдайЮк зижйнтиждлШа:!)

!W[[33mB[37m]rief: !9iАмлу Ю гтЯжЫжк ЬгнШдхЭЬа гцдж лжд ШиаЯгц лжм гЮдчгШлжк,
зцлЬ ЪиснлЮбЬ, лжд ШзжйлжвтШ бШа цйж Шзц лж ЯтгШ лжм гЮдчгШлжк орисЬа
йлж звслжк лЮк жЯцдЮк йШк.!)
!0l
!W[[33mT[37m]itle: !9iАмлу Ю гтЯжЫжк ЬгнШдхЭЬа лЮд звуиЮ ЬзабЬнШвхЫШ (header)
бсЯЬ гЮдчгШлжк. Ж ЬзабЬнШвхЫШ зЬиавШгЩсдЬа лжд ШиаЯгц лжм гЮдчгШлжк,
зцлЬ ЪиснлЮбЬ, ШзжйлжвтШ бШа зШиШвузлЮ, Ьсд мзсиоЬа
ймдЮггтдж ШиоЬхж, зжаж лж цджгс лжм бШа зцйЬк нжитк тоЬа вЮЯЬх,
зцйЬк нжитк тоЬа ЫаШЩШйлЬх лж гудмгШ бШа зцйЬк ШзШдлуйЬак тоЬа, бШа лж звуиЬк ЯтгШ.!)
!0l
!W[[33mF[37m]ull:  !9iАмлу Ю гтЯжЫжк ЬгнШдхЭЬа лЮд ЬзабЬнШвхЫШ (цзрк Ю гтЯжЫжк [33mT[37mitle)
бШа жвцбвЮиж лж гудмгШ, Шввс цоа бШа лШ заЯШдцд ймдЮггтдШ ШиоЬхШ.!)
!0l
[0;1m
} T List Club messages, method menu help


RLASK {[0;1m
!JГщйлЬ лжд ШиаЯгц гЮдчгШлжк Шзц цзжм ЯШ ШиохйЬлЬ лЮд ЬзхЫЬаеЮ, [[33mF[37m]irst
(Пищлж) ЪаШ лж зищлж мзсиожд гудмгШ, [[33mL[37m]ast (ТЬвЬмлШхж)
ЪаШ лж лЬвЬмлШхж гудмгШ, [33mEnter[37m ЪаШ лж литожд гудмгШ
([32m#%ld[37m), у [33m?[0;1m ЪаШ ЩжуЯЬаШ.!)

!WАзц зжаж гудмгШ дШ еЬбадуйЬа Ю ЬзхЫЬаеЮ; !) [0m} T List Club messages, asking for message number 


RLASKR {[0;1;31m
!WКмзсгШа, ЫЬд мзсиоЬа Шмлу Ю ЬзавжЪу.!)
[0;1m} T List Club messages, error while asking for message number


RLASKH {[0;1m
!JАд зШлуйЬлЬ Шзвщк [33mEnter[37m, ЯШ ШиохйЬлЬ Шзц лж зищлж дтж гудмгШ
лжм Club @CLUB@. Ад ЫЬд мзсиожмд дтШ гЮдчгШлШ, лцлЬ Ю ШдсЪдрйЮ ЯШ еЬбадуйЬа гЬ лж лЬвЬмлШхж
Шзц лШ зШвас. Ж лЬвЬхШ ([33m.[37m) ЬхдШа айжЫчдШгЮ гЬ лж [33mEnter[37m, 
Шд оиЮйагжзжаЬхлЬ ймдлгуйЬак. ГЮвШЫу Ю Ьдлжву [33mCRLB.[37m Шзц лж бЬдлиабц
гЬджч йЮгШхдЬа "сгЬйЮ йчдлжгЮ ЬгнсдайЮ цврд лрд дтрд гЮдмгслрд лжм литождлжк club".!)

!JГхдждлШк [33mF[37m (First), ЯШ ШиохйЬлЬ лЮд ШдсЪдрйЮ Шзц лж зШвацлЬиж
ЫаШЯтйагж гудмгШ.!)

!JГхдждлШк [33mL[37m (Last), ЯШ ШиохйЬлЬ лЮд ШдсЪдрйЮ Шзц лж заж зицйнШлж
гудмгШ зжм ЪиснлЮбЬ.!)

!JГщйлЬ [33mX[37m (eXit) Шд ЯтвЬлЬ дШ ЩЪЬхлЬ, Швващк ЫщйлЬ лжд ШиаЯгц лжм
гЮдчгШлжк Шзж лж жзжхж ЯтвЬлЬ дШ ШиохйЬлЬ. Ад ЫЬд мзсиоЬа гудмгШ гЬ Шмлцд лжд
ШиаЯгц лцлЬ ЯШ оиЮйагжзжаЮЯЬх лж зищлж гудмгШ гЬ ШиаЯгц гЬЪШвчлЬиж Шзц Шмлцд
зжм ЫщйШлЬ.!)
[0;1m} T List Club messages, help about entering message numbers


RLBNMSG {[0;1;31m
!JГЬд ЩитЯЮбШд гЮдчгШлШ.!)
[0;1m} T List Club messages, no messages found


RLMISS {[0;1m
Тж гудмгШ [32m%d[37m ЫЬд ЩитЯЮбЬ. ДзавтоЯЮбЬ лж звЮйатйлЬиж:
[0;1m} T List Club messages, message number not found


RLBHDR {[0;1;32m
ДгнсдайЮ лжм [37m@CLUB@: @CLUBDESC@[32m...
[37m
ЛудмгШ  АзжйлжвтШк  ЖгЬижгЮдхШ бШа щиШ  ЗтгШ
!F─
} T List Club messages, brief listing header


RLBTAB {[0;1;33m%6d  %-10s  %s %s  %s
} List Club messages, brief listing table


RLBFTR {[0;1m!F─
[0;1m} T List Club messages, brief listing footer


RLTHDR {[0;1;32m
ДгнсдайЮ лжм [37m@CLUB@: @CLUBDESC@[32m...
[0;1m} T List Club messages, title/full listing header


RLDONE {[0;1m
!WФлсйШлЬ йлж лтвжк лрд гЮдмгслрд.!)
[0;1m} T List Club messages, end of listing



RLABORT {[0;1m

!WГаШбцзЮбЬ Шзц лжд оиуйлЮ.!)
[0;1m} T List Club messages, listing aborted





RSASK {[0;1m
!JГщйлЬ лжд ШиаЯгц гЮдчгШлжк Шзц цзжм ЯШ ШиохйЬлЬ лЮд ШдсЪдрйЮ, [[33mF[37m]irst
(Пищлж) ЪаШ лж зищлж мзсиожд гудмгШ, [[33mL[37m]ast (ТЬвЬмлШхж)
ЪаШ лж лЬвЬмлШхж гудмгШ, [33mEnter[37m ЪаШ лж литожд гудмгШ
([32m#%ld[37m), у [33m?[0;1m ЪаШ ЩжуЯЬаШ.!)

!WАзц зжаж гудмгШ дШ еЬбадуйЬа Ю ШдсЪдрйЮ; !) [0m} T Scan Club messages, asking for message number 


RSASKR {[0;1;31m
!WКмзсгШа, ЫЬд мзсиоЬа Шмлу Ю ЬзавжЪу.!)
[0;1m} T Scan Club messages, error while asking for message number


RSASKH {[0;1m
!JАд зШлуйЬлЬ Шзвщк [33mEnter[37m, ЯШ ШиохйЬлЬ Шзц лж зищлж дтж гудмгШ
лжм Club @CLUB@. Ад ЫЬд мзсиожмд дтШ гЮдчгШлШ, лцлЬ Ю ШдсЪдрйЮ ЯШ еЬбадуйЬа гЬ лж лЬвЬмлШхж
Шзц лШ зШвас. Ж лЬвЬхШ ([33m.[37m) ЬхдШа айжЫчдШгЮ гЬ лж [33mEnter[37m, 
Шд оиЮйагжзжаЬхлЬ ймдлгуйЬак. ГЮвШЫу Ю Ьдлжву [33mCRS.[37m Шзц лж бЬдлиабц
гЬджч йЮгШхдЬа "сгЬйЮ ШдсЪдрйЮ цврд лрд дтрд гЮдмгслрд лжм литождлжк club".!)

!JГхдждлШк [33mF[37m (First), ЯШ ШиохйЬлЬ лЮд ШдсЪдрйЮ Шзц лж зШвацлЬиж
ЫаШЯтйагж гудмгШ.!)

!JГхдждлШк [33mL[37m (Last), ЯШ ШиохйЬлЬ лЮд ШдсЪдрйЮ Шзц лж заж зицйнШлж
гудмгШ зжм ЪиснлЮбЬ.!)

!JГщйлЬ [33mX[37m (eXit) Шд ЯтвЬлЬ дШ ЩЪЬхлЬ, Швващк ЫщйлЬ лжд ШиаЯгц лжм
гЮдчгШлжк Шзж лж жзжхж ЯтвЬлЬ дШ ШиохйЬлЬ. Ад ЫЬд мзсиоЬа гудмгШ гЬ Шмлцд лжд
ШиаЯгц лцлЬ ЯШ оиЮйагжзжаЮЯЬх лж зищлж гудмгШ гЬ ШиаЯгц гЬЪШвчлЬиж Шзц Шмлцд
зжм ЫщйШлЬ.!)
[0;1m} T Scan Club messages, help about entering message numbers


RSWAIT {[0;1;32m
!JДиЬмдШ гЮдмгслрд, зШиШбШвщ зЬиагтдЬлЬ...!)
[0;1m} T Scan Club messages, please wait...


RSBNMSG {[0;1;31m
!JГЬд ЩитЯЮбШд гЮдчгШлШ.!)
[0;1m} T Scan Club messages, no messages found


RSMISS {[0;1m
Тж гудмгШ [32m%d[37m ЫЬд ЩитЯЮбЬ. ДзавтоЯЮбЬ лж звЮйатйлЬиж:
[0;1m} T Scan Club messages, message number not found


RSTHDR {[0;1;32m
ДгнсдайЮ лжм [37m@CLUB@: @CLUBDESC@[32m...
[0;1m} T Scan Club messages, scanning club


RSSCNM {[0;1m
[[33mN[37m]ext . . . . . . . ДзцгЬдж гудмгШ   [[33mP[37m]revious . . . ПижЮЪжчгЬдж гудмгШ
[[33mR[37m]ead  . . . . . . . . .  АдсЪдрйЮ   [[33m#[37m] . . . . . . АвгШ йЬ сввж гудмгШ
[[33mT[37m]hread . . . . АбжвжмЯхШ ЫаШвцЪжм   [[33mQ[37m]uickscan . . . ВиуЪжиЮ ШдходЬмйЮ
e[[33mX[37m]it . . . . . . . . . . . ДежЫжк

Ж ЬзавжЪу йШк ([33m?[37m ЪаШ ЩжуЯЬаШ); } T Scan Club messages, choices while scanning messages


RSSCNMH {[0;1m

!JЛзжиЬхлЬ дШ ЫщйЬлЬ лак Ьеук Ьдлжвтк йЬ Шмлц лж йЮгЬхж:!)

!W[33mN[37mext:      !iЛЬлШнтиЬйлЬ йлж ЬзцгЬдж гудмгШ, орихк дШ ЫаШЩсйЬлЬ лж литожд.
ЛзжиЬхлЬ дШ оиЮйагжзжауйЬлЬ Шмлу лЮд Ьдлжву ЪаШ тдШ ЬхЫжк Шзвук ШдходЬмйЮк лрд гЮдмгслрд.
ГщйлЬ зжввтк нжитк лЮд Ьдлжву N рк йчдлгЮйЮ, бШа лж йчйлЮгШ ЯШ зижориуйЬа ЬгнШдхЭждлск йШк
лак ЬзабЬнШвхЫЬк (headers) лрд гЮдмгслрд зжм зЬидсЬа. Длйа, гЬ лЮд Ьдлжву [33mNNNN[37m,
Ю ЩсйЮ ЯШ йШк ЫЬхеЬа лак ЬзабЬнШвхЫЬк лрд ЬзцгЬдрд лЬййсирд гЮдмгслрд, бШа ЯШ йлШгШлуйЬа йлж лЬвЬмлШхж.!)
!0l
!W[33mP[37mrevious:  !iЛЬлШнтиЬйлЬ йлж зижЮЪжчгЬдж гудмгШ. КЬалжмиЪЬх цзрк ШбиаЩщк бШа Ю зижЮЪжчгЬдЮ Ьдлжву.!)
!0l
!W[33m#[37m:         !iТж йчйлЮгШ ЯШ йШк ЭЮлуйЬа тдШд ШиаЯгц гЮдчгШлжк йлж жзжхж ЯШ гЬлШЩЬхлЬ.
Ад лж гудмгШ ЫЬд ЩиЬЯЬх, ЯШ лжзжЯЬлЮЯЬхлЬ йлж бждладцлЬиж гудмгШ. ЛзжиЬхлЬ бШа ЬЫщ дШ оиЮйагжзжауйЬлЬ
ймдлгуйЬак: Ю Ьдлжву [33m#1000[37m ЯШ йШк зсЬа бШлЬмЯЬхШд йлж гудмгШ 1000.!)
!0l
!W[33mT[37mhread:    !iАбжвжмЯхШ ЫаШвцЪжм. Амлу Ю Ьдлжву йШк ЬгнШдхЭЬа
тдШ ШбцгШ гЬджч, гЬ лЮд ЩжуЯЬаШ лжм жзжхжм гзжиЬхлЬ дШ бадЮЯЬхлЬ йлж
зижЮЪжчгЬдж у ЬзцгЬдж гудмгШ лЮк ймЭулЮйЮк. ЛзжиЬхлЬ ЬзхйЮк дШ зслЬ йлж
гудмгШ зижк лж жзжхж ШзШдлс лж литожд гудмгШ.!)
!0l
!W[33mQ[37muickscan: !iДЫщ ЯШ ЩиЬхлЬ бсзжаЬк ЬаЫабтк Ьдлжвтк ЪаШ лЮд ЪиуЪжиЮ
ШдходЬмйЮ. ЛзжиЬхлЬ дШ бадЮЯЬхлЬ йлж ЬзцгЬдж у зижЮЪжчгЬдж club, дШ ШнШаитйЬлЬ лж
литожд club Шзц лЮд вхйлШ ЪиуЪжиЮк ШдходЬмйЮк, бШа сввШ.!)
!0l
!W[33mR[37mead:      !iАдсЪдрйЮ лжм литождлжк гЮдчгШлжк. ЛЬлс лЮд ШдсЪдрйЮ тоЬлЬ Ьзазвтжд
ЫмдШлцлЮлЬк оЬаиайгжч лжм гЮдчгШлжк.!)
!0l
[0;1m} T Scan Club messages, help about scanning commands


RSSCNMD {[0;1m
[[33mN[37m]ext . . . . . . . ДзцгЬдж гудмгШ   [[33mP[37m]revious . . . ПижЮЪжчгЬдж гудмгШ
[[33mR[37m]ead  . . . . . . . . .  АдсЪдрйЮ   [[33m#[37m] . . . . . . АвгШ йЬ сввж гудмгШ
[[33mT[37m]hread . . . . АбжвжмЯхШ ЫаШвцЪжм   [[33mD[37m]ownload . . . . КупЮ лжм ШиоЬхжм
[[33mQ[37m]uickscan . . . ВиуЪжиЮ ШдходЬмйЮ   e[[33mX[37m]it . . . . . . . . . . . ДежЫжк

Ж ЬзавжЪу йШк ([33m?[37m ЪаШ ЩжуЯЬаШ); } T Scan Club messages, scan choices with download


RSSCNMHD {[0;1m

!JЛзжиЬхлЬ дШ ЫщйЬлЬ лак Ьеук Ьдлжвтк йЬ Шмлц лж йЮгЬхж:!)

!W[33mN[37mext:     !iЛЬлШнтиЬйлЬ йлж ЬзцгЬдж гудмгШ, орихк дШ ЫаШЩсйЬлЬ лж литожд.
ЛзжиЬхлЬ дШ оиЮйагжзжауйЬлЬ Шмлу лЮд Ьдлжву ЪаШ тдШ ЬхЫжк Шзвук ШдходЬмйЮк лрд гЮдмгслрд.
ГщйлЬ зжввтк нжитк лЮд Ьдлжву N рк йчдлгЮйЮ, бШа лж йчйлЮгШ ЯШ зижориуйЬа ЬгнШдхЭждлск йШк
лак ЬзабЬнШвхЫЬк (headers) лрд гЮдмгслрд зжм зЬидсЬа. Длйа, гЬ лЮд Ьдлжву [33mNNNN[37m,
Ю ЩсйЮ ЯШ йШк ЫЬхеЬа лак ЬзабЬнШвхЫЬк лрд ЬзцгЬдрд лЬййсирд гЮдмгслрд, бШа ЯШ йлШгШлуйЬа йлж лЬвЬмлШхж.!)
!0l
!W[33mP[37mrevious:  !iЛЬлШнтиЬйлЬ йлж зижЮЪжчгЬдж гудмгШ. КЬалжмиЪЬх цзрк ШбиаЩщк бШа Ю зижЮЪжчгЬдЮ Ьдлжву.!)
!0l
!W[33m#[37m:         !iТж йчйлЮгШ ЯШ йШк ЭЮлуйЬа тдШд ШиаЯгц гЮдчгШлжк йлж жзжхж ЯШ гЬлШЩЬхлЬ.
Ад лж гудмгШ ЫЬд ЩиЬЯЬх, ЯШ лжзжЯЬлЮЯЬхлЬ йлж бждладцлЬиж гудмгШ. ЛзжиЬхлЬ бШа ЬЫщ дШ оиЮйагжзжауйЬлЬ
ймдлгуйЬак: Ю Ьдлжву [33m#1000[37m ЯШ йШк зсЬа бШлЬмЯЬхШд йлж гудмгШ 1000.!)
!0l
!W[33mT[37mhread:    !iАбжвжмЯхШ ЫаШвцЪжм. Амлу Ю Ьдлжву йШк ЬгнШдхЭЬа
тдШ ШбцгШ гЬджч, гЬ лЮд ЩжуЯЬаШ лжм жзжхжм гзжиЬхлЬ дШ бадЮЯЬхлЬ йлж
зижЮЪжчгЬдж у ЬзцгЬдж гудмгШ лЮк ймЭулЮйЮк. ЛзжиЬхлЬ ЬзхйЮк дШ зслЬ йлж
гудмгШ зижк лж жзжхж ШзШдлс лж литожд гудмгШ.!)
!0l
!W[33mQ[37muickscan: !iДЫщ ЯШ ЩиЬхлЬ бсзжаЬк ЬаЫабтк Ьдлжвтк ЪаШ лЮд ЪиуЪжиЮ
ШдходЬмйЮ. ЛзжиЬхлЬ дШ бадЮЯЬхлЬ йлж ЬзцгЬдж у зижЮЪжчгЬдж club, дШ ШнШаитйЬлЬ лж
литожд club Шзц лЮд вхйлШ ЪиуЪжиЮк ШдходЬмйЮк, бШа сввШ.!)
!0l
!W[33mR[37mead:      !iАдсЪдрйЮ лжм литождлжк гЮдчгШлжк. ЛЬлс лЮд ШдсЪдрйЮ тоЬлЬ Ьзазвтжд
ЫмдШлцлЮлЬк оЬаиайгжч лжм гЮдчгШлжк.!)
!0l
!W[33mD[37mownload:  !iТж гудмгШ тоЬа тдШ ймдЮггтдж ШиоЬхж. ЛЬ Шмлу лЮд Ьдлжву гзжиЬхлЬ дШ всЩЬлЬ
Шмлц лж ШиоЬхж орихк дШ ЫаШЩсйЬлЬ лж йщгШ лжм гЮдчгШлжк (зЬиаЪиШну лжм ШиоЬхжм).!)
!0l
[0;1m} T Scan Club messages, help for RSSCNMD


RSSCNR {[0;1;31m
КмзсгШа, Шмлу Ю ЬзавжЪу ЫЬд ЬхдШа ЫмдШлу.
[0;1m} T Scan Club messages, invalid selection from scan menu


RSDEF {[Enter=[33m%c[37m]: [0m} T Scan Club messages, default value for menus

RSGONUM {[0;1m
!JЛзжиЬхлЬ дШ гЬлШбадЮЯЬхлЬ йЬ бсзжаж ймЪбЬбиагтдж гудмгШ ЫхдждлШк ЬЫщ
лжд ШиаЯгц лжм. О ШиаЯгцк ЫЬд ЬхдШа ШдсЪбЮ дШ ШдубЬа йЬ мзсиожд гудмгШ:
Шд лж ймЪбЬбиагтдж гудмгШ ЫЬд ЩиЬЯЬх, ЯШ ЩиЬЯЬхлЬ йлж бждладцлЬиж гудмгШ.
ВаШ заж ЪиуЪжиШ, гзжиЬхлЬ дШ оиЮйагжзжауйЬлЬ лЮд йчдлгЮйЮ лЮк гжинук
[33m#123[37m Шзц лж зижЮЪжчгЬдж гЬджч, зжм ЯШ йШк зижрЯуйЬа бШлЬмЯЬхШд
йлж гудмгШ 123.!)

ГщйлЬ лжд ШиаЯгц гЮдчгШлжк зжм ЯШ зижрЯЮЯЬхлЬ у [33mX[0;1m ЪаШ ШбчирйЮ: } T Scan Club messages, goto what message?


RSBEG {[0;1;33m
ФлсйШлЬ йлЮд Шиоу лрд гЮдмгслрд.
[0;1m} T Scan Club messages, reached beginning of messages


RSEND {[0;1;33m
ФлсйШлЬ йлж лтвжк лрд гЮдмгслрд.
[0;1m} T Scan Club messages, reached beginning of messages


RSDEL {[0;1;31m
!JЕЮлжчгЬ ймЪЪдщгЮ, Шввс лж гудмгШ Шмлц гцвак ЫаЬЪиснЮ.!)
[0;1m} T Scan Club messages, message has just been deleted, can't read


RSIOERR {[0;1;31m
!JУзуиеЬ йнсвгШ ЬЪЪиШнук/ШдсЪдрйЮк бШлс лЮд ШдсЪдрйЮ лжм гЮдчгШлжк.
ПШиШбШвжчгЬ ЬаЫжзжауйлЬ лжд ХЬаиайлу СмйлугШлжк ЪаШ лак ймдЯубЬк
зжм жЫуЪЮйШд йЬ Шмлц лж всЯжк.!)
[0;1m} T Scan Club messages, I/O error while reading message


RSRMNU1 {[0;1m
[[33mN[37m]ext . . . . . . . ДзцгЬдж гудмгШ   [[33mP[37m]revious  . .  ПижЮЪжчгЬдж гудмгШ
[[33mE[37m]mail reply .  Пижйрзабу ШзсдлЮйЮ   [[33mR[37m]eply  . . . . . . . . . АзсдлЮйЮ
[[33mT[37m]hread . . . . АбжвжмЯхШ ЫаШвцЪжм   e[[33mX[37m]it  . . . . . . . . . .  ДежЫжк

Ж ЬзавжЪу йШк ([33m?[37m ЪаШ ЩжуЯЬаШ); } T Scan Club messages, choices after reading message


RSRMNU1H {[0;1m

!JЛзжиЬхлЬ дШ ЫщйЬлЬ лак Ьеук Ьдлжвтк йЬ Шмлц лж йЮгЬхж:!)

!W[33mN[37mext:     !iЛЬлШнтиЬйлЬ йлж ЬзцгЬдж гудмгШ.
ЛзжиЬхлЬ дШ оиЮйагжзжауйЬлЬ Шмлу лЮд Ьдлжву ЪаШ тдШ ЬхЫжк Шзвук ШдходЬмйЮк лрд гЮдмгслрд.
ГщйлЬ зжввтк нжитк лЮд Ьдлжву N рк йчдлгЮйЮ, бШа лж йчйлЮгШ ЯШ зижориуйЬа ЬгнШдхЭждлск йШк
лак ЬзабЬнШвхЫЬк (headers) лрд гЮдмгслрд зжм зЬидсЬа. Длйа, гЬ лЮд Ьдлжву [33mNNNN[37m,
Ю ЩсйЮ ЯШ йШк ЫЬхеЬа лак ЬзабЬнШвхЫЬк лрд ЬзцгЬдрд лЬййсирд гЮдмгслрд, бШа ЯШ йлШгШлуйЬа йлж лЬвЬмлШхж.!)
!0l
!W[33mP[37mrevious: !iЛЬлШнтиЬйлЬ йлж зижЮЪжчгЬдж гудмгШ. КЬалжмиЪЬх цзрк ШбиаЩщк бШа Ю зижЮЪжчгЬдЮ Ьдлжву.!)
!0l
!W[33m#[37m:        !iТж йчйлЮгШ ЯШ йШк ЭЮлуйЬа тдШд ШиаЯгц гЮдчгШлжк йлж жзжхж ЯШ гЬлШЩЬхлЬ.
Ад лж гудмгШ ЫЬд ЩиЬЯЬх, ЯШ лжзжЯЬлЮЯЬхлЬ йлж бждладцлЬиж гудмгШ. ЛзжиЬхлЬ бШа ЬЫщ дШ оиЮйагжзжауйЬлЬ
ймдлгуйЬак: Ю Ьдлжву [33m#1000[37m ЯШ йШк зсЬа бШлЬмЯЬхШд йлж гудмгШ 1000.!)
!0l
!W[33mT[37mhread:   !iАбжвжмЯхШ ЫаШвцЪжм. Амлу Ю Ьдлжву йШк ЬгнШдхЭЬа
тдШ ШбцгШ гЬджч, гЬ лЮд ЩжуЯЬаШ лжм жзжхжм гзжиЬхлЬ дШ бадЮЯЬхлЬ йлж
зижЮЪжчгЬдж у ЬзцгЬдж гудмгШ лЮк ймЭулЮйЮк. ЛзжиЬхлЬ ЬзхйЮк дШ зслЬ йлж
гудмгШ зижк лж жзжхж ШзШдлс лж литожд гудмгШ.!)
!0l
!W[33mE[37mmail:    !iСоЮгШлхЭЬлЬ ШзсдлЮйЮ зижк Шмлц лж гудмгШ. Ж ШзсдлЮйЮ ЯШ йлШвЬх рк
зижйрзабц гудмгШ йлж ШзжйлжвтШ лжм гЮдчгШлжк.!)
!W[33mR[37meply:    !iГЮгажмиЪЬхлШа ЫЮгцйаж гудмгШ-ШзсдлЮйЮ зижк лж литожд гудмгШ.!)
!0l
[0;1m} T Scan Club messages, help about reading messages, version 1


RSRMNU2 {[0;1m
[[33mN[37m]ext . . . . . . . ДзцгЬдж гудмгШ   [[33mP[37m]revious . . . ПижЮЪжчгЬдж гудмгШ
[[33mC[37m]lear . . . .  ГаШЪиШну гЮдчгШлжк   [[33mM[37m]odify  . . . .  АввШЪу гЮдчгШлжк
[[33mE[37m]mail reply  . Пижйрзабу ШзсдлЮйЮ   [[33mR[37m]eply  . . . . . . . . . АзсдлЮйЮ
[[33mT[37m]hread  . . .  АбжвжмЯхШ ЫаШвцЪжм   e[[33mX[37m]it  . . . . . . . . . .  ДежЫжк

Ж ЬзавжЪу йШк ([33m?[37m ЪаШ ЩжуЯЬаШ); } T Scan Club messages, choices after reading message


RSRMNU2H {[0;1m

!JЛзжиЬхлЬ дШ ЫщйЬлЬ лак Ьеук Ьдлжвтк йЬ Шмлц лж йЮгЬхж:!)

!W[33mN[37mext:     !iЛЬлШнтиЬйлЬ йлж ЬзцгЬдж гудмгШ.
ЛзжиЬхлЬ дШ оиЮйагжзжауйЬлЬ Шмлу лЮд Ьдлжву ЪаШ тдШ ЬхЫжк Шзвук ШдходЬмйЮк лрд гЮдмгслрд.
ГщйлЬ зжввтк нжитк лЮд Ьдлжву N рк йчдлгЮйЮ, бШа лж йчйлЮгШ ЯШ зижориуйЬа ЬгнШдхЭждлск йШк
лак ЬзабЬнШвхЫЬк (headers) лрд гЮдмгслрд зжм зЬидсЬа. Длйа, гЬ лЮд Ьдлжву [33mNNNN[37m,
Ю ЩсйЮ ЯШ йШк ЫЬхеЬа лак ЬзабЬнШвхЫЬк лрд ЬзцгЬдрд лЬййсирд гЮдмгслрд, бШа ЯШ йлШгШлуйЬа йлж лЬвЬмлШхж.!)
!0l
!W[33mP[37mrevious: !iЛЬлШнтиЬйлЬ йлж зижЮЪжчгЬдж гудмгШ. КЬалжмиЪЬх цзрк ШбиаЩщк бШа Ю зижЮЪжчгЬдЮ Ьдлжву.!)
!0l
!W[33m#[37m:        !iТж йчйлЮгШ ЯШ йШк ЭЮлуйЬа тдШд ШиаЯгц гЮдчгШлжк йлж жзжхж ЯШ гЬлШЩЬхлЬ.
Ад лж гудмгШ ЫЬд ЩиЬЯЬх, ЯШ лжзжЯЬлЮЯЬхлЬ йлж бждладцлЬиж гудмгШ. ЛзжиЬхлЬ бШа ЬЫщ дШ оиЮйагжзжауйЬлЬ
ймдлгуйЬак: Ю Ьдлжву [33m#1000[37m ЯШ йШк зсЬа бШлЬмЯЬхШд йлж гудмгШ 1000.!)
!0l
!W[33mM[37modify:   !iТж гудмгШ тоЬа йлШвЬх Шзц Ьйск. ДоЬлЬ лж ЫабШхргШ дШ ШввсеЬлЬ лШ зЬиаЬоцгЬдс лжм.
Амлу Ю Ьдлжву йШк ЬзалитзЬа дШ бсдЬлЬ ШбиаЩщк Шмлц.!)
!0l
!W[33mC[37mlear:    !iТж гудмгШ тоЬа йлШвЬх Шзц Ьйск. ЛЬ Шмлу лЮд Ьдлжву лж ЫаШЪиснЬлЬ Шзц лж club @CLUB@.
ГЬд ЯШ мзсиеЬа бШггхШ ЬищлЮйЮ ЬзаЩЬЩШхрйЮк.!)
!0l
!W[33mT[37mhread:   !iАбжвжмЯхШ ЫаШвцЪжм. Амлу Ю Ьдлжву йШк ЬгнШдхЭЬа
тдШ ШбцгШ гЬджч, гЬ лЮд ЩжуЯЬаШ лжм жзжхжм гзжиЬхлЬ дШ бадЮЯЬхлЬ йлж
зижЮЪжчгЬдж у ЬзцгЬдж гудмгШ лЮк ймЭулЮйЮк. ЛзжиЬхлЬ ЬзхйЮк дШ зслЬ йлж
гудмгШ зижк лж жзжхж ШзШдлс лж литожд гудмгШ.!)
!0l
!W[33mE[37mmail:    !iСоЮгШлхЭЬлЬ ШзсдлЮйЮ зижк Шмлц лж гудмгШ. Ж ШзсдлЮйЮ ЯШ йлШвЬх рк
зижйрзабц гудмгШ йлж ШзжйлжвтШ лжм гЮдчгШлжк.!)
!0l
!W[33mR[37meply:    !iГЮгажмиЪЬхлШа ЫЮгцйаж гудмгШ-ШзсдлЮйЮ зижк лж литожд гудмгШ.!)
!0l
[0;1m} T Scan Club messages, help about reading messages, version 2


RSRMNU3 {[0;1m
[[33mN[37m]ext  . . . . . .  ДзцгЬдж гудмгШ   [[33mP[37m]revious . . . ПижЮЪжчгЬдж гудмгШ
[[33mE[37m]mail reply  . Пижйрзабу ШзсдлЮйЮ   [[33mR[37m]eply . . . . . . . . .  АзсдлЮйЮ
[[33mT[37m]hread  . . .  АбжвжмЯхШ ЫаШвцЪжм   [[33mS[37m]IGop menu . . . Ддлжвтк жиЪШдрлу
e[[33mX[37m]it . . . . . . . . . . . ДежЫжк

Ж ЬзавжЪу йШк ([33m?[37m ЪаШ ЩжуЯЬаШ); } T Scan Club messages, choices after reading message


RSRMNU3H {[0;1m

!JЛзжиЬхлЬ дШ ЫщйЬлЬ лак Ьеук Ьдлжвтк йЬ Шмлц лж йЮгЬхж:!)

!W[33mN[37mext:     !iЛЬлШнтиЬйлЬ йлж ЬзцгЬдж гудмгШ.
ЛзжиЬхлЬ дШ оиЮйагжзжауйЬлЬ Шмлу лЮд Ьдлжву ЪаШ тдШ ЬхЫжк Шзвук ШдходЬмйЮк лрд гЮдмгслрд.
ГщйлЬ зжввтк нжитк лЮд Ьдлжву N рк йчдлгЮйЮ, бШа лж йчйлЮгШ ЯШ зижориуйЬа ЬгнШдхЭждлск йШк
лак ЬзабЬнШвхЫЬк (headers) лрд гЮдмгслрд зжм зЬидсЬа. Длйа, гЬ лЮд Ьдлжву [33mNNNN[37m,
Ю ЩсйЮ ЯШ йШк ЫЬхеЬа лак ЬзабЬнШвхЫЬк лрд ЬзцгЬдрд лЬййсирд гЮдмгслрд, бШа ЯШ йлШгШлуйЬа йлж лЬвЬмлШхж.!)
!0l
!W[33mP[37mrevious: !iЛЬлШнтиЬйлЬ йлж зижЮЪжчгЬдж гудмгШ. КЬалжмиЪЬх цзрк ШбиаЩщк бШа Ю зижЮЪжчгЬдЮ Ьдлжву.!)
!0l
!W[33m#[37m:        !iТж йчйлЮгШ ЯШ йШк ЭЮлуйЬа тдШд ШиаЯгц гЮдчгШлжк йлж жзжхж ЯШ гЬлШЩЬхлЬ.
Ад лж гудмгШ ЫЬд ЩиЬЯЬх, ЯШ лжзжЯЬлЮЯЬхлЬ йлж бждладцлЬиж гудмгШ. ЛзжиЬхлЬ бШа ЬЫщ дШ оиЮйагжзжауйЬлЬ
ймдлгуйЬак: Ю Ьдлжву [33m#1000[37m ЯШ йШк зсЬа бШлЬмЯЬхШд йлж гудмгШ 1000.!)
!0l
!W[33mT[37mhread:   !iАбжвжмЯхШ ЫаШвцЪжм. Амлу Ю Ьдлжву йШк ЬгнШдхЭЬа
тдШ ШбцгШ гЬджч, гЬ лЮд ЩжуЯЬаШ лжм жзжхжм гзжиЬхлЬ дШ бадЮЯЬхлЬ йлж
зижЮЪжчгЬдж у ЬзцгЬдж гудмгШ лЮк ймЭулЮйЮк. ЛзжиЬхлЬ ЬзхйЮк дШ зслЬ йлж
гудмгШ зижк лж жзжхж ШзШдлс лж литожд гудмгШ.!)
!0l
!W[33mE[37mmail:    !iСоЮгШлхЭЬлЬ ШзсдлЮйЮ зижк Шмлц лж гудмгШ. Ж ШзсдлЮйЮ ЯШ йлШвЬх рк
зижйрзабц гудмгШ йлж ШзжйлжвтШ лжм гЮдчгШлжк.!)
!W[33mR[37meply:    !iГЮгажмиЪЬхлШа ЫЮгцйаж гудмгШ-ШзсдлЮйЮ зижк лж литожд гудмгШ.!)
!0l
!W[33mS[37mIGop:    !iЛЬлШнтиЬйлЬ йлж гЬджч жиЪШдрлу лжм club @CLUB@. ДбЬх гзжиЬхлЬ дШ
ШдлаЪиспЬлЬ, дШ зижрЮЯуйЬлЬ, дШ ЫаШЪиспЬлЬ бШа дШ гЬлШЩсввЬлЬ гЮдчгШлШ, бШа сввШ. ВаШ зЬиаййцлЬиЬк звЮижнжихЬк
гзЬхлЬ йлж гЬджч бШа ЭЮлуйлЬ ЩжуЯЬаШ.!)
!0l
[0;1m} T Scan Club messages, help about reading messages, version 3


ATTNAP {[0;1;31m
██  !W!iУзсиоЬа тдШ ШиоЬхж ймдЮггтдж йлж гудмгШ, Шввс
ж жиЪШдрлук лжм club ЫЬд лж тоЬа ШбцгШ ЬЪбихдЬа.!)
!0l[0;1m} T Download Club attachment, file not approved


ATTNAX {[0;1;31m
██  !W!iУзсиоЬа тдШ ШиоЬхж ймдЮггтдж йлж гудмгШ, Шввс йЬ Шмлц лж Club
ЫЬд тоЬлЬ ЬзхзЬЫж зжм дШ йШк ЬзалитзЬа лЮд гЬлШнжис лжм.!)
!0l[0;1m} T Download Club attachment, access denied


THRMNU {[0;1m
АбжвжмЯхШ ЬетваеЮк ЫаШвцЪжм гтйр гЮдмгслрд:

[[33mF[37m]orward . . . . .  ДзцгЬдж гудмгШ   [[33mB[37m]ackward . . . ПижЮЪжчгЬдж гудмгШ
[[33mP[37m]arent . . . . . . ПШлиабц гудмгШ   [[33mR[37m]eturn  . . . . . . . . Дзайлижну
e[[33mX[37m]it . . . . . . . . . . . ДежЫжк

Ж ЬзавжЪу йШк ([33m?[37m ЪаШ ЩжуЯЬаШ); } T Scan Club messages, threading menu



THRMNUH {[0;1m

!JЛзжиЬхлЬ дШ ШбжвжмЯуйЬлЬ лЮд ЬетваеЮ Ьдцк ЫаШвцЪжм зжвч ЬчбжвШ. ДдШк ЫасвжЪжк
ШзжлЬвЬхлШа Шзц гЮдчгШлШ зжм тожмд лж хЫаж ЯтгШ.
ЛзжиЬхлЬ дШ ЫщйЬлЬ лак Ьеук Ьдлжвтк йЬ Шмлц лж йЮгЬхж:!)

!W[33mF[37morward:  !iЛЬлШбхдЮйЮ йлж ЬзцгЬдж гудмгШ гЬ Шмлц лж ЯтгШ.!)
!0l
!W[33mB[37mackward: !iЛЬлШнтиЬйлЬ йлж зижЮЪжчгЬдж гудмгШ лЮк ймЭулЮйЮк.!)
!0l
!W[33mP[37marent:   !iЛЬлШбхдЮйЮ йлж зШлиабц гудмгШ, ЫЮвШЫу лж гудмгШ зижк лж жзжхж
ШзШдлс лж литожд гудмгШ.!)
!0l
!W[33mR[37meturn:   !iДзайлижну йлж Шиоабц гудмгШ. Ж Ьдлжву Шмлу йШк ЬзайлитнЬа
йлж гудмгШ зжм ЫаШЩсЭШлЬ цлШд еЬбадуйШлЬ лЮд ШбжвжмЯхШ ЫаШвцЪжм. Ад тоЬлЬ бсдЬа зсдр Шзц гхШ ШбжвжмЯхШ
ЫаШвцЪжм, гЬлШнтиЬйлЬ йлж гудмгШ зжм ЫаШЩсЭШлЬ цлШд еЬбадуйШлЬ лЮд зищлЮ ШбжвжмЯхШ.!)
!0l
[0;1m} T Scan Club messages, threading help


THREAD {[0;1;36;5m
██  [0;1;36m!W!iАбжвжмЯхШ ЫаШвцЪжм ([33mTR[36m ЪаШ лЬигШлайгц ШбжвжмЯхШк).!)
!0l[0;1m} T Scan Club messages, thread indicator


THRNRET {[0;1;31m
!JГЬд ЩихйбЬйлЬ йЬ бШлсйлШйЮ ШбжвжмЯхШк ЫаШвцЪжм. Ж Ьзайлижну йлж
зижЮЪжчгЬдж гудмгШ ЫЬд тоЬа дцЮгШ.!)
[0;1m} T Threading, can't use return unless threading


THREND {[0;1;33m
!JФлсйШлЬ йлж лтвжк лЮк ймЭулЮйЮк. ХиЮйагжзжауйлЬ лЮд Ьдлжву [37mTR[33m ЪаШ дШ
ЬзШдтвЯЬлЬ йлж Шиоабц гудмгШ.!)
[0;1m} T Threading, reached end of discussion


THRBEG {[0;1m
!JФлсйШлЬ йлЮд Шиоу лЮк ймЭулЮйЮк. ХиЮйагжзжауйлЬ лЮд Ьдлжву [33mTR[37m
ЪаШ дШ ЬзШдтвЯЬлЬ йлж Шиоабц гудмгШ.!)
[0;1m} T Threading, reached beginning of discussion


THRRET {[0;1m
!JДзайлижну йлж гудмгШ [32m%s/%d[37m, лж жзжхж ЫаШЩсЭШлЬ цлШд
еЬбадуйШлЬ лЮд ШбжвжмЯхШ ЫаШвцЪжм.!)
[0;1m} T Threading, returning to original message


THRPR {[0;1;31m
!JСмЪЪдщгЮ, Шмлц лж гудмгШ ЫЬд ЬхдШа ШзсдлЮйЮ йЬ
бсзжаж сввж. ВаШ дШ ЫЬхлЬ лж "зШлиабц гудмгШ" зитзЬа лж литожд гудмгШ дШ
ШдШнтиЬа "[37m(АзсдлЮйЮ йлж Club/xxx)[31m", цзжм [37mxxx[31m
ЬхдШа ШиаЯгцк лжм "зШлиабжч гЮдчгШлжк".!)
} T Threading, there is no parent message


THRPNF {[0;1;31m
!JТж гудмгШ [37m%s/%d[31m ЫЬд ЩитЯЮбЬ.
ПаЯШдцлШлШ ЫаШЪиснлЮбЬ Шзц лжд ШзжйлжвтШ, лжд ОиЪШдрлу лжм Club, у лж
йчйлЮгШ.!)
[0;1m} T Threading, parent message not found


THRCLC {[0;1;32m
!JДЪбШлШвЬхзжмгЬ лж club [37m@CLUB@[32m, бШа гзШхджмгЬ йлж [37m%s[32m.
ЛзжиЬхлЬ дШ ЫщйЬлЬ лЮд Ьдлжву [32mTR[32m ЪаШ дШ ЬзайлитпЬлЬ йлж Шиоабц
club бШа гудмгШ.!)
[0;1m} T Threading, leaving current club





MCMVT {[0;30;47m ┌─────────────────────────── [34mЛЬлШЩжву гЮдчгШлжк[0;30;47m ───────────────────────────[0;1;37;47m┐ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │  ЗтгШ . . . . . . . . . . [1;44;37m@63;43;0s[0;1;47;37m  │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │  АиоЬхж  . . . . . . . .  [1;44;37m@16;16;0s[0;1;47;37m                             │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │  Ctrl-R ЪаШ ЩжуЯЬаШ                                                      [1;37m│ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │             [0;1;42;33m@14;"ЙЬхгЬдж"b[0;47;30m▄    [0;1;42;33m@14;"OK"b[0;47;30m▄    [0;1;41;33m@14;"Абмиж"b[0;47;30m▄  [0;1;47;37m│ [0m
[30;47m │              ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀     ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀     ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀  [0;1;47;37m│ [0m
[30;47m └[0;1;37;47m──────────────────────────────────────────────────────────────────────────┘ [0m} T Modify Club Message, visual template


MCMLT {[2J[0;30;47m ┌─────────────────────────── [34mЛЬлШЩжву гЮдчгШлжк[0;30;47m ───────────────────────────[0;1;37;47m┐ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ [31m1[30m. ЗтгШ . . . . [34m@63;56;0s[0;1;47;37m │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ [31m2[30m. АиоЬхж  . . . . . . . . . . . . . . . . . . . . . .  [34m@16;16;0s[0;1;47;37m │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ [31m3[30m. ЛЬлШЩжву бЬагтджм гЮдчгШлжк@1;"3Edit"b                                         [1;37m  │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m └[0;1;37;47m──────────────────────────────────────────────────────────────────────────┘ [0;1m
} T Modify message, linear template


MCMNEWSUBJ {[0;1m
!WГщйлЬ лж дтж ЯтгШ лжм гЮдчгШлцк йШк.!)
} T Modify message, new subject


MCMNEWATTN {[0;1m
!WГщйлЬ лж дтж цджгШ лжм ймдЮггтджм ШиоЬхжм. Ад ШнуйЬлЬ лж цджгШ бЬдц,
ЯШ ЬзШдтвЯЬа ШмлцгШлШ йлж бШлс ймдЯубЮ цджгШ, xxx.att, цзжм xxx ж ШиаЯгцк
лжм гЮдчгШлжк. Амлц лж зЬЫхж ЯШ ШЪджЮЯЬх Шд ЫЬд тоЬлЬ ЬзаймдспЬа ШиоЬхж йлж
гудмгс йШк.!)
} T Modify message, new filename




COPMNU {[0;1m
Ддлжвтк жиЪШдрлу:

[[33mM[37m]odify  . . . .  АввШЪу гЮдчгШлжк   [[33mE[37m]rase  . . . . ГаШЪиШну гЮдчгШлжк
[[33mC[37m]opy . . . . . . . . .  АдлаЪиШну   [[33mF[37m]orward . . . . . . . .  ПижщЯЮйЮ
[[33mT[37m]ag exempt  . . . (ЛЮ) ЫаШЪиспагж   [[33mP[37m]eriodic . . . . ПЬиажЫабц гудмгШ
[[33mB[37m]ulletin . . . .  ДайШЪрЪу сиЯижм   e[[33mX[37m]it  . . . . . . . . . .  ДежЫжк

Ж ЬзавжЪу йШк ([33m?[37m ЪаШ ЩжуЯЬаШ); } T Club-op menu


COPMNUH {[0;1m

!JЧк жиЪШдрлук лжм club @CLUB@, тоЬлЬ лак Ьеук ЬаЫабтк Ьдлжвтк:!)

!W[33mM[37modify:     !iДзалитзЬа лЮд ШввШЪу лжм бЬагтджм Ьдцк гЮдчгШлжк,
бШЯщк бШа жиайгтдрд свврд оШиШблЮиайлабщд лжм (ЯтгШ, гЮ ЫаШЪиспагж, зЬиажЫабц гудмгШ,
цджгШ бШа тЪбиайЮ ШиоЬхжм, бвз).!)
!0l
!W[33mE[37mrase:      !iГаШЪиснЬа лж гудмгШ. ГДМ ЯШ мзсиеЬа зижЬаЫжзжхЮйЮ. Тж гудмгШ
осдЬлШа ШдЬзайлиЬзлх.!)
!0l
!W[33mC[37mopy:       !iГЮгажмиЪЬхлШа ШдлхЪиШнж лжм гЮдчгШлжк, лж жзжхж йлтвдЬлШа йЬ ЫаЬчЯмдйЮ
зжм ЯШ жихйЬлЬ.!)
!0l
!W[33mF[37morward:    !iТж гудмгШ ЫаШЪиснЬлШа Шзц лж club, бШа зижрЯЬхлШа йлЮд
ЫаЬчЯмдйЮ зжм ЯШ жихйЬлЬ.!)
!0l
!W[33mT[37mag exempt:  !iТж бЬхгЬдж ЪхдЬлШа гЮ ЫаШЪиспагж. ТШ гЮ ЫаШЪиспагШ гЮдчгШлШ ЫЬд гзжижчд дШ ЫаШЪиШнжчд
гЬ лЮд Ьдлжву [33mE[37mrase. ХиЮйагжзжащдлШк лЮд Ьдлжву [33mT[37mag йЬ тдШ гудмгШ зжм ЬхдШа уЫЮ гЮ ЫаШЪиспагж,
лж гудмгШ осдЬа Шмлу лЮд аЫацлЮлШ бШа гзжиЬх звтжд дШ ЫаШЪиШнЬх ЬхлЬ Шзц оиуйлЬк, ЬхлЬ Шзц лж йчйлЮгШ.!)
!0l
!W[33mP[37meriodic:    !iЛЬ Шмлу лЮд Ьдлжву жихЭЬлЬ цла лж гудмгШ ЬхдШа зЬиажЫабц. ГхдЬлЬ гхШ зЬихжЫж йЬ ЮгтиЬк.
Тж гудмгШ ЯШ зижрЯЬхлШа ШмлцгШлШ йЬ Шмлц лж Club, йЬ бсЯЬ зЬихжЫц лжм. Амлц йЮгШхдЬа цла лж гудмгШ ЯШ еШдШЬгнШдхЭЬлШа
йлж club йЬ лШблс оиждабс ЫаШйлугШлШ, йШд дШ улШд бШаджчиаж. Амлц ЬхдШа оиуйагж ЪаШ гЮдчгШлШ гЬ жЫЮЪхЬк ЪаШ тдШ club,
FAQs, ЫаШнЮгайлабс, бвз. НШдШоиЮйагжзжауйлЬ Шмлу лЮд Ьдлжву, ЫхдждлШк зЬихжЫж [33m0[37m, ЪаШ дШ ШбмищйЬлЬ лЮд
зЬиажЫабу нчйЮ Ьдцк гЮдчгШлжк.!)
!0l
!W[33mB[37mulletin:    !iТж йщгШ лжм гЮдчгШлжк (у лж ймдЮггтдж ШиоЬхж, Шд тоЬа -- ЯШ ЬирлЮЯЬхлЬ)
ЬайсЪЬлШа йлж ШдШЪдрйлуиаж сиЯирд. АбжвжмЯуйлЬ лак жЫЮЪхЬк зжм ЯШ йШк ЫщйЬа лж йчйлЮгШ.!)
!0l
[0;1m} T Club-op menu, help


COPMNUF {[0;1m
Ддлжвтк жиЪШдрлу:

[[33mM[37m]odify  . . . .  АввШЪу гЮдчгШлжк   [[33mE[37m]rase  . . . . ГаШЪиШну гЮдчгШлжк
[[33mC[37m]opy . . . . . . . . .  АдлаЪиШну   [[33mF[37m]orward . . . . . . . .  ПижщЯЮйЮ
[[33mT[37m]ag exempt  . . . (ЛЮ) ЫаШЪиспагж   [[33mP[37m]eriodic . . . . ПЬиажЫабц гудмгШ
[[33mA[37m]pprove  . . . .  ДЪбиайЮ ШиоЬхжм   [[33mI[37m]nsert att . . ДдйргслрйЮ ШиоЬхжм
[[33mB[37m]ulletin  . . . . ДайШЪрЪу сиЯижм   e[[33mX[37m]it  . . . . . . . . . .  ДежЫжк

Ж ЬзавжЪу йШк ([33m?[37m ЪаШ ЩжуЯЬаШ); } T Club-op menu for file attachments


COPERR {[0;1;31m
!JКмзсгШа, ЫЬд мзсиоЬа Шмлу Ю ЬзавжЪу.!)
[0;1m} T Club-op menu, invalid selection from menu


COPMNUFH {[0;1m

!JЧк жиЪШдрлук лжм club @CLUB@, тоЬлЬ лак Ьеук ЬаЫабтк Ьдлжвтк:!)

!W[33mM[37modify:     !iДзалитзЬа лЮд ШввШЪу лжм бЬагтджм Ьдцк гЮдчгШлжк,
бШЯщк бШа жиайгтдрд свврд оШиШблЮиайлабщд лжм (ЯтгШ, гЮ ЫаШЪиспагж, зЬиажЫабц гудмгШ,
цджгШ бШа тЪбиайЮ ШиоЬхжм, бвз).!)
!0l
!W[33mE[37mrase:      !iГаШЪиснЬа лж гудмгШ. ГДМ ЯШ мзсиеЬа зижЬаЫжзжхЮйЮ. Тж гудмгШ
осдЬлШа ШдЬзайлиЬзлх.!)
!0l
!W[33mC[37mopy:       !iГЮгажмиЪЬхлШа ШдлхЪиШнж лжм гЮдчгШлжк, лж жзжхж йлтвдЬлШа йЬ ЫаЬчЯмдйЮ
зжм ЯШ жихйЬлЬ.!)
!0l
!W[33mF[37morward:    !iТж гудмгШ ЫаШЪиснЬлШа Шзц лж club, бШа зижрЯЬхлШа йлЮд
ЫаЬчЯмдйЮ зжм ЯШ жихйЬлЬ.!)
!0l
!W[33mT[37mag exempt:  !iТж бЬхгЬдж ЪхдЬлШа гЮ ЫаШЪиспагж. ТШ гЮ ЫаШЪиспагШ гЮдчгШлШ ЫЬд гзжижчд дШ ЫаШЪиШнжчд
гЬ лЮд Ьдлжву [33mE[37mrase. ХиЮйагжзжащдлШк лЮд Ьдлжву [33mT[37mag йЬ тдШ гудмгШ зжм ЬхдШа уЫЮ гЮ ЫаШЪиспагж,
лж гудмгШ осдЬа Шмлу лЮд аЫацлЮлШ бШа гзжиЬх звтжд дШ ЫаШЪиШнЬх ЬхлЬ Шзц оиуйлЬк, ЬхлЬ Шзц лж йчйлЮгШ.!)
!0l
!W[33mP[37meriodic:    !iЛЬ Шмлу лЮд Ьдлжву жихЭЬлЬ цла лж гудмгШ ЬхдШа зЬиажЫабц. ГхдЬлЬ гхШ зЬихжЫж йЬ ЮгтиЬк.
Тж гудмгШ ЯШ зижрЯЬхлШа ШмлцгШлШ йЬ Шмлц лж Club, йЬ бсЯЬ зЬихжЫц лжм. Амлц йЮгШхдЬа цла лж гудмгШ ЯШ еШдШЬгнШдхЭЬлШа
йлж club йЬ лШблс оиждабс ЫаШйлугШлШ, йШд дШ улШд бШаджчиаж. Амлц ЬхдШа оиуйагж ЪаШ гЮдчгШлШ гЬ жЫЮЪхЬк ЪаШ тдШ club,
FAQs, ЫаШнЮгайлабс, бвз. НШдШоиЮйагжзжауйлЬ Шмлу лЮд Ьдлжву, ЫхдждлШк зЬихжЫж [33m0[37m, ЪаШ дШ ШбмищйЬлЬ лЮд
зЬиажЫабу нчйЮ Ьдцк гЮдчгШлжк.!)
!0l
!W[33mA[37mpprove:     !iТж гудмгШ тоЬа тдШ ймдЮггтдж ШиоЬхж. Тж ШиоЬхж ЬЪбихдЬлШа ЪаШ вупЮ Шзц лжмк оиуйлЬк.
Ад лж ШиоЬхж ЬхдШа уЫЮ ЬЪбЬбиаггтдж, Шмлу Ю Ьдлжву ШдШаиЬх лЮд тЪбиайЮ.!)
!0l
!W[33mI[37mnsert att:  !iПжввжх оиуйлЬк йлтвджмд лШ гЮдчгШлс лжмк
рк ймдЮггтдШ ШиоЬхШ, гЬ ШзжлтвЬйгШ йоЬЫцд бШдЬхк дШ гЮд лШ ЫаШЩсЭЬа. ЛЬ
Шмлу лЮд Ьдлжву лж ймдЮггтдж йЬ тдШ гудмгШ ШиоЬхж зижйлхЯЬлШа йлж йщгШ лжм
гЮдчгШлжк (у ШдлабШЯайлс лж йщгШ лжм гЮдчгШлжк -- ЯШ ЬирлЮЯЬхлЬ ЪаШ лак
ШбиаЩЬхк зижЯтйЬак йШк). Тж гудмгШ йлШгШлсЬа дШ тоЬа ймдЮггтдж ШиоЬхж.!)
!0l
!W[33mB[37mulletin:    !iТж йщгШ лжм гЮдчгШлжк (у лж ймдЮггтдж ШиоЬхж, Шд тоЬа -- ЯШ ЬирлЮЯЬхлЬ)
ЬайсЪЬлШа йлж ШдШЪдрйлуиаж сиЯирд. АбжвжмЯуйлЬ лак жЫЮЪхЬк зжм ЯШ йШк ЫщйЬа лж йчйлЮгШ.!)
!0l
[0;1m} T Club-op menu for file attachments, help



COPTTG {[0;1;32m
!JЙШвщк, лж гудмгШ ЬхдШа звтжд [37mЛЮ ГаШЪиспагж[32m.!)
[0;1m} T Club-op menu, tag exempt, message has been tagged


COPTUN {[0;1;32m
!JЙШвщк, лж гудмгШ ЬхдШа звтжд [37mЫаШЪиспагж[32m.!)
[0;1m} T Club-op menu, tag exempt, message has been untagged


COPPASK {[0;1m
!WЙсЯЬ зцйЬк гтиЬк ЯтвЬлЬ дШ ЬзШдЬгнШдхЭЬлШа Шмлц лж гудмгШ (0=гЮ зЬиажЫабц); } T Club-op menu, periodic message, get period


COPPDEF {[Enter=%d]!) [0m} T Club-op menu, periodic message, default


COPPERR {[0;1;31m
!WПШиШбШвщ ЫщйлЬ тдШд ШиаЯгц гЬлШеч [37m%d[31m бШа [37m%d[31m.!)
[0;1m} T Club-op menu, periodic message, error


COPPOK1 {[0;1;32m
!WЙШвщк, лж гудмгШ осдЬа лЮд зЬиажЫабу лжм нчйЮ.!)
[0;1m} T Club-op menu, periodic message, zero period


COPPOK2 {[0;1;32m
!WЙШвщк, лж гудмгШ ЯШ ЬзШдЬгнШдхЭЬлШа йлж club бсЯЬ [37m%d Югти%s[32m.!)
[0;1m} T Club-op menu, periodic message, zero period


DAYSNG {Ш} T Days, singular form
DAYPLR {Ьк} T Days, plural form


COPAAPP {[0;1m
!JЙШвщк, лж ймдЮггтдж йЬ Шмлц лж гудмгШ ШиоЬхж ЬЪбихЯЮбЬ.!)
[0;1m} T Club-op menu, approved attached file


COPAUNA {[0;1m
!JЙШвщк, Ю тЪбиайЮ вупЮк лжм ймдЮггтджм йЬ Шмлц лж гудмгШ ШиоЬхжм
ШзжйчиЬлШа.!)
[0;1m} T Club-op menu, unapproved attached file


COPMVT {[0;30;47m ┌─────────────────────────── [34mЛЬлШЩжву гЮдчгШлжк[0;30;47m ───────────────────────────[0;1;37;47m┐ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │  ЗтгШ . . . . . . . . . . [1;44;37m@63;43;0s[0;1;47;37m  │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │  АиоЬхж  . . . . . . . .  [1;44;37m@16;16;0s[0;1;47;37m                             │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │  ДЪбиайЮ ШиоЬхжм . . . .  [0;30;46m [@"X "t] [0;47;30m                      (space ЪаШ ШввШЪу)  [1;37m│ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │  ЛЮ ЫаШЪиспагж . . . . .  [0;30;46m [@"X "t] [0;47;30m                      (space ЪаШ ШввШЪу)  [1;37m│ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │  ПЬихжЫжк гЮдчгШлжк  . .  [1;44;37m@6;0;999999;0n[0;30;47m    (0-999999, 0=гЮ зЬиажЫабц гудмгШ)  [1;37m│ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │  Ctrl-R ЪаШ ЩжуЯЬаШ                                                      [1;37m│ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │             [0;1;42;33m@14;"ЙЬхгЬдж"b[0;47;30m▄    [0;1;42;33m@14;"OK"b[0;47;30m▄    [0;1;41;33m@14;"Абмиж"b[0;47;30m▄  [0;1;47;37m│ [0m
[30;47m │              ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀     ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀     ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀  [0;1;47;37m│ [0m
[30;47m └[0;1;37;47m──────────────────────────────────────────────────────────────────────────┘ [0m} T Club-op menu, modify club message, visual template


COPMLT {[2J[0;30;47m ┌─────────────────────────── [34mЛЬлШЩжву гЮдчгШлжк[0;30;47m ───────────────────────────[0;1;37;47m┐ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ [31m1[30m. ЗтгШ . . . . [34m@63;56;0s[0;1;47;37m │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ [31m2[30m. АиоЬхж  . . . . . . . . . . . . . . . . . . . . . .  [34m@16;16;0s[0;1;47;37m │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ [31m3[30m. ДЪбиайЮ ШиоЬхжм  . . . . . . . . . . . . . . . . . . . . . . . .  [34m@"X "t[0;1;47;37m │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ [31m4[30m. ЛЮ ЫаШЪиспагж  . . . . . . . . . . . . . . . . . . . . . . . . .  [34m@"X "t[0;1;47;37m │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ [31m5[30m. ПЬихжЫжк гЮдчгШлжк . . . . . . . . . . . . . . . . . . . . . . [34m@6;0;999999;1n[0;1;47;37m │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ [31m6[30m. ЛЬлШЩжву бЬагтджм гЮдчгШлжк@1;"6Edit"b                                         [1;37m  │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m └[0;1;37;47m──────────────────────────────────────────────────────────────────────────┘ [0;1m
} T Club-op menu, modify club message, linear template


COPMLT1 {[0;1m
!JГщйлЬ лж дтж ЯтгШ лжм гЮдчгШлцк йШк.!)
} T Club-op menu, modify club message, linear template field #1


COPMLT2 {[0;1m
!JГщйлЬ лж дтж цджгШ лжм ймдЮггтджм ШиоЬхжм. Ад ШнуйЬлЬ лж цджгШ бЬдц,
ЯШ ЬзШдтвЯЬа ШмлцгШлШ йлж бШлс ймдЯубЮ цджгШ, xxx.att, цзжм xxx ж ШиаЯгцк
лжм гЮдчгШлжк. Амлц лж зЬЫхж ЯШ ШЪджЮЯЬх Шд ЫЬд тоЬлЬ ЬзаймдспЬа ШиоЬхж йлж
гудмгс йШк.!)
} T Club-op menu, modify club message, linear template field #2


COPMLT3 {[0;1m
!JЖ лагу Шмлжч лжм зЬЫхжм бШЯжихЭЬа Шд лж ймдЮггтдж ШиоЬхж ЬхдШа ЬЪбЬбиаггтдж у цоа.
Ад ЫЬд мзсиоЬа ймдЮггтдж ШиоЬхж, Шмлц лж зЬЫхж ЯШ ШЪджЮЯЬх.!)
} T Club-op menu, modify club message, linear template field #3


COPMLT4 {[0;1m
!JЖ лагу Шмлжч лжм зЬЫхжм бШЯжихЭЬа Шд лж гудмгШ ЬхдШа гЮ ЫаШЪиспагж у цоа.!)
} T Club-op menu, modify club message, linear template field #4


COPMLT5 {[0;1m
!JТШ зЬиажЫабс гЮдчгШлШ ЬхдШа гЮдчгШлШ зжм ЬгнШдхЭждлШа лШблабс йлж club. Амлц лж зЬЫхж
бШЯжихЭЬа Шд лж гудмгШ зжм гЬлШЩсввЬлЬ ЬхдШа зЬиажЫабц, бШа Шд дШа, бсЯЬ зцйЬк гтиЬк ЯШ
ЬгнШдхЭЬлШа. ГщйлЬ зЬихжЫж [33m0[37m ЪаШ дШ бсдЬлЬ лж гудмгШ гЮ зЬиажЫабц.
Авващк, ЫщйлЬ лЮд зЬихжЫц лжм йЬ гтиЬк. ЛЬ зЬихжЫж [33m1[37m, лж гудмгШ еШдШЬгнШдхЭЬлШа
йлж club бсЯЬ гтиШ.!)
} T Club-op menu, modify club message, linear template field #5


COPMW1 {[0;1;31m
!JТж гудмгШ ЫЬд тоЬа ймдЮггтдж ШиоЬхж. Тж зЬЫхж тЪбиайЮк ШЪджЬхлШа.!)
[0;1m} T Club-op menu, modify club message, warning 1


COPOK1 {[0;1;32m
!JТж ймдЮггтдж йЬ Шмлц лж гудмгШ ШиоЬхж ЬЪбихдЬлШа ЪаШ вупЮ.!)
[0;1m} T Club-op menu, approved message


COPOK2 {[0;1;32m
!JЖ тЪбиайЮ вупЮк лжм ймдЮггтджм йЬ Шмлц лж гудмгШ ШиоЬхжм сиЬлШа.!)
[0;1m} T Club-op menu, unapproved message


COPOK3 {[0;1;32m
!JТж гудмгШ ЬхдШа звтжд гЮ ЫаШЪиспагж.!)
[0;1m} T Club-op menu, exempted message


COPOK4 {[0;1;32m
!JТж гудмгШ гзжиЬх звтжд дШ ЫаШЪиШнЬх.!)
[0;1m} T Club-op menu, unexempted message


COPOK5 {[0;1;32m
!JТж гудмгШ ЬхдШа звтжд зЬиажЫабц, гЬ зЬихжЫж [37m%d Югти%s[32m.!)
[0;1m} T Club-op menu, periodic message


COPOK6 {[0;1;32m
!JТж гудмгШ ЫЬд ЬхдШа звтжд зЬиажЫабц.!)
[0;1m} T Club-op menu, non-periodic message


COPIAMNU {[0;1m
!WТа ШбиаЩщк ЯтвЬлЬ дШ бсдЬлЬ гЬ лж ймдЮггтдж ШиоЬхж;!)

 [[33mO[37m]verwrite body . . . . . . .  ЬзабсвмпЮ йщгШлжк гЮдчгШлжк
 [[33mA[37m]ppend to body  . . .  ЬзазицйЯЬйЮ йлж йщгШ лжм гЮдчгШлжк
e[[33mX[37m]it  . . . . . . . . . . . .  ШбчирйЮ ЫаШЫабШйхШк, тежЫжк
[0;1m} T Club-op menu, insert attachment menu


COPIASMNU {[0;1m
!WГщйлЬ лЮд ЬзавжЪу йШк ([33mO[37m,[33mA[37m, [33m?[37m  ЪаШ ЩжуЯЬаШ, у [33mX[37m ЪаШ тежЫж):!) [0m} T Club-op menu, insert attachment short menu


COPIARS {[0;1;31m
!WКмзсгШа, Шмлу Ю ЬзавжЪу ЫЬд ЬхдШа ЫмдШлу.!)
[0;1m} T Club-op menu, insert attachment, invalid selection


COPIAH {[0;1m

!WOverwrite: !iТж ймдЮггтдж ШиоЬхж ШдлабШЯайлс лж йщгШ лжм гЮдчгШлжк.
Тж Шиоабц йщгШ лжм гЮдчгШлжк осдЬлШа ШдЬзайлиЬзлх.!)
!0l
!WAppend:    !iТж ймдЮггтдж ШиоЬхж зижйлхЯЬлШа йлж лтвжк лжм йщгШлжк лжм
гЮдчгШлжк.!)
!0l
!W[0;1;33;5m██[0;1;33m  ПРОСОХЖ: !iПиад оиЮйагжзжауйЬлЬ Шмлу лЮд Ьдлжву,
ЬзаЩЬЩШащйлЬ цла лж ймдЮггтдж ШиоЬхж зжм зижйзШЯЬхлЬ дШ ЬдйргШлщйЬлЬ ЬхдШа
цдлрк ШиоЬхж бЬагтджм, бШа цоа бсзжаж ЫмШЫабц ШиоЬхж.!)
!0l
[0;1m} T Club-op menu, insert attachment, help


COPIAO {[0;1;32m
!JЙШвщк, лж ймдЮггтдж ШиоЬхж тоЬа звтжд ШдлабШлШйлуйЬа лж йщгШ лжм гЮдчгШлжк.!)
[0;1m} T Club-op menu, insert attachment, overwritten


COPIAA {[0;1;32m
!JЙШвщк, лж ймдЮггтдж ШиоЬхж тоЬа звтжд зижйлЬЯЬх йлж лтвжк лжм йщгШлжк
лжм гЮдчгШлжк.!)
[0;1m} T Club-op menu, insert attachment, appended


COPIAR {[0;1;31m
!JУзуиеЬ йнсвгШ ЬЪЪиШнук/ШдсЪдрйЮк бШлс лЮд ЫасибЬаШ лЮк ЫаШЫабШйхШк.
ПШиШбШвщ ЬаЫжзжауйлЬ лжд ХЬаиайлу СмйлугШлжк ЪаШ лак ймдЯубЬк зжм ЫЮгажчиЪЮйШд
Шмлц лж всЯжк.!)
[0;1m} T Club-op menu, insert attachment, error


RKASK {[0;1m
!WГщйлЬ гхШ у зЬиаййцлЬиЬк втеЬак бвЬаЫхШ, у [33m?[37m ЪаШ ЩжуЯЬаШ:!)[0m } T Keyword scan, get search key(s)


RKHELP {[0;1m
!JЖ ЬзавжЪу Шмлу ШдаодЬчЬа цвШ лШ гЮдчгШлШ Ьдцк Club йлШгШлщдлШк гцдж йЬ Шмлс
зжм зЬиатожмд лак втеЬак бвЬаЫас зжм жихйШлЬ. ВаШ дШ жихйЬлЬ гцдж гхШ втеЮ
бвЬаЫх, Шзвщк ЫщйлЬ лЮ втеЮ бШа зШлуйлЬ [33mEnter[37m. ВаШ зЬиаййцлЬиЬк втеЬак
бвЬаЫас, ЫаШориуйлЬ лак гЬ бЬдс. Ад тоЬлЬ гаШ йчдЯЬлЮ втеЮ бвЬаЫх зжм зЬиатоЬа
бЬдс, оиЮйагжзжауйлЬ гаШ зШчвШ ([33m-[37m): Ю зШчвШ йЮгШхдЬа бЬдц, йЮгЬхж йлхеЮк,
йчгЩжвж у бШа лШ лихШ гШЭх.!)

!JЖ тиЬмдШ ЬхдШа нрдЮлабу, щйлЬ дШ еЬзЬидс ШджиЯжЪиШнхЬк бШа сввШ всЯЮ.
ГЮвШЫу, Ю втеЮ бвЬаЫх "Sysop" лШаиасЭЬа гЬ жзжаШЫузжлЬ Шзц лак втеЬак "ймйжз",
"ймйрз", "СУСОП", "SYSOP".!)

!JВаШ зШисЫЬаЪгШ, Шд ЫщйЬлЬ рк втеЬак бвЬаЫхШ "demo system" ЪаШ дШ ШдаодЬчйЬлЬ
лШ гЮдчгШлШ гЬ лак втеЬак "demo" бШа "system", лж ШзжлтвЬйгШ ЯШ ймгзЬиавсЩЬа
Ьехйжм лЮд нисйЮ "drugs [32msystem[37matically [32mdemo[37mlish your brain".!)

!JВаШ дШ ймЪбЬбиагЬджзжауйЬлЬ лЮд ШдходЬмйЮ йЬ "DH Demo System",
ЫщйлЬ "DH-demo-system". Аввс ЬхдШа бШвчлЬиШ дШ тоЬлЬ гЬиабс гЮдчгШлШ зШиШзсдр
зШис дШ осйЬлЬ бсзжаШ сввШ йЮгШдлабс!!)
[0;1m} T Keyword scan, help on searching


RKSCAN1 {[0;1m
!WАдаодЬчр лж club [32m@CLUB@[37m ЪаШ лЮд втеЮ бвЬаЫх "[32m%s[37m"...!)
[0;1m} T Keyword scan, start scanning (single keyword)


RKSCAN2 {[0;1m
!WАдаодЬчр лж club [32m@CLUB@[37m ЪаШ лак втеЬак бвЬаЫас "[32m%s[37m"} T Keyword scan, start scanning (multiple keyword)


RKSCAN3 {, "[32m%s[37m"} T Keyword scan, keyword


RKSCAN4 { бШа "[32m%s[37m".!)
[0;1m} T Keyword scan, last keyword


RKIND0 {[s [0;30;40m[K[u} T Keyword scan, work indicator, begin

RKIND1 {[u[0m| %d[30m[K} T Keyword scan, work indicator, frame 1
RKIND2 {[u[0m/ %d[30m[K} T Keyword scan, work indicator, frame 2
RKIND3 {[u[0m- %d[30m[K} T Keyword scan, work indicator, frame 3
RKIND4 {[u[0m\ %d[30m[K} T Keyword scan, work indicator, frame 4
RKIND5 {[u[0m| %d[30m[K} T Keyword scan, work indicator, frame 5
RKIND6 {[u[0m/ %d[30m[K} T Keyword scan, work indicator, frame 6
RKIND7 {[u[0m- %d[30m[K} T Keyword scan, work indicator, frame 7
RKIND8 {[u[0m\ %d[30m[K} T Keyword scan, work indicator, frame 8

RKINDE {[u[0;1m[K} T Keyword scan, work indicator, end


RKFOUND {[0;1;32m
!W██  !iЖ втеЮ бвЬаЫх "%s" ЩитЯЮбЬ.!)
!0l[0;1m} T Keyword scan, found the keyword


RKCAN {[0;1;31m

!JГаШбцзЮбЬ Шзц лжд оиуйлЮ.!)
[0;1m} T Keyword scan, aborted


FAPPSCN {[0;1;32m
!JЦсодр лж club [37m@CLUB@[32m ЪаШ ШиоЬхШ зжм ШдШгтджмд тЪбиайЮ.!)
[0;1m} T File approval, scanning for unapproved files


FAPPASK {[0;1m
!WЗтвЬлЬ дШ ЬЪбихдЬлЬ Шмлц лж ШиоЬхж; [[33mY[37m]yes=дШа / [[33mN[37m]o=цоа):!)[0m } T File approval, approval question


FAPPERR {[0;1;31m
!JКмзсгШа, Шмлу Ю ЬзавжЪу ЫЬд ЬхдШа ЫмдШлу.!)
[0;1m} T File approval, error in answer to FAPPASK


FAPPAPP {[0;1;32m
!JЙШвщк, лж ШиоЬхж ЬхдШа звтжд ЬЪбЬбиагтдж бШа ЫаШЯтйагж ЪаШ вупЮ.!)
[0;1m} T File approval, file has been approved





QSEMPTY {[0;1;31m
!JСмЪЪдщгЮ, Шввс ЫЬд мзсиожмд clubs йлЮд вхйлШ ЪиуЪжиЮк ШдходЬмйук йШк.
ХиЮйагжзжауйлЬ лЮд Ьдлжву [33mRQC[31m Шзц лж бЬдлиабц гЬджч лрд clubs ЪаШ дШ
жихйЬлЬ йЬ зжаШ clubs ЯШ ЪхдЬлШа Ю ЪиуЪжиЮ ШдходЬмйЮ.!)
[0;1m} T Quickscan, quickscan record is empty.


QSNONEW {[0;1;33m
!JГЬд ЩитЯЮбШд дтШ гЮдчгШлШ.!)
[0;1m} T Quickscan, no new messages found


QSSCAN {[0;1;32m
!WАдходЬмйЮ лжм [37m/%s[32m...!)
[0;1m} T Quickscan, quick scanning


QSEND {[0;1;32m
!JТтвжк лЮк ШдходЬмйЮк.!)
[0;1m} T Quickscan, end of quickscan


QSABORT {[0;1;31m
!JТЬигШлайгцк лЮк ЪиуЪжиЮк ШдходЬмйЮк.!)
[0;1m} T Quickscan, aborted


QSLEAVE {[0;1;32m
!JФЬчЪжмгЬ Шзц лж club [37m/@CLUB@[32m.!)
[0;1m} T Quickscan, leaving current club


QSDONE {[0;1m
!JТтвжк лЮк ЪиуЪжиЮк ШдходЬмйЮк.!)
[0;1m} T Quickscan, done with quickscan


QSNNEM {[0;1;32m
!JГЬд мзсиожмд дтШ гЮдчгШлШ йлж ЖвЬближдабц ТШомЫижгЬхж.!)
[0;1m} T Email Quickscan, no new mail in email area


QSLVEM {[0;1;32m
!JФЬчЪжмгЬ Шзц лШ гЮдчгШлШ ЖвЬближдабжч ТШомЫижгЬхжм...!)
[0;1m} T Email Quickscan, leaving email area


QWRT2EM {[0;1;32m
!JДзайлитнжмгЬ йлШ гЮдчгШлШ ЖвЬближдабжч ТШомЫижгЬхжм...!)
[0;1m} T Email Quickscan, back to email messages


QSNOJMP {[0;1;31m
!JКмзсгШа, Шмлу Ю Ьдлжву ЫЬд ЬхдШа ЫмдШлу йЬ Шмлц лж йЮгЬхж.!)
[0;1m} T Email Quickscan, can't use jump commands here


RQSRMNU1 {[0;1m
[[33mN[37m]ext . . . . . . . ДзцгЬдж гудмгШ   [[33mP[37m]revious  . .  ПижЮЪжчгЬдж гудмгШ
[[33mE[37m]mail reply .  Пижйрзабу ШзсдлЮйЮ   [[33mR[37m]eply  . . . . . . . . . АзсдлЮйЮ
[[33mT[37m]hread . . . . АбжвжмЯхШ ЫаШвцЪжм   [[33mQ[37m]uickscan . . . ВиуЪжиЮ ШдходЬмйЮ
e[[33mX[37m]it  . . . . . . . . . .  ДежЫжк

Ж ЬзавжЪу йШк ([33m?[37m ЪаШ ЩжуЯЬаШ); } T Quickscan, choices after reading message


RQSRMNU1H {[0;1m

!JЛзжиЬхлЬ дШ ЫщйЬлЬ лак Ьеук Ьдлжвтк йЬ Шмлц лж йЮгЬхж:!)

!W[33mN[37mext:      !iЛЬлШнтиЬйлЬ йлж ЬзцгЬдж гудмгШ.
ЛзжиЬхлЬ дШ оиЮйагжзжауйЬлЬ Шмлу лЮд Ьдлжву ЪаШ тдШ ЬхЫжк Шзвук ШдходЬмйЮк лрд гЮдмгслрд.
ГщйлЬ зжввтк нжитк лЮд Ьдлжву N рк йчдлгЮйЮ, бШа лж йчйлЮгШ ЯШ зижориуйЬа ЬгнШдхЭждлск йШк
лак ЬзабЬнШвхЫЬк (headers) лрд гЮдмгслрд зжм зЬидсЬа. Длйа, гЬ лЮд Ьдлжву [33mNNNN[37m,
Ю ЩсйЮ ЯШ йШк ЫЬхеЬа лак ЬзабЬнШвхЫЬк лрд ЬзцгЬдрд лЬййсирд гЮдмгслрд, бШа ЯШ йлШгШлуйЬа йлж лЬвЬмлШхж.!)
!0l 
!W[33mP[37mrevious:  !iЛЬлШнтиЬйлЬ йлж зижЮЪжчгЬдж гудмгШ. КЬалжмиЪЬх цзрк ШбиаЩщк бШа Ю зижЮЪжчгЬдЮ Ьдлжву.!)
!0l
!W[33m#[37m:         !iТж йчйлЮгШ ЯШ йШк ЭЮлуйЬа тдШд ШиаЯгц гЮдчгШлжк йлж жзжхж ЯШ гЬлШЩЬхлЬ.
Ад лж гудмгШ ЫЬд ЩиЬЯЬх, ЯШ лжзжЯЬлЮЯЬхлЬ йлж бждладцлЬиж гудмгШ. ЛзжиЬхлЬ бШа ЬЫщ дШ оиЮйагжзжауйЬлЬ
ймдлгуйЬак: Ю Ьдлжву [33m#1000[37m ЯШ йШк зсЬа бШлЬмЯЬхШд йлж гудмгШ 1000.!)
!0l
!W[33mT[37mhread:    !iАбжвжмЯхШ ЫаШвцЪжм. Амлу Ю Ьдлжву йШк ЬгнШдхЭЬа
тдШ ШбцгШ гЬджч, гЬ лЮд ЩжуЯЬаШ лжм жзжхжм гзжиЬхлЬ дШ бадЮЯЬхлЬ йлж
зижЮЪжчгЬдж у ЬзцгЬдж гудмгШ лЮк ймЭулЮйЮк. ЛзжиЬхлЬ ЬзхйЮк дШ зслЬ йлж
гудмгШ зижк лж жзжхж ШзШдлс лж литожд гудмгШ.!)
!0l
!W[33mQ[37muickscan: !iДЫщ ЯШ ЩиЬхлЬ бсзжаЬк ЬаЫабтк Ьдлжвтк ЪаШ лЮд ЪиуЪжиЮ
ШдходЬмйЮ. ЛзжиЬхлЬ дШ бадЮЯЬхлЬ йлж ЬзцгЬдж у зижЮЪжчгЬдж club, дШ ШнШаитйЬлЬ лж
литожд club Шзц лЮд вхйлШ ЪиуЪжиЮк ШдходЬмйЮк, бШа сввШ.!)
!0l
!W[33mE[37mmail:     !iСоЮгШлхЭЬлЬ ШзсдлЮйЮ зижк Шмлц лж гудмгШ. Ж ШзсдлЮйЮ ЯШ йлШвЬх рк
зижйрзабц гудмгШ йлж ШзжйлжвтШ лжм гЮдчгШлжк.!)
!W[33mR[37meply:     !iГЮгажмиЪЬхлШа ЫЮгцйаж гудмгШ-ШзсдлЮйЮ зижк лж литожд гудмгШ.!)
!0l
[0;1m} T Quickscan, help about reading messages, version 1


RQSRMNU2 {[0;1m
[[33mN[37m]ext . . . . . . . ДзцгЬдж гудмгШ   [[33mP[37m]revious . . . ПижЮЪжчгЬдж гудмгШ
[[33mC[37m]lear . . . .  ГаШЪиШну гЮдчгШлжк   [[33mM[37m]odify  . . . .  АввШЪу гЮдчгШлжк
[[33mE[37m]mail reply  . Пижйрзабу ШзсдлЮйЮ   [[33mR[37m]eply  . . . . . . . . . АзсдлЮйЮ
[[33mT[37m]hread  . . .  АбжвжмЯхШ ЫаШвцЪжм   [[33mQ[37m]uickscan . . . ВиуЪжиЮ ШдходЬмйЮ
e[[33mX[37m]it  . . . . . . . . . .  ДежЫжк

Ж ЬзавжЪу йШк ([33m?[37m ЪаШ ЩжуЯЬаШ); } T Quickscan, choices after reading message


RQSRMNU2H {[0;1m

!JЛзжиЬхлЬ дШ ЫщйЬлЬ лак Ьеук Ьдлжвтк йЬ Шмлц лж йЮгЬхж:!)

!W[33mN[37mext:     !iЛЬлШнтиЬйлЬ йлж ЬзцгЬдж гудмгШ.
ЛзжиЬхлЬ дШ оиЮйагжзжауйЬлЬ Шмлу лЮд Ьдлжву ЪаШ тдШ ЬхЫжк Шзвук ШдходЬмйЮк лрд гЮдмгслрд.
ГщйлЬ зжввтк нжитк лЮд Ьдлжву N рк йчдлгЮйЮ, бШа лж йчйлЮгШ ЯШ зижориуйЬа ЬгнШдхЭждлск йШк
лак ЬзабЬнШвхЫЬк (headers) лрд гЮдмгслрд зжм зЬидсЬа. Длйа, гЬ лЮд Ьдлжву [33mNNNN[37m,
Ю ЩсйЮ ЯШ йШк ЫЬхеЬа лак ЬзабЬнШвхЫЬк лрд ЬзцгЬдрд лЬййсирд гЮдмгслрд, бШа ЯШ йлШгШлуйЬа йлж лЬвЬмлШхж.!)
!0l
!W[33mP[37mrevious: !iЛЬлШнтиЬйлЬ йлж зижЮЪжчгЬдж гудмгШ. КЬалжмиЪЬх цзрк ШбиаЩщк бШа Ю зижЮЪжчгЬдЮ Ьдлжву.!)
!0l
!W[33m#[37m:        !iТж йчйлЮгШ ЯШ йШк ЭЮлуйЬа тдШд ШиаЯгц гЮдчгШлжк йлж жзжхж ЯШ гЬлШЩЬхлЬ.
Ад лж гудмгШ ЫЬд ЩиЬЯЬх, ЯШ лжзжЯЬлЮЯЬхлЬ йлж бждладцлЬиж гудмгШ. ЛзжиЬхлЬ бШа ЬЫщ дШ оиЮйагжзжауйЬлЬ
ймдлгуйЬак: Ю Ьдлжву [33m#1000[37m ЯШ йШк зсЬа бШлЬмЯЬхШд йлж гудмгШ 1000.!)
!0l
!W[33mM[37modify:   !iТж гудмгШ тоЬа йлШвЬх Шзц Ьйск. ДоЬлЬ лж ЫабШхргШ дШ ШввсеЬлЬ лШ зЬиаЬоцгЬдс лжм.
Амлу Ю Ьдлжву йШк ЬзалитзЬа дШ бсдЬлЬ ШбиаЩщк Шмлц.!)
!0l
!W[33mC[37mlear:    !iТж гудмгШ тоЬа йлШвЬх Шзц Ьйск. ЛЬ Шмлу лЮд Ьдлжву лж ЫаШЪиснЬлЬ Шзц лж club @CLUB@.
ГЬд ЯШ мзсиеЬа бШггхШ ЬищлЮйЮ ЬзаЩЬЩШхрйЮк.!)
!0l
!W[33mT[37mhread:   !iАбжвжмЯхШ ЫаШвцЪжм. Амлу Ю Ьдлжву йШк ЬгнШдхЭЬа
тдШ ШбцгШ гЬджч, гЬ лЮд ЩжуЯЬаШ лжм жзжхжм гзжиЬхлЬ дШ бадЮЯЬхлЬ йлж
зижЮЪжчгЬдж у ЬзцгЬдж гудмгШ лЮк ймЭулЮйЮк. ЛзжиЬхлЬ ЬзхйЮк дШ зслЬ йлж
гудмгШ зижк лж жзжхж ШзШдлс лж литожд гудмгШ.!)
!W[33mQ[37muickscan: !iДЫщ ЯШ ЩиЬхлЬ бсзжаЬк ЬаЫабтк Ьдлжвтк ЪаШ лЮд ЪиуЪжиЮ
ШдходЬмйЮ. ЛзжиЬхлЬ дШ бадЮЯЬхлЬ йлж ЬзцгЬдж у зижЮЪжчгЬдж club, дШ ШнШаитйЬлЬ лж
литожд club Шзц лЮд вхйлШ ЪиуЪжиЮк ШдходЬмйЮк, бШа сввШ.!)
!0l
!0l
!W[33mE[37mmail:    !iСоЮгШлхЭЬлЬ ШзсдлЮйЮ зижк Шмлц лж гудмгШ. Ж ШзсдлЮйЮ ЯШ йлШвЬх рк
зижйрзабц гудмгШ йлж ШзжйлжвтШ лжм гЮдчгШлжк.!)
!0l
!W[33mR[37meply:    !iГЮгажмиЪЬхлШа ЫЮгцйаж гудмгШ-ШзсдлЮйЮ зижк лж литожд гудмгШ.!)
!0l
[0;1m} T Quickscan, help about reading messages, version 2


RQSRMNU3 {[0;1m
[[33mN[37m]ext  . . . . . .  ДзцгЬдж гудмгШ   [[33mP[37m]revious . . . ПижЮЪжчгЬдж гудмгШ
[[33mE[37m]mail reply  . Пижйрзабу ШзсдлЮйЮ   [[33mR[37m]eply . . . . . . . . .  АзсдлЮйЮ
[[33mT[37m]hread  . . .  АбжвжмЯхШ ЫаШвцЪжм   [[33mS[37m]IGop menu . . . Ддлжвтк жиЪШдрлу
[[33mQ[37m]uickscan . . . ВиуЪжиЮ ШдходЬмйЮ   e[[33mX[37m]it . . . . . . . . . . . ДежЫжк

Ж ЬзавжЪу йШк ([33m?[37m ЪаШ ЩжуЯЬаШ); } T Quickscan, choices after reading message


RQSRMNU3H {[0;1m

!JЛзжиЬхлЬ дШ ЫщйЬлЬ лак Ьеук Ьдлжвтк йЬ Шмлц лж йЮгЬхж:!)

!W[33mN[37mext:     !iЛЬлШнтиЬйлЬ йлж ЬзцгЬдж гудмгШ.
ЛзжиЬхлЬ дШ оиЮйагжзжауйЬлЬ Шмлу лЮд Ьдлжву ЪаШ тдШ ЬхЫжк Шзвук ШдходЬмйЮк лрд гЮдмгслрд.
ГщйлЬ зжввтк нжитк лЮд Ьдлжву N рк йчдлгЮйЮ, бШа лж йчйлЮгШ ЯШ зижориуйЬа ЬгнШдхЭждлск йШк
лак ЬзабЬнШвхЫЬк (headers) лрд гЮдмгслрд зжм зЬидсЬа. Длйа, гЬ лЮд Ьдлжву [33mNNNN[37m,
Ю ЩсйЮ ЯШ йШк ЫЬхеЬа лак ЬзабЬнШвхЫЬк лрд ЬзцгЬдрд лЬййсирд гЮдмгслрд, бШа ЯШ йлШгШлуйЬа йлж лЬвЬмлШхж.!)
!0l
!W[33mP[37mrevious: !iЛЬлШнтиЬйлЬ йлж зижЮЪжчгЬдж гудмгШ. КЬалжмиЪЬх цзрк ШбиаЩщк бШа Ю зижЮЪжчгЬдЮ Ьдлжву.!)
!0l
!W[33m#[37m:        !iТж йчйлЮгШ ЯШ йШк ЭЮлуйЬа тдШд ШиаЯгц гЮдчгШлжк йлж жзжхж ЯШ гЬлШЩЬхлЬ.
Ад лж гудмгШ ЫЬд ЩиЬЯЬх, ЯШ лжзжЯЬлЮЯЬхлЬ йлж бждладцлЬиж гудмгШ. ЛзжиЬхлЬ бШа ЬЫщ дШ оиЮйагжзжауйЬлЬ
ймдлгуйЬак: Ю Ьдлжву [33m#1000[37m ЯШ йШк зсЬа бШлЬмЯЬхШд йлж гудмгШ 1000.!)
!0l
!W[33mT[37mhread:   !iАбжвжмЯхШ ЫаШвцЪжм. Амлу Ю Ьдлжву йШк ЬгнШдхЭЬа
тдШ ШбцгШ гЬджч, гЬ лЮд ЩжуЯЬаШ лжм жзжхжм гзжиЬхлЬ дШ бадЮЯЬхлЬ йлж
зижЮЪжчгЬдж у ЬзцгЬдж гудмгШ лЮк ймЭулЮйЮк. ЛзжиЬхлЬ ЬзхйЮк дШ зслЬ йлж
гудмгШ зижк лж жзжхж ШзШдлс лж литожд гудмгШ.!)
!0l
!W[33mQ[37muickscan: !iДЫщ ЯШ ЩиЬхлЬ бсзжаЬк ЬаЫабтк Ьдлжвтк ЪаШ лЮд ЪиуЪжиЮ
ШдходЬмйЮ. ЛзжиЬхлЬ дШ бадЮЯЬхлЬ йлж ЬзцгЬдж у зижЮЪжчгЬдж club, дШ ШнШаитйЬлЬ лж
литожд club Шзц лЮд вхйлШ ЪиуЪжиЮк ШдходЬмйЮк, бШа сввШ.!)
!0l
!W[33mE[37mmail:    !iСоЮгШлхЭЬлЬ ШзсдлЮйЮ зижк Шмлц лж гудмгШ. Ж ШзсдлЮйЮ ЯШ йлШвЬх рк
зижйрзабц гудмгШ йлж ШзжйлжвтШ лжм гЮдчгШлжк.!)
!W[33mR[37meply:    !iГЮгажмиЪЬхлШа ЫЮгцйаж гудмгШ-ШзсдлЮйЮ зижк лж литожд гудмгШ.!)
!0l
!W[33mS[37mIGop:    !iЛЬлШнтиЬйлЬ йлж гЬджч жиЪШдрлу лжм club @CLUB@. ДбЬх гзжиЬхлЬ дШ
ШдлаЪиспЬлЬ, дШ зижрЮЯуйЬлЬ, дШ ЫаШЪиспЬлЬ бШа дШ гЬлШЩсввЬлЬ гЮдчгШлШ, бШа сввШ. ВаШ зЬиаййцлЬиЬк звЮижнжихЬк
гзЬхлЬ йлж гЬджч бШа ЭЮлуйлЬ ЩжуЯЬаШ.!)
!0l
[0;1m} T Quickscan, help about reading messages, version 3


QSMMNU {[0;1m
Ддлжвтк ЪиуЪжиЮк ШдходЬмйЮк:

[[33mN[37m]ext club . . . . .  ДзцгЬдж club   [[33mP[37m]revious club  . ПижЮЪжчгЬдж club
[[33mR[37m]emove club . . . . АнШхиЬйЮ club   [[33mB[37m]ookmark  . . . . . СЬваЫжЫЬхблЮк
[[33mC[37m]atch up . . Ттвжк ШдсЪдрйЮк club   [[33mS[37m]elect club  . . . . ДзавжЪу club
e[[33mX[37m]it  . . . . . . . . . .  ДежЫжк

Ж ЬзавжЪу йШк ([33m?[37m ЪаШ ЩжуЯЬаШ); } T Quickscan menu


QWMNUR {[0;1;31m
!JКмзсгШа, Шмлу Ю ЬзавжЪу ЫЬд ЬхдШа ЫмдШлу.!)
[0;1m} T Quickscan menu, invalid selection


QSMNUH {[0;1m

!JЛзжиЬхлЬ дШ ЫщйЬлЬ лак Ьеук Ьдлжвтк йЬ Шмлц лж йЮгЬхж:!)

!W[33mN[37mext club:     !iЛЬлШнтиЬйлЬ йлж ЬзцгЬдж club лЮк ЪиуЪжиЮк ШдходЬмйук йШк.
ОйШ гЮдчгШлШ ЫЬд тоЬлЬ ШбцгШ ЫаШЩсйЬа йЬ Шмлц лж club зШиШгтджмд ШЫасЩШйлШ бШа ЯШ йШк зижйнЬиЯжчд
ЪаШ ШдсЪдрйЮ йлЮд ЬзцгЬдЮ ЪиуЪжиЮ ШдходЬмйЮ. Ад ЫЬд мзсиоЬа ЬзцгЬдж club, лцлЬ
Ю ЪиуЪжиЮ ШдходЬмйЮ йлШгШлсЬа ЬЫщ.!)
!0l
!W[33mP[37mrevious club: !iКЬалжмиЪЬх цзрк ШбиаЩщк бШа Ю зижЮЪжчгЬдЮ Ьдлжву, Шввс йШк
гЬлШнтиЬа йлж зижЮЪжчгЬдж club.!)
!0l
!W[33mR[37memove club:   !iАнШаиЬх лж литожд club Шзц лЮд вхйлШ ЪиуЪжиЮк ШдходЬмйук йШк.
ЛЬлШнтиЬйлЬ ШмлцгШлШ йлж ЬзцгЬдж club. ТШ дтШ гЮдчгШлШ лжм club ЫЬд ЯШ йШк зижйнтиждлШа
звтжд ЪаШ ШдсЪдрйЮ, Ьблцк ба Шд еШдШзижйЯтйЬлЬ лж club йлЮд вхйлШ ЪиуЪжиЮк ШдходЬмйук йШк,
гЬ лЮд Ьдлжву [33mCRQC[37m Шзц лж бЬдлиабц гЬджч лЮк ЩсйЮк.!)
!0l
!W[33mB[37mookmark:      !iЛЬ Шмлу лЮд Ьдлжву жихЭЬлЬ зжаж ЯШ ЯЬриЬхлШа лж лЬвЬмлШхж
ЫаШЩШйгтдж гудмгШ лжм club. Тж литожд гудмгШ бШа цвШ лШ ЬзцгЬдШ гЮдчгШлШ лжм club
ЯШ ЯЬриЮЯжчд гЮ ЫаШЩШйгтдШ бШа ЯШ йШк зижйнЬиЯжчд ЪаШ ШдсЪдрйЮ йлЮд ЬзцгЬдЮ ЪиуЪжиЮ ШдходЬмйЮ. Амлу
Ю Ьдлжву ЬхдШа оиуйагЮ Шд тоЬлЬ уЫЮ ЫаШЩсйЬа лж club, Шввс ЯтвЬлЬ дШ лж еШдШЫаШЩсйЬлЬ заж зижйЬблабс
ШиЪцлЬиШ.!)
!0l
!W[33mC[37match up:      !iОвШ лШ гЮдчгШлШ лжм club ЯЬрижчдлШа ШмлцгШлШ ЫаШЩШйгтдШ. ЛЬлШнтиЬйлЬ
йлж ЬзцгЬдж club.!)
!0l
!W[33mS[37melect club:   !iЛЬ Шмлу лЮд Ьдлжву гзжиЬхлЬ дШ гЬлШнЬиЯЬхлЬ йЬ тдШ сввж club ЫхдждлШк
Шзвщк лж цджгс лжм. Тж club ЫЬд ЬхдШа ШдсЪбЮ дШ зЬиавШгЩсдЬлШа йлЮд вхйлШ ЪиуЪжиЮк ШдходЬмйук
йШк.!)
!0l
[0;1m} T Quickscan menu, help


QSMBM {[0;1;32m
!JЙШвщк, лж гудмгШ [37m%d[32m ЯЬриЬхлШа лж зищлж гЮ ЫаШЩШйгтдж гудмгШ лжм
club [37m%s[32m.!)
[0;1m} T Quickscan menu, bookmark placed


QSMCU {[0;1;32m
!JЙШвщк, цвШ лШ гЮдчгШлШ лжм club [37m%s[32m ЯЬрижчдлШа ЫаШЩШйгтдШ.!)
[0;1m} T Quickscan menu, caught up


QSMRM {[0;1;32m
!JЙШвщк, лж club [37m%s[32m ШнШаиЬхлШа Шзц лЮд вхйлШ ЪиуЪжиЮк ШдходЬмйЮк.
Ад ЯтвЬлЬ дШ лж еШдШзижйЯтйЬлЬ, зитзЬа дШ оиЮйагжзжауйЬлЬ лЮд Ьдлжву
[33mCRQC[32m Шзц лж бЬдлиабц гЬджч лЮк ЩсйЮк ([33mRQC[32m Шзц лж
бЬдлиабц гЬджч лрд clubs).!)
[0;1m} T Quickscan menu, removed club from quickscan configuration


TLCNAX {[0;1;31m
!JКмзсгШа, лж ЬзхзЬЫц йШк ЫЬд ЬзалитзЬа дШ гзЬхлЬ йлж бШдсва лЮвЬймджгаващд
Шмлжч лжм club.!)
[0;1m} T Enter teleconferences, access denied


BLTNAX {[0;1;31m
!JКмзсгШа, лж ЬзхзЬЫц йШк ЫЬд ЬзалитзЬа дШ гзЬхлЬ йлж ШдШЪдрйлуиаж сиЯирд
Шмлжч лжм club.!)
[0;1m} T Enter bulletin reader, access denied
