LEVEL2 {}


LINKEY {Key required to see news at login: 0} N 0 129

ENTRYKEY {Key required to gain entry to the news module: 0} N 0 129

SOPKEY {Key required for privileged access to the module: 128} N 0 129

DEFDUR {Default duration of bulletin (days): 10} N 0 3650

DEFSHW {Default announcement mode: ALWAYS} E ALWAYS ONCE

DEFHDR {Default header style (time/date): DATE} E NONE DATE TIME BOTH

DEFCLS {} S 10 Default Class locking for bulletins:

DEFKEY {Default key locking for bulletins: 0} N 0 129

MAXLEN {Maximum length of news bulletin: 65536} N 256 262144

UPLDESC {News Bulletin} S 50 File upload description




LEVEL3 {}


NOENTRY {[0;1;31m
Š¬§á£˜ , ›œ¤ â®œ«œ §¨æ©™˜© ©œ ˜¬«ã «¤ §œ¨ ¦®ã.
[0;1;31m} T User has no access to chosen area


MENU {[2J[0m[47;1;37m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;30;47m¿ [40m
[47;1;37m ³  [0;47;30m                  ’˜ Tœ¢œ¬«˜å˜ Nâ˜                     [0;47;30m³ [40m
[47;1;37m ³  [0;47;30mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ  [0;47;30m³ [40m
[47;1;37m ³  [0;31;47mR[30mead news . . . . . . . . . . . . . . . „£­á¤ © ¤âà¤  [30m³ [40m
[47;1;37m ³  [0;31;47mL[30mist news  . . . . . . . . . . . .  ‰˜«á¢¦š¦ª ›œ¢«åà¤  [30m³ [40m
[47;1;37m ³  [0;31;47mI[30mmport bulletin . . . . . . . . . .  „ ©˜šàšã ›œ¢«å¦¬  [30m³ [40m
[47;1;37m ³  [0;31;47mD[30melete bulletin  . . . . . . . . .   ƒ ˜š¨˜­ã ›œ¢«å¦¬  [30m³ [40m
[47;1;37m ³  [0;31;47mE[30mdit bulletin . . . . . . . . . . . „¤£â¨à© ›œ¢«å¦¬  [30m³ [40m
[47;1;37m ³                                                         [0;47;30m³ [40m
[47;1;37m ³ [0;30;47me[31mX[30mit  . . . . . . . . . . . . . . . . . . . . . „¥¦›¦ª  [30m³ [40m
[47;1;37m À[0;30;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0;1m

’œ¢œ¬«˜å˜ ¤â˜
˜¨˜¡˜¢é ›é©«œ «¤ œ§ ¢¦šã ©˜ª: [0m} T News menu (privileged users only)


SHMENU {[0;1m
’œ¢œ¬«˜å˜ ¤â˜
!Wƒé©«œ «¤ œ§ ¢¦šã ©˜ª ([33mR[37m,[33mL[37m,[33mI[37m,[33mD[37m,[33mE[37m,[33mX[37m š ˜ â¥¦›¦, ã [33m?[37m š ˜ «¦ £œ¤¦ç): !)[0m} T News short menu


ERRSEL {[0;1;31m
!WŠ¬§á£˜ , ›œ¤ ¬§á¨®œ   œ§ ¢¦šã "%c".!)
[0;1m} T Invalid option selection


LEAVE {[0;1m
!W„¥¦›¦ª ˜§æ «˜ ’œ¢œ¬«˜å˜ Œâ˜.!)
[0m} T Exiting to main menu


PRESS {[0;1m
!W â©«œ Enter š ˜ ¤˜ œ§ ©«¨â¯œ«œ ©«¦ ¡œ¤«¨ ¡æ £œ¤¦ç.!)[30m } T Press Enter to return to the main menu


VEDIT {[0;30;47m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [34m‘«¦ ®œå˜ ›œ¢«å¦¬[0;30;47m ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;1;37;47m¿ [0m
[30;47m ³                                                                          [0;1;47;37m³ [0m
[30;47m ³  ƒ á¨¡œ ˜ ›œ¢«å¦¬ (£â¨œª)   [1;44;37m@4;0;9999;0n[0;47;30m                            (0-9999)  [1;37m³ [0m
[30;47m ³                                                                          [0;1;47;37m³ [0m
[30;47m ³  „£­á¤ ©                    [0;30;46m [@"X "t] [0;47;30m                   (Space š ˜ ˜¢¢˜šã)  [1;37m³ [0m
[30;47m ³                                                                          [0;1;47;37m³ [0m
[30;47m ³  „§ §¢â¦¤ §¢¨¦­¦¨åœª        [0;30;46m @18;"‰˜££å˜|—¨˜|†£œ¨¦£¤å˜|—¨˜ ¡˜  †£œ¨¦£¤å˜"l [0;47;30m    (Space š ˜ ˜¢¢˜šã)  [1;37m³ [0m
[30;47m ³                                                                          [0;1;47;37m³ [0m
[30;47m ³  „£­á¤ © £æ¤¦ ©«¤ ¡¢á©    [1;37;44m@10;10;1s[0;47;30m                              [0;1;47;37m  ³ [0m
[30;47m ³                                                                          [0;1;47;37m³ [0m
[30;47m ³  €¨ Ÿ£æª ¡¢œ › ¦ç            [1;37;44m@3;0;129;0n[0;47;30m                              (0-129)[0;1;47;37m  ³ [0m
[30;47m ³                                                                          [0;1;47;37m³ [0m
[30;47m ³  ¨¦«œ¨˜ æ««˜ ›œ¢«å¦¬       [1;37;44m@4;-100;100;0n[0;47;30m                         (-100-+100)[0;1;47;37m  ³ [0m
[30;47m ³                                                                          [0;1;47;37m³ [0m
[30;47m ³  Ctrl-Q: Cancel  Ctrl-S: Ok                                              [0;1;47;37m³ [0m
[30;47m ³  Ctrl-L: Redraw  Ctrl-X: Line    [0;1;42;33m@14;"OK"b[0;47;30mÜ    [0;1;41;33m@14;"Cancel"b[0;47;30mÜ  [0;1;47;37m³ [0m
[30;47m ³  Ctrl-R: Help                     ßßßßßßßßßßßßßßßß     ßßßßßßßßßßßßßßßß  [0;1;47;37m³ [0m
[30;47m À[0;1;37;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0m} T Visual template


VEDIT1A {‰˜££å˜} T Visual template, 'NONE' string
VEDIT1B {†£œ¨¦£¤å˜} T Visual template, 'DATE' string
VEDIT1C {—¨˜} T Visual template, 'TIME' string
VEDIT1D {†£œ¨¦£¤å˜ ¡˜  —¨˜} T Visual template, 'BOTH' string


LEDIT {[2J[0;30;47m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;1;37;47m¿ [0m
[30;47m ³                   ‘«¦ ®œå˜ ›œ¢«å¦¬                  [0;1;47;37m³ [0m
[30;47m ³ ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [0;1;47;37m³ [0m
[30;47m ³ [31m1[30m. ƒ á¨¡œ ˜ ›œ¢«å¦¬ (£â¨œª) .  [34m@4;0;9999;0n                [0;1;47;37m³ [0m
[30;47m ³ [31m2[30m. „£­á¤ © . . . . . . . . . . [34m@"X "t                 [0;1;47;37m³ [0m
[30;47m ³ [31m3[30m. „§ §¢â¦¤ §¢¨¦­¦¨åœª  . . .  [34m@18;"‰˜££å˜|—¨˜|†£œ¨¦£¤å˜|—¨˜ ¡˜  †£œ¨¦£¤å˜"l  [0;1;47;37m³ [0m
[30;47m ³ [31m4[30m. „£­á¤ © £æ¤¦ ©«¤ ¡¢á© . . [34m@10;10;1s          [0;1;47;37m³ [0m
[30;47m ³ [31m5[30m. €¨ Ÿ£æª ¡¢œ › ¦ç  . . . . .  [34m@3;0;129;0n                 [0;1;47;37m³ [0m
[30;47m ³ [31m6[30m. ¨¦«œ¨˜ æ««˜ ›œ¢«å¦¬ . . .  [34m@4;-100;100;0n                [0;1;47;37m³ [0m
[30;47m ³                                                     [0;1;47;37m³ [0m
[30;47m ³ [31m0[30m. ‘¬¤â®œ ˜.@14;"0OK"b                                        [0;1;47;37m³ [0m
[30;47m ³ [31mX[30m. €¡¬¨¦.@14;"XCancel"b                                           [0;1;47;37m³ [0m
[30;47m À[0;1;37;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0m
} T Linear template example


FIELD1 {[0;1m
!Wƒé©«œ «¤ › á¨¡œ ˜ «¦¬ ›œ¢«å¦¬ ©œ £â¨œª (0-9999, 0=œ§'˜æ¨ ©«¦¤).!)
[0;1m} T Linear prompt #1


FIELD2 {[0;1m
!W€¬«æ «¦ §œ›å¦ ¡˜Ÿ¦¨åœ  ˜¤ «¦ ›œ¢«å¦ Ÿ˜ œ£­˜¤åœ«˜ . ’˜ ›œ¢«å˜
›œ¤ › ˜š¨á­¦¤«˜ , ˜§¢éª ©«˜£˜«¦ç¤ ¤˜ œ£­˜¤å¦¤«˜ . €¬«æ «¦ §œ›å¦
œ¢âš®œ  ˜¡¨ ™éª ˜¬«ã «¤ ›¬¤˜«æ««˜.!)
[0;1m} T Linear prompt #2


FIELD3 {[0;1m
!Wƒ ˜¢â¥«œ «  œ§ §¢â¦¤ §¢¨¦­¦¨åœª Ÿ˜ œ£­˜¤å¦¤«˜  ©«¤ ¡¦¨¬­ã «¦¬ ›œ¢«å¦¬.!)
[0;1m} T Linear prompt #3


FIELD4 {[0;1m
!W„¤˜ ›œ¢«å¦ £§¦¨œå ¤˜ œ£­˜¤åœ«˜  £æ¤¦ ©«¦¬ª ®¨ã©«œª œ¤æª ©¬š¡œ¡¨ £â¤¦¬ class.
„›é £§¦¨œå«œ ¤˜ ¡˜Ÿ¦¨å©œ«œ §¦ ¦ Ÿ˜ œå¤˜  ˜¬«æ «¦ class. €­ã¤¦¤«˜ª «¦ §œ›å¦ ¡œ¤æ,
«¦ ›œ¢«å¦ Ÿ˜ œå¤˜  ¦¨˜«æ ˜§æ æ¢¦¬ª «¦¬ª ®¨ã©«œª.!)
[0;1m} T Linear prompt #4


FIELD5 {[0;1m
!W„¤˜ ›œ¢«å¦ £§¦¨œå ¤˜ œ£­˜¤åœ«˜  £æ¤¦ ©«¦¬ª ®¨ã©«œª §¦¬ â®¦¬¤ â¤˜ ©¬š¡œ¡¨ £â¤¦
¡¢œ ›å. „›é £§¦¨œå«œ ¤˜ ¡˜Ÿ¦¨å©œ«œ §¦ ¦ Ÿ˜ œå¤˜  ˜¬«æ «¦ ¡¢œ ›å. ’¦ ¡¢œ ›å 0 ¡á¤œ 
«¦ ›œ¢«å¦ ¦¨˜«æ ˜§æ æ¢¦¬ª «¦¬ª ®¨ã©«œª. ’¦ ¡¢œ ›å 129 ¡á¤œ  «¦ ›œ¢«å¦ ¦¨˜«æ £æ¤¦ ˜§æ
«¦ ¯œ¬›é¤¬£¦ Sysop.!)
[0;1m} T Linear prompt #5


FIELD6 {[0;1m
!W‰˜¤¦¤ ¡á «˜ ›œ¢«å˜ œ£­˜¤å¦¤«˜  £œ ®¨¦¤¦¢¦š ¡ã ©œ ¨á («˜ § ¦ §¨æ©­˜«˜ ›œ¢«å˜ §¨é«˜).
‹§¦¨œå«œ ¤˜ ˜¤˜š¡á©œ«œ â¤˜ ›œ¢«å¦ ¤˜ â®œ  £œš˜¢ç«œ¨ §¨¦«œ¨˜ æ««˜ ˜§æ «˜ á¢¢˜, ¦¨å¦¤«˜ª
£ ˜ « £ã š ˜ ˜¬«æ «¦ §œ›å¦. ’˜ ›œ¢«å˜ œ£­˜¤å¦¤«˜  ¡˜«á ­Ÿå¤¦¬©˜ ©œ ¨á §¨¦«œ¨˜ æ««˜ª ¡˜ 
‹„’€ ¡˜«á ®¨¦¤¦¢¦š ¡ã ©œ ¨á. €¨¤« ¡¦å ˜¨ Ÿ£¦å ©£˜å¤¦¬¤ æ«  «¦ ›œ¢«å¦ Ÿ˜ œ£­˜¤ ©«œå §¨¦ª
«¦ «â¢¦ª «ª ¢å©«˜ª, Ÿœ« ¡¦å ˜¨ Ÿ£¦å ©£˜å¤¦¬¤ æ«  «¦ ›œ¢«å¦ Ÿ˜ œ£­˜¤ ©«œå §¨¦ª «¤ ˜¨®ã
«ª ¢å©«˜ª. ‹§¦¨œå«œ ¤˜ ›é©œ«œ ˜¨ Ÿ£¦çª ©«¦ › á©«£˜ -100,...,+100.!)
[0;1m} T Linear prompt #6



WARNCLS {[0;1;33m
!W¨¦©¦®ã: ’¦ class "[37m%s[33m" §¦¬ ¦¨å©˜«œ ›œ¤ ¬§á¨®œ !!)
[0;1m} T Warning: class does not exist


CANCEL {[0;1;33m
!W€¡ç¨à© «ª › ˜› ¡˜©å˜ª.!)
[0;1m} T Process aborted


IOERR {[0;1;31m
!Wƒ£ ¦¬¨šãŸ¡œ §¨æ™¢£˜ ¡˜«á «¤ ›£ ¦¬¨šå˜ «¦¬ ›œ¢«å¦¬. † › ˜› ¡˜©å˜ ˜¡¬¨éŸ¡œ.!)
[0;1m} T I/O error while writing news bulletin


BLTOK {[0;1;32m
!W’¦ ›œ¢«å¦ [37m%d[32m ˜§¦Ÿ¡œç«¡œ.!)
[0;1m} T News bulletin created


TXTCAN {[0;1;32m
!W  ˜¢¢˜šâª ©«¦ ¡œå£œ¤¦ «¦¬ ›œ¢«å¦¬ ˜¡¬¨éŸ¡˜¤ («¬®æ¤ ˜¢¢˜šâª §¦¬
§¨˜š£˜«¦§¦ ã©˜«œ ©«˜ ©«¦ ®œå˜ «¦¬ bulletin §¨¦š¦¬£â¤àª â®¦¬¤ ã› ©àŸœå).!)
[0;1m} T News bulletin text edit canceled





ASKEDT {[0;1m
!Wƒé©«œ «¦¤ ˜¨ Ÿ£æ «¦¬ §¨¦ª œ¤£â¨à© ›œ¢«å¦¬, [33m?[37m š ˜ ™¦ãŸœ ˜, ã
[33mX[37m š ˜ â¥¦›¦:!)[0m } T Edit bulletin: What number?


ASKUPL {[0;1m
!W‡â¢œ«œ ¤˜ ¥˜¤˜©«œå¢œ«œ ã ¤˜ › ¦¨Ÿé©œ«œ «˜ §œ¨ œ®æ£œ¤˜ «¦¬ ›œ¢«å¦¬;
([[33mY[37m]es=˜§¦©«¦¢ã, [[33mN[37m]o=æ® , [[33mE[37m]dit=› æ¨Ÿà©) } T Edit bulletin: re-upload bulletin?


ASKUPLD {[Enter=No]:[0m!) } T Edit bulletin: default response


ASKERR {[0;1;31m
!J˜¨˜¡˜¢é ›é©«œ [33mY[31m, [33mN[31m ã [33mE[31m.!)
[0;1m} T Edit bulletin: bad answer to ASKUPL


SHEADER {[0;1;35m
ÚÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
³ ƒœ¢«å¦ [37m#%-3d[35m ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
³ „©«á¢: [37m%-9s %-8s[35m       ³ ¨¦«œ¨˜ æ««˜: [37m%-4d[35m                       ³
³ ƒ á¨¡œ ˜ ›œ¢«å¦¬ (£â¨œª): [37m%4d[35m  ³ „§ §¢â¦¤ §¢¨¦­¦¨åœª: [37m%-18s[35m  ³
³ ‰¢á©: [37m%-10s[35m                ³ ‰¢œ ›å: [37m%-3d[35m                               ³
ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
[0;1m} T Sysop version of the Bulletin Header


LSTHDR {[0;1m

ÚÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
³ [33mA/A[37m ³ [33m†‹„‹†Œˆ€ ‰€ˆ —€[37m ³ [33m’[37m ³ [33mƒˆ€‰„ˆ€[37m ³ [33m‰Š€‘† ‰€ˆ ‰Š„ˆƒˆ[37m ³
ÃÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ´
} T News bulletin list, header


LSTTAB {³ [32m%3d[37m ³ [32m%s %s[37m ³ [32m%+4d[37m ³  [32m%5d%c[37m  ³ [32m%-10s   %3d[37m ³
} T News bulletin list, table


LSTFTR {ÀÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ

(*) = ’¦ ›œ¢«å¦ œå¤˜  ˜¤œ¤œ¨šæ (›œ¤ œ£­˜¤åœ«˜ ).

[0;1m} T News bulletin list, footer



RDNEWS {[2J[0;1;31m’˜ «œ¢œ¬«˜å˜ £˜ª ¤â˜:

} T Reading news bulletins


HEADER {[0;1mÛÛ  [35m%s[0;1m  ÛÛ  %s

} T Bulletin Header


NEWBLT {[0;1;33;5m*Œâ¦*[0;1m} T You've never read this bulletin before


BLTDIV {[0;1m
} T Bulletin divider


NONEWS {[0;1;31m
[!Wƒœ¤ ¬§á¨®¦¬¤ «œ¢œ¬«˜å˜ ¤â˜.!)
[0;1m
} T News file is empty


DELBLT {[0;1m
!Wƒé©«œ «¦¤ ˜¨ Ÿ£æ «¦¬ §¨¦ª › ˜š¨˜­ã ›œ¢«å¦¬, [33m?[37m š ˜ ¡˜«á¢¦š¦, ã
[33mX[37m š ˜ â¥¦›¦:!)[0m } T Delete bulletin: What number?


NUMERR {[0;1;31m
!W’¦ ›œ¢«å¦ [37m%d[31m ›œ¤ ¬§á¨®œ . ˜¤˜›¦¡ £á©«œ...!)
} T Delete bulletin rebuff unknown bulletin


DELOK {[0;1m
!W„§ ™œ™˜ éŸ¡œ:  › ˜š¨˜­ã «œ¢œåà©œ £œ œ§ «¬®å˜.!)
[0;1m} T Delete bulletin: Deletion successful


FTOOMANY {[0;1;33m
!J€§¦©«œå¢˜«œ §á¤à ˜§æ â¤˜ ˜¨®œå¦. ‹æ¤¦ «¦ §¨é«¦ ˜¨®œå¦ Ÿ˜
®¨© £¦§¦ Ÿœå.!)
[0;1m} T Upload bulltin: more than one file uploaded





LANG {}



NOENTRY {[0;1;31m
Sorry, you don't have access to this area.
[0;1;31m} T User has no access to chosen area


MENU {[2J[0m[47;1;37m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;30;47m¿ [40m
[47;1;37m ³  [0;47;30m    Latest News      [0;47;30m³ [40m
[47;1;37m ³  [0;47;30mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ  [0;47;30m³ [40m
[47;1;37m ³  [0;31;47mR[30mead news bulletins  [30m³ [40m
[47;1;37m ³  [0;31;47mL[30mist news bulletins  [30m³ [40m
[47;1;37m ³  [0;31;47mI[30mmport bulletin      [30m³ [40m
[47;1;37m ³  [0;31;47mD[30melete bulletin      [30m³ [40m
[47;1;37m ³  [0;31;47mE[30mdit bulletin        [30m³ [40m
[47;1;37m ³                       [0;47;30m³ [40m
[47;1;37m ³ [0;30;47me[31mX[30mit                  [30m³ [40m
[47;1;37m À[0;30;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0;1m

Latest news
Please enter your choice: [0m} T News menu (privileged users only)


SHMENU {[0;1m
Latest news
!WEnter your choice ([33mR[37m,[33mL[37m,[33mI[37m,[33mD[37m,[33mE[37m,[33mX[37m
to exit, or [33m?[37m for the menu): !)[0m} T News short menu


ERRSEL {[0;1;31m
!WSorry, there is not option "%c" here.!)
[0;1m} T Invalid option selection


LEAVE {[0;1m
!WLeaving the news area.!)
[0m} T Exiting to main menu


PRESS {[0;1m
!WPress [33mEnter[37m to return to the main menu.!)[30m } T Press Enter to return to the main menu


VEDIT {[0;30;47m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [34mBulletin Properties[0;30;47m ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;1;37;47m¿ [0m
[30;47m ³                                                                          [0;1;47;37m³ [0m
[30;47m ³  Bulletin lifetime (days)    [1;44;37m@4;0;9999;0n[0;47;30m                            (0-9999)  [1;37m³ [0m
[30;47m ³                                                                          [0;1;47;37m³ [0m
[30;47m ³  Bulletin is visible         [0;30;46m [@"X "t] [0;47;30m                    (Space to toggle)  [1;37m³ [0m
[30;47m ³                                                                          [0;1;47;37m³ [0m
[30;47m ³  Bulletin header display     [0;30;46m @18;"None|Time|Date|Time and Date"l [0;47;30m     (Space to change)  [1;37m³ [0m
[30;47m ³                                                                          [0;1;47;37m³ [0m
[30;47m ³  Show only to user in class  [1;37;44m@10;10;1s[0;47;30m                              [0;1;47;37m  ³ [0m
[30;47m ³                                                                          [0;1;47;37m³ [0m
[30;47m ³  Show only to owners of key  [1;37;44m@3;0;129;0n[0;47;30m                              (0-129)[0;1;47;37m  ³ [0m
[30;47m ³                                                                          [0;1;47;37m³ [0m
[30;47m ³  Display priority            [1;37;44m@4;-100;100;0n[0;47;30m                         (-100-+100)[0;1;47;37m  ³ [0m
[30;47m ³                                                                          [0;1;47;37m³ [0m
[30;47m ³  Ctrl-Q: Cancel  Ctrl-S: Ok                                              [0;1;47;37m³ [0m
[30;47m ³  Ctrl-L: Redraw  Ctrl-X: Line    [0;1;42;33m@14;"OK"b[0;47;30mÜ    [0;1;41;33m@14;"Cancel"b[0;47;30mÜ  [0;1;47;37m³ [0m
[30;47m ³  Ctrl-R: Help                     ßßßßßßßßßßßßßßßß     ßßßßßßßßßßßßßßßß  [0;1;47;37m³ [0m
[30;47m À[0;1;37;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0m} T Visual template


VEDIT1A {None} T Visual template, 'NONE' string
VEDIT1B {Date} T Visual template, 'DATE' string
VEDIT1C {Time} T Visual template, 'TIME' string
VEDIT1D {Time and Date} T Visual template, 'BOTH' string


LEDIT {[2J[0;30;47m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;1;37;47m¿ [0m
[30;47m ³                 Bulletin Properties                 [0;1;47;37m³ [0m
[30;47m ³ ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [0;1;47;37m³ [0m
[30;47m ³ [31m1[30m. Bulletin lifetime (days)  .  [34m@4;0;9999;0n                [0;1;47;37m³ [0m
[30;47m ³ [31m2[30m. Visible  . . . . . . . . . . [34m@"X "t                 [0;1;47;37m³ [0m
[30;47m ³ [31m3[30m. Header display  . . . . . .  [34m@18;"None|Time|Date|Time and Date"l  [0;1;47;37m³ [0m
[30;47m ³ [31m4[30m. Show only to class . . . . . [34m@10;10;1s          [0;1;47;37m³ [0m
[30;47m ³ [31m5[30m. Show only to key owners . .  [34m@3;0;129;0n                 [0;1;47;37m³ [0m
[30;47m ³ [31m6[30m. Display priority  . . . . .  [34m@4;-100;100;0n                [0;1;47;37m³ [0m
[30;47m ³                                                     [0;1;47;37m³ [0m
[30;47m ³ [31m0[30m. Continue.@14;"0OK"b                                        [0;1;47;37m³ [0m
[30;47m ³ [31mX[30m. Cancel.@14;"XCancel"b                                          [0;1;47;37m³ [0m
[30;47m À[0;1;37;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0m
} T Linear template example


FIELD1 {[0;1m
!WEnter the bulletin lifetime in days (0-9999, 0=permanent).!)
[0;1m} T Linear prompt #1


FIELD2 {[0;1m
!WThis field controls whether the bulletin will be visible.
If you need to keep a certain bulletin around but only show it
at certain times (eg season greetings, reminders of regular events etc),
all you need to do is make it invisible.!)
[0;1m} T Linear prompt #2


FIELD3 {[0;1m
!WPlease choose the bulletin's header type.!)
[0;1m} T Linear prompt #3


FIELD4 {[0;1m
!WThis allows you to control who can see this bulletin. Enter a class name
here to make the bulletin visible only to members of that class. Leave the
field empty to make the bulletin visible to users of all classes.!)
[0;1m} T Linear prompt #4


FIELD5 {[0;1m
!WYou can limit the visibility of a news bulletin to owners of a certain key.
For instance, you could add reminders to fellow BBS administrators. Key 0 makes
the bulletin visible to all users. Key 129 makes it visible only to user Sysop.!)
[0;1m} T Linear prompt #5


FIELD6 {[0;1m
!WNews bulletins are normally shown in chronological order (most recent bulletins first).
You can force a bulletin to be displayed above other by increasing its priority. Conversely,
you can make a bulletin show below others by decreasing its priority. Bulletins are sorted by
decreasing priority, THEN by increasing age. You can specify priorities between -100 and +100.!)
[0;1m} T Linear prompt #6



WARNCLS {[0;1;33m
!WCaution: Class "[37m%s[33m" does not exist!!)
[0;1m} T Warning: class does not exist


CANCEL {[0;1;33m
!WAborted.!)
[0;1m} T Process aborted


IOERR {[0;1;31m
!WThere was a problem in creating the bulletin. Creation aborted.!)
[0;1m} T I/O error while writing news bulletin


BLTOK {[0;1;32m
!WNews bulletin [37m%d[32m created.!)
[0;1m} T News bulletin created


TXTCAN {[0;1;32m
!WBulletin text edit aborted.
Any changes to the bulletin's properties have been saved, though.!)
[0;1m} T News bulletin text edit canceled





ASKEDT {[0;1m
!WEnter the bulletin number to edit, [33m?[37m for help, or
[33mX[37m to exit:!)[0m } T Edit bulletin: What number?


ASKUPL {[0;1m
!WWould you like to upload a new news bulletin or edit the existing text of the news bulletin?
([[33mY[37m]es=upload, [[33mN[37m]o=neither, or [[33mE[37m]dit) } T Edit bulletin: re-upload bulletin?


ASKUPLD {[Enter=No]:[0m!) } T Edit bulletin: default response


ASKERR {[0;1;31m
!JPlease enter [33mY[31m, [33mN[31m or [33mE[31m.!)
[0;1m} T Edit bulletin: bad answer to ASKUPL


SHEADER {[0;1;35m
ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
³ Bulletin [37m#%-3d[35m ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
³ Send: [37m%-9s %-8s[35m         ³ Priority: [37m%-4d[35m                            ³
³ Bulletin lifetime (days): [37m%4d[35m   ³ Additional info: [37m%-18s[35m       ³
³ Class: [37m%-10s[35m                ³ Key: [37m%-3d[35m                                  ³
ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
[0;1m} T Sysop version of the Bulletin Header


LSTHDR {[0;1m

ÚÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
³ [33m # [37m ³ [33m   DATE AND TIME  [37m ³ [33mPRIO[37m ³ [33mLIFETIME[37m ³ [33mCLASS  AND  KEY [37m ³
ÃÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ´
} T News bulletin list, header


LSTTAB {³ [32m%3d[37m ³ [32m%s %s[37m ³ [32m%+4d[37m ³  [32m%5d%c[37m  ³ [32m%-10s   %3d[37m ³
} T News bulletin list, table


LSTFTR {ÀÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ

(*) = Disabled (invisible) bulletin.

[0;1m} T News bulletin list, footer



RDNEWS {[2J[0;1;31mLatest news:

} T Reading news bulletins


HEADER {[0;1mÛÛ  [35m%s[0;1m  ÛÛ  %s

} T Bulletin Header


NEWBLT {[0;1;33;5m*NEW*[0;1m} T You've never read this bulletin before


BLTDIV {[0;1m
} T Bulletin divider


NONEWS {[0;1;31m
[!WSorry, there aren't any news news bulletins to show.!)
[0;1m
} T News file is empty


DELBLT {[0;1m
!WEnter the number of the bulleting to delete, [33m?[37m for a list, or
[33mX[37m to exit:!)[0m } T Delete bulletin: What number?


NUMERR {[0;1;31m
!WSorry, bulletin [37m%d[31m does not exist.!)
} T Delete bulletin rebuff unknown bulletin


DELOK {[0;1m
!WOK, the bulletin was deleted.!)
[0;1m} T Delete bulletin: Deletion successful


FTOOMANY {[0;1;33m
!JYou've uploaded more than one file. Only the first file will be used.!)
[0;1m} T Upload bulltin: more than one file uploaded


LANGEND {}

