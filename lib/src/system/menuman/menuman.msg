LEVEL2 {}

 Credits are purchased by users to permit them "live"
 connect time on The Major BBS.  They are consumed,
 typically, at the rate of 1 per minute.  You may
 change this value to adjust the default "cost" to
 users of using your system. Please note that the 
 consumption unit is credits per 100 minutes, not
 credits per minute! So, for the standard charge of
 1 credit/min, you should fill in this field with
 the value '100' (100 creds/100 mins, 1 cred/min)

DEFCCR {Credits per 100 minutes consumed at the Main menu 100} N 0 32767


TOPPAG {TOP} S 16 Name of the default top-level page

EXTPAG {EXIT} S 16 Name of the 'exit' page


 Do you want the menuman to display the ordinary short
 menu or just a short prompt right after displaying a full
 menu?

USESHM {What do we display after a long menu? PROMPT} E SHORT PROMPT


 Do you want to show the short or full menu when RETURN
 is pressed?

RETMENU {Which menu type to use after Return key pressed? SHORT} E SHORT LONG


 Do you want to display the short or full menu when exit-
 int from another page?

EXTMENU {Display what menu type when exiting from another page? SHORT} E SHORT LONG


RELOGSTG {rel} S 20 'Relogon' command string


KEYREL {Key required to use the relogon command: 12} N 0 129


LEVEL3 {}



DEFDESCR {‰œ¤«¨ ¡æ £œ¤¦ç œ§ ¢¦šé¤} S 40 Default menuman description


XITDESCR {„¥¦›¦ª, ’â¢¦ª ®¨ã©ª} S 40 Logout menuman description


MENPRO {} T Menu prologue

MENEPI {[0;1;32m
‘œ¢å›˜: [37m@PAGE@[0;1m} T Menu epilogue

SHMBEG {[0;1;32m
‘œ¢å›˜: [37m@PAGE@
!Wƒé©«œ «¤ œ§ ¢¦šã ©˜ª (} T Short menu starting prompt

SHMOPT {[33m%c[37m,} T Short menu option 

SHMLOP {[33m%c[37m,} T Short menu last option 

SHMEND { ã [33m?[37m š ˜ £œ¤¦ç): [0m!)} T Short menu ending prompt


SHMPRM {
!W[0;1mƒé©«œ «¤ œ§ ¢¦šã ©˜ª ([33m?[37m š ˜ £œ¤¦ç): [0m!)} T Short menu prompt


ERRSEL {
[0;31;1mŠ¬§á£˜ , ›œ¤ ¬§á¨®œ  œ§ ¢¦šã "%c" ©«¤ ©œ¢å›˜ @PAGE@.
[0;1m} T Incorrect selection


NOAXES1 {
[0;31;1mŠ¬§á£˜ ,  ©œ¢å›˜ %s ›œ¤ ¬§á¨®œ .
[0;1m} T You don't have access to that page


NOAXES2 {
[0;31;1mŠ¬§á£˜ , ›œ¤ â®œ«œ §¨æ©™˜© ©«¤ œ§ ¢¦šã "%c".
[0;1m} T You don't have access to that menu option


CANTXEC {
!J[0;31;1mŠ¬§á£˜ , ›œ¤ £§æ¨œ©œ ¤˜ ­¦¨«àŸœå  ©œ¢å›˜ @PAGE@.
˜¨˜¡˜¢¦ç£œ œ ›¦§¦ ã©«œ «¦¤ •œ ¨ ©«ã ‘¬©«ã£˜«¦ª š ˜ « ª
©¬¤Ÿã¡œª ¡á«à ˜§æ « ª ¦§¦åœª ›£ ¦¬¨šãŸ¡œ «¦ ¢áŸ¦ª.!)
[0;1m} T Unable to spawn module/program


 When a user makes the "exit" selection from the Main Menu
 (option XITSEL), we confirm his request with this message.
 If he types 'Y' in response to THIS message, he is logged
 off.  If he types anything else, he is returned to the
 short main menu (letters only).

 This text applies to non-live users, who are not offered
 the option of R for "re-logon".

RUSXITN {[0;5;1m
‡â¢œ«œ §¨˜š£˜« ¡á ¤˜ › ˜¡æ¯œ«œ «¤ ©ç¤›œ©;
[0;1;31m
([[33mY[31m~]es=¤˜å / [[33mN[31m~]o=æ® ) [0m } T Main menu exit:  confirm logoff

 When a user makes the "exit" selection from the Main Menu
 (option XITSEL), we confirm his request with this message.
 If he types 'Y' in response to THIS message, he is logged
 off.  If he types anything else, he is returned to the
 short main menu (letters only).

 This text applies to live users, who are offered the
 option to "re-logon" by entering an 'R' at this prompt.

RUSXITL {[0;5;1m
‡â¢œ«œ §¨áš£˜«  ¤˜ › ˜¡æ¯œ«œ ˜¬«ã «¤ ©ç¤›œ©;
[0;1;31m
([[33mY[31m~]es=¤˜å / [[33mN[31m~]o=æ® )[1;37m: } T Main menu exit:  confirm logoff

