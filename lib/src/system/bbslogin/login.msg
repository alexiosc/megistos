LEVEL2 {}

LONALRM {Minutes before bbslogin timeout (0=disable): 1} N 0 32767

TERMINAL {megistos} S 32 Default terminal type of BBS channels

METAB4 {If available, run MetaBBS client before the local BBS' login screen? NO} B

METALG {If available, enable OUT command to run MetaBBS client at login? YES} B

UNIXUID {bbsuser} S 8 UNIX UID used for BBS users? (name or numerical)



LEVEL3 {}

DESCR {„å©¦›¦ª ©« ™á©} S 43 Area description for login stuff

LDOWN {

@BBS@

Š¬§á£˜ , ˜¬«ã  š¨˜££ã œå¤˜  ˜§œ¤œ¨š¦§¦ £â¤...

} T Line is down, hanging up


XLATEM {[0;1m
¨ ¤ ¥œ¡ ¤ã©¦¬£œ, Ÿ˜ Ÿâ¢˜£œ ¤˜ ¥â¨˜£œ «  œå›¦¬ª š¨˜££˜«¦©œ ¨á â®œ«œ.
Before we start, we'd like to know what kind of character set you have.

[33m1[37m. [32mGreek 437G/737[37m ã ©¬£™˜«æ font. €¤ £§¦¨œå«œ ¤˜ › ˜™á©œ«œ ˜¬«æ «¦
   ¡œå£œ¤¦, «æ«œ ›é©«œ '[33m1[37m'.

[33m2[37m. [32mCodepage 928, ÅËÏÔ-928 Ş ISO-8859-7[37m. Áí ìğïñåßôå íá äéáâÜóåôå áõôü ôï
   êåßìåíï, ôüôå äşóôå '[33m2[37m'.

[33m3[37m. [32mIBM PC extended ASCII, xwris Ellhnika[37m. Dwste '[33m3[37m' an oi akolouthoi
   xarakthres emfanizontai ws tria orthogwnia diaforetikwn tonwn: °° ±± ²²

[33m4[37m. [32m7-bit ASCII[37m. Dialejte ayth thn epilogh an tipota apo ta parapanv den sas
   einai katallhlo.

ƒé©«œ «¤ œ§ ¢¦šã ©˜ª.
Please enter your option. ([33m1[37m,[33m2[37m,[33m3[37m,[33m4[37m) [Enter=%d]: [0m} T Before login, ask about character set translation


XLATEE {
¨â§œ  ¤˜ › ˜¢â¥œ«œ £å˜ ˜§æ « ª §˜¨˜¡á«à £œŸæ›¦¬ª £œ«á­¨˜©ª.
You have to choose one of the translation methods below.

} T Invalid option


 This is the string output when ANSIOP is set to AUTO,
 to solicit from the user's terminal emulator the ANSI
 "cursor position report" sequence.

SANSI {[0;1m
‘ç¤›œ© œ§ «¬®ãª. ˜¨˜¡˜¢é §œ¨ £â¤œ«œ.
} T Auto-sensing ANSI

 This question is only used if you have answered "ASK" as
 the value of parameter ANSIOP: "Initial ANSI setting at
 start of session".  The question is asked before the
 HELLO message even appears, so that you can conditionally
 display ANSI graphics as part of your system-ID, if you
 like.  (Note that the preferred method for determining
 this is to set ANSIOP to AUTO, however.)


QANSI {

!C[0;1;31m  ÛÛÛ[32m  ÛÛÛ[34m  ÛÛÛ  [37m!)

!J€¤ «˜ «¨å˜ ¦¨Ÿ¦šé¤ ˜ § ¦ §á¤à œ£­˜¤å¦¤«˜  âš®¨à£˜ ã ©œ › ˜­¦¨œ« ¡¦çª
«æ¤¦¬ª «¦¬ š¡¨å¦¬, ˜§˜¤«ã©«œ £œ Y ©«¤ œ¨é«©. €¢¢ éª, ›é©«œ N.!)

‡â¢œ«œ ANSI š¨˜­ ¡á; ([Y]es=¤˜  / [N]o=æ® ) } T Display ANSI graphics question


QANSIERR {
˜¨˜¡˜¢é ˜§˜¤«ã©«œ ©«¤ œ¨é«© £œ Y ã N.

} T Rebuff, wrong answer to ANSI question


ASKLNG1 {[2J[0;1m
The following languages are available:

} T Language menu, header

ASKLNG2 {%d. %s
} T Language menu, one line of menu

ASKLNG3 {
Please select your language of choice (1-%d). [Enter=%d]: } T Language menu, prompt.

ASKLNGR {

Please enter a number in the range 1 to %d.

} T Language menu, error.





 This message is given to users when they first connect to
 The Major BBS.  It tells them the title of your BBS, your
 registration number, their baud rate, and the time and
 date.

 This message comes immediately BEFORE any special log-on
 message that may have been set from the Sysop console of
 The Major BBS.

             Tap F2 to view or edit this text.

HELLO {[2J[0;1m@VERSION@.

[0;1;30m[37C[0;1mÛ[0mÛÛÛÛ   ‰˜¢éª ã¨Ÿ˜«œ ©«¦¤ ‹âš ©«¦
[36C[1mÛÛÛ[0mÛÛÛÛ   á©: @BBS@
[35C[1mÛÛÛÛÛ[0mÛÛÛÛ   ’˜®ç««˜: @BAUD@
[34C[1mÛÛÛÛÛÛÛ[0mÛÛÛÛ   ‘¬¤›œŸã¡˜«œ: @TIME@ @DATE@
[33C[1mÛÛÛÛ[30mÛ[37mÛÛÛÛ[0mÛÛÛÛ
[32C[1mÛÛÛÛ[30mÛÛÛ[37mÛÛÛÛ[0mÛÛÛÛ
[31C[1mÛÛÛÛ[30mÛÛÛÛ [37mÛÛÛÛ[0mÛÛÛÛ
[30C[1mÛÛÛÛ[30mÛÛÛÛ   [37mÛÛÛÛ[0mÛÛÛÛ
[29C[1mÛÛÛÛ[30mÛÛÛÛ[5C[37mÛÛÛÛ[0mÛÛÛÛ
[28C[1mÛÛÛÛ[30mÛÛÛÛ[7C[37mÛÛÛÛ[0mÛÛÛÛ
[27C[1mÛÛÛÛ[30mÛÛÛÛ[9C[37mÛÛÛÛ[0mÛÛÛÛ
[26C[1mÛÛÛÛ[30mÛÛÛÛ[11C[37mÛÛÛÛ[0mÛÛÛÛ
[25C[1mÛÛÛÛ[30mÛÛÛÛ[13C[37mÛÛÛÛ[0mÛÛÛÛ
[24C[1mÛÛÛÛ[30mÛÛÛÛ[15C[37mÛÛÛÛ[0mÛÛÛÛ
[23C[1mÛÛÛÛ[30mÛÛÛÛ[0mÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ
[22C[1mÛÛÛÛ[30mÛÛÛÛ[0mÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ
[22C[1mÛÛÛ[30mÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ
[23C[37mÛ[30mÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ

[24C[37mP R O J E C T   M E G I S T O S[0;1m
} T Greeting message when user first connects to the BBS


THELLO {[2J[0;1m@VERSION@.

[0;1;30m[37C[0;1mÛ[0mÛÛÛÛ   ‰˜¢éª ã¨Ÿ˜«œ ©«¦¤ ‹âš ©«¦
[36C[1mÛÛÛ[0mÛÛÛÛ   á©: @BBS@
[35C[1mÛÛÛÛÛ[0mÛÛÛÛ   ’˜®ç««˜: @BAUD@
[34C[1mÛÛÛÛÛÛÛ[0mÛÛÛÛ   ‘¬¤›œŸã¡˜«œ: @TIME@ @DATE@
[33C[1mÛÛÛÛ[30mÛ[37mÛÛÛÛ[0mÛÛÛÛ   ‚¨˜££ã telnet: @TNLNUM@/@TNLMAX@
[32C[1mÛÛÛÛ[30mÛÛÛ[37mÛÛÛÛ[0mÛÛÛÛ
[31C[1mÛÛÛÛ[30mÛÛÛÛ [37mÛÛÛÛ[0mÛÛÛÛ
[30C[1mÛÛÛÛ[30mÛÛÛÛ   [37mÛÛÛÛ[0mÛÛÛÛ
[29C[1mÛÛÛÛ[30mÛÛÛÛ[5C[37mÛÛÛÛ[0mÛÛÛÛ
[28C[1mÛÛÛÛ[30mÛÛÛÛ[7C[37mÛÛÛÛ[0mÛÛÛÛ
[27C[1mÛÛÛÛ[30mÛÛÛÛ[9C[37mÛÛÛÛ[0mÛÛÛÛ
[26C[1mÛÛÛÛ[30mÛÛÛÛ[11C[37mÛÛÛÛ[0mÛÛÛÛ
[25C[1mÛÛÛÛ[30mÛÛÛÛ[13C[37mÛÛÛÛ[0mÛÛÛÛ
[24C[1mÛÛÛÛ[30mÛÛÛÛ[15C[37mÛÛÛÛ[0mÛÛÛÛ
[23C[1mÛÛÛÛ[30mÛÛÛÛ[0mÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ
[22C[1mÛÛÛÛ[30mÛÛÛÛ[0mÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ
[22C[1mÛÛÛ[30mÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ
[23C[37mÛ[30mÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ

[24C[37mP R O J E C T   M E G I S T O S[0;1m
} T Greeting message for telnet connections


TFULL {

@BBS@

Š¬§¦ç£˜©«œ, ˜¢¢á ¡˜  ¦  @TNLMAX@ telnet š¨˜££âª £˜ª œå¤˜  ¡˜«œ ¢££â¤œª ˜¬«ã
«¤ ©« š£ã. ˜¨˜¡˜¢¦ç£œ ¥˜¤˜§¨¦©§˜Ÿã©«œ ˜¨šæ«œ¨˜. …«¦ç£œ ©¬šš¤é£ š ˜ «¤
«˜¢˜ §à¨å˜.

} T All telnet lines full, cannot connect


 This message (if given) comes immediately AFTER the log-on
 message that may have been set from the Sysop console of
 The Major BBS.

ENTUSID {[0;1m
˜¨˜¡˜¢é ›é©«œ «¦ ¯œ¬›é¤¬£æ ©˜ª.
„á¤ œå©«œ ¤â¦ª ®¨ã©«ª ›é©«œ "[33mnew[0;1m" (®à¨åª œ ©˜šàš ¡á): [K[0m} T Asking for User-Id, free sample channel


 This is the first question asked of any user accessing your
 BBS on one of your "live" reserved channels.
 These channels only allow
 users to log on who already have an account.

 This message (if given) comes immediately AFTER the log-on
 message that may have been set from the Sysop console of
 The Major BBS.

LOGUID {[0;1;33m
„á¤ œå©«œ ¤â¦ª ®¨ã©«ª, §˜¨˜¡˜¢¦ç£œ ¡˜¢â©«œ ©«˜ «¢â­à¤˜ 8231753 ¡˜  8815616[37m

˜¨˜¡˜¢¦ç£œ ›é©«œ «¦ ¯œ¬›é¤¬£æ ©˜ª: [K[0m} T Asking for User-Id, live channel



ENTUSIDM {[0;1m
˜¨˜¡˜¢é ›é©«œ «¦ ¯œ¬›é¤¬£æ ©˜ª, ã [33mout[0;1m š ˜ ©ç¤›œ© £œ á¢¢¦ ©ç©«£˜
£â©à › ¡«ç¦¬. „á¤ œå©«œ ¤â¦ª ®¨ã©«ª ›é©«œ [33mnew[0;1m: [K[0m} T Asking for User-Id, free sample channel

 This is the first question asked of any user accessing your
 BBS on one of your "live" reserved channels.  This is a
 channel whose channel number is greater than or equal to
 the value of the NSAMPLN option.  These channels only allow
 users to log on who already have an account and whose
 account is "live" (has had credits posted to it).

 This message (if given) comes immediately AFTER the log-on
 message that may have been set from the Sysop console of
 The Major BBS.

LOGUIDM {[0;1;33m
„á¤ œå©«œ ¤â¦ª ®¨ã©«ª, §˜¨˜¡˜¢¦ç£œ ¡˜¢â©«œ ©«˜ «¢â­à¤˜ 8231753 ¡˜  8815616[37m

˜¨˜¡˜¢¦ç£œ ›é©«œ «¦ ¯œ¬›é¤¬£æ ©˜ª, ã [33mout[0;1m š ˜ ©ç¤›œ© £œ á¢¢¦ ©ç©«£˜
£â©à › ¡«ç¦¬: [K[0m} T Asking for User-Id, live channel






 When a user on one of the free sample channels enters a
 User-Id that your BBS does not recognize, he is asked for
 his User-Id again with this message.

UIDNOG {[0;1;31m
€¬«æ «¦ ¯œ¬›é¤¬£¦ ›œ¤ œå¤˜  ¡˜«˜®à¨£â¤¦. ‹ã§àª ¡á¤˜«œ ¡á§¦ ¦ ¢áŸ¦ª;[0;1m
} T Bad User-Id, free sample channel

 When a user on one of the live channels enters a User-Id
 that your BBS does not recognize, he is asked for his
 User-Id again with this message.  He is told to call your
 free sample phone line (option DATAPH) if he does not
 already have an account.

LOGNOG {[0;1;31m
€¬«æ «¦ ¯œ¬›é¤¬£¦ ›œ¤ œå¤˜  ¡˜«˜®à¨£â¤¦. ‹ã§àª ¡á¤˜«œ ¡á§¦ ¦ ¢áŸ¦ª;[0;1m
} T Bad User-Id, live channel


 This user has entered a User-Id that is already online
 and using your BBS at this moment.  He is connected on a
 free sample channel, so we can tell him to type "new" if he
 does not already have an account.

ALRDON {[0;1m
€¬«æ «¦ ¯œ¬›é¤¬£¦ œå¤˜  ã› ©¬¤›œ›œ£â¤¦.

!J˜¨˜¡˜¢é œ¢âš¥«œ £˜å £˜ª «¤  › ¦¡«©å˜ «¦¬ ¯œ¬›à¤ç£¦¬ £§˜å¤¦¤«˜ª
éª ¤â¦ª ®¨ã©«ª, ¡˜  ˜­ã¤¦¤«˜ª £ã¤¬£˜ ©«¦¤ •œ ¨ ©«ã ‘¬©«ã£˜«¦ª ¢âš¦¤«˜ª
§¦ æ œå¤˜  «¦ ¡˜¤¦¤ ¡æ ©˜ª ¯œ¬›é¤¬£¦ ¡˜Ÿéª ¡˜  «¤ é¨˜ §¦¬ ©¬¤›œŸã¡˜«œ.!)

„¬®˜¨ ©«¦ç£œ §¦¬ ¡˜¢â©˜«œ.
} T User-Id already online, free sample channel

 This user has tried to enter a User-Id or a password three
 times already with no success (either there was no such
 User-Id, or it was already online, or the password was
 incorrect).  He is disconnected at the end of this message.

STRUKO {[0;1;31m
‚ ˜ «¨å« ­¦¨á ¡á¤˜«œ ¢áŸ¦ª.
‚ ˜ ¢æš¦¬ª ˜©­˜¢œå˜ª  ©ç¤›œ©ã ©˜ª › ˜¡æ§«œ«˜ .
˜¨˜¡˜¢é ¡˜¢â©«œ ¥˜¤á ˜¤ Ÿâ¢œ«œ ¤˜ ¥˜¤˜›¦¡ £á©œ«œ.
[0m} T Disconnect message after 3 bad User-Id's



 Users get one timeout for the login screen, and another, usually longer
 timeout in the MetaBBS client. This allows a weak denial of service attack
 by bouncing to and from MetaBBS. We obviously can't allow this, so any more
 than LOGINSTRIKES (not configurable, usually 3) bounces kick the user out
 with a polite message. This is that polite message. With the typical 1 and
 3 min timeout (for logins and MetaBBS respectively), this means that the
 line can only be held for 3*(1+3)=12 mins and that only if the cracker
 wannabe is using a stopwatch. :-)

METAKO {[0;1;31m
‘¬šš¤é£, š ˜ ¢æš¦¬ª ˜©­˜¢œå˜ª ›œ¤ £§¦¨¦ç£œ ¤˜ ©˜ª œ§ «¨â¯¦¬£œ ¤˜
©¬¤œ®å©œ«œ. ˜¨˜¡˜¢¦ç£œ ¥˜¤˜¡˜¢â©«œ æ«˜¤ ˜§¦­˜©å©œ«œ £œ §¦ ¦ ©ç©«£˜
Ÿâ¢œ«œ ¤˜ ©¬¤›œŸœå«œ. …«¦ç£œ ©¬šš¤é£ š ˜ «¤ «˜¢˜ §à¨å˜.
[0m} T Disconnect message after 3 bounces to/from the MetaBBS client



 When a user with a non-live account (an account to which
 credits have never been posted) tries to call on one of the
 lines reserved for live users only, he is told to call
 back on one of the free sample lines.  He is bumped off
 after this message.

 When a user whose account has been suspended tries to
 log on, they are notified of the suspension and told
 that they can write you at your stated address to find
 out why their account was suspended.

ACCSUS {[0;1m

!J •œ ¨ ©«ãª ‘¬©«ã£˜«¦ª â®œ  ˜­˜ ¨â©œ  §¨¦©à¨ ¤á «¤ ›¬¤˜«æ««á ©˜ª ¤˜ ¡á¤œ«œ
®¨ã© «¦¬ ¯œ¬›à¤ç£¦¬ ©˜ª ©«¤ @BBS@. ˜¨˜¡˜¢¦ç£œ §¨¦©§˜Ÿã©«œ ¤˜
œ§ ¡¦ ¤à¤ã©œ«œ £˜å £˜ª ©«¤ › œçŸ¬¤©!)

!C@COMPANY@,
@ADDRESS1@,
@ADDRESS2@,
@CITY@.!)

˜¨˜¡˜¢¦ç£œ ©«¤ œ§ ©«¦¢ã ©˜ª ¤˜ š¨á¯œ«œ ¡˜  «¦ ¯œ¬›é¤¬£¦ ©˜ª.

„¬®˜¨ ©«¦ç£œ §¦¬ ¡˜¢â©˜«œ.
} T User's account has been suspended


ACCDEL {[0;1m

!J •œ ¨ ©«ãª ‘¬©«ã£˜«¦ª â®œ  ˜­˜ ¨â©œ  «¤ ›¬¤˜«æ««á ©˜ª ¤˜ ¡á¤œ«œ
®¨ã© «¦¬ ¯œ¬›à¤ç£¦¬ ©˜ª ©«¤ @BBS@. ˜¨˜¡˜¢¦ç£œ §¨¦©§˜Ÿã©«œ ¤˜
œ§ ¡¦ ¤à¤ã©œ«œ £˜å £˜ª ©«¤ › œçŸ¬¤©!)

!C@COMPANY@,
@ADDRESS1@,
@ADDRESS2@,
@CITY@.!)

˜¨˜¡˜¢¦ç£œ ©«¤ œ§ ©«¦¢ã ©˜ª ¤˜ š¨á¯œ«œ ¡˜  «¦ ¯œ¬›é¤¬£¦ ©˜ª.

„¬®˜¨ ©«¦ç£œ §¦¬ ¡˜¢â©˜«œ.
} T User's account has been suspended


LOKOUT {[0;1m

!J’¦ œ§å§œ›æ ©˜ª (class) ›œ¤ ©˜ª œ§ «¨â§œ  ˜¬«ã «¤ ©« š£ã ¤˜ ©¬¤›œŸœå«œ ˜¬«ã
«¤ ©« š£ã ©«¤ @BBS@. ˜¨˜¡˜¢¦ç£œ §¨¦©§˜Ÿã©«œ ¤˜ œ§ ¡¦ ¤à¤ã©œ«œ £˜å £˜ª
©«¤ › œçŸ¬¤©!)

!C@COMPANY@,
@ADDRESS1@,
@ADDRESS2@,
@CITY@.!)

˜¨˜¡˜¢¦ç£œ ©«¤ œ§ ©«¦¢ã ©˜ª ¤˜ š¨á¯œ«œ ¡˜  «¦ ¯œ¬›é¤¬£¦ ©˜ª.

„¬®˜¨ ©«¦ç£œ §¦¬ ¡˜¢â©˜«œ.
} T User's class forbids logins


NOKEY {[0;1m

!J† š¨˜££ã §¦¬ ¡˜¢â©˜«œ â®œ  §œ¨ ¦¨ ©£â¤ §¨æ©™˜©. ƒ¬©«¬®éª ›œ¤ £§¦¨¦ç£œ ¤˜
©˜ª œ§ «¨â¯¦¬£œ ¤˜ ©¬¤›œŸœå«œ. ˜¨˜¡˜¢¦ç£œ ›¦¡ £á©«œ ¡á§¦ ˜ ˜§æ « ª  á¢¢œª
š¨˜££âª «ª @BBS@. „¬®˜¨ ©«¦ç£œ §¦¬ ¡˜¢â©˜«œ.!)

} T User doesn't have the proper key to login


BBSOFF {[0;1m

!J…«¦ç£œ ©¬šš¤é£, ˜¢¢á  @BBS@ œå¤˜  ˜¬«ã «¤ ©« š£ã œ¡«æª ¢œ «¦¬¨šå˜ª
š ˜ ©£˜¤« ¡âª œ¨š˜©åœª. ˜¨˜¡˜¢¦ç£œ ¡˜¢â©«œ ˜¨šæ«œ¨˜. …«¦ç£œ ©¬šš¤é£ ¡˜ 
§á¢  š ˜ «¤ «˜¢˜ §à¨å˜.!)

„¬®˜¨ ©«¦ç£œ §¦¬ ¡˜¢â©˜«œ.

} T BBS is currently off-line for maintenance

 After a user has correctly entered his User-Id, he is asked
 for his password with this prompt.  Echo is disabled after
 this prompt to hide the password from observers.

ENTPSW {[0;1m
˜¨˜¡˜¢é ›é©«œ «¦ ©ç¤Ÿ£á ©˜ª: [K[0m} T Asking for password

 When the user enters an incorrect password he is given this
 message, and another chance to enter his password.

PSWNOG {[0;1;31m
‰á¤˜«œ ¢áŸ¦ª.
[0;1m} T Bad password


 This message is given to all users when they log onto The
 Major BBS.  A user has logged on when he has correctly
 entered his User-Id and his password.


GREETINGS {[2J[0;1m‰˜¢à©ã¢Ÿ˜«œ ©«¤ [36m@BBS@[37m, %s!

[36m„®œ«œ ©¬¤›œŸœå [33m@NUMCONNS@[36m ­¦¨âª.
[37m† «œ¢œ¬«˜å˜ ©˜ª ©ç¤›œ© ã«˜¤ «¤ [33m@DATELAST@[37m.

} T Log-on greeting message


NEWGREET {[2J[0;1m‰˜¢©ã¢Ÿ˜«œ ©«¤ [36m@BBS@[37m, %s!

} T Log-on greeting message, new user


WARNING: IT IS AGAINST THE GNU PUBLIC LICENSE (GPL) TO REMOVE OR ALTER THIS
NOTICE IN ANY WAY. BY DOING SO YOU TERMINATE YOUR LICENSE AGREEMENT AND THE
RIGHTFUL OWNERS OF THIS SOFTWARE MAY AND WILL TAKE LEGAL ACTION AGAINST YOU.

GPL {[0;1m
!J@SHORTVERSION@ Copyright (c) 1994-2000 €¢â¥ ¦ª •¦ç®¦¬¢˜ª
<alexios@@vennea.demon.co.uk>. [32m ‹âš ©«¦ª â¨®œ«˜ 
®à¨åª [37m‰€‹‹ˆ€ €Š“’—‘ „‚‚“†‘†[32m. ’¦ §˜¨æ¤ œå¤˜  œ¢œçŸœ¨¦ ¢¦š ©£ ¡æ.
„å©«œ œ¬§¨æ©›œ¡«¦  ¤˜ «¦ › ˜¡ ¤ã©œ«œ [37m¬§æ ¦¨ ©£â¤¦¬ª æ¨¦¬ª[32m. ‚¨á¯«œ
[33m/GPL[32m š ˜ §œ¨ ©©æ«œ¨œª §¢¨¦­¦¨åœª.!)

[0;1m} T GPL report. DO NOT REMOVE OR ALTER IN ANY WAY


 This user has confirmed his desire to log off.  He is
 reminded of the name of your BBS (option BBSTTL).

SEEYA {[0;1;36m!Z

†[31m @BBS@ [37m©˜ª œ¬®˜¨ ©«œå §¦¬ £œå¤˜«œ £˜å «ª š ˜ @ONLINE@ ¢œ§«á.
„¢§å¦¬£œ ¤˜ â®¦¬£œ «¤ ®˜¨á ¤˜ ©˜ª ¥˜¤˜›¦ç£œ ©ç¤«¦£˜.!)


[0m
} T Logoff goodbye message


TIMEOUT {

!JŠ¬§á£˜ , ˜¢¢á ›œ¤ £§¦¨¦ç£œ ¤˜ ¡¨˜«á£œ «¤ š¨˜££ã ˜¤¦ ¡«ã š ˜ §á¤à ˜§æ â¤˜
¢œ§«æ, £â®¨  ¤˜ £áŸ¦¬£œ «˜ ©«¦ ®œå˜ ©˜ª. ˜¨˜¡˜¢é ¥˜¤˜¡˜¢â©«œ æ«˜¤ œå©«œ ©œ
Ÿâ© ¤˜ «˜ ›é©œ«œ.!)


[0m} T User timed out while logging in


LANG {} T

DESCR {Entering the system} S 43 Area description for login stuff

LDOWN {

@BBS@

We're sorry, this line is deactivated...

} T Line is down, hanging up


XLATEM {[0;1m
Before we start, we'd like to know what kind of character set you have.
If you aren't going to be using Greek on this system, try options 3 or 4.

[33m1[37m. [32mGreek 437G/737 ã ©¬£™˜«æ font[37m. €¤ £§¦¨œå«œ ¤˜ › ˜™á©œ«œ ˜¬«æ «¦
   ¡œå£œ¤¦, «æ«œ ›é©«œ '[33m1[37m'.

[33m2[37m. [32mCodepage 928, ÅËÏÔ-928 Ş ISO-8859-7[37m. Áí ìğïñåßôå íá äéáâÜóåôå áõôü ôï
   êåßìåíï, ôüôå äşóôå '[33m2[37m'.

[33m3[37m. [32mIBM PC extended ASCII without Greek[37m. Enter '[33m3[37m' if the following characters
   appear as three rectangles of different shades: °° ±± ²²

[33m4[37m. [32m7-bit ASCII[37m. Choose this encoding if none of the above encodings are
   suitable for you.

Please enter your option. ([33m1[37m,[33m2[37m,[33m3[37m,[33m4[37m) [Enter=%d]: } T Before login, ask about character set translation


XLATEE {
You have to choose one of the translation methods below.

} T Invalid option


 This is the string output when ANSIOP is set to AUTO,
 to solicit from the user's terminal emulator the ANSI
 "cursor position report" sequence.

SANSI {[0;1m
Connected. Please stand by.
} T Auto-sensing ANSI

 This question is only used if you have answered "ASK" as
 the value of parameter ANSIOP: "Initial ANSI setting at
 start of session".  The question is asked before the
 HELLO message even appears, so that you can conditionally
 display ANSI graphics as part of your system-ID, if you
 like.  (Note that the preferred method for determining
 this is to set ANSIOP to AUTO, however.)

QANSI {

!C[0;1;31m  ÛÛÛ[32m  ÛÛÛ[34m  ÛÛÛ  [37m!)

!JIf the three blocks above display in colour, or different shades of
grey, answer Y to the following prompt. Otherwise, enter N.!)

!WWould you like ANSI graphics? ([Y]es / [N]o) !)} T T Display ANSI graphics question


QANSIERR {
!WPlease answer the question with either Y or N.!)

} T Rebuff, wrong answer to ANSI question


 This message is given to users when they first connect to
 The Major BBS.  It tells them the title of your BBS, your
 registration number, their baud rate, and the time and
 date.

 This message comes immediately BEFORE any special log-on
 message that may have been set from the Sysop console of
 The Major BBS.

             Tap F2 to view or edit this text.

HELLO {[2J[0;1m@VERSION@.

[0;1;30m[37C[0;1mÛ[0mÛÛÛÛ     Welcome to Megistos BBS
[36C[1mÛÛÛ[0mÛÛÛÛ   Name: @BBS@
[35C[1mÛÛÛÛÛ[0mÛÛÛÛ   Speed: @BAUD@ bps
[34C[1mÛÛÛÛÛÛÛ[0mÛÛÛÛ   Time/Date: @TIME@ @DATE@
[33C[1mÛÛÛÛ[30mÛ[37mÛÛÛÛ[0mÛÛÛÛ
[32C[1mÛÛÛÛ[30mÛÛÛ[37mÛÛÛÛ[0mÛÛÛÛ
[31C[1mÛÛÛÛ[30mÛÛÛÛ [37mÛÛÛÛ[0mÛÛÛÛ
[30C[1mÛÛÛÛ[30mÛÛÛÛ   [37mÛÛÛÛ[0mÛÛÛÛ
[29C[1mÛÛÛÛ[30mÛÛÛÛ[5C[37mÛÛÛÛ[0mÛÛÛÛ
[28C[1mÛÛÛÛ[30mÛÛÛÛ[7C[37mÛÛÛÛ[0mÛÛÛÛ
[27C[1mÛÛÛÛ[30mÛÛÛÛ[9C[37mÛÛÛÛ[0mÛÛÛÛ
[26C[1mÛÛÛÛ[30mÛÛÛÛ[11C[37mÛÛÛÛ[0mÛÛÛÛ
[25C[1mÛÛÛÛ[30mÛÛÛÛ[13C[37mÛÛÛÛ[0mÛÛÛÛ
[24C[1mÛÛÛÛ[30mÛÛÛÛ[15C[37mÛÛÛÛ[0mÛÛÛÛ
[23C[1mÛÛÛÛ[30mÛÛÛÛ[0mÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ
[22C[1mÛÛÛÛ[30mÛÛÛÛ[0mÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ
[22C[1mÛÛÛ[30mÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ
[23C[37mÛ[30mÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ

[24C[37mP R O J E C T   M E G I S T O S[0;1m
} T Greeting message when user first connects to the BBS


THELLO {[2J[0;1m@VERSION@.

[0;1;30m[37C[0;1mÛ[0mÛÛÛÛ     Welcome to Megistos BBS
[36C[1mÛÛÛ[0mÛÛÛÛ   Name: @BBS@
[35C[1mÛÛÛÛÛ[0mÛÛÛÛ   Speed: @BAUD@ bps
[34C[1mÛÛÛÛÛÛÛ[0mÛÛÛÛ   Time/Date: @TIME@ @DATE@
[33C[1mÛÛÛÛ[30mÛ[37mÛÛÛÛ[0mÛÛÛÛ   Telnet line: @TNLNUM@/@TNLMAX@
[32C[1mÛÛÛÛ[30mÛÛÛ[37mÛÛÛÛ[0mÛÛÛÛ
[31C[1mÛÛÛÛ[30mÛÛÛÛ [37mÛÛÛÛ[0mÛÛÛÛ
[30C[1mÛÛÛÛ[30mÛÛÛÛ   [37mÛÛÛÛ[0mÛÛÛÛ
[29C[1mÛÛÛÛ[30mÛÛÛÛ[5C[37mÛÛÛÛ[0mÛÛÛÛ
[28C[1mÛÛÛÛ[30mÛÛÛÛ[7C[37mÛÛÛÛ[0mÛÛÛÛ
[27C[1mÛÛÛÛ[30mÛÛÛÛ[9C[37mÛÛÛÛ[0mÛÛÛÛ
[26C[1mÛÛÛÛ[30mÛÛÛÛ[11C[37mÛÛÛÛ[0mÛÛÛÛ
[25C[1mÛÛÛÛ[30mÛÛÛÛ[13C[37mÛÛÛÛ[0mÛÛÛÛ
[24C[1mÛÛÛÛ[30mÛÛÛÛ[15C[37mÛÛÛÛ[0mÛÛÛÛ
[23C[1mÛÛÛÛ[30mÛÛÛÛ[0mÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ
[22C[1mÛÛÛÛ[30mÛÛÛÛ[0mÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ
[22C[1mÛÛÛ[30mÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ
[23C[37mÛ[30mÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛÛ

[24C[37mP R O J E C T   M E G I S T O S[0;1m
} T Greeting message for telnet connections


TFULL {

@BBS@

We're sorry, but all @TNLMAX@ of our telnet lines are currently occupied.
Please try again later. We apologise for the inconvenience.

} T All telnet lines full, cannot connect


ENTUSID {[0;1m
Please enter your user ID.
If you're a new user, enter "[33mnew[0;1m" (without quotes): [K[0m} T Asking for User-Id, free sample channel

 This is the first question asked of any user accessing your
 BBS on one of your "live" reserved channels.  This is a
 channel whose channel number is greater than or equal to
 the value of the NSAMPLN option.  These channels only allow
 users to log on who already have an account and whose
 account is "live" (has had credits posted to it).

 This message (if given) comes immediately AFTER the log-on
 message that may have been set from the Sysop console of
 The Major BBS.

LOGUID {[0;1;33m
If you are a new user, please call one of our signup lines, 8231753 or 8815616[37m

Please enter your user ID: [K[0m} T Asking for User-Id, live channel

 When a user on one of the free sample channels enters a
 User-Id that your BBS does not recognize, he is asked for
 his User-Id again with this message.

UIDNOG {[0;1;31m
This user ID is not registered. Please re-enter your user ID.[0;1m
} T Bad User-Id, free sample channel

 When a user on one of the live channels enters a User-Id
 that your BBS does not recognize, he is asked for his
 User-Id again with this message.  He is told to call your
 free sample phone line (option DATAPH) if he does not
 already have an account.

LOGNOG {[0;1;31m
This user ID is not registered. Please re-enter your user ID.[0;1m
} T Bad User-Id, live channel


 This user has entered a User-Id that is already online
 and using your BBS at this moment.  He is connected on a
 free sample channel, so we can tell him to type "new" if he
 does not already have an account.

ALRDON {[0;1m
A user with this User ID is already connected to the system.

!JPlease check ownership of the user ID with us by signing up as a new
user, and leaving a message to the System Operator, specifying your normal
user ID, and the time and date of your attempted connection.!)

Thank you for calling.
} T User-Id already online, free sample channel

 This user has tried to enter a User-Id or a password three
 times already with no success (either there was no such
 User-Id, or it was already online, or the password was
 incorrect).  He is disconnected at the end of this message.

STRUKO {[0;1;31m
You have entered incorrect data for the third time.
Your connection is terminated for security reasons.
Please call back if you want to try again.
[0m} T Disconnect message after 3 bad User-Id's

 When a user with a non-live account (an account to which
 credits have never been posted) tries to call on one of the
 lines reserved for live users only, he is told to call
 back on one of the free sample lines.  He is bumped off
 after this message.

 When a user whose account has been suspended tries to
 log on, they are notified of the suspension and told
 that they can write you at your stated address to find
 out why their account was suspended.

ACCSUS {[0;1m

!JThe System Operator is temporarily denying you access to @BBS@.
Please contact us at the following address:!)

!C@COMPANY@,
@ADDRESS1@,
@ADDRESS2@,
@CITY@.!)

Please specify your User ID in your letter.

Thank you for calling.
} T User's account has been suspended


ACCDEL {[0;1m

!JThe System Operator is denying you access to @BBS@.
Please contact us at the following address:!)

!C@COMPANY@,
@ADDRESS1@,
@ADDRESS2@,
@CITY@.!)

Please specify your User ID in your letter.

Thank you for calling.
} T User's account has been suspended


LOKOUT {[0;1m

!JYour user class does not allow access to @BBS@ at this time. Please
contact us at the following address:!)

!C@COMPANY@,
@ADDRESS1@,
@ADDRESS2@,
@CITY@.!)

Please specify your user ID in your letter.

Thank you for calling.
} T User's class forbids logins


NOKEY {[0;1m

!JThe line you called has restricted access. Unfortunately, we are unable
to allow you to login. Please try one of @BBS@'s other lines. Thank you for
calling.!)

} T User doesn't have the proper key to login


BBSOFF {[0;1m

!JWe're sorry, but @BBS@ is currently off-line for important maintenance
operations. Please call back later. We apologise for the inconvenience.!)

Thank you for calling.

} T BBS is currently off-line for maintenance

 After a user has correctly entered his User-Id, he is asked
 for his password with this prompt.  Echo is disabled after
 this prompt to hide the password from observers.

ENTPSW {[0;1m
Please enter your password: [K[0m} T Asking for password

 When the user enters an incorrect password he is given this
 message, and another chance to enter his password.

PSWNOG {[0;1;31m
That is not the correct password.
[0;1m} T Bad password

 This message is given to all users when they log onto The
 Major BBS.  A user has logged on when he has correctly
 entered his User-Id and his password.


GREETINGS {[2J[0;1mWelcome to [36m@BBS@[37m, %s!
} T Log-on greeting message


WARNING: IT IS AGAINST THE GNU PUBLIC LICENSE (GPL) TO REMOVE OR ALTER THIS
NOTICE IN ANY WAY. BY DOING SO YOU TERMINATE YOUR LICENSE AGREEMENT AND THE
RIGHTFUL OWNERS OF THIS SOFTWARE MAY AND WILL TAKE LEGAL ACTION AGAINST YOU.

GPL {[0;1m
!J@SHORTVERSION@ Copyright (c) 1994-2000 Alexios Chouchoulas
<alexios@@vennea.demon.co.uk>. [32mMegistos comes
with [37mABSOLUTELY NO WARRANTY[32m. This is free software and you are
welcome to redistribute it under [37mcertain conditions[32m. Type
[33m/GPL[32m for more information.!)

[0;1m} T GPL report. DO NOT REMOVE OR ALTER IN ANY WAY


SEEYA {[0;1;36m!Z

[31m @BBS@ [37mthanks you for staying with us for @ONLINE@ minutes.
We hope to see you again soon.!)


[0m
} T Logoff goodbye message


TIMEOUT {

!JWe're sorry, but we can't maintain the connection for more than one
minute, unless you log in. Please call back when you are ready to do so.!)


[0m} T User timed out while logging in


LANGEND {}

