LEVEL2 {}

LONALRM {Minutes before bbslogin timeout (0=disable): 1} N 0 32767

TERMINAL {linux} S 32 Default terminal type of BBS channels

METAB4 {If available, run MetaBBS client before the local BBS' login screen? NO} B

METALG {If available, enable OUT command to run MetaBBS client at login? YES} B

UNIXUID {bbsuser} S 8 UNIX UID used for BBS users? (name or numerical)



LEVEL3 {}

DESCR {�婦��� ��� �ᩞ} S 43 Area description for login stuff

LDOWN {

@BBS@

���ᣘ�, ���� � ������ �夘� �������������⤞...

} T Line is down, hanging up


XLATEM {[0;1m
���� �����㩦���, �� �⢘�� �� �⨘�� �� �囦�� ������������� ⮜��.
Before we start, we'd like to know what kind of character set you have.

[33m1[37m. [32mGreek 437G/737[37m � ������� font. �� �����嫜 �� ����ᩜ�� ���� ��
   ��壜��, �櫜 �驫� '[33m1[37m'.

[33m2[37m. [32mCodepage 928, ����-928 � ISO-8859-7[37m. �� �������� �� ��������� ���� ��
   �������, ���� ����� '[33m2[37m'.

[33m3[37m. [32mIBM PC extended ASCII, xwris Ellhnika[37m. Dwste '[33m3[37m' an oi akolouthoi
   xarakthres emfanizontai ws tria orthogwnia diaforetikwn tonwn: �� �� ��

[33m4[37m. [32m7-bit ASCII[37m. Dialejte ayth thn epilogh an tipota apo ta parapanv den sas
   einai katallhlo.

�驫� ��� ������� ���.
Please enter your option. ([33m1[37m,[33m2[37m,[33m3[37m,[33m4[37m) [Enter=%d]: [0m} T Before login, ask about character set translation


XLATEE {
��⧜� �� ����⥜�� �� ��� ��� ������� ���曦�� ���᭨����.
You have to choose one of the translation methods below.

} T Invalid option


 This is the string output when ANSIOP is set to AUTO,
 to solicit from the user's terminal emulator the ANSI
 "cursor position report" sequence.

SANSI {[0;1m
�礛��� �������. �������� �����⤜��.
} T Auto-sensing ANSI

 This question is only used if you have answered "ASK" as
 the value of parameter ANSIOP: "Initial ANSI setting at
 start of session".  The question is asked before the
 HELLO message even appears, so that you can conditionally
 display ANSI graphics as part of your system-ID, if you
 like.  (Note that the preferred method for determining
 this is to set ANSIOP to AUTO, however.)


QANSI {

!C[0;1;31m  ���[32m  ���[34m  ���  [37m!)

!J�� �� ��� �����餠� ��� ��� �����坦���� ⚮�ࣘ � �� ������������
�椦�� ��� ���坦�, �����㩫� �� Y ���� ��髞��. �����, �驫� N.!)

�⢜�� ANSI �������; ([Y]es=��� / [N]o=殠) } T Display ANSI graphics question


QANSIERR {
�������� �����㩫� ���� ��髞�� �� Y � N.

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

HELLO {[2J[0;1m���� 㨟��� ���� [1;33;5m@BBS@[0;1m.
��⮦��� [33m@VERSION@[0;1m.
[0;1m������㡘�� ��� @BAUD@ baud ��� @TIMESEC@ ��� @DATE@
[0;1;44m     �� ����嫜�� ���� ��� ���੦�坦��� ��� �填�� [36mAcroBase[37m &  [33mG[37m.[33mA[37m.[32mT[37m.[33mE[37m.     [40m
[36m ��������������������������������������������������������������������������[0;36m�
[1m �                 ��                [33m����� ��  ������  [34m�������[33m ������      [0;36m�
[1m �     ����������� �� ��������      [33m��������� �������� [34m�������[33m��������     [0;36m�
[1m �     ��[7C�� ��[7C��      [33m��     ��  ������� [34m��[33m     ��������     [0;36m�
[1m �     ��[7C�� ��[7C��      [33m��������� �������� [34m��[33m     �������      [0;36m�
[1m �     ��[7C�� ��[7C��       [33m�������� ���������[34m���[33m    ��������     [0;36m�
[1m �     �������� �� �����������      [33m��[36m     [33m��  ����� �� [34m��[33m     ������      [0;36m�
[1m �              ��                  [33m���������[34m�������������������������     [0;36m�
[1m �[0;36m��������������������������������������������������������������������������
[1;37;44m    Data : (01) 8231753 8815616 8816312 8220610 8819963  [31mwww.acrogate.org    [40m
[36;44m     telnet://acrogate.org:1024 [37m([36mAcro[37m)[36m telnet://acrogate.org:1025 [37m([33mGATE[37m)     [40m
[33;44m    Secure Shell ssh2 -C sshbbs acrogate.org � ssh -C sshbbs acrogate.org    [40m
} T Greeting message when user first connects to the BBS


THELLO {[2J[0;1m���� 㨟��� ���� [1;33;5m@BBS@[0;1m.
��⮦��� [33m@VERSION@[0;1m.
[0;1m������㡘�� ��� telnet ��� @TIMESEC@ ��� @DATE@
��������ᤜ�� ��� @TNLNUM@� ��� ��� @TNLMAX@ ����⩠��� telnet ������.
[0;1;44m     �� ����嫜�� ���� ��� ���੦�坦��� ��� �填�� [36mAcroBase[37m &  [33mG[37m.[33mA[37m.[32mT[37m.[33mE[37m.     [40m
[36m ��������������������������������������������������������������������������[0;36m�
[1m �                 ��                [33m����� ��  ������  [34m�������[33m ������      [0;36m�
[1m �     ����������� �� ��������      [33m��������� �������� [34m�������[33m��������     [0;36m�
[1m �     ��[7C�� ��[7C��      [33m��     ��  ������� [34m��[33m     ��������     [0;36m�
[1m �     ��[7C�� ��[7C��      [33m��������� �������� [34m��[33m     �������      [0;36m�
[1m �     ��[7C�� ��[7C��       [33m�������� ���������[34m���[33m    ��������     [0;36m�
[1m �     �������� �� �����������      [33m��[36m     [33m��  ����� �� [34m��[33m     ������      [0;36m�
[1m �              ��                  [33m���������[34m�������������������������     [0;36m�
[1m �[0;36m��������������������������������������������������������������������������
[1;37;44m    Data : (01) 8231753 8815616 8816312 8220610 8819963  [31mwww.acrogate.org    [40m
[36;44m     telnet://acrogate.org:1024 [37m([36mAcro[37m)[36m telnet://acrogate.org:1025 [37m([33mGATE[37m)     [40m
[33;44m    Secure Shell ssh2 -C sshbbs acrogate.org � ssh -C sshbbs acrogate.org    [40m
} T Greeting message for telnet connections


TFULL {

@BBS@

����磘���, ���� ��� �� @TNLMAX@ telnet ������ ��� �夘� ���������⤜� ����
��� ������. ��������磜 �����������㩫� ���櫜��. ����磜 �����飞 ��� ���
��������.

} T All telnet lines full, cannot connect


 This message (if given) comes immediately AFTER the log-on
 message that may have been set from the Sysop console of
 The Major BBS.

ENTUSID {[0;1m
�������� �驫� �� ����餬�� ���.
�� �婫� �⦪ ��㩫�� �驫� "[33mnew[0;1m" (��� ����������): [K[0m} T Asking for User-Id, free sample channel


 This is the first question asked of any user accessing your
 BBS on one of your "live" reserved channels.
 These channels only allow
 users to log on who already have an account.

 This message (if given) comes immediately AFTER the log-on
 message that may have been set from the Sysop console of
 The Major BBS.

LOGUID {[0;1;33m
�� �婫� �⦪ ��㩫��, ��������磜 ���⩫� ��� ����घ 8231753 ��� 8815616[37m

��������磜 �驫� �� ����餬�� ���: [K[0m} T Asking for User-Id, live channel



ENTUSIDM {[0;1m
�������� �驫� �� ����餬�� ���, � [33mout[0;1m ��� �礛��� �� ��� GATE
��� ����禬. �� �婫� �⦪ ��㩫�� �驫� [33mnew[0;1m: [K[0m} T Asking for User-Id, free sample channel

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
�� �婫� �⦪ ��㩫��, ��������磜 ���⩫� ��� ����घ 8231753 ��� 8815616[37m

��������磜 �驫� �� ����餬�� ���, � [33mout[0;1m ��� �礛��� �� ᢢ� �穫���
��� ����禬: [K[0m} T Asking for User-Id, live channel






 When a user on one of the free sample channels enters a
 User-Id that your BBS does not recognize, he is asked for
 his User-Id again with this message.

UIDNOG {[0;1;31m
���� �� ����餬�� ��� �夘� �����ਞ�⤦. ��� �ᤘ�� �᧦�� �៦�;[0;1m
} T Bad User-Id, free sample channel

 When a user on one of the live channels enters a User-Id
 that your BBS does not recognize, he is asked for his
 User-Id again with this message.  He is told to call your
 free sample phone line (option DATAPH) if he does not
 already have an account.

LOGNOG {[0;1;31m
���� �� ����餬�� ��� �夘� �����ਞ�⤦. ��� �ᤘ�� �᧦�� �៦�;[0;1m
} T Bad User-Id, live channel


 This user has entered a User-Id that is already online
 and using your BBS at this moment.  He is connected on a
 free sample channel, so we can tell him to type "new" if he
 does not already have an account.

ALRDON {[0;1m
���� �� ����餬�� �夘� 㛞 ��������⤦.

!J�������� ��⚥�� ���� ��� ��� ��������� ��� �����磦� ���夦����
� �⦪ ��㩫��, ��� ��㤦���� �㤬�� ���� �������� ����㣘��� �⚦����
���� �夘� �� �������� ��� ����餬�� ���� ��� ��� 騘 ��� ������㡘��.!)

���������磜 ��� ���⩘��.
} T User-Id already online, free sample channel

 This user has tried to enter a User-Id or a password three
 times already with no success (either there was no such
 User-Id, or it was already online, or the password was
 incorrect).  He is disconnected at the end of this message.

STRUKO {[0;1;31m
��� ��嫞 ���� �ᤘ�� �៦�.
��� �暦�� ������嘪 � �礛��� ��� ����槫����.
�������� ���⩫� ���� �� �⢜�� �� ���������ᩜ��.
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
�����飞, ��� �暦�� ������嘪 ��� �����磜 �� ��� �����⯦��� ��
�����婜��. ��������磜 �������⩫� 櫘� ������婜�� �� ���� �穫���
�⢜�� �� �������嫜. ����磜 �����飞 ��� ��� ��������.
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

!J� �������� ����㣘��� ⮜� �����⩜� ����ਠ�� ��� �����櫞�� ��� �� �ᤜ��
��㩞 ��� �����磦� ��� ���� AcroBase. ��������磜 �������㩫� ��
��������㩜�� ���� ��� ���� ���矬���!)

!C@COMPANY@,
@ADDRESS1@,
@ADDRESS2@,
@CITY@.!)

��������磜 ���� �������� ��� �� ��ᯜ�� ��� �� ����餬�� ���.

���������磜 ��� ���⩘��.
} T User's account has been suspended


ACCDEL {[0;1m

!J� �������� ����㣘��� ⮜� �����⩜� ��� �����櫞�� ��� �� �ᤜ��
��㩞 ��� �����磦� ��� ���� AcroBase. ��������磜 �������㩫� ��
��������㩜�� ���� ��� ���� ���矬���!)

!C@COMPANY@,
@ADDRESS1@,
@ADDRESS2@,
@CITY@.!)

��������磜 ���� �������� ��� �� ��ᯜ�� ��� �� ����餬�� ���.

���������磜 ��� ���⩘��.
} T User's account has been suspended


LOKOUT {[0;1m

!J�� ��姜�� ��� (class) ��� ��� �����⧜� ���� ��� ������ �� �������嫜 ����
��� ������ ���� @BBS@. ��������磜 �������㩫� �� ��������㩜�� ���� ���
���� ���矬���!)

!C@COMPANY@,
@ADDRESS1@,
@ADDRESS2@,
@CITY@.!)

��������磜 ���� �������� ��� �� ��ᯜ�� ��� �� ����餬�� ���.

���������磜 ��� ���⩘��.
} T User's class forbids logins


NOKEY {[0;1m

!J� ������ ��� ���⩘�� ⮜� ���������⤞ ��橙���. ������� ��� �����磜 ��
��� �����⯦��� �� �������嫜. ��������磜 �����ᩫ� �᧦�� ��� ���  ᢢ��
������ ��� @BBS@. ���������磜 ��� ���⩘��.!)

} T User doesn't have the proper key to login


BBSOFF {[0;1m

!J����磜 �����飞, ���� � @BBS@ �夘� ���� ��� ������ ���� ��������嘪
��� ��������� �����圪. ��������磜 ���⩫� ���櫜��. ����磜 �����飞 ���
�ᢠ ��� ��� ��������.!)

���������磜 ��� ���⩘��.

} T BBS is currently off-line for maintenance

 After a user has correctly entered his User-Id, he is asked
 for his password with this prompt.  Echo is disabled after
 this prompt to hide the password from observers.

ENTPSW {[0;1m
�������� �驫� �� �礟��� ���: [K[0m} T Asking for password

 When the user enters an incorrect password he is given this
 message, and another chance to enter his password.

PSWNOG {[0;1;31m
�ᤘ�� �៦�.
[0;1m} T Bad password


 This message is given to all users when they log onto The
 Major BBS.  A user has logged on when he has correctly
 entered his User-Id and his password.


GREETINGS {[2J[0;1m����㢟��� ���� [36m@BBS@[37m, %s!

[36m����� �������� [33m@NUMCONNS@[36m ����.
[37m� �������� ��� �礛��� 㫘� ��� [33m@DATELAST@[37m.

} T Log-on greeting message


NEWGREET {[2J[0;1m�����㢟��� ���� [36m@BBS@[37m, %s!

} T Log-on greeting message, new user


WARNING: IT IS AGAINST THE GNU PUBLIC LICENSE (GPL) TO REMOVE OR ALTER THIS
NOTICE IN ANY WAY. BY DOING SO YOU TERMINATE YOUR LICENSE AGREEMENT AND THE
RIGHTFUL OWNERS OF THIS SOFTWARE MAY AND WILL TAKE LEGAL ACTION AGAINST YOU.

GPL {[0;1m
!J@SHORTVERSION@ Copyright (c) 1994-98 ��⥠�� ��箦����. [32m� �⚠���� ⨮����
��� [37m������ �������� �������[32m. �� ���� �夘� ���矜�� ���������.
�婫� ����橛����� �� �� ������㩜�� [37m��� �����⤦�� 樦��[32m. ��ᯫ�
[33m/GPL[32m ��� ������櫜��� ��������圪.!)

[0;1m} T GPL report. DO NOT REMOVE OR ALTER IN ANY WAY


 This user has confirmed his desire to log off.  He is
 reminded of the name of your BBS (option BBSTTL).

SEEYA {[0;1;36m!Z!C             ��          
������������ �� ���������
��        �� ��        ��
��        �� ��        ��
��        �� ��        ��
��        �� ��        ��
��������� �� ������������
          ��             [37m

�[31m @BBS@ [37m��� ���������� ��� ��夘�� ���� ��� ��� @ONLINE@ �����.
���坦��� �� ⮦��� ��� ���� �� ��� ������磜 �礫���.!)


[0m
} T Logoff goodbye message


TIMEOUT {

!J���ᣘ�, ���� ��� �����磜 �� ����ᣜ ��� ������ ������� ��� ��� ��� ⤘
�����, �⮨� �� �៦��� �� ������� ���. �������� �������⩫� 櫘� �婫� ��
�⩞ �� �� �驜��.!)

!C[36m          ��       
��������� �� ������
��     �� ��     ��
��     �� ��     ��
������ �� ���������
       ��          
!)



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

[33m1[37m. [32mGreek 437G/737 � ������� font[37m. �� �����嫜 �� ����ᩜ�� ���� ��
   ��壜��, �櫜 �驫� '[33m1[37m'.

[33m2[37m. [32mCodepage 928, ����-928 � ISO-8859-7[37m. �� �������� �� ��������� ���� ��
   �������, ���� ����� '[33m2[37m'.

[33m3[37m. [32mIBM PC extended ASCII without Greek[37m. Enter '[33m3[37m' if the following characters
   appear as three rectangles of different shades: �� �� ��

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

!C[0;1;31m  ���[32m  ���[34m  ���  [37m!)

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

HELLO {[2J[0;1mWelcome to [1;33;5m@BBS@[0;1m.
Running [33m@VERSION@[0;1m.
[0;1mYou have been connected at @BAUD@ baud on @TIMESEC@ at @DATE@
[0;1;34;47m                 ��              [37m����������������������������������������[0;30;47m� [40m
[1;34;47m     ����������� �� ��������     [37m�  We are very happy to welcome you to  [0;30;47m� [40m
[1;34;47m     ��       �� ��       ��     [37m�  the Greek amateur communication and  [0;30;47m� [40m
[1;34;47m     ��       �� ��       ��     [37m�        Information oriented BBS       [0;30;47m� [40m
[1;34;47m     ��       �� ��       ��     [37m�[34m            A c r o B a s e            [0;30;47m� [40m
[1;34;47m     �������� �� �����������     [37m�      We wish you a pleasant stay.     [0;30;47m� [40m
[1;34;47m              ��                 [37m�[0;30;47m���������������������������������������� [40m
[1;37;47m ������������������������������������������������������������������������[0;30;47m� [40m
[1;37;47m � Data : (01) 8231753 8815616 8816312 8220610 8819963  [0;31;47mwww.acrogate.org [30m� [40m
[1;37;47m �[0;34;47m  telnet://acrogate.org:1024 ([1mAcro[0;34;47m) telnet://acrogate.org:1025 ([1;33mGATE[0;34;47m)  [30m� [40m
[1;37;47m �[33m Secure Shell ssh2 -C sshbbs acrogate.org � ssh -C sshbbs acrogate.org [0;30;47m� [40m
[1;37;47m �[0;30;47m������������������������������������������������������������������������ [40m[1;37m
} T Greeting message when user first connects to BBS


THELLO {[2J[0;1mWelcome to [1;33;5m@BBS@[0;1m.
Running [33m@VERSION@[0;1m.
[0;1mYou have been connected on @TIMESEC@ at @DATE@ using telnet
You are telnet line number @TNLNUM@ (out of @TNLMAX@)
[0;1;34;47m                 ��              [37m����������������������������������������[0;30;47m� [40m
[1;34;47m     ����������� �� ��������     [37m�  We are very happy to welcome you to  [0;30;47m� [40m
[1;34;47m     ��       �� ��       ��     [37m�  the Greek amateur communication and  [0;30;47m� [40m
[1;34;47m     ��       �� ��       ��     [37m�        Information oriented BBS       [0;30;47m� [40m
[1;34;47m     ��       �� ��       ��     [37m�[34m            A c r o B a s e            [0;30;47m� [40m
[1;34;47m     �������� �� �����������     [37m�      We wish you a pleasant stay.     [0;30;47m� [40m
[1;34;47m              ��                 [37m�[0;30;47m���������������������������������������� [40m
[1;37;47m ������������������������������������������������������������������������[0;30;47m� [40m
[1;37;47m � Data : (01) 8231753 8815616 8816312 8220610 8819963  [0;31;47mwww.acrogate.org [30m� [40m
[1;37;47m �[0;34;47m  telnet://acrogate.org:1024 ([1mAcro[0;34;47m) telnet://acrogate.org:1025 ([1;33mGATE[0;34;47m)  [30m� [40m
[1;37;47m �[33m Secure Shell ssh2 -C sshbbs acrogate.org � ssh -C sshbbs acrogate.org [0;30;47m� [40m
[1;37;47m �[0;30;47m������������������������������������������������������������������������ [40m[1;37m
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
!J@SHORTVERSION@ Copyright (c) 1994-98 Alexios Chouchoulas. [32mMegistos comes
with [37mABSOLUTELY NO WARRANTY[32m. This is free software and you are
welcome to redistribute it under [37mcertain conditions[32m. Type
[33m/GPL[32m for more information.!)

[0;1m} T GPL report. DO NOT REMOVE OR ALTER IN ANY WAY


SEEYA {[0;1;36m!Z!C             ��          
������������ �� ���������
��        �� ��        ��
��        �� ��        ��
��        �� ��        ��
��        �� ��        ��
��������� �� ������������
          ��             [37m

[31m @BBS@ [37mthanks you for staying with us for @ONLINE@ minutes.
We hope to see you again soon.!)


[0m
} T Logoff goodbye message


TIMEOUT {

!JWe're sorry, but we can't maintain the connection for more than one
minute, unless you log in. Please call back when you are ready to do so.!)

!C[36m          ��       
��������� �� ������
��     �� ��     ��
��     �� ��     ��
������ �� ���������
       ��          
!)


[0m} T User timed out while logging in


LANGEND {}

