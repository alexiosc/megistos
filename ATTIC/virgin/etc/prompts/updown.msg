LEVEL2 {}


PEFFIC {Average protocol efficiency in percent: 77} N 1 1000


VPRSEL {V} S 8 Viewer "protocol" selection string:


DISSEC {Automatic disconnection countdown (seconds): 10} N 1 32767


LNKKEY {Access key required to use 'link' upload protocol: 128} N 0 129


LNKSEL {F} S 8 Selection string for the 'link' protocol:


REFND {Refund users for failed (partial) transfers? YES} B


REFPER {Percentage of refund given to users? 100} N 0 100


LEVEL3 {}


NOFILES {
[0;1;31mƒœ¤ â®œ«œ ˜¨®œå˜ š ˜ £œ«˜­¦¨á ˜¬«ã «¤ ©« š£ã.
[0;1m} T Error: no files or tags to transfer, exiting


FNOTFND {
[0;1;31mŠ¬§á£˜ , «¦ ˜¨®œå¦ "%s" ›œ¤ ¬§á¨®œ  §¢â¦¤.
} T File not found


MINSNG {æ} T Minutes, singular suffix

MINPLR {á} T Minutes, plural suffix


DNLHDR {[0;1m
[47m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;47;30m¿ [0m
[1;47;37m ³ [0;47;30m€¨®œå¦:  [31m%-16s  %-46s [30m³ [40m
[1;47;37m ³ [0;47;30m‹âšœŸ¦ª: [31m%-8d          [30m•¨æ¤¦ª £œ«˜­¦¨áª (¡˜«á §¨¦©âšš ©): [31m%4d ¢œ§«%s [30m³ [0m
[1;47;37m ³ [0;47;30m’ç§¦ª:   [31m%-64s [30m³ [0m
[1;47;37m ³ [0;47;30mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [30m³ [0m
} T Download header for single files


DNLHDR1 {[0;1m
[47m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;47;30m¿ [0m
[1;47;37m ³ [0;47;30m‘¬¤¦¢ ¡æ ‹âšœŸ¦ª: [31m%-8d [30m•¨æ¤¦ª £œ«˜­¦¨áª (¡˜«á §¨¦©âšš ©): [31m%4d ¢œ§«%s [30m³ [0m
[1;47;37m ³ [0;47;30mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [30m³ [0m
} T Download header for multiple files (no info pane)


PROTLIN1 {[1;47;37m ³ [0;47;34m%-2s[30m%33s ³ } T Protocol Menu Line, First Half


PROTLIN2 {[34m%-2s[30m%33s [30m³ [0m
} T Protocol Menu Line, Seconf Half


DNLFTR {[1;47;37m ³ [0;47;30mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [30m³ [0m
[1;47;37m ³ [0;47;34mT [30m . (tag) † ¢ã¯ Ÿ˜ šå¤œ  ˜¨šæ«œ¨˜ ³ [34mTE[30m . . . . . . . . . . . Tag Editor [30m³ [0m
[1;47;37m ³ [0;47;34mTT[30m  .  Šã¯ «à¤ tagged ˜¨®œåà¤: [31m%3s[30m ³ ¨¦©Ÿâ©«œ [34m![30m š ˜ ˜¬«æ£˜« ˜§¦©ç¤›œ© [30m³ [0m
} T Download footer with tag commands


DNLFTRT {[1;47;37m ³ [0;47;30mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [30m³ [0m
[1;47;37m ³ [0;47;30mT [30m . (tag) † ¢ã¯ Ÿ˜ šå¤œ  ˜¨šæ«œ¨˜ ³ ¨¦©Ÿâ©«œ [34m![30m š ˜ ˜¬«æ£˜« ˜§¦©ç¤›œ© [30m³ [0m
} T Download footer without tag commands


DNLFTRI {[1;47;37m ³ [0;47;30mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [30m³ [0m
[1;47;37m ³ [0;47;30m¨¦ª ¢ã¯ ˜¨®œå˜: [31m%4d[30m      €¨®œå˜ §¦¬ Ÿ˜ ¢­Ÿ¦ç¤ ˜¨šæ«œ¨˜ (tagged): [31m%4d [30m³ [0m
} T Download footer, file information


DNLFTRL {[1;47;37m À[0;47;30mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0m
[0m} T Download footer, last line


YES {Œ˜ } T "Yes" string


NO {® } T "No" string


VIEWNAME {„§ Ÿœé¨© %s ˜¨®œå¦¬} T Name of the viewer "protocol"


FTUNK {(€š¤é©«¦¬ «ç§¦¬ - ¬§ã¨¥œ ¢áŸ¦ª)} T File type detection failed


SHORT {[0;1m
!Wƒé©«œ «¤ œ§ ¢¦šã ©˜ª, ã [33mX[37m š ˜ â¥¦›¦, ã [33m?[37m š ˜ «¦ £œ¤¦ç:!) [0m} T Short menu


ERRSEL {
[0;1;31mŠ¬§á£˜ , ›œ¤ ¬§á¨®œ  œ§ ¢¦šã "%s".
[0;1m} T Oops, no such option


CONFX {[0;1;31m
!W‹˜«˜ é¤¦¤«˜ª « ¢ã¯ §¨¦©à¨ ¤é¤ ˜¨®œåà¤, ®á¤¦¬£œ «˜ ˜¨®œå˜. Œ˜
œš¡˜«˜¢œå¯¦¬£œ « ¢ã¯; ([[33mY[31m]es=¤˜å / [[33mN[31m]o=æ® )!) [0m} T Confirm exit



VIEWWRK {
[s[0;1;36;5m˜¨˜¡˜¢é §œ¨ £â¤œ«œ... } T Preparing file viewer - please wait


VIEWBEG {[u[0;1m[K[0;32mÛÛ  [1mœ¨ œ®æ£œ¤˜ «¦¬ ˜¨®œå¦¬ [37m%s  [42m[K[0;1m

[0;1m} T Viewing archive contents


VIEWEND {
[0;42m[K[0;1m
[0;1m} T Viewing archive contents


CANTAG {[0;1;31m
!J’¦ ˜¨®œå¦ [37m%s[31m œå¤˜  §¨¦©à¨ ¤æ. ¨â§œ  ¤˜ «¦ ¢á™œ«œ «é¨˜, £ ˜ ¡˜ 
›œ¤ œå¤˜  ©åš¦¬¨¦ æ«  Ÿ˜ ¬§á¨®œ  ˜¨šæ«œ¨˜.!)
[0;1m} T Unable to tag transient file


TAGSOMEFIL {[0;1;31m
!Jƒœ¤ ˜¤˜™¢ãŸ¡œ  ¢ã¯ æ¢à¤ «à¤ ˜¨®œåà¤. ’˜
œ¤˜§¦£œå¤˜¤«˜ ˜¨®œå˜ œå¤˜  §¨¦©à¨ ¤á ¡˜  ›œ¤ ¬§á¨®œ  œššç© æ«  Ÿ˜ ¬§á¨®¦¬¤
©« ™á© ˜¨šæ«œ¨˜. ‡˜ §¨â§œ  ¤˜ «˜ ¢á™œ«œ ã ¤˜ ˜¡¬¨é©œ«œ «é¨˜.!) [0;1m} T
Tagged some files, must download the rest


TAGFIL {
[0;1m„¤«á¥œ ,  ¢ã¯ ˜¤˜™á¢¢œ«˜ ...
} T Tagged all files, download postponed


TAGSOM {
!J[0;1m„¤«á¥œ ,  ¢ã¯ «à¤ £ §¨¦©à¨ ¤é¤ ˜¨®œåà¤ ˜¤˜™á¢¢œ«˜ .
‡˜ §¨â§œ  æ£àª ¤˜ ¢á™œ«œ ã ¤˜ £˜«˜ é©œ«œ «˜ §¨¦©à¨ ¤á ˜¨®œå˜.!)
} T Tagged all files, download postponed


SUPLOAD {˜§¦©«¦¢ã} T 'Upload' (used in XFERBEG)

SDNLOAD {¢ã¯} T 'Download'(used in XFERBEG)

SSINGLE {˜¨®œå¦¬} T 'file' (used in XFERBEG)

SMULTI {˜¨®œåà¤} T 'files' (used in XFERBEG)
 

XFERBEG {
[0;1;32m
[5mÛÛ  [0;1;32m„«¦ £¦ª š ˜ [37m%s %s[32m £œ «¦ §¨à«æ¡¦¢¦ [37m%s[32m.
     â©«œ [33m%s[32m £œ¨ ¡âª ­¦¨âª š ˜ ˜¡ç¨à©.[0;1m

} T Transfer begins now


DNLFAIL {

[0;1;31;5mÛÛ  [0;1;31m† ¢ã¯ › ˜¡æ§¡œ.

[32m€¨®œå˜ «à¤ ¦§¦åà¤  ¢ã¯ œ¡¡¨œ£œå: [37m%d
} T Download failed


RETRY {[0;1m
‡â¢œ«œ ¤˜ œ§ ®œ ¨ã©œ«œ «¤ ¢ã¯ á¢¢ £å˜ ­¦¨á; ([[33mY[37m]es=¤˜  / [[33mN[37m]o=æ® ) } T Retry failed download?


TEMENU {
[0;47;1;37m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;30;47m¿ [0m
[47;1;37m ³  [0;47;30mTag Editor                                      [0;47;30m³ [0m
[47;1;37m ³  [0;47;30mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ  [0;47;30m³ [0m
[47;1;37m ³  [0;31;47mL[30mist files . . . . . . . . . ‰˜«á¢¦š¦ª ˜¨®œåà¤  [30m³ [0m
[47;1;37m ³  [0;31;47mT[30mag/untag file . . . . . €¤˜™¦¢ã ¢ã¯ª ˜¨®œå¦¬  [30m³ [0m
[47;1;37m ³  [0;31;47mD[30melete/undelete file .  ‹˜«˜åà© ¢ã¯ª ˜¨®œå¦¬  [30m³ [0m
[47;1;37m ³  [0;31;47mS[30mtatistics . . . . . . . . ‘«˜« ©« ¡á ©«¦ ®œå˜  [30m³ [0m
[47;1;37m ³                                                  [0;47;30m³ [0m
[47;1;37m ³ [0;30;47me[31mX[30mit . . . . . . . . . . . . . . . . . . „¥¦›¦ª  [30m³ [0m
[47;1;37m À[0;30;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0m
} T Tag Editor menu


TESHMNU {[0;1m
!Wƒé©«œ «¤ œ§ ¢¦šã ©˜ª ([33mL[37m,[33mT[37m,[33mD[37m,[33mS[37m,[33mX[37m š ˜ â¥¦›¦, ã [33m?[37m š ˜ «¦ £œ¤¦ç):!) [0m} T Tag Editor Short menu


TEERR {
[0;1;31mŠ¬§á£˜ , ›œ¤ ¬§á¨®œ  œ§ ¢¦šã "%c".
[0;1m} T Tag Editor, no such option


TELHDR {[0;1m
           ‰˜«á¢¦š¦ª æ¢à¤ «à¤ §¨¦ª ¢ã¯ ˜¨®œåà¤:
               ÚÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÄ¿
               ³[33m€¤˜™¦¢ã[37m³[33m‹˜«˜åà©[37m³
ÚÄÄÄÂÄÄÄÄÄÄÄÄÄÄÁÄÄÄÄÄ¿ ³ ÚÄÄÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
³[33m€/€[37m³[33m€¨®œå¦[37m          ³ ³ ³[33mœ¨ š¨˜­ã ˜¨®œå¦¬[37m                                ³
ÃÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÅÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ´
} T Tag Editor file list header


TELMRK {Û} T Tag Editor file list mark


TELTAB {[0;1m³[32m%3d[37m³[32m%-16s[37m³[32m%-1s[37m³[32m%-1s[37m³[32m%-49s[37m³
} Tag Editor file list


TELFTR {[0;1mÀÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÁÄÁÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
} Tag Editor file list footer


TENASK {[0;1m
ƒé©«œ «¦¤ ˜¨ Ÿ£æ «¦¬ ˜¨®œå¦¬ ([33mX[37m š ˜ â¥¦›¦): [0m} T Tag Editor file number prompt


TENERR {[0;1;31m
˜¨˜¡˜¢é ›é©«œ â¤˜¤ ˜¨ Ÿ£æ ˜¨®œå¦¬ £œ«˜¥ç %d ¡˜  %d.
[0;1m} T Tag Editor bad file number


TENTAG {[0;1;32m
† ¢ã¯ «¦¬ ˜¨®œå¦¬ [37m%d (%s)[32m ˜¤˜™¢ãŸ¡œ.
[0;1m} T Tag Editor, file tagged.


TENUTG {[0;1;32m
€¨© «ª ˜¤˜™¦¢ãª ¢ã¯ª «¦¬ ˜¨®œå¦¬ [37m%d (%s)[32m.
[0;1m} T Tag Editor, file untagged.


TENKLL {[0;1;32m
† ¢ã¯ «¦¬ ˜¨®œå¦¬ [37m%d (%s)[32m £˜«˜ éŸ¡œ.
[0;1m} T Tag Editor, file killed.


TENUKL {[0;1;32m
€¨© «ª £˜«˜åà©ª ¢ã¯ª «¦¬ ˜¨®œå¦¬ [37m%d (%s)[32m.
[0;1m} T Tag Editor, file unkilled.


TESTAT {[0;36m
ÛÛ  [1m‘«˜« ©« ¡á ©«¦ ®œå˜ £œ«˜­¦¨áª ˜¨®œåà¤  [46m[K[0;1m

[37m¨¦ª ¢ã¯:
[32m  €¨®œå˜: [37m%8d
[32m  ‹âšœŸ¦ª:[37m%8d bytes
[32m  •¨æ¤¦ª: [37m%8d ¢œ§«%s

[37m€¤˜™¢ãŸ¡˜¤:
[32m  €¨®œå˜: [37m%8d
[32m  ‹âšœŸ¦ª:[37m%8d bytes

[46m[K[0;1m
} T Tag Editor transfer statistics


CRDSNG {˜} T Credits, singular form

CRDPLR {œª} T Credits, plural form


REFUND {[0;1;35m
!W‘˜ª œ§ ©«¨â­¦¤«˜  [37m%d [35m£¦¤á›%s ®¨æ¤¦¬ ®¨ã©ª ˜§æ ˜¨®œå˜ «à¤
¦§¦åà¤  ¢ã¯ £˜«˜ éŸ¡œ.!)
} T Credits being refunded


DISCON {[0;1m

[33;5mÛÛ[0;1;33m  €“’‹€’† €‘“Œƒ„‘†  !FÛ[0;1;33m

† ©ç¤›œ©ã ©˜ª «œ¨£˜«åœ«˜  ˜¬«æ£˜«˜, æ§àª œå®˜«œ «ã©œ .

!W â©«œ [33;5mEsc[0;1;33m, [33;5mEnter[0;1;33m, ã [33;5mSpace[0;1;33m
š ˜ ˜¡ç¨à© «ª › ˜› ¡˜©å˜ª.!)

[32m€¤«å©«¨¦­ £â«¨©: [0;1m[s} T Automatic Disconnection


COUNTDN {[u[s%02d[30m[K} T Automatic Disconnection countdown


ADABORT {[0;1;32m[K

† ˜¬«æ£˜« ˜§¦©ç¤›œ© ˜¡¬¨éŸ¡œ!
[0;1m} T Automatic Disconnection aborted


UPLHDR {[0;1m
[47m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;47;30m¿ [0;1m
[1;47;37m ³ [0;34;47m€§¦©«¦¢ã ˜¨®œåà¤. ƒé©«œ «¦ œ§ Ÿ¬£«æ §¨à«æ¡¦¢¦ £œ«˜­¦¨áª.                 [30m³ [0;1m
[1;47;37m ³ [0;47;30mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [30m³ [0;1m
} T Upload header


UPLFTR {[1;47;37m ³ [0;47;30mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [30m³ [0;1m
[1;47;37m ³ [0;47;30m ¨¦©Ÿâ©«œ [34m![30m š ˜ ˜¬«æ£˜« ˜§¦©ç¤›œ© £œ«á «¤ ˜§¦©«¦¢ã                    ³ [0;1m
[1;47;37m À[0;47;30mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0;1m
} T Upload footer


LNKNAM {Link ©œ ¬§á¨®¦¤ ˜¨®œå¦} S 40 Name of the 'link' protocol:


UPLFAIL {

[0;1;31;5mÛÛ  [0;1;31m† ˜§¦©«¦¢ã › ˜¡æ§¡œ.

} T Upload failed


URETRY {[0;1m
‡â¢œ«œ ¤˜ œ§ ®œ ¨ã©œ«œ «¤ ˜§¦©«¦¢ã á¢¢ £å˜ ­¦¨á; ([[33mY[37m]es=¤˜  / [[33mN[37m]o=æ® ) } T Retry failed upload?


LNKASK {[0;1m
!W˜¨˜¡˜¢é ›é©«œ «¦ §¢ã¨œª directory ¡˜  æ¤¦£˜ «¦¬ ˜¨®œå¦¬ §¦¬ Ÿâ¢œ«œ ¤˜ œ ©ášœ«œ: [0m!)} T Link file: What file?


LNKERR {[0;1;31m
’¦ ˜¨®œå¦ %s ›œ¤ ­˜å¤œ«˜  ¤˜ ¬§á¨®œ . ˜¤˜›¦¡ £á©«œ.
[0;1m} T Link file: Unable to locate file


LINKOK {[0;1;32m
’¦ ˜¨®œå¦ %s ™¨âŸ¡œ, ¡˜  ›£ ¦¬¨šãŸ¡œ symbolic link §¨¦ª ˜¬«æ.
[0;1m} T Link file: ok


FILSNG {¦¬} T 'file' singular form
FILPLR {à¤} T 'file' plural form

LOGOUT {[0;1;32m
[5mÛÛ[0;1;32m  !i!W„®œ«œ ˜¤˜™á¢œ  «¤ ¢ã¯ [37m%d ˜¨®œå%s[32m.!)
!0l[0;1m} T Logout: you have tagged N files


LOGOUT2 {[0;1m
€¬«ã œå¤˜   «œ¢œ¬«˜å˜ ©˜ª œ¬¡˜ ¨å˜ š ˜ ¤˜ §¨˜š£˜«¦§¦ ã©œ«œ «¤ ¢ã¯.
‡â¢œ«œ ¤˜ šå¤œ  «é¨˜  ¢ã¯; ([[33mY[37m]yes=¤˜  / [[33mN[37m]o=æ® ):!)[0m } T Logout: do you want to receive tagged files?


LANG {}


NOFILES {
[0;1;31mYou don't have any files to transfer at this time.
[0;1m} T Error: no files or tags to transfer, exiting


FNOTFND {
[0;1;31mSorry, the file "%s" no longer exists.
} T File not found


MINSNG {} T Minutes, singular suffix

MINPLR {s} T Minutes, plural suffix


DNLHDR {[0;1m
[47m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;47;30m¿ [0m
[1;47;37m ³ [0;47;30mFile: [31m%-16s  %-49s [30m³ [40m
[1;47;37m ³ [0;47;30mSize: [31m%-8d                [30mTransfer time (approximately): [31m%4d minute%1s [30m³ [0m
[1;47;37m ³ [0;47;30mType: [31m%-67s [30m³ [0m
[1;47;37m ³ [0;47;30mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [30m³ [0m
} T Download header for single files


DNLHDR1 {[0;1m
[47m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;47;30m¿ [0m
[1;47;37m ³ [0;47;30mTotal size: [31m%-8d          [30mTransfer time (approximately): [31m%4d minute%1s [30m³ [0m
[1;47;37m ³ [0;47;30mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [30m³ [0m
} T Download header for multiple files (no info pane)


PROTLIN1 {[1;47;37m ³ [0;47;34m%-2s[30m%33s ³ } T Protocol Menu Line, First Half


PROTLIN2 {[34m%-2s[30m%33s [30m³ [0m
} T Protocol Menu Line, Seconf Half


DNLFTR {[1;47;37m ³ [0;47;30mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [30m³ [0m
[1;47;37m ³ [0;47;34mT [30m . . . .  (tag) Postpone download ³ [34mTE[30m . . . . . . . . . . . Tag Editor [30m³ [0m
[1;47;37m ³ [0;47;34mTT[30m  . .  Download tagged files: [31m%3s[30m ³ Append [34m![30m for auto-hangup when done  [30m³ [0m
} T Download footer with tag commands


DNLFTRT {[1;47;37m ³ [0;47;30mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [30m³ [0m
[1;47;37m ³ [0;47;30mT [30m . . . .  (tag) Postpone download ³ Append [34m![30m for auto-hangup when done  [30m³ [0m
} T Download footer without tag commands


DNLFTRI {[1;47;37m ³ [0;47;30mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [30m³ [0m
[1;47;37m ³ [0;47;30mFiles to download: [31m%4d[30m       Files to be downloaded later (tagged): [31m%4d [30m³ [0m
} T Download footer, file information


DNLFTRL {[1;47;37m À[0;47;30mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0m
[0m} T Download footer, last line


YES {Yes} T "Yes" string


NO {No } T "No" string


VIEWNAME {Inspect %s file} T Name of the viewer "protocol"


FTUNK {(Unknown type - error occured)} T File type detection failed


SHORT {[0;1m
!WPlease enter your option, or [33mX[37m to exit, or [33m?[37m for the menu:!) [0m} T Short menu


ERRSEL {
[0;1;31mI'm sorry, "%s" is not an option.
[0;1m} T Oops, no such option


CONFX {[0;1;31m
!WIf you abort the download, any temporary files will be lost. Do you confirm? 
([[33mY[31m]es / [[33mN[31m]o)!) [0m} T Confirm exit


VIEWWRK {
[s[0;1;36;5mPlease stand by... } T Preparing file viewer - please wait


VIEWBEG {[u[0;1m[K[0;32mÛÛ  [1mContents of file [37m%s  [42m[K[0;1m

[0;1m} T Viewing archive contents


VIEWEND {
[0;42m[K[0;1m
[0;1m} T Viewing archive contents


CANTAG {[0;1;31m
!JFile [37m%s[31m is transient and must be downloaded now.
The system will delete it soon.!)
[0;1m} T Unable to tag transient file


TAGSOMEFIL {[0;1;31m
!JSome files were not tagged for postponed download.
These files are transient and there is no guarantee that they
will exist later. You will have to download or cancel the outstanding
files now.!) [0;1m} T
Tagged some files, must download the rest


TAGFIL {
[0;1mOkay, tagging for later download...
} T Tagged all files, download postponed


TAGSOM {
!J[0;1mOkay, tagging any non temporary files. You'll still
have to download the temporary one(s).!)
} T Tagged all files, download postponed


SUPLOAD {upload} T 'Upload' (used in XFERBEG)

SDNLOAD {download} T 'Download'(used in XFERBEG)

SSINGLE {file} T 'file' (used in XFERBEG)

SMULTI {files} T 'files' (used in XFERBEG)
 

XFERBEG {
[0;1;32m
[5mÛÛ  [0;1;32mReady to [37m%s %s[32m with the [37m%s[32m protocol.
    Press [33m%s[32m a few times to abort.[0;1m

} T Transfer begins now


DNLFAIL {

[0;1;31;5mÛÛ  [0;1;31mThe download was aborted.

[32mFiles still to be downloaded: [37m%d
} T Download failed


RETRY {[0;1m
Would you like to try once more? ([[33mY[37m]es / [[33mN[37m]o) } T Retry failed download?


TEMENU {
[0;47;1;37m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;30;47m¿ [0m
[47;1;37m ³  [0;47;30mTag Editor            [0;47;30m³ [0m
[47;1;37m ³  [0;47;30mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [0;47;30m³ [0m
[47;1;37m ³  [0;31;47mL[30mist files            [30m³ [0m
[47;1;37m ³  [0;31;47mT[30mag/untag file        [30m³ [0m
[47;1;37m ³  [0;31;47mD[30melete/undelete file  [30m³ [0m
[47;1;37m ³  [0;31;47mS[30mtatistics            [30m³ [0m
[47;1;37m ³                        [0;47;30m³ [0m
[47;1;37m ³ [0;30;47me[31mX[30mit                   [30m³ [0m
[47;1;37m À[0;30;47mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0m
} T Tag Editor menu


TESHMNU {[0;1m
!WEnter your choice ([33mL[37m,[33mT[37m,[33mD[37m,[33mS[37m,[33mX[37m to exit, or [33m?[37m for the menu):!) [0m} T Tag Editor Short menu


TEERR {
[0;1;31mSorry, "%c" is not an option here.
[0;1m} T Tag Editor, no such option


TELHDR {[0;1m
                   ÚÄÄÄÂÄÄÄÄÄÄ¿
                   ³[33mTag[37m³[33mCancel[37m³
ÚÄÄÄÂÄÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄ¿ ³ ÚÄÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
³[33m # [37m³[33mFile[37m            ³ ³ ³[33mDescription      [37m                                ³
ÃÄÄÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÅÄÅÄÅÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ´
} T Tag Editor file list header


TELMRK {Û} T Tag Editor file list mark


TELTAB {[0;1m³[32m%3d[37m³[32m%-16s[37m³[32m%-1s[37m³[32m%-1s[37m³[32m%-49s[37m³
} Tag Editor file list


TELFTR {[0;1mÀÄÄÄÁÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÁÄÁÄÁÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
} Tag Editor file list footer


TENASK {[0;1m
Enter the number of the file ([33mX[37m to exit): [0m} T Tag Editor file number prompt


TENERR {[0;1;31m
Please enter a file number in the range %d to %d.
[0;1m} T Tag Editor bad file number


TENTAG {[0;1;32m
The file [37m%d (%s)[32m has been tagged.
[0;1m} T Tag Editor, file tagged.


TENUTG {[0;1;32m
The file [37m%d (%s)[32m has just been untagged.
[0;1m} T Tag Editor, file untagged.


TENKLL {[0;1;32m
Download of the file [37m%d (%s)[32m has been canceled.
[0;1m} T Tag Editor, file killed.


TENUKL {[0;1;32m
Download cancelation for file [37m%d (%s)[32m has just been withdrawn.
[0;1m} T Tag Editor, file unkilled.


TESTAT {[0;36m
ÛÛ  [1mFile transfer statistics  [46m[K[0;1m

[37mTo download:
[32m  Files:    [37m%6d
[32m  Size:     [37m%6d bytes
[32m  Time:     [37m%6d ¢œ§«%s

[37mPostponed (tagged):
[32m  Files:    [37m%6d
[32m  Size:     [37m%6d bytes

[46m[K[0;1m
} T Tag Editor transfer statistics


CRDSNG {} T Credits, singular form

CRDPLR {s} T Credits, plural form


REFUND {[0;1;35m
!WYou have received a [37m%d [35mcredit refund for the files you canceled.!)
} T Credits being refunded


DISCON {[0;1m

[33;5mÛÛ[0;1;33m  AUTOMATIC DISCONNECTION  !FÛ[0;1m

Your connection will be terminated automatically in a moment.

!WPress [33;5mEsc[0;1;33m, [33;5mEnter[0;1;33m, or [33;5mSpace[0;1;33m
to cancel the disconnection.!)

[32mCountdown: [0;1m[s} T Automatic Disconnection


COUNTDN {[u[s%02d[30m[K} T Automatic Disconnection countdown


ADABORT {[0;1;32m[K

Automatic disconnection aborted!
[0;1m} T Automatic Disconnection aborted


UPLHDR {[0;1m
[47m ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ[0;47;30m¿ [0;1m
[1;47;37m ³ [0;34;47mFile upload. Please enter your desired file transfer protocol.            [30m³ [0;1m
[1;47;37m ³ [0;47;30mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [30m³ [0;1m
} T Upload header


UPLFTR {[1;47;37m ³ [0;47;30mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ [30m³ [0;1m
[1;47;37m ³ [0;47;30m Append [34m![30m for automatic disconnection when done                           ³ [0;1m
[1;47;37m À[0;47;30mÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ [0m} T Upload footer


LNKNAM {Link an existing file} S 40 Name of the 'link' protocol:


UPLFAIL {

[0;1;31;5mÛÛ  [0;1;31mThe upload was aborted.

} T Upload failed


URETRY {[0;1m
Would you like to try uploading again? ([[33mY[37m]es / [[33mN[37m]o) } T Retry failed upload?


LNKASK {[0;1m
!WPlease enter the full name (directory & filename) of the file you want to link: [0m!)} T Link file: What file?


LNKERR {[0;1;31m
%s does not appear to exist. Please try again.
[0;1m} T Link file: Unable to locate file


LINKOK {[0;1;32m
%s was found, and a symbolic link was created to it.
[0;1m} T Link file: ok


FILSNG {} T 'file' singular form
FILPLR {s} T 'file' plural form

LOGOUT {[0;1;32m
[5mÛÛ[0;1;32m  !i!WYou have tagged [37m%d file%s[32m for later download.!)
!0l[0;1m} T Logout: you have tagged N files


LOGOUT2 {[0;1m
This is your last chance to download the file(s).
Do you want to do so now? ([[33mY[37m]yes / [[33mN[37m]o):!)[0m } T Logout: do you want to receive tagged files?


LANGEND {}
