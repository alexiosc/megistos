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
[0;1;31m��� ⮜�� ����� ��� �������� ���� ��� ������.
[0;1m} T Error: no files or tags to transfer, exiting


FNOTFND {
[0;1;31m���ᣘ�, �� ����� "%s" ��� ��ᨮ�� ��⦤.
} T File not found


MINSNG {�} T Minutes, singular suffix

MINPLR {�} T Minutes, plural suffix


DNLHDR {[0;1m
[47m ����������������������������������������������������������������������������[0;47;30m� [0m
[1;47;37m � [0;47;30m�����:  [31m%-16s  %-46s [30m� [40m
[1;47;37m � [0;47;30m�⚜���: [31m%-8d          [30m��椦� �������� (���� ����⚚���): [31m%4d ����%s [30m� [0m
[1;47;37m � [0;47;30m�秦�:   [31m%-64s [30m� [0m
[1;47;37m � [0;47;30m������������������������������������������������������������������������� [30m� [0m
} T Download header for single files


DNLHDR1 {[0;1m
[47m ����������������������������������������������������������������������������[0;47;30m� [0m
[1;47;37m � [0;47;30m�������� �⚜���: [31m%-8d [30m��椦� �������� (���� ����⚚���): [31m%4d ����%s [30m� [0m
[1;47;37m � [0;47;30m������������������������������������������������������������������������� [30m� [0m
} T Download header for multiple files (no info pane)


PROTLIN1 {[1;47;37m � [0;47;34m%-2s[30m%33s � } T Protocol Menu Line, First Half


PROTLIN2 {[34m%-2s[30m%33s [30m� [0m
} T Protocol Menu Line, Seconf Half


DNLFTR {[1;47;37m � [0;47;30m������������������������������������������������������������������������� [30m� [0m
[1;47;37m � [0;47;34mT [30m . (tag) � �㯞 �� �夜� ���櫜�� � [34mTE[30m . . . . . . . . . . . Tag Editor [30m� [0m
[1;47;37m � [0;47;34mTT[30m  .  �㯞 �� tagged ������: [31m%3s[30m � �����⩫� [34m![30m ��� ���棘�� ����礛��� [30m� [0m
} T Download footer with tag commands


DNLFTRT {[1;47;37m � [0;47;30m������������������������������������������������������������������������� [30m� [0m
[1;47;37m � [0;47;30mT [30m . (tag) � �㯞 �� �夜� ���櫜�� � �����⩫� [34m![30m ��� ���棘�� ����礛��� [30m� [0m
} T Download footer without tag commands


DNLFTRI {[1;47;37m � [0;47;30m������������������������������������������������������������������������� [30m� [0m
[1;47;37m � [0;47;30m���� �㯞 �����: [31m%4d[30m      ����� ��� �� ������ ���櫜�� (tagged): [31m%4d [30m� [0m
} T Download footer, file information


DNLFTRL {[1;47;37m �[0;47;30m���������������������������������������������������������������������������� [0m
[0m} T Download footer, last line


YES {���} T "Yes" string


NO {���} T "No" string


VIEWNAME {�����騞�� %s ����妬} T Name of the viewer "protocol"


FTUNK {(���驫�� �秦� - ��㨥� �៦�)} T File type detection failed


SHORT {[0;1m
!W�驫� ��� ������� ���, � [33mX[37m ��� ⥦��, � [33m?[37m ��� �� �����:!) [0m} T Short menu


ERRSEL {
[0;1;31m���ᣘ�, ��� ��ᨮ�� ������� "%s".
[0;1m} T Oops, no such option


CONFX {[0;1;31m
!W�����餦���� �� �㯞 ����ਠ�� ������, �ᤦ��� �� �����. ��
��������實��� �� �㯞; ([[33mY[31m]es=��� / [[33mN[31m]o=殠)!) [0m} T Confirm exit



VIEWWRK {
[s[0;1;36;5m�������� �����⤜��... } T Preparing file viewer - please wait


VIEWBEG {[u[0;1m[K[0;32m��  [1m������棜�� ��� ����妬 [37m%s  [42m[K[0;1m

[0;1m} T Viewing archive contents


VIEWEND {
[0;42m[K[0;1m
[0;1m} T Viewing archive contents


CANTAG {[0;1;31m
!J�� ����� [37m%s[31m �夘� ����ਠ��. ��⧜� �� �� �ᙜ�� �騘, ��� ���
��� �夘� �嚦��� 櫠 �� ��ᨮ�� ���櫜��.!)
[0;1m} T Unable to tag transient file


TAGSOMEFIL {[0;1;31m
!J��� �����㟞�� � �㯞 �� �� ������. ��
�������夘��� ����� �夘� ����ਠ�� ��� ��� ��ᨮ�� ���瞩� 櫠 �� ��ᨮ���
��� �ᩞ ���櫜��. �� ��⧜� �� �� �ᙜ�� � �� ����驜�� �騘.!) [0;1m} T
Tagged some files, must download the rest


TAGFIL {
[0;1m���ᥜ�, � �㯞 ����ᢢ����...
} T Tagged all files, download postponed


TAGSOM {
!J[0;1m���ᥜ�, � �㯞 �� �� ����ਠ�� ������ ����ᢢ����.
�� ��⧜� �� �� �ᙜ�� � �� �����驜�� �� ����ਠ�� �����.!)
} T Tagged all files, download postponed


SUPLOAD {��������} T 'Upload' (used in XFERBEG)

SDNLOAD {�㯞} T 'Download'(used in XFERBEG)

SSINGLE {����妬} T 'file' (used in XFERBEG)

SMULTI {������} T 'files' (used in XFERBEG)
 

XFERBEG {
[0;1;32m
[5m��  [0;1;32m������� ��� [37m%s %s[32m �� �� ���桦�� [37m%s[32m.
    ��⩫� [33m%s[32m ������ ���� ��� ���ਫ਼.[0;1m

} T Transfer begins now


DNLFAIL {

[0;1;31;5m��  [0;1;31m� �㯞 ����槞��.

[32m����� �� ����� � �㯞 ��������: [37m%d
} T Download failed


RETRY {[0;1m
�⢜�� �� �������㩜�� ��� �㯞 ᢢ� �� ����; ([[33mY[37m]es=��� / [[33mN[37m]o=殠) } T Retry failed download?


TEMENU {
[0;47;1;37m ���������������������������������������������������[0;30;47m� [0m
[47;1;37m �  [0;47;30mTag Editor                                      [0;47;30m� [0m
[47;1;37m �  [0;47;30m����������������������������������������������  [0;47;30m� [0m
[47;1;37m �  [0;31;47mL[30mist files . . . . . . . . . ���ᢦ��� ������  [30m� [0m
[47;1;37m �  [0;31;47mT[30mag/untag file . . . . . ������� �㯞� ����妬  [30m� [0m
[47;1;37m �  [0;31;47mD[30melete/undelete file .  �����ਫ਼ �㯞� ����妬  [30m� [0m
[47;1;37m �  [0;31;47mS[30mtatistics . . . . . . . . ���������� �������  [30m� [0m
[47;1;37m �                                                  [0;47;30m� [0m
[47;1;37m � [0;30;47me[31mX[30mit . . . . . . . . . . . . . . . . . . ������  [30m� [0m
[47;1;37m �[0;30;47m��������������������������������������������������� [0m
} T Tag Editor menu


TESHMNU {[0;1m
!W�驫� ��� ������� ��� ([33mL[37m,[33mT[37m,[33mD[37m,[33mS[37m,[33mX[37m ��� ⥦��, � [33m?[37m ��� �� �����):!) [0m} T Tag Editor Short menu


TEERR {
[0;1;31m���ᣘ�, ��� ��ᨮ�� ������� "%c".
[0;1m} T Tag Editor, no such option


TELHDR {[0;1m
           ���ᢦ��� �� �� ���� �㯞 ������:
               ����������������Ŀ
               �[33m�������[37m�[33m�����ਫ਼[37m�
��������������������Ŀ � �������������������������������������������������Ŀ
�[33m�/�[37m�[33m�����[37m          � � �[33m��������� ����妬[37m                                �
��������������������������������������������������������������������������Ĵ
} T Tag Editor file list header


TELMRK {�} T Tag Editor file list mark


TELTAB {[0;1m�[32m%3d[37m�[32m%-16s[37m�[32m%-1s[37m�[32m%-1s[37m�[32m%-49s[37m�
} Tag Editor file list


TELFTR {[0;1m����������������������������������������������������������������������������
} Tag Editor file list footer


TENASK {[0;1m
�驫� ��� ������ ��� ����妬 ([33mX[37m ��� ⥦��): [0m} T Tag Editor file number prompt


TENERR {[0;1;31m
�������� �驫� ⤘� ������ ����妬 ������ %d ��� %d.
[0;1m} T Tag Editor bad file number


TENTAG {[0;1;32m
� �㯞 ��� ����妬 [37m%d (%s)[32m �����㟞��.
[0;1m} T Tag Editor, file tagged.


TENUTG {[0;1;32m
���� ��� ������� �㯞� ��� ����妬 [37m%d (%s)[32m.
[0;1m} T Tag Editor, file untagged.


TENKLL {[0;1;32m
� �㯞 ��� ����妬 [37m%d (%s)[32m �����韞��.
[0;1m} T Tag Editor, file killed.


TENUKL {[0;1;32m
���� ��� �����ਫ਼� �㯞� ��� ����妬 [37m%d (%s)[32m.
[0;1m} T Tag Editor, file unkilled.


TESTAT {[0;36m
��  [1m���������� ������� �������� ������  [46m[K[0;1m

[37m���� �㯞:
[32m  �����: [37m%8d
[32m  �⚜���:[37m%8d bytes
[32m  ��椦�: [37m%8d ����%s

[37m�����㟞���:
[32m  �����: [37m%8d
[32m  �⚜���:[37m%8d bytes

[46m[K[0;1m
} T Tag Editor transfer statistics


CRDSNG {�} T Credits, singular form

CRDPLR {��} T Credits, plural form


REFUND {[0;1;35m
!W��� ������⭦���� [37m%d [35m����%s ��椦� ��㩞� ��� ����� ��
����� � �㯞 �����韞��.!)
} T Credits being refunded


DISCON {[0;1m

[33;5m��[0;1;33m  �������� ����������  !F�[0;1;33m

� �礛��� ��� ������坜��� ���棘��, �� �官�� ���㩜�.

!W��⩫� [33;5mEsc[0;1;33m, [33;5mEnter[0;1;33m, � [33;5mSpace[0;1;33m
��� ���ਫ਼ ��� ��������嘪.!)

[32m���婫���� �⫨���: [0;1m[s} T Automatic Disconnection


COUNTDN {[u[s%02d[30m[K} T Automatic Disconnection countdown


ADABORT {[0;1;32m[K

� ���棘�� ����礛��� ����韞��!
[0;1m} T Automatic Disconnection aborted


UPLHDR {[0;1m
[47m ����������������������������������������������������������������������������[0;47;30m� [0;1m
[1;47;37m � [0;34;47m�������� ������. �驫� �� ��������� ���桦�� ��������.                 [30m� [0;1m
[1;47;37m � [0;47;30m������������������������������������������������������������������������� [30m� [0;1m
} T Upload header


UPLFTR {[1;47;37m � [0;47;30m������������������������������������������������������������������������� [30m� [0;1m
[1;47;37m � [0;47;30m �����⩫� [34m![30m ��� ���棘�� ����礛��� ���� ��� ��������                    � [0;1m
[1;47;37m �[0;47;30m���������������������������������������������������������������������������� [0;1m
} T Upload footer


LNKNAM {Link �� ��ᨮ�� �����} S 40 Name of the 'link' protocol:


UPLFAIL {

[0;1;31;5m��  [0;1;31m� �������� ����槞��.

} T Upload failed


URETRY {[0;1m
�⢜�� �� �������㩜�� ��� �������� ᢢ� �� ����; ([[33mY[37m]es=��� / [[33mN[37m]o=殠) } T Retry failed upload?


LNKASK {[0;1m
!W�������� �驫� �� ��㨜� directory ��� 椦�� ��� ����妬 ��� �⢜�� �� ���᚜��: [0m!)} T Link file: What file?


LNKERR {[0;1;31m
�� ����� %s ��� ��夜��� �� ��ᨮ��. ���������ᩫ�.
[0;1m} T Link file: Unable to locate file


LINKOK {[0;1;32m
�� ����� %s ��⟞��, ��� ��������㟞�� symbolic link ���� ����.
[0;1m} T Link file: ok


FILSNG {��} T 'file' singular form
FILPLR {�} T 'file' plural form

LOGOUT {[0;1;32m
[5m��[0;1;32m  !i!W����� ����ᢜ� ��� �㯞 [37m%d �����%s[32m.!)
!0l[0;1m} T Logout: you have tagged N files


LOGOUT2 {[0;1m
���� �夘� � �������� ��� ������� ��� �� �����������㩜�� ��� �㯞.
�⢜�� �� �夜� �騘 � �㯞; ([[33mY[37m]yes=��� / [[33mN[37m]o=殠):!)[0m } T Logout: do you want to receive tagged files?


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
[47m ����������������������������������������������������������������������������[0;47;30m� [0m
[1;47;37m � [0;47;30mFile: [31m%-16s  %-49s [30m� [40m
[1;47;37m � [0;47;30mSize: [31m%-8d                [30mTransfer time (approximately): [31m%4d minute%1s [30m� [0m
[1;47;37m � [0;47;30mType: [31m%-67s [30m� [0m
[1;47;37m � [0;47;30m������������������������������������������������������������������������� [30m� [0m
} T Download header for single files


DNLHDR1 {[0;1m
[47m ����������������������������������������������������������������������������[0;47;30m� [0m
[1;47;37m � [0;47;30mTotal size: [31m%-8d          [30mTransfer time (approximately): [31m%4d minute%1s [30m� [0m
[1;47;37m � [0;47;30m������������������������������������������������������������������������� [30m� [0m
} T Download header for multiple files (no info pane)


PROTLIN1 {[1;47;37m � [0;47;34m%-2s[30m%33s � } T Protocol Menu Line, First Half


PROTLIN2 {[34m%-2s[30m%33s [30m� [0m
} T Protocol Menu Line, Seconf Half


DNLFTR {[1;47;37m � [0;47;30m������������������������������������������������������������������������� [30m� [0m
[1;47;37m � [0;47;34mT [30m . . . .  (tag) Postpone download � [34mTE[30m . . . . . . . . . . . Tag Editor [30m� [0m
[1;47;37m � [0;47;34mTT[30m  . .  Download tagged files: [31m%3s[30m � Append [34m![30m for auto-hangup when done  [30m� [0m
} T Download footer with tag commands


DNLFTRT {[1;47;37m � [0;47;30m������������������������������������������������������������������������� [30m� [0m
[1;47;37m � [0;47;30mT [30m . . . .  (tag) Postpone download � Append [34m![30m for auto-hangup when done  [30m� [0m
} T Download footer without tag commands


DNLFTRI {[1;47;37m � [0;47;30m������������������������������������������������������������������������� [30m� [0m
[1;47;37m � [0;47;30mFiles to download: [31m%4d[30m       Files to be downloaded later (tagged): [31m%4d [30m� [0m
} T Download footer, file information


DNLFTRL {[1;47;37m �[0;47;30m���������������������������������������������������������������������������� [0m
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


VIEWBEG {[u[0;1m[K[0;32m��  [1mContents of file [37m%s  [42m[K[0;1m

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
[5m��  [0;1;32mReady to [37m%s %s[32m with the [37m%s[32m protocol.
    Press [33m%s[32m a few times to abort.[0;1m

} T Transfer begins now


DNLFAIL {

[0;1;31;5m��  [0;1;31mThe download was aborted.

[32mFiles still to be downloaded: [37m%d
} T Download failed


RETRY {[0;1m
Would you like to try once more? ([[33mY[37m]es / [[33mN[37m]o) } T Retry failed download?


TEMENU {
[0;47;1;37m �������������������������[0;30;47m� [0m
[47;1;37m �  [0;47;30mTag Editor            [0;47;30m� [0m
[47;1;37m �  [0;47;30m��������������������� [0;47;30m� [0m
[47;1;37m �  [0;31;47mL[30mist files            [30m� [0m
[47;1;37m �  [0;31;47mT[30mag/untag file        [30m� [0m
[47;1;37m �  [0;31;47mD[30melete/undelete file  [30m� [0m
[47;1;37m �  [0;31;47mS[30mtatistics            [30m� [0m
[47;1;37m �                        [0;47;30m� [0m
[47;1;37m � [0;30;47me[31mX[30mit                   [30m� [0m
[47;1;37m �[0;30;47m������������������������� [0m
} T Tag Editor menu


TESHMNU {[0;1m
!WEnter your choice ([33mL[37m,[33mT[37m,[33mD[37m,[33mS[37m,[33mX[37m to exit, or [33m?[37m for the menu):!) [0m} T Tag Editor Short menu


TEERR {
[0;1;31mSorry, "%c" is not an option here.
[0;1m} T Tag Editor, no such option


TELHDR {[0;1m
                   ����������Ŀ
                   �[33mTag[37m�[33mCancel[37m�
��������������������Ŀ � �������������������������������������������������Ŀ
�[33m # [37m�[33mFile[37m            � � �[33mDescription      [37m                                �
��������������������������������������������������������������������������Ĵ
} T Tag Editor file list header


TELMRK {�} T Tag Editor file list mark


TELTAB {[0;1m�[32m%3d[37m�[32m%-16s[37m�[32m%-1s[37m�[32m%-1s[37m�[32m%-49s[37m�
} Tag Editor file list


TELFTR {[0;1m����������������������������������������������������������������������������
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
��  [1mFile transfer statistics  [46m[K[0;1m

[37mTo download:
[32m  Files:    [37m%6d
[32m  Size:     [37m%6d bytes
[32m  Time:     [37m%6d ����%s

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

[33;5m��[0;1;33m  AUTOMATIC DISCONNECTION  !F�[0;1m

Your connection will be terminated automatically in a moment.

!WPress [33;5mEsc[0;1;33m, [33;5mEnter[0;1;33m, or [33;5mSpace[0;1;33m
to cancel the disconnection.!)

[32mCountdown: [0;1m[s} T Automatic Disconnection


COUNTDN {[u[s%02d[30m[K} T Automatic Disconnection countdown


ADABORT {[0;1;32m[K

Automatic disconnection aborted!
[0;1m} T Automatic Disconnection aborted


UPLHDR {[0;1m
[47m ����������������������������������������������������������������������������[0;47;30m� [0;1m
[1;47;37m � [0;34;47mFile upload. Please enter your desired file transfer protocol.            [30m� [0;1m
[1;47;37m � [0;47;30m������������������������������������������������������������������������� [30m� [0;1m
} T Upload header


UPLFTR {[1;47;37m � [0;47;30m������������������������������������������������������������������������� [30m� [0;1m
[1;47;37m � [0;47;30m Append [34m![30m for automatic disconnection when done                           � [0;1m
[1;47;37m �[0;47;30m���������������������������������������������������������������������������� [0m} T Upload footer


LNKNAM {Link an existing file} S 40 Name of the 'link' protocol:


UPLFAIL {

[0;1;31;5m��  [0;1;31mThe upload was aborted.

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
[5m��[0;1;32m  !i!WYou have tagged [37m%d file%s[32m for later download.!)
!0l[0;1m} T Logout: you have tagged N files


LOGOUT2 {[0;1m
This is your last chance to download the file(s).
Do you want to do so now? ([[33mY[37m]yes / [[33mN[37m]o):!)[0m } T Logout: do you want to receive tagged files?


LANGEND {}
