LEVEL2 {}

ENTRYKEY {Key required to enter the mailer: 0} N 0 129

UPLKEY {Key required to upload packets: 2} N 0 129

CHGDNL {Charge for downloading packet: 0} N -100000 100000

BBSID {ACRO} S 8 Short BBS-ID stamped on QWK packets

STPNCNF {Stop download if user hasn't set up preferences? NO} B

QWKUC {QWK Packet filename converted to: LOWERCASE} E UPPERCASE LOWERCASE

ANSIHI {Include a 'welcome' ANSI file in QWK packets? YES} B

HIFILE {MRGMHI.ANS} S 12 'Welcome' file name? (no directories)

ANSIBYE {Include a 'goodbye' ANSI file in QWK packets? YES} B

BYEFILE {MRGMBYE.ANS} S 12 'Goodbye' file name? (no directories)

DEFGRK {Produce Greek QWK packets by default? YES} B

AUDDNL {Log downloads in the audit trail? YES} B

AUDUPL {Log uploads in the audit trail? NO} B

CTLNAME1 {Mailer} S 16 QWK Control Name (recipient for requests, etc):

CTLNAME2 {MRGMAIL} S 16 QWK Control Name alias 1/5 (if necessary)

CTLNAME3 {NETMAIL} S 16 QWK Control Name alias 2/5 (if necessary)

CTLNAME4 {QWKMAIL} S 16 QWK Control Name alias 3/5 (if necessary)

CTLNAME5 {QMAIL} S 16 QWK Control Name alias 4/5 (if necessary)

CTLNAME6 {ACRO} S 16 QWK Control Name alias 5/5 (if necessary)





LEVEL3 {}


NOAXES {[0;1;31m
!J¬§á£ , «¦ §å§æ §¨æ©©ãª ©ª ¤ ©ª § «¨â§  « ®¨ã© «¦¬ mailer.!)
[0;1m} T You don't have the proper key to access the mailer


MENU {[2J[0m[47;1;37m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;30;47m¿ [40m
[47;1;37m ³  [0;47;30m                    Off-Line Mailer                    [0;47;30m³ [40m
[47;1;37m ³  [0;47;30mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ  [0;47;30m³ [40m
[47;1;37m ³  [0;31;47mA[30mbout the Mailer . . . . . . . .  ¤ ¡âª ¢¨¦­¦¨åª  [30m³ [40m
[47;1;37m ³  [0;31;47mD[30mownload  . . . . . . . . . . . . . ã¯ ¤â¦¬ §¡â«¦¬  [30m³ [40m
[47;1;37m ³  [0;31;47mU[30mpload . . . . . . . . . . . . .  §¦©«¦¢ã §¤«ã©à¤  [30m³ [40m
[47;1;37m ³  [0;31;47mS[30metup . . . . . . . . . . .  ¨¦« £ã© ª ¡  § ¢¦âª  [30m³ [40m
[47;1;37m ³                                                         [0;47;30m³ [40m
[47;1;37m ³ [0;30;47me[31mX[30mit  . . . . . . . . . . . . . . . . . . . . . ¥¦¦ª  [30m³ [40m
[47;1;37m À[0;30;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0;1m

Off-Line Mailer
¨¡¢é é©« «¤ § ¢¦ã ©ª: [0m} T Mailer main menu


SHORT {[0;1m
Off-Line Mailer
!Wé©« «¤ § ¢¦ã ©ª ([33mA[37m,[33mD[37m,[33mU[37m,[33mS[37m,[33mX[37m   â¥¦¦, ã [33m?[37m   «¦ £¤¦ç): !)[0m} T Mailer short menu


ERRSEL {[0;1;31m
¬§á£ , ¤ ¬§á¨®   § ¢¦ã "%c".
[0;1m} T Invalid option selection


LEAVE {[0;1m
!J¥¦¦ª §æ «¦¤ Off-line Mailer.!)
[0;1m} T Leaving the mailer


ABOUT {[0;1m
!J «¤ ¦ã  «¦¬ [32mOff-Line Mailer[37m £§¦¨å« ¤ ¢á« « £¤ç£« «ª
á©ª © ©¬£§ ©£â¤ £¦¨­ã ¡  £ «¦ [32mQWK format[37m.  "§¡â« £¤¬£á«à¤" §¦¬
¢£á¤«  á¦¤«  £ «¤ ¦ã  ¤à©«é¤ [32moff-line readers[37m §¦¬  â« 
 @BBS@.!)

!J¦ §¨é«¦ §¨á£ §¦¬ §¨â§  ¤ ¡á¤« å¤  ¤ ¨¬£å©« « ª §¨¦« £ã© ª
©ª, £â©à «ª ¤«¦¢ãª [33mS[37metup (¡¦¢¦¬ã©« « ª ¡å ¦åª). ©«¨
£§¦¨å« ¤ ¢á« â¤ §¡â«¦ QWK £ «¤ ¤«¦¢ã [33mD[37mownload. ¤
¨æ«¨ â®« ©®£«å©  §¡â«¦ §¤«ã©à¤, £§¦¨å« ¤ «¦ §¦©«å¢« ©«¤
á© £ «¤ [33mU[37mpload.!)

[0;1m} T Main Menu Help


NEWCNF {[0;1;36m
!J§ ã ¬«ã å¤   §¨é« ­¦¨á §¦¬ ®¨© £¦§¦ å« «¦¤ Off-Line Mailer,
§¨ ¤ ¡á¤« ¦« ã§¦« á¢¢¦ ©ª «å«  ¤ ¨¬£å©« « ª §¨¦©à§ ¡âª ©ª
§¨¦« £ã© ª.!)

!J¨¡¢¦ç£, [37m§¨ ¤[36m £ ¦¬¨ã©« «¦ §¨é«¦ ©ª §¡â«¦, ¢â¥« æ« 
[37mæ¢ª[36m ¦  ¨¬£å© ª ©ª å¤   ¡¤¦§¦ « ¡âª. ¢¢ éª  ¡ ¤¬¤ç« ¤
¢á« §¡â«¦ ©ç£«¦ £ «¦ §¨æ¨££á ©ª, ã ¤ ®¨àå« § §¢â¦¤ £¦¤áª
®à¨åª ¢æ¦.!)
[0;1m} T User's first use of the mailer, forcing configuration


SETUPH {[2J[0m[47;1;37m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;30;47m¿ [40m
[47;1;37m ³  [0;47;30m                         ç£ © ¨¦« £ã©à¤                         [0;47;30m  ³ [40m
[47;1;37m ³  [0;47;30mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ  [0;47;30m³ [40m
} T Setup, menu header


SETUPPL {[47;1;37m ³  [0;31;47m%c[30m %67s  [30m³ [40m
} T Setup, plugin line


SETUPF {[47;1;37m ³                                                                         [0;47;30m³ [40m
[47;1;37m ³  [0;31;47mS[30metup QWK  . . . . . . . . . . . . . . . .  ¤ ¡ãª ­ç©ª §¨¦« £ã© ª  [30m³ [40m
[47;1;37m ³                                                                         [0;47;30m³ [40m
[47;1;37m ³ [0;30;47me[31mX[30mit  . . . . . . . . . . . . . . . . . . . . . . . . . . . . . ¥¦¦ª  [30m³ [40m
[47;1;37m À[0;30;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0;1m

ç£ © §¨¦« £ã©à¤
¨¡¢é é©« «¤ § ¢¦ã ©ª: [0m} T Setup, menu footer


SETUPSH {[0;1m
!Wé©« «¤ § ¢¦ã ©ª, [33mX[37m   â¥¦¦ ã [33m?[37m   «¦ £¤¦ç: [0m!) } T Setup, short menu


QWKVT {[0m[30;47m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [34m¤ ¡ãª ­ç©ª §¨¦« £ã© ª[0;30;47m ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;1;37;47m¿ [0m
[30;47m ³                                                                          [0;1;47;37m³ [0m
[30;47m ³  ¨æ¨££ ©¬£§å©ª         [0;30;46m @20;"PKZIP 2.04g|LHARC 1.02|Tar & GNUZip (Unix)|ZOO 2.1"l [0;47;30m  (space   ¢¢ã)[0;1;47;37m  ³ [0m
[30;47m ³                                                                          [0;1;47;37m³ [0m
[30;47m ³  ¨æ¨££ §¦©¬£§å©ª      [0;30;46m @20;"PKZIP 2.04g|ARJ 2.30|LHARC 1.02|Tar & GNUZip (Unix)|ZOO 2.1"l [0;47;30m  (space   ¢¢ã)[0;1;47;37m  ³ [0m
[30;47m ³                                                                          [0;1;47;37m³ [0m
[30;47m ³  ¢¢¤ ¡æ QWK format         [0;30;46m [@"X "t] [0;47;30m                   (Space   ¢¢ã)  [0;1;47;37m³ [0m
[30;47m ³                                                                          [0;1;47;37m³ [0m
[30;47m ³  ¤¦£©å §¡â«¦¬            [1;37;44m@10;10;0s[0;47;30m.QWK                          [0;1;47;37m  ³ [0m
[30;47m ³                                                                          [0;1;47;37m³ [0m
[30;47m ³  Character set               [0;30;46m @21;"¢¢¤ ¡á 437G/737|¢¢¤ ¡á /ISO|437 PC ®à¨åª ¢¢¤ ¡á|7-bit ASCII"l [0;47;30m                     [0;1;47;37m³ [0m
[30;47m ³                                                                          [0;1;47;37m³ [0m
[30;47m ³  Ctrl-R: ¦ã                  [0;1;42;33m@14;"OK"b[0;47;30mÜ    [0;1;41;33m@14;"¡¬¨¦"b[0;47;30mÜ  [0;1;47;37m³ [0m
[30;47m ³                                   ßßßßßßßßßßßßßßßß     ßßßßßßßßßßßßßßßß  [0;1;47;37m³ [0m
[30;47m À[0;1;37;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0m} T Setup QWK, Visual template


TR0 {} T String for translation table #0 in edit templates
TR1 {¢¢¤ ¡á 437G/737} T String for translation table #1 in edit templates
TR2 {¢¢¤ ¡á /ISO} T String for translation table #2 in edit templates
TR3 {437 PC ®à¨åª ¢¢¤ ¡á} T String for translation table #3 in edit templates
TR4 {7-bit ASCII} T String for translation table #4 in edit templates
TR5 {} T String for translation table #5 in edit templates
TR6 {} T String for translation table #6 in edit templates
TR7 {} T String for translation table #7 in edit templates
TR8 {} T String for translation table #8 in edit templates
TR9 {} T String for translation table #9 in edit templates


QWKLT {[2J[0;30;47m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [34m¤ ¡ãª ­ç©ª §¨¦« £ã© ª[0;30;47m ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;1;37;47m¿ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m1[30m. ¨æ¨££ ©¬£§å©ª . . . . . . . . . . . . .  [34m@20;"PKZIP 2.04g|LHARC 1.02|Tar & GNUZip (Unix)|ZOO 2.1"l[0;1;47;37m   ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m2[30m. ¨æ¨££ §¦©¬£§å©ª . . . . . . . . . . . . [34m@20;"PKZIP 2.04g|ARJ 2.30|LHARC 1.02|Tar & GNUZip (Unix)|ZOO 2.1"l[0;1;47;37m   ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m3[30m. ¢¢¤ ¡æ QWK format . . . . . . . . . . . . .  [34m@"X "t[0;1;47;37m                    ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m4[30m. ¤¦£©å §¡â«¦¬ . . . . . . . . . . . . . . . [34m@10;10;0s[30m.QWK[1;37m         ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m ³ [31m5[30m. Character set «¦¬ reader ©ª  . . . . . . . .  [34m@21;"¢¢¤ ¡á 437G/737|¢¢¤ ¡á /ISO|437 PC ®à¨åª ¢¢¤ ¡á|7-bit ASCII"l[0;1;47;37m  ³ [0m
[30;47m ³                                                                          [1;37m³ [0m
[30;47m À[0;1;37;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0;1m
} T Setup QWK, Linear template


QWKLT1 {[0;1m
!Jé £§¦¨å« ¤ ¦¨å©« «¦ §¨æ¨££ §¦¬  ®¨© £¦§¦ å
¦ Mailer   ¤ ©¬£§ â©  « §¡â« ©ª.  ¢â¥« â¤ §¨æ¨££ §¦¬
¬§á¨®  ©«¦¤ ¬§¦¢¦ ©«ã ©ª, £  ¡  ¡å  §¦©¬£§ ©«å «¦ §¡â«¦
£ «¦ ¤«å©«¦ ®¦ §¦©¬£§ ©« ¡æ.!)
[0;1m} T Setup QWK, Linear template, set compressor


QWKLT2 {[0;1m
!Jé £§¦¨å« ¤ ¦¨å©« «¦ §¨æ¨££ §¦¬  ®¨© £¦§¦ å
¦ Mailer   ¤ §¦©¬£§ â©  « §¡â« §¤«ã©é¤ ©ª. ¬£§ â« « §¡â« ©ª
£ â¤ §æ « §¨¡á«à §¨¦¨á££« (ã ¡á§¦ ¦ ©¬£«æ)   ¤ £§¦¨å  @BBS@ ¤
§¦©¬£§ â©  ©à©«á «¦ §¡â«¦.!)
[0;1m} T Setup QWK, Linear template, set decompressor


QWKLT3 {[0;1m
!Jå £ ¡¨ã ¢§«¦£â¨   ­¦¨¦§¦ å «¦ QWK format §¦¬ ®¨© £¦§¦ å«  ©«¤
@BBS@ §æ ¬«æ §¦¬ ®¨© £¦§¦ å«   ¤éª: ¦ QWK format ®¨© £¦§¦ å «¦¤
®¨¡«ã¨ 'ã' (ã« «¦¤¦ç£¤¦)   ¤  ®à¨å©  « ª ¨££âª ¤æª £¤ç£«¦ª. 
§ ã ©« ¢¢¤ ¡á ©¬©«ã£« «¦ ¨á££ ¬«æ å¤  £á¢¢¦¤ ®¨ã© £¦, â® 
å¤  £««¨¦§ã ©«¦ format é©« ¤ ®¨© £¦§¦ å á¢¢¦¤ ®¨¡«ã¨ (ASCII #12).

!J¤  § ¢¦ã ¢¢¤ ¡é¤ QWK §¡â«à¤ å¤  ¤¨¦§¦ £â¤, « §¡â« 
¡¦¢¦¬¦ç¤ «¦ GreekQWK format, ¢¢ éª  ©¬£­à¤¦ç¤ £ «¦  ¤âª QWK.   ¤
 á©« §¡â« GreekQWK  ®¨ ©«å ¤ ­¨£æ©« â¤ patch ©«¦¤ off-line
reader ©ª, ã ¤ ¦¨å©« â¤   ¡æ §¨æ¨££ àª ©¬£§ ©« ¡æ.  
§¨ ©©æ«¨ª ¦åª, å« «¦ manual «¦¬ Mailer.!)
[0;1m} T Setup QWK, Linear template, GreekQWK


QWKLT4 {[0;1m
!J¬«ã  § ¢¦ã ©ª § «¨â§  ¤ ¦¨å©« «¦ æ¤¦£ ¨®å¦¬ §¦¬  â®  «¦
§¡â«¦ ©ª. ¬«æ å¤  ®¨ã© £¦   single-user ©¬©«ã£« £ §¦¢¢¦çª ®¨ã©«ª
(§® MS-DOS) ã   ¤ ¤«§¥â¢  ¡¤åª ©   ¡âª ¤á¡ª ¡á§¦ à¤ off-line
readers ã QWK ©¬©«£á«à¤.!)
[0;1m} T Setup QWK, Linear template, set packet name


QWKLT5 {[0;1m
!Jé £§¦¨å« ¤ ¨¬£å©« «  å¦¬ª ©ç¤¦¢¦ ¢â§« ©«¦¤ off-line reader
©ª.  mailer  £«­¨á  « §¡â« ©ª §æ ¡  §¨¦ª ¬«æ «¦ character set
  ¤  ¬¡¦¢ç¤  «¤ ¤á¤à©.  £«á­¨© ©¬¤ãàª  â®  ¤«å©«¦ ®
¨ç£ © £'¡å¤ ©«¦¤ ¢¦¨ ©£æ ©ª ([33m/GO ACCOUNT[37m), ¢¢á ¬§á¨®¦¬¤
§¨ §«é© ª §¦¬ ¬«æ ¤ ©¬£å¤  (§® ©¬¤â©« £â©à 7-bit telnet, ¢¢á
 á« « §¡â« ©ª £ -928).!)

!J¤ ¤ £§¦¨å« ¤ §¦­©å©«, ®¨© £¦§¦ ã©« [33m437G/737[37m  
§¢ á ©¬©«ã£« ã readers ¡á«à §æ DOS (ã © DOS §¨á¬¨¦ «à¤ Windows), ã
[33m-928[37m   ¦¨ ©£â¤ setups Amiga ¡  ¤â ©¬©«ã£«
¤ ¡æ«¨.!)
} T Setup QWK, Linear template, character set help





SETUPAB {[0;1;31m
!J ©«¦ ®å ©ª ¤ ¤£¨é¡¤.!)
[0;1m} T Setup QWK, data not updated


SETUPOK {[0;1;32m
!J ©«¦ ®å ©ª ¤£¨é¡¤ § «¬®éª.!)
[0;1m} T Setup QWK, data updated successfully





BEGINQWK {[0;1m
!J¨¦«¦ £©å §¡â«¦¬ £¤¬£á«à¤ [32m%s.QWK[37m.  â©« [33mCtrl-C[37m
  «¨£« ©£æ «ª   ¡©åª.!)

[0;1m} T Download, beginning download


DNLNCRD {[0;1;31m
!J¬§á£ , ¤ â®« ¨¡«âª £¦¤áª   ¤ £ ¦¬¨ã©« §¡â«¦ £¤¬£á«à¤
¬«ã « ©« £ã.!)
[0;1m} T Download, you don't have enough credits


NOTCFG {[0m
!W[0;1;33;5mÛÛ[0;1;33m  ¨¦ ¦§¦å©: !i¤ â®« ¡æ£ ¨¬£å© 
(æ¢ª) « ª §¨¦« £ã© ª ©ª. §¦â«¦¬£ æ« 
¦  ¡«á ©¬¤ã¡ ¨¬£å© ª å¤  ¡«á¢¢¢ª   «¦ ©ç©«£á ©ª, ¢¢á
å¤  § ¤æ «¦ §¡â«¦ §¦¬  £ ¦¬¨å «é¨ ¤ å¤  ¥ ¨« ¡á £á¢¦,
á ¦, ã ©ç£«¦ £ «¦¤ off-line reader ©ª.!)
!0l[0;1m} T Download, preferences not found


NOTCFG2 {[0;1;31m
!J¤ â®« ¡æ£ ¨¬£å©  (æ¢ª) « ª §¨¦« £ã© ª ©ª. ¤ £§¦¨¦ç£ ¤
©¬¤®å©¦¬£ £ «¤ £ ¦¬¨å «¦¬ §¡â«¦¬, £  ¡  ¬«æ £§¦¨å ¤ ¡«¢ã¥ 
¥ ¨« ¡á £á¢¦, á ¦, ã ©ç£«¦ £ «¦¤ off-line reader ©ª. ¨¡¢¦ç£
¨¬£å©« æ¢ª « ª §¨¦« £ã© ª ©ª (£ «¤ ¤«¦¢ã [33mS[31m §æ «¦ ¡¤«¨ ¡æ
£¤¦ç «¦¬ Mailer) ¡  ¥¤¦¡ £á©«.!)
[0;1m} T Download, preferences not found, won't create packet


ERRQWK {[0;1;31m
!J £ ¦¬¨å «¦¬ §¡â«¦¬ ©ª ¤ ã«¤ ­ ¡«ã ¥' «åª ¡á§¦ ¦¬
¢á¦¬ª. ¨¡¢¦ç£  ¦§¦ ã©«
«¦¤  ¨ ©«ã ¬©«ã£«¦ª   «¦ ¦¤æª.!)
[0;1m} T Download, error creating packet


ABOQWK {[0;1;31m
!J £ ¦¬¨å «¦¬ §¡â«¦¬ ©ª ¡¬¨é¡.!)
[0;1m} T Download, aborted packet creation


PACKING {[0m
[2J[0;1;32m
!J¨¡¢é §¨ £â¤«, ©¬£§ â¦¬£ «¦ §¡â«¦ ©ª £ «¦ [37m%s[32m...!)[0m } T Download, compressing...


PACKOK {[0;1;32m  «¦ £¦.

[0;1m} T Download, done.


PACKERR {[0;1;31m

!J¬¤é£, ¬§ã¨¥ ¡á§¦ ¦ ¢á¦ª ¡«á «¤ ©¬£§å© «¦¬ §¡â«¦¬ ©ª.
¨¡¢¦ç£  ¦§¦ ã©« «¦¤  ¨ ©«ã ¬©«ã£«¦ª   «¦ ¦¤æª.!)
[0;1m} T Download, compression error


QWKDESC {¡â«¦ £¤¬£á«à¤ QWK} S 49 QWK Packet description when downloading


UPLNAX {[0;1;31m
!J¬§á£ , «¦ §å§æ ©ª ¤ § «¨â§  ¤ §¦©«å¢« §¡â«.!)
[0;1m} T Upload, no access


UPL2MF {[0;1;31m
!J§¦©«å¢« §á¤à §æ â¤ ¨®å¦.  §¥¨©«¦ç£ æ¢ « ¨®å, ­'æ©¦¤
å¤  §¡â« £¤¬£á«à¤.!)
[0;1m} T Upload, you have uploaded more than one files


UPL1F {[0;1;32m
!J¦ §¡â«¦ ©ª §¦¡ç¡ ¡  ¨®å   §¥¨©å «¦¬.!)
[0;1m} T Upload, uploaded one file


REPF {[0;1;32m
!J§¥¨æ£©« «¦ §¡â«¦ [37m%d[32m §æ ©ç¤¦¢¦ [37m%d[32m
§¡â«à¤.!)
[0;1m} T Processing REP file (one out of many uploaded)


REPRPRE {[0;1;31m
!Já¦ª ¡«á «¤ §¨¦«¦ £©å «¦¬ §¡â«¦¬! ¨¡¢¦ç£  ¦§¦ ã©« «¦¤
 ¨ ©«ã ¬©«ã£«¦ª   «¦ ¦¤æª.!)
[0;1m} T Error while preparing packet for processing


WRNDUPL {[0;1;33m
!W[5mÛÛ[0;1;33m  ¨¦ ¦§¦å©: !i®« ¥¤©«å¢  ¬«æ ¡¨ éª «¦
§¡â«¦ §¤«ã©à¤! ¤ «¦ §¥¨©«¦ç£, ¡á§¦  £¤ç£«á ©ª £§¦¨å ¤ £­¤ ©«¦ç¤
ç¦ ­¦¨âª ©« á©. ª å¤¦¬£ «¤ ¬¡ ¨å ¤ §¦­©å©« ¤ §¨â§  ¤
§¥¨©«¦ç£ «¦ §¡â«¦,   «¤ §¨å§«à© §¦¬ ©¬£å¤  ¡á«  «¦
©¬¤ã ©«¦. ¤ ¤ ¥â¨«  «å £­¤å©«¡ ¬«æ «¦ £ã¤¬£, §¤«ã©«
¨¤« ¡á ©«¤ §¨¡á«à ¨é«©.!)
!0l[0;1m} T Warning, duplicate packet uploaded


ASKDUPL {[0;1m
!J®« ¥¤©«å¢  ¬«æ «¦ §¡â«¦ §¤«ã©à¤. â¢« ¤
§¥¨©«å ¦ç«àª ã á¢¢àª; ([[33mY[37m]es=¤å / [[33mN[37m]o=æ® )!) } T Ask whether duplicate packet should be processed anyway


ASKDUPD {[Enter=[33mN[37m][0m } T ASKDUPL default answer


ASKDUPR {[0;1;31m
!J¨¡¢¦ç£ §¤«ã©« £ [33mY[31m ã [33mN[31m.!)
[0;1m} T Wrong reply to ASKDUPL


UNPACK {[0m
[2J[0;1;32m
!J§¦©¬£§ â¦¬£ « ª §¤«ã© ª ©ª £ «¦ [37m%s[32m...!)[0m } T Upload, decompressing 


UPACKOK {[0;1;32m  «¦ £¦.

[0;1m} T Upload, done.


UPACKR {[0;1;31m

!J¬¤é£, ¬§ã¨¥ ¡á§¦ ¦ ¢á¦ª ¡«á «¤ §¦©¬£§å© «¦¬ §¡â«¦¬ ©ª.
 ©¬¤ ©£â¤  «å ¬«¦ç «¦¬ ¢á¦¬ª å¤   £ ¤¤é¨ © «¦¬ §¡â«¦¬ ©ª
§æ «¦ §¨§á¤à §¨æ¨££ §¦¦©¬£§å©ª.  àå« æ«   ©¬£§å© «¦¬ 
§¡â«¦¬ §¤«ã©é¤ ©ª â ¤ £ ¬«æ «¦ §¨æ¨££ ¡  ¥¤§¨¦©§ã©«.!)
[0;1m} T Upload, decompression error


ERRREP {[0;1;31m
!J §¨á«à© «ª §¥¨©åª «¦¬ §¡â«¦¬ §¤«ã©é¤ ©ª
¤ ã«¤ ­ ¡«ã ¥' «åª ¡á§¦ ¦¬ ¢á¦¬ª. ¨¡¢¦ç£  ¦§¦ ã©«
«¦¤  ¨ ©«ã ¬©«ã£«¦ª   «¦ ¦¤æª.!)
[0;1m} T Upload, error processing packet


ABOREP {[0;1;31m
!J §¥¨©å «¦¬ §¡â«¦¬ ©ª ¡¬¨é¡. ¨¡¢¦ç£, ©£ é©« §àª æ© £¤ç£«
«¦¬ §¡â«¦¬ §¤«ã©é¤ ©ª â®¦¬¤ ã §¥¨©«å ¨å©¡¦¤«  ã ©«¤ á© ¡  
§¨â§  ¤ «  ¨á¯« §æ «¦ ¢¡«¨¦¤ ¡æ ®¬¨¦£å¦ (Email).!)
[0;1m} T Upload, aborted packet processing






















MPTYQWK {[0;1;31m
¤ ¨â¡¤ £¤ç£« ã ¨®å ¤  ©®¦ç¤ ©«¦ §¡â«¦ ©ª.
[0;1m} T Download: Nothing to put in your packet











WARNDUP {[0;1;31;5m
¨¦ ¦§¦å©: [0;1m®« ã ©«å¢  §¡â«¦ §¤«ã©à¤ £«á §æ «¤
               «¢¬«å ©ª ¢ã¯ §¡â«¦¬ £¤¬£á«à¤. §á¨®  § ¤æ««
               «¦ §¡â«¦ §¤«ã©à¤ §¦¬ â¢« ¤ §¦©«å¢« «é¨ ¤ â-
               ®  ã ©«¢å ©«¤ á©. ¨¡¢é ¢â¥« «¦ §¡â«¦ ©ª
               §¨¦¡ £â¤¦¬ ¤ §¦­¬®¦ç¤ §¦¢¢§¢âª £­¤å© ª £¤¬£á«à¤
               ©ª ©«¤ á©. ã¤« « §¡â« §¤«ã©é¤ ©ª £«á §æ
               «¤ §¦©«¦¢ã «¦¬ª ©«¤ á©.

 â©« [33mEnter[37m   ©¬¤â® , ã [33mX[37m   â¥¦¦: [0m} T Upload: You may have already uploaded this REP packet


WARNSRT {[0;1;31;5m
¨¦ ¦§¦å©: [0;1m  ¡à ¡¦å ¨ £¦å ¦¨ ©£â¤à¤ clubs â®¦¬¤ £«¢å ¢æà
               ¢­« ¡ãª «¥ ¤æ£©ãª «à¤ clubs. §á¨®  § ¤æ«« ¡á§¦ 
               £¤ç£«á ©ª ¤ ©«¢¦ç¤ © ¢á¦ª §¨ ¦®ã. ¨¡¢é ¢â¥«
               §¨¦©¡« ¡á «¦¤ §¨¦¦¨ ©£æ «¦¬ª æ§àª £­¤å«  ©«¦¤ §å¤¡
               §¥¨©åª «¦¬ REP §¡â«¦¬ ©ª.

 â©« [33mEnter[37m   ©¬¤â® , ã [33mX[37m   â¥¦¦: [0m} T Upload: SIGSORT changed SIG numbers












UPLING {[0;1;31m
á§¦ ¦ª á¢¢¦ª ®¨© £¦§¦ å ¬«ã «¤ ¬§¨©å. ¤¦¡ £á©« © ¢å é¨.
[0;1m} T Upload: The upload facility is currently in use


NOREPF {[0;1;31m
¤ £§æ¨© ¤ ¨å «¦ §¡â«¦ §¤«ã©é¤ ©ª.
[0;1m} T Upload: Couldn't find the REP file attachment


UNKREPF {[0;1;31m
¦ ¨®å¦ §¦¬ §¦©«å¢« ¤ å¤  §¡â«¦ §¤«ã©à¤.  §¡â« §¤«ã©é¤
©ª §¨â§  ¤ §¨ â®¦¬¤ «¦ ¨®å¦ [33m%s.MSG[31m ã [33m%s.MSG[31m, ¡  ¤
å¤  ©¬£§ ©£â¤ £ «¦ ©¬£§ ©« ¡æ §¨æ¨££ [33mPKZIP 1.1[31m.
[0;1m} T Upload: This is not a REP packet


BADREP {[0;1;31m
¦ ¨®å¦ §¦¬ §¦©«å¢« ¤ å¤  §¦¡«æ QWK §¡â«¦ §¤«ã©à¤.
[0;1m} T Upload: This is not an acceptable REP packet


BADBBSID {[0;1;31m
¦ §¡â«¦ £¤¬£á«à¤ §¦¬ §¦©«å¢« §¨¦¦¨ æ«¤   «¤ á© £ ¡à ¡æ
[33m%s[31m ¡  æ®    «¤ Acrobase (¡à ¡æª [33m%s[31m).
[0;1m} T Upload: Incorrect BBS ID stamped on REP packet


ABORT {[0;1;31;5m
¨£« ©£æª   ¡©åª.
[0;1m} T Generic: Process aborted


EXIOLM {[0;1m
¥¦¦ª §æ «¦¤ Off-Line Mailer...
[0;1m} T Generic: Exit from the Off-Line Mailer


EXIMAIN {[0;1m
¥¦¦ª ©«¦ ¡¤«¨ ¡æ £¤¦ç «¦¬ Off-Line Mailer.
[0;1m} T Generic: Exit to main Off-Line Mailer menu
