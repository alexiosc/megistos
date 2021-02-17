LEVEL2 {}

SUPZAP {Hangup idle signups after how many minutes? 3} N 0 32767

 If you want a time-and-date-stamped entry in your Audit
 Trail file each time a new account (User-ID) is created,
 answer YES to this question, otherwise answer NO.

SGNAUD {Make Audit Trail entry for each new signup? YES} B

NEWCLSS {DEMO} S 9 Starting user class for new users

INTPAUZ {Seconds to pause after INTRO screen (0=disable)? 5} N 0 1000

WELPAUZ {Seconds to pause after WELCOME screen (0=disable)? 5} N 0 1000

ASKSCR {Ask users the dimensions of their CRT screen? YES} B

 When a user signs up (types "new" in place of logging on
 with a User-Id), do you want to ask them for the name of
 their company?

ASKCOM {Ask users their company name? YES} B

 When a user signs up (types "new" in place of logging on
 with a User-Id), do you want to ask them for the address
 of their company?

ASKADR {Ask users their address (2 lines)? YES} B

 When a user signs up (types "new" in place of logging on
 with a User-Id), do you want to ask them for their
 telephone number?

ASKPHO {Ask users their telephone number? YES} B

 When a user signs up (types "new" in place of logging on
 with a User-Id), do you want to ask them what type of
 computer system they are using?

ASKSYS {Ask users the type of system they are using? YES} B

 When a user signs up (types "new" in place of logging on
 with a User-Id), do you want to ask them how old they are?

ASKAGE {Ask users their age? YES} B

 When a user signs up (types "new" in place of logging on
 with a User-Id), do you want to ask them what sex they are?

ASKSEX {Ask users their sex? YES} B

PRFVIS {Will new users use visual (Full screen) programs? YES} B

MXUIDL {Maximum allowable user ID length? 10} N 3 16

ALWNUM {Allow numbers in User IDs? NO} B

ALWSYM {Allow dashes, underscores and dots in User IDs? NO} B



 Each time a new account is created, the BBS can write an
 E-Mail message to User-ID "Sysop" with the user's sign-up
 accounting data, just as it appears on the account detail
 screen.

 To enable this feature, answer YES to this question.  To
 disable it, answer NO.

SUPU2S {Write E-Mail automatically to Sysop from new users? YES} B

 Each time a new account is created, the BBS can create a
 message to the new user automatically.  Typically the
 message you create will welcome the user to the system,
 and provide some helpful information.  You can optionally
 have an "attachment" to the message, containing whatever
 additional information you may wish to give to the user.


SUPAUTH {/usr/local/bbs/bin/supauth} S 50 Extra signup authentication program


SUPS2U {Write E-Mail automatically to new users from Sysop? YES} B


 The message automatically sent to new users upon account
 creation may optionally have a file "attachment".  This
 means that the user will have the option of downloading
 the file you specify here, after he or she has read the
 new-user message text.   (Only the single copy of the
 file you specify here will exist on your disk, even when
 hundreds of new user messages use it as an attachment.)

 To eliminate any attachment from new-user messages, hit
 the F2 key now.

E2UATT {/usr/local/bbs/doc/newuser.txt} S 50 Attachment to new user E-Mail, if any


E2UNAM {acrobase.txt} S 50 Name of the new user E-Mail attachment


 The message automatically sent to new users upon account
 creation may optionally generate a "return receipt" to
 the Sysop after the user reads the message.

 To enable this feature, answer YES to this question.  To
 disable it, answer NO.

E2URRR {Return receipt when user reads new-user E-Mail? NO} B


LEVEL3 {}


