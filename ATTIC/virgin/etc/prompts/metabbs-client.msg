LEVEL2 {}

USRLRM {User selection timeout (minutes, 0=disable): 3} N 0 60

QRYLRM {Network timeout while requesting info (seconds, 0=disable): 7} N 0 3600

HOSTS {gate} S 256 Hosts to contact:

LOCAL {Show the local system along with remote ones? YES} B




LEVEL3 {}

BEGIN {[2J[0;1m!J¢à©ã¢« ©«¦ ¬§¦©ç©«£  ¡«çà©ª á©à¤
(MetaBBS).  ©æ ¢§«æ §¨¡¢é, §¦©«â¢¦¬£  «ã© ª ©«¦ å¡«¬¦...!)
[0;1m} T Welcome, please wait: sendind requests


LOOKUP {[0;1;32m
¨¬¤   «¦¤ server [37m%s[32m...
} T Looking up host


DNSFAIL {[31m  ¬¤é£, §¦«¬®å â¨¬¤ª.
[0;1m} T Host lookup failed.


SENDREQ {  §¦©«¦¢ã å«©ª   §¢¨¦­¦¨åª...
  ¤£¦¤ã §á¤«©ª... } T Request sent, waiting for response


SENDOK {[37m
  ¤«á¥ , «â¢¦ª § ¡¦ ¤à¤åª.
[0;1m} T Ok, received info packages from server


SENDERR {[31m  §¦«¬®å, «¦ç£ ©¬¤é£.
[0;1m} T Error while getting info


NOSYS {[0;1m
¬©«¬®éª ¤ ¨â¡ ¡¤â¤  â© £¦ ©ç©«£. § ©«¨¦­ã ©«¤ @BBS@.
[0;1m} T No systems found


SYSCOUNT1 {[0;1m
[0;1;32m¨â¡ [37mâ¤[32m  â© £¦ ©ç©«£.

[0;1m} T Number of systems available (singular)


SYSCOUNT {[0;1m
[0;1;32m¬¨â©¤ [37m%d[32m  â© £ ©¬©«ã£«.

[0;1m} T Number of systems available (plural)


WARNTIME {[0;1;33m
[5mÛÛ[0;1;33m ¨¦ ¦§¦å©: â®« [37m%d %s[33m ¤ ¡á¤« «¤ § ¢¦ã ©ª.

[0;1m} T Warning about timeout


MINSNG {¢§«æ} T Minutes, singular form
MINPLR {¢§«á} T Minutes, plural form


KICKOUT {[0;1;31m
!J¬¤é£,  ©ç¤©ã ©ª â£ ¤ ¤¤¨ã   §¨ ©©æ«¨¦ ®¨æ¤¦ §'æ« 
£§¦¨¦ç£ ¤ § «¨â¯¦¬£. ¨¡¢¦ç£ ¥¤¡¢â©« æ«¤ §¦­©å©« £ §¦ ¦
©ç©«£ â¢« ¤ ©¬¤å«. «¦ç£ ©¬¤é£   «¤ «¢ §à¨å.!)
[0m


} T Timeout kickout warning.



SYSTBLH {[0;1;33m
## [32m¤¦£ ©¬©«ã£«¦ª                    [37m¬¤£â¤¦  ®¨ã©«ª  ¢ç¨ª ¨££âª
!FÄ
[0;1m} T System table header


SYSTBLL {[0;1;33m%2d [32m%-51.51s  [37m%3d  %3d
} T System table entry


SYSTBLN {[0;1;33m%2d [32m%-51.51s [37m [á¤à©«¦]
} T System table entry (non-Megistos system)


SYSTBLF {[0;1m!FÄ
[0;1m} T System table footer


SYSMNU {[0;1m
!Wé©« â¤¤ ¨ £æ [33m1[33m-[33m%d[37m, [33mI1[37m-[33mI%d[37m
  §¢¨¦­¦¨åª   «¦ ¤«å©«¦ ®¦ ©ç©«£, [33mR[37m   ¤¤âà© ¡«¢æ¦¬,
[33mX[37m   § ©«¨¦­ã ©«¤ @BBS@, ã [33m?[37m   «¦¤ ¡«á¢¦¦ ©¬©«£á«à¤:!) [0m} T Menu prompt


ERROPT {[0;1;31m
¬§á£ ,  ¤«¦¢ã ©ª ¤ â ¤ ¡«¢§«ã. ¤§¨¦©§ã©«.
[0;1m} T Invalid selection from the menu


BBSINFO {[0;36m
ÛÛ  [1m¢¨¦­¦¨åª   «¦ ©ç©«£ %d  [0;46m[K[0;1m

¤¦£ . . . . . . . [32m%s[37m
à ¡æª  . . . . .  [32m%s[37m
 ¦¡«ã«ª  . . . . [32m%s[37m
 ç¬¤©  . . . .  !W!i[32m%s%s%s%s%s[37m!)
!0l¢. data . . . . . [32m%s[37m
¢. voice . . . .  [32m%s[37m
Email . . . . . . . [32m%-51.51s[37m
Home page  . . . .  [32m%-51.51s[37m
¨ã©«ª . . . . . . [32m%d[37m ©¬¤£â¤¦ , telnet ¨££âª ¢ç¨ª: [32m%d[37m §æ [32m%d[37m.
Internet æ¤¦£ . .  [32m%s[37m, port [32m%d[37m.

[0;46m[K
[0;1m} T System information, part 1 (identity and contact information)


BBSINFN {[0;36m
ÛÛ  [1m¢¨¦­¦¨åª   «¦ ©ç©«£ %d  [0;46m[K[0;1m

¬«æ «¦ ©ç©«£ ¤ «¨â®  â ©«¦.

¤¦£ . . . . . . . [32m%s[37m
à ¡æª  . . . . .  [32m%s[37m
 ¦¡«ã«ª  . . . . [32m%s[37m
 ç¬¤©  . . . .  !W!i[32m%s%s%s%s%s[37m!)
!0l¢. data . . . . . [32m%s[37m
¢. voice . . . .  [32m%s[37m
Email . . . . . . . [32m%-51.51s[37m
Home page  . . . .  [32m%-51.51s[37m
¨ã©«ª . . . . . . ¤à©«¦: «¦ ©ç©«£ ¤ ©¬¤¨á«  £ «¦ MetaBBS.
Internet æ¤¦£ . .  [32m%s[37m, port [32m%d[37m.

[0;46m[K
[0;1m} T System information, part 1 (for non-Megistos systems)


BBSAD {[0;1m
 ­£ ©« ¡æ ¡å£¤¦ á©ª:[0m

%s

[0;1m} T System information, system advertisement



RUNTEL {[0;1;32m
¢éª, ©ª ©¬¤â¦¬£ £â©à telnet...


[0m[2J} T Connecting to remote system
