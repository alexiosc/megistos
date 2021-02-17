LEVEL2 {}

USRLRM {User selection timeout (minutes, 0=disable): 3} N 0 60

QRYLRM {Network timeout while requesting info (seconds, 0=disable): 7} N 0 3600

HOSTS {gate} S 256 Hosts to contact:

LOCAL {Show the local system along with remote ones? YES} B




LEVEL3 {}

BEGIN {[2J[0;1m!J‰˜¢à©ã¢Ÿ˜«œ ©«¦ ¬§¦©ç©«£˜ › ¡«çà©ª ™á©œà¤
(MetaBBS). ‹ ©æ ¢œ§«æ §˜¨˜¡˜¢é, ˜§¦©«â¢¦¬£œ ˜ «ã©œ ª ©«¦ ›å¡«¬¦...!)
[0;1m} T Welcome, please wait: sendind requests


LOOKUP {[0;1;32m
„¨œ¬¤˜ š ˜ «¦¤ server [37m%s[32m...
} T Looking up host


DNSFAIL {[31m  ‘¬šš¤é£, ˜§¦«¬®å˜ â¨œ¬¤˜ª.
[0;1m} T Host lookup failed.


SENDREQ {  €§¦©«¦¢ã ˜å«©ª š ˜ §¢¨¦­¦¨åœª...
  €¤˜£¦¤ã ˜§á¤«©ª... } T Request sent, waiting for response


SENDOK {[37m
  „¤«á¥œ , «â¢¦ª œ§ ¡¦ ¤à¤å˜ª.
[0;1m} T Ok, received info packages from server


SENDERR {[31m  €§¦«¬®å˜, «¦ç£œ ©¬šš¤é£.
[0;1m} T Error while getting info


NOSYS {[0;1m
ƒ¬©«¬®éª ›œ¤ ™¨âŸ¡œ ¡˜¤â¤˜ › ˜Ÿâ© £¦ ©ç©«£˜. „§ ©«¨¦­ã ©«¤ @BBS@.
[0;1m} T No systems found


SYSCOUNT1 {[0;1m
[0;1;32m¨âŸ¡œ [37mâ¤˜[32m › ˜Ÿâ© £¦ ©ç©«£˜.

[0;1m} T Number of systems available (singular)


SYSCOUNT {[0;1m
[0;1;32m„¬¨âŸ©˜¤ [37m%d[32m › ˜Ÿâ© £˜ ©¬©«ã£˜«˜.

[0;1m} T Number of systems available (plural)


WARNTIME {[0;1;33m
[5mÛÛ[0;1;33m ¨¦œ ›¦§¦å©: â®œ«œ [37m%d %s[33m ¤˜ ¡á¤œ«œ «¤ œ§ ¢¦šã ©˜ª.

[0;1m} T Warning about timeout


MINSNG {¢œ§«æ} T Minutes, singular form
MINPLR {¢œ§«á} T Minutes, plural form


KICKOUT {[0;1;31m
!J‘¬šš¤é£,  ©ç¤›œ©ã ©˜ª â£œ ¤œ ˜¤˜¤œ¨šã š ˜ §œ¨ ©©æ«œ¨¦ ®¨æ¤¦ ˜§'æ« 
£§¦¨¦ç£œ ¤˜ œ§ «¨â¯¦¬£œ. ˜¨˜¡˜¢¦ç£œ ¥˜¤˜¡˜¢â©«œ æ«˜¤ ˜§¦­˜©å©œ«œ £œ §¦ ¦
©ç©«£˜ Ÿâ¢œ«œ ¤˜ ©¬¤›œŸœå«œ. …«¦ç£œ ©¬šš¤é£ š ˜ «¤ «˜¢˜ §à¨å˜.!)
[0m


} T Timeout kickout warning.



SYSTBLH {[0;1;33m
## [32m¤¦£˜ ©¬©«ã£˜«¦ª                    [37m‘¬¤›œ›œ£â¤¦  ®¨ã©«œª  „¢œçŸœ¨œª š¨˜££âª
!FÄ
[0;1m} T System table header


SYSTBLL {[0;1;33m%2d [32m%-51.51s  [37m%3d  %3d
} T System table entry


SYSTBLN {[0;1;33m%2d [32m%-51.51s [37m [áš¤à©«¦]
} T System table entry (non-Megistos system)


SYSTBLF {[0;1m!FÄ
[0;1m} T System table footer


SYSMNU {[0;1m
!Wƒé©«œ â¤˜¤ ˜¨ Ÿ£æ [33m1[33m-[33m%d[37m, [33mI1[37m-[33mI%d[37m
š ˜ §¢¨¦­¦¨åœª š ˜ «¦ ˜¤«å©«¦ ®¦ ©ç©«£˜, [33mR[37m š ˜ ˜¤˜¤âà© ¡˜«˜¢æš¦¬,
[33mX[37m š ˜ œ§ ©«¨¦­ã ©«¤ @BBS@, ã [33m?[37m š ˜ «¦¤ ¡˜«á¢¦š¦ ©¬©«£á«à¤:!) [0m} T Menu prompt


ERROPT {[0;1;31m
Š¬§á£˜ ,  œ¤«¦¢ã ©˜ª ›œ¤ âš ¤œ ¡˜«˜¢§«ã. ˜¤˜§¨¦©§˜Ÿã©«œ.
[0;1m} T Invalid selection from the menu


BBSINFO {[0;36m
ÛÛ  [1m¢¨¦­¦¨åœª š ˜ «¦ ©ç©«£˜ %d  [0;46m[K[0;1m

¤¦£˜ . . . . . . . [32m%s[37m
‰à› ¡æª  . . . . .  [32m%s[37m
ˆ› ¦¡«ã«ª  . . . . [32m%s[37m
ƒ œçŸ¬¤©  . . . .  !W!i[32m%s%s%s%s%s[37m!)
!0l’¢. data . . . . . [32m%s[37m
’¢. voice . . . .  [32m%s[37m
Email . . . . . . . [32m%-51.51s[37m
Home page  . . . .  [32m%-51.51s[37m
•¨ã©«œª . . . . . . [32m%d[37m ©¬¤›œ›œ£â¤¦ , telnet š¨˜££âª œ¢œçŸœ¨œª: [32m%d[37m ˜§æ [32m%d[37m.
Internet æ¤¦£˜ . .  [32m%s[37m, port [32m%d[37m.

[0;46m[K
[0;1m} T System information, part 1 (identity and contact information)


BBSINFN {[0;36m
ÛÛ  [1m¢¨¦­¦¨åœª š ˜ «¦ ©ç©«£˜ %d  [0;46m[K[0;1m

€¬«æ «¦ ©ç©«£˜ ›œ¤ «¨â®œ  ‹âš ©«¦.

¤¦£˜ . . . . . . . [32m%s[37m
‰à› ¡æª  . . . . .  [32m%s[37m
ˆ› ¦¡«ã«ª  . . . . [32m%s[37m
ƒ œçŸ¬¤©  . . . .  !W!i[32m%s%s%s%s%s[37m!)
!0l’¢. data . . . . . [32m%s[37m
’¢. voice . . . .  [32m%s[37m
Email . . . . . . . [32m%-51.51s[37m
Home page  . . . .  [32m%-51.51s[37m
•¨ã©«œª . . . . . . €š¤à©«¦: «¦ ©ç©«£˜ ›œ¤ ©¬¤œ¨šáœ«˜  £œ «¦ MetaBBS.
Internet æ¤¦£˜ . .  [32m%s[37m, port [32m%d[37m.

[0;46m[K
[0;1m} T System information, part 1 (for non-Megistos systems)


BBSAD {[0;1m
ƒ ˜­£ ©« ¡æ ¡œå£œ¤¦ ™á©ª:[0m

%s

[0;1m} T System information, system advertisement



RUNTEL {[0;1;32m
‰˜¢éª, ©˜ª ©¬¤›â¦¬£œ £â©à telnet...


[0m[2J} T Connecting to remote system