LNGSEL1 {[2J[0;1m
  ˜¡æ¢¦¬Ÿœª š¢é©©œª œå¤˜  › ˜Ÿâ© £œª:
The following languages are available:

} T Language menu, header

LNGSEL2 {%d. %s
} T Language menu, one line of menu

LNGSEL3 {
ƒ ˜¢â¥«œ «¤ š¢é©©˜ §¦¬ œ§ Ÿ¬£œå«œ. ƒé©«œ ? š ˜ «¦ £œ¤¦ç:
Please select your language of choice (%d-%d). Enter ? to see the menu: } T Language menu, prompt.

LNGSLRR {
˜¨˜¡˜¢é ›é©«œ â¤˜¤ ˜¨ Ÿ£æ ©«¦ › á©«£˜ %d-%d.
Please enter a number within the above limits.
} T Language menu, error.


LNGSLOK {
ƒ ˜¢â¥˜«œ «¤ š¢é©©˜ %s. €¤  œ§ ¢¦šã ©˜ª ›œ¤ ©˜ª  ¡˜¤¦§¦ œå, £§¦¨œå«œ
˜¨šæ«œ¨˜ ¤˜ «¤ ˜¢¢á¥œ«œ.

} T Language selected OK.


B4QANS {[2J} T Signup, clear screen (hopefully) before ANSI question


NEWANS {!C[0;1;31m  ÛÛÛ[32m  ÛÛÛ[34m  ÛÛÛ  [37m!)

!J¨¦©§˜Ÿ¦ç£œ ¤˜ ›¦ç£œ ˜¤ «¦ «œ¨£˜« ¡æ ©˜ª ¬§¦©«¨åœ  ANSI š¨˜­ ¡á. €¤
«¦ §¨æš¨˜££˜ œ§ ¡¦ ¤à¤ é¤ ©˜ª › ˜Ÿâ«œ  œ¥¦£¦åà© «œ¨£˜« ¡é¤ (terminal
emulation), «ã©«œ «¤ œ§ ¢¦šã ANSI, VT-102, VT-100, ã VT-52, ¡˜ 
§ â©«œ Y ¡˜  <enter>.!)

!J€¤ «˜ «¨å˜ ¦¨Ÿ¦šé¤ ˜ § ¦ §á¤à œ£­˜¤å¦¤«˜  âš®¨à£˜ ã ©œ › ˜­¦¨œ« ¡¦çª
«æ¤¦¬ª «¦¬ š¡¨å¦¬, ˜§˜¤«ã©«œ £œ Y ©«¤ œ¨é«©. €¢¢ éª, ›é©«œ N.!)

‡â¢œ«œ ANSI š¨˜­ ¡á; ([Y]es=¤˜  / [N]o=æ® ) } T Signup, asking user for new ANSI setting


ANSBERR {
˜¨˜¡˜¢é ˜§˜¤«ã©«œ ©«¤ œ¨é«© £œ Y ã N.

} T Rebuff, wrong answer to ANSI question


 This message is sent to users when they sign up. That is,
 when they type "new" in place of a User-Id. A user is told
 they can do this only when they have connected with a free
 sample channel (see level 2 option "NSAMPLN").

INTRO {[2J[0;1;36m!Z!C           ÜÜ        
ÛÛÛÛÛÛÛÛÛÛ ÛÛ ÛÛÛÛÛÛÛ
ÛÛ      ÛÛ ÛÛ      ÛÛ
ÛÛ      ÛÛ ÛÛ      ÛÛ
ÛÛÛÛÛÛÛ ÛÛ ÛÛÛÛÛÛÛÛÛÛ
        ßß           
[37m‰˜¢à©ã¨Ÿ˜«œ ©«¤ [1m@BBS@[0;1m.
!)

!J‹œ  › ˜å«œ¨ ®˜¨á ©˜ª ¬§¦›œ®æ£˜©«œ ©«¤ £œšá¢ §¦ ¦« ¡ã „¢¢¤ ¡ã œ¨˜© «œ®¤ ¡ã
«¨á§œ˜ §¢¨¦­¦¨ é¤ ¡˜  œ§ ¡¦ ¤à¤å˜ª. „¬®æ£˜©«œ  §¨¦©§áŸœ ˜ £˜ª ¤˜ ©˜ª
˜¨â©œ .!)

!J¨å¤ æ£àª ©¬¤œ®å©¦¬£œ Ÿ˜ Ÿâ¢˜£œ ¡á§¦ ˜ ©«¦ ®œå˜ š ˜ «¦ á«¦£æ ©˜ª š ˜ ¤˜
›£ ¦¬¨šã©¦¬£œ œ¤˜ ¢¦š˜¨ ˜©£æ ©«¦ æ¤¦£á ©˜ª.!)

!J‘«˜ ©«¦ ®œå˜ §¦¬ Ÿ˜ £˜ª ›é©œ«œ «é¨˜ â®¦¬¤ §¨æ©™˜© [5m£æ¤¦[0;1m ¦  •œ ¨ ©«âª
‘¬©«ã£˜«¦ª, ¦  ¦§¦å¦  ¡˜  ›œ©£œç¦¤«˜  ©ç£­à¤˜ £œ «¦ ¡˜«˜©«˜« ¡æ «ª ™á©ª ¤˜ «˜
¡¨˜«ã©¦¬¤ ˜¬©«¨á ˜§æ¨¨«˜. „å¤˜  ˜§˜¨˜å««¦ ¤˜ â®¦¬£œ «˜ [5m˜¢Ÿ ¤á[0;1m ©˜ª
©«¦ ®œå˜ š ˜ ¤˜ £§¦¨œå«œ ¤˜ ©¬¤›œŸœå«œ ©«¤ ™á©. ‘«¤ ˜¤«åŸœ« §œ¨å§«à© Ÿ˜ ™¨œŸ¦ç£œ
©«¤ ›ç©¡¦¢ Ÿâ© ¤˜ ©˜ª › ˜š¨á¯¦¬£œ.!)

} T Introductory message for users when signing up


PAUSE1 {[0;1;32m˜ç© [37m%d[32m ›œ¬«œ¨¦¢â§«à¤... [s} T Pause message (start)

PAUSE2 {[u[0m%02d[30m[K } T Pause message (counting)

PAUSE3 {[0;1;32m[80D[K„¬®˜¨ ©«¦ç£œ š ˜ «¤ ¬§¦£¦¤ã ©˜ª!

} T Pause message (end)


GUSRNAM {[0;1;33m

[A˜¨˜¡˜¢é ›é©«œ «¦ æ¤¦£˜ ¡˜  œ§é¤¬£æ ©˜ª:   [0;47;30m                                 [32D} T Asking a user signing up for their first and last names


GUSRCOM {[0;1;33m
˜¨˜¡˜¢é  ›é©«œ  «¦ æ¤¦£˜  «ª  œ«˜ ¨å˜ª
æ§¦¬  œ¨šáœ©«œ, ã §˜«ã©«œ Enter ˜¤  ›œ¤

[A¬§á¨®œ :                                   [0;47;30m                                 [32D} T Asking a user signing up for their company name


GUSRAD1 {[0;1;33m
ƒé©«œ  «¤ §¨é«  š¨˜££ã «ª  › œçŸ¬¤©ãª

[A©˜ª (¦›æ ¡˜  ˜¨ Ÿ£æ):                      [0;47;30m                                 [32D} T Asking a user signing up for their address (street)


GUSRAD2 {[0;1;33m
ƒé©«œ «¤ ›œç«œ¨  š¨˜££ã «ª › œçŸ¬¤©ãª

[A©˜ª (©¬¤¦ ¡å˜ ¡˜  ’‰):                     [0;47;30m                                 [32D} T Asking a user signing up for their address (city,state,zip)


GUSRPHO {[0;1;33m
ƒé©«œ «¦¤ ˜¨ Ÿ£æ  «¢œ­é¤¦¬ §¦¬ £§¦¨¦ç£œ

[A¤˜ ©˜ª ™¨¦ç£œ:                             [0;47;30m                         [24D} T Asking a user signing up for their telephone number


GUSRAGE {[0;1;33m
‰˜ , ˜¤  ›œ¤ š ¤æ£˜©«œ  ˜› á¡¨ «¦ , §¦ ˜

[Aœå¤˜   ¢ ¡å˜ ©˜ª;                        [0;47;30m    [3D} T Asking a user signing up how old they are


GUSRSEX {[0;1;33m

[A„å©«œ á¤«¨˜ª ã š¬¤˜å¡˜; (ƒé©«œ [[37mM[33m]ale=á¤«¨˜ª ã [[37mF[33m]emale=š¬¤˜å¡˜)  [0;47;30m   [2D} T Asking a user signing up what sex they are


GSCNWID {[0;1;32m

!Jƒ ˜™á©«œ ˜¬«ã «¤ œ¨é«© §¨¦©œ¡« ¡á. €¤ ˜§˜¤«ã©œ«œ ¢˜¤Ÿ˜©£â¤˜, [37m›œ¤ Ÿ˜
£§¦¨œå«œ ¤˜ ›œå«œ ©à©«á ¦¨ ©£â¤œª §œ¨ ¦®âª «ª ™á©ª[32m.!)

!J€¨® ¡á ¢¦ §æ¤ Ÿ˜ Ÿâ¢˜£œ ¤˜ £˜ª §œå«œ §æ©¦¬ª [5;37m®˜¨˜¡«ã¨œª ˜¤˜ š¨˜££ã
(©«ã¢œª)[0;1;32m £§¦¨œå ¤˜ ›œå¥œ   ¦Ÿæ¤ ©˜ª. ˜«ã©«œ [37mEnter[32m š ˜
«¦ ©ç¤Ÿœª §¦¬ œå¤˜  [37m80[32m.!)


[A[33mæ©œª ©«ã¢œª ¡œ £â¤¦¬ œ£­˜¤åœ   ¦Ÿæ¤ ©˜ª; [Enter=80] [0;47;30m     [4D} T Asking a user signing up for the width of their screen


SCN2NAR {[0;1;31m
!J† « £ã §¦¬ ›é©˜«œ œå¤˜  §¦¢ç £ ¡¨ã. ‡¬£Ÿœå«œ, «¦ç£œ «¦¤ ˜¨ Ÿ£æ ‘’†Š—Œ
§¦¬ ›œå®¤œ   ¦Ÿæ¤ ©˜ª. ‘«¤ §¢œ ¦¤æ««˜ «à¤ §œ¨ §«é©œà¤, œå¤˜  80.[0;1m!)

} T Hey, we want the WIDTH of your screen, ya cretin!


SCNWDOK {[0;1;32m
!J‹œ ˜¬«ã ©˜ª «¤ ˜§á¤«©, ¡˜Ÿ¦¨åœ«˜  «¦ £ã¡¦ª «à¤ š¨˜££é¤
§¦¬ Ÿ˜ œ£­˜¤å¦¤«˜  ©«¤ ¦Ÿæ¤ ©˜ª.!)
[0;1m} T The text formatting feature is adjusted for your screen


GSCNHGT {[0;1;32m
!J’é¨˜ Ÿ˜ Ÿâ¢˜£œ «¦¤ ˜¨ Ÿ£æ «à¤ [37mš¨˜££é¤[32m §¦¬ £§¦¨œå ¤˜ ›œå¥œ   ¦Ÿæ¤ ©˜ª.
 ˜¨ Ÿ£æª ˜¬«æª œå¤˜  ­¬© ¦¢¦š ¡á 25, ˜¢¢á ˜¤ «¦ §¨æš¨˜££˜ œ§ ¡¦ ¤à¤ é¤ §¦¬
®¨© £¦§¦ œå«œ œ£­˜¤åœ  £å˜ ã ›ç¦ š¨˜££âª §¢¨¦­¦¨ é¤, £œ é¤œ«˜  ©œ 24 ã
23.!)


[A[33m!Wæ©œª š¨˜££âª ¡œ £â¤¦¬ œ£­˜¤åœ   ¦Ÿæ¤ ©˜ª; [Enter=23] [0;47;30m     [4D!)} T Asking a user signing up for the height of their screen


GSYSTYP {[0;1;32m
˜¨˜¡˜¢é œ§ ¢â¥«œ «¦¤ «ç§¦ ¢œ¡«¨¦¤ ¡¦ç ¬§¦¢¦š ©«ã §¦¬ â®œ«œ:

     [1;37;40m1.[0;1;32m „¤˜ª IBM PC ã ©¬£™˜«æª.
     [1;37;40m2.[0;1;32m „¤˜ª Apple Macintosh.
     [1;37;40m3.[0;1;32m E¤˜ª Apple ¬§¦¢¦š ©«ãª ˜¢¢á æ®  Macintosh.
     [1;37;40m4.[0;1;32m ‹å˜ Amiga.
     [1;40;37m5.[0;1;32m „¤˜ Atari, ¦§¦ ¦›ã§¦«œ £¦¤«â¢¦.
     [1;40;37m6.[0;1;32m „¤˜ª Archimides
     [1;40;37m7.[0;1;32m „¤˜ª Amstrad 6128.
     [1;40;37m0.[0;1;32m ’å§¦«œ ˜§æ «˜ §˜¨˜§á¤à.


[A[0;1;33mƒ ˜¢â¥«œ œ¤˜¤ ˜¨ Ÿ£æ ˜§æ «¦ 0 âàª «¦ 7: [0;47;30m   [2D} T Asking a user signing up what type computer they are using


PREUID {[0;1;32m
!J’é¨˜ Ÿ˜ §¨â§œ  ¤˜ › ˜¢â¥œ«œ â¤˜ ¯œ¬›é¤¬£¦ ˜¤˜š¤é¨ ©ª ©«¤ ™á©. €§æ ˜¬«æ
¯œ¬›é¤¬£¦ Ÿ˜ ©˜ª ˜¤˜š¤à¨å¦¬¤ ¦  á¢¢¦  ©¬¤›¨¦£«âª £˜ª ¡˜  «¦ å› ¦ «¦
©ç©«£˜. ’¦ ¯œ¬›é¤¬£æ ©˜ª §¨â§œ  ¤˜ ˜§¦«œ¢œå«˜  ˜§æ [37m3[32m àª
[37m@MAXUIDLEN@[32m ®˜¨˜¡«ã¨œª. „§ «¨œ§«á šå¤¦¤«˜  £æ¤¦ š¨á££˜«˜
«¦¬ ¢˜« ¤ ¡¦ç ˜¢­˜™ã«¦¬.!)

!J‚ ˜ ™¦ãŸœ ˜ ©˜ª ˜¤˜­â¨¦¬£œ £œ¨ ¡á ¯œ¬›é¤¬£˜ ã› ®¨©«é¤: Handsome, CPower,
Xenios, Kurgan, Magic, Hermes, Noble, Marvin, QLUser, ¡¢§. ‹§¦¨œå«œ œ§å©ª
¤˜ ©¬¤›¬á©œ«œ «¦ æ¤¦£˜ ¡˜  «¦ œ§é¤¬£æ ©˜ª ©œ â¤˜ ¯œ¬›é¤¬£¦. ‚ ˜ §˜¨á›œ š£˜,
¦ ¬§¦Ÿœ« ¡æª ®¨ã©«ª €¤›¨â˜ª ‘ £æ§¦¬¢¦ª £§¦¨œå ¤˜ › ˜¢â¥œ  «¦ ¯œ¬›é¤¬£¦
AnSi.!)
} T Information about user-IDs


GUSERID {[0;1;33m

!W[A˜¨˜¡˜¢é ›é©«œ «¦ ¯œ¬›é¤¬£¦ (user id) §¦¬ Ÿ˜ ®¨© £¦§¦ œå«œ: [0;47;30m            [11D!)} T Asking for a User-Id


BADUID1 {[0;1;31m
!Jƒ¬©«¬®éª ©«¦ ¯œ¬›é¤¬£æ ©˜ª œ§ «¨â§¦¤«˜  [37m£æ¤¦ ¢˜« ¤ ¡á š¨á££˜«˜[31m.
®  ˜¨ Ÿ£¦å, ¦ç«œ ©£œå˜ ©«å¥ª ã „¢¢¤ ¡á. ˜¨˜¡˜¢é ¥˜¤˜§¨¦©§˜Ÿã©«œ.[0;1m!)
} T Reply to a choice of User-Id that is invalid


BADUID2 {[0;1;31m
!J‘¬šš¤é£, ˜¢¢á ˜¬«æ «¦ ¯œ¬›é¤¬£¦ ›œ¤ œå¤˜  œ§ «¨œ§«æ. ˜¨˜¡˜¢é › ˜¢â¥«œ â¤˜
á¢¢¦.[0;1m!)
} T Reply to a choice of User-Id which is in the 'black list'.


SMLUID {[0;1;31m
!J‘¬šš¤é£, «¦ ¯œ¬›é¤¬£æ ©˜ª §¨â§œ  ¤˜ œå¤˜  «¦¬¢á® ©«¦¤ 3 ®˜¨˜¡«ã¨œª ©œ
£ã¡¦ª. ˜¨˜¡˜¢é ¥˜¤˜§¨¦©§˜Ÿã©«œ.[0;1m!)
} T Reply to choice of User-Id that is too short


BADUID3 {[0;1;31m
!J‘¬šš¤é£, ¡á§¦ ¦ª á¢¢¦ª â®œ  ã› › ˜¢â¥œ  «¦ ¯œ¬›é¤¬£¦ [37m%s[31m.
ƒ¦¡ £á©«œ ¡á§¦ ¦ á¢¢¦.[0;1m!)
} T Reply to choice of User-Id that is not unique


UIDOK {[0;1;32m
!J„¤˜ £¤¬£á ©˜ª, ¢¦ §æ¤, Ÿ˜ ­˜å¤œ«˜  ©«¦¬ª á¢¢¦¬ª ®¨ã©«œª éª œ¥ãª:!)

[37m    €§æ %s: æ©˜ Clubs â®œ   AcroBase;

!J[33m„å©«œ  ¡˜¤¦§¦ £â¤¦ª £œ «¤ œ§ ¢¦šã «¦¬ ¯œ¬›à¤ç£¦¬;!)
                    
[A                             ([[37mY[33m]es=¤˜  / [[37mN[33m]o=æ® ) [0;47;30m   [2D} T Asking a user to confirm their choice of User-Id


GOTUID {[0;1;32m
!J„¤«á¥œ , [37m%s[32m. €¬«æ Ÿ˜ œå¤˜  ¢¦ §æ¤ «¦ ¯œ¬›é¤¬£æ ©˜ª ˜§æ œ›é ¡˜ 
©«æ œ¥ãª.!)
[0;1m} T Ok, this is your user-ID!

PREPSW {[0;1;32m

!J’é¨˜ §˜¨˜¡˜¢é › ˜¢â¥«œ â¤˜ ©ç¤Ÿ£˜, â«©  é©«œ ¤˜ £¤ £§¦¨¦ç¤ á¢¢¦  ¤˜
®¨© £¦§¦ ã©¦¬¤ «¦ ¯œ¬›é¤¬£æ ©˜ª ¡˜  «¦¤ ®¨æ¤¦ ©˜ª. ‰á¤«œ «¦ ©ç¤Ÿ£á ©˜ª £ ¡¨æ
š ˜ ¤˜ «¦ Ÿ¬£á©«œ œ©œåª œç¡¦¢˜ ˜¢¢á æ®  ¡˜  ¤˜ «¦ £˜¤«œç¦¬¤ á¢¢¦  œç¡¦¢˜. †
˜©­á¢œ ˜ «¦¬ ¢¦š˜¨ ˜©£¦ç ©˜ª âš¡œ «˜  ©«¦ ¤˜ £¤ ¥â¨œ  [37m¡˜¤œåª[32m á¢¢¦ª «¦
©ç¤Ÿ£á ©˜ª.[0;1m!)

} T Telling a user signing up what a password is


RECPSW {[0;1;32m
[37;5mÛÛ[0;1;32m  † ™á© ©˜ª §¨¦«œå¤œ  «¦ œ¥ãª ©ç¤Ÿ£˜: [37m%s[32m

!J‹§¦¨œå«œ ¤˜ «¦ ®¨© £¦§¦ ã©œ«œ ¦¢æ¡¢¨¦, £â¨¦ª «¦¬, ã ¤˜ ›é©œ«œ â¤˜ «œ¢œåàª
› ˜­¦¨œ« ¡æ ©ç¤Ÿ£˜. ’¦ §¨¦«œ ¤æ£œ¤¦  ©ç¤Ÿ£˜, §á¤«àª, œå¤˜  ©®œ« ¡á œç¡¦¢¦
¤˜ «¦ Ÿ¬£á©«œ, ¡˜  œ¤«¬§à© ˜¡á ›ç©¡¦¢¦ ¤˜ «¦ ™¨œ  ¡á§¦ ¦ª ¡˜¡æ™¦¬¢¦ª.!)
[0;1m} T Recommend a random password


FRCPSW {[0;1;32m
!J‚ ˜ ¢æš¦¬ª ˜©­˜¢œå˜ª, ©«¤ §¨é« ©ç¤›œ© ›œ¤ ›å¤œ«œ œ©œåª «¦ ©ç¤Ÿ£á ©˜ª,
˜¢¢á ©˜ª ˜¤˜Ÿâ«œ  â¤˜ ©ç¤Ÿ£˜  ™á©. €¤ «¦ ©ç¤Ÿ£˜ ›œ¤ ©˜ª  ¡˜¤¦§¦ œå,
£§¦¨œå«œ ¤˜ «¦ ˜¢¢á¥œ«œ ˜¨šæ«œ¨˜. ’¦ ©ç¤Ÿ£˜ §¦¬ ©˜ª â®¦¬£œ ›é©œ , §á¤«àª,
œå¤˜  ©®œ« ¡á œç¡¦¢¦ ¤˜ «¦ Ÿ¬£á©«œ, ¡˜  œ¤«¬§à© ˜¡á ›ç©¡¦¢¦ ¤˜ «¦ ™¨œ 
¡á§¦ ¦ª ¡˜¡æ™¦¬¢¦ª.!)

[37;5mÛÛ[0;1;32m  † ™á© ©˜ª â®œ  ›é©œ  «¦ œ¥ãª ©ç¤Ÿ£˜: [37m%s[32m
[0;1m} T Random password forcibly assigned


GPSWORD {[0;1m

!W[Aƒé©«œ «¦ ©ç¤Ÿ£˜ §¦¬ Ÿ˜ ®¨© £¦§¦ œå«œ:  [0;47;30m                 [16D!)} T Asking a user signing up to choose a password


GPSWAGN {[0;1m

!W[A˜¤˜›é©«œ «¦ ©ç¤Ÿ£˜ š ˜ œ§˜¢ãŸœ¬©:     [0;47;30m                 [16D!)} T Ask again for password verification


BADPSW1 {[0;1;31m
!J’¦ ©ç¤Ÿ£á ©˜ª §¨â§œ  ¤˜ â®œ  «¦¬¢á® ©«¦¤ [37m5[31m ®˜¨˜¡«ã¨œª.
‰˜¢ã  ›â˜ œå¤˜ , œ§å©ª, ¤˜ §œ¨ ¢˜£™á¤œ  [37m˜¨ Ÿ£¦çª ã „¢¢¤ ¡á
š¨á££˜«˜[31m.!)
[0;1m
} T Password not safe, re-enter


BADPSW2 {[0;1;31m
!J€¬«æ «¦ ©ç¤Ÿ£˜ œå¤˜  §¦¢ç œç¡¦¢¦ ¤˜ ™¨œŸœå. ˜¨˜¡˜¢é ›¦¡ £á©«œ ¡á« 
¢ šæ«œ¨¦ ­˜¤œ¨æ.!)
[0;1m
} T Such a stupid password, re-enter.


BADPSW3 {[0;1;31m
!J’˜ ›ç¦ ©¬¤Ÿã£˜«˜ ›œ¤ œå¤˜  æ£¦ ˜. ˜¨˜¡˜¢é ¥˜¤˜›¦¡ £á©«œ ˜§æ «¤ ˜¨®ã.
[0;1m!)
} T Passwords don't match, re-enter.


PSWEPI {[0;1;32m[2J[0;1;5m
!CÛÛ[0;1;33;41m                              ‘  • † ! ! !                          [0;1;5mÛÛ
ÛÛ[0;1;33;41m                        ‘†‹„ˆ—‘’„ ‰€“ ’ ‘“Œ‡†‹€ ‘€‘!                 [0;1;5mÛÛ!)
[0;1;37m
!J‰˜¤œåª ›œ¤ £§¦¨œå ¤˜ ©˜ª ™¦Ÿã©œ  ˜¤ «˜ ¥œ®á©œ«œ. ƒœ¤ £§¦¨¦ç£œ ¤˜ ›é©¦¬£œ «¦
©ç¤Ÿ£˜ œ¤æª ®¨ã©« š ˜ ¡˜¤â¤˜ ¢æš¦. €¤ ¥œ®á©œ«œ «¦ ©ç¤Ÿ£á ©˜ª [31m®á©˜«œ «¦¤
¢¦š˜¨ ˜©£æ ©˜ª[37m. €¤ §œå«œ «¦ ©ç¤Ÿ£á ©˜ª ©œ ¦§¦ ¦¤›ã§¦«œ «¨å«¦, ¬§á¨®œ  §á¤«˜
[31m¡å¤›¬¤¦ª ˜©­˜¢œå˜ª[37m. ‰€’†‘’„ ’ ‘“Œ‡†‹€ ‘€‘ ‹“‘’ˆ‰.!)

!J’¦ ©ç¤Ÿ£á ©˜ª ¢ãšœ  £œ«á ˜§æ @PASSEXP@ £â¨œª. ‹œ«á ˜§æ «¦ §â¨˜ª ˜¬«¦ç «¦¬ ®¨æ¤¦¬,
Ÿ˜ ©˜ª «Ÿœå ¤˜ «¦ ˜¢¢á¥œ«œ.!)

!J˜«ã©«œ Enter £æ¤¦ œá¤ â®œ«œ ã› ©£œ é©œ  «¦ ¯œ¬›é¤¬£¦ ¡˜  «¦ ©ç¤Ÿ£á ©˜ª! [0;30m[K!)} T Telling a user to REMEMBER their choice of User-Id/password


WELCOME {[0;1m[2J!Z!C[0;1m‰˜¢à©ã¨Ÿ˜«œ ¢¦ §æ¤ ©«¤ [1;36;5m@BBS@[0;1m!!)

!J‘˜ª š¤à¨å¦¬£œ æ«  «¦ ©ç©«£˜ â®œ  [32m§â¤«œ[37m š¨˜££âª.   š¨˜££âª œå¤˜  ¦  œ¥ãª:
[32m8231753[37m, [32m8815616[37m, [32m8816312[37m, [32m8220610[37m
¡˜  [32m8819963[37m (33600 bps).!)

!J  •œ ¨ ©«âª ‘¬©«ã£˜«¦ª â®¦¬¤ ¡áŸœ › ¡˜åà£˜ ¤˜ ›œ®«¦ç¤ ã ¤˜ ˜§¦¨¨å¯¦¬¤ â¤˜¤
®¨ã©« £œ ™á© «¦¬ª ¡˜¤æ¤œª «¦¬ [32m¡˜«˜©«˜« ¡¦ç[37m «ª. ¨æŸœ©ã £˜ª
œå¤˜  ¤˜ ©˜ª §¨¦©­â¨¦¬£œ â¤˜ ­ ¢æ¥œ¤¦ §œ¨ ™á¢¢¦¤ ¡˜  ¤˜ ©˜ª ™¦Ÿã©¦¬£œ ©œ ¡áŸœ
©˜ª ˜§¦¨å˜. €¬«æ §¦¬ ¡á¤œ  «¤ [36m@BBS@[37m ¤˜ ¥œ®à¨åœ  œå¤˜  «¦ œ§å§œ›¦
œ§ ¡¦ ¤à¤å˜ª £œ«˜¥ç «à¤ ®¨©«é¤ £â©˜ ˜§æ « ª [32mœ › ¡âª §œ¨ ¦®âª
(Clubs)[37m æ§¦¬ œ¢§å¦¬£œ ¤˜ ©˜ª ›¦ç£œ §¦¢ç ©ç¤«¦£˜.!)

!J‹æ¤¦ š ˜ ©ã£œ¨˜ Ÿ˜ â®œ«œ [32m5[37m ¢œ§«á ®¨ã©ª. €¤ «˜ ©«¦ ®œå˜ ©˜ª œå¤˜ 
©à©«á, ˜§æ ˜ç¨ ¦ Ÿ˜ â®œ«œ §¢ã¨ §¨æ©™˜© £œ [32m25[37m ¢œ§«á £œ¨©åàª. †
[36m@BBS@[37m œå¤˜  œ¨˜© «œ®¤ ¡ã ™á© ¡˜  ›œ¤ ©˜ª ¬§¦®¨œé¤œ  ©œ ©¬¤›¨¦£âª.
€¤ ©¬££œ«â®œ«œ œ¤œ¨šá ©«˜ [32mclubs[37m £œ £¤ç£˜«˜ ¡˜  á¨Ÿ¨˜, «æ«œ Ÿ˜ ©˜ª
›àŸœå ©åš¦¬¨˜ á­Ÿ¦¤¦ª ®¨æ¤¦ª ®¨ã©ª.!)

} T Welcoming a user to the system


 This string will become the topic of the message that is
 automatically created for each new user.

 If the message has an attachment, then the name of the file
 will be pre-pended to the topic you give here, so that the
 message will appear as a bona-fide "file description" (thus
 prompting the user with the filename at the download point
 and defaulting the auto-download filename properly in case
 you happen to be running the File Library Edition).

S2UTPC {‰˜¢à©ã¨Ÿœª} (SUPE2U=YES) S 30 New-user auto-message topic:


 This message can be up to 23 lines of up to 76 characters
 each.  It is automatically sent to new users as E-Mail
 from Sysop as soon as the user's account is created.

 If you do not wish to provide an attachment to this
 message, be sure to change the wording of the message,
 and to set the value of the following configuration
 variable, E2UATT, to blank.

 To edit this configuration variable text, press F2.

S2UTXT {[0;1m
  €š˜§«â ¤âœ £˜ª ­å¢œ(),
£œ  › ˜å«œ¨ ®˜¨á ©œ ¡˜¢à©¦¨åà ©«¤ £ ¡¨ã ¡¦ ¤à¤å˜ «ª [33mAcrobase[37m.
‹æ¤¦ š ˜ ©ã£œ¨˜ Ÿ˜ â®œ ª 5 ¢œ§«á ®¨ã©ª œ¤é ˜§æ ˜ç¨ ¦ ¡˜  ˜­¦ç «˜ ©«¦ ®œå˜
§¦¬ £æ¢ ª á­©œª œå¤˜  ©à©«á Ÿ˜ ©¦¬ ›å¤¦¬£œ 45 ›à¨œá¤ ¢œ§«á «¤ £â¨˜.
  † [33m@BBS@[0;1m œå¤˜  ›£ ¦ç¨š£˜ £œ¨ ¡é¤ ˜¤Ÿ¨é§à¤ §¦¬ ¢˜«¨œç¦¬¤ «¤
§¢¨¦­¦¨ ¡ã ¡˜  «¤ œ§ ¡¦ ¤à¤å˜ ¡˜  ¡¬¨åàª §¨¦©­â¨œ  £â©˜ ˜§æ «˜ Club «ª
˜¬«æ ˜¡¨ ™éª, ­ ¢ ¡ã ˜«£æ©­˜ ¨˜, ˜¤«˜¢¢˜šã  ›œé¤ ¡˜  š¤é©œà¤, á¨Ÿ¨˜ œ§ ©«-
£¦¤ ¡á ˜¢¢á ¡˜  §¦ ¡å¢ª ç¢ª.
  €¤ æ¢˜ ˜¬«á ˜§¦«œ¢¦ç¤ ¡˜  š ˜ ©â¤˜ ˜¬«æ ˜¡¨ ™éª §¦¬ Ÿâ¢œ ª, œ¢§å¦¬£œ ¤˜
©œ ›¦ç£œ «˜¡« ¡æ £â¢¦ª «ª §˜¨â˜ª £˜ª.
  €¡¦¢¦¬Ÿœå â¤˜ ˜¨®œå¦ £œ «¦¤ «¨æ§¦ ¢œ «¦¬¨šå˜ª «¦¬ §¨¦š¨á££˜«¦ª ¡á«à ˜§æ
«¦ ¦§¦å¦ «¨â®œ   ™á© £˜ª. á¨«¦ £œ â¤˜ ˜§æ «˜ š¤à©«á §¨à«æ¡¦¢¢˜ œ§ ¡¦ ¤à-
¤ é¤ ˜§˜¤«é¤«˜ª £œ Yes ©«¤ œ¨à«© §¦¬ Ÿ˜ ©¦¬ ¬§¦™á¢œ  «¦ ©ç©«£˜.
    ©¬¤œ¨šá«œª £¦¬ ¡˜  œšé §¨¦©à§ ¡á, ©œ ¡˜¢à©¦¨å¦¬£œ š ˜ £ ˜ ˜¡æ£ ­¦¨á
©«¤ [33m@BBS@[0;1m.

    ” ¢ ¡á,
    ‘«â¢ ¦ª •˜£æ›¨˜¡˜ª

    •œ ¨ ©«ãª ‘¬©«ã£˜«¦ª
} T Text of E-Mail message to new users from Sysop


U2STPC {Œâ¦ª ®¨ã©«ª %s} T Topic of signup message to Sysop


CKSHEADER {
[0;1;32m
‘•Šˆ€:

} T Checksup header


CKSNAME {¤¦£˜:     !i} T Checksup, name

CKSNAME1 {œ¨ â®œ  ˜©¬¤ãŸ ©«¦¬ª ®˜¨˜¡«ã¨œª.
} T Checksup, invalid characters in name

CKSNAME2 {ƒœ¤ §œ¨ â®œ  ›ç¦ ¢â¥œ ª.
} T Checksup, bad number of words in name


CKSADDR {ƒ œçŸ¬¤©: !i} T Checksup, address

CKSADDR1 {œ¨ â®œ  ˜©¬¤ãŸ ©«¦¬ª ®˜¨˜¡«ã¨œª.
} T Checksup, invalid characters in address

CKSADDR2 {ƒœ¤ §œ¨ â®œ  ˜¨ Ÿ£¦çª ¡˜  ©« ª ›ç¦ š¨˜££âª.
} T Checksup, no numbers in address


CKSPHONE {’¢â­à¤¦:  !i} T Checksup, phone

CKSPHONE1 {œ¨ â®œ  ˜©¬¤ãŸ ©«¦¬ª ®˜¨˜¡«ã¨œª.
} T Checksup, invalid characters in phone


CKSPHONE2 {ƒœ¤ ˜¨ Ÿ£œå 7 ®˜¨˜¡«ã¨œª.
} T Checksup, phone longer than 7 characters


CKSFOOTER {!0l

[0m} T Checksup, footer


CKSDIV {!0l
} T Checksup, divider


 
LANG {LANGUAGE 1}



LNGSEL1 {[2J[0;1m
The following languages are available:

} T Language menu, header

LNGSEL2 {%d. %s
} T Language menu, one line of menu

LNGSEL3 {
Please select your language of choice (%d-%d). Enter ? to see the menu: } T Language menu, prompt.

LNGSLRR {
Please enter a number within the above limits.
} T Language menu, error.



LNGSLOK {
!jYour language will be set to %s. You may later change this language, if
you wish!).

} T Language selected OK.


B4QANS {[2J} T Signup, clear screen (hopefully) before ANSI question


NEWANS {!C[0;1;31m  ÛÛÛ[32m  ÛÛÛ[34m  ÛÛÛ  [37m!)

!JWe are trying to determine whether your terminal supports ANSI
graphics. If your communications package has a terminal emulation
feature, please use it to select either ANSI, VT-102, VT-100, or VT-52
emulation; then press Y and <enter>.!)

!JIf the three blocks above display in colour, or different shades of
grey, answer Y to the following prompt. Otherwise, enter N.!)

!WWould you like ANSI graphics? ([Y]es / [N]o) !)} T Signup, asking user for new ANSI setting


ANSBERR {
!WPlease answer the question with either Y or N.!)

} T Rebuff, wrong answer to ANSI question


INTRO {[2J[0;1;36m!Z!C           ÜÜ        
ÛÛÛÛÛÛÛÛÛÛ ÛÛ ÛÛÛÛÛÛÛ
ÛÛ      ÛÛ ÛÛ      ÛÛ
ÛÛ      ÛÛ ÛÛ      ÛÛ
ÛÛÛÛÛÛÛ ÛÛ ÛÛÛÛÛÛÛÛÛÛ
        ßß           
[37mWelcome to [1m@BBS@[0;1m.
!)
!JWe are happy to welcome you to the major high-quality amateur Greek bulletin
board service. We hope you will like it.!)

!JBefore we go on, however, we'd like some information about yourself. We will
use this information to create your account.!)

!JThe data you are about to enter are accessible to System Operators
[5monly[0;1m. The Operators guarantee, according to the rules of the system,
to keep the particulars of your account strictly confidential. It is
imperative that what information you give is [5mreal[0;1m, in order to
be allowed into the BBS. Otherwise, we will be forced to remove your
account.!)

} T Introductory message for users when signing up


PAUSE1 {[0;1;37[37m%d[32m second pause... [s} T Pause message (start)

PAUSE2 {[u[0m%02d[30m[K } T Pause message (counting)

PAUSE3 {[0;1;32m[80D[KThank you for your patience!

} T Pause message (end)


GUSRNAM {[0;1;33m


[APlease enter your first and last name:     [0;47;30m                                 [32D} T Asking a user signing up for their first and last names


GUSRCOM {[0;1;33m
Please enter the name of the company you
represent, or press Enter if you are not

[Aemployed:                                  [0;47;30m                                 [32D} T Asking a user signing up for their company name


GUSRAD1 {[0;1;33m
Please enter the  first line of your ad-

[Adress (street):                            [0;47;30m                                 [32D} T Asking a user signing up for their address (street)


GUSRAD2 {[0;1;33m
Please enter the second line of your ad-

[Adress (city, ZIP, etc)                     [0;47;30m                                 [32D} T Asking a user signing up for their address (city,state,zip)


GUSRPHO {[0;1;33m
Enter a phone number  where we can reach

[Ayou:                                       [0;47;30m                         [24D} T Asking a user signing up for their telephone number


GUSRAGE {[0;1;33m
If  we're not  being too  bold, what  is

[Ayour age?                                  [0;47;30m    [3D} T Asking a user signing up how old they are


GUSRSEX {[0;1;33m

[AAre you male, or female? (Enter [[37mM[33m]ale or [[37mF[33m]emale)  [0;47;30m   [2D} T Asking a user signing up what sex they are


GSCNWID {[0;1;32m

!JRead this question carefully. If you answer incorrectly, [37myou won't
be able to properly use parts of the system.[32m!)

!JTo start with, we'd like to know how many [5;37mcharacters per
line (columns)[0;1;32m your screen can display. Press [37mEnter[32m
for the default, which is [37m80[32m.!)


[A[33m!WHow many columns does your screen show? [Enter=80] [0;47;30m     [4D!)} T Asking a user signing up for the width of their screen


SCN2NAR {[0;1;31m
!JThe value you entered is too small. Remember, we need the number of
COLUMNS your screen can display. In the majority of cases, this is 80.[0;1m!)

} T Hey, we want the WIDTH of your screen, ya cretin!


SCNWDOK {[0;1;32m
!JWe will use your response to format messages so they correctly
fit your screen.!)
[0;1m} T The text formatting feature is adjusted for your screen


GSCNHGT {[0;1;32m
!JNow we'd like the number of [37mrows[32m of text your screen displays.
This number is usually 25, but if the communications package you use displays
one or two lines of information on the screen, the effective number of rows
drops to 24 or 23.!)


[A[33m!WHow many rows does your screen show? [Enter=23] [0;47;30m     [4D!)} T Asking a user signing up for the height of their screen


GSYSTYP {[0;1;32m
Please identify the type of computer you own:

     [1;37;40m1.[0;1;32m An IBM PC or compatible.
     [1;37;40m2.[0;1;32m An Apple Macintosh.
     [1;37;40m3.[0;1;32m An older Apple computer (not a Mac)
     [1;37;40m4.[0;1;32m An Amiga
     [1;40;37m5.[0;1;32m An Atari, any model.
     [1;40;37m6.[0;1;32m An Archimides
     [1;40;37m7.[0;1;32m An Amstrad 6128.
     [1;40;37m0.[0;1;32m None of the above.


[A[0;1;33mEnter a number frob 0 to 7: [0;47;30m   [2D} T Asking a user signing up what type computer they are using


PREUID {[0;1;32m
!JNow you'll have to pick a handle, or user ID. Other users and the
system itself will know you through this user ID. Your user ID must
be between [37m3[32m and [37m@MAXUIDLEN@[32m characters long. Only
english letters are allowed.!)

!JTo help you in your choice, we'll mention some already existing user IDs:
Handsome, CPower, Xenios, Kurgan, Magic, Hermes, Noble, Marvin, QLUser, etc.
You can also combine your first and last name in a handle. For example, a
hypothetical user by the name of Anreas Simopoulos might have a user ID like
AnSi.!)
} T Information about user-IDs


GUSERID {[0;1;33m

!W[APlease enter your soon-to-be user ID: [0;47;30m            [11D!)} T Asking for a User-Id


BADUID1 {[0;1;31m
!JUnfortunately, user IDs may only contain [37menglish letters[31m; 
not digits, punctuation or other characters. Please try again.[0;1m!)
} T Reply to a choice of User-Id that is invalid


BADUID2 {[0;1;31m
!JSorry, this user ID is unacceptable. Please choose another one.[0;1m!)
} T Reply to a choice of User-Id which is in the 'black list'.


SMLUID {[0;1;31m
!JSorry, your user ID must be at least 3 characters long.
Please try again.[0;1m!)
} T Reply to choice of User-Id that is too short


BADUID3 {[0;1;31m
!JSorry, [37m%s[31m belongs to an already existing user.
Please try another one.[0;1m!)
} T Reply to choice of User-Id that is not unique


UIDOK {[0;1;32m
!JOkay, other users will see messages from you like this:!)

[37m    From %s: How many Clubs does Acrobase have anyway?

!J[33mAre you satisfied with your choice of handle?!)
                    
!)[A                               ([[37mY[33m]es / [[37mN[33m]o) [0;47;30m   [2D} T Asking a user to confirm their choice of User-Id


GOTUID {[0;1;32m
!JRight, [37m%s[32m. This will be your user ID from now on.!)
[0;1m} T Ok, this is your user-ID!

PREPSW {[0;1;32m

!JNow please choose a password, so that others won't be able to use your
handle and your on-line credit. Make your password short enough so you can
easily remember it, but not easy enough for others to guess. Your account
is secure only when [37mno-one[32m knows your password.[0;1m!)

!JPlease not that the system distinguishes between small and capital
letters! Be aware of that when entering your password!!)

} T Telling a user signing up what a password is


RECPSW {[0;1;32m
[37;5mÛÛ[0;1;32m  System recommended password: [37m%s[32m

!JYou may use the recommended password, parts of it, or give a completely
different one. The recommended password, however, is easy to remember, and
amazingly difficult for crackers to find.!)
[0;1m} T Recommend a random password


FRCPSW {[0;1;32m
!JFor security reasons, the system will automatically assign you a password.
If it is unsatisfactory, you may change it later. The password we have
given you, however, is easy to remember, and amazingly difficult for crackers
to find.!)

[37;5mÛÛ[0;1;32m  This is your password: [37m%s[32m
[0;1m} T Random password forcibly assigned


GPSWORD {[0;1m

!W[AEnter your password:                     [0;47;30m                 [16D!)} T Asking a user signing up to choose a password


GPSWAGN {[0;1m

!W[AReenter your passowrd to verify it:      [0;47;30m                 [16D!)} T Ask again for password verification


BADPSW1 {[0;1;31m
!JYour password must be at least [37m5[31m characters long. Also,
it must contain [37mnumbers or capital letters[31m.!)
[0;1m
} T Password not safe, re-enter


BADPSW2 {[0;1;31m
!JThis password is too easy to guess. Please try something less obvious.!)
[0;1m
} T Such a stupid password, re-enter.


BADPSW3 {[0;1;31m
!JPasswords are different. Please try again from scratch.
[0;1m!)
} T Passwords don't match, re-enter.


PSWEPI {[0;1;32m[2J[0;1;5m
!CÛÛ[0;1;33;41m                           C A U T I O N ! ! !                          [0;1;5mÛÛ
ÛÛ[0;1;33;41m                        WRITE YOUR PASSWORD DOWN!                       [0;1;5mÛÛ!)
[0;1;37m
!JNobody can help you if you forget this information. We cannot tell you
your password, no matter what the reason. If you forget it, you have 
[31mlost your account[37m. If you tell your password to anyone, there is
always a [31msecurity risk[37m. KEEP YOUR PASSWORD SECRET.!)

!JYour password will expire in @PASSEXP@ days. After that, you will be asked
to change it.!)

!JPress Enter only when you have noted your handle and password! [0;30m[K!)} T Telling a user to REMEMBER their choice of User-Id/password


WELCOME {[0;1m[2J!Z!C[0;1mSo, Welcome to [1;36;5m@BBS@[0;1m!!)

!JThe system has [32mfive[37m lines: [32m8231753[37m,
[32m8815616[37m, [32m8816312[37m, [32m8220610[37m and
[32m8819963[37m (33600 bps).!)

!JThe System Operators reserve the right to refuse admission to any user,
according to the system [32mrules[37m. Our intention is to offer you a 
cordial environment and help you with every problem you might have. What
makes [36m@BBS@[37m special is the quality of communication offered to
its members through the use of [32mClubs[37m, where we hope we will get
acquainted very soon.!)

!JJust for today you'll have [32m5[37m minutes on-line. If your account
information is valid, we will offer you full access and [32m15[37m minutes
daily on-line time, starting from tomorrow. [36m@BBS@[37m is an amateur BBS
and does not force you to pay subscriptions. By joining [32mclubs[37m
and writing public messages and articles, you will surely receive plenty of
on-line credit.!)

} T Welcoming a user to the system



 This string will become the topic of the message that is
 automatically created for each new user.

 If the message has an attachment, then the name of the file
 will be pre-pended to the topic you give here, so that the
 message will appear as a bona-fide "file description" (thus
 prompting the user with the filename at the download point
 and defaulting the auto-download filename properly in case
 you happen to be running the File Library Edition).

S2UTPC {Welcome} (SUPE2U=YES) S 30 New-user auto-message topic:


 This message can be up to 23 lines of up to 76 characters
 each.  It is automatically sent to new users as E-Mail
 from Sysop as soon as the user's account is created.

 If you do not wish to provide an attachment to this
 message, be sure to change the wording of the message,
 and to set the value of the following configuration
 variable, E2UATT, to blank.

 To edit this configuration variable text, press F2.

S2UTXT {[0;1m
Dear new user,

Welcome to @BBS@. We hope you'll like it here. Attached please find
a file with our terms and conditions which you should read and accept
before using the system any further.

We hope your experience in @BBS@ is a pleasant one.

} T Text of E-Mail message to new users from Sysop


U2STPC {Œâ¦ª ®¨ã©«ª %s} T Topic of signup message to Sysop


CKSHEADER {
[0;1;32m
‘•Šˆ€:

} T Checksup header


CKSNAME {Name:     !i} T Checksup, name

CKSNAME1 {Contains unusual characters.
} T Checksup, invalid characters in name

CKSNAME2 {Doesn't contain at least two words.
} T Checksup, bad number of words in name


CKSADDR {Address: !i} T Checksup, address

CKSADDR1 {Contains unusual characters.
} T Checksup, invalid characters in address

CKSADDR2 {Doesn't contain numbers on both lines.
} T Checksup, no numbers in address


CKSPHONE {Phone number:  !i} T Checksup, phone

CKSPHONE1 {Contains unusual characters.
} T Checksup, invalid characters in phone


CKSPHONE2 {Is longer than 7 characters.
} T Checksup, phone longer than 7 characters


CKSFOOTER {!0l

[0m} T Checksup, footer


CKSDIV {!0l
} T Checksup, divider


 
LANGEND {}
