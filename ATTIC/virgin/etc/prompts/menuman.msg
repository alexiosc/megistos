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



DEFDESCR {�������� ����� �������} S 40 Default menuman description


XITDESCR {������, �⢦� ��㩞�} S 40 Logout menuman description


MENPRO {} T Menu prologue

MENEPI {[0;1;32m
���囘: [37m@PAGE@[0;1m} T Menu epilogue

SHMBEG {[0;1;32m
���囘: [37m@PAGE@
!W�驫� ��� ������� ��� (} T Short menu starting prompt

SHMOPT {[33m%c[37m,} T Short menu option 

SHMLOP {[33m%c[37m,} T Short menu last option 

SHMEND { � [33m?[37m ��� �����): [0m!)} T Short menu ending prompt


SHMPRM {
!W[0;1m�驫� ��� ������� ��� ([33m?[37m ��� �����): [0m!)} T Short menu prompt


ERRSEL {
[0;31;1m���ᣘ�, ��� ��ᨮ�� ������� "%c" ���� ���囘 @PAGE@.
[0;1m} T Incorrect selection


NOAXES1 {
[0;31;1m���ᣘ�, � ���囘 %s ��� ��ᨮ��.
[0;1m} T You don't have access to that page


NOAXES2 {
[0;31;1m���ᣘ�, ��� ⮜�� ��橙��� ���� ������� "%c".
[0;1m} T You don't have access to that menu option


CANTXEC {
!J[0;31;1m���ᣘ�, ��� ��樜�� �� �������� � ���囘 @PAGE@.
��������磜 �������㩫� ��� �������� ����㣘��� ��� ���
����㡜� ��� ��� ��� ���圪 ��������㟞�� �� �៦�.!)
[0;1m} T Unable to spawn module/program


 When a user makes the "exit" selection from the Main Menu
 (option XITSEL), we confirm his request with this message.
 If he types 'Y' in response to THIS message, he is logged
 off.  If he types anything else, he is returned to the
 short main menu (letters only).

 This text applies to non-live users, who are not offered
 the option of R for "re-logon".

RUSXITN {[0;5;1m
�⢜�� ���������� �� ����毜�� ��� �礛���;
[0;1;31m
([[33mY[31m~]es=��� / [[33mN[31m~]o=殠) [0m } T Main menu exit:  confirm logoff

 When a user makes the "exit" selection from the Main Menu
 (option XITSEL), we confirm his request with this message.
 If he types 'Y' in response to THIS message, he is logged
 off.  If he types anything else, he is returned to the
 short main menu (letters only).

 This text applies to live users, who are offered the
 option to "re-logon" by entering an 'R' at this prompt.

RUSXITL {[0;5;1m
�⢜�� ��ᚣ��� �� ����毜�� ���� ��� �礛���;
[0;1;31m
([[33mY[31m~]es=��� / [[33mN[31m~]o=殠)[1;37m: } T Main menu exit:  confirm logoff


LANG {}

DEFDESCR {Main menu} S 40 Default menuman description


XITDESCR {Logging out} S 40 Logout menuman description


MENPRO {} T Menu prologue

MENEPI {[0;1;32m
Page: [37m@PAGE@[0;1m} T Menu epilogue

SHMBEG {[0;1;32m
Page: [37m@PAGE@
!WPlease enter your choice (} T Short menu starting prompt

SHMOPT {[33m%c[37m,} T Short menu option 

SHMLOP {[33m%c[37m,} T Short menu last option 

SHMEND { or [33m?[37m for the menu): [0m!)} T Short menu ending prompt


SHMPRM {
!W[0;1mPlease enter your choice ([33m?[37m for the menu): [0m!)} T Short menu prompt


ERRSEL {
[0;31;1mSorry, "%c" isn't a valid choice here.
[0;1m} T Incorrect selection


NOAXES1 {
[0;31;1mSorry, page "%s" doesn't exist.
[0;1m} T You don't have access to that page


NOAXES2 {
[0;31;1mSorry, you don't have access to option "%c".
[0;1m} T You don't have access to that menu option


CANTXEC {
!J[0;31;1mSorry, page @PAGE@ could not be loaded.
Please notify the System Operator of the circumstances
leading up to this.!)
[0;1m} T Unable to spawn module/program


 When a user makes the "exit" selection from the Main Menu
 (option XITSEL), we confirm his request with this message.
 If he types 'Y' in response to THIS message, he is logged
 off.  If he types anything else, he is returned to the
 short main menu (letters only).

 This text applies to non-live users, who are not offered
 the option of R for "re-logon".

RUSXITN {[0;1m
!WDo you really want to disconnect? ([[33mY[31m~]es / [[33mN[31m~]o):!)[0m } T Main menu exit:  confirm logoff

 When a user makes the "exit" selection from the Main Menu
 (option XITSEL), we confirm his request with this message.
 If he types 'Y' in response to THIS message, he is logged
 off.  If he types anything else, he is returned to the
 short main menu (letters only).

 This text applies to live users, who are offered the
 option to "re-logon" by entering an 'R' at this prompt.

RUSXITL {[0;1m
!WDo you really want to disconnect? ([[33mY[31m~]es / [[33mN[31m~]o /
[[33mR[31m~]elogon as another user):!)[0m } T Main menu exit: confirm logoff (with relogon)




LANGEND {}
