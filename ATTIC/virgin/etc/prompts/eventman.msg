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
���ᣘ�, ��� ⮜�� ��橙��� �� ���� ��� �������.
[0;1m} T You don't have access to this module


MENU {[2J[0m[47;1;37m �������������������������������������������������������[0;30;47m� [40m
[47;1;37m �  [0;47;30mEvent Manager 0.5                                   [0;47;30m� [40m
[47;1;37m �  [0;47;30m��������������������������������������������������  [0;47;30m� [40m
[47;1;37m �  [0;31;47mS[30mhutdown BBS . . . . . . .  ����������垩� ������  [30m� [40m
[47;1;37m �  [0;31;47mU[30mndo shutdown . . . . . . �����ਫ਼ ����������垩��  [30m� [40m
[47;1;37m �                                                      [0;47;30m� [40m
[47;1;37m �  [0;31;47mL[30mist events . . . . . . . . . . . ���ᢦ��� events  [30m� [40m
[47;1;37m �  [0;31;47mA[30mdd (schedule) event . . . . .  ��������垩� event  [30m� [40m
[47;1;37m �  [0;31;47mC[30mancel event  . . . . . . . . . . . �����ਫ਼ event  [30m� [40m
[47;1;37m �                                                      [0;47;30m� [40m
[47;1;37m � [0;30;47me[31mX[30mit . . . . . . . . . . . . . . . . . . . . ������  [30m� [40m
[47;1;37m �[0;30;47m������������������������������������������������������� [0;1m

[32mEvent Manager[37m
�������� �驫� ��� ������� ���: [0m} T Main menu, normal version


SHMENU {[0;1;32m
Event Manager[37m
!W�驫� ��� ������� ��� ([33mS[37m,[33mU[37m,[33mL[37m,[33mA[37m,[33mC[37m,[33mX[37m ��� ⥦��, � [33m?[37m ��� �� �����): !)[0m} T Short menu, normal version


PMENU {[2J[0m[47;1;37m �������������������������������������������������������[0;30;47m� [40m
[47;1;37m �  [0;47;30mEvent Manager 0.5                                   [0;47;30m� [40m
[47;1;37m �  [0;47;30m��������������������������������������������������  [0;47;30m� [40m
[47;1;37m �  [0;31;47mS[30mhutdown BBS . . . . . . .  ����������垩� ������  [30m� [40m
[47;1;37m �  [0;31;47mU[30mndo shutdown . . . . . . �����ਫ਼ ����������垩��  [30m� [40m
[47;1;37m �                                                      [0;47;30m� [40m
[47;1;37m �  [0;31;47mL[30mist events . . . . . . . . . . . ���ᢦ��� events  [30m� [40m
[47;1;37m �  [0;31;47mA[30mdd (schedule) event . . . . .  ��������垩� event  [30m� [40m
[47;1;37m �  [0;31;47mC[30mancel event  . . . . . . . . . . . �����ਫ਼ event  [30m� [40m
[47;1;37m �                                                      [0;47;30m� [40m
[47;1;37m �  [0;31;47mN[30mew event  . . . . . . . . . ��������� �⦬ event  [30m� [40m
[47;1;37m �  [0;31;47mD[30melete event  . . . . . . . . . .  ���ᨚ��� event  [30m� [40m
[47;1;37m �                                                      [0;47;30m� [40m
[47;1;37m � [0;30;47me[31mX[30mit . . . . . . . . . . . . . . . . . . . . ������  [30m� [40m
[47;1;37m �[0;30;47m������������������������������������������������������� [0;1m

[32mEvent Manager[37m
�������� �驫� ��� ������� ���: [0m} T Main menu, privileged version


SHPMENU {[0;1;32m
Event Manager[37m
!W�驫� ��� ������� ��� ([33mS[37m,[33mU[37m,[33mL[37m,[33mA[37m,[33mC[37m,[33mN[37m,[33mD[37m,[33mX[37m ��� ⥦��, � [33m?[37m ��� �� �����): !)[0m} T Short menu, privileged version


ERRSEL {[0;1;31m
���ᣘ�, ��� ��ᨮ�� ���� � �������.
[0;1m} T Invalid option


LEAVE {[0;1m
������ ��� ��� event manager.
} T Leaving the event manager


EVNNAME {[0;1;32m
!J���'���� ��⧜� �� �驜�� ⤘ �礫��� 椦�� (�⮨� 13 ������㨜�) ��� ����
��������� event. �� 椦�� ������ �� ����⮜� �椦 ��ᣣ��� ��� �������.
�������������� ��棘�� �夘� "shutdown", "cleanup", ���.!)[37m

                                             �����������Ĵ
�驫� �� 椦�� ��� �⦬ event ([33mX[37m ��� ⥦��): [0m} T New event: Asking for event name


EVNALRX {[0;1;31m
���� �� event ⮜� 㛞 ������������.
[0;1m} T New event: Event name already exists


EVNCHR {[0;1;31m
�� 椦�� ��� event ����⮜� �� ��������� ������㨜�.
[0;1m} T New event: Event name contains invalid characters


EVNDESC {[0;1;32m
!J�騘 ��⧜� �� �驜�� �� �礫��� ��������� ��� event, �㡦�� 40
��������. �ᤫ� ��� ��������� �������������, �� ���姫ਫ਼ ��� ��
椦�� ��� �� �✠ 梘. � ��������� ������ �� ����⮜� �,�� ������㨜�
�⢜��.!)[37m

                                   ��������������������������������������Ĵ
�驫� ��� ��������� ([33mX[37m ��� ⥦��): [0m} T New event: Asking for event description


EVNPROG {[0;1;32m
!J�驫� �� 椦�� ��� �����ᣣ���� ��� �� ��⮜� � BBS daemon ��� ��
���������� �� event. �����嫜 �� �驜�� ��㨜� command line
(�� �����⫨��� ���). �� working directory ��� BBSD ���� ������� events
�夘� �� /usr/local/bbs/bin. Binaries �� ᢢ� directories ��⧜� �� ����� ��� ��
�� ��㨜� 椦�� ���� (�� /usr/bin/soupieres). ����������� �ᤫ� ⤘
link ��� �� /usr/local/bbs/bin ��� ���ᢢ��� directory. ������� �� ��� �⨜�� ������
�� �ᤜ��, ��� �� �ᤜ��.!)[37m

�驫� �� command line ��� event ([33mX[37m ��� ⥦��): [0m} T New event: Asking for event command


EVNONCE {[0;1;32m
!J�� ��棜��� ����� (��� �������圪) ���㩜�� �� �����婦�� ��� �穞
��� event.!)

!J���� ⤘ event ������嫘�, �⢜�� �� �⤜� ���� �婫�; �� �����㩜��
���������� ���, ��� ����������婜�� �� event �� ��⥜�, ��, ���� 05.00,
�� event �� ������夜� ���� �婫� ��'�樠����, ��� �� ������嫘� ����
�⨘ ���� 05.00. �� cleanup �夘� ���ᛜ���� ��� �⫦��� event. ��,
���埜��, �����㩜�� �������� ���� ��髞��, �櫜 �� event �� ������嫘� �椦
�� ����. �� shutdown �夘� ���ᛜ���� ��� event ��� ��� �⢦��� ��
������嫘� �ៜ �⨘.!)[37m

���⢜�� ��� event ���������� ([33mX[37m ��� ⥦��); [0m} T New event: Running once/daily?


EVNUNIQ {[0;1;32m
!J������ events ��⧜� �� ��婡����� ���� �婫� ���⢜��� �� ���� �� ����.
��� ���ᛜ����, �� shutdowns ����殨��� (� �� ����������� 騜�), ����
���������� �ᦪ, ��� �� cleanups ����殨��� (� �� ����������� 騜� ���
因� �⨘), �������⭦�� ���������� ������� ���. �����㩫� ���������� ��
�� �� event ��㡜� �� ���� ��� ��������.!)[37m

���� ⤘ �⫦�� event ��� �ᩘ ������ ([33mX[37m ��� ⥦��); [0m} T New event: Unique event?


EVNWARN {[0;1;32m
!J�� �⢜��, �����磜 �� ����磜 �� event ��� ��婘�� �� ��� ���ᣜ���
-warn, �� ����� ������� �����㣘�� ���� ��� ��������垩� ��� event. ����
�夘� ��㩠�� ��� �� �����������磜 ���� ��㩫�� ��� �᧦�� event (�� ��
�� shutdown). �� �� ��暨����/script ��� event ��� �� �������坜� ����,
�夘� ���� ��� �� �����㩜�� ���������� ���.!)[37m

�⢜�� ����������㩜��; ([33mX[37m ��� ⥦��); [0m} T New event: Do you want warnings?


EVNOK {[0;1;32m
!J�� event [37m%s[32m ��������㟞�� �������. �����嫜 �騘 �� ����������婜��
�櫜 �� ����������嫘�, �� ��� ������ [33mA[37m.!)
[0;1m} T New event created successfully


CANCEL {[0;1;31m
� ��������� ����韞��.[0;1m
} T Cancelling...


EVDWARN {[0;1;31;5m
��  [0;1;31m�������: !J!14i�����眫� �� [37m������㩜��[31m ⤘ event.
���� ����夜� 櫠 �� event ��� �� ������ �� ������������������ �⮨� �� ��
������������㩜��, ��ᚣ� ��� ������ �� �ᤜ� ����� ���� �ᩞ. [37m���[31m
�����᭜�� events �� �� cleanup ��� �� shutdown, �夘�
[37m����������[31m ��� �� ��������㩜� � �ᩞ. ��� ����᝜��� �� ��
������, �� ��� �⨜�� ������ �� �ᤜ��, ���㩫� X �騘.!)
!0l[0;1m} T Delete event: Warning


EVDASK {[0;1m
 !W���� event �⢜�� �� ������㩜��; ([33m?[37m ��� ���ᢦ��,
[33mX[37m ��� ⥦��):!) [0m} T Delete event: Which one?


EVDNEXS {[0;1;31m
���� �� event ��� ��ᨮ��. �驫� [33m?[31m ��� ���ᢦ��.
[0;1m} T Delete event: Unknown event name


EVDCONF {[0;1;31m
!W�������� ��������驫� 櫠 �⢜�� �� [37m������㩜��[31m ���� �� event.
��� �� ��ᨥ�� ᢢ� ���������垩�, ��� �� event ��� �� ������ �� ���������
�� ���⤘ ��槦.!)

[37m�嚦��� �⢜�� �� ���������� �� event; ([[33mY[37m]yes=��� / [[33mN[37m]o=殠): [0m} T Delete event: Confirm deletion


EVDOK {[0;1m
����, �� event %s ������㟞��.
} T Delete event: Event deleted


EVPHDR {[0;1;32m
                  ���ᢦ��� �����椫� events

������������������������������������������������������������Ŀ
� ����� event     � ���������                                �
������������������������������������������������������������Ĵ
} T List event prototypes: header


EVPTAB {[0;1;32m� [37m%-15s [32m� [37m%-40s[32m �
} T List event prototypes: table line


EVPFTR {[0;1;32m��������������������������������������������������������������
[0;1;32m} T List event prototypes: footer


EVANAM {[0;1m
!W�������� �驫� �� 椦�� ��� event ��� �⢜�� �� ����������婜�� ([33m?[37m ��� ���ᢦ��,
[33mX[37m ��� ⥦��):!) [0m} T Schedule event: What event?


EVANEX {[0;1;31m
��� ��ᨮ�� �⫦�� event. �驫� [33m?[31m ��� ���ᢦ��.
[0;1m} T Schedule event: Unknown event name


EVAUNI {[0;1;31m
!J���ᣘ�, ���� � ���⢜�� ��� event [33m%s[31m ⮜� 㛞 ���������������,
��� ��� ������ �� ��ᨮ�� ��� ��� ⤘ ������ event ����� ��� �囦��.!)
[0;1m} T Schedule event: Can't schedule more than one unique event


EVAWHH {[0;1;32m
!J�櫜 �⢜�� �� ���������� �� event; ��ᨮ��� ����� ��槦� �� �� ��婜��
����:!)

!2i!J�夦���� [37mHH:MM[32m ��坜�� ��� ������ 騘 ���⢜��� ��� event (��
騜� �夘� ��� ��ᩫ��� 0-23).!)
!0l
!2i!J�夦���� ⤘� ������ (�� [37m60[32m) ��坜�� �� �橘 ����� ���
�騘 �� ���������� �� event.!)
!0l
!2i!J�� [37mNOW[32m, �� event �� ������������� ����.!)
!0l
!2i!J�⢦�, �� [37mASAP[32m, �� ᛜ��� ������ �夦���� BUSY-OUT,
��� �� event �����ᜠ 櫘� ����������� ��� � �������妪 ��㩫��. [31m���
������� �� ���� ��� ������� ����� ����: �� ������� [37m���[31m ����������� ����
������ ���� ��������� ���� �� ����� ��� EVENT. �� ASAP ����� ������ ���
SHUTDOWN.!)
!0l[0;1m} T Schedule event: Help


EVAWHN {[0;1m
!W�櫜 �⢜�� �� ���������� �� event; ([33mhh:mm[37m, [33mxx[37m,
[33mNOW[37m, [33mASAP[37m, [33m?[37m ��� ��㟜��, � [33mX[37m ��� ⥦��):!) [0m} T Schedule event: When?


EVAWARN {[0;1;31;5m
��  [0;1;31m�������: !J!14i�����眫� ��
����������婜�� ⤘ event ��� ���⢜�� [37mNOW[31m. �� ���� �� event
�����㚜� �� shutdown ��� �ᩞ�, � �ᩞ �� ������ �� ��♜� ���� ��� ���
����梘.!)
!0l[0;1m
�嚦��� �⢜�� �� ����������婜�� �� event; ([[33mY[37m]yes=��� / [[33mN[37m]o=殠) [0m} T Schedule event: Final warning



EVAWHE {[0;1;31m
�� �������� ��椦� ���⢜���. ���������ᩫ�.
[0;1m} T Schedule event: Invalid time specification


EVA2MN {[0;1;31m
!J��� �����嫜 �� ⮜�� ��� ��� 100 ������ %s events. ���ਫ਼ ���
��������嘪. � ���, ��� 槦��� ����夦� ��������᫠�� 100 因� events, ��
���� �� �� ������ �� �� ����. ���������.!)
[0;1m} T Schedule event: Too many events of that type scheduled


EVADD1 {[0;1;32m
!W�� event [37m%s[32m ����������婫��� ������� ��� ���
[37m%02d:%02d[32m.!)
[0;1m} T Schedule event: Event scheduled (to be run once)


EVADD2 {[0;1;32m
!W�� event [37m%s[32m ����������婫��� �������. �� ������嫘� ����������
���� [37m%02d:%02d[32m!).
[0;1m} T Schedule event: Event scheduled (to be run daily)


EVADD3 {[0;1;32m
!W�� event [37m%s[32m ����������婫��� �������. �� ���������� 櫘�
����������� 梦� �� ��㩫�� ��� ��� �ᩞ.!)
[0;1m} T Schedule event: Event scheduled (to be run ASAP)


EVADD4 {[0;1;32m
!W�� event [37m%s[32m ����������婫��� ��� ᣜ�� ���⢜��.!)
[0;1m} T Schedule event: Event scheduled (to be run NOW)


EVLHDR {[0;1;32m

                     ���ᢦ��� ��������������� events

���������������������������������������������������������������������������Ŀ
� �����            �  ���  � ���������                         � ���������� �
���������������������������������������������������������������������������Ĵ
} T List events: List header


EVLTAB {[0;1;32m� [37m%-16s [32m� [37m%-5s [32m� [37m%-40s [32m� [37m%-3s [32m�
} T List events: List line


EVLFTR {[0;1;32m�����������������������������������������������������������������������������
[0;1m} T List events: List footer


EVLASAP {ASAP} T List events: ASAP string


EVLNO {���} T List events: NO string


EVLYES {���} T List events: YES string


EVCNAM {[0;1m
!W�������� �驫� �� ��㨜� 椦�� (�� shutdown-00) ��� event
��� �⢜�� �� ����驜�� ([33m?[37m ��� ���ᢦ��,
[33mX[37m ��� ⥦��):!) [0m} T Cancel event: What event?


EVCNEX {[0;1;31m
��� ��ᨮ�� �⫦�� event. �驫� [33m?[31m ��� ���ᢦ��.
[0;1m} T Cancel event: Unknown event name


EVCWARN {[0;1;31;5m
��  [0;1;31m�������: !J!14i���㩘�� �� �����ᯜ�� �� event [37m%s[31m.
�� �����㩜�� ���������� ���� ������� ��髞��, �� event �� ���������. ��
������嫘� ����������, ��� �� �������������� ����, ���� �� �� ��
��������������婜��. ��, ������, ��ᥜ�� �� cleanup, � �ᩞ �� ��夜� ���
cleanup �⮨� �� �� ������篜� �᧦��� ��� �� �� ��������������婜�. ������
�⢜� �� ��奜�, �� ��奜� �� �᫠ ᢢ�. ���� ��� �夘� ����夛���.
��� ����������, �;!)
!0l[0;1m} T Cancel event: Warning


EVCASK {[0;1m
�������� ��������驫� ��� ��'�樠���� �����ਫ਼ ��� event: ([[33mY[37m]yes=��� / [[33mN[37m]o=殠): [0m} T Cancel event: Yes or no?


EVCAN  {[0;1;32m
����, �� event [37m%s[32m �����韞�� ��'�樠����.
[0;1m} T Cancel event: Success



LANG {}

NOENTRY {[0;1;31m
Sorry, you don't have access to this area.
[0;1m} T You don't have access to this module


MENU {[2J[0m[47;1;37m �������������������������[0;30;47m� [40m
[47;1;37m �  [0;47;30mEvent Manager 0.5     [0;47;30m� [40m
[47;1;37m �  [0;47;30m��������������������  [0;47;30m� [40m
[47;1;37m �  [0;31;47mS[30mhutdown BBS          [30m� [40m
[47;1;37m �  [0;31;47mU[30mndo shutdown         [30m� [40m
[47;1;37m �                        [0;47;30m� [40m
[47;1;37m �  [0;31;47mL[30mist events           [30m� [40m
[47;1;37m �  [0;31;47mA[30mdd (schedule) event  [30m� [40m
[47;1;37m �  [0;31;47mC[30mancel event          [30m� [40m
[47;1;37m �                        [0;47;30m� [40m
[47;1;37m � [0;30;47me[31mX[30mit                   [30m� [40m
[47;1;37m �[0;30;47m������������������������� [0;1m

[32mEvent Manager[37m
Please enter your choice: [0m} T Main menu, normal version


SHMENU {[0;1;32m
Event Manager[37m
!WEnter your choice ([33mS[37m,[33mU[37m,[33mL[37m,[33mA[37m,[33mC[37m,[33mX[37m
to exit, or [33m?[37m for the menu): !)[0m} T Short menu, normal version


PMENU {[2J[0m[47;1;37m �������������������������[0;30;47m� [40m
[47;1;37m �  [0;47;30mEvent Manager 0.5     [0;47;30m� [40m
[47;1;37m �  [0;47;30m��������������������  [0;47;30m� [40m
[47;1;37m �  [0;31;47mS[30mhutdown BBS          [30m� [40m
[47;1;37m �  [0;31;47mU[30mndo shutdown         [30m� [40m
[47;1;37m �                        [0;47;30m� [40m
[47;1;37m �  [0;31;47mL[30mist events           [30m� [40m
[47;1;37m �  [0;31;47mA[30mdd (schedule) event  [30m� [40m
[47;1;37m �  [0;31;47mC[30mancel event          [30m� [40m
[47;1;37m �                        [0;47;30m� [40m
[47;1;37m �  [0;31;47mN[30mew event             [30m� [40m
[47;1;37m �  [0;31;47mD[30melete event          [30m� [40m
[47;1;37m �                        [0;47;30m� [40m
[47;1;37m � [0;30;47me[31mX[30mit                   [30m� [40m
[47;1;37m �[0;30;47m������������������������� [0;1m

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

                                             �����������Ĵ
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

                                   ��������������������������������������Ĵ
Enter the description ([33mX[37m to exit): [0m} T New event: Asking for event description


EVNPROG {[0;1;32m
!JEnter the UNIX command this event will execute. Specify the full path
of the binary. Obviously, if you don't know what you're doing, don't do
it here!!)[37m

Event command line ([33mX[37m ��� ⥦��): [0m} T New event: Asking for event command


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
��  [0;1;31mCAUTION: !J!14iYou're about to permanently [37mdelete[31m an
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

������������������������������������������������������������Ŀ
� Event name      � Description                              �
������������������������������������������������������������Ĵ
} T List event prototypes: header


EVPTAB {[0;1;32m� [37m%-15s [32m� [37m%-40s[32m �
} T List event prototypes: table line


EVPFTR {[0;1;32m��������������������������������������������������������������
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
��  [0;1;31mCAUTION: !J!14iYou're about to
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

���������������������������������������������������������������������������Ŀ
� Event name       � Time  � Description                            � Daily �
���������������������������������������������������������������������������Ĵ
} T List events: List header


EVLTAB {[0;1;32m� [37m%-16s [32m� [37m%-5s [32m� [37m%-40s [32m� [37m%-3s [32m�
} T List events: List line


EVLFTR {[0;1;32m�����������������������������������������������������������������������������
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
��  [0;1;31mCAUTION: !J!14iYou are about to cancel event instance [37m%s[31m.
If you answer yes, execution of this event will be cancelled. If the event is
executed regularly, it will NOT be executed again, unless you re-schedule it.!)
!0l[0;1m} T Cancel event: Warning


EVCASK {[0;1m
Please confirm cancelation of this event instance ([[33mY[37m]yes / [[33mN[37m]o): [0m} T Cancel event: Yes or no?


EVCAN  {[0;1;32m
OK, event instance [37m%s[32m was cancelled.
[0;1m} T Cancel event: Success



LANGEND {}