LEVEL2 {}


LINKEY {Key required to see news at login: 0} N 0 129

ENTRYKEY {Key required to gain entry to the news module: 0} N 0 129

SOPKEY {Key required for privileged access to the module: 128} N 0 129

DEFDUR {Default duration of bulletin (days): 10} N 0 3650

DEFSHW {Default announcement mode: ALWAYS} E ALWAYS ONCE

DEFHDR {Default header style (time/date): DATE} E NONE DATE TIME BOTH

DEFCLS {} S 10 Default Class locking for bulletins:

DEFKEY {Default key locking for bulletins: 0} N 0 129

MAXLEN {Maximum length of news bulletin: 65536} N 256 262144

UPLDESC {News Bulletin} S 50 File upload description




LEVEL3 {}


NOENTRY {[0;1;31m
���ᣘ�, ��� ⮜�� ��橙��� �� ���� ��� �������.
[0;1;31m} T User has no access to chosen area


MENU {[2J[0m[47;1;37m ����������������������������������������������������������[0;30;47m� [40m
[47;1;37m �  [0;47;30m                  �� T������� N�                     [0;47;30m� [40m
[47;1;37m �  [0;47;30m�����������������������������������������������������  [0;47;30m� [40m
[47;1;37m �  [0;31;47mR[30mead news . . . . . . . . . . . . . . . ���ᤠ�� ���  [30m� [40m
[47;1;37m �  [0;31;47mL[30mist news  . . . . . . . . . . . .  ���ᢦ��� ������  [30m� [40m
[47;1;37m �  [0;31;47mI[30mmport bulletin . . . . . . . . . .  �������� ����妬  [30m� [40m
[47;1;37m �  [0;31;47mD[30melete bulletin  . . . . . . . . .   �������� ����妬  [30m� [40m
[47;1;37m �  [0;31;47mE[30mdit bulletin . . . . . . . . . . . �����ਫ਼ ����妬  [30m� [40m
[47;1;37m �                                                         [0;47;30m� [40m
[47;1;37m � [0;30;47me[31mX[30mit  . . . . . . . . . . . . . . . . . . . . . ������  [30m� [40m
[47;1;37m �[0;30;47m���������������������������������������������������������� [0;1m

�������� ��
�������� �驫� ��� ������� ���: [0m} T News menu (privileged users only)


SHMENU {[0;1m
�������� ��
!W�驫� ��� ������� ��� ([33mR[37m,[33mL[37m,[33mI[37m,[33mD[37m,[33mE[37m,[33mX[37m ��� ⥦��, � [33m?[37m ��� �� �����): !)[0m} T News short menu


ERRSEL {[0;1;31m
!W���ᣘ�, ��� ��ᨮ�� � ������� "%c".!)
[0;1m} T Invalid option selection


LEAVE {[0;1m
!W������ ��� �� �������� ��.!)
[0m} T Exiting to main menu


PRESS {[0;1m
!W��⩫� Enter ��� �� ������⯜�� ��� �������� �����.!)[30m } T Press Enter to return to the main menu


VEDIT {[0;30;47m ����������������������������� [34m������� ����妬[0;30;47m ����������������������������[0;1;37;47m� [0m
[30;47m �                                                                          [0;1;47;37m� [0m
[30;47m �  ��ᨡ��� ����妬 (��⨜�)   [1;44;37m@4;0;9999;0n[0;47;30m                            (0-9999)  [1;37m� [0m
[30;47m �                                                                          [0;1;47;37m� [0m
[30;47m �  ���ᤠ��                    [0;30;46m [@"X "t] [0;47;30m                   (Space ��� ������)  [1;37m� [0m
[30;47m �                                                                          [0;1;47;37m� [0m
[30;47m �  �����⦤ ��������圪        [0;30;46m @18;"�����|���|���������|��� ��� ���������"l [0;47;30m    (Space ��� ������)  [1;37m� [0m
[30;47m �                                                                          [0;1;47;37m� [0m
[30;47m �  ���ᤠ�� �椦 ���� ��ᩞ    [1;37;44m@10;10;1s[0;47;30m                              [0;1;47;37m  � [0m
[30;47m �                                                                          [0;1;47;37m� [0m
[30;47m �  ������ ��������            [1;37;44m@3;0;129;0n[0;47;30m                              (0-129)[0;1;47;37m  � [0m
[30;47m �                                                                          [0;1;47;37m� [0m
[30;47m �  ��������櫞�� ����妬       [1;37;44m@4;-100;100;0n[0;47;30m                         (-100-+100)[0;1;47;37m  � [0m
[30;47m �                                                                          [0;1;47;37m� [0m
[30;47m �  Ctrl-Q: Cancel  Ctrl-S: Ok                                              [0;1;47;37m� [0m
[30;47m �  Ctrl-L: Redraw  Ctrl-X: Line    [0;1;42;33m@14;"OK"b[0;47;30m�    [0;1;41;33m@14;"Cancel"b[0;47;30m�  [0;1;47;37m� [0m
[30;47m �  Ctrl-R: Help                     ����������������     ����������������  [0;1;47;37m� [0m
[30;47m �[0;1;37;47m��������������������������������������������������������������������������� [0m} T Visual template


VEDIT1A {�����} T Visual template, 'NONE' string
VEDIT1B {���������} T Visual template, 'DATE' string
VEDIT1C {���} T Visual template, 'TIME' string
VEDIT1D {��������� ��� ���} T Visual template, 'BOTH' string


LEDIT {[2J[0;30;47m ������������������������������������������������������[0;1;37;47m� [0m
[30;47m �                   ������� ����妬                  [0;1;47;37m� [0m
[30;47m � ��������������������������������������������������� [0;1;47;37m� [0m
[30;47m � [31m1[30m. ��ᨡ��� ����妬 (��⨜�) .  [34m@4;0;9999;0n                [0;1;47;37m� [0m
[30;47m � [31m2[30m. ���ᤠ�� . . . . . . . . . . [34m@"X "t                 [0;1;47;37m� [0m
[30;47m � [31m3[30m. �����⦤ ��������圪  . . .  [34m@18;"�����|���|���������|��� ��� ���������"l  [0;1;47;37m� [0m
[30;47m � [31m4[30m. ���ᤠ�� �椦 ���� ��ᩞ . . [34m@10;10;1s          [0;1;47;37m� [0m
[30;47m � [31m5[30m. ������ ��������  . . . . .  [34m@3;0;129;0n                 [0;1;47;37m� [0m
[30;47m � [31m6[30m. ��������櫞�� ����妬 . . .  [34m@4;-100;100;0n                [0;1;47;37m� [0m
[30;47m �                                                     [0;1;47;37m� [0m
[30;47m � [31m0[30m. ���⮜��.@14;"0OK"b                                        [0;1;47;37m� [0m
[30;47m � [31mX[30m. �����.@14;"XCancel"b                                           [0;1;47;37m� [0m
[30;47m �[0;1;37;47m������������������������������������������������������ [0m
} T Linear template example


FIELD1 {[0;1m
!W�驫� ��� ��ᨡ��� ��� ����妬 �� ��⨜� (0-9999, 0=��'�樠����).!)
[0;1m} T Linear prompt #1


FIELD2 {[0;1m
!W���� �� ���� �����坜� �� �� ����� �� �����坜���. �� �����
��� �����᭦����, ���� �������� �� �����坦����. ���� �� ����
��⚮�� ������ ���� ��� �����櫞��.!)
[0;1m} T Linear prompt #2


FIELD3 {[0;1m
!W����⥫� �� �����⦤ ��������圪 �� �����坦���� ���� ������ ��� ����妬.!)
[0;1m} T Linear prompt #3


FIELD4 {[0;1m
!W��� ����� ������ �� �����坜��� �椦 ����� ��㩫�� ��� ���������⤦� class.
��� �����嫜 �� �����婜�� ���� �� �夘� ���� �� class. ��㤦���� �� ���� ����,
�� ����� �� �夘� ����� ��� 梦�� ���� ��㩫��.!)
[0;1m} T Linear prompt #4


FIELD5 {[0;1m
!W��� ����� ������ �� �����坜��� �椦 ����� ��㩫�� ��� ⮦�� ⤘ ���������⤦
������. ��� �����嫜 �� �����婜�� ���� �� �夘� ���� �� ������. �� ������ 0 �ᤜ�
�� ����� ����� ��� 梦�� ���� ��㩫��. �� ������ 129 �ᤜ� �� ����� ����� �椦 ���
�� ����餬�� Sysop.!)
[0;1m} T Linear prompt #5


FIELD6 {[0;1m
!W�������� �� ����� �����坦���� �� ����������� ����� (�� ��� ��橭��� ����� ��高).
�����嫜 �� �����ᩜ�� ⤘ ����� �� ⮜� �����竜�� ��������櫞�� ��� �� ᢢ�, ��坦����
��� ���� ��� ���� �� ����. �� ����� �����坦���� ���� ��夦��� ����� ��������櫞��� ���
���� ���� ����������� �����. ��������� ������� ����夦�� 櫠 �� ����� �� ���������� ����
�� �⢦� ��� �婫��, ������� ������� ����夦�� 櫠 �� ����� �� ���������� ���� ��� ����
��� �婫��. �����嫜 �� �驜�� ������� ��� ��ᩫ��� -100,...,+100.!)
[0;1m} T Linear prompt #6



WARNCLS {[0;1;33m
!W�������: �� class "[37m%s[33m" ��� ��婘�� ��� ��ᨮ��!!)
[0;1m} T Warning: class does not exist


CANCEL {[0;1;33m
!W���ਫ਼ ��� ��������嘪.!)
[0;1m} T Process aborted


IOERR {[0;1;31m
!W��������㟞�� ��晢��� ���� ��� ��������� ��� ����妬. � ��������� ����韞��.!)
[0;1m} T I/O error while writing news bulletin


BLTOK {[0;1;32m
!W�� ����� [37m%d[32m �������竞��.!)
[0;1m} T News bulletin created


TXTCAN {[0;1;32m
!W�� ������ ��� ��壜�� ��� ����妬 ����韞��� (���� ������ ���
�����������㩘�� ��� ������� ��� bulletin ���������� ⮦�� 㛞 �����).!)
[0;1m} T News bulletin text edit canceled





ASKEDT {[0;1m
!W�驫� ��� ������ ��� ���� �����ਫ਼ ����妬, [33m?[37m ��� ��㟜��, �
[33mX[37m ��� ⥦��:!)[0m } T Edit bulletin: What number?


ASKUPL {[0;1m
!W�⢜�� �� �������墜�� � �� �����驜�� �� ������棜�� ��� ����妬;
([[33mY[37m]es=��������, [[33mN[37m]o=殠, [[33mE[37m]dit=��樟ਫ਼) } T Edit bulletin: re-upload bulletin?


ASKUPLD {[Enter=No]:[0m!) } T Edit bulletin: default response


ASKERR {[0;1;31m
!J�������� �驫� [33mY[31m, [33mN[31m � [33mE[31m.!)
[0;1m} T Edit bulletin: bad answer to ASKUPL


SHEADER {[0;1;35m
�������������Ŀ
� ����� [37m#%-3d[35m ����������������������������������������������������������������Ŀ
� ���ᢞ: [37m%-9s %-8s[35m       � ��������櫞��: [37m%-4d[35m                       �
� ��ᨡ��� ����妬 (��⨜�): [37m%4d[35m  � �����⦤ ��������圪: [37m%-18s[35m  �
� ��ᩞ: [37m%-10s[35m                � ������: [37m%-3d[35m                               �
��������������������������������������������������������������������������������
[0;1m} T Sysop version of the Bulletin Header


LSTHDR {[0;1m

���������������������������������������������������������������Ŀ
� [33mA/A[37m � [33m���������� ��� ���[37m � [33m����[37m � [33m��������[37m � [33m����� ��� ������[37m �
���������������������������������������������������������������Ĵ
} T News bulletin list, header


LSTTAB {� [32m%3d[37m � [32m%s %s[37m � [32m%+4d[37m �  [32m%5d%c[37m  � [32m%-10s   %3d[37m �
} T News bulletin list, table


LSTFTR {�����������������������������������������������������������������

(*) = �� ����� �夘� �������� (��� �����坜���).

[0;1m} T News bulletin list, footer



RDNEWS {[2J[0;1;31m�� �������� ��� ��:

} T Reading news bulletins


HEADER {[0;1m��  [35m%s[0;1m  ��  %s

} T Bulletin Header


NEWBLT {[0;1;33;5m*��*[0;1m} T You've never read this bulletin before


BLTDIV {[0;1m
} T Bulletin divider


NONEWS {[0;1;31m
[!W��� ��ᨮ��� �������� ��.!)
[0;1m
} T News file is empty


DELBLT {[0;1m
!W�驫� ��� ������ ��� ���� �������� ����妬, [33m?[37m ��� ���ᢦ��, �
[33mX[37m ��� ⥦��:!)[0m } T Delete bulletin: What number?


NUMERR {[0;1;31m
!W�� ����� [37m%d[31m ��� ��ᨮ��. ���������ᩫ�...!)
} T Delete bulletin rebuff unknown bulletin


DELOK {[0;1m
!W��������韞��: � �������� �����ੜ �� �������.!)
[0;1m} T Delete bulletin: Deletion successful


FTOOMANY {[0;1;33m
!J������墘�� ��� ��� ⤘ �����. �椦 �� ��髦 ����� ��
��������������.!)
[0;1m} T Upload bulltin: more than one file uploaded





LANG {}



NOENTRY {[0;1;31m
Sorry, you don't have access to this area.
[0;1;31m} T User has no access to chosen area


MENU {[2J[0m[47;1;37m ������������������������[0;30;47m� [40m
[47;1;37m �  [0;47;30m    Latest News      [0;47;30m� [40m
[47;1;37m �  [0;47;30m�������������������  [0;47;30m� [40m
[47;1;37m �  [0;31;47mR[30mead news bulletins  [30m� [40m
[47;1;37m �  [0;31;47mL[30mist news bulletins  [30m� [40m
[47;1;37m �  [0;31;47mI[30mmport bulletin      [30m� [40m
[47;1;37m �  [0;31;47mD[30melete bulletin      [30m� [40m
[47;1;37m �  [0;31;47mE[30mdit bulletin        [30m� [40m
[47;1;37m �                       [0;47;30m� [40m
[47;1;37m � [0;30;47me[31mX[30mit                  [30m� [40m
[47;1;37m �[0;30;47m������������������������ [0;1m

Latest news
Please enter your choice: [0m} T News menu (privileged users only)


SHMENU {[0;1m
Latest news
!WEnter your choice ([33mR[37m,[33mL[37m,[33mI[37m,[33mD[37m,[33mE[37m,[33mX[37m
to exit, or [33m?[37m for the menu): !)[0m} T News short menu


ERRSEL {[0;1;31m
!WSorry, there is not option "%c" here.!)
[0;1m} T Invalid option selection


LEAVE {[0;1m
!WLeaving the news area.!)
[0m} T Exiting to main menu


PRESS {[0;1m
!WPress [33mEnter[37m to return to the main menu.!)[30m } T Press Enter to return to the main menu


VEDIT {[0;30;47m ��������������������������� [34mBulletin Properties[0;30;47m ���������������������������[0;1;37;47m� [0m
[30;47m �                                                                          [0;1;47;37m� [0m
[30;47m �  Bulletin lifetime (days)    [1;44;37m@4;0;9999;0n[0;47;30m                            (0-9999)  [1;37m� [0m
[30;47m �                                                                          [0;1;47;37m� [0m
[30;47m �  Bulletin is visible         [0;30;46m [@"X "t] [0;47;30m                    (Space to toggle)  [1;37m� [0m
[30;47m �                                                                          [0;1;47;37m� [0m
[30;47m �  Bulletin header display     [0;30;46m @18;"None|Time|Date|Time and Date"l [0;47;30m     (Space to change)  [1;37m� [0m
[30;47m �                                                                          [0;1;47;37m� [0m
[30;47m �  Show only to user in class  [1;37;44m@10;10;1s[0;47;30m                              [0;1;47;37m  � [0m
[30;47m �                                                                          [0;1;47;37m� [0m
[30;47m �  Show only to owners of key  [1;37;44m@3;0;129;0n[0;47;30m                              (0-129)[0;1;47;37m  � [0m
[30;47m �                                                                          [0;1;47;37m� [0m
[30;47m �  Display priority            [1;37;44m@4;-100;100;0n[0;47;30m                         (-100-+100)[0;1;47;37m  � [0m
[30;47m �                                                                          [0;1;47;37m� [0m
[30;47m �  Ctrl-Q: Cancel  Ctrl-S: Ok                                              [0;1;47;37m� [0m
[30;47m �  Ctrl-L: Redraw  Ctrl-X: Line    [0;1;42;33m@14;"OK"b[0;47;30m�    [0;1;41;33m@14;"Cancel"b[0;47;30m�  [0;1;47;37m� [0m
[30;47m �  Ctrl-R: Help                     ����������������     ����������������  [0;1;47;37m� [0m
[30;47m �[0;1;37;47m��������������������������������������������������������������������������� [0m} T Visual template


VEDIT1A {None} T Visual template, 'NONE' string
VEDIT1B {Date} T Visual template, 'DATE' string
VEDIT1C {Time} T Visual template, 'TIME' string
VEDIT1D {Time and Date} T Visual template, 'BOTH' string


LEDIT {[2J[0;30;47m ������������������������������������������������������[0;1;37;47m� [0m
[30;47m �                 Bulletin Properties                 [0;1;47;37m� [0m
[30;47m � ��������������������������������������������������� [0;1;47;37m� [0m
[30;47m � [31m1[30m. Bulletin lifetime (days)  .  [34m@4;0;9999;0n                [0;1;47;37m� [0m
[30;47m � [31m2[30m. Visible  . . . . . . . . . . [34m@"X "t                 [0;1;47;37m� [0m
[30;47m � [31m3[30m. Header display  . . . . . .  [34m@18;"None|Time|Date|Time and Date"l  [0;1;47;37m� [0m
[30;47m � [31m4[30m. Show only to class . . . . . [34m@10;10;1s          [0;1;47;37m� [0m
[30;47m � [31m5[30m. Show only to key owners . .  [34m@3;0;129;0n                 [0;1;47;37m� [0m
[30;47m � [31m6[30m. Display priority  . . . . .  [34m@4;-100;100;0n                [0;1;47;37m� [0m
[30;47m �                                                     [0;1;47;37m� [0m
[30;47m � [31m0[30m. Continue.@14;"0OK"b                                        [0;1;47;37m� [0m
[30;47m � [31mX[30m. Cancel.@14;"XCancel"b                                          [0;1;47;37m� [0m
[30;47m �[0;1;37;47m������������������������������������������������������ [0m
} T Linear template example


FIELD1 {[0;1m
!WEnter the bulletin lifetime in days (0-9999, 0=permanent).!)
[0;1m} T Linear prompt #1


FIELD2 {[0;1m
!WThis field controls whether the bulletin will be visible.
If you need to keep a certain bulletin around but only show it
at certain times (eg season greetings, reminders of regular events etc),
all you need to do is make it invisible.!)
[0;1m} T Linear prompt #2


FIELD3 {[0;1m
!WPlease choose the bulletin's header type.!)
[0;1m} T Linear prompt #3


FIELD4 {[0;1m
!WThis allows you to control who can see this bulletin. Enter a class name
here to make the bulletin visible only to members of that class. Leave the
field empty to make the bulletin visible to users of all classes.!)
[0;1m} T Linear prompt #4


FIELD5 {[0;1m
!WYou can limit the visibility of a news bulletin to owners of a certain key.
For instance, you could add reminders to fellow BBS administrators. Key 0 makes
the bulletin visible to all users. Key 129 makes it visible only to user Sysop.!)
[0;1m} T Linear prompt #5


FIELD6 {[0;1m
!WNews bulletins are normally shown in chronological order (most recent bulletins first).
You can force a bulletin to be displayed above other by increasing its priority. Conversely,
you can make a bulletin show below others by decreasing its priority. Bulletins are sorted by
decreasing priority, THEN by increasing age. You can specify priorities between -100 and +100.!)
[0;1m} T Linear prompt #6



WARNCLS {[0;1;33m
!WCaution: Class "[37m%s[33m" does not exist!!)
[0;1m} T Warning: class does not exist


CANCEL {[0;1;33m
!WAborted.!)
[0;1m} T Process aborted


IOERR {[0;1;31m
!WThere was a problem in creating the bulletin. Creation aborted.!)
[0;1m} T I/O error while writing news bulletin


BLTOK {[0;1;32m
!WNews bulletin [37m%d[32m created.!)
[0;1m} T News bulletin created


TXTCAN {[0;1;32m
!WBulletin text edit aborted.
Any changes to the bulletin's properties have been saved, though.!)
[0;1m} T News bulletin text edit canceled





ASKEDT {[0;1m
!WEnter the bulletin number to edit, [33m?[37m for help, or
[33mX[37m to exit:!)[0m } T Edit bulletin: What number?


ASKUPL {[0;1m
!WWould you like to upload a new news bulletin or edit the existing text of the news bulletin?
([[33mY[37m]es=upload, [[33mN[37m]o=neither, or [[33mE[37m]dit) } T Edit bulletin: re-upload bulletin?


ASKUPLD {[Enter=No]:[0m!) } T Edit bulletin: default response


ASKERR {[0;1;31m
!JPlease enter [33mY[31m, [33mN[31m or [33mE[31m.!)
[0;1m} T Edit bulletin: bad answer to ASKUPL


SHEADER {[0;1;35m
���������������Ŀ
� Bulletin [37m#%-3d[35m ��������������������������������������������������������������Ŀ
� Send: [37m%-9s %-8s[35m         � Priority: [37m%-4d[35m                            �
� Bulletin lifetime (days): [37m%4d[35m   � Additional info: [37m%-18s[35m       �
� Class: [37m%-10s[35m                � Key: [37m%-3d[35m                                  �
��������������������������������������������������������������������������������
[0;1m} T Sysop version of the Bulletin Header


LSTHDR {[0;1m

���������������������������������������������������������������Ŀ
� [33m # [37m � [33m   DATE AND TIME  [37m � [33mPRIO[37m � [33mLIFETIME[37m � [33mCLASS  AND  KEY [37m �
���������������������������������������������������������������Ĵ
} T News bulletin list, header


LSTTAB {� [32m%3d[37m � [32m%s %s[37m � [32m%+4d[37m �  [32m%5d%c[37m  � [32m%-10s   %3d[37m �
} T News bulletin list, table


LSTFTR {�����������������������������������������������������������������

(*) = Disabled (invisible) bulletin.

[0;1m} T News bulletin list, footer



RDNEWS {[2J[0;1;31mLatest news:

} T Reading news bulletins


HEADER {[0;1m��  [35m%s[0;1m  ��  %s

} T Bulletin Header


NEWBLT {[0;1;33;5m*NEW*[0;1m} T You've never read this bulletin before


BLTDIV {[0;1m
} T Bulletin divider


NONEWS {[0;1;31m
[!WSorry, there aren't any news news bulletins to show.!)
[0;1m
} T News file is empty


DELBLT {[0;1m
!WEnter the number of the bulleting to delete, [33m?[37m for a list, or
[33mX[37m to exit:!)[0m } T Delete bulletin: What number?


NUMERR {[0;1;31m
!WSorry, bulletin [37m%d[31m does not exist.!)
} T Delete bulletin rebuff unknown bulletin


DELOK {[0;1m
!WOK, the bulletin was deleted.!)
[0;1m} T Delete bulletin: Deletion successful


FTOOMANY {[0;1;33m
!JYou've uploaded more than one file. Only the first file will be used.!)
[0;1m} T Upload bulltin: more than one file uploaded


LANGEND {}

