LEVEL2 {}

 This is the title of your BBS (Bulletin Board System).
 This title will be presented to users when they connect
 with your system.

 Please hit F2, type in the name of your BBS, and hit the
 ÄÙ key.

BBSTTL {Acrobase} S 50 BBS name

 This is the codename (or maybe nodename) of the BBS used to
 make ourselves known to other friendly systems. It's usually
 a shorter (up to 8 characters) version of the full title.
 NO SPACES PLEASE!

BBSCOD {ACRO} S 8 BBS Codename for networking (NO SPACES PLEASE!)

 Your company name and address are presented to users when
 they are instructed as to how to purchase system credits,
 allowing them live connect time.

 Please hit F2, type your company name, and hit the ÄÙ key.

COMPANY {«â¢ ¦ª £æ¨¡ª} S 46 Company name

 Your company name and address are presented to users when
 they are instructed as to how to purchase system credits,
 allowing them live connect time.

 Please hit F2, type your company's street address, and hit
 the ÄÙ key.

ADDRES1 {à¡åà¤¦ª â¨ 62} S 44 Address Line 1

 Your company name and address are presented to users when
 they are instructed as to how to purchase system credits,
 allowing them live connect time.

 Please hit F2, type your company's city, state, and zip
 code, and hit the ÄÙ key.

ADDRES2 {¬¯â¢, 113 61} S 44 Address Line 2

 This is the city and state where your BBS is operating.
 When your live users connect with the system, they will be
 given the message:

 LIVE!  From <City and State>!  You have <so many> credits!

 Please hit F2, type the city and state where your BBS is
 operating (in capital letters), and hit the ÄÙ key.

CITY {ã¤} S 40 BBS city and state

 You may allocate some of your phone lines for demonstration
 purposes, while reserving others for live users only.

 Users will be told to dial this number with their modem
 when their account does not have "live" status, or when
 they are signing up for the first time.

 By default, all BBS lines are available for non-live usage.
 See the configuration variable SAMPLN (below) to limit
 your non-live lines.

DATAPH {8231753} S 32 Your main BBS phone number

 You may allocate some of your phone lines for demonstration
 purposes, while reserving others for live users only (see
 the preceding option).  When doing this, you will typically
 have two separate phone line "rotaries": one for everybody
 (your main BBS number) and one for live users only (which
 you can specify here).

 Users will be told that they can only use this phone number
 to dial up your BBS when their account has "live" status.

LIVEPH {8815616} S 34 Live usage phone number

VOICEPH {} S 32 Your voice phone number

IDLZAP {Minutes of user inactivity before hangup (0=off) 0} X 0 32767

IDLZAPT {Minutes of telnet line inactivity before hangup (0=off) 15} X 0 32767

IDLZAPS {Minutes of SSH line inactivity before hangup (0=off) 0} X 0 32767

IDLOVR {Key needed to override inactivity hangup? 5} N 0 129

 The "system variables" include many time measurements for
 accounting and statistical purposes.  In case of power-loss
 or other catastrophes, the system variables are
 periodically saved on disk.  This save takes a little chunk
 of time, so you will not want to do it constantly.  How
 often (in seconds) do you wish to save the system
 variables?

SVRATE {Minutes between saving system variables/statistics 3} N 3 32767

 How much are you going to charge users for each hour of
 live connect time (that is, for 3600 credits)?

CHGHOUR {60 ¨®£âª} S 30 Connect time charge per hour

 What is the minimum amount of live connect time that users
 may purchase?

CHGTIME {17 é¨ª} S 29 Minimum connect time purchase

 What is the charge for the minimum amount of live connect
 time that users may purchase?  This figure should be the
 product of the previous two.

CHGMIN {1000 ¨®£âª} S 31 Charge for minimum purchase

 The Audit trail is a database that records important events
 on The Major BBS.  The last seven entries in the audit
 trail appear on the Sysop console.  The entire audit trail
 database may be viewed by selecting (9) from the introduc-
 tory menu of The Major BBS.

 Do you wish to make an Audit Trail entry each time a user
 logs on -- that is connects with The Major BBS and is
 recognized?

LONAUD {Make Audit Trail entry for each Log-on? YES} B

 The Audit trail is a database that records important events
 on The Major BBS.  The last seven entries in the audit
 trail appear on the Sysop console.  The entire audit trail
 database may be viewed by selecting (9) from the introduc-
 tory menu of The Major BBS.

 Do you wish to make an Audit Trail entry each time a user
 logs off -- that is, when a user's session ends due to:
 exiting from the main menu, excess profanity, or simply
 hanging up the phone line?

LOFAUD {Make Audit Trail entry for each Log-off? YES} B


TNLMAX {Maximum number of telnet lines occupied? 15} N 1 32767

BBSRST {Minimum time between bbs restarts (hours, 0=disable)? 12} N 0 9999


PSWEXP {Passwords expire after how many days (0=disable)? 0} N 0 360

PAGEKEY {Key required to allow paging of other users? 0} N 0 129

PGOVKEY {Key required to override page restrictions? 8} N 0 129

PALLKEY {Key required for access to /p all command? 7} N 0 129

 This parameter controls the default setting of the value
 controlled by the PAGE command.  PAGE ON means that the
 user can receive pages, but no more often than once every
 so often (as controlled by config parameter PAGINT above).
 PAGE OFF means the user cannot be paged at all.  PAGE OK
 means that the user can be paged with wild abandon, free
 of any waiting-time restrictions.

DFTPOP {Initial page-enable status at user signup STORE} E STORE OK ON OFF

DFTPTM {Initial time between pages, when in ON status (mins) 2} N 0 9


 é £§¦¨å« ¤ ¤¨¦§¦ ã©« «¤ ¬¤«æ««
 ¤ §å¨¤  ¦ ®¨ã©«ª cookies ¤á §á© ©« £ã
 £ «¤ global ¤«¦¢ã /cookie.         (¢â¥ª)

GLOCKIE {Have a Cookie whenever /cookie issued? YES} B


KGDNAM {Key required to show NAME field in DETAIL INFO: 0} N 0 129

KGDCOM {Key required to show COMPANY field in DETAIL INFO: 0} N 0 129

KGDADR {Key required to show ADDRESS field in DETAIL INFO: 0} N 0 129

KGDPHO {Key required to show PHONE field in DETAIL INFO: 13} N 0 129

KGDAGE {Key required to show AGE field in DETAIL INFO: 0} N 0 129

KGDSEX {Key required to show SEX field in DETAIL INFO: 0} N 0 129

KGDPSS {Key required to show PASSWORD field in DETAIL INFO: 129} N 0 129

KGDPASS {Hide passwords from DETAIL VIEW, regardless of key? YES} B



LEVEL3 {}

W2CLR { â©« â¤ §¢ã¡«¨¦   ©¬¤â® .} T Press any key to clear screen

