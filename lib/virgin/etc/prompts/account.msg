LEVEL2 {}


SYSKEY {Key required for privileged access to the Account module? 128} N 0 129

XFKEY {Key required to transfer credits? 0} N 0 129

REMEXP {Remind users of password expiry during login? NO} B

STREXP {After expiry, ask for new password during login? NO} B

SAFPSW {Make the user enter a safe password? YES} B

STRPSS {Insist on new passwords having non-alpha characters? NO} B

MINPLN {Minimum length of new passwords? 5} N 3 15

MKPSWD {Let the BBS provide the user with a safe password? YES} B

MKPWDF {Let the BBS force safe passwords to users? NO} B

LIPSKO {Password attempts allowed when changing passwd from login? 3} N 1 32767

LOGNAM {Record user name changes in the audit trail? YES} B

LOGCMP {Record user company changes in the audit trail? NO} B

LOGADR {Record user address changes in the audit trail? YES} B

LOGPHN {Record user phone changes in the audit trail? YES} B

LOGAGE {Record user age changes in the audit trail? YES} B

LOGSEX {Record user sex changes in the audit trail? YES} B

LOGSYS {Record user system type changes in the audit trail? NO} B

DEMCXF {Allow user without paid credits to transfer credits? YES} B

MINCXF {Minimum number of credits users can transfer? 100} N 0 1000000

MAXCXF {Maximum number of credits users can transfer? 1000} N 0 1000000 



LEVEL3 {}


DAYSNG {˜} T Days, singular form
DAYPLR {œª} T Days, plural form


