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

DEFCLUB {/Acro} S 15 Default Club for users when first online

MODAXKEY {Key required to modify Club accesses: 128} N 0 129

MODCHKEY {Key required to modify Club charges: 128} N 0 129

MODHDKEY {Key required to modify Club banners/descriptions: 128} N 0 129

TLCPAG {TELE} S 15 Menuman page of Teleconferences

BLTPAG {BULLETINS} S 15 Menuman page of Bulletin reader


ADDNEW {Automatically add new clubs to all user's quickscans: YES} B




LEVEL3 {}


HISTCC {€¤«åš¨˜­¦ «¦¬ %s} S 50 Message history: carbon copy


HISTCP {€¤«åš¨˜­¦ ˜§æ %s} S 50 Message history: message copy


HISTFW {¨¦àŸãŸ¡œ ˜§æ %s} S 50 Message history: forward


HISTNM {Internet mail} S 50 Message history: netmail


HISTRRR {€§æ›œ ¥ ˜¤áš¤à©ª «¦¬ %s} S 50 Message history: return receipt


HISTREP {€§á¤«© ©«¦ %s} S 50 Message history: reply


HISTAFW {€¬«æ£˜« £œ«˜™å™˜© ˜§æ %s} S 50 Message history: autoforward


HISTDST {ƒ ˜¤œ££â¤¦} S 50 Message history: distributed


HISTOLR {Off-line} S 50 Message history: off-line


HISTNET {‹â©à › ¡«ç¦¬ ˜§æ %s} S 50 Message history: via network



TIMEOUT1 {
!J[0;1;33m…«¦ç£œ ©¬šš¤é£ š ˜ «¤ ¡˜Ÿ¬©«â¨©, ˜¢¢á «¦ ©ç©«£˜
˜¤˜›£ ¦¬¨šœå ¦¨ ©£â¤˜ ˜§æ «˜ ˜¨®œå˜ «¦¬ ¢æšà ©­á¢£˜«¦ª. ˆ©àª ®¨œ ˜©«œå ¤˜
§œ¨ £â¤œ«œ ¢åš¦ ˜¡æ£...!)
[0;1m} T bbsmail: timed out waiting for message number lock (1)


TIMEOUT2 {
!J[0;1;31m‘¬šš¤é£, ˜¢¢á  ¡˜«á©«˜© ¢áŸ¦¬ª ›œ¤ â®œ  › ¦¨ŸàŸœå ˜¡æ£˜.
† ˜§¦Ÿã¡œ¬© «¦¬ £¤ç£˜«¦ª £˜«˜ é¤œ«˜  ˜¤˜š¡˜©« ¡á.!)
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
‹¤¬£˜ «¦¬ ¤â¦¬ ®¨ã©« "%s".
} T Electronic Mail alert to Sysop of new-user mail


CLUBINFO {[0;1m
!J† @BBS@ â®œ  £ ˜ £œšá¢ ©¬¢¢¦šã [32m"œ › ¡é¤ §œ¨ ¦®é¤"[37m (clubs, SIGs
ã forums) §¦¬ ­ ¢¦¥œ¤¦ç¤ ©¬«ã©œ ª š ˜ æ,«  £§¦¨œå«œ ¤˜ ­˜¤«˜©«œå«œ. ‹ ˜
¡˜  ˜¬«ã œå¤˜   §¨é« ©˜ª ­¦¨á ©« ™á©, ©˜ª š¨á­¦¬£œ ˜¬«æ£˜«˜ ©œ æ¢˜ «˜
clubs.!)

!J‹§¦¨œå«œ ¤˜ ›œå«œ «˜ ¤â˜ £¤ç£˜«˜ æ¢à¤ «à¤ clubs §¦¬ â®œ«œ ©« ¢å©«˜
š¨ãš¦¨ª ˜¤å®¤œ¬©ãª ©˜ª (›¢˜›ã ˜¬«á ©«˜ ¦§¦å˜ â®œ«œ "œšš¨˜­œå") £œ
«¤ œ¤«¦¢ã [33mQ[37m ˜§æ «¦ ¡œ¤«¨ ¡æ £œ¤¦ç (ã [33m/GO CRQS[37m ˜§æ
¦§¦¬›ã§¦«œ ©« ™á©). €¤ Ÿâ¢œ«œ ¤˜ §¨¦©Ÿ˜­˜ ¨â©œ«œ clubs ©« ¢å©«˜ š¨ãš¦¨ª
˜¤å®¤œ¬©ª ("quickscan"), ›é©«œ [33mCRQC[37m ˜§æ «¦ ¡œ¤«¨ ¡æ £œ¤¦ç (ã
[33m/GO CRQC[37m ˜§æ ¦§¦¬›ã§¦«œ ©« ™á©).!)

!J‘œ ˜¬«ã « ©ç¤›œ©ã ©˜ª § Ÿ˜¤æ«˜«˜ ›œ¤ Ÿ˜ ›œå«œ ¤â˜ £¤ç£˜«˜, ˜¢¢á ˜§æ
˜ç¨ ¦ «¦ "quickscan" Ÿ˜ ©˜ª §˜¨¦¬© á©œ  æ¢˜ «˜ ¤â˜ £¤ç£˜«˜ æ¢à¤ «à¤ clubs
§¦¬ ©˜ª œ¤› ˜­â¨¦¬¤.!)
[0;1m} T User is new, created a fresh quickscan config with ALL clubs.


CHKNCLB {[s[0;1;35m‹ ˜ ©« š£ã §˜¨˜¡˜¢é, œ¨œ¬¤é «˜ clubs...}


NNEWCLB {[u[0;1m[K
[0;1m} T Clubs, no new messages found


NEWCLUB {[u[0;1m[K
!W[5mÛÛ[0;1m  !i“§á¨®¦¬¤ [5m¤â˜[0;1m £¤ç£˜«˜ š ˜ ©˜ª ©« ª œ › ¡âª §œ¨ ¦®âª
(clubs).!)
!0l[0;1m} T Clubs, new mail waiting alert


NEWMAIL {[0;1m
!W[5mÛÛ[0;1m  !i“§á¨®¦¬¤ [5m¤â˜[0;1m §¨¦©à§ ¡á £¤ç£˜«˜ ©«¦ ¢œ¡«¨¦¤ ¡æ «˜®¬›¨¦£œå¦ š ˜ ©˜ª.!)
!0l[0;1m} T E-Mail new private mail waiting alert


OLDMAIL {[0;1;32m
!W“§á¨®¦¬¤ §˜¢ á §¨¦©à§ ¡á £¤ç£˜«˜ ©«¦ ¢œ¡«¨¦¤ ¡æ «˜®¬›¨¦£œå¦ š ˜ ©˜ª.!)
[0;1m} T E-Mail old private mail waiting alert


HOW2READ {[0;1;32m
!W‚ ˜ ¤˜ «˜ › ˜™á©œ«œ, ›é©«œ [33mERT[32m
([[33mE[32m]mail [[33mR[32m]ead [[33mT[32m]o you)
˜§æ «¦ ¡œ¤«¨ ¡æ £œ¤¦ç.!)
[0;1m} T E-Mail post-alert recommendation


ASKRDNOW {[0;1m
!W‡â¢œ«œ ¤˜ «˜ › ˜™á©œ«œ «é¨˜; [[33mY[37m]yes=¤˜  / [[33mN[37m]o=æ® ) } T Ask if user wants to read E-mail now

ASKRDERR {[0;1;31m
Š¬§á£˜ , ˜¬«ã  œ§ ¢¦šã ›œ¤ œå¤˜  ›¬¤˜«ã.
[0;1m} T Invalid selection for ASKRDNOW

ASKRDDEF {[Enter=[33mN[37m]!) [0m} T Default answer to ASKRDNOW


NOENTRY {[0;1;31m
Š¬§á£˜ , ›œ¤ â®œ«œ §¨æ©™˜© ©«¦ †¢œ¡«¨¦¤ ¡æ ’˜®¬›¨¦£œå¦.
[0;1m} T User does not have access to the E-mail module


EMMNU {[2J[0m[47;1;37m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;30;47m¿ [40m
[47;1;37m ³  [0;47;30m               †¢œ¡«¨¦¤ ¡æ ’˜®¬›¨¦£œå¦                 [0;47;30m³ [40m
[47;1;37m ³  [0;47;30mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ  [0;47;30m³ [40m
[47;1;37m ³  [0;31;47mA[30mbout E-mail . . . . . . . . . .  ‚œ¤ ¡âª ¢¨¦­¦¨åœª  [30m³ [40m
[47;1;37m ³  [0;31;47mR[30mead your mail  . . . . . . . . .  €¤áš¤à© £¤¬£á«à¤  [30m³ [40m
[47;1;37m ³  [0;31;47mW[30mrite message  . . . . . . . . . . €§¦©«¦¢ã £¤ç£˜«¦ª  [30m³ [40m
[47;1;37m ³  [0;31;47mM[30modify message  . . . . . . . . . .  €¢¢˜šã £¤ç£˜«¦ª  [30m³ [40m
[47;1;37m ³  [0;31;47mP[30mreferences . . . . . . . . .  ¨¦©à§ ¡âª §¨¦« £ã©œ ª  [30m³ [40m
[47;1;37m ³  [0;31;47mD[30mistribution list  . . . . . Šå©«˜ › ˜¤¦£ãª £¤¬£á«à¤  [30m³ [40m
[47;1;37m ³                                                         [0;47;30m³ [40m
[47;1;37m ³ [0;30;47me[31mX[30mit  . . . . . . . . . . . . . . . . . . . . . „¥¦›¦ª  [30m³ [40m
[47;1;37m À[0;30;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0;1m

†¢œ¡«¨¦¤ ¡æ «˜®¬›¨¦£œå¦
˜¨˜¡˜¢é ›é©«œ «¤ œ§ ¢¦šã ©˜ª: [0m} T Electronic mail menu


SHEMMNU {[0;1m
†¢œ¡«¨¦¤ ¡æ «˜®¬›¨¦£œå¦
!Wƒé©«œ «¤ œ§ ¢¦šã ©˜ª ([33mA[37m,[33mR[37m,[33mW[37m,[33mM[37m,[33mP[37m,[33mD[37m,[33mX[37m š ˜ â¥¦›¦, ã [33m?[37m š ˜ «¦ £œ¤¦ç): !)[0m} T Electronic mail short menu


ERRSEL {[0;1;31m
Š¬§á£˜ , ›œ¤ ¬§á¨®œ   œ§ ¢¦šã "%c".
[0;1m} T Invalid option selection


NOAXES {[0;1;31m
Š¬§á£˜ , ›œ¤ â®œ«œ §¨æ©™˜© ©œ ˜¬«ã «¤ œ§ ¢¦šã.
[0;1;31m} T User has no access to chosen area


EMLEAVE {[0;1m
„¥¦›¦ª ˜§æ «¦ †¢œ¡«¨¦¤ ¡æ ’˜®¬›¨¦£œå¦.
} T Exiting from the Electronic Mail module


ABOUT {[0;1m

!J‹â©à «¦¬ ¢œ¡«¨¦¤ ¡¦ç «˜®¬›¨¦£œå¦¬ £§¦¨œå«œ ¤˜ ©«œå¢œ«œ ¡˜  ¤˜ › ˜™á©œ«œ
«¦§ ¡á ¡˜  §˜š¡æ©£ ˜ (Internet) £¤ç£˜«˜ ˜§æ ¡˜  §¨¦ª œ©áª.!)

!J€¤ ®¨© £¦§¦ œå«œ «¤ §œ¨ ¦®ã ˜¬«ã š ˜ §¨é« ­¦¨á, ›é©«œ «¤ œ§ ¢¦šã
[33mP[37m (Preferences, §¨¦« £ã©œ ª) š ˜ ¤˜ ¨¬Ÿ£å©œ«œ « ª ›¬¤˜«æ««œª «¦¬
˜¤˜š¤à©«¨å¦¬ £¤¬£á«à¤ ©ç£­à¤˜ £œ « ª §¨¦©à§ ¡âª ©˜ª §¨¦« £ã©œ ª.!)

!J‹§¦¨œå«œ ¤˜ › ˜™á©œ«œ £¤ç£˜«˜ (œ¤«¦¢ã [[33mR[37m]ead) ¡˜  ¤˜ ©«œå¢œ«œ
â¤˜ £ã¤¬£˜ ã £¤ç£˜«˜ ([[33mW[37m]rite).!)

!J‹§¦¨œå«œ œ§å©ª ¤˜ ˜¢¢á¥œ«œ «¦ ¡œå£œ¤¦ œ¤æª £¤ç£˜«æª ©˜ª (£œ
[[33mM[37m]odify), ã ¤˜ › ˜š¨á¯œ«œ â¤˜ £ã¤¬£˜. €¬«âª
¦  ›ç¦ œ¤«¦¢âª ¢œ «¦¬¨š¦ç¤ £æ¤¦ ©œ «¦§ ¡á £¤ç£˜«˜. ƒœ¤ £§¦¨œå«œ ¤˜
£œ«˜™á¢œ«œ ã ¤˜ › ˜š¨á¯œ«œ Internet £¤ç£˜«˜ §¦¬ â®¦¬¤ ã› ˜§¦©«˜¢œå.!)

!J’â¢¦ª, £œ «¤ œ¤«¦¢ã [[33mP[37m]references £§¦¨œå«œ ¤˜ ¨¬Ÿ£å©œ«œ « ª
§¨¦©à§ ¡âª ©˜ª §¨¦« £ã©œ ª, œ¤é £œ [[33mD[37m]istribution list â®œ«œ «¤
›¬¤˜«æ««˜ ¤˜ ¦¨å©œ«œ £å˜ ¢å©«˜ ˜§æ ®¨ã©«œª/› œ¬Ÿç¤©œ ª §¦¬ Ÿ˜
®¨© £¦§¦ œå«˜  š ˜ › ˜¤œ££â¤˜ £¤ç£˜«˜.!)

[0;1m} T About the email module


PMENU {[2J[0m[47;1;37m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;30;47m¿ [40m
[47;1;37m ³  [0;47;30m             ¨¦« £ã©œ ª †¢œ¡«¨¦¤ ¡¦ç ’˜®¬›¨¦£œå¦¬               [0;47;30m³ [40m
[47;1;37m ³  [0;47;30mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ  [0;47;30m³ [40m
[47;1;37m ³  [0;31;47m1[30m . . . .  €¬«æ£˜« £œ«˜™å™˜© £¤¬£á«à¤ ©œ ¡á§¦ ¦¤ á¢¢¦ ®¨ã©«  [30m³ [40m
[47;1;37m ³  [0;31;47m2[30m  . . . . . . . . .  „ ©˜šàšã (quoting) §¨¦š¦ç£œ¤¦¬ £¤ç£˜«¦ª  [30m³ [40m
[47;1;37m ³  [0;31;47m3[30m . . . . . „ ›¦§¦å© š ˜ ¤â˜ £¤ç£˜«˜ ˜£â©àª £œ«á «¤ ©ç¤›œ©  [30m³ [40m
[47;1;37m ³  [0;31;47m4[30m  . . . . . . . . . .  €¢¢˜šã §¨¦©à§ ¡ãª ¬§¦š¨˜­ãª (signature)  [30m³ [40m
[47;1;37m ³                                                                   [0;47;30m³ [40m
[47;1;37m ³ [0;30;47me[31mX[30mit  . . . . . . . . . . . . . . . . . . . . . . . . . . „¥¦›¦ª  [30m³ [40m
[47;1;37m À[0;30;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0;1m
[0;1m} T Preferences, menu


PMENUS {[0;1m
¨¦« £ã©œ ª †¢œ¡«¨¦¤ ¡¦ç ’˜®¬›¨¦£œå¦¬
!Wƒé©«œ «¤ œ§ ¢¦šã ©˜ª ([33m1[37m,[33m2[37m,[33m3[37m,[33m4[37m,[33mX[37m š ˜ â¥¦›¦, ã [33m?[37m š ˜ «¦ £œ¤¦ç): !)[0m} T Preferences, short menu


PQUEST1A {[0;1m

!Wƒé©«œ «¦ ¯œ¬›é¤¬£¦ «¦¬ ®¨ã©« š ˜ «¦¤ ¦§¦å¦ Ÿ˜ ¦¨å©œ«œ ˜¬«æ£˜«
£œ«˜™å™˜©.!) } T Preferences, question 1A, sysop access


PQUEST1IA {[0;1;32m
!J’˜ £¤ç£˜«˜ £œ«˜™ ™á¦¤«˜  ˜¬«æ£˜«˜ §¨¦ª [37m%s[32m.!)
[0;1m} T Preferences, autoforwarding information 1


PQUEST1IB {[0;1;32m
!J’˜ £¤ç£˜«˜ ›œ¤ £œ«˜™ ™á¦¤«˜  ˜¬«æ£˜«˜ ˜¬«ã «¤ ©« š£ã.!)
[0;1m} T Preferences, autoforwarding information 2


PQUEST1B {[0;1m

!J€¤ Ÿâ¢œ«œ, £§¦¨œå«œ ¤˜ ¦¨å©œ«œ «¦ ¯œ¬›é¤¬£¦ œ¤æª ®¨ã©« ©«¦¤ ¦§¦å¦ Ÿ˜
£œ«˜™ ™á¦¤«˜  ˜¬«æ£˜«˜ æ¢˜ «˜ £¤ç£˜«˜ §¨¦ª œ©áª. €¬«æ œå¤˜  ®¨ã© £¦ ©œ
§œ¨ §«é©œ ª §¦¬ ®¨œ áœ«˜  ¤˜ ˜§¦¬© á©œ«œ ˜§æ «¤ ™á© š ˜ £œšá¢¦ ®¨¦¤ ¡æ
› á©«£˜. ƒœ¤ £§¦¨œå«œ ¤˜ £œ«˜™ ™á©œ«œ «˜ £¤ç£˜«á ©˜ª £â©à Internet.!)

!J¨¦©¦®ã: ©œ §œ¨å§«à© ¡¬¡¢ ¡é¤ £œ«˜™ ™á©œà¤ (§® ¦ € £œ«˜™ ™áœ  ©«¦¤ 
¡˜  ¦  ©«¦¤ €), «¦ ©ç©«£˜ Ÿ˜ ©«˜£˜«ã©œ  «¤ £œ«˜™å™˜© ¡˜  Ÿ˜ §˜¨˜›é©œ  «¦
£ã¤¬£˜ ©«¦¤ ˜¨® ¡æ «¦¬ §˜¨˜¢ã§«.!)

!Wƒé©«œ «¦ ¯œ¬›é¤¬£¦ «¦¬ ®¨ã©«, ã [33mEnter[37m š ˜ ¤˜ ˜§œ¤œ¨š¦§¦ ã©œ«œ «¤
˜¬«æ£˜« £œ«˜™å™˜©!) } T Preferences, question 1B


PQUEST1D {[Enter=[33m%s[37m] [0m} T Preferences, default value for PQUEST1A


PQUEST1N {[0;1;32m

!JŠ¬§á£˜ , £æ¤¦ ¦ ®œ ¨ ©«ãª ©¬©«ã£˜«¦ª £§¦¨œå ¤˜ ¦¨å©œ  ˜¬«æ£˜«
£œ«˜™å™˜©. ˜¨˜¡˜¢¦ç£œ ©«œå¢«œ £ã¤¬£˜ §¨¦ª [37mSysop[32m £œ «¦ ¯œ¬›é¤¬£æ
©˜ª ¡˜  «¦ ¯œ¬›é¤¬£¦ ©«¦ ¦§¦å¦ Ÿâ¢œ«œ ¤˜ £œ«˜™ ™áœ«œ «˜ £¤ç£˜«á ©˜ª.!)
[0;1m} T Preferences, question 1, no access



PQUEST1U {[0;1;31m
!JŠ¬§á£˜ , ˜¬«æª ¦ ®¨ã©«ª ›œ¤ ¬§á¨®œ  ©«¦ ©ç©«£˜.!)
[0;1m} T Preferences, question 1, unknown user


PQUEST1O {[0;1;32m
!J‰˜¢éª, ©«¦ œ¥ãª æ¢˜ «˜ £¤ç£˜«˜ Ÿ˜ £œ«˜™ ™á¦¤«˜  ©«¦ £â¢¦ª [37m%s[32m.!)
[0;1m} T Preferences, question 1, autoforwarding set


PQUEST1Y {[0;1;32m
!J‰˜¢éª, ©«¦ œ¥ãª «˜ £¤ç£˜«á ›œ¤ Ÿ˜ £œ«˜™ ™á¦¤«˜ .!)
[0;1m} T Preferences, question 1, autoforwarding disabled


PQUEST2 {[0;1m

!J«˜¤ ˜§˜¤«á«œ ©œ â¤˜ £ã¤¬£˜, §¦¢¢âª ­¦¨âª Ÿ˜ Ÿâ¢œ«œ ¤˜ œ ©ášœ«œ
(quote) £â¨¦ª «¦¬ §¨¦š¦ç£œ¤¦¬ £¤ç£˜«¦ª. „›é £§¦¨œå«œ ¤˜ ¨¬Ÿ£å©œ«œ ˜¤
Ÿâ¢œ«œ ¤˜ ©¬£™˜å¤œ  ˜¬«æ.   œ¥ãª œ§ ¢¦šâª œå¤˜  ›¬¤˜«âª:!)

  [33m1[37m . .  ’¦ £ã¤¬£˜ ©«¦ ¦§¦å¦ ˜§˜¤«á«œ ›œ¤ Ÿ˜ œ ©ášœ«˜  ©«¤ ˜§á¤«©.
  [33m2[37m  . . . . . . . . . . . . .  ’¦ £ã¤¬£˜ Ÿ˜ œ ©ášœ«˜  ©«¤ ˜§á¤«©.
  [33m3[37m . . . . . ’¦ ©ç©«£˜ Ÿ˜ ©˜ª ¨à«áœ  ˜¤ Ÿâ¢œ«œ ¤˜ šå¤œ   œ ©˜šàšã.

[0;1m} T Preferences, question 2


PQUEST2S {[0;1m
!Wƒé©«œ «¤ œ§ ¢¦šã ©˜ª ([33m1[37m,[33m2[37m,[33m3[37m, ã [33mX[37m š ˜ ˜§¦Ÿã¡œ¬© ¡˜  â¥¦›¦):!) [0m} T Preferences, question 2, short menu


PQUEST2R {[0;1;31m
Š¬§á£˜ , ›œ¤ ¬§á¨®œ  ˜¬«ã  œ§ ¢¦šã.
[0;1m} T Preferences, question 2, bad option



PQUEST3 {[0;1m

!J€£â©àª ˜­¦ç ©¬¤›œŸœå«œ,  ™á© ©˜ª œ¤£œ¨é¤œ  š ˜ «¬®æ¤ ¤â˜
£¤ç£˜«˜ §¨¦ª œ©áª. €¤ Ÿâ¢œ«œ, £§¦¨œå«œ ¤˜ › ˜™á©œ«œ «˜ ¤â˜ £¤ç£˜«á ©˜ª
œ¡œå¤ «¤ ©« š£ã, ã ¤˜ ©¬¤›œŸœå«œ ¡˜¤¦¤ ¡á ©«¤ ™á©. „®œ«œ « ª œ¥ãª
œ§ ¢¦šâª:!)

  [33m1[37m . . . . ’¦ ©ç©«£˜ ˜§¢éª ©˜ª œ¤£œ¨é¤œ  š ˜ «¬®æ¤ ¤â˜ £¤ç£˜«˜.
  [33m2[37m  . . . . . .  €¤ ¬§á¨®¦¬¤ ¤â˜ £¤ç£˜«˜, Ÿ˜ «˜ › ˜™á©œ«œ ˜£â©àª.
  [33m3[37m . .  ’¦ ©ç©«£˜ Ÿ˜ ©˜ª ¨à«áœ  ˜¤ Ÿâ¢œ«œ ¤˜ «˜ › ˜™á©œ«œ ˜£â©àª.

[0;1m} T Preferences, question 3


PQUEST3S {[0;1m
!Wƒé©«œ «¤ œ§ ¢¦šã ©˜ª ([33m1[37m,[33m2[37m,[33m3[37m, ã [33mX[37m š ˜ ˜§¦Ÿã¡œ¬© ¡˜  â¥¦›¦):!) [0m} T Preferences, question 3, short menu


PQUEST3R {[0;1;31m
Š¬§á£˜ , ›œ¤ ¬§á¨®œ  ˜¬«ã  œ§ ¢¦šã.
[0;1m} T Preferences, question 3, bad option


NOAXSIG {[0;1;31m
!JŠ¬§á£˜ , «¦ œ§å§œ›¦ §¨æ©™˜©ãª ©˜ª ›œ¤ œ§ «¨â§œ  «¤ ˜¢¢˜šã «ª ¬§¦š¨˜­ãª ©˜ª.!)
[0;1m} T Preferences, access to signature editor denied


CRDSNG {˜} T Credits, singular form
CRDPLR {œª} T Credits, plural form


NOCRSIG {[0;1;31m
!JŠ¬§á£˜ , ˜¢¢á ›œ¤ â®œ«œ ˜¨¡œ«âª £¦¤á›œª š ˜ ¤˜ ˜¢¢á¥œ«œ «¤ ¬§¦š¨˜­ã ©˜ª.
† ˜¢¢˜šã ¬§¦š¨˜­ãª ®¨œé¤œ«˜  [37m%d[31m £¦¤á›%s.!)
[0;1m} T Preferences, not enough credits to change signature


SIGCCAN {[0;1;33m
!J† › ˜› ¡˜©å˜ ˜¡¬¨éŸ¡œ. † ¬§¦š¨˜­ã ©˜ª ›œ¤ á¢¢˜¥œ.!)
[0;1m} T Preferences, signature not changed


LINSNG {ã} T Lines, singular form
LINPLR {âª} T Lines, plural form


SIGLIN {[0;1;33m
!J† ¬§¦š¨˜­ã ©˜ª ã«˜¤ £œš˜¢ç«œ¨ ˜§æ [37m%d[33m š¨˜££%s.   œ§ §¢â¦¤ š¨˜££âª ¡æ§¡˜¤.!)
[0;1m} T Preferences, signature truncated


SIGOK {[0;1;32m
!J† ¬§¦š¨˜­ã ©˜ª œš¡˜«˜©«áŸ¡œ, ¡˜  ®¨œàŸã¡˜«œ [37m%d[32m £¦¤á›%s.!)
[0;1m} T signature installed, you have been charged


OPONLY {[0;1;33m
!J‘¬šš¤é£, «¦ œ§å§œ›¦ §¨æ©™˜©ãª ©˜ª ›œ¤ œ§ «¨â§œ  ¤˜ š¨á¯œ«œ £ã¤¬£˜ §˜¨á
£æ¤¦ [37m§¨¦ª «¦¤ •œ ¨ ©«ã ‘¬©«ã£˜«¦ª[33m (Sysop). €¤ ›œ¤ Ÿâ¢œ«œ ¤˜ ©«œå¢œ«œ £ã¤¬£˜
§¨¦ª «¦¤ [37mSysop[33m, ›é©«œ X «é¨˜.!)
[0;1m} T Write email: can only send email to Sysop


WENCRDS {[0;1;31m
!Jƒœ¤ â®œ«œ ˜¨¡œ«âª £¦¤á›œª ®¨ã©ª š ˜ ¤˜ ©«œå¢œ«œ £¤ç£˜«˜ ¢œ¡«¨¦¤ ¡¦ç
«˜®¬›¨¦£œå¦¬. ‹§¦¨œå«œ ¤˜ ˜­ã©œ«œ £ã¤¬£˜ [5m£æ¤¦[0;1;31m ©«¦¤
•œ ¨ ©«ã ‘¬©«ã£˜«¦ª (Sysop).!)
[0;1m
!J€¤ ›œ¤ Ÿâ¢œ«œ ¤˜ ˜­ã©œ«œ £ã¤¬£˜, ›é©«œ e[[33mX[0;1m~]it ©«¤ œ§æ£œ¤ œ¨é«©.!)
} T Write email: not enough credits


WEWHO {[0;1m
‚¨á¯«œ ¯œ¬›é¤¬£¦ ã club §¦¬ Ÿ˜ ©«œå¢œ«œ «¦ £ã¤¬£˜
([33m?[37m š ˜ ™¦ãŸœ ˜) [Enter=Sysop]: [0m} T Write email: get recipient of message


WEWHOC {[0;1m
‚¨á¯«œ ¯œ¬›é¤¬£¦ ã club §¦¬ Ÿ˜ ˜¤« š¨á¯œ«œ «¦ £ã¤¬£˜
([33m?[37m š ˜ ™¦ãŸœ ˜) [Enter=Sysop]: [0m} T Write email: get recipient of copied message


WEUNKID {[0;1;31m
!JŠ¬§á£˜ , ˜¬«æ «¦ ¯œ¬›é¤¬£¦ ›œ¤ ¬§á¨®œ .!)
[0;1m} T Write email: unknown user ID


WEHELP1 {[0;1m

!J‹§¦¨œå«œ ¤˜ ›é©œ«œ «¦¤ §˜¨˜¢ã§« «¦¬ £¤ç£˜«æª ©˜ª àª œ¥ãª:!)

1. !i!Jƒé©«œ «¦ ¯œ¬›é¤¬£¦ œ¤æª £â¢¦¬ª. ‹§¦¨œå«œ ¤˜ ›é©œ«œ «¦ ¯œ¬›é¤¬£¦
¦¢æ¡¢¨¦, ã ¤˜ š¨á¯œ«œ «¦¬¢á® ©«¦¤ «˜ §¨é«˜ «¨å˜ š¨á££˜«˜. ’¦ ©ç©«£˜ Ÿ˜
˜¤˜¢á™œ  «˜ ¬§æ¢¦ §˜.!)
!0l
2. !i!Jƒé©«œ [33mEnter[37m š ˜ ¤˜ ©«œå¢œ«œ £ã¤¬£˜ ©«¦¤ Sysop.
ƒœ¤ Ÿ˜ ®¨œàŸœå«œ š ˜ ˜¬«æ «¦ £ã¤¬£˜.!)
!0l
3. !i!Jƒé©«œ £å˜ Internet › œçŸ¬¤© (user@@host.domain) š ˜ ¤˜ ©«œå¢œ«œ
£ã¤¬£˜ ©«¦ ›å¡«¬¦. † œ§ §¢â¦¤ ®¨âà© š '˜¬«ã «¤ ¬§¨œ©å˜ œå¤˜ 
[32m%d £¦¤á›%s[37m.!)
!0l
4. !i!Jƒé©«œ '/' ¡˜  «¦ æ¤¦£˜ œ¤æª Club š ˜ ¤˜ ©«œå¢œ«œ £ã¤¬£˜ §¨¦ª æ¢¦¬ª
©œ ˜¬«æ «¦ Club. † ®¨âà© š '˜¬«ã «¤ ¬§¨œ©å˜ œ¥˜¨«á«˜  ˜§æ «¦ Club §¦¬ Ÿ˜
¢á™œ  «¦ £ã¤¬£á ©˜ª. ‚ ˜ §œ¨ ©©æ«œ¨œª §¢¨¦­¦¨åœª ˜§¦«˜¤Ÿœå«œ ©«¤ œ¤«¦¢ã
[33mI[37mnformation ˜§æ «¦ £œ¤¦ç «à¤ „ › ¡é¤ œ¨ ¦®é¤ (Clubs).!)
!0l
5. !i!J•¨© £¦§¦ ã©«œ «¦ ©®ã£˜ [33m/Club -User[37m š ˜ ¤˜ ©«œå¢œ«œ £ã¤¬£˜
©œ â¤˜ ©¬š¡œ¡¨ £â¤¦ ®¨ã©« User £â©˜ ©«¦ club Club. ‹œ [33m/Club -All[37m
©«â¢¤œ«œ «¦ £ã¤¬£˜ §¨¦ª æ¢¦¬ª «¦¬ª ®¨ã©«œª «¦¬ club Club, æ§àª ˜¡¨ ™éª ¡˜ 
©«¤ §˜¨˜§á¤à ©ç¤«˜¥ (4).!)
!0l
[0;1m} T Write email: help for unprivileged users


WEHELP2 {[0;1m6. !i!Jƒé©«œ «¦ æ¤¦£˜ £ ˜ª ¢å©«˜ª › ˜¤¦£ãª š ˜ ¤˜ ©«œå¢œ«œ
˜¤«åš¨˜­¦ «¦¬ £¤ç£˜«¦ª ©œ ¡áŸœ £â¢¦ª «ª ¢å©«˜ª. “§á¨®¦¬¤ ¦  œ¥ãª
¢å©«œª › ˜¤¦£ãª:!)
!0l
} T Write email: help on distribution lists, footer


WEHELP3 {      !%s
} T Write email: help on distribution lists


WEHELP4 {} T Write email: help on distribution lists, footer


WEFCAU {[0;1m
!W˜¨˜¡˜¢é ›é©«œ «¦ ¯œ¬›é¤¬£¦ œ¤æª £â¢¦¬ª, ã [33mALL[37m š ˜ æ¢¦¬ª:!) [0m} T Write email: forward/copy club/user question


WEFCAUR {[0;1;31m
!J€¬«æ «¦ ¯œ¬›é¤¬£¦ ›œ¤ ¬§á¨®œ . ˜¨˜¡˜¢é ¥˜¤˜›¦¡ £á©«œ, ã ›é©«œ [33mX[31m š ˜ â¥¦›¦.!)
[0;1m} T Write email: forward/copy club/user error


WERNNET {[0;1;31m
!JŠ¬§á£˜ , ›œ¤ â®œ«œ §¨æ©™˜© ©œ ˜¬«ã «¤ ¬§¨œ©å˜.!)
[0;1m} T Write email: access to netmail denied


WERNNET2 {[0;1;31m
!JŠ¬§á£˜ , ›œ¤ â®œ«œ ˜¨¡œ«æ ®¨æ¤¦ ®¨ã©ª š ˜ ¤˜ ®¨© £¦§¦ ã©œ«œ ˜¬«ã «¤
¬§¨œ©å˜.!)
[0;1m} T Write email: not enough credits to send netmail


WERLNEC {[0;1;31m
!JŠ¬§á£˜ , ›œ¤ â®œ«œ ˜¨¡œ«æ ®¨æ¤¦ ®¨ã©ª š ˜ ¤˜ ©¬¤œ®å©œ«œ «¤ › ˜¤¦£ã
«¦¬ £¤ç£˜«¦ª.!)
[0;1m} T Write email: not enough credits to continue distribution


WERNEC {[0;1;31m
!JŠ¬§á£˜ , ›œ¤ â®œ«œ ˜¨¡œ«æ ®¨æ¤¦ ®¨ã©ª š ˜ ¤˜ ©«œå¢œ«œ «¦ £ã¤¬£˜.!)
[0;1m} T Write email: not enough credits to send message


WERCLUB {[0;1;31m
!JŠ¬§á£˜ , «¦ œ§å§œ›¦ §¨æ©™˜©ãª ©˜ª ©«¦ club [37m%s[31m ›œ¤ ©˜ª
œ§ «¨â§œ  «¤ ˜§¦©«¦¢ã £¤¬£á«à¤.!)
[0;1m} T Write email: club message, access denied


MSGSNG {£ã¤¬£˜} T Messages, singular form
MSGPLR {£¤ç£˜«˜} T Messages, plural form


DISTBEG {[0;1;32m
!J„¡¡å¤© › ˜¤¦£ãª. ‹§¦¨œå«œ ¤˜ ©«˜£˜«ã©œ«œ «¤ › ˜¤¦£ã § â¦¤«˜ª
[33mEnter[32m.!)
[0;1m} T Write email: beginning of distribution


DISTINFO {[0;1;32m
!J’â¢¦ª › ˜¤¦£ãª £¤ç£˜«¦ª. ‘«œå¢˜«œ [37m%d[32m %s.!)
[0;1m} T Write email: distribution information


WECAN {[0;1;31m
!J€¡ç¨à© › ˜› ¡˜©å˜ª.!)
[0;1m} T Write email: distribution stoppep prematurely


EWRLERR {[0;1;31m
!J€š¤à©«¦ æ¤¦£˜ ¢å©«˜ª › ˜¤¦£ãª. ƒé©«œ [33m?[31m š ˜ ¤˜ ›œå«œ « ª
¬§á¨®¦¬©œª ¢å©«œª.!)
[0;1m} T Write email: unknown distribution list name


WERCPOK {[0;1;32m
!J˜¨˜¢ã§«ª «¦¬ £¤ç£˜«æª ©˜ª Ÿ˜ œå¤˜  «¦ £â¢¦ª [37m%s[32m.!)
[0;1m} T Write email: confirming recipient of message


WERCPOKN {[0;1;32m
!J’¦ £ã¤¬£á ©˜ª Ÿ˜ ©«˜¢œå £â©à Internet Mail ©«¤ › œçŸ¬¤© [37m%s[32m.!)
[0;1m} T Write email: confirming recipient of message, net mail


WERCPOKL {[0;1;32m
!J’¦ £ã¤¬£á ©˜ª Ÿ˜ › ˜¤œ£Ÿœå ©«˜ £â¢ «ª ¢å©«˜ª [37m%s[32m.!)
[0;1m} T Write email: confirming recipient of message, dist list


WERCPOKC {[0;1;32m
!J’¦ £ã¤¬£á ©˜ª Ÿ˜ ©«˜¢œå ©«¦ Club [37m%s[32m, §¨¦ª æ¢¦¬ª.!)
[0;1m} T Write email: confirming recipient of message, club message


WERCPOKU {[0;1;32m
!J’¦ £ã¤¬£á ©˜ª Ÿ˜ ©«˜¢œå ©«¦ Club [37m%s[32m, §¨¦ª [37m%s[32m.!)
[0;1m} T Write email: confirming recipient of message, club message to user


ASKSUBJ {[0;1m
!Jƒé©«œ «¦ Ÿâ£˜ «¦¬ £¤ç£˜«æª ©˜ª (63 ®˜¨˜¡«ã¨œª): !)[0m} T Asking for the subject of a message


CRDSING {˜} T 'Credits', singular form

CRDPLUR {œª} T 'Credits', plural form


WEATT {[0;1m
!W‡â¢œ«œ ¤˜ œ§ ©¬¤á¯œ«œ â¤˜ ˜¨®œå¦ ©œ ˜¬«æ «¦ £ã¤¬£˜;
(† ®¨âà© š ˜ ˜¬«ã «¤ ¬§¨œ©å˜ œå¤˜  [32m%d £¦¤á›%s[37m)
([[33m“[0;1m]es=¤˜  / [[33mN[0;1m]o=æ® ):!) [0m} T Write email: ask if file attachment required


WERRR {[0;1m
!W‡â¢œ«œ "˜§æ›œ ¥ §˜¨˜¢˜™ãª" æ«˜¤ ˜¬«æ «¦ £ã¤¬£˜ › ˜™˜©«œå;
(† ®¨âà© š ˜ ˜¬«ã «¤ ¬§¨œ©å˜ œå¤˜  [32m%d £¦¤á›%s[37m)
([[33mY[0;1m]es=¤˜  / [[33mN[0;1m]o=æ® ):!) [0m} T Write email: ask if return receipt required


WECC {[0;1m
!W‡â¢œ«œ ¤˜ ©«œå¢œ«œ ˜¤«åš¨˜­¦ ©œ á¢¢¦ ®¨ã©«;
(† ®¨âà© š ˜ ˜¬«ã «¤ ¬§¨œ©å˜ œå¤˜  [32m%d £¦¤á›%s[37m ˜¤á ˜¤«åš¨˜­¦)
([[33mY[0;1m]es=¤˜  / [[33mN[0;1m]o=æ® ):!) [0m} T Write email: ask if carbon copies required


WEQNCRD {[0;1;31m
!JŠ¬§á£˜ , ›œ¤ â®œ«œ §¢â¦¤ ˜¨¡œ«âª £¦¤á›œª ®¨ã©ª š ˜ ¤˜ «ã©œ«œ ˜¬«ã «¤
¬§¨œ©å˜.!)
[0;1m} T Write email: ran out of credits


WECCAN {[0;1;31m
!W˜¨˜¡˜¢é œ§ ™œ™˜ é©«œ æ«  Ÿâ¢œ«œ ¤˜ [37m®á©œ«œ[31m «¦ £ã¤¬£á ©˜ª.!)
[0;1m([[33mY[0;1m]es=¤˜  / [[33mN[0;1m]o=æ® ): [0m} T Write email: ask for confirmation before exiting


WECCND {} T Write email: default answer string for WECCAN


WERRSEL {[0;1;31m
!W˜¨˜¡˜¢é ›é©«œ [33mY[31m ã [33mN[31m.!)
[0;1m} T Write email: invalid answer to question


WEXFERR {[0;1;31m
!J’¦ ˜¨®œå¦ ©˜ª ®áŸ¡œ ¢æšà ¢áŸ¦¬ª œšš¨˜­ãª/˜¤áš¤à©ª. ˜¨˜¡˜¢¦ç£œ
œ ›¦§¦ ã©«œ «¦¤ ®œ ¨ ©«ã ©¬©«ã£˜«¦ª š ˜ « ª ©¬¤Ÿã¡œª §¦¬ ¦›ãš©˜¤ ©'˜¬«æ «¦
¢áŸ¦ª.!)
[0;1m} T Write email: I/O error, attachment was lost


WEXFER2 {[0;1;33m
!J€§¦©«œå¢˜«œ §á¤à ˜§æ â¤˜ ˜¨®œå¦. ‹æ¤¦ «¦ §¨é«¦ ˜¨®œå¦ Ÿ˜ œ§ ©¬¤˜­Ÿœå ©«¦
£ã¤¬£˜.!)
[0;1m} T Write email: >1 files uploaded; only first file will be attached


WENOATT {[0;1;33m
!J‰˜¢éª, «¦ £ã¤¬£˜ Ÿ˜ §˜¨˜£œå¤œ  ®à¨åª ©¬¤££â¤¦ ˜¨®œå¦.!)
[0;1m} T Write email: leaving message without an attached file


WEREEFN {[0;1;37m
’¨â®¦¤ æ¤¦£˜ ˜¨®œå¦¬: [32m%s[37m

‡â¢œ«œ ¤˜ ›é©œ«œ æ¤¦£˜ ©œ ˜¬«æ «¦ ˜¨®œå¦;

!J€¤ ˜§˜¤«ã©œ«œ [33mY[37mes (¤˜ ) ¡˜  ›é©œ«œ â¤˜ æ¤¦£˜ ˜¨®œå¦¬ (æ§àª §.®.
"FILENAME.EXT"), «æ«œ ˜¬«æ «¦ æ¤¦£˜ ˜¨®œå¦¬ Ÿ˜ ®¨© £¦§¦ Ÿœå ¡˜«á «¤ ¢ã¯
«¦¬. €¤ ˜§˜¤«ã©œ«œ [33mN[37mo (æ® ), «¦ «¨â®¦¤ æ¤¦£˜ «¦¬ ˜¨®œå¦¬ Ÿ˜
§˜¨˜£œå¤œ . (€¢¢á¦¤«˜ª «¦ æ¤¦£˜ «¦¬ ˜¨®œå¦¬ ›œ¤ ˜¢¢áœ«œ ‰€ˆ «¦ Ÿâ£˜
«¦¬ £¤ç£˜«¦ª)!)

!W‡â¢œ«œ ¤˜ ¥˜¤˜›é©œ«œ «¦ æ¤¦£˜ «¦¬ ˜¨®œå¦¬;!)
[0;1m([[33mY[0;1m]es=¤˜  / [[33mN[0;1m]o=æ® ): [0m} T Write email: change/enter filename?


WEFFN {[0;1m
Œâ¦ æ¤¦£˜ ˜¨®œå¦¬ (15 ®˜¨˜¡«ã¨œª): [0m} T Write email: reenter filename


WEFFNR {[0;1;31m
!J’¦ æ¤¦£˜ «¦¬ ˜¨®œå¦¬ §œ¨ â®œ  £ ˜§¦›œ¡«¦çª ®˜¨˜¡«ã¨œª. •˜¨˜¡«ã¨œª §¦¬ šå¤¦¤«˜ 
›œ¡«¦å œå¤˜  ®˜¨˜¡«ã¨œª «¦¬ ¢˜« ¤ ¡¦ç ˜¢­˜™ã«¦¬, ˜¨ Ÿ£¦å, ¡˜  «˜ œ¥ãª ©ç£™¦¢˜:
@ # % ^ ( ) - _ + = [ ] .!)
[0;1m} T Write email: bad characters in filename


WEDFFN {[0;1m
„¤«á¥œ , «¦ ˜¨®œå¦ ©˜ª Ÿ˜ ¦¤¦£áœ«˜  "[32m%s[37m".
’¦ Ÿâ£˜ «¦¬ £¤ç£˜«¦ª §˜¨˜£â¤œ  "[32m%s[37m".
[0;1m
} T Write email: displaying filename


WECONFS {[0;1;32m
„§ ™œ™˜ éŸ¡œ: «¦ £ã¤¬£˜ [37m%s/%d[32m ˜§¦Ÿ¡œç«¡œ.
[0;1m
} T Write email: message written to disk


WECONFC {[0;1;32m
!J„§ ™œ™˜ éŸ¡œ: «¦ £ã¤¬£˜ [37m%s/%d[32m ˜¤« š¨á­Ÿ¡œ ©«¦ [37m%s/%d[32m
¡˜  œ©«á¢ §¨¦ª [37m%s[32m.!)
[0;1m
} T Write email: message copied


WEALL {¢¦¬ª} T Write email: 'all' string


WECONFL {[0;1;32m!Jƒ ˜¤¦£ã: «¦ £ã¤¬£˜ [37m%d[32m œ©«á¢ §¨¦ª [37m%s[32m.!)
[0;1m} T Write email: message distributed


WELUNKU {[0;1;31m
!J€¤ç§˜¨¡«¦ª ®¨ã©«ª: [37m%s[31m.!)
[0;1m} T Write email: unknown user in distribution list


WENOTFD {[0;1m
!J’¦ £â¢¦ª [32m%s[37m œå¤˜  ©¬¤›œ›œ£â¤¦, ¡˜  œ ›¦§¦ ãŸ¡œ.!)
[0;1m
} T Write email: recipient is online and has been notified


WERNOT {[0;1m***

!J’¦ £â¢¦ª [32m%s[37m £æ¢ ª ©˜ª â©«œ ¢œ £ã¤¬£˜ £œ Ÿâ£˜ "[32m%s[37m".
‹§¦¨œå«œ ¤˜ «¦ › ˜™á©œ«œ ›å¤¦¤«˜ª ˜§æ «¦ ¡œ¤«¨ ¡æ £œ¤¦ç:!)

([33mE[37m)mail = ¢œ¡«¨¦¤ ¡æ «˜®¬›¨¦£œå¦
([33mR[37m)ead  = ˜¤áš¤à©
([33mT[37m)o    = §¨æª œ©áª

!J'H š¨á­¦¤«˜ª [33m/GO ERT[37m ˜§æ ¦§¦¬›ã§¦«œ ©«¤ ™á©.!)
[0;1m} T Write email: notification for recipient


WERNOTC {[0;1m***

!J’¦ £â¢¦ª [32m%s[37m £æ¢ ª ©˜ª ˜¤«âš¨˜¯œ £ã¤¬£˜ £œ Ÿâ£˜ "[32m%s[37m".
‹§¦¨œå«œ ¤˜ «¦ › ˜™á©œ«œ ›å¤¦¤«˜ª ˜§æ «¦ ¡œ¤«¨ ¡æ £œ¤¦ç:!)

([33mE[37m)mail = ¢œ¡«¨¦¤ ¡æ «˜®¬›¨¦£œå¦
([33mR[37m)ead  = ˜¤áš¤à©
([33mT[37m)o    = §¨æª œ©áª

!J'H š¨á­¦¤«˜ª [33m/GO ERT[37m ˜§æ ¦§¦¬›ã§¦«œ ©«¤ ™á©.!)
[0;1m} T Write email: notification for recipient, copied message


WERNOTCC {[0;1m***

!J’¦ £â¢¦ª [32m%s[37m £æ¢ ª ©˜ª ˜¤«âš¨˜¯œ ©«¦ club [32m%s[37m
£ã¤¬£˜ £œ Ÿâ£˜ "[32m%s[37m".!)
[0;1m} T Write email: notification for recipient, copied message (to club)


WERNOTFW {[0;1m***
!J’¦ £â¢¦ª [32m%s[37m £æ¢ ª ©˜ª §¨¦éŸ©œ ©«¦ club [32m%s[37m
£ã¤¬£˜ £œ Ÿâ£˜ "[32m%s[37m".!)
[0;1m} T Clubs: notification for recipient, forwarded message (to club)








RDWHAT {[0;1m
!W‡â¢œ«œ ¤˜ › ˜™á©«œ £¤ç£˜«˜ §¦¬ œå¤˜ :!)

[33m’[0;1mo  . . . . . . . . . . . . . . . . . . ¨æª œ©áª,
[33mP[0;1mrivate  . . .  §¨¦©à§ ¡á (œ¡«æª clubs) §¨æª œ©áª,
[33mF[0;1mrom . . . . . . . . . . . . . . . . . . €§æ œ©áª,

!Wƒé©«œ «¤ œ§ ¢¦šã ©˜ª:!) [0m} T Read mail submenu


RDWHATR {[0;1;31m
!WŠ¬§á£˜ , ›œ¤ ¬§á¨®œ  ˜¬«ã  œ§ ¢¦šã.!)
[0;1m} T Read mail, invalid selection


RDASKNO {[0;1m
!Jƒé©«œ «¦¤ ˜¨ Ÿ£æ £¤ç£˜«¦ª ˜§æ æ§¦¬ Ÿ˜ ˜¨®å©œ«œ, [[33mF[37m]irst
(¨é«¦) š ˜ «¦ §¨é«¦ ¬§á¨®¦¤ £ã¤¬£˜, [[33mL[37m]ast (’œ¢œ¬«˜å¦)
š ˜ «¦ «œ¢œ¬«˜å¦ £ã¤¬£˜, [33mEnter[37m š ˜ «¦ «¨â®¦¤ £ã¤¬£˜
([32m#%ld[37m), ã [33m?[0;1m š ˜ ™¦ãŸœ ˜.!)

!W€§æ §¦ ¦ £ã¤¬£˜ ¤˜ ¥œ¡ ¤ã©œ   ˜¤áš¤à©; !) [0m} T Read Mail, asking for message number


RDASKNOR {[0;1;31m
!WŠ¬§á£˜ , ›œ¤ ¬§á¨®œ  ˜¬«ã  œ§ ¢¦šã.!)
[0;1m} T Read mail, error while asking for message number


RDASKH {[0;1m
!J€¤ §˜«ã©œ«œ ˜§¢éª [33mEnter[37m, Ÿ˜ ˜¨®å©œ«œ ˜§æ «¦ §¨é«¦ ¤â¦ £ã¤¬£˜.
€¤ ›œ¤ ¬§á¨®¦¬¤ ¤â˜ £¤ç£˜«˜, «æ«œ  ˜¤áš¤à© Ÿ˜ ¥œ¡ ¤ã©œ  £œ «¦ «œ¢œ¬«˜å¦
˜§æ «˜ §˜¢ á. † «œ¢œå˜ ([33m.[37m) œå¤˜   ©¦›ç¤˜£ £œ «¦ [33mEnter[37m, 
˜¤ ®¨© £¦§¦ œå«œ ©¬¤«£ã©œ ª. ƒ¢˜›ã  œ¤«¦¢ã [33mERT.[37m ˜§æ «¦ ¡œ¤«¨ ¡æ
£œ¤¦ç ©£˜å¤œ  "á£œ© ˜¤áš¤à© æ¢à¤ «à¤ ¤âà¤ £¤¬£á«à¤ §¨¦ª œ©áª".!)

!Jƒå¤¦¤«˜ª [33mF[37m (First), Ÿ˜ ˜¨®å©œ«œ «¤ ˜¤áš¤à© ˜§æ «¦ §˜¢ æ«œ¨¦
› ˜Ÿâ© £¦ £ã¤¬£˜.!)

!Jƒå¤¦¤«˜ª [33mL[37m (Last), Ÿ˜ ˜¨®å©œ«œ «¤ ˜¤áš¤à© ˜§æ «¦ § ¦ §¨æ©­˜«¦
£ã¤¬£˜ §¦¬ š¨á­«¡œ.!)

!Jƒé©«œ [33mX[37m (eXit) ˜¤ Ÿâ¢œ«œ ¤˜ ™šœå«œ, ˜¢¢ éª ›é©«œ «¦¤ ˜¨ Ÿ£æ «¦¬
£¤ç£˜«¦ª ˜§¦ «¦ ¦§¦å¦ Ÿâ¢œ«œ ¤˜ ˜¨®å©œ«œ. €¤ ›œ¤ ¬§á¨®œ  £ã¤¬£˜ £œ ˜¬«æ¤ «¦¤
˜¨ Ÿ£æ «æ«œ Ÿ˜ ®¨© £¦§¦ Ÿœå «¦ §¨é«¦ £ã¤¬£˜ £œ ˜¨ Ÿ£æ £œš˜¢ç«œ¨¦ ˜§æ ˜¬«æ¤
§¦¬ ›é©˜«œ.!)
[0;1m} T Read Mail, help for RDASKNO


RDNOMSGT {[0;1;33m
!J‘¬šš¤é£, ›œ¤ ¬§á¨®¦¬¤ £¤ç£˜«˜ §¨æª œ©áª ©«¦ †¢œ¡«¨¦¤ ¡æ ’˜®¬›¨¦£œå¦.!)
[0;1m} T Read mail, no messages to you


RDNOMSGP {[0;1;33m
!J‘¬šš¤é£, ›œ¤ ¬§á¨®¦¬¤ §¨¦©à§ ¡á £¤ç£˜«˜ §¨æª œ©áª.!)
[0;1m} T Read Mail, no private messages to you


RDNOMSGF {[0;1;33m
!J‘¬šš¤é£, ›œ¤ ¬§á¨®¦¬¤ £¤ç£˜«˜ ˜§æ œ©áª ©«¦ †¢œ¡«¨¦¤ ¡æ ’˜®¬›¨¦£œå¦.!)
[0;1m} T Read mail, no messages from you


RDTRCLUB {[0;1;32m
!J„¨œ¬¤¦ç£œ š ˜ £¤ç£˜«˜ [37m§¨¦ª œ©áª[32m ©«˜ Clubs.!)
[0;1m} T Read mail, looking for matching messages in the clubs


RDMISS {[0;1m
’¦ £ã¤¬£˜ [32m%d[37m ›œ¤ ™¨âŸ¡œ. „§ ¢â®Ÿ¡œ «¦ §¢© â©«œ¨¦:
[0;1m} T Read Mail, message number not found


RDSCNM {[0;1m
[[33mN[37m]ext . . . . . . . „§æ£œ¤¦ £ã¤¬£˜   [[33mP[37m]revious . . . ¨¦š¦ç£œ¤¦ £ã¤¬£˜
[[33mR[37m]ead  . . . . . . . . .  €¤áš¤à©   [[33m#[37m] . . . . . . €¢£˜ ©œ á¢¢¦ £ã¤¬£˜
[[33mC[37m]lubs  . . . . ‹¤ç£˜«˜ ©«˜ Clubs   e[[33mX[37m]it . . . . . . . . . . . „¥¦›¦ª

† œ§ ¢¦šã ©˜ª ([33m?[37m š ˜ ™¦ãŸœ ˜); } T Read Mail, choices while scanning messages


RDSCNMH {[0;1m

!J‹§¦¨œå«œ ¤˜ ›é©œ«œ « ª œ¥ãª œ¤«¦¢âª ©œ ˜¬«æ «¦ ©£œå¦:!)

!W[33mN[37mext:     !i‹œ«˜­â¨œ©«œ ©«¦ œ§æ£œ¤¦ £ã¤¬£˜, ®à¨åª ¤˜ › ˜™á©œ«œ «¦ «¨â®¦¤.
‹§¦¨œå«œ ¤˜ ®¨© £¦§¦ ã©œ«œ ˜¬«ã «¤ œ¤«¦¢ã š ˜ â¤˜ œå›¦ª ˜§¢ãª ˜¤å®¤œ¬©ª «à¤ £¤¬£á«à¤.
ƒé©«œ §¦¢¢âª ­¦¨âª «¤ œ¤«¦¢ã N àª ©ç¤«£©, ¡˜  «¦ ©ç©«£˜ Ÿ˜ §¨¦®à¨ã©œ  œ£­˜¤å¦¤«áª ©˜ª
« ª œ§ ¡œ­˜¢å›œª (headers) «à¤ £¤¬£á«à¤ §¦¬ §œ¨¤áœ . „«© , £œ «¤ œ¤«¦¢ã [33mNNNN[37m,
 ™á© Ÿ˜ ©˜ª ›œå¥œ  « ª œ§ ¡œ­˜¢å›œª «à¤ œ§æ£œ¤à¤ «œ©©á¨à¤ £¤¬£á«à¤, ¡˜  Ÿ˜ ©«˜£˜«ã©œ  ©«¦ «œ¢œ¬«˜å¦.!)
!0l
!W[33mP[37mrevious: !i‹œ«˜­â¨œ©«œ ©«¦ §¨¦š¦ç£œ¤¦ £ã¤¬£˜. Šœ «¦¬¨šœå æ§àª ˜¡¨ ™éª ¡˜   §¨¦š¦ç£œ¤ œ¤«¦¢ã.!)
!0l
!W[33m#[37m:        !i’¦ ©ç©«£˜ Ÿ˜ ©˜ª «ã©œ  â¤˜¤ ˜¨ Ÿ£æ £¤ç£˜«¦ª ©«¦ ¦§¦å¦ Ÿ˜ £œ«˜™œå«œ.
€¤ «¦ £ã¤¬£˜ ›œ¤ ™¨œŸœå, Ÿ˜ «¦§¦Ÿœ«Ÿœå«œ ©«¦ ¡¦¤« ¤æ«œ¨¦ £ã¤¬£˜. ‹§¦¨œå«œ ¡˜  œ›é ¤˜ ®¨© £¦§¦ ã©œ«œ
©¬¤«£ã©œ ª:  œ¤«¦¢ã [33m#1000[37m Ÿ˜ ©˜ª §áœ  ¡˜«œ¬Ÿœå˜¤ ©«¦ £ã¤¬£˜ 1000.!)
!0l
!W[33mR[37mead:     !i€¤áš¤à© «¦¬ «¨â®¦¤«¦ª £¤ç£˜«¦ª. ‹œ«á «¤ ˜¤áš¤à© â®œ«œ œ§ §¢â¦¤
›¬¤˜«æ««œª ®œ ¨ ©£¦ç «¦¬ £¤ç£˜«¦ª.!)
!0l
[0;1m} T Read Mail, help about scanning commands


RDSCNR {[0;1;31m
Š¬§á£˜ , ˜¬«ã  œ§ ¢¦šã ›œ¤ œå¤˜  ›¬¤˜«ã.
[0;1m} T Read Mail, invalid selection from scan menu


RDDEF {[Enter=[33m%c[37m]: [0m} T Read Mail, default value for menus


RDGOHLP {[0;1m
!J‹§¦¨œå«œ ¤˜ £œ«˜¡ ¤Ÿœå«œ ©œ ¡á§¦ ¦ ©¬š¡œ¡¨ £â¤¦ £ã¤¬£˜ ›å¤¦¤«˜ª œ›é
«¦¤ ˜¨ Ÿ£æ «¦¬.  ˜¨ Ÿ£æª ›œ¤ œå¤˜  ˜¤áš¡ ¤˜ ˜¤ã¡œ  ©œ ¬§á¨®¦¤ £ã¤¬£˜:
˜¤ «¦ ©¬š¡œ¡¨ £â¤¦ £ã¤¬£˜ ›œ¤ ™¨œŸœå, Ÿ˜ ™¨œŸœå«œ ©«¦ ¡¦¤« ¤æ«œ¨¦ £ã¤¬£˜.
ƒå¤¦¤«˜ª [33mF[37m (First) Ÿ˜ £œ«˜™œå«œ ©«¦ §¨é«¦ £ã¤¬£˜, œ¤é £œ
[33mL[37m (Last) £œ«˜¡ ¤œå©«œ ©«¦ «œ¢œ¬«˜å¦ £ã¤¬£˜.
‚ ˜ § ¦ š¨ãš¦¨˜, £§¦¨œå«œ ¤˜ ®¨© £¦§¦ ã©œ«œ «¤ ©ç¤«£© «ª £¦¨­ãª
[33m#123[37m ˜§æ «¦ §¨¦š¦ç£œ¤¦ £œ¤¦ç, §¦¬ Ÿ˜ ©˜ª §¨¦àŸã©œ  ¡˜«œ¬Ÿœå˜¤
©«¦ £ã¤¬£˜ 123.!)
[0;1m} T Read Mail, help on '#' command


RDGONUM {[0;1m
!Wƒé©«œ «¦¤ ˜¨ Ÿ£æ £¤ç£˜«¦ª §¦¬ Ÿ˜ §¨¦àŸŸœå«œ, [33mF[37m š ˜ «¦ §¨é«¦
£ã¤¬£˜, [33mL[37m š ˜ «¦ «œ¢œ¬«˜å¦, [33m?[37m š ˜ ™¦ãŸœ ˜, ã
[33mX[0;1m š ˜ ˜¡ç¨à©:!)[0m } T Read Mail, goto what message?


RDBEG {[0;1;33m
”«á©˜«œ ©«¤ ˜¨®ã «à¤ £¤¬£á«à¤.
[0;1m} T Read Mail, reached beginning of messages


RDEND {[0;1;33m
”«á©˜«œ ©«¦ «â¢¦ª «à¤ £¤¬£á«à¤.
[0;1m} T Read Mail, reached end of messages


RDDEL {[0;1;31m
!J…«¦ç£œ ©¬šš¤é£, ˜¢¢á «¦ £ã¤¬£˜ ˜¬«æ £æ¢ ª › œš¨á­.!)
[0;1m} T Read Mail, message has just been deleted, can't read


RDIOERR {[0;1;31m
!J“§ã¨¥œ ©­á¢£˜ œšš¨˜­ãª/˜¤áš¤à©ª ¡˜«á «¤ ˜¤áš¤à© «¦¬ £¤ç£˜«¦ª.
˜¨˜¡˜¢¦ç£œ œ ›¦§¦ ã©«œ «¦¤ •œ ¨ ©«ã ‘¬©«ã£˜«¦ª š ˜ « ª ©¬¤Ÿã¡œª
§¦¬ ¦›ãš©˜¤ ©œ ˜¬«æ «¦ ¢áŸ¦ª.!)
[0;1m} T Read Mail, I/O error while reading message


RDRMNU1 {[0;1m
[[33mN[37m]ext . . . . . . . „§æ£œ¤¦ £ã¤¬£˜   [[33mP[37m]revious . . . ¨¦š¦ç£œ¤¦ £ã¤¬£˜
[[33mE[37m]rase . . . .  ƒ ˜š¨˜­ã £¤ç£˜«¦ª   [[33mC[37m]opy  . . . . €¤« š¨˜­ã £¤ç£˜«¦ª
[[33mF[37m]orward  . . ‹œ«˜™å™˜© £¤ç£˜«¦ª   [[33mR[37m]eply  . . . . . . . . . €§á¤«©
e[[33mX[37m]it  . . . . . . . . . .  „¥¦›¦ª

† œ§ ¢¦šã ©˜ª ([33m?[37m š ˜ ™¦ãŸœ ˜); } T Read Mail, choices after reading message


RDRMNU1H {[0;1m

!J‹§¦¨œå«œ ¤˜ ›é©œ«œ « ª œ¥ãª œ¤«¦¢âª ©œ ˜¬«æ «¦ ©£œå¦:!)

!W[33mN[37mext:     !i‹œ«˜­â¨œ©«œ ©«¦ œ§æ£œ¤¦ £ã¤¬£˜.
‹§¦¨œå«œ ¤˜ ®¨© £¦§¦ ã©œ«œ ˜¬«ã «¤ œ¤«¦¢ã š ˜ â¤˜ œå›¦ª ˜§¢ãª ˜¤å®¤œ¬©ª «à¤ £¤¬£á«à¤.
ƒé©«œ §¦¢¢âª ­¦¨âª «¤ œ¤«¦¢ã N àª ©ç¤«£©, ¡˜  «¦ ©ç©«£˜ Ÿ˜ §¨¦®à¨ã©œ  œ£­˜¤å¦¤«áª ©˜ª
« ª œ§ ¡œ­˜¢å›œª (headers) «à¤ £¤¬£á«à¤ §¦¬ §œ¨¤áœ . „«© , £œ «¤ œ¤«¦¢ã [33mNNNN[37m,
 ™á© Ÿ˜ ©˜ª ›œå¥œ  « ª œ§ ¡œ­˜¢å›œª «à¤ œ§æ£œ¤à¤ «œ©©á¨à¤ £¤¬£á«à¤, ¡˜  Ÿ˜ ©«˜£˜«ã©œ  ©«¦ «œ¢œ¬«˜å¦.!)
!0l
!W[33mP[37mrevious: !i‹œ«˜­â¨œ©«œ ©«¦ §¨¦š¦ç£œ¤¦ £ã¤¬£˜. Šœ «¦¬¨šœå æ§àª ˜¡¨ ™éª ¡˜   §¨¦š¦ç£œ¤ œ¤«¦¢ã.!)
!0l
!W[33m#[37m:        !i’¦ ©ç©«£˜ Ÿ˜ ©˜ª «ã©œ  â¤˜¤ ˜¨ Ÿ£æ £¤ç£˜«¦ª ©«¦ ¦§¦å¦ Ÿ˜ £œ«˜™œå«œ.
€¤ «¦ £ã¤¬£˜ ›œ¤ ™¨œŸœå, Ÿ˜ «¦§¦Ÿœ«Ÿœå«œ ©«¦ ¡¦¤« ¤æ«œ¨¦ £ã¤¬£˜. ‹§¦¨œå«œ ¡˜  œ›é ¤˜ ®¨© £¦§¦ ã©œ«œ
©¬¤«£ã©œ ª:  œ¤«¦¢ã [33m#1000[37m Ÿ˜ ©˜ª §áœ  ¡˜«œ¬Ÿœå˜¤ ©«¦ £ã¤¬£˜ 1000.!)
!0l
!W[33mE[37mrase:    !iƒ ˜š¨˜­ã «¦¬ «¨â®¦¤«¦ª £¤ç£˜«¦ª. ƒ„Œ Ÿ˜ ¬§á¨¥œ  œ§ ™œ™˜åà©. ’¦ £ã¤¬£˜
› ˜š¨á­œ«˜  ˜£â©àª.!)
!0l
!W[33mC[37mopy:     !i€¤« š¨˜­ã «¦¬ £¤ç£˜«¦ª ©œ ¡á§¦ ¦¤ á¢¢¦ §˜¨˜¢ã§«. ‚ ˜ ™¦ãŸœ ˜ §á¤à
©«˜ œå› §˜¨˜¢ã§«, ›é©«œ [33mC?[37m.!)
!0l
!W[33mF[37morward:  !i¨¦éŸ© «¦¬ £¤ç£˜«¦ª ©œ ¡á§¦ ¦¤ á¢¢¦ §˜¨˜¢ã§«. ’¦ £ã¤¬£˜ ˜¤« š¨á­œ«˜  ©«¤ ¤â˜
› œçŸ¬¤©. ’¦ › ¡æ ©˜ª ˜¤«åš¨˜­¦ › ˜š¨á­œ«˜ .!)
!0l
!W[33mR[37meply:    !iƒ£ ¦¬¨šœå«˜  £ã¤¬£˜-˜§á¤«© §¨¦ª «¦ «¨â®¦¤ £ã¤¬£˜.!)
!0l
[0;1m} T Read Mail, help about reading messages, version 1


RDRMNU2 {[0;1m
[[33mN[37m]ext . . . . . . . „§æ£œ¤¦ £ã¤¬£˜   [[33mP[37m]revious . . . ¨¦š¦ç£œ¤¦ £ã¤¬£˜
[[33mE[37m]rase . . . .  ƒ ˜š¨˜­ã £¤ç£˜«¦ª   [[33mC[37m]opy  . . . . €¤« š¨˜­ã £¤ç£˜«¦ª
[[33mF[37m]orward  . . ‹œ«˜™å™˜© £¤ç£˜«¦ª   [[33mR[37m]eply  . . . . . . . . . €§á¤«©
[[33mB[37m]acktrack . . . .  ˜«¨ ¡æ £ã¤¬£˜   e[[33mX[37m]it  . . . . . . . . . .  „¥¦›¦ª

† œ§ ¢¦šã ©˜ª ([33m?[37m š ˜ ™¦ãŸœ ˜); } T Read Mail, menu with backtrack command

                                             
RDRMNU2H {[0;1m

!J‹§¦¨œå«œ ¤˜ ›é©œ«œ « ª œ¥ãª œ¤«¦¢âª ©œ ˜¬«æ «¦ ©£œå¦:!)

!W[33mN[37mext:      !i‹œ«˜­â¨œ©«œ ©«¦ œ§æ£œ¤¦ £ã¤¬£˜.
‹§¦¨œå«œ ¤˜ ®¨© £¦§¦ ã©œ«œ ˜¬«ã «¤ œ¤«¦¢ã š ˜ â¤˜ œå›¦ª ˜§¢ãª ˜¤å®¤œ¬©ª «à¤ £¤¬£á«à¤.
ƒé©«œ §¦¢¢âª ­¦¨âª «¤ œ¤«¦¢ã N àª ©ç¤«£©, ¡˜  «¦ ©ç©«£˜ Ÿ˜ §¨¦®à¨ã©œ  œ£­˜¤å¦¤«áª ©˜ª
« ª œ§ ¡œ­˜¢å›œª (headers) «à¤ £¤¬£á«à¤ §¦¬ §œ¨¤áœ . „«© , £œ «¤ œ¤«¦¢ã [33mNNNN[37m,
 ™á© Ÿ˜ ©˜ª ›œå¥œ  « ª œ§ ¡œ­˜¢å›œª «à¤ œ§æ£œ¤à¤ «œ©©á¨à¤ £¤¬£á«à¤, ¡˜  Ÿ˜ ©«˜£˜«ã©œ  ©«¦ «œ¢œ¬«˜å¦.!)
!0l
!W[33mP[37mrevious:  !i‹œ«˜­â¨œ©«œ ©«¦ §¨¦š¦ç£œ¤¦ £ã¤¬£˜. Šœ «¦¬¨šœå æ§àª ˜¡¨ ™éª ¡˜   §¨¦š¦ç£œ¤ œ¤«¦¢ã.!)
!0l
!W[33m#[37m:         !i’¦ ©ç©«£˜ Ÿ˜ ©˜ª «ã©œ  â¤˜¤ ˜¨ Ÿ£æ £¤ç£˜«¦ª ©«¦ ¦§¦å¦ Ÿ˜ £œ«˜™œå«œ.
€¤ «¦ £ã¤¬£˜ ›œ¤ ™¨œŸœå, Ÿ˜ «¦§¦Ÿœ«Ÿœå«œ ©«¦ ¡¦¤« ¤æ«œ¨¦ £ã¤¬£˜. ‹§¦¨œå«œ ¡˜  œ›é ¤˜ ®¨© £¦§¦ ã©œ«œ
©¬¤«£ã©œ ª:  œ¤«¦¢ã [33m#1000[37m Ÿ˜ ©˜ª §áœ  ¡˜«œ¬Ÿœå˜¤ ©«¦ £ã¤¬£˜ 1000.!)
!0l
!W[33mE[37mrase:     !iƒ ˜š¨˜­ã «¦¬ «¨â®¦¤«¦ª £¤ç£˜«¦ª. ƒ„Œ Ÿ˜ ¬§á¨¥œ  œ§ ™œ™˜åà©. ’¦ £ã¤¬£˜
› ˜š¨á­œ«˜  ˜£â©àª.!)
!0l
!W[33mC[37mopy:      !i€¤« š¨˜­ã «¦¬ £¤ç£˜«¦ª ©œ ¡á§¦ ¦¤ á¢¢¦ §˜¨˜¢ã§«. ‚ ˜ ™¦ãŸœ ˜ §á¤à
©«˜ œå› §˜¨˜¢ã§«, ›é©«œ [33mC?[37m.!)
!0l
!W[33mF[37morward:   !i¨¦éŸ© «¦¬ £¤ç£˜«¦ª ©œ ¡á§¦ ¦¤ á¢¢¦ §˜¨˜¢ã§«. ’¦ £ã¤¬£˜ ˜¤« š¨á­œ«˜  ©«¤ ¤â˜
› œçŸ¬¤©. ’¦ › ¡æ ©˜ª ˜¤«åš¨˜­¦ › ˜š¨á­œ«˜ .!)
!0l
!W[33mR[37meply:     !iƒ£ ¦¬¨šœå«˜  £ã¤¬£˜-˜§á¤«© §¨¦ª «¦ «¨â®¦¤ £ã¤¬£˜.!)
!0l
!W[33mB[37macktrack: !i’¦ «¨â®¦¤ £ã¤¬£˜ œå¤˜  ˜§á¤«© §¨¦ª ¡á§¦ ¦ á¢¢¦.
‹œ ˜¬«ã «¤ œ¤«¦¢ã £œ«˜­â¨œ©«œ ©«¦ £ã¤¬£˜ «¦ ¦§¦å¦ ˜§˜¤«áœ  «¦ «¨â®¦¤ £ã¤¬£˜.!)
!0l
[0;1m} T Read Mail, help about reading messages, version 2


RDRMNU3 {[0;1m
[[33mN[37m]ext . . . . . . . „§æ£œ¤¦ £ã¤¬£˜   [[33mP[37m]revious . . . ¨¦š¦ç£œ¤¦ £ã¤¬£˜
[[33mE[37m]rase . . . .  ƒ ˜š¨˜­ã £¤ç£˜«¦ª   [[33mC[37m]opy  . . . . €¤« š¨˜­ã £¤ç£˜«¦ª
[[33mF[37m]orward  . . ‹œ«˜™å™˜© £¤ç£˜«¦ª   [[33mR[37m]eply  . . . . . . . . . €§á¤«©
[[33mD[37m]elete user . . . ƒ ˜š¨˜­ã ®¨ã©«   e[[33mX[37m]it  . . . . . . . . . .  „¥¦›¦ª

† œ§ ¢¦šã ©˜ª ([33m?[37m š ˜ ™¦ãŸœ ˜); } T Read Mail, menu with delete user command
                                             

RDRMNU3H {[0;1m

!J‹§¦¨œå«œ ¤˜ ›é©œ«œ « ª œ¥ãª œ¤«¦¢âª ©œ ˜¬«æ «¦ ©£œå¦:!)

!W[33mN[37mext:        !i‹œ«˜­â¨œ©«œ ©«¦ œ§æ£œ¤¦ £ã¤¬£˜.
‹§¦¨œå«œ ¤˜ ®¨© £¦§¦ ã©œ«œ ˜¬«ã «¤ œ¤«¦¢ã š ˜ â¤˜ œå›¦ª ˜§¢ãª ˜¤å®¤œ¬©ª «à¤ £¤¬£á«à¤.
ƒé©«œ §¦¢¢âª ­¦¨âª «¤ œ¤«¦¢ã N àª ©ç¤«£©, ¡˜  «¦ ©ç©«£˜ Ÿ˜ §¨¦®à¨ã©œ  œ£­˜¤å¦¤«áª ©˜ª
« ª œ§ ¡œ­˜¢å›œª (headers) «à¤ £¤¬£á«à¤ §¦¬ §œ¨¤áœ . „«© , £œ «¤ œ¤«¦¢ã [33mNNNN[37m,
 ™á© Ÿ˜ ©˜ª ›œå¥œ  « ª œ§ ¡œ­˜¢å›œª «à¤ œ§æ£œ¤à¤ «œ©©á¨à¤ £¤¬£á«à¤, ¡˜  Ÿ˜ ©«˜£˜«ã©œ  ©«¦ «œ¢œ¬«˜å¦.!)
!0l
!W[33mP[37mrevious:    !i‹œ«˜­â¨œ©«œ ©«¦ §¨¦š¦ç£œ¤¦ £ã¤¬£˜. Šœ «¦¬¨šœå æ§àª ˜¡¨ ™éª ¡˜   §¨¦š¦ç£œ¤ œ¤«¦¢ã.!)
!0l
!W[33m#[37m:           !i’¦ ©ç©«£˜ Ÿ˜ ©˜ª «ã©œ  â¤˜¤ ˜¨ Ÿ£æ £¤ç£˜«¦ª ©«¦ ¦§¦å¦ Ÿ˜ £œ«˜™œå«œ.
€¤ «¦ £ã¤¬£˜ ›œ¤ ™¨œŸœå, Ÿ˜ «¦§¦Ÿœ«Ÿœå«œ ©«¦ ¡¦¤« ¤æ«œ¨¦ £ã¤¬£˜. ‹§¦¨œå«œ ¡˜  œ›é ¤˜ ®¨© £¦§¦ ã©œ«œ
©¬¤«£ã©œ ª:  œ¤«¦¢ã [33m#1000[37m Ÿ˜ ©˜ª §áœ  ¡˜«œ¬Ÿœå˜¤ ©«¦ £ã¤¬£˜ 1000.!)
!0l
!W[33mE[37mrase:       !iƒ ˜š¨˜­ã «¦¬ «¨â®¦¤«¦ª £¤ç£˜«¦ª. ƒ„Œ Ÿ˜ ¬§á¨¥œ  œ§ ™œ™˜åà©. ’¦ £ã¤¬£˜
› ˜š¨á­œ«˜  ˜£â©àª.!)
!0l
!W[33mC[37mopy:        !i€¤« š¨˜­ã «¦¬ £¤ç£˜«¦ª ©œ ¡á§¦ ¦¤ á¢¢¦ §˜¨˜¢ã§«. ‚ ˜ ™¦ãŸœ ˜ §á¤à
©«˜ œå› §˜¨˜¢ã§«, ›é©«œ [33mC?[37m.!)
!0l
!W[33mF[37morward:     !i¨¦éŸ© «¦¬ £¤ç£˜«¦ª ©œ ¡á§¦ ¦¤ á¢¢¦ §˜¨˜¢ã§«. ’¦ £ã¤¬£˜ ˜¤« š¨á­œ«˜  ©«¤ ¤â˜
› œçŸ¬¤©. ’¦ › ¡æ ©˜ª ˜¤«åš¨˜­¦ › ˜š¨á­œ«˜ .!)
!0l
!W[33mR[37meply:       !iƒ£ ¦¬¨šœå«˜  £ã¤¬£˜-˜§á¤«© §¨¦ª «¦ «¨â®¦¤ £ã¤¬£˜.!)
!0l
!W[33mD[37melete user: !i’¦ «¨â®¦¤ £ã¤¬£˜ §œ¨ â®œ  «˜ ©«¦ ®œå˜ œ¤æª ¤â¦¬
®¨ã©«. ‹œ ˜¬«ã «¤ œ¤«¦¢ã › ˜š¨á­œ«œ «¦¤ ®¨ã©«. ƒ„Œ Ÿ˜ ¬§á¨¥œ  œ§ ™œ™˜åà© «à¤ §¨¦Ÿâ©œé¤ ©˜ª.
 ¢¦š˜¨ ˜©£æª Ÿ˜ £§¦¨œå ¤˜ œ§˜¤â¢Ÿœ  ©œ ®¨ã© £æ¤¦ £œ ®¨ã© «ª œ¤«¦¢ãª [33mDELETE[37m «¦¬ £œ¤¦ç ®œ ¨ ©«é¤,
¡˜  £æ¤¦ £â®¨  «¦ œ¨®æ£œ¤¦ cleanup.!)
!0l
[0;1m} T Read Mail, help about reading messages, version 3


RDRMNU4 {[0;1m
[[33mN[37m]ext . . . . . . . „§æ£œ¤¦ £ã¤¬£˜   [[33mP[37m]revious . . . ¨¦š¦ç£œ¤¦ £ã¤¬£˜
[[33mE[37m]rase . . . .  ƒ ˜š¨˜­ã £¤ç£˜«¦ª   [[33mC[37m]opy  . . . . €¤« š¨˜­ã £¤ç£˜«¦ª
[[33mF[37m]orward  . . ‹œ«˜™å™˜© £¤ç£˜«¦ª   [[33mR[37m]eply  . . . . . . . . . €§á¤«©
[[33mS[37m]top autofw . €¡ç¨à© £œ«˜™å™˜©ª   e[[33mX[37m]it  . . . . . . . . . .  „¥¦›¦ª

† œ§ ¢¦šã ©˜ª ([33m?[37m š ˜ ™¦ãŸœ ˜); } T Read Mail, menu with stop autofw command
                                             

RDRMNU4H {[0;1m

!J‹§¦¨œå«œ ¤˜ ›é©œ«œ « ª œ¥ãª œ¤«¦¢âª ©œ ˜¬«æ «¦ ©£œå¦:!)

!W[33mN[37mext:        !i‹œ«˜­â¨œ©«œ ©«¦ œ§æ£œ¤¦ £ã¤¬£˜.
‹§¦¨œå«œ ¤˜ ®¨© £¦§¦ ã©œ«œ ˜¬«ã «¤ œ¤«¦¢ã š ˜ â¤˜ œå›¦ª ˜§¢ãª ˜¤å®¤œ¬©ª «à¤ £¤¬£á«à¤.
ƒé©«œ §¦¢¢âª ­¦¨âª «¤ œ¤«¦¢ã N àª ©ç¤«£©, ¡˜  «¦ ©ç©«£˜ Ÿ˜ §¨¦®à¨ã©œ  œ£­˜¤å¦¤«áª ©˜ª
« ª œ§ ¡œ­˜¢å›œª (headers) «à¤ £¤¬£á«à¤ §¦¬ §œ¨¤áœ . „«© , £œ «¤ œ¤«¦¢ã [33mNNNN[37m,
 ™á© Ÿ˜ ©˜ª ›œå¥œ  « ª œ§ ¡œ­˜¢å›œª «à¤ œ§æ£œ¤à¤ «œ©©á¨à¤ £¤¬£á«à¤, ¡˜  Ÿ˜ ©«˜£˜«ã©œ  ©«¦ «œ¢œ¬«˜å¦.!)
!0l
!W[33mP[37mrevious:    !i‹œ«˜­â¨œ©«œ ©«¦ §¨¦š¦ç£œ¤¦ £ã¤¬£˜. Šœ «¦¬¨šœå æ§àª ˜¡¨ ™éª ¡˜   §¨¦š¦ç£œ¤ œ¤«¦¢ã.!)
!0l
!W[33m#[37m:           !i’¦ ©ç©«£˜ Ÿ˜ ©˜ª «ã©œ  â¤˜¤ ˜¨ Ÿ£æ £¤ç£˜«¦ª ©«¦ ¦§¦å¦ Ÿ˜ £œ«˜™œå«œ.
€¤ «¦ £ã¤¬£˜ ›œ¤ ™¨œŸœå, Ÿ˜ «¦§¦Ÿœ«Ÿœå«œ ©«¦ ¡¦¤« ¤æ«œ¨¦ £ã¤¬£˜. ‹§¦¨œå«œ ¡˜  œ›é ¤˜ ®¨© £¦§¦ ã©œ«œ
©¬¤«£ã©œ ª:  œ¤«¦¢ã [33m#1000[37m Ÿ˜ ©˜ª §áœ  ¡˜«œ¬Ÿœå˜¤ ©«¦ £ã¤¬£˜ 1000.!)
!0l
!W[33mE[37mrase:       !iƒ ˜š¨˜­ã «¦¬ «¨â®¦¤«¦ª £¤ç£˜«¦ª. ƒ„Œ Ÿ˜ ¬§á¨¥œ  œ§ ™œ™˜åà©. ’¦ £ã¤¬£˜
› ˜š¨á­œ«˜  ˜£â©àª.!)
!0l
!W[33mC[37mopy:        !i€¤« š¨˜­ã «¦¬ £¤ç£˜«¦ª ©œ ¡á§¦ ¦¤ á¢¢¦ §˜¨˜¢ã§«. ‚ ˜ ™¦ãŸœ ˜ §á¤à
©«˜ œå› §˜¨˜¢ã§«, ›é©«œ [33mC?[37m.!)
!0l
!W[33mF[37morward:     !i¨¦éŸ© «¦¬ £¤ç£˜«¦ª ©œ ¡á§¦ ¦¤ á¢¢¦ §˜¨˜¢ã§«. ’¦ £ã¤¬£˜ ˜¤« š¨á­œ«˜  ©«¤ ¤â˜
› œçŸ¬¤©. ’¦ › ¡æ ©˜ª ˜¤«åš¨˜­¦ › ˜š¨á­œ«˜ .!)
!0l
!W[33mR[37meply:       !iƒ£ ¦¬¨šœå«˜  £ã¤¬£˜-˜§á¤«© §¨¦ª «¦ «¨â®¦¤ £ã¤¬£˜.!)
!0l
!W[33mS[37mtop autofw: !i’¦ «¨â®¦¤ £ã¤¬£˜ ©˜ª â®œ  £œ«˜™ ™˜©«œå (forward) ˜¬«æ£˜«˜ ˜§æ ¡á§¦ ¦¤
®¨ã©«. ¢˜ «˜ £¤ç£˜«˜ §¨¦ª ˜¬«æ «¦¤ ®¨ã©« Ÿ˜ £œ«˜™ ™á¦¤«˜  ˜¬«æ£˜«˜ §¨¦ª œ©áª. „á¤ ˜¬«æ ©˜ª œå¤˜  œ¤¦®¢« ¡æ,
®¨© £¦§¦ ã©«œ ˜¬«ã «¤ œ¤«¦¢ã š ˜ ¤˜ ˜¡¬¨é©œ«œ «¤ ˜¬«æ£˜« £œ«˜™å™˜© «¦¬ ©¬š¡œ¡¨ £â¤¦¬ ®¨ã©« §¨¦ª œ©áª. ˜¨˜¡˜¢¦ç£œ
œ ›¦§¦ ã©«œ «¦¤ ®¨ã©« š ˜ ˜¬«ã «¤ œ¤â¨šœ ˜.!)
!0l
[0;1m} T Read Mail, help about reading messages, version 4


RDMNUR {[0;1;31m
!JŠ¬§á£˜ , ˜¬«ã  œ§ ¢¦šã ›œ¤ œå¤˜  ›¬¤˜«ã.!)
[0;1m} T Read Mail, invalid selection from read menu


RDSAR1 {[0;1;31m
!JŠ¬§á£˜ , ˜¬«æ «¦ £ã¤¬£˜ ›œ¤ â®œ  £œ«˜™ ™˜©«œå ˜¬«æ£˜«˜ §¨¦ª œ©áª.!)
[0;1m} T Read Mail, stop autofw, message has not been autofw'ed


RDSAR2 {[0;1;31m
!J’¦ £â¢¦ª [37m%s[31m â®œ  › ˜š¨˜­œå.!)
[0;1m} T Read Mail, stop autofw, user not found


RDSAR3 {[0;1;31m
!JŠ¬§á£˜ , «¦ £â¢¦ª [37m%s[31m ›œ¤ £œ«˜™ ™áœ  §¢â¦¤ «˜ £¤ç£˜«á «¦¬ §¨¦ª œ©áª.!)
[0;1m} T Read Mail, stop autofw, user does not forward any more


RDSAI {[0;1m
!J¢˜ «˜ £¤ç£˜«˜ §¨¦ª [32m%s[37m £œ«˜™ ™á¦¤«˜  ˜¬«æ£˜«˜ §¨¦ª œ©áª.
€§˜¤«é¤«˜ª ¡˜«˜­˜« ¡á ©«¤ œ§æ£œ¤ œ¨é«©,
˜¡¬¨é¤œ«œ «¤ œ¤«¦¢ã ˜¬«æ£˜«ª £œ«˜™å™˜©ª §¨¦ª œ©áª.!)
[0;1m} T Read Mail, stop autofw, information


RDSAQ {[0;1m
!W‡â¢œ«œ ¤˜ ©«˜£˜«ã©œ«œ «¤ ˜¬«æ£˜« §¨¦éŸ© «à¤ £¤¬£á«à¤ «¦¬
§˜¨˜§á¤à £â¢¦¬ª §¨¦ª œ©áª; [[33mY[37m]yes=¤˜  / [[33mN[37m]o=æ® )!) [0m} T Read Mail, stop autofw question


RDSAQR {[0;1;31m
!J€¬«ã  œ§ ¢¦šã ›œ¤ œå¤˜  ›¬¤˜«ã.!)
[0;1m} T Read Mail, stop autofw, invalid response


RDSAC {[0;1;32m
!J† ˜¬«æ£˜« £œ«˜™å™˜© ›œ¤ ˜¡¬¨éŸ¡œ.!)
[0;1m} T Read Mail, stop autofw, autoforwarding not stopped


RDSAS {[0;1;32m
!J† ˜¬«æ£˜« £œ«˜™å™˜© ˜¡¬¨éŸ¡œ.!)
[0;1m} T Read Mail, stop autofw, autoforwarding stopped


RDMSGHDR {[0m
} T Read Mail, body of message, header


RDMSGFTR {} T Read Mail, body of message, footer


DUERR {[0;1;31m
!JŠ¬§á£˜ , ¦ ®¨ã©«ª ›œ¤ ¬§á¨®œ  §¢â¦¤.!)
[0;1m} T Delete user, user does not exist


DUDEL {[0;1;31m
!JŠ¬§á£˜ , ¦ ®¨ã©«ª â®œ  ã› ©£œ àŸœå š ˜ › ˜š¨˜­ã. ‹§¦¨œå«œ ¤˜ «¦¤ ˜¤˜©«ã©œ«œ ›å¤¦¤«˜ª «¤ œ¤«¦¢ã DELETE ˜§æ «¦ £œ¤¦ç «à¤ ®œ ¨ ©«é¤, §¨ ¤ «¦ œ¨®æ£œ¤¦ cleanup.!)
[0;1m} T Delete user, user is already marked for deletion


DUOK {[0;1;31m
!J„¤«á¥œ , ¦ ®¨ã©«ª › œš¨á­. ‹§¦¨œå«œ ¤˜ «¦¤ ˜¤˜©«ã©œ«œ ›å¤¦¤«˜ª «¤ œ¤«¦¢ã DELETE ˜§æ «¦ £œ¤¦ç «à¤ ®œ ¨ ©«é¤, §¨ ¤ «¦ œ¨®æ£œ¤¦ cleanup.!)
[0;1m} T Delete user, user deleted


DUXM {[0;1;31m
!Jƒœ¤ £§¦¨œå«œ ¤˜ › ˜š¨á¯œ«œ ˜¬«æ «¦¤ ®¨ã©«.!)
[0;1m} T Delete user, can't delete this user



QMASK {[0;1m
!W‡â¢œ«œ ¤˜ œ ©ášœ«œ (quote) «¦ §¨¦ª ˜§á¤«© £ã¤¬£˜ ©«¤ ˜§á¤«©ã ©˜ª;
[[33mY[37m]yes=¤˜  / [[33mN[37m]o=æ® ):!) [0m} T Quote message question


QMERR {[0;1;31m
!J˜¨˜¡˜¢é ˜§˜¤«ã©«œ ©«¤ œ¨é«© £œ [33mY[31m (¤˜ ), ã [33mN[31m
(æ® ), ã ›é©«œ [33mX[31m š ˜ ˜¡ç¨à© «ª ˜§á¤«©ª.!)
[0;1m} T Quote message, invalid answer


MMINFO {[0;1m
!J‹œ ˜¬«ã «¤ œ¤«¦¢ã £§¦¨œå«œ ¤˜ ˜¢¢á¥œ«œ «˜ §œ¨ œ®æ£œ¤˜ œ¤æª £¤ç£˜«¦ª §¦¬
â®œ«œ ã› ©«œå¢œ .!)

!J‘£œ é©«œ æ« , œ¤é £§¦¨œå«œ ¤˜ ˜¢¢á¥œ«œ «˜ §œ¨ œ®æ£œ¤˜
œ¤æª £¤ç£˜«¦ª §¦¬ â®œ  › ˜™ ™˜©«œå £â©à Internet Mail, ˜¬«æ §¦¬ ˜¢¢áœ«œ
œå¤˜  ‹Œ «¦ «¦§ ¡æ ˜¤«åš¨˜­¦ «¦¬ £¤ç£˜«¦ª. ’¦ å› ¦ «¦ £ã¤¬£˜ â®œ  ã›
˜§¦©«˜¢¢œå ¡˜  ›œ¤ £§¦¨œå ¤˜ ˜¢¢˜®Ÿœå.!)
[0;1m} T Modify Message, information


MMASK {[0;1m
!W¦ ¦ £ã¤¬£˜ Ÿâ¢œ«œ ¤˜ £œ«˜™á¢¢œ«œ; ƒé©«œ «¦¤ ˜¨ Ÿ£æ «¦¬ £¤ç£˜«¦ª
([33m%d[37m-[33m%d[37m):!) [0m} T Modify Message, question


MMERR1 {[0;1;31m
!JŠ¬§á£˜ , «¦ £ã¤¬£˜ [37m%d[31m ›œ¤ ¬§á¨®œ  ã ›œ¤ «¦ â®œ«œ ©«œå¢œ 
œ©œåª.!)
[0;1m} T Modify Message, can't use that message number


MMERR2 {[0;1;31m
!JŠ¬§á£˜ , ›œ¤ £§¦¨œå«œ ¤˜ £œ«˜™á¢¢œ«œ ˜¬«æ «¦ £ã¤¬£˜.!)
[0;1m} T Modify Message, can't modify this message


MMERR3 {[0;1;31m
!Jƒé©«œ â¤˜¤ ˜¨ Ÿ£æ £œ«˜¥ç [37m%d[31m ¡˜  [37m%d[31m.!)
[0;1m} T Modify Message, message number out of bounds


EMERR {[0;1;31m
!JŠ¬§á£˜ , ›œ¤ £§¦¨œå«œ ¤˜ › ˜š¨á¯œ«œ ˜¬«æ «¦ £ã¤¬£˜.!)
[0;1m} T Erase Message, can't erase this message


EMXMPT {[0;1;31m
!JŠ¬§á£˜ , ˜¬«æ «¦ £ã¤¬£˜ œå¤˜  £ › ˜š¨á¯ £¦ (exempt).!)
[0;1m} T Erase Message, can't erase this message



USING {[0;1;31m
!J‰á§¦ ¦ª á¢¢¦ª ®¨ã©«ª œ¨šáœ«˜  £œ ˜¬«æ «¦ £ã¤¬£˜.
˜¨˜¡˜¢é §œ¨ £â¤œ«œ ¢åš é¨˜ §¨ ¤ ¥˜¤˜§¨¦©§˜Ÿã©œ«œ.!)
} T Can't mess with message due to conflicts


MMVT {[0;30;47m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [34m‹œ«˜™¦¢ã £¤ç£˜«¦ª[0;30;47m ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;1;37;47m¿ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  ‡â£˜ . . . . . . . . . . [1;44;37m@63;43;0s[0;1;47;37m  ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  €¨®œå¦  . . . . . . . .  [1;44;37m@16;16;0s[0;1;47;37m                             ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  €§æ›œ ¥ €¤áš¤à©ª . . . [0;30;46m [@"X "t] [1;47;37m                                          ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  Ctrl-R š ˜ ™¦ãŸœ ˜                                                      [1;37m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³             [0;1;42;33m@14;"‰œå£œ¤¦"b[0;47;30mÜ    [0;1;42;33m@14;"OK"b[0;47;30mÜ    [0;1;41;33m@14;"€¡¬¨¦"b[0;47;30mÜ  [0;1;47;37m³ [0m
[30;47m ³              ßßßßßßßßßßßßßßßß     ßßßßßßßßßßßßßßßß     ßßßßßßßßßßßßßßßß  [0;1;47;37m³ [0m
[30;47m À[0;1;37;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0m} T Message edit visual template


MMWARN1 {[0;1;33m
!J’¦ £ã¤¬£˜ ›œ¤ â®œ  ©¬¤££â¤¦ ˜¨®œå¦.
ƒœ¤ ¬§ã¨®œ ¢æš¦ª ¤˜ ˜¢¢á¥œ«œ «¦ æ¤¦£˜ «¦¬ ˜¨®œå¦¬.!)
[0;1m} T Modify message, warning 1: no attached file, filename not changed


MMWARN2 {[0;1;33m
!J’¦ æ¤¦£˜ «¦¬ ˜¨®œå¦¬ §œ¨ œå®œ £ ˜§¦›œ¡«¦çª ®˜¨˜¡«ã¨œª.
’¦ â®¦¬£œ ˜¢¢á¥œ  ©œ "[37m%s[37m".!)
[0;1m} T Modify message, warning 2: bad characters in filename


MMWARN3 {[0;1;31m
!J’¦ œ§å§œ›¦ §¨æ©™˜©ãª ©˜ª ›œ¤ ©˜ª œ§ «¨â§œ  ¤˜ «ã©œ«œ ˜§æ›œ ¥ ˜¤áš¤à©ª.!)
[0;1m} T Modify message, warning 3: can't request return receipt


MMWARN4 {[0;1;31m
!Jƒœ¤ â®œ«œ ˜¨¡œ«æ ®¨æ¤¦ ®¨ã©ª š ˜ ¤˜ «ã©œ«œ ˜§æ›œ ¥ ˜¤áš¤à©ª.!)
[0;1m} T Modify message, warning 4: not enough credits for return receipt


MMINFO1 {[0;1;32m
!J…«ãŸ¡œ ˜§æ›œ ¥ ˜¤áš¤à©ª, ¡˜  ®¨œàŸã¡˜«œ [32m%d £¦¤á›%s[32m.!)
[0;1m} T Modify message, return receipt requested


MMCAN {[0;1;33m
!J† › ˜› ¡˜©å˜ ˜¡¬¨éŸ¡œ. ’¦ £ã¤¬£˜ ›œ¤ £œ«˜™¢ãŸ¡œ.!)
[0;1m} T Modify message, abort message


MMLT {[2J[0;30;47m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [34m‹œ«˜™¦¢ã £¤ç£˜«¦ª[0;30;47m ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;1;37;47m¿ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m1[30m. ‡â£˜ . . . . [34m@63;56;0s[0;1;47;37m ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m2[30m. €¨®œå¦  . . . . . . . . . . . . . . . . . . . . . .  [34m@16;16;0s[0;1;47;37m ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m3[30m. €§æ›œ ¥ €¤áš¤à©ª . . . . . . . . . . . . . . . . . . . . . . .  [34m@"X "t[0;1;47;37m ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m4[30m. ‹œ«˜™¦¢ã ¡œ £â¤¦¬ £¤ç£˜«¦ª@1;"4Edit"b                                         [1;37m  ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m À[0;1;37;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0;1m
} T Modify message, linear template


NEWSUBJ {[0;1m
!Wƒé©«œ «¦ ¤â¦ Ÿâ£˜ «¦¬ £¤ç£˜«æª ©˜ª.!)
} T Modify message, new subject


NEWATTN {[0;1m
!Wƒé©«œ «¦ ¤â¦ æ¤¦£˜ «¦¬ ©¬¤££â¤¦¬ ˜¨®œå¦¬. €¤ ˜­ã©œ«œ «¦ æ¤¦£˜ ¡œ¤æ,
Ÿ˜ œ§˜¤â¢Ÿœ  ˜¬«æ£˜«˜ ©«¦ ¡˜«á ©¬¤Ÿã¡ æ¤¦£˜, xxx.att, æ§¦¬ xxx ¦ ˜¨ Ÿ£æª
«¦¬ £¤ç£˜«¦ª. €¬«æ «¦ §œ›å¦ Ÿ˜ ˜š¤¦Ÿœå ˜¤ ›œ¤ â®œ«œ œ§ ©¬¤á¯œ  ˜¨®œå¦ ©«¦
£ã¤¬£á ©˜ª.!)
} T Modify message, new filename




RRRSUBJ {<<€§æ›œ ¥ §˜¨˜¢˜™ãª š ˜ «¦ £ã¤¬£˜ %s/%d>>} T Return Receipt message subject


RRRBODY {[0;1;36m

ÛÛ  €ƒ„ˆ† €€Š€†‘

%s %s â®œ  › ˜™á©œ  «¦ £ã¤¬£˜ %s/%ld §¦¬
©«œå¢˜«œ «¤ %s, %d %s %d, ©« ª %s.   [0;1m

ÛÛ  €¬«ã  ˜§æ›œ ¥ §˜¨˜¢˜™ãª ›£ ¦¬¨šãŸ¡œ ˜¬«æ£˜«˜,
    æ§àª œå®˜«œ «ã©œ  ¡˜«á «¤ ˜§¦©«¦¢ã «¦¬ £¤ç£˜«¦ª.

} T Return Receipt message body (no formatting)


SEXMALE {} T Masculine article
SEXFEM {†} T Feminine article


RRRGEN {[0;1;36m
!WÛÛ  !iƒ£ ¦¬¨šãŸ¡œ [37m˜§æ›œ ¥ §˜¨˜¢˜™ãª[36m
æ§àª œå®œ «Ÿœå ˜§æ «¦¤ ˜§¦©«¦¢â˜.!)
!0l[0;1m} T Return Receipt generated


RRRINJ {[0;1m***

!J’¦ £â¢¦ª [32m%s[37m £æ¢ ª › á™˜©œ «¦ £¤¬£á ©˜ª,
¡˜  ›£ ¦¬¨šãŸ¡œ ˜§æ›œ ¥ §˜¨˜¢˜™ãª.!)
} T Return Receipt notification for receipt recipient


RRRNOT {[0;1m
!WÛÛ  !i’¦ £â¢¦ª [32m%s[37m œå¤˜  ©¬¤›œ›œ£â¤¦ ¡˜  œ ›¦§¦ ãŸ¡œ
š ˜ «¤ ˜§æ›œ ¥ §˜¨˜¢˜™ãª.!)
!0l[0;1m} T Return Receipt notification for receipt sender




ATTNF {[0;1;31m
!J€¬«æ «¦ £ã¤¬£˜ Ÿ˜ â§¨œ§œ ¤˜ â®œ  â¤˜ ˜¨®œå¦ ©¬¤££â¤¦,
˜¢¢á «¦ ˜¨®œå¦ ¢œå§œ ! ˜¨˜¡˜¢¦ç£œ œ ›¦§¦ ã©«œ £˜ª š ˜ «¦ £ã¤¬£˜ [33m%s/%d[31m!
…«á£œ ©¬šš¤é£ ¡˜  Ÿ˜ ¡á¤¦¬£œ «¦ §˜¤ ›¬¤˜«æ š ˜ ¤˜ ©é©¦¬£œ «¦ ˜¨®œå¦.!)
[0;1m} T File Attachment missing


ATTIO {[0;1;31m
!J† ¢ã¯ «¦¬ ˜¨®œå¦¬ £˜«˜ éŸ¡œ ¢æšà ¢áŸ¦¬ª œšš¨˜­ãª/˜¤áš¤à©ª. ˜¨˜¡˜¢é
œ ›¦§¦ ã©«œ «¦¤ •œ ¨ ©«ã ‘¬©«ã£˜«¦ª š ˜ « ª ©¬¤Ÿã¡œª §¦¬ ¦›ãš©˜¤ ©œ ˜¬«æ «¦
¢áŸ¦ª.!)
[0;1m} T Can't link file attachment for downloading


ATTMNT1 {[0;1;32m
!J€¬«æ «¦ £ã¤¬£˜ â®œ  â¤˜ ˜¨®œå¦ £ã¡¦¬ª [37m%d bytes[32m ©¬¤££â¤¦.!)
[0;1m} T File Attachment information, no filename


ATTMNT2 {[0;1;32m
!J€¨®œå¦ £œ æ¤¦£˜ "[37m%s[32m" ¡˜  £ã¡¦ª [37m%d bytes[32m
œå¤˜  ©¬¤££â¤¦ ©«¦ £ã¤¬£˜.!)
[0;1m} T File Attachment information with filename


ATTDNL {[0;1m
‡â¢œ«œ ¤˜ ›œå«œ ã ¤˜ ¢á™œ«œ «¦ ˜¨®œå¦ «é¨˜; ([[33mY[37m]es=¤˜  / [[33mN[37m]o=æ® ) } T File Attachment, download question


ATTDEF {[Enter=[33m%c[37m]: [0m} T File Attachment, default answer to ATTDNL



ATTERR {[0;1;31m
!J˜¨˜¡˜¢é ˜§˜¤«ã©«œ ©«¤ œ¨é«© £œ [[33mY[31m]es=¤˜  ã [[33mN[31m]o=æ® .!)
[0;1m} T File Attachment, wrong answer to download question

         
ATTDESC {„§ ©ç¤˜¯ £¤ç£˜«¦ª %s/%d} S 49 File Attachment Download description


DNLNCRD {[0;1;31m
!JŠ¬§á£˜ , ›œ¤ â®œ«œ ˜¨¡œ«âª £¦¤á›œª š ˜ ¤˜ ¢á™œ«œ «¦ ©¬¤££â¤¦ ˜¨®œå¦.!)
[0;1m} T File Attachment download, not enough credits


CPNOAXES {[0;1;31m
!JŠ¬§á£˜ , ›œ¤ â®œ«œ §¨æ©™˜© ©œ ˜¬«ã «¤ œ§ ¢¦šã.!)
[0;1m} T Copy message, access denied


CPWHO {[0;1m
‚¨á¯«œ ¯œ¬›é¤¬£¦ ã club §¦¬ Ÿ˜ ˜¤« š¨á¯œ«œ «¦ £ã¤¬£˜
([33m?[37m š ˜ ™¦ãŸœ ˜) [Enter=Sysop]: [0m} T Copy message, ask for recipient


CPERR {[0;1;31m
!JŠ¬§á£˜ , ›œ¤ £§¦¨œå«œ ¤˜ ®¨© £¦§¦ ã©œ«œ ¢å©«œª › ˜¤¦£ãª ©œ ˜¬«æ
©£œå¦.!)
[0;1m} T Copy message, can't use distribution lists here


CPCERR {[0;1;31m
!JŠ¬§á£˜ , «¦ œ§å§œ›¦ §¨æ©™˜©ãª ©˜ª ©«¦ club [37m%s[31m ›œ¤ œ§ «¨â§œ 
«¤ ˜§¦©«¦¢ã £¤¬£á«à¤.!)
[0;1m} T Copy message, no WRITE access to target club


CPCERR2 {[0;1;31m
!JŠ¬§á£˜ , «¦ œ§å§œ›¦ §¨æ©™˜©ãª ©˜ª ©«¦ club [37m%s[31m ›œ¤ œ§ «¨â§œ 
«¤ ˜§¦©«¦¢ã ©¬¤££â¤à¤ ˜¨®œåà¤. ’¦ ©¬¤££â¤¦ ©œ ˜¬«æ «¦ £ã¤¬£˜ ˜¨®œå¦
›œ¤ Ÿ˜ ˜¤« š¨˜­œå.!)
[0;1m} T Copy message, no UPLOAD access to target club


CPRCPOK {[0;1;32m
!J˜¨˜¢ã§«ª «¦¬ ˜¤«åš¨˜­¦¬ Ÿ˜ œå¤˜  «¦ £â¢¦ª [37m%s[32m.!)
[0;1m} T Copy message: confirming recipient of message


CPRCPOKN {[0;1;32m
!J’¦ ˜¤«åš¨˜­¦ Ÿ˜ ©«˜¢œå £â©à Internet Mail ©«¤ › œçŸ¬¤© [37m%s[32m.!)
[0;1m} T Copy message: confirming recipient of message, net mail


CPIO {[0;1;31m
!J“§ã¨¥œ ¢áŸ¦ª œšš¨˜­ãª/˜¤áš¤à©ª ¡˜«á «¤ ˜¤« š¨˜­ã «¦¬ £¤ç£˜«¦ª.
˜¨˜¡˜¢¦ç£œ œ ›¦§¦ ã©«œ «¦¤ ®œ ¨ ©«ã ©¬©«ã£˜«¦ª š ˜ « ª ©¬¤Ÿã¡œª §¦¬ ¦›ãš©˜¤
©«¦ ¢áŸ¦ª.!)
[0;1m} T Copy message: I/O error




FWNOAXES {[0;1;31m
!JŠ¬§á£˜ , ›œ¤ â®œ«œ §¨æ©™˜© ©œ ˜¬«ã «¤ œ§ ¢¦šã.!)
[0;1m} T Forward message, access denied


FWWHO {[0;1m
‚¨á¯«œ ¯œ¬›é¤¬£¦ ã club §¦¬ Ÿ˜ §¨¦àŸã©œ«œ «¦ £ã¤¬£˜
([33m?[37m š ˜ ™¦ãŸœ ˜) [Enter=Sysop]: [0m} T Forward message, ask for recipient


FWERR {[0;1;31m
!JŠ¬§á£˜ , ›œ¤ £§¦¨œå«œ ¤˜ ®¨© £¦§¦ ã©œ«œ ¢å©«œª › ˜¤¦£ãª ©œ ˜¬«æ
©£œå¦.!)
[0;1m} T Forward message, can't use distribution lists here


FWCERR {[0;1;31m
!JŠ¬§á£˜ , «¦ œ§å§œ›¦ §¨æ©™˜©ãª ©˜ª ©«¦ club [37m%s[31m ›œ¤ œ§ «¨â§œ 
«¤ ˜§¦©«¦¢ã £¤¬£á«à¤.!)
[0;1m} T Forward message, no WRITE access to target club


FWCERR2 {[0;1;31m
!JŠ¬§á£˜ , «¦ œ§å§œ›¦ §¨æ©™˜©ãª ©˜ª ©«¦ club [37m%s[31m ›œ¤ œ§ «¨â§œ 
«¤ ˜§¦©«¦¢ã ©¬¤££â¤à¤ ˜¨®œåà¤. ’¦ ©¬¤££â¤¦ ©œ ˜¬«æ «¦ £ã¤¬£˜ ˜¨®œå¦
›œ¤ £§¦¨œå ¤˜ §¨¦àŸŸœå. † §¨¦éŸ© «¦¬ £¤ç£˜«¦ª ©«˜£˜«áœ 
š ˜ ¤˜ £¤ ®á©œ«œ «¦ ©¬¤££â¤¦ ˜¨®œå¦.!)
[0;1m} T Forward message, no UPLOAD access to target club


FWRCPOK {[0;1;32m
!J˜¨˜¢ã§«ª «¦¬ £¤ç£˜«¦ª Ÿ˜ œå¤˜  «¦ £â¢¦ª [37m%s[32m.!)
[0;1m} T Forward message: confirming recipient of message


FWRCPOKN {[0;1;32m
!J’¦ £ã¤¬£˜ Ÿ˜ §¨¦àŸŸœå £â©à Internet Mail ©«¤ › œçŸ¬¤© [37m%s[32m.!)
[0;1m} T Forward message: confirming recipient of message, net mail



FWIO {[0;1;31m
!J“§ã¨¥œ ¢áŸ¦ª œšš¨˜­ãª/˜¤áš¤à©ª ¡˜«á «¤ §¨¦éŸ© «¦¬ £¤ç£˜«¦ª.
˜¨˜¡˜¢¦ç£œ œ ›¦§¦ ã©«œ «¦¤ ®œ ¨ ©«ã ©¬©«ã£˜«¦ª š ˜ « ª ©¬¤Ÿã¡œª §¦¬ ¦›ãš©˜¤
©«¦ ¢áŸ¦ª.!)
[0;1m} T Forward message: I/O error


FWCONF {[0;1;31m
!J‰á§¦ ¦ª á¢¢¦ª ®¨ã©«ª œ¨šáœ«˜  £œ ˜¬«æ «¦ £ã¤¬£˜.
’¦ £œ«˜™ ™˜©£â¤¦ £ã¤¬£˜ ›œ¤ £§¦¨œå ¤˜ › ˜š¨˜­œå «é¨˜,
˜¨šæ«œ¨˜ §á¤«àª £§¦¨œå«œ ¤˜ «¦ ©™ã©œ«œ £æ¤¦ª ©˜ª, ˜¤
Ÿâ¢œ«œ. ˜¨'æ¢˜ ˜¬«á «¦ £ã¤¬£˜ â®œ  §¨¦àŸŸœå.!)
[0;1m} T Forward message: cant' erase due to conflicts


BKERR {[0;1;31m
!JŠ¬§á£˜ , «¦ £ã¤¬£˜ ›œ¤ œå¤˜  ˜§œ¬Ÿœå˜ª ˜§á¤«© ©œ ¡á§¦ ¦ á¢¢¦.!)
[0;1m} T Backtrack: message is not a reply


DLMNU {[2J[0m[47;1;37m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;30;47m¿ [40m
[47;1;37m ³  [0;47;30m                    Šå©«˜ ƒ ˜¤¦£ãª ‹¤¬£á«à¤                     [0;47;30m³ [40m
[47;1;37m ³  [0;47;30mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ  [0;47;30m³ [40m
[47;1;37m ³  [0;31;47mH[30melp . . . . . . . . . . . . .  ¦ãŸœ ˜ š ˜ « ª ¢å©«œª › ˜¤¦£ãª  [30m³ [40m
[47;1;37m ³  [0;31;47mL[30mist addresses. . . . . . ‰˜«á¢¦š¦ª › œ¬Ÿç¤©œà¤ ¢å©«˜ª › ˜¤¦£ãª  [30m³ [40m
[47;1;37m ³  [0;31;47mA[30mdd address. . . . . . . .  ¨æ©Ÿœ© £ ˜ª › œçŸ¬¤©ª ©«¤ ¢å©«˜  [30m³ [40m
[47;1;37m ³  [0;31;47mD[30melete address  . . . .  ƒ ˜š¨˜­ã £ ˜ª › œçŸ¬¤©ª ˜§æ «¤ ¢å©«˜  [30m³ [40m
[47;1;37m ³                                                                   [0;47;30m³ [40m
[47;1;37m ³ [0;30;47me[31mX[30mit  . . . . . . . . . . . . . . . . . . . . . . . . . . „¥¦›¦ª  [30m³ [40m
[47;1;37m À[0;30;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0;1m
[0;1m} T Distribution list, menu


DLMNUS {[0;1m
Šå©«˜ ƒ ˜¤¦£ãª ‹¤¬£á«à¤
!Wƒé©«œ «¤ œ§ ¢¦šã ©˜ª ([33mH[37m,[33mL[37m,[33mA[37m,[33mD[37m,[33mX[37m š ˜ â¥¦›¦, ã [33m?[37m š ˜ «¦ £œ¤¦ç): !)[0m} T Distribution list, short menu


DLSMNU {[2J[0m[47;1;37m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;30;47m¿ [40m
[47;1;37m ³  [0;47;30m                    Šå©«˜ ƒ ˜¤¦£ãª ‹¤¬£á«à¤                     [0;47;30m³ [40m
[47;1;37m ³  [0;47;30mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ  [0;47;30m³ [40m
[47;1;37m ³  [0;31;47mH[30melp . . . . . . . . . . . . .  ¦ãŸœ ˜ š ˜ « ª ¢å©«œª › ˜¤¦£ãª  [30m³ [40m
[47;1;37m ³  [0;31;47mL[30mist addresses. . . . . . ‰˜«á¢¦š¦ª › œ¬Ÿç¤©œà¤ ¢å©«˜ª › ˜¤¦£ãª  [30m³ [40m
[47;1;37m ³  [0;31;47mA[30mdd address. . . . . . . .  ¨æ©Ÿœ© £ ˜ª › œçŸ¬¤©ª ©«¤ ¢å©«˜  [30m³ [40m
[47;1;37m ³  [0;31;47mD[30melete address  . . . .  ƒ ˜š¨˜­ã £ ˜ª › œçŸ¬¤©ª ˜§æ «¤ ¢å©«˜  [30m³ [40m
[47;1;37m ³  [0;31;47mP[30mrotect distribution list  . . . . .  ¨¦©«˜©å˜ ¢å©«˜ª › ˜¤¦£ãª  [30m³ [40m
[47;1;37m ³  [0;31;47mS[30melect distribution list . . . . . . .  „§ ¢¦šã ¢å©«˜ª › ˜¤¦£ãª  [30m³ [40m
[47;1;37m ³  [0;31;47mK[30mill current list . . . . . . . . . . ƒ ˜š¨˜­ã «¨â®¦¬©˜ª ¢å©«˜ª  [30m³ [40m
[47;1;37m ³                                                                   [0;47;30m³ [40m
[47;1;37m ³ [0;30;47me[31mX[30mit  . . . . . . . . . . . . . . . . . . . . . . . . . . „¥¦›¦ª  [30m³ [40m
[47;1;37m À[0;30;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0;1m
[0;1m} T Distribution list, menu


DLSMNUS {[0;1m
Šå©«˜ ƒ ˜¤¦£ãª ‹¤¬£á«à¤ («¨â®¦¬©˜ ¢å©«˜: [32m!%s[37m)
!Wƒé©«œ «¤ œ§ ¢¦šã ©˜ª ([33mH[37m,[33mL[37m,[33mA[37m,[33mD[37m,[33mP[37m,[33mS[37m,[33mK[37m,[33mX[37m š ˜ â¥¦›¦, ã [33m?[37m š ˜ «¦ £œ¤¦ç): !)[0m} T Distribution list, short menu


DLNOAX {[0;1;31m
Š¬§á£˜ , ›œ¤ â®œ«œ §¨æ©™˜© ©œ ˜¬«ã «¤ œ§ ¢¦šã.
[0;1;31m} T Distribution list, access denied


DLERRS {[0;1;31m
!JŠ¬§á£˜ , ˜¬«ã  œ§ ¢¦šã ›œ¤ œå¤˜  ›¬¤˜«ã.!)
[0;1m} T Distribution List, invalid selection


DLHELP {[0;1m

!J„›é £§¦¨œå«œ ¤˜ ¦¨å©œ«œ £â®¨  %d › œ¬Ÿç¤©œ ª (œå«œ «¦§ ¡âª, œå«œ Internet)
©« ª ¦§¦åœª £§¦¨œå«œ ¤˜ ©«â¢¤œ«œ › ˜¤œ££â¤˜ £¤ç£˜«˜. ‚ ˜ ¤˜ ©«œå¢œ«œ â¤˜
› ˜¤œ££â¤¦ £ã¤¬£˜, ›é©«œ '!' ˜¤«å š ˜ §˜¨˜¢ã§« «¦¬ £¤ç£˜«¦ª.!)

!J‹œ «¤ œ¤«¦¢ã [33mL[37m £§¦¨œå«œ ¤˜ ›œå«œ « ª › œ¬Ÿç¤©œ ª §¦¬ §œ¨ ¢˜£™á¤œ 
 ¢å©«˜ ˜¬«ã «¤ ©« š£ã. ‹œ [33mA[37m £§¦¨œå«œ ¤˜ §¨¦©Ÿâ©œ«œ £å˜ › œçŸ¬¤©
©«¤ ¢å©«˜. ‹œ [33mD[37m › ˜š¨á­œ«œ £å˜ › œçŸ¬¤©.!)

!J† ®¨âà© ˜§¦©«¦¢ãª œ¤æª › ˜¤œ££â¤¦¬ £¤ç£˜«¦ª  ©¦ç«˜  £œ «¦
áŸ¨¦ ©£˜ «ª ®¨âà©ª š ˜ «¤ ˜§¦©«¦¢ã ˜¤«åš¨˜­¦¬ «¦¬ £¤ç£˜«¦ª ©œ ¡áŸœ £â¢¦ª
«ª ¢å©«˜ª. ‹§¦¨œå«œ ¤˜ ›œå«œ §æ©¦ Ÿ˜ ©˜ª ¡¦©«å©œ  â¤˜ › ˜¤œ££â¤¦ £ã¤¬£˜ £œ
«¤ œ¤«¦¢ã [33mL[37m.!)

[0;1m} T Distribution List, help


DLHELPS {[0;1m

!J„›é £§¦¨œå«œ ¤˜ ¦¨å©œ«œ £â®¨  %d › œ¬Ÿç¤©œ ª (œå«œ «¦§ ¡âª, œå«œ Internet)
©« ª ¦§¦åœª £§¦¨œå«œ ¤˜ ©«â¢¤œ«œ › ˜¤œ££â¤˜ £¤ç£˜«˜. ‚ ˜ ¤˜ ©«œå¢œ«œ â¤˜
› ˜¤œ££â¤¦ £ã¤¬£˜, ›é©«œ '!' ¡˜  «¦ æ¤¦£˜ «ª ¢å©«˜ª ˜¤«å š ˜ §˜¨˜¢ã§« «¦¬ £¤ç£˜«¦ª.
 §˜¨˜¡á«à §å¤˜¡˜ª ›å¤œ  « ª › á­¦¨œª ¢å©«œª ¡˜  §éª ©¬¤«á©¦¤«˜ .!)

!CÚÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
³ [33m!.Sysop   [37m³ [32m† §¨¦©à§ ¡ã ¢å©«˜ «¦¬ ®¨ã©« Sysop                     [37m³
³ [33m!         [37m³ [32m‘¬¤é¤¬£¦ £œ «¤ §¨¦©à§ ¡ã ©˜ª ¢å©«˜                    [37m³
³ [33m!mass     [37m³ [32mŠˆ ¦  ®¨ã©«œª.                                       [37m³
³ [33m!all      [37m³ [32m’¦ å› ¦.                                               [37m³
³ [33m!!<class> [37m³ [32m¢¦  ¦  ®¨ã©«œª £å˜ª ¡¢á©ª (§.®. !!DEMO ã !!OPERATOR) [37m³
³ [33m!listname [37m³ [32m† ¢å©«˜ › ˜¤¦£ãª £œ æ¤¦£˜ listname.                    [37m³
ÀÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ!)

!J  › ˜­¦¨âª ¡œ­˜¢˜åà¤/£ ¡¨é¤ ›œ¤ §˜å¦¬¤ ¨æ¢¦.!)

!J‹œ «¤ œ¤«¦¢ã [33mL[37m £§¦¨œå«œ ¤˜ ›œå«œ « ª › œ¬Ÿç¤©œ ª §¦¬ §œ¨ ¢˜£™á¤œ 
 ¢å©«˜ ˜¬«ã «¤ ©« š£ã. ‹œ [33mA[37m £§¦¨œå«œ ¤˜ §¨¦©Ÿâ©œ«œ £å˜ › œçŸ¬¤©
©«¤ ¢å©«˜. ‹œ [33mD[37m › ˜š¨á­œ«œ £å˜ › œçŸ¬¤©. ‹œ [33mP[37m £§¦¨œå«œ ¤˜
§œ¨ ¦¨å©œ«œ «¤ ®¨ã© «ª ¢å©«˜ª ˜§æ á¢¢¦¬ª. ’â¢¦ª, £œ [33mS[37m ­¦¨«é¤œ«œ
£å˜ á¢¢ ¢å©«˜.!)

!J† ®¨âà© ˜§¦©«¦¢ãª œ¤æª › ˜¤œ££â¤¦¬ £¤ç£˜«¦ª  ©¦ç«˜  £œ «¦
áŸ¨¦ ©£˜ «ª ®¨âà©ª š ˜ «¤ ˜§¦©«¦¢ã ˜¤«åš¨˜­¦¬ «¦¬ £¤ç£˜«¦ª ©œ ¡áŸœ £â¢¦ª
«ª ¢å©«˜ª. ‹§¦¨œå«œ ¤˜ ›œå«œ §æ©¦ Ÿ˜ ©˜ª ¡¦©«å©œ  â¤˜ › ˜¤œ££â¤¦ £ã¤¬£˜ £œ
«¤ œ¤«¦¢ã [33mL[37m.!)

[0;1m} T Distribution List, help for the privileged


DLLISTH {[0;1m

Šå©«˜:  [32m!%s[37m
‰¢œ ›å: [32m%d[37m

‹â¢ ¢å©«˜ª:

[0;1;32m} T Distribution list, address list header


DLLISTL {%3d. %s
} T Distribution list, address list

DLLISTF {[0;1m
‰æ©«¦ª £¤ç£˜«¦ª: [32m%d £¦¤á›%s[37m
[0;1m} T Distribution list, address list footer


DLAR1 {[0;1;31m
!JŠ¬§á£˜ , ›œ¤ £§¦¨œå«œ ¤˜ §¨¦©Ÿâ©œ«œ §á¤à ˜§æ [37m%d[31m
£â¢ ©«¤ ¢å©«˜.!)
[0;1m} T Distribution list, add, too many members


DLANNET {[0;1;31m
!JŠ¬§á£˜ , «¦ œ§å§œ›¦ §¨æ©™˜©ãª ©˜ª ›œ¤ ©˜ª œ§ «¨â§œ  ¤˜ â®œ«œ
› œ¬Ÿç¤©œ ª Internet àª £â¢ «ª ¢å©«˜ª › ˜¤¦£ãª ©˜ª.!)
[0;1m} T Distribution list, add, can't specify net address


DLAUNKID {[0;1;31m
!Jƒœ¤ ¬§á¨®œ  ®¨ã©«ª "[37m%s[31m".!)
[0;1m} T Distribution list, add, unknown user


DLADUPL {[0;1;31m
!J€¬«ã  › œçŸ¬¤© ¬§á¨®œ  ã› ©« ¢å©«˜.!)
[0;1m} T Distribution list, add, duplicate address


DLAWHO {[0;1m
!Wƒé©«œ « › œçŸ¬¤© §¦¬ Ÿâ¢œ«œ ¤˜ §¨¦©Ÿâ©œ«œ ©«¤ ¢å©«˜ ([33m?[37m š ˜ ¡˜«á¢¦š¦ £œ¢é¤):!) [0m} T Distribution list, add, whom?


DLDR1 {[0;1;31m
!J† ¢å©«˜ œå¤˜  ã› ¡œ¤ã.!)
[0;1m} T Distribution list, delete, list is empty


DLDASK {[0;1m
!Wƒé©«œ «¦¤ ˜¨ Ÿ£æ «ª › œçŸ¬¤©ª §¦¬ Ÿâ¢œ«œ ¤˜ ˜­˜ ¨â©œ«œ ([33m%d[37m-[33m%d[37m, ã [33m?[37m š ˜ ¡˜«á¢¦š¦ £œ¢é¤):!) [0m} T Distribution list, delete, whom?


DLDERR {[0;1;31m
!Jƒé©«œ â¤˜¤ ˜¨ Ÿ£æ ©«¦ › á©«£˜ [33m%d[37m-[33m%d[37m.!)
[0;1m} T Distribution list, delete, error


DLPASK {[0;1m
!Wƒé©«œ «¦ ¡¢œ ›å §¦¬ ˜§˜ «œå«˜  š ˜ §¨æ©™˜© ©œ ˜¬«ã «¤ ¢å©«˜ ([33m0[37m = ®à¨åª
§¨¦©«˜©å˜, [33m1[37m-[33n128[37m = ¡¢œ ›å, [33m129[37m = £æ¤¦ «¦ ¯œ¬›é¤¬£¦ Sysop):!) [0m} T Distribution list, set protection


DLPERR {[0;1;31m
!J˜¨˜¡˜¢é ›é©«œ â¤˜¤ ˜¨ Ÿ£æ ˜§æ [37m%d[31m àª [37m%d[31m. ‘£œ é©«œ æ«  £æ¤¦ «¦
¯œ¬›é¤¬£¦ [37mSysop[31m £§¦¨œå ¤˜ «ã©œ  «¦ ¡¢œ ›å 129.!)
[0;1m} T Distribution list, set protection, error


DLSASK {[0;1m
!Wƒé©«œ «¦ æ¤¦£˜ «ª ¢å©«˜ª §¦¬ Ÿâ¢œ«œ ¤˜ ­¦¨«é©œ«œ ([33m?[37m š ˜ ¡˜«á¢¦š¦):!) [0m} T Distribution list, select list


DLSERR1 {[0;1;31m
!J˜¨˜¡˜¢é ›é©«œ «¦ §¢ã¨œª æ¤¦£˜ «ª ¢å©«˜ª, £˜å £œ «¦ '!'.!)
[0;1m} T Distribution list, select list, bad list name


DLSERR2 {[0;1;31m
!J’¦ æ¤¦£˜ §¦¬ ›é©˜«œ §œ¨ â®œ  £ ˜§¦›œ¡«¦çª ®˜¨˜¡«ã¨œª.!)
[0;1m} T Distribution list, select list, bad characters in name


DLSERR3 {[0;1;31m
!JŠ¬§á£˜ , ›œ¤ £§¦¨œå«œ ¤˜ «¤ ˜¢¢á¥œ«œ «¤ ¢å©«˜ "%s".!)
[0;1m} T Distribution list, select list, access denied


DLKASK {[0;1m
!W‡â¢œ«œ ©åš¦¬¨˜ ¤˜ › ˜š¨á¯œ«œ «¤ «¨â®¦¬©˜ ¢å©«˜; [[33mY[37m]yes=¤˜  / [[33mN[37m]o=æ® )!) [0m} T Distribution list, kill list?


DLKERR {[0;1;31m
!J˜¨˜¡˜¢é ˜§˜¤«ã©«œ £œ [33mY[31m ã [33mN[31m.!)
[0;1m} T Distritbution list, kill list, error


LSTLSTH {[0;1m

“€•“‘„‘ Šˆ‘’„‘ ƒˆ€Œ‹†‘:
!FÄ
[32m} T List of lists, header


LSTLST {!%s
} T List of lists, table entry


LSTLSTF {[0;1m!FÄ
} T List of lists, footer







MSGHDR1 {
[0;1;32m%s/%d  %s
†‹/Œˆ€: [36m%-38.38s[32m  %31.31s
€:    [36m%-42.42s  [32m%s
‘:   [36m%s%-48.48s  [0;1;32m%21.21s
‡„‹€:   [36m%-54.54s  [32m%15.15s
} T Message header, top part


MSGHDR2 {€•„ˆ: [36m%-52s  [32m%17s
} T Message header, optional file attachment part


MSGHDR3 {} T Message header, bottom part


MHFORU {[5m} T Message header, message for you (clubs only)


MHALL {¢¦¬ª} T Message header, string for 'All'


MHDAY0 {‰¬¨ ˜¡ã} T Message header, string for Sunday
MHDAY1 {ƒœ¬«â¨˜} T Message header, string for Monday
MHDAY2 {’¨å«} T Message header, string for Tuesday
MHDAY3 {’œ«á¨«} T Message header, string for Wednesday
MHDAY4 {â£§«} T Message header, string for Thursday
MHDAY5 {˜¨˜©¡œ¬ã} T Message header, string for Friday
MHDAY6 {‘á™™˜«¦} T Message header, string for Saturday


MHJAN {ˆ˜¤¦¬˜¨å¦¬} T Message header, string for January
MHFEB {”œ™¨¦¬˜¨å¦¬} T Message header, string for February
MHMAR {‹˜¨«å¦¬} T Message header, string for March
MHAPR {€§¨ ¢å¦¬} T Message header, string for April
MHMAY {‹˜ä¦¬} T Message header, string for May
MHJUN {ˆ¦¬¤å¦¬} T Message header, string for June
MHJUL {ˆ¦¬¢å¦¬} T Message header, string for July
MHAUG {€¬š¦ç©«¦¬} T Message header, string for August
MHSEP {‘œ§«œ£™¨å¦¬} T Message header, string for September
MHOCT {¡«à™¨å¦¬} T Message header, string for October
MHNOV {Œ¦œ£™¨å¦¬} T Message header, string for November
MHDEC {ƒœ¡œ£™¨å¦¬} T Message header, string for December

MHPERIOD {œ¨ ¦› ¡æ, ˜¤á %d £â¨%s} T Message header, string for 'periodic'

MHXMPT {‹ › ˜š¨á¯ £¦} T Message header, string for 'exempt'

MHRRR {…«ãŸ¡œ ˜§æ›œ ¥ ˜¤áš¤à©ª} T Message header, string for 'return receipt requested'
        
MHTMRD {ƒ ˜™á©«¡œ %d ­¦¨%s} T Message header, string for 'read x times'

MHNREP {%d %s} T Message header, string for 'x replies'

MHNDNL {„¢ã­Ÿ %d ­¦¨%s} T Message header, string for 'downloaded x times'


TIMSNG {á} T 'Times', singular form
TIMPLR {âª} T 'Times', plural form

REPSNG {˜§á¤«©} T 'Reply', singular form
REPPLR {˜§˜¤«ã©œ ª} T 'Replies', plural form


















CLNONTR {[0;1;31m
Š¬§á£˜ , ›œ¤ â®œ«œ §¨æ©™˜© ©« ª „ › ¡âª œ¨ ¦®âª (Clubs).
[0;1m} T User does not have access to the Clubs module


BANNERH {[2J} T Club banner header

BANNERF {} T Club banner footer


CLMNU1 {[2J[0m[47;1;37m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;30;47m¿ [0m
[47;1;37m ³  [0;47;30m              „ › ¡âª œ¨ ¦®âª (Clubs)                 [0;47;30m³ [0m
[47;1;37m ³  [0;47;30mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ  [0;47;30m³ [0m
[47;1;37m ³  [0;31;47mH[30melp  . . . . . . . . . . . . . . ‚œ¤ ¡âª ¢¨¦­¦¨åœª  [30m³ [0m
[47;1;37m ³  [0;31;47mI[30mnformation  . . . . . . . .  ¢¨¦­¦¨åœª š ˜ «¦ club  [30m³ [0m
[47;1;37m ³  [0;31;47mL[30mist clubs . . . . . . . . . . . . .  ‰˜«á¢¦š¦ª clubs  [30m³ [0m
[47;1;37m ³  [0;31;47mR[30mead messages . . . . . . . . . .  €¤áš¤à© £¤¬£á«à¤  [30m³ [0m
[47;1;37m ³  [0;31;47mW[30mrite message  . . . . . . . . . . €§¦©«¦¢ã £¤ç£˜«¦ª  [30m³ [0m
[47;1;37m ³  [0;31;47mD[30mownload file . . . . . . . . . . . . .  Šã¯ ˜¨®œå¦¬  [30m³ [0m
[47;1;37m ³  [0;31;47mT[30meleconference . . . .  ‰˜¤á¢  «¢œ©¬¤¦£ ¢é¤ «¦¬ Club  [30m³ [0m
[47;1;37m ³  [0;31;47mB[30mulletins . . . . . . .  €¤˜š¤à©«ã¨ ¦ á¨Ÿ¨à¤ «¦¬ Club  [30m³ [0m
[47;1;37m ³  [0;31;47mS[30melect club  . . . . . . . . . . . . . . „§ ¢¦šã club  [30m³ [0m
[47;1;37m ³                                                         [0;47;30m³ [0m
[47;1;37m ³ [0;30;47me[31mX[30mit . . . . . . . . . . . . . . . . . . . . .  „¥¦›¦ª  [30m³ [0m
[47;1;37m À[0;30;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0;1m

„ › ¡âª §œ¨ ¦®âª (Clubs)
!W¨å©¡œ©«œ ©«¦ club [32m@CLUB@: @CLUBDESC@[37m.!)
˜¨˜¡˜¢é ›é©«œ «¤ œ§ ¢¦šã ©˜ª: [0m} T Club main menu, non-privileged version


SHCLMNU1 {[0;1m
!W¨å©¡œ©«œ ©«¦ club [32m@CLUB@: @CLUBDESC@[37m.!)
!Wƒé©«œ «¤ œ§ ¢¦šã ©˜ª ([33mH[37m,[33mI[37m,[33mL[37m,[33mR[37m,[33mW[37m,[33mD[37m,[33mT[37m,[33mB[37m,[33mS[37m,[33mX[37m š ˜ â¥¦›¦, ã [33m?[37m š ˜ «¦ £œ¤¦ç): !)[0m} T Club short menu, non-privileged version


CLMNU2 {[2J[0m[47;1;37m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;30;47m¿ [0m
[47;1;37m ³  [0;47;30m              „ › ¡âª œ¨ ¦®âª (Clubs)                 [0;47;30m³ [0m
[47;1;37m ³  [0;47;30mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ  [0;47;30m³ [0m
[47;1;37m ³  [0;31;47mH[30melp  . . . . . . . . . . . . . . ‚œ¤ ¡âª ¢¨¦­¦¨åœª  [30m³ [0m
[47;1;37m ³  [0;31;47mI[30mnformation  . . . . . . . .  ¢¨¦­¦¨åœª š ˜ «¦ club  [30m³ [0m
[47;1;37m ³  [0;31;47mL[30mist clubs . . . . . . . . . . . . .  ‰˜«á¢¦š¦ª clubs  [30m³ [0m
[47;1;37m ³  [0;31;47mR[30mead messages . . . . . . . . . .  €¤áš¤à© £¤¬£á«à¤  [30m³ [0m
[47;1;37m ³  [0;31;47mW[30mrite message  . . . . . . . . . . €§¦©«¦¢ã £¤ç£˜«¦ª  [30m³ [0m
[47;1;37m ³  [0;31;47mD[30mownload file . . . . . . . . . . . . .  Šã¯ ˜¨®œå¦¬  [30m³ [0m
[47;1;37m ³  [0;31;47mT[30meleconference . . . .  ‰˜¤á¢  «¢œ©¬¤¦£ ¢é¤ «¦¬ Club  [30m³ [0m
[47;1;37m ³  [0;31;47mB[30mulletins . . . . . . .  €¤˜š¤à©«ã¨ ¦ á¨Ÿ¨à¤ «¦¬ Club  [30m³ [0m
[47;1;37m ³  [0;31;47mA[30mpprove files  . . . „š¡¨ © ˜¨®œåà¤ ([31m%03d[30m œ¤ ˜¤˜£¦¤ã)  [30m³ [0m
[47;1;37m ³  [0;31;47mS[30melect club . . . . . . . . . . . . . .  „§ ¢¦šã club  [30m³ [0m
[47;1;37m ³                                                         [0;47;30m³ [0m
[47;1;37m ³ [0;30;47me[31mX[30mit  . . . . . . . . . . . . . . . . . . . . . „¥¦›¦ª  [30m³ [0m
[47;1;37m À[0;30;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0;1m

„ › ¡âª §œ¨ ¦®âª (Clubs)
!W‰˜¢à©ã¢Ÿ˜«œ, ¦¨š˜¤à«á, ©«¦ club [32m@CLUB@: @CLUBDESC@[37m.!)
˜¨˜¡˜¢é ›é©«œ «¤ œ§ ¢¦šã ©˜ª: [0m} T Club main menu, co-op version


SHCLMNU2 {[0;1m
!W‰˜¢à©ã¢Ÿ˜«œ, ¦¨š˜¤à«á, ©«¦ club [32m@CLUB@: @CLUBDESC@[37m.!)
!Wƒé©«œ «¤ œ§ ¢¦šã ©˜ª ([33mH[37m,[33mI[37m,[33mL[37m,[33mR[37m,[33mW[37m,[33mD[37m,[33mT[37m,[33mB[37m,[33mA[37m,[33mS[37m,[33mX[37m
š ˜ â¥¦›¦, ã [33m?[37m š ˜ «¦ £œ¤¦ç): !)[0m} T Club short menu, co-op version


CLMNU3 {[2J[0m[47;1;37m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;30;47m¿ [0m
[47;1;37m ³  [0;47;30m              „ › ¡âª œ¨ ¦®âª (Clubs)                 [0;47;30m³ [0m
[47;1;37m ³  [0;47;30mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ  [0;47;30m³ [0m
[47;1;37m ³  [0;31;47mH[30melp . . . . . . . . . . . . . .  ‚œ¤ ¡âª ¢¨¦­¦¨åœª  [30m³ [0m
[47;1;37m ³  [0;31;47mI[30mnformation . . . . . . . . . ¢¨¦­¦¨åœª š ˜ «¦ club  [30m³ [0m
[47;1;37m ³  [0;31;47mL[30mist clubs . . . . . . . . . . . . .  ‰˜«á¢¦š¦ª clubs  [30m³ [0m
[47;1;37m ³  [0;31;47mR[30mead messages . . . . . . . . . .  €¤áš¤à© £¤¬£á«à¤  [30m³ [0m
[47;1;37m ³  [0;31;47mW[30mrite message  . . . . . . . . . . €§¦©«¦¢ã £¤ç£˜«¦ª  [30m³ [0m
[47;1;37m ³  [0;31;47mD[30mownload file . . . . . . . . . . . . .  Šã¯ ˜¨®œå¦¬  [30m³ [0m
[47;1;37m ³  [0;31;47mT[30meleconference  . . . . ‰˜¤á¢  «¢œ©¬¤¦£ ¢é¤ «¦¬ Club  [30m³ [0m
[47;1;37m ³  [0;31;47mB[30mulletins  . . . . . . . €¤˜š¤à©«ã¨ ¦ á¨Ÿ¨à¤ «¦¬ Club  [30m³ [0m
[47;1;37m ³  [0;31;47mA[30mpprove files . . .  „š¡¨ © ˜¨®œåà¤ ([31m%03d[30m œ¤ ˜¤˜£¦¤ã)  [30m³ [0m
[47;1;37m ³  [0;31;47mO[30mptions . . . . . . . . . . „¤«¦¢âª ¦¨š˜¤à«ã/®œ ¨ ©«ã  [30m³ [0m
[47;1;37m ³  [0;31;47mN[30metworking . . . . . . . . ƒ ˜¤¦£ã clubs £â©à › ¡«ç¦¬  [30m³ [0m
[47;1;37m ³  [0;31;47mS[30melect club . . . . . . . . . . . . . .  „§ ¢¦šã club  [30m³ [0m
[47;1;37m ³                                                         [0;47;30m³ [0m
[47;1;37m ³ [0;30;47me[31mX[30mit . . . . . . . . . . . . . . . . . . . . .  „¥¦›¦ª  [30m³ [0m
[47;1;37m À[0;30;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0;1m

„ › ¡âª §œ¨ ¦®âª (Clubs)
!W‰˜¢à©ã¢Ÿ˜«œ, ¦¨š˜¤à«á, ©«¦ club [32m@CLUB@: @CLUBDESC@[37m.!)
˜¨˜¡˜¢é ›é©«œ «¤ œ§ ¢¦šã ©˜ª: [0m} T Club main menu, club-op/privileged version


SHCLMNU3 {[0;1m
!W‰˜¢à©ã¢Ÿ˜«œ, ¦¨š˜¤à«á, ©«¦ club [32m@CLUB@: @CLUBDESC@[37m.!)
!Wƒé©«œ «¤ œ§ ¢¦šã ©˜ª ([33mH[37m,[33mI[37m,[33mL[37m,[33mR[37m,[33mW[37m,[33mU[37m,[33mT[37m,[33mB[37m,[33mA[37m,[33mO[37m,[33mS[37m,[33mX[37m
š ˜ â¥¦›¦, ã [33m?[37m š ˜ «¦ £œ¤¦ç): !)[0m} T Club short menu, club-op/privileged version


CLLEAVE {[0;1m
„¥¦›¦ª ˜§æ « ª „ › ¡âª œ¨ ¦®âª.
} T Exiting from Clubs module


CLABOUT {[0;1m

!J  „ › ¡âª œ¨ ¦®âª œå¤˜  ©ç¤¦¢˜ ›£æ© à¤ §¢¨¦­¦¨ é¤ (£¤¬£á«à¤, ˜¨®œåà¤
¡˜  á¨Ÿ¨à¤). ‹â©à ˜¬«¦ç «¦¬ £œ¤¦ç £§¦¨œå«œ ¤˜ ®œ ¨ ©«œå«œ £å˜ œ › ¡ã §œ¨ ¦®ã
(club).!)

!J‚ ˜ ¤˜ §á¨œ«œ §¢¨¦­¦¨åœª š ˜ «¦ «¨â®¦¤ club, ›é©«œ «¤ œ¤«¦¢ã
[33mI[37mnformation. ‚ ˜ ¤˜ œ§ ¢â¥œ«œ £ ˜ á¢¢ œ › ¡ã §œ¨ ¦®ã, ›é©«œ
[33mS[37melect. ‹§¦¨œå«œ ¤˜ ›œå«œ â¤˜¤ ©ç¤«¦£¦ ¡˜«á¢¦š¦ «à¤ clubs £œ «¤
œ¤«¦¢ã [33mS?[37m, ã â¤˜¤ §œ¨ œ¡« ¡æ«œ¨¦ ¡˜«á¢¦š¦ £œ [33mL[37mist
clubs.!)

!J‚ ˜ ¤˜ › ˜™á©œ«œ «˜ ›£æ© ˜ £¤ç£˜«˜ «¦¬ Club, ®¨© £¦§¦ ã©«œ «¤ œ¤«¦¢ã
[33mR[37mead messages, ¡˜  ˜¡¦¢¦¬Ÿã©«œ « ª œ¡œå ¦›šåœª. ‚ ˜ ¤˜ š¨á¯œ«œ
£¤ç£˜«˜, ®¨© £¦§¦ ã©«œ «¤ œ¤«¦¢ã [33mW[37mrite. ‚ ˜ ¤˜ › ˜™á©œ«œ ¡˜  ¤˜
š¨á¯œ«œ ˜§¦¡¢œ ©« ¡á ¡˜  £æ¤¦ £¤ç£˜«˜ £œ ©¬¤££â¤˜ ˜¨®œå˜, ®¨© £¦§¦ ã©«œ
« ª œ¤«¦¢âª [33mD[37mownload ¡˜  [33mU[37mpload file ˜¤«å©«¦ ®˜.
Šœ «¦¬¨š¦ç¤ ˜¡¨ ™éª æ§àª ¡˜  ¦  Read ¡˜  Write message. ’˜ ˜¨®œå˜ §¦¬
©«â¢¤œ«œ ®¨œ á¦¤«˜  âš¡¨ © ˜§æ «¦¤ ¨š˜¤à«ã §¨ ¤ šå¤¦¬¤ › ˜Ÿâ© £˜ ©«˜ £â¢
«¦¬ Club.!)

!J‰áŸœ Club â®œ  ¡˜  â¤˜ › ¡æ «¦¬ ¡˜¤á¢  ©« ª «¢œ©¬¤¦£ ¢åœª, £œ Ÿâ£˜ «¦
Ÿâ£˜ «¦¬ Club. „¡œå šå¤¦¤«˜  ¦  ©®œ« ¡âª £œ «¦ Club ©¬«ã©œ ª. ‹œ «¤
œ¤«¦¢ã [33mT[37meleconference £œ«˜­â¨œ©«œ ˜¬«¦£á«àª ©œ ˜¬«æ «¦ ¡˜¤á¢  «à¤
«¢œ©¬¤¦£ ¢ é¤.!)

!J‹§¦¨œå«œ ¤˜ › ˜™á©œ«œ «˜ á¨Ÿ¨˜ «¦¬ «¨â®¦¤«¦ª Club £œ «¤ œ¤«¦¢ã
[33mB[37mulletins, §¦¬ ©˜ª £œ«˜­â¨œ  ©«¦ €¤˜š¤à©«ã¨ ¦ €¨Ÿ¨à¤. ‹æ¤¦ ¦
¨š˜¤à«ãª «¦¬ club £§¦¨œå ¤˜ £œ«˜­â¨œ  â¤˜ £ã¤¬£˜ ©«¦ €¤˜š¤à©«ã¨ ¦. ‚ ˜ ¤˜
š¨á¯œ«œ â¤˜ á¨Ÿ¨¦, ˜§¢éª ©«œå¢«œ àª £ã¤¬£˜, ã àª ˜¨®œå¦ ©¬¤££â¤¦ ©œ â¤˜
£ã¤¬£˜ «¦¬ club.  ¨š˜¤à«ãª Ÿ˜ ˜¤˜¢á™œ  «˜ ¬§æ¢¦ §˜.!)

„§å§œ›˜ §¨æ©™˜©ª:

!J“§á¨®¦¬¤ §â¤«œ œ§å§œ›˜ §¨æ©™˜©ª ©«˜ clubs:!)

!WZero:     !10i‹›œ¤ ¡ã §¨æ©™˜©.  ®¨ã©«ª ›œ¤ £§¦¨œå ¤˜ §¨¦©§œ¢á©œ  ¡˜££å˜
˜§æ « ª ¬§¦§œ¨ ¦®âª «¦¬ club.!)
!0l
!WRead:     !10i¨æ©™˜© ˜¤áš¤à©ª £æ¤¦.  ®¨ã©«ª £§¦¨œå ¤˜ › ˜™á©œ 
£¤ç£˜«˜ ¡˜  á¨Ÿ¨˜, ˜¢¢á ›œ¤ £§¦¨œå ¤˜ ¢á™œ  ˜¨®œå˜.!)
!0l
!WDownload: !10i¨æ©™˜© ¢ã¯ª ˜¨®œåà¤.  ®¨ã©«ª £§¦¨œå ¤˜ › ˜™á©œ 
£¤ç£˜«˜ ¡˜  á¨Ÿ¨˜ ¡˜  ¤˜ ¢á™œ  ˜¨®œå˜. ƒœ¤ £§¦¨œå ¤˜ š¨á¯œ  £¤ç£˜«˜ ã ¤˜
©«œå¢œ  ˜¨®œå˜.!)
!0l
!WWrite:    !10i¨æ©™˜© ˜§¦©«¦¢ãª £¤¬£á«à¤. §àª ¡˜   Download
§¨æ©™˜©, ˜¢¢á ¦ ®¨ã©«ª £§¦¨œå ¡˜  ¤˜ š¨á¯œ  £¤ç£˜«˜.!)
!0l
!WUpload:   !10i¨æ©™˜© ˜§¦©«¦¢ãª ˜¨®œåà¤. §àª ¡˜   Write §¨æ©™˜©,
˜¢¢á ¦ ®¨ã©«ª £§¦¨œå ¡˜  ¤˜ ©«œå¢œ  ˜¨®œå˜ ©«¦ club.!)
!0l
[0;1m} T Clubs, about the module


CLINFO {
[0;36mÛÛ  [1m¢¨¦­¦¨åœª š ˜ «¦ club @CLUB@  [46m[K[0;1m

¨š˜¤à«ãª . . . . . . . . . . . @CLUBOP@
ƒ£ ¦¬¨šãŸ¡œ  . . . . . . . .  @CLUBCRDATE@, @CLUBCRTIME@
‹¤ç£˜«˜  . . . . . . . . . . . @CLUBMSGS@
€¨®œå˜ . . . . . . . . . . . .  @CLUBFILES@
€¨Ÿ¨˜ . . . . . . . . . . . . . @CLUBBLTS@
•¨âà© . . . . . . . . . . . .  @CHARGE@ credits/¢œ§«æ
•¨âà© ˜§¦©«¦¢ãª £¤ç£˜«¦ª  . . @CLUBPOSTCHG@ credit(s)
•¨âà© ˜§¦©«¦¢ãª ˜¨®œå¦¬ . . .  @CLUBUPLCHG@ credit(s)
•¨âà© ¢ã¯ª ˜¨®œå¦¬  . . . . . @CLUBDNLCHG@ credit(s)

[46m[K[0;1m
} T Club information



OPMNU {[2J[0m[47;1;37m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;30;47m¿ [0m
[47;1;37m ³  [0;47;30m           „¤«¦¢âª •œ ¨ ©«ã/¨š˜¤à«ã Club              [0;47;30m³ [0m
[47;1;37m ³  [0;47;30mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ  [0;47;30m³ [0m
[47;1;37m ³  [0;31;47mH[30melp  . . . . . . . . . . . . . . ‚œ¤ ¡âª ¢¨¦­¦¨åœª  [30m³ [0m
[47;1;37m ³  [0;31;47mN[30mew club . . . . . . . . . . . . . .  ƒ£ ¦¬¨šå˜ club  [30m³ [0m
[47;1;37m ³  [0;31;47mD[30melete club . . . . . . . . . . . . . . ƒ ˜š¨˜­ã club  [30m³ [0m
[47;1;37m ³  [0;31;47mE[30mdit club  . . . . . . . . . . €¢¢˜šã §˜¨˜£â«¨à¤ club  [30m³ [0m
[47;1;37m ³  [0;31;47mA[30mccess levels . . . . . . . €¢¢˜šã œ§ §â›à¤ §¨æ©™˜©ª  [30m³ [0m
[47;1;37m ³  [0;31;47mM[30modify charges . . . . . . . . . . .  €¢¢˜šã ®¨œé©œà¤  [30m³ [0m
[47;1;37m ³  [0;31;47mC[30monfigure user  . . . . . .  €¢¢˜šã §¨æ©™˜©ª ®¨©«é¤  [30m³ [0m
[47;1;37m ³                                                         [0;47;30m³ [0m
[47;1;37m ³ [0;30;47me[31mX[30mit . . . . . . . . . . . . . . . . . . . . .  „¥¦›¦ª  [30m³ [0m
[47;1;37m À[0;30;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0;1m

¨å©¡œ©«œ ©«¦ Club [32m@CLUB@: @CLUBDESC@[37m.
[0;1m} T Club operation menu, long version


SHOPMNU {[0;1m
!Wƒé©«œ «¤ œ§ ¢¦šã ©˜ª ([33mH[37m,[33mN[37m,[33mD[37m,[33mE[37m,[33mA[37m,[33mM[37m,[33mC[37m,[33mX[37m
š ˜ â¥¦›¦, ã [33m?[37m š ˜ «¦ £œ¤¦ç): !)[0m} T Club operation menu, short version



OPHELP {[2J[0;1m
!J‹œ «¤ ™¦ãŸœ ˜ ˜¬«¦ç «¦¬ £œ¤¦ç £§¦¨œå«œ ¤˜ ¡á¤œ«œ «˜ œ¥ãª
(©£œ é©«œ æ«  ˜¤á¢¦š˜ £œ «¦ œ§å§œ›¦ §¨æ©™˜©ãª ©˜ª, ¦¨ ©£â¤œª œ¤«¦¢âª £§¦¨œå ¤˜ £¤
œå¤˜  › ˜Ÿâ© £œª):!)

!J‹œ «¤ œ¤«¦¢ã New Club £§¦¨œå«œ ¤˜ ›£ ¦¬¨šã©œ«œ â¤˜ ¤â¦ club.
‹œ «¤ œ¤«¦¢ã Delete Club £§¦¨œå«œ ¤˜ › ˜š¨á¯œ«œ â¤˜ club.!)

!J‹œ «¤ œ¤«¦¢ã Edit Club â®œ«œ «¤ ›¬¤˜«æ««˜ ¤˜ ˜¢¢á¥œ«œ ¦¨ ©£â¤œª
§˜¨˜£â«¨¦¬ª «¦¬ «¨â®¦¤«¦ª club, æ§àª «¤ §œ¨ š¨˜­ã «¦¬, «¤ › á¨¡œ ˜
àãª «à¤ £¤¬£á«à¤, ¡˜  «¦ ©ã£˜ (banner) «¦¬. † œ¤«¦¢ã Access levels
œ§ «¨â§œ  ¤˜ ¦¨å©œ«œ «¤ §¨æ©™˜© «à¤ ®¨©«é¤ ©«¦ «¨â®¦¤ club. ‹œ «¤
œ§æ£œ¤ œ¤«¦¢ã, Modify charges, œ¢âš®œ«œ «¤ ®¨âà© «à¤ ®¨©«é¤ §¦¬
› ˜™á¦¬¤ «¦ club. ’â¢¦ª, £œ «¤ œ¤«¦¢ã Configure user £§¦¨œå«œ ¤˜ ¦¨å©œ«œ
«¦ œ§å§œ›¦ §¨æ©™˜©ª œ¤æª ©¬š¡œ¡¨ £â¤¦¬ ®¨ã©« ©«¦ «¨â®¦¤ club.!)

[0;1m} T Club operation menu help





ECVT {[0;30;47m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [34m˜¨á£œ«¨¦  Club[0;30;47m ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;1;37;47m¿ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  œ¨ š¨˜­ã club . . . . . [1;44;37m@63;43;0s[0;1;47;37m  ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  ƒ á¨¡œ ˜ £¤¬£á«à¤  . .  [1;44;37m@5;0;32767;0n[0;30;47m  £â¨œª        (0-32767, 0=š ˜ §á¤«˜)[1;37m  ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  Ctrl-R š ˜ ™¦ãŸœ ˜                                                      [1;37m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³             [0;1;42;33m@14;"‘ã£˜"b[0;47;30mÜ    [0;1;42;33m@14;"OK"b[0;47;30mÜ    [0;1;41;33m@14;"€¡¬¨¦"b[0;47;30mÜ  [0;1;47;37m³ [0m
[30;47m ³              ßßßßßßßßßßßßßßßß     ßßßßßßßßßßßßßßßß     ßßßßßßßßßßßßßßßß  [0;1;47;37m³ [0m
[30;47m À[0;1;37;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0m} T Edit club, visual template


ECLT {[2J[0;30;47m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [34m˜¨á£œ«¨¦  club[0;30;47m ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;1;37;47m¿ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m1[30m. œ¨ š¨˜­ã club  . . . .  [34m@63;43;0s[0;1;47m  ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m2[30m. ƒ á¨¡œ ˜ £¤¬£á«à¤  . .  [34m@5;0;32767;0n[30m (£â¨œª, 0=š ˜ §á¤«˜)                  [1;37;47m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m3[30m. ‹œ«˜™¦¢ã ©ã£˜«¦ª (banner)@1;"3Edit"b                                           [1;37m  ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m À[0;1;37;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0;1m
} T Edit club, linear template


ECFLD1 {[0;1m
!J˜¨˜¡˜¢é ›é©«œ « ¤â˜ §œ¨ š¨˜­ã «¦¬ club.!)
[0;1m} T Edit club, linear template, field 1


ECFLD2 {[0;1m
!J˜¨˜¡˜¢é ›é©«œ « ¤â˜ › á¨¡œ ˜ àãª «à¤ £¤¬£á«à¤ «¦¬ club ©œ £â¨œª.
’¦ §œ›å¦ ›â®œ«˜  « £âª ˜§æ 0 àª 32767. €¤ ›é©œ«œ 0, «˜ £¤ç£˜«˜ «¦¬ club Ÿ˜ › ˜«¨¦ç¤«˜ 
œ§'˜æ¨ ©«¦¤.!)
[0;1m} T Edit club, linear template, field 2


ECCAN {[0;1;31m
!J† £œ«˜™¦¢ã «¦¬ club ˜¡¬¨éŸ¡œ.!)
[0;1m} T Edit club, edit aborted


ECDONE {[0;1;32m
!J† £œ«˜™¦¢ã «¦¬ club «â¢œ à©œ £œ œ§ «¬®å˜.!)
[0;1m} T Edit club, edit successful




AXLVT {[0;30;47m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [34m„§å§œ›˜ §¨æ©™˜©ª Club[0;30;47m ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;1;37;47m¿ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  €§˜ «¦ç£œ¤¦ ¡¢œ ›å š ˜ READ §¨æ©™˜© ©«¦ club  . . . . [1;44;37m@3;0;129;1n[0;47;30m  (0..129)  [1;37m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  €§˜ «¦ç£œ¤¦ ¡¢œ ›å š ˜ DOWNLOAD §¨æ©™˜© ©«¦ club . .  [1;44;37m@3;0;129;1n[0;47;30m  (0..129)  [1;37m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  €§˜ «¦ç£œ¤¦ ¡¢œ ›å š ˜ WRITE §¨æ©™˜© ©«¦ club . . . . [1;44;37m@3;0;129;1n[0;47;30m  (0..129)  [1;37m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  €§˜ «¦ç£œ¤¦ ¡¢œ ›å š ˜ UPLOAD §¨æ©™˜© ©«¦ club . . .  [1;44;37m@3;0;129;1n[0;47;30m  (0..129)  [1;37m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  (’˜ œ§å§œ›˜  CO-OP ¡˜  CLUB-OP ›œ¤ £§¦¨¦ç¤ ¤˜ ›àŸ¦ç¤  £˜ ¡á. •¨© £¦-  [1;37m³ [0m
[30;47m ³  §¦ ã©«œ «¤ œ¤«¦¢ã [1;33mC[0;30;47monfigure user š ˜ ¤˜ ›é©œ«œ ˜¬«á «˜ œ§å§œ›˜ ©œ £œ-  [1;37m³ [0m
[30;47m ³  £¦¤¦£â¤¦¬ª ®¨ã©«œª).                                                    [1;37m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  Ctrl-R š ˜ ™¦ãŸœ ˜                                                      [1;37m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³                                  [0;1;42;33m@14;"OK"b[0;47;30mÜ    [0;1;41;33m@14;"€¡¬¨¦"b[0;47;30mÜ  [0;1;47;37m³ [0m
[30;47m ³                                   ßßßßßßßßßßßßßßßß     ßßßßßßßßßßßßßßßß  [0;1;47;37m³ [0m
[30;47m À[0;1;37;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0m} T Club Access levels, visual template


AXLLT {[2J[0;30;47m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [34m„§å§œ›˜ §¨æ©™˜©ª Club[0;30;47m ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;1;37;47m¿ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m1[30m. €§˜ «¦ç£œ¤¦ ¡¢œ ›å š ˜ READ §¨æ©™˜© ©«¦ club  . . . . . . . . . [34m@3;0;129;1n[0;1;47m  ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m2[30m. €§˜ «¦ç£œ¤¦ ¡¢œ ›å š ˜ DOWNLOAD §¨æ©™˜© ©«¦ club . . . . . . .  [34m@3;0;129;1n[0;1;47m  ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m3[30m. €§˜ «¦ç£œ¤¦ ¡¢œ ›å š ˜ WRITE §¨æ©™˜© ©«¦ club . . . . . . . . . [34m@3;0;129;1n[0;1;47m  ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m4[30m. €§˜ «¦ç£œ¤¦ ¡¢œ ›å š ˜ UPLOAD §¨æ©™˜© ©«¦ club . . . . . . . .  [34m@3;0;129;1n[0;1;47m  ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  (’˜ œ§å§œ›˜  CO-OP ¡˜  CLUB-OP ›œ¤ £§¦¨¦ç¤ ¤˜ ›àŸ¦ç¤  £˜ ¡á. •¨© £¦-  [1;37m³ [0m
[30;47m ³  §¦ ã©«œ «¤ œ¤«¦¢ã [1;33mC[0;30;47monfigure user š ˜ ¤˜ ›é©œ«œ ˜¬«á «˜ œ§å§œ›˜ ©œ £œ-  [1;37m³ [0m
[30;47m ³  £¦¤¦£â¤¦¬ª ®¨ã©«œª).                                                    [1;37m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m À[0;1;37;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0;1m
} T Club Access levels, linear template


AXLF1 {[0;1m
!J  ®¨ã©«œª £œ READ §¨æ©™˜© £§¦¨¦ç¤ ¤˜ ›¦¬¤ «¦ club ¡˜  ¤˜ › ˜™á©¦¬¤ «˜ £¤ç£˜«á «¦¬.
ƒœ¤ £§¦¨¦ç¤ æ£àª ¤˜ ¢á™¦¬¤ ˜¨®œå˜, ¤˜ š¨á¯¦¬¤ £¤ç£˜«˜ ã ¤˜ ©«œå¢¦¬¤ ˜¨®œå˜.
ƒé©«œ «¦ ¡¢œ ›å §¦¬
˜§˜ «œå«˜  š ˜ ¤˜ â®œ  â¤˜ª ®¨ã©«ª READ §¨æ©™˜© ©œ ˜¬«æ «¦ club.!)
[0;1m} T Club Access levels, linear template field 1


AXLF2 {[0;1m
!J  ®¨ã©«œª £œ DOWNLOAD §¨æ©™˜© £§¦¨¦ç¤ ¤˜ ›¦¬¤ «¦ club,
¤˜ › ˜™á©¦¬¤ «˜ £¤ç£˜«á «¦¬,
¡˜  ¤˜ ¢á™¦¬¤ «˜ ˜¨®œå˜ «¦¬. ƒœ¤ £§¦¨¦ç¤ ¤˜ š¨á¯¦¬¤ £¤ç£˜«˜
ã ¤˜ ©«œå¢¦¬¤ ˜¨®œå˜. ƒé©«œ «¦ ¡¢œ ›å §¦¬
˜§˜ «œå«˜  š ˜ ¤˜ â®œ  â¤˜ª ®¨ã©«ª DOWNLOAD §¨æ©™˜© ©œ ˜¬«æ «¦ club.!)
[0;1m} T Club Access levels, linear template field 2


AXLF3 {[0;1m
!J  ®¨ã©«œª £œ WRITE §¨æ©™˜© £§¦¨¦ç¤ ¤˜ ›¦¬¤ «¦ club,
¤˜ › ˜™á©¦¬¤ ¡˜  ¤˜ š¨á¯¦¬¤ £¤ç£˜«˜, ¡˜  ¤˜ ¢á™¦¬¤ ˜¨®œå˜.
ƒœ¤ £§¦¨¦ç¤ £æ¤¦ ¤˜ ©«œå¢¦¬¤ ˜¨®œå˜.
ƒé©«œ «¦ ¡¢œ ›å §¦¬ ˜§˜ «œå«˜  š ˜ ¤˜ â®œ  â¤˜ª ®¨ã©«ª
WRITE §¨æ©™˜© ©œ ˜¬«æ «¦ club.!)
[0;1m} T Club Access levels, linear template field 3


AXLF4 {[0;1m
!J  ®¨ã©«œª £œ UPLOAD §¨æ©™˜© £§¦¨¦ç¤ ¤˜ ›¦¬¤ «¦ club,
¤˜ › ˜™á©¦¬¤ ¡˜  ¤˜ š¨á¯¦¬¤ £¤ç£˜«˜,
¡˜  ¤˜ ¢á™¦¬¤ ¡˜  ¤˜ ˜§¦©«œå¢¦¬¤ ˜¨®œå˜.
ƒé©«œ «¦ ¡¢œ ›å §¦¬
˜§˜ «œå«˜  š ˜ ¤˜ â®œ  â¤˜ª ®¨ã©«ª UPLOAD §¨æ©™˜© ©œ ˜¬«æ «¦ club.!)
[0;1m} T Club Access levels, linear template field 4


WRNDEFC {[0;1;33m
!J€¬«æ œå¤˜  «¦ default club, ©«¦ ¦§¦å¦ §¨â§œ  ¤˜ â®¦¬¤ §¨æ©™˜© æ¢¦  ¦ 
®¨ã©«œª. ’¦ ¡¢œ ›å ˜¤áš¤à©ª «¦¬ club âš ¤œ ¡˜  Ÿ˜ §˜¨˜£œå¤œ  [37m0[33m.!)
[0;1m} T Club Access levels, the default club has to be readable by all







CHVT {[0;30;47m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [34m•¨œé©œ ª Club[0;30;47m ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;1;37;47m¿ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  •¨âà© š ˜ «¤ œšš¨˜­ã £¤ç£˜«¦ª . . . . . . [1;44;37m@6;-30000;30000;1n[0;47;30m  (-30000..30000)  [1;37m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  •¨âà© š ˜ «¤ ˜§¦©«¦¢ã ˜¨®œå¦¬ . . . . . .  [1;44;37m@6;-30000;30000;1n[0;47;30m  (-30000..30000)  [1;37m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  •¨âà© š ˜ «¤ ¢ã¯ ˜¨®œå¦¬  . . . . . . . . [1;44;37m@6;-30000;30000;1n[0;47;30m  (-30000..30000)  [1;37m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  ‰˜«˜¤á¢à© credits (credits/100 ¢œ§«á)  . .  [1;44;37m@6;-30000;30000;1n[0;47;30m  (-30000..30000)  [1;37m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  († ¡˜«˜¤á¢à© credits œå¤˜  ©œ credits ˜¤á 100 ¢œ§«á.  ƒ¢˜›ã, š ˜ ¡˜-  [1;37m³ [0m
[30;47m ³  «˜¤á¢à© 1  credit/¢œ§«æ, ›é©«œ  «¤ « £ã 100.  ƒé©«œ -1 š ˜ «¤  ¡˜«á  [1;37m³ [0m
[30;47m ³  ©¬¤Ÿã¡ ¡˜«˜¤á¢à© ©« ª „ › ¡âª œ¨ ¦®âª)                               [1;37m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  Ctrl-R š ˜ ™¦ãŸœ ˜                                                      [1;37m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³                                  [0;1;42;33m@14;"OK"b[0;47;30mÜ    [0;1;41;33m@14;"€¡¬¨¦"b[0;47;30mÜ  [0;1;47;37m³ [0m
[30;47m ³                                   ßßßßßßßßßßßßßßßß     ßßßßßßßßßßßßßßßß  [0;1;47;37m³ [0m
[30;47m À[0;1;37;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0m} T Club charges, visual template


CHLT {[2J[0;30;47m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [34m„§å§œ›˜ §¨æ©™˜©ª Club[0;30;47m ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;1;37;47m¿ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m1[30m. •¨âà© š ˜ «¤ œšš¨˜­ã £¤ç£˜«¦ª  . . . . . . . . . . . . . . [34m@6;-30000;30000;1n[0;1;47m  ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m2[30m. •¨âà© š ˜ «¤ ˜§¦©«¦¢ã ˜¨®œå¦¬  . . . . . . . . . . . . . .  [34m@6;-30000;30000;1n[0;1;47m  ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m3[30m. •¨âà© š ˜ «¤ ¢ã¯ ˜¨®œå¦¬ . . . . . . . . . . . . . . . . . [34m@6;-30000;30000;1n[0;1;47m  ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m4[30m. ‰˜«˜¤á¢à© credits (credits/100 ¢œ§«á)  . . . . . . . . . . . [34m@6;-30000;30000;1n[0;1;47m  ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  († ¡˜«˜¤á¢à© credits œå¤˜  ©œ credits ˜¤á 100 ¢œ§«á.  ƒ¢˜›ã, š ˜ ¡˜-  [1;37m³ [0m
[30;47m ³  «˜¤á¢à© 1  credit/¢œ§«æ, ›é©«œ  «¤ « £ã 100.  ƒé©«œ -1 š ˜ «¤  ¡˜«á  [1;37m³ [0m
[30;47m ³  ©¬¤Ÿã¡ ¡˜«˜¤á¢à© ©« ª „ › ¡âª œ¨ ¦®âª)                               [1;37m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m À[0;1;37;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0;1m
} T Club charges, linear template


CHLTF1 {[0;1m
!Jƒé©«œ «¦ §¦©æ £¦¤á›à¤ §¦¬ Ÿ˜ ®¨œé¤œ«˜  ¦ ®¨ã©«ª ¡áŸœ ­¦¨á §¦¬ Ÿ˜ š¨á­œ  â¤˜ £ã¤¬£˜ ©«¦ club.!)
[0;1m} T Club charges, linear template, field 1


CHLTF2 {[0;1m
!Jƒé©«œ «¦ §¦©æ £¦¤á›à¤ §¦¬ Ÿ˜ ®¨œé¤œ«˜  ¦ ®¨ã©«ª ¡áŸœ ­¦¨á §¦¬ Ÿ˜ ©«â¢¤œ  â¤˜ ˜¨®œå¦ ©«¦ club.!)
[0;1m} T Club charges, linear template, field 2


CHLTF3 {[0;1m
!Jƒé©«œ «¦ §¦©æ £¦¤á›à¤ §¦¬ Ÿ˜ ®¨œé¤œ«˜  ¦ ®¨ã©«ª ¡áŸœ ­¦¨á §¦¬ Ÿ˜ ¢˜£™á¤œ  â¤˜ ˜¨®œå¦ ˜§æ «¦ club.!)
[0;1m} T Club charges, linear template, field 3


CHLTF4 {[0;1m
!J‰áŸœ club £§¦¨œå ¤˜ â®œ  › ˜­¦¨œ« ¡ã ®¨¦¤¦®¨âà©. ‘œ ˜¬«æ «¦ §œ›å¦ ¦¨åœ«œ §æ©œª £¦¤á›œª Ÿ˜ ˜­˜ ¨¦ç¤«˜  ˜§æ
«¦¤ ®¨ã©« ˜¤á 100 ¢œ§«á §˜¨¦¬©å˜ª ©«¦ club. „«© , š ˜ «¤ ¡˜¤¦¤ ¡ã ®¨âà© «¦¬ 1 credit / ¢œ§«æ, ›é©«œ ©«¦
§œ›å¦ «¤ « ¡ã 100 (100 credits / 100 ¢œ§«á = 1 credit / ¢œ§«æ). €¤ Ÿâ¢œ«œ «¦ club ¤˜ â®œ  «¤ ¡˜«á ©¬¤Ÿã¡
®¨âà© «à¤ œ › ¡é¤ §œ¨ ¦®é¤, ›é©«œ ©«¦ §œ›å¦ «¤ « £ã -1.!)
[0;1m} T Club charges, linear template, field 4






CUASK {[0;1m
!Wƒé©«œ «¦ æ¤¦£˜ «¦¬ ®¨ã©« «¦¬ ¦§¦å¦¬ Ÿâ¢œ«œ ¤˜ £œ«˜™á¢¢œ«œ «¦ œ§å§œ›¦:!)[0m } T Configure user access, which user?


CUERR1 {[0;1;31m
!WŠ¬§á£˜ , ˜¬«æª ¦ ®¨ã©«ª ›œ¤ ¬§á¨®œ .!)
[0;1m} T Configure user access, unknown user


CUERR2 {[0;1;31m
!W‘ šá, §œ¨å£œ¤œ... ƒœ¤ £§¦¨¦ç£œ ¤˜ §œ¨ ¦¨å©¦¬£œ «¦ œ§å§œ›¦ «¦¬ ©ç©¦§˜! €¬«æª â®œ  §á¤«˜ ©¬©¦§ ¡ã §¨æ©™˜©!!)
[0;1m} T Configure user access, can't modify Sysop


CUHLP {[0;1m

“§á¨®¦¬¤ «˜ œ¥ãª œ§å§œ›˜:

Default    !i!W† æ§¦ ˜ œ › ¡ã §¨æ©™˜© ˜­˜ ¨œå«˜ , ¡˜  ¦ ®¨ã©«ª
˜§¦¡«á «¤ ¡˜«á ©¬¤Ÿã¡ §¨æ©™˜© «¦¬ club §¦¬ «¦¬ ˜¤˜¢¦šœå,
æ§àª ˜¬«ã ¦¨åœ«˜  £â©à «ª œ¤«¦¢ãª [33mM[37m.!)
!0l
Zero       !i!W ®¨ã©«ª ›œ¤ ™¢â§œ  «¦ club, ¡˜  ›œ¤ â®œ  ¡˜££å˜ §¨æ©™˜© ©'˜¬«æ.!)
!0l
Read       !i!W ®¨ã©«ª £§¦¨œå £æ¤¦ ¤˜ › ˜™á©œ  £¤ç£˜«˜.!)
!0l
Download   !i!W ®¨ã©«ª £§¦¨œå ¤˜ › ˜™á©œ  £¤ç£˜«˜ ¡˜  ¤˜ ¢á™œ  ˜¨®œå˜.!)
!0l
Write      !i!W ®¨ã©«ª £§¦¨œå ¤˜ › ˜™á©œ  £¤ç£˜«˜, ¤˜ š¨á¯œ  £¤ç£˜«˜, ¡˜  ¤˜ ¢á™œ  ˜¨®œå˜.!)
!0l
Upload     !i!W§àª «¦ Write, ˜¢¢á ¦ ®¨ã©«ª £§¦¨œå ¡˜  ¤˜ ©«œå¢œ  ˜¨®œå˜.!)
!0l
Co-op      !i!W ®¨ã©«ª œå¤˜  ¦¨š˜¤à«ãª «¦¬ club. „®œ  §¢ã¨ §¨æ©™˜© ©«¦ club, ¡˜  £§¦¨œå
¤˜ ©«â¢¤œ  ˜¨®œå˜ §¦¬ ›œ¤ ®¨œ á¦¤«˜  âš¡¨ ©, ¤˜ œš¡¨å¤œ  ˜¨®œå˜, ¡¢§.!)
!0l
Club-op    !i!W ®¨ã©«ª œå¤˜  ¦ ™˜© ¡æª ¦¨š˜¤à«ãª «¦¬ club. „®œ  « ª å› œª ›¬¤˜«æ««œª £œ
«¦¤ ©¬¤¦¨š˜¤à«ã (Co-op), £œ £æ¤ › ˜­¦¨á æ«  â®œ  «¦ › ¡˜åà£˜ ¤˜ ˜¢¢á¥œ  «¤ §¨æ©™˜©
®¨©«é¤ ©«¦ club. ‹§¦¨œå ¤˜ ¬§á¨®œ  £æ¤¦ â¤˜ª ™˜© ¡æª ¦¨š˜¤à«ãª, ¦§æ«œ, ˜¤ ¦¨å©œ«œ á¢¢¦
¦¨š˜¤à«ã š ˜ «¦ «¨â®¦¤ club, ¦ ¬§á¨®à¤ ¦¨š˜¤à«ãª œ¡«¦§åœ«˜ . ‹æ¤¦ ¦ ®œ ¨ ©«ãª (sysop) £§¦¨œå
¤˜ ¦¨å©œ  ¦¨š˜¤à«ã š ˜ â¤˜ club.!)
!0l
} T Configure user access, help on access levels


CUCUR {[0;1;32m
!W’¦ «¨â®¦¤ œ§å§œ›¦ «¦¬ £â¢¦¬ª [37m%s[32m œå¤˜  [37m%s[32m.!)
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
!J“§'æ¯ ¤: «¦ £â¢¦ª ˜¬«æ â®œ  §¨¦¤æ£ ˜ Sysop ©« ª „ › ¡âª œ¨ ¦®âª. „«© 
â®œ  §á¤«˜ ¡˜  §˜¤«¦ç §¨æ©™˜©. ’¦ œ§å§œ›¦ §¦¬ Ÿ˜ ¨¬Ÿ£å©œ«œ «é¨˜ Ÿ˜  ©®ç©œ 
£æ¤¦ ˜¤ ˜­˜ ¨œŸ¦ç¤ «˜ §¨¦¤æ£ ˜ ®œ ¨ ©«ã ˜§æ «¦¤ ®¨ã©«.!)
[0;1m} T Configure user access, warning about privileged user


CUMNU {[0;1m
˜¨˜¡˜¢é ›é©«œ «¤ ¤â˜ §¨æ©™˜© «¦¬ ®¨ã©«:
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
!Wƒé©«œ «¤ œ§ ¢¦šã ©˜ª ([33mD[37m,[33m0[37m-[33m6[37m,[33mX[37m š ˜ â¥¦›¦, ã [33m?[37m š ˜ ™¦ãŸœ ˜):!) [0m} T Configure user access, short level menu


CUMNUR {[0;1;31m
!WŠ¬§á£˜ , ˜¬«ã  œ§ ¢¦šã ›œ¤ ¬§á¨®œ . ƒé©«œ [33m?[31m š ˜ ™¦ãŸœ ˜.!)
[0;1m} T Configure user access, invalid selection


CUMNUR1 {[0;1;31m
!WŠ¬§á£˜ , £æ¤¦ ¦ •œ ¨ ©«ãª £§¦¨œå ¤˜ ¦¨å©œ  ¨š˜¤à«âª š ˜ «˜ Clubs.
ƒé©«œ [33m?[31m š ˜ ™¦ãŸœ ˜.!)
[0;1m} T Configure user access, only privileged users can set club-ops


CUMNUR2 {[0;1;31m
!WŠ¬§á£˜ , £æ¤¦ ¦ §¨à«˜¨® ¡æª ¦¨š˜¤à«ãª ã ¦ •œ ¨ ©«ãª £§¦¨œå ¤˜ ¦¨å©œ 
o¨š˜¤à«âª š ˜ «˜ Clubs. ƒé©«œ [33m?[31m š ˜ ™¦ãŸœ ˜.!)
[0;1m} T Configure user access, only club-ops can set co-club-ops


CUMNUR3 {[0;1;33m
!Jƒœ¤ £§¦¨œå«œ ¤˜ ˜§¦¡¢œå©œ«œ ®¨ã©«œª ˜§æ «¦ default club.!)
[0;1m} T Configure user access, the default club has to be readable by all



CUCHG {[0;1m
!W’¦ œ§å§œ›¦ «¦¬ £â¢¦¬ª [32m%s[37m ©«¦ club @CLUB@ á¢¢˜¥œ œ§ «¬®éª.!)
[0;1m} T Configure user access, user level set successfully


CUDIS {[0;1m
!W’¦ £â¢¦ª [32m%s[37m ®á¤œ  «¤ Ÿâ© «¦¬ ¦¨š˜¤à«ã «¦¬ club @CLUB@.!)
[0;1m} T Configure user access, current club operator lost their place


CUCNOT {[0;1;35m***
!J •œ ¨ ©«ãª ‘¬©«ã£˜«¦ª £æ¢ ª ©˜ª
â¡˜¤œ ¦¨š˜¤à«ã «¦¬ [37m%s[35m Club!
‘¬š®˜¨«ã¨ ˜ ¡˜  ¡˜¢ã œ§ «¬®å˜.!)
[0;1m} T Configure user access, notify new co-op/club-op









CRCASK {[0;1m
!Wƒé©œ «¦ æ¤¦£˜ «¦¬ Club £œšá¢œ ›£ ¦¬¨šâ ([33m?[37m š ˜ ¡˜«á¢¦š¦):!)[0m } T Create club, ask name


CRERR {[0;1;31m
!J® , ®˜¨ «à£â¤œ £¦¬, ›œ¤ £§¦¨œåª ¤˜ ­« á¥œ ª club £œ «â«¦ ¦ æ¤¦£˜!
’¦ ¦¤¦£˜«á¡  «¦¬ £§¦¨œå ¤˜'®œ  £â®¨  ¡˜  15 ®˜¨˜¡«ã¨œª, ¡˜  ¤˜ §œ¨ ¢˜£™á¤œ 
˜¢­˜¨ Ÿ£« ¡¦çª ®˜¨˜¡«ã¨œª, ã «¦¬ª œ¥ãª: # % ^ ( ) - _ + = [ ] .!)
[0;1m} T Create club, malformed club name


CRCXST {[0;1;31m
!J‹˜¤á¨  £¦¬ œ©ç... “§á¨®œ  [5mã›[0;31;1m ˜¬«æ «¦ Club ®££££££££££!
(‰á¤œ ¡˜  ¡˜¤â¤˜ CRQS §æ«œ §æ«œ)!)
[0;1m} T Create club, club already exists


CRCCNF {[0;1m
!J‹á'©«˜... ”« á®«¡œ ¡˜  «¦ "%s" Club.
€¤«œ «é¨˜ ¡˜  ©¦¬¢¦ç§à©â «¦ £œ « ª œ¤«¦¢âª
[33mE[37m, [33mA[37m ¡˜  [33mM[37m, œ¤«á¥œ ;!)
[0;1m} T Create club, confirm creation




DCASK {[0;1m
!W¦ ˜¤¦ç ­«à®¦ç «¦ Club Ÿœª ¤˜ ©­á¥œ ª; ([33m?[37m š ˜ ¡˜«á¢¦š¦):!)[0m } T Delete Club, what club?


DCUNK {[0;1;31m
!Jƒœ¤ ¬§á¨®œ  ˜¬«æ «¦ Club... ’©¡ «©¡ «©¡...!)
[0;1m} T Delete Club, unknown club


DCERR1 {[0;1;31m
!J‰¦å«˜ ¨œ §¦¬ §áœ  ¤˜ ­áœ  Club §¦ç â®œ  ¡æ©£¦ £â©˜...
‘™ã©œ ¡˜¢ç«œ¨˜ «¤ @BBS@ §¦¬ œå¤˜  á›œ ˜ ¨œ ˜›œ¨­á¡ ...
’é¨˜ §á¢  ˜¤ œ©ç â®œ ª ¡¦¢¢ã©œ  ¡˜  Ÿâª ˜¬«ã ¤˜ ¡á¤œ ª ¡˜¢¦¡˜ ¨ ¤ã ©é¤œ 
¡˜  ¡˜¢á, ¡˜¢ç«œ¨˜ Ÿ˜ ã«˜¤ ¤˜ §œ¨å£œ¤œª £â®¨  ¤˜ ­çš¦¬¤ æ¢¦  ˜§æ £â©˜...!)
} T Delete Club, Club is in use


DCERR2 {[0;1;31m
!J€ «¦ ¡˜£â¤¦... „¨à«œ¬£â¤¦ œå¤˜ ...
‹˜ ¡˜¢á, œå©˜  ©¦™˜¨æª «é¨˜;;;
’¦ default Club §˜ª ¤˜ ©™ã©œ ª;
€¤«œ æ¨ ©œ á¢¢¦ §¨é«˜ ¡˜  £œ«á «˜ ¢â£œ...
(€¢¢¦ª §á¢  ¡˜  ˜¬«æª...
¨â §¦¬ §â©˜£œ...)!)
} T Delete Club, can't delete default club


DCINFO {[0;1;32m
¤¦£˜  . . . . . . . .  [37m@CLUB@[32m
œ¨ š¨˜­ã . . . . . . . [37m@CLUBDESC@[32m
¨š˜¤à«ãª  . . . . . .  [37m@CLUBOP@[32m
‹¤ç£˜«˜  . . . . . . . [37m@CLUBMSGS@[32m
€¨®œå˜ . . . . . . . .  [37m@CLUBFILES@[32m
€¨Ÿ¨˜ . . . . . . . . . [37m@CLUBBLTS@[32m
[0;1m} T Delete Club, club information


DCCONF {[0;1;31m
!W[5mÛÛ[0;1;31m  ‘•†: !i€§˜¤«é¤«˜ª YES ©«¤ §˜¨˜¡á«à
œ¨é«© «¦ ©ç©«£˜ Ÿ˜ › ˜š¨á¯œ :!)
!W- ’¦ å› ¦ «¦ Club!)
!W- ’˜ £¤ç£˜«˜, «˜ ˜¨®œå˜ ¡˜  «˜ á¨Ÿ¨˜ «¦¬!)
!W- ¢˜ «˜ ©®œ« ¡á directories!)
!0l[0;1m
!W„å©˜  ©åš¦¬¨¦ª æ«  Ÿâ¢œ ª ¤˜ «¦ ©­á¥œ ª [[33mY[37m]yes=¤˜  / [[33mN[37m]o=æ® );!)[0m } T Delete Club, ask for confirmation


DCCR {[0;1;31m
!J˜¨˜¡˜¢é ˜§˜¤«ã©«œ ©«¤ œ¨é«© £œ [33mY[31m ã [33mN[31m.!)
[0;1m} T Delete Club, invalid answer


DCSNUK {[0;1;31m
!J’é¨˜ £á¢ ©«˜... €¤«œ ¤˜ §á¨œ ª ¢˜®œå¦ ¤˜ §¢¦¬«å©œ  ¦ ¢˜®œ ¦§é¢ª...
‰á§¦ ¦ª £§ã¡œ £â©˜ ©«¦ Club æ©¦ ™˜©á¤ œª ©«¦ £¬˜¢æ ©¦¬ «¦ ›å¢££˜
«ª àãª ¡˜  «¦¬ Ÿ˜¤á«¦¬ «¦¬.
‘¬¤â® ©œ ¤˜ «¦ ™˜©˜¤åœ ª ¡˜  ˜¤ œå¤˜  ¤˜ «¦
Ÿá¯œ ª â¢˜ æ«˜¤ Ÿ˜ â®œ  ­çšœ ...

(‰˜  ©¦¬'¢œš˜ šà ©™ã©œ «¤ Acrobase §¦¬ œå¤˜  á›œ ˜...)!)
[0;1m} T Delete Club, someone just entered the Club


DCWAIT {[0;1;32;5m
˜¨˜¡˜¢é §œ¨ £â¤œ«œ, æ¢˜ «˜ ©­áà æ¢˜ «˜ ¥œ¡¦ ¢ áà...[30m[K} T Delete Club, please wait


DCOK {[0;1;32m


áœ  «¦ Club, §á¤œ ¡˜  «˜ directories §¦¬ «¦¬ ˜¤ã¡˜¤.
[0;1m} T Delete Club, club deleted





LCHDR {[0;1m
[33mClub            •œ ¨ ©«ãª  œ¨ š¨˜­ã Club[37m
ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
[0m} T Short club list, header


LCTAB {%-15s %-10s %-50.50s
} T Short club list, table line


LCFTR {[0;1mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ

} T Short club list, footer


LC2HDR {[0;1m
       ÚÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄ¿
ÚÄÄÄÄÄÄ³ [33m‹¤ç£˜«˜[37m ³ [33m€¨®œå˜[37m ³ [33m€¨Ÿ¨˜[37m ³ [33mƒ£ ¦¬¨šå˜[37m ³ÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
³      ÀÄÄÄÄÄÄÄÄ¿ ÀÄÄ¿    ÚÙ   ÚÄÄÄÙ     ÚÄÄÄÄÄÄÙ    ³                       ³
³ [33mClub[37m          ³    ³    ³    ³         ³ [33m¨š˜¤à«ãª[37m ³ [33mœ¨ š¨˜­ã[37m             ³
ÃÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÅÄÄÄÄÅÄÄÄÄÅÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ´
[0;1m} T Long club list, header


LC2TAB {³[0m%-15s[1m³[0m%4d[1m³[0m%4d[1m³[0m%4d[1m³[0m%-9s[1m³[0m%-11s[1m³[0m%-23.23s[1m³
} T Long club list, table line


LC2FTR {[0;1mÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÁÄÄÄÄÁÄÄÄÄÁÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ

} T Long club list, footer



SCASK {[0;1m
!Wƒé©«œ «¦ æ¤¦£˜ «¦¬ ¤â¦¬ Club ã [33m?[37m š ˜ ¡˜«á¢¦š¦:!)[0m } T Select new club, what club?


SCERR {[0;1;31m
!J‘¬šš¤é£, ›œ¤ ¬§á¨®œ  «â«¦ ¦ Club.
ƒé©«œ [33mX[31m (eXit) ¦§¦ ˜›ã§¦«œ ©« š£ã š ˜ œ§ ©«¨¦­ã
©«¦ ¡œ¤«¨ ¡æ £œ¤¦ç «à¤ Clubs.!)
[0;1m} T Select new club, club does not exist


SCADD {[0;1;32m
!J’¦ club [37m%s[32m §¨¦©«âŸ¡œ ©«¤ š¨ãš¦¨ ˜¤å®¤œ¬©ã ©˜ª.!)
[0;1m} T Select new club, the club was added to your quickscan configuration







NETMNU {[2J[0m[47;1;37m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;30;47m¿ [0m
[47;1;37m ³  [0;47;30m           ƒ ˜¤¦£ã £¤¬£á«à¤ £â©à › ¡«ç¦¬              [0;47;30m³ [0m
[47;1;37m ³  [0;47;30mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ  [0;47;30m³ [0m
[47;1;37m ³  [0;31;47mH[30melp  . . . . . . . . . . . . . . ‚œ¤ ¡âª ¢¨¦­¦¨åœª  [30m³ [0m
[47;1;37m ³  [0;31;47mD[30mefine import BBSs . . . .  šâª œ ©˜šàšãª £¤¬£á«à¤  [30m³ [0m
[47;1;37m ³  [0;31;47mI[30mmport clubs  . . .  „ ©˜šàšã £¤¬£á«à¤ ˜§æ «¦ ›å¡«¬¦  [30m³ [0m
[47;1;37m ³  [0;31;47mE[30mxport clubs . . . . „¥˜šàšã £¤¬£á«à¤ §¨¦ª «¦ ›å¡«¬¦  [30m³ [0m
[47;1;37m ³  [0;31;47mS[30mtatus  . . . . .  ‰˜«á©«˜© œ ©˜šàšé¤ ˜¬«¦ç «¦¬ club  [30m³ [0m
[47;1;37m ³                                                         [0;47;30m³ [0m
[47;1;37m ³ [0;30;47me[31mX[30mit . . . . . . . . . . . . . . . . . . . . .  „¥¦›¦ª  [30m³ [0m
[47;1;37m À[0;30;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0;1m

[0;1m} T Networking menu, long version


SHNETMNU {[0;1m
!Wƒé©«œ «¤ œ§ ¢¦šã ©˜ª
([33mH[37m,[33mD[37m,[33mI[37m,[33mE[37m,[33mC[37m,[33mS[37m,[33mX[37m
š ˜ â¥¦›¦, ã [33m?[37m š ˜ «¦ £œ¤¦ç): !)[0m} T Networking menu, short version



NETHELP {[0;1m
!J’˜ £¤ç£˜«˜ «à¤ clubs £§¦¨¦ç¤ ¤˜ › ˜¤œ£Ÿ¦ç¤ £â©à › ¡«ç¦¬. €¬«æ œ¤¤¦œå «¤
œ ©˜šàšã £¤¬£á«à¤ ˜§æ á¢¢œª ™á©œ ª, ˜¢¢á ¡˜  «¤ œ¥˜šàšã «¦¬ª.!)

!J‚ ˜ «¤ œ ©˜šàšã £¤¬£á«à¤ §¨â§œ  ¤˜ ¦¨å©¦¬£œ (£œ «¤ œ¤«¦¢ã
[33mD[37mefine import BBSs) «˜ ¦¤æ£˜«˜ «à¤ ©¬©«£á«à¤ ˜§æ «˜ ¦§¦å˜ Ÿ˜
œ ©áš¦¬£œ £¤ç£˜«˜ ¡˜Ÿéª ¡˜  «¦ ®¨¦¤ ¡æ › á©«£˜ §¦¬ Ÿ˜ £œ©¦¢˜™œå £œ«˜¥ç
«à¤ œ ©˜šàšé¤ §˜¡â«à¤ £¤¬£á«à¤.!)

!J‹œ«á £§¦¨¦ç£œ ¤˜ ¦¨å©¦¬£œ «¦¤ §å¤˜¡˜ œ ©˜šàšãª clubs.  §å¤˜¡˜ª â®œ  ›ç¦
©«ã¢œª: «¦ › ˜¤œ££â¤¦ club ˜§'«¦ ¦§¦å¦ œ ©áš¦¬£œ £¤ç£˜«˜ ¡˜  «¦ «¦§ ¡æ club
©«¦ ¦§¦å¦ «˜ ˜§¦Ÿ¡œç¦¬£œ. ’¦ «¦§ ¡æ club ­¬© ¡á š¨á­œ«˜  ©˜¤ [32m/Club[37m.
’¦ › ˜¤œ££â¤¦ club â®œ  ˜¨¡œ«á › ˜­¦¨œ« ¡ã ©ç¤«˜¥. „§å §˜¨˜›œåš£˜« :!)

!C[32mhost.domain.tld/BBSNAME/Club[37m!)

!J’¦ §¨é«¦ £â¨¦ª œå¤˜   §¢ã¨ª Internet › œçŸ¬¤© «¦¬ £®˜¤ã£˜«¦ª §¦¬
­ ¢¦¥œ¤œå «¤ ™á©. €¡¦¢¦¬Ÿœå ¦ ¡à› ¡æª › ¡«çà©ª «ª ™á©ª (BBSNAME) ¡˜ 
«â¢¦ª «¦ æ¤¦£˜ «¦¬ club. ¨ ¤ §¨¦©Ÿâ©œ«œ œ ©˜šæ£œ¤˜ clubs ˜§æ £å˜ á¢¢ ™á©,
§¨â§œ  ¤˜ â®œ«œ ›¢é©œ  «¦ æ¤¦£˜ (host.domain.tld/BBSNAME) «¦¬ ˜§¦£˜¡¨¬©£â¤¦¬
©¬©«ã£˜«¦ª £œ «¤ œ¤«¦¢ã [33mD[37m (§˜¨˜§á¤à).!)

!J‚ ˜ ¤˜ œ¥áš¦¬£œ clubs ©œ á¢¢œª ™á©œ ª, ˜¨¡œå ¤˜ ®¨© £¦§¦ ã©¦¬£œ «¤ œ¤«¦¢ã
[33mE[37mxport clubs š ˜ ¤˜ ¦¨å©¦¬£œ §¦ ˜ ˜§æ «˜ clubs
£˜ª œå¤˜  «¦§ ¡á ¡˜  §¦ ˜ æ® .!)

!J’â¢¦ª, £œ «¤ œ¤«¦¢ã [33mS[37mtatus £§¦¨¦ç£œ ¤˜ ›¦ç£œ §¦ ˜ clubs œ ©áš¦¬¤
£¤ç£˜«˜ ˜§æ §¦ ˜ ©¬©«ã£˜«˜.!)
[0;1m} T Network menu help




DIPMNU {[0;1m
!W‡â¢œ«œ ¤˜ §¨¦©Ÿâ©œ«œ ([[33mA[37m]dd), ¤˜ £œ«˜™á¢¢œ«œ
([[33mM[37m]odify), ã ¤˜ › ˜š¨á¯œ«œ ([[33mD[37m]elete) â¤˜ ©ç©«£˜; ƒé©«œ
[33mA[37m, [33mM[37m, [33mD[37m, [33mX[37m š ˜ â¥¦›¦ ã [33m?[37m š ˜
¡˜«á¢¦š¦ ¬§˜¨®æ¤«à¤ ©¬©«£á«à¤:!)[0m } T Networking, operations on import points


DIPADD {[0;1m
!Jƒé©«œ «¦ æ¤¦£˜ «¦¬ ©¬©«ã£˜«¦ª §¦¬ Ÿâ¢œ«œ ¤˜ §¨¦©Ÿâ©œ«œ, ©« £¦¨­ã
[32mhost.domain.tld/BBSCODE[37m. ‰œ­˜¢˜å˜ ¡˜  £ ¡¨á
›œ¤ › ˜­â¨¦¬¤. ‹§¦¨œå«œ ¤˜ ®¨© £¦§¦ ã©œ«œ «¤
˜¨ Ÿ£« ¡ã IP › œçŸ¬¤© «¦¬ ©¬©«ã£˜«¦ª ˜¤ Ÿâ¢œ«œ. €¢¢ éª, §¨â§œ  ¤˜ ›é©œ«œ «¤
§¢ã¨ › œçŸ¬¤© «¦¬ ˜§¦£˜¡¨¬©£â¤¦¬ ©¬©«ã£˜«¦ª. ’¦ æ¤¦£˜ ›œ¤ œ¢âš®œ«˜  ˜§æ «¦
©ç©«£˜: §¨¦©¦®ã ©«˜ ¢áŸ!!)

!W¤¦£˜ ¤â¦¬ ©¬©«ã£˜«¦ª ˜§'æ§¦¬ Ÿ˜ œ ©áš¦¬£œ £¤ç£˜«˜:!)[0m } T Networking, add import point


DIPADR {[0;1;31m
!J† › œçŸ¬¤© «¦¬ ©¬©«ã£˜«¦ª ›œ¤ ›œå®¤œ  ©à©«ã. ¨â§œ  ¤˜ œå¤˜  ©«
£¦¨­ã [37mhost.domain.tld/BBSCODE[31m ã, ˜¤ ›œ¤ š¤à¨åœ«œ «¦ ˜¢­˜™« ¡æ
æ¤¦£˜ «¦¬ ©¬©«ã£˜«¦ª, [37mwww.xxx.yyy.zzz/BBSCODE[31m.!)
[0;1m} T Networking, incorrect remote BBS address


DIPADX {[0;1;31m
!J’¦ ©ç©«£˜ [37m%s[31m â®œ  ã› ›¢àŸœå.[31m!)
[0;1m} T Networking, system name already exists


DIPADT {[0;1m
!J’é¨˜ §¨â§œ  ¤˜ ¦¨å©œ«œ ¡áŸœ §æ«œ Ÿ˜ œ ©áš¦¬£œ £¤ç£˜«˜ ˜§æ «¦ §˜¨˜§á¤à
©ç©«£˜. ƒé©«œ â¤˜¤ ˜¨ Ÿ£æ £œ¨é¤ £œš˜¢ç«œ¨¦ «¦¬ £›â¤, ã â¤˜¤ ˜¨ Ÿ£æ
˜¡¦¢¦¬Ÿ¦ç£œ¤¦ ˜§æ «¦ œ§åŸœ£˜ [33mm[37m (minutes, ¢œ§«á) ã [33mh[37m
(hours, é¨œª). „§å §˜¨˜›œåš£˜« , ›å¤¦¤«˜ª ˜§¢á "1" ¦¨å¦¬£œ æ«   œ ©˜šàšã Ÿ˜
œ§ ®œ ¨œå«˜  ˜¤á £å˜ £â¨˜. ƒå¤¦¤«˜ª "15m", ˜¬«æ Ÿ˜ šå¤œ«˜  ˜¤á 15 ¢œ§«á.!)

!W„¢á® ©«¦ ®¨¦¤ ¡æ › á©«£˜ £œ«˜¥ç œ¤£œ¨é©œà¤:!)[0m } T Networking, asking for time between updates

DIPADTR {[0;1;31m
!J‘¬šš¤é£, ›œ¤ ˜¤˜š¤à¨å©˜£œ «¦ œ§åŸœ£˜ §¦¬ ®¨© £¦§¦ ã©˜«œ.!)
[0;1m} T Networking, time specification suffix was invalid


DIPADDOK {[0;1;32m
!J‰˜¢éª, «¦ ©ç©«£˜ [37m%s[32m ›¢éŸ¡œ œ§ «¬®éª. ‹¤ç£˜«˜ Ÿ˜ œ ©áš¦¤«˜ 
¡áŸœ [37m%d[32m ›œ¬«œ¨æ¢œ§«˜.!)
[0;1m} T Networking, system added




DIPDEL {[0;1m
!Jƒé©«œ «¦ æ¤¦£˜ «¦¬ ©¬©«ã£˜«¦ª §¦¬ Ÿâ¢œ«œ ¤˜ › ˜š¨á¯œ«œ, ã [33m?[37m š ˜
¡˜«á¢¦š¦ ©¬©«£á«à¤:!) [0m} T Networking, delete import point


DIPDELX {[0;1;31m
!J€¬«æ «¦ ©ç©«£˜ ›œ¤ â®œ  ›¢àŸœå.!)
[0;1m} T Networking, delete import point, system doesn't exist


DIPDELOK {[0;1;32m
!J„¤«á¥œ , «¦ ©ç©«£˜ [37m%s[32m › œš¨á­.!)
[0;1m} T Networking, system deleted



DIPMOD {[0;1m
!Jƒé©«œ «¦ æ¤¦£˜ «¦¬ ©¬©«ã£˜«¦ª §¦¬ Ÿâ¢œ«œ ¤˜ £œ«˜™á¢œ«œ, ã [33m?[37m š ˜
¡˜«á¢¦š¦ ©¬©«£á«à¤:!) [0m} T Networking, modify import point


DIPMODX {[0;1;31m
!J€¬«æ «¦ ©ç©«£˜ ›œ¤ â®œ  ›¢àŸœå.!)
[0;1m} T Networking, modify import point, system doesn't exist.


DIPMODT {[0;1;32m
!J„ ©áš¦¬£œ £¤ç£˜«˜ ˜§æ «¦ ©ç©«£˜ [37m%s[32m ¡áŸœ [37m%d[32m £â¨œª,
[37m%d[32m é¨œª ¡˜  [37m%d[32m ¢œ§«á.!)
[0;1m} T Networking, modify import point, show refresh time


DIPMODA {[0;1m
!J€¤ Ÿâ¢œ«œ ¤'˜¢¢á¥œ«œ «¦ §˜¨˜§á¤à, ›é©«œ â¤˜¤ ˜¨ Ÿ£æ £œ¨é¤ £œš˜¢ç«œ¨¦ «¦¬
£›â¤, ã â¤˜¤ ˜¨ Ÿ£æ ˜¡¦¢¦¬Ÿ¦ç£œ¤¦ ˜§æ «¦ œ§åŸœ£˜ [33mm[37m (minutes, ¢œ§«á)
ã [33mh[37m (hours, é¨œª). „§å §˜¨˜›œåš£˜« , ›å¤¦¤«˜ª ˜§¢á "1" ¦¨å¦¬£œ æ« 
 œ ©˜šàšã Ÿ˜ œ§ ®œ ¨œå«˜  ˜¤á £å˜ £â¨˜. ƒå¤¦¤«˜ª "15m", ˜¬«æ Ÿ˜ šå¤œ«˜  ˜¤á
15 ¢œ§«á.!)

!W„¢á® ©«¦ ®¨¦¤ ¡æ › á©«£˜ £œ«˜¥ç œ¤£œ¨é©œà¤: [[33mEnter[37m=æ®  ˜¢¢˜šã]!)[0m } T Networking, asking for new time between updates


DIPMODOK {[0;1;32m
!J„¤«á¥œ ,  ¡˜«˜®é¨© «¦¬ ©¬©«ã£˜«¦ª [[37m%s[[32m £œ«˜™¢ãŸ¡œ.!)
[0;1m} T Networking, system updated






IMPCLUB {[0;1m
!J˜¨˜¡˜¢é ›é©«œ «¦ æ¤¦£˜ «¦¬ ˜§¦£˜¡¨¬©£â¤¦¬ club ˜§æ «¦ ¦§¦å¦ Ÿ˜ œ ©áš¦¬£œ
£¤ç£˜«˜. † ©ç¤«˜¥ «¦¬ ˜§¦£˜¡¨¬©£â¤¦¬ club œå¤˜ 
[32mhost.domain.tld/BBSCODE/Club[37m. ¨¦©¦®ã: §â¨˜¤ «¦¬ ©¬¤«˜¤« ¡¦ç
œ¢âš®¦¬,  ¦¨Ÿæ««˜ «¦¬ ˜§¦£˜¡¨¬©£â¤¦¬ club ›œ¤ £§¦¨œå ¤˜ œ¢œš®Ÿœå! ¤¦£˜
˜§¦£˜¡¨¬©£â¤¦¬ club: !)[0m } T Networking, asking for name of remote club


IMPCLBR {[0;1;31m
!J’¦ æ¤¦£˜ «¦¬ ˜§¦£˜¡¨¬©£â¤¦¬ club ›œ¤ œå¤˜  ©¬¤«˜¡« ¡á ©à©«æ!!)
[0;1m} T Networking, invalid remote club path


IMPCLBS {[0;1;31m
!J’¦ æ¤¦£˜ «¦¬ ˜§¦£˜¡¨¬©£â¤¦¬ ©¬©«ã£˜«¦ª ›œ¤ â®œ  ›¢àŸœå ˜¡æ£˜!
•¨© £¦§¦ ã©«œ «¤ œ¤«¦¢ã [33mD[31m š ˜ ¤˜ «¦ §¨¦©Ÿâ©œ«œ.!)
[0;1m} T Networking, system name hasn't been declared


IMPLOCC {[0;1m
!J‘œ §¦ ¦ «¦§ ¡æ club ¤˜ œ¤˜§¦Ÿâ©¦¬£œ «˜ œ ©˜šæ£œ¤˜ £¤ç£˜«˜; ƒé©«œ
[33m?[37m š ˜ ¡˜«á¢¦š¦, ã [33m-[37m š ˜ ¤˜ ˜¡¬¨é©œ«œ «¤ œ ©˜šàšã
«¦¬ ˜§¦£˜¡¨¬©£â¤¦¬ club:!)[0m } T Networking, asking for name of local club


IMPLOCR {[0;1;31m
!Jƒœ¤ ¬§á¨®œ  ˜¬«æ «¦ «¦§ ¡æ Club... ƒ¦¡ £á©«œ [33m?[31m š ˜ ¤˜ ›œå«œ
«¦¤ ¡˜«á¢¦š¦ «à¤ clubs «ª ™á©ª.!)
[0;1m} T Networking, unknown local club


IMPOK {[0;1;32m
!J„¤«á¥œ , «˜ £¤ç£˜«˜ «¦¬ ˜§¦£˜¡¨¬©£â¤¦¬ club [37m%s[32m Ÿ˜ œ ©áš¦¤«˜  ©«¦
«¦§ ¡æ club [37m%s[32m.!)
[0;1m} T Networking, added import entry

IMPDISP {[0;1;33m
!J’˜ £¤ç£˜«˜ «¦¬ ˜§¦£˜¡¨¬©£â¤¦¬ club [37m%s[33m Ÿ˜ œ ©áš¦¤«˜  ©«¦
«¦§ ¡æ club [37m%s[33m. ‘£œåà©: ¦¨å¦¤«˜ª ˜¬«ã «¤ ˜¤« ©«¦ ®å˜,
¡˜«˜¨šã©˜£œ «¤ §¨¦è§á¨®¦¬©˜, §¦¬ œ¤˜§æŸœ«œ «˜ £¤ç£˜«˜ ©«¦ «¦§ ¡æ club
[37m%s[33m.!)
[0;1m} T Networking, added import entry, displaced previous one






DIPLSTH {[0;1;32m
                                             „ ©˜šàšã ¡áŸœ:
€§¦£˜¡¨¬©£â¤¦ ©ç©«£˜                     †£â¨œª  —¨œª  Šœ§«á  „ ©˜šæ£œ¤˜ clubs
!FÄ
} T Networking, remote system list header


DIPLSTL {[0;1m%-40.40s    %2s     %2s     %2s        %4d
} T Networking, remote system list item


DIPLSTF {[0;1;32m!FÄ
[0;1m} T Networking, remote system list footer




EXPLSTH {[0;1m
’¦§ ¡æ club      ’¦§ ¡æ/[32m„§ «¨â§¦¬£œ[37m/[31m€§˜š¦¨œç¦¬£œ[37m
!FÄ
} T Networking, list of exported clubs, header


EXPLSTL {[0;1m%-15.15s  !W!i} T Networking, list of exported clubs, entry part 1

EXPLSTL2 {’¦§ ¡æ Club!)
!0l} T Networking, list of exported clubs, local club

EXPLSTL3 {€¤¦ ¡«æ š ˜ æ¢˜ «˜ ©¬©«ã£˜«˜!)
!0l} T Networking, list of exported clubs, open to all

EXPLSTL4 {[0;1;32m%s } T Networking, list of exported clubs, ALLOW string

EXPLSTL5 {[0;1;31m%s } T Networking, list of exported clubs, DENY string

EXPLSTL6 {!)
!0l} T Networking, list of exported clubs, ALLOW/DENY end of line


EXPLSTF {[0;1m!FÄ
[0;1m} T Networking, list of exported clubs, footer



EXPASK {[0;1m
!Jƒé©«œ «¦ æ¤¦£˜ «¦¬ «¦§ ¡¦ç club «¦¬ ¦§¦å¦¬ «¤ ¡˜«á©«˜© Ÿâ¢œ«œ ¤˜
˜¢¢á¥œ«œ, ã [33mALL[37m š ˜ æ¢˜ «˜ clubs, ã [33m?[37m š ˜ ¡˜«á¢¦š¦:!) [0m} T  Networking, export status change, ask for club name


EXPCLBR {[0;1;31m
!J‘¬šš¤é£, ›œ¤ ¬§á¨®œ  ˜¬«æ «¦ club. ƒé©«œ [33m?[31m š ˜ ¡˜«á¢¦š¦.!)
[0;1m} T Networking, export status change, unknown club


EXPSPEC {[0;1m
!J’é¨˜ §¨â§œ  ¤˜ ¦¨å©œ«œ « ª §¨¦©™á©œ ª ¥â¤à¤ ©¬©«£á«à¤ ©'˜¬«æ «¦ club.
‹§¦¨œå«œ ¤˜ ›é©œ«œ [33m-[37m š ˜ ¤˜ ˜§˜š¦¨œç©œ«œ ©œ æ¢¦¬ª «¤ §¨æ©™˜©
(«¦§ ¡æ club), [33m+[37m š ˜ ¤˜ œ§ «¨â¯œ«œ «¤ œ¥˜šàšã «¦¬ club ©œ æ¢˜ «˜
©¬©«ã£˜«˜. ‹§¦¨œå«œ œ§å©ª ¤˜ ›é©œ«œ £å˜ ¢å©«˜ ©¬©«£á«à¤ (§® host.domain.tld
ã host.domain.tld/BBSCODE) ®à¨ ©£â¤à¤ £œ › ˜©«ã£˜«˜. † §¨æ©™˜© Ÿ˜ œ§ «¨â§œ«˜ 
£æ¤¦ ©'˜¬«á «˜ ©¬©«ã£˜«˜. €¤ ¦ §¨é«¦ª ®˜¨˜¡«ã¨˜ª «ª ¢å©«˜ª œå¤˜  "-", «æ«œ 
§¨æ©™˜© Ÿ˜ œ§ «¨â§œ«˜  ©œ æ¢¦¬ª „‰’‘ ˜§æ «˜ ©¬©«ã£˜«˜ §¦¬ Ÿ˜ ˜¤˜­â¨œ«œ.!)

!Wƒé©«œ «¤ ¢å©«˜ §¨æ©™˜©ª š ˜ «¦ §˜¨˜§á¤à club, ã [33m?[37m š ˜ ¡˜«á¢¦š¦
«à¤ clubs ¡˜  «à¤ §¨¦©™á©œé¤ «¦¬ª:!) [0m} T Networking, asking for export access list



NETST1 {[0;1m
!W‰˜«á©«˜© œ ©˜šàšé¤ £¤¬£á«à¤:!)
[0;1m} T Networking, import status


NETST2 {[0;1;32m
!W€§æ «¦ ©ç©«£˜ [37m%s[32m:!)
[37m!FÄ
[0;1m} T Networking, import, system name


NETST3 {[0;1;32m    %-55.55s -> %-16.16s
} T Networking, import, list item


NETST4 {[0;1m!FÄ
[0;1m} T Networking, import, list footer








WCNAXES {[0;1;31m
!J‘¬šš¤é£, ›œ¤ â®œ«œ œ§å§œ›¦ §¦¬ ¤˜ ©˜ª œ§ «¨â§œ 
«¤ ˜§¦©«¦¢ã £¤¬£á«à¤ ©«¦ Club @CLUB@.!)
[0;1m} T Write Club message, you don't have write access


WCCLUBR {[0;1;31m
!J‘¬šš¤é£, ˜¬«æ «¦ Club ›œ¤ ¬§á¨®œ .!)
[0;1m} T Write Club message, club does not exist


WCNCRDS {[0;1;31m
!Jƒœ¤ â®œ«œ ˜¨¡œ«âª £¦¤á›œª ®¨ã©ª š ˜ ¤˜ ©«œå¢œ«œ £ã¤¬£˜ ©«¦ Club @CLUB@.!)
[0;1m} T Write Club message: not enough credits, while asking


WCRNEC {[0;1;31m
!Jƒœ¤ â®œ«œ § ˜ ˜¨¡œ«âª £¦¤á›œª ®¨æ¤¦¬ ®¨ã©ª š ˜ ¤˜ ©«œå¢œ«œ ˜¬«æ «¦ £ã¤¬£˜
©«¦ Club @CLUB@.!)
[0;1m} T Write Club message: not enough credits to send


WCWHO {[0;1m
!Wƒé©«œ «¦¤ §˜¨˜¢ã§« «¦¬ £¤ç£˜«¦ª
([33m?[37m š ˜ ™¦ãŸœ ˜) [Enter=¢¦ ]:!) [0m} T Write Club message: get recipient of message


WCHELP {[0;1m

!J‹§¦¨œå«œ ¤˜ ›é©œ«œ «¦¤ §˜¨˜¢ã§« «¦¬ £¤ç£˜«æª ©˜ª àª œ¥ãª:!)

1. !i!Jƒé©«œ «¦ ¯œ¬›é¤¬£¦ œ¤æª £â¢¦¬ª. ‹§¦¨œå«œ ¤˜ ›é©œ«œ «¦ ¯œ¬›é¤¬£¦
¦¢æ¡¢¨¦, ã ¤˜ š¨á¯œ«œ «¦¬¢á® ©«¦¤ «˜ §¨é«˜ «¨å˜ š¨á££˜«˜. ’¦ ©ç©«£˜ Ÿ˜
˜¤˜¢á™œ  «˜ ¬§æ¢¦ §˜.!)
!0l
2. !i!Jƒé©«œ [33mEnter[37m š ˜ ¤˜ ©«œå¢œ«œ £ã¤¬£˜ §¨¦ª æ¢¦¬ª.!)
!0l
[0;1m} T Write Club message: help


WCUNKID {[0;1;31m
!JŠ¬§á£˜ , ˜¬«æ «¦ ¯œ¬›é¤¬£¦ ›œ¤ ¬§á¨®œ .!)
[0;1m} T Write Club message: unknown user ID


WCRCPOK {[0;1;32m
!J˜¨˜¢ã§«ª «¦¬ £¤ç£˜«æª ©˜ª Ÿ˜ œå¤˜  «¦ £â¢¦ª [37m%s[32m.!)
[0;1m} T Write Club message: confirming recipient of message


WCRCPALL {[0;1;32m
!J’¦ £ã¤¬£á ©˜ª Ÿ˜ ©«˜¢œå §¨¦ª [37m¢¦¬ª[32m.!)
[0;1m} T Write Club message: confirming recipient of message is 'All'


WCATT {[0;1m
!W‡â¢œ«œ ¤˜ œ§ ©¬¤á¯œ«œ â¤˜ ˜¨®œå¦ ©œ ˜¬«æ «¦ £ã¤¬£˜;
(† ®¨âà© š ˜ ˜¬«ã «¤ ¬§¨œ©å˜ œå¤˜  [32m%d £¦¤á›%s[37m)
([[33m“[0;1m]es=¤˜  / [[33mN[0;1m]o=æ® ):!) [0m} T Write Club message: ask if file attachment required


WCRRSEL {[0;1;31m
!W˜¨˜¡˜¢é ›é©«œ [33mY[31m ã [33mN[31m.!)
[0;1m} T Write Club message: invalid answer to question


WCATTAPP {[0;1;32m
ÛÛ  !W!i† £œ«˜­¦¨á «¦¬ ©¬¤££â¤¦¬ ˜¨®œå¦¬ âš ¤œ ˜¬«æ£˜«˜ œ§ «¨œ§«ã ©«¦ Club.!)
!0l[0;1m} T Write Club message: attachment auto-approved


WCATTNAP {[0;1;33m
ÛÛ  !W!i† £œ«˜­¦¨á «¦¬ ©¬¤££â¤¦¬ ˜¨®œå¦¬ Ÿ˜ šå¤œ 
œ§ «¨œ§«ã ˜­¦ç «¦ œ¢âš¥œ  ¦ ¨š˜¤à«ãª «¦¬ Club.!)
!0l[0;1m} T Write Club message: attachment needs approval


WCRNOT {[0;1m***

!J’¦ £â¢¦ª [32m%s[37m £æ¢ ª ©˜ª â©«œ ¢œ £ã¤¬£˜ ©«¦ Club
[32m%s[37m £œ Ÿâ£˜ "[32m%s[37m".!)
[0;1m
} T Write Club message: notification for recipient


WCRNOTC {[0;1m***

!J’¦ £â¢¦ª [32m%s[37m £æ¢ ª ©˜ª ˜¤«âš¨˜¯œ £ã¤¬£˜ ©«¦ Club [32m%s[37m
£œ Ÿâ£˜ "[32m%s[37m".!)
[0;1m
} T Write Club message: notification for recipient, copied message






RCMNU {[0;1m
!J‹§¦¨œå«œ ¤˜ › ˜¢â¥œ«œ «˜ £¤ç£˜«˜ §¦¬
Ÿâ¢œ«œ ¤˜ › ˜™á©œ«œ £œ «¦¬ª œ¥ãª «¨æ§¦¬ª:!)@CLUB@

  [[33mS[37m~]can . . . . . . €¤å®¤œ¬© £¤¬£á«à¤ â¤˜ §¨æª â¤˜
  [[33mL[37m~]ist  . . . . . . . ‘¬¤œ®æ£œ¤ œ§å›œ ¥ £¤¬£á«à¤
  [[33mT[37m~]o You . . . . . .  €¤å®¤œ¬© £¤¬£á«à¤ §¨¦ª œ©áª
  [[33mF[37m~]rom You  . . . . .  €¤å®¤œ¬© £¤¬£á«à¤ ˜§æ œ©áª
  [[33mK[37m~]ey  . .  €¤å®¤œ¬© £¤¬£á«à¤ éª §¨æª ¢â¥ ¡¢œ ›å

  [[33mQ[37m~]uick . . . . . . . . . ‹œ¤¦ç š¨ãš¦¨ª ˜¤å®¤œ¬©ª

!Wƒé©«œ «¤ œ§ ¢¦šã ©˜ª ([33m?[37m š ˜ ™¦ãŸœ ˜) } T Read Club messages, method menu


RCMNUD {[Enter=[33m%c[37m]:[0m!) } T Read Club messages, default value


RCMNUR {[0;1;31m
!J€¬«ã  œ§ ¢¦šã ›œ¤ œå¤˜  ›¬¤˜«ã.!)
[0;1m} T Read Club messages, invalid selection in method menu


RCMNUH {[0;1m

!J“§á¨®¦¬¤ §¦¢¢¦å «¨æ§¦  œ§ ¢¦šãª ˜¤áš¤à©ª £¤¬£á«à¤ œ¤æª Club:!)

!W[[33mS[37m]can:     !12i‹§¦¨œå«œ ˜§¢éª ¤˜ «˜ › ˜«¨â¥œ«œ,
«¦ ¦§¦å¦ ©£˜å¤œ  æ«  ¥œ¡ ¤á«œ ˜§æ «¦ §¨é«¦ £ã¤¬£˜
(ã ¦§¦ ¦›ã§¦«œ Ÿœ¢ã©œ«œ) ¡˜  ˜¨®åœ«œ ¤˜ › ˜™áœ«œ.
‹§¦¨œå«œ ¤˜ "˜¡¦¢¦¬Ÿœå«œ" › ˜¢æš¦¬ª ¡«¢.!)
!0l 
!W[[33mT[37m]o you:   !12i§àª ¡˜   §˜¨˜§á¤à £âŸ¦›¦ª ˜¤áš¤à©ª,
˜¢¢á œ£­˜¤å¦¤«˜  £æ¤¦ «˜ £¤ç£˜«˜ §¦¬ §¨¦¦¨å¦¤«˜  §¨¦ª œ©áª.!)
!0l 
!W[[33mF[37m]rom you: !12i’¦ å› ¦, ˜¢¢á œ£­˜¤å¦¤«˜  £æ¤¦ «˜
£¤ç£˜«˜ §¦¬ â®œ«œ š¨á¯œ  œ©œåª.!)
!0l 
!W[[33mL[37m]ist:     !12i‹§¦¨œå«œ ¤˜ §á¨œ«œ â¤˜ ¡˜«á¢¦š¦
£¤¬£á«à¤ œ¤æª Club ©œ £ ˜ ˜§æ « ª ˜¡æ¢¦¬Ÿœª £¦¨­âª: œ¨ š¨˜­ã, ’å«¢¦ª,
¢ã¨œª ¡œå£œ¤¦. ‰áŸœ §œ¨ š¨˜­ã ˜¡¦¢¦¬Ÿœå«˜  ˜§æ «¦¤ ˜¨ Ÿ£æ «¦¬
£¤ç£˜«¦ª â«©  é©«œ ¤˜ £§¦¨œå«œ ˜¨šæ«œ¨˜ ¤˜ ˜¨®å©œ«œ ˜§'˜¬«æ.!)
!0l
!W[[33mK[37m]ey:      !12iM§¦¨œå«œ ¤˜ ›é©œ«œ £ ˜ ã §œ¨ ©©æ«œ¨œª
"¢â¥œ ª ¡¢œ › ˜". † ˜¤å®¤œ¬© §¦¬ Ÿ˜ šå¤œ  ©ç£­à¤˜ £œ ˜¬«âª « ª ¢â¥œ ª
¡¢œ › á Ÿ˜ â®œ  éª ˜§¦«â¢œ©£˜ ¤˜ œ£­˜¤ ©«¦ç¤ ‹Œ «˜ £¤ç£˜«˜
«à¤ ¦§¦åà¤  §œ¨ š¨˜­ã œ£§œ¨ â®œ  «¤ ã « ª ¢â¥œ ª ¡¢œ › á.!)
!0l
!W[[33mQ[37m]uick:    !12i‹§¦¨œå«œ ¤˜ ¡á¤œ«œ ¦« ›ã§¦«œ ˜§æ «˜ §˜¨˜§á¤à
©œ £ ˜ ¦£á›˜ Clubs §¦¬ ©˜ª œ¤› ˜­â¨œ , ¡˜«œ¬Ÿœå˜¤, ˜§¦ «¦ «œ¢œ¬«˜å¦
£ã¤¬£˜ §¦¬ â®œ«œ › ˜™á©œ .!)
!0l
[0;1m
} T Read Club messages, help on method menu


DNLNAX {[0;1;31m
!JŠ¬§á£˜ , «¦ œ§å§œ›¦ §¨æ©™˜©ãª ©˜ª ›œ¤ ©˜ª œ§ «¨â§œ  «¤ ¢ã¯ ˜¨®œåà¤ ˜§æ
«¦ club [37m@CLUB@[31m.!)
[0;1m} T Download Club files, access denied


DMNU {[0;1m
!J‹§¦¨œå«œ ¤˜ › ˜¢â¥œ«œ «˜ £¤ç£˜«˜ £œ ©¬¤££â¤˜ ˜¨®œå˜ §¦¬ Ÿ˜
›œå«œ £œ «¦¬ª œ¥ãª «¨æ§¦¬ª:!)

  [[33mS[37m~]can . . . . . . . €¤å®¤œ¬© ˜¨®œåà¤ â¤˜ §¨æª â¤˜
  [[33mT[37m~]o You . . . . . . .  €¤å®¤œ¬© ˜¨®œåà¤ §¨¦ª œ©áª
  [[33mF[37m~]rom You  . . . . . .  €¤å®¤œ¬© ˜¨®œåà¤ ˜§æ œ©áª
  [[33mL[37m~]ist . . . . . . . .  ‘¬¤œ®æ£œ¤ œ§å›œ ¥ ˜¨®œåà¤
  [[33mK[37m~]ey . . . . €¤å®¤œ¬© ˜¨®œåà¤ àª §¨æª ¢â¥ ¡¢œ ›å

  [[33mQ[37m~]uick . . . . . . . . . ‹œ¤¦ç š¨ãš¦¨ª ˜¤å®¤œ¬©ª

!Wƒé©«œ «¤ œ§ ¢¦šã ©˜ª ([33m?[37m š ˜ ™¦ãŸœ ˜) } T Download Club files, method menu


DMNUD {[Enter=[33m%c[37m]:[0m!) } T Download Club files, default value


DMNUR {[0;1;31m
!J€¬«ã  œ§ ¢¦šã ›œ¤ œå¤˜  ›¬¤˜«ã.!)
[0;1m} T Download Club files, invalid selection in method menu

DMNUH {[0;1m

!J‹œ ˜¬«ã «¤ œ§ ¢¦šã £§¦¨œå«œ ¤˜ œ¥œ«á©œ«œ £æ¤¦ «˜ £¤ç£˜«˜ «¦¬
club §¦¬ â®¦¬¤ ¡á§¦ ¦ ©¬¤££â¤¦ ˜¨®œå¦. ‹§¦¨œå«œ ­¬© ¡á ¤˜ ¢á™œ«œ ¡˜  «˜
˜¨®œå˜. “§á¨®¦¬¤ ¦  œ¥ãª «¨æ§¦  œ¥â«˜©ª «à¤ £¤¬£á«à¤/˜¨®œåà¤:!)

!W[[33mS[37m]can:     !12i‹§¦¨œå«œ ˜§¢éª ¤˜ «˜ › ˜«¨â¥œ«œ,
«¦ ¦§¦å¦ ©£˜å¤œ  æ«  ¥œ¡ ¤á«œ ˜§æ «¦ §¨é«¦ £ã¤¬£˜
(ã ¦§¦ ¦›ã§¦«œ Ÿœ¢ã©œ«œ) ¡˜  ˜¨®åœ«œ ¤˜ › ˜™áœ«œ.
‹§¦¨œå«œ ¤˜ "˜¡¦¢¦¬Ÿœå«œ" › ˜¢æš¦¬ª ¡«¢.!)
!0l
!W[[33mT[37m]o you:   !12i§àª ¡˜   §˜¨˜§á¤à £âŸ¦›¦ª ˜¤áš¤à©ª,
˜¢¢á œ£­˜¤å¦¤«˜  £æ¤¦ «˜ £¤ç£˜«˜ §¦¬ §¨¦¦¨å¦¤«˜  §¨¦ª œ©áª.!)
!0l 
!W[[33mF[37m]rom you: !12i’¦ å› ¦, ˜¢¢á œ£­˜¤å¦¤«˜  £æ¤¦ «˜
£¤ç£˜«˜ §¦¬ â®œ«œ š¨á¯œ  œ©œåª.!)
!0l 
!W[[33mL[37m]ist:     !12i‹§¦¨œå«œ ¤˜ §á¨œ«œ â¤˜ ¡˜«á¢¦š¦
£¤¬£á«à¤ œ¤æª Club ©œ £ ˜ ˜§æ « ª ˜¡æ¢¦¬Ÿœª £¦¨­âª: œ¨ š¨˜­ã, ’å«¢¦ª,
¢ã¨œª ¡œå£œ¤¦. ‰áŸœ §œ¨ š¨˜­ã ˜¡¦¢¦¬Ÿœå«˜  ˜§æ «¦¤ ˜¨ Ÿ£æ «¦¬
£¤ç£˜«¦ª â«©  é©«œ ¤˜ £§¦¨œå«œ ˜¨šæ«œ¨˜ ¤˜ ˜¨®å©œ«œ ˜§'˜¬«æ.!)
!0l
!W[[33mK[37m]ey:      !12iM§¦¨œå«œ ¤˜ ›é©œ«œ £ ˜ ã §œ¨ ©©æ«œ¨œª
"¢â¥œ ª ¡¢œ › ˜". † ˜¤å®¤œ¬© §¦¬ Ÿ˜ šå¤œ  ©ç£­à¤˜ £œ ˜¬«âª « ª ¢â¥œ ª
¡¢œ › á Ÿ˜ â®œ  éª ˜§¦«â¢œ©£˜ ¤˜ œ£­˜¤ ©«¦ç¤ ‹Œ «˜ £¤ç£˜«˜
«à¤ ¦§¦åà¤  §œ¨ š¨˜­ã œ£§œ¨ â®œ  «¤ ã « ª ¢â¥œ ª ¡¢œ › á.!)
!0l
!W[[33mQ[37m]uick:    !12i‹§¦¨œå«œ ¤˜ ¡á¤œ«œ ¦« ›ã§¦«œ ˜§æ «˜ §˜¨˜§á¤à
©œ £ ˜ ¦£á›˜ Clubs §¦¬ ©˜ª œ¤› ˜­â¨œ , ¡˜«œ¬Ÿœå˜¤, ˜§¦ «¦ «œ¢œ¬«˜å¦
£ã¤¬£˜ §¦¬ â®œ«œ › ˜™á©œ .!)
!0l
[0;1m
} T Download Club files, help on method menu


FSCCAN {[0;1;31m
!J€¡ç¨à© › ˜› ¡˜©å˜ª.!)
[0;1m} T File scan aborted


RQMNU {[0;1m
‹âŸ¦›¦  š¨ãš¦¨ª ˜¤å®¤œ¬©ª:

  [[33mS[37m]can . . . . . . . €¤å®¤œ¬© £¤¬£á«à¤ ã/¡˜  ˜¨®œåà¤ â¤˜ §¨æª â¤˜
  [[33mT[37m]o You . . . . . . .  €¤å®¤œ¬© £¤¬£á«à¤ ã/¡˜  ˜¨®œåà¤ §¨¦ª œ©áª
  [[33mF[37m]rom You  . . . . . .  €¤å®¤œ¬© £¤¬£á«à¤ ã/¡˜  ˜¨®œåà¤ ˜§æ œ©áª
  [[33mL[37m]ist  . . . . . . . . . . . . .  ‰˜«á¢¦š¦ª ¡œ £â¤à¤ ã/¡˜  ˜¨®œåà¤
  [[33mK[37m]ey  . . . . . . . . €¤å®¤œ¬© «à¤ £¤¬£á«à¤ £â©à ¢â¥œàª ¡¢œ › ¦ç

  [[33mC[37m]onfigure . . . . . . . . . . . .  ƒ ˜£æ¨­à© š¨ãš¦¨ª ˜¤å®¤œ¬©ª

!Wƒ ˜¢â¥«œ £âŸ¦›¦ ˜¤å®¤œ¬©ª ([33m?[37m š ˜ ™¦ãŸœ ˜ } T Read club messages, Quick method menu


RQMNUH {[0;1m

!J† œ§ ¢¦šã ([[33mQ[37m]uick=š¨ãš¦¨ ˜¤å®¤œ¬©) œå¤˜  «¦ §¨¦©à§ ¡æ ©˜ª œ¨š˜¢œå¦
£œ «¦ ¦§¦å¦ £§¦¨œå«œ ¤˜ › ˜«¨â¥œ«œ «˜ ¤â˜ £¤ç£˜«˜ «¦¬ ¡áŸœ œ§ ¢œš£â¤¦¬
Club, ˜§æ «¦ ©£œå¦ §¦¬ œå®˜«œ £œå¤œ  «¤ «œ¢œ¬«˜å˜ ­¦¨á.!)

!W[[33mS[37m]can:      !13i‹§¦¨œå«œ ˜§¢éª ¤˜ › ˜«¨â¥œ«œ «˜ œ§ ¢œš£â¤˜ ©˜ª Club, ¥œ¡ ¤é¤«˜ª
˜§æ œ¡œå §¦¬ œå®˜«œ £œå¤œ , › ˜™á¦¤«˜ª £¤ç£˜«˜, "˜¡¦¢¦¬Ÿé¤«˜ª" › ˜¢æš¦¬ª ¡«¢.!)
!0l
!W[[33mT[37m]o you:    !13i§àª ¡˜   §˜¨˜§á¤à £âŸ¦›¦ª ˜¤áš¤à©ª,
˜¢¢á œ£­˜¤å¦¤«˜  £æ¤¦ «˜ £¤ç£˜«˜ §¦¬ §¨¦¦¨å¦¤«˜  §¨¦ª œ©áª.!)
!0l 
!W[[33mF[37m]rom you:  !13i’¦ å› ¦, ˜¢¢á œ£­˜¤å¦¤«˜  £æ¤¦ «˜
£¤ç£˜«˜ §¦¬ â®œ«œ š¨á¯œ  œ©œåª.!)
!0l 
!W[[33mL[37m]ist:      !13i‹§¦¨œå«œ ¤˜ œ£­˜¤å©œ«œ «˜ ¤â˜ £¤ç£˜«˜ ©«˜ œ§ ¢œš£â¤˜ Clubs £œ
¡á§¦ ˜ ˜§æ « ª «¨œåª £œŸæ›¦¬ª: œ¨ š¨˜­ã, ’å«¢¦ª, ¢ã¨œª ¡œå£œ¤¦.!)
!0l
!W[[33mK[37m]ey:       !13i‹§¦¨œå«œ ¤˜ ¯á¥œ«œ «˜ ¤â˜ £¤ç£˜«˜ «à¤ œ§ ¢œš£â¤à¤ Clubs š ˜
£å˜ ã §œ¨ ©©æ«œ¨œª ¢â¥œ ª ¡¢œ › á §¦¬ Ÿ˜ ¦¨å©œ«œ.!)
!0l
!W[[33mC[37m]onfigure: !13iƒ ˜£æ¨­à© š¨ãš¦¨ª ˜¤å®¤œ¬©ª. „›é ¦¨åœ«œ «˜ Clubs §¦¬ Ÿ˜
§œ¨ ¢˜£™á¤¦¤«˜  ©«¤ š¨ãš¦¨ ˜¤å®¤œ¬©.!)
!0l
[0;1m} T Read club messages, Quick method help


RQCFH {[0;1m

!J‹ ˜ ¡˜  ˜¬«ã œå¤˜  ˜¬«ã  §¨é« ­¦¨á §¦¬ ®¨© £¦§¦ œå«œ «¤
š¨ãš¦¨ ˜¤å®¤œ¬© ©˜ª £œ«˜­â¨¦¬£œ ¡˜«œ¬Ÿœå˜¤ ©«¦ œ¨š˜¢œå¦ › ˜£æ¨­à©ª
«ª ˜¤å®¤œ¬©ª. ƒ ˜£¦¨­é¤¦¤«˜ª «¤ š¨ãš¦¨ ˜¤å®¤œ¬© ¦¨åœ«œ §¦ ˜ Clubs
Ÿ˜ › ˜™áœ«œ/˜¤ ®¤œçœ«œ ˜¨šæ«œ¨˜.!)

!J’¦ ©ç©«£˜ "Ÿ¬£á«˜ " «¦ «œ¢œ¬«˜å¦ £ã¤¬£˜ §¦¬ â®œ«œ › ˜™á©œ  ©œ ¡áŸœ Club,
â«©  é©«œ ¡áŸœ ˜¤å®¤œ¬© ¤˜ šå¤œ«˜  £æ¤¦ ©«˜ £¤ç£˜«˜ §¦¬ â®¦¬¤ ©«˜¢œå
£œ«á «¤ «œ¢œ¬«˜å˜ ©˜ª ˜¤áš¤à©.!)

!J€¨® ¡á æ¢˜ «˜ Clubs §œ¨ ¢˜£™á¤¦¤«˜  ©« š¨ãš¦¨ ˜¤å®¤œ¬© (¡˜  ©«˜ QWK
§˜¡â«˜ §¦¬ £§¦¨œå«œ ¤˜ ¢á™œ«œ £â©à «¦¬ Off-Line Mailer), ˜¢¢á £§¦¨œå«œ ¤˜
˜­˜ ¨â©œ«œ â¤˜ ›å¤¦¤«˜ª "[33m-/¤¦£˜Club[37m", ã ¤˜ §¨¦©Ÿâ©œ«œ â¤˜
›å¤¦¤«˜ª "[33m+/¤¦£˜Club[37m". ‚ ˜ ¤˜ ›œå«œ â¤˜ ¡˜«á¢¦š¦ æ¢à¤ «à¤ Clubs
£§¦¨œå«œ ¤˜ ›é©œ«œ "[33m+?[37m". ‚ ˜ ¤˜ ©¬£§œ¨ ¢á™œ«œ æ¢˜ «˜ Clubs ›é©«œ
"[33m+ALL[37m" ¡˜  š ˜ ¤˜ «˜ › ˜š¨á¯œ«œ æ¢˜, "[33m-ALL[37m".
‚ ˜ ¤˜ Ÿœà¨Ÿ¦ç¤ æ¢˜ «˜ £¤ç£˜«˜ œ¤æª Club ã› › ˜™˜©£â¤˜ ›é©«œ
"[33m+/O¤¦£˜Club[37m" ›ç¦ ­¦¨âª. ƒ¢˜›ã, ˜¤ ›é©œ«œ "[33m+ALL +ALL[37m",
«¦ ©ç©«£˜ Ÿ˜ Ÿœà¨ã©œ  æ¢˜ «˜ £¤ç£˜«˜ æ¢à¤ «à¤ Clubs ã› › ˜™˜©£â¤˜.
„«© , «¤ œ§æ£œ¤ ­¦¨á §¦¬ Ÿ˜ ©¬¤›œŸœå«œ Ÿ˜ £§¦¨â©œ«œ £œ «¤ œ¤«¦¢ã [33mCRQS[37m ¤˜ › ˜™á©œ«œ
æ¢˜ «˜ ¤â˜ £¤ç£˜«˜.!)
} T Read Club messages, Quick Configure help


RQCLH {[0;1;32m
† š¨ãš¦¨ ˜¤å®¤œ¬©ã ©˜ª šå¤œ«˜  ©«á œ¥ãª Club(s):

[0m} T Read Club messages, Quick Configure, club list header


RQLCE {[0;1;31m
!J‰˜¤â¤˜ club ›œ¤ §œ¨ ¢˜£™á¤œ«˜  ©«¤ š¨ãš¦¨ã ©˜ª ˜¤å®¤œ¬©.!)
[0m} T Read Club messages, Quick Configure, no clubs



RQCLF {[0;1m
} T Read Club messages, Quick Configure, club list footer


RQCMNU {[0;1m
   [33m+[37m  . . . . . . . . . . . .  ¨¦©Ÿâ©«œ â¤˜ Club
   [33m-[37m . . . . . . . . . . . . . €­˜ ¨â©«œ â¤˜ Club
   [33mV[37miew . . „£­á¤ © «à¤ Club §¦¬ Ÿ˜ ˜¤ ®¤œç¦¤«˜ 

!W„á¤ â®œ«œ ›é©œ  ã› «¤ œ¤«¦¢ã [33m+ALL +ALL[37m ›é©«œ e[33mX[37mit.!)

!Wƒé©«œ «¤ œ§ ¢¦šã ©˜ª ([33mV[37m,[33m+[37m,[33m-[37m,[33m?[37m š ˜ ™¦ãŸœ ˜, ã [33mX[37m š ˜ «â¢¦ª:!)[0m } T Read Club messages, Quick Configure, menu


RQCHELP {[0;1m

!Jƒ ˜£¦¨­é¤¦¤«˜ª « š¨ãš¦¨ ˜¤å®¤œ¬© ¦¨åœ«œ §¦ à¤ Clubs «˜ £¤ç£˜«˜
Ÿ˜ › ˜™áœ«œ/˜¤ ®¤œçœ«œ ˜¨šæ«œ¨˜ £œ «¤ œ¤«¦¢ã [33mCRQS[37m.!)

!J’¦ ©ç©«£˜ "Ÿ¬£á«˜ " «¦ «œ¢œ¬«˜å¦ £ã¤¬£˜ §¦¬ â®œ«œ › ˜™á©œ  ©œ ¡áŸœ Club,
â«©  é©«œ ¡áŸœ ˜¤å®¤œ¬© ¤˜ šå¤œ«˜  £æ¤¦ ©«˜ £¤ç£˜«˜ §¦¬ â®¦¬¤ ©«˜¢œå
£œ«á «¤ «œ¢œ¬«˜å˜ ©˜ª ˜¤áš¤à©.!)

!J€¨® ¡á æ¢˜ «˜ Clubs §œ¨ ¢˜£™á¤¦¤«˜  ©« š¨ãš¦¨ ˜¤å®¤œ¬©, ˜¢¢á £§¦¨œå«œ ¤˜
˜­˜ ¨â©œ«œ â¤˜ ›å¤¦¤«˜ª "[33m-/¤¦£˜Club[37m", ã ¤˜ §¨¦©Ÿâ©œ«œ â¤˜
›å¤¦¤«˜ª "[33m+/¤¦£˜Club[37m". ‚ ˜ ¤˜ ›œå«œ â¤˜ ¡˜«á¢¦š¦ æ¢à¤ «à¤ Clubs
£§¦¨œå«œ ¤˜ ›é©œ«œ "[33m+?[37m". ‚ ˜ ¤˜ ©¬£§œ¨ ¢á™œ«œ æ¢˜ «˜ Clubs ›é©«œ
"[33m+ALL[37m" ¡˜  š ˜ ¤˜ «˜ › ˜š¨á¯œ«œ æ¢˜, "[33m-ALL[37m".
‚ ˜ ¤˜ Ÿœà¨Ÿ¦ç¤ æ¢˜ «˜ £¤ç£˜«˜ œ¤æª Club ã› › ˜™˜©£â¤˜ ›é©«œ
"[33m+/O¤¦£˜Club[37m" ›ç¦ ­¦¨âª. ƒ¢˜›ã, ˜¤ ›é©œ«œ "[33m+ALL +ALL[37m",
«¦ ©ç©«£˜ Ÿ˜ Ÿœà¨ã©œ  æ¢˜ «˜ £¤ç£˜«˜ æ¢à¤ «à¤ Clubs ã› › ˜™˜©£â¤˜.
„«© , «¤ œ§æ£œ¤ ­¦¨á §¦¬ Ÿ˜ ©¬¤›œŸœå«œ Ÿ˜ £§¦¨â©œ«œ £œ «¤ œ¤«¦¢ã [33mCRQS[37m ¤˜ › ˜™á©œ«œ
æ¢˜ «˜ ¤â˜ £¤ç£˜«˜.!)
[0;1m
} T Read Club messages, Quick Configure help #2


RQCADD {[0;1m
!Wƒé©«œ Club §¦¬ Ÿ˜ ©¬£§œ¨ ¢á™œ«œ ©«¤ š¨ãš¦¨ ˜¤å®¤œ¬© ([33m?[37m š ˜ ¡˜«á¢¦š¦):!)[0m } T Read Club messages, Quick Configure, add club


RQCCR {[0;1;31m
!Jƒœ¤ ¬§á¨®œ  ˜¬«æ «¦ Club.!)
} T Read Club messages, Quick Configure, add, unknown club


RQCDEL {[0;1m
!Wƒé©«œ Club §¦¬ Ÿ˜ › ˜š¨á¯œ«œ ˜§æ «¤ š¨ãš¦¨ ˜¤å®¤œ¬© ([33m?[37m š ˜ ¡˜«á¢¦š¦):!)[0m } T Read Club messages, Quick Configure, delete club


RQCDR {[0;1;31m
!Jƒœ¤ ¬§á¨®œ  «â«¦ ¦ Club ©«¦¤ ¡˜«á¢¦š¦ «à¤ ˜¤ ®¤œ¬¦£â¤à¤ Club.
ƒé©«œ [33mX[31m (eXit) ¦§¦ ˜›ã§¦«œ ©« š£ã š ˜ ¤˜ œ§ ©«¨â¯œ«œ ©«¦
¡œ¤«¨ ¡æ £œ¤¦ç «à¤ Club.!)
} T Read Club messages, Quick Configure, delete, unknown club


RLMNU {[0;1m
  £âŸ¦›¦  ©¬¤œ®æ£œ¤ª œ§å›œ ¥ª œå¤˜ :

  [[33mB[37m]rief . . . . œ¨ š¨˜­ã, £ ˜ š¨˜££ã š ˜ ¡áŸœ £ã¤¬£˜ ã ˜¨®œå¦
  [[33mT[37m]itle  . . . .  ’å«¢¦ª, œ§ ¡œ­˜¢å›˜ £¤ç£˜«¦ª, 5 ã 6 š¨˜££âª
  [[33mF[37m]ull  . . . . . . . . . . . . „§ ¡œ­˜¢å›˜ ¡˜  §¢ã¨œª ¡œå£œ¤¦

!Wƒ ˜¢â¥«œ £å˜ ˜§æ « ª §˜¨˜§á¤à £œŸæ›¦¬ª ([33m?[0;1m š ˜ ™¦ãŸœ ˜)!)[0m } T List Club messages, method menu


RLMNUR {[0;1;31m
!W€¬«ã  œ§ ¢¦šã ›œ¤ œå¤˜  ›¬¤˜«ã. ƒé©«œ [33m?[31m š ˜ ™¦ãŸœ ˜.!)
[0;1m} T List Club messages, invalid selection


RLMNUH {[0;1m

!J† œ§ ¢¦šã [33mL[37mist ˜§¢éª œ£­˜¤åœ  §¢¨¦­¦¨åœª š ˜ ¡áŸœ £ã¤¬£˜ ©«¤ ¦Ÿæ¤
©˜ª.   œ§æ£œ¤œª £âŸ¦›¦  œ£­á¤ ©ª §¨¦©­â¨¦¤«˜ :!)

!W[[33mB[37m]rief: !9i€¬«ã  £âŸ¦›¦ª œ£­˜¤åœ  £æ¤¦ «¦¤ ˜¨ Ÿ£æ «¦¬ £¤ç£˜«¦ª,
§æ«œ š¨á­«¡œ, «¦¤ ˜§¦©«¦¢â˜ ¡˜  æ©¦ ˜§æ «¦ Ÿâ£˜ «¦¬ £¤ç£˜«¦ª ®à¨áœ 
©«¦ §¢á«¦ª «ª ¦Ÿæ¤ª ©˜ª.!)
!0l
!W[[33mT[37m]itle: !9i€¬«ã  £âŸ¦›¦ª œ£­˜¤åœ  «¤ §¢ã¨ œ§ ¡œ­˜¢å›˜ (header)
¡áŸœ £¤ç£˜«¦ª. † œ§ ¡œ­˜¢å›˜ §œ¨ ¢˜£™á¤œ  «¦¤ ˜¨ Ÿ£æ «¦¬ £¤ç£˜«¦ª,
§æ«œ š¨á­«¡œ, ˜§¦©«¦¢â˜ ¡˜  §˜¨˜¢ã§«, œá¤ ¬§á¨®œ 
©¬¤££â¤¦ ˜¨®œå¦, §¦ ¦ «¦ æ¤¦£á «¦¬ ¡˜  §æ©œª ­¦¨âª â®œ  ¢Ÿœå,
§æ©œª ­¦¨âª â®œ  › ˜™˜©«œå «¦ £ã¤¬£˜ ¡˜  §æ©œª ˜§˜¤«ã©œ ª â®œ , ¡˜  «¦ §¢ã¨œª Ÿâ£˜.!)
!0l
!W[[33mF[37m]ull:  !9i€¬«ã  £âŸ¦›¦ª œ£­˜¤åœ  «¤ œ§ ¡œ­˜¢å›˜ (æ§àª  £âŸ¦›¦ª [33mT[37mitle)
¡˜  ¦¢æ¡¢¨¦ «¦ £ã¤¬£˜, ˜¢¢á æ®  ¡˜  «˜ § Ÿ˜¤æ¤ ©¬¤££â¤˜ ˜¨®œå˜.!)
!0l
[0;1m
} T List Club messages, method menu help


RLASK {[0;1m
!Jƒé©«œ «¦¤ ˜¨ Ÿ£æ £¤ç£˜«¦ª ˜§æ æ§¦¬ Ÿ˜ ˜¨®å©œ«œ «¤ œ§å›œ ¥, [[33mF[37m]irst
(¨é«¦) š ˜ «¦ §¨é«¦ ¬§á¨®¦¤ £ã¤¬£˜, [[33mL[37m]ast (’œ¢œ¬«˜å¦)
š ˜ «¦ «œ¢œ¬«˜å¦ £ã¤¬£˜, [33mEnter[37m š ˜ «¦ «¨â®¦¤ £ã¤¬£˜
([32m#%ld[37m), ã [33m?[0;1m š ˜ ™¦ãŸœ ˜.!)

!W€§æ §¦ ¦ £ã¤¬£˜ ¤˜ ¥œ¡ ¤ã©œ   œ§å›œ ¥; !) [0m} T List Club messages, asking for message number 


RLASKR {[0;1;31m
!WŠ¬§á£˜ , ›œ¤ ¬§á¨®œ  ˜¬«ã  œ§ ¢¦šã.!)
[0;1m} T List Club messages, error while asking for message number


RLASKH {[0;1m
!J€¤ §˜«ã©œ«œ ˜§¢éª [33mEnter[37m, Ÿ˜ ˜¨®å©œ«œ ˜§æ «¦ §¨é«¦ ¤â¦ £ã¤¬£˜
«¦¬ Club @CLUB@. €¤ ›œ¤ ¬§á¨®¦¬¤ ¤â˜ £¤ç£˜«˜, «æ«œ  ˜¤áš¤à© Ÿ˜ ¥œ¡ ¤ã©œ  £œ «¦ «œ¢œ¬«˜å¦
˜§æ «˜ §˜¢ á. † «œ¢œå˜ ([33m.[37m) œå¤˜   ©¦›ç¤˜£ £œ «¦ [33mEnter[37m, 
˜¤ ®¨© £¦§¦ œå«œ ©¬¤«£ã©œ ª. ƒ¢˜›ã  œ¤«¦¢ã [33mCRLB.[37m ˜§æ «¦ ¡œ¤«¨ ¡æ
£œ¤¦ç ©£˜å¤œ  "á£œ© ©ç¤«¦£ œ£­á¤ © æ¢à¤ «à¤ ¤âà¤ £¤¬£á«à¤ «¦¬ «¨â®¦¤«¦ª club".!)

!Jƒå¤¦¤«˜ª [33mF[37m (First), Ÿ˜ ˜¨®å©œ«œ «¤ ˜¤áš¤à© ˜§æ «¦ §˜¢ æ«œ¨¦
› ˜Ÿâ© £¦ £ã¤¬£˜.!)

!Jƒå¤¦¤«˜ª [33mL[37m (Last), Ÿ˜ ˜¨®å©œ«œ «¤ ˜¤áš¤à© ˜§æ «¦ § ¦ §¨æ©­˜«¦
£ã¤¬£˜ §¦¬ š¨á­«¡œ.!)

!Jƒé©«œ [33mX[37m (eXit) ˜¤ Ÿâ¢œ«œ ¤˜ ™šœå«œ, ˜¢¢ éª ›é©«œ «¦¤ ˜¨ Ÿ£æ «¦¬
£¤ç£˜«¦ª ˜§¦ «¦ ¦§¦å¦ Ÿâ¢œ«œ ¤˜ ˜¨®å©œ«œ. €¤ ›œ¤ ¬§á¨®œ  £ã¤¬£˜ £œ ˜¬«æ¤ «¦¤
˜¨ Ÿ£æ «æ«œ Ÿ˜ ®¨© £¦§¦ Ÿœå «¦ §¨é«¦ £ã¤¬£˜ £œ ˜¨ Ÿ£æ £œš˜¢ç«œ¨¦ ˜§æ ˜¬«æ¤
§¦¬ ›é©˜«œ.!)
[0;1m} T List Club messages, help about entering message numbers


RLBNMSG {[0;1;31m
!Jƒœ¤ ™¨âŸ¡˜¤ £¤ç£˜«˜.!)
[0;1m} T List Club messages, no messages found


RLMISS {[0;1m
’¦ £ã¤¬£˜ [32m%d[37m ›œ¤ ™¨âŸ¡œ. „§ ¢â®Ÿ¡œ «¦ §¢© â©«œ¨¦:
[0;1m} T List Club messages, message number not found


RLBHDR {[0;1;32m
„£­á¤ © «¦¬ [37m@CLUB@: @CLUBDESC@[32m...
[37m
‹ã¤¬£˜  €§¦©«¦¢â˜ª  †£œ¨¦£¤å˜ ¡˜  é¨˜  ‡â£˜
!FÄ
} T List Club messages, brief listing header


RLBTAB {[0;1;33m%6d  %-10s  %s %s  %s
} List Club messages, brief listing table


RLBFTR {[0;1m!FÄ
[0;1m} T List Club messages, brief listing footer


RLTHDR {[0;1;32m
„£­á¤ © «¦¬ [37m@CLUB@: @CLUBDESC@[32m...
[0;1m} T List Club messages, title/full listing header


RLDONE {[0;1m
!W”«á©˜«œ ©«¦ «â¢¦ª «à¤ £¤¬£á«à¤.!)
[0;1m} T List Club messages, end of listing



RLABORT {[0;1m

!Wƒ ˜¡æ§¡œ ˜§æ «¦¤ ®¨ã©«.!)
[0;1m} T List Club messages, listing aborted





RSASK {[0;1m
!Jƒé©«œ «¦¤ ˜¨ Ÿ£æ £¤ç£˜«¦ª ˜§æ æ§¦¬ Ÿ˜ ˜¨®å©œ«œ «¤ ˜¤áš¤à©, [[33mF[37m]irst
(¨é«¦) š ˜ «¦ §¨é«¦ ¬§á¨®¦¤ £ã¤¬£˜, [[33mL[37m]ast (’œ¢œ¬«˜å¦)
š ˜ «¦ «œ¢œ¬«˜å¦ £ã¤¬£˜, [33mEnter[37m š ˜ «¦ «¨â®¦¤ £ã¤¬£˜
([32m#%ld[37m), ã [33m?[0;1m š ˜ ™¦ãŸœ ˜.!)

!W€§æ §¦ ¦ £ã¤¬£˜ ¤˜ ¥œ¡ ¤ã©œ   ˜¤áš¤à©; !) [0m} T Scan Club messages, asking for message number 


RSASKR {[0;1;31m
!WŠ¬§á£˜ , ›œ¤ ¬§á¨®œ  ˜¬«ã  œ§ ¢¦šã.!)
[0;1m} T Scan Club messages, error while asking for message number


RSASKH {[0;1m
!J€¤ §˜«ã©œ«œ ˜§¢éª [33mEnter[37m, Ÿ˜ ˜¨®å©œ«œ ˜§æ «¦ §¨é«¦ ¤â¦ £ã¤¬£˜
«¦¬ Club @CLUB@. €¤ ›œ¤ ¬§á¨®¦¬¤ ¤â˜ £¤ç£˜«˜, «æ«œ  ˜¤áš¤à© Ÿ˜ ¥œ¡ ¤ã©œ  £œ «¦ «œ¢œ¬«˜å¦
˜§æ «˜ §˜¢ á. † «œ¢œå˜ ([33m.[37m) œå¤˜   ©¦›ç¤˜£ £œ «¦ [33mEnter[37m, 
˜¤ ®¨© £¦§¦ œå«œ ©¬¤«£ã©œ ª. ƒ¢˜›ã  œ¤«¦¢ã [33mCRS.[37m ˜§æ «¦ ¡œ¤«¨ ¡æ
£œ¤¦ç ©£˜å¤œ  "á£œ© ˜¤áš¤à© æ¢à¤ «à¤ ¤âà¤ £¤¬£á«à¤ «¦¬ «¨â®¦¤«¦ª club".!)

!Jƒå¤¦¤«˜ª [33mF[37m (First), Ÿ˜ ˜¨®å©œ«œ «¤ ˜¤áš¤à© ˜§æ «¦ §˜¢ æ«œ¨¦
› ˜Ÿâ© £¦ £ã¤¬£˜.!)

!Jƒå¤¦¤«˜ª [33mL[37m (Last), Ÿ˜ ˜¨®å©œ«œ «¤ ˜¤áš¤à© ˜§æ «¦ § ¦ §¨æ©­˜«¦
£ã¤¬£˜ §¦¬ š¨á­«¡œ.!)

!Jƒé©«œ [33mX[37m (eXit) ˜¤ Ÿâ¢œ«œ ¤˜ ™šœå«œ, ˜¢¢ éª ›é©«œ «¦¤ ˜¨ Ÿ£æ «¦¬
£¤ç£˜«¦ª ˜§¦ «¦ ¦§¦å¦ Ÿâ¢œ«œ ¤˜ ˜¨®å©œ«œ. €¤ ›œ¤ ¬§á¨®œ  £ã¤¬£˜ £œ ˜¬«æ¤ «¦¤
˜¨ Ÿ£æ «æ«œ Ÿ˜ ®¨© £¦§¦ Ÿœå «¦ §¨é«¦ £ã¤¬£˜ £œ ˜¨ Ÿ£æ £œš˜¢ç«œ¨¦ ˜§æ ˜¬«æ¤
§¦¬ ›é©˜«œ.!)
[0;1m} T Scan Club messages, help about entering message numbers


RSWAIT {[0;1;32m
!J„¨œ¬¤˜ £¤¬£á«à¤, §˜¨˜¡˜¢é §œ¨ £â¤œ«œ...!)
[0;1m} T Scan Club messages, please wait...


RSBNMSG {[0;1;31m
!Jƒœ¤ ™¨âŸ¡˜¤ £¤ç£˜«˜.!)
[0;1m} T Scan Club messages, no messages found


RSMISS {[0;1m
’¦ £ã¤¬£˜ [32m%d[37m ›œ¤ ™¨âŸ¡œ. „§ ¢â®Ÿ¡œ «¦ §¢© â©«œ¨¦:
[0;1m} T Scan Club messages, message number not found


RSTHDR {[0;1;32m
„£­á¤ © «¦¬ [37m@CLUB@: @CLUBDESC@[32m...
[0;1m} T Scan Club messages, scanning club


RSSCNM {[0;1m
[[33mN[37m]ext . . . . . . . „§æ£œ¤¦ £ã¤¬£˜   [[33mP[37m]revious . . . ¨¦š¦ç£œ¤¦ £ã¤¬£˜
[[33mR[37m]ead  . . . . . . . . .  €¤áš¤à©   [[33m#[37m] . . . . . . €¢£˜ ©œ á¢¢¦ £ã¤¬£˜
[[33mT[37m]hread . . . . €¡¦¢¦¬Ÿå˜ › ˜¢æš¦¬   [[33mQ[37m]uickscan . . . ‚¨ãš¦¨ ˜¤å®¤œ¬©
e[[33mX[37m]it . . . . . . . . . . . „¥¦›¦ª

† œ§ ¢¦šã ©˜ª ([33m?[37m š ˜ ™¦ãŸœ ˜); } T Scan Club messages, choices while scanning messages


RSSCNMH {[0;1m

!J‹§¦¨œå«œ ¤˜ ›é©œ«œ « ª œ¥ãª œ¤«¦¢âª ©œ ˜¬«æ «¦ ©£œå¦:!)

!W[33mN[37mext:      !i‹œ«˜­â¨œ©«œ ©«¦ œ§æ£œ¤¦ £ã¤¬£˜, ®à¨åª ¤˜ › ˜™á©œ«œ «¦ «¨â®¦¤.
‹§¦¨œå«œ ¤˜ ®¨© £¦§¦ ã©œ«œ ˜¬«ã «¤ œ¤«¦¢ã š ˜ â¤˜ œå›¦ª ˜§¢ãª ˜¤å®¤œ¬©ª «à¤ £¤¬£á«à¤.
ƒé©«œ §¦¢¢âª ­¦¨âª «¤ œ¤«¦¢ã N àª ©ç¤«£©, ¡˜  «¦ ©ç©«£˜ Ÿ˜ §¨¦®à¨ã©œ  œ£­˜¤å¦¤«áª ©˜ª
« ª œ§ ¡œ­˜¢å›œª (headers) «à¤ £¤¬£á«à¤ §¦¬ §œ¨¤áœ . „«© , £œ «¤ œ¤«¦¢ã [33mNNNN[37m,
 ™á© Ÿ˜ ©˜ª ›œå¥œ  « ª œ§ ¡œ­˜¢å›œª «à¤ œ§æ£œ¤à¤ «œ©©á¨à¤ £¤¬£á«à¤, ¡˜  Ÿ˜ ©«˜£˜«ã©œ  ©«¦ «œ¢œ¬«˜å¦.!)
!0l
!W[33mP[37mrevious:  !i‹œ«˜­â¨œ©«œ ©«¦ §¨¦š¦ç£œ¤¦ £ã¤¬£˜. Šœ «¦¬¨šœå æ§àª ˜¡¨ ™éª ¡˜   §¨¦š¦ç£œ¤ œ¤«¦¢ã.!)
!0l
!W[33m#[37m:         !i’¦ ©ç©«£˜ Ÿ˜ ©˜ª «ã©œ  â¤˜¤ ˜¨ Ÿ£æ £¤ç£˜«¦ª ©«¦ ¦§¦å¦ Ÿ˜ £œ«˜™œå«œ.
€¤ «¦ £ã¤¬£˜ ›œ¤ ™¨œŸœå, Ÿ˜ «¦§¦Ÿœ«Ÿœå«œ ©«¦ ¡¦¤« ¤æ«œ¨¦ £ã¤¬£˜. ‹§¦¨œå«œ ¡˜  œ›é ¤˜ ®¨© £¦§¦ ã©œ«œ
©¬¤«£ã©œ ª:  œ¤«¦¢ã [33m#1000[37m Ÿ˜ ©˜ª §áœ  ¡˜«œ¬Ÿœå˜¤ ©«¦ £ã¤¬£˜ 1000.!)
!0l
!W[33mT[37mhread:    !i€¡¦¢¦¬Ÿå˜ › ˜¢æš¦¬. €¬«ã  œ¤«¦¢ã ©˜ª œ£­˜¤åœ 
â¤˜ ˜¡æ£˜ £œ¤¦ç, £œ «¤ ™¦ãŸœ ˜ «¦¬ ¦§¦å¦¬ £§¦¨œå«œ ¤˜ ¡ ¤Ÿœå«œ ©«¦
§¨¦š¦ç£œ¤¦ ã œ§æ£œ¤¦ £ã¤¬£˜ «ª ©¬ã«©ª. ‹§¦¨œå«œ œ§å©ª ¤˜ §á«œ ©«¦
£ã¤¬£˜ §¨¦ª «¦ ¦§¦å¦ ˜§˜¤«á «¦ «¨â®¦¤ £ã¤¬£˜.!)
!0l
!W[33mQ[37muickscan: !i„›é Ÿ˜ ™¨œå«œ ¡á§¦ œª œ › ¡âª œ¤«¦¢âª š ˜ «¤ š¨ãš¦¨
˜¤å®¤œ¬©. ‹§¦¨œå«œ ¤˜ ¡ ¤Ÿœå«œ ©«¦ œ§æ£œ¤¦ ã §¨¦š¦ç£œ¤¦ club, ¤˜ ˜­˜ ¨â©œ«œ «¦
«¨â®¦¤ club ˜§æ «¤ ¢å©«˜ š¨ãš¦¨ª ˜¤å®¤œ¬©ª, ¡˜  á¢¢˜.!)
!0l
!W[33mR[37mead:      !i€¤áš¤à© «¦¬ «¨â®¦¤«¦ª £¤ç£˜«¦ª. ‹œ«á «¤ ˜¤áš¤à© â®œ«œ œ§ §¢â¦¤
›¬¤˜«æ««œª ®œ ¨ ©£¦ç «¦¬ £¤ç£˜«¦ª.!)
!0l
[0;1m} T Scan Club messages, help about scanning commands


RSSCNMD {[0;1m
[[33mN[37m]ext . . . . . . . „§æ£œ¤¦ £ã¤¬£˜   [[33mP[37m]revious . . . ¨¦š¦ç£œ¤¦ £ã¤¬£˜
[[33mR[37m]ead  . . . . . . . . .  €¤áš¤à©   [[33m#[37m] . . . . . . €¢£˜ ©œ á¢¢¦ £ã¤¬£˜
[[33mT[37m]hread . . . . €¡¦¢¦¬Ÿå˜ › ˜¢æš¦¬   [[33mD[37m]ownload . . . . Šã¯ «¦¬ ˜¨®œå¦¬
[[33mQ[37m]uickscan . . . ‚¨ãš¦¨ ˜¤å®¤œ¬©   e[[33mX[37m]it . . . . . . . . . . . „¥¦›¦ª

† œ§ ¢¦šã ©˜ª ([33m?[37m š ˜ ™¦ãŸœ ˜); } T Scan Club messages, scan choices with download


RSSCNMHD {[0;1m

!J‹§¦¨œå«œ ¤˜ ›é©œ«œ « ª œ¥ãª œ¤«¦¢âª ©œ ˜¬«æ «¦ ©£œå¦:!)

!W[33mN[37mext:     !i‹œ«˜­â¨œ©«œ ©«¦ œ§æ£œ¤¦ £ã¤¬£˜, ®à¨åª ¤˜ › ˜™á©œ«œ «¦ «¨â®¦¤.
‹§¦¨œå«œ ¤˜ ®¨© £¦§¦ ã©œ«œ ˜¬«ã «¤ œ¤«¦¢ã š ˜ â¤˜ œå›¦ª ˜§¢ãª ˜¤å®¤œ¬©ª «à¤ £¤¬£á«à¤.
ƒé©«œ §¦¢¢âª ­¦¨âª «¤ œ¤«¦¢ã N àª ©ç¤«£©, ¡˜  «¦ ©ç©«£˜ Ÿ˜ §¨¦®à¨ã©œ  œ£­˜¤å¦¤«áª ©˜ª
« ª œ§ ¡œ­˜¢å›œª (headers) «à¤ £¤¬£á«à¤ §¦¬ §œ¨¤áœ . „«© , £œ «¤ œ¤«¦¢ã [33mNNNN[37m,
 ™á© Ÿ˜ ©˜ª ›œå¥œ  « ª œ§ ¡œ­˜¢å›œª «à¤ œ§æ£œ¤à¤ «œ©©á¨à¤ £¤¬£á«à¤, ¡˜  Ÿ˜ ©«˜£˜«ã©œ  ©«¦ «œ¢œ¬«˜å¦.!)
!0l
!W[33mP[37mrevious:  !i‹œ«˜­â¨œ©«œ ©«¦ §¨¦š¦ç£œ¤¦ £ã¤¬£˜. Šœ «¦¬¨šœå æ§àª ˜¡¨ ™éª ¡˜   §¨¦š¦ç£œ¤ œ¤«¦¢ã.!)
!0l
!W[33m#[37m:         !i’¦ ©ç©«£˜ Ÿ˜ ©˜ª «ã©œ  â¤˜¤ ˜¨ Ÿ£æ £¤ç£˜«¦ª ©«¦ ¦§¦å¦ Ÿ˜ £œ«˜™œå«œ.
€¤ «¦ £ã¤¬£˜ ›œ¤ ™¨œŸœå, Ÿ˜ «¦§¦Ÿœ«Ÿœå«œ ©«¦ ¡¦¤« ¤æ«œ¨¦ £ã¤¬£˜. ‹§¦¨œå«œ ¡˜  œ›é ¤˜ ®¨© £¦§¦ ã©œ«œ
©¬¤«£ã©œ ª:  œ¤«¦¢ã [33m#1000[37m Ÿ˜ ©˜ª §áœ  ¡˜«œ¬Ÿœå˜¤ ©«¦ £ã¤¬£˜ 1000.!)
!0l
!W[33mT[37mhread:    !i€¡¦¢¦¬Ÿå˜ › ˜¢æš¦¬. €¬«ã  œ¤«¦¢ã ©˜ª œ£­˜¤åœ 
â¤˜ ˜¡æ£˜ £œ¤¦ç, £œ «¤ ™¦ãŸœ ˜ «¦¬ ¦§¦å¦¬ £§¦¨œå«œ ¤˜ ¡ ¤Ÿœå«œ ©«¦
§¨¦š¦ç£œ¤¦ ã œ§æ£œ¤¦ £ã¤¬£˜ «ª ©¬ã«©ª. ‹§¦¨œå«œ œ§å©ª ¤˜ §á«œ ©«¦
£ã¤¬£˜ §¨¦ª «¦ ¦§¦å¦ ˜§˜¤«á «¦ «¨â®¦¤ £ã¤¬£˜.!)
!0l
!W[33mQ[37muickscan: !i„›é Ÿ˜ ™¨œå«œ ¡á§¦ œª œ › ¡âª œ¤«¦¢âª š ˜ «¤ š¨ãš¦¨
˜¤å®¤œ¬©. ‹§¦¨œå«œ ¤˜ ¡ ¤Ÿœå«œ ©«¦ œ§æ£œ¤¦ ã §¨¦š¦ç£œ¤¦ club, ¤˜ ˜­˜ ¨â©œ«œ «¦
«¨â®¦¤ club ˜§æ «¤ ¢å©«˜ š¨ãš¦¨ª ˜¤å®¤œ¬©ª, ¡˜  á¢¢˜.!)
!0l
!W[33mR[37mead:      !i€¤áš¤à© «¦¬ «¨â®¦¤«¦ª £¤ç£˜«¦ª. ‹œ«á «¤ ˜¤áš¤à© â®œ«œ œ§ §¢â¦¤
›¬¤˜«æ««œª ®œ ¨ ©£¦ç «¦¬ £¤ç£˜«¦ª.!)
!0l
!W[33mD[37mownload:  !i’¦ £ã¤¬£˜ â®œ  â¤˜ ©¬¤££â¤¦ ˜¨®œå¦. ‹œ ˜¬«ã «¤ œ¤«¦¢ã £§¦¨œå«œ ¤˜ ¢á™œ«œ
˜¬«æ «¦ ˜¨®œå¦ ®à¨åª ¤˜ › ˜™á©œ«œ «¦ ©é£˜ «¦¬ £¤ç£˜«¦ª (§œ¨ š¨˜­ã «¦¬ ˜¨®œå¦¬).!)
!0l
[0;1m} T Scan Club messages, help for RSSCNMD


RSSCNR {[0;1;31m
Š¬§á£˜ , ˜¬«ã  œ§ ¢¦šã ›œ¤ œå¤˜  ›¬¤˜«ã.
[0;1m} T Scan Club messages, invalid selection from scan menu


RSDEF {[Enter=[33m%c[37m]: [0m} T Scan Club messages, default value for menus

RSGONUM {[0;1m
!J‹§¦¨œå«œ ¤˜ £œ«˜¡ ¤Ÿœå«œ ©œ ¡á§¦ ¦ ©¬š¡œ¡¨ £â¤¦ £ã¤¬£˜ ›å¤¦¤«˜ª œ›é
«¦¤ ˜¨ Ÿ£æ «¦¬.  ˜¨ Ÿ£æª ›œ¤ œå¤˜  ˜¤áš¡ ¤˜ ˜¤ã¡œ  ©œ ¬§á¨®¦¤ £ã¤¬£˜:
˜¤ «¦ ©¬š¡œ¡¨ £â¤¦ £ã¤¬£˜ ›œ¤ ™¨œŸœå, Ÿ˜ ™¨œŸœå«œ ©«¦ ¡¦¤« ¤æ«œ¨¦ £ã¤¬£˜.
‚ ˜ § ¦ š¨ãš¦¨˜, £§¦¨œå«œ ¤˜ ®¨© £¦§¦ ã©œ«œ «¤ ©ç¤«£© «ª £¦¨­ãª
[33m#123[37m ˜§æ «¦ §¨¦š¦ç£œ¤¦ £œ¤¦ç, §¦¬ Ÿ˜ ©˜ª §¨¦àŸã©œ  ¡˜«œ¬Ÿœå˜¤
©«¦ £ã¤¬£˜ 123.!)

ƒé©«œ «¦¤ ˜¨ Ÿ£æ £¤ç£˜«¦ª §¦¬ Ÿ˜ §¨¦àŸŸœå«œ ã [33mX[0;1m š ˜ ˜¡ç¨à©: } T Scan Club messages, goto what message?


RSBEG {[0;1;33m
”«á©˜«œ ©«¤ ˜¨®ã «à¤ £¤¬£á«à¤.
[0;1m} T Scan Club messages, reached beginning of messages


RSEND {[0;1;33m
”«á©˜«œ ©«¦ «â¢¦ª «à¤ £¤¬£á«à¤.
[0;1m} T Scan Club messages, reached beginning of messages


RSDEL {[0;1;31m
!J…«¦ç£œ ©¬šš¤é£, ˜¢¢á «¦ £ã¤¬£˜ ˜¬«æ £æ¢ ª › œš¨á­.!)
[0;1m} T Scan Club messages, message has just been deleted, can't read


RSIOERR {[0;1;31m
!J“§ã¨¥œ ©­á¢£˜ œšš¨˜­ãª/˜¤áš¤à©ª ¡˜«á «¤ ˜¤áš¤à© «¦¬ £¤ç£˜«¦ª.
˜¨˜¡˜¢¦ç£œ œ ›¦§¦ ã©«œ «¦¤ •œ ¨ ©«ã ‘¬©«ã£˜«¦ª š ˜ « ª ©¬¤Ÿã¡œª
§¦¬ ¦›ãš©˜¤ ©œ ˜¬«æ «¦ ¢áŸ¦ª.!)
[0;1m} T Scan Club messages, I/O error while reading message


RSRMNU1 {[0;1m
[[33mN[37m]ext . . . . . . . „§æ£œ¤¦ £ã¤¬£˜   [[33mP[37m]revious  . .  ¨¦š¦ç£œ¤¦ £ã¤¬£˜
[[33mE[37m]mail reply .  ¨¦©à§ ¡ã ˜§á¤«©   [[33mR[37m]eply  . . . . . . . . . €§á¤«©
[[33mT[37m]hread . . . . €¡¦¢¦¬Ÿå˜ › ˜¢æš¦¬   e[[33mX[37m]it  . . . . . . . . . .  „¥¦›¦ª

† œ§ ¢¦šã ©˜ª ([33m?[37m š ˜ ™¦ãŸœ ˜); } T Scan Club messages, choices after reading message


RSRMNU1H {[0;1m

!J‹§¦¨œå«œ ¤˜ ›é©œ«œ « ª œ¥ãª œ¤«¦¢âª ©œ ˜¬«æ «¦ ©£œå¦:!)

!W[33mN[37mext:     !i‹œ«˜­â¨œ©«œ ©«¦ œ§æ£œ¤¦ £ã¤¬£˜.
‹§¦¨œå«œ ¤˜ ®¨© £¦§¦ ã©œ«œ ˜¬«ã «¤ œ¤«¦¢ã š ˜ â¤˜ œå›¦ª ˜§¢ãª ˜¤å®¤œ¬©ª «à¤ £¤¬£á«à¤.
ƒé©«œ §¦¢¢âª ­¦¨âª «¤ œ¤«¦¢ã N àª ©ç¤«£©, ¡˜  «¦ ©ç©«£˜ Ÿ˜ §¨¦®à¨ã©œ  œ£­˜¤å¦¤«áª ©˜ª
« ª œ§ ¡œ­˜¢å›œª (headers) «à¤ £¤¬£á«à¤ §¦¬ §œ¨¤áœ . „«© , £œ «¤ œ¤«¦¢ã [33mNNNN[37m,
 ™á© Ÿ˜ ©˜ª ›œå¥œ  « ª œ§ ¡œ­˜¢å›œª «à¤ œ§æ£œ¤à¤ «œ©©á¨à¤ £¤¬£á«à¤, ¡˜  Ÿ˜ ©«˜£˜«ã©œ  ©«¦ «œ¢œ¬«˜å¦.!)
!0l
!W[33mP[37mrevious: !i‹œ«˜­â¨œ©«œ ©«¦ §¨¦š¦ç£œ¤¦ £ã¤¬£˜. Šœ «¦¬¨šœå æ§àª ˜¡¨ ™éª ¡˜   §¨¦š¦ç£œ¤ œ¤«¦¢ã.!)
!0l
!W[33m#[37m:        !i’¦ ©ç©«£˜ Ÿ˜ ©˜ª «ã©œ  â¤˜¤ ˜¨ Ÿ£æ £¤ç£˜«¦ª ©«¦ ¦§¦å¦ Ÿ˜ £œ«˜™œå«œ.
€¤ «¦ £ã¤¬£˜ ›œ¤ ™¨œŸœå, Ÿ˜ «¦§¦Ÿœ«Ÿœå«œ ©«¦ ¡¦¤« ¤æ«œ¨¦ £ã¤¬£˜. ‹§¦¨œå«œ ¡˜  œ›é ¤˜ ®¨© £¦§¦ ã©œ«œ
©¬¤«£ã©œ ª:  œ¤«¦¢ã [33m#1000[37m Ÿ˜ ©˜ª §áœ  ¡˜«œ¬Ÿœå˜¤ ©«¦ £ã¤¬£˜ 1000.!)
!0l
!W[33mT[37mhread:   !i€¡¦¢¦¬Ÿå˜ › ˜¢æš¦¬. €¬«ã  œ¤«¦¢ã ©˜ª œ£­˜¤åœ 
â¤˜ ˜¡æ£˜ £œ¤¦ç, £œ «¤ ™¦ãŸœ ˜ «¦¬ ¦§¦å¦¬ £§¦¨œå«œ ¤˜ ¡ ¤Ÿœå«œ ©«¦
§¨¦š¦ç£œ¤¦ ã œ§æ£œ¤¦ £ã¤¬£˜ «ª ©¬ã«©ª. ‹§¦¨œå«œ œ§å©ª ¤˜ §á«œ ©«¦
£ã¤¬£˜ §¨¦ª «¦ ¦§¦å¦ ˜§˜¤«á «¦ «¨â®¦¤ £ã¤¬£˜.!)
!0l
!W[33mE[37mmail:    !i‘®£˜«åœ«œ ˜§á¤«© §¨¦ª ˜¬«æ «¦ £ã¤¬£˜. † ˜§á¤«© Ÿ˜ ©«˜¢œå àª
§¨¦©à§ ¡æ £ã¤¬£˜ ©«¦ ˜§¦©«¦¢â˜ «¦¬ £¤ç£˜«¦ª.!)
!W[33mR[37meply:    !iƒ£ ¦¬¨šœå«˜  ›£æ© ¦ £ã¤¬£˜-˜§á¤«© §¨¦ª «¦ «¨â®¦¤ £ã¤¬£˜.!)
!0l
[0;1m} T Scan Club messages, help about reading messages, version 1


RSRMNU2 {[0;1m
[[33mN[37m]ext . . . . . . . „§æ£œ¤¦ £ã¤¬£˜   [[33mP[37m]revious . . . ¨¦š¦ç£œ¤¦ £ã¤¬£˜
[[33mC[37m]lear . . . .  ƒ ˜š¨˜­ã £¤ç£˜«¦ª   [[33mM[37m]odify  . . . .  €¢¢˜šã £¤ç£˜«¦ª
[[33mE[37m]mail reply  . ¨¦©à§ ¡ã ˜§á¤«©   [[33mR[37m]eply  . . . . . . . . . €§á¤«©
[[33mT[37m]hread  . . .  €¡¦¢¦¬Ÿå˜ › ˜¢æš¦¬   e[[33mX[37m]it  . . . . . . . . . .  „¥¦›¦ª

† œ§ ¢¦šã ©˜ª ([33m?[37m š ˜ ™¦ãŸœ ˜); } T Scan Club messages, choices after reading message


RSRMNU2H {[0;1m

!J‹§¦¨œå«œ ¤˜ ›é©œ«œ « ª œ¥ãª œ¤«¦¢âª ©œ ˜¬«æ «¦ ©£œå¦:!)

!W[33mN[37mext:     !i‹œ«˜­â¨œ©«œ ©«¦ œ§æ£œ¤¦ £ã¤¬£˜.
‹§¦¨œå«œ ¤˜ ®¨© £¦§¦ ã©œ«œ ˜¬«ã «¤ œ¤«¦¢ã š ˜ â¤˜ œå›¦ª ˜§¢ãª ˜¤å®¤œ¬©ª «à¤ £¤¬£á«à¤.
ƒé©«œ §¦¢¢âª ­¦¨âª «¤ œ¤«¦¢ã N àª ©ç¤«£©, ¡˜  «¦ ©ç©«£˜ Ÿ˜ §¨¦®à¨ã©œ  œ£­˜¤å¦¤«áª ©˜ª
« ª œ§ ¡œ­˜¢å›œª (headers) «à¤ £¤¬£á«à¤ §¦¬ §œ¨¤áœ . „«© , £œ «¤ œ¤«¦¢ã [33mNNNN[37m,
 ™á© Ÿ˜ ©˜ª ›œå¥œ  « ª œ§ ¡œ­˜¢å›œª «à¤ œ§æ£œ¤à¤ «œ©©á¨à¤ £¤¬£á«à¤, ¡˜  Ÿ˜ ©«˜£˜«ã©œ  ©«¦ «œ¢œ¬«˜å¦.!)
!0l
!W[33mP[37mrevious: !i‹œ«˜­â¨œ©«œ ©«¦ §¨¦š¦ç£œ¤¦ £ã¤¬£˜. Šœ «¦¬¨šœå æ§àª ˜¡¨ ™éª ¡˜   §¨¦š¦ç£œ¤ œ¤«¦¢ã.!)
!0l
!W[33m#[37m:        !i’¦ ©ç©«£˜ Ÿ˜ ©˜ª «ã©œ  â¤˜¤ ˜¨ Ÿ£æ £¤ç£˜«¦ª ©«¦ ¦§¦å¦ Ÿ˜ £œ«˜™œå«œ.
€¤ «¦ £ã¤¬£˜ ›œ¤ ™¨œŸœå, Ÿ˜ «¦§¦Ÿœ«Ÿœå«œ ©«¦ ¡¦¤« ¤æ«œ¨¦ £ã¤¬£˜. ‹§¦¨œå«œ ¡˜  œ›é ¤˜ ®¨© £¦§¦ ã©œ«œ
©¬¤«£ã©œ ª:  œ¤«¦¢ã [33m#1000[37m Ÿ˜ ©˜ª §áœ  ¡˜«œ¬Ÿœå˜¤ ©«¦ £ã¤¬£˜ 1000.!)
!0l
!W[33mM[37modify:   !i’¦ £ã¤¬£˜ â®œ  ©«˜¢œå ˜§æ œ©áª. „®œ«œ «¦ › ¡˜åà£˜ ¤˜ ˜¢¢á¥œ«œ «˜ §œ¨ œ®æ£œ¤á «¦¬.
€¬«ã  œ¤«¦¢ã ©˜ª œ§ «¨â§œ  ¤˜ ¡á¤œ«œ ˜¡¨ ™éª ˜¬«æ.!)
!0l
!W[33mC[37mlear:    !i’¦ £ã¤¬£˜ â®œ  ©«˜¢œå ˜§æ œ©áª. ‹œ ˜¬«ã «¤ œ¤«¦¢ã «¦ › ˜š¨á­œ«œ ˜§æ «¦ club @CLUB@.
ƒœ¤ Ÿ˜ ¬§á¨¥œ  ¡˜££å˜ œ¨é«© œ§ ™œ™˜åà©ª.!)
!0l
!W[33mT[37mhread:   !i€¡¦¢¦¬Ÿå˜ › ˜¢æš¦¬. €¬«ã  œ¤«¦¢ã ©˜ª œ£­˜¤åœ 
â¤˜ ˜¡æ£˜ £œ¤¦ç, £œ «¤ ™¦ãŸœ ˜ «¦¬ ¦§¦å¦¬ £§¦¨œå«œ ¤˜ ¡ ¤Ÿœå«œ ©«¦
§¨¦š¦ç£œ¤¦ ã œ§æ£œ¤¦ £ã¤¬£˜ «ª ©¬ã«©ª. ‹§¦¨œå«œ œ§å©ª ¤˜ §á«œ ©«¦
£ã¤¬£˜ §¨¦ª «¦ ¦§¦å¦ ˜§˜¤«á «¦ «¨â®¦¤ £ã¤¬£˜.!)
!0l
!W[33mE[37mmail:    !i‘®£˜«åœ«œ ˜§á¤«© §¨¦ª ˜¬«æ «¦ £ã¤¬£˜. † ˜§á¤«© Ÿ˜ ©«˜¢œå àª
§¨¦©à§ ¡æ £ã¤¬£˜ ©«¦ ˜§¦©«¦¢â˜ «¦¬ £¤ç£˜«¦ª.!)
!0l
!W[33mR[37meply:    !iƒ£ ¦¬¨šœå«˜  ›£æ© ¦ £ã¤¬£˜-˜§á¤«© §¨¦ª «¦ «¨â®¦¤ £ã¤¬£˜.!)
!0l
[0;1m} T Scan Club messages, help about reading messages, version 2


RSRMNU3 {[0;1m
[[33mN[37m]ext  . . . . . .  „§æ£œ¤¦ £ã¤¬£˜   [[33mP[37m]revious . . . ¨¦š¦ç£œ¤¦ £ã¤¬£˜
[[33mE[37m]mail reply  . ¨¦©à§ ¡ã ˜§á¤«©   [[33mR[37m]eply . . . . . . . . .  €§á¤«©
[[33mT[37m]hread  . . .  €¡¦¢¦¬Ÿå˜ › ˜¢æš¦¬   [[33mS[37m]IGop menu . . . „¤«¦¢âª ¦¨š˜¤à«ã
e[[33mX[37m]it . . . . . . . . . . . „¥¦›¦ª

† œ§ ¢¦šã ©˜ª ([33m?[37m š ˜ ™¦ãŸœ ˜); } T Scan Club messages, choices after reading message


RSRMNU3H {[0;1m

!J‹§¦¨œå«œ ¤˜ ›é©œ«œ « ª œ¥ãª œ¤«¦¢âª ©œ ˜¬«æ «¦ ©£œå¦:!)

!W[33mN[37mext:     !i‹œ«˜­â¨œ©«œ ©«¦ œ§æ£œ¤¦ £ã¤¬£˜.
‹§¦¨œå«œ ¤˜ ®¨© £¦§¦ ã©œ«œ ˜¬«ã «¤ œ¤«¦¢ã š ˜ â¤˜ œå›¦ª ˜§¢ãª ˜¤å®¤œ¬©ª «à¤ £¤¬£á«à¤.
ƒé©«œ §¦¢¢âª ­¦¨âª «¤ œ¤«¦¢ã N àª ©ç¤«£©, ¡˜  «¦ ©ç©«£˜ Ÿ˜ §¨¦®à¨ã©œ  œ£­˜¤å¦¤«áª ©˜ª
« ª œ§ ¡œ­˜¢å›œª (headers) «à¤ £¤¬£á«à¤ §¦¬ §œ¨¤áœ . „«© , £œ «¤ œ¤«¦¢ã [33mNNNN[37m,
 ™á© Ÿ˜ ©˜ª ›œå¥œ  « ª œ§ ¡œ­˜¢å›œª «à¤ œ§æ£œ¤à¤ «œ©©á¨à¤ £¤¬£á«à¤, ¡˜  Ÿ˜ ©«˜£˜«ã©œ  ©«¦ «œ¢œ¬«˜å¦.!)
!0l
!W[33mP[37mrevious: !i‹œ«˜­â¨œ©«œ ©«¦ §¨¦š¦ç£œ¤¦ £ã¤¬£˜. Šœ «¦¬¨šœå æ§àª ˜¡¨ ™éª ¡˜   §¨¦š¦ç£œ¤ œ¤«¦¢ã.!)
!0l
!W[33m#[37m:        !i’¦ ©ç©«£˜ Ÿ˜ ©˜ª «ã©œ  â¤˜¤ ˜¨ Ÿ£æ £¤ç£˜«¦ª ©«¦ ¦§¦å¦ Ÿ˜ £œ«˜™œå«œ.
€¤ «¦ £ã¤¬£˜ ›œ¤ ™¨œŸœå, Ÿ˜ «¦§¦Ÿœ«Ÿœå«œ ©«¦ ¡¦¤« ¤æ«œ¨¦ £ã¤¬£˜. ‹§¦¨œå«œ ¡˜  œ›é ¤˜ ®¨© £¦§¦ ã©œ«œ
©¬¤«£ã©œ ª:  œ¤«¦¢ã [33m#1000[37m Ÿ˜ ©˜ª §áœ  ¡˜«œ¬Ÿœå˜¤ ©«¦ £ã¤¬£˜ 1000.!)
!0l
!W[33mT[37mhread:   !i€¡¦¢¦¬Ÿå˜ › ˜¢æš¦¬. €¬«ã  œ¤«¦¢ã ©˜ª œ£­˜¤åœ 
â¤˜ ˜¡æ£˜ £œ¤¦ç, £œ «¤ ™¦ãŸœ ˜ «¦¬ ¦§¦å¦¬ £§¦¨œå«œ ¤˜ ¡ ¤Ÿœå«œ ©«¦
§¨¦š¦ç£œ¤¦ ã œ§æ£œ¤¦ £ã¤¬£˜ «ª ©¬ã«©ª. ‹§¦¨œå«œ œ§å©ª ¤˜ §á«œ ©«¦
£ã¤¬£˜ §¨¦ª «¦ ¦§¦å¦ ˜§˜¤«á «¦ «¨â®¦¤ £ã¤¬£˜.!)
!0l
!W[33mE[37mmail:    !i‘®£˜«åœ«œ ˜§á¤«© §¨¦ª ˜¬«æ «¦ £ã¤¬£˜. † ˜§á¤«© Ÿ˜ ©«˜¢œå àª
§¨¦©à§ ¡æ £ã¤¬£˜ ©«¦ ˜§¦©«¦¢â˜ «¦¬ £¤ç£˜«¦ª.!)
!W[33mR[37meply:    !iƒ£ ¦¬¨šœå«˜  ›£æ© ¦ £ã¤¬£˜-˜§á¤«© §¨¦ª «¦ «¨â®¦¤ £ã¤¬£˜.!)
!0l
!W[33mS[37mIGop:    !i‹œ«˜­â¨œ©«œ ©«¦ £œ¤¦ç ¦¨š˜¤à«ã «¦¬ club @CLUB@. „¡œå £§¦¨œå«œ ¤˜
˜¤« š¨á¯œ«œ, ¤˜ §¨¦àŸã©œ«œ, ¤˜ › ˜š¨á¯œ«œ ¡˜  ¤˜ £œ«˜™á¢¢œ«œ £¤ç£˜«˜, ¡˜  á¢¢˜. ‚ ˜ §œ¨ ©©æ«œ¨œª §¢¨¦­¦¨åœª
£§œå«œ ©«¦ £œ¤¦ç ¡˜  «ã©«œ ™¦ãŸœ ˜.!)
!0l
[0;1m} T Scan Club messages, help about reading messages, version 3


ATTNAP {[0;1;31m
ÛÛ  !W!i“§á¨®œ  â¤˜ ˜¨®œå¦ ©¬¤££â¤¦ ©«¦ £ã¤¬£˜, ˜¢¢á
¦ ¦¨š˜¤à«ãª «¦¬ club ›œ¤ «¦ â®œ  ˜¡æ£˜ œš¡¨å¤œ .!)
!0l[0;1m} T Download Club attachment, file not approved


ATTNAX {[0;1;31m
ÛÛ  !W!i“§á¨®œ  â¤˜ ˜¨®œå¦ ©¬¤££â¤¦ ©«¦ £ã¤¬£˜, ˜¢¢á ©œ ˜¬«æ «¦ Club
›œ¤ â®œ«œ œ§å§œ›¦ §¦¬ ¤˜ ©˜ª œ§ «¨â§œ  «¤ £œ«˜­¦¨á «¦¬.!)
!0l[0;1m} T Download Club attachment, access denied


THRMNU {[0;1m
€¡¦¢¦¬Ÿå˜ œ¥â¢ ¥ª › ˜¢æš¦¬ £â©à £¤¬£á«à¤:

[[33mF[37m]orward . . . . .  „§æ£œ¤¦ £ã¤¬£˜   [[33mB[37m]ackward . . . ¨¦š¦ç£œ¤¦ £ã¤¬£˜
[[33mP[37m]arent . . . . . . ˜«¨ ¡æ £ã¤¬£˜   [[33mR[37m]eturn  . . . . . . . . „§ ©«¨¦­ã
e[[33mX[37m]it . . . . . . . . . . . „¥¦›¦ª

† œ§ ¢¦šã ©˜ª ([33m?[37m š ˜ ™¦ãŸœ ˜); } T Scan Club messages, threading menu



THRMNUH {[0;1m

!J‹§¦¨œå«œ ¤˜ ˜¡¦¢¦¬Ÿã©œ«œ «¤ œ¥â¢ ¥ œ¤æª › ˜¢æš¦¬ §¦¢ç œç¡¦¢˜. „¤˜ª › á¢¦š¦ª
˜§¦«œ¢œå«˜  ˜§æ £¤ç£˜«˜ §¦¬ â®¦¬¤ «¦ å› ¦ Ÿâ£˜.
‹§¦¨œå«œ ¤˜ ›é©œ«œ « ª œ¥ãª œ¤«¦¢âª ©œ ˜¬«æ «¦ ©£œå¦:!)

!W[33mF[37morward:  !i‹œ«˜¡å¤© ©«¦ œ§æ£œ¤¦ £ã¤¬£˜ £œ ˜¬«æ «¦ Ÿâ£˜.!)
!0l
!W[33mB[37mackward: !i‹œ«˜­â¨œ©«œ ©«¦ §¨¦š¦ç£œ¤¦ £ã¤¬£˜ «ª ©¬ã«©ª.!)
!0l
!W[33mP[37marent:   !i‹œ«˜¡å¤© ©«¦ §˜«¨ ¡æ £ã¤¬£˜, ›¢˜›ã «¦ £ã¤¬£˜ §¨¦ª «¦ ¦§¦å¦
˜§˜¤«á «¦ «¨â®¦¤ £ã¤¬£˜.!)
!0l
!W[33mR[37meturn:   !i„§ ©«¨¦­ã ©«¦ ˜¨® ¡æ £ã¤¬£˜. † œ¤«¦¢ã ˜¬«ã ©˜ª œ§ ©«¨â­œ 
©«¦ £ã¤¬£˜ §¦¬ › ˜™á˜«œ æ«˜¤ ¥œ¡ ¤ã©˜«œ «¤ ˜¡¦¢¦¬Ÿå˜ › ˜¢æš¦¬. €¤ â®œ«œ ¡á¤œ  §á¤à ˜§æ £å˜ ˜¡¦¢¦¬Ÿå˜
› ˜¢æš¦¬, £œ«˜­â¨œ©«œ ©«¦ £ã¤¬£˜ §¦¬ › ˜™á˜«œ æ«˜¤ ¥œ¡ ¤ã©˜«œ «¤ §¨é« ˜¡¦¢¦¬Ÿå˜.!)
!0l
[0;1m} T Scan Club messages, threading help


THREAD {[0;1;36;5m
ÛÛ  [0;1;36m!W!i€¡¦¢¦¬Ÿå˜ › ˜¢æš¦¬ ([33mTR[36m š ˜ «œ¨£˜« ©£æ ˜¡¦¢¦¬Ÿå˜ª).!)
!0l[0;1m} T Scan Club messages, thread indicator


THRNRET {[0;1;31m
!Jƒœ¤ ™¨å©¡œ©«œ ©œ ¡˜«á©«˜© ˜¡¦¢¦¬Ÿå˜ª › ˜¢æš¦¬. † œ§ ©«¨¦­ã ©«¦
§¨¦š¦ç£œ¤¦ £ã¤¬£˜ ›œ¤ â®œ  ¤æ£˜.!)
[0;1m} T Threading, can't use return unless threading


THREND {[0;1;33m
!J”«á©˜«œ ©«¦ «â¢¦ª «ª ©¬ã«©ª. •¨© £¦§¦ ã©«œ «¤ œ¤«¦¢ã [37mTR[33m š ˜ ¤˜
œ§˜¤â¢Ÿœ«œ ©«¦ ˜¨® ¡æ £ã¤¬£˜.!)
[0;1m} T Threading, reached end of discussion


THRBEG {[0;1m
!J”«á©˜«œ ©«¤ ˜¨®ã «ª ©¬ã«©ª. •¨© £¦§¦ ã©«œ «¤ œ¤«¦¢ã [33mTR[37m
š ˜ ¤˜ œ§˜¤â¢Ÿœ«œ ©«¦ ˜¨® ¡æ £ã¤¬£˜.!)
[0;1m} T Threading, reached beginning of discussion


THRRET {[0;1m
!J„§ ©«¨¦­ã ©«¦ £ã¤¬£˜ [32m%s/%d[37m, «¦ ¦§¦å¦ › ˜™á˜«œ æ«˜¤
¥œ¡ ¤ã©˜«œ «¤ ˜¡¦¢¦¬Ÿå˜ › ˜¢æš¦¬.!)
[0;1m} T Threading, returning to original message


THRPR {[0;1;31m
!J‘¬šš¤é£, ˜¬«æ «¦ £ã¤¬£˜ ›œ¤ œå¤˜  ˜§á¤«© ©œ
¡á§¦ ¦ á¢¢¦. ‚ ˜ ¤˜ ›œå«œ «¦ "§˜«¨ ¡æ £ã¤¬£˜" §¨â§œ  «¦ «¨â®¦¤ £ã¤¬£˜ ¤˜
˜¤˜­â¨œ  "[37m(€§á¤«© ©«¦ Club/xxx)[31m", æ§¦¬ [37mxxx[31m
œå¤˜  ˜¨ Ÿ£æª «¦¬ "§˜«¨ ¡¦ç £¤ç£˜«¦ª".!)
} T Threading, there is no parent message


THRPNF {[0;1;31m
!J’¦ £ã¤¬£˜ [37m%s/%d[31m ›œ¤ ™¨âŸ¡œ.
 Ÿ˜¤æ«˜«˜ › ˜š¨á­«¡œ ˜§æ «¦¤ ˜§¦©«¦¢â˜, «¦¤ ¨š˜¤à«ã «¦¬ Club, ã «¦
©ç©«£˜.!)
[0;1m} T Threading, parent message not found


THRCLC {[0;1;32m
!J„š¡˜«˜¢œå§¦¬£œ «¦ club [37m@CLUB@[32m, ¡˜  £§˜å¤¦¬£œ ©«¦ [37m%s[32m.
‹§¦¨œå«œ ¤˜ ›é©œ«œ «¤ œ¤«¦¢ã [32mTR[32m š ˜ ¤˜ œ§ ©«¨â¯œ«œ ©«¦ ˜¨® ¡æ
club ¡˜  £ã¤¬£˜.!)
[0;1m} T Threading, leaving current club





MCMVT {[0;30;47m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [34m‹œ«˜™¦¢ã £¤ç£˜«¦ª[0;30;47m ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;1;37;47m¿ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  ‡â£˜ . . . . . . . . . . [1;44;37m@63;43;0s[0;1;47;37m  ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  €¨®œå¦  . . . . . . . .  [1;44;37m@16;16;0s[0;1;47;37m                             ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  Ctrl-R š ˜ ™¦ãŸœ ˜                                                      [1;37m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³             [0;1;42;33m@14;"‰œå£œ¤¦"b[0;47;30mÜ    [0;1;42;33m@14;"OK"b[0;47;30mÜ    [0;1;41;33m@14;"€¡¬¨¦"b[0;47;30mÜ  [0;1;47;37m³ [0m
[30;47m ³              ßßßßßßßßßßßßßßßß     ßßßßßßßßßßßßßßßß     ßßßßßßßßßßßßßßßß  [0;1;47;37m³ [0m
[30;47m À[0;1;37;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0m} T Modify Club Message, visual template


MCMLT {[2J[0;30;47m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [34m‹œ«˜™¦¢ã £¤ç£˜«¦ª[0;30;47m ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;1;37;47m¿ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m1[30m. ‡â£˜ . . . . [34m@63;56;0s[0;1;47;37m ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m2[30m. €¨®œå¦  . . . . . . . . . . . . . . . . . . . . . .  [34m@16;16;0s[0;1;47;37m ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m3[30m. ‹œ«˜™¦¢ã ¡œ £â¤¦¬ £¤ç£˜«¦ª@1;"3Edit"b                                         [1;37m  ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m À[0;1;37;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0;1m
} T Modify message, linear template


MCMNEWSUBJ {[0;1m
!Wƒé©«œ «¦ ¤â¦ Ÿâ£˜ «¦¬ £¤ç£˜«æª ©˜ª.!)
} T Modify message, new subject


MCMNEWATTN {[0;1m
!Wƒé©«œ «¦ ¤â¦ æ¤¦£˜ «¦¬ ©¬¤££â¤¦¬ ˜¨®œå¦¬. €¤ ˜­ã©œ«œ «¦ æ¤¦£˜ ¡œ¤æ,
Ÿ˜ œ§˜¤â¢Ÿœ  ˜¬«æ£˜«˜ ©«¦ ¡˜«á ©¬¤Ÿã¡ æ¤¦£˜, xxx.att, æ§¦¬ xxx ¦ ˜¨ Ÿ£æª
«¦¬ £¤ç£˜«¦ª. €¬«æ «¦ §œ›å¦ Ÿ˜ ˜š¤¦Ÿœå ˜¤ ›œ¤ â®œ«œ œ§ ©¬¤á¯œ  ˜¨®œå¦ ©«¦
£ã¤¬£á ©˜ª.!)
} T Modify message, new filename




COPMNU {[0;1m
„¤«¦¢âª ¦¨š˜¤à«ã:

[[33mM[37m]odify  . . . .  €¢¢˜šã £¤ç£˜«¦ª   [[33mE[37m]rase  . . . . ƒ ˜š¨˜­ã £¤ç£˜«¦ª
[[33mC[37m]opy . . . . . . . . .  €¤« š¨˜­ã   [[33mF[37m]orward . . . . . . . .  ¨¦éŸ©
[[33mT[37m]ag exempt  . . . (‹) › ˜š¨á¯ £¦   [[33mP[37m]eriodic . . . . œ¨ ¦› ¡æ £ã¤¬£˜
[[33mB[37m]ulletin . . . .  „ ©˜šàšã á¨Ÿ¨¦¬   e[[33mX[37m]it  . . . . . . . . . .  „¥¦›¦ª

† œ§ ¢¦šã ©˜ª ([33m?[37m š ˜ ™¦ãŸœ ˜); } T Club-op menu


COPMNUH {[0;1m

!J—ª ¦¨š˜¤à«ãª «¦¬ club @CLUB@, â®œ«œ « ª œ¥ãª œ › ¡âª œ¤«¦¢âª:!)

!W[33mM[37modify:     !i„§ «¨â§œ  «¤ ˜¢¢˜šã «¦¬ ¡œ £â¤¦¬ œ¤æª £¤ç£˜«¦ª,
¡˜Ÿéª ¡˜  ¦¨ ©£â¤à¤ á¢¢à¤ ®˜¨˜¡«¨ ©« ¡é¤ «¦¬ (Ÿâ£˜, £ › ˜š¨á¯ £¦, §œ¨ ¦› ¡æ £ã¤¬£˜,
æ¤¦£˜ ¡˜  âš¡¨ © ˜¨®œå¦¬, ¡¢§).!)
!0l
!W[33mE[37mrase:      !iƒ ˜š¨á­œ  «¦ £ã¤¬£˜. ƒ„Œ Ÿ˜ ¬§á¨¥œ  §¨¦œ ›¦§¦å©. ’¦ £ã¤¬£˜
®á¤œ«˜  ˜¤œ§ ©«¨œ§«å.!)
!0l
!W[33mC[37mopy:       !iƒ£ ¦¬¨šœå«˜  ˜¤«åš¨˜­¦ «¦¬ £¤ç£˜«¦ª, «¦ ¦§¦å¦ ©«â¢¤œ«˜  ©œ › œçŸ¬¤©
§¦¬ Ÿ˜ ¦¨å©œ«œ.!)
!0l
!W[33mF[37morward:    !i’¦ £ã¤¬£˜ › ˜š¨á­œ«˜  ˜§æ «¦ club, ¡˜  §¨¦àŸœå«˜  ©«¤
› œçŸ¬¤© §¦¬ Ÿ˜ ¦¨å©œ«œ.!)
!0l
!W[33mT[37mag exempt:  !i’¦ ¡œå£œ¤¦ šå¤œ«˜  £ › ˜š¨á¯ £¦. ’˜ £ › ˜š¨á¯ £˜ £¤ç£˜«˜ ›œ¤ £§¦¨¦ç¤ ¤˜ › ˜š¨˜­¦ç¤
£œ «¤ œ¤«¦¢ã [33mE[37mrase. •¨© £¦§¦ é¤«˜ª «¤ œ¤«¦¢ã [33mT[37mag ©œ â¤˜ £ã¤¬£˜ §¦¬ œå¤˜  ã› £ › ˜š¨á¯ £¦,
«¦ £ã¤¬£˜ ®á¤œ  ˜¬«ã «¤  › æ««˜ ¡˜  £§¦¨œå §¢â¦¤ ¤˜ › ˜š¨˜­œå œå«œ ˜§æ ®¨ã©«œª, œå«œ ˜§æ «¦ ©ç©«£˜.!)
!0l
!W[33mP[37meriodic:    !i‹œ ˜¬«ã «¤ œ¤«¦¢ã ¦¨åœ«œ æ«  «¦ £ã¤¬£˜ œå¤˜  §œ¨ ¦› ¡æ. ƒå¤œ«œ £å˜ §œ¨å¦›¦ ©œ £â¨œª.
’¦ £ã¤¬£˜ Ÿ˜ §¨¦àŸœå«˜  ˜¬«æ£˜«˜ ©œ ˜¬«æ «¦ Club, ©œ ¡áŸœ §œ¨å¦›æ «¦¬. €¬«æ ©£˜å¤œ  æ«  «¦ £ã¤¬£˜ Ÿ˜ ¥˜¤˜œ£­˜¤åœ«˜ 
©«¦ club ©œ «˜¡«á ®¨¦¤ ¡á › ˜©«ã£˜«˜, ©˜¤ ¤˜ ã«˜¤ ¡˜ ¤¦ç¨ ¦. €¬«æ œå¤˜  ®¨ã© £¦ š ˜ £¤ç£˜«˜ £œ ¦›šåœª š ˜ â¤˜ club,
FAQs, › ˜­£ ©« ¡á, ¡¢§. ˜¤˜®¨© £¦§¦ ã©«œ ˜¬«ã «¤ œ¤«¦¢ã, ›å¤¦¤«˜ª §œ¨å¦›¦ [33m0[37m, š ˜ ¤˜ ˜¡¬¨é©œ«œ «¤
§œ¨ ¦› ¡ã ­ç© œ¤æª £¤ç£˜«¦ª.!)
!0l
!W[33mB[37mulletin:    !i’¦ ©é£˜ «¦¬ £¤ç£˜«¦ª (ã «¦ ©¬¤££â¤¦ ˜¨®œå¦, ˜¤ â®œ  -- Ÿ˜ œ¨à«Ÿœå«œ)
œ ©ášœ«˜  ©«¦ ˜¤˜š¤à©«ã¨ ¦ á¨Ÿ¨à¤. €¡¦¢¦¬Ÿã©«œ « ª ¦›šåœª §¦¬ Ÿ˜ ©˜ª ›é©œ  «¦ ©ç©«£˜.!)
!0l
[0;1m} T Club-op menu, help


COPMNUF {[0;1m
„¤«¦¢âª ¦¨š˜¤à«ã:

[[33mM[37m]odify  . . . .  €¢¢˜šã £¤ç£˜«¦ª   [[33mE[37m]rase  . . . . ƒ ˜š¨˜­ã £¤ç£˜«¦ª
[[33mC[37m]opy . . . . . . . . .  €¤« š¨˜­ã   [[33mF[37m]orward . . . . . . . .  ¨¦éŸ©
[[33mT[37m]ag exempt  . . . (‹) › ˜š¨á¯ £¦   [[33mP[37m]eriodic . . . . œ¨ ¦› ¡æ £ã¤¬£˜
[[33mA[37m]pprove  . . . .  „š¡¨ © ˜¨®œå¦¬   [[33mI[37m]nsert att . . „¤©à£á«à© ˜¨®œå¦¬
[[33mB[37m]ulletin  . . . . „ ©˜šàšã á¨Ÿ¨¦¬   e[[33mX[37m]it  . . . . . . . . . .  „¥¦›¦ª

† œ§ ¢¦šã ©˜ª ([33m?[37m š ˜ ™¦ãŸœ ˜); } T Club-op menu for file attachments


COPERR {[0;1;31m
!JŠ¬§á£˜ , ›œ¤ ¬§á¨®œ  ˜¬«ã  œ§ ¢¦šã.!)
[0;1m} T Club-op menu, invalid selection from menu


COPMNUFH {[0;1m

!J—ª ¦¨š˜¤à«ãª «¦¬ club @CLUB@, â®œ«œ « ª œ¥ãª œ › ¡âª œ¤«¦¢âª:!)

!W[33mM[37modify:     !i„§ «¨â§œ  «¤ ˜¢¢˜šã «¦¬ ¡œ £â¤¦¬ œ¤æª £¤ç£˜«¦ª,
¡˜Ÿéª ¡˜  ¦¨ ©£â¤à¤ á¢¢à¤ ®˜¨˜¡«¨ ©« ¡é¤ «¦¬ (Ÿâ£˜, £ › ˜š¨á¯ £¦, §œ¨ ¦› ¡æ £ã¤¬£˜,
æ¤¦£˜ ¡˜  âš¡¨ © ˜¨®œå¦¬, ¡¢§).!)
!0l
!W[33mE[37mrase:      !iƒ ˜š¨á­œ  «¦ £ã¤¬£˜. ƒ„Œ Ÿ˜ ¬§á¨¥œ  §¨¦œ ›¦§¦å©. ’¦ £ã¤¬£˜
®á¤œ«˜  ˜¤œ§ ©«¨œ§«å.!)
!0l
!W[33mC[37mopy:       !iƒ£ ¦¬¨šœå«˜  ˜¤«åš¨˜­¦ «¦¬ £¤ç£˜«¦ª, «¦ ¦§¦å¦ ©«â¢¤œ«˜  ©œ › œçŸ¬¤©
§¦¬ Ÿ˜ ¦¨å©œ«œ.!)
!0l
!W[33mF[37morward:    !i’¦ £ã¤¬£˜ › ˜š¨á­œ«˜  ˜§æ «¦ club, ¡˜  §¨¦àŸœå«˜  ©«¤
› œçŸ¬¤© §¦¬ Ÿ˜ ¦¨å©œ«œ.!)
!0l
!W[33mT[37mag exempt:  !i’¦ ¡œå£œ¤¦ šå¤œ«˜  £ › ˜š¨á¯ £¦. ’˜ £ › ˜š¨á¯ £˜ £¤ç£˜«˜ ›œ¤ £§¦¨¦ç¤ ¤˜ › ˜š¨˜­¦ç¤
£œ «¤ œ¤«¦¢ã [33mE[37mrase. •¨© £¦§¦ é¤«˜ª «¤ œ¤«¦¢ã [33mT[37mag ©œ â¤˜ £ã¤¬£˜ §¦¬ œå¤˜  ã› £ › ˜š¨á¯ £¦,
«¦ £ã¤¬£˜ ®á¤œ  ˜¬«ã «¤  › æ««˜ ¡˜  £§¦¨œå §¢â¦¤ ¤˜ › ˜š¨˜­œå œå«œ ˜§æ ®¨ã©«œª, œå«œ ˜§æ «¦ ©ç©«£˜.!)
!0l
!W[33mP[37meriodic:    !i‹œ ˜¬«ã «¤ œ¤«¦¢ã ¦¨åœ«œ æ«  «¦ £ã¤¬£˜ œå¤˜  §œ¨ ¦› ¡æ. ƒå¤œ«œ £å˜ §œ¨å¦›¦ ©œ £â¨œª.
’¦ £ã¤¬£˜ Ÿ˜ §¨¦àŸœå«˜  ˜¬«æ£˜«˜ ©œ ˜¬«æ «¦ Club, ©œ ¡áŸœ §œ¨å¦›æ «¦¬. €¬«æ ©£˜å¤œ  æ«  «¦ £ã¤¬£˜ Ÿ˜ ¥˜¤˜œ£­˜¤åœ«˜ 
©«¦ club ©œ «˜¡«á ®¨¦¤ ¡á › ˜©«ã£˜«˜, ©˜¤ ¤˜ ã«˜¤ ¡˜ ¤¦ç¨ ¦. €¬«æ œå¤˜  ®¨ã© £¦ š ˜ £¤ç£˜«˜ £œ ¦›šåœª š ˜ â¤˜ club,
FAQs, › ˜­£ ©« ¡á, ¡¢§. ˜¤˜®¨© £¦§¦ ã©«œ ˜¬«ã «¤ œ¤«¦¢ã, ›å¤¦¤«˜ª §œ¨å¦›¦ [33m0[37m, š ˜ ¤˜ ˜¡¬¨é©œ«œ «¤
§œ¨ ¦› ¡ã ­ç© œ¤æª £¤ç£˜«¦ª.!)
!0l
!W[33mA[37mpprove:     !i’¦ £ã¤¬£˜ â®œ  â¤˜ ©¬¤££â¤¦ ˜¨®œå¦. ’¦ ˜¨®œå¦ œš¡¨å¤œ«˜  š ˜ ¢ã¯ ˜§æ «¦¬ª ®¨ã©«œª.
€¤ «¦ ˜¨®œå¦ œå¤˜  ã› œš¡œ¡¨ ££â¤¦, ˜¬«ã  œ¤«¦¢ã ˜¤˜ ¨œå «¤ âš¡¨ ©.!)
!0l
!W[33mI[37mnsert att:  !i¦¢¢¦å ®¨ã©«œª ©«â¢¤¦¬¤ «˜ £¤ç£˜«á «¦¬ª
àª ©¬¤££â¤˜ ˜¨®œå˜, £œ ˜§¦«â¢œ©£˜ ©®œ›æ¤ ¡˜¤œåª ¤˜ £¤ «˜ › ˜™áœ . ‹œ
˜¬«ã «¤ œ¤«¦¢ã «¦ ©¬¤££â¤¦ ©œ â¤˜ £ã¤¬£˜ ˜¨®œå¦ §¨¦©«åŸœ«˜  ©«¦ ©é£˜ «¦¬
£¤ç£˜«¦ª (ã ˜¤« ¡˜Ÿ ©«á «¦ ©é£˜ «¦¬ £¤ç£˜«¦ª -- Ÿ˜ œ¨à«Ÿœå«œ š ˜ « ª
˜¡¨ ™œåª §¨¦Ÿâ©œ ª ©˜ª). ’¦ £ã¤¬£˜ ©«˜£˜«áœ  ¤˜ â®œ  ©¬¤££â¤¦ ˜¨®œå¦.!)
!0l
!W[33mB[37mulletin:    !i’¦ ©é£˜ «¦¬ £¤ç£˜«¦ª (ã «¦ ©¬¤££â¤¦ ˜¨®œå¦, ˜¤ â®œ  -- Ÿ˜ œ¨à«Ÿœå«œ)
œ ©ášœ«˜  ©«¦ ˜¤˜š¤à©«ã¨ ¦ á¨Ÿ¨à¤. €¡¦¢¦¬Ÿã©«œ « ª ¦›šåœª §¦¬ Ÿ˜ ©˜ª ›é©œ  «¦ ©ç©«£˜.!)
!0l
[0;1m} T Club-op menu for file attachments, help



COPTTG {[0;1;32m
!J‰˜¢éª, «¦ £ã¤¬£˜ œå¤˜  §¢â¦¤ [37m‹ ƒ ˜š¨á¯ £¦[32m.!)
[0;1m} T Club-op menu, tag exempt, message has been tagged


COPTUN {[0;1;32m
!J‰˜¢éª, «¦ £ã¤¬£˜ œå¤˜  §¢â¦¤ [37m› ˜š¨á¯ £¦[32m.!)
[0;1m} T Club-op menu, tag exempt, message has been untagged


COPPASK {[0;1m
!W‰áŸœ §æ©œª £â¨œª Ÿâ¢œ«œ ¤˜ œ§˜¤œ£­˜¤åœ«˜  ˜¬«æ «¦ £ã¤¬£˜ (0=£ §œ¨ ¦› ¡æ); } T Club-op menu, periodic message, get period


COPPDEF {[Enter=%d]!) [0m} T Club-op menu, periodic message, default


COPPERR {[0;1;31m
!W˜¨˜¡˜¢é ›é©«œ â¤˜¤ ˜¨ Ÿ£æ £œ«˜¥ç [37m%d[31m ¡˜  [37m%d[31m.!)
[0;1m} T Club-op menu, periodic message, error


COPPOK1 {[0;1;32m
!W‰˜¢éª, «¦ £ã¤¬£˜ ®á¤œ  «¤ §œ¨ ¦› ¡ã «¦¬ ­ç©.!)
[0;1m} T Club-op menu, periodic message, zero period


COPPOK2 {[0;1;32m
!W‰˜¢éª, «¦ £ã¤¬£˜ Ÿ˜ œ§˜¤œ£­˜¤åœ«˜  ©«¦ club ¡áŸœ [37m%d £â¨%s[32m.!)
[0;1m} T Club-op menu, periodic message, zero period


DAYSNG {˜} T Days, singular form
DAYPLR {œª} T Days, plural form


COPAAPP {[0;1m
!J‰˜¢éª, «¦ ©¬¤££â¤¦ ©œ ˜¬«æ «¦ £ã¤¬£˜ ˜¨®œå¦ œš¡¨åŸ¡œ.!)
[0;1m} T Club-op menu, approved attached file


COPAUNA {[0;1m
!J‰˜¢éª,  âš¡¨ © ¢ã¯ª «¦¬ ©¬¤££â¤¦¬ ©œ ˜¬«æ «¦ £ã¤¬£˜ ˜¨®œå¦¬
˜§¦©ç¨œ«˜ .!)
[0;1m} T Club-op menu, unapproved attached file


COPMVT {[0;30;47m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [34m‹œ«˜™¦¢ã £¤ç£˜«¦ª[0;30;47m ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;1;37;47m¿ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  ‡â£˜ . . . . . . . . . . [1;44;37m@63;43;0s[0;1;47;37m  ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  €¨®œå¦  . . . . . . . .  [1;44;37m@16;16;0s[0;1;47;37m                             ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  „š¡¨ © ˜¨®œå¦¬ . . . .  [0;30;46m [@"X "t] [0;47;30m                      (space š ˜ ˜¢¢˜šã)  [1;37m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  ‹ › ˜š¨á¯ £¦ . . . . .  [0;30;46m [@"X "t] [0;47;30m                      (space š ˜ ˜¢¢˜šã)  [1;37m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  œ¨å¦›¦ª £¤ç£˜«¦ª  . .  [1;44;37m@6;0;999999;0n[0;30;47m    (0-999999, 0=£ §œ¨ ¦› ¡æ £ã¤¬£˜)  [1;37m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  Ctrl-R š ˜ ™¦ãŸœ ˜                                                      [1;37m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³             [0;1;42;33m@14;"‰œå£œ¤¦"b[0;47;30mÜ    [0;1;42;33m@14;"OK"b[0;47;30mÜ    [0;1;41;33m@14;"€¡¬¨¦"b[0;47;30mÜ  [0;1;47;37m³ [0m
[30;47m ³              ßßßßßßßßßßßßßßßß     ßßßßßßßßßßßßßßßß     ßßßßßßßßßßßßßßßß  [0;1;47;37m³ [0m
[30;47m À[0;1;37;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0m} T Club-op menu, modify club message, visual template


COPMLT {[2J[0;30;47m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [34m‹œ«˜™¦¢ã £¤ç£˜«¦ª[0;30;47m ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;1;37;47m¿ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m1[30m. ‡â£˜ . . . . [34m@63;56;0s[0;1;47;37m ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m2[30m. €¨®œå¦  . . . . . . . . . . . . . . . . . . . . . .  [34m@16;16;0s[0;1;47;37m ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m3[30m. „š¡¨ © ˜¨®œå¦¬  . . . . . . . . . . . . . . . . . . . . . . . .  [34m@"X "t[0;1;47;37m ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m4[30m. ‹ › ˜š¨á¯ £¦  . . . . . . . . . . . . . . . . . . . . . . . . .  [34m@"X "t[0;1;47;37m ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m5[30m. œ¨å¦›¦ª £¤ç£˜«¦ª . . . . . . . . . . . . . . . . . . . . . . [34m@6;0;999999;1n[0;1;47;37m ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m6[30m. ‹œ«˜™¦¢ã ¡œ £â¤¦¬ £¤ç£˜«¦ª@1;"6Edit"b                                         [1;37m  ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m À[0;1;37;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0;1m
} T Club-op menu, modify club message, linear template


COPMLT1 {[0;1m
!Jƒé©«œ «¦ ¤â¦ Ÿâ£˜ «¦¬ £¤ç£˜«æª ©˜ª.!)
} T Club-op menu, modify club message, linear template field #1


COPMLT2 {[0;1m
!Jƒé©«œ «¦ ¤â¦ æ¤¦£˜ «¦¬ ©¬¤££â¤¦¬ ˜¨®œå¦¬. €¤ ˜­ã©œ«œ «¦ æ¤¦£˜ ¡œ¤æ,
Ÿ˜ œ§˜¤â¢Ÿœ  ˜¬«æ£˜«˜ ©«¦ ¡˜«á ©¬¤Ÿã¡ æ¤¦£˜, xxx.att, æ§¦¬ xxx ¦ ˜¨ Ÿ£æª
«¦¬ £¤ç£˜«¦ª. €¬«æ «¦ §œ›å¦ Ÿ˜ ˜š¤¦Ÿœå ˜¤ ›œ¤ â®œ«œ œ§ ©¬¤á¯œ  ˜¨®œå¦ ©«¦
£ã¤¬£á ©˜ª.!)
} T Club-op menu, modify club message, linear template field #2


COPMLT3 {[0;1m
!J† « £ã ˜¬«¦ç «¦¬ §œ›å¦¬ ¡˜Ÿ¦¨åœ  ˜¤ «¦ ©¬¤££â¤¦ ˜¨®œå¦ œå¤˜  œš¡œ¡¨ ££â¤¦ ã æ® .
€¤ ›œ¤ ¬§á¨®œ  ©¬¤££â¤¦ ˜¨®œå¦, ˜¬«æ «¦ §œ›å¦ Ÿ˜ ˜š¤¦Ÿœå.!)
} T Club-op menu, modify club message, linear template field #3


COPMLT4 {[0;1m
!J† « £ã ˜¬«¦ç «¦¬ §œ›å¦¬ ¡˜Ÿ¦¨åœ  ˜¤ «¦ £ã¤¬£˜ œå¤˜  £ › ˜š¨á¯ £¦ ã æ® .!)
} T Club-op menu, modify club message, linear template field #4


COPMLT5 {[0;1m
!J’˜ §œ¨ ¦› ¡á £¤ç£˜«˜ œå¤˜  £¤ç£˜«˜ §¦¬ œ£­˜¤å¦¤«˜  «˜¡« ¡á ©«¦ club. €¬«æ «¦ §œ›å¦
¡˜Ÿ¦¨åœ  ˜¤ «¦ £ã¤¬£˜ §¦¬ £œ«˜™á¢¢œ«œ œå¤˜  §œ¨ ¦› ¡æ, ¡˜  ˜¤ ¤˜ , ¡áŸœ §æ©œª £â¨œª Ÿ˜
œ£­˜¤åœ«˜ . ƒé©«œ §œ¨å¦›¦ [33m0[37m š ˜ ¤˜ ¡á¤œ«œ «¦ £ã¤¬£˜ £ §œ¨ ¦› ¡æ.
€¢¢ éª, ›é©«œ «¤ §œ¨å¦›æ «¦¬ ©œ £â¨œª. ‹œ §œ¨å¦›¦ [33m1[37m, «¦ £ã¤¬£˜ ¥˜¤˜œ£­˜¤åœ«˜ 
©«¦ club ¡áŸœ £â¨˜.!)
} T Club-op menu, modify club message, linear template field #5


COPMW1 {[0;1;31m
!J’¦ £ã¤¬£˜ ›œ¤ â®œ  ©¬¤££â¤¦ ˜¨®œå¦. ’¦ §œ›å¦ âš¡¨ ©ª ˜š¤¦œå«˜ .!)
[0;1m} T Club-op menu, modify club message, warning 1


COPOK1 {[0;1;32m
!J’¦ ©¬¤££â¤¦ ©œ ˜¬«æ «¦ £ã¤¬£˜ ˜¨®œå¦ œš¡¨å¤œ«˜  š ˜ ¢ã¯.!)
[0;1m} T Club-op menu, approved message


COPOK2 {[0;1;32m
!J† âš¡¨ © ¢ã¯ª «¦¬ ©¬¤££â¤¦¬ ©œ ˜¬«æ «¦ £ã¤¬£˜ ˜¨®œå¦¬ á¨œ«˜ .!)
[0;1m} T Club-op menu, unapproved message


COPOK3 {[0;1;32m
!J’¦ £ã¤¬£˜ œå¤˜  §¢â¦¤ £ › ˜š¨á¯ £¦.!)
[0;1m} T Club-op menu, exempted message


COPOK4 {[0;1;32m
!J’¦ £ã¤¬£˜ £§¦¨œå §¢â¦¤ ¤˜ › ˜š¨˜­œå.!)
[0;1m} T Club-op menu, unexempted message


COPOK5 {[0;1;32m
!J’¦ £ã¤¬£˜ œå¤˜  §¢â¦¤ §œ¨ ¦› ¡æ, £œ §œ¨å¦›¦ [37m%d £â¨%s[32m.!)
[0;1m} T Club-op menu, periodic message


COPOK6 {[0;1;32m
!J’¦ £ã¤¬£˜ ›œ¤ œå¤˜  §¢â¦¤ §œ¨ ¦› ¡æ.!)
[0;1m} T Club-op menu, non-periodic message


COPIAMNU {[0;1m
!W’  ˜¡¨ ™éª Ÿâ¢œ«œ ¤˜ ¡á¤œ«œ £œ «¦ ©¬¤££â¤¦ ˜¨®œå¦;!)

 [[33mO[37m]verwrite body . . . . . . .  œ§ ¡á¢¬¯ ©é£˜«¦ª £¤ç£˜«¦ª
 [[33mA[37m]ppend to body  . . .  œ§ §¨æ©Ÿœ© ©«¦ ©é£˜ «¦¬ £¤ç£˜«¦ª
e[[33mX[37m]it  . . . . . . . . . . . .  ˜¡ç¨à© › ˜› ¡˜©å˜ª, â¥¦›¦ª
[0;1m} T Club-op menu, insert attachment menu


COPIASMNU {[0;1m
!Wƒé©«œ «¤ œ§ ¢¦šã ©˜ª ([33mO[37m,[33mA[37m, [33m?[37m  š ˜ ™¦ãŸœ ˜, ã [33mX[37m š ˜ â¥¦›¦):!) [0m} T Club-op menu, insert attachment short menu


COPIARS {[0;1;31m
!WŠ¬§á£˜ , ˜¬«ã  œ§ ¢¦šã ›œ¤ œå¤˜  ›¬¤˜«ã.!)
[0;1m} T Club-op menu, insert attachment, invalid selection


COPIAH {[0;1m

!WOverwrite: !i’¦ ©¬¤££â¤¦ ˜¨®œå¦ ˜¤« ¡˜Ÿ ©«á «¦ ©é£˜ «¦¬ £¤ç£˜«¦ª.
’¦ ˜¨® ¡æ ©é£˜ «¦¬ £¤ç£˜«¦ª ®á¤œ«˜  ˜¤œ§ ©«¨œ§«å.!)
!0l
!WAppend:    !i’¦ ©¬¤££â¤¦ ˜¨®œå¦ §¨¦©«åŸœ«˜  ©«¦ «â¢¦ª «¦¬ ©é£˜«¦ª «¦¬
£¤ç£˜«¦ª.!)
!0l
!W[0;1;33;5mÛÛ[0;1;33m  ‘•†: !i¨ ¤ ®¨© £¦§¦ ã©œ«œ ˜¬«ã «¤ œ¤«¦¢ã,
œ§ ™œ™˜ é©«œ æ«  «¦ ©¬¤££â¤¦ ˜¨®œå¦ §¦¬ §¨¦©§˜Ÿœå«œ ¤˜ œ¤©à£˜«é©œ«œ œå¤˜ 
æ¤«àª ˜¨®œå¦ ¡œ £â¤¦¬, ¡˜  æ®  ¡á§¦ ¦ ›¬˜› ¡æ ˜¨®œå¦.!)
!0l
[0;1m} T Club-op menu, insert attachment, help


COPIAO {[0;1;32m
!J‰˜¢éª, «¦ ©¬¤££â¤¦ ˜¨®œå¦ â®œ  §¢â¦¤ ˜¤« ¡˜«˜©«ã©œ  «¦ ©é£˜ «¦¬ £¤ç£˜«¦ª.!)
[0;1m} T Club-op menu, insert attachment, overwritten


COPIAA {[0;1;32m
!J‰˜¢éª, «¦ ©¬¤££â¤¦ ˜¨®œå¦ â®œ  §¢â¦¤ §¨¦©«œŸœå ©«¦ «â¢¦ª «¦¬ ©é£˜«¦ª
«¦¬ £¤ç£˜«¦ª.!)
[0;1m} T Club-op menu, insert attachment, appended


COPIAR {[0;1;31m
!J“§ã¨¥œ ©­á¢£˜ œšš¨˜­ãª/˜¤áš¤à©ª ¡˜«á «¤ › á¨¡œ ˜ «ª › ˜› ¡˜©å˜ª.
˜¨˜¡˜¢é œ ›¦§¦ ã©«œ «¦¤ •œ ¨ ©«ã ‘¬©«ã£˜«¦ª š ˜ « ª ©¬¤Ÿã¡œª §¦¬ ›£ ¦ç¨š©˜¤
˜¬«æ «¦ ¢áŸ¦ª.!)
[0;1m} T Club-op menu, insert attachment, error


RKASK {[0;1m
!Wƒé©«œ £å˜ ã §œ¨ ©©æ«œ¨œª ¢â¥œ ª ¡¢œ ›å˜, ã [33m?[37m š ˜ ™¦ãŸœ ˜:!)[0m } T Keyword scan, get search key(s)


RKHELP {[0;1m
!J† œ§ ¢¦šã ˜¬«ã ˜¤ ®¤œçœ  æ¢˜ «˜ £¤ç£˜«˜ œ¤æª Club ©«˜£˜«é¤«˜ª £æ¤¦ ©œ ˜¬«á
§¦¬ §œ¨ â®¦¬¤ « ª ¢â¥œ ª ¡¢œ › á §¦¬ ¦¨å©˜«œ. ‚ ˜ ¤˜ ¦¨å©œ«œ £æ¤¦ £å˜ ¢â¥
¡¢œ ›å, ˜§¢éª ›é©«œ « ¢â¥ ¡˜  §˜«ã©«œ [33mEnter[37m. ‚ ˜ §œ¨ ©©æ«œ¨œª ¢â¥œ ª
¡¢œ › á, › ˜®à¨ã©«œ « ª £œ ¡œ¤á. €¤ â®œ«œ £ ˜ ©ç¤Ÿœ« ¢â¥ ¡¢œ ›å §¦¬ §œ¨ â®œ 
¡œ¤á, ®¨© £¦§¦ ã©«œ £ ˜ §˜ç¢˜ ([33m-[37m):  §˜ç¢˜ ©£˜å¤œ  ¡œ¤æ, ©£œå¦ ©«å¥ª,
©ç£™¦¢¦ ã ¡˜  «˜ «¨å˜ £˜å.!)

!J† â¨œ¬¤˜ œå¤˜  ­à¤« ¡ã, é©«œ ¤˜ ¥œ§œ¨¤á ˜¤¦¨Ÿ¦š¨˜­åœª ¡˜  á¢¢˜ ¢áŸ.
ƒ¢˜›ã,  ¢â¥ ¡¢œ ›å "Sysop" «˜ ¨ áœ  £œ ¦§¦ ˜›ã§¦«œ ˜§æ « ª ¢â¥œ ª "©¬©¦§",
"©¬©à§", "‘“‘", "SYSOP".!)

!J‚ ˜ §˜¨á›œ š£˜, ˜¤ ›é©œ«œ àª ¢â¥œ ª ¡¢œ ›å˜ "demo system" š ˜ ¤˜ ˜¤ ®¤œç©œ«œ
«˜ £¤ç£˜«˜ £œ « ª ¢â¥œ ª "demo" ¡˜  "system", «¦ ˜§¦«â¢œ©£˜ Ÿ˜ ©¬£§œ¨ ¢á™œ 
œ¥å©¦¬ «¤ ­¨á© "drugs [32msystem[37matically [32mdemo[37mlish your brain".!)

!J‚ ˜ ¤˜ ©¬š¡œ¡¨ £œ¤¦§¦ ã©œ«œ «¤ ˜¤å®¤œ¬© ©œ "DH Demo System",
›é©«œ "DH-demo-system". €¢¢á œå¤˜  ¡˜¢ç«œ¨˜ ¤˜ â®œ«œ £œ¨ ¡á £¤ç£˜«˜ §˜¨˜§á¤à
§˜¨á ¤˜ ®á©œ«œ ¡á§¦ ˜ á¢¢˜ ©£˜¤« ¡á!!)
[0;1m} T Keyword scan, help on searching


RKSCAN1 {[0;1m
!W€¤ ®¤œçà «¦ club [32m@CLUB@[37m š ˜ «¤ ¢â¥ ¡¢œ ›å "[32m%s[37m"...!)
[0;1m} T Keyword scan, start scanning (single keyword)


RKSCAN2 {[0;1m
!W€¤ ®¤œçà «¦ club [32m@CLUB@[37m š ˜ « ª ¢â¥œ ª ¡¢œ › á "[32m%s[37m"} T Keyword scan, start scanning (multiple keyword)


RKSCAN3 {, "[32m%s[37m"} T Keyword scan, keyword


RKSCAN4 { ¡˜  "[32m%s[37m".!)
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
!WÛÛ  !i† ¢â¥ ¡¢œ ›å "%s" ™¨âŸ¡œ.!)
!0l[0;1m} T Keyword scan, found the keyword


RKCAN {[0;1;31m

!Jƒ ˜¡æ§¡œ ˜§æ «¦¤ ®¨ã©«.!)
[0;1m} T Keyword scan, aborted


FAPPSCN {[0;1;32m
!J–á®¤à «¦ club [37m@CLUB@[32m š ˜ ˜¨®œå˜ §¦¬ ˜¤˜£â¤¦¬¤ âš¡¨ ©.!)
[0;1m} T File approval, scanning for unapproved files


FAPPASK {[0;1m
!W‡â¢œ«œ ¤˜ œš¡¨å¤œ«œ ˜¬«æ «¦ ˜¨®œå¦; [[33mY[37m]yes=¤˜  / [[33mN[37m]o=æ® ):!)[0m } T File approval, approval question


FAPPERR {[0;1;31m
!JŠ¬§á£˜ , ˜¬«ã  œ§ ¢¦šã ›œ¤ œå¤˜  ›¬¤˜«ã.!)
[0;1m} T File approval, error in answer to FAPPASK


FAPPAPP {[0;1;32m
!J‰˜¢éª, «¦ ˜¨®œå¦ œå¤˜  §¢â¦¤ œš¡œ¡¨ £â¤¦ ¡˜  › ˜Ÿâ© £¦ š ˜ ¢ã¯.!)
[0;1m} T File approval, file has been approved





QSEMPTY {[0;1;31m
!J‘¬šš¤é£, ˜¢¢á ›œ¤ ¬§á¨®¦¬¤ clubs ©«¤ ¢å©«˜ š¨ãš¦¨ª ˜¤å®¤œ¬©ãª ©˜ª.
•¨© £¦§¦ ã©«œ «¤ œ¤«¦¢ã [33mRQC[31m ˜§æ «¦ ¡œ¤«¨ ¡æ £œ¤¦ç «à¤ clubs š ˜ ¤˜
¦¨å©œ«œ ©œ §¦ ˜ clubs Ÿ˜ šå¤œ«˜   š¨ãš¦¨ ˜¤å®¤œ¬©.!)
[0;1m} T Quickscan, quickscan record is empty.


QSNONEW {[0;1;33m
!Jƒœ¤ ™¨âŸ¡˜¤ ¤â˜ £¤ç£˜«˜.!)
[0;1m} T Quickscan, no new messages found


QSSCAN {[0;1;32m
!W€¤å®¤œ¬© «¦¬ [37m/%s[32m...!)
[0;1m} T Quickscan, quick scanning


QSEND {[0;1;32m
!J’â¢¦ª «ª ˜¤å®¤œ¬©ª.!)
[0;1m} T Quickscan, end of quickscan


QSABORT {[0;1;31m
!J’œ¨£˜« ©£æª «ª š¨ãš¦¨ª ˜¤å®¤œ¬©ª.!)
[0;1m} T Quickscan, aborted


QSLEAVE {[0;1;32m
!J”œçš¦¬£œ ˜§æ «¦ club [37m/@CLUB@[32m.!)
[0;1m} T Quickscan, leaving current club


QSDONE {[0;1m
!J’â¢¦ª «ª š¨ãš¦¨ª ˜¤å®¤œ¬©ª.!)
[0;1m} T Quickscan, done with quickscan


QSNNEM {[0;1;32m
!Jƒœ¤ ¬§á¨®¦¬¤ ¤â˜ £¤ç£˜«˜ ©«¦ †¢œ¡«¨¦¤ ¡æ ’˜®¬›¨¦£œå¦.!)
[0;1m} T Email Quickscan, no new mail in email area


QSLVEM {[0;1;32m
!J”œçš¦¬£œ ˜§æ «˜ £¤ç£˜«˜ †¢œ¡«¨¦¤ ¡¦ç ’˜®¬›¨¦£œå¦¬...!)
[0;1m} T Email Quickscan, leaving email area


QWRT2EM {[0;1;32m
!J„§ ©«¨â­¦¬£œ ©«˜ £¤ç£˜«˜ †¢œ¡«¨¦¤ ¡¦ç ’˜®¬›¨¦£œå¦¬...!)
[0;1m} T Email Quickscan, back to email messages


QSNOJMP {[0;1;31m
!JŠ¬§á£˜ , ˜¬«ã  œ¤«¦¢ã ›œ¤ œå¤˜  ›¬¤˜«ã ©œ ˜¬«æ «¦ ©£œå¦.!)
[0;1m} T Email Quickscan, can't use jump commands here


RQSRMNU1 {[0;1m
[[33mN[37m]ext . . . . . . . „§æ£œ¤¦ £ã¤¬£˜   [[33mP[37m]revious  . .  ¨¦š¦ç£œ¤¦ £ã¤¬£˜
[[33mE[37m]mail reply .  ¨¦©à§ ¡ã ˜§á¤«©   [[33mR[37m]eply  . . . . . . . . . €§á¤«©
[[33mT[37m]hread . . . . €¡¦¢¦¬Ÿå˜ › ˜¢æš¦¬   [[33mQ[37m]uickscan . . . ‚¨ãš¦¨ ˜¤å®¤œ¬©
e[[33mX[37m]it  . . . . . . . . . .  „¥¦›¦ª

† œ§ ¢¦šã ©˜ª ([33m?[37m š ˜ ™¦ãŸœ ˜); } T Quickscan, choices after reading message


RQSRMNU1H {[0;1m

!J‹§¦¨œå«œ ¤˜ ›é©œ«œ « ª œ¥ãª œ¤«¦¢âª ©œ ˜¬«æ «¦ ©£œå¦:!)

!W[33mN[37mext:      !i‹œ«˜­â¨œ©«œ ©«¦ œ§æ£œ¤¦ £ã¤¬£˜.
‹§¦¨œå«œ ¤˜ ®¨© £¦§¦ ã©œ«œ ˜¬«ã «¤ œ¤«¦¢ã š ˜ â¤˜ œå›¦ª ˜§¢ãª ˜¤å®¤œ¬©ª «à¤ £¤¬£á«à¤.
ƒé©«œ §¦¢¢âª ­¦¨âª «¤ œ¤«¦¢ã N àª ©ç¤«£©, ¡˜  «¦ ©ç©«£˜ Ÿ˜ §¨¦®à¨ã©œ  œ£­˜¤å¦¤«áª ©˜ª
« ª œ§ ¡œ­˜¢å›œª (headers) «à¤ £¤¬£á«à¤ §¦¬ §œ¨¤áœ . „«© , £œ «¤ œ¤«¦¢ã [33mNNNN[37m,
 ™á© Ÿ˜ ©˜ª ›œå¥œ  « ª œ§ ¡œ­˜¢å›œª «à¤ œ§æ£œ¤à¤ «œ©©á¨à¤ £¤¬£á«à¤, ¡˜  Ÿ˜ ©«˜£˜«ã©œ  ©«¦ «œ¢œ¬«˜å¦.!)
!0l 
!W[33mP[37mrevious:  !i‹œ«˜­â¨œ©«œ ©«¦ §¨¦š¦ç£œ¤¦ £ã¤¬£˜. Šœ «¦¬¨šœå æ§àª ˜¡¨ ™éª ¡˜   §¨¦š¦ç£œ¤ œ¤«¦¢ã.!)
!0l
!W[33m#[37m:         !i’¦ ©ç©«£˜ Ÿ˜ ©˜ª «ã©œ  â¤˜¤ ˜¨ Ÿ£æ £¤ç£˜«¦ª ©«¦ ¦§¦å¦ Ÿ˜ £œ«˜™œå«œ.
€¤ «¦ £ã¤¬£˜ ›œ¤ ™¨œŸœå, Ÿ˜ «¦§¦Ÿœ«Ÿœå«œ ©«¦ ¡¦¤« ¤æ«œ¨¦ £ã¤¬£˜. ‹§¦¨œå«œ ¡˜  œ›é ¤˜ ®¨© £¦§¦ ã©œ«œ
©¬¤«£ã©œ ª:  œ¤«¦¢ã [33m#1000[37m Ÿ˜ ©˜ª §áœ  ¡˜«œ¬Ÿœå˜¤ ©«¦ £ã¤¬£˜ 1000.!)
!0l
!W[33mT[37mhread:    !i€¡¦¢¦¬Ÿå˜ › ˜¢æš¦¬. €¬«ã  œ¤«¦¢ã ©˜ª œ£­˜¤åœ 
â¤˜ ˜¡æ£˜ £œ¤¦ç, £œ «¤ ™¦ãŸœ ˜ «¦¬ ¦§¦å¦¬ £§¦¨œå«œ ¤˜ ¡ ¤Ÿœå«œ ©«¦
§¨¦š¦ç£œ¤¦ ã œ§æ£œ¤¦ £ã¤¬£˜ «ª ©¬ã«©ª. ‹§¦¨œå«œ œ§å©ª ¤˜ §á«œ ©«¦
£ã¤¬£˜ §¨¦ª «¦ ¦§¦å¦ ˜§˜¤«á «¦ «¨â®¦¤ £ã¤¬£˜.!)
!0l
!W[33mQ[37muickscan: !i„›é Ÿ˜ ™¨œå«œ ¡á§¦ œª œ › ¡âª œ¤«¦¢âª š ˜ «¤ š¨ãš¦¨
˜¤å®¤œ¬©. ‹§¦¨œå«œ ¤˜ ¡ ¤Ÿœå«œ ©«¦ œ§æ£œ¤¦ ã §¨¦š¦ç£œ¤¦ club, ¤˜ ˜­˜ ¨â©œ«œ «¦
«¨â®¦¤ club ˜§æ «¤ ¢å©«˜ š¨ãš¦¨ª ˜¤å®¤œ¬©ª, ¡˜  á¢¢˜.!)
!0l
!W[33mE[37mmail:     !i‘®£˜«åœ«œ ˜§á¤«© §¨¦ª ˜¬«æ «¦ £ã¤¬£˜. † ˜§á¤«© Ÿ˜ ©«˜¢œå àª
§¨¦©à§ ¡æ £ã¤¬£˜ ©«¦ ˜§¦©«¦¢â˜ «¦¬ £¤ç£˜«¦ª.!)
!W[33mR[37meply:     !iƒ£ ¦¬¨šœå«˜  ›£æ© ¦ £ã¤¬£˜-˜§á¤«© §¨¦ª «¦ «¨â®¦¤ £ã¤¬£˜.!)
!0l
[0;1m} T Quickscan, help about reading messages, version 1


RQSRMNU2 {[0;1m
[[33mN[37m]ext . . . . . . . „§æ£œ¤¦ £ã¤¬£˜   [[33mP[37m]revious . . . ¨¦š¦ç£œ¤¦ £ã¤¬£˜
[[33mC[37m]lear . . . .  ƒ ˜š¨˜­ã £¤ç£˜«¦ª   [[33mM[37m]odify  . . . .  €¢¢˜šã £¤ç£˜«¦ª
[[33mE[37m]mail reply  . ¨¦©à§ ¡ã ˜§á¤«©   [[33mR[37m]eply  . . . . . . . . . €§á¤«©
[[33mT[37m]hread  . . .  €¡¦¢¦¬Ÿå˜ › ˜¢æš¦¬   [[33mQ[37m]uickscan . . . ‚¨ãš¦¨ ˜¤å®¤œ¬©
e[[33mX[37m]it  . . . . . . . . . .  „¥¦›¦ª

† œ§ ¢¦šã ©˜ª ([33m?[37m š ˜ ™¦ãŸœ ˜); } T Quickscan, choices after reading message


RQSRMNU2H {[0;1m

!J‹§¦¨œå«œ ¤˜ ›é©œ«œ « ª œ¥ãª œ¤«¦¢âª ©œ ˜¬«æ «¦ ©£œå¦:!)

!W[33mN[37mext:     !i‹œ«˜­â¨œ©«œ ©«¦ œ§æ£œ¤¦ £ã¤¬£˜.
‹§¦¨œå«œ ¤˜ ®¨© £¦§¦ ã©œ«œ ˜¬«ã «¤ œ¤«¦¢ã š ˜ â¤˜ œå›¦ª ˜§¢ãª ˜¤å®¤œ¬©ª «à¤ £¤¬£á«à¤.
ƒé©«œ §¦¢¢âª ­¦¨âª «¤ œ¤«¦¢ã N àª ©ç¤«£©, ¡˜  «¦ ©ç©«£˜ Ÿ˜ §¨¦®à¨ã©œ  œ£­˜¤å¦¤«áª ©˜ª
« ª œ§ ¡œ­˜¢å›œª (headers) «à¤ £¤¬£á«à¤ §¦¬ §œ¨¤áœ . „«© , £œ «¤ œ¤«¦¢ã [33mNNNN[37m,
 ™á© Ÿ˜ ©˜ª ›œå¥œ  « ª œ§ ¡œ­˜¢å›œª «à¤ œ§æ£œ¤à¤ «œ©©á¨à¤ £¤¬£á«à¤, ¡˜  Ÿ˜ ©«˜£˜«ã©œ  ©«¦ «œ¢œ¬«˜å¦.!)
!0l
!W[33mP[37mrevious: !i‹œ«˜­â¨œ©«œ ©«¦ §¨¦š¦ç£œ¤¦ £ã¤¬£˜. Šœ «¦¬¨šœå æ§àª ˜¡¨ ™éª ¡˜   §¨¦š¦ç£œ¤ œ¤«¦¢ã.!)
!0l
!W[33m#[37m:        !i’¦ ©ç©«£˜ Ÿ˜ ©˜ª «ã©œ  â¤˜¤ ˜¨ Ÿ£æ £¤ç£˜«¦ª ©«¦ ¦§¦å¦ Ÿ˜ £œ«˜™œå«œ.
€¤ «¦ £ã¤¬£˜ ›œ¤ ™¨œŸœå, Ÿ˜ «¦§¦Ÿœ«Ÿœå«œ ©«¦ ¡¦¤« ¤æ«œ¨¦ £ã¤¬£˜. ‹§¦¨œå«œ ¡˜  œ›é ¤˜ ®¨© £¦§¦ ã©œ«œ
©¬¤«£ã©œ ª:  œ¤«¦¢ã [33m#1000[37m Ÿ˜ ©˜ª §áœ  ¡˜«œ¬Ÿœå˜¤ ©«¦ £ã¤¬£˜ 1000.!)
!0l
!W[33mM[37modify:   !i’¦ £ã¤¬£˜ â®œ  ©«˜¢œå ˜§æ œ©áª. „®œ«œ «¦ › ¡˜åà£˜ ¤˜ ˜¢¢á¥œ«œ «˜ §œ¨ œ®æ£œ¤á «¦¬.
€¬«ã  œ¤«¦¢ã ©˜ª œ§ «¨â§œ  ¤˜ ¡á¤œ«œ ˜¡¨ ™éª ˜¬«æ.!)
!0l
!W[33mC[37mlear:    !i’¦ £ã¤¬£˜ â®œ  ©«˜¢œå ˜§æ œ©áª. ‹œ ˜¬«ã «¤ œ¤«¦¢ã «¦ › ˜š¨á­œ«œ ˜§æ «¦ club @CLUB@.
ƒœ¤ Ÿ˜ ¬§á¨¥œ  ¡˜££å˜ œ¨é«© œ§ ™œ™˜åà©ª.!)
!0l
!W[33mT[37mhread:   !i€¡¦¢¦¬Ÿå˜ › ˜¢æš¦¬. €¬«ã  œ¤«¦¢ã ©˜ª œ£­˜¤åœ 
â¤˜ ˜¡æ£˜ £œ¤¦ç, £œ «¤ ™¦ãŸœ ˜ «¦¬ ¦§¦å¦¬ £§¦¨œå«œ ¤˜ ¡ ¤Ÿœå«œ ©«¦
§¨¦š¦ç£œ¤¦ ã œ§æ£œ¤¦ £ã¤¬£˜ «ª ©¬ã«©ª. ‹§¦¨œå«œ œ§å©ª ¤˜ §á«œ ©«¦
£ã¤¬£˜ §¨¦ª «¦ ¦§¦å¦ ˜§˜¤«á «¦ «¨â®¦¤ £ã¤¬£˜.!)
!W[33mQ[37muickscan: !i„›é Ÿ˜ ™¨œå«œ ¡á§¦ œª œ › ¡âª œ¤«¦¢âª š ˜ «¤ š¨ãš¦¨
˜¤å®¤œ¬©. ‹§¦¨œå«œ ¤˜ ¡ ¤Ÿœå«œ ©«¦ œ§æ£œ¤¦ ã §¨¦š¦ç£œ¤¦ club, ¤˜ ˜­˜ ¨â©œ«œ «¦
«¨â®¦¤ club ˜§æ «¤ ¢å©«˜ š¨ãš¦¨ª ˜¤å®¤œ¬©ª, ¡˜  á¢¢˜.!)
!0l
!0l
!W[33mE[37mmail:    !i‘®£˜«åœ«œ ˜§á¤«© §¨¦ª ˜¬«æ «¦ £ã¤¬£˜. † ˜§á¤«© Ÿ˜ ©«˜¢œå àª
§¨¦©à§ ¡æ £ã¤¬£˜ ©«¦ ˜§¦©«¦¢â˜ «¦¬ £¤ç£˜«¦ª.!)
!0l
!W[33mR[37meply:    !iƒ£ ¦¬¨šœå«˜  ›£æ© ¦ £ã¤¬£˜-˜§á¤«© §¨¦ª «¦ «¨â®¦¤ £ã¤¬£˜.!)
!0l
[0;1m} T Quickscan, help about reading messages, version 2


RQSRMNU3 {[0;1m
[[33mN[37m]ext  . . . . . .  „§æ£œ¤¦ £ã¤¬£˜   [[33mP[37m]revious . . . ¨¦š¦ç£œ¤¦ £ã¤¬£˜
[[33mE[37m]mail reply  . ¨¦©à§ ¡ã ˜§á¤«©   [[33mR[37m]eply . . . . . . . . .  €§á¤«©
[[33mT[37m]hread  . . .  €¡¦¢¦¬Ÿå˜ › ˜¢æš¦¬   [[33mS[37m]IGop menu . . . „¤«¦¢âª ¦¨š˜¤à«ã
[[33mQ[37m]uickscan . . . ‚¨ãš¦¨ ˜¤å®¤œ¬©   e[[33mX[37m]it . . . . . . . . . . . „¥¦›¦ª

† œ§ ¢¦šã ©˜ª ([33m?[37m š ˜ ™¦ãŸœ ˜); } T Quickscan, choices after reading message


RQSRMNU3H {[0;1m

!J‹§¦¨œå«œ ¤˜ ›é©œ«œ « ª œ¥ãª œ¤«¦¢âª ©œ ˜¬«æ «¦ ©£œå¦:!)

!W[33mN[37mext:     !i‹œ«˜­â¨œ©«œ ©«¦ œ§æ£œ¤¦ £ã¤¬£˜.
‹§¦¨œå«œ ¤˜ ®¨© £¦§¦ ã©œ«œ ˜¬«ã «¤ œ¤«¦¢ã š ˜ â¤˜ œå›¦ª ˜§¢ãª ˜¤å®¤œ¬©ª «à¤ £¤¬£á«à¤.
ƒé©«œ §¦¢¢âª ­¦¨âª «¤ œ¤«¦¢ã N àª ©ç¤«£©, ¡˜  «¦ ©ç©«£˜ Ÿ˜ §¨¦®à¨ã©œ  œ£­˜¤å¦¤«áª ©˜ª
« ª œ§ ¡œ­˜¢å›œª (headers) «à¤ £¤¬£á«à¤ §¦¬ §œ¨¤áœ . „«© , £œ «¤ œ¤«¦¢ã [33mNNNN[37m,
 ™á© Ÿ˜ ©˜ª ›œå¥œ  « ª œ§ ¡œ­˜¢å›œª «à¤ œ§æ£œ¤à¤ «œ©©á¨à¤ £¤¬£á«à¤, ¡˜  Ÿ˜ ©«˜£˜«ã©œ  ©«¦ «œ¢œ¬«˜å¦.!)
!0l
!W[33mP[37mrevious: !i‹œ«˜­â¨œ©«œ ©«¦ §¨¦š¦ç£œ¤¦ £ã¤¬£˜. Šœ «¦¬¨šœå æ§àª ˜¡¨ ™éª ¡˜   §¨¦š¦ç£œ¤ œ¤«¦¢ã.!)
!0l
!W[33m#[37m:        !i’¦ ©ç©«£˜ Ÿ˜ ©˜ª «ã©œ  â¤˜¤ ˜¨ Ÿ£æ £¤ç£˜«¦ª ©«¦ ¦§¦å¦ Ÿ˜ £œ«˜™œå«œ.
€¤ «¦ £ã¤¬£˜ ›œ¤ ™¨œŸœå, Ÿ˜ «¦§¦Ÿœ«Ÿœå«œ ©«¦ ¡¦¤« ¤æ«œ¨¦ £ã¤¬£˜. ‹§¦¨œå«œ ¡˜  œ›é ¤˜ ®¨© £¦§¦ ã©œ«œ
©¬¤«£ã©œ ª:  œ¤«¦¢ã [33m#1000[37m Ÿ˜ ©˜ª §áœ  ¡˜«œ¬Ÿœå˜¤ ©«¦ £ã¤¬£˜ 1000.!)
!0l
!W[33mT[37mhread:   !i€¡¦¢¦¬Ÿå˜ › ˜¢æš¦¬. €¬«ã  œ¤«¦¢ã ©˜ª œ£­˜¤åœ 
â¤˜ ˜¡æ£˜ £œ¤¦ç, £œ «¤ ™¦ãŸœ ˜ «¦¬ ¦§¦å¦¬ £§¦¨œå«œ ¤˜ ¡ ¤Ÿœå«œ ©«¦
§¨¦š¦ç£œ¤¦ ã œ§æ£œ¤¦ £ã¤¬£˜ «ª ©¬ã«©ª. ‹§¦¨œå«œ œ§å©ª ¤˜ §á«œ ©«¦
£ã¤¬£˜ §¨¦ª «¦ ¦§¦å¦ ˜§˜¤«á «¦ «¨â®¦¤ £ã¤¬£˜.!)
!0l
!W[33mQ[37muickscan: !i„›é Ÿ˜ ™¨œå«œ ¡á§¦ œª œ › ¡âª œ¤«¦¢âª š ˜ «¤ š¨ãš¦¨
˜¤å®¤œ¬©. ‹§¦¨œå«œ ¤˜ ¡ ¤Ÿœå«œ ©«¦ œ§æ£œ¤¦ ã §¨¦š¦ç£œ¤¦ club, ¤˜ ˜­˜ ¨â©œ«œ «¦
«¨â®¦¤ club ˜§æ «¤ ¢å©«˜ š¨ãš¦¨ª ˜¤å®¤œ¬©ª, ¡˜  á¢¢˜.!)
!0l
!W[33mE[37mmail:    !i‘®£˜«åœ«œ ˜§á¤«© §¨¦ª ˜¬«æ «¦ £ã¤¬£˜. † ˜§á¤«© Ÿ˜ ©«˜¢œå àª
§¨¦©à§ ¡æ £ã¤¬£˜ ©«¦ ˜§¦©«¦¢â˜ «¦¬ £¤ç£˜«¦ª.!)
!W[33mR[37meply:    !iƒ£ ¦¬¨šœå«˜  ›£æ© ¦ £ã¤¬£˜-˜§á¤«© §¨¦ª «¦ «¨â®¦¤ £ã¤¬£˜.!)
!0l
!W[33mS[37mIGop:    !i‹œ«˜­â¨œ©«œ ©«¦ £œ¤¦ç ¦¨š˜¤à«ã «¦¬ club @CLUB@. „¡œå £§¦¨œå«œ ¤˜
˜¤« š¨á¯œ«œ, ¤˜ §¨¦àŸã©œ«œ, ¤˜ › ˜š¨á¯œ«œ ¡˜  ¤˜ £œ«˜™á¢¢œ«œ £¤ç£˜«˜, ¡˜  á¢¢˜. ‚ ˜ §œ¨ ©©æ«œ¨œª §¢¨¦­¦¨åœª
£§œå«œ ©«¦ £œ¤¦ç ¡˜  «ã©«œ ™¦ãŸœ ˜.!)
!0l
[0;1m} T Quickscan, help about reading messages, version 3


QSMMNU {[0;1m
„¤«¦¢âª š¨ãš¦¨ª ˜¤å®¤œ¬©ª:

[[33mN[37m]ext club . . . . .  „§æ£œ¤¦ club   [[33mP[37m]revious club  . ¨¦š¦ç£œ¤¦ club
[[33mR[37m]emove club . . . . €­˜å¨œ© club   [[33mB[37m]ookmark  . . . . . ‘œ¢ ›¦›œå¡«ª
[[33mC[37m]atch up . . ’â¢¦ª ˜¤áš¤à©ª club   [[33mS[37m]elect club  . . . . „§ ¢¦šã club
e[[33mX[37m]it  . . . . . . . . . .  „¥¦›¦ª

† œ§ ¢¦šã ©˜ª ([33m?[37m š ˜ ™¦ãŸœ ˜); } T Quickscan menu


QWMNUR {[0;1;31m
!JŠ¬§á£˜ , ˜¬«ã  œ§ ¢¦šã ›œ¤ œå¤˜  ›¬¤˜«ã.!)
[0;1m} T Quickscan menu, invalid selection


QSMNUH {[0;1m

!J‹§¦¨œå«œ ¤˜ ›é©œ«œ « ª œ¥ãª œ¤«¦¢âª ©œ ˜¬«æ «¦ ©£œå¦:!)

!W[33mN[37mext club:     !i‹œ«˜­â¨œ©«œ ©«¦ œ§æ£œ¤¦ club «ª š¨ãš¦¨ª ˜¤å®¤œ¬©ãª ©˜ª.
©˜ £¤ç£˜«˜ ›œ¤ â®œ«œ ˜¡æ£˜ › ˜™á©œ  ©œ ˜¬«æ «¦ club §˜¨˜£â¤¦¬¤ ˜› á™˜©«˜ ¡˜  Ÿ˜ ©˜ª §¨¦©­œ¨Ÿ¦ç¤
š ˜ ˜¤áš¤à© ©«¤ œ§æ£œ¤ š¨ãš¦¨ ˜¤å®¤œ¬©. €¤ ›œ¤ ¬§á¨®œ  œ§æ£œ¤¦ club, «æ«œ
 š¨ãš¦¨ ˜¤å®¤œ¬© ©«˜£˜«áœ  œ›é.!)
!0l
!W[33mP[37mrevious club: !iŠœ «¦¬¨šœå æ§àª ˜¡¨ ™éª ¡˜   §¨¦š¦ç£œ¤ œ¤«¦¢ã, ˜¢¢á ©˜ª
£œ«˜­â¨œ  ©«¦ §¨¦š¦ç£œ¤¦ club.!)
!0l
!W[33mR[37memove club:   !i€­˜ ¨œå «¦ «¨â®¦¤ club ˜§æ «¤ ¢å©«˜ š¨ãš¦¨ª ˜¤å®¤œ¬©ãª ©˜ª.
‹œ«˜­â¨œ©«œ ˜¬«æ£˜«˜ ©«¦ œ§æ£œ¤¦ club. ’˜ ¤â˜ £¤ç£˜«˜ «¦¬ club ›œ¤ Ÿ˜ ©˜ª §¨¦©­â¨¦¤«˜ 
§¢â¦¤ š ˜ ˜¤áš¤à©, œ¡«æª ¡  ˜¤ ¥˜¤˜§¨¦©Ÿâ©œ«œ «¦ club ©«¤ ¢å©«˜ š¨ãš¦¨ª ˜¤å®¤œ¬©ãª ©˜ª,
£œ «¤ œ¤«¦¢ã [33mCRQC[37m ˜§æ «¦ ¡œ¤«¨ ¡æ £œ¤¦ç «ª ™á©ª.!)
!0l
!W[33mB[37mookmark:      !i‹œ ˜¬«ã «¤ œ¤«¦¢ã ¦¨åœ«œ §¦ ¦ Ÿ˜ Ÿœà¨œå«˜  «¦ «œ¢œ¬«˜å¦
› ˜™˜©£â¤¦ £ã¤¬£˜ «¦¬ club. ’¦ «¨â®¦¤ £ã¤¬£˜ ¡˜  æ¢˜ «˜ œ§æ£œ¤˜ £¤ç£˜«˜ «¦¬ club
Ÿ˜ Ÿœà¨Ÿ¦ç¤ £ › ˜™˜©£â¤˜ ¡˜  Ÿ˜ ©˜ª §¨¦©­œ¨Ÿ¦ç¤ š ˜ ˜¤áš¤à© ©«¤ œ§æ£œ¤ š¨ãš¦¨ ˜¤å®¤œ¬©. €¬«ã
 œ¤«¦¢ã œå¤˜  ®¨ã© £ ˜¤ â®œ«œ ã› › ˜™á©œ  «¦ club, ˜¢¢á Ÿâ¢œ«œ ¤˜ «¦ ¥˜¤˜› ˜™á©œ«œ § ¦ §¨¦©œ¡« ¡á
˜¨šæ«œ¨˜.!)
!0l
!W[33mC[37match up:      !i¢˜ «˜ £¤ç£˜«˜ «¦¬ club Ÿœà¨¦ç¤«˜  ˜¬«æ£˜«˜ › ˜™˜©£â¤˜. ‹œ«˜­â¨œ©«œ
©«¦ œ§æ£œ¤¦ club.!)
!0l
!W[33mS[37melect club:   !i‹œ ˜¬«ã «¤ œ¤«¦¢ã £§¦¨œå«œ ¤˜ £œ«˜­œ¨Ÿœå«œ ©œ â¤˜ á¢¢¦ club ›å¤¦¤«˜ª
˜§¢éª «¦ æ¤¦£á «¦¬. ’¦ club ›œ¤ œå¤˜  ˜¤áš¡ ¤˜ §œ¨ ¢˜£™á¤œ«˜  ©«¤ ¢å©«˜ š¨ãš¦¨ª ˜¤å®¤œ¬©ãª
©˜ª.!)
!0l
[0;1m} T Quickscan menu, help


QSMBM {[0;1;32m
!J‰˜¢éª, «¦ £ã¤¬£˜ [37m%d[32m Ÿœà¨œå«˜  «¦ §¨é«¦ £ › ˜™˜©£â¤¦ £ã¤¬£˜ «¦¬
club [37m%s[32m.!)
[0;1m} T Quickscan menu, bookmark placed


QSMCU {[0;1;32m
!J‰˜¢éª, æ¢˜ «˜ £¤ç£˜«˜ «¦¬ club [37m%s[32m Ÿœà¨¦ç¤«˜  › ˜™˜©£â¤˜.!)
[0;1m} T Quickscan menu, caught up


QSMRM {[0;1;32m
!J‰˜¢éª, «¦ club [37m%s[32m ˜­˜ ¨œå«˜  ˜§æ «¤ ¢å©«˜ š¨ãš¦¨ª ˜¤å®¤œ¬©ª.
€¤ Ÿâ¢œ«œ ¤˜ «¦ ¥˜¤˜§¨¦©Ÿâ©œ«œ, §¨â§œ  ¤˜ ®¨© £¦§¦ ã©œ«œ «¤ œ¤«¦¢ã
[33mCRQC[32m ˜§æ «¦ ¡œ¤«¨ ¡æ £œ¤¦ç «ª ™á©ª ([33mRQC[32m ˜§æ «¦
¡œ¤«¨ ¡æ £œ¤¦ç «à¤ clubs).!)
[0;1m} T Quickscan menu, removed club from quickscan configuration


TLCNAX {[0;1;31m
!JŠ¬§á£˜ , «¦ œ§å§œ›æ ©˜ª ›œ¤ œ§ «¨â§œ  ¤˜ £§œå«œ ©«¦ ¡˜¤á¢  «¢œ©¬¤¦£ ¢ é¤
˜¬«¦ç «¦¬ club.!)
[0;1m} T Enter teleconferences, access denied


BLTNAX {[0;1;31m
!JŠ¬§á£˜ , «¦ œ§å§œ›æ ©˜ª ›œ¤ œ§ «¨â§œ  ¤˜ £§œå«œ ©«¦ ˜¤˜š¤à©«ã¨ ¦ á¨Ÿ¨à¤
˜¬«¦ç «¦¬ club.!)
[0;1m} T Enter bulletin reader, access denied


LANG {}


HISTCC {Copy of %s} S 50 Message history: carbon copy


HISTCP {Copied by %s} S 50 Message history: message copy


HISTFW {Forwarded by %s} S 50 Message history: forward


HISTNM {Internet mail} S 50 Message history: netmail


HISTRRR {Return receipt of %s} S 50 Message history: return receipt


HISTREP {Reply to %s} S 50 Message history: reply


HISTAFW {Autoforwarded by %s} S 50 Message history: autoforward


HISTDST {Distributed} S 50 Message history: distributed


HISTOLR {Off-line} S 50 Message history: off-line


HISTNET {Networked from %s} S 50 Message history: via network



TIMEOUT1 {
!J[0;1;33mThe system is rebuilding some of its files as part
of regular maintenance or to resolve problems. This may take a
while. Please be patient. We apologise for the delay...!)
[0;1m} T bbsmail: timed out waiting for message number lock (1)


TIMEOUT2 {
!J[0;1;31mWe apologise, but the error condition still hasn't been
resolved. We are unable to keep your message.!)
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
New user signup, "%s".
} T Electronic Mail alert to Sysop of new-user mail


CLUBINFO {[0;1m
!J@BBS@ has a wide choice of [32m"special interest groups"[37m (aka SIGs,
clubs or forums), hosting discussions on many topics. Since this is your
first time on the BBS, we'll automatically subscribe you to all clubs.!)

!JYou can see new messages in all clubs in your quickscan (i.e.
subscription) list by typing [33mQ[37m or [33mCRQS[37m at the main menu
prompt, or [33m/GO CRQS[37m anywhere in the system. To edit your quickscan
list, enter [33mCRQC[37m at the main menu or [33m/GO CRQC[37m anywhere
in the system.!)

!JYou probably won't see any new messages this time, unless some are
written while you're connected. In subsequent connections, however,
the quickscan command will present all new messages of all clubs you're
subscribed to.!)
[0;1m} T User is new, created a fresh quickscan config with ALL clubs.


CHKNCLB {[s[0;1;35mOne moment, scanning clubs...}


NNEWCLB {[u[0;1m[K
[0;1m} T Clubs, no new messages found


NEWCLUB {[u[0;1m[K
!W[5mÛÛ[0;1m  !iThere are [5mnew[0;1m club messages for you.!)
!0l[0;1m} T Clubs, new mail waiting alert


NEWMAIL {[0;1m
!W[5mÛÛ[0;1m  !iThere are [5mnew[0;1m private email messages for you.!)
!0l[0;1m} T E-Mail new private mail waiting alert


OLDMAIL {[0;1;32m
!WThere are old private email messages for you.!)
[0;1m} T E-Mail old private mail waiting alert


HOW2READ {[0;1;32m
!WTo read them, enter [33mERT[32m
([[33mE[32m]mail [[33mR[32m]ead [[33mT[32m]o you)
at the main menu.!)
[0;1m} T E-Mail post-alert recommendation


ASKRDNOW {[0;1m
!WRead them now? [[33mY[37m]yes / [[33mN[37m]o) } T Ask if user wants to read E-mail now

ASKRDERR {[0;1;31m
Sorry, this option is not possible.
[0;1m} T Invalid selection for ASKRDNOW

ASKRDDEF {[Enter=[33mN[37m]!) [0m} T Default answer to ASKRDNOW


NOENTRY {[0;1;31m
Sorry, you don't have access to the email area.
[0;1m} T User does not have access to the E-mail module


EMMNU {[2J[0m[47;1;37m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;30;47m¿ [40m
[47;1;37m ³  [0;47;30m  Electronic Mail  [0;47;30m³ [40m
[47;1;37m ³  [0;47;30mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ  [0;47;30m³ [40m
[47;1;37m ³  [0;31;47mA[30mbout E-mail       [30m³ [40m
[47;1;37m ³  [0;31;47mR[30mead your mail     [30m³ [40m
[47;1;37m ³  [0;31;47mW[30mrite message      [30m³ [40m
[47;1;37m ³  [0;31;47mM[30modify message     [30m³ [40m
[47;1;37m ³  [0;31;47mP[30mreferences        [30m³ [40m
[47;1;37m ³  [0;31;47mD[30mistribution list  [30m³ [40m
[47;1;37m ³                     [0;47;30m³ [40m
[47;1;37m ³ [0;30;47me[31mX[30mit                [30m³ [40m
[47;1;37m À[0;30;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0;1m

Email
Enter your choice: [0m} T Electronic mail menu


SHEMMNU {[0;1m
Email
!WEnter your choice ([33mA[37m,[33mR[37m,[33mW[37m,[33mM[37m,[33mP[37m,[33mD[37m,[33mX[37m to exit, or [33m?[37m for the menu): !)[0m} T Electronic mail short menu


ERRSEL {[0;1;31m
Sorry, there is no command "%c".
[0;1m} T Invalid option selection


NOAXES {[0;1;31m
Sorry, you don't have access to that.
[0;1;31m} T User has no access to chosen area


EMLEAVE {[0;1m
Leaving email.
} T Exiting from the Electronic Mail module


ABOUT {[0;1m

!JUsing email you can send and receive local and global (Internet) mail.!)

!JIf this is your first time in this part of the system, try the
[33mP[37m (Preferences) command to set your preferences and options
including your personal signature.!)

!JYou can read messages (type [[33mR[37m]ead) and send a message or
messages ([[33mW[37m]rite).!)

!JYou can also change the text of a message after it's sent
([[33mM[37m]odify), or even delete it. These two commands only work for
local messages, of course. You can't alter or delete Internet messages that
have already been sent.!)

!JUse the [[33mP[37m]references command to set options and
preferences. You can also create a personal mailing list so to mail all your
friends with one command (try [[33mD[37m]istribution list).!)

[0;1m} T About the email module


PMENU {[2J[0m[47;1;37m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;30;47m¿ [40m
[47;1;37m ³  [0;47;30m                  Electronic Mail Preferences                    [0;47;30m³ [40m
[47;1;37m ³  [0;47;30mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ  [0;47;30m³ [40m
[47;1;37m ³  [0;31;47m1[30m . .  Automatic forwarding of email to another address  [30m³ [40m
[47;1;37m ³  [0;31;47m2[30m  . . . . . . . . . . . Quoting preferences in replies  [30m³ [40m
[47;1;37m ³  [0;31;47m3[30m . . . . . .  Notification about new messages at login  [30m³ [40m
[47;1;37m ³  [0;31;47m4[30m  . . . . . . . . . . . . .  Change personal signature  [30m³ [40m
[47;1;37m ³                                                                   [0;47;30m³ [40m
[47;1;37m ³ [0;30;47me[31mX[30m  . . . . . . . . . . . . . Save changes and exit  [30m³ [40m
[47;1;37m À[0;30;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0;1m
[0;1m} T Preferences, menu


PMENUS {[0;1m
Electronic Mail preferences
!WEnter your command ([33m1[37m,[33m2[37m,[33m3[37m,[33m4[37m,[33mX[37m to exit, or [33m?[37m for the menu): !)[0m} T Preferences, short menu


PQUEST1A {[0;1m

!WEnter the user ID of a user to whom all incoming email will be
forwarded.!) } T Preferences, question 1A, sysop access


PQUEST1IA {[0;1;32m
!JAll your mail will be autoforwarded to [37m%s[32m.!)
[0;1m} T Preferences, autoforwarding information 1


PQUEST1IB {[0;1;32m
!JYour mail is not autoforwarded right now.!)
[0;1m} T Preferences, autoforwarding information 2


PQUEST1B {[0;1m

!JIf you wish, you can have all your mail autoforwarded to another user
on this system. This comes in handy when you have to be absent for long
periods of time. You can't forward your mail to Internet addresses, only
to local users.!)

!JWarning: in case of circular forwarding (A autoforwards to B, B
autoforwards back to A), the system will cancel autoforwarding,
delivering the message to its original recipient.!)

!WEnter the user ID of the user to receive your messages,
or [33mEnter[37m to disable autoforwarding!) } T Preferences, question 1B

PQUEST1D {[Enter=[33m%s[37m] [0m} T Preferences, default value for PQUEST1A


PQUEST1N {[0;1;32m

!JSorry, only the Sysop can set autoforwarding.
Please send a message to [37mSysop[32m specifying the user ID to which
you want your mail autoforwarded.!)
[0;1m} T Preferences, question 1, no access



PQUEST1U {[0;1;31m
!JSorry, that user does not exist.!)
[0;1m} T Preferences, question 1, unknown user


PQUEST1O {[0;1;32m
!JMail to you will be autoforwarded to [37m%s[32m.!)
[0;1m} T Preferences, question 1, autoforwarding set


PQUEST1Y {[0;1;32m
!JAutoforwarding is now disabled.!)
[0;1m} T Preferences, question 1, autoforwarding disabled


PQUEST2 {[0;1m

!JWhen you reply to email, you often need to quote part of the message
you're replying to. This menu controls your preferred quoting behaviour.!)

  [33m1[37m. Messages will never be quoted.
  [33m2[37m. Messages will always be quoted.
  [33m3[37m. You will be asked whether to quote individual messages.

[0;1m} T Preferences, question 2


PQUEST2S {[0;1m
!WEnter your choice ([33m1[37m,[33m2[37m,[33m3[37m, or [33mX[37m to save and exit):!) [0m} T Preferences, question 2, short menu


PQUEST2R {[0;1;31m
Sorry, that option is not possible here.
[0;1m} T Preferences, question 2, bad option



PQUEST3 {[0;1m

!JImmediately after you login, the system notifies you of any
new messages. If you want, you can read new mail immediately, or to
complete your login and read mail later, at your convenience. Here are
the possible notification/reading options:!)

  [33m1[37m. The system merely notifies you of new mail.
  [33m2[37m. New mail will be presented immediately for reading.
  [33m3[37m. You will be asked if you want to read mail immediately.

[0;1m} T Preferences, question 3


PQUEST3S {[0;1m
!WEnter your choice ([33m1[37m,[33m2[37m,[33m3[37m, or [33mX[37m to save and exit):!) [0m} T Preferences, question 3, short menu


PQUEST3R {[0;1;31m
Sorry, that option is not available here.
[0;1m} T Preferences, question 3, bad option


NOAXSIG {[0;1;31m
!JSorry, your access level does not permit changing your signature.!)
[0;1m} T Preferences, access to signature editor denied


CRDSNG {} T Credits, singular form
CRDPLR {s} T Credits, plural form


NOCRSIG {[0;1;31m
!JSorry, you don't have enough credits to change your signature.
This action costs [37m%d[31m credit%s.!)
[0;1m} T Preferences, not enough credits to change signature


SIGCCAN {[0;1;33m
!JYour signature was not changed.!)
[0;1m} T Preferences, signature not changed


LINSNG {} T Lines, singular form
LINPLR {s} T Lines, plural form


SIGLIN {[0;1;33m
!JYour signature was longer than [37m%d[33m line%s. Extra lines were
automatically deleted.!)
[0;1m} T Preferences, signature truncated


SIGOK {[0;1;32m
!JYour signature was installed. You were charged [37m%d[32m credit%s.!)
[0;1m} T signature installed, you have been charged


OPONLY {[0;1;33m
!JSorry, your access level does not permit sending mail to anyone
but [37mthe system operator[33m (Sysop). If you don't want to mail
the [37mSysop[33m now, enter [33mX[37m here.!)
[0;1m} T Write email: can only send email to Sysop


WENCRDS {[0;1;31m
!JYou don't have enough credits to send email. You can [5monly[0;1;31m
mail the system operator (Sysop).!)
[0;1m
!JIf you don't want to mail the Sysop now, please enter [33mX[0;1m now.!)
} T Write email: not enough credits


WEWHO {[0;1m
Enter a user ID or club name to send a message to
([33m?[37m for help) [Enter=Sysop]: [0m} T Write email: get recipient of message


WEWHOC {[0;1m
Enter a user ID or club name to copy the message to
([33m?[37m for help) [Enter=Sysop]: [0m} T Write email: get recipient of copied message


WEUNKID {[0;1;31m
!JSorry, that user ID does not exist.!)
[0;1m} T Write email: unknown user ID


WEHELP1 {[0;1m

!JYou can specify message recipient(s) in the following ways:!)

1. !i!JEnter the user ID of an existing user. You can enter part of the
user ID (at least three letters). The system will do the rest.!)
!0l
2. !i!JPress [33mEnter[37m to send a message to the Sysop.
You will not be charged for this message.!)
!0l
3. !i!JEnter an Internet address (user@@host.domain) to send Internet mail.
This service is charged [32m%d credit%s[37m.!)
!0l
4. !i!JEnter '/' and the name of a Club to send a message to all users in
that Club. You will be charged according to the rules of the recipient club. For
more information, please issue the [33mI[37mnformation command within that club's
main menu.!)
!0l
5. !i!JWrite [33m/Club -User[37m to mail a specific user within the specified
club, or [33m/Club -All[37m to mail all users within that club (just like
option 4 above).!)
!0l
[0;1m} T Write email: help for unprivileged users


WEHELP2 {[0;1m6. !i!JEnter the name of a distribution list to mass-mail copies
of the message to multiple recipients. The following distribution lists are
available to you:!)
!0l
} T Write email: help on distribution lists, footer


WEHELP3 {      !%s
} T Write email: help on distribution lists


WEHELP4 {} T Write email: help on distribution lists, footer


WEFCAU {[0;1m
!WPlease enter a user ID, or [33mALL[37m:!) [0m} T Write email: forward/copy club/user question


WEFCAUR {[0;1;31m
!JThis user ID does not exist. Please try again, or enter [33mX[31m to exit.!)
[0;1m} T Write email: forward/copy club/user error


WERNNET {[0;1;31m
!JSorry, you have no access to this service.!)
[0;1m} T Write email: access to netmail denied


WERNNET2 {[0;1;31m
!JSorry, you don't have enough credits to use this service.!)
[0;1m} T Write email: not enough credits to send netmail


WERLNEC {[0;1;31m
!JSorry, you don't have enough credits to continue distributing
this messsage.!)
[0;1m} T Write email: not enough credits to continue distribution


WERNEC {[0;1;31m
!JSorry, you don't have enough credits to send this message.!)
[0;1m} T Write email: not enough credits to send message


WERCLUB {[0;1;31m
!JSorry, your access level for club [37m%s[31m does not permit
writing messages.!)
[0;1m} T Write email: club message, access denied


MSGSNG {message} T Messages, singular form
MSGPLR {messages} T Messages, plural form


DISTBEG {[0;1;32m
!JCommencing distribution. You can abort the distribution
at any time by pressing [33mEnter[32m.!)
[0;1m} T Write email: beginning of distribution


DISTINFO {[0;1;32m
!JEnd of distribution. You sent [37m%d[32m %s.!)
[0;1m} T Write email: distribution information


WECAN {[0;1;31m
!JDistribution aborted.!)
[0;1m} T Write email: distribution stoppep prematurely


EWRLERR {[0;1;31m
!JUnknown distribution list. Enter [33m?[31m to see the
existing lists.!)
[0;1m} T Write email: unknown distribution list name


WERCPOK {[0;1;32m
!JYour message will be sent to [37m%s[32m.!)
[0;1m} T Write email: confirming recipient of message


WERCPOKN {[0;1;32m
!JYour message will be delivered to the Internet address [37m%s[32m.!)
[0;1m} T Write email: confirming recipient of message, net mail


WERCPOKL {[0;1;32m
!JYour message will be mailed to members of the [37m%s[32m
distribution list.!)
[0;1m} T Write email: confirming recipient of message, dist list


WERCPOKC {[0;1;32m
!JYour message will be sent to Club [37m%s[32m, all users.!)
[0;1m} T Write email: confirming recipient of message, club message


WERCPOKU {[0;1;32m
!JYour message will be sent to Club [37m%s[32m, user [37m%s[32m.!)
[0;1m} T Write email: confirming recipient of message, club message to user


ASKSUBJ {[0;1m
!JSubject (63 characters): !)[0m} T Asking for the subject of a message


CRDSING {} T 'Credits', singular form

CRDPLUR {s} T 'Credits', plural form


WEATT {[0;1m
!WWould you like to attach a file to this message?
(This service costs [32m%d credit%s[37m)
([[33m“[0;1m]es / [[33mN[0;1m]o):!) [0m} T Write email: ask if file attachment required


WERRR {[0;1m
!WWould you like a receipt when this message is read?
(This service is charged [32m%d credit%s[37m)
([[33mY[0;1m]es / [[33mN[0;1m]o):!) [0m} T Write email: ask if return receipt required


WECC {[0;1m
!WWould you like to copy this message to another user?
(This service is charged [32m%d credit%s[37m per copy)
([[33mY[0;1m]es / [[33mN[0;1m]o):!) [0m} T Write email: ask if carbon copies required


WEQNCRD {[0;1;31m
!JSorry, you no longer have enough credits for this service.!)
[0;1m} T Write email: ran out of credits


WECCAN {[0;1;31m
!WAnswering 'yes' will [37mdelete[31m your message. Confirm?!)
[0;1m([[33mY[0;1m]es / [[33mN[0;1m]o): [0m} T Write email: ask for confirmation before exiting


WECCND {} T Write email: default answer string for WECCAN


WERRSEL {[0;1;31m
!WPlease enter [33mY[31m or [33mN[31m.!)
[0;1m} T Write email: invalid answer to question


WEXFERR {[0;1;31m
!JYour file was lost due to an input/output error. Please notify
the Sysop of the event and the conditions that led to the fault.!)
[0;1m} T Write email: I/O error, attachment was lost


WEXFER2 {[0;1;33m
!JYou've sent more than one file. Only the first file will be attached
to the message.!)
[0;1m} T Write email: >1 files uploaded; only first file will be attached


WENOATT {[0;1;33m
!JOkay, the message will stay without an attachment.!)
[0;1m} T Write email: leaving message without an attached file


WEREEFN {[0;1;37m
Current filename: [32m%s[37m

Would you like to change the name of this file?

!JBy answering [33mY[37mes, you can provide a name for this file (e.g. "FILENAME.EXT").
That name will be used during download by the recipient. Otherwise, the current
filename will remain.!)

!WWould you like to change the filename?!)
[0;1m([[33mY[0;1m]es / [[33mN[0;1m]o): [0m} T Write email: change/enter filename?


WEFFN {[0;1m
New filename (15 characters): [0m} T Write email: reenter filename


WEFFNR {[0;1;31m
!JThe filename contains unacceptable characters.
Acceptable characters are letters, numbers and the following symbols:
@ # % ^ ( ) - _ + = [ ] .!)
[0;1m} T Write email: bad characters in filename


WEDFFN {[0;1m
The attached file will be named "[32m%s[37m".
The subject of the message is stil "[32m%s[37m".
[0;1m
} T Write email: displaying filename


WECONFS {[0;1;32m
Confirmed: message [37m%s/%d[32m was stored.
[0;1m
} T Write email: message written to disk


WECONFC {[0;1;32m
!JConfirmed: message [37m%s/%d[32m was copied to [37m%s/%d[32m
and sent to [37m%s[32m.!)
[0;1m
} T Write email: message copied


WEALL {All} T Write email: 'all' string


WECONFL {[0;1;32m!JDistribution: message [37m%d[32m sent to [37m%s[32m.!)
[0;1m} T Write email: message distributed


WELUNKU {[0;1;31m
!JNonexistent user: [37m%s[31m.!)
[0;1m} T Write email: unknown user in distribution list


WENOTFD {[0;1m
!J[32m%s[37m is connected and has been notified.!)
[0;1m
} T Write email: recipient is online and has been notified


WERNOT {[0;1m***

!J[32m%s[37m just sent you a message regarding "[32m%s[37m".
You can read this message by entering the following at the main
menu:!)

([33mE[37m)mail ([33mR[37m)ead ([33mT[37m)o

!JOr enter [33m/GO ERT[37m wherever you are.!)
[0;1m} T Write email: notification for recipient


WERNOTC {[0;1m***

!J[32m%s[37m just copied you a message regarding "[32m%s[37m".
You can read this message by entering the following at the main
menu:!)

([33mE[37m)mail ([33mR[37m)ead ([33mT[37m)o

!JOr enter [33m/GO ERT[37m wherever you are.!)
[0;1m} T Write email: notification for recipient, copied message


WERNOTCC {[0;1m***

!J[32m%s[37m just copied you a message to club [32m%s[37m,
regarding "[32m%s[37m".!)
[0;1m} T Write email: notification for recipient, copied message (to club)


WERNOTFW {[0;1m***
!J[32m%s[37m just forwarded you a message to club [32m%s[37m
regarding "[32m%s[37m".!)
[0;1m} T Clubs: notification for recipient, forwarded message (to club)








RDWHAT {[0;1m
!WWould you like to read messages:!)

[33m’[0;1mo you,
[33mP[0;1mrivate to you only (not in clubs), or
[33mF[0;1mrom you?

!WEnter your choice:!) [0m} T Read mail submenu


RDWHATR {[0;1;31m
!WSorry, that choice is not available.!)
[0;1m} T Read mail, invalid selection


RDASKNO {[0;1m
!JEnter message number to scan from, [[33mF[37m]irst
for the first available message, [[33mL[37m]ast for the last one,
simply press [33mEnter[37m for the current message ([32m#%ld[37m),
or [33m?[0;1m for help.!)

!WWhere do we start scanning from? !) [0m} T Read Mail, asking for message number


RDASKNOR {[0;1;31m
!WSorry, I didn't understand that.!)
[0;1m} T Read mail, error while asking for message number


RDASKH {[0;1m
!JPress [33mEnter[37m to start at the first new message.
If there aren't any new messages, scanning will select the more recent old one.
A dot ([33m.[37m) is equivalent to [33mEnter[37m, and
convenient as a shortcut (e.g. try [33mERT.[37m at the main menu to see
all new messages to you).!)

!JEntering [33mF[37m (First), you will see the earliest available message.!)

!JEnter [33mL[37m (Last), to start with the most recent message available.!)

!JEnter [33mX[37m (eXit) to bail out. Otherwise, enter a message number
to start with. If no message by that number exists, the closest message will
be located.!)
[0;1m} T Read Mail, help for RDASKNO


RDNOMSGT {[0;1;33m
!JSorry, there are no messages for you.!)
[0;1m} T Read mail, no messages to you


RDNOMSGP {[0;1;33m
!JSorry, there are no private messages for you.!)
[0;1m} T Read Mail, no private messages to you


RDNOMSGF {[0;1;33m
!JSorry, there are no stored messages from you.!)
[0;1m} T Read mail, no messages from you


RDTRCLUB {[0;1;32m
!JSearching for club messages [37mto you[32m.!)
[0;1m} T Read mail, looking for matching messages in the clubs


RDMISS {[0;1m
Message [32m%d[37m was not found. Accessing the closest one:
[0;1m} T Read Mail, message number not found


RDSCNM {[0;1m
[[33mN[37m]ext             [[33mP[37m]revious message
[[33mR[37m]ead             [[33m#[37m] jump to a message
[[33mC[37m]lub messages    e[[33mX[37m]it

Your choice ([33m?[37m for help):[0m } T Read Mail, choices while scanning messages


RDSCNMH {[0;1m

!JYour options at this point are as follows:!)

!W[33mN[37mext:     !iJump to the next message without reading this one. You can
use this command as a simple means of scanning messages. Concatenate N multiple times
e.g. [33mNNNNN[37m) and message headers of the next few (five, in this example) messages
will be printed, leaving you at the last one.!)
!0l
!W[33mP[37mrevious: !iJump to the previous message. Works just like the above command.!)
!0l
!W[33m#[37m:        !iEnter a message number after the [33m#[37m and you can jump to that
message, or the closest available one if the desired message isn't available. You can also use
[33m#L[37m (last message) and [33m#F[37m (first message).!)
!0l
!W[33mR[37mead:     !iRead the current message. There will be more message management
options after the message is displayed.!)
!0l
[0;1m} T Read Mail, help about scanning commands


RDSCNR {[0;1;31m
Sorry, this command is not available at this point.
[0;1m} T Read Mail, invalid selection from scan menu


RDDEF {[Enter=[33m%c[37m]: [0m} T Read Mail, default value for menus


RDGOHLP {[0;1m
!JYou can jump to a message by giving its number here. The number need not
belong to an existent message: if a message isn't found, you'll be placed at the
closest available one. Enter [33mF[37m to jump to the first (oldest) available
message, or [33mL[37m to get to the last one. For extra speed, you can
use a concatenated command like [33m#123[37m at the previous menu. This will automatically
jump to message 123.!)
[0;1m} T Read Mail, help on '#' command


RDGONUM {[0;1m
!WEnter a message number to jump to, [33mF[37m for the first
message, [33mL[37m for the last one, [33m?[37m for help, or
[33mX[0;1m to bail out:!)[0m } T Read Mail, goto what message?


RDBEG {[0;1;33m
You've reached the first available message.
[0;1m} T Read Mail, reached beginning of messages


RDEND {[0;1;33m
You've reached the last available message.
[0;1m} T Read Mail, reached end of messages


RDDEL {[0;1;31m
!JSorry, that message was just deleted.!)
[0;1m} T Read Mail, message has just been deleted, can't read


RDIOERR {[0;1;31m
!JThere was an error while reading this message.
Please notify the Sysop about the conditions that
led to this fault.!)
[0;1m} T Read Mail, I/O error while reading message


RDRMNU1 {[0;1m
[[33mN[37m]ext         [[33mP[37m]revious
[[33mE[37m]rase        [[33mC[37m]opy
[[33mF[37m]orward      [[33mR[37m]eply
e[[33mX[37m]it

Your choice ([33m?[37m for help):[0m } T Read Mail, choices after reading message


RDRMNU1H {[0;1m

!JHere's what all those commands do:!)

!W[33mN[37mext:     !iJump to the next message without reading this one. You can
use this command as a simple means of scanning messages. Concatenate N multiple times
e.g. [33mNNNNN[37m) and message headers of the next few (five, in this example) messages
will be printed, leaving you at the last one.!)
!0l
!W[33mP[37mrevious: !iJump to the previous message. Works just like the above command.!)
!0l
!W[33m#[37m:        !iEnter a message number after the [33m#[37m and you can jump to that
message, or the closest available one if the desired message isn't available. You can also use
[33m#L[37m (last message) and [33m#F[37m (first message).!)
!0l
!W[33mE[37mrase:    !iPermanently deletes this message.
You will NOT be asked for confirmation!!)
!0l
!W[33mC[37mopy:     !iCopies the message to another user. For more help on
copying messages, enter [33mC[37m and then [33m?[37m.!)
!0l
!W[33mF[37morward:  !iCopies the message to another user or address, then deletes your own copy.!)
!0l
!W[33mR[37meply:    !iReply to this message.!)
!0l
[0;1m} T Read Mail, help about reading messages, version 1


RDRMNU2 {[0;1m
[[33mN[37m]ext         [[33mP[37m]revious
[[33mE[37m]rase        [[33mC[37m]opy
[[33mF[37m]orward      [[33mR[37m]eply
[[33mB[37m]acktrack    e[[33mX[37m]it

Your choice ([33m?[37m for help):[0m } T Read Mail, menu with backtrack command

                                             
RDRMNU2H {[0;1m

!JHere's what all those commands do:!)

!W[33mN[37mext:      !iJump to the next message without reading this one. You can
use this command as a simple means of scanning messages. Concatenate N multiple times
e.g. [33mNNNNN[37m) and message headers of the next few (five, in this example) messages
will be printed, leaving you at the last one.!)
!0l
!W[33mP[37mrevious:  !iJump to the previous message. Works just like the above command.!)
!0l
!W[33m#[37m:         !iEnter a message number after the [33m#[37m and you can jump to that
message, or the closest available one if the desired message isn't available. You can also use
[33m#L[37m (last message) and [33m#F[37m (first message).!)
!0l
!W[33mE[37mrase:     !iPermanently deletes this message.
You will NOT be asked for confirmation!!)
!0l
!W[33mC[37mopy:      !iCopies the message to another user. For more help on
copying messages, enter [33mC[37m and then [33m?[37m.!)
!0l
!W[33mF[37morward:   !iCopies the message to another user or address, then deletes your own copy.!)
!0l
!W[33mR[37meply:     !iReply to this message.!)
!0l
!W[33mB[37macktrack: !iThis message is a reply to another one. Using the [33mB[37m command
you can view the 'parent' message.!)
!0l
[0;1m} T Read Mail, help about reading messages, version 2


RDRMNU3 {[0;1m
[[33mN[37m]ext          [[33mP[37m]revious
[[33mE[37m]rase         [[33mC[37m]opy
[[33mF[37m]orward       [[33mR[37m]eply
[[33mD[37m]elete user   e[[33mX[37m]it

Your choice ([33m?[37m for help):[0m } T Read Mail, menu with delete user command
                                             

RDRMNU3H {[0;1m

!JHere's what all those commands do:!)

!W[33mN[37mext:        !iJump to the next message without reading this one. You can
use this command as a simple means of scanning messages. Concatenate N multiple times
e.g. [33mNNNNN[37m) and message headers of the next few (five, in this example) messages
will be printed, leaving you at the last one.!)
!0l
!W[33mP[37mrevious:    !iJump to the previous message. Works just like the above command.!)
!0l
!W[33m#[37m:           !iEnter a message number after the [33m#[37m and you can jump to that
message, or the closest available one if the desired message isn't available. You can also use
[33m#L[37m (last message) and [33m#F[37m (first message).!)
!0l
!W[33mE[37mrase:       !iPermanently deletes this message.
You will NOT be asked for confirmation!!)
!0l
!W[33mC[37mopy:        !iCopies the message to another user. For more help on
copying messages, enter [33mC[37m and then [33m?[37m.!)
!0l
!W[33mF[37morward:     !iCopies the message to another user or address, then deletes your own copy.!)
!0l
!W[33mR[37meply:       !iReply to this message.!)
!0l
!W[33mD[37melete user: !iThis message contains the details of a new user
signup. Use this command to delete the user, i.e. to not approve their account for use
on the system. You will NOT be asked for confirmation. The account can be undeleted
using the [33mDELETE[37m command in the sysop menu, provided this is done before the
next cleanup.!)
!0l
[0;1m} T Read Mail, help about reading messages, version 3


RDRMNU4 {[0;1m
[[33mN[37m]ext                  [[33mP[37m]revious
[[33mE[37m]rase                 [[33mC[37m]opy
[[33mF[37m]orward               [[33mR[37m]eply
[[33mS[37m]top autoforwarding   e[[33mX[37m]it

Your choice ([33m?[37m for help):[0m } T Read Mail, menu with stop autofw command
                                             

RDRMNU4H {[0;1m

!JHere's what all those commands do:!)

!W[33mN[37mext:        !iJump to the next message without reading this one. You can
use this command as a simple means of scanning messages. Concatenate N multiple times
e.g. [33mNNNNN[37m) and message headers of the next few (five, in this example) messages
will be printed, leaving you at the last one.!)
!0l
!W[33mP[37mrevious:    !iJump to the previous message. Works just like the above command.!)
!0l
!W[33m#[37m:           !iEnter a message number after the [33m#[37m and you can jump to that
message, or the closest available one if the desired message isn't available. You can also use
[33m#L[37m (last message) and [33m#F[37m (first message).!)
!0l
!W[33mE[37mrase:       !iPermanently deletes this message.
You will NOT be asked for confirmation!!)
!0l
!W[33mC[37mopy:        !iCopies the message to another user. For more help on
copying messages, enter [33mC[37m and then [33m?[37m.!)
!0l
!W[33mF[37morward:     !iCopies the message to another user or address, then deletes your own copy.!)
!0l
!W[33mR[37meply:       !iReply to this message.!)
!0l
!W[33mS[37mtop autofw: !iThis message has been autoforwarded
to your account by another user. All mail to that user will end
up in your mailbox. If this is inconvenient, or has happened without
your consent, you can use this command to cancel the other user's
autoforwarding. Please also notify the Sysop of this, too.!)
!0l
[0;1m} T Read Mail, help about reading messages, version 4


RDMNUR {[0;1;31m
!JSorry, that choice is not available here.!)
[0;1m} T Read Mail, invalid selection from read menu


RDSAR1 {[0;1;31m
!JSorry, this message wasn't autoforwarded to you.!)
[0;1m} T Read Mail, stop autofw, message has not been autofw'ed


RDSAR2 {[0;1;31m
!J[37m%s[31m has been deleted by the Sysop.!)
[0;1m} T Read Mail, stop autofw, user not found


RDSAR3 {[0;1;31m
!JSorry, [37m%s[31m no longer autoforwards mail to you.!)
[0;1m} T Read Mail, stop autofw, user does not forward any more


RDSAI {[0;1m
!JAll mail to [32m%s[37m is currently autoforwarded to you.
Please confirm that you wish to cancel this autoforwarding.!)
[0;1m} T Read Mail, stop autofw, information


RDSAQ {[0;1m
!WCancel that user's autoforwarind to your account?
[[33mY[37m]yes / [[33mN[37m]o)!) [0m} T Read Mail, stop autofw question


RDSAQR {[0;1;31m
!JThis is not a valid option at this point.!)
[0;1m} T Read Mail, stop autofw, invalid response


RDSAC {[0;1;32m
!JAutoforwarding was not terminated.!)
[0;1m} T Read Mail, stop autofw, autoforwarding not stopped


RDSAS {[0;1;32m
!JAutoforwarding was terminated.!)
[0;1m} T Read Mail, stop autofw, autoforwarding stopped


RDMSGHDR {[0m
} T Read Mail, body of message, header


RDMSGFTR {} T Read Mail, body of message, footer


DUERR {[0;1;31m
!JSorry, that user no longer exists.!)
[0;1m} T Delete user, user does not exist


DUDEL {[0;1;31m
!JSorry, that user is marked for deletion. You can undelete them
before the next cleanup, using the DELETE command of the Sysop
menu.!)
[0;1m} T Delete user, user is already marked for deletion


DUOK {[0;1;31m
!JOkay, the user was deleted. You can undelete them
before the next cleanup, using the DELETE command of the Sysop
menu.!)
[0;1m} T Delete user, user deleted


DUXM {[0;1;31m
!JYou can't delete this user.!)
[0;1m} T Delete user, can't delete this user



QMASK {[0;1m
!WQuote the message in your reply?
[[33mY[37m]yes / [[33mN[37m]o):!) [0m} T Quote message question


QMERR {[0;1;31m
!JPlease answer the question with [33mY[31m (yes), ã [33mN[31m
(no), or enter [33mX[31m to cancel your reply.!)
[0;1m} T Quote message, invalid answer


MMINFO {[0;1m
!JThis command allows you to modify a message you've already sent.!)

!JPlease note that, although you can change the contents of an message
routed to the Internet, you're only changing the LOCAL copy of the message.
The message itself has already been delivered and can't be changed.!)
[0;1m} T Modify Message, information


MMASK {[0;1m
!WModify what message? Please enter its number
([33m%d[37m-[33m%d[37m):!) [0m} T Modify Message, question


MMERR1 {[0;1;31m
!JSorry, message [37m%d[31m doesn't exist or wasn't sent by you.!)
[0;1m} T Modify Message, can't use that message number


MMERR2 {[0;1;31m
!JSorry, you can't modify that message.!)
[0;1m} T Modify Message, can't modify this message


MMERR3 {[0;1;31m
!JEnter a number in the range [37m%d[31m-[37m%d[31m.!)
[0;1m} T Modify Message, message number out of bounds


EMERR {[0;1;31m
!JSorry, you can't erase this message.!)
[0;1m} T Erase Message, can't erase this message


EMXMPT {[0;1;31m
!JSorry, this message is exempt from deletion.!)
[0;1m} T Erase Message, can't erase this message



USING {[0;1;31m
!JAnother user is accessing this message. Please try again
later.!)
} T Can't mess with message due to conflicts


MMVT {[0;30;47m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [34mModify message[0;30;47m ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;1;37;47m¿ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  Subject  . . . . . . . . [1;44;37m@63;43;0s[0;1;47;37m  ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  Attachment filename . .  [1;44;37m@16;16;0s[0;1;47;37m                             ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  Return receipt . . . . . [0;30;46m [@"X "t] [1;47;37m                                          ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  Ctrl-R for help                                                         [1;37m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³             [0;1;42;33m@14;"Text"b[0;47;30mÜ    [0;1;42;33m@14;"OK"b[0;47;30mÜ    [0;1;41;33m@14;"€¡¬¨¦"b[0;47;30mÜ  [0;1;47;37m³ [0m
[30;47m ³              ßßßßßßßßßßßßßßßß     ßßßßßßßßßßßßßßßß     ßßßßßßßßßßßßßßßß  [0;1;47;37m³ [0m
[30;47m À[0;1;37;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0m} T Message edit visual template


MMWARN1 {[0;1;33m
!JThis message doesn't have an attachment. There was no reason
to change the attachment filename.!)
[0;1m} T Modify message, warning 1: no attached file, filename not changed


MMWARN2 {[0;1;33m
!JThe filename contains unacceptable characters. I took the liberty of
changing it to "[37m%s[37m". Feel free to modify the message again if this
is not acceptable to you.!)
[0;1m} T Modify message, warning 2: bad characters in filename


MMWARN3 {[0;1;31m
!JYour access level does not allow requesting receipts.!)
[0;1m} T Modify message, warning 3: can't request return receipt


MMWARN4 {[0;1;31m
!JYou don't have enough credits to request a receipt.!)
[0;1m} T Modify message, warning 4: not enough credits for return receipt


MMINFO1 {[0;1;32m
!JA return receipt was requested. You were charged [32m%d credit%s[32m.!)
[0;1m} T Modify message, return receipt requested


MMCAN {[0;1;33m
!JMessage modification aborted.!)
[0;1m} T Modify message, abort message


MMLT {[2J[0;30;47m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [34mModify message[0;30;47m ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;1;37;47m¿ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m1[30m. Subject  . . [34m@63;56;0s[0;1;47;37m ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m2[30m. Attachment filename . . . . . . . . . . . . . . . .  [34m@16;16;0s[0;1;47;37m ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m3[30m. Return receipt . . . . . . . . . . . . . . . . . . . . . . . . .  [34m@"X "t[0;1;47;37m ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m4[30m. Modify message body@1;"4Edit"b                                                 [1;37m  ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m À[0;1;37;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0;1m
} T Modify message, linear template


NEWSUBJ {[0;1m
!WPlease enter the new subject.!)
} T Modify message, new subject


NEWATTN {[0;1m
!WPlease enter the new filename of the attachment. If you leave the name
blank, it will fall back to the default filename, xxx.att, where xxx is the
number of this message. The attachment filename will be ignored if the message
has no attachment.!)
} T Modify message, new filename




RRRSUBJ {Return receipt for message %s/%d} T Return Receipt message subject


RRRBODY {[0;1;36m

ÛÛ  RETURN RECEIPT

%s%s has read message %s/%ld.
You sent that message on %s, %d %s %d, at %s.[0;1m

ÛÛ  This return receipt was created automatically,
    as you requested when you sent the message.

} T Return Receipt message body (no formatting)


SEXMALE {} T Masculine article
SEXFEM {} T Feminine article


RRRGEN {[0;1;36m
!WÛÛ  !iA [37mreturn receipt[36m
was created for this message, as requested by the sender.!)
!0l[0;1m} T Return Receipt generated


RRRINJ {[0;1m***

!J[32m%s[37m just read your message and a
return receipt was created.!)
} T Return Receipt notification for receipt recipient


RRRNOT {[0;1m
!WÛÛ  !i[32m%s[37m is online and has been notified.!)
!0l[0;1m} T Return Receipt notification for receipt sender




ATTNF {[0;1;31m
!JThis message had a file attachment, but the file appears to be missing!
Please let the Sysop know about message [33m%s/%d[31m!
We apologise for the inconveniene and will do whatever is possible to
recover this file.!)
[0;1m} T File Attachment missing


ATTIO {[0;1;31m
!JAn error made downloading this file impossible. Please notify the Sysop
of this event.!)
[0;1m} T Can't link file attachment for downloading


ATTMNT1 {[0;1;32m
!JThis message has a [37m%d byte-long[32m attached file.!)
[0;1m} T File Attachment information, no filename


ATTMNT2 {[0;1;32m
!JThis message has a file attachment named "[37m%s[32m".
The file is [37m%d bytes[32m long.!)
[0;1m} T File Attachment information with filename


ATTDNL {[0;1m
Download the file now? ([[33mY[37m]es / [[33mN[37m]o) } T File Attachment, download question


ATTDEF {[Enter=[33m%c[37m]: [0m} T File Attachment, default answer to ATTDNL


ATTERR {[0;1;31m
!JPlease answer the question with [33mY[31m]es or [[33mN[31m]o.!)
[0;1m} T File Attachment, wrong answer to download question

         
ATTDESC {Message %s/%d attachment} S 49 File Attachment Download description


DNLNCRD {[0;1;31m
!JSorry, you don't have enough credits to download this attachment.!)
[0;1m} T File Attachment download, not enough credits


CPNOAXES {[0;1;31m
!JSorry, you don't have access to this feature.!)
[0;1m} T Copy message, access denied


CPWHO {[0;1m
User ID or Club name to copy to ([33m?[37m for help) [Enter=Sysop]: [0m} T Copy message, ask for recipient


CPERR {[0;1;31m
!JSorry, you can't use distribution lists here.!)
[0;1m} T Copy message, can't use distribution lists here


CPCERR {[0;1;31m
!JSorry, your access level for club [37m%s[31m does not allow
writing messages.!)
[0;1m} T Copy message, no WRITE access to target club


CPCERR2 {[0;1;31m
!JSorry, your access level for club [37m%s[31m does not allow
attaching files to messages. The file attached to this message will
not be copied.!)
[0;1m} T Copy message, no UPLOAD access to target club


CPRCPOK {[0;1;32m
!JThe copy will be sent to [37m%s[32m.!)
[0;1m} T Copy message: confirming recipient of message


CPRCPOKN {[0;1;32m
!JThe copy will be sent to Internet address [37m%s[32m.!)
[0;1m} T Copy message: confirming recipient of message, net mail


CPIO {[0;1;31m
!JInput/output error while copying message. Please notify the
Sysop of this event.!)
[0;1m} T Copy message: I/O error




FWNOAXES {[0;1;31m
!JSorry, you don't have access to this command.!)
[0;1m} T Forward message, access denied


FWWHO {[0;1m
User ID or club to forward message to
([33m?[37m for help) [Enter=Sysop]: [0m} T Forward message, ask for recipient


FWERR {[0;1;31m
!JSorry, you can't use distribution lists at this point.!)
[0;1m} T Forward message, can't use distribution lists here


FWCERR {[0;1;31m
!JSorry, your access level in club [37m%s[31m doesn't allow
writing messages.!)
[0;1m} T Forward message, no WRITE access to target club


FWCERR2 {[0;1;31m
!JSorry, your access level for club [37m%s[31m does not allow
attaching files to messages. The message will not be forwarded so that
the file attachment won't be lost.!)
[0;1m} T Forward message, no UPLOAD access to target club


FWRCPOK {[0;1;32m
!JForwarding to [37m%s[32m.!)
[0;1m} T Forward message: confirming recipient of message


FWRCPOKN {[0;1;32m
!JForwarding to Internet address [37m%s[32m.!)
[0;1m} T Forward message: confirming recipient of message, net mail



FWIO {[0;1;31m
!JInput/output error while forwarding message. Please notify the
Sysop of this event.!)
[0;1m} T Forward message: I/O error


FWCONF {[0;1;31m
!JAnother user is accessing the original message. I can't
delete it, but you can do it yourself later. A copy of the message
was sent to the specified recipient, though.!)
[0;1m} T Forward message: cant' erase due to conflicts


BKERR {[0;1;31m
!JSorry, this message isn't a reply to another.!)
[0;1m} T Backtrack: message is not a reply


DLMNU {[2J[0m[47;1;37m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;30;47m¿ [40m
[47;1;37m ³  [0;47;30mDistribution List Editor  [0;47;30m³ [40m
[47;1;37m ³  [0;47;30mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ  [0;47;30m³ [40m
[47;1;37m ³  [0;31;47mH[30melp                      [30m³ [40m
[47;1;37m ³  [0;31;47mL[30mist addresses            [30m³ [40m
[47;1;37m ³  [0;31;47mA[30mdd address               [30m³ [40m
[47;1;37m ³  [0;31;47mD[30melete address            [30m³ [40m
[47;1;37m ³                            [0;47;30m³ [40m
[47;1;37m ³ [0;30;47me[31mX[30mit                       [30m³ [40m
[47;1;37m À[0;30;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0;1m
[0;1m} T Distribution list, menu


DLMNUS {[0;1m
Distribution list editor
!WEnter your command ([33mH[37m,[33mL[37m,[33mA[37m,[33mD[37m,[33mX[37m to exit, or [33m?[37m for the menu): !)[0m} T Distribution list, short menu


DLSMNU {[2J[0m[47;1;37m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;30;47m¿ [40m
[47;1;37m ³  [0;47;30mDistribution List Editor  [0;47;30m³ [40m
[47;1;37m ³  [0;47;30mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ  [0;47;30m³ [40m
[47;1;37m ³  [0;31;47mH[30melp                      [30m³ [40m
[47;1;37m ³  [0;31;47mL[30mist addresses            [30m³ [40m
[47;1;37m ³  [0;31;47mA[30mdd address               [30m³ [40m
[47;1;37m ³  [0;31;47mD[30melete address            [30m³ [40m
[47;1;37m ³  [0;31;47mP[30mrotect distribution list [30m³ [40m
[47;1;37m ³  [0;31;47mS[30melect distribution list  [30m³ [40m
[47;1;37m ³  [0;31;47mK[30mill current list         [30m³ [40m
[47;1;37m ³                            [0;47;30m³ [40m
[47;1;37m ³ [0;30;47me[31mX[30mit                       [30m³ [40m
[47;1;37m À[0;30;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0;1m
[0;1m} T Distribution list, menu


DLSMNUS {[0;1m
Distribution list editor (current list: [32m!%s[37m)
!WEnter your command ([33mH[37m,[33mL[37m,[33mA[37m,[33mD[37m,[33mP[37m,[33mS[37m,[33mK[37m,[33mX[37m to exit, or [33m?[37m for help): !)[0m} T Distribution list, short menu


DLNOAX {[0;1;31m
Sorry, you don't have access to this command.
[0;1;31m} T Distribution list, access denied


DLERRS {[0;1;31m
!JSorry, this command is not possible.!)
[0;1m} T Distribution List, invalid selection


DLHELP {[0;1m

!JUse this editor to specify up to [32m%d[37m addresses (local
or Internet) to which you'll be able to send mass email distributions. To
send such a mass message, enter '!' as the recipient of the message.!)

!JThe [33mL[37m command lists the current addresses in your distribution
list. [33mA[37m adds addresses. [33mD[37m deletes addresses.!)

!JThe charge for sending a message to a distribution list equals the charge
for writing a message to the first person plus the charge for sending copies
of the message to the rest of the people in the list. You can see the exact
figure using the [33mL[37m command.!)

[0;1m} T Distribution List, help


DLHELPS {[0;1m

!JUse this editor to specify up to [32m%d[37m addresses (local
or Internet) to which you'll be able to send mass email distributions. To
send such a mass message, enter '!name' where 'name' is the name of the
distribution list in question. The table below shows available distribution
lists.!)

!CÚÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
³ [33m!.Sysop   [37m³ [32mSysop's personal distribution list                     [37m³
³ [33m!         [37m³ [32mYour own personal distribution list                    [37m³
³ [33m!mass     [37m³ [32mALL users.                                             [37m³
³ [33m!all      [37m³ [32mLikewise.                                              [37m³
³ [33m!!<class> [37m³ [32mAll users in the speified class (e.g !!DEMO or !!LIVE) [37m³
³ [33m!listname [37m³ [32mA generic list called listname.                        [37m³
ÀÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ!)

!JList names are not case sensitive.!)

!JThe [33mL[37m command lists the current addresses in your distribution
list. [33mA[37m adds addresses. [33mD[37m deletes addresses. Use
[33mP[37m to control who has access to this distribution list. Finally, use
[33mS[37m to load another list into the editor.!)

!JThe charge for sending a message to a distribution list equals the charge
for writing a message to the first person plus the charge for sending copies
of the message to the rest of the people in the list. You can see the exact
figure using the [33mL[37m command.!)

[0;1m} T Distribution List, help for the privileged


DLLISTH {[0;1m

List: [32m!%s[37m
Key:  [32m%d[37m

List members:

[0;1;32m} T Distribution list, address list header


DLLISTL {%3d. %s
} T Distribution list, address list

DLLISTF {[0;1m
Charge per message: [32m%d credit%s[37m
[0;1m} T Distribution list, address list footer


DLAR1 {[0;1;31m
!JSorry, you can't add more than [37m%d[31m
members to this list.!)
[0;1m} T Distribution list, add, too many members


DLANNET {[0;1;31m
!JSorry, your access level does not permit Internet addresses
as members of your distribution list.!)
[0;1m} T Distribution list, add, can't specify net address


DLAUNKID {[0;1;31m
!JThere no user by the name "[37m%s[31m".!)
[0;1m} T Distribution list, add, unknown user


DLADUPL {[0;1;31m
!JThis address is already listed.!)
[0;1m} T Distribution list, add, duplicate address


DLAWHO {[0;1m
!WAddress to add to the list ([33m?[37m for current members):!) [0m} T Distribution list, add, whom?


DLDR1 {[0;1;31m
!JThe list is empty.!)
[0;1m} T Distribution list, delete, list is empty


DLDASK {[0;1m
!WNumber of entry to delete ([33m%d[37m-[33m%d[37m, or [33m?[37m for a
list of current members):!) [0m} T Distribution list, delete, whom?


DLDERR {[0;1;31m
!JPlease enter a number in the range [33m%d[37m-[33m%d[37m.!)
[0;1m} T Distribution list, delete, error



DLPASK {[0;1m
!WPlease enter the key needed to access this list
([33m0[37m no protection, [33m1[37m-[33n128[37m = various keys,
[33m129[37m = user ID "Sysop" only):!) [0m} T Distribution list, set
protection


DLPERR {[0;1;31m
!JPlease enter a number between [37m%d[31m àª [37m%d[31m. Note that
only the user ID [37mSysop[31m can specify key 129.!)
[0;1m} T Distribution list, set protection, error


DLSASK {[0;1m
!WName of the distribution list to load ([33m?[37m for a list):!) [0m} T Distribution list, select list


DLSERR1 {[0;1;31m
!JPlease enter the full name of the list, including the exclamation mark ('!').!)
[0;1m} T Distribution list, select list, bad list name


DLSERR2 {[0;1;31m
!JThat name contains unacceptable characters.!)
[0;1m} T Distribution list, select list, bad characters in name


DLSERR3 {[0;1;31m
!JSorry, you can't modify distribution list "%s".!)
[0;1m} T Distribution list, select list, access denied


DLKASK {[0;1m
!WAre you sure you want to delete this list? [[33mY[37m]yes / [[33mN[37m]o)!) [0m} T Distribution list, kill list?


DLKERR {[0;1;31m
!JPlease enter [33mY[31m or [33mN[31m.!)
[0;1m} T Distritbution list, kill list, error


LSTLSTH {[0;1m

DISTRIBUTION LISTS:
!FÄ
[32m} T List of lists, header


LSTLST {!%s
} T List of lists, table entry


LSTLSTF {[0;1m!FÄ
} T List of lists, footer







MSGHDR1 {
[0;1;32m%s/%d  %s
DATE:    [36m%-38.38s[32m %31.31s
FROM:    [36m%-42.42s [32m%s
TO:      [36m%s%-48.48s [0;1;32m%21.21s
SUBJECT: [36m%-54.54s [32m%15.15s
} T Message header, top part


MSGHDR2 {FILE:    [36m%-52s [32m%17s
} T Message header, optional file attachment part


MSGHDR3 {} T Message header, bottom part


MHFORU {[5m} T Message header, message for you (clubs only)


MHALL {All} T Message header, string for 'All'


MHDAY0 {Sunday} T Message header, string for Sunday
MHDAY1 {Monday} T Message header, string for Monday
MHDAY2 {Tuesday} T Message header, string for Tuesday
MHDAY3 {Wednesday} T Message header, string for Wednesday
MHDAY4 {Thursday} T Message header, string for Thursday
MHDAY5 {Friday} T Message header, string for Friday
MHDAY6 {Saturday} T Message header, string for Saturday


MHJAN {January} T Message header, string for January
MHFEB {February} T Message header, string for February
MHMAR {March} T Message header, string for March
MHAPR {April} T Message header, string for April
MHMAY {May} T Message header, string for May
MHJUN {June} T Message header, string for June
MHJUL {July} T Message header, string for July
MHAUG {August} T Message header, string for August
MHSEP {September} T Message header, string for September
MHOCT {October} T Message header, string for October
MHNOV {November} T Message header, string for November
MHDEC {December} T Message header, string for December

MHPERIOD {Periodic, every %d day%s} T Message header, string for 'periodic'

MHXMPT {Exempt} T Message header, string for 'exempt'

MHRRR {Return receipte requested} T Message header, string for 'return receipt requested'
        
MHTMRD {Read %d time%s} T Message header, string for 'read x times'

MHNREP {%d %s} T Message header, string for 'x replies'

MHNDNL {Downloaded %d time%s} T Message header, string for 'downloaded x times'


TIMSNG {} T 'Times', singular form
TIMPLR {s} T 'Times', plural form

REPSNG {reply} T 'Reply', singular form
REPPLR {replies} T 'Replies', plural form









CLNONTR {[0;1;31m
[JSorry, you don't have access to the Clubs.!)
[0;1m} T User does not have access to the Clubs module


BANNERH {[2J} T Club banner header

BANNERF {} T Club banner footer


CLMNU1 {[2J[0m[47;1;37m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;30;47m¿ [0m
[47;1;37m ³  [0;47;30m     Clubs      [0;47;30m³ [0m
[47;1;37m ³  [0;47;30mÄÄÄÄÄÄÄÄÄÄÄÄÄÄ  [0;47;30m³ [0m
[47;1;37m ³  [0;31;47mH[30melp            [30m³ [0m
[47;1;37m ³  [0;31;47mI[30mnformation     [30m³ [0m
[47;1;37m ³  [0;31;47mL[30mist clubs      [30m³ [0m
[47;1;37m ³  [0;31;47mR[30mead messages   [30m³ [0m
[47;1;37m ³  [0;31;47mW[30mrite message   [30m³ [0m
[47;1;37m ³  [0;31;47mD[30mownload file   [30m³ [0m
[47;1;37m ³  [0;31;47mT[30meleconference  [30m³ [0m
[47;1;37m ³  [0;31;47mB[30mulletins       [30m³ [0m
[47;1;37m ³  [0;31;47mS[30melect club     [30m³ [0m
[47;1;37m ³                  [0;47;30m³ [0m
[47;1;37m ³ [0;30;47me[31mX[30mit             [30m³ [0m
[47;1;37m À[0;30;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0;1m

Clubs
!WCurrent club: [32m@CLUB@: @CLUBDESC@[37m.!)
Enter your choice: [0m} T Club main menu, non-privileged version


SHCLMNU1 {[0;1m
!WCurret club: [32m@CLUB@: @CLUBDESC@[37m.!)
!WEnter your choice
([33mH[37m,[33mI[37m,[33mL[37m,[33mR[37m,[33mW[37m,[33mD[37m,[33mT[37m,[33mB[37m,[33mS[37m,[33mX[37m
to exit, or [33m?[37m for the menu): !)[0m} T Club short menu, non-privileged version


CLMNU2 {[2J[0m[47;1;37m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;30;47m¿ [0m
[47;1;37m ³  [0;47;30m           Clubs             [0;47;30m³ [0m
[47;1;37m ³  [0;47;30mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ  [0;47;30m³ [0m
[47;1;37m ³  [0;31;47mH[30melp                         [30m³ [0m
[47;1;37m ³  [0;31;47mI[30mnformation                  [30m³ [0m
[47;1;37m ³  [0;31;47mL[30mist clubs                   [30m³ [0m
[47;1;37m ³  [0;31;47mR[30mead messages                [30m³ [0m
[47;1;37m ³  [0;31;47mW[30mrite message                [30m³ [0m
[47;1;37m ³  [0;31;47mD[30mownload file                [30m³ [0m
[47;1;37m ³  [0;31;47mT[30meleconference               [30m³ [0m
[47;1;37m ³  [0;31;47mB[30mulletins                    [30m³ [0m
[47;1;37m ³  [0;31;47mA[30mpprove files ([31m%03d[30m waiting)  [30m³ [0m
[47;1;37m ³  [0;31;47mS[30melect club                  [30m³ [0m
[47;1;37m ³                               [0;47;30m³ [0m
[47;1;37m ³ [0;30;47me[31mX[30mit                          [30m³ [0m
[47;1;37m À[0;30;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0;1m

Clubs
!WWelcome to your club, operator: [32m@CLUB@: @CLUBDESC@[37m.!)
Enter your choice: [0m} T Club main menu, co-op version


SHCLMNU2 {[0;1m
!WWelcome to your club, operator: [32m@CLUB@: @CLUBDESC@[37m.!)
!WEnter your choice
([33mH[37m,[33mI[37m,[33mL[37m,[33mR[37m,[33mW[37m,[33mD[37m,[33mT[37m,[33mB[37m,[33mA[37m,[33mS[37m,[33mX[37m
to exit, or [33m?[37m for the menu): !)[0m} T Club short menu, co-op version


CLMNU3 {[2J[0m[47;1;37m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;30;47m¿ [0m
[47;1;37m ³  [0;47;30m           Clubs             [0;47;30m³ [0m
[47;1;37m ³  [0;47;30mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ  [0;47;30m³ [0m
[47;1;37m ³  [0;31;47mH[30melp                         [30m³ [0m
[47;1;37m ³  [0;31;47mI[30mnformation                  [30m³ [0m
[47;1;37m ³  [0;31;47mL[30mist clubs                   [30m³ [0m
[47;1;37m ³  [0;31;47mR[30mead messages                [30m³ [0m
[47;1;37m ³  [0;31;47mW[30mrite message                [30m³ [0m
[47;1;37m ³  [0;31;47mD[30mownload file                [30m³ [0m
[47;1;37m ³  [0;31;47mT[30meleconference               [30m³ [0m
[47;1;37m ³  [0;31;47mB[30mulletins                    [30m³ [0m
[47;1;37m ³  [0;31;47mA[30mpprove files ([31m%03d[30m waiting)  [30m³ [0m
[47;1;37m ³  [0;31;47mO[30mptions                      [30m³ [0m
[47;1;37m ³  [0;31;47mN[30metworking                   [30m³ [0m
[47;1;37m ³  [0;31;47mS[30melect club                  [30m³ [0m
[47;1;37m ³                               [0;47;30m³ [0m
[47;1;37m ³ [0;30;47me[31mX[30mit                          [30m³ [0m
[47;1;37m À[0;30;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0;1m

Clubs
!WWelcome to your club, operator: [32m@CLUB@: @CLUBDESC@[37m.!)
Enter your choice: [0m} T Club main menu, club-op/privileged version


SHCLMNU3 {[0;1m
!WWelcome to your club, operator: [32m@CLUB@: @CLUBDESC@[37m.!)
!WEnter your choice
([33mH[37m,[33mI[37m,[33mL[37m,[33mR[37m,[33mW[37m,[33mU[37m,[33mT[37m,[33mB[37m,[33mA[37m,[33mO[37m,[33mS[37m,[33mX[37m
to exit, or [33m?[37m for the menu): !)[0m} T Club short menu, club-op/privileged version


CLLEAVE {[0;1m
Leaving the Clubs.
} T Exiting from Clubs module


CLABOUT {[0;1m

!JClubs are also known as echoes, special interest groups (SIGs), or
discussion groups. They are repositories for publically contributed
information including public messages, files, articles and bulletins. This
menu gives you access to this information.!)

!JTo get information about the current club, enter the
[33mI[37m(nformation) command. This will list useful information like
charges for posting (if any), et cetera. To select another club, try
[33mS[37(melect). You can see a brief list of clubs using [33mS?[37m, or
a more information-rich listing with [33mL[37m.!)

!JTo read club messages, use the [33mR[37m(ead messages) command, and
follow instructions (there will be more help at that point). To write a
message, use the obvious [33mW[37m(rite) command. If your intention is to
read or write only messages with attached files, use the
[33mD[37m(ownload file) and [33mU[37m(pload file) commands respectively.
They work just like [33mR[37m and [33mW[37m. It's generally better to
use [33mR[37m and [33mW[37m because they're more generic (they DO allow
you to download and upload files, too). Any files you upload may have to be
approved by the Club operators before they're available for download by
other members.!)

!JEach club has its own teleconference channel, with the same topic as the
club itself. You can join the channel to discuss online. Just enter
[33mT[37m(eleconference).!)

!JYou can read this club's articles and bulletins using the
[33mB[37m(ulletins) command. You can't add articles and bulletins
yourself: all you need to do is write a new club message with the article or
bulletin either in the main body or as an plain text attachment. Then notify
the club operator and they will take care of the rest.!)

Access levels:

!JThere are five access levels in clubs:!)

!WZero:     !10iNo access. Can't access any of a club's informaiton.!)
!0l
!WRead:     !10iRead-only access. Can read messages and bulletins, but
not download files or add any information.!)
!0l
!WDownload: !10iDownload access. Can read messages and bulletins and
download files, but not add any information.!)
!0l
!WWrite:    !10iWrite access. Like Download access, but allows writing
messages. Uploading files is not allowed.!)
!0l
!WUpload:   !10iSame as write access, but also allows sending files.!)
!0l
[0;1m} T Clubs, about the module


CLINFO {
[0;36mÛÛ  [1mInformation about club @CLUB@  [46m[K[0;1m

Main operator . . . . . . . . . @CLUBOP@
Created on . . . . . . . . . .  @CLUBCRDATE@, @CLUBCRTIME@
Number of messages  . . . . . . @CLUBMSGS@
Number of files  . . . . . . .  @CLUBFILES@
Bulletins/articles  . . . . . . @CLUBBLTS@
Basic charge . . . . . . . . .  @CHARGE@ credits/minute
Charge for sending messages . . @CLUBPOSTCHG@ credit(s)/message
Charge for uploading a file  .  @CLUBUPLCHG@ credit(s)/file
Charge for downloading files  . @CLUBDNLCHG@ credit(s)/file

[46m[K[0;1m
} T Club information



OPMNU {[2J[0m[47;1;37m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;30;47m¿ [0m
[47;1;37m ³  [0;47;30m                 Club Administration                   [0;47;30m³ [0m
[47;1;37m ³  [0;47;30mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ  [0;47;30m³ [0m
[47;1;37m ³  [0;31;47mH[30melp  . . . . . . . . . . . . . . .  Read this first!  [30m³ [0m
[47;1;37m ³  [0;31;47mN[30mew club . . . . . . . . . . . . .  Create a new club  [30m³ [0m
[47;1;37m ³  [0;31;47mD[30melete club . . . . . . . . . . . . . . Delete a club  [30m³ [0m
[47;1;37m ³  [0;31;47mE[30mdit club  . . . . . . . . . . .  Basic club settings  [30m³ [0m
[47;1;37m ³  [0;31;47mA[30mccess levels . . . . . . . .  Set club access levels  [30m³ [0m
[47;1;37m ³  [0;31;47mM[30modify charges . . . . . . . . . . . Set club charges  [30m³ [0m
[47;1;37m ³  [0;31;47mC[30monfigure user  . . . . .  Set individual user access  [30m³ [0m
[47;1;37m ³                                                         [0;47;30m³ [0m
[47;1;37m ³ [0;30;47me[31mX[30mit . . . . . . . . . . . . . . . . . . Save and Exit  [30m³ [0m
[47;1;37m À[0;30;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0;1m

Current club: [32m@CLUB@: @CLUBDESC@[37m.
[0;1m} T Club operation menu, long version


SHOPMNU {[0;1m
!WEnter your choice
([33mH[37m,[33mN[37m,[33mD[37m,[33mE[37m,[33mA[37m,[33mM[37m,[33mC[37m,[33mX[37m
to exit, or [33m?[37m for the menu): !)[0m} T Club operation menu, short version



OPHELP {[2J[0;1m
!JThis menu is for club operators and sysops. This is what all the commands are
(depending on your access level, some of them may not be available):!)

!JIf you're the system operator (not just a club operator) you can create
new clubs and delete existing clubs using the [33mN[37mew Club and [33mD[37melete
club commands respectively.!)

!JUse the [33mE[37mdit Club command to change a few fundamental
settings for this club, like its description, message expiry and
the club banner/logo. The [33mA[37mccess levels command allows you
to limit access to your club. The [33mM[37modify charges command
sets the cost of the various actions within a club. Finally, [33mC[37monfigure
user is an (inaptly named) command that sets the access level of individual
users. You can ban individuals, or elevate them to privileged levels.!)

[0;1m} T Club operation menu help




ECVT {[0;30;47m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [34mClub Settings[0;30;47m ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;1;37;47m¿ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  Club description . . . . [1;44;37m@63;43;0s[0;1;47;37m  ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  Messages expire in  . .  [1;44;37m@5;0;32767;0n[0;30;47m  days              (0-32767, 0=never)[1;37m  ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  Ctrl-R for help                                                         [1;37m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³             [0;1;42;33m@14;"Banner"b[0;47;30mÜ    [0;1;42;33m@14;"OK"b[0;47;30mÜ    [0;1;41;33m@14;"Cancel"b[0;47;30mÜ  [0;1;47;37m³ [0m
[30;47m ³              ßßßßßßßßßßßßßßßß     ßßßßßßßßßßßßßßßß     ßßßßßßßßßßßßßßßß  [0;1;47;37m³ [0m
[30;47m À[0;1;37;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0m} T Edit club, visual template


ECLT {[2J[0;30;47m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [34mClub Settings[0;30;47m ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;1;37;47m¿ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m1[30m. Club description  . . .  [34m@63;43;0s[0;1;47m  ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m2[30m. Message expiry . . . . . [34m@5;0;32767;0n[30m       (days, 0=never)                  [1;37;47m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m3[30m. Change club banner/logo@1;"3Edit"b                                             [1;37m  ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m À[0;1;37;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0;1m
} T Edit club, linear template


ECFLD1 {[0;1m
!JEnter the new club description.!)
[0;1m} T Edit club, linear template, field 1


ECFLD2 {[0;1m
!JEnter the new message expiry in days. Messages will be deleted
after they've stayed in the system for more than the specified length
of time. Enter a number in the range 0-32767. Enter 0 to disable
message expiry.!)
[0;1m} T Edit club, linear template, field 2


ECCAN {[0;1;31m
!JClub setting were aborted.!)
[0;1m} T Edit club, edit aborted


ECDONE {[0;1;32m
!JClub settings saved.!)
[0;1m} T Edit club, edit successful




AXLVT {[0;30;47m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [34mClub access levels[0;30;47m ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;1;37;47m¿ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  Key needed for READ access to this club  . . . . . . . [1;44;37m@3;0;129;1n[0;47;30m  (0..129)  [1;37m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  Key needed for DOWNLOAD access to this club . . . . .  [1;44;37m@3;0;129;1n[0;47;30m  (0..129)  [1;37m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  Key needed for WRITE access to this club . . . . . . . [1;44;37m@3;0;129;1n[0;47;30m  (0..129)  [1;37m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  Key needed for UPLOAD access to this club . . . . . .  [1;44;37m@3;0;129;1n[0;47;30m  (0..129)  [1;37m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  (Access levels CO-OP and CLUB-OP are only assigned to individuals. Use  [1;37m³ [0m
[30;47m ³  the [1;33mC[0;30;47monfigure user command to give those privileges to trusted users).  [1;37m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  Ctrl-R for help                                                         [1;37m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³                                  [0;1;42;33m@14;"OK"b[0;47;30mÜ    [0;1;41;33m@14;"Cancel"b[0;47;30mÜ  [0;1;47;37m³ [0m
[30;47m ³                                   ßßßßßßßßßßßßßßßß     ßßßßßßßßßßßßßßßß  [0;1;47;37m³ [0m
[30;47m À[0;1;37;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0m} T Club Access levels, visual template


AXLLT {[2J[0;30;47m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [34mClub access levels[0;30;47m ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;1;37;47m¿ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m1[30m. Key needed for READ access to this club  . . . . . . . . . . . . [34m@3;0;129;1n[0;1;47m  ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m2[30m. Key needed for DOWNLOAD access to this club . . . . . . . . . .  [34m@3;0;129;1n[0;1;47m  ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m3[30m. Key needed for WRITE access to this club . . . . . . . . . . . . [34m@3;0;129;1n[0;1;47m  ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m4[30m. Key needed for UPLOAD access to this club . . . . . . . . . . .  [34m@3;0;129;1n[0;1;47m  ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  (Access levels CO-OP and CLUB-OP are only assigned to individuals. Use  [1;37m³ [0m
[30;47m ³  the [1;33mC[0;30;47monfigure user command to give those privileges to trusted users).  [1;37m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m À[0;1;37;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0;1m
} T Club Access levels, linear template


AXLF1 {[0;1m
!JUsers with READ access can enter the club and read its messages,
but can't download files, write messages or upload files.
Enter the key required for READ access to this club.!)
[0;1m} T Club Access levels, linear template field 1


AXLF2 {[0;1m
!JUsers with DOWNLOAD access can enter the club,
read its messages
and download files. They can't write messages or upload files.
Enter the key required for DOWNLOAD access to this club.!)
[0;1m} T Club Access levels, linear template field 2


AXLF3 {[0;1m
!JUsers with WRITE access can enter the club,
read its messages, download files and write messages, but they
can't upload files.
Enter the key required for WRITE access to this club.!)
[0;1m} T Club Access levels, linear template field 3


AXLF4 {[0;1m
!JUsers with UPLOAD have full access to the club: they can
read and write messages and download and upload files.
Enter the key required for WRITE access to this club.!)
[0;1m} T Club Access levels, linear template field 4


WRNDEFC {[0;1;33m
!JThis is the default club. Everyone should have access to at least
read this club. The READ access key was reset to [37m0[33m.!)
[0;1m} T Club Access levels, the default club has to be readable by all







CHVT {[0;30;47m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [34mClub Charges[0;30;47m ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;1;37;47m¿ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  Charge for writing a message . . . . . . . . [1;44;37m@6;-30000;30000;1n[0;47;30m  (-30000..30000)  [1;37m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  Charge for uploading a file . . . . . . . .  [1;44;37m@6;-30000;30000;1n[0;47;30m  (-30000..30000)  [1;37m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  Charge for downloading a file  . . . . . . . [1;44;37m@6;-30000;30000;1n[0;47;30m  (-30000..30000)  [1;37m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  Credit consumption (credits/100 mins) . . .  [1;44;37m@6;-30000;30000;1n[0;47;30m  (-30000..30000)  [1;37m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  (Credit consumption is in credits per 100 minutes. That is, for the     [1;37m³ [0m
[30;47m ³  standard 1 credit/min consumption, you have to specify 100. Enter -1    [1;37m³ [0m
[30;47m ³  for the default Club consumption rate)                                  [1;37m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  Ctrl-R for help                                                         [1;37m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³                                  [0;1;42;33m@14;"OK"b[0;47;30mÜ    [0;1;41;33m@14;"Cancel"b[0;47;30mÜ  [0;1;47;37m³ [0m
[30;47m ³                                   ßßßßßßßßßßßßßßßß     ßßßßßßßßßßßßßßßß  [0;1;47;37m³ [0m
[30;47m À[0;1;37;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0m} T Club charges, visual template


CHLT {[2J[0;30;47m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [34mClub Charges[0;30;47m ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;1;37;47m¿ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m1[30m. Charge for writing a message  . . . . . . . . . . . . . . . . [34m@6;-30000;30000;1n[0;1;47m  ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m2[30m. Charge for uploading a file  . . . . . . . . . . . . . . . .  [34m@6;-30000;30000;1n[0;1;47m  ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m3[30m. Charge for downloading a file . . . . . . . . . . . . . . . . [34m@6;-30000;30000;1n[0;1;47m  ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m4[30m. Credit consumption (credits/100 mins) . . . . . . . . . . . . [34m@6;-30000;30000;1n[0;1;47m  ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  (Credit consumption is in credits per 100 minutes. That is, for the     [1;37m³ [0m
[30;47m ³  standard 1 credit/min consumption, you have to specify 100. Enter -1    [1;37m³ [0m
[30;47m ³  for the default Club consumption rate)                                  [1;37m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m À[0;1;37;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0;1m
} T Club charges, linear template


CHLTF1 {[0;1m
!JHow many credits do we charge users for writing messages?!)
[0;1m} T Club charges, linear template, field 1


CHLTF2 {[0;1m
!JHow many credits do we charge users for uploading files? Please remember that users are
also charged for writing a message, since files are always attached to messages.!)
[0;1m} T Club charges, linear template, field 2


CHLTF3 {[0;1m
!JHow many credits do we charge users for reading messages?!)
[0;1m} T Club charges, linear template, field 3


CHLTF4 {[0;1m
!JEach club can have its own, individual charging scheme,
complete with its own credit consumption rate. Please specify
how many credits users are charged per 100 minutes they spend
in the club. If you want a one-credit-per-minute charge, enter
100 here (100 credits/100 mins = 1 credit/min). For the default
charge, enter -1.!)
[0;1m} T Club charges, linear template, field 4






CUASK {[0;1m
!WEnter user ID for which to change access:!)[0m } T Configure user access, which user?


CUERR1 {[0;1;31m
!WSorry, that user does not exist.!)
[0;1m} T Configure user access, unknown user


CUERR2 {[0;1;31m
!WWhoa, hold on, I'm not changing Sysop's access level! Sysop
always has full access everywhere!!)
[0;1m} T Configure user access, can't modify Sysop


CUHLP {[0;1m

These are the available levels:

Default    !i!WAny special individual access level si removed and
the user falls back to the default access level, as defined by the
user's keys and the settings of the [33mM[37m command.!)
!0l
Zero       !i!WThe club is invisible and inaccessible to this user.!)
!0l
Read       !i!WThe user can only read messages.!)
!0l
Download   !i!WAs READ, but can also download files.!)
!0l
Write      !i!WAs DOWNLOAD, but can also write messages.!)
!0l
Upload     !i!WAs WRITE, but can also upload files.!)
!0l
Co-op      !i!WThe user is one of the operators of the club.
User has UPLOAD access. Any uploaded files are automatically
approved for download. User can also approve files, and otherwise
administer the club.!)
!0l
Club-op    !i!WOnly one user may have this level at any one time.
The Club-op is the main operator of the club. This level affords the
same privileges as the one above, plus the ability to change club
access levels. If you assign this access level to a user, the current
club-op is automatically demoted. Only system operators can assign this
access leve.!)
!0l
} T Configure user access, help on access levels


CUCUR {[0;1;32m
!WUser [37m%s[32m currently has [37m%s[32m access.!)
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
!JFor your information: this user has system operator privileges
throughout the Clubs. Any access level you set for them will be
ignored. If the user ever loses their operator privilege, the access
level you're about to set will take effect.!)
[0;1m} T Configure user access, warning about privileged user


CUMNU {[0;1m
Enter the user's new access level:
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
!WEnter your selection ([33mD[37m,[33m0[37m-[33m6[37m,[33mX[37m to exit, or [33m?[37m for help):!) [0m} T Configure user access, short level menu


CUMNUR {[0;1;31m
!WSorry this is not a possible access level. Enter [33m?[31m for help.!)
[0;1m} T Configure user access, invalid selection


CUMNUR1 {[0;1;31m
!WSorry, only the system operators can set club operators.
Enter [33m?[31m for help.!)
[0;1m} T Configure user access, only privileged users can set club-ops


CUMNUR2 {[0;1;31m
!WSorry, only the main operator of a club (Club-op) or a system
operator can assign this access level. Enter [33m?[31m for help.!)
[0;1m} T Configure user access, only club-ops can set co-club-ops


CUMNUR3 {[0;1;33m
!JYou can't ban users from the default club.!)
[0;1m} T Configure user access, the default club has to be readable by all



CUCHG {[0;1m
!WSuccessfully set access level for user [32m%s[37m in @CLUB@.!)
[0;1m} T Configure user access, user level set successfully


CUDIS {[0;1m
!W[32m%s[37m has lost operator privileges for this @CLUB@.!)
[0;1m} T Configure user access, current club operator lost their place


CUCNOT {[0;1;35m***
!JAn operator has just given you
operator access for [37m%s[35m Club.
Congratulations!!)
[0;1m} T Configure user access, notify new co-op/club-op





CRCASK {[0;1m
!WWhat's the name of the new club ([33m?[37m for a list of existing clubs)?!)[0m } T Create club, ask name


CRERR {[0;1;31m
!JSorry, that name is unacceptable. Club names have to
be at most 15 characters long, and contain only alphanumeric
characters and the following: # % ^ ( ) - _ + = [ ] .!)
[0;1m} T Create club, malformed club name


CRCXST {[0;1;31m
!JErm, that club already exists! You must be new here. :-)!)
[0;1m} T Create club, club already exists


CRCCNF {[0;1m
!JRight, Club "%s" created. You should use
the [33mE[37m, [33mA[37m and [33mM[37m
commands to set it up before allowing users to see it.!)
[0;1m} T Create club, confirm creation




DCASK {[0;1m
!JRead the following questions carefully. You will
be offered a confirmation question before the club is
deleted. Deleting a club permanently removes all information
stored within it, including its messages, files, bulletins,
and articles.!J

!WWhat poor club is your next victim, oh mighty Club Slayer? ([33m?[37m for a list):!)[0m } T Delete Club, what club?


DCUNK {[0;1;31m
!JThere's no such club!!)
[0;1m} T Delete Club, unknown club


DCERR1 {[0;1;31m
!JThere are users in that club right now. We can't
delete the club before they leave.!)
} T Delete Club, Club is in use


DCERR2 {[0;1;31m
!JYou're trying to delete the default club.
The system depends on it being there. Reconfigure
the clubs module to use another default club and
try again.!)
} T Delete Club, can't delete default club


DCINFO {[0;1;32m
Club name  . . . . . .  [37m@CLUB@[32m
Description . . . . . . [37m@CLUBDESC@[32m
Operator . . . . . . .  [37m@CLUBOP@[32m
Messages  . . . . . . . [37m@CLUBMSGS@[32m
Files  . . . . . . . .  [37m@CLUBFILES@[32m
Bulletins/Articles  . . [37m@CLUBBLTS@[32m
[0;1m} T Delete Club, club information


DCCONF {[0;1;31m
!W[5mÛÛ[0;1;31m  WARNING: !iAnswering YES to the following
question will cause the system to delete:!)
!W- The Club itself!)
!W- All its messages, files and bulletins/articles!)
!W- All directories used by the club!)
!0l[0;1m
!WDo you really want to do this? [[33mY[37m]yes / [[33mN[37m]o);!)[0m } T Delete Club, ask for confirmation


DCCR {[0;1;31m
!JPlease answer the question with [33mY[31m or [33mN[31m.!)
[0;1m} T Delete Club, invalid answer


DCSNUK {[0;1;31m
!JWhoops, a user just entered the club while you were being
asked forconfirmation. Please try again.!)
[0;1m} T Delete Club, someone just entered the Club


DCWAIT {[0;1;32;5m
Please way, club slaughter in progress...[30m[K} T Delete Club, please wait


DCOK {[0;1;32m


Done, club and directories deleted.
[0;1m} T Delete Club, club deleted





LCHDR {[0;1m
[33mClub            Operator   Description[37m
ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
[0m} T Short club list, header


LCTAB {%-15s %-10s %-50.50s
} T Short club list, table line


LCFTR {[0;1mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ

} T Short club list, footer


LC2HDR {[0;1m
       ÚÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄ¿
ÚÄÄÄÄÄÄ³ [33mMessages[37m ³ [33mFiles[37m ³ [33mBulletins[37m ³ [33mCreated[37m ³ÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
³      ÀÄÄÄÄÄÄÄÄ¿ ÀÄÄ¿    ³    ÚÄÄÄÄÄÄÙ  ÚÄÄÄÄÄÄÙ    ³                       ³
³ [33mClub[37m          ³    ³    ³    ³         ³ [33mOperator [37m ³ [33mDescription[37m           ³
ÃÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÅÄÄÄÄÅÄÄÄÄÅÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ´
[0;1m} T Long club list, header


LC2TAB {³[0m%-15s[1m³[0m%4d[1m³[0m%4d[1m³[0m%4d[1m³[0m%-9s[1m³[0m%-11s[1m³[0m%-23.23s[1m³
} T Long club list, table line


LC2FTR {[0;1mÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÁÄÄÄÄÁÄÄÄÄÁÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ

} T Long club list, footer



SCASK {[0;1m
!WWhat club do we go to? Enter [33m?[37m for a list:!)[0m } T Select new club, what club?


SCERR {[0;1;31m
!JSorry, this club does not exist.!)
[0;1m} T Select new club, club does not exist


SCADD {[0;1;32m
!JClub [37m%s[32m was added to your quickscan list.!)
[0;1m} T Select new club, the club was added to your quickscan configuration







NETMNU {[2J[0m[47;1;37m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;30;47m¿ [0m
[47;1;37m ³  [0;47;30m Networked Clubs    [0;47;30m³ [0m
[47;1;37m ³  [0;47;30mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ  [0;47;30m³ [0m
[47;1;37m ³  [0;31;47mH[30melp                [30m³ [0m
[47;1;37m ³  [0;31;47mD[30mefine import BBSs  [30m³ [0m
[47;1;37m ³  [0;31;47mI[30mmport clubs        [30m³ [0m
[47;1;37m ³  [0;31;47mE[30mxport clubs        [30m³ [0m
[47;1;37m ³  [0;31;47mS[30mtatus              [30m³ [0m
[47;1;37m ³                      [0;47;30m³ [0m
[47;1;37m ³ [0;30;47me[31mX[30mit                 [30m³ [0m
[47;1;37m À[0;30;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0;1m

[0;1m} T Networking menu, long version


SHNETMNU {[0;1m
!WYour choice
([33mH[37m,[33mD[37m,[33mI[37m,[33mE[37m,[33mC[37m,[33mS[37m,[33mX[37m
to exit, or [33m?[37m for the menu): !)[0m} T Networking menu, short version



NETHELP {[0;1m
!JClub messages may be distributed over a network. This includes both
importing messages from other systems and exporting messages to them.!)

!JTo import messages you need to use the [33mD[37m (Define import BBSs)
command to define systems from which messages will be imported, as well as
the desired frequency of message imports.!)

!JOnce this is done, you can configure the import rule table. The table has
two columns: the remote club from which we'll be importin messages, and the
local club where messages are to be stored. Local clubs are denoted in the
usual notation (e.g. [32m/Club[37m). Remote clubs are different. For
instance:!)

!C[32mhost.domain.tld/BBSNAME/Club[37m!)

!JThe first part is the fully qualified domain name 


---- THE UNDERLYING NETWORKING CODE IS UNDERGOING MASSIVE CHANGES.
     THIS NEEDS TO BE REVIEWED, SO I'LL LEAVE IT UNTRANSLATED FOR NOW -----

’¦ §¨é«¦ £â¨¦ª œå¤˜   §¢ã¨ª Internet › œçŸ¬¤© «¦¬ £®˜¤ã£˜«¦ª §¦¬
­ ¢¦¥œ¤œå «¤ ™á©. €¡¦¢¦¬Ÿœå ¦ ¡à› ¡æª › ¡«çà©ª «ª ™á©ª (BBSNAME) ¡˜ 
«â¢¦ª «¦ æ¤¦£˜ «¦¬ club. ¨ ¤ §¨¦©Ÿâ©œ«œ œ ©˜šæ£œ¤˜ clubs ˜§æ £å˜ á¢¢ ™á©,
§¨â§œ  ¤˜ â®œ«œ ›¢é©œ  «¦ æ¤¦£˜ (host.domain.tld/BBSNAME) «¦¬ ˜§¦£˜¡¨¬©£â¤¦¬
©¬©«ã£˜«¦ª £œ «¤ œ¤«¦¢ã [33mD[37m (§˜¨˜§á¤à).!)

!J‚ ˜ ¤˜ œ¥áš¦¬£œ clubs ©œ á¢¢œª ™á©œ ª, ˜¨¡œå ¤˜ ®¨© £¦§¦ ã©¦¬£œ «¤ œ¤«¦¢ã
[33mE[37mxport clubs š ˜ ¤˜ ¦¨å©¦¬£œ §¦ ˜ ˜§æ «˜ clubs
£˜ª œå¤˜  «¦§ ¡á ¡˜  §¦ ˜ æ® .!)

!J’â¢¦ª, £œ «¤ œ¤«¦¢ã [33mS[37mtatus £§¦¨¦ç£œ ¤˜ ›¦ç£œ §¦ ˜ clubs œ ©áš¦¬¤
£¤ç£˜«˜ ˜§æ §¦ ˜ ©¬©«ã£˜«˜.!)
[0;1m} T Network menu help




DIPMNU {[0;1m
!W‡â¢œ«œ ¤˜ §¨¦©Ÿâ©œ«œ ([[33mA[37m]dd), ¤˜ £œ«˜™á¢¢œ«œ
([[33mM[37m]odify), ã ¤˜ › ˜š¨á¯œ«œ ([[33mD[37m]elete) â¤˜ ©ç©«£˜; ƒé©«œ
[33mA[37m, [33mM[37m, [33mD[37m, [33mX[37m š ˜ â¥¦›¦ ã [33m?[37m š ˜
¡˜«á¢¦š¦ ¬§˜¨®æ¤«à¤ ©¬©«£á«à¤:!)[0m } T Networking, operations on import points


DIPADD {[0;1m
!Jƒé©«œ «¦ æ¤¦£˜ «¦¬ ©¬©«ã£˜«¦ª §¦¬ Ÿâ¢œ«œ ¤˜ §¨¦©Ÿâ©œ«œ, ©« £¦¨­ã
[32mhost.domain.tld/BBSCODE[37m. ‰œ­˜¢˜å˜ ¡˜  £ ¡¨á
›œ¤ › ˜­â¨¦¬¤. ‹§¦¨œå«œ ¤˜ ®¨© £¦§¦ ã©œ«œ «¤
˜¨ Ÿ£« ¡ã IP › œçŸ¬¤© «¦¬ ©¬©«ã£˜«¦ª ˜¤ Ÿâ¢œ«œ. €¢¢ éª, §¨â§œ  ¤˜ ›é©œ«œ «¤
§¢ã¨ › œçŸ¬¤© «¦¬ ˜§¦£˜¡¨¬©£â¤¦¬ ©¬©«ã£˜«¦ª. ’¦ æ¤¦£˜ ›œ¤ œ¢âš®œ«˜  ˜§æ «¦
©ç©«£˜: §¨¦©¦®ã ©«˜ ¢áŸ!!)

!W¤¦£˜ ¤â¦¬ ©¬©«ã£˜«¦ª ˜§'æ§¦¬ Ÿ˜ œ ©áš¦¬£œ £¤ç£˜«˜:!)[0m } T Networking, add import point


DIPADR {[0;1;31m
!J† › œçŸ¬¤© «¦¬ ©¬©«ã£˜«¦ª ›œ¤ ›œå®¤œ  ©à©«ã. ¨â§œ  ¤˜ œå¤˜  ©«
£¦¨­ã [37mhost.domain.tld/BBSCODE[31m ã, ˜¤ ›œ¤ š¤à¨åœ«œ «¦ ˜¢­˜™« ¡æ
æ¤¦£˜ «¦¬ ©¬©«ã£˜«¦ª, [37mwww.xxx.yyy.zzz/BBSCODE[31m.!)
[0;1m} T Networking, incorrect remote BBS address


DIPADX {[0;1;31m
!J’¦ ©ç©«£˜ [37m%s[31m â®œ  ã› ›¢àŸœå.[31m!)
[0;1m} T Networking, system name already exists


DIPADT {[0;1m
!J’é¨˜ §¨â§œ  ¤˜ ¦¨å©œ«œ ¡áŸœ §æ«œ Ÿ˜ œ ©áš¦¬£œ £¤ç£˜«˜ ˜§æ «¦ §˜¨˜§á¤à
©ç©«£˜. ƒé©«œ â¤˜¤ ˜¨ Ÿ£æ £œ¨é¤ £œš˜¢ç«œ¨¦ «¦¬ £›â¤, ã â¤˜¤ ˜¨ Ÿ£æ
˜¡¦¢¦¬Ÿ¦ç£œ¤¦ ˜§æ «¦ œ§åŸœ£˜ [33mm[37m (minutes, ¢œ§«á) ã [33mh[37m
(hours, é¨œª). „§å §˜¨˜›œåš£˜« , ›å¤¦¤«˜ª ˜§¢á "1" ¦¨å¦¬£œ æ«   œ ©˜šàšã Ÿ˜
œ§ ®œ ¨œå«˜  ˜¤á £å˜ £â¨˜. ƒå¤¦¤«˜ª "15m", ˜¬«æ Ÿ˜ šå¤œ«˜  ˜¤á 15 ¢œ§«á.!)

!W„¢á® ©«¦ ®¨¦¤ ¡æ › á©«£˜ £œ«˜¥ç œ¤£œ¨é©œà¤:!)[0m } T Networking, asking for time between updates

DIPADTR {[0;1;31m
!J‘¬šš¤é£, ›œ¤ ˜¤˜š¤à¨å©˜£œ «¦ œ§åŸœ£˜ §¦¬ ®¨© £¦§¦ ã©˜«œ.!)
[0;1m} T Networking, time specification suffix was invalid


DIPADDOK {[0;1;32m
!J‰˜¢éª, «¦ ©ç©«£˜ [37m%s[32m ›¢éŸ¡œ œ§ «¬®éª. ‹¤ç£˜«˜ Ÿ˜ œ ©áš¦¤«˜ 
¡áŸœ [37m%d[32m ›œ¬«œ¨æ¢œ§«˜.!)
[0;1m} T Networking, system added




DIPDEL {[0;1m
!Jƒé©«œ «¦ æ¤¦£˜ «¦¬ ©¬©«ã£˜«¦ª §¦¬ Ÿâ¢œ«œ ¤˜ › ˜š¨á¯œ«œ, ã [33m?[37m š ˜
¡˜«á¢¦š¦ ©¬©«£á«à¤:!) [0m} T Networking, delete import point


DIPDELX {[0;1;31m
!J€¬«æ «¦ ©ç©«£˜ ›œ¤ â®œ  ›¢àŸœå.!)
[0;1m} T Networking, delete import point, system doesn't exist


DIPDELOK {[0;1;32m
!J„¤«á¥œ , «¦ ©ç©«£˜ [37m%s[32m › œš¨á­.!)
[0;1m} T Networking, system deleted



DIPMOD {[0;1m
!Jƒé©«œ «¦ æ¤¦£˜ «¦¬ ©¬©«ã£˜«¦ª §¦¬ Ÿâ¢œ«œ ¤˜ £œ«˜™á¢œ«œ, ã [33m?[37m š ˜
¡˜«á¢¦š¦ ©¬©«£á«à¤:!) [0m} T Networking, modify import point


DIPMODX {[0;1;31m
!J€¬«æ «¦ ©ç©«£˜ ›œ¤ â®œ  ›¢àŸœå.!)
[0;1m} T Networking, modify import point, system doesn't exist.


DIPMODT {[0;1;32m
!J„ ©áš¦¬£œ £¤ç£˜«˜ ˜§æ «¦ ©ç©«£˜ [37m%s[32m ¡áŸœ [37m%d[32m £â¨œª,
[37m%d[32m é¨œª ¡˜  [37m%d[32m ¢œ§«á.!)
[0;1m} T Networking, modify import point, show refresh time


DIPMODA {[0;1m
!J€¤ Ÿâ¢œ«œ ¤'˜¢¢á¥œ«œ «¦ §˜¨˜§á¤à, ›é©«œ â¤˜¤ ˜¨ Ÿ£æ £œ¨é¤ £œš˜¢ç«œ¨¦ «¦¬
£›â¤, ã â¤˜¤ ˜¨ Ÿ£æ ˜¡¦¢¦¬Ÿ¦ç£œ¤¦ ˜§æ «¦ œ§åŸœ£˜ [33mm[37m (minutes, ¢œ§«á)
ã [33mh[37m (hours, é¨œª). „§å §˜¨˜›œåš£˜« , ›å¤¦¤«˜ª ˜§¢á "1" ¦¨å¦¬£œ æ« 
 œ ©˜šàšã Ÿ˜ œ§ ®œ ¨œå«˜  ˜¤á £å˜ £â¨˜. ƒå¤¦¤«˜ª "15m", ˜¬«æ Ÿ˜ šå¤œ«˜  ˜¤á
15 ¢œ§«á.!)

!W„¢á® ©«¦ ®¨¦¤ ¡æ › á©«£˜ £œ«˜¥ç œ¤£œ¨é©œà¤: [[33mEnter[37m=æ®  ˜¢¢˜šã]!)[0m } T Networking, asking for new time between updates


DIPMODOK {[0;1;32m
!J„¤«á¥œ ,  ¡˜«˜®é¨© «¦¬ ©¬©«ã£˜«¦ª [[37m%s[[32m £œ«˜™¢ãŸ¡œ.!)
[0;1m} T Networking, system updated






IMPCLUB {[0;1m
!J˜¨˜¡˜¢é ›é©«œ «¦ æ¤¦£˜ «¦¬ ˜§¦£˜¡¨¬©£â¤¦¬ club ˜§æ «¦ ¦§¦å¦ Ÿ˜ œ ©áš¦¬£œ
£¤ç£˜«˜. † ©ç¤«˜¥ «¦¬ ˜§¦£˜¡¨¬©£â¤¦¬ club œå¤˜ 
[32mhost.domain.tld/BBSCODE/Club[37m. ¨¦©¦®ã: §â¨˜¤ «¦¬ ©¬¤«˜¤« ¡¦ç
œ¢âš®¦¬,  ¦¨Ÿæ««˜ «¦¬ ˜§¦£˜¡¨¬©£â¤¦¬ club ›œ¤ £§¦¨œå ¤˜ œ¢œš®Ÿœå! ¤¦£˜
˜§¦£˜¡¨¬©£â¤¦¬ club: !)[0m } T Networking, asking for name of remote club


IMPCLBR {[0;1;31m
!J’¦ æ¤¦£˜ «¦¬ ˜§¦£˜¡¨¬©£â¤¦¬ club ›œ¤ œå¤˜  ©¬¤«˜¡« ¡á ©à©«æ!!)
[0;1m} T Networking, invalid remote club path


IMPCLBS {[0;1;31m
!J’¦ æ¤¦£˜ «¦¬ ˜§¦£˜¡¨¬©£â¤¦¬ ©¬©«ã£˜«¦ª ›œ¤ â®œ  ›¢àŸœå ˜¡æ£˜!
•¨© £¦§¦ ã©«œ «¤ œ¤«¦¢ã [33mD[31m š ˜ ¤˜ «¦ §¨¦©Ÿâ©œ«œ.!)
[0;1m} T Networking, system name hasn't been declared


IMPLOCC {[0;1m
!J‘œ §¦ ¦ «¦§ ¡æ club ¤˜ œ¤˜§¦Ÿâ©¦¬£œ «˜ œ ©˜šæ£œ¤˜ £¤ç£˜«˜; ƒé©«œ
[33m?[37m š ˜ ¡˜«á¢¦š¦, ã [33m-[37m š ˜ ¤˜ ˜¡¬¨é©œ«œ «¤ œ ©˜šàšã
«¦¬ ˜§¦£˜¡¨¬©£â¤¦¬ club:!)[0m } T Networking, asking for name of local club


IMPLOCR {[0;1;31m
!Jƒœ¤ ¬§á¨®œ  ˜¬«æ «¦ «¦§ ¡æ Club... ƒ¦¡ £á©«œ [33m?[31m š ˜ ¤˜ ›œå«œ
«¦¤ ¡˜«á¢¦š¦ «à¤ clubs «ª ™á©ª.!)
[0;1m} T Networking, unknown local club


IMPOK {[0;1;32m
!J„¤«á¥œ , «˜ £¤ç£˜«˜ «¦¬ ˜§¦£˜¡¨¬©£â¤¦¬ club [37m%s[32m Ÿ˜ œ ©áš¦¤«˜  ©«¦
«¦§ ¡æ club [37m%s[32m.!)
[0;1m} T Networking, added import entry

IMPDISP {[0;1;33m
!J’˜ £¤ç£˜«˜ «¦¬ ˜§¦£˜¡¨¬©£â¤¦¬ club [37m%s[33m Ÿ˜ œ ©áš¦¤«˜  ©«¦
«¦§ ¡æ club [37m%s[33m. ‘£œåà©: ¦¨å¦¤«˜ª ˜¬«ã «¤ ˜¤« ©«¦ ®å˜,
¡˜«˜¨šã©˜£œ «¤ §¨¦è§á¨®¦¬©˜, §¦¬ œ¤˜§æŸœ«œ «˜ £¤ç£˜«˜ ©«¦ «¦§ ¡æ club
[37m%s[33m.!)
[0;1m} T Networking, added import entry, displaced previous one






DIPLSTH {[0;1;32m
                                             „ ©˜šàšã ¡áŸœ:
€§¦£˜¡¨¬©£â¤¦ ©ç©«£˜                     †£â¨œª  —¨œª  Šœ§«á  „ ©˜šæ£œ¤˜ clubs
!FÄ
} T Networking, remote system list header


DIPLSTL {[0;1m%-40.40s    %2s     %2s     %2s        %4d
} T Networking, remote system list item


DIPLSTF {[0;1;32m!FÄ
[0;1m} T Networking, remote system list footer




EXPLSTH {[0;1m
’¦§ ¡æ club      ’¦§ ¡æ/[32m„§ «¨â§¦¬£œ[37m/[31m€§˜š¦¨œç¦¬£œ[37m
!FÄ
} T Networking, list of exported clubs, header


EXPLSTL {[0;1m%-15.15s  !W!i} T Networking, list of exported clubs, entry part 1

EXPLSTL2 {’¦§ ¡æ Club!)
!0l} T Networking, list of exported clubs, local club

EXPLSTL3 {€¤¦ ¡«æ š ˜ æ¢˜ «˜ ©¬©«ã£˜«˜!)
!0l} T Networking, list of exported clubs, open to all

EXPLSTL4 {[0;1;32m%s } T Networking, list of exported clubs, ALLOW string

EXPLSTL5 {[0;1;31m%s } T Networking, list of exported clubs, DENY string

EXPLSTL6 {!)
!0l} T Networking, list of exported clubs, ALLOW/DENY end of line


EXPLSTF {[0;1m!FÄ
[0;1m} T Networking, list of exported clubs, footer



EXPASK {[0;1m
!Jƒé©«œ «¦ æ¤¦£˜ «¦¬ «¦§ ¡¦ç club «¦¬ ¦§¦å¦¬ «¤ ¡˜«á©«˜© Ÿâ¢œ«œ ¤˜
˜¢¢á¥œ«œ, ã [33mALL[37m š ˜ æ¢˜ «˜ clubs, ã [33m?[37m š ˜ ¡˜«á¢¦š¦:!) [0m} T  Networking, export status change, ask for club name


EXPCLBR {[0;1;31m
!J‘¬šš¤é£, ›œ¤ ¬§á¨®œ  ˜¬«æ «¦ club. ƒé©«œ [33m?[31m š ˜ ¡˜«á¢¦š¦.!)
[0;1m} T Networking, export status change, unknown club


EXPSPEC {[0;1m
!J’é¨˜ §¨â§œ  ¤˜ ¦¨å©œ«œ « ª §¨¦©™á©œ ª ¥â¤à¤ ©¬©«£á«à¤ ©'˜¬«æ «¦ club.
‹§¦¨œå«œ ¤˜ ›é©œ«œ [33m-[37m š ˜ ¤˜ ˜§˜š¦¨œç©œ«œ ©œ æ¢¦¬ª «¤ §¨æ©™˜©
(«¦§ ¡æ club), [33m+[37m š ˜ ¤˜ œ§ «¨â¯œ«œ «¤ œ¥˜šàšã «¦¬ club ©œ æ¢˜ «˜
©¬©«ã£˜«˜. ‹§¦¨œå«œ œ§å©ª ¤˜ ›é©œ«œ £å˜ ¢å©«˜ ©¬©«£á«à¤ (§® host.domain.tld
ã host.domain.tld/BBSCODE) ®à¨ ©£â¤à¤ £œ › ˜©«ã£˜«˜. † §¨æ©™˜© Ÿ˜ œ§ «¨â§œ«˜ 
£æ¤¦ ©'˜¬«á «˜ ©¬©«ã£˜«˜. €¤ ¦ §¨é«¦ª ®˜¨˜¡«ã¨˜ª «ª ¢å©«˜ª œå¤˜  "-", «æ«œ 
§¨æ©™˜© Ÿ˜ œ§ «¨â§œ«˜  ©œ æ¢¦¬ª „‰’‘ ˜§æ «˜ ©¬©«ã£˜«˜ §¦¬ Ÿ˜ ˜¤˜­â¨œ«œ.!)

!Wƒé©«œ «¤ ¢å©«˜ §¨æ©™˜©ª š ˜ «¦ §˜¨˜§á¤à club, ã [33m?[37m š ˜ ¡˜«á¢¦š¦
«à¤ clubs ¡˜  «à¤ §¨¦©™á©œé¤ «¦¬ª:!) [0m} T Networking, asking for export access list



NETST1 {[0;1m
!W‰˜«á©«˜© œ ©˜šàšé¤ £¤¬£á«à¤:!)
[0;1m} T Networking, import status


NETST2 {[0;1;32m
!W€§æ «¦ ©ç©«£˜ [37m%s[32m:!)
[37m!FÄ
[0;1m} T Networking, import, system name


NETST3 {[0;1;32m    %-55.55s -> %-16.16s
} T Networking, import, list item


NETST4 {[0;1m!FÄ
[0;1m} T Networking, import, list footer






----------------------------------------------------------------------

WCNAXES {[0;1;31m
!JSorry, your access level does not allow writing messages to
club @CLUB@.!)
[0;1m} T Write Club message, you don't have write access


WCCLUBR {[0;1;31m
!JSorry, that club doesn't exist.!)
[0;1m} T Write Club message, club does not exist


WCNCRDS {[0;1;31m
!JYou don't have enough credits to write a message to Club @CLUB@.!)
[0;1m} T Write Club message: not enough credits, while asking


WCRNEC {[0;1;31m
!JYou no longer have enough credits to send this message to club @CLUB@.!)
[0;1m} T Write Club message: not enough credits to send


WCWHO {[0;1m
!WMessage recipient
([33m?[37m for help) [Enter=everyone]:!) [0m} T Write Club message: get recipient of message


WCHELP {[0;1m

!JYou can enter a message recipient as follows:!)

1. !i!JEnter a user ID, or part of one (at least three characters,
though).!)
!0l
2. !i!JPress [33mEnter[37m to send a message to everyone in the club.!)
!0l
[0;1m} T Write Club message: help


WCUNKID {[0;1;31m
!JSorry, that user does not exist.!)
[0;1m} T Write Club message: unknown user ID


WCRCPOK {[0;1;32m
!JYour message will be sent to [37m%s[32m.!)
[0;1m} T Write Club message: confirming recipient of message


WCRCPALL {[0;1;32m
!JYour message will be sent to [37meveryone[32m.!)
[0;1m} T Write Club message: confirming recipient of message is 'All'


WCATT {[0;1m
!WWould you like to attach a file to this message?
(This is charged [32m%d credit%s[37m)
([[33m“[0;1m]es / [[33mN[0;1m]o):!) [0m} T Write Club message: ask if file attachment required


WCRRSEL {[0;1;31m
!WPlease answer with [33mY[31m or [33mN[31m.!)
[0;1m} T Write Club message: invalid answer to question


WCATTAPP {[0;1;32m
ÛÛ  !W!iThe file you uploaded has been automatically approved for
users' download.!)
!0l[0;1m} T Write Club message: attachment auto-approved


WCATTNAP {[0;1;33m
ÛÛ  !W!iThe file must be approved by the club operator before it
becomes available for other users to download.!)
!0l[0;1m} T Write Club message: attachment needs approval


WCRNOT {[0;1m***

!J[32m%s[37m just sent you a message in club
[32m%s[37m. It regards "[32m%s[37m".!)
[0;1m
} T Write Club message: notification for recipient


WCRNOTC {[0;1m***

!J[32m%s[37m just copied you a message in club
[32m%s[37m. It regards "[32m%s[37m".!)
[0;1m
} T Write Club message: notification for recipient, copied message






RCMNU {[0;1m
!JYou can read messages in the following ways:!)

  [[33mS[37m~]can . . . . . . . . . .  Read messages interactively     
  [[33mL[37m~]ist  . . . . . . . . . . Continuous list of messages
  [[33mT[37m~]o You . . . . . . . . . .  Scan messages to you only
  [[33mF[37m~]rom You  . . . . . . . . Scan messages from you only
  [[33mK[37m~]ey  . . . . . . . . . . . . . . . . . Keyword search

  [[33mQ[37m~]uick . . . . . . . . Quickscan (read multiple clubs)

!WEnter your choice ([33m?[37m for help) } T Read Club messages, method menu


RCMNUD {[Enter=[33m%c[37m]:[0m!) } T Read Club messages, default value


RCMNUR {[0;1;31m
!JThis is not a valid choice at this point.!)
[0;1m} T Read Club messages, invalid selection in method menu


RCMNUH {[0;1m

!JYou can read club messages in the following ways:!)

!W[[33mS[37m]can:     !12iInteractive reading. Start
reading at any message. You can move to other messages, reply
publically or by email, follow threads, et cetera
(see the help screens while scanning for more information).!)
!0l 
!W[[33mT[37m]o you:   !12iJust like scan, but only shows
messages addressed to you.!)
!0l 
!W[[33mF[37m]rom you: !12iSame thing, but only shows messages
you've written.!)
!0l 
!W[[33mL[37m]ist:     !12iDisplays a list of club messages. There
are a various different list styles to choose from (see the list help for
more information).!)
!0l
!W[[33mK[37m]ey:      !12iSearches the club for one or more keywords
and displays the messages containing any of them as per the scan command.!)
!0l
!W[[33mQ[37m]uick:    !12iQuickscan allows you to read new
messages in multiple clubs, using any of the above methods. See the
quickscan help screens for more information.!)
!0l
[0;1m
} T Read Club messages, help on method menu


DNLNAX {[0;1;31m
!JSorry, your access level does not allow downloading files from
club [37m@CLUB@[31m.!)
[0;1m} T Download Club files, access denied


DMNU {[0;1m
!JYou can browse messages with file attachments in a number of ways:!)

  [[33mS[37m~]can . . . . . . . . . .  Read messages interactively     
  [[33mL[37m~]ist  . . . . . . . . . . Continuous list of messages
  [[33mT[37m~]o You . . . . . . . . . .  Scan messages to you only
  [[33mF[37m~]rom You  . . . . . . . . Scan messages from you only
  [[33mK[37m~]ey  . . . . . . . . . . . . . . . . . Keyword search

  [[33mQ[37m~]uick . . . . . . . . Quickscan (read multiple clubs)

!WEnter your choice ([33m?[37m for help) } T Download Club files, method menu


DMNUD {[Enter=[33m%c[37m]:[0m!) } T Download Club files, default value


DMNUR {[0;1;31m
!JThis is not a valid option.!)
[0;1m} T Download Club files, invalid selection in method menu

DMNUH {[0;1m

!JThis command works just like the Read command, but only displays
messages with files attached. You can browse messages/files
in the following ways:!)

!W[[33mS[37m]can:     !12iInteractive reading. Start
reading at any message. You can move to other messages, reply
publically or by email, follow threads, et cetera
(see the help screens while scanning for more information).!)
!0l 
!W[[33mT[37m]o you:   !12iJust like scan, but only shows
messages addressed to you.!)
!0l 
!W[[33mF[37m]rom you: !12iSame thing, but only shows messages
you've written.!)
!0l 
!W[[33mL[37m]ist:     !12iDisplays a list of club messages. There
are a various different list styles to choose from (see the list help for
more information).!)
!0l
!W[[33mK[37m]ey:      !12iSearches the club for one or more keywords
and displays the messages containing any of them as per the scan command.!)
!0l
!W[[33mQ[37m]uick:    !12iQuickscan allows you to read new
messages in multiple clubs, using any of the above methods. See the
quickscan help screens for more information.!)
!0l
[0;1m
} T Download Club files, help on method menu


FSCCAN {[0;1;31m
!JAborted.!)
[0;1m} T File scan aborted


RQMNU {[0;1m
Quickscan methods:

  [[33mS[37m~]can . . . . . . . . . .  Read messages interactively     
  [[33mL[37m~]ist  . . . . . . . . . . Continuous list of messages
  [[33mT[37m~]o You . . . . . . . . . .  Scan messages to you only
  [[33mF[37m~]rom You  . . . . . . . . Scan messages from you only
  [[33mK[37m~]ey  . . . . . . . . . . . . . . . . . Keyword search

  [[33mC[37m]onfigure . . . . . . .  Configure your quickscan list

!WQuickscan method ([33m?[37m for help } T Read club messages, Quick method menu


RQMNUH {[0;1m

!JQuickscan is your personalised club reading tool. It allows you to
read new messages in all clubs that interest you. You can browse messages
in the following ways:!)

!W[[33mS[37m]can:     !13iInteractive reading. Start
reading at any message. You can move to other messages, reply
publically or by email, follow threads, et cetera
(see the help screens while scanning for more information).!)
!0l 
!W[[33mT[37m]o you:   !13iJust like scan, but only shows
messages addressed to you.!)
!0l 
!W[[33mF[37m]rom you: !13iSame thing, but only shows messages
you've written.!)
!0l 
!W[[33mL[37m]ist:     !13iDisplays a list of club messages. There
are a various different list styles to choose from (see the list help for
more information).!)
!0l
!W[[33mK[37m]ey:      !13iSearches the club for one or more keywords
and displays the messages containing any of them as per the scan command.!)
!0l
!W[[33mC[37m]onfigure: !13iAllows you to set which clubs will be search
by Quickscan. Power users can also reset the last read message pointers.!)
!0l
[0;1m} T Read club messages, Quick method help


RQCFH {[0;1m

!JThis is the first time you're using Quickscan. Before you can use
Quickscan, you must configure it. This involves choosing which clubs you
find interesting.!)

!JThe system remembers the last read message in each club, so that
Quickscan only presents messages posted after you last read a club.!)

!JInitially, all clubs are included in your Quickscan list. You can remove
club Foo by entering [33m-/Foo[37m, or add it using
[33m+/Foo[37m (the slashes are optional, but it's convention to show them
when referring to clubs). For a list of all available clubs, try
[33m+?[37m. To add all clubs, enter
[33m+ALL[37m. To remove them all, do the obvious: [33m-ALL[37m.
To mark all of a club's messages as already read, enter 
[33m+/Foo[37m twice. To catch up with all messages in all clubs, you could
enter [33m+ALL +ALL[37m (no need to press Enter in between).!)
} T Read Club messages, Quick Configure help


RQCLH {[0;1;32m
Your Quickscan list includes the following club(s):

[0m} T Read Club messages, Quick Configure, club list header


RQLCE {[0;1;31m
!JYour Quickscan list is empty.!)
[0m} T Read Club messages, Quick Configure, no clubs



RQCLF {[0;1m
} T Read Club messages, Quick Configure, club list footer


RQCMNU {[0;1m
   [33m+[37m  . . . . . . . . . . . . . . Add a Club
   [33m-[37m . . . . . . . . . . . . . Remove a Club
   [33mV[37miew . . . .  Display your Quickscan list

!WEnter your choice ([33mV[37m,[33m+[37m,[33m-[37m,[33m?[37m
for help, or [33mX[37m to save the list:!)[0m } T Read Club messages, Quick Configure, menu


RQCHELP {[0;1m

!JYour Quickscan list contains clubs that you find interesting. Quickscan
allows you to read new messages in those clubs, using one command
([33mCRQS[37m, in most systems).!)

!JThe system remembers the last read message in each club, so that
Quickscan only presents messages posted after you last read a club.!)

!JInitially, all clubs are included in your Quickscan list. You can remove
club Foo by entering [33m-/Foo[37m, or add it using
[33m+/Foo[37m (the slashes are optional, but it's convention to show them
when referring to clubs). For a list of all available clubs, try
[33m+?[37m. To add all clubs, enter
[33m+ALL[37m. To remove them all, do the obvious: [33m-ALL[37m.
To mark all of a club's messages as already read, enter 
[33m+/Foo[37m twice. To catch up with all messages in all clubs, you could
enter [33m+ALL +ALL[37m (no need to press Enter in between).!)
[0;1m
} T Read Club messages, Quick Configure help #2


RQCADD {[0;1m
!WClub name to add to the list ([33m?[37m to list clubs):!)[0m } T Read Club messages, Quick Configure, add club


RQCCR {[0;1;31m
!JThat club doesn't exist.!)
} T Read Club messages, Quick Configure, add, unknown club


RQCDEL {[0;1m
!WClub name to remove from the list ([33m?[37m to list clubs):!)[0m } T Read Club messages, Quick Configure, delete club


RQCDR {[0;1;31m
!JThat club isn't in your Quickscan list.!)
} T Read Club messages, Quick Configure, delete, unknown club


RLMNU {[0;1m
!WYou can list messages in the following ways:!)

  [[33mB[37m]rief . . . . . One brief line per message
  [[33mT[37m]itle  . . . .  Shows message headers only
  [[33mF[37m]ull  . . . Shows message headers and body

!WList method ([33m?[0;1m for help)!)[0m } T List Club messages, method menu


RLMNUR {[0;1;31m
!WThis is not a valid choice at this stage. Enter [33m?[31m for help.!)
[0;1m} T List Club messages, invalid selection


RLMNUH {[0;1m

!JThe [33mL[37mist command displays continuous lists of messages
in one of the following formats:!)

!W[[33mB[37m]rief: !9iDisplay one line for each message. This includes
message number, date, sender and as much of the subject as can fit your
screen width.!)
!0l
!W[[33mT[37m]itle: !9iThis shows the full header of each message. This
includes message number, date, sender and recipient, subject, the name of the
attached file (if any), how many times the message was read, how many times
the file was downloaded, how many replies the message has had, and the most
recent entries of the message's history.!)
!0l
!W[[33mF[37m]ull:  !9iSame as the above, but also displays the message
body, i.e. the text of the messae. Any attached files are ignored.!)
!0l
[0;1m
} T List Club messages, method menu help


RLASK {[0;1m
!JStart listing at what message number? Enter [[33mF[37m]irst
for the first existing message, [[33mL[37m]ast 
for the last one, [33mEnter[37m for the current message
([32m#%ld[37m), or [33m?[0;1m for help.!)

!WMessage to start listing with:!) [0m} T List Club messages, asking for message number 


RLASKR {[0;1;31m
!WSorry, that is not a valid choice here.!)
[0;1m} T List Club messages, error while asking for message number


RLASKH {[0;1m
!JSimply press [33mEnter[37m to start the list with the first new message
of club @CLUB@. If there are no new messages, listing will start with the
last one. A period ([33m.[37m) is equivalent to [33mEnter[37m, which is
handy for concatenated commands. For instance, the command [33mCRLB.[37m
at the main menu means "brief list of all new messages of the current club".!)

!JEnter [33mF[37m to start with the first available message, or
[33mL[37m for the last one.!)

!JEnter [33mX[37m (eXit) to bail out. Otherwise, enter a message number
to start listing from. If that message doesn't exist, the next available
message will be used.!)
[0;1m} T List Club messages, help about entering message numbers


RLBNMSG {[0;1;31m
!JNo messages were found.!)
[0;1m} T List Club messages, no messages found


RLMISS {[0;1m
Message [32m%d[37m not found. Proceeding to the next one:
[0;1m} T List Club messages, message number not found


RLBHDR {[0;1;32m
Listing [37m@CLUB@: @CLUBDESC@[32m...
[37m
Number  Sender      Date and time       Subject
!FÄ
} T List Club messages, brief listing header


RLBTAB {[0;1;33m%6d  %-10s  %s %s  %s
} List Club messages, brief listing table


RLBFTR {[0;1m!FÄ
[0;1m} T List Club messages, brief listing footer


RLTHDR {[0;1;32m
Listing [37m@CLUB@: @CLUBDESC@[32m...
[0;1m} T List Club messages, title/full listing header


RLDONE {[0;1m
!WEnd of messages.!)
[0;1m} T List Club messages, end of listing



RLABORT {[0;1m

!WListing aborted.!)
[0;1m} T List Club messages, listing aborted





RSASK {[0;1m
!JStart reading at what message number? Enter [[33mF[37m]irst
for the first existing message, [[33mL[37m]ast 
for the last one, [33mEnter[37m for the current message
([32m#%ld[37m), or [33m?[0;1m for help.!)

!WMessage to start with:!) [0m} T Scan Club messages, asking for message number 


RSASKR {[0;1;31m
!WSorry, that is not a valid choice here.!)
[0;1m} T Scan Club messages, error while asking for message number


RSASKH {[0;1m
!JSimply press [33mEnter[37m to start reading the first new message
of club @CLUB@. If there are no new messages, listing will start with the
last one. A period ([33m.[37m) is equivalent to [33mEnter[37m, which is
handy for concatenated commands. For instance, the command [33mCRS.[37m
at the main menu means "start scanning new messages in the current club".!)

!JEnter [33mF[37m to start with the first available message, or
[33mL[37m for the last one.!)

!JEnter [33mX[37m (eXit) to bail out. Otherwise, enter a message number
to start listing from. If that message doesn't exist, the next available
message will be used.!)
[0;1m} T Scan Club messages, help about entering message numbers


RSWAIT {[0;1;32m
!JScanning messages, please wait...!)
[0;1m} T Scan Club messages, please wait...


RSBNMSG {[0;1;31m
!JNo messages were found.!)
[0;1m} T Scan Club messages, no messages found


RSMISS {[0;1m
Message [32m%d[37m not found. Proceeding to the next one:
[0;1m} T Scan Club messages, message number not found


RSTHDR {[0;1;32m
Scanning [37m@CLUB@: @CLUBDESC@[32m...
[0;1m} T Scan Club messages, scanning club


RSSCNM {[0;1m
[[33mN[37m]ext      [[33mP[37m]revious
[[33mR[37m]ead      [[33m#[37m] jump to message
[[33mT[37m]hread    [[33mQ[37m]uickscan commands
e[[33mX[37m]it

Your choice ([33m?[37m for help); } T Scan Club messages, choices while scanning messages


RSSCNMH {[0;1m

!JHere's what all those commands do:!)

!W[33mN[37mext:      !iJump to the next message without reading this one. You can
use this command as a simple means of scanning messages. Concatenate N multiple times
e.g. [33mNNNNN[37m) and message headers of the next few (five, in this example) messages
will be printed, leaving you at the last one.!)
!0l
!W[33mP[37mrevious:  !iJump to the previous message. Works just like the above command.!)
!0l
!W[33m#[37m:         !iEnter a message number after the [33m#[37m and you can jump to that
message, or the closest available one if the desired message isn't available. You can also use
[33m#L[37m (last message) and [33m#F[37m (first message).!)
!0l
!W[33mT[37mhread:    !iMessage threading. This leads you to a submenu.
Use it to move to the previous or next message in this discussion (thread).
You can also jump to the message this one is a reply to.!)
!0l
!W[33mQ[37muickscan: !iThis opens a submenu. Use it to handle your
quickscan process: you can jump to the previous or next club, remove the
current club from your quickscan list, catch up with this club, and more.!)
!0l
!W[33mR[37mead:      !iRead this message. After reading it, you'll have
more message handling options.!)
!0l
[0;1m} T Scan Club messages, help about scanning commands


RSSCNMD {[0;1m
[[33mN[37m]ext               [[33mP[37m]revious
[[33mR[37m]ead               [[33m#[37m] jump to a message 
[[33mT[37m]hread menu        [[33mD[37m]ownload
[[33mQ[37m]uickscan menu     e[[33mX[37m]it

Your choice ([33m?[37m for help)? } T Scan Club messages, scan choices with download


RSSCNMHD {[0;1m

!JHere's what all those commands do:!)

!W[33mN[37mext:      !iJump to the next message without reading this one. You can
use this command as a simple means of scanning messages. Concatenate N multiple times
e.g. [33mNNNNN[37m) and message headers of the next few (five, in this example) messages
will be printed, leaving you at the last one.!)
!0l
!W[33mP[37mrevious:  !iJump to the previous message. Works just like the above command.!)
!0l
!W[33m#[37m:         !iEnter a message number after the [33m#[37m and you can jump to that
message, or the closest available one if the desired message isn't available. You can also use
[33m#L[37m (last message) and [33m#F[37m (first message).!)
!0l
!W[33mT[37mhread:    !iMessage threading. This leads you to a submenu.
Use it to move to the previous or next message in this discussion (thread).
You can also jump to the message this one is a reply to.!)
!0l
!W[33mQ[37muickscan: !iThis opens a submenu. Use it to handle your
quickscan process: you can jump to the previous or next club, remove the
current club from your quickscan list, catch up with this club, and more.!)
!0l
!W[33mR[37mead:      !iRead this message. After reading it, you'll have
more message handling options.!)
!0l
!W[33mD[37mownload:  !iDownload the file attached to this message
without reading the message itself.!)
!0l
[0;1m} T Scan Club messages, help for RSSCNMD


RSSCNR {[0;1;31m
!JSorry, that is not a valid option at this stage.!)
[0;1m} T Scan Club messages, invalid selection from scan menu


RSDEF {[Enter=[33m%c[37m]: [0m} T Scan Club messages, default value for menus



RSGONUM {[0;1m
!JYou can jump to a message by entering its number here. If the message
isn't found, you'll see the next available one. For quicker navigation,
concatenate this command as, for instance, [33m#123[37m (at the previous
menu), to jump to message 123.!)

Jump to what message? ([33mX[0;1m to bail out): } T Scan Club messages, goto what message?


RSBEG {[0;1;33m
You've reached the first message.
[0;1m} T Scan Club messages, reached beginning of messages


RSEND {[0;1;33m
You've reached the last message.
[0;1m} T Scan Club messages, reached beginning of messages


RSDEL {[0;1;31m
!JSorry, this message was just deleted.!)
[0;1m} T Scan Club messages, message has just been deleted, can't read


RSIOERR {[0;1;31m
!JThere was an error while reading the message. Please notify the Sysop
about this.!)
[0;1m} T Scan Club messages, I/O error while reading message


RSRMNU1 {[0;1m
[[33mN[37m]ext          [[33mP[37m]revious
[[33mE[37m]mail reply   [[33mR[37m]eply
[[33mT[37m]hread        e[[33mX[37m]it

Your choice ([33m?[37m for help): } T Scan Club messages, choices after reading message


RSRMNU1H {[0;1m

!JHere's what all those commands do:!)

!W[33mN[37mext:      !iJump to the next message without reading this one. You can
use this command as a simple means of scanning messages. Concatenate N multiple times
e.g. [33mNNNNN[37m) and message headers of the next few (five, in this example) messages
will be printed, leaving you at the last one.!)
!0l
!W[33mP[37mrevious:  !iJump to the previous message. Works just like the above command.!)
!0l
!W[33m#[37m:         !iEnter a message number after the [33m#[37m and you can jump to that
message, or the closest available one if the desired message isn't available. You can also use
[33m#L[37m (last message) and [33m#F[37m (first message).!)
!0l
!W[33mT[37mhread:    !iMessage threading. This leads you to a submenu.
Use it to move to the previous or next message in this discussion (thread).
You can also jump to the message this one is a reply to.!)
!0l
!W[33mE[37mmail:     !iReply to this user in private. The message will
be sent via email.!)
!W[33mR[37meply:     !iPublically reply to this message.!)
!0l
[0;1m} T Scan Club messages, help about reading messages, version 1


RSRMNU2 {[0;1m
[[33mN[37m]ext          [[33mP[37m]revious
[[33mC[37m]lear         [[33mM[37m]odify
[[33mE[37m]mail reply   [[33mR[37m]eply
[[33mT[37m]hread        e[[33mX[37m]it

Your choice ([33m?[37m for help): } T Scan Club messages, choices after reading message


RSRMNU2H {[0;1m

!JHere's what all those commands do:!)

!W[33mN[37mext:      !iJump to the next message without reading this one. You can
use this command as a simple means of scanning messages. Concatenate N multiple times
e.g. [33mNNNNN[37m) and message headers of the next few (five, in this example) messages
will be printed, leaving you at the last one.!)
!0l
!W[33mP[37mrevious:  !iJump to the previous message. Works just like the above command.!)
!0l
!W[33m#[37m:         !iEnter a message number after the [33m#[37m and you can jump to that
message, or the closest available one if the desired message isn't available. You can also use
[33m#L[37m (last message) and [33m#F[37m (first message).!)
!0l
!W[33mT[37mhread:    !iMessage threading. This leads you to a submenu.
Use it to move to the previous or next message in this discussion (thread).
You can also jump to the message this one is a reply to.!)
!0l
!W[33mE[37mmail:     !iReply to this user in private. The message will
be sent via email.!)
!W[33mR[37meply:     !iPublically reply to this message.!)
!0l
!W[33mM[37modify:    !iYou are the sender of this message. Use this
command to modify its contents.!)
!0l
!W[33mC[37mlear:     !iYou are the sender of this message. Use this
command to delete this message. You will not be asked for confirmation.!)
!0l
[0;1m} T Scan Club messages, help about reading messages, version 2


RSRMNU3 {[0;1m
[[33mN[37m]ext           [[33mP[37m]revious
[[33mE[37m]mail reply    [[33mR[37m]eply
[[33mT[37m]hread         [[33mS[37m]IGop menu
e[[33mX[37m]it

Your choice ([33m?[37m for help): } T Scan Club messages, choices after reading message


RSRMNU3H {[0;1m

!JHere's what all those commands do:!)

!W[33mN[37mext:      !iJump to the next message without reading this one. You can
use this command as a simple means of scanning messages. Concatenate N multiple times
e.g. [33mNNNNN[37m) and message headers of the next few (five, in this example) messages
will be printed, leaving you at the last one.!)
!0l
!W[33mP[37mrevious:  !iJump to the previous message. Works just like the above command.!)
!0l
!W[33m#[37m:         !iEnter a message number after the [33m#[37m and you can jump to that
message, or the closest available one if the desired message isn't available. You can also use
[33m#L[37m (last message) and [33m#F[37m (first message).!)
!0l
!W[33mT[37mhread:    !iMessage threading. This leads you to a submenu.
Use it to move to the previous or next message in this discussion (thread).
You can also jump to the message this one is a reply to.!)
!0l
!W[33mE[37mmail:     !iReply to this user in private. The message will
be sent via email.!)
!W[33mR[37meply:     !iPublically reply to this message.!)
!0l
!W[33mS[37mIGop:     !iTakes you to the operator's submenu for club
@CLUB@, where you can copy, forward, delete and modify this message. For
more information, enter the submenu and request help.!)
!0l
[0;1m} T Scan Club messages, help about reading messages, version 3


ATTNAP {[0;1;31m
ÛÛ  !W!iThere is a file attached to this message, but
the club operator hasn't approved it yet.!)
!0l[0;1m} T Download Club attachment, file not approved


ATTNAX {[0;1;31m
ÛÛ  !W!iThere is a file attached to this message, but
your access level doesn't allow you to download it.!)
!0l[0;1m} T Download Club attachment, access denied


THRMNU {[0;1m
Message threading:

[[33mF[37m]orward .  Next message in thread   [[33mB[37m]ackward . . . Previous in thread
[[33mP[37m]arent . . . . . . Parent message   [[33mR[37m]eturn  . . . .  Starting message
e[[33mX[37m]it . . . . Leave threading mode

Your choice ([33m?[37m for help): } T Scan Club messages, threading menu



THRMNUH {[0;1m

!JUse this menu to follow a discussion thread. A thread is a number of
messages sharing the same subject. Here's what the commands do:!)

!W[33mF[37morward:  !iMove to the next message in the thread.!)
!0l
!W[33mB[37mackward: !iMove to the previous message in the thread.!)
!0l
!W[33mP[37marent:   !iMove to the message replied to by the current
message.!)
!0l
!W[33mR[37meturn:   !iReturn to the message you were reading when you
entered thread mode. If you have entered multiple thread modes, it exits all
of them.!)
!0l
[0;1m} T Scan Club messages, threading help


THREAD {[0;1;36;5m
ÛÛ  [0;1;36m!W!iThread mode ([33mTR[36m to exit mode).!)
!0l[0;1m} T Scan Club messages, thread indicator


THRNRET {[0;1;31m
!JYou aren't in thread mode, so there's nowhere to return to.!)
[0;1m} T Threading, can't use return unless threading


THREND {[0;1;33m
!JYou've reached the end of this thread. Use the [37mTR[33m command
to return to the original message.!)
[0;1m} T Threading, reached end of discussion


THRBEG {[0;1m
!JYou've reached the beginning of the thread. Use the [33mTR[37m
command to return to the original message.!)
[0;1m} T Threading, reached beginning of discussion


THRRET {[0;1m
!JReturning to message [32m%s/%d[37m, the message you were reading
when you invoked thread mode.!)
[0;1m} T Threading, returning to original message


THRPR {[0;1;31m
!JSorry, this message isn't a reply. You can tell replies by the
"[37m(Reply to Club/xxx)[31m" line at the top of the message.!)
} T Threading, there is no parent message


THRPNF {[0;1;31m
!JMessage [37m%s/%d[31m wasn't found.
It has probably been deleted or it expired.!)
[0;1m} T Threading, parent message not found


THRCLC {[0;1;32m
!JLeaving club [37m@CLUB@[32m to enter [37m%s[32m.
Enter [32mTR[32m to return to the original club and message.!)
[0;1m} T Threading, leaving current club





MCMVT {[0;30;47m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [34mModify Message[0;30;47m ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;1;37;47m¿ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  Subject  . . . . . . . . [1;44;37m@63;43;0s[0;1;47;37m  ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  Filename  . . . . . . .  [1;44;37m@16;16;0s[0;1;47;37m                             ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  Ctrl-R for help                                                         [1;37m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³             [0;1;42;33m@14;"Edit"b[0;47;30mÜ    [0;1;42;33m@14;"OK"b[0;47;30mÜ    [0;1;41;33m@14;"Cancel"b[0;47;30mÜ  [0;1;47;37m³ [0m
[30;47m ³              ßßßßßßßßßßßßßßßß     ßßßßßßßßßßßßßßßß     ßßßßßßßßßßßßßßßß  [0;1;47;37m³ [0m
[30;47m À[0;1;37;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0m} T Modify Club Message, visual template


MCMLT {[2J[0;30;47m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [34mModify Message[0;30;47m ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;1;37;47m¿ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m1[30m. Subject  . . [34m@63;56;0s[0;1;47;37m ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m2[30m. Filename  . . . . . . . . . . . . . . . . . . . . .  [34m@16;16;0s[0;1;47;37m ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m3[30m. Edit message body          @1;"3Edit"b                                         [1;37m  ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m À[0;1;37;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0;1m
} T Modify message, linear template


MCMNEWSUBJ {[0;1m
!WEnter a new subject for this message.!)
} T Modify message, new subject


MCMNEWATTN {[0;1m
!WPlease enter the new filename of the attachment. If you leave the name
blank, it will fall back to the default filename, xxx.att, where xxx is the
number of this message. The attachment filename will be ignored if the message
has no attachment.!)
} T Modify message, new filename




COPMNU {[0;1m
Club operator menu:

[[33mM[37m]odify  . . . Change this message   [[33mE[37m]rase  . . . . . . Delete message
[[33mC[37m]opy . . .  To a user ans/or club   [[33mF[37m]orward . . . . Send to user/club
[[33mT[37m]ag . . . . .  Delete (un)protect   [[33mP[37m]eriodic . . . .  Regular posting
[[33mB[37m]ulletin . . .  Add as a bulletin   e[[33mX[37m]it  . . . . . . . . . . . Leave

Your choice ([33m?[37m for help): } T Club-op menu


COPMNUH {[0;1m

!JAs operator of @CLUB@, you can do the following:!)

!W[33mM[37modify:     !iChange the subject, attached file name (if any)
and/or body of message.!)
!0l
!W[33mE[37mrase:      !iDeletes the message. There will be NO confirmation.
The message is irretrievably lost.!)
!0l
!W[33mC[37mopy:       !iCopies this message to a user and/or another club.!)
!0l
!W[33mF[37morward:    !iForwards this message to a user and/or another club.
Works just like Copy above, but also deletes the original message from this club.!)
!0l
!W[33mT[37mag exempt: !iToggles the delete-protect flat on this message.
When the flag is set, the message becomes delete-protected. It will
never expire and other operators cannot delete this unless they clear the
flag first (using the same command).!)
!0l
!W[33mP[37meriodic:   !iUse this command to turn a message into a regular
posting. The message will resurface at regular intervals (that you specify).
This is useful to publicise club charters, FAQs and instructions for new users
who are unlikely to read old messages. You can remove the periodic nature of
a message by setting the period to 0.!)
!0l
!W[33mB[37mulletin:   !iInserts the message's body or attached file
(if any) into the bulletin databse for this club. Useful for archiving
interesting articles, FAQs etc.!)
!0l
[0;1m} T Club-op menu, help


COPMNUF {[0;1m
Club operator menu:

[[33mM[37m]odify  . . . Change this message   [[33mE[37m]rase  . . . . . . Delete message
[[33mC[37m]opy . . .  To a user ans/or club   [[33mF[37m]orward . . . . Send to user/club
[[33mT[37m]ag . . . . .  Delete (un)protect   [[33mP[37m]eriodic . . . .  Regular posting
[[33mA[37m]pprove . .  Allow file downloads   [[33mI[37m]nsert . . .  Merge body and file
[[33mB[37m]ulletin . . .  Add as a bulletin   e[[33mX[37m]it  . . . . . . . . . . . Leave

Your choice ([33m?[37m for help): } T Club-op menu for file attachments


COPERR {[0;1;31m
!JSorry, that is not a valid choice here.!)
[0;1m} T Club-op menu, invalid selection from menu


COPMNUFH {[0;1m

!JAs operator of @CLUB@, you can do the following:!)

!W[33mM[37modify:     !iChange the subject, attached file name (if any)
and/or body of message.!)
!0l
!W[33mE[37mrase:      !iDeletes the message. There will be NO confirmation.
The message is irretrievably lost.!)
!0l
!W[33mC[37mopy:       !iCopies this message to a user and/or another club.!)
!0l
!W[33mF[37morward:    !iForwards this message to a user and/or another club.
Works just like Copy above, but also deletes the original message from this club.!)
!0l
!W[33mT[37mag exempt: !iToggles the delete-protect flat on this message.
When the flag is set, the message becomes delete-protected. It will
never expire and other operators cannot delete this unless they clear the
flag first (using the same command).!)
!0l
!W[33mP[37meriodic:   !iUse this command to turn a message into a regular
posting. The message will resurface at regular intervals (that you specify).
This is useful to publicise club charters, FAQs and instructions for new users
who are unlikely to read old messages. You can remove the periodic nature of
a message by setting the period to 0.!)
!0l
!W[33mB[37mulletin:   !iInserts the message's body or attached file
(if any) into the bulletin databse for this club. Useful for archiving
interesting articles, FAQs etc.!)
!0l
!W[33mA[37mpprove:    !iThis message has an attached file. Use this
command to approve the file for download by mere mortals. If the file has
already been approved, this command will unapprove it. This is useful
if a file has to be reviewed further before approval.!)
!0l
!W[33mI[37mnsert:     !iSome users have a nasty habit of sending
their messages as attached files. As a result, many people don't read them.
Use this command to fix this. It appends the attached file to the message's
body, or overwrites the body with the file (you will be asked for your
preference). The message stops having an attachment.!)
!0l
[0;1m} T Club-op menu for file attachments, help



COPTTG {[0;1;32m
!JOkay, the message [37mcannot be deleted[32m.!)
[0;1m} T Club-op menu, tag exempt, message has been tagged


COPTUN {[0;1;32m
!JOkay, the message [37mcan be deleted again[32m.!)
[0;1m} T Club-op menu, tag exempt, message has been untagged


COPPASK {[0;1m
!WHow many days before this message will resurface (0=never); } T Club-op menu, periodic message, get period


COPPDEF {[Enter=%d]!) [0m} T Club-op menu, periodic message, default


COPPERR {[0;1;31m
!WEnter a number between [37m%d[31m and [37m%d[31m.!)
[0;1m} T Club-op menu, periodic message, error


COPPOK1 {[0;1;32m
!WOkay, the message is no longer periodic.!)
[0;1m} T Club-op menu, periodic message, zero period


COPPOK2 {[0;1;32m
!WOkay, the message will resurface every [37m%d day%s[32m.!)
[0;1m} T Club-op menu, periodic message, zero period


DAYSNG {} T Days, singular form
DAYPLR {s} T Days, plural form


COPAAPP {[0;1m
!JOkay, the attachment's been approved.!)
[0;1m} T Club-op menu, approved attached file


COPAUNA {[0;1m
!JOkay, the attachment's approval has been lifted.!)
[0;1m} T Club-op menu, unapproved attached file


COPMVT {[0;30;47m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [34mModify Message[0;30;47m ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;1;37;47m¿ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  Subject  . . . . . . . . [1;44;37m@63;43;0s[0;1;47;37m  ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  Filename  . . . . . . .  [1;44;37m@16;16;0s[0;1;47;37m                             ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  File approved  . . . . . [0;30;46m [@"X "t] [0;47;30m                      (space š ˜ ˜¢¢˜šã)  [1;37m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  Delete exempt . . . . .  [0;30;46m [@"X "t] [0;47;30m                      (space š ˜ ˜¢¢˜šã)  [1;37m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  Periodic, every  . . . . [1;44;37m@6;0;999999;0n[0;30;47m      (0-999999 days, 0=non-periodic)  [1;37m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  Ctrl-R for help                                                         [1;37m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³             [0;1;42;33m@14;"Edit"b[0;47;30mÜ    [0;1;42;33m@14;"OK"b[0;47;30mÜ    [0;1;41;33m@14;"Cancel"b[0;47;30mÜ  [0;1;47;37m³ [0m
[30;47m ³              ßßßßßßßßßßßßßßßß     ßßßßßßßßßßßßßßßß     ßßßßßßßßßßßßßßßß  [0;1;47;37m³ [0m
[30;47m À[0;1;37;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0m} T Club-op menu, modify club message, visual template


COPMLT {[2J[0;30;47m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [34mModify Message[0;30;47m ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;1;37;47m¿ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m1[30m. Subject  . . [34m@63;56;0s[0;1;47;37m ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m2[30m. Filename  . . . . . . . . . . . . . . . . . . . . .  [34m@16;16;0s[0;1;47;37m ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m3[30m. File approved  . . . . . . . . . . . . . . . . . . . . . . . . .  [34m@"X "t[0;1;47;37m ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m4[30m. Delete exempt  . . . . . . . . . . . . . . . . . . . . . . . . .  [34m@"X "t[0;1;47;37m ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m5[30m. Periodic, every  . . . . . . . . . . . . . . . . . . . . . . . [34m@6;0;999999;1n[0;1;47;37m ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m6[30m. Edit message test          @1;"6Edit"b                                         [1;37m  ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m À[0;1;37;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0;1m
} T Club-op menu, modify club message, linear template


COPMLT1 {[0;1m
!JPlease enter the new subject for this message.!)
} T Club-op menu, modify club message, linear template field #1


COPMLT2 {[0;1m
!JPlease enter a new name for the attached file. If you don't
specify a name, the default filename will be reinstated (xxx.att, where xxx
is the message number). Changing the filename does nothing if this message
doesn't have a file attached.!)
} T Club-op menu, modify club message, linear template field #2


COPMLT3 {[0;1m
!JThis field controls the approval state of the attached file (if any).
Most users will only be able to download approved files. If this message
has no attached file, this field has no effect.!)
} T Club-op menu, modify club message, linear template field #3


COPMLT4 {[0;1m
!JThis field controls whether the message is exempt from deletions.!)
} T Club-op menu, modify club message, linear template field #4


COPMLT5 {[0;1m
!JPeriodic messages are automatically re-posted to a club at regular
intervals. This field controls whether this message is periodic, and if so,
how often it should be re-posted. If the number is [33m0[37m, the message is not
periodic. Any other message specifies how many days to wait before
re-posting. For instance, enter a period of [33m1[37m to cause the message
to be re-posted every day, or [33m30[37m to get a (roughly) monthly
re-posting.!)
} T Club-op menu, modify club message, linear template field #5


COPMW1 {[0;1;31m
!JThis message lacks an attached file. The approval field has been ignored.!)
[0;1m} T Club-op menu, modify club message, warning 1


COPOK1 {[0;1;32m
!JThe file attached to this message has been approved for download.!)
[0;1m} T Club-op menu, approved message


COPOK2 {[0;1;32m
!JThe approval state of the file attached to this message has been revoked.
The file is no longer available for download.!)
[0;1m} T Club-op menu, unapproved message


COPOK3 {[0;1;32m
!JThis message is now exempt from deletion.!)
[0;1m} T Club-op menu, exempted message


COPOK4 {[0;1;32m
!JThis message is no longer exempt from deletion.!)
[0;1m} T Club-op menu, unexempted message


COPOK5 {[0;1;32m
!JThis message is now periodic, re-posted every [37m%d day%s[32m.!)
[0;1m} T Club-op menu, periodic message


COPOK6 {[0;1;32m
!JThis message is now non-periodic.!)
[0;1m} T Club-op menu, non-periodic message


COPIAMNU {[0;1m
!WWhat would you like to do with the attached file?!)

 [[33mO[37m]verwrite body . .  Replace message body with text of attached file
 [[33mA[37m]ppend to body  . . Add text of attached file to end of message body
e[[33mX[37m]it  . . . . . . .  Cancel
[0;1m} T Club-op menu, insert attachment menu


COPIASMNU {[0;1m
!WEnter your choice ([33mO[37m,[33mA[37m, [33m?[37m for help, or [33mX[37m to cancel):!) [0m} T Club-op menu, insert attachment short menu


COPIARS {[0;1;31m
!WSorry, this isn't an option at this stage.!)
[0;1m} T Club-op menu, insert attachment, invalid selection


COPIAH {[0;1m

!WOverwrite: !iThe text of the attached file replaces the body of the message. The original
message body is irretrievably lost.!)
!0l
!WAppend:    !iThe text of the attached file is appended to the body of the message.!)
!0l
!W[0;1;33;5mÛÛ[0;1;33m  ATTENTION: !iBefore using this command,
please ensure that the file attachment is in fact an uncompressed text file and not
a compressed or binary file.!)
!0l
[0;1m} T Club-op menu, insert attachment, help


COPIAO {[0;1;32m
!JOK, the contents of the attached file have replaced the body of the message.!)
[0;1m} T Club-op menu, insert attachment, overwritten


COPIAA {[0;1;32m
!JOK, the attached file has been appended to the message body.!)
[0;1m} T Club-op menu, insert attachment, appended


COPIAR {[0;1;31m
!JThere was in input/output error during the procedure.
Please notify the Sysop about the conditions leading up to this.!)
[0;1m} T Club-op menu, insert attachment, error


RKASK {[0;1m
!WEnter one or more keywords, or [33m?[37m for help:!)[0m } T Keyword scan, get search key(s)


RKHELP {[0;1m
!JThis command searches through club messages for one or more keywords that you supply.
Separate multiple keywords with spaces. If one of your keywords contains spaces, substitute
a dash ([33m-[37m) for the spaces. The dash stands for space, punctuation, and other symbols.!)

!JFor example, if you supply the keywords "demo system" you will scan for messages containing
"demo" or "system". The keywords will also match phrases like
"drugs [32msystem[37matically [32mdemo[37mlish your brain".!)

!JTo search for "DH Demo System" explicitly,
enter "DH-demo-system", although it's better to get slightly more hits than you'd want
rather than to lose important messages!!)
[0;1m} T Keyword scan, help on searching


RKSCAN1 {[0;1m
!WScanning club [32m@CLUB@[37m for keyword "[32m%s[37m"...!)
[0;1m} T Keyword scan, start scanning (single keyword)


RKSCAN2 {[0;1m
!WScanning club [32m@CLUB@[37m for keywords "[32m%s[37m"} T Keyword scan, start scanning (multiple keyword)


RKSCAN3 {, "[32m%s[37m"} T Keyword scan, keyword


RKSCAN4 { and "[32m%s[37m".!)
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
!WÛÛ  !iKeyword "%s" found.!)
!0l[0;1m} T Keyword scan, found the keyword


RKCAN {[0;1;31m

!JAborted by the user.!)
[0;1m} T Keyword scan, aborted


FAPPSCN {[0;1;32m
!JSearching club [37m@CLUB@[32m for unapproved files.!)
[0;1m} T File approval, scanning for unapproved files


FAPPASK {[0;1m
!WApprove this file? [[33mY[37m]yes / [[33mN[37m]o):!)[0m } T File approval, approval question


FAPPERR {[0;1;31m
!JSorry, this option isn't possible here.!)
[0;1m} T File approval, error in answer to FAPPASK


FAPPAPP {[0;1;32m
!JOK, the file's been approved and is available for download.!)
[0;1m} T File approval, file has been approved





QSEMPTY {[0;1;31m
!JSorry, there aren't any clubs in your quickscan list.
Issue the command [33mRQC[31m at the main clubs menu to
add clubs to your quickscan list.!)
[0;1m} T Quickscan, quickscan record is empty.


QSNONEW {[0;1;33m
!JNo new messages found.!)
[0;1m} T Quickscan, no new messages found


QSSCAN {[0;1;32m
!WQuickscanning [37m/%s[32m...!)
[0;1m} T Quickscan, quick scanning


QSEND {[0;1;32m
!JEnd of quickscan.!)
[0;1m} T Quickscan, end of quickscan


QSABORT {[0;1;31m
!JQuickscan aborted.!)
[0;1m} T Quickscan, aborted


QSLEAVE {[0;1;32m
!JLeaving club [37m/@CLUB@[32m.!)
[0;1m} T Quickscan, leaving current club


QSDONE {[0;1m
!JEnd of quickscan.!)
[0;1m} T Quickscan, done with quickscan


QSNNEM {[0;1;32m
!JNo new Email messages.!)
[0;1m} T Email Quickscan, no new mail in email area


QSLVEM {[0;1;32m
!JLeaving Email area...!)
[0;1m} T Email Quickscan, leaving email area


QWRT2EM {[0;1;32m
!JBack to the Email area...!)
[0;1m} T Email Quickscan, back to email messages


QSNOJMP {[0;1;31m
!JSorry, this isn't a valid option at this stage.!)
[0;1m} T Email Quickscan, can't use jump commands here


RQSRMNU1 {[0;1m
[[33mN[37m]ext         [[33mP[37m]revious
[[33mE[37m]mail reply  [[33mR[37m]eply
[[33mT[37m]hread       [[33mQ[37m]uickscan
e[[33mX[37m]it

Your choice ([33m?[37m for help)? } T Quickscan, choices after reading message


RQSRMNU1H {[0;1m

!JHere are your choices at this stage:!)

!W[33mN[37mext:      !iJump to the next message without reading this one. You can
use this command as a simple means of scanning messages. Concatenate N multiple times
e.g. [33mNNNNN[37m) and message headers of the next few (five, in this example) messages
will be printed, leaving you at the last one.!)
!0l
!W[33mP[37mrevious:  !iJump to the previous message. Works just like the above command.!)
!0l
!W[33m#[37m:         !iEnter a message number after the [33m#[37m and you can jump to that
message, or the closest available one if the desired message isn't available. You can also use
[33m#L[37m (last message) and [33m#F[37m (first message).!)
!0l
!W[33mT[37mhread:    !iMessage threading. This leads you to a submenu.
Use it to move to the previous or next message in this discussion (thread).
You can also jump to the message this one is a reply to.!)
!0l
!W[33mQ[37muickscan: !iThis opens a submenu. Use it to handle your
quickscan process: you can jump to the previous or next club, remove the
current club from your quickscan list, catch up with this club, and more.!)
!0l
!W[33mE[37mmail:     !iReply to this message in private. Your reply is
sent as email, not to the club.!)
!0l
!W[33mR[37meply:     !iPublic reply to this message.!)
!0l
[0;1m} T Quickscan, help about reading messages, version 1


RQSRMNU2 {[0;1m
[[33mN[37m]ext            [[33mP[37m]revious
[[33mC[37m]lear (delete)  [[33mM[37m]odify message
[[33mE[37m]mail reply     [[33mR[37m]eply
[[33mT[37m]hread          [[33mQ[37m]uickscan
e[[33mX[37m]it

Your choice ([33m?[37m for help)? } T Quickscan, choices after reading message


RQSRMNU2H {[0;1m

!JHere are your choices at this stage:!)

!W[33mN[37mext:      !iJump to the next message without reading this one. You can
use this command as a simple means of scanning messages. Concatenate N multiple times
e.g. [33mNNNNN[37m) and message headers of the next few (five, in this example) messages
will be printed, leaving you at the last one.!)
!0l
!W[33mP[37mrevious:  !iJump to the previous message. Works just like the above command.!)
!0l
!W[33m#[37m:         !iEnter a message number after the [33m#[37m and you can jump to that
message, or the closest available one if the desired message isn't available. You can also use
[33m#L[37m (last message) and [33m#F[37m (first message).!)
!0l
!W[33mM[37modify:    !iYou are the sender of this message. You can
modify its contents using this command.!)
!0l
!W[33mC[37mlear:     !iYou are the sender of this message. You can
delete this message with this command. Beware: you won't be asked for confirmation.!)
!0l
!W[33mT[37mhread:    !iMessage threading. This leads you to a submenu.
Use it to move to the previous or next message in this discussion (thread).
You can also jump to the message this one is a reply to.!)
!0l
!W[33mQ[37muickscan: !iThis opens a submenu. Use it to handle your
quickscan process: you can jump to the previous or next club, remove the
current club from your quickscan list, catch up with this club, and more.!)
!0l
!W[33mE[37mmail:     !iReply to this message in private. Your reply is
sent as email, not to the club.!)
!0l
!W[33mR[37meply:     !iPublic reply to this message.!)
!0l
[0;1m} T Quickscan, help about reading messages, version 2


RQSRMNU3 {[0;1m
[[33mN[37m]ext            [[33mP[37m]revious
[[33mE[37m]mail reply     [[33mR[37m]eply
[[33mT[37m]hread          [[33mS[37m]IGop menu
[[33mQ[37m]uickscan       e[[33mX[37m]it

Your choice ([33m?[37m for help)? } T Quickscan, choices after reading message


RQSRMNU3H {[0;1m

!JHere are your choices at this stage:!)

!W[33mN[37mext:      !iJump to the next message without reading this one. You can
use this command as a simple means of scanning messages. Concatenate N multiple times
e.g. [33mNNNNN[37m) and message headers of the next few (five, in this example) messages
will be printed, leaving you at the last one.!)
!0l
!W[33mP[37mrevious:  !iJump to the previous message. Works just like the above command.!)
!0l
!W[33m#[37m:         !iEnter a message number after the [33m#[37m and you can jump to that
message, or the closest available one if the desired message isn't available. You can also use
[33m#L[37m (last message) and [33m#F[37m (first message).!)
!0l
!W[33mM[37modify:    !iYou are the sender of this message. You can
modify its contents using this command.!)
!0l
!W[33mC[37mlear:     !iYou are the sender of this message. You can
delete this message with this command. Beware: you won't be asked for confirmation.!)
!0l
!W[33mT[37mhread:    !iMessage threading. This leads you to a submenu.
Use it to move to the previous or next message in this discussion (thread).
You can also jump to the message this one is a reply to.!)
!0l
!W[33mE[37mmail:     !iReply to this user in private. The message will
be sent via email.!)
!W[33mR[37meply:     !iPublically reply to this message.!)
!0l
!W[33mQ[37muickscan: !iThis opens a submenu. Use it to handle your
quickscan process: you can jump to the previous or next club, remove the
current club from your quickscan list, catch up with this club, and more.!)
!0l
!W[33mE[37mmail:     !iReply to this message in private. Your reply is
sent as email, not to the club.!)
!0l
!W[33mR[37meply:     !iPublic reply to this message.!)
!0l
!W[33mS[37mIGop:     !iMoves you to the operator's menu for club @CLUB@.
There, you can copy, forward, delete and modify this message, among other
things. For more information, enter the menu and request help there.!)
!0l
[0;1m} T Quickscan, help about reading messages, version 3


QSMMNU {[0;1m
Quickscan commands:

[[33mN[37m]ext club      [[33mP[37m]revious club
[[33mR[37m]emove club    [[33mB[37m]ookmark message
[[33mC[37m]atch up       [[33mS[37m]elect club
e[[33mX[37m]it

Your choice ([33m?[37m for help)? } T Quickscan menu


QWMNUR {[0;1;31m
!JSorry, that is not a valid option at this point.!)
[0;1m} T Quickscan menu, invalid selection


QSMNUH {[0;1m

!JAt this point, you can do the following:!)

!W[33mN[37mext club:     !iJump to the next club in your quickscan list.
Any unread messages in this club will be shown again in your next quickscan.
If this is the last club in your quickscan list, this command concludes the
scan.!)
!0l
!W[33mP[37mrevious club: !iJust like the above command, but jumps to the
previous club.!)
!0l
!W[33mR[37memove club:   !iRemoves this club from your quickscan list
and moves you to the next one. To add the club to your quiskcan list again,
use the [33mRQC[37m command at the main club menu.!)
!0l
!W[33mB[37mookmark:      !iSets this message to be the 'last read' message
for this club. This message and all previous ones will be considered read;
all further messages will be considered unread and will be presented to you
at your next cleanup. This command is useful when you've already read the
messages in a club, but you'd like to come back later on for a more careful reading.!)
!0l
!W[33mC[37match up:      !iMarks all messages in this club as read.
Takes you to the next club.!)
!0l
!W[33mS[37melect club:   !iJumps to a club of your choice. The club need
not be in your quickscan list.!)
!0l
[0;1m} T Quickscan menu, help


QSMBM {[0;1;32m
!JOK, bookmark place on message [37m%d[32m for club [37m%s[32m.!)
[0;1m} T Quickscan menu, bookmark placed


QSMCU {[0;1;32m
!JOK, all messages in club [37m%s[32m have been marked as read.!)
[0;1m} T Quickscan menu, caught up


QSMRM {[0;1;32m
!JOK, club [37m%s[32m has been removed from your quickscan list.
To add it again, use the [33mRQC[32m command at the main club menu.!)
[0;1m} T Quickscan menu, removed club from quickscan configuration


TLCNAX {[0;1;31m
!JSorry, this club's teleconference channel isn't available to your access
level.!)
[0;1m} T Enter teleconferences, access denied


BLTNAX {[0;1;31m
!JSorry, this club's  bulletin area isn't available to your access level.!)
[0;1m} T Enter bulletin reader, access denied


LANGEND {}
