LEVEL2 {}


ENTRYKEY {Key required to enter the event manager? 128} N 0 129


Normally, even sysops aren't allowed full access to the
event manager, for more-than-clear reasons of security.
The following space-delimited list of users (Sysop is
always allowed full access) defines the trusted users,
who may add, delete and modify events. All other users
with access to this module are restricted to scheduling
and cancelling already existing events.

FULLAXID {Morgul} S 40 Privileged access granted to:


LOGSHD {Record BBS shutdown events in the audit trail? YES} B

LOGSPN {Record all scheduled events in the audit trail? YES} B

LOGPRE {Record creation/deletion of events in the audit trail? YES} B


LEVEL3 {}


NOENTRY {[0;1;31m
Š¬§á£˜ , ›œ¤ â®œ«œ §¨æ©™˜© ©œ ˜¬«ã «¤ §œ¨ ¦®ã.
[0;1m} T You don't have access to this module


MENU {[2J[0m[47;1;37m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;30;47m¿ [40m
[47;1;37m ³  [0;47;30mEvent Manager 0.5                                   [0;47;30m³ [40m
[47;1;37m ³  [0;47;30mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ  [0;47;30m³ [40m
[47;1;37m ³  [0;31;47mS[30mhutdown BBS . . . . . . .  €§œ¤œ¨š¦§¦å© š¨˜££é¤  [30m³ [40m
[47;1;37m ³  [0;31;47mU[30mndo shutdown . . . . . . ‹˜«˜åà© ˜§œ¤œ¨š¦§¦å©ª  [30m³ [40m
[47;1;37m ³                                                      [0;47;30m³ [40m
[47;1;37m ³  [0;31;47mL[30mist events . . . . . . . . . . . ‰˜«á¢¦š¦ª events  [30m³ [40m
[47;1;37m ³  [0;31;47mA[30mdd (schedule) event . . . . .  „¤œ¨š¦§¦å© event  [30m³ [40m
[47;1;37m ³  [0;31;47mC[30mancel event  . . . . . . . . . . . ‹˜«˜åà© event  [30m³ [40m
[47;1;37m ³                                                      [0;47;30m³ [40m
[47;1;37m ³ [0;30;47me[31mX[30mit . . . . . . . . . . . . . . . . . . . . „¥¦›¦ª  [30m³ [40m
[47;1;37m À[0;30;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0;1m

[32mEvent Manager[37m
˜¨˜¡˜¢é ›é©«œ «¤ œ§ ¢¦šã ©˜ª: [0m} T Main menu, normal version


SHMENU {[0;1;32m
Event Manager[37m
!Wƒé©«œ «¤ œ§ ¢¦šã ©˜ª ([33mS[37m,[33mU[37m,[33mL[37m,[33mA[37m,[33mC[37m,[33mX[37m š ˜ â¥¦›¦, ã [33m?[37m š ˜ «¦ £œ¤¦ç): !)[0m} T Short menu, normal version


PMENU {[2J[0m[47;1;37m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;30;47m¿ [40m
[47;1;37m ³  [0;47;30mEvent Manager 0.5                                   [0;47;30m³ [40m
[47;1;37m ³  [0;47;30mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ  [0;47;30m³ [40m
[47;1;37m ³  [0;31;47mS[30mhutdown BBS . . . . . . .  €§œ¤œ¨š¦§¦å© š¨˜££é¤  [30m³ [40m
[47;1;37m ³  [0;31;47mU[30mndo shutdown . . . . . . ‹˜«˜åà© ˜§œ¤œ¨š¦§¦å©ª  [30m³ [40m
[47;1;37m ³                                                      [0;47;30m³ [40m
[47;1;37m ³  [0;31;47mL[30mist events . . . . . . . . . . . ‰˜«á¢¦š¦ª events  [30m³ [40m
[47;1;37m ³  [0;31;47mA[30mdd (schedule) event . . . . .  „¤œ¨š¦§¦å© event  [30m³ [40m
[47;1;37m ³  [0;31;47mC[30mancel event  . . . . . . . . . . . ‹˜«˜åà© event  [30m³ [40m
[47;1;37m ³                                                      [0;47;30m³ [40m
[47;1;37m ³  [0;31;47mN[30mew event  . . . . . . . . . ƒ£ ¦¬¨šå˜ ¤â¦¬ event  [30m³ [40m
[47;1;37m ³  [0;31;47mD[30melete event  . . . . . . . . . .  ‰˜«á¨š© event  [30m³ [40m
[47;1;37m ³                                                      [0;47;30m³ [40m
[47;1;37m ³ [0;30;47me[31mX[30mit . . . . . . . . . . . . . . . . . . . . „¥¦›¦ª  [30m³ [40m
[47;1;37m À[0;30;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0;1m

[32mEvent Manager[37m
˜¨˜¡˜¢é ›é©«œ «¤ œ§ ¢¦šã ©˜ª: [0m} T Main menu, privileged version


SHPMENU {[0;1;32m
Event Manager[37m
!Wƒé©«œ «¤ œ§ ¢¦šã ©˜ª ([33mS[37m,[33mU[37m,[33mL[37m,[33mA[37m,[33mC[37m,[33mN[37m,[33mD[37m,[33mX[37m š ˜ â¥¦›¦, ã [33m?[37m š ˜ «¦ £œ¤¦ç): !)[0m} T Short menu, privileged version


ERRSEL {[0;1;31m
Š¬§á£˜ , ›œ¤ ¬§á¨®œ  ˜¬«ã  œ§ ¢¦šã.
[0;1m} T Invalid option


LEAVE {[0;1m
„¥¦›¦ª ˜§æ «¦¤ event manager.
} T Leaving the event manager


EVNNAME {[0;1;32m
!J‰˜«'˜¨®ã¤ §¨â§œ  ¤˜ ›é©œ«œ â¤˜ ©ç¤«¦£¦ æ¤¦£˜ (£â®¨  13 ®˜¨˜¡«ã¨œª) ©«¦ §¨¦ª
›£ ¦¬¨šå˜ event. ’¦ æ¤¦£˜ £§¦¨œå ¤˜ §œ¨ â®œ  £æ¤¦ š¨á££˜«˜ ¡˜  ˜¨ Ÿ£¦çª.
•˜¨˜¡«¨ ©« ¡á ¦¤æ£˜«˜ œå¤˜  "shutdown", "cleanup", ¡¢§.!)[37m

                                             ÃÄÄÄÄÄÄÄÄÄÄÄ´
ƒé©«œ «¦ æ¤¦£˜ «¦¬ ¤â¦¬ event ([33mX[37m š ˜ â¥¦›¦): [0m} T New event: Asking for event name


EVNALRX {[0;1;31m
€¬«æ «¦ event â®œ  ã› ›£ ¦¬¨šŸœå.
[0;1m} T New event: Event name already exists


EVNCHR {[0;1;31m
’¦ æ¤¦£˜ «¦¬ event §œ¨ â®œ  £ ˜§¦›œ¡«¦çª ®˜¨˜¡«ã¨œª.
[0;1m} T New event: Event name contains invalid characters


EVNDESC {[0;1;32m
!J’é¨˜ §¨â§œ  ¤˜ ›é©œ«œ £å˜ ©ç¤«¦£ §œ¨ š¨˜­ã «¦¬ event, £ã¡¦¬ª 40
®˜¨˜¡«ã¨à¤. ‰á¤«œ «¤ §œ¨ š¨˜­ã œ§œ¥š£˜« ¡ã, ©œ §œ¨å§«à© §¦¬ «¦
æ¤¦£˜ ›œ¤ «˜ ¢âœ  æ¢˜. † §œ¨ š¨˜­ã £§¦¨œå ¤˜ §œ¨ â®œ  æ,«  ®˜¨˜¡«ã¨œª
Ÿâ¢œ«œ.!)[37m

                                   ÃÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ´
ƒé©«œ «¤ §œ¨ š¨˜­ã ([33mX[37m š ˜ â¥¦›¦): [0m} T New event: Asking for event description


EVNPROG {[0;1;32m
!Jƒé©«œ «¦ æ¤¦£˜ «¦¬ §¨¦š¨á££˜«¦ª §¦¬ Ÿ˜ «¨â®œ  ¦ BBS daemon š ˜ ¤˜
œ¡«œ¢œ©«œå «¦ event. ‹§¦¨œå«œ ¤˜ ›é©œ«œ §¢ã¨œª command line
(£œ §˜¨˜£â«¨¦¬ª ¡¢§). ’¦ working directory «¦¬ BBSD ¡˜Ÿéª œ¡«œ¢œå events
œå¤˜  «¦ /usr/local/bbs/bin. Binaries ©œ á¢¢˜ directories §¨â§œ  ¤˜ ›àŸ¦ç¤ œ›é £œ
«¦ §¢ã¨œª æ¤¦£á «¦¬ª (§® /usr/bin/soupieres). „¤˜¢¢˜¡« ¡á ¡á¤«œ â¤˜
link ˜§æ «¦ /usr/local/bbs/bin ©«¦ ¡˜«á¢¢¢¦ directory. ¨¦­˜¤éª ˜¤ ›œ¤ ¥â¨œ«œ ˜¡¨ ™éª
«  ¡á¤œ«œ, £¤ «¦ ¡á¤œ«œ.!)[37m

ƒé©«œ «¦ command line «¦¬ event ([33mX[37m š ˜ â¥¦›¦): [0m} T New event: Asking for event command


EVNONCE {[0;1;32m
!J  œ§æ£œ¤œª «¨œ ª (¡˜  «œ¢œ¬«˜åœª) œ¨à«ã©œ ª Ÿ˜ ¡˜Ÿ¦¨å©¦¬¤ «¤ ­ç©
«¦¬ event.!)

!J«˜¤ â¤˜ event œ¡«œ¢œå«˜ , Ÿâ¢œ«œ ¤˜ £â¤œ  ©«¤ ¢å©«˜; €¤ ˜§˜¤«ã©œ«œ
¡˜«˜­˜« ¡á œ›é, ¡˜  §¨¦š¨˜££˜«å©œ«œ «¦ event ¤˜ «¨â¥œ , §®, ©« ª 05.00,
«¦ event Ÿ˜ §˜¨˜£œå¤œ  ©«¤ ¢å©«˜ œ§'˜æ¨ ©«¦¤, ¡˜  Ÿ˜ œ¡«œ¢œå«˜  ‰€‡„
£â¨˜ ©« ª 05.00. ’¦ cleanup œå¤˜  §˜¨á›œ š£˜ œ¤æª «â«¦ ¦¬ event. €¤,
˜¤«åŸœ«˜, ˜§˜¤«ã©œ«œ ˜¨¤« ¡á ©«¤ œ¨é«©, «æ«œ «¦ event Ÿ˜ œ¡«œ¢œå«˜  £æ¤¦
£å˜ ­¦¨á. ’¦ shutdown œå¤˜  §˜¨á›œ š£˜ œ¤æª event §¦¬ ›œ¤ Ÿâ¢¦¬£œ ¤˜
œ¡«œ¢œå«˜  ¡áŸœ £â¨˜.!)[37m

„¡«â¢œ© «¦¬ event ¡˜Ÿ£œ¨ ¤á ([33mX[37m š ˜ â¥¦›¦); [0m} T New event: Running once/daily?


EVNUNIQ {[0;1;32m
!J‹œ¨ ¡á events §¨â§œ  ¤˜ ™¨å©¡¦¤«˜  ©«¤ ¢å©«˜ œ¡«â¢œ©ª «¦ §¦¢ç £å˜ ­¦¨á.
‚ ˜ §˜¨á›œ š£˜, ›ç¦ shutdowns «˜¬«æ®¨¦¤˜ (ã ©œ › ˜­¦¨œ« ¡âª é¨œª), ˜§¢éª
›£ ¦¬¨š¦ç¤ ®á¦ª, œ¤é ›ç¦ cleanups «˜¬«æ®¨¦¤˜ (ã ©œ › ˜­¦¨œ« ¡âª é¨œª «¤
å› ˜ £â¨˜), ¡˜«˜©«¨â­¦¬¤ ©«˜« ©« ¡á ©«¦ ®œå˜ ¡¢§. €§˜¤«ã©«œ ¡˜«˜­˜« ¡á ˜¤
«¦ ¤â¦ event ˜¤ã¡œ  ©œ ˜¬«ã «¤ ¡˜«š¦¨å˜.!)[37m

‹¦¤¦ â¤˜ «â«¦ ¦ event ˜¤á §á©˜ ©« š£ã ([33mX[37m š ˜ â¥¦›¦); [0m} T New event: Unique event?


EVNWARN {[0;1;32m
!J€¤ Ÿâ¢œ«œ, £§¦¨¦ç£œ ¤˜ ¡˜¢¦ç£œ «¦ event §¦¬ ¦¨å©˜«œ £œ «¤ §˜¨á£œ«¨¦
-warn, ©œ «˜¡«á ®¨¦¤ ¡á › ˜©«ã£˜«˜ §¨ ¤ «¤ œ¤œ¨š¦§¦å© «¦¬ event. €¬«æ
œå¤˜  ®¨ã© £¦ š ˜ ¤˜ §¨¦œ ›¦§¦ ¦ç£œ «¦¬ª ®¨ã©«œª š ˜ ¡á§¦ ¦ event (æ§àª §®
«¦ shutdown). €¤ «¦ §¨æš¨˜££˜/script «¦¬ event ›œ¤ «¦ ¬§¦©«¨åœ  ˜¬«æ,
œå¤˜  ¡˜¡ã  ›â˜ ¤˜ ˜§˜¤«ã©œ«œ ¡˜«˜­˜« ¡á œ›é.!)[37m

‡â¢œ«œ §¨¦œ ›¦§¦ ã©œ ª; ([33mX[37m š ˜ â¥¦›¦); [0m} T New event: Do you want warnings?


EVNOK {[0;1;32m
!J’¦ event [37m%s[32m ›£ ¦¬¨šãŸ¡œ œ§ «¬®éª. ‹§¦¨œå«œ «é¨˜ ¤˜ §¨¦š¨˜££˜«å©œ«œ
§æ«œ Ÿ˜ œ¤œ¨š¦§¦ œå«˜ , £œ «¤ œ¤«¦¢ã [33mA[37m.!)
[0;1m} T New event created successfully


CANCEL {[0;1;31m
† › ˜› ¡˜©å˜ ˜¡¬¨éŸ¡œ.[0;1m
} T Cancelling...


EVDWARN {[0;1;31;5m
ÛÛ  [0;1;31m‘•†: !J!14i‘¡¦§œçœ«œ ¤˜ [37m¡˜«˜¨šã©œ«œ[31m â¤˜ event.
€¬«æ ©£˜å¤œ  æ«  «¦ event ›œ¤ Ÿ˜ £§¦¨œå ¤˜ ¥˜¤˜®¨© £¦§¦ Ÿœå £â®¨  ¤˜ «¦
¥˜¤˜›£ ¦¬¨šã©œ«œ, §¨áš£˜ §¦¬ £§¦¨œå ¤˜ ¡á¤œ  £ á ©«¤ ™á©. [37m‹†Œ[31m
› ˜š¨á­œ«œ events æ§àª «¦ cleanup ¡˜  «¦ shutdown, œå¤˜ 
[37m€€€ˆ’†’€[31m š ˜ ¤˜ ¢œ «¦¬¨šã©œ   ™á©. ƒœ¤ ®¨œ áœ«˜  ¤˜ «¦
¥˜¤˜§é, ˜¤ ›œ¤ ¥â¨œ«œ ˜¡¨ ™éª «  ¡á¤œ«œ, §˜«ã©«œ X «é¨˜.!)
!0l[0;1m} T Delete event: Warning


EVDASK {[0;1m
 !W¦ ¦ event Ÿâ¢œ«œ ¤˜ ¡˜«˜¨šã©œ«œ; ([33m?[37m š ˜ ¡˜«á¢¦š¦,
[33mX[37m š ˜ â¥¦›¦):!) [0m} T Delete event: Which one?


EVDNEXS {[0;1;31m
€¬«æ «¦ event ›œ¤ ¬§á¨®œ . ƒé©«œ [33m?[31m š ˜ ¡˜«á¢¦š¦.
[0;1m} T Delete event: Unknown event name


EVDCONF {[0;1;31m
!W˜¨˜¡˜¢é œ§ ™œ™˜ é©«œ æ«  Ÿâ¢œ«œ ¤˜ [37m¡˜«˜¨šã©œ«œ[31m ˜¬«æ «¦ event.
ƒœ¤ Ÿ˜ ¬§á¨¥œ  á¢¢ §¨¦œ ›¦§¦å©, ¡˜  «¦ event ›œ¤ Ÿ˜ £§¦¨œå ¤˜ ˜¤˜¡«Ÿœå
£œ ¡˜¤â¤˜ «¨æ§¦.!)

[37m‘åš¦¬¨˜ Ÿâ¢œ«œ ¤˜ ¡˜«˜¨šŸœå «¦ event; ([[33mY[37m]yes=¤˜  / [[33mN[37m]o=æ® ): [0m} T Delete event: Confirm deletion


EVDOK {[0;1m
‰˜¢éª, «¦ event %s ¡˜«˜¨šãŸ¡œ.
} T Delete event: Event deleted


EVPHDR {[0;1;32m
                  ‰˜«á¢¦š¦ª ¬§˜¨®æ¤«à¤ events

ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
³ ¤¦£˜ event     ³ œ¨ š¨˜­ã                                ³
ÃÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ´
} T List event prototypes: header


EVPTAB {[0;1;32m³ [37m%-15s [32m³ [37m%-40s[32m ³
} T List event prototypes: table line


EVPFTR {[0;1;32mÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
[0;1;32m} T List event prototypes: footer


EVANAM {[0;1m
!W˜¨˜¡˜¢é ›é©«œ «¦ æ¤¦£˜ «¦¬ event §¦¬ Ÿâ¢œ«œ ¤˜ §¨¦š¨˜££˜«å©œ«œ ([33m?[37m š ˜ ¡˜«á¢¦š¦,
[33mX[37m š ˜ â¥¦›¦):!) [0m} T Schedule event: What event?


EVANEX {[0;1;31m
ƒœ¤ ¬§á¨®œ  «â«¦ ¦ event. ƒé©«œ [33m?[31m š ˜ ¡˜«á¢¦š¦.
[0;1m} T Schedule event: Unknown event name


EVAUNI {[0;1;31m
!JŠ¬§á£˜ , ˜¢¢á  œ¡«â¢œ© «¦¬ event [33m%s[31m â®œ  ã› §¨¦š¨˜££˜« ©«œå,
¡˜  ›œ¤ £§¦¨œå ¤˜ ¬§á¨®œ  §á¤à ˜§æ â¤˜ œ¤œ¨šæ event ˜¬«¦ç «¦¬ œå›¦¬ª.!)
[0;1m} T Schedule event: Can't schedule more than one unique event


EVAWHH {[0;1;32m
!Jæ«œ Ÿâ¢œ«œ ¤˜ œ¡«œ¢œ©«œå «¦ event; “§á¨®¦¬¤ «¨œ ª «¨æ§¦  ¤˜ «¦ ¦¨å©œ«œ
˜¬«æ:!)

!2i!Jƒå¤¦¤«˜ª [37mHH:MM[32m ¦¨åœ«œ «¤ ˜¡¨ ™ã é¨˜ œ¡«â¢œ©ª «¦¬ event (¦ 
é¨œª œå¤˜  ©«¦ › á©«£˜ 0-23).!)
!0l
!2i!Jƒå¤¦¤«˜ª â¤˜¤ ˜¨ Ÿ£æ (§® [37m60[32m) ¦¨åœ«œ ©œ §æ©˜ ¢œ§«á ˜§æ
«é¨˜ Ÿ˜ œ¡«œ¢œ©«œå «¦ event.!)
!0l
!2i!J‹œ [37mNOW[32m, «¦ event Ÿ˜ œ¤œ¨š¦§¦ Ÿœå ˜£â©àª.!)
!0l
!2i!J’â¢¦ª, £œ [37mASAP[32m, ¦  á›œ œª š¨˜££âª šå¤¦¤«˜  BUSY-OUT,
¡˜  «¦ event ¥œ¡ ¤áœ  æ«˜¤ ˜§¦©¬¤›œŸœå ¡˜  ¦ «œ¢œ¬«˜å¦ª ®¨ã©«ª. [31m‹†Œ
€ˆ…„’„ ‹„ €“’† ’†Œ „ˆŠ‚† •—ˆ‘ Š‚: ˆ ‚€‹‹„‘ [37mƒ„Œ[31m „ˆ‘’„”“Œ ‘’†Œ
€•ˆ‰† ’“‘ ‰€’€‘’€‘† ‹„’€ ’ ’„Š‘ ’“ EVENT. ’ ASAP „ˆŒ€ˆ ‰“ˆ—‘ ‚ˆ€
SHUTDOWN.!)
!0l[0;1m} T Schedule event: Help


EVAWHN {[0;1m
!Wæ«œ Ÿâ¢œ«œ ¤˜ œ¡«œ¢œ©«œå «¦ event; ([33mhh:mm[37m, [33mxx[37m,
[33mNOW[37m, [33mASAP[37m, [33m?[37m š ˜ ™¦ãŸœ ˜, ã [33mX[37m š ˜ â¥¦›¦):!) [0m} T Schedule event: When?


EVAWARN {[0;1;31;5m
ÛÛ  [0;1;31m‘•†: !J!14i‘¡¦§œçœ«œ ¤˜
§¨¦š¨˜££˜«å©œ«œ â¤˜ event š ˜ œ¡«â¢œ© [37mNOW[31m. €¤ ˜¬«æ «¦ event
¡˜«˜¢ãšœ  ©œ shutdown «ª ™á©ª,  ™á© Ÿ˜ £§¦¨œå ¤˜ ˜¤â™œ  ‹Œ ˜§æ «¤
¡¦¤©æ¢˜.!)
!0l[0;1m
‘åš¦¬¨˜ Ÿâ¢œ«œ ¤˜ §¨¦š¨˜££˜«å©œ«œ «¦ event; ([[33mY[37m]yes=¤˜  / [[33mN[37m]o=æ® ) [0m} T Schedule event: Final warning



EVAWHE {[0;1;31m
‹ ˜§¦›œ¡«æª ®¨æ¤¦ª œ¡«â¢œ©ª. ˜¤˜›¦¡ £á©«œ.
[0;1m} T Schedule event: Invalid time specification


EVA2MN {[0;1;31m
!Jƒœ¤ £§¦¨œå«œ ¤˜ â®œ«œ §á¤à ˜§æ 100 œ¤œ¨šá %s events. €¡ç¨à© «ª
› ˜› ¡˜©å˜ª. € ¤˜ , ¡˜  æ§¦ ¦ª ¡¨œ«å¤¦ª §¨¦š¨˜££á« ©œ 100 å› ˜ events, ¤˜
€„ˆ Œ€ ’€ ‘”€„ˆ ‹„ ’ •„ˆ. ‹“€‚‰€.!)
[0;1m} T Schedule event: Too many events of that type scheduled


EVADD1 {[0;1;32m
!W’¦ event [37m%s[32m §¨¦š¨˜££˜«å©«¡œ œ§ «¬®éª š ˜ « ª
[37m%02d:%02d[32m.!)
[0;1m} T Schedule event: Event scheduled (to be run once)


EVADD2 {[0;1;32m
!W’¦ event [37m%s[32m §¨¦š¨˜££˜«å©«¡œ œ§ «¬®éª. ‡˜ œ¡«œ¢œå«˜  ¡˜Ÿ£œ¨ ¤á
©« ª [37m%02d:%02d[32m!).
[0;1m} T Schedule event: Event scheduled (to be run daily)


EVADD3 {[0;1;32m
!W’¦ event [37m%s[32m §¨¦š¨˜££˜«å©«¡œ œ§ «¬®éª. ‡˜ œ¡«œ¢œ©«œå æ«˜¤
˜§¦©¬¤›œŸ¦ç¤ æ¢¦  ¦  ®¨ã©«œª ˜§æ «¤ ™á©.!)
[0;1m} T Schedule event: Event scheduled (to be run ASAP)


EVADD4 {[0;1;32m
!W’¦ event [37m%s[32m §¨¦š¨˜££˜«å©«¡œ š ˜ á£œ© œ¡«â¢œ©.!)
[0;1m} T Schedule event: Event scheduled (to be run NOW)


EVLHDR {[0;1;32m

                     ‰˜«á¢¦š¦ª §¨¦š¨˜££˜« ©£â¤à¤ events

ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄ¿
³ ¤¦£˜            ³  —¨˜  ³ œ¨ š¨˜­ã                         ³ ‰˜Ÿ£œ¨ ¤á ³
ÃÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÂÄÄÄÄÄ´
} T List events: List header


EVLTAB {[0;1;32m³ [37m%-16s [32m³ [37m%-5s [32m³ [37m%-40s [32m³ [37m%-3s [32m³
} T List events: List line


EVLFTR {[0;1;32mÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÙ
[0;1m} T List events: List footer


EVLASAP {ASAP} T List events: ASAP string


EVLNO {® } T List events: NO string


EVLYES {Œ˜ } T List events: YES string


EVCNAM {[0;1m
!W˜¨˜¡˜¢é ›é©«œ «¦ §¢ã¨œª æ¤¦£˜ (§® shutdown-00) «¦¬ event
§¦¬ Ÿâ¢œ«œ ¤˜ ˜¡¬¨é©œ«œ ([33m?[37m š ˜ ¡˜«á¢¦š¦,
[33mX[37m š ˜ â¥¦›¦):!) [0m} T Cancel event: What event?


EVCNEX {[0;1;31m
ƒœ¤ ¬§á¨®œ  «â«¦ ¦ event. ƒé©«œ [33m?[31m š ˜ ¡˜«á¢¦š¦.
[0;1m} T Cancel event: Unknown event name


EVCWARN {[0;1;31;5m
ÛÛ  [0;1;31m‘•†: !J!14i…«ã©˜«œ ¤˜ › ˜š¨á¯œ«œ «¦ event [37m%s[31m.
€¤ ˜§˜¤«ã©œ«œ ¡˜«˜­˜« ¡á ©«¤ §˜¨˜¡á«à œ¨é«©, «¦ event Ÿ˜ £˜«˜ àŸœå. €¤
œ¡«œ¢œå«˜  ¡˜Ÿ£œ¨ ¤á, ƒ„Œ Ÿ˜ ¥˜¤˜œ¡«œ¢œ©«œå §¦«â, œ¡«æª ¡  ˜¤ «¦
¥˜¤˜§¨¦š¨˜££˜«å©œ«œ. €¤, ›¢˜›ã, ©­á¥œ«œ «¦ cleanup,  ™á© Ÿ˜ £œå¤œ  ®à¨åª
cleanup £â®¨  ¤˜ «¦ ˜¤˜¡˜¢ç¯œ  ¡á§¦ ¦ª ¡˜  ¤˜ «¦ ¥˜¤˜§¨¦š¨˜££˜«å©œ . §¦ ¦ª
Ÿâ¢œ  ¤˜ §˜å¥œ , ¤˜ §˜å¥œ  £œ ¡á«  á¢¢¦. €¬«á œ›é œå¤˜  œ§ ¡å¤›¬¤˜.
‰˜  ©¦™˜¨¦¢¦šé, œ;!)
!0l[0;1m} T Cancel event: Warning


EVCASK {[0;1m
˜¨˜¡˜¢é œ§ ™œ™˜ é©«œ «¤ œ§'˜æ¨ ©«¦¤ £˜«˜åà© «¦¬ event: ([[33mY[37m]yes=¤˜  / [[33mN[37m]o=æ® ): [0m} T Cancel event: Yes or no?


EVCAN  {[0;1;32m
‰˜¢éª, «¦ event [37m%s[32m £˜«˜ éŸ¡œ œ§'˜æ¨ ©«¦¤.
[0;1m} T Cancel event: Success



LANG {}

NOENTRY {[0;1;31m
Sorry, you don't have access to this area.
[0;1m} T You don't have access to this module


MENU {[2J[0m[47;1;37m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;30;47m¿ [40m
[47;1;37m ³  [0;47;30mEvent Manager 0.5     [0;47;30m³ [40m
[47;1;37m ³  [0;47;30mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ  [0;47;30m³ [40m
[47;1;37m ³  [0;31;47mS[30mhutdown BBS          [30m³ [40m
[47;1;37m ³  [0;31;47mU[30mndo shutdown         [30m³ [40m
[47;1;37m ³                        [0;47;30m³ [40m
[47;1;37m ³  [0;31;47mL[30mist events           [30m³ [40m
[47;1;37m ³  [0;31;47mA[30mdd (schedule) event  [30m³ [40m
[47;1;37m ³  [0;31;47mC[30mancel event          [30m³ [40m
[47;1;37m ³                        [0;47;30m³ [40m
[47;1;37m ³ [0;30;47me[31mX[30mit                   [30m³ [40m
[47;1;37m À[0;30;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0;1m

[32mEvent Manager[37m
Please enter your choice: [0m} T Main menu, normal version


SHMENU {[0;1;32m
Event Manager[37m
!WEnter your choice ([33mS[37m,[33mU[37m,[33mL[37m,[33mA[37m,[33mC[37m,[33mX[37m
to exit, or [33m?[37m for the menu): !)[0m} T Short menu, normal version


PMENU {[2J[0m[47;1;37m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;30;47m¿ [40m
[47;1;37m ³  [0;47;30mEvent Manager 0.5     [0;47;30m³ [40m
[47;1;37m ³  [0;47;30mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ  [0;47;30m³ [40m
[47;1;37m ³  [0;31;47mS[30mhutdown BBS          [30m³ [40m
[47;1;37m ³  [0;31;47mU[30mndo shutdown         [30m³ [40m
[47;1;37m ³                        [0;47;30m³ [40m
[47;1;37m ³  [0;31;47mL[30mist events           [30m³ [40m
[47;1;37m ³  [0;31;47mA[30mdd (schedule) event  [30m³ [40m
[47;1;37m ³  [0;31;47mC[30mancel event          [30m³ [40m
[47;1;37m ³                        [0;47;30m³ [40m
[47;1;37m ³  [0;31;47mN[30mew event             [30m³ [40m
[47;1;37m ³  [0;31;47mD[30melete event          [30m³ [40m
[47;1;37m ³                        [0;47;30m³ [40m
[47;1;37m ³ [0;30;47me[31mX[30mit                   [30m³ [40m
[47;1;37m À[0;30;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0;1m

[32mEvent Manager[37m
Please enter your choice: [0m} T Main menu, privileged version


SHPMENU {[0;1;32m
Event Manager[37m
!WEnter your choice ([33mS[37m,[33mU[37m,[33mL[37m,[33mA[37m,[33mC[37m,[33mN[37m,[33mD[37m,[33mX[37m to exit, or [33m?[37m for the menu): !)[0m} T Short menu, privileged version


ERRSEL {[0;1;31m
Sorry, that is not an available option at this stage.
[0;1m} T Invalid option


LEAVE {[0;1m
Leaving the event manager.
} T Leaving the event manager


EVNNAME {[0;1;32m
!JTo begin with, you need to give a short name (up to 13 characters) to
the new event. The name can only contain letters and numbers. Typical names
are "shutdown", "cleanup", etc.!)[37m

                                             ÃÄÄÄÄÄÄÄÄÄÄÄ´
Enter the name of the new event ([33mX[37m to exit): [0m} T New event: Asking for event name


EVNALRX {[0;1;31m
An event by that name already exists.
[0;1m} T New event: Event name already exists


EVNCHR {[0;1;31m
The name contains unacceptable characters.
[0;1m} T New event: Event name contains invalid characters


EVNDESC {[0;1;32m
!JYou must now provide a brief description of this event, up to 40
characters in length. Make it easy to understand and self-explanatory,
in case the name doesn't manage to convey the nature of the event. The
description may contain any characters you like, of course.!)[37m

                                   ÃÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ´
Enter the description ([33mX[37m to exit): [0m} T New event: Asking for event description


EVNPROG {[0;1;32m
!JEnter the UNIX command this event will execute. Specify the full path
of the binary. Obviously, if you don't know what you're doing, don't do
it here!!)[37m

Event command line ([33mX[37m š ˜ â¥¦›¦): [0m} T New event: Asking for event command


EVNONCE {[0;1;32m
!JThe following three (and last) questions will determine the nature
of the new event.!)

!JDo you want the event to stay scheduled after it's executed? Answering
yes here will make an event execute every day at the specified time.
Answering no will make it an one-off event that you'll need to schedule
every time you want it executed. Maintenance and
cleanup-type events are examples of events for which you should answer yes.
Something like a BBS shutdown should not normally be regular, so you would
say no.!)[37m

Execute this event every day ([33mX[37m to exit)? [0m} T New event: Running once/daily?


EVNUNIQ {[0;1;32m
!JSome events need to be scheduled multiple times in a day.
For instance, two shutdown events scheduled for the same time could
wreak havoc. Answer yes if the event belongs to this category.!)[37m

!WAllow only one event of this type to be scheduled at any one time
([33mX[37m to exit)?!) [0m} T New event: Unique event?


EVNWARN {[0;1;32m
!JDo you want users to be warned of the execution of this event?
The event will be asked to warn users at regular intervals before it's
finally executed. This must be supported by the event executable.
If it's not, it's probably a bad idea to say yes here.!)[37m

Issue warnings to users ([33mX[37m to exit)? [0m} T New event: Do you want warnings?


EVNOK {[0;1;32m
!JEvent [37m%s[32m was created successfully.
You can use the [33mA[37m command to schedule it if you wish.!)
[0;1m} T New event created successfully


CANCEL {[0;1;31m
Aborted.[0;1m
} T Cancelling...


EVDWARN {[0;1;31;5m
ÛÛ  [0;1;31mCAUTION: !J!14iYou're about to permanently [37mdelete[31m an
event type. You should not remove certain event types (such as cleanup and
shutdown) because they're not easy to recreate. If you don't know what you're
doing, press [33mX[37m now.!)
!0l[0;1m} T Delete event: Warning


EVDASK {[0;1m
!WWhat event would you like to delete ([33m?[37m for a list,
[33mX[37m to exit)?!) [0m} T Delete event: Which one?


EVDNEXS {[0;1;31m
There is no event by that name. Enter [33m?[31m for a list.
[0;1m} T Delete event: Unknown event name


EVDCONF {[0;1;31m
!WPlease confirm that you want to [37mdelete[31m this event type.
This is your last chance to quit, and you cannot undelete the event type
once it's gone.!)

[37mAre you sure you want to delete this event ([[33mY[37m]yes / [[33mN[37m]o)? [0m} T Delete event: Confirm deletion


EVDOK {[0;1m
OK, event [32m%s[37m was deleted.
} T Delete event: Event deleted


EVPHDR {[0;1;32m
List of existing events

ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
³ Event name      ³ Description                              ³
ÃÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ´
} T List event prototypes: header


EVPTAB {[0;1;32m³ [37m%-15s [32m³ [37m%-40s[32m ³
} T List event prototypes: table line


EVPFTR {[0;1;32mÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
[0;1;32m} T List event prototypes: footer


EVANAM {[0;1m
!WPlease enter the name of the event to schedule ([33m?[37m for a list,
[33mX[37m to exit):!) [0m} T Schedule event: What event?


EVANEX {[0;1;31m
Ther is no such event. Enter [33m?[31m for a list of events.
[0;1m} T Schedule event: Unknown event name


EVAUNI {[0;1;31m
!JSorry, but event [33m%s[31m is already scheduled and you
can't have more than one scheduled event of this type.!)
[0;1m} T Schedule event: Can't schedule more than one unique event


EVAWHH {[0;1;32m
!JWhen should the event be executed? There are three ways to set the
execution time:!)

!2i!JEnter [37mHH:MM[32m to set the exact time (in 24 hour format, with HH in the range 0-23).!)
!0l
!2i!JEnter a number (e.g. [37m60[32m) to execute the event in that many minutes from now.!)
!0l
!2i!JEnter [37mNOW[32m to execute the event immediately.!)
!0l
!2i!JFinally, with [37mASAP[32m, unused lines are changed to the BUSY-OUT state.
Users are notified of the event having been scheduled. When they logout, their lines
also drop to the BUSY-OUT state. When all users have logged out, the event is
executed. [31mDON'T USE THIS UNLESS YOU KNOW WHAT YOU'RE DOING: LINES [37mDO NOT[31m
REVERT TO THEIR ORIGINAL STATE AFTER THE EVENT IS EXECUTED, EFFECTIVELY LOCKING EVERYONE OUTE.
ASAP IS MOSTLY USED TO SHUTDOWN THE SYSTEM NICELY.!)
!0l[0;1m} T Schedule event: Help


EVAWHN {[0;1m
!WWhen would you like to execute this event? ([33mhh:mm[37m, [33mxx[37m,
[33mNOW[37m, [33mASAP[37m, [33m?[37m for help, or [33mX[37m to exit):!) [0m} T Schedule event: When?


EVAWARN {[0;1;31;5m
ÛÛ  [0;1;31mCAUTION: !J!14iYou're about to
schedule an event to be executed [37mNOW[31m.
If this event shuts down the BBS or otherwise changes line states,
you might only be able to restart it from the system console (or a remote login
to an underlying UNIX account, if you have one).!)
!0l[0;1m
Are you sure? ([[33mY[37m]yes / [[33mN[37m]o) [0m} T Schedule event: Final warning



EVAWHE {[0;1;31m
Invalid schedule time. Please try again.
[0;1m} T Schedule event: Invalid time specification


EVA2MN {[0;1;31m
!JYou can't have more than 100 scheduled %s type events. Aborting.!)
[0;1m} T Schedule event: Too many events of that type scheduled


EVADD1 {[0;1;32m
!WEvent [37m%s[32m scheduled to run at [37m%02d:%02d[32m.!)
[0;1m} T Schedule event: Event scheduled (to be run once)


EVADD2 {[0;1;32m
!WEvent [37m%s[32m scheduled to be executed daily at [37m%02d:%02d[32m!).
[0;1m} T Schedule event: Event scheduled (to be run daily)


EVADD3 {[0;1;32m
!WEvent [37m%s[32m scheduled to be executed ASAP (i.e. when all
users have disconnected).!)
[0;1m} T Schedule event: Event scheduled (to be run ASAP)


EVADD4 {[0;1;32m
!WEvent [37m%s[32m scheduled to be executed immediately.!)
[0;1m} T Schedule event: Event scheduled (to be run NOW)


EVLHDR {[0;1;32m

                          List of scheduled events

ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄ¿
³ Event name       ³ Time  ³ Description                            ³ Daily ³
ÃÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÂÄÄÄÄ´
} T List events: List header


EVLTAB {[0;1;32m³ [37m%-16s [32m³ [37m%-5s [32m³ [37m%-40s [32m³ [37m%-3s [32m³
} T List events: List line


EVLFTR {[0;1;32mÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄÙ
[0;1m} T List events: List footer


EVLASAP {ASAP} T List events: ASAP string


EVLNO {No} T List events: NO string


EVLYES {Yes} T List events: YES string


EVCNAM {[0;1m
!WEnter the full name of the event instance (e.g. shutdown-00) to cancel
([33m?[37m for a list, [33mX[37m to exit):!) [0m} T Cancel event: What event?


EVCNEX {[0;1;31m
There is no such event. Enter [33m?[31m for a list.
[0;1m} T Cancel event: Unknown event name


EVCWARN {[0;1;31;5m
ÛÛ  [0;1;31mCAUTION: !J!14iYou are about to cancel event instance [37m%s[31m.
If you answer yes, execution of this event will be cancelled. If the event is
executed regularly, it will NOT be executed again, unless you re-schedule it.!)
!0l[0;1m} T Cancel event: Warning


EVCASK {[0;1m
Please confirm cancelation of this event instance ([[33mY[37m]yes / [[33mN[37m]o): [0m} T Cancel event: Yes or no?


EVCAN  {[0;1;32m
OK, event instance [37m%s[32m was cancelled.
[0;1m} T Cancel event: Success



LANGEND {}