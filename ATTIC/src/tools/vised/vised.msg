LEVEL2 {}

RMARGIN {Default right margin: 75} N 20 999

VSCRINC {Vertical scrolling increment: 10} N 1 25

HSCRINC {Horizontal scrolling increment: 10} N 1 25

PAGEINC {Page up/down increment (0= 1 screenful): 0} N 0 100

INSERT {Turn insert mode on at start of session? YES} B

FORMAT {Default formatting mode: JUSTIFY} E NONE LEFT RIGHT CENTRE JUSTIFY

TXTUPLD {Text Editor Upload} S 50 File upload description

QTECHRS {>} S 20 Quote character(s)

QTEMAXC {Maximum column where quote chr may appear: 3} N 1 10


CFGTXT {Foreground of normal text: WHITE} E BLACK DARKBLUE DARKGREEN DARKCYAN DARKRED DARKMAGENTA BROWN GREY DARKGREY BLUE GREEN CYAN RED MAGENTA YELLOW WHITE

CBGTXT {Background of normal text: BLACK} E BLACK BLUE GREEN CYAN RED MAGENTA BROWN GREY


CFGBLK {Foreground of block text: WHITE} E BLACK DARKBLUE DARKGREEN DARKCYAN DARKRED DARKMAGENTA BROWN GREY DARKGREY BLUE GREEN CYAN RED MAGENTA YELLOW WHITE

CBGBLK {Background of block text: GREEN} E BLACK BLUE GREEN CYAN RED MAGENTA BROWN GREY


CFGFND {Foreground of found text: MAGENTA} E BLACK DARKBLUE DARKGREEN DARKCYAN DARKRED DARKMAGENTA BROWN GREY DARKGREY BLUE GREEN CYAN RED MAGENTA YELLOW WHITE

CBGFND {Background of found text: BLACK} E BLACK BLUE GREEN CYAN RED MAGENTA BROWN GREY


CFGQTE {Foreground of quoted text: GREEN} E BLACK DARKBLUE DARKGREEN DARKCYAN DARKRED DARKMAGENTA BROWN GREY DARKGREY BLUE GREEN CYAN RED MAGENTA YELLOW WHITE

CBGQTE {Background of quoted text: BLACK} E BLACK BLUE GREEN CYAN RED MAGENTA BROWN GREY


LEVEL3 {}


LOADERR {[0;1;31m
!W�� ��壜�� ������ᜠ �� 樠� �� [37m%d[31m bytes.
��� ������ �� �������� ��桢��� ���� ����ᡫ� ����⤦�.!)
!0l[0m

[2J} T File is too big


STOVR {Overwrite} T Top Status line 'Overwrite' string

STINS {Insert   } T Top Status line 'Insert' string


STNONE {No formatting} T Top Status line 'no formatting' string

STLEFT {Left-flush   } Top Status line 'left flush' string

STRGHT {Right-flush  } Top Status line 'right flush' string

STCNTR {Centre       } Top Status line 'centre' string

STJUST {Justify      } Top Status line 'justify' string


STATUST {[0;30;46m[K%4d,%-3d  %6d/%d bytes  %s  %s  ��᫦� %d} T Top Status line


STATUSB {[K[0;1;36m Escape [0;30;46m Meta (M-)  [0;1;36m Ctrl-O [0;30;46m Format     [0;1;36m Ctrl-K [0;30;46m Blocks     [0;1;36m Ctrl-L [0;30;46m Redraw[K
K[0;1;36m Ctrl-R [0;30;46m ��㟜��    [0;1;36m Ctrl-S [0;30;46m ������     [0;1;36m Ctrl-C [0;30;46m ���ਫ਼    [0;1;36m Meta-F [0;30;46m Reformat[K} T Bottom Status lines

STATUSM {[K[0;30;42m Meta-              [0;1;32m    V   [0;30;42m ���囘 -   [0;1;32m    <   [0;30;42m ����       [0;1;32m    X   [0;30;42m ������[K
[K[0;1;32m Ctrl-R [0;30;42m ��㟜��    [0;1;32m    %   [0;30;42m Find/repl. [0;1;32m    >   [0;30;42m �⢦�      [0;1;32m    Q   [0;30;42m ���ਫ਼[K} T Bottom Status lines, meta key

STATUSO {[K[0;30;42m Formatting-        [0;1;32m    I   [0;30;42m Insert     [0;1;32m    L   [0;30;42m ��������   [0;1;32m    C   [0;30;42m �⤫��[K
[K[0;1;32m Ctrl-R [0;30;42m ��㟜��    [0;1;32m    R   [0;30;42m �����      [0;1;32m    J   [0;30;42m ���宠��   [0;1;32m    N   [0;30;42m �姦��[K} T Bottom Status lines, formatting

STATUSK {[K[0;30;42m Blocks-            [0;1;32m    B   [0;30;42m ����       [0;1;32m    K   [0;30;42m �⢦�      [0;1;32m    C   [0;30;42m ���������[K
[K[0;1;32m Ctrl-R [0;30;42m ��㟜��    [0;1;32m    V   [0;30;42m �����夞�� [0;1;32m    Y   [0;30;42m ��������   [0;1;32m        [0;30;42m       [K} T Bottom Status lines, blocks 


ERRSIZ {[0;1;33;41m[K��ᩘ�� �� 樠� ���⟦�� ��� ����⤦� ���.} T Error: reached size limit

ERRFMT {[0;1;33;41m[K�� ��壜�� ���⨘�� �� 樠� ���⟦��. �� ����� 櫘� ���嫜 ��� ��� editor.} T Error: exceeded size limit


HELP1 {[0;1;47;37m �����������������������������������������������������������������������������[0;47;30m� [0m
[0;1;47;37m � [0;30;47mFull Screen Editor                                    ������� - ���囘 1/4 � [0m
[0;1;47;37m � [0;30;47m�������������������������������������������������������������������������� � [0m
[0;1;47;37m � ������:[0;30;47m C-P  [34m���           [30mC-N  [34m���            [30m�����������������������Ŀ [0;47;30m� [0m
[0;1;47;37m � [0;30;47m        C-B  [34m��������       [30mC-F  [34m�����           [30m� Home: �  Up   � PgUp: � [0;47;30m� [0m
[0;1;47;37m � [0;30;47m        C-A  [34m���� ������   [30mC-E  [34m�⢦� ������   [30m�  C-A  �  C-P  �  C-T  � [0;47;30m� [0m
[0;1;47;37m � [0;30;47m        C-T  [34m�����. ���囘  [30mC-V  [34m���. ���囘    [30m�����������������������Ĵ [0;47;30m� [0m
[0;1;47;37m � [0;30;47m        C-Q  [34m���� ����⤦�  [30mC-W  [34m�⢦� ����⤦�  [30m� Left: �       � Rght: � [0;47;30m� [0m
[0;1;47;37m � [0;30;47m        M-<  [34m���� ����⤦�  [30mM->  [34m�⢦� ����⤦�  [30m�  C-B  �       �  C-F  � [0;47;30m� [0m
[0;1;47;37m � [0;30;47m                                                 �����������������������Ĵ [0;47;30m� [0m
[0;1;47;37m � [0;30;47m        '� ����������㩫� �� �⢞ (ANSI/VT).     � End:  � Down: � PgDn: � [0;47;30m� [0m
[0;1;47;37m � [0;30;47m                                                 �  C-E  �  C-N  �  C-V  � [0;47;30m� [0m
[0;1;47;37m � ��������: [0;30;47mC-D  [34m�������� ��棜��� ������㨘       [30m������������������������� [0;47;30m� [0m
[0;1;47;37m �           [0;30;47mC-Y  [34m�������� ��⮦���� ������                                  [0;47;30m� [0m
[0;1;47;37m �                                                                            [0;47;30m� [0m
[0;1;47;37m � [0;30;47m (C-A = Ctrl-A, M-A = Esc + A � Alt-A �� ��婡���� �� Linux ����梘)       [0;47;30m� [0m
[0;1;47;37m � [0;30;47m (1" ���� ��⩜�� ⤘ ������ ��㡫��, �����坦���� �� ������ ��㟜���)   [0;47;30m� [0m
[0;1;47;37m �                                                                            [0;47;30m� [0m
[0;1;47;37m � [0;30;47m Enter ��� ��� ��棜�� ���囘, ������㧦�� ᢢ� ��㡫�� ��� ���������.     [0;47;30m� [0m
[0;1;47;37m �[0;47;30m����������������������������������������������������������������������������� [0m
} T Help, page 1 (basic commands)


HELP2 {[0;1;47;37m �����������������������������������������������������������������������������[0;47;30m� [0m
[0;1;47;37m � [0;30;47mFull Screen Editor                                    ������� - ���囘 2/4 � [0m
[0;1;47;37m � [0;30;47m�������������������������������������������������������������������������� � [0m
[0;1;47;37m � ����� �������:[0;30;47m                                                             � [0m
[0;1;47;37m � [0;30;47m    C-K F [34m�ᥠ�� ��� ��壜�� (Find)                                        [0;47;30m� [0m
[0;1;47;37m � [0;30;47m    C-U   [34m���⮜�� ���壘��� (Find next)                                   [0;47;30m� [0m
[0;1;47;37m � [0;30;47m    C-K A [34m�������ᩫ��� ����⤦� (Find-Replace)                            [0;47;30m� [0m
[0;1;47;37m � [0;30;47m                                                                           � [0m
[0;1;47;37m � [0;30;47m    C-K B [34m���� �����ᩣ���� (Block beginning)                              [0;47;30m� [0m
[0;1;47;37m � [0;30;47m    C-K K [34m�⢦� �����ᩣ���� (Block end)                                   [0;47;30m� [0m
[0;1;47;37m � [0;30;47m    C-K C [34m��������� �����ᩣ���� (Copy block)                              [0;47;30m� [0m
[0;1;47;37m � [0;30;47m    C-K M [34m�����夞�� �����ᩣ���� (Move block)                             [0;47;30m� [0m
[0;1;47;37m � [0;30;47m    C-K V [34m�� 因�                                                          [0;47;30m� [0m
[0;1;47;37m � [0;30;47m    C-K Y [34m�������� �����ᩣ����                                            [0;47;30m� [0m
[0;1;47;37m � [0;30;47m                                                                           � [0m
[0;1;47;37m � [0;30;47m    C-K R [34m�矣��� ������ ������妬                                        � [0m
[0;1;47;37m � [0;30;47m                                                                           [0;47;30m� [0m
[0;1;47;37m � [0;30;47m                                                                           � [0m
[0;1;47;37m � [0;30;47m Enter ��� ��� ��棜�� ���囘, ������㧦�� ᢢ� ��㡫�� ��� ���������.     [0;47;30m� [0m
[0;1;47;37m �[0;47;30m����������������������������������������������������������������������������� [0m
} T Help, page 2 (blocks, etc.)


HELP3 {[0;1;47;37m �����������������������������������������������������������������������������[0;47;30m� [0m
[0;1;47;37m � [0;30;47mFull Screen Editor                                    ������� - ���囘 3/4 � [0m
[0;1;47;37m � [0;30;47m�������������������������������������������������������������������������� � [0m
[0;1;47;37m � ����������� ��������:[0;30;47m                                                      [0;47;30m� [0m
[0;1;47;37m � [0;30;47m    C-O I � M-I [34mInsert/Overtype mode (��������/�����᢬�� ����⤦�)        [0;47;30m� [0m
[0;1;47;37m � [0;30;47m    C-O L � M-L [34m���宠�� �������� (wrap)                                   [0;47;30m� [0m
[0;1;47;37m � [0;30;47m    C-O C � M-C [34m�����ᨠ��� ������                                        [0;47;30m� [0m
[0;1;47;37m � [0;30;47m    C-O R � M-R [34m���宠�� �����                                             [0;47;30m� [0m
[0;1;47;37m � [0;30;47m    C-O J � M-J [34m���宠�� �������� ��� ����� (justify)                      [0;47;30m� [0m
[0;1;47;37m � [0;30;47m    C-O N � M-N [34m����������垩� �������垩�� (��� ������᫘�)               [0;47;30m� [0m
[0;1;47;37m �                                                                            [0;47;30m� [0m
[0;1;47;37m � [0;30;47m    M-F         [34m�������垩� ������᭦� ��� ��� ��⮦��� ������ ��� ���    [0;47;30m� [0m
[0;1;47;37m �                                                                            [0;47;30m� [0m
[0;1;47;37m � [0;47;30m���棘�� �������垩� ��� �������嘪 ������ �夜��� �� ��� �圩� ��� Enter � [0m
[0;1;47;37m � [0;47;30m��� �椦 ��� ���宠�� ����� ��� �����ᨠ���. ���� ���宠�� �������� (wrap) � [0m
[0;1;47;37m � [0;47;30m� �������垩� �夜��� ���� �����������嫜.  ��� Justify ��� �夜��� ����- � [0m
[0;1;47;37m � [0;47;30m���� ���宠��. ��⩫� Tab ���� ���� ��� ������᭦� ��� �� ��� �����婜��.  � [0m
[0;1;47;37m �                                                                            [0;47;30m� [0m
[0;1;47;37m � [0;30;47m Enter ��� ��� ��棜�� ���囘, ������㧦�� ᢢ� ��㡫�� ��� ���������.     [0;47;30m� [0m
[0;1;47;37m �[0;47;30m����������������������������������������������������������������������������� [0m
} T Help, page 3 (formatting)


HELP4 {[0;1;47;37m �����������������������������������������������������������������������������[0;47;30m� [0m
[0;1;47;37m � [0;30;47mFull Screen Editor                                    ������� - ���囘 4/4 � [0m
[0;1;47;37m � [0;30;47m�������������������������������������������������������������������������� � [0m
[0;1;47;37m � ������� ������� ��� ������[0;30;47m                                                 [0;47;30m� [0m
[0;1;47;37m �                                                                            [0;47;30m� [0m
[0;1;47;37m � [0;47;30mC-S � M-X  [34m����㡜��� ��� ����⤦� ��� ⥦���                              [30m� [0m
[0;1;47;37m � [0;47;30mC-Y � M-Q  [34m�����ᢜ��� ��� ����⤦� ��� ⥦���                             [30m� [0m
[0;1;47;37m � [0;47;30mC-X        [34m���ᙘ�� ��� ����⤦� ���� line editor                          [30m� [0m
[0;1;47;37m �                                                                            [0;47;30m� [0m
[0;1;47;37m � [0;47;30mC-Z        [34m�������� (upload) ⫦���� ����⤦� ���� editor                  [30m� [0m
[0;1;47;37m �                                                                            [0;47;30m� [0m
[0;1;47;37m � [0;47;30m�����嫜 ��  ���᚜�� ��壜�� �� ������� ������㨜�  (�� ANSI ������) �� � [0m
[0;1;47;37m � [0;47;30m��� �������� ������. ���� ������� ������㨜� �����坦���� ��� ��૞����- � [0m
[0;1;47;37m � [0;47;30m�� ('?'). � �������垩� ��� ⫦���� ����⤦� �夘� ���� ��� ���礞.        � [0m
[0;1;47;37m �                                                                            [0;47;30m� [0m
[0;1;47;37m � [0;47;30m�� ���姫ਫ਼ ���, ���� ��� ⥦��  ��� ��� ��� editor, �� ��壜�� ������ᜠ � [0m
[0;1;47;37m � [0;47;30m�� 樠� ���⟦�� (�� ��� �������垩��), �� �����⦤ ��壜�� �� ���������. � [0m
[0;1;47;37m �                                                                            [0;47;30m� [0m
[0;1;47;37m � [0;30;47m ��⩫� ������㧦�� ��㡫�� ��� ��������� ��� ��壜��.                     [0;47;30m� [0m
[0;1;47;37m �[0;47;30m����������������������������������������������������������������������������� [0m
} T Help, page 4 (exiting etc.)


FIND1 {[0;30;42m[K �ᥠ�� ��� ��壜��. �驫� �� ��壜�� ��� �⢜�� �� ���嫜.
[K >} T Find, enter text to search for

FIND2 {[0;30;42m[K �ᥠ�� ��� ��壜��. �� �囦� ⨜���� �⢜��;
[K[0;1;32m  Enter [0;30;42m �������    [0;1;32m    I   [0;30;42m ���./����� [0;1;32m    P   [0;30;42m �ञ����   [0;1;32m        [0;30;42m       [K} T Find, enter search options


FREP1 {[0;30;42m[K ������ ����⤦�. �驫� �� ��壜�� ��� �⢜�� �� ���嫜.
[K >} T Find-Replace, enter text to search for

FREP2 {[0;30;42m[K ������ ����⤦�. �驫� �� �� ��壜��.
[K >} T Find-Replace, enter text to replace with

FREP3 {[0;30;42m[K ������ ����⤦�. �� �囦� ⨜���� �⢜��;
[K[0;1;32m  Enter [0;30;42m �������    [0;1;32m    I   [0;30;42m ���./����� [0;1;32m    P   [0;30;42m �ञ����   [0;1;32m        [0;30;42m       [K} T Find-Replace, enter search options

FREP4 {[0;30;42m[K �� ��壜�� ��⟞��. �� �� ������������;
[K[0;1;32m    Y   [0;30;42m ���        [0;1;32m    N   [0;30;42m ���        [0;1;32m    A   [0;30;42m ��� �� 梘 [0;1;32m    Q   [0;30;42m ���ਫ਼[K} T Find-Replace, replace commands


RMARG {[0;30;42m[K �矣��� ������ ������妬. �驫� ⤘� ������ (20-999).
[K >} T Set right margin


QUIT {[0;30;42m[K �������� ��������驫� 櫠 �⢜�� �� ��������寜�� �� ��壜�� ���.
[K[0;1;32m    Y   [0;30;42m ���        [0;1;32m    N   [0;30;42m ���        [0;1;32m        [0;30;42m            [0;1;32m        [0;30;42m        [K} T Quit, ask for confirmation


XFERERR {[0;1;31m
!J���ᣘ�, �� ����� ��� �梠� ������墘�� �៞��. ��������磜
��������婫� ��� �������� ����㣘��� ��� �� �����.!)
[0;1m[2J} T Editor error, unable to open uploaded file


CLRSCR {[2J} T Clear screen upon exit (possibly faster than curses)


SAVEERR {[0;1;31m


!J���ᣘ�, ��㨥� �៦� ������� ��ᚤਫ਼� ���� ��� ����㡜���
��� ����妬 (�秦� Unix �៦��: #%d, %s).!)
[0;1m} T Editor error, unable to save file


LANG {}

LOADERR {[0;1;31m
!WThe size of the text is beyond the limit of [37m%d[31m bytes.
It cannot be loaded into the editor and has been truncated.!)
!0l[0;1m

[2J} T File is too big


STOVR {Overwrite} T Top Status line 'Overwrite' string

STINS {Insert   } T Top Status line 'Insert' string


STNONE {No formatting} T Top Status line 'no formatting' string

STLEFT {Left-flush   } Top Status line 'left flush' string

STRGHT {Right-flush  } Top Status line 'right flush' string

STCNTR {Centre       } Top Status line 'centre' string

STJUST {Justify      } Top Status line 'justify' string


STATUST {[0;30;46m[K%4d,%-3d  %6d/%d bytes  %s  %s  Width %d} T Top Status line


STATUSB {[K[0;1;36m Escape [0;30;46m Meta (M-)  [0;1;36m Ctrl-O [0;30;46m Format     [0;1;36m Ctrl-K [0;30;46m Blocks     [0;1;36m Ctrl-L [0;30;46m Redraw[K
[K[0;1;36m Ctrl-R [0;30;46m Help       [0;1;36m Ctrl-S [0;30;46m Save, exit [0;1;36m Ctrl-C [0;30;46m Abort      [0;1;36m Tab    [0;30;46m Reformat[K} T Bottom Status lines

STATUSM {[K[0;30;42m Meta-              [0;1;32m    V   [0;30;42m Page up    [0;1;32m    <   [0;30;42m Top        [0;1;32m    X   [0;30;42m Save, exit[K
[K[0;1;32m Ctrl-R [0;30;42m Help       [0;1;32m    %   [0;30;42m Find/repl. [0;1;32m    >   [0;30;42m Bottom     [0;1;32m    Q   [0;30;42m Abort     [K} T Bottom Status lines, meta key

STATUSO {[K[0;30;42m Formatting-        [0;1;32m    I   [0;30;42m Insert     [0;1;32m    L   [0;30;42m Left       [0;1;32m    C   [0;30;42m Centre[K
[K[0;1;32m Ctrl-R [0;30;42m Help       [0;1;32m    R   [0;30;42m Right      [0;1;32m    J   [0;30;42m Justify    [0;1;32m    N   [0;30;42m None  [K} T Bottom Status lines, formatting

STATUSK {[K[0;30;42m Blocks-            [0;1;32m    B   [0;30;42m Begin      [0;1;32m    K   [0;30;42m End        [0;1;32m    C   [0;30;42m Copy     [K
[K[0;1;32m Ctrl-R [0;30;42m Help       [0;1;32m    V   [0;30;42m Move       [0;1;32m    Y   [0;30;42m Delete     [0;1;32m        [0;30;42m       [K} T Bottom Status lines, blocks 


ERRSIZ {[0;1;33;41m[KYou have reached the size limit.} T Error: reached size limit

ERRFMT {[0;1;33;41m[KYour text has surpassed the size limit. It will be truncated upon exit.} T Error: exceeded size limit


HELP1 {[0;1;47;37m �����������������������������������������������������������������������������[0;47;30m� [0m
[0;1;47;37m � [0;30;47mFull Screen Editor                                         HELP - Page 1/4 � [0m
[0;1;47;37m � [0;30;47m�������������������������������������������������������������������������� � [0m
[0;1;47;37m � ������:[0;30;47m C-P  [34mMove up         [30mC-N  [34mMove down      [30m�����������������������Ŀ [0;47;30m� [0m
[0;1;47;37m � [0;30;47m        C-B  [34mMove left       [30mC-F  [34mMove right     [30m� Home: �  Up   � PgUp: � [0;47;30m� [0m
[0;1;47;37m � [0;30;47m        C-A  [34mGo to column 1  [30mC-E  [34mEnd of line    [30m�  C-A  �  C-P  �  C-T  � [0;47;30m� [0m
[0;1;47;37m � [0;30;47m        C-T  [34mPage up         [30mC-V  [34mPage down      [30m�����������������������Ĵ [0;47;30m� [0m
[0;1;47;37m � [0;30;47m        C-Q  [34mTop of text     [30mC-W  [34mBottom of text [30m� Left: �       � Rght: � [0;47;30m� [0m
[0;1;47;37m � [0;30;47m        M-<  [34mTop of text     [30mM->  [34mBottom of text [30m�  C-B  �       �  C-F  � [0;47;30m� [0m
[0;1;47;37m � [0;30;47m                                                 �����������������������Ĵ [0;47;30m� [0m
[0;1;47;37m � [0;30;47m        Or use the arrow keys (ANSI/VT).         � End:  � Down: � PgDn: � [0;47;30m� [0m
[0;1;47;37m � [0;30;47m                                                 �  C-E  �  C-N  �  C-V  � [0;47;30m� [0m
[0;1;47;37m � ��������: [0;30;47mC-D  [34mDelete next character             [30m������������������������� [0;47;30m� [0m
[0;1;47;37m �           [0;30;47mC-Y  [34mDelete current line                                         [0;47;30m� [0m
[0;1;47;37m �                                                                            [0;47;30m� [0m
[0;1;47;37m � [0;30;47m (C-A = Ctrl-A, M-A = Esc + A or Alt-A if you're on a Un*x console)        [0;47;30m� [0m
[0;1;47;37m � [0;30;47m (1 second after pressing a special key, two help lines will appear)       [0;47;30m� [0m
[0;1;47;37m �                                                                            [0;47;30m� [0m
[0;1;47;37m � [0;30;47m Enter for the next page, any other key to return.                         [0;47;30m� [0m
[0;1;47;37m �[0;47;30m����������������������������������������������������������������������������� [0m
} T Help, page 1 (basic commands)


HELP2 {[0;1;47;37m �����������������������������������������������������������������������������[0;47;30m� [0m
[0;1;47;37m � [0;30;47mFull Screen Editor                                         HELP - Page 2/4 � [0m
[0;1;47;37m � [0;30;47m�������������������������������������������������������������������������� � [0m
[0;1;47;37m � OTHER COMMANDS:[0;30;47m                                                            � [0m
[0;1;47;37m � [0;30;47m    C-K F [34mSearch for text                                                  [0;47;30m� [0m
[0;1;47;37m � [0;30;47m    C-U   [34mFind next occurence                                              [0;47;30m� [0m
[0;1;47;37m � [0;30;47m    C-K A [34mFind and replace text                                            [0;47;30m� [0m
[0;1;47;37m � [0;30;47m                                                                           � [0m
[0;1;47;37m � [0;30;47m    C-K B [34mSet beginning of block                                           [0;47;30m� [0m
[0;1;47;37m � [0;30;47m    C-K K [34mSet end of block                                                 [0;47;30m� [0m
[0;1;47;37m � [0;30;47m    C-K C [34mCopy block                                                       [0;47;30m� [0m
[0;1;47;37m � [0;30;47m    C-K M [34mMove block                                                       [0;47;30m� [0m
[0;1;47;37m � [0;30;47m    C-K V [34mMove block                                                       [0;47;30m� [0m
[0;1;47;37m � [0;30;47m    C-K Y [34mDelete block                                                     [0;47;30m� [0m
[0;1;47;37m � [0;30;47m                                                                           � [0m
[0;1;47;37m � [0;30;47m    C-K R [34mSet right margin                                                 � [0m
[0;1;47;37m � [0;30;47m                                                                           [0;47;30m� [0m
[0;1;47;37m � [0;30;47m                                                                           � [0m
[0;1;47;37m � [0;30;47m Enter for the next page, any other key to return.                         [0;47;30m� [0m
[0;1;47;37m �[0;47;30m����������������������������������������������������������������������������� [0m
} T Help, page 2 (blocks, etc.)


HELP3 {[0;1;47;37m �����������������������������������������������������������������������������[0;47;30m� [0m
[0;1;47;37m � [0;30;47mFull Screen Editor                                         HELP - Page 3/4 � [0m
[0;1;47;37m � [0;30;47m�������������������������������������������������������������������������� � [0m
[0;1;47;37m � TEXT FORMATTING:[0;30;47m                                                           [0;47;30m� [0m
[0;1;47;37m � [0;30;47m    C-O I or M-I [34mInsert/Overtype mode                                      [0;47;30m� [0m
[0;1;47;37m � [0;30;47m    C-O L or M-L [34mLeft justify (wrap around)                                [0;47;30m� [0m
[0;1;47;37m � [0;30;47m    C-O C or M-C [34mCentre lines                                              [0;47;30m� [0m
[0;1;47;37m � [0;30;47m    C-O R or M-R [34mFlush right                                               [0;47;30m� [0m
[0;1;47;37m � [0;30;47m    C-O J or M-J [34mLeft and right justification                              [0;47;30m� [0m
[0;1;47;37m � [0;30;47m    C-O N or M-N [34mNo formatting (not recommended)                           [0;47;30m� [0m
[0;1;47;37m �                                                                            [0;47;30m� [0m
[0;1;47;37m � [0;30;47m    Tab         [34mReformat paragraph starting from current line              [0;47;30m� [0m
[0;1;47;37m �                                                                            [0;47;30m� [0m
[0;1;47;37m � [0;47;30mLines  typed  are  automatically formatted  when Enter is  pressed, if the � [0m
[0;1;47;37m � [0;47;30mformatting mode is 'flush right' or 'centre'. For left justification, your � [0m
[0;1;47;37m � [0;47;30mtext is formatted while you type.  For left and right justification, there � [0m
[0;1;47;37m � [0;47;30mis no auto formatting. Press Tab to format the current paragraph.          � [0m
[0;1;47;37m �                                                                            [0;47;30m� [0m
[0;1;47;37m � [0;30;47m Enter for the next page, any other key to return.                         [0;47;30m� [0m
[0;1;47;37m �[0;47;30m����������������������������������������������������������������������������� [0m
} T Help, page 3 (formatting)


HELP4 {[0;1;47;37m �����������������������������������������������������������������������������[0;47;30m� [0m
[0;1;47;37m � [0;30;47mFull Screen Editor                                         HELP - Page 4/4 � [0m
[0;1;47;37m � [0;30;47m�������������������������������������������������������������������������� � [0m
[0;1;47;37m � SPECIAL COMMANDS AND EXITING:[0;30;47m                                              [0;47;30m� [0m
[0;1;47;37m �                                                                            [0;47;30m� [0m
[0;1;47;37m � [0;47;30mC-S or M-X  [34mSave the text and exit                                         [30m� [0m
[0;1;47;37m � [0;47;30mC-Y or M-Q  [34mAbort the editing session and lose the text                    [30m� [0m
[0;1;47;37m � [0;47;30mC-X         [34mMove the text to the line editor                               [30m� [0m
[0;1;47;37m �                                                                            [0;47;30m� [0m
[0;1;47;37m � [0;47;30mC-Z         [34mUpload a preformatted file into the editor                     [30m� [0m
[0;1;47;37m �                                                                            [0;47;30m� [0m
[0;1;47;37m � [0;47;30mYou can upload files  with special characters  (eg ANSI directives)  using � [0m
[0;1;47;37m � [0;47;30mthe upload command. Any special  characters will appear as question-marks� � [0m
[0;1;47;37m � [0;47;30m('?'). Formatting the text is entirely your responsibility.                � [0m
[0;1;47;37m �                                                                            [0;47;30m� [0m
[0;1;47;37m � [0;47;30mIf, during exit from the editor,  your text is over the size limit (eg due � [0m
[0;1;47;37m � [0;47;30mto reformatting), it will be truncated.                                    � [0m
[0;1;47;37m �                                                                            [0;47;30m� [0m
[0;1;47;37m � [0;30;47m Press any key to return to the editor.                                    [0;47;30m� [0m
[0;1;47;37m �[0;47;30m����������������������������������������������������������������������������� [0m
} T Help, page 4 (exiting etc.)


FIND1 {[0;30;42m[K Find text. Please enter the text to search for.
[K >} T Find, enter text to search for

FIND2 {[0;30;42m[K Find text. Please enter the desired search type:
[K[0;1;32m  Enter [0;30;42m Strict     [0;1;32m    I   [0;30;42m No case    [0;1;32m    P   [0;30;42m Phonetic   [0;1;32m        [0;30;42m       [K} T Find, enter search options


FREP1 {[0;30;42m[K Find/Replace. Enter the text to search for.
[K >} T Find-Replace, enter text to search for

FREP2 {[0;30;42m[K Find/Replace. Enter the replacement text.
[K >} T Find-Replace, enter text to replace with

FREP3 {[0;30;42m[K Find/Replace. Please enter the desired search type:
[K[0;1;32m  Enter [0;30;42m Strict     [0;1;32m    I   [0;30;42m No case    [0;1;32m    P   [0;30;42m Phonetic   [0;1;32m        [0;30;42m       [K} T Find-Replace, enter search options

FREP4 {[0;30;42m[K The text was located. Replace it?          
[K[0;1;32m    Y   [0;30;42m Yes        [0;1;32m    N   [0;30;42m No         [0;1;32m    A   [0;30;42m Yes to all [0;1;32m    Q   [0;30;42m Cancel [K} T Find-Replace, replace commands


RMARG {[0;30;42m[K Set right margin. Please enter a number (20-79).
[K >} T Set right margin


QUIT {[0;30;42m[K Please confirm that you intend to lose your text.    
[K[0;1;32m    Y   [0;30;42m Yes        [0;1;32m    N   [0;30;42m No         [0;1;32m        [0;30;42m            [0;1;32m        [0;30;42m        [K} T Quit, ask for confirmation


XFERERR {[0;1;31m
!JSorry, the file you just uploaded was lost. Please
notify the system operator about this incident.!)
[0;1m[2J} T Editor error, unable to open uploaded file


CLRSCR {[2J} T Clear screen upon exit (possibly faster than curses)

SAVEERR {[0;1;31m


!JSorry, there was an I/O error while saving the file (Unix error: #%d,
%s).!)
[0;1m} T Editor error, unable to save file





LANGEND {}
