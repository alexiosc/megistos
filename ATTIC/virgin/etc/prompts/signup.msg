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
  ”ę¢¦¬Ŗ ¢é©©Ŗ å¤   ā© £Ŗ:
The following languages are available:

} T Language menu, header

LNGSEL2 {%d. %s
} T Language menu, one line of menu

LNGSEL3 {
 ¢ā„« «¤ ¢é©© §¦¬ § ¬£å«. é©« ?   «¦ £¤¦ē:
Please select your language of choice (%d-%d). Enter ? to see the menu: } T Language menu, prompt.

LNGSLRR {
Ø”¢é é©« ā¤¤ Ø £ę ©«¦  į©«£ %d-%d.
Please enter a number within the above limits.
} T Language menu, error.


LNGSLOK {
 ¢ā„« «¤ ¢é©© %s. ¤  § ¢¦ć ©Ŗ ¤ ©Ŗ  ”¤¦§¦ å, £§¦Øå«
Øę«Ø ¤ «¤ ¢¢į„«.

} T Language selected OK.


B4QANS {[2J} T Signup, clear screen (hopefully) before ANSI question


NEWANS {!C[0;1;31m  ŪŪŪ[32m  ŪŪŪ[34m  ŪŪŪ  [37m!)

!JØ¦©§¦ē£ ¤ ¦ē£ ¤ «¦ «Ø£« ”ę ©Ŗ ¬§¦©«Øå  ANSI Ø­ ”į. ¤
«¦ §ØęØ££ § ”¦ ¤ą¤ é¤ ©Ŗ  ā«  „¦£¦åą© «Ø£« ”é¤ (terminal
emulation), «ć©« «¤ § ¢¦ć ANSI, VT-102, VT-100, ć VT-52, ” 
§ ā©« Y ”  <enter>.!)

!J¤ « «Øå ¦Ø¦é¤  § ¦ §į¤ą £­¤å¦¤«  ā®Øą£ ć ©  ­¦Ø« ”¦ēŖ
«ę¤¦¬Ŗ «¦¬ ”Øå¦¬, §¤«ć©« £ Y ©«¤ Øé«©. ¢¢ éŖ, é©« N.!)

ā¢« ANSI Ø­ ”į; ([Y]es=¤  / [N]o=ę® ) } T Signup, asking user for new ANSI setting


ANSBERR {
Ø”¢é §¤«ć©« ©«¤ Øé«© £ Y ć N.

} T Rebuff, wrong answer to ANSI question


 This message is sent to users when they sign up. That is,
 when they type "new" in place of a User-Id. A user is told
 they can do this only when they have connected with a free
 sample channel (see level 2 option "NSAMPLN").

INTRO {[2J[0;1;36m!Z!C           ÜÜ        
ŪŪŪŪŪŪŪŪŪŪ ŪŪ ŪŪŪŪŪŪŪ
ŪŪ      ŪŪ ŪŪ      ŪŪ
ŪŪ      ŪŪ ŪŪ      ŪŪ
ŪŪŪŪŪŪŪ ŪŪ ŪŪŪŪŪŪŪŪŪŪ
        ßß           
[37m¢ą©ćØ« ©«¤ [1m@BBS@[0;1m.
!)

!J   å«Ø ®Øį ©Ŗ ¬§¦®ę£©« ©«¤ £į¢ §¦ ¦« ”ć ¢¢¤ ”ć Ø© «®¤ ”ć
«Øį§ §¢Ø¦­¦Ø é¤ ”  § ”¦ ¤ą¤åŖ. ¬®ę£©«  §Ø¦©§į  £Ŗ ¤ ©Ŗ
Øā© .!)

!JØå¤ ę£ąŖ ©¬¤®å©¦¬£  ā¢£ ”į§¦  ©«¦ ®å   «¦ į«¦£ę ©Ŗ   ¤
£ ¦¬Øć©¦¬£ ¤ ¢¦Ø ©£ę ©«¦ ę¤¦£į ©Ŗ.!)

!J« ©«¦ ®å §¦¬  £Ŗ é©« «éØ ā®¦¬¤ §Øę©© [5m£ę¤¦[0;1m ¦   Ø ©«āŖ
¬©«ć£«¦Ŗ, ¦  ¦§¦å¦  ”  ©£ē¦¤«  ©ē£­ą¤ £ «¦ ”«©«« ”ę «Ŗ į©Ŗ ¤ «
”Ø«ć©¦¬¤ ¬©«Øį §ęØØ«. å¤  §Øå««¦ ¤ ā®¦¬£ « [5m¢ ¤į[0;1m ©Ŗ
©«¦ ®å   ¤ £§¦Øå« ¤ ©¬¤å« ©«¤ į©. «¤ ¤«å« §Øå§«ą©  Ø¦ē£
©«¤ ē©”¦¢ ā© ¤ ©Ŗ  ØįÆ¦¬£.!)

} T Introductory message for users when signing up


PAUSE1 {[0;1;32mē© [37m%d[32m ¬«Ø¦¢ā§«ą¤... [s} T Pause message (start)

PAUSE2 {[u[0m%02d[30m[K } T Pause message (counting)

PAUSE3 {[0;1;32m[80D[K¬®Ø ©«¦ē£   «¤ ¬§¦£¦¤ć ©Ŗ!

} T Pause message (end)


GUSRNAM {[0;1;33m

[AØ”¢é é©« «¦ ę¤¦£ ”  §é¤¬£ę ©Ŗ:   [0;47;30m                                 [32D} T Asking a user signing up for their first and last names


GUSRCOM {[0;1;33m
Ø”¢é  é©«  «¦ ę¤¦£  «Ŗ  « ØåŖ
ę§¦¬  Øį©«, ć §«ć©« Enter ¤  ¤

[A¬§įØ® :                                   [0;47;30m                                 [32D} T Asking a user signing up for their company name


GUSRAD1 {[0;1;33m
é©«  «¤ §Øé«  Ø££ć «Ŗ   ē¬¤©ćŖ

[A©Ŗ (¦ę ”  Ø £ę):                      [0;47;30m                                 [32D} T Asking a user signing up for their address (street)


GUSRAD2 {[0;1;33m
é©« «¤ ē«Ø  Ø££ć «Ŗ  ē¬¤©ćŖ

[A©Ŗ (©¬¤¦ ”å ”  ):                     [0;47;30m                                 [32D} T Asking a user signing up for their address (city,state,zip)


GUSRPHO {[0;1;33m
é©« «¦¤ Ø £ę  «¢­é¤¦¬ §¦¬ £§¦Ø¦ē£

[A¤ ©Ŗ Ø¦ē£:                             [0;47;30m                         [24D} T Asking a user signing up for their telephone number


GUSRAGE {[0;1;33m
 , ¤  ¤  ¤ę£©«   į”Ø «¦ , §¦ 

[Aå¤   ¢ ”å ©Ŗ;                        [0;47;30m    [3D} T Asking a user signing up how old they are


GUSRSEX {[0;1;33m

[Aå©« į¤«ØŖ ć ¬¤å”; (é©« [[37mM[33m]ale=į¤«ØŖ ć [[37mF[33m]emale=¬¤å”)  [0;47;30m   [2D} T Asking a user signing up what sex they are


GSCNWID {[0;1;32m

!J į©« ¬«ć «¤ Øé«© §Ø¦©”« ”į. ¤ §¤«ć©« ¢¤©£ā¤, [37m¤ 
£§¦Øå« ¤ å« ©ą©«į ¦Ø ©£ā¤Ŗ §Ø ¦®āŖ «Ŗ į©Ŗ[32m.!)

!JØ® ”į ¢¦ §ę¤  ā¢£ ¤ £Ŗ §å« §ę©¦¬Ŗ [5;37m®Ø”«ćØŖ ¤ Ø££ć
(©«ć¢Ŗ)[0;1;32m £§¦Øå ¤ å„   ¦ę¤ ©Ŗ. «ć©« [37mEnter[32m  
«¦ ©ē¤Ŗ §¦¬ å¤  [37m80[32m.!)


[A[33mę©Ŗ ©«ć¢Ŗ ” £ā¤¦¬ £­¤å   ¦ę¤ ©Ŗ; [Enter=80] [0;47;30m     [4D} T Asking a user signing up for the width of their screen


SCN2NAR {[0;1;31m
!J « £ć §¦¬ é©« å¤  §¦¢ē £ ”Øć. ¬£å«, «¦ē£ «¦¤ Ø £ę 
§¦¬ å®¤   ¦ę¤ ©Ŗ. «¤ §¢ ¦¤ę«« «ą¤ §Ø §«é©ą¤, å¤  80.[0;1m!)

} T Hey, we want the WIDTH of your screen, ya cretin!


SCNWDOK {[0;1;32m
!J ¬«ć ©Ŗ «¤ §į¤«©, ”¦Øå«  «¦ £ć”¦Ŗ «ą¤ Ø££é¤
§¦¬  £­¤å¦¤«  ©«¤ ¦ę¤ ©Ŗ.!)
[0;1m} T The text formatting feature is adjusted for your screen


GSCNHGT {[0;1;32m
!JéØ  ā¢£ «¦¤ Ø £ę «ą¤ [37mØ££é¤[32m §¦¬ £§¦Øå ¤ å„   ¦ę¤ ©Ŗ.
 Ø £ęŖ ¬«ęŖ å¤  ­¬© ¦¢¦ ”į 25, ¢¢į ¤ «¦ §ØęØ££ § ”¦ ¤ą¤ é¤ §¦¬
®Ø© £¦§¦ å« £­¤å  £å ć ē¦ Ø££āŖ §¢Ø¦­¦Ø é¤, £ é¤«  © 24 ć
23.!)


[A[33m!Wę©Ŗ Ø££āŖ ” £ā¤¦¬ £­¤å   ¦ę¤ ©Ŗ; [Enter=23] [0;47;30m     [4D!)} T Asking a user signing up for the height of their screen


GSYSTYP {[0;1;32m
Ø”¢é § ¢ā„« «¦¤ «ē§¦ ¢”«Ø¦¤ ”¦ē ¬§¦¢¦ ©«ć §¦¬ ā®«:

     [1;37;40m1.[0;1;32m ¤Ŗ IBM PC ć ©¬£«ęŖ.
     [1;37;40m2.[0;1;32m ¤Ŗ Apple Macintosh.
     [1;37;40m3.[0;1;32m E¤Ŗ Apple ¬§¦¢¦ ©«ćŖ ¢¢į ę®  Macintosh.
     [1;37;40m4.[0;1;32m å Amiga.
     [1;40;37m5.[0;1;32m ¤ Atari, ¦§¦ ¦ć§¦« £¦¤«ā¢¦.
     [1;40;37m6.[0;1;32m ¤Ŗ Archimides
     [1;40;37m7.[0;1;32m ¤Ŗ Amstrad 6128.
     [1;40;37m0.[0;1;32m å§¦« §ę « §Ø§į¤ą.


[A[0;1;33m ¢ā„« ¤¤ Ø £ę §ę «¦ 0 āąŖ «¦ 7: [0;47;30m   [2D} T Asking a user signing up what type computer they are using


PREUID {[0;1;32m
!JéØ  §Øā§  ¤  ¢ā„« ā¤ Æ¬é¤¬£¦ ¤¤éØ ©Ŗ ©«¤ į©. §ę ¬«ę
Æ¬é¤¬£¦  ©Ŗ ¤¤ąØå¦¬¤ ¦  į¢¢¦  ©¬¤Ø¦£«āŖ £Ŗ ”  «¦ å ¦ «¦
©ē©«£. ¦ Æ¬é¤¬£ę ©Ŗ §Øā§  ¤ §¦«¢å«  §ę [37m3[32m ąŖ
[37m@MAXUIDLEN@[32m ®Ø”«ćØŖ. § «Ø§«į å¤¦¤«  £ę¤¦ Øį££«
«¦¬ ¢« ¤ ”¦ē ¢­ć«¦¬.!)

!J  ¦ć  ©Ŗ ¤­āØ¦¬£ £Ø ”į Æ¬é¤¬£ ć ®Ø©«é¤: Handsome, CPower,
Xenios, Kurgan, Magic, Hermes, Noble, Marvin, QLUser, ”¢§. §¦Øå« §å©Ŗ
¤ ©¬¤¬į©« «¦ ę¤¦£ ”  «¦ §é¤¬£ę ©Ŗ © ā¤ Æ¬é¤¬£¦.   §Øį £,
¦ ¬§¦« ”ęŖ ®Øć©«Ŗ ¤ØāŖ  £ę§¦¬¢¦Ŗ £§¦Øå ¤  ¢ā„  «¦ Æ¬é¤¬£¦
AnSi.!)
} T Information about user-IDs


GUSERID {[0;1;33m

!W[AØ”¢é é©« «¦ Æ¬é¤¬£¦ (user id) §¦¬  ®Ø© £¦§¦ å«: [0;47;30m            [11D!)} T Asking for a User-Id


BADUID1 {[0;1;31m
!J¬©«¬®éŖ ©«¦ Æ¬é¤¬£ę ©Ŗ § «Øā§¦¤«  [37m£ę¤¦ ¢« ¤ ”į Øį££«[31m.
®  Ø £¦å, ¦ē« ©£å ©«å„Ŗ ć ¢¢¤ ”į. Ø”¢é „¤§Ø¦©§ć©«.[0;1m!)
} T Reply to a choice of User-Id that is invalid


BADUID2 {[0;1;31m
!J¬¤é£, ¢¢į ¬«ę «¦ Æ¬é¤¬£¦ ¤ å¤  § «Ø§«ę. Ø”¢é  ¢ā„« ā¤
į¢¢¦.[0;1m!)
} T Reply to a choice of User-Id which is in the 'black list'.


SMLUID {[0;1;31m
!J¬¤é£, «¦ Æ¬é¤¬£ę ©Ŗ §Øā§  ¤ å¤  «¦¬¢į® ©«¦¤ 3 ®Ø”«ćØŖ ©
£ć”¦Ŗ. Ø”¢é „¤§Ø¦©§ć©«.[0;1m!)
} T Reply to choice of User-Id that is too short


BADUID3 {[0;1;31m
!J¬¤é£, ”į§¦ ¦Ŗ į¢¢¦Ŗ ā®  ć  ¢ā„  «¦ Æ¬é¤¬£¦ [37m%s[31m.
¦” £į©« ”į§¦ ¦ į¢¢¦.[0;1m!)
} T Reply to choice of User-Id that is not unique


UIDOK {[0;1;32m
!J¤ £¤¬£į ©Ŗ, ¢¦ §ę¤,  ­å¤«  ©«¦¬Ŗ į¢¢¦¬Ŗ ®Øć©«Ŗ éŖ „ćŖ:!)

[37m    §ę %s: ę© Clubs ā®   AcroBase;

!J[33må©«  ”¤¦§¦ £ā¤¦Ŗ £ «¤ § ¢¦ć «¦¬ Æ¬ą¤ē£¦¬;!)
                    
[A                             ([[37mY[33m]es=¤  / [[37mN[33m]o=ę® ) [0;47;30m   [2D} T Asking a user to confirm their choice of User-Id


GOTUID {[0;1;32m
!J¤«į„ , [37m%s[32m. ¬«ę  å¤  ¢¦ §ę¤ «¦ Æ¬é¤¬£ę ©Ŗ §ę é ” 
©«ę „ćŖ.!)
[0;1m} T Ok, this is your user-ID!

PREPSW {[0;1;32m

!JéØ §Ø”¢é  ¢ā„« ā¤ ©ē¤£, ā«©  é©« ¤ £¤ £§¦Ø¦ē¤ į¢¢¦  ¤
®Ø© £¦§¦ ć©¦¬¤ «¦ Æ¬é¤¬£ę ©Ŗ ”  «¦¤ ®Øę¤¦ ©Ŗ. į¤« «¦ ©ē¤£į ©Ŗ £ ”Øę
  ¤ «¦ ¬£į©« ©åŖ ē”¦¢ ¢¢į ę®  ”  ¤ «¦ £¤«ē¦¬¤ į¢¢¦  ē”¦¢. 
©­į¢  «¦¬ ¢¦Ø ©£¦ē ©Ŗ ā” «  ©«¦ ¤ £¤ „āØ  [37m”¤åŖ[32m į¢¢¦Ŗ «¦
©ē¤£į ©Ŗ.[0;1m!)

} T Telling a user signing up what a password is


RECPSW {[0;1;32m
[37;5mŪŪ[0;1;32m   į© ©Ŗ §Ø¦«å¤  «¦ „ćŖ ©ē¤£: [37m%s[32m

!J§¦Øå« ¤ «¦ ®Ø© £¦§¦ ć©« ¦¢ę”¢Ø¦, £āØ¦Ŗ «¦¬, ć ¤ é©« ā¤ «¢åąŖ
 ­¦Ø« ”ę ©ē¤£. ¦ §Ø¦« ¤ę£¤¦  ©ē¤£, §į¤«ąŖ, å¤  ©®« ”į ē”¦¢¦
¤ «¦ ¬£į©«, ”  ¤«¬§ą© ”į ē©”¦¢¦ ¤ «¦ Ø  ”į§¦ ¦Ŗ ””ę¦¬¢¦Ŗ.!)
[0;1m} T Recommend a random password


FRCPSW {[0;1;32m
!J  ¢ę¦¬Ŗ ©­¢åŖ, ©«¤ §Øé« ©ē¤© ¤ å¤« ©åŖ «¦ ©ē¤£į ©Ŗ,
¢¢į ©Ŗ ¤ā«  ā¤ ©ē¤£  į©. ¤ «¦ ©ē¤£ ¤ ©Ŗ  ”¤¦§¦ å,
£§¦Øå« ¤ «¦ ¢¢į„« Øę«Ø. ¦ ©ē¤£ §¦¬ ©Ŗ ā®¦¬£ é© , §į¤«ąŖ,
å¤  ©®« ”į ē”¦¢¦ ¤ «¦ ¬£į©«, ”  ¤«¬§ą© ”į ē©”¦¢¦ ¤ «¦ Ø 
”į§¦ ¦Ŗ ””ę¦¬¢¦Ŗ.!)

[37;5mŪŪ[0;1;32m   į© ©Ŗ ā®  é©  «¦ „ćŖ ©ē¤£: [37m%s[32m
[0;1m} T Random password forcibly assigned


GPSWORD {[0;1m

!W[Aé©« «¦ ©ē¤£ §¦¬  ®Ø© £¦§¦ å«:  [0;47;30m                 [16D!)} T Asking a user signing up to choose a password


GPSWAGN {[0;1m

!W[A¤é©« «¦ ©ē¤£   §¢ć¬©:     [0;47;30m                 [16D!)} T Ask again for password verification


BADPSW1 {[0;1;31m
!J¦ ©ē¤£į ©Ŗ §Øā§  ¤ ā®  «¦¬¢į® ©«¦¤ [37m5[31m ®Ø”«ćØŖ.
¢ć  ā å¤ , §å©Ŗ, ¤ §Ø ¢£į¤  [37mØ £¦ēŖ ć ¢¢¤ ”į
Øį££«[31m.!)
[0;1m
} T Password not safe, re-enter


BADPSW2 {[0;1;31m
!J¬«ę «¦ ©ē¤£ å¤  §¦¢ē ē”¦¢¦ ¤ Øå. Ø”¢é ¦” £į©« ”į« 
¢ ę«Ø¦ ­¤Øę.!)
[0;1m
} T Such a stupid password, re-enter.


BADPSW3 {[0;1;31m
!J ē¦ ©¬¤ć£« ¤ å¤  ę£¦ . Ø”¢é „¤¦” £į©« §ę «¤ Ø®ć.
[0;1m!)
} T Passwords don't match, re-enter.


PSWEPI {[0;1;32m[2J[0;1;5m
!CŪŪ[0;1;33;41m                                  ! ! !                          [0;1;5mŪŪ
ŪŪ[0;1;33;41m                            !                 [0;1;5mŪŪ!)
[0;1;37m
!J¤åŖ ¤ £§¦Øå ¤ ©Ŗ ¦ć©  ¤ « „®į©«. ¤ £§¦Ø¦ē£ ¤ é©¦¬£ «¦
©ē¤£ ¤ęŖ ®Øć©«   ”¤ā¤ ¢ę¦. ¤ „®į©« «¦ ©ē¤£į ©Ŗ [31m®į©« «¦¤
¢¦Ø ©£ę ©Ŗ[37m. ¤ §å« «¦ ©ē¤£į ©Ŗ © ¦§¦ ¦¤ć§¦« «Øå«¦, ¬§įØ®  §į¤«
[31m”å¤¬¤¦Ŗ ©­¢åŖ[37m.     .!)

!J¦ ©ē¤£į ©Ŗ ¢ć  £«į §ę @PASSEXP@ £āØŖ. «į §ę «¦ §āØŖ ¬«¦ē «¦¬ ®Øę¤¦¬,
 ©Ŗ «å ¤ «¦ ¢¢į„«.!)

!J«ć©« Enter £ę¤¦ į¤ ā®« ć ©£ é©  «¦ Æ¬é¤¬£¦ ”  «¦ ©ē¤£į ©Ŗ! [0;30m[K!)} T Telling a user to REMEMBER their choice of User-Id/password


WELCOME {[0;1m[2J!Z!C[0;1m¢ą©ćØ« ¢¦ §ę¤ ©«¤ [1;36;5m@BBS@[0;1m!!)

!JŖ ¤ąØå¦¬£ ę«  «¦ ©ē©«£ ā®  [32m§ā¤«[37m Ø££āŖ.   Ø££āŖ å¤  ¦  „ćŖ:
[32m8231753[37m, [32m8815616[37m, [32m8816312[37m, [32m8220610[37m
”  [32m8819963[37m (33600 bps).!)

!J   Ø ©«āŖ ¬©«ć£«¦Ŗ ā®¦¬¤ ”į  ”åą£ ¤ ®«¦ē¤ ć ¤ §¦ØØåÆ¦¬¤ ā¤¤
®Øć©« £ į© «¦¬Ŗ ”¤ę¤Ŗ «¦¬ [32m”«©«« ”¦ē[37m «Ŗ. Øę©ć £Ŗ
å¤  ¤ ©Ŗ §Ø¦©­āØ¦¬£ ā¤ ­ ¢ę„¤¦ §Ø į¢¢¦¤ ”  ¤ ©Ŗ ¦ć©¦¬£ © ”į
©Ŗ §¦Øå. ¬«ę §¦¬ ”į¤  «¤ [36m@BBS@[37m ¤ „®ąØå  å¤  «¦ §å§¦
§ ”¦ ¤ą¤åŖ £«„ē «ą¤ ®Ø©«é¤ £ā© §ę « Ŗ [32m  ”āŖ §Ø ¦®āŖ
(Clubs)[37m ę§¦¬ ¢§å¦¬£ ¤ ©Ŗ ¦ē£ §¦¢ē ©ē¤«¦£.!)

!Ję¤¦   ©ć£Ø  ā®« [32m5[37m ¢§«į ®Øć©Ŗ. ¤ « ©«¦ ®å ©Ŗ å¤ 
©ą©«į, §ę ēØ ¦  ā®« §¢ćØ §Øę©© £ [32m25[37m ¢§«į £Ø©åąŖ. 
[36m@BBS@[37m å¤  Ø© «®¤ ”ć į© ”  ¤ ©Ŗ ¬§¦®Øé¤  © ©¬¤Ø¦£āŖ.
¤ ©¬££«ā®« ¤Øį ©« [32mclubs[37m £ £¤ē£« ”  įØØ, «ę«  ©Ŗ
ąå ©å¦¬Ø į­¦¤¦Ŗ ®Øę¤¦Ŗ ®Øć©Ŗ.!)

} T Welcoming a user to the system


 This string will become the topic of the message that is
 automatically created for each new user.

 If the message has an attachment, then the name of the file
 will be pre-pended to the topic you give here, so that the
 message will appear as a bona-fide "file description" (thus
 prompting the user with the filename at the download point
 and defaulting the auto-download filename properly in case
 you happen to be running the File Library Edition).

S2UTPC {¢ą©ćØŖ} (SUPE2U=YES) S 30 New-user auto-message topic:


 This message can be up to 23 lines of up to 76 characters
 each.  It is automatically sent to new users as E-Mail
 from Sysop as soon as the user's account is created.

 If you do not wish to provide an attachment to this
 message, be sure to change the wording of the message,
 and to set the value of the following configuration
 variable, E2UATT, to blank.

 To edit this configuration variable text, press F2.

S2UTXT {[0;1m
  §«ā ¤ā £Ŗ ­å¢(),
£   å«Ø ®Øį © ”¢ą©¦Øåą ©«¤ £ ”Øć ”¦ ¤ą¤å «Ŗ [33mAcrobase[37m.
ę¤¦   ©ć£Ø  ā® Ŗ 5 ¢§«į ®Øć©Ŗ ¤é §ę ēØ ¦ ”  ­¦ē « ©«¦ ®å
§¦¬ £ę¢ Ŗ į­©Ŗ å¤  ©ą©«į  ©¦¬ å¤¦¬£ 45 ąØį¤ ¢§«į «¤ £āØ.
   [33m@BBS@[0;1m å¤  £ ¦ēØ£ £Ø ”é¤ ¤Øé§ą¤ §¦¬ ¢«Øē¦¬¤ «¤
§¢Ø¦­¦Ø ”ć ”  «¤ § ”¦ ¤ą¤å ”  ”¬ØåąŖ §Ø¦©­āØ  £ā© §ę « Club «Ŗ
¬«ę ”Ø éŖ, ­ ¢ ”ć «£ę©­ Ø, ¤«¢¢ć  é¤ ”  ¤é©ą¤, įØØ § ©«-
£¦¤ ”į ¢¢į ”  §¦ ”å¢Ŗ ē¢Ŗ.
  ¤ ę¢ ¬«į §¦«¢¦ē¤ ”    ©ā¤ ¬«ę ”Ø éŖ §¦¬ ā¢ Ŗ, ¢§å¦¬£ ¤
© ¦ē£ «”« ”ę £ā¢¦Ŗ «Ŗ §ØāŖ £Ŗ.
  ”¦¢¦¬å ā¤ Ø®å¦ £ «¦¤ «Øę§¦ ¢ «¦¬ØåŖ «¦¬ §Ø¦Øį££«¦Ŗ ”į«ą §ę
«¦ ¦§¦å¦ «Øā®   į© £Ŗ. įØ«¦ £ ā¤ §ę « ¤ą©«į §Øą«ę”¦¢¢ § ”¦ ¤ą-
¤ é¤ §¤«é¤«Ŗ £ Yes ©«¤ Øą«© §¦¬  ©¦¬ ¬§¦į¢  «¦ ©ē©«£.
    ©¬¤Øį«Ŗ £¦¬ ”  é §Ø¦©ą§ ”į, © ”¢ą©¦Øå¦¬£   £  ”ę£ ­¦Øį
©«¤ [33m@BBS@[0;1m.

     ¢ ”į,
    «ā¢ ¦Ŗ £ęØ”Ŗ

     Ø ©«ćŖ ¬©«ć£«¦Ŗ
} T Text of E-Mail message to new users from Sysop


U2STPC {ā¦Ŗ ®Øć©«Ŗ %s} T Topic of signup message to Sysop


CKSHEADER {
[0;1;32m
:

} T Checksup header


CKSNAME {¤¦£:     !i} T Checksup, name

CKSNAME1 {Ø ā®  ©¬¤ć ©«¦¬Ŗ ®Ø”«ćØŖ.
} T Checksup, invalid characters in name

CKSNAME2 {¤ §Ø ā®  ē¦ ¢ā„ Ŗ.
} T Checksup, bad number of words in name


CKSADDR { ē¬¤©: !i} T Checksup, address

CKSADDR1 {Ø ā®  ©¬¤ć ©«¦¬Ŗ ®Ø”«ćØŖ.
} T Checksup, invalid characters in address

CKSADDR2 {¤ §Ø ā®  Ø £¦ēŖ ”  ©« Ŗ ē¦ Ø££āŖ.
} T Checksup, no numbers in address


CKSPHONE {¢ā­ą¤¦:  !i} T Checksup, phone

CKSPHONE1 {Ø ā®  ©¬¤ć ©«¦¬Ŗ ®Ø”«ćØŖ.
} T Checksup, invalid characters in phone


CKSPHONE2 {¤ Ø £å 7 ®Ø”«ćØŖ.
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


NEWANS {!C[0;1;31m  ŪŪŪ[32m  ŪŪŪ[34m  ŪŪŪ  [37m!)

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
ŪŪŪŪŪŪŪŪŪŪ ŪŪ ŪŪŪŪŪŪŪ
ŪŪ      ŪŪ ŪŪ      ŪŪ
ŪŪ      ŪŪ ŪŪ      ŪŪ
ŪŪŪŪŪŪŪ ŪŪ ŪŪŪŪŪŪŪŪŪŪ
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
[37;5mŪŪ[0;1;32m  System recommended password: [37m%s[32m

!JYou may use the recommended password, parts of it, or give a completely
different one. The recommended password, however, is easy to remember, and
amazingly difficult for crackers to find.!)
[0;1m} T Recommend a random password


FRCPSW {[0;1;32m
!JFor security reasons, the system will automatically assign you a password.
If it is unsatisfactory, you may change it later. The password we have
given you, however, is easy to remember, and amazingly difficult for crackers
to find.!)

[37;5mŪŪ[0;1;32m  This is your password: [37m%s[32m
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
!CŪŪ[0;1;33;41m                           C A U T I O N ! ! !                          [0;1;5mŪŪ
ŪŪ[0;1;33;41m                        WRITE YOUR PASSWORD DOWN!                       [0;1;5mŪŪ!)
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


U2STPC {ā¦Ŗ ®Øć©«Ŗ %s} T Topic of signup message to Sysop


CKSHEADER {
[0;1;32m
:

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