EXPDAYS {[0;1;36m
’¦ «¨â®¦¤ ©ç¤Ÿ£á ©˜ª ¢ãšœ  ©œ [37m%d £â¨%s[36m.

[0;1m} T Login: Your password expires in X days


EXPIRED {[0;1;33m
!W[5mÛÛ[0;1;33m  !i’¦ ©ç¤Ÿ£á ©˜ª â®œ  ¢ã¥œ . ˜¨˜¡˜¢¦ç£œ ˜¢¢á¥«œ «¦ æ©¦ § ¦
©ç¤«¦£˜ šå¤œ«˜ , š ˜ «¤ › ¡ã ©˜ª ˜©­á¢œ ˜.!)

!0l[0;1m} T Login: Your password has expired


PASSEX {[0;1;31m
!J’¦ ©ç¤Ÿ£á ©˜ª â®œ  ¢ã¥œ . ˜¨˜¡˜¢¦ç£œ ¦¨å©«œ «é¨˜ «¦ ¤â¦ ©˜ª ©ç¤Ÿ£˜, §¨ ¤
§¨¦®à¨ã©œ«œ...!)

[0;1m} T Login: Your password has expired, enter new one now


ACCMNU {[2J[0m[47;1;37m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;30;47m¿ [40m
[47;1;37m ³  [0;47;30m              Š¦š˜¨ ˜©£æª ©˜ª ©«¦ ©ç©«£˜              [0;47;30m³ [40m
[47;1;37m ³  [0;47;30mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ  [0;47;30m³ [40m
[47;1;37m ³  [0;31;47mA[30mbout your account . . . . . . .  ‚œ¤ ¡âª ¢¨¦­¦¨åœª  [30m³ [40m
[47;1;37m ³  [0;31;47mC[30mhange account  . . . . . .  €¢¢˜šã «à¤ ©«¦ ®œåà¤ ©˜ª  [30m³ [40m
[47;1;37m ³  [0;31;47mP[30massword . . . . . . . . . . . . .  €¢¢˜šã ©¬¤Ÿã£˜«¦ª  [30m³ [40m
[47;1;37m ³  [0;31;47mS[30metup preferences . . . .  ¨¦©à§ ¡âª ©˜ª §¨¦« £ã©œ ª  [30m³ [40m
[47;1;37m ³  [0;31;47mT[30mransfer credits . . . . . .  ‹œ«˜­¦¨á £¦¤á›à¤ ®¨ã©ª  [30m³ [40m
[47;1;37m ³  [0;31;47mV[30miew statistics . . . . . . . . . ‘«˜« ©« ¡á ©«¦ ®œå˜  [30m³ [40m
[47;1;37m ³                                                         [0;47;30m³ [40m
[47;1;37m ³ [0;30;47me[31mX[30mit  . . . . . . . . . . . . . . . . . . . . . „¥¦›¦ª  [30m³ [40m
[47;1;37m À[0;30;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0;1m
} T Registry main menu


VSHMENU {[0;1m
Š¦š˜¨ ˜©£æª ©˜ª ©«¦ ©ç©«£˜
˜¨˜¡˜¢é ›é©«œ «¤ œ§ ¢¦šã ©˜ª: [0m} T Registry menu, very short prompt


SHMENU {[0;1m
Š¦š˜¨ ˜©£æª ©˜ª ©«¦ ©ç©«£˜
!Wƒé©«œ «¤ œ§ ¢¦šã ©˜ª ([33mA[37m,[33mC[37m,[33mP[37m,[33mS[37m,[33mT[37m,[33mV[37m,[33mX[37m š ˜ â¥¦›¦, ã [33m?[37m š ˜ «¦ £œ¤¦ç): !)[0m} T Registry short menu


ACCSMNU {[2J[0m[47;1;37m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;30;47m¿ [40m
[47;1;37m ³  [0;47;30m         ‡œä¡æª Š¦š˜¨ ˜©£æª ©˜ª ©«¦ ©ç©«£˜            [0;47;30m³ [40m
[47;1;37m ³  [0;47;30mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ  [0;47;30m³ [40m
[47;1;37m ³  [0;31;47mA[30mbout your account . . . . . . .  ‚œ¤ ¡âª ¢¨¦­¦¨åœª  [30m³ [40m
[47;1;37m ³  [0;31;47mC[30mhange account  . . . . . .  €¢¢˜šã «à¤ ©«¦ ®œåà¤ ©˜ª  [30m³ [40m
[47;1;37m ³  [0;31;47mP[30massword . . . . . . . . . . . . .  €¢¢˜šã ©¬¤Ÿã£˜«¦ª  [30m³ [40m
[47;1;37m ³  [0;31;47mS[30metup preferences . . . .  ¨¦©à§ ¡âª ©˜ª §¨¦« £ã©œ ª  [30m³ [40m
[47;1;37m ³  [0;31;47mT[30mransfer credits . . . . . .  ‹œ«˜­¦¨á £¦¤á›à¤ ®¨ã©ª  [30m³ [40m
[47;1;37m ³  [0;31;47mV[30miew statistics . . . . . . . . . ‘«˜« ©« ¡á ©«¦ ®œå˜  [30m³ [40m
[47;1;37m ³  [0;31;47mO[30mther user's password  €¢¢˜šã ©¬¤Ÿã£˜«¦ª á¢¢¦¬ ®¨ã©«  [30m³ [40m
[47;1;37m ³                                                         [0;47;30m³ [40m
[47;1;37m ³ [0;30;47me[31mX[30mit  . . . . . . . . . . . . . . . . . . . . . „¥¦›¦ª  [30m³ [40m
[47;1;37m À[0;30;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0;1m
} T Registry main menu for sysops


SHSMENU {[0;1m
Š¦š˜¨ ˜©£æª ©˜ª ©«¦ ©ç©«£˜
!Wƒé©«œ «¤ œ§ ¢¦šã ©˜ª ([33mA[37m,[33mC[37m,[33mP[37m,[33mS[37m,[33mT[37m,[33mV[37m,[33mO[37m,[33mX[37m š ˜ â¥¦›¦, ã [33m?[37m š ˜ «¦ £œ¤¦ç): !)[0m} T Registry short menu for sysops


ERRSEL {[0;1;31m
Š¬§á£˜ , ›œ¤ ¬§á¨®œ  œ§ ¢¦šã "%c".
[0;1m} T Wrong selection from the main account menu


LEAVE {[0;1m
„¥¦›¦ª ˜§æ «¦¤ Š¦š˜¨ ˜©£æ ©˜ª...
} T Leaving the account module


ABOUT {[0;1m

!J€¬«ã  §œ¨ ¦®ã ©˜ª œ§ «¨â§œ  ¤˜ §¨˜š£˜«¦§¦ ã©œ«œ ˜¨¡œ«âª › ˜­¦¨œ« ¡âª
œ¤â¨šœ œª. ‹§¦¨œå«œ ¤˜ œ¤£œ¨é©œ«œ ©«¦ ®œå˜ ©˜ª §¦¬ «¬®æ¤ â®¦¬¤ ˜¢¢á¥œ ,
¤˜ ¦¨å©œ«œ « ª §¨¦« £ã©œ ª ©˜ª ©«¦ ©ç©«£˜ (æ§àª œå›¦ª «œ¨£˜« ¡¦ç ¡˜  š¢é©©˜),
¤˜ £œ«˜­â¨œ«œ ®¨æ¤¦ ®¨ã©ª ©œ á¢¢¦¬ª ®¨ã©«œª, ¤˜ ›œå«œ ¡á§¦ œª ©«˜« ©« ¡âª
š ˜ «¦¤ ¢¦š˜¨ ˜©£æ ©˜ª, ã ¤˜ ˜¢¢á¥œ«œ «¦ ©ç¤Ÿ£á ©˜ª.!)

!J’˜ ©«¦ ®œå˜ §¦¬ ›å¤œ«œ œ›é œå¤˜  «˜ å› ˜ £œ ˜¬«á §¦¬ ©˜ª «ãŸ¡˜¤ æ«˜¤
š¨˜­«ã¡˜«œ ©«¤ ™á©. ‘ç£­à¤˜ £œ «¤ ©ç£™˜©ã ©˜ª £œ «¤ @BBS@ (¡˜«˜©«˜« ¡æ),
[31m›œ©£œçœ©«œ ¤¦£ ¡á æ«  «˜ ©«¦ ®œå˜ §¦¬ §œ¨ â®¦¤«˜  ©«¦¤ ¢¦š˜¨ ˜©£æ ©˜ª
œå¤˜  ˜¡¨ ™ã ¡˜  ˜¢Ÿã[37m. ‘œ §œ¨å§«à© §¦¬ ˜¬«æ ›œ¤ ©¬£™˜å¤œ , ¦ 
•œ ¨ ©«âª ‘¬©«ã£˜«¦ª Ÿ˜ ™¨œŸ¦ç¤ ©«¤ ›¬©á¨œ©« Ÿâ© ¤˜ ©˜ª ˜¨¤Ÿ¦ç¤ «¤
§¨æ©™˜© ©«¦ ©ç©«£˜.!)

!J‚ ˜ §œ¨ ©©æ«œ¨œª §¢¨¦­¦¨åœª, §˜¨˜¡˜¢¦ç£œ ˜§œ¬Ÿ¬¤Ÿœå«œ
©«¤ ©ç£™˜©ã ©˜ª (¡˜«˜©«˜« ¡æ), ©« ª ¢¨¦­¦¨åœª ‘¬©«ã£˜«¦ª ([33m/go
info[37m ˜§æ «¦ ¡œ¤«¨ ¡æ £œ¤¦ç).!)
} T About the account


PASSXP {
!J[0;1;33m‘£œåà©: [37m!i‘«¤ @BBS@ ¬§á¨®œ  › á¨¡œ ˜ àãª ©¬¤Ÿ£á«à¤. €¬«æ
©£˜å¤œ  æ«  œå©«œ ¬§¦®¨œà£â¤¦ª ¤˜ ˜¢¢áœ«œ «¦ ©ç¤Ÿ£á ©˜ª ¡áŸœ [32m@PASSEXP@
£â¨œª[37m. €¬«æ šå¤œ«˜  š ˜ › ¡ã ©˜ª §¨¦©«˜©å˜ ¡˜  £æ¤¦. …«¦ç£œ «¤ ©¬šš¤é£
¡˜  «¤ ¡˜«˜¤æ©ã ©˜ª š ˜ «¬®æ¤ «˜¢˜ §à¨å˜.!)
!0l[0;1m} T About password expiry


PXPDAYS {[0;1;32m
’¦ ©ç¤Ÿ£á ©˜ª ¢ãšœ  ©œ [37m%d £â¨%s[32m.
[0;1m} T Your password expires in N days


PEXPIRED {[0;1;31m
’¦ ©ç¤Ÿ£á ©˜ª â®œ  ¢ã¥œ . ˜¨˜¡˜¢¦ç£œ ˜¢¢á¥«œ «¦.
[0;1m} T Your password has expired, please change it.


ACCVT {[0;30;47m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [34m‘«¦ ®œå˜ ¢¦š˜¨ ˜©£¦ç[0;30;47m ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;1;37;47m¿ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  ¤¦£˜«œ§é¤¬£¦ . . . . . . . . .  [1;44;37m@31;31;0s[0;1;47;37m      ³ [0m
[30;47m ³  „«˜ ¨å˜  . . . . . . . . . . . . [1;44;37m@31;31;0s[0;1;47;37m      ³ [0m
[30;47m ³  ƒ œçŸ¬¤© (š¨˜££ã 1 ˜§æ 2)  . .  [1;44;37m@31;31;0s[0;1;47;37m      ³ [0m
[30;47m ³  ƒ œçŸ¬¤© (š¨˜££ã 2 ˜§æ 2) . . . [1;44;37m@31;31;0s[0;1;47;37m      ³ [0m
[30;47m ³  ’¢â­à¤¦  . . . . . . . . . . .  [1;44;37m@23;23;0s[0;1;47;37m              ³ [0m
[30;47m ³  †¢ ¡å˜ . . . . . . . . . . . . . [1;44;37m@2;1;99;0n[0;47;30m                           (1-99)  [1;37m³ [0m
[30;47m ³  ”ç¢¦  . . . . . . . . . . . . .  [0;30;46m @7;"€¤›¨˜ª|‚¬¤˜å¡˜"l [0;47;30m          (space š ˜ ˜¢¢˜šã)  [1;37m³ [0m
[30;47m ³  †¢œ¡«¨¦¤ ¡æª “§¦¢¦š ©«ãª . . . . [0;30;46m @14;"IBM compatible|Apple Mac|Old Apple|Amiga|Atari|Archimedes|Amstrad CPC|€š¤à©«¦"l [0;47;30m   (space š ˜ ˜¢¢˜šã)  [1;37m³ [0m
[30;47m ³                                                                          [0;1;47;37m³ [0m
[30;47m ³  Ctrl-R š ˜ ™¦ãŸœ ˜              [0;1;42;33m@14;"OK"b[0;47;30mÜ    [0;1;41;33m@14;"Cancel"b[0;47;30mÜ  [0;1;47;37m³ [0m
[30;47m ³                                   ßßßßßßßßßßßßßßßß     ßßßßßßßßßßßßßßßß  [0;1;47;37m³ [0m
[30;47m À[0;1;37;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0m} T Account edit visual template


SEXM {€¤›¨˜ª} T String for 'male' in edit templates
SEXF {‚¬¤˜å¡˜} T String for 'female' in edit templates

SYS1 {IBM compatible} T String for system type #1 in edit templates
SYS2 {Apple Mac} T String for system type #2 in edit templates
SYS3 {Old Apple} T String for system type #3 in edit templates
SYS4 {Amiga} T String for system type #4 in edit templates
SYS5 {Atari} T String for system type #5 in edit templates
SYS6 {Archimedes} T String for system type #6 in edit templates
SYS7 {Amstrad CPC} T String for system type #7 in edit templates
SYS8 {€š¤à©«¦} T String for system type #8 (unknown) in edit templates


ACCLT {[2J[0;30;47m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [34m‘«¦ ®œå˜ ¢¦š˜¨ ˜©£¦ç[0;30;47m ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;1;37;47m¿ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  [31m1[30m. ¤¦£˜«œ§é¤¬£¦ . . . . . . . . .  [34m@31;31;0s[0;1;47;37m     ³ [0m
[30;47m ³  [31m2[30m. „«˜ ¨å˜  . . . . . . . . . . . . [34m@31;31;0s[0;1;47;37m     ³ [0m
[30;47m ³  [31m3[30m. ƒ œçŸ¬¤© (š¨˜££ã 1 ˜§æ 2)  . .  [34m@31;31;0s[0;1;47;37m     ³ [0m
[30;47m ³  [31m4[30m. ƒ œçŸ¬¤© (š¨˜££ã 2 ˜§æ 2) . . . [34m@31;31;0s[0;1;47;37m     ³ [0m
[30;47m ³  [31m5[30m. ’¢â­à¤¦  . . . . . . . . . . .  [34m@23;23;0s[0;1;47;37m             ³ [0m
[30;47m ³  [31m6[30m. †¢ ¡å˜ . . . . . . . . . . . . . [34m@2;1;99;0n[0;47;30m                                  [1;37m³ [0m
[30;47m ³  [31m7[30m. ”ç¢¦  . . . . . . . . . . . . .  [34m@7;"€¤›¨˜ª|‚¬¤˜å¡˜"l                             [1;37m³ [0m
[30;47m ³  [31m8[30m. †¢œ¡«¨¦¤ ¡æª “§¦¢¦š ©«ãª . . . . [34m@14;"IBM compatible|Apple Mac|Old Apple|Amiga|Atari|Archimedes|Amstrad CPC|€š¤à©«¦"l                      [1;37m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m À[0;1;37;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0;1m
} T Account edit linear template


NEWUSN {[0;1m
!Wƒé©«œ «¦ ˜¤˜¤œà£â¤¦ ©˜ª æ¤¦£˜.!)
} T Account edit, ask user for their new name


NEWCMP {[0;1m
!Wƒé©«œ «¦ ¤â¦ æ¤¦£˜ «ª œ«˜ ¨å˜ª ©˜ª.!)
} T Account edit, ask user for their new company name


NEWADR1 {[0;1m
!Wƒé©«œ «¤ ¤â˜ › œçŸ¬¤©ã ©˜ª (¦›æ ¡˜  ˜¨ Ÿ£æ).!)
} T Account edit, ask user for new address line 1


NEWADR2 {[0;1m
!Wƒé©«œ «¤ ¤â˜ §æ¢ ¡˜  «¦¤ «˜®¬›¨¦£ ¡æ ¡é› ¡á ©˜ª.!)
} T Account edit, ask user for new address line 2


NEWPHN {[0;1m
!Wƒé©«œ «¦¤ ¤â¦ ©˜ª ˜¨ Ÿ£æ «¢œ­é¤¦¬.!)
} T Account edit, asking user for new phone number


NEWAGE {[0;1m
!W•¨æ¤ ˜ §¦¢¢á! æ©¦ ®¨æ¤à¤ šå¤˜«œ;!)
} T Account edit, asking user for new age


NEWSEX {[0;1m
!W‚¨á¯«œ £˜ª «¦ ¤â¦ ©˜ª... ­ç¢¦.!)
} T Account edit, asking user for their new sex


NEWSYS {[0;1m
!)‹œ šœ á ¦ ¤â¦ª ©˜ª ¢œ¡«¨¦¤ ¡æª ¬§¦¢¦š ©«ãª. ’  œå›¦ª œå¤˜ ;!)
} T Account edit, asking user for their new system type


EDITCAN {[0;1;31m
!W  ˜¢¢˜šâª ˜¡¬¨éŸ¡˜¤.!)
[0;1m} T After data entry: Changes cancelled.


EDITOK {[0;1;32m
!W’˜ ©«¦ ®œå˜ ©˜ª œ¤£œ¨éŸ¡˜¤.!)
[0;1m} T After data entry: Changes updated


PSCUR {[0;1m
ƒé©«œ «¦ «¨â®¦¤ ©ç¤Ÿ£á ©˜ª (›œ¤ Ÿ˜ ™¢â§œ«œ «¦¬ª ®˜¨˜¡«ã¨œª): [0m} T Enter your current password


CPSERR {[0;1;31m
’¦ ©ç¤Ÿ£˜ §¦¬ ›é©˜«œ ›œ¤ œå¤˜  ©à©«æ.
[0;1m} T Wrong password entered.


PREPSW {[0;1;32m
!J˜¨˜¡˜¢é ›é©«œ «¦ ¤â¦ ©˜ª ©ç¤Ÿ£˜. ‰á¤«œ «¦ ©ç¤Ÿ£á ©˜ª £ ¡¨æ
š ˜ ¤˜ «¦ Ÿ¬£á©«œ œ©œåª ˜¢¢á æ®  ¡˜  ¤˜ «¦ £˜¤«œç¦¬¤ á¢¢¦  œç¡¦¢˜. †
˜©­á¢œ ˜ «¦¬ ¢¦š˜¨ ˜©£¦ç ©˜ª âš¡œ «˜  ©«¦ ¤˜ £¤ ¥â¨œ  [37m¡˜¤œåª[32m
á¢¢¦ª «¦ ©ç¤Ÿ£á ©˜ª.[0;1m!)
[0;1m} T Hints about thinking up passwords


RECPSW {[0;1;32m
[37;5mÛÛ[0;1;32m  † ™á© ©˜ª §¨¦«œå¤œ  «¦ œ¥ãª ©ç¤Ÿ£˜: [37m%s[32m

!J‹§¦¨œå«œ ¤˜ «¦ ®¨© £¦§¦ ã©œ«œ ¦¢æ¡¢¨¦, £â¨¦ª «¦¬, ã ¤˜ ›é©œ«œ â¤˜ «œ¢œåàª
› ˜­¦¨œ« ¡æ ©ç¤Ÿ£˜. ’¦ §¨¦«œ ¤æ£œ¤¦  ©ç¤Ÿ£˜, §á¤«àª, œå¤˜  ©®œ« ¡á œç¡¦¢¦
¤˜ «¦ Ÿ¬£á©«œ, ¡˜  œ¤«¬§à© ˜¡á ›ç©¡¦¢¦ ¤˜ «¦ ™¨œ  ¡á§¦ ¦ª ¡˜¡æ™¦¬¢¦ª.!)
[0;1m} T Recommend a random password


FRCPSW {[0;1;32m
!J‚ ˜ ¢æš¦¬ª ˜©­˜¢œå˜ª, ›œ¤ £§¦¨œå«œ ¤˜ ›é©œ«œ ¦ å› ¦ª «¦ ©ç¤Ÿ£á ©˜ª,
˜¢¢á ©˜ª ˜¤˜Ÿâ«œ  â¤˜ ©ç¤Ÿ£˜  ™á©. ’¦ ©ç¤Ÿ£˜ §¦¬ ©˜ª â®¦¬£œ ›é©œ 
œå¤˜  ©®œ« ¡á œç¡¦¢¦ ¤˜ «¦ Ÿ¬£á©«œ ¡˜  œ¤«¬§à© ˜¡á ›ç©¡¦¢¦ ¤˜ «¦ ™¨œ 
¡á§¦ ¦ª ¡˜¡æ™¦¬¢¦ª.!)

[37;5mÛÛ[0;1;32m  † ™á© ©˜ª â®œ  ›é©œ  «¦ œ¥ãª ©ç¤Ÿ£˜: [37m%s[32m
[0;1m} T Random password forcibly assigned


GPSWORD {[0;1m

!W[Aƒé©«œ «¦ ©ç¤Ÿ£˜ §¦¬ Ÿ˜ ®¨© £¦§¦ œå«œ: [0m!)} T Asking a user to choose a password


GPSWAGN {[0;1m

!W[A˜¤˜›é©«œ «¦ ©ç¤Ÿ£˜ š ˜ œ§˜¢ãŸœ¬©:    [0m!)} T Ask again for password verification


BADPSW1 {[0;1;31m
!J’¦ ©ç¤Ÿ£á ©˜ª §¨â§œ  ¤˜ â®œ  «¦¬¢á® ©«¦¤ [37m5[31m ®˜¨˜¡«ã¨œª. ‰˜¢ã
 ›â˜ œå¤˜ , œ§å©ª, ¤˜ §œ¨ ¢˜£™á¤œ   [37m˜¨ Ÿ£¦çª ã „¢¢¤ ¡á š¨á££˜«˜[31m.!)
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


BADPSW4 {[0;1;31m
!J’¦ ¤â¦ ©˜ª ©ç¤Ÿ£˜ ›œ¤ £§¦¨œå ¤˜ œå¤˜  å› ¦ £œ «¦ §˜¢ æ. ˜¨˜¡˜¢é
¥˜¤˜›¦¡ £á©«œ ˜§æ «¤ ˜¨®ã.
[0;1m!)
} T New password must be different than old password


PNOTSET {[0;1;31m
’¦ ©ç¤Ÿ£á ©˜ª ›œ¤ á¢¢˜¥œ.
[0;1m} T Password not changed


PSWEPI {[0;1;32m
’¦ ©ç¤Ÿ£á ©˜ª á¢¢˜¥œ œ§ «¬®éª.
[0;1m} T Password changed successfully


PSWKO {[0;1;31m
!J‚ ˜ «¨å« ­¦¨á ¡á¤˜«œ ¢áŸ¦ª. ƒ¬©«¬®éª ›œ¤ £§¦¨¦ç£œ ¤˜ ©˜ª
œ§ «¨â¯¦¬£œ ¤˜ ˜¢¢á¥œ«œ «¦ ©ç¤Ÿ£á ©˜ª ˜¤ ›œ¤ ˜§¦›œå¥œ«œ æ«  œ©œåª œå©«œ ¦
¤æ£ £¦ª š¤é©«ª «¦¬, ¡˜  š ˜ ¢æš¦¬ª ˜©­˜¢œå˜ª ›œ¤ £§¦¨¦ç£œ ¤˜ ©˜ª ˜­ã©¦¬£œ
¤˜ £§œå«œ ©«¤ ™á© ˜¤ ›œ¤ ˜¢¢á¥œ«œ «¦ ¢ã¥˜¤ ©¬¤Ÿ£á ©˜ª. ˜¨˜¡˜¢¦ç£œ
¥˜¤˜¡˜¢â©«œ æ«˜¤ Ÿ˜ œå©«œ ©œ Ÿâ© ¤˜ ›é©œ«œ «¦ ©ç¤Ÿ£á ©˜ª.!)
[0;1m

} T Password wrong during login change, kicking you out


PRFVT {[0;30;47m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [34m¨¦©à§ ¡âª §¨¦« £ã©œ ª[0;30;47m ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;1;37;47m¿ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  ANSI š¨˜­ ¡á . . . . . . . . . . . . .  [0;46;30m @7;"ON|OFF|Default|Ask"l [47m   (space š ˜ ˜¢¢˜šã)[1;37m  ³ [0m
[30;47m ³  Font/«œ¨£˜« ¡æ/œå›¦ª ©ç¤›œ©ª . . . . . [0;46;30m @21;"„¢¢¤ ¡á 437G/737|„¢¢¤ ¡á „Š’/ISO|437 PC ®à¨åª „¢¢¤ ¡á|7-bit ASCII|Default|Ask"l [47m       [1;37m  ³ [0m
[30;47m ³  „£­á¤ © ¡œ £â¤¦¬ ®à¨åª §˜ç©œ ª  . . .  [0;46;30m [@"X "t] [1;47;37m                           ³ [0m
[30;47m ³  Full Screen œ¨š˜¢œå˜  . . . . . . . . . [0;46;30m [@"X "t] [1;47;37m                           ³ [0m
[30;47m ³  ‚¢é©©˜/’œ¨£˜« ¡æ . . . . . . . . . . .  [0;46;30m @16;"„¢¢¤ ¡á|English"l [1;47;37m              ³ [0m
[30;47m ³  ƒ ˜©«á©œ ª ¦Ÿæ¤ª (©«ã¢œª x š¨˜££âª)  . [1;44;37m@3;20;250;0n[0;30;47m x [1;44;37m@3;5;250;0n[0;30;47m                   [1;37m³ [0m
[30;47m ³  €¨® ¡ã ¡˜«á©«˜© ¡¢ã©œà¤ (pages) . . .  [0;46;30m @5;"OFF|ON|OK|STORE"l [47m     (space š ˜ ˜¢¢˜šã)  [1;37m³ [0m
[30;47m ³  •¨æ¤¦ª £œ«˜¥ç ¡¢ã©œà¤ (¢œ§«á) . . . . . [1;44;37m@1;1;9;0n[0;47;30m                             [1;37m³ [0m
[30;47m ³                                                                          [0;1;47;37m³ [0m
[30;47m ³  Ctrl-R š ˜ ™¦ãŸœ ˜              [0;1;42;33m@14;"OK"b[0;47;30mÜ    [0;1;41;33m@14;"Cancel"b[0;47;30mÜ  [0;1;47;37m³ [0m
[30;47m ³                                   ßßßßßßßßßßßßßßßß     ßßßßßßßßßßßßßßßß  [0;1;47;37m³ [0m
[30;47m À[0;1;37;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0m} T Preference edit visual template


ANSON {ON} T String for ANSI ON in edit templates
ANSOFF {OFF} T String for ANSI OFF in edit templates
ANSDEF {Default} T String for ANSI Default in edit templates
ANSASK {Ask} T String for ANSI Ask in edit templates

TR0 {} T String for translation table #0 in edit templates
TR1 {„¢¢¤ ¡á 437G/737} T String for translation table #1 in edit templates
TR2 {„¢¢¤ ¡á „Š’/ISO} T String for translation table #2 in edit templates
TR3 {437 PC ®à¨åª „¢¢¤ ¡á} T String for translation table #3 in edit templates
TR4 {7-bit ASCII} T String for translation table #4 in edit templates
TR5 {} T String for translation table #5 in edit templates
TR6 {} T String for translation table #6 in edit templates
TR7 {} T String for translation table #7 in edit templates
TR8 {} T String for translation table #8 in edit templates
TR9 {} T String for translation table #9 in edit templates
TRDEF {Default} T String for Default translation in edit templates
TRASK {Ask} T String for "Ask" "translation" (asking for one at login)

LANG1 {„¢¢¤ ¡á} T String for Language 1 in edit templates
LANG2 {English} T String for Language 2 in edit templates
LANG3 {} T String for Language 3 in edit templates
LANG4 {} T String for Language 4 in edit templates
LANG5 {} T String for Language 5 in edit templates
LANG6 {} T String for Language 6 in edit templates
LANG7 {} T String for Language 7 in edit templates
LANG8 {} T String for Language 8 in edit templates
LANG9 {} T String for Language 9 in edit templates
LANG10 {} T String for Language 10 in edit templates

PGSSTR {STORE} T String for page STORE state in edit templates
PGSOK {OK} T String for page OK state in edit templates
PGSON {ON} T String for page ON state in edit templates
PGSOFF {OFF} T String for page OFF state in edit templates


PRFLT {[2J[0;30;47m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [34m¨¦©à§ ¡âª §¨¦« £ã©œ ª[0;30;47m ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;1;37;47m¿ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  [31m1[30m. ANSI š¨˜­ ¡á . . . . . . . . . . . . .  [34m@7;"ON|OFF|Default|Ask"l [47m                   [1;37m  ³ [0m
[30;47m ³  [31m2[30m. Font/«œ¨£˜« ¡æ/œå›¦ª ©ç¤›œ©ª . . . . . [34m@21;"„¢¢¤ ¡á 437G/737|„¢¢¤ ¡á „Š’/ISO|437 PC ®à¨åª „¢¢¤ ¡á|7-bit ASCII|Default|Ask"l      [1;37m  ³ [0m
[30;47m ³  [31m3[30m. „£­á¤ © ¡œ £â¤¦¬ ®à¨åª §˜ç©œ ª . . . . [34m@"X "t                          [1;37m³ [0m
[30;47m ³  [31m4[30m. Full Screen œ¨š˜¢œå˜ . . . . . . . . .  [34m@"X "t                          [1;37m³ [0m
[30;47m ³  [31m5[30m. ‚¢é©©˜/’œ¨£˜« ¡æ  . . . . . . . . . . . [34m@16;"„¢¢¤ ¡á|English"l             [1;37m³ [0m
[30;47m ³  [31m6[30m. ƒ ˜©«á©œ ª ¦Ÿæ¤ª (©«ã¢œª) . . . . . .  [34m@3;20;250;0n[0;30;47m                          [1;37m³ [0m
[30;47m ³  [31m7[30m. ƒ ˜©«á©œ ª ¦Ÿæ¤ª (š¨˜££âª) . . . . . . [34m@3;5;250;0n[0;30;47m                          [1;37m³ [0m
[30;47m ³  [31m8[30m. €¨® ¡ã ¡˜«á©«˜© ¡¢ã©œà¤ (pages) . . .  [34m@5;"OFF|ON|OK|STORE"l [47m                       [1;37m³ [0m
[30;47m ³  [31m9[30m. •¨æ¤¦ª £œ«˜¥ç ¡¢ã©œà¤ (¢œ§«á) . . . . . [34m@1;1;9;0n                            [1;37m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m À[0;1;37;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0;1m
} T Preference edit linear template


NEWANS {[0;1m
!J€¬«ã  œ§ ¢¦šã œ¢âš®œ  «¤ ˜§¦©«¦¢ã ã £ ANSI (VT-102) œ¤«¦¢é¤ ©«¦
«œ¨£˜« ¡æ ©˜ª. ‘«¤ Ÿâ© 'ON', æ¢¦  ¦  ANSI ¡à› ¡¦å ˜§¦©«â¢¦¤«˜ . ‘«¤ Ÿâ©
'OFF', ¦  œ¤«¦¢âª ANSI ˜­˜ ¨¦ç¤«˜  ˜¬«æ£˜«˜. ‘«¤ Ÿâ© 'DEFAULT',  ¨çŸ£ ©
œ¥˜¨«á«˜  ˜§æ «¤ ˜¨® ¡ã ¨çŸ£ © «ª š¨˜££ãª ©«¤ ¦§¦å˜ ©¬¤›âœ©«œ
( ©®çœ  ˜§æ «¤ œ§æ£œ¤ã ©˜ª ©ç¤›œ©). ‘«¤ Ÿâ© 'ASK', «¦ ©ç©«£˜
©˜ª ¨à«áœ  ˜¤ Ÿâ¢œ«œ ANSI ¬§¦©«ã¨ ¥ ©œ ¡áŸœ ©ç¤›œ©ã ©˜ª.!)

!J  ›ç¦ «œ¢œ¬«˜åœª ¨¬Ÿ£å©œ ª ƒ„Œ ˜¢¢á¦¬¤ «¤ ¬§¦©«ã¨ ¥ ANSI š¨˜­ ¡é¤
š ˜ ˜¬«ã ©˜ª « ©ç¤›œ©.!)
} T Preference edit, info on ANSI setting


NEWXLT {[0;1m
!J‹œ ˜¬«ã «¤ œ§ ¢¦šã £§¦¨œå«œ ¤˜ «ã©œ«œ ˜§æ «¦ ©ç©«£˜ ¤˜ ©˜ª £œ«˜­¨áœ 
«¦¬ª ®˜¨˜¡«ã¨œª §¦¬ ™¢â§œ«œ, ©œ §œ¨å§«à© §¦¬ ›œ¤ â®œ«œ „¢¢¤ ¡á, ã ˜¤ «¦
«œ¨£˜« ¡æ ©˜ª ›œ¤ ¬§¦©«¨åœ  «¦¬ª ®˜¨˜¡«ã¨œª §¦¬ ©«â¢¤œ   ™á©.!)

!J„§ ¢â¥«œ '[33m„¢¢¤ ¡á 437G/737[37m' ˜¤ â®œ«œ 8-bit IBM ASCII £œ „¢¢¤ ¡æ
('437G' ©¬£™˜«æ) font. „§ ¢â¥«œ '[33m„¢¢¤ ¡á „Š’/ISO[37m' ˜¤
®¨© £¦§¦ œå«œ «¦ §¨æ«¬§¦ „Š’-928 ã ISO-8859-7 ã codepage 928. €¤ â®œ«œ £œ¤
IBM ASCII ˜¢¢á æ®  „¢¢¤ ¡¦çª ®˜¨˜¡«ã¨œª, ›¦¡ £á©«œ «¦ '[33m437 PC ®à¨åª
„¢¢¤ ¡á[37m'. ’â¢¦ª, ˜¤ ›œ¤ â®œ«œ ¦ç«œ PC font ¦ç«œ „¢¢¤ ¡á, › ˜¢â¥«œ «¦
'[33m7-bit ASCII[37m'.!)

!J† œ§ ¢¦šã '[33mDefault[37m' ¨¬Ÿ£åœ  ˜¬«æ£˜«˜ «¤ £œ«á­¨˜© ˜¤á¢¦š˜ £œ
«¤ š¨˜££ã §¦¬ ©¬¤›âœ©«œ. † œ§ ¢¦šã '[33mAsk[37m' ¡á¤œ  «¦ ©ç©«£˜ ¤˜ ©˜ª
¨à«áœ  «  œå›¦¬ª £œ«á­¨˜© Ÿâ¢œ«œ ©œ ¡áŸœ ©˜ª ©ç¤›œ©. €¬«âª ¦  ›ç¦ œ§ ¢¦šâª
›œ¤ ˜¢¢á¦¬¤ «¤ £œ«á­¨˜© ©œ ˜¬«ã ©˜ª « ©ç¤›œ©.!)
} T Preference edit, info on translation setting



NEWNPS {[0;1m
!J€¤ œ¤œ¨š¦§¦ ã©œ«œ ˜¬«ã «¤ œ§ ¢¦šã, «¦ ©ç©«£˜ ›œ¤ Ÿ˜ ©«˜£˜«áœ 
«¤ œ£­á¤ © ¡œ £â¤¦¬, æ«˜¤ ˜¬«æ œå¤˜  £œš˜¢ç«œ¨¦ ˜§æ £å˜ ¦Ÿæ¤. €¬«æ
œå¤˜  ¡á«  §¦¬ ›œ¤ ©¬¤ ©«¦ç£œ, š ˜«å Ÿ˜ ®á¤œ«œ §á¨˜ §¦¢¢á £¤ç£˜«˜ «¦¬
©¬©«ã£˜«¦ª. † œ§ ¢¦šã ˜¬«ã œå¤˜  ®¨ã© £ š ˜ ¤˜ ¡¨˜«á«œ captures ˜§æ
› á­¦¨œª §œ¨ ¦®âª «ª ™á©ª ®à¨åª §˜ç©œ ª.!)
} T Preference edit, info on no-screen-pause setting


NEWFST {[0;1m
!J€¤ «¦ «œ¨£˜« ¡æ ©˜ª ¬§¦©«¨åœ  ANSI (VT-102) š¨˜­ ¡á,
IBM extended character set, ¡˜  â®œ   ¡˜¤¦§¦ « ¡ã «˜®ç««˜ œ§ ¡¦ ¤à¤å˜ª,
©¬¤ ©«¦ç£œ ¤˜ œ¤œ¨š¦§¦ ã©œ«œ ˜¬«ã «¤ œ§ ¢¦šã: Ÿ˜ ©˜ª œ§ «¨â¯œ  ¤˜
®¨© £¦§¦ œå«œ «˜ full screen œ¨š˜¢œå˜ «ª ™á©ª (editors, viewers, dialog
boxes, ¡¢§), ©œ ˜¤«åŸœ© £œ «˜ §˜¢ á, linear ¬§¦©¬©«ã£˜«˜.!)
} T Preference edit, info on full screen tools


NEWLAN {[0;1m
!J˜¨˜¡˜¢é › ˜¢â¥«œ «¤ š¢é©©˜ ©«¤ ¦§¦å˜ Ÿâ¢œ«œ ¤˜ ¢˜£™á¤œ«œ «˜ £¤ç£˜«˜
«ª ™á©ª.!)
} T Preference edit, choosing a new language


NEWSWD {[0;1m
!J˜¨˜¡˜¢é ›é©«œ «¦¤ ˜¨ Ÿ£æ [32m©«¢é¤[37m §¦¬ £§¦¨œå ¤˜ ˜§œ ¡¦¤å©œ  
¦Ÿæ¤ ©˜ª. ‚ ˜ §˜¨á›œ š£˜, ˜¤  ¦Ÿæ¤ ©˜ª ˜§œ ¡¦¤åœ  80x25 ®˜¨˜¡«ã¨œª, ›é©«œ
80.!)
} T Preference edit, entering new screen width


NEWSHT {[0;1m
!J˜¨˜¡˜¢é ›é©«œ «¦¤ ˜¨ Ÿ£æ [32mš¨˜££é¤[37m §¦¬ £§¦¨œå ¤˜ ˜§œ ¡¦¤å©œ  
¦Ÿæ¤ ©˜ª. ‚ ˜ §˜¨á›œ š£˜, ˜¤  ¦Ÿæ¤ ©˜ª ˜§œ ¡¦¤åœ  80x25 ®˜¨˜¡«ã¨œª, ›é©«œ
25. ‹§¦¨œå ¤˜ Ÿâ¢œ«œ ¤˜ ›¢é©œ«œ £å˜ ã ›ç¦ š¨˜££âª ¢ šæ«œ¨œª ˜§æ «¦
§¨˜š£˜« ¡æ £âšœŸ¦ª «ª ¦Ÿæ¤ª ©˜ª, ˜¤ «¦ §¨æš¨˜££˜ œ§ ¡¦ ¤à¤ é¤ ©˜ª
®¨© £¦§¦ œå £å˜ ã ›ç¦ š¨˜££âª š ˜ ˜§œ ¡æ¤ © › ¡é¤ «¦¬ ›œ›¦£â¤à¤.!)
} T Preference edit, entering new screen width


NEWPGS {[0;1m
!J† œ§ ¢¦šã ˜¬«ã ¦¨åœ  ˜¤ Ÿ˜ ›â®œ©«œ ¡¢ã©œ ª ©«¤ ˜¨®ã «ª ©ç¤›œ©ãª ©˜ª.
‹œ ˜¬«ã «¤ œ§ ¢¦šã ƒ„Œ ˜¢¢áœ   «¨â®¦¬©˜ œ§ ¢¦šã ©˜ª (›é©«œ /p š ˜ ¤˜
«¤ ˜¢¢á¥œ«œ). ‹œ«˜™á¢¢œ«˜  £æ¤¦  œ§ ¢¦šã §¦¬ Ÿ˜ œå¤˜  œ¤œ¨šã ˜£â©àª ˜­¦ç
©¬¤›œŸœå«œ.!)

!J  œ§ ¢¦šâª â®¦¬¤ àª œ¥ãª: OFF: ƒœ¤ ›â®œ©«œ ¡˜Ÿæ¢¦¬ ¡¢ã©œ ª. ON:
ƒâ®œ©«œ ¡¢ã©œ ª, ˜¢¢á £œ«˜¥ç ¡¢ã©œà¤ £œ©¦¢˜™œå ¬§¦®¨œà« ¡á â¤˜ª ˜¨ Ÿ£æª
¢œ§«é¤ (§¦¬ ¦¨åœ«œ £œ «¤ œ§ ¢¦šã 8). OK: ƒâ®œ©«œ ¡¢ã©œ ª ®à¨åª æ¨ ˜.
STORE:   ¡¢ã©œ ª §¨¦ª œ©áª ˜§¦Ÿ¡œç¦¤«˜  ©œ §œ¨å§«à© §¦¬ ›œ¤ £§¦¨œå«œ ¤˜
œ¤¦®¢Ÿœå«œ, ¡˜  ©˜ª £œ«˜›å›¦¤«˜  ˜¨šæ«œ¨˜.!)
} T Preference edit, entering new default page state


NEWPGT {[0;1m
!J˜¨˜¡˜¢é ›é©«œ «¦¤ ˜¨ Ÿ£æ ¢œ§«é¤ §¦¬ Ÿ˜ £œ©¦¢˜™¦ç¤ £œ«˜¥ç «¬®æ¤ ¡¢ã©œà¤
§¨¦ª œ©áª (¦ ˜¨ Ÿ£æª ˜¬«æª  ©®çœ  £æ¤¦ æ«˜¤  ¡˜«á©«˜© ¡¢ã©œé¤ ©˜ª œå¤˜ 
©«¤ Ÿâ© 'ON').!)
} T Preference edit, entering new inter-page time





XFERR1 {[0;1;31m
!JŠ¬§á£˜ , ˜¢¢á §¨â§œ  ¤˜ â®œ«œ «¦¬¢á® ©«¦¤ %d credits š ˜ ¤˜ £§¦¨â©œ«œ
¤˜ £œ«˜­â¨œ«œ. €¬«æ œå¤˜  ¡˜  «¦ œ¢á® ©«¦ §¦©æ £œ«˜­¦¨áª £¦¤á›à¤.!)[0;1m
} T Credit transfer, insufficient credits for transferring


XFERR2 {[0;1;31m
!JŠ¬§á£˜ , ˜¢¢á «¦ œ§å§œ›æ ©˜ª ›œ¤ ©˜ª œ§ «¨â§œ  ¤˜ £œ«˜­â¨œ«œ £¦¤á›œª.!)[0;1m
} T Credit transfer, user not allowed to transfer their credits


XFERR3 {[0;1;31m
!JŠ¬§á£˜ , ˜¢¢á ›œ¤ â®œ«œ ˜š¦¨á©œ  (paid) £¦¤á›œª, ¡  â«©  ›œ¤ £§¦¨œå«œ ¤˜
£œ«˜­â¨œ«œ. ƒœ¤ Ÿ˜ ã«˜¤ ›å¡˜ ¦, á¢¢à©«œ, ˜­¦ç ¦ •œ ¨ ©«ãª ‘¬©«ã£˜«¦ª
§˜¨˜®é¨©œ £¦¤á›œª £æ¤¦ š ˜ §¨¦©à§ ¡ã ©˜ª ®¨ã©. ‚ ˜ ¤˜ £áŸœ«œ §éª ¤˜
˜§¦¡«ã©œ«œ paid £¦¤á›œª ©«¤ @BBS@, §˜¨˜¡˜¢¦ç£œ ˜¤˜«¨â¥«œ ©« ª [37m¢¨¦­¦¨åœª
‘¬©«ã£˜«¦ª[31m ([33m/go info[31m).!)[0;1m
} T Credit transfer, user not allowed to transfer their credits


CREDTR {[0;1m
!J€¬«ã  œ§ ¢¦šã ®¨© £œçœ  š ˜ ¤˜ ›é©œ«œ ®¨æ¤¦ ®¨ã©ª ©œ
¡á§¦ ¦¤ á¢¢¦ ®¨ã©«.!)

!Wæ©˜ ¢œ§«á ®¨ã©ª Ÿâ¢œ«œ ¤˜ £œ«˜­â¨œ«œ;!) [0m} T Credit transfer, how many credits to transfer?


NUMERR {[0;1;31m
!W˜¨˜¡˜¢é ›é©«œ â¤˜¤ ˜¨ Ÿ£æ £œ«˜¥ç %d ¡˜  %d. €¢¢ éª ›é©«œ
[33mX[31m š ˜ â¥¦›¦.!)
} T Credit transfer, invalid number of credits


RANOUT {[0;1;31m
!Jƒ¬©«¬®éª ›œ¤ â®œ«œ §¢â¦¤ ˜¨¡œ«æ ®¨æ¤¦ ®¨ã©ª, ¦§æ«œ ›œ¤ ¬§á¨®œ  ¡˜  ¢æš¦ª
£œ«˜­¦¨áª. œ¨ ©©æ«œ¨œª §¢¨¦­¦¨åœª š ˜ «¦ §éª £§¦¨œå«œ ¤˜ ˜§¦¡«ã©œ«œ
§œ¨ ©©æ«œ¨¦ ®¨æ¤¦ ®¨ã©ª £§¦¨œå«œ ¤˜ ™¨œå«œ ˜§æ «¤ œ§ ¢¦šã [33mI[31m «¦¬
¡œ¤«¨ ¡¦ç £œ¤¦ç.!)
[0;1m} T Credit transfer, just barely too many credits


CTWHO {[0;1m
!W‘œ §¦ æ ¯œ¬›é¤¬£¦ Ÿâ¢œ«œ ¤˜ £œ«˜­â¨œ«œ ®¨æ¤¦ ®¨ã©ª;!)[0m } T Credit transfer, Asking to whom to transfer credits


CTNSELF {[0;1;31m
!W’  ¤æ£˜ â®œ  ¤˜ ›é©œ«œ ®¨æ¤¦ ®¨ã©ª ©«¦¤ œ˜¬«æ ©˜ª;!)
} T Credit transfer, Can't transfer credits to yourself


UIDERR {[0;1;31m
!Wƒœ¤ ¬§á¨®œ  «â«¦ ¦ ¯œ¬›é¤¬£¦. ˜¤˜›¦¡ £á©«œ, ã ›é©«œ [33mX[31m š ˜
â¥¦›¦.!)
[0;1m} T Credit transfer, user ID does not exist


CTWARN {
!J[0;1;31;5mÛÛ[0;1;31m  ‘•†:  !i’¦ £â¢¦ª %s ›œ¤ Ÿ˜ £§¦¨â©œ 
¤˜ ©˜ª œ§ ©«¨â¯œ  «˜ ¢œ§«á ®¨ã©ª §¦¬ Ÿâ¢œ«œ ¤˜ «¦¬ ›é©œ«œ.!)
!0l[0;1m} T Credit transfer, transferring to user who can't transfer back


CTCONF {[0;1;33m
!W’œ¢ ¡æª â¢œš®¦ª: [37m!i‡â¢œ«œ ¤˜ £œ«˜­â¨œ«œ [32m%d[37m ¢œ§«á ®¨ã©ª ˜§æ «¦
¯œ¬›é¤¬£¦ [32m%s[37m ©«¦ ¯œ¬›é¤¬£¦ [32m%s[37m.!)
!0l[0;1m} T Credit transfer, final confirmation.


CTCQUE {[0;1m
!W„å¤˜  ©à©«æ ˜¬«æ; ([[33mY[0;1m]es=¤˜  / [[33mN[0;1m]o=æ® )!)[0m } T Credit transfer, asking for confirmation


BOOLERR {[0;1;31m
!W˜¨˜¡˜¢é ˜§˜¤«ã©«œ ©«¤ œ¨é«© £œ [33mY[31mes=¤˜ , ã
[[33mN[31m]o=æ® .!)
[0;1m} T Credit transfer, wrong answer to confirmation question


ACCDEL {[0;1;31m
!WŠ¬§á£˜ , ˜¢¢á «¦ ¯œ¬›é¤¬£¦ "%s" £æ¢ ª › ˜š¨á­¡œ.
ƒœ¤ âš ¤œ £œ«˜­¦¨á £¦¤á›à¤.!)
[0;1m} T Credit transfer, user deleted, no transfer


NOENOT {[0;1;33m
!W‘«æ ®¨¦¤ ¡æ › á©«£˜ §¦¬ ˜§¦­˜©å˜«œ «¦¤ §˜¨˜¢ã§« ¦ ®¨æ¤¦ª ®¨ã©ª ©˜ª
£œ éŸ¡œ ©œ %d ¢œ§«á. “§¦Ÿâ«¦¤«˜ª æ«  Ÿâ¢˜«œ ¤˜ «˜ £œ«˜­â¨œ«œ æ¢˜, «˜
£œ«˜­â¨˜£œ.!)
[0;1m} T Credit transfer, transfer amount truncated


CXFOK {[0;1;32m
!W„§ ™œ™˜åà©: !i[37m%d[32m ¢œ§«á £œ«˜­â¨Ÿ¡˜¤ ˜§æ «¦
¯œ¬›é¤¬£¦ [37m%s[32m ©«¦ ¯œ¬›é¤¬£¦ [37m%s[32m.!)
!0l[0;1m} T Credit transfer, transaction successful


CXFINJ {[0;1;35m***
’¦ £â¢¦ª [37m%s[35m £æ¢ ª ©˜ª £œ«â­œ¨œ [37m%d[35m ¢œ§«á ®¨ã©ª.
} T Credit transfer, informing online user of transfer to their account


NOTICE {[0;1m
!W’¦ £â¢¦ª %s œå¤˜  ˜¬«ã « ©« š£ã ©¬¤›œ›œ£â¤¦ ¡˜  œ ›¦§¦ ãŸ¡œ
š ˜ «¤ £œ«˜­¦¨á.!)
[0;1m} T Credit transfer, credit recipient has been notified


CXFABO {
[0;1;31mƒœ¤ âš ¤œ  £œ«˜­¦¨á ®¨æ¤¦¬. „§ ©«¨¦­ã ©«¦ §¨¦š¦ç£œ¤¦ £œ¤¦ç.
[0;1m} T Credit transfer, transfer aborted


ACCST1 {
[0;36mÛÛ  [1m‘«˜« ©« ¡á ©«¦ ®œå˜ «¦¬ ¢¦š˜¨ ˜©£¦ç ©˜ª  [46m[K[0;1m

} T Account Statistics, chunk 1


ACCST2 {!J ¢¦š˜¨ ˜©£æª ©˜ª ›£ ¦¬¨šãŸ¡œ «¤ [32m@DATECRE@[37m.
† «œ¢œ¬«˜å˜ ©ç¤›œ©ã ©˜ª ã«˜¤ «¤ [32m@DATELAST@[37m.
’¦ ¯œ¬›é¤¬£æ ©˜ª ¬§á¨®œ  ©«¤ ™á© œ›é ¡˜  [32m%d £â¨%s[37m,
¡˜  â®œ«œ ©¬¤›œŸœå [32m@NUMCONNS@ ­¦¨%s[37m.
˜¨œ§ §«æ¤«àª, «¦ ©ç¤Ÿ£á ©˜ª ¢ãšœ  ©œ [32m@UPASSEXP@ £â¨%s[37m ˜§æ ©ã£œ¨˜.!)

} T Account statistics, chunk 2


ACCST2A {!J ¢¦š˜¨ ˜©£æª ©˜ª ›£ ¦¬¨šãŸ¡œ [32m©ã£œ¨˜[37m.
’¦ ©ç¤Ÿ£á ©˜ª ¢ãšœ  ©œ [32m@UPASSEXP@ £â¨%s[37m ˜§æ ©ã£œ¨˜.!)

} T Account statistics, chunk 2 for newbies


ACCST3 {!J‘«¦¤ ¢¦š˜¨ ˜©£æ ©˜ª â®œ«œ [32m@CREDITS@ £¦¤á›%s[37m.
‘˜ª â®¦¬¤ ›¦Ÿœå ©¬¤¦¢ ¡á [32m@TOTCREDS@ £¦¤á›%s[37m,
˜§æ « ª ¦§¦åœª [32m@TOTPAID@[37m œå¤˜  'paid'.
„®œ«œ ¡˜«˜¤˜¢é©œ  ©¬¤¦¢ ¡á [32m@CREDSEVER@ £¦¤á›%s[37m,
š ˜ ©¬¤¦¢ ¡ã ©ç¤›œ© [32m@TIMEVER@ ¢œ§«%s[37m.!)

} T Account statistics, chunk 3


ACCST4 {!J‹â®¨  «é¨˜, â®œ«œ ¢á™œ  [32m@FILESDNL@ ˜¨®œå%s[37m ˜§æ «¦ ©ç©«£˜,
£œ ©¬¤¦¢ ¡æ £âšœŸ¦ª [32m@KBSDNL@ Kbytes[37m.
„®œ«œ ˜§¦©«œå¢œ  ©«¤ ™á© [32m@FILESUPL@ ˜¨®œå%s[37m,
£œ ©¬¤¦¢ ¡æ £âšœŸ¦ª [32m@KBSUPL@ Kbytes[37m.!)

} T Account statistics, chunk 4


ACCST5A {!J ¢¦š˜¨ ˜©£æª ©˜ª ˜¤ã¡œ  ©«¤ «á¥ [32m@USERCLASS@[37m. } T Account statistics, chunk 5A


ACCST5B {€¤œ¥á¨««˜ ˜§æ «¦ §æ©œª £¦¤á›œª â®œ«œ, ¬§á¨®œ  æ¨ ¦ [32m%d
¢œ§«%s[37m §˜¨˜£¦¤ãª ©˜ª ©«¤ ™á© ˜¤á ¡¢ã©. } T Account statistics, chunk 5B


ACCST5C {€¤œ¥á¨««˜ ˜§æ «¦ §æ©œª £¦¤á›œª â®œ«œ, ¬§á¨®œ  æ¨ ¦ [32m%d
¢œ§«%s[37m §˜¨˜£¦¤ãª ©˜ª ©«¤ ™á© £œ¨©åàª. } T Account statistics, chunk 5C


ACCST5D {’¦ ©ç©«£˜ ©˜ª ›å¤œ  [32m%d £¦¤á›%s[37m %s. } T Account statistics, chunk 5D


ACCST5E { ¢¦š˜¨ ˜©£æª ©˜ª â®œ  ˜£œåà«œª £¦¤á›œª. } T Account statistics, chunk 5E


ACCST5F {‘œ [32m%d £œ¨%s[37m, Ÿ˜ £œ«˜­œ¨Ÿœå«œ ©«¤ «á¥ [32m%s[37m. } T Account statistics, chunk 5F


ACCST5FT {[32m€ç¨ ¦[37m Ÿ˜ £œ«˜­œ¨Ÿœå«œ ©«¤ «á¥ [32m%s[37m. } T Account statistics, chunk 5F (tomorrow)


ACCST5G {€¤ ›œ¤ ©¬¤›œŸœå«œ š ˜ [32m%d £œ¨%s[37m, Ÿ˜ £œ«˜­œ¨Ÿœå«œ ©«¤ «á¥ [32m%s[37m. } T Account statistics, chunk 5G


ACCST5H {€¤ ©˜ª «œ¢œ é©¦¬¤ ¦  £¦¤á›œª, Ÿ˜ £œ«˜­œ¨Ÿœå«œ §¨¦©à¨ ¤á ©«¤ «á¥ [32m%s[37m. } T Account statistics, chunk 5H


ACCST5I {«˜¤ ©˜ª ›àŸ¦ç¤ paid £¦¤á›œª, Ÿ˜ £œ«˜­œ¨Ÿœå«œ ©«¤ «á¥ [32m%s[37m. } T Account statistics, chunk 5I


ACCST5J {!)

} T Account statistics, chunk 5J


ACCST6 {[0;46m[K[0;1m
} T Account statistics, chunk 6


MINSNG {¦ç} T Minutes, singular form
MINPLR {é¤} T Minutes, plural form

TIMSNG {á} T 'Times', singular form
TIMPLR {âª} T 'Times', plural form

CRDSNG {˜} T Credits, singular form
CRDPLR {œª} T Credits, plural form

FILSNG {¦} T Files, singular form
FLIPLR {˜} T Files, plural form

DAILY {£œ¨©åàª} T String for 'daily' in statistics
WEEKLY {œ™›¦£˜› ˜åàª} T String for 'weekly' in statistics
MNTHLY {£¤ ˜åàª} T String for 'monthly' in statistics


OPSWHO {[0;1;31m
[5mÛÛ  !i!J[0;1;31m† ˜¢¢˜šã ©¬¤Ÿã£˜«¦ª á¢¢¦¬ ®¨ã©« ¡˜«˜š¨á­œ«˜ .
€¤ ›œ¤ â®œ«œ «å§¦«˜ ¤˜ ¡á¤œ«œ, £¤ «¦ ¡á¤œ«œ œ›é.  ¡¦¤©¦¢ â¨ª Ÿ˜ ©˜ª ©«œå¢œ 
«¦¤ «¨¦­¦©¬¢¢â¡« «ª œ™›¦£á›˜ª £œ «¦ ¨æ§˜¢æ «¦¬. ‰€ˆ ƒ„Œ „ˆŒ€ˆ €‘’„ˆ.!)
!0l[0;1m
!Wƒé©«œ «¦ ¯œ¬›é¤¬£¦ «¦¬ ¦§¦å¦¬ «¦ ©ç¤Ÿ£˜ Ÿâ¢œ«œ ¤˜ ˜¢¢á¥œ«œ, ã 
[33mX[37m š ˜ â¥¦›¦:!) [0m} T Change someone else's password


OUIDERR {[0;1;31m
ƒœ¤ ¬§á¨®œ  «â«¦ ¦ ¯œ¬›é¤¬£¦ ©«¤ ™á©.
[0;1m} T User ID does not exist


PSWOTH {[0;1;33m
€¢¢áœ«œ «¦ ©ç¤Ÿ£˜ «¦¬ £â¢¦¬ª [37m%s[33m.
[0;1m} T Changing other user's password


LANG {}


DAYSNG {} T Days, singular form
DAYPLR {s} T Days, plural form


EXPDAYS {[0;1;36m
Your current password expires in [37m%d day%s[36m.

[0;1m} T Login: Your password expires in X days


EXPIRED {[0;1;33m
!W[5mÛÛ[0;1;33m  !iYour password has expired. Please change it as soon
as possible, for your own safety.!)

!0l[0;1m} T Login: Your password has expired


PASSEX {[0;1;31m
!JYour password has expired. Please set a new one now, before you go on...!)

[0;1m} T Login: Your password has expired, enter new one now


ACCMNU {[2J[0m[47;1;37m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;30;47m¿ [40m
[47;1;37m ³  [0;47;30m              Your Account in the System               [0;47;30m³ [40m
[47;1;37m ³  [0;47;30mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ  [0;47;30m³ [40m
[47;1;37m ³  [0;31;47mA[30mbout your account . . . . . . .  General Information  [30m³ [40m
[47;1;37m ³  [0;31;47mC[30mhange account  . . . . . . . . Update your specifics  [30m³ [40m
[47;1;37m ³  [0;31;47mP[30massword . . . . . . . . . . . . . .  Change password  [30m³ [40m
[47;1;37m ³  [0;31;47mS[30metup preferences . . . Set your personal preferences  [30m³ [40m
[47;1;37m ³  [0;31;47mT[30mransfer credits . . . . . Transfer credits to a user  [30m³ [40m
[47;1;37m ³  [0;31;47mV[30miew statistics . . . . .  Statistics on your account  [30m³ [40m
[47;1;37m ³                                                         [0;47;30m³ [40m
[47;1;37m ³ [0;30;47me[31mX[30mit  . . . . . . . . . . . . . . . Leave your Account  [30m³ [40m
[47;1;37m À[0;30;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0;1m
} T Registry main menu


VSHMENU {[0;1m
Your account in the system
Please enter your choice: [0m} T Registry menu, very short prompt


SHMENU {[0;1m
Your account in the system
!WEnter your choice ([33mA[37m,[33mC[37m,[33mP[37m,[33mS[37m,[33mT[37m,[33mV[37m,[33mX[37m to exit, or [33m?[37m for the menu): !)[0m} T Registry short menu


ACCSMNU {[2J[0m[47;1;37m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;30;47m¿ [40m
[47;1;37m ³  [0;47;30m         Your Account in the System (Sysop)            [0;47;30m³ [40m
[47;1;37m ³  [0;47;30mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ  [0;47;30m³ [40m
[47;1;37m ³  [0;31;47mA[30mbout your account . . . . . . .  General Information  [30m³ [40m
[47;1;37m ³  [0;31;47mC[30mhange account  . . . . . . . . Update your specifics  [30m³ [40m
[47;1;37m ³  [0;31;47mP[30massword . . . . . . . . . . . . . .  Change password  [30m³ [40m
[47;1;37m ³  [0;31;47mS[30metup preferences . . . Set your personal preferences  [30m³ [40m
[47;1;37m ³  [0;31;47mT[30mransfer credits . . . . . Transfer credits to a user  [30m³ [40m
[47;1;37m ³  [0;31;47mV[30miew statistics . . . . .  Statistics on your account  [30m³ [40m
[47;1;37m ³  [0;31;47mO[30mther user's password  . Change other user's password  [30m³ [40m
[47;1;37m ³                                                         [0;47;30m³ [40m
[47;1;37m ³ [0;30;47me[31mX[30mit  . . . . . . . . . . . . . . . Leave your Account  [30m³ [40m
[47;1;37m À[0;30;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0;1m
} T Registry main menu for sysops


SHSMENU {[0;1m
Your account in the system
!WPlease enter your choice ([33mA[37m,[33mC[37m,[33mP[37m,[33mS[37m,[33mT[37m,[33mV[37m,[33mO[37m,[33mX[37m to exit, or [33m?[37m for the menu): !)[0m} T Registry short menu for sysops


ERRSEL {[0;1;31m
I'm sorry, "%c" is not an option.
[0;1m} T Wrong selection from the main account menu


LEAVE {[0;1m
Leaving your account...
} T Leaving the account module


ABOUT {[0;1m

!JThis module allows you to perform a number of activities. You can update
your account in case some of its data have changed; you can set your preferences
(e.g. terminal type and language); transfer credits to other users; see statistics
about your account; and change your password.!)

!JThe information you provide here is the same you provided when you signed up.
According to your contract with @BBS@, [31myou are legally bound to observe the
truthfullness and accuracy of this information[37m. Otherwise, the System Operators
will be forced to deny you access to the system.!)

!JFor more information, please read your contract, in the Information module
([33m/go info[37m).!)
} T About the account


PASSXP {
!J[0;1;33mNote: [37m!iPasswords in @BBS@ operate on an expiry basis. This means
that you have to change your password every [32m@PASSEXP@ days[37m. This is done
for your own protection only. We apologise for any inconvenience caused.!)
!0l[0;1m} T About password expiry


PXPDAYS {[0;1;32m
Your password expires in [37m%d day%s[32m.
[0;1m} T Your password expires in N days


PEXPIRED {[0;1;31m
Your password has changed. Please change it.
[0;1m} T Your password has expired, please change it.


ACCVT {[0;30;47m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [34mYour Account[0;30;47m ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;1;37;47m¿ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  First and last name . . . . . .  [1;44;37m@31;31;0s[0;1;47;37m      ³ [0m
[30;47m ³  Company  . . . . . . . . . . . . [1;44;37m@31;31;0s[0;1;47;37m      ³ [0m
[30;47m ³  Address (line 1 of 2) . . . . .  [1;44;37m@31;31;0s[0;1;47;37m      ³ [0m
[30;47m ³  Address (line 2 of 2)  . . . . . [1;44;37m@31;31;0s[0;1;47;37m      ³ [0m
[30;47m ³  Phone number  . . . . . . . . .  [1;44;37m@23;23;0s[0;1;47;37m              ³ [0m
[30;47m ³  Age  . . . . . . . . . . . . . . [1;44;37m@2;1;99;0n[0;47;30m                           (1-99)  [1;37m³ [0m
[30;47m ³  Sex . . . . . . . . . . . . . .  [0;30;46m @7;"male|female"l [0;47;30m           (space to change)  [1;37m³ [0m
[30;47m ³  Computer type  . . . . . . . . . [0;30;46m @14;"IBM compatible|Apple Mac|Old Apple|Amiga|Atari|Archimedes|Amstrad CPC|Unknown"l [0;47;30m    (space to change)  [1;37m³ [0m
[30;47m ³                                                                          [0;1;47;37m³ [0m
[30;47m ³  Ctrl-R for help                 [0;1;42;33m@14;"OK"b[0;47;30mÜ    [0;1;41;33m@14;"Cancel"b[0;47;30mÜ  [0;1;47;37m³ [0m
[30;47m ³                                   ßßßßßßßßßßßßßßßß     ßßßßßßßßßßßßßßßß  [0;1;47;37m³ [0m
[30;47m À[0;1;37;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0m} T Account edit visual template


SEXM {Male} T String for 'male' in edit templates
SEXF {Female} T String for 'female' in edit templates

SYS1 {IBM compatible} T String for system type #1 in edit templates
SYS2 {Apple Mac} T String for system type #2 in edit templates
SYS3 {Old Apple} T String for system type #3 in edit templates
SYS4 {Amiga} T String for system type #4 in edit templates
SYS5 {Atari} T String for system type #5 in edit templates
SYS6 {Archimedes} T String for system type #6 in edit templates
SYS7 {Amstrad CPC} T String for system type #7 in edit templates
SYS8 {Unknown} T String for system type #8 (unknown) in edit templates


ACCLT {[2J[0;30;47m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [34mYour account[0;30;47m ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;1;37;47m¿ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  [31m1[30m. First and last name . . . . . .  [34m@31;31;0s[0;1;47;37m     ³ [0m
[30;47m ³  [31m2[30m. Company  . . . . . . . . . . . . [34m@31;31;0s[0;1;47;37m     ³ [0m
[30;47m ³  [31m3[30m. Address (line 1 of 2) . . . . .  [34m@31;31;0s[0;1;47;37m     ³ [0m
[30;47m ³  [31m4[30m. Address (line 2 of 2)  . . . . . [34m@31;31;0s[0;1;47;37m     ³ [0m
[30;47m ³  [31m5[30m. Phone number  . . . . . . . . .  [34m@23;23;0s[0;1;47;37m             ³ [0m
[30;47m ³  [31m6[30m. Age  . . . . . . . . . . . . . . [34m@2;1;99;0n[0;47;30m                                  [1;37m³ [0m
[30;47m ³  [31m7[30m. Sex . . . . . . . . . . . . . .  [34m@7;"€¤›¨˜ª|‚¬¤˜å¡˜"l                             [1;37m³ [0m
[30;47m ³  [31m8[30m. Computer type  . . . . . . . . . [34m@14;"IBM compatible|Apple Mac|Old Apple|Amiga|Atari|Archimedes|Amstrad CPC|€š¤à©«¦"l                      [1;37m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m À[0;1;37;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0;1m
} T Account edit linear template


NEWUSN {[0;1m
!WPlease enter your new name.!)
} T Account edit, ask user for their new name


NEWCMP {[0;1m
!WPlease enter your new company name.!)
} T Account edit, ask user for their new company name


NEWADR1 {[0;1m
!WPlease enter your new address (street).!)
} T Account edit, ask user for new address line 1


NEWADR2 {[0;1m
!WPlease enter your new area code, city, etc.!)
} T Account edit, ask user for new address line 2


NEWPHN {[0;1m
!WPlease enter your new phone number.!)
} T Account edit, asking user for new phone number


NEWAGE {[0;1m
!WHappy Birthday! How old are you now?!)
} T Account edit, asking user for new age


NEWSEX {[0;1m
!WPlease enter your new sex (!).!)
} T Account edit, asking user for their new sex


NEWSYS {[0;1m
!)What type is your new computer?!)
} T Account edit, asking user for their new system type


EDITCAN {[0;1;31m
!WThe changes were cancelled.!)
[0;1m} T After data entry: Changes cancelled.


EDITOK {[0;1;32m
!WYour account has been updated.!)
[0;1m} T After data entry: Changes updated


PSCUR {[0;1m
Enter your current password (asterisks will echo): [0m} T Enter your current password


CPSERR {[0;1;31m
The password you entered was incorrect.
[0;1m} T Wrong password entered.


PREPSW {[0;1;32m
!JPlease enter your new password. Make your password short enough
so you can remember it, but not easy enough so others can't guess it.
The security of your account depends on your password being known to
you [37monly[32m.[0;1m!)
} T Hints about thinking up passwords


RECPSW {[0;1;32m
[37;5mÛÛ[0;1;32m  The BBS recommends this password: [37m%s[32m

!JYou may use it as it is, use parts of it, or enter a completely different one.
The recommended password, though, is easy to remember, and surprisingly difficult
for others to find.!)
[0;1m} T Recommend a random password


FRCPSW {[0;1;32m
!JFor security reasons, you can't enter a password yourself. Instead, the
system assigns one to you. The password assigned to you is easy to remember,
yet surprisingly difficult for others to find.!)

[37;5mÛÛ[0;1;32m  The BBS has assigned this password: [37m%s[32m
[0;1m} T Random password forcibly assigned


GPSWORD {[0;1m

!W[AEnter your new password: [0m!)} T Asking a user to choose a password


GPSWAGN {[0;1m

!W[ARe-enter to verify:      [0m!)} T Ask again for password verification


BADPSW1 {[0;1;31m
!JYour password must be at least [37m5[31m characters long. It must also
contain [37mnumbers or capital letters[31m. Punctuation marks and special
characters are a good idea for additional safety.!)
[0;1m
} T Password not safe, re-enter


BADPSW2 {[0;1;31m
!JThis password is too easy to guess. Please try something less obvious.!)
[0;1m
} T Such a stupid password, re-enter.


BADPSW3 {[0;1;31m
!JThe passwords don't match. Please try again.
[0;1m!)
} T Passwords don't match, re-enter.


BADPSW4 {[0;1;31m
!JYour new password can't be the same as your old one. Please try again.
[0;1m!)
} T New password must be different than old password


PNOTSET {[0;1;31m
Your password has not been changed.
[0;1m} T Password not changed


PSWEPI {[0;1;32m
Your password has been changed successfully.
[0;1m} T Password changed successfully


PSWKO {[0;1;31m
!JYou failed to provide the correct password. Unfortunately, we cannot allow you
to change your password unless you prove that you are its rightful owner, and we
can't allow you to enter the system unless you change your password. Please call
back when you are ready to provide the correct password.!)
[0;1m

} T Password wrong during login change, kicking you out



PRFVT {[0;30;47m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [34mPersonal Preferences[0;30;47m ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;1;37;47m¿ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  ANSI colours . . . . . . . . . . . . .  [0;46;30m @7;"ON|OFF|Default|Ask"l [47m    (space to change)[1;37m  ³ [0m
[30;47m ³  Font/terminal/connection type . . . . . [0;46;30m @16;"Greek 437G/737|Greek „L’/ISO|PC without Greek|7-bit ASCII|Default|Ask"l [47m            [1;37m  ³ [0m
[30;47m ³  Never pause while scrolling  . . . . .  [0;46;30m [@"X "t] [1;47;37m                           ³ [0m
[30;47m ³  Full Screen utilities . . . . . . . . . [0;46;30m [@"X "t] [1;47;37m                           ³ [0m
[30;47m ³  Language/Terminal type . . . . . . . .  [0;46;30m @16;"„¢¢¤ ¡á|English"l [1;47;37m              ³ [0m
[30;47m ³  Screen size (columns x rows)  . . . . . [1;44;37m@3;20;250;0n[0;30;47m x [1;44;37m@3;5;250;0n[0;30;47m                   [1;37m³ [0m
[30;47m ³  Initial paging mode  . . . . . . . . .  [0;46;30m @5;"OFF|ON|OK|STORE"l [47m      (space to change)  [1;37m³ [0m
[30;47m ³  Time between pages (minutes)  . . . . . [1;44;37m@1;1;9;0n[0;47;30m                             [1;37m³ [0m
[30;47m ³                                                                          [0;1;47;37m³ [0m
[30;47m ³  Ctrl-R for help                 [0;1;42;33m@14;"OK"b[0;47;30mÜ    [0;1;41;33m@14;"Cancel"b[0;47;30mÜ  [0;1;47;37m³ [0m
[30;47m ³                                   ßßßßßßßßßßßßßßßß     ßßßßßßßßßßßßßßßß  [0;1;47;37m³ [0m
[30;47m À[0;1;37;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0m} T Preference edit visual template


ANSON {ON} T String for ANSI ON in edit templates
ANSOFF {OFF} T String for ANSI OFF in edit templates
ANSDEF {Default} T String for ANSI Default in edit templates
ANSASK {Ask} T String for ANSI Ask in edit templates

TR0 {} T String for translation table #0 in edit templates
TR1 {Greek 437G/737} T String for translation table #1 in edit templates
TR2 {Greek „L’/ISO} T String for translation table #2 in edit templates
TR3 {PC without Greek} T String for translation table #3 in edit templates
TR4 {7-bit ASCII} T String for translation table #4 in edit templates
TR5 {} T String for translation table #5 in edit templates
TR6 {} T String for translation table #6 in edit templates
TR7 {} T String for translation table #7 in edit templates
TR8 {} T String for translation table #8 in edit templates
TR9 {} T String for translation table #9 in edit templates
TRDEF {Default} T String for Default translation in edit templates
TRASK {Ask} T String for "Ask" "translation" (asking for one at login)

LANG1 {„¢¢¤ ¡á} T String for Language 1 in edit templates
LANG2 {English} T String for Language 2 in edit templates
LANG3 {} T String for Language 3 in edit templates
LANG4 {} T String for Language 4 in edit templates
LANG5 {} T String for Language 5 in edit templates
LANG6 {} T String for Language 6 in edit templates
LANG7 {} T String for Language 7 in edit templates
LANG8 {} T String for Language 8 in edit templates
LANG9 {} T String for Language 9 in edit templates
LANG10 {} T String for Language 10 in edit templates

PGSSTR {STORE} T String for page STORE state in edit templates
PGSOK {OK} T String for page OK state in edit templates
PGSON {ON} T String for page ON state in edit templates
PGSOFF {OFF} T String for page OFF state in edit templates


PRFLT {[2J[0;30;47m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [34mPersonal Preferences[0;30;47m ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;1;37;47m¿ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³  [31m1[30m. ANSI colours . . . . . . . . . . . . .  [34m@7;"ON|OFF|Default|Ask"l [47m                   [1;37m  ³ [0m
[30;47m ³  [31m2[30m. Font/terminal/connection type . . . . . [34m@16;"Greek 437G/737|Greek „L’/ISO|PC without Greek|7-bit ASCII|Default|Ask"l           [1;37m  ³ [0m
[30;47m ³  [31m3[30m. Never pause while scrolling  . . . . .  [34m@"X "t                          [1;37m³ [0m
[30;47m ³  [31m4[30m. Full Screen utilities . . . . . . . . . [34m@"X "t                          [1;37m³ [0m
[30;47m ³  [31m5[30m. Language/Terminal  . . . . . . . . . .  [34m@16;"„¢¢¤ ¡á|English"l             [1;37m³ [0m
[30;47m ³  [31m6[30m. Screen size (columns) . . . . . . . . . [34m@3;20;250;0n[0;30;47m                          [1;37m³ [0m
[30;47m ³  [31m7[30m. Screen size (rows) . . . . . . . . . .  [34m@3;5;250;0n[0;30;47m                          [1;37m³ [0m
[30;47m ³  [31m8[30m. Initial paging mode . . . . . . . . . . [34m@5;"OFF|ON|OK|STORE"l [47m                       [1;37m³ [0m
[30;47m ³  [31m9[30m. Time between pages (minutes) . . . . .  [34m@1;1;9;0n                            [1;37m³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m À[0;1;37;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0;1m
} T Preference edit linear template


NEWANS {[0;1m
!JThis option controls whether ANSI (VT-102) directives will be sent
to your terminal or not. When set to 'ON', all ANSI codes will be sent. In the
'OFF' ANSI directives are automatically stripped. In 'Default', this setting
depends on the initial ANSI setting of the channel to which you are connected
(this takes effect on your next connection). Specifying 'Ask' will force
the system to ask you whether you want ANSI support during login.!)

!JThe last two settings have no effect on ANSI support in your current connection.
They take effect next time you connect.!)
} T Preference edit, info on ANSI setting



NEWXLT {[0;1m
!JWith this option you can make the system translate the characters you see,
to account for a terminal without full IBM PC ASCII, for example. Choose
'[33mGreek 437G/737[37m' if you have 8-bit IBM ASCII with a 437G/737 Greek font.
Select '[33mGreek ELOT/ISO[37m' if you're using the ELOT-928 or ISO-8859-7 standards, or
codepage 928. If you have IBM ASCII but not Greek characters, try
'[33m437 PC without Greek[37m'. Finally, if you have neither a PC font nor Greek, choose
'[33m7-bit ASCII[37m'.!)

!JThe '[33mDefault[37m' option sets the translation automatically depending on what
channel you connect to. '[33mAsk[37m' forces the system to ask you what translation
to use every time you login.!)

!JThe last two settings take effect the next time you connect and appear to do nothing to
your current connection.!)
} T Preference edit, info on translation setting


NEWNPS {[0;1m
!JBy activating this option, you tell the system not to suspend text display
when the screen is about to scroll. Doing so is not recommended, as you will
tend to lose many system messages. This option is useful for capturing (logging)
long texts from the system.!)
} T Preference edit, info on no-screen-pause setting


NEWFST {[0;1m
!JIf your terminal supports ANSI (VT-102) directives, the IBM extended character set,
and your modem is sufficiently fast, we recommend setting this option to ON: it will
allow you to use the system's full screen tools (editors, viewers, dialog boxes, etc),
instead of the old, linear utilities.!)
} T Preference edit, info on full screen tools


NEWLAN {[0;1m
!JPlease enter the language in which you wish to receive system messages.!)
} T Preference edit, choosing a new language


NEWSWD {[0;1m
!JPlease enter the number of [32mcolumns[37m your screen can display.
For example, if your screen displays 80x25 characters, enter 80.!)
} T Preference edit, entering new screen width


NEWSHT {[0;1m
!JPlease enter the number of [32mlines[37m your screen can display.
For example, if your screen displays 80x25 characters, enter 25.
You might like to enter one or two lines less than the full height of your screen,
in case your communications program uses one or two status lines.!)
} T Preference edit, entering new screen width


NEWPGS {[0;1m
!JThis option controls whether or not you will accept pages right after
you log in. Changing this setting does NOT change your current paging mode
(enter [33m/p[37m to see how to change it). Only your initial paging mode
(active when you log in) is altered.!)

!JYour options are as follows: OFF: You forbid all pages to you. ON: You
accept pages, but you force a time interval between pages (this time interval
is set using option 8). OK: You accept all pages, without constrictions. STORE:
If you are busy (transferring files, editing a message, etc), pages to you are
stored and displayed when you become available again.!)
} T Preference edit, entering new default page state


NEWPGT {[0;1m
!JPlease enter the number of minutes between pages to you (this option is
effective only when your paging mode is 'ON').!)
} T Preference edit, entering new inter-page time


XFERR1 {[0;1;31m
!JI'm sorry, but you must have at least %d credits to be able to transfer.
This is the minimum transferable amount of credits.!)[0;1m
} T Credit transfer, insufficient credits for transferring


XFERR2 {[0;1;31m
!JI'm sorry, but your security level does not permit transferring credits.!)[0;1m
} T Credit transfer, user not allowed to transfer their credits


XFERR3 {[0;1;31m
!JI'm sorry, but you haven't bought (paid) credits, and so you may not transfer.
This wouldn't be fair, anyway, since the System Operator gave credits for your own
use only. To find out how to get paid credits in @BBS@, please check the
[37mInformation module[31m ([33m/go info[31m).!)[0;1m
} T Credit transfer, user not allowed to transfer their credits


CREDTR {[0;1m
!JThis option transfers credits from your account to another user.!)

!WHow many credits (minutes) do you want to transfer?!) [0m} T Credit transfer, how many credits to transfer?


NUMERR {[0;1;31m
!WPlease enter a number in the range %d to %d. Otherwise,
enter [33mX[31m to exit.!)
} T Credit transfer, invalid number of credits


RANOUT {[0;1;31m
!JUnfortunately you don't have enough credits any more, so you can't transfer.
You can obtain more information about getting paid credits using the Information
service (main menu option [33mI[31m).!)
[0;1m} T Credit transfer, just barely too many credits


CTWHO {[0;1m
!WWhom do you want to transfer credits to?!)[0m } T Credit transfer, Asking to whom to transfer credits


CTNSELF {[0;1;31m
!WWhy transfer credits to yourself?!)
} T Credit transfer, Can't transfer credits to yourself


UIDERR {[0;1;31m
!WThere is no such user. Please try again, or enter [33mX[31m to
exit.!)
[0;1m} T Credit transfer, user ID does not exist


CTWARN {
!J[0;1;31;5mÛÛ[0;1;31m  WARNING:  !i%s will be unable to return the credits
you are about to transfer.!)
!0l[0;1m} T Credit transfer, transferring to user who can't transfer back


CTCONF {[0;1;33m
!WConfirmation: [37m!iYou are about to transfer [32m%d[37m credits from
[32m%s[37m to [32m%s[37m.!)
!0l[0;1m} T Credit transfer, final confirmation.


CTCQUE {[0;1m
!WIs this right? ([[33mY[0;1m]es / [[33mN[0;1m]o)!)[0m } T Credit transfer, asking for confirmation


BOOLERR {[0;1;31m
!WPlease answer the question with either [33mY[31mes, or
[[33mN[31m]o.!)
[0;1m} T Credit transfer, wrong answer to confirmation question


ACCDEL {[0;1;31m
!WI'm sorry, but "%s" has just been deleted.
Unable to transfer credits.!)
[0;1m} T Credit transfer, user deleted, no transfer


NOENOT {[0;1;33m
!WWhile you were deciding on the receiver of the credits, your credits
diminished to %d. Supposing you wanted to transfer everything, we did so.!)
[0;1m} T Credit transfer, transfer amount truncated


CXFOK {[0;1;32m
!WAcknowledgement: !i[37m%d[32m credits transferred
from [37m%s[32m to [37m%s[32m.!)
!0l[0;1m} T Credit transfer, transaction successful


CXFINJ {[0;1;35m***
[37m%s[35m just transferred [37m%d[35m credits to you.
} T Credit transfer, informing online user of transfer to their account


NOTICE {[0;1m
!W%s is on-line right now and has been notified of the transfer.!)
[0;1m} T Credit transfer, credit recipient has been notified


CXFABO {
[0;1;31mThe transfer was aborted. Returning to the previous menu.
[0;1m} T Credit transfer, transfer aborted


ACCST1 {
[0;36mÛÛ  [1mStatistics  [46m[K[0;1m

} T Account Statistics, chunk 1


ACCST2 {!JYou account was created on [32m@DATECRE@[37m.
Your last connection was on [32m@DATELAST@[37m.
Your user ID has been around for [32m%d day%s[37m,
and you have been on-line [32m@NUMCONNS@ time%s[37m.
By the way, your password expires in [32m@PASSEXP@ day%s[37m.!)

} T Account statistics, chunk 2


ACCST2A {!JYour account was created [32mtoday[37m.
Your password expires in [32m@UPASSEXP@ day%s[37m.!)

} T Account statistics, chunk 2 for newbies


ACCST3 {!JYour account has [32m@CREDITS@ credit%s[37m.
You were posted [32m@TOTCREDS@ credit%s[37m in total,
of which [32m@TOTPAID@[37m are 'paid'.
You have consumed [32m@CREDSEVER@ credit%s[37m in total,
for a total connection time of [32m@TIMEVER@ minute%s[37m.!)

} T Account statistics, chunk 3


ACCST4 {!JUp to now, you have downloaded [32m@FILESDNL@ file%s[37m,
for a total size of [32m@KBSDNL@ Kbytes[37m.
You have uploaded [32m@FILESUPL@ file%s[37m,
for a total size of [32m@KBSUPL@ Kbytes[37m.!)

} T Account statistics, chunk 4


ACCST5A {!JYour account belongs to the [32m@USERCLASS@[37m class. } T Account statistics, chunk 5A


ACCST5B {Regardless of how many credits you have, there is a
per-connection on-line time limit of [32m%d minute%s[37m. } T Account statistics, chunk 5B


ACCST5C {Regardless of how many credits you have, there is a
daily on-line time limit of [32m%d minutes%s[37m. } T Account statistics, chunk 5C


ACCST5D {The system gives you [32m%d credit%s[37m %s. } T Account statistics, chunk 5D


ACCST5E {You are exempt from all credit charges. } T Account statistics, chunk 5E


ACCST5F {In [32m%d day%s[37m, you will be transferred to the [32m%s[37m class. } T Account statistics, chunk 5F


ACCST5FT {You will be transferred to the [32m%s[37m class [32mtomorrow[37m. } T Account statistics, chunk 5F (tomorrow)


ACCST5G {If you don't connect at all for [32m%d day%s[37m, you will be transferred to the [32m%s[37m class. } T Account statistics, chunk 5G


ACCST5H {If you run out of credits, you will be temporarily transferred to the [32m%s[37m class. } T Account statistics, chunk 5H


ACCST5I {When posted paid credits, you get transferred to the [32m%s[37m class. } T Account statistics, chunk 5I


ACCST5J {!)

} T Account statistics, chunk 5J


ACCST6 {[0;46m[K[0;1m
} T Account statistics, chunk 6


MINSNG {} T Minutes, singular form
MINPLR {s} T Minutes, plural form

TIMSNG {} T 'Times', singular form
TIMPLR {s} T 'Times', plural form

CRDSNG {} T Credits, singular form
CRDPLR {s} T Credits, plural form

FILSNG {} T Files, singular form
FLIPLR {s} T Files, plural form

DAILY {daily} T String for 'daily' in statistics
WEEKLY {weekly} T String for 'weekly' in statistics
MNTHLY {monthly} T String for 'monthly' in statistics


OPSWHO {[0;1;31m
[5mÛÛ  !i!J[0;1;31mChanging another user's password is logged.!)
!0l[0;1m
!WEnter the user ID whose password you want to change, or 
[33mX[37m to exit:!) [0m} T Change someone else's password


OUIDERR {[0;1;31m
This user ID does not exist.
[0;1m} T User ID does not exist


PSWOTH {[0;1;33m
You are changing the password for user [37m%s[33m.
[0;1m} T Changing other user's password


LANGEND {}