PAUSE {(N)onstop, (Q)uit, (C)ontinue, (S)tep? } T Nonstop, Quit, Continue, or Step?

NOCREDS {[0;35;1m***

!J¬¤é£   «¤ ¤æ®¢©, ¢¢á ¦ ®¨æ¤¦ª ©ª ©«¤ [1;5;33m@BBS@[0;1;35m
â­«© ©®æ¤ ©«¦ «â¢¦ª «¦¬.  â¤ ¢§«æ  §¦©¬¤å« ¬«æ£«,
 '¬«æ «¢ é©« « ª ¨©åª ©ª £â© © ¬«æ «¦  á©«£.
¬®¨ ©«¦ç£.!)
[0;1m
} T No more credits, user will be kicked out in one minute


NOCRDBYE {[0;1;31m[K***
[K
[K
[K ®¨æ¤¦ª ®¨ã©ª ©ª «¢åà©.[0;1m
[K
[K[36m Acrobase ¥ ¦§¦ å «¤ §¨¦©­¦¨á ©ª ©« Clubs, « £¤ç£« ©ª ã «
[Ká¨¨ ©ª £§¦¨¦ç¤ ¤ §¦æ©¦¬¤ ¨¡«æ à¨á¤ ®¨æ¤¦ ®¨ã©àª.
[K
[K[37mª ¬®¨ ©«¦ç£ §¦¬ ¡¢â©«.
[K
[K
[K
[K
[K[0;40;30;8m
} T No credits, bye bye


NOCTIM {[0;35;1m***

!J¬¤é£   «¤ ¤æ®¢©, ¢¢á «¦ ®¨¦¤ ¡æ æ¨ ¦ §¦¬ ©ª â«   [1;5;33m@BBS@[0;1;35m
© ¡á ¡¢ã© â­«© ©®æ¤ ©«¦ «â¢¦ª «¦¬.  â¤ ¢§«æ  §¦©¬¤å«
¬«æ£«,  '¬«æ «¢ é©« « ª ¨©åª ©ª £â© © ¬«æ «¦  á©«£.
¬®¨ ©«¦ç£.!)
[0;1m
} T No more time for this call, user will be kicked out in one minute


NOCTIMBYE {[0;1;31m[K***
[K
[K
[K§¨á©« «¦ ®¨¦¤ ¡æ ©ª æ¨ ¦ ¤á ¡¢ã©.[0;1m
[K
[K[36m Acrobase ¥ ¦§¦ å «¤ §¨¦©­¦¨á ©ª ©« Clubs, « £¤ç£« ©ª ã «
[Ká¨¨ ©ª £§¦¨¦ç¤ ¤ §¦æ©¦¬¤ ¨¡«æ à¨á¤ ®¨æ¤¦ ®¨ã©àª.
[K
[K[37mª ¬®¨ ©«¦ç£ §¦¬ ¡¢â©«.
[K
[K
[K
[K
[K[0;40;30;8m
} T No more time for this call, bye bye


NODTIM {[0;35;1m***

!J¬¤é£   «¤ ¤æ®¢©, ¢¢á «¦ £¨ã© ¦ ®¨¦¤ ¡æ æ¨ ¦ §¦¬ ©ª â«  
[1;5;33m@BBS@[0;1;35m â­«© ©®æ¤ ©«¦ «â¢¦ª «¦¬.  â¤ ¢§«æ  §¦©¬¤å«
¬«æ£«,  '¬«æ «¢ é©« « ª ¨©åª ©ª £â© © ¬«æ «¦  á©«£.
¬®¨ ©«¦ç£.!)
[0;1m
} T No more time today, user will be kicked out in one minute


NODTIMBYE {[0;1;31m[K***
[K
[K
[K§¨á©« «¦ £¨ã© ¦ ®¨¦¤ ¡æ ©ª æ¨ ¦.[0;1m
[K
[K[36m Acrobase ¥ ¦§¦ å «¤ §¨¦©­¦¨á ©ª ©« Clubs, « £¤ç£« ©ª ã «
[Ká¨¨ ©ª £§¦¨¦ç¤ ¤ §¦æ©¦¬¤ ¨¡«æ à¨á¤ ®¨æ¤¦ ®¨ã©àª.
[K
[K[37mª ¬®¨ ©«¦ç£ §¦¬ ¡¢â©«.
[K
[K
[K
[K
[K[0;40;30;8m
} T No more time today, bye bye


IDLEWRN {[0;1;31m***

¨£å¤« ¤¤¨æª   §¨ ©©æ«¨¦ §æ %d ¢§«á.
[5m*****   ,         ***** [0;1m

} T One-minute warning to inactivity logoff


IDLEBYE {[0;1;31m[K***
[K
[K
[K¨£å¤« ¤¤¨æª   £á¢¦ ®¨¦¤ ¡æ  á©«£.
[K ©ç¤©ã ©ª  ¡æ§««    ¤ £¤ ¥¦ç« á ¡ ®¨æ¤¦ ®¨ã©ª.
[K¨¡¢é ¥¤¡¢â©« æ§¦« â¢«.
[K
[K[33;m¬®¨ ©«¦ç£.[0;30;40;8m
[K
[K
} T Inactivity logoff message


SHTDW1 {[0;1;36m[K***

!J @BBS@  «¨£«å©  «¤ ¢ «¦¬¨å «ª ©« ª [37m%02d:%02d[36m.
¨¡¢¦ç£ §¨¦©§ã©« ¤ â®« «¢ é©  « ª ¨©åª ©ª £â®¨  «æ«.!)

[0;1m} T BBS Shutdown, warning type 1


SHTDW2 {[0;1;36m[K***

!J @BBS@  «¨£«å©  «¤ ¢ «¦¬¨å «ª © [37m%d[36m ¢§«%s.
¨¡¢¦ç£ §¨¦©§ã©« ¤ â®« «¢ é©  « ª ¨©åª ©ª £â®¨  «æ«.!)

[0;1m} T BBS Shutdown, warning type 2


SHTDW3 {[0;1;31m[K***

[5mÛÛ[0;1;31m  : !J!13i @BBS@  «¨£«å©  «¤ ¢ «¦¬¨å «ª
© [37m%d[31m ¢§«%s. ¨¡¢¦ç£ «¢ é©« « ª ¨©åª ©ª ¡ 
§¦©¬¤å«.!)
!0l
[0;1m} T BBS Shutdown, warning type 3

LNCHGW1 {[0;1;36m[K***

!J @BBS@  ®¨ ©«å « ¨££ã ©«¤ ¦§¦å ¨å©¡©« ©« ª [37m%02d:%02d[36m.
¨¡¢¦ç£ §¨¦©§ã©« ¤ â®« «¢ é©  « ª ¨©åª ©ª £â®¨  «æ«,
ã ¤ â®« ©¬¤å ©  ­¦¨« ¡ã ¨££ã.!)

[0;1m} T BBS Line change, warning type 1


LNCHGW2 {[0;1;36m[K***

!J @BBS@  ®¨ ©«å « ¨££ã ©«¤ ¦§¦å ¨å©¡©« © [37m%d[36m ¢§«%s.
¨¡¢¦ç£ §¨¦©§ã©« ¤ â®« «¢ é©  « ª ¨©åª ©ª £â®¨  «æ«,
ã ¤ â®« ©¬¤å ©  ­¦¨« ¡ã ¨££ã.!)

[0;1m} T BBS Line change, warning type 2


LNCHGW3 {[0;1;31m[K***

[5mÛÛ[0;1;31m  : !J!13i @BBS@  ®¨ ©«å «¤ ¨££ã ©ª
© [37m%d[31m ¢§«%s. ¨¡¢¦ç£ «¢ é©« « ª ¨©åª ©ª ¡ 
§¦©¬¤å«.!)
!0l
[0;1m} T BBS Line change, warning type 3




DTCJAN {¤¦¬¨å¦¬} S 20 Month names: January
DTCFEB {¨¦¬¨å¦¬} S 20 Month names: February
DTCMAR {¨«å¦¬} S 20 Month names: March
DTCAPR {§¨ ¢å¦¬} S 20 Month names: April
DTCMAY {ä¦¬} S 20 Month names: May
DTCJUN {¦¬¤å¦¬} S 20 Month names: June
DTCJUL {¦¬¢å¦¬} S 20 Month names: July
DTCAUG {¬¦ç©«¦¬} S 20 Month names: August
DTCSEP {§«£¨å¦¬} S 20 Month names: September
DTCOCT {¡«à¨å¦¬} S 20 Month names: October
DTCNOV {¦£¨å¦¬} S 20 Month names: November
DTCDEC {¡£¨å¦¬} S 20 Month names: December

TIME {[0;1m
 ©£¨ ¤ã £¨¦£¤å å¤  [32m%u %s, %u.[37m
 é¨ å¤  [32m%s.[37m
} T Global time display (/TIME, /T)



WHOHDR {[0;1m
               BAUD      
!FÄ
} T Global 'who' header


WHOLINE1 { %02x      %-10s       %6s
} T Global 'who' no-user line


WHOLINE2 { %02x       %-10s      %6s  %c%c  %s
} T Global 'who' user line


WHOLON {(ç¤©)} T Global 'who' logon


WHOSUP {(¨­ã)} T Global 'who' signup


WHONIX {(Unix)} T Global 'who' unix connection


INVON {[0;1m
¦ invisible mode «¦¬ sysop ¤¨¦§¦ ã¡.
} T You are now invisible


INVOFF {[0;1m
¦ invisible mode «¦¬ sysop §¤¨¦§¦ ã¡.
} T You are now visible


AUDINJI {[0;1;32m
***
AUDIT TRAIL: !i!W%s %s!)
!0l             !i!W%s!)
!0l[0;1m} T Audit trail injoth message for sysops, 'info' severity


AUDINJC {[0;1;33m
***
! AUDIT TRAIL: !i!W%s %s!)
!0l                      !i!W%s!)
!0l[0;1m} T Audit trail injoth message for sysops, 'caution' severity


AUDINJE {[0;1;31m
***
[5m!!![0;1;31m AUDIT TRAIL: !i!W%s %s!)
!0l                        !i!W%s!)
!0l[0;1m} T Audit trail injoth message for sysops, 'emergency' severity


CRDSING {} T Credits, singular form
CRDPLUR {s} T Credits, plural form

MINSING {æ} T Minutes, singular form
MINPLUR {á} T Minutes, plural form


CRDAVAIL {
[0;1;32m®« ©¬¤å é ¡  [37m%d[32m ¢§«%s.
®« ¡æ£ [37m%d[32m credit%s.
[0;1m} T Global /$ command output


CANTPG {[0;1;31m
!J¬¤é£, «¦ §å§¦ §¨æ©©ãª ©ª ¤ ©ª § «¨â§  ¤ ¡¢â©«
á¢¢¦¬ª ®¨ã©«ª.!)
[0;1m} T Page: Your access level disallows paging


PAGFMT {[0;1m
¬¤«âª §¨á£«¨¦  «ª ¤«¦¢ãª /P å¤ :

[33m/P <¬é¤¬£¦>             [37m¢ã© ®¨ã©« ©«¦ ¡¤á¢  ©ª.
[33m/P <¬é¤¬£¦> <¡å£¤¦>   [37m¢ã© ®¨ã©« ¢â¦¤«ª ¡  <¡å£¤¦>.
[33m/P OFF                     [37m§æ¨¬© ©«¦¬ª á¢¢¦¬ª ¤ ©ª ¡¢¦ç¤.
[33m/P ON                      [37m¨© §æ¨¬©ª ¡¢ã©ª.
[33m/P OK                      [37m¨¦«¨¦§ã ¤ ©ª ¡¢¦ç¤ æ§¦« â¢¦¬¤.
[33m/P STORE                   [37m  ¡¢ã© ª §¨¦ª ©áª §¦¡ç¦¤«  ¤
                           ¤ £§¦¨å« ¤ ¤¦®¢å«, ¡  ©ª
                           £«å¦¤«  ¨æ«¨.
[0;1m} T Page: Help


PAGTON {[0;1;36m
!J  á¢¢¦  ®¨ã©«ª  £§¦¨¦ç¤ ¤ ©ª ¡¢¦ç¤ ã ¤
«¦ç¤ §¨¦©à§ ¡ã ©¬¤¦£ ¢å £å ©ª, ¢¢á æ®  ©¬®¤æ«¨ §æ ¡á %d ¢§«%s.[0;1m!)
} T Page: confirmation of /P ON


PAGTOF {
!J[0;1;36m  á¢¢¦  ®¨ã©«ª ¤  £§¦¨¦ç¤ ¤ ©ª ¡¢¦ç¤
ã ¤ «¦ç¤ §¨¦©à§ ¡âª ©¬¤¦£ ¢åª £å ©ª.[0;1m!)
} T Page: confirmation of /P OFF


PAGTOK {
[0;1;36m!J  á¢¢¦  ®¨ã©«ª  £§¦¨¦ç¤ ¤ ©ª ¡¢¦ç¤ ¡  ¤ «¦ç¤
§¨¦©à§ ¡âª ©¬¤¦£ ¢åª £å ©ª [5m®à¨åª[0;1m æ¨ .[0;1m!)
} T Page: confirmation of /P OK


PAGTST {
[0;1;36m!J  ¡¢ã© ª «à¤ á¢¢à¤ ®¨©«é¤ §¨¦ª ©áª  §¦¡ç¦¤« 
æ«¤ ¤ £§¦¨å« ¤ ¤¦®¢å«, ¡   ©ª £«å¦¤«  ¨æ«¨.[0;1m!)
} T Page: confirmation of /P STORE


PAGNON {
[0;1;31m!J¬¤é£, «¦ £â¢¦ª %s ¤ å¤  ©¬¤£â¤¦
¬«ã « ©« £ã.[0;1m!)
} T Page: user not logged on


PAGMOM {
[0;1;31m!J¦ "%s" « ¨ á  © §á¤à §æ â¤ ¯¬é¤¬£¦.[0;1m!)
} T Page: more than one users match


SEXM {} T Masculine definite article, if needed

SEXF {} T Feminine definite article, if needed


PAGOFF {
[0;1;31m!J¬¤é£, %s %s â®  §¦¨ç©  « ª
¡¢ã© ª.[0;1m!)
} T Page: rebuffing a page of someone with /P OFF


PAGL2M {
[0;1;33m!J%s %s â®  ã ¡¢å ©«
«¢¬«å %d ¢§«%s.[0;1m!)
} T Page: rebuffing a page of someone too often


URINVS {
[0;1;31m!J  æ¨«¦  ¤ £ ¢á¤ © ¡¦ ¤¦çª ¤«¦çª!
 «¦¤ «¨¦£á¥ ª «¦¤ á¤¨à§¦!!)[0;1m
} T Page: can't page a user when invisible


PAGMSG1 {[0;1;32m***
%s %s ©ª ¡á¢© §æ %s, æ©¦ ¤ £§¦¨¦ç©« ¤ ¤¦®¢å«.[0;1m
} T Page: you have been paged, no message


PAGNOT1 {[0;1;32m***
%s %s ©ª ¡á¢© §æ %s, æ©¦ ¤ £§¦¨¦ç©« ¤ ¤¦®¢å«:
!W!0v%s!1v[0;1m!)
} T Page: you have been paged, message included 


PAGMSG2 {[0;1;32m***
%s %s ©ª ¡¢å §æ %s.[0;1m
} T Page: you are being paged, no message


PAGNOT2 {[0;1;32m***
%s %s ©ª ¡¢å §æ %s:
!W!0v%s!1v[0;1m!)
} T Page: you are being paged, message included 


PAGEOK {[0;1;36m¢ã© %s %s...[0;1m
} T Page: confirmation of page to the pager


ACKM {«¦¬} T Masculine prefix for username in PAGEOK
ACKF {«ª} T Feminine prefix for username in PAGEOK


PGSYSOP {[0;1;36m¢ã© «¦¬  ¨ ©«ã ¬©«ã£«¦ª (©«¤ ¡¤«¨ ¡ã ¡¦¤©æ¢)...
[0;1m} T Page: paging the main console


PAGNPS {[0;1;31m!Z!J%s %s ¤ £§¦¨å ¤ ¤¦®¢å ¬«ã « ©« £ã.
¦¡ £á©« © ¢å ¢§«á.[0;1m!)
} T Page: "pagee" can't be paged right now


PAGNPST {[0;1;31m!Z!J%s %s ¤ £§¦¨å ¤ ¤¦®¢å ¬«ã « ©« £ã.
 ¡¢ã© ©ª §¦¡ç¡ ¡   £«¦å «¦ ©¬¤«¦£æ«¨¦ ¬¤«æ¤.[0;1m!)
} T Page: "pagee" can't be paged right now, page stored


PAGSTOK {[0;1;32m***
%s %s £æ¢ ª â¢ «¤ ¡¢ã© ©ª.
} T Page: your previously stored page was delivered.


NOMM {} T Masculine definite article for PAGNPST
NOMF {} T Feminine definite article for PAGNPST


PALLNC {
[0;1;31mæ¤¦ª ©¦¬ å©  ©«¤ á©, ¨ ®¨ «à£â¤.[0;1m
} T Page: page all rebuff, didn't page any users


CHATBEG {

[0;1må©¦¦ª © ©¬¤¦£ ¢å £ «¦¤ ® ¨ ©«ã ©¬©«ã£«¦ª...[0m

} T Entering sysop chat mode


CHATEND {
[0;1mâ¢¦ª ©¬¤¦£ ¢åª, § ©«¨¦­ã ©«¦ ©ç©«£...[0m
} T Leaving sysop chat mode


GCOOKIE {
[33;1mÄÄ[37m  á¨« â¤ cookie![33m  !FÄ
[0m} T Cookie header text


  ¬«æ å¤  «¦ £ã¤¬£ §¦¬  §å¨¤  ¦ ®¨ã©«ª £«á
  §æ «¦ global cookie.                    (¢â¥ª)

GCKIEEND {!L!1r[1;33m!FÄ[0m
} T Cookie footer text


COOKIE {
[0;36mÛÛ  [37;1m     [46m[K[80C[0m
[1;33m
} T Cookie header text


CKIELN1 {%s} T Cookie quotation line


CKIELN2 {!40r!R- %s!)} T Cookie person line


CKIEEND {!L!1r
[46m[K[80C[0m
} T Cookie footer text


UXRF1 {[0;1;33m
¦ "[37m%s[33m" « ¨ á  © á¤à «¦¬ ¤æª ¯¬à¤ç£¦¬.
¦ ¦ ¯¬é¤¬£¦ â¢«;

[0;1;33m} T User cross-reference, message 1


UXRF2 {[0;1;33m%2d: [37m%s
} T User cross-reference, menu line


UXRF3 {[0;1m
é©« «¦¤ ¨ £æ «¦¬ ¯¬à¤ç£¦¬ §¦¬ â¢« ([33m%d[37m-[33m%d[37m),
ã «¦ å ¦ «¦ ¯¬é¤¬£¦: [0m} T User cross-reference, prompt


UXRF3A {[0;1m
é©« «¦ ¯¬é¤¬£¦ §¦¬ â¢«: [0m} T User cross-reference, prompt 2


UXRF4 {[0;1;31m
¬«ã  § ¢¦ã ¤ ¬§á¨® .
[0;1m} T User cross-reference, error


UXRF5 {[0;1;31m
¤ £§¦¨é ¤ ¨à ¬«æ «¦ ¯¬é¤¬£¦.
¨¡¢é é©« «¦¬¢á® ©«¦¤ «¨å ¨á££«.
[0;1m} T User cross-reference, user ID does not exist


GDETUR {[0;1;31m
©¡ «©¡ «©¡... ¤ ¬§á¨®  ®¨ã©«ª "%s".
[0;1m} T /L: user not found


GDETNAX {<¤ £­¤å« >} T /L: field contents withheld

GDETSUSP {[31mþSUSPENDEDþ} T /L: 'suspended' string

GDETXMPT {[32mþEXEMPTþ} T /L: 'exempt' string

GDETDEL {[31mþDELETEDþ} T /L: 'deleted' string

GDETOP {[32mþOPERATORþ} T /L: 'operator' string

GDETM {¤¨ª} T /L: 'male' string
GDETF {¬¤å¡} T /L: 'female' string

GDETS1 {IBM PC ã ©¬£«æª} T /L: system #1
GDETS2 {Apple Macintosh} T /L: system #2
GDETS3 {Apple II/II+/IIe, ¡¢§} T /L: system #3
GDETS4 {Amiga} T /L: system #4
GDETS5 {Atari} T /L: system #5
GDETS6 {Archimedes} T /L: system #6
GDETS7 {Amstrad CPC 464/664/6128} T /L: system #7
GDETS8 {¤à©«¦} T /L: system #8
GDETS9 {} T /L: system #9

GDETNST {(®à¨åª §ç© ª)} T /L: 'non-stop' string

GDETL1 {¢¢¤ ¡á} T /L: language #1
GDETL2 {¢ ¡á} T /L: language #2
GDETL3 {} T /L: language #3
GDETL4 {} T /L: language #4
GDETL5 {} T /L: language #5
GDETL6 {} T /L: language #6
GDETL7 {} T /L: language #7
GDETL8 {} T /L: language #8
GDETL9 {} T /L: language #9
GDETL0 {} T /L: language #10


GDET {[0;1m
[0;36mÛÛ  [1m«¦ ®å «¦¬ ¯¬à¤ç£¦¬ %s  [46m[K[0;1m

[32m£ ¦¬¨ã¡ . . . .  [37m%-9s  %s %s
[32m¢¬«å ©ç¤©  . . [37m%-9s  %s %s

[32m¤¦£«§é¤¬£¦ . . . .  [37m%s
[32m« ¨å . . . . . . . [37m%s
[32m ç¬¤© (1/2) . . .  [37m%s
[32m ç¬¤© (2/2)  . . . [37m%s
[32m¢â­à¤¦  . . . . . .  [37m%s
[32m¢ ¡å . . . . . . . . [37m%s
[32mç¢¦ . . . . . . . . . [37m%s
[32m§¦¢¦ ©«ãª . . . . .  [37m%s
[32m ©«á© ª ¦æ¤ª  . . [37m%d x %d %s
[32m¢é©©  . . . . . . .  [37m%s
[32mClass  . . . . . . . . [37m%s
[32mç¤£ . . . . . . .  [37m%s
[32m¦¤áª  . . . . . . . [37m%d (%d PAID àª «é¨)

[46m[K[0;1m
} T /L: template


REMSERR {[0;1;31m
!Jå©  ** ©«¦ ä¡æ £¤¦ç, ®¨ «à£â¤ ©ç©¦§! ©¡ «©¡ «©¡ «©¡ «©¡.!)
[0;1m} T Global Remote Sysop menu: you're already there


CANTGO {[0;31;1m
¬§á£ , ¤ £§¦¨å« ¤ ®¨© £¦§¦ ã©« «¤ ¤«¦¢ã [33m/GO[31m © ¬«æ «¦
©£å¦.
[0;1m} T /GO: Can't use this command at this point


GONAX {[0;31;1m
¬§á£ ,  ©¢å %s ¤ ¬§á¨® .
[0;1m} T /GO: You don't have access to that page



LSTHDR {[0;1;32m
«á¢¦¦ª ¨¦©­á«à¤ ¬¤â©à¤

[37m                     
ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
[0m} T /RECENT [n] list header


LSTLIN {%-10s   %02x    %s, %s - %s  %02d:%02d:%02d
} T /RECENT [n] tabulation


RCFTR {[0;1mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ

¬¤¦¢ ¡âª ©¬¤â© ª: [37m%u
[0;1m} T /RECENT [n] footer


UNKUSR {[0;1;31m
!J¤ ¬§á¨®  ¡«®é¨© §¨¦©­á«à¤ ©¬¤â©à¤ «¦¬ £â¢¦¬ª [37m%s[31m.!)
} T /RECENT <user> rebuff unknown user-id or no log-offs yet


USRHDR {[0;1;32m
!W«á¢¦¦ª ¨¦©­á«à¤ ¬¤â©à¤ «¦¬ £â¢¦¬ª [37m%s[32m.!)

!W¬¤¦¢ ¡âª ©¬¤â© ª: [37m%u!)

                 
ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
[0m} T /RECENT <user> list header


USRLIN {  %02x    %s, %s - %s  %02d:%02d:%02d
} T /RECENT <user> tabulation


URCFTR {[0;1mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ

[0;1m} T /RECENT <user> footer


RCNTHLP {[0;1m
[1;47;37m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;30;47m¿ [40m
[1;47;37m ³[0;34;47m  Recent[30m: ¨¦¬© á  «¦¬ª «¢¬«å¦¬ª ®¨ã©«ª §¦¬ ©¬¤â¡¤         ³ [40m
[1;47;37m ³[0;30;47m          ©«¤ á© ã « ª «¢¬«åª ©¬¤â© ª ¤æª ®¨ã©«.           ³ [40m
[1;47;37m ³[0;30;47m                                                                      ³ [40m
[1;47;37m ³[0;34;47m  /Recent         [30m å®¤  « ª «¢¬«åª ©¬¤â© ª.                  ³ [40m
[1;47;37m ³[0;34;47m  /RC             [30m ¬¤«¦£¦¨­å «¦¬ /Recent.                         ³ [40m
[1;47;37m ³[0;34;47m  /Recent n       [30m å®¤  « ª «¢¬«åª n ©¬¤â© ª.                ³ [40m
[1;47;37m ³[0;34;47m  /Recent user    [30m å®¤  « ª «¢¬«åª ©¬¤â© ª «¦¬ ®¨ã©« user.  ³ [40m
[1;47;37m ³[0;34;47m  /Recent help    [30m £­¤å  ¬«ã «¤ ©¢å.                         ³ [40m
[1;47;37m À[0;30;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [40m
[0;1m} T /RECENT n rebuff n is off limits


AUDITHLP {[0;1m
!J «¤ ¤«¦¢ã /audit £§¦¨å« ¤ ¦¨å©« ¤  ¢â§« « ª ¡«®à¨ã© ª
«¦¬ audit trail ¡  ¤ ¤ , §¦ ª §'¬«âª.  ©ç¤«¥ «ª ¤«¦¢ãª â®  àª
¥ãª:!)

[33m/audit[37m  . . . . . .  ¦ã  («¤ ¢â§« «é¨).
[33m/audit off[37m . . . . . ¤  ¢â§« ¡££å ¡«®é¨©.
[33m/audit e[37m  . . . . .  §å¦¬©ª ¡«®à¨ã© ª £æ¤¦.
[33m/audit emergency[37m . . ¦ å ¦.
[33m/audit c[37m  . . . . .  £¤« ¡âª ¡  §å¦¬©ª ¡«®à¨ã© ª.
[33m/audit caution[37m . . . ¦ å ¦.
[33m/audit i[37m  . . . . .  ¢ª ¦  ¡«®à¨ã© ª (§¢¨¦­¦¨ ¡âª,
[33m/audit info[37m  . . . . ©£¤« ¡âª ¡  §å¦¬©ª)

!J  §¨ ©©æ«¨ª ¬¤«æ««ª, é©« «¤ ¤«¦¢ã AUDITPAGE §æ «¦ £¤¦ç
«à¤  ¨ ©«é¤ ¬©«ã£«¦ª!).
[0;1m} T /AUDIT, help


AUDITOFF {[0;1m
!J  «¦ ¬§æ¢¦ §¦ ¬«ãª «ª ©ç¤©ª   ¢£á¤«
« ª ¡«®à¨ã© ª «¦¬ audit trail.!)
[0;1m} T /AUDIT is off


AUDITE {[0;1m
!J  «¦ ¬§æ¢¦ §¦ ¬«ãª «ª ©ç¤©ª  ¢£á¤« £æ¤¦ « ª §å¦¬©ª
¡«®à¨ã© ª «¦¬ audit trail.!)
[0;1m} T /AUDIT is set to emergencies only


AUDITC {[0;1m
!J  «¦ ¬§æ¢¦ §¦ ¬«ãª «ª ©ç¤©ª  ¢£á¤« « ª ©£¤« ¡âª ¡ 
§å¦¬©ª ¡«®à¨ã© ª «¦¬ ¡«®à¨ã© ª «¦¬ audit trail.!)
[0;1m} T /AUDIT is set to emergencies only


AUDITI {[0;1m
!J  «¦ ¬§æ¢¦ §¦ ¬«ãª «ª ©ç¤©ª  ¢£á¤« æ¢ª « ª ¡«®à¨ã© ª
«¦¬ audit trail.!)
[0;1m} T /AUDIT is set to all entries



LANG {}


W2CLR {Press any key to continue.} T Press any key to clear screen

PAUSE {(N)onstop, (Q)uit, (C)ontinue, (S)tep? } T Nonstop, Quit, Continue, or Step?

NOCREDS {[0;35;1m***

!JWe're sorry for the inconvenience, but your time in [1;5;33m@BBS@[0;1;35m
is almost at its end. In one minute you will be automatically disconnected,
so, please, finish up in that interval. Thank you.!)
[0;1m
} T No more credits, user will be kicked out in one minute


NOCRDBYE {[0;1;31m[K***
[K
[K
[KSorry, you ran out of time.[0;1m
[K
[K[36mAcrobase appreciates contributions to its Clubs; messages or
[Karticles may provide you with a lot of credits.
[K
[K[37mThank you for calling.
[K
[K
[K
[K
[K[0;40;30;8m
} T No credits, bye bye


NOCTIM {[0;35;1m***

!JWe're sorry for the inconvenience, but you have almost reached your time limit
for this call. In one minute you will be automatically disconnected, so,
please, finish up in that interval. Thank you.!)
[0;1m
} T No more time for this call, user will be kicked out in one minute


NOCTIMBYE {[0;1;31m[K***
[K
[K
[KYou have reached your time limit for this call.[0;1m
[K
[K[36mAcrobase appreciates contributions to its Clubs; messages or
[Karticles may provide you with a lot of credits.
[K
[K[37mThank you for calling.
[K
[K
[K
[K
[K[0;40;30;8m
} T No more time for this call, bye bye


NODTIM {[0;35;1m***

!JWe're sorry for the inconvenience, but you have almost reached your daily
on-line time limit. In one minute you will be automatically disconnected,
so, please, finish up in that interval. Thank you.!)
[0;1m
} T No more time today, user will be kicked out in one minute


NODTIMBYE {[0;1;31m[K***
[K
[K
[KYou have reached your daily time limit.[0;1m
[K
[K[36mAcrobase appreciates contributions to its Clubs; messages or
[Karticles may provide you with a lot of credits.
[K
[K[37mThank you for calling.
[K
[K
[K
[K
[K[0;40;30;8m
} T No more time today, bye bye


IDLEWRN {[0;1;31m***

You have remained idle for more than %d minutes.
[5m***** IF YOU REMAIN IDLE, YOU WILL BE DISCONNECTED IN ONE MINUTE. ***** [0;1m

} T One-minute warning to inactivity logoff


IDLEBYE {[0;1;31m[K***
[K
[K
[KYou have been idle for far too long.
[KYour connection has been terminated so you won't spend any more credits.
[KPlease call back whenever you wish.
[K
[K[33;mThank you.[0;30;40;8m
[K
[K
} T Inactivity logoff message


SHTDW1 {[0;1;36m[K***

!J@BBS@ will shut down at [37m%02d:%02d[36m. Please try to have finished
your session by then.!)

[0;1m} T BBS Shutdown, warning type 1


SHTDW2 {[0;1;36m[K***

!J@BBS@ will shut down in [37m%d[36m minute%s.
Please try to have finished your session by then.!)

[0;1m} T BBS Shutdown, warning type 2


SHTDW3 {[0;1;31m[K***

[5mÛÛ[0;1;31m  WARNING: !J!13i@BBS@ will shut down in [37m%d[31m minute%s.
Please finish up and exit the system.!)
!0l
[0;1m} T BBS Shutdown, warning type 3


LNCHGW1 {[0;1;36m[K***

!JSorry for the interruption. At [37m%02d:%02d[36m, @BBS@ will need
the line you're currently using. The line will be disconnected at that time.
Feel free to use another line. We apologise for the inconvenience.!)

[0;1m} T BBS Line change, warning type 1


LNCHGW2 {[0;1;36m[K***

!JIn [37m%d[36m minute%s, @BBS@ will need to use the line you're on.
Please try to have finished by that time. Feel free to connect to
another line. We apologise for the inconvenience.!)

[0;1m} T BBS Line change, warning type 2


LNCHGW3 {[0;1;31m[K***

[5mÛÛ[0;1;31m  ATTENTION: !J!13i@BBS@ needs your line
and will terminate your connection in [37m%d[31m minute%s.
Please wrap up and disconnect, or connect to another line. We apologise for
the inconvenience.!)
!0l
[0;1m} T BBS Line change, warning type 3




DTCJAN {January} S 20 Month names: January
DTCFEB {February} S 20 Month names: February
DTCMAR {March} S 20 Month names: March
DTCAPR {April} S 20 Month names: April
DTCMAY {May} S 20 Month names: May
DTCJUN {June} S 20 Month names: June
DTCJUL {July} S 20 Month names: July
DTCAUG {August} S 20 Month names: August
DTCSEP {September} S 20 Month names: September
DTCOCT {October} S 20 Month names: October
DTCNOV {November} S 20 Month names: November
DTCDEC {December} S 20 Month names: December

TIME {[0;1m
Today's date is [32m%u %s, %u.[37m
The time is [32m%s.[37m
} T Global time display (/TIME, /T)


WHOHDR {[0;1m
LINE      USER               SPEED     AREA
!FÄ
} T Global 'who' header


WHOLINE1 { %02x      %-10s       %6s
} T Global 'who' no-user line


WHOLINE2 { %02x       %-10s      %6s  %c%c  %s
} T Global 'who' user line


WHOLON {(Logging in)} T Global 'who' logon


WHOSUP {(Signing up)} T Global 'who' signup


WHONIX {(Unix)} T Global 'who' unix connection


INVON {[0;1m
Sysop invisibility mode activated.
} T You are now invisible


INVOFF {[0;1m
Sysop invisibility mode deactivated.
} T You are now visible


AUDINJI {[0;1;32m
***
AUDIT TRAIL: !i!W%s %s!)
!0l             !i!W%s!)
!0l[0;1m} T Audit trail injoth message for sysops, 'info' severity


AUDINJC {[0;1;33m
***
CAUTION! AUDIT TRAIL: !i!W%s %s!)
!0l                      !i!W%s!)
!0l[0;1m} T Audit trail injoth message for sysops, 'caution' severity


AUDINJE {[0;1;31m
***
[5mEMERGENCY!!![0;1;31m AUDIT TRAIL: !i!W%s %s!)
!0l                          !i!W%s!)
!0l[0;1m} T Audit trail injoth message for sysops, 'emergency' severity


CRDSING {} T Credits, singular form
CRDPLUR {s} T Credits, plural form

MINSING {} T Minutes, singular form
MINPLUR {s} T Minutes, plural form


CRDAVAIL {
[0;1;32mYou have been online for the last [37m%d[32m minute%s.
You have [37m%d[32m credit%s left.
[0;1m} T Global /$ command output


CANTPG {[0;1;31m
!JI'm sorry, your access level does not permit paging users.!)
[0;1m} T Page: Your access level disallows paging


PAGFMT {[0;1m
Possible parameters for the /P command are:

[33m/P <user>                  [37mPage <user> to your channel
[33m/P <user> <text>           [37mPage <user>, relaying <text>
[33m/P OFF                     [37mStop other people from paging you
[33m/P ON                      [37mAllow pages to you
[33m/P OK                      [37mAllow pages to you without limits
[33m/P STORE                   [37mPages to you will be stored when
                             you are busy; they will be transmitted
                             as soon as you are available for paging.
[0;1m} T Page: Help


PAGTON {[0;1;36m
!JOther users will be able to page you and request chats with you,
but only every %d minute%s.[0;1m!)
} T Page: confirmation of /P ON


PAGTOF {
!J[0;1;36mOther users will not be able to page you or request chats.
[0;1m!)
} T Page: confirmation of /P OFF


PAGTOK {
[0;1;36m!JOther users will be able to page you and request chats with you,
[5mwithout[0;1m limits.[0;1m!)
} T Page: confirmation of /P OK


PAGTST {
[0;1;36m!JOther users' pages will be stored when you are not available
for paging, and transmitted to you as soon as you become available.[0;1m!)
} T Page: confirmation of /P STORE


PAGNON {
[0;1;31m!JSorry, %s is not connected right now.[0;1m!)
} T Page: user not logged on


PAGMOM {
[0;1;31m!JShortcut "%s" matches more than one user.[0;1m!)
} T Page: more than one users match


SEXM {} T Masculine definite article, if needed

SEXF {} T Feminine definite article, if needed


PAGOFF {
[0;1;31m!JSorry, %s%s has disallowed paging.[0;1m!)
} T Page: rebuffing a page of someone with /P OFF


PAGL2M {
[0;1;33m!J%s%s has already been paged in the last %d minute%s.[0;1m!)
} T Page: rebuffing a page of someone too often


URINVS {
[0;1;31m!JYou're invisible! You can't talk to mere mortals,
you'll scare them off!!)[0;1m
} T Page: can't page a user when invisible


PAGMSG1 {[0;1;32m***
%s%s paged you from %s, while you were busy.[0;1m
} T Page: you have been paged, no message


PAGNOT1 {[0;1;32m***
%s%s paged you from %s, while you were busy:
!W!0v%s!1v[0;1m!)
} T Page: you have been paged, message included 


PAGMSG2 {[0;1;32m***
%s%s is paging you from %s.[0;1m
} T Page: you are being paged, no message


PAGNOT2 {[0;1;32m***
%s%s is paging you from %s:
!W!0v%s!1v[0;1m!)
} T Page: you are being paged, message included 


PAGEOK {[0;1;36mPaging %s%s...[0;1m
} T Page: confirmation of page to the pager


ACKM {} T Masculine prefix for username in PAGEOK
ACKF {} T Feminine prefix for username in PAGEOK


PGSYSOP {[0;1;36mPaging the sysop (at the main console)...
[0;1m} T Page: paging the main console


PAGNPS {[0;1;31m!Z!J%s%s is not available for paging right now. Try again
later.[0;1m!)
} T Page: "pagee" can't be paged right now


PAGNPST {[0;1;31m!Z!J%s%s is not available for paging right now. Your
message has been stored and will be transmitted as soon as possible.[0;1m!)
} T Page: "pagee" can't be paged right now, page stored


PAGSTOK {[0;1;32m***
%s%s has just received your previously stored page.
} T Page: your previously stored page was delivered.


NOMM {} T Masculine definite article for PAGNPST
NOMF {} T Feminine definite article for PAGNPST


PALLNC {
[0;1;31mYou are alone in the system![0;1m
} T Page: page all rebuff, didn't page any users


CHATBEG {

[0;1mSysop chat mode activated...[0m

} T Entering sysop chat mode


CHATEND {
[0;1mEnd of sysop chat, back to the system...[0m
} T Leaving sysop chat mode



GCOOKIE {
[33;1mÄÄ[37m  Have a cookie![33m  !FÄ
[0m} T Cookie header text


GCKIEEND {!L!1r[1;33m!FÄ[0m
} T Cookie footer text


COOKIE {
[0;36mÛÛ  [37;1mQUOTE OF THE DAY  [46m[K[80C[0m
[1;33m
} T Cookie header text


CKIELN1 {%s} T Cookie quotation line


CKIELN2 {!40r!R- %s!)} T Cookie person line


CKIEEND {!L!1r
[46m[K[80C[0m
} T Cookie footer text


UXRF1 {[0;1;33m
The string "[37m%s[33m" matches more than one user.
Which one would you like?

[0;1;33m} T User cross-reference, message 1


UXRF2 {[0;1;33m%2d: [37m%s
} T User cross-reference, menu line


UXRF3 {[0;1m
Enter the number of a user-ID ([33m%d[37m-[33m%d[37m),
or type in a user-ID: [0m} T User cross-reference, prompt


UXRF3A {[0;1m
Type in a user-ID: [0m} T User cross-reference, prompt 2


UXRF4 {[0;1;31m
I'm sorry, that is not an option.
[0;1m} T User cross-reference, error


UXRF5 {[0;1;31m
Unable to find this user-ID. Please type in at least three letters.
[0;1m} T User cross-reference, user ID does not exist




GDETUR {[0;1;31m
Ahem... There's no such user as "%s".
[0;1m} T /L: user not found


GDETNAX {<Suppressed>} T /L: field contents withheld

GDETSUSP {[31mþSUSPENDEDþ} T /L: 'suspended' string

GDETXMPT {[32mþEXEMPTþ} T /L: 'exempt' string

GDETDEL {[31mþDELETEDþ} T /L: 'deleted' string

GDETOP {[32mþOPERATORþ} T /L: 'operator' string

GDETM {Male} T /L: 'male' string
GDETF {Female} T /L: 'female' string

GDETS1 {IBM PC compatible} T /L: system #1
GDETS2 {Apple Macintosh} T /L: system #2
GDETS3 {Apple II/II+/IIe, ¡¢§} T /L: system #3
GDETS4 {Amiga} T /L: system #4
GDETS5 {Atari} T /L: system #5
GDETS6 {Archimedes} T /L: system #6
GDETS7 {Amstrad CPC 464/664/6128} T /L: system #7
GDETS8 {Unknown} T /L: system #8
GDETS9 {} T /L: system #9

GDETNST {(non-stop)} T /L: 'non-stop' string

GDETL1 {Ellhnika} T /L: language #1
GDETL2 {English} T /L: language #2
GDETL3 {} T /L: language #3
GDETL4 {} T /L: language #4
GDETL5 {} T /L: language #5
GDETL6 {} T /L: language #6
GDETL7 {} T /L: language #7
GDETL8 {} T /L: language #8
GDETL9 {} T /L: language #9
GDETL0 {} T /L: language #10


GDET {[0;1m
[0;36mÛÛ  [1mAccount details for %s  [46m[K[0;1m

[32mCreation date . . . .  [37m%-9s  %s %s
[32mLast connection  . . . [37m%-9s  %s %s

[32mName  . . . . . . . .  [37m%s
[32mCompany  . . . . . . . [37m%s
[32mAddress (1/2) . . . .  [37m%s
[32mAddress (2/2)  . . . . [37m%s
[32mTelephone . . . . . .  [37m%s
[32mAge  . . . . . . . . . [37m%s
[32mSex . . . . . . . . .  [37m%s
[32mComputer type  . . . . [37m%s
[32mScreen size . . . . .  [37m%d x %d %s
[32mLanguage . . . . . . . [37m%s
[32mClass . . . . . . . .  [37m%s
[32mPassword . . . . . . . [37m%s
[32mCredits . . . . . . .  [37m%d (%d PAID)

[46m[K[0;1m
} T /L: template






REMSERR {[0;1;31m
!JYou're *ALREADY* in the Sysop menu!!)
[0;1m} T Global Remote Sysop menu: you're already there


CANTGO {[0;31;1m
Sorry, you can't use [33m/GO[31m at this point.
[0;1m} T /GO: Can't use this command at this point


GONAX {[0;31;1m
Sorry, there is no page by the name of "%s".
[0;1m} T /GO: You don't have access to that page



LSTHDR {[0;1;32m
List of Recent Logins

[37mUSER      CHANNEL  LOGIN                     LOGOUT  DURATION
ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
[0m} T /RECENT [n] list header


LSTLIN {%-10s   %02x    %s, %s - %s  %02d:%02d:%02d
} T /RECENT [n] tabulation


RCFTR {[0;1mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ

Total connections: [37m%u
[0;1m} T /RECENT [n] footer


UNKUSR {[0;1;31m
!JThere is no record of recent logins for [37m%s[31m.!)
} T /RECENT <user> rebuff unknown user-id or no log-offs yet


USRHDR {[0;1;32m
!WList of Recent Logins for [37m%s[32m.!)

!WTotal connections: [37m%u!)

CHANNEL  LOGIN                     LOGOUT  DURATION
ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ
[0m} T /RECENT <user> list header


USRLIN {  %02x     %s, %s - %s  %02d:%02d:%02d
} T /RECENT <user> tabulation


URCFTR {[0;1mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ

[0;1m} T /RECENT <user> footer


RCNTHLP {[0;1m
[1;47;37m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;30;47m¿ [40m
[1;47;37m ³[0;34;47m  Recent[30m: Displays a list of recent connections to the system,        ³ [40m
[1;47;37m ³[0;30;47m          or a list of a user's recent logins.                        ³ [40m
[1;47;37m ³[0;30;47m                                                                      ³ [40m
[1;47;37m ³[0;34;47m  /Recent         [30m Shows all recent connections.                      ³ [40m
[1;47;37m ³[0;34;47m  /RC             [30m Short for /Recent.                                 ³ [40m
[1;47;37m ³[0;34;47m  /Recent n       [30m Displays the last (most recent) n connections.     ³ [40m
[1;47;37m ³[0;34;47m  /Recent user    [30m Displays user's most recent connections.           ³ [40m
[1;47;37m ³[0;34;47m  /Recent help    [30m Shows this page.                                   ³ [40m
[1;47;37m À[0;30;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [40m
[0;1m} T /RECENT n rebuff n is off limits


AUDITHLP {[0;1m
!JWith the /audit command you can control whether you wish to see
audit trail entries globally and, if yes, which ones. The /audit syntax is
as follows:!)

[33m/audit  . . . . . .  [37mHelp (you're seing it now)
[33m/audit off . . . . . [37mNo entries shown.
[33m/audit e  . . . . .  [31mEMERGENCY[37m entries alone.
[33m/audit emergency . . [37mThe same.
[33m/audit c  . . . . .  [33mCautionary[37m and [31mEMERGENCY[37m.
[33m/audit caution . . . [37mThe same.
[33m/audit i  . . . . .  [37mAll entries ([32mInformational[37m, 
[33m/audit info  . . . . [37m  [33mCautionary[37m and [31mEMERGENCY[37m.

!JFor more features, please give the AUDITPAGE command from the Remote
Operator menu.!).
[0;1m} T /AUDIT, help


AUDITOFF {[0;1m
!JAudit trail entries will NOT be sent to you for the rest of this session.!)
[0;1m} T /AUDIT is off


AUDITE {[0;1m
!JOnly emergency audit trail entries will be sent to you for the rest of
this session.!)
[0;1m} T /AUDIT is set to emergencies only


AUDITC {[0;1m
!JOnly emergency and cautionary audit trail entries will be sent to you for
the rest of this session.!)
[0;1m} T /AUDIT is set to emergencies only


AUDITI {[0;1m
!JAll audit trail entries will be sent to you for the remainder of this
session.!)
[0;1m} T /AUDIT is set to all entries



LANGEND {}
