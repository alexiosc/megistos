LEVEL2 {}

ENTRYKEY {Key required to enter the File Library: 0} N 0 129

LIBOPKEY {Key required for privileged access: 128} N 0 129

DEFRKEY {Default read key for new libraries: 128} N 0 129

DEFDKEY {Default download key for new libraries: 128} N 0 129

DEFUKEY {Default upload key for new libraries: 128} N 0 129

DEFOKEY {Default overwrite key for new libraries: 128} N 0 129

DEFFLIM {Default maximum number of files for new libraries: 1000} N 0 1000000

DEFSLIM {Default maximum size (in Kb) of any file for new libraries: 1024} N 0 1024000

DEFLLIM {Default maximum total size (in Mb) of new libraries: 10} N 0 10240

DEFUCHG {Default charge for uploading a file: 0} N -1000000 1000000

DEFDCHG {Default charge for downloading a file: 0} N -1000000 1000000

DEFREB {Default user roylaties (percent): 0} N -100 100

DEFUAUD {Default auditing of uploads for new libraries: YES} B

DEFDAUD {Default auditing of downloads for new libraries: YES} B

LIBMAIN {Main} S 19 Name of the Main library

MAXNEST {Maximum nesting level for sublibraries: 12} N 1 12

RDMEFIL {00README} S 32 Name of library long description file

RDMESIZ {Maximum size (in K) of library long description file: 8} N 1 1024

OTHRDME {README README.TXT Readme readme READ.ME Read.me read.me
00Readme 00-Readme 00-README .Readme .README .readme
00INDEX 00-INDEX 00-index 00-Index
welcome.msg welcome WELCOME Welcome welcome.txt WELCOME.TXT Welcome.txt} T Other filenames to try as long descriptions

FILELST {FILES} S 23 Name of library file listing file

FILELSTD {File List for this library} S 43 Description of library file listing

MFILLST {MASTER_FILES} S 23 Name of the master file listing

MFILLSTD {File Listing for all libraries} S 43 Description of master listing


OTHRFLS {00FILES Files files ls-lr LS-LR ls_lr LS_LR FILELIST.TXT filelist.txt
INDEX Index index INDEX.TXT Index.txt index.txt MANIFEST Manifest manifest
MANIFEST.TXT Manifest.txt manifest.txt} T Other filenames to try as file lists (OS libs)


FILEIND {INDEX} S 23 Name of keyword index file 

FILEINDD {Index of keywords for this library} S 43 Description of keyword index


MFILIND {MASTER_INDEX} S 23 Name of master keyword index

MFILINDD {Master keyword index for all libraries} S 43 Master Index description


FILETOP {TOPFILES} S 23 Name of file listing top downloads

NUMTOPS {TOP-<N> most downloaded files listing, <N>= 30} N 5 1000

TOPFILD {Most downloaded files for this library} S 43 Description of top downloads file


MFILETP {MASTER_TOPFILES} S 23 Name of master list of topfiles

NUMMTPS {Number of entries in master topfiles: 100} N 5 1000

MTPFILD {Most downloaded files of this system} S 43 Description of master topfile


SHOWHID {Show files starting with dots in OS-only library listings? NO} B




Notify the filer of any slow devices that are on the same bus
(like CD jukeboxes). Files on devices belonging to the same
group will not be accessed simultaneously.

SLOWDEV0 {/dev/scd*} S 40 Slow devices on the same bus, group 1

Notify the filer of any slow devices that are on the same bus
(like CD jukeboxes). Files on devices belonging to the same
group will not be accessed simultaneously.

SLOWDEV1 {/dev/sbpcd*} S 40 Slow devices on the same bus, group 2

Notify the filer of any slow devices that are on the same bus
(like CD jukeboxes). Files on devices belonging to the same
group will not be accessed simultaneously.

SLOWDEV2 {} S 40 Slow devices on the same bus, group 3

Notify the filer of any slow devices that are on the same bus
(like CD jukeboxes). Files on devices belonging to the same
group will not be accessed simultaneously.

SLOWDEV3 {} S 40 Slow devices on the same bus, group 4

Notify the filer of any slow devices that are on the same bus
(like CD jukeboxes). Files on devices belonging to the same
group will not be accessed simultaneously.

SLOWDEV4 {} S 40 Slow devices on the same bus, group 5

Notify the filer of any slow devices that are on the same bus
(like CD jukeboxes). Files on devices belonging to the same
group will not be accessed simultaneously.

SLOWDEV5 {} S 40 Slow devices on the same bus, group 6

Notify the filer of any slow devices that are on the same bus
(like CD jukeboxes). Files on devices belonging to the same
group will not be accessed simultaneously.

SLOWDEV6 {} S 40 Slow devices on the same bus, group 7

Notify the filer of any slow devices that are on the same bus
(like CD jukeboxes). Files on devices belonging to the same
group will not be accessed simultaneously.

SLOWDEV7 {} S 40 Slow devices on the same bus, group 8


Notify the filer of any slow devices that are on the same bus
(like CD jukeboxes). Files on devices belonging to the same
group will not be accessed simultaneously.

SLOWDEV8 {} S 40 Slow devices on the same bus, group 9


Notify the filer of any slow devices that are on the same bus
(like CD jukeboxes). Files on devices belonging to the same
group will not be accessed simultaneously.

SLOWDEV9 {} S 40 Slow devices on the same bus, group 10


Notify the filer of any slow devices that are on the same bus
(like CD jukeboxes). Files on devices belonging to the same
group will not be accessed simultaneously.

SLOWDEVA {} S 40 Slow devices on the same bus, group 11


Notify the filer of any slow devices that are on the same bus
(like CD jukeboxes). Files on devices belonging to the same
group will not be accessed simultaneously.

SLOWDEVB {} S 40 Slow devices on the same bus, group 12


Notify the filer of any slow devices that are on the same bus
(like CD jukeboxes). Files on devices belonging to the same
group will not be accessed simultaneously.

SLOWDEVC {} S 40 Slow devices on the same bus, group 13


Notify the filer of any slow devices that are on the same bus
(like CD jukeboxes). Files on devices belonging to the same
group will not be accessed simultaneously.

SLOWDEVD {} S 40 Slow devices on the same bus, group 14


Notify the filer of any slow devices that are on the same bus
(like CD jukeboxes). Files on devices belonging to the same
group will not be accessed simultaneously.

SLOWDEVE {} S 40 Slow devices on the same bus, group 15


Notify the filer of any slow devices that are on the same bus
(like CD jukeboxes). Files on devices belonging to the same
group will not be accessed simultaneously.

SLOWDEVF {} S 40 Slow devices on the same bus, group 16


SLDEVTO {Seconds to wait for slow devices to become available? 30} N 1 3600


SLDCMAX {Maximum size of slow device cache (Mbytes)? 2} N 1 1024


SLDCTIM {Maximum age of files in slow device cache (minutes)? 120} N 1 10000


SLDCSMN {Minimum size of file on the cache (kbytes)? 300} N 1 1048576


NUMTRIES {Number of allowed password entry attempts? 3} N 1 1000


DESLEN {Maximum length of long desription? 1910} E 118 374 886 1398 1910 2422 2934 3446 3958


FILEDES {FILE_ID.DIZ file_id.diz} T Detailed description filenames (eg FILE_ID.DIZ)


FNCHARS {$&'()+,-.=@[]^_`~~} S 72 Allowed filename characters (except alphanumeric)


MAXKEYW {Maximum number of keywords per file: 10} N 1 100


ACCMTSD {Accept empty short descriptions for new files? NO} B


SRLSTLN {Number of entries shown in search results: 10} N 2 20














 The Special Interest Groups of The Major BBS have several
 access levels (Zero, Read, Download, Up&download, Sysop)
 that can be assigned by class of user (live/non-live) or
 by specific User-Id.  If you answer YES here, these same
 access restrictions will be applied to LIBs with the same
 name as the SIG (without the leading "/" slash).

 Note:  if you answer YES, then for true "Zero" access to
 any LIB you should give all users only "Read" access to
 the "MAIN" LIB (by creating a "/Main" SIG and configuring
 its live and non-live default access levels to "Read").

SIGAXS {Enforce SIG access levels in the File Library? NO} B

 The "TOPFILES" file is updated every auto-cleanup and
 contains the files that have been downloaded most often
 (excluding of course system files:  LIBS, INDEX, FILES,
 TOPFILES).

 In the MAIN LIB, TOPFILES lists the top downloads from all
 LIBs.  In other LIBs, TOPFILES comes from that LIB only.

 Make this option 0 to disable generation of TOPFILES.

TOPFIL {List how many often-downloaded files in "TOPFILES"? 30} N 0 1000

 You may have configured some LIBs to charge users for
 downloading files (deducting "credits" from the user's
 account).  This option here answers a policy question that
 applies to all LIBs that charge for downloads.

 YES = charge for each file that they start to download, but
 abort for whatever reason.  Answer NO = charge only when
 download completes.  ZMODEM = charge only for completed
 downloads, or ZMODEM downloads whether aborted or not.

CHGABT {Charge users for aborted downloads? NO} E NO YES ZMODEM




LEVEL3 {}


MAINDESCR {ЙЬдлиабу АиоЬажЯубЮ} S 39 Main library description


OSFDESC {АиоЬхж орихк зЬиаЪиШну} S 44 File description for files in OS-only LIBS


NOAXES {[0;1;31m
КмзсгШа, ЫЬд тоЬлЬ зицйЩШйЮ йЬ Шмлу лЮд ЬзавжЪу.
[0;1;31m} T User has no access to chosen area


INFOHDR {[2J[0;1m} T Library information header


MENU {[2J[0m[47;1;37m ┌─────────────────────────────────────────────────────────[0;30;47m┐ [40m
[47;1;37m │  [0;47;30m                     АиоЬажЯубЬк                       [0;47;30m│ [40m
[47;1;37m │  [0;47;30m─────────────────────────────────────────────────────  [0;47;30m│ [40m
[47;1;37m │  [0;31;47mA[30mbout the Library  . . . . . . .  ВЬдабтк ПвЮижнжихЬк  [30m│ [40m
[47;1;37m │  [0;31;47mI[30mnformation . . . . . . . . . ПвЮижнжихЬк ЩаЩважЯубЮк  [30m│ [40m
[47;1;37m │  [0;31;47mT[30mree of libraries  . . . . . . . . . Гжгу ШиоЬажЯЮбщд  [30m│ [40m
[47;1;37m │  [0;31;47mS[30melect library  . . . . . . . . . ДзавжЪу ШиоЬажЯубЮк  [30m│ [40m
[47;1;37m │  [0;31;47mL[30mist of files  . . . . . . . . . .  ЙШлсвжЪжк ШиоЬхрд  [30m│ [40m
[47;1;37m │  [0;31;47mF[30mind files  . . . . . . . . . . . . . .  КупЮ ШиоЬхрд  [30m│ [40m
[47;1;37m │  [0;31;47mD[30mownload files . . . . . . . . . . . . . КупЮ ШиоЬхрд  [30m│ [40m
[47;1;37m │  [0;31;47mU[30mpload files  . . . . . . . . . . .  Азжйлжву ШиоЬхрд  [30m│ [40m
[47;1;37m │                                                         [0;47;30m│ [40m
[47;1;37m │ [0;30;47me[31mX[30mit  . . . . . . . . . . . . . . . . . . . . . ДежЫжк  [30m│ [40m
[47;1;37m └[0;30;47m─────────────────────────────────────────────────────────┘ [0;1m

АиоЬажЯубЮ [32m@LIB@ (@LIBDESCR@)[37m
ПШиШбШвщ ЫщйлЬ лЮд ЬзавжЪу йШк: [0m} T Electronic mail menu


SHORT {[0;1m
АиоЬажЯубЮ [32m@LIB@ (@LIBDESCR@)[37m
!WГщйлЬ лЮд ЬзавжЪу йШк ([33mA[37m,[33mI[37m,[33mT[37m,[33mS[37m,[33mL[37m,[33mF[37m,[33mD[37m,[33mU[37m,[33mX[37m ЪаШ тежЫж, у [33m?[37m ЪаШ лж гЬджч): !)[0m} T Electronic mail short menu


OPMENU {[2J[0m[47;1;37m ┌─────────────────────────────────────────────────────────[0;30;47m┐ [40m
[47;1;37m │  [0;47;30m                 ЗЬфбтк АиоЬажЯубЬк                    [0;47;30m│ [40m
[47;1;37m │  [0;47;30m─────────────────────────────────────────────────────  [0;47;30m│ [40m
[47;1;37m │  [0;31;47mA[30mbout the Library  . . . . . . .  ВЬдабтк ПвЮижнжихЬк  [30m│ [40m
[47;1;37m │  [0;31;47mI[30mnformation . . . . . . . . . ПвЮижнжихЬк ЩаЩважЯубЮк  [30m│ [40m
[47;1;37m │  [0;31;47mT[30mree of libraries  . . . . . . . . . Гжгу ШиоЬажЯЮбщд  [30m│ [40m
[47;1;37m │  [0;31;47mS[30melect library  . . . . . . . . . ДзавжЪу ШиоЬажЯубЮк  [30m│ [40m
[47;1;37m │  [0;31;47mL[30mist of files  . . . . . . . . . .  ЙШлсвжЪжк ШиоЬхрд  [30m│ [40m
[47;1;37m │  [0;31;47mF[30mind files  . . . . . . . . . . . . . .  КупЮ ШиоЬхрд  [30m│ [40m
[47;1;37m │  [0;31;47mD[30mownload files . . . . . . . . . . . . . КупЮ ШиоЬхрд  [30m│ [40m
[47;1;37m │  [0;31;47mU[30mpload files  . . . . . . . . . . .  Азжйлжву ШиоЬхрд  [30m│ [40m
[47;1;37m │  [0;31;47mO[30mperations . . . . . . . . . . . ЛЬджч ШиоЬажЯЮбсиажм  [30m│ [40m
[47;1;37m │                                                         [0;47;30m│ [40m
[47;1;37m │ [0;30;47me[31mX[30mit  . . . . . . . . . . . . . . . . . . . . . ДежЫжк  [30m│ [40m
[47;1;37m └[0;30;47m─────────────────────────────────────────────────────────┘ [0;1m

ЙШврйувЯШлЬ йлЮд ШиоЬажЯубЮ йШк [32m@LIB@ (@LIBDESCR@)[37m
ПШиШбШвщ ЫщйлЬ лЮд ЬзавжЪу йШк: [0m} T Electronic mail menu


OPSHORT {[0;1m
ЙШврйувЯШлЬ йлЮд ШиоЬажЯубЮ йШк [32m@LIB@ (@LIBDESCR@)[37m
!WГщйлЬ лЮд ЬзавжЪу йШк ([33mA[37m,[33mI[37m,[33mT[37m,[33mS[37m,[33mL[37m,[33mF[37m,[33mD[37m,[33mU[37m,[33mO[37m,[33mX[37m ЪаШ тежЫж, у [33m?[37m ЪаШ лж гЬджч): !)[0m} T Electronic mail short menu


ERRSEL {[0;1;31m
КмзсгШа, ЫЬд мзсиоЬа Ю ЬзавжЪу "%c".
[0;1m} T Invalid option selection


LEAVE {[0;1m
!JДежЫжк Шзц лак АиоЬажЯубЬк.!)
[0;1m} T Leaving the account module



ABOUT {[0;1m
!JОа ШиоЬажЯубЬк бШвчзлжмд Ыаснжижмк лжгЬхк, ШдсЪбЬк бШа ЬдЫаШнтиждлШ бШа
жгШЫжзжажчд лШ ШиоЬхШ лЮк @BBS@ тлйа щйлЬ дШ ЫаЬмбжвчджмд лЮд зицйЩШйЮ
бШа вупЮ лжмк.!)

!JАдсвжЪШ гЬ лШ ЬдЫаШнтиждлс йШк гзжиЬхлЬ дШ ЬзавтеЬлЬ лЮд ШиоЬажЯубЮ
Шз'цзжм ЯШ всЩЬлЬ у ЯШ ШзжйлЬхвЬлЬ бсзжаШ ШиоЬхШ орихк дШ ШзШйожвЬхйлЬ
гЬ сввЬк ШиоЬажЯубЬк зжм зЬиатожмд ШиоЬхШ зжм ЫЬд йШк ЬдЫаШнтижмд.!)

!JОа ШиоЬажЯубЬк ЬхдШа жиЪШдргтдЬк аЬиШиоабс, цзрк ШбиаЩщк бШа жа бШлсвжЪжа
бШа мзжбШлсвжЪжа (directories, folders) йлжд мзжвжЪайлу йШк. ЛзжиЬхлЬ дШ
ЫЬхлЬ лж Ытдлиж лрд ШиоЬажЯЮбщд гЬ лЮд Ьдлжву [33mT[37m(ree). ВаШ дШ
ЫаШвтеЬлЬ гхШ Шз'Шмлтк, оиЮйагжзжауйлЬ лЮд Ьдлжву [33mS[37m(elect) бШа
ЫщйлЬ лж цджгШ гаШк ШиоЬажЯубЮк у лЮд звуиЮ лЮк ЫаШЫижгу (зо
[33mwindows/games/arcade[37m). Тж йчйлЮгШ бШлШвШЩШхдЬа бШа лжмк Ычж Ьмитрк
оиЮйагжзжажчгЬджмк оШиШблуиЬк жиайгжч ЫаШЫижгук ([33m/[37m бШа
[33m\[37m). ВдщиагЬк ймдлжгЬчйЬак цзрк [33m/[37m ЪаШ лЮд бЬдлиабу ШиоЬажЯубЮ
у [33m..[37m ЪаШ лЮд зижЮЪжчгЬдЮ (йлЮд аЬиШиохШ) ШиоЬажЯубЮ ЬхдШа ЬзхйЮк
ЫаШЯтйагЬк.!)

!JВаШ дШ ЩиЬхлЬ тдШ ШиоЬхж, гзжиЬхлЬ дШ оиЮйагжзжауйЬлЬ лЮд Ьдлжву
[33mL[37m(ist files) зжм ЫхдЬа тдШд Шзвц бШлсвжЪж ШиоЬхрд. ЛзжиЬхлЬ дШ
псеЬлЬ ЪаШ тдШ ймЪбЬбиагтдж ШиоЬхж гЬ лЮд Ьдлжву [33mF[37m(ind). Дн'цйжд
ЩиЬхлЬ бсла зжм йШк ЬдЫаШнтиЬа, гзжиЬхлЬ дШ лж всЩЬлЬ гЬ лЮд Ьдлжву
[33mD[37m(ownload). ВаШ дШ ШзжйлЬхвЬлЬ ШиоЬхШ, оиЮйагжзжауйлЬ лЮд Ьдлжву
[33mU[37m(pload). Ттвжк, гЬ лЮд Ьдлжву [33mI[37m(nformation) зШхидЬлЬ
ЬблЬдЬхк звЮижнжихЬк ЪаШ лЮд литожмйШ ШиоЬажЯубЮ.!)

[0;1m} T About Libraries


OPLHDR {} T One-line Libop list (for a single library), header

OPLCOMMA {, } T Libop list, comma separated entry

OPLLAST { бШа } T Libop list, last entry

OPLFTR {.} T Libop list, footer

OPLNONE {ХЬаиайлук СмйлугШлжк} T Libop list, no libops


LITRHD {[0;1;32m
ИЬиШиохШ АиоЬажЯЮбщд
!F─
[0;1m} T Library tree listing, header

LITRTB {[0;1m%s[32m%s: [33m%s
} T Library tree listing, line


LITRVR  {   │   } T Library tree listing, vertical line

LITRBRL {   └── } T Library tree listing, last branch

LITRBL  {       } T Library tree listing, no branch (spacing)

LITRBR  {   ├── } T Library tree listing, branch


LITRFT {[0;1;32m!F─
[0;1m} T Library tree listing, footer


SELLIB {[0;1m
!WГаШвтелЬ гаШ ШиоЬажЯубЮ ([33m?[37m ЪаШ бШлсвжЪж):[0;1m!) } T Select library, prompt


SELHELP {[0;1m
!JГаШвтЪждлШк гаШ ймЪбЬбиагтдЮ ШиоЬажЯубЮ зЬиажихЭЬлЬ лЮд ЪбсгШ лрд ЫаШЯтйагрд
ШиоЬхрд йЬ гаШ ймЪбЬбиагтдЮ жгсЫШ зжм йШк ЬдЫаШнтиЬа.
Амлц ШзвжзжаЬх гЬиабтк вЬалжмиЪхЬк цзрк лжд Ьдлжзайгц, лЮд вупЮ, у лЮд
Шзжйлжву ШиоЬхрд.!)
[0;1m
} T Select library, help


SELERR {[0;1;31m
!JГЬд мзсиоЬа ШиоЬажЯубЮ "[37m%s[31m" бслр Шзц лЮд "[37m%s[31m". ГщйлЬ
[33m?[31m ЪаШ дШ ЫЬхлЬ лжд бШлсвжЪж лрд ШиоЬажЯЮбщд, у [33mX[31m ЪаШ
тежЫж йлж зижЮЪжчгЬдж гЬджч.!)
[0;1m} T Select library, library not found


SELNPR {[0;1;31m
!JБихйбЬйлЬ уЫЮ йлЮд бЬдлиабу ШиоЬажЯубЮ. ГЬд гзжиЬхлЬ дШ жзайЯжориуйЬлЬ
сввж.!)
[0;1m} T Select library, no parent library


LIBLSTH {[0;1;32m
ЙШлсвжЪжк ШиоЬажЯЮбщд бслр Шзц лЮд ШиоЬажЯубЮ [37m@LIB@[32m

ОджгШ                АиоЬхШ  kBytes  ПЬиаЪиШну
!F─
[37m} T Library listing, header


LIBLSTP {[0;1m..                   %6d  %6d  АиоЬажЯубЮ %s
} T Library listing, parent library


LIBLSTL {[0;1m%-19s  %6d  %6d  %s
} T Library listing, line


LIBLSTF {[0;1;32m!F─
[0;1m} T Library listing, footer




LIBINFO1 {
[0;36m██  [1m@LIB@ (@LIBDESCR@)  [0;46m[K[0;1m

ГЮгажмиЪуЯЮбЬ . . . . . . . [32m@LIBCRDATE@ @LIBCRTIME@[37m
УзЬчЯмджк/жа . . . . . . .  [32m@LIBOPS@[37m
ПвЮицлЮлШ . . . . . . . . . [32m@LIBNUMFILES@/@LIBFILELIMIT@[37m ШиоЬхШ, [32m@LIBNUMMBYTES@/@LIBLSIZELIMIT@[37m Mbytes
ХитрйЮ вупЮк . . . . . . .  [32m@LIBCHDNL@[37m credit(s)/ШиоЬхж
ХитрйЮ Шзжйлжвук  . . . . . [32m@LIBCHUPL@[37m credit(s)/ШиоЬхж
ДзаЩисЩЬмйЮ Шзжйлжвук  . .  [32m@LIBREBATE@[37m Шдс ШиоЬхж

!J} T Library information, first section (for mere mortals)


LIBINFO2 {
[0;36m██  [1m@LIB@ (@LIBDESCR@)  [0;46m[K[0;1m

АиоЬажЯубЮ . . . . . . . .  [32m@LIB@ (@LIBDESCR@)[37m
ГЮгажмиЪуЯЮбЬ . . . . . . . [32m@LIBCRDATE@ @LIBCRTIME@[37m
УзЬчЯмджк/жа . . . . . . .  [32m@LIBOPS@[37m
ПвЮицлЮлШ . . . . . . . . . [32m@LIBNUMFILES@/@LIBFILELIMIT@[37m ШиоЬхШ, [32m@LIBNUMMBYTES@/@LIBLSIZELIMIT@[37m Mbytes
ХитрйЮ вупЮк . . . . . . .  [32m@LIBCHDNL@[37m credit(s)/ШиоЬхж
ХитрйЮ Шзжйлжвук  . . . . . [32m@LIBCHUPL@[37m credit(s)/ШиоЬхж
ДзаЩисЩЬмйЮ Шзжйлжвук  . .  [32m@LIBREBATE@[37m Шдс ШиоЬхж
ЛЮ ЬЪбЬбиагтдШ ШиоЬхШ . . . [32m@LIBNUMUNAPP@[37m ШиоЬхШ, [32m@LIBKBYTESUNAPP@[37m kbytes

!J} T Library information, first section (for libops)


LIBINFOO {
[0;36m██  [1m@LIB@ (@LIBDESCR@)  [0;46m[K[0;1m

ГЮгажмиЪуЯЮбЬ . . . . . . . [32m@LIBCRDATE@ @LIBCRTIME@[37m
УзЬчЯмджк/жа . . . . . . .  [32m@LIBOPS@[37m
ХитрйЮ вупЮк  . . . . . . . [32m@LIBCHDNL@[37m credit(s)/ШиоЬхж
ХитрйЮ Шзжйлжвук . . . . .  [32m@LIBCHUPL@[37m credit(s)/ШиоЬхж

!J} T Library information, first section (for OS-only libraries)


LIBINFO3 {Оа Шзжйлжвтк ШиоЬхрд бШлШЪиснждлШа. } T Library information, uploads audited 

LIBINFO4 {Оа вупЬак ШиоЬхрд бШлШЪиснждлШа. } T Library information, downloads audited

LIBINFO5 {Ж ШиоЬажЯубЮ зижйлШлЬчЬлШа гЬ йчдЯЮгШ. } T Library information, library is password protected

LIBINFO6 {Ж ШиоЬажЯубЮ ЬхдШа гцдж ШдсЪдрйЮк (ЫЬд ЫтоЬлШа Шзжйлжвтк ШиоЬхрд). } T Library information, read-only library

LIBINFO7A {ДоЬа ШзжйлШвЬх [5m1[0;1m дтж ШиоЬхж йугЬиШ. } T Library information, one file uploaded today

LIBINFO7B {Дожмд ШзжйлШвЬх [5m%d[0;1m дтШ ШиоЬхШ йугЬиШ. } T Library information, files uploaded today

LIBINFO8A {ДоЬа ШзжйлШвЬх [5m1[0;1m дтж ШиоЬхж Шмлу лЮд ЬЩЫжгсЫШ. } T Library information, one file uploaded this week

LIBINFO8B {Дожмд ШзжйлШвЬх [5m%d[0;1m дтШ ШиоЬхШ Шмлу лЮд ЬЩЫжгсЫШ. } T Library information, files uploaded this week

LIBINFO9 {Ж ШиоЬажЯубЮ ЬхдШа "OS-only". } T Library information, library is OS-only

LIBINFO10 {!)

МтШ ШиоЬхШ йугЬиШ . . . . . [32m@LIBUPLSTODAY@[37m ШиоЬхж/Ш, [32m@LIBKUPLSTODAY@[37m kbytes
Амлу лЮд ЬЩЫжгсЫШ  . . . .  [32m@LIBUPLSWEEK@[37m ШиоЬхж/Ш, [32m@LIBKUPLSWEEK@[37m kbytes!(} T Library information, recent uploads


LIBINFOF {!)

[0;46m[K[0;1m
} T Library information, footer




OPRSMENU {[0;1m
CREATE  . . .  ГЮгажмиЪхШ ШиоЬажЯубЮк   EDIT  . . .  АввШЪу ЩШйабщд имЯгхйЬрд
LIBDEL . . . . . ГаШЪиШну ШиоЬажЯубЮк   ACCESS . . ПижйЩсйЬак йлЮд ШиоЬажЯубЮ
ADDTREE . . . .  ГЮгажмиЪхШ аЬиШиохШк   CHARGES . .  ХиЬщйЬак лЮк ШиоЬажЯубЮк
DELTREEE . . . . ЙШлШйлижну аЬиШиохШк   LIMITS . . . ОиаШ ШиоЬхрд/ШиоЬажЯубЮк
                                        OPTIONS . . . . . . ДаЫабтк имЯгхйЬак
CD . . . . . . . . АввШЪу ШиоЬажЯубЮк   LIBDESCRIBE  . . КЬзлжгЬиук зЬиаЪиШну
COPY  . . . . . . . АдлаЪиШну ШиоЬхрд
DEL  . . . . . . . . ГаШЪиШну ШиоЬхрд
DIR . . . . . . . . ЙШлсвжЪжк ШиоЬхрд   UNAPP . . . ЙШлсвжЪжк гЮ ЬЪбЬбиагтдрд
FILES  . . . . . . . .  Тчзжа ШиоЬхрд   APPROVE  . . . . . .  ДЪбиайЮ ШиоЬхрд
INFO  . . . . ПвЮижнжихЬк ШиоЬажЯубЮк   DISAPP  . . . . АийЮ тЪбиайак ШиоЬхрд
LS . . . .  ЙШлсвжЪжк лЮк ШиоЬажЯубЮк
MOVE  . . . . . .  ЛЬлШбхдЮйЮ ШиоЬхрд
REN  . . . . . .  ЛЬлжджгШйхШ ШиоЬхжм   DESCR . . . АввШЪу зЬиаЪиШнук ШиоЬхрд
TREE  . . . . .  ИЬиШиохШ ШиоЬажЯЮбщд   LONG .  АввШЪу вЬзлжгЬижчк зЬиаЪиШнук

} T Operations menu for Sysops


OPRMENU {[0;1m
LIMITS . . . ОиаШ ШиоЬхрд/ШиоЬажЯубЮк   CD . . . . . . . . АввШЪу ШиоЬажЯубЮк
LIBDESCRIBE  . . КЬзлжгЬиук зЬиаЪиШну   COPY  . . . . . . . АдлаЪиШну ШиоЬхрд
                                        DEL  . . . . . . . . ГаШЪиШну ШиоЬхрд
UNAPP . . . ЙШлсвжЪжк гЮ ЬЪбЬбиагтдрд   DIR . . . . . . . . ЙШлсвжЪжк ШиоЬхрд
APPROVE  . . . . . .  ДЪбиайЮ ШиоЬхрд   FILES  . . . . . . . .  Тчзжа ШиоЬхрд
DISAPP  . . . . АийЮ тЪбиайак ШиоЬхрд   INFO  . . . . ПвЮижнжихЬк ШиоЬажЯубЮк
                                        LS . . . .  ЙШлсвжЪжк лЮк ШиоЬажЯубЮк
                                        MOVE  . . . . . .  ЛЬлШбхдЮйЮ ШиоЬхрд
                                        REN  . . . . . .  ЛЬлжджгШйхШ ШиоЬхжм
                                        TREE  . . . . .  ИЬиШиохШ ШиоЬажЯЮбщд

} T Operations menu for Libops


OPRSHORT {[0;1m
ЛДМОУ ХДИРИСТЖ АРХДИОЗЖЙЧМ
!JЖ литожмйШ ШиоЬажЯубЮ ЬхдШа Ю [32m@LIB@ (@LIBDESCR@)[37m.!)
!JГщйлЬ лЮд ЬзавжЪу йШк, у [33m?[37m ЪаШ лж гЬджч, у [33mX[37m ЪаШ
тежЫж!): } T Operations menu, short prompt


OPRERR {[0;1;31m
!JКмзсгШа, ЫЬд мзсиоЬа Шмлу Ю ЬзавжЪу.!)
[0;1m} T Operations menu, incorrect command


OPRRED {[0;1;31m
!JТж "[33m%s[31m" лШаиасЭЬа йЬ зсдр Шзц гхШ Ьдлжву.!)
[0;1m} T Operations menu, redundant command abbvreviation


OPCAN {[0;1;31m
!JЖ ЫаЬиЪШйхШ ШбмищЯЮбЬ.!)
[0;1m} T Operation canceled


LIBCOL {[0;1;33m
!JТж ШнЬдлабц зШхЭЬа гЬ лШ spells лжм. ПЬиагтджмгЬ 5 ЫЬмлЬицвЬзлШ
ЪаШ дШ ЬзалиШзЬх еШдс Ю гЬлШЩжву лЮк ШиоЬажЯубЮк...!)
[0;1m} T Library can't be operated on, another libop is doing just that


LIBFAIL {[0;1;31m
!JТж ШнЬдлабц зШхЭЬа ШбцгШ гЬ лШ spells лжм. СмЪЪдщгЮ, ЫЬд бШлШнтиШгЬ дШ
ШзжблуйжмгЬ зижлЬиШацлЮлШ гЬлШЩжвук лЮк ШиоЬажЯубЮк. НШдШЫжбагсйлЬ йЬ
вхЪж.!)
[0;1m} T Failed to get permissions to operate on library


OCREASK {[0;1m
!JПШиШбШвщ ЫщйлЬ лж цджгШ лЮк ШиоЬажЯубЮк зжм ЯтвЬлЬ дШ ЫЮгажмиЪуйЬлЬ
бслр Шзц лЮд ШиоЬажЯубЮ "@LIB@". Пижйжоу йлШ бЬнШвШхШ бШа габис ЪисггШлШ!
(ЫщйлЬ [33m?[37m ЪаШ бШлсвжЪж):[0m!) } T CREATE, ask for library name


OCREEXS {[0;1;31m
!JКмзсгШа, Ю ШиоЬажЯубЮ "[37m%s[31m" мзсиоЬа уЫЮ бслр Шзц лЮд ШиоЬажЯубЮ
"[37m@LIB@[31m".!)
[0;1m} T CREATE, that library already exists


OCRE2LN {[0;1;31m
!JТж цджгШ лЮк ШиоЬажЯубЮк ЫЬд гзжиЬх дШ ЬхдШа гЬЪШвчлЬиж
Шзц [37m%d[31m оШиШблуиЬк.!)
[0;1m} T CREATE, library name is too long


OCRECHR {[0;1;31m
!JТж цджгШ лЮк ШиоЬажЯубЮк зЬиатоЬа гЮ ШзжЫЬблжчк оШиШблуиЬк.
АзжЫЬблжх оШиШблуиЬк ЬхдШа лж вШладабц ШвнсЩЮлж, жа ШиаЯгЮлабжх оШиШблуиЬк
бШа лШ йчгЩжвШ "# % ^ ( ) - _ + = [ ] .". ПШиШбШвщ еШдШЫжбагсйлЬ.!)
[0;1m} T CREATE, library name contains strange characters


OCRENST {[0;1;31m
!JКмзсгШа, ЫЬд гзжиЬхлЬ дШ еЬзЬисйЬлЬ лж циаж лрд [37m%d[31m мзжШиоЬажЯЮбщд,
лЮ гхШ бслр Шзц лЮд сввЮ.!)
[0;1m} T CREATE, library too deep in the tree


OCREMKD {[0;1;31m
!JГЬд улШд ЫмдШлу Ю ЫЮгажмиЪхШ лжм directory \"[37m%s[31m\"
(Unix всЯжк [37m%d (%s)[31m).!)
[0;1m} T CREATE, Failed to mkdir()


OADTASK {[0;1m
!JЛЬ Шмлу лЮд Ьдлжву гзжиЬхлЬ дШ зижйЯтйЬлЬ йлак ШиоЬажЯубЬк тдШ UNIX
directory бШа цвШ лжм лШ subdirectories. ЗШ ЫЮгажмиЪЮЯЬх гаШ DOS-ONLY
ШиоЬажЯубЮ ЪаШ бсЯЬ directory бШа Ю цвЮ аЬиШиохШ ЯШ лжзжЯЬлЮЯЬх гтйШ йЬ гаШ
ШиоЬажЯубЮ зжм ЯШ ЫЮгажмиЪЮЯЬх Ъа'Шмлц лж йбжзц. Ж Ьдлжву оиЮйагЬчЬа ЪаШ дШ
ЬЪбШлШйлуйЬлЬ жвцбвЮиШ CD-ROM, FTP mirrors, бвз йлак ШиоЬажЯубЬк.!)

!JПШиШбШвщ ЫщйлЬ лж цджгШ лЮк дтШк ШиоЬажЯубЮк (бслр Шзц лЮд ШиоЬажЯубЮ
"@LIB@") зжм ЯШ навжеЬдуйЬа лЮд аЬиШиохШ:!) [0m} T ADDTREE, give help, ask for lib name


OADTDIR {[0;1m
!JПШиШбШвщ ЫщйлЬ лж UNIX directory бслр Шзц лж жзжхж ЩихйбждлШа лШ ШиоЬхШ
бШа subdirectories зжм ЯтвЬлЬ дШ зижйЯтйжмгЬ й'Шмлу лЮд ШиоЬажЯубЮ:!) [0m} T ADDTREE, asking for directory


OADTDR {[0;1;31m
!JТж UNIX directory зитзЬа дШ ЬхдШа Шзцвмлж (дШ еЬбадсЬа гЬ "/").!)
[0;1m} T ADDTREE, directory must be absolute


OADTDR2 {[0;1;31m
!JТж UNIX directory "[37m%s[31m" ЫЬд мзсиоЬа, ЫЬд тоЬлЬ зицйЩШйЮ, у ЫЬд ЬхдШа directory!!)
[0;1m} T ADDTREE, directory does not exist


OADTCRE {[0;1;32mГЮгажмиЪжчгЬ лЮд ШиоЬажЯубЮ [37m%s[32m.
[0;1m} T ADDTREE, creating lib





OCREVT {[0;30;47m ┌────────────────────── [34mБШйабтк РмЯгхйЬак АиоЬажЯубЮк[0;30;47m ─────────────────────[0;1;37;47m┐ [0m
[30;47m │                                                                          [0;1;47;37m│ [0m
[30;47m │  СчдлжгЮ зЬиаЪиШну      [1;44;37m@39;39;0s[0;1;47;37m        │ [0m
[30;47m │                                                                          [0;1;47;37m│ [0m
[30;47m │  СчдЯЮгШ ШиоЬажЯубЮк    [1;44;37m@15;15;2s[0;47;30m             (Case sensitive!)[1;37m  │ [0m
[30;47m │                                                                          [0;1;47;37m│ [0m
[30;47m │  Club йлж жзжхж ШдубЬа  [1;44;37m@15;15;0s[0;1;47;37m                              [0;1;47;37m  │ [0m
[30;47m │                                                                          [0;1;47;37m│ [0m
[30;47m │  Directory ШиоЬажЯубЮк  [1;44;37m@256;45;0s[0;1;47;37m  │ [0m
[30;47m │                                                                          [0;1;47;37m│ [0m
[30;47m │                                                                          [0;1;47;37m│ [0m
[30;47m │  Ctrl-R ЪаШ ЩжуЯЬаШ              [0;1;42;33m@14;"OK"b[0;47;30m▄    [0;1;41;33m@14;"Cancel"b[0;47;30m▄  [0;1;47;37m│ [0m
[30;47m │                                   ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀     ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀  [0;1;47;37m│ [0m
[30;47m └[0;1;37;47m──────────────────────────────────────────────────────────────────────────┘ [0m
} T CREATE, edit basic library parameters, visual template


OCRELT {[2J[0;30;47m ┌────────────────────── [34mБШйабтк РмЯгхйЬак АиоЬажЯубЮк[0;30;47m ─────────────────────[0;1;37;47m┐ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ [31m1[30m. СчдлжгЮ зЬиаЪиШну  . . . . .  [34m@39;39;0s[0;1;47;37m │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ [31m2[30m. СчдЯЮгШ ШиоЬажЯубЮк  . . . . . . . . . . . . . . . .  [34m@15;15;2s[0;1;47;37m │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ [31m3[30m. Club йлж жзжхж ШдубЬа . . . . . . . . . . . . . . . . [34m@15;15;0s[0;1;47;37m │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ [31m4[30m. Directory ШиоЬажЯубЮк . . [34m@256;43;0s[0;1;47;37m │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m └[0;1;37;47m──────────────────────────────────────────────────────────────────────────┘ [0;1m
} T CREATE, edit basic library parameters, linear template


OCRELT1 {[0;1m
!JПЬиаЪисплЬ йчдлжгШ (йЬ 39 оШиШблуиЬк) лШ зЬиаЬоцгЬдШ лЮк ШиоЬажЯубЮк.!)
[0;1m} T CREATE, edit basic library parameters, field help


OCRELT2 {[0;1m
!JДЫщ гзжиЬхлЬ дШ ЫщйЬлЬ лж йчдЯЮгШ зжм ЯШ бвЬаЫщдЬа лЮд ШиоЬажЯубЮ.
ГЬд ЯШ ЩвтзЬлЬ лжмк оШиШблуиЬк.!)
[0;1m} T CREATE, edit basic library parameters, field help


OCRELT3 {[0;1m
!JЛхШ ШиоЬажЯубЮ гзжиЬх дШ ЫрЯЬх йЬ тдШ Club. Длйа, жа зижйЩсйЬак
зжм мзсиожмд йлж club ЯШ айочжмд бШа йлЮд ШиоЬажЯубЮ. Оа жиЪШдрлтк лжм club ЯШ
тожмд зицйЩШйЮ ШиоЬажЯЮбсиажм йлЮд ШиоЬажЯубЮ. Ойжа тожмд [32mUPLOAD[37m
зицйЩШйЮ йлж club ЯШ гзжижчд дШ йлтвджмд ШиоЬхШ. Ойжа тожмд зицйЩШйЮ
[32mDOWNLOAD[37m ЯШ гзжижчд дШ вШгЩсджмд ШиоЬхШ. Ойжа тожмд зицйЩШйЮ
[32mZERO[37m ЫЬд ЯШ гзжижчд дШ Ыжмд лЮд ШиоЬажЯубЮ у дШ гзжмд й'Шмлуд.!)
[0;1m} T CREATE, edit basic library parameters, field help


OCRELT4 {[0;1m
!JДЫщ гзжиЬхлЬ дШ ШввсеЬлЬ лж directory лЮк ШиоЬажЯубЮк.
ПижйтелЬ: Шд ЫЬд етиЬлЬ ла бсдЬлЬ, ЛЖМ ШввсЭЬлЬ
лж directory. ЛзжиЬх дШ ШоиЮйлЬчйЬлЬ зижйриадс у гцдагШ лЮд ШиоЬажЯубЮ.!)
[0;1m} T CREATE, edit basic library parameters, field help


OCRECNE {[0;1;31m
!JТж club "[37m%s[31m" ЫЬд мзсиоЬа. ГЬд ШввсЭжмгЬ лШ зЬиаЬоцгЬдШ лжм зЬЫхжм.
ВаШ дШ лШ ШввсеЬлЬ ШиЪцлЬиШ, оиЮйагжзжауйлЬ лЮд Ьдлжву [33mEDIT[37m.!)
[0;1m} T CREATE, specified club does not exist


OCRENAB {[0;1;31m
!JТж directory "[37m%s[31m" ЫЬд ЬхдШа Шзцвмлж (ЫЬд еЬбадсЬа гЬ '/', ЫЮвШЫу
Шзц лж root directory). ДхдШа зжвч заЯШдц дШ гЮд гзжиЬх дШ ЫЮгажмиЪЮЯЬх у
дШ вЬалжмиЪуйЬа Ю ШиоЬажЯубЮ.!)
[0;1m} T CREATE, specified directory is not absolute


OCREOK {[0;1;32m
!JДдлсеЬа, ЫЮгажмиЪуЯЮбЬ Ю ШиоЬажЯубЮ "[37m%s[32m" бслр Шзц лЮд ШиоЬажЯубЮ
"[37m@LIB@[32m". ЛзШхджмгЬ йлЮд дтШ ШиоЬажЯубЮ. ТщиШ гзжиЬхлЬ (бШа зитзЬа)
дШ имЯгхйЬлЬ лЮд ШиоЬажЯубЮ гЬ лак Ьдлжвтк
[33mEDIT[37m, [33mACCESS[37m, [33mCHARGES[37m, [33mLIMITS[37m бШа
[33mOPTIONS[37m.!)
[0;1m} T CREATE, library created





OEDIVT {[0;30;47m ┌────────────────────── [34mБШйабтк РмЯгхйЬак АиоЬажЯубЮк[0;30;47m ─────────────────────[0;1;37;47m┐ [0m
[30;47m │                                                                          [0;1;47;37m│ [0m
[30;47m │  СчдлжгЮ зЬиаЪиШну      [1;44;37m@39;39;0s[0;1;47;37m        │ [0m
[30;47m │                                                                          [0;1;47;37m│ [0m
[30;47m │  СчдЯЮгШ ШиоЬажЯубЮк    [1;44;37m@15;15;2s[0;47;30m             (Case sensitive!)[1;37m  │ [0m
[30;47m │                                                                          [0;1;47;37m│ [0m
[30;47m │  Club йлж жзжхж ШдубЬа  [1;44;37m@15;15;0s[0;1;47;37m                              [0;1;47;37m  │ [0m
[30;47m │                                                                          [0;1;47;37m│ [0m
[30;47m │  Directory ШиоЬажЯубЮк  [1;44;37m@256;45;0s[0;1;47;37m  │ [0m
[30;47m │                                                                          [0;1;47;37m│ [0m
[30;47m │  ──────────────────────────────────────────────────────────────────────  [0;1;47;37m│ [0m
[30;47m │  [0;30;46m [@"X "t] [0;47;30m  ДнШигжЪу ШввШЪщд бШа йлак мзжШиоЬажЯубЬк     (Space ЪаШ ШввШЪу)  [0;1;47;37m│ [0m
[30;47m │                                                                          [0;1;47;37m│ [0m
[30;47m │  Ctrl-R ЪаШ ЩжуЯЬаШ              [0;1;42;33m@14;"OK"b[0;47;30m▄    [0;1;41;33m@14;"Cancel"b[0;47;30m▄  [0;1;47;37m│ [0m
[30;47m │                                   ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀     ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀  [0;1;47;37m│ [0m
[30;47m └[0;1;37;47m──────────────────────────────────────────────────────────────────────────┘ [0m
} T EDIT, edit basic library parameters, visual template


OEDILT {[2J[0;30;47m ┌────────────────────── [34mБШйабтк РмЯгхйЬак АиоЬажЯубЮк[0;30;47m ─────────────────────[0;1;37;47m┐ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ [31m1[30m. СчдлжгЮ зЬиаЪиШну  . . . . .  [34m@39;39;0s[0;1;47;37m │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ [31m2[30m. СчдЯЮгШ ШиоЬажЯубЮк  . . . . . . . . . . . . . . . .  [34m@15;15;2s[0;1;47;37m │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ [31m3[30m. Club йлж жзжхж ШдубЬа . . . . . . . . . . . . . . . . [34m@15;15;0s[0;1;47;37m │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ [31m4[30m. Directory ШиоЬажЯубЮк . . [34m@256;43;0s[0;1;47;37m │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ ──────────────────────────────────────────────────────────────────────── [1;37m│ [0m
[30;47m │ [31m5[30m. ДнШигжЪу ШввШЪщд бШа йлак мзжШиоЬажЯубЬк . . . . . . . . . . . .  [34m@"X "t[0;1;47;37m │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m └[0;1;37;47m──────────────────────────────────────────────────────────────────────────┘ [0;1m
} T EDIT, edit basic library parameters, linear template


OEDILT1 {[0;1m
!JПЬиаЪисплЬ йчдлжгШ (йЬ 39 оШиШблуиЬк) лШ зЬиаЬоцгЬдШ лЮк ШиоЬажЯубЮк.!)
[0;1m} T EDIT, edit basic library parameters, field help


OEDILT2 {[0;1m
!JДЫщ гзжиЬхлЬ дШ ЫщйЬлЬ лж йчдЯЮгШ зжм ЯШ бвЬаЫщдЬа лЮд ШиоЬажЯубЮ.
ГЬд ЯШ ЩвтзЬлЬ лжмк оШиШблуиЬк.!)
[0;1m} T EDIT, edit basic library parameters, field help


OEDILT3 {[0;1m
!JЛхШ ШиоЬажЯубЮ гзжиЬх дШ ЫрЯЬх йЬ тдШ Club. Длйа, жа зижйЩсйЬак
зжм мзсиожмд йлж club ЯШ айочжмд бШа йлЮд ШиоЬажЯубЮ. Оа жиЪШдрлтк лжм club ЯШ
тожмд зицйЩШйЮ ШиоЬажЯЮбсиажм йлЮд ШиоЬажЯубЮ. Ойжа тожмд [32mUPLOAD[37m
зицйЩШйЮ йлж club ЯШ гзжижчд дШ йлтвджмд ШиоЬхШ. Ойжа тожмд зицйЩШйЮ
[32mDOWNLOAD[37m ЯШ гзжижчд дШ вШгЩсджмд ШиоЬхШ. Ойжа тожмд зицйЩШйЮ
[32mZERO[37m ЫЬд ЯШ гзжижчд дШ Ыжмд лЮд ШиоЬажЯубЮ у дШ гзжмд й'Шмлуд.!)

!JЛцдж ж бЬдлиабцк ШиоЬажЯЮбсиажк бШа ж оЬаиайлук ймйлугШлжк гзжижчд дШ Шввсежмд
Шмлу лЮд ичЯгайЮ.!)
[0;1m} T EDIT, edit basic library parameters, field help


OEDILT4 {[0;1m
!JДЫщ гзжиЬхлЬ дШ ШввсеЬлЬ лж directory лЮк ШиоЬажЯубЮк.
Лцдж ж бЬдлиабцк ШиоЬажЯЮбсиажк у ж оЬаиайлук ймйлугШлжк гзжижчд
дШ Шввсежмд лж directory. ПижйтелЬ: Шд ЫЬд етиЬлЬ ла бсдЬлЬ, ЛЖМ ШввсЭЬлЬ
лж directory. ЛзжиЬх дШ ШоиЮйлЬчйЬлЬ зижйриадс у гцдагШ лЮд ШиоЬажЯубЮ.!)
[0;1m} T EDIT, edit basic library parameters, field help


OEDILT5 {[0;1m
!JАд ЬдЬиЪжзжауйЬлЬ Шмлу лЮд ЬзавжЪу, жа ШввШЪтк зжм зиШЪгШлжзжауйШлЬ
ЯШ ЬнШигжйлжчд цоа гцдж й'Шмлу лЮд ШиоЬажЯубЮ, Шввс бШа йЬ цвЬк цйЬк
ЩихйбждлШа бслр лЮк йлж Ытдлиж лрд ШиоЬажЯЮбщд. Лцдж жа имЯгхйЬак зжм
[32mШввсеШлЬ[37m ЯШ оиЮйагжзжаЮЯжчд ЬЫщ. Тж directory ЬхдШа ЬаЫабу зЬихзлрйЮ.
Амлц ЫЬд ЬнШигцЭЬлШа йЬ цвЬк лак ШиоЬажЯубЬк бслр Шзц лЮд литожмйШ. Адлх Ъа'Шмлц,
жа мзжШиоЬажЯубЬк ЬдЮгЬищдждлШа тлйа щйлЬ дШ ЬхдШа subdirectories лжм directory
зжм жихйШлЬ.!)

!JАд ЫЬд етиЬлЬ ла бсдЬлЬ, [32mЛЖМ[37m ЬдЬиЪжзжауйЬлЬ Шмлу лЮд ЬзавжЪу!!)
[0;1m} T EDIT, edit basic library parameters, field help


OEDINOP1 {[0;1;31m
!JГЬд гзжиЬхлЬ дШ ШввсеЬлЬ лж Club йлж жзжхж ШдубЬа Ю ШиоЬажЯубЮ.
Амлц ЬхдШа ЫабШхргШ гцдж лжм оЬиайлу ймйлугШлжк!).
[0;1m} T EDIT, can't change club (Master libop's prerogative only)


OEDINOP2 {[0;1;31m
!JГЬд гзжиЬхлЬ дШ ШввсеЬлЬ лж directory лЮк ШиоЬажЯубЮк.
Амлц ЬхдШа ЫабШхргШ гцдж лжм оЬиайлу ймйлугШлжк!).
[0;1m} T EDIT, can't change directory (Master libop's prerogative only)


OEDIREC {[0;1m
!JДдЮгЬищджмгЬ бШа лак мзжШиоЬажЯубЬк:!)
[0;1m} T EDIT, recursively applying changes

OEDIREC1 {[0;1m!WУзжШиоЬажЯубЮ [32m%s[37m: ЬдЮгЬищЯЮбЬ.!)
[0;1m} T EDIT, recursively applied changes to library


OEDIREC2 {[0;1m!WУзжШиоЬажЯубЮ [32m%s[37m: ЬдЮгЬищЯЮбЬ (дЬж directory: [32m%s[37m).!)
[0;1m} T EDIT, recursively applied changes (directory changed)


OEDIREC3 {[0;1;31m
!JЛаШ бШа ЫЬд гзжитйШгЬ дШ ШзжблуйжмгЬ лж ЫабШхргШ гЬлШЩжвук лЮк
ШиоЬажЯубЮк, Ю ШиоЬажЯубЮ [37m%s[31m ЫЬд сввШеЬ. ЗШ зитзЬа дШ лЮд ШввсеЬлЬ
ШиЪцлЬиШ.!)
[0;1m} T EDIT, recursively applying changes (failed to obtain lock)


OACCVT {[0;30;47m ┌───────────────────────── [34mПижйЩсйЬак АиоЬажЯубЮк[0;30;47m ─────────────────────────[0;1;37;47m┐ [0m
[30;47m │                                                                          [0;1;47;37m│ [0m
[30;47m │  ЙвЬаЫх ЬайцЫжм    [1;44;37m@3;0;129;1n[0;47;30m  (0..129) . . .  [0;30;46m [@"X "t] [0;47;30m  МШ ЭЮлЮЯЬх бШа йчдЯЮгШ  [1;37m│ [0m
[30;47m │  ЙвЬаЫх Шзжйлжвук  [1;44;37m@3;0;129;1n[0;47;30m  (0..129)  . . . [0;30;46m [@"X "t] [0;47;30m  МШ ЭЮлЮЯЬх бШа йчдЯЮгШ  [1;37m│ [0m
[30;47m │  ЙвЬаЫх вупЮк      [1;44;37m@3;0;129;1n[0;47;30m  (0..129) . . .  [0;30;46m [@"X "t] [0;47;30m  МШ ЭЮлЮЯЬх бШа йчдЯЮгШ  [1;37m│ [0m
[30;47m │                                                                          [0;1;47;37m│ [0m
[30;47m │  ──────────────────────────────────────────────────────────────────────  [0;1;47;37m│ [0m
[30;47m │                                                                          [0;1;47;37m│ [0m
[30;47m │  СчдЯЮгШ ШиоЬажЯубЮк    [1;44;37m@15;15;2s[0;47;30m             (Case sensitive!)[1;37m  │ [0m
[30;47m │                                                                          [0;1;47;37m│ [0m
[30;47m │  АиоЬажЯЮбсиажа     1.  [1;44;37m@23;23;8s[0;47;30m           Ж йЬаис ЫЬд  [1;37m│ [0m
[30;47m │                     2.  [1;44;37m@23;23;8s[0;47;30m           зШхЭЬа ицвж  [1;37m│ [0m
[30;47m │                     3.  [1;44;37m@23;23;8s[0;47;30m                        [1;37m│ [0m
[30;47m │                     4.  [1;44;37m@23;23;8s[0;47;30m                        [1;37m│ [0m
[30;47m │                     5.  [1;44;37m@23;23;8s[0;47;30m                        [1;37m│ [0m
[30;47m │                                                                          [0;1;47;37m│ [0m
[30;47m │  ──────────────────────────────────────────────────────────────────────  [0;1;47;37m│ [0m
[30;47m │  [0;30;46m [@"X "t] [0;47;30m  ДнШигжЪу ШввШЪщд бШа йлак мзжШиоЬажЯубЬк     (Space ЪаШ ШввШЪу)  [0;1;47;37m│ [0m
[30;47m │                                                                          [0;1;47;37m│ [0m
[30;47m │  Ctrl-R ЪаШ ЩжуЯЬаШ              [0;1;42;33m@14;"OK"b[0;47;30m▄    [0;1;41;33m@14;"Cancel"b[0;47;30m▄  [0;1;47;37m│ [0m
[30;47m │                                   ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀     ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀  [0;1;47;37m│ [0m
[30;47m └[0;1;37;47m──────────────────────────────────────────────────────────────────────────┘ [0m
} T ACCESS, edit accesses, visual template


OACCLT {[2J[0;30;47m ┌───────────────────────── [34mПижйЩсйЬак АиоЬажЯубЮк[0;30;47m ─────────────────────────[0;1;37;47m┐ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │  [31m1[30m. ЙвЬаЫх ЬайцЫжм  . . . . [34m@3;0;129;1n[0;47;30m    [31m2[30m. МШ ЭЮлЮЯЬх бШа йчдЯЮгШ . . . . [34m@"X "t [1;37m│ [0m
[30;47m │  [31m3[30m. ЙвЬаЫх Шзжйлжвук . . .  [34m@3;0;129;1n[0;47;30m    [31m4[30m. МШ ЭЮлЮЯЬх бШа йчдЯЮгШ  . . .  [34m@"X "t [1;37m│ [0m
[30;47m │  [31m5[30m. ЙвЬаЫх вупЮк  . . . . . [34m@3;0;129;1n[0;47;30m    [31m6[30m. МШ ЭЮлЮЯЬх бШа йчдЯЮгШ . . . . [34m@"X "t [1;37m│ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │  [31m7[30m. СчдЯЮгШ ШиоЬажЯубЮк . . . . . . . . . . . . . . . .  [34m@15;15;2s[0;1;47;37m │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │  [31m8[30m. АиоЬажЯЮбсиажк 1  . . . . . . . . . . . . .  [34m@23;23;8s[0;1;47;37m │ [0m
[30;47m │  [31m9[30m. АиоЬажЯЮбсиажк 2   . . . . . . . . . . . . . [34m@23;23;8s[0;1;47;37m │ [0m
[30;47m │ [31m10[30m. АиоЬажЯЮбсиажк 3  . . . . . . . . . . . . .  [34m@23;23;8s[0;1;47;37m │ [0m
[30;47m │ [31m11[30m. АиоЬажЯЮбсиажк 4   . . . . . . . . . . . . . [34m@23;23;8s[0;1;47;37m │ [0m
[30;47m │ [31m12[30m. АиоЬажЯЮбсиажк 5  . . . . . . . . . . . . .  [34m@23;23;8s[0;1;47;37m │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ ──────────────────────────────────────────────────────────────────────── [1;37m│ [0m
[30;47m │ [31m13[30m. ДнШигжЪу ШввШЪщд бШа йлак мзжШиоЬажЯубЬк . . . . . . . . . . . . [34m@"X "t[0;1;47;37m │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m └[0;1;37;47m──────────────────────────────────────────────────────────────────────────┘ [0;1m
} T ACCESS, edit accesses, linear template


OACCLT1 {[0;1m
!JТж бвЬаЫх ЬайцЫжм жихЭЬа зжажа оиуйлЬк ЯШ Щвтзжмд бШа
ЯШ гзжижчд дШ гзШхджмд йлЮд ШиоЬажЯубЮ. ГщйлЬ [33m0[37m Шд ЫЬд ЯтвЬлЬ
дШ бвЬаЫщйЬлЬ лЮд ШиоЬажЯубЮ й'Шмлц лж йЮгЬхж. ГщйлЬ [33m129[37m
Шд ЯтвЬлЬ дШ ЩвтзЬа лЮд ШиоЬажЯубЮ гцдж лж пЬмЫщдмгж [32mSysop[37m.
ВаШ ЬигЮдЬхШ лрд свврд бвЬаЫащд, ЬвслЬ йЬ ЬзабжадрдхШ гЬ лжд
оЬаиайлу ймйлугШлжк.!)
[0;1m} T ACCESS, edit accesses, linear template, field help


OACCLT2 {[0;1m
!JДдЬиЪжзжащдлШк Шмлу лЮд ЬзавжЪу жихЭЬлЬ цла, Ьблцк Шзц лЮд
чзШиеЮ лжм бШлсввЮвжм бвЬаЫажч (Шд тоЬа жиайлЬх), лж йчйлЮгШ
ЯШ ЭЮлсЬа бШа лж йчдЯЮгШ лЮк ШиоЬажЯубЮк зижлжч ЬзалитпЬа
йЬ бсзжаж оиуйлЮ дШ гзЬа йлЮд ШиоЬажЯубЮ.!)
[0;1m} T ACCESS, edit accesses, linear template, field help


OACCLT3 {[0;1m
!JТж бвЬаЫх Шзжйлжвук жихЭЬа зжажа оиуйлЬк ЯШ гзжижчд дШ ШзжйлЬхвжмд
ШиоЬхШ йлЮд ШиоЬажЯубЮ. ГщйлЬ [33m0[37m Шд ЫЬд ЯтвЬлЬ
дШ бвЬаЫщйЬлЬ лЮд ШиоЬажЯубЮ й'Шмлц лж йЮгЬхж. ГщйлЬ [33m129[37m
Шд ЯтвЬлЬ дШ ШзжйлтвЬа ШиоЬхШ гцдж лж пЬмЫщдмгж [32mSysop[37m.
ВаШ ЬигЮдЬхШ лрд свврд бвЬаЫащд, ЬвслЬ йЬ ЬзабжадрдхШ гЬ лжд
оЬаиайлу ймйлугШлжк.!)
[0;1m} T ACCESS, edit accesses, linear template, field help


OACCLT4 {[0;1m
!JДдЬиЪжзжащдлШк Шмлу лЮд ЬзавжЪу жихЭЬлЬ цла, Ьблцк Шзц лЮд
чзШиеЮ лжм бШлсввЮвжм бвЬаЫажч (Шд тоЬа жиайлЬх), лж йчйлЮгШ
ЯШ ЭЮлсЬа бШа лж йчдЯЮгШ лЮк ШиоЬажЯубЮк зижлжч ЬзалитпЬа
йЬ бсзжаж оиуйлЮ дШ ШзжйлЬхвЬа ШиоЬхШ.!)
[0;1m} T ACCESS, edit accesses, linear template, field help


OACCLT5 {[0;1m
!JТж бвЬаЫх вупЮк жихЭЬа зжажа оиуйлЬк ЯШ гзжижчд дШ всЩжмд
ШиоЬхШ Шзц лЮд ШиоЬажЯубЮ. ГщйлЬ [33m0[37m Шд ЫЬд ЯтвЬлЬ
дШ бвЬаЫщйЬлЬ лЮд ШиоЬажЯубЮ й'Шмлц лж йЮгЬхж. ГщйлЬ [33m129[37m
Шд ЯтвЬлЬ дШ вШгЩсдЬа ШиоЬхШ гцдж лж пЬмЫщдмгж [32mSysop[37m.
ВаШ ЬигЮдЬхШ лрд свврд бвЬаЫащд, ЬвслЬ йЬ ЬзабжадрдхШ гЬ лжд
оЬаиайлу ймйлугШлжк.!)
[0;1m} T ACCESS, edit accesses, linear template, field help


OACCLT6 {[0;1m
!JДдЬиЪжзжащдлШк Шмлу лЮд ЬзавжЪу жихЭЬлЬ цла, Ьблцк Шзц лЮд
чзШиеЮ лжм бШлсввЮвжм бвЬаЫажч (Шд тоЬа жиайлЬх), лж йчйлЮгШ
ЯШ ЭЮлсЬа бШа лж йчдЯЮгШ лЮк ШиоЬажЯубЮк зижлжч ЬзалитпЬа
йЬ бсзжаж оиуйлЮ дШ вШгЩсдЬа ШиоЬхШ.!)
[0;1m} T ACCESS, edit accesses, linear template, field help


OACCLT7 {[0;1m
!JДЫщ гзжиЬхлЬ дШ ЫщйЬлЬ лж йчдЯЮгШ зжм ЯШ бвЬаЫщдЬа лЮд ШиоЬажЯубЮ
йлак зЬиазлщйЬак зжм ЫаШвтеШлЬ зШиШзсдр. ГЬд ЯШ ЩвтзЬлЬ лжмк оШиШблуиЬк.!)
[0;1m} T ACCESS, edit accesses, linear template, field help


OACCLT8 {[0;1m
!JГщйлЬ лж цджгШ Ьдцк Шзц лжмк зтдлЬ ШиоЬажЯЮбсиажмк. Ад ЫЬд ЯтвЬлЬ дШ
жихйЬлЬ бШдтдШ цджгШ, ЫщйлЬ "[33mSysop[37m". ОихЭждлШк тдШ оиуйлЮ
ШиоЬажЯЮбсиаж й'Шмлу лЮд ШиоЬажЯубЮ, ж оиуйлЮк ЯШ ШзжблуйЬа ШмлцгШлШ зиждцгаШ ШиоЬажЯЮбШихжм
[32mбШа[37m йлак мзжШиоЬажЯубЬк лЮк литожмйШк (ШдЬесилЮлШ Шзц лжмк лмоцд
ШиоЬажЯЮбсиажмк лЮк ЬбсйлжлЬ мзжШиоЬажЯубЮк). Ж йЬаис гЬ лЮд жзжхШ ЫхдЬлЬ лШ ждцгШлШ ЫЬд тоЬа
йЮгШйхШ.!)

!JЛцдж ж оЬаиайлук ймйлугШлжк бШа ж ЩШйабцк ШиоЬажЯЮбсиажк гзжижчд дШ
Шввсежмд лжмк мзЬчЯмджмк гаШк ШиоЬажЯубЮк.!)
[0;1m} T ACCESS, edit accesses, linear template, field help


OACCLT9 {[0;1m
!JГщйлЬ лж цджгШ Ьдцк Шзц лжмк зтдлЬ ШиоЬажЯЮбсиажмк. Ад ЫЬд ЯтвЬлЬ дШ
жихйЬлЬ бШдтдШ цджгШ, ЫщйлЬ "[33mSysop[37m". ОихЭждлШк тдШ оиуйлЮ
ШиоЬажЯЮбсиаж й'Шмлу лЮд ШиоЬажЯубЮ, ж оиуйлЮк ЯШ ШзжблуйЬа ШмлцгШлШ зиждцгаШ ШиоЬажЯЮбШихжм
[32mбШа[37m йлак мзжШиоЬажЯубЬк лЮк литожмйШк (ШдЬесилЮлШ Шзц лжмк лмоцд
ШиоЬажЯЮбсиажмк лЮк ЬбсйлжлЬ мзжШиоЬажЯубЮк). Ж йЬаис гЬ лЮд жзжхШ ЫхдЬлЬ лШ ждцгШлШ ЫЬд тоЬа
йЮгШйхШ.!)

!JЛцдж ж оЬаиайлук ймйлугШлжк бШа ж ЩШйабцк ШиоЬажЯЮбсиажк гзжижчд дШ
Шввсежмд лжмк мзЬчЯмджмк гаШк ШиоЬажЯубЮк.!)
[0;1m} T ACCESS, edit accesses, linear template, field help


OACCLTA {[0;1m
!JГщйлЬ лж цджгШ Ьдцк Шзц лжмк зтдлЬ ШиоЬажЯЮбсиажмк. Ад ЫЬд ЯтвЬлЬ дШ
жихйЬлЬ бШдтдШ цджгШ, ЫщйлЬ "[33mSysop[37m". ОихЭждлШк тдШ оиуйлЮ
ШиоЬажЯЮбсиаж й'Шмлу лЮд ШиоЬажЯубЮ, ж оиуйлЮк ЯШ ШзжблуйЬа ШмлцгШлШ зиждцгаШ ШиоЬажЯЮбШихжм
[32mбШа[37m йлак мзжШиоЬажЯубЬк лЮк литожмйШк (ШдЬесилЮлШ Шзц лжмк лмоцд
ШиоЬажЯЮбсиажмк лЮк ЬбсйлжлЬ мзжШиоЬажЯубЮк). Ж йЬаис гЬ лЮд жзжхШ ЫхдЬлЬ лШ ждцгШлШ ЫЬд тоЬа
йЮгШйхШ.!)

!JЛцдж ж оЬаиайлук ймйлугШлжк бШа ж ЩШйабцк ШиоЬажЯЮбсиажк гзжижчд дШ
Шввсежмд лжмк мзЬчЯмджмк гаШк ШиоЬажЯубЮк.!)
[0;1m} T ACCESS, edit accesses, linear template, field help


OACCLTB {[0;1m
!JГщйлЬ лж цджгШ Ьдцк Шзц лжмк зтдлЬ ШиоЬажЯЮбсиажмк. Ад ЫЬд ЯтвЬлЬ дШ
жихйЬлЬ бШдтдШ цджгШ, ЫщйлЬ "[33mSysop[37m". ОихЭждлШк тдШ оиуйлЮ
ШиоЬажЯЮбсиаж й'Шмлу лЮд ШиоЬажЯубЮ, ж оиуйлЮк ЯШ ШзжблуйЬа ШмлцгШлШ зиждцгаШ ШиоЬажЯЮбШихжм
[32mбШа[37m йлак мзжШиоЬажЯубЬк лЮк литожмйШк (ШдЬесилЮлШ Шзц лжмк лмоцд
ШиоЬажЯЮбсиажмк лЮк ЬбсйлжлЬ мзжШиоЬажЯубЮк). Ж йЬаис гЬ лЮд жзжхШ ЫхдЬлЬ лШ ждцгШлШ ЫЬд тоЬа
йЮгШйхШ.!)

!JЛцдж ж оЬаиайлук ймйлугШлжк бШа ж ЩШйабцк ШиоЬажЯЮбсиажк гзжижчд дШ
Шввсежмд лжмк мзЬчЯмджмк гаШк ШиоЬажЯубЮк.!)
[0;1m} T ACCESS, edit accesses, linear template, field help


OACCLTC {[0;1m
!JГщйлЬ лж цджгШ Ьдцк Шзц лжмк зтдлЬ ШиоЬажЯЮбсиажмк. Ад ЫЬд ЯтвЬлЬ дШ
жихйЬлЬ бШдтдШ цджгШ, ЫщйлЬ "[33mSysop[37m". ОихЭждлШк тдШ оиуйлЮ
ШиоЬажЯЮбсиаж й'Шмлу лЮд ШиоЬажЯубЮ, ж оиуйлЮк ЯШ ШзжблуйЬа ШмлцгШлШ зиждцгаШ ШиоЬажЯЮбШихжм
[32mбШа[37m йлак мзжШиоЬажЯубЬк лЮк литожмйШк (ШдЬесилЮлШ Шзц лжмк лмоцд
ШиоЬажЯЮбсиажмк лЮк ЬбсйлжлЬ мзжШиоЬажЯубЮк). Ж йЬаис гЬ лЮд жзжхШ ЫхдЬлЬ лШ ждцгШлШ ЫЬд тоЬа
йЮгШйхШ.!)

!JЛцдж ж оЬаиайлук ймйлугШлжк бШа ж ЩШйабцк ШиоЬажЯЮбсиажк гзжижчд дШ
Шввсежмд лжмк мзЬчЯмджмк гаШк ШиоЬажЯубЮк.!)
[0;1m} T ACCESS, edit accesses, linear template, field help


OACCLTD {[0;1m
!JАд ЬдЬиЪжзжауйЬлЬ Шмлу лЮд ЬзавжЪу, жа ШввШЪтк зжм зиШЪгШлжзжауйШлЬ
ЯШ ЬнШигжйлжчд цоа гцдж й'Шмлу лЮд ШиоЬажЯубЮ, Шввс бШа йЬ цвЬк цйЬк
ЩихйбждлШа бслр лЮк йлж Ытдлиж лрд ШиоЬажЯЮбщд. Лцдж жа имЯгхйЬак зжм
[32mШввсеШлЬ[37m ЯШ оиЮйагжзжаЮЯжчд ЬЫщ. ТШ ждцгШлШ лрд ШиоЬажЯЮбШихрд
[32mГДМ[37m гЬлШнтиждлШа бШа йлак мзжШиоЬажЯубЬк.!)

!JАд ЫЬд етиЬлЬ ла бсдЬлЬ, [32mЛЖМ[37m ЬдЬиЪжзжауйЬлЬ Шмлу лЮд ЬзавжЪу!!)
[0;1m} T ACCESS, edit accesses, linear template, field help


OACNMAIN {[0;1;31m
!JГЬд гзжиЬхлЬ дШ бвЬаЫщйЬлЬ лЮд ЬхйжЫж йлЮд бЬдлиабу ШиоЬажЯубЮ.
ДзалитзжмгЬ лЮд ЬхйжЫж йЬ цвжмк (бвЬаЫх [33m0[31m, ЫЬд ШзШалЬхлШа
йчдЯЮгШ).!)
[0;1m} T ACCESS, can't restrict entry to the main library


OACCNOP {[0;1;31m
!JГЬд гзжиЬхлЬ дШ ШввсеЬлЬ лжмк жиЪШдрлтк лЮк ШиоЬажЯубЮк.
Амлц ЬхдШа ЫабШхргШ гцдж лжм оЬиайлу ймйлугШлжк!).
[0;1m} T ACCESS, can't change libops (Master libop's prerogative only)


OACCREC {[0;1m
!JДдЮгЬищджмгЬ бШа лак мзжШиоЬажЯубЬк:!)
[0;1m} T ACCESS, recursively applying changes


OACCREC1 {[0;1m!WУзжШиоЬажЯубЮ [32m%s[37m: ЬдЮгЬищЯЮбЬ.!)
[0;1m} T ACCESS, recursively applied changes to library


OACCREC2 {[0;1;31m
!JЛаШ бШа ЫЬд гзжитйШгЬ дШ ШзжблуйжмгЬ лж ЫабШхргШ гЬлШЩжвук лЮк
ШиоЬажЯубЮк, Ю ШиоЬажЯубЮ [37m%s[31m ЫЬд сввШеЬ. ЗШ зитзЬа дШ лЮд ШввсеЬлЬ
ШиЪцлЬиШ.!)
[0;1m} T ACCESS, recursively applying changes (failed to obtain lock)


OLIMVT {[0;30;47m ┌─────────────────── [34mОиаШ ЛЬЪтЯжмк АиоЬхрд бШа АиоЬажЯубЮк[0;30;47m ────────────────[0;1;37;47m┐ [0m
[30;47m │                                                                          [0;1;47;37m│ [0m
[30;47m │  Оиаж ШиаЯгжч ШиоЬхрд йлЮд ШиоЬажЯубЮ    [1;44;37m@7;0;1000000;1n[0;47;30m  ШиоЬхШ  (0..100000)  [0;1;47;37m│ [0m
[30;47m │                                                                          [0;1;47;37m│ [0m
[30;47m │  Оиаж гЬЪтЯжмк ШиоЬхжм                   [1;44;37m@7;0;1000000;1n[0;47;30m  kBytes  (0..100000)  [0;1;47;37m│ [0m
[30;47m │                                                                          [0;1;47;37m│ [0m
[30;47m │  Оиаж ймджвабжч гЬЪтЯжмк ШиоЬажЯубЮк     [1;44;37m@7;0;10000;1n[0;47;30m  MBytes  (0..10000)  [0;1;47;37m│ [0m
[30;47m │                                                                          [0;1;47;37m│ [0m
[30;47m │  ──────────────────────────────────────────────────────────────────────  [0;1;47;37m│ [0m
[30;47m │  [0;30;46m [@"X "t] [0;47;30m  ДнШигжЪу ШввШЪщд бШа йлак мзжШиоЬажЯубЬк     (Space ЪаШ ШввШЪу)  [0;1;47;37m│ [0m
[30;47m │                                                                          [0;1;47;37m│ [0m
[30;47m │  Ctrl-R ЪаШ ЩжуЯЬаШ              [0;1;42;33m@14;"OK"b[0;47;30m▄    [0;1;41;33m@14;"Cancel"b[0;47;30m▄  [0;1;47;37m│ [0m
[30;47m │                                   ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀     ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀  [0;1;47;37m│ [0m
[30;47m └[0;1;37;47m──────────────────────────────────────────────────────────────────────────┘ [0m
} T LIMITS, edit charges, visual template


OLIMLT {[2J[0;30;47m ┌─────────────────── [34mОиаШ ЛЬЪтЯжмк АиоЬхрд бШа АиоЬажЯубЮк[0;30;47m ────────────────[0;1;37;47m┐ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ [31m1[30m. Оиаж ШиаЯгжч ШиоЬхрд йлЮд ШиоЬажЯубЮ . . . . . . . . . [34m@7;0;1000000;1n ШиоЬхШ [1;37m│ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ [31m2[30m. Оиаж гЬЪтЯжмк ШиоЬхжм . . . . . . . . . . . . . . . .  [34m@7;0;1000000;1n kBytes [1;37m│ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ [31m3[30m. Оиаж ймджвабжч гЬЪтЯжмк ШиоЬажЯубЮк  . . . . . . . . . [34m@7;0;10000;1n MBytes [1;37m│ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ ──────────────────────────────────────────────────────────────────────── [1;37m│ [0m
[30;47m │ [31m4[30m. ДнШигжЪу ШввШЪщд бШа йлак мзжШиоЬажЯубЬк . . . . . . . . . . . .  [34m@"X "t[0;1;47;37m │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m └[0;1;37;47m──────────────────────────────────────────────────────────────────────────┘ [0;1m
} T LIMITS, edit charges, linear template


OLIMLT1 {[0;1m
!JЛЬ Шмлу лЮд ЬзавжЪу гзжиЬхлЬ дШ жихйЬлЬ тдШ циаж йлжд ШиаЯгц ШиоЬхрд
зжм гзжиЬх дШ ШзжЯЮбЬчйЬа Ю ШиоЬажЯубЮ. ГщйлЬ тдШд ШиаЯгц Шзц 0 рк 1000000
(лж [33m0[37m йЮгШхдЬа ШзЬдЬиЪжзжхЮйЮ лжм жихжм).!)
[0;1m} T LIMITS, edit charges, linear template, field help


OLIMLT2 {[0;1m
!JЛЬ Шмлу лЮд ЬзавжЪу гзжиЬхлЬ дШ ЯтйЬлЬ тдШ циаж йлж гтЪЬЯжк бсЯЬ
ШиоЬхжм зжм ШзжйлтвЬлШа йлЮд ШиоЬажЯубЮ. Тж гтЪЬЯжк жихЭЬлШа йЬ [32mkBytes[37m
(1 kByte = 1024 bytes). ЛзжиЬхлЬ дШ ЫщйЬлЬ тдШд ШиаЯгц Шзц 0 рк 1000000
(лж [33m0[37m йЮгШхдЬа ШзЬдЬиЪжзжхЮйЮ лжм жихжм).!)
[0;1m} T LIMITS, edit charges, linear template, field help


OLIMLT3 {[0;1m
!JДЫщ гзжиЬхлЬ дШ жихйЬлЬ лж гтЪайлж ймджвабц гтЪЬЯжк лЮк ШиоЬажЯубЮк йЬ
[32mMBytes[37m (1 MByte = 1024 kbytes). ЛзжиЬхлЬ дШ ЫщйЬлЬ тдШд ШиаЯгц Шзц 0 рк 10000
(лж [33m0[37m йЮгШхдЬа ШзЬдЬиЪжзжхЮйЮ лжм жихжм).!)
[0;1m} T LIMITS, edit charges, linear template, field help


OLIMLT4 {[0;1m
!JАд ЬдЬиЪжзжауйЬлЬ Шмлу лЮд ЬзавжЪу, жа ШввШЪтк зжм зиШЪгШлжзжауйШлЬ
ЯШ ЬнШигжйлжчд цоа гцдж й'Шмлу лЮд ШиоЬажЯубЮ, Шввс бШа йЬ цвЬк цйЬк
ЩихйбждлШа бслр лЮк йлж Ытдлиж лрд ШиоЬажЯЮбщд. Лцдж жа имЯгхйЬак зжм
[32mШввсеШлЬ[37m ЯШ оиЮйагжзжаЮЯжчд ЬЫщ.!)

!JАд ЫЬд етиЬлЬ ла бсдЬлЬ, [32mЛЖМ[37m ЬдЬиЪжзжауйЬлЬ Шмлу лЮд ЬзавжЪу!!)
[0;1m} T ACCESS, edit accesses, linear template, field help


OLIMREC {[0;1m
!JДдЮгЬищджмгЬ бШа лак мзжШиоЬажЯубЬк:!)
[0;1m} T LIMITS, recursively applying changes


OLIMREC1 {[0;1m!WУзжШиоЬажЯубЮ [32m%s[37m: ЬдЮгЬищЯЮбЬ.!)
[0;1m} T LIMITS, recursively applied changes to library


OLIMREC2 {[0;1;31m
!JЛаШ бШа ЫЬд гзжитйШгЬ дШ ШзжблуйжмгЬ лж ЫабШхргШ гЬлШЩжвук лЮк
ШиоЬажЯубЮк, Ю ШиоЬажЯубЮ [37m%s[31m ЫЬд сввШеЬ. ЗШ зитзЬа дШ лЮд ШввсеЬлЬ
ШиЪцлЬиШ.!)
[0;1m} T LIMITS, recursively applying changes (failed to obtain lock)


OCHGVT {[0;30;47m ┌───────────────────── [34mХиЬщйЬак оиуйЮк лЮк АиоЬажЯубЮк[0;30;47m ────────────────────[0;1;37;47m┐ [0m
[30;47m │                                                                          [0;1;47;37m│ [0m
[30;47m │  ХитрйЮ вупЮк Ьдцк ШиоЬхжм       [1;44;37m@8;-1000000;1000000;1n[0;47;30m credits (-1000000..1000000)  [0;1;47;37m│ [0m
[30;47m │                                                                          [0;1;47;37m│ [0m
[30;47m │  ХитрйЮ Шзжйлжвук Ьдцк ШиоЬхжм   [1;44;37m@8;-1000000;1000000;1n[0;47;30m credits (-1000000..1000000)  [0;1;47;37m│ [0m
[30;47m │                                                                          [0;1;47;37m│ [0m
[30;47m │  ДзаЫцлЮйЮ ШзжйлжвтШ ЪаШ вупЬак  [1;44;37m@4;-100;100;1n[0;47;30m %                   (-100..100)  [0;1;47;37m│ [0m
[30;47m │                                                                          [0;1;47;37m│ [0m
[30;47m │  ──────────────────────────────────────────────────────────────────────  [0;1;47;37m│ [0m
[30;47m │  [0;30;46m [@"X "t] [0;47;30m  ДнШигжЪу ШввШЪщд бШа йлак мзжШиоЬажЯубЬк     (Space ЪаШ ШввШЪу)  [0;1;47;37m│ [0m
[30;47m │                                                                          [0;1;47;37m│ [0m
[30;47m │  Ctrl-R ЪаШ ЩжуЯЬаШ              [0;1;42;33m@14;"OK"b[0;47;30m▄    [0;1;41;33m@14;"Cancel"b[0;47;30m▄  [0;1;47;37m│ [0m
[30;47m │                                   ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀     ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀  [0;1;47;37m│ [0m
[30;47m └[0;1;37;47m──────────────────────────────────────────────────────────────────────────┘ [0m
} T CHARGES, edit charges, visual template


OCHGLT {[2J[0;30;47m ┌───────────────────── [34mХиЬщйЬак оиуйЮк лЮк АиоЬажЯубЮк[0;30;47m ────────────────────[0;1;37;47m┐ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ [31m1[30m. ХитрйЮ вупЮк Ьдцк ШиоЬхжм . . . . . . . . . . . . .  [34m@8;-1000000;1000000;1n credits [1;37m│ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ [31m2[30m. ХитрйЮ Шзжйлжвук Ьдцк ШиоЬхжм  . . . . . . . . . . . [34m@8;-1000000;1000000;1n credits [1;37m│ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ [31m3[30m. ДзаЫцлЮйЮ ШзжйлжвтШ ЪаШ вупЬак  . . . . . . . . . . . . . . .  [34m@4;-100;100;1n % [1;37m│ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ ──────────────────────────────────────────────────────────────────────── [1;37m│ [0m
[30;47m │ [31m4[30m. ДнШигжЪу ШввШЪщд бШа йлак мзжШиоЬажЯубЬк . . . . . . . . . . . .  [34m@"X "t[0;1;47;37m │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m └[0;1;37;47m──────────────────────────────────────────────────────────────────────────┘ [0;1m
} T CHARGES, edit charges, linear template


OCHGLT1 {[0;1m
!JДЫщ имЯгхЭЬлЬ зцйЬк гждсЫЬк ЯШ оиЬщдждлШа йлжд вжЪШиаШйгц Ьдцк
оиуйлЮ зжм вШгЩсдЬа тдШ ШиоЬхж Шзц Шмлу лЮд ШиоЬажЯубЮ. Ад жихйЬлЬ
ШидЮлабу оищйЮ, ж оиуйлЮ ЯШ Шзжблс гждсЫЬк гЬ бсЯЬ вупЮ ШиоЬхжм
(Шмлц ЫЬд ЬхдШа бШа зжвч бШву аЫтШ).!)
[0;1m} T CHARGES, edit charges, linear template, field help


OCHGLT2 {[0;1m
!JДЫщ имЯгхЭЬлЬ зцйЬк гждсЫЬк ЯШ оиЬщдждлШа йлжд вжЪШиаШйгц Ьдцк
оиуйлЮ зжм ШзжйлтввЬа тдШ ШиоЬхж Шзц Шмлу лЮд ШиоЬажЯубЮ. Ад жихйЬлЬ
ШидЮлабу оищйЮ, ж оиуйлЮ ЯШ Шзжблс гждсЫЬк гЬ бсЯЬ Шзжйлжву ШиоЬхжм.!)
[0;1m} T CHARGES, edit charges, linear template, field help


OCHGLT3 {[0;1m
!JЖ ЬзаЫцлЮйЮ ЬхдШа ШгжаЩу лЮк ЩсйЮк зижк лжд ШзжйлжвтШ Ьдцк оиуйагжм
ШиоЬхжм. ЙсЯЬ нжис зжм тдШ ШиоЬхж вШгЩсдЬлШа Шзц бсзжаж оиуйлЮ, ж оиуйлЮк
зжм лж тйлЬавЬ ЯШ зШхидЬа тдШ зжйжйлц Шзц лШ credits зжм бШлШдШвщЯЮбШд
бШлс лЮ вупЮ. Тж зжйжйлц ЬзаЫцлЮйЮк ЬхдШа ШбиаЩщк Шмлц. Ад лж имЯгхйЬлЬ йлж 100%,
лцлЬ ж ШзжйлжвтШк Ьдцк ШиоЬхжм ЯШ зШхидЬа цйШ ШбиаЩщк credits ЫШзШдЮЯжчд ЪаШ
лЮ вупЮ лжм ШиоЬхжм. ЛЬ ШидЮлабтк лагтк, ж ШзжйлжвтШк оиЬщдЬлШа
бсЯЬ нжис зжм лж ШиоЬхж лжм вШгЩсдЬлШа Шзц бсзжажд (бШбу аЫтШ).!)
[0;1m} T CHARGES, edit charges, linear template, field help


OCHGLT4 {[0;1m
!JАд ЬдЬиЪжзжауйЬлЬ Шмлу лЮд ЬзавжЪу, жа ШввШЪтк зжм зиШЪгШлжзжауйШлЬ
ЯШ ЬнШигжйлжчд цоа гцдж й'Шмлу лЮд ШиоЬажЯубЮ, Шввс бШа йЬ цвЬк цйЬк
ЩихйбждлШа бслр лЮк йлж Ытдлиж лрд ШиоЬажЯЮбщд. Лцдж жа имЯгхйЬак зжм
[32mШввсеШлЬ[37m ЯШ оиЮйагжзжаЮЯжчд ЬЫщ.!)

!JАд ЫЬд етиЬлЬ ла бсдЬлЬ, [32mЛЖМ[37m ЬдЬиЪжзжауйЬлЬ Шмлу лЮд ЬзавжЪу!!)
[0;1m} T ACCESS, edit accesses, linear template, field help


OCHGREC {[0;1m
!JДдЮгЬищджмгЬ бШа лак мзжШиоЬажЯубЬк:!)
[0;1m} T CHARGES, recursively applying changes


OCHGREC1 {[0;1m!WУзжШиоЬажЯубЮ [32m%s[37m: ЬдЮгЬищЯЮбЬ.!)
[0;1m} T CHARGES, recursively applied changes to library


OCHGREC2 {[0;1;31m
!JЛаШ бШа ЫЬд гзжитйШгЬ дШ ШзжблуйжмгЬ лж ЫабШхргШ гЬлШЩжвук лЮк
ШиоЬажЯубЮк, Ю ШиоЬажЯубЮ [37m%s[31m ЫЬд сввШеЬ. ЗШ зитзЬа дШ лЮд ШввсеЬлЬ
ШиЪцлЬиШ.!)
[0;1m} T CHARGES, recursively applying changes (failed to obtain lock)



OOPTVT {[0;30;47m ┌────────────────────── [34mДаЫабтк имЯгхйЬак АиоЬажЯубЮк[0;30;47m ─────────────────────[0;1;37;47m┐ [0m
[30;47m │                                                                          [0;1;47;37m│ [0m
[30;47m │  [0;30;46m [@"X "t] [0;47;30m  АиоЬажЯубЮ read-only (орихк uploads)         (Space ЪаШ ШввШЪу)  [0;1;47;37m│ [0m
[30;47m │  [0;30;46m [@"X "t] [0;47;30m  СЬ ШиЪу ймйбЬму (зо CD-ROM, CD-ROM jukebox)                      [0;1;47;37m│ [0m
[30;47m │  [0;30;46m [@"X "t] [0;47;30m  "DOS-only" ШиоЬажЯубЮ (Шзц CD-ROM, FTP directories, бвз)         [0;1;47;37m│ [0m
[30;47m │  [0;30;46m [@"X "t] [0;47;30m  "DOS-only" ШиоЬажЯубЮ гЬ бШлсвжЪж ШиоЬхрд                        [0;1;47;37m│ [0m
[30;47m │  [0;30;46m [@"X "t] [0;47;30m  АмлцгШлЮ тЪбиайЮ ШиоЬхрд гЬ лЮд Шзжйлжву лжмк                    [0;1;47;37m│ [0m
[30;47m │  [0;30;46m [@"X "t] [0;47;30m  АзШЪциЬмйЮ ЫЮгажмиЪхШк ЬмиЬлЮихжм/бШлШвцЪжм ШиоЬхрд              [0;1;47;37m│ [0m
[30;47m │  [0;30;46m [@"X "t] [0;47;30m  ЙШлШЪиШну Шзжйлжвщд ШиоЬхрд йлж audit trail                      [0;1;47;37m│ [0m
[30;47m │  [0;30;46m [@"X "t] [0;47;30m  ЙШлШЪиШну вупЬрд ШиоЬхрд йлж audit trail                         [0;1;47;37m│ [0m
[30;47m │  [0;30;46m [@"X "t] [0;47;30m  ДзаЩжву DOS жджгслрд ШиоЬхрд (8+3 оШиШблуиЬк)                    [0;1;47;37m│ [0m
[30;47m │                                                                          [0;1;47;37m│ [0m
[30;47m │  ──────────────────────────────────────────────────────────────────────  [0;1;47;37m│ [0m
[30;47m │  [0;30;46m [@"X "t] [0;47;30m  ДнШигжЪу ШввШЪщд бШа йлак мзжШиоЬажЯубЬк     (Space ЪаШ ШввШЪу)  [0;1;47;37m│ [0m
[30;47m │                                                                          [0;1;47;37m│ [0m
[30;47m │  Ctrl-R ЪаШ ЩжуЯЬаШ              [0;1;42;33m@14;"OK"b[0;47;30m▄    [0;1;41;33m@14;"Cancel"b[0;47;30m▄  [0;1;47;37m│ [0m
[30;47m │                                   ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀     ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀  [0;1;47;37m│ [0m
[30;47m └[0;1;37;47m──────────────────────────────────────────────────────────────────────────┘ [0m
} T OPTIONS, edit charges, visual template


OOPTLT {[2J[0;30;47m ┌────────────────────── [34mДаЫабтк имЯгхйЬак АиоЬажЯубЮк[0;30;47m ─────────────────────[0;1;37;47m┐ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ [31m 1[30m. АиоЬажЯубЮ read-only (орихк uploads) . . . . . . . . . . . . . . [34m@"X "t[0;1;47;37m │ [0m
[30;47m │ [31m 2[30m. СЬ ШиЪу ймйбЬму (зо CD-ROM, CD-ROM jukebox) . . . . . . . . . .  [34m@"X "t[0;1;47;37m │ [0m
[30;47m │ [31m 3[30m. "DOS-only" ШиоЬажЯубЮ (Шзц CD-ROM, FTP directories, бвз) . . . . [34m@"X "t[0;1;47;37m │ [0m
[30;47m │ [31m 4[30m. "DOS-only" ШиоЬажЯубЮ гЬ бШлсвжЪж ШиоЬхрд . . . . . . . . . . .  [34m@"X "t[0;1;47;37m │ [0m
[30;47m │ [31m 5[30m. АмлцгШлЮ тЪбиайЮ ШиоЬхрд гЬ лЮд Шзжйлжву лжмк  . . . . . . . . . [34m@"X "t[0;1;47;37m │ [0m
[30;47m │ [31m 6[30m. АзШЪциЬмйЮ ЫЮгажмиЪхШк ЬмиЬлЮихжм/бШлШвцЪжм ШиоЬхрд . . . . . .  [34m@"X "t[0;1;47;37m │ [0m
[30;47m │ [31m 7[30m. ЙШлШЪиШну Шзжйлжвщд ШиоЬхрд йлж audit trail  . . . . . . . . . . [34m@"X "t[0;1;47;37m │ [0m
[30;47m │ [31m 8[30m. ЙШлШЪиШну вупЬрд ШиоЬхрд йлж audit trail  . . . . . . . . . . .  [34m@"X "t[0;1;47;37m │ [0m
[30;47m │ [31m 9[30m. ДзаЩжву DOS жджгслрд ШиоЬхрд (8+3 оШиШблуиЬк)  . . . . . . . . . [34m@"X "t[0;1;47;37m │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ ──────────────────────────────────────────────────────────────────────── [1;37m│ [0m
[30;47m │ [31m10[30m. ДнШигжЪу ШввШЪщд бШа йлак мзжШиоЬажЯубЬк . . . . . . . . . . . . [34m@"X "t[0;1;47;37m │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m └[0;1;37;47m──────────────────────────────────────────────────────────────────────────┘ [0;1m
} T OPTIONS, edit charges, linear template


OOPTLT1 {[0;1m
!JДдЬиЪжзжащдлШк Шмлу лЮд ЬзавжЪу, ШзШЪжиЬчЬлЬ лак ЬЪЪиШнтк ШиоЬхрд
йлж directory лЮк ШиоЬажЯубЮк. ГЬд гзжижчд дШ Ъхджмд Шзжйлжвтк ШиоЬхрд
бШа ЫЬд (еШдШ)ЫЮгажмиЪжчдлШа зжлт ЬмиЬлуиаж бШа бШлсвжЪжа ШиоЬхрд. ДдЬиЪжзжауйлЬ
лЮд ЬзавжЪу Шмлу Шд, зо, Ю ШиоЬажЯубЮ ЬхдШа гтйШ йЬ тдШ CD-ROM.!)
[0;1m} T OPTIONS, edit charges, linear template, field help


OOPTLT2 {[0;1m
!JДдЬиЪжзжауйлЬ Шмлу лЮд ЬзавжЪу Шд Ю ймйбЬму йлЮд жзжхШ ЩихйбЬлШа Ю ШиоЬажЯубЮ ЬхдШа
ШиЪу. ГЮвШЫу, Шд оиЬасЭЬлШа ШнчйабШ гЬЪсвШ оиждабс ЫаШйлугШлШ ЪаШ дШ зижйзЬвШйлЬх
Шзц лж multitasking йчйлЮгШ. Ад Ю ШиоЬажЯубЮ ЬхдШа йЬ тдШ ШиЪц CD-ROM у йЬ тдШ
CD-ROM jukebox, бШвц ЬхдШа дШ ЬдЬиЪжзжауйЬлЬ Шмлу лЮд ЬзавжЪу. ТШ ШиоЬхШ лЮк
ШиоЬажЯубЮк ЯШ лжзжЯЬлжчдлШа йЬ cache йлж Ыхйбж, Ьдщ Ю ймйбЬму ЯШ бвЬаЫщдЬа
гЬ бсЯЬ зижйзтвШйЮ лЮк, щйлЬ дШ гЮд гзжижчд дШ лЮд оЬаиайлжчд зШиШзсдр Шзц тдШк
оиуйлЮк, ЬзаЩиШЫчдждлск лЮд (Шмлц ЬхдШа ЬеШаиЬлабс оиуйагж йлЮд зЬихзлрйЮ лрд CD-ROM
jukeboxes).!)
[0;1m} T OPTIONS, edit charges, linear template, field help


OOPTLT3 {[0;1m
!JЛаШ "DOS-only" ШиоЬажЯубЮ ЬхдШа тдШ Шзвц directory йлжд Ыхйбж.
ГЬд тоЬа втеЬак бвЬаЫас, лШ ШиоЬхШ лЮк ЫЬд ЩихйбждлШа йлЮд database
ШиоЬхрд бШа гзжиЬх бШдЬхк дШ лЮд оЬаиайлЬх гтйр лжм вЬалжмиЪабжч ймйлугШлжк.
ДдЬиЪжзжауйлЬ Шмлу лЮд ЬзавжЪу Шд Ю ШиоЬажЯубЮ ЩихйбЬлШа йЬ бсзжаж CD-ROM у ЬхдШа
ЬаЫабук нчйЮк (зо тдШ FTP directory зжм тоЬа ЪхдЬа mounted гтйр Ыаблчжм, бвз).!)
[0;1m} T OPTIONS, edit charges, linear template, field help


OOPTLT4 {[0;1m
!JЛаШ "DOS-only" ШиоЬажЯубЮ ЬхдШа тдШ Шзвц directory йлжд Ыхйбж.
ОлШд ж оиуйлЮк ЭЮлсЬа лжд бШлсвжЪж гаШк лтлжаШк ШиоЬажЯубЮк, бШдждабс
вШгЩсдЬа лжд бШлсвжЪж цврд лрд ШиоЬхрд цзрк лжд ШдШнтиЬа лж вЬалжмиЪабц
йчйлЮгШ. ЛЬ Шмлу лЮд ЬзавжЪу ЬдЬиЪжзжаЮгтдЮ, Ю ЩсйЮ ЯШ псеЬа зищлШ ЪаШ
тдШ ШиоЬхж-бШлсвжЪж (зо "FILES" у "INDEX"). Ад ЩиЬЯЬх бШлсввЮвж ШиоЬхж, лмзщдЬлШа
йлжд оиуйлЮ. Авващк ЬгнШдхЭЬлШа ж бШлсвжЪжк Шзц лж вЬалжмиЪабц йчйлЮгШ.
Амлу Ю ЬзавжЪу ЫЬд бсдЬа лхзжлШ Шд Ю зижЮЪжчгЬдЮ ЬхдШа ШдЬдЬиЪу.!)
[0;1m} T OPTIONS, edit charges, linear template, field help


OOPTLT5 {[0;1m
!JДдЬиЪжзжауйлЬ Шмлу лЮд Ьдлжву Шд ЬгзайлЬчЬйлЬ лжмк оиуйлЬк лЮк
ШиоЬажЯубЮк ШибЬлс щйлЬ дШ гЮд оиЬасЭЬлШа дШ ЬЪбихдЬлЬ лШ ШиоЬхШ
тдШ тдШ. ТШ ШиоЬхШ ЯШ ЬЪбихдждлШа ШмлцгШлШ Шзц лж йчйлЮгШ Шгтйрк
гЬлс лЮд Шзжйлжву лжмк.!)
[0;1m} T OPTIONS, edit charges, linear template, field help


OOPTLT6 {[0;1m
!JЛЬ Шмлу лЮд ЬзавжЪу гзжиЬхлЬ дШ ШзШЪжиЬчйЬлЬ лЮд ЫЮгажмиЪхШ
бШлШвцЪжм ШиоЬхрд бШа ЬмиЬлЮихжм йлЮд ШиоЬажЯубЮ. Амлц гзжиЬх
дШ нШдЬх оиуйагж йЬ зЬихзлрйЮ зжм ЬхлЬ лШ ШиоЬхШ ЬхдШа лЬисйлаШ,
ЬхлЬ Ю ШиоЬажЯубЮ тоЬа Ыабжчк лЮк бШлШвцЪжмк (зо FTP sites).!)
[0;1m} T OPTIONS, edit charges, linear template, field help


OOPTLT7 {[0;1m
!JДдЬиЪжзжауйлЬ Шмлу лЮд ЬзавжЪу ЪаШ дШ бШлШЪиснждлШа
цвЬк жа Шзжйлжвтк ШиоЬхрд йлж audit trail. Ад ЫЬд етиЬлЬ ла
дШ бсдЬлЬ, ЬдЬиЪжзжауйлЬ лЮд ЬзавжЪу Шмлу.!)
[0;1m} T OPTIONS, edit charges, linear template, field help


OOPTLT8 {[0;1m
!JДдЬиЪжзжауйлЬ Шмлу лЮд ЬзавжЪу ЪаШ дШ бШлШЪиснждлШа
цвЬк жа вупЬак ШиоЬхрд йлж audit trail. Ад ЫЬд етиЬлЬ ла
дШ бсдЬлЬ, ЬдЬиЪжзжауйлЬ лЮд ЬзавжЪу Шмлу.!)
[0;1m} T OPTIONS, edit charges, linear template, field help


OOPTLT9 {[0;1m
!JАд ЯтвЬлЬ Ю ШиоЬажЯубЮ дШ зЬиатоЬа гцдж ШзжЫЬблс ждцгШлШ
DOS ШиоЬхрд (xxxxxxxx.xxx), лцлЬ ЬдЬиЪжзжауйлЬ Шмлу лЮд ЬзавжЪу.
АввШ вЬалжмиЪабс ймйлугШлШ зжм тожмд лжд хЫаж зЬиажиайгц ЬхдШа лж
CP/M бШа лж TOS. ГЬд ЬхдШа ШдсЪбЮ дШ ЬдЬиЪжзжауйЬлЬ лЮд ЬзаЩжву
DOS жджгслрд, Шввс ЬхдШа бШву аЫтШ (лШ зЬиаййцлЬиШ зижЪисггШлШ
бШа зирлцбжвШ Ьзабжадрдащд бсджмд лЮд гЬлШлижзу ШмлцгШлШ).!)
[0;1m} T OPTIONS, edit charges, linear template, field help


OOPTLTA {[0;1m
!JАд ЬдЬиЪжзжауйЬлЬ Шмлу лЮд ЬзавжЪу, жа ШввШЪтк зжм зиШЪгШлжзжауйШлЬ
ЯШ ЬнШигжйлжчд цоа гцдж й'Шмлу лЮд ШиоЬажЯубЮ, Шввс бШа йЬ цвЬк цйЬк
ЩихйбждлШа бслр лЮк йлж Ытдлиж лрд ШиоЬажЯЮбщд. Лцдж жа имЯгхйЬак зжм
[32mШввсеШлЬ[37m ЯШ оиЮйагжзжаЮЯжчд ЬЫщ.!)

!JАд ЫЬд етиЬлЬ ла бсдЬлЬ, [32mЛЖМ[37m ЬдЬиЪжзжауйЬлЬ Шмлу лЮд ЬзавжЪу!!)
[0;1m} T ACCESS, edit accesses, linear template, field help


OOPTREC {[0;1m
!JДдЮгЬищджмгЬ бШа лак мзжШиоЬажЯубЬк:!)
[0;1m} T OPTIONS, recursively applying changes


OOPTREC1 {[0;1m!WУзжШиоЬажЯубЮ [32m%s[37m: ЬдЮгЬищЯЮбЬ.!)
[0;1m} T OPTIONS, recursively applied changes to library


OOPTREC2 {[0;1;31m
!JЛаШ бШа ЫЬд гзжитйШгЬ дШ ШзжблуйжмгЬ лж ЫабШхргШ гЬлШЩжвук лЮк
ШиоЬажЯубЮк, Ю ШиоЬажЯубЮ [37m%s[31m ЫЬд сввШеЬ. ЗШ зитзЬа дШ лЮд ШввсеЬлЬ
ШиЪцлЬиШ.!)
[0;1m} T OPTIONS, recursively applying changes (failed to obtain lock)


OLDLASK {[0;1m
!JПШиШбШвщ ЫщйлЬ лж цджгШ лЮк ШиоЬажЯубЮк зжм ЯтвЬлЬ дШ ЫаШЪиспЬлЬ
бслр Шзц лЮд ШиоЬажЯубЮ "@LIB@". Пижйжоу йлШ бЬнШвШхШ бШа габис ЪисггШлШ!
[5mГДМ ЗА УПАРНДИ ДУЙАИРИА МА АККАНДТД ВМЧЛЖ![0;1m
(ЫщйлЬ [33m?[37m ЪаШ бШлсвжЪж):[0m!) } T LIBDEL, ask for library name


OLDLNEX {[0;1;31m
!JКмзсгШа, Ю ШиоЬажЯубЮ "[37m%s[31m" ЫЬд мзсиоЬа бслр Шзц лЮд ШиоЬажЯубЮ
"[37m@LIB@[31m".!)
[0;1m} T LIBDEL, that library doesn't exist


OLDLSUB {[0;1;31m
!JЖ ШиоЬажЯубЮ зЬиатоЬа мзжШиоЬажЯубЬк. Пиад лЮд ЫаШЪиспЬлЬ ЯШ зитзЬа
дШ гЬлШбадуйЬлЬ у дШ ЫаШЪиспЬлЬ цвЬк лак мзжШиоЬажЯубЬк лЮк.!)
[0;1m} T LIBDEL, library name is too long


OLDLMAI {[0;1;31m
!JГЬд гзжиЬхлЬ дШ ЫаШЪиспЬлЬ лЮд ШиоЬажЯубЮ [37m%s[31m.!)
} T LIBDEL, can't delete main library


ODLTASK {[0;1m
!JПШиШбШвщ ЫщйлЬ лж цджгШ лЮк ШиоЬажЯубЮк зжм ЯтвЬлЬ дШ ЫаШЪиспЬлЬ
бслр Шзц лЮд ШиоЬажЯубЮ "@LIB@". Пижйжоу йлШ бЬнШвШхШ бШа габис ЪисггШлШ!
[5mГДМ ЗА УПАРНДИ ДУЙАИРИА МА АККАНДТД ВМЧЛЖ![0;1m ЗА ГИАВРАФОУМ ЙАИ ОИ УПОАРХДИОЗЖЙДС!
ПРОСДНТД ОЛЧС: СД АМТИЗДСЖ ЛД ТЖМ ДМТОКЖ LIBDEL, ГДМ ЗА СБЖСТОУМ АРХДИА ЙАИ DIRECTORIES.
ОджгШ зижк ЫаШЪиШну (ЫщйлЬ [33m?[37m ЪаШ бШлсвжЪж):[0m!) } T DELTREE, ask for root library name


ODLTINF {[0;1;32mГаШЪиШну ШиоЬажЯубЮк [37m%s[32m: втеЬак бвЬаЫас... } T DELTREE, Deleting library (keywords)

ODLTINF2 {ШиоЬхШ... } T DELTREE, Deleting library (file entries)

ODLTINF3 {ДдлсеЬа.
[0;1m} T DELTREE, Done. 



OLDLKEY {[0;1;31m
!JГаШЪиснжмгЬ лак втеЬак бвЬаЫас лЮк ШиоЬажЯубЮк...!)
[0;1m} T LIBDEL, deleting keywords

OLDLFIL {[0;1;31m
!JГаШЪиснжмгЬ лШ ШиоЬхШ Шзц лЮд ШиоЬажЯубЮ (лШ ШиоЬхШ гтджмд
ШдтзШнШ йлжд Ыхйбж)...!)
[0;1m} T LIBDEL, deleting keywords



OFILHD {[0;1;32m
!CТчзжа ШиоЬхрд лЮк ШиоЬажЯубЮк [37m@LIB@[32m.!)
[37m!F─
[0;1m} T FILE, header


OFILLN {[0;1;36m%s [37m!i!W%s!)
!0l} T FILE, table line


OFILFT {[0;1m!F─
[0;1m} T FILE, table footer


OLUNOS {[0;1;31mЖ ШиоЬажЯубЮ [37m%s[31m ЬхдШа "DOS-ONLY" бШа ЫЬд гзжиЬх
дШ тоЬа ШиоЬхШ зижк тЪбиайЮ.
[0;1m} T UNAPP, DOS-ONLY lib can't have unapproved files


OAPPQ {[0;1m
!JГщйлЬ цджгШ ШиоЬхжм зижк тЪбиайЮ, у [33m.[37m ЪаШ тиЬмдШ гЮ
ЬЪбЬбиагтдрд ШиоЬхрд йлЮд ШиоЬажЯубЮ [32m@LIB@[37m бШа лмоцд мзШиоЬажЯубЬк
лЮк: [0m[Enter=тиЬмдШ]!) } T APPROVE, ask for filename or scan


OAPPR {[0;1;31m
!JАмлц лж ШиоЬхж ЫЬд мзсиоЬа йлЮд ШиоЬажЯубЮ [37m@LIB@[31m. ГщйлЬ тдШ
сввж цджгШ, у [33m.[31m ЪаШ тиЬмдШ ШиоЬхрд зижк тЪбиайЮ.!)
[0;1m} T APPROVE, file not found


OAPPASK {[0;1m
!JЗтвЬлЬ дШ ЬЪбихдЬлЬ Шмлц лж ШиоЬхж; ([[33mY[37m]es=дШх,
[[33mN[37m]o=цоа, [[33mD[37m]ownload=вупЮ/ЬзаЯЬщиЮйЮ):!) [0m} T APPROVE, Approve/Don't Approve/Download?


OAPPERR {[0;1;31m
!JАмлу Ю ЬзавжЪу ЫЬд ЬхдШа ЫмдШлу.!)
[0;1m} T APPROVE, invalid selection for OAPPASK


OAPPOK {[0;1;32m
!JЙШвщк, лж ШиоЬхж ЬЪбихЯЮбЬ ЪаШ вупЮ Шзц лжмк оиуйлЬк.!)
[0;1m} T APPROVE, file approved


OAPPSCN {[0;1;32m
!WДиЬмдщ лЮд ШиоЬажЯубЮ [37m@LIB@[32m ЪаШ ШиоЬхШ зижк тЪбиайЮ...!)
[0;1m} T APPROVE, scanning library


OAPPNUN {[0;1;33m
!JГЬд ЩитЯЮбШд ШиоЬхШ ЪаШ тЪбиайЮ.!)
[0;1m} T APPROVE, no unapproved files found


ODISQ {[0;1m
!JГщйлЬ цджгШ ШиоЬхжм зижк сийЮ тЪбиайЮк: [0m!)} T DISAPPROVE, ask for filename


ODISR {[0;1;31m
!JАмлц лж ШиоЬхж ЫЬд мзсиоЬа йлЮд ШиоЬажЯубЮ [37m@LIB@[31m.!)
[0;1m} T DISAPPROVE, file not found


ODISASK {[0;1m
!JЗтвЬлЬ дШ сиЬлЬ лЮд тЪбиайЮ Шмлжч лжм ШиоЬхжм; ([[33mY[37m]es=дШх,
[[33mN[37m]o=цоа, [[33mD[37m]ownload=вупЮ/ЬзаЯЬщиЮйЮ):!) [0m} T DISAPPROVE, Disapprove/Don't Disapprove/Download?


ODISERR {[0;1;31m
!JАмлу Ю ЬзавжЪу ЫЬд ЬхдШа ЫмдШлу.!)
[0;1m} T DISAPPROVE, invalid selection for ODISASK


ODISOK {[0;1;32m
!JЙШвщк, Ю тЪбиайЮ вупЮк лжм ШиоЬхжм ЫЬд айочЬа звтжд.!)
[0;1m} T DISAPPROVE, file disapproved


OLGRASK {[0;1m
!JАмлу Ю Ьдлжву ЬзалитзЬа дШ гЬлШбадуйЬлЬ лЮд литожмйШ ШиоЬажЯубЮ @LIB@
(бШа цвЬк лак мзжШиоЬажЯубЬк лЮк) йЬ бсзжаж сввж йЮгЬхж лжм Ытдлижм
ШиоЬажЯЮбщд. Ж ШиоЬажЯубЮ ГДМ гЬлШбадЬхлШа йлжд Ыхйбж, Шзвс ШввсЭЬа Ю ЯтйЮ
лЮк йлЮд аЬиШиохШ.!)

!JЖ ШиоЬажЯубЮ @LIB@ тоЬа звуиЬк цджгШ @LIBFULL@. Йслр Шзц зжаШ ШиоЬажЯубЮ
ЯтвЬлЬ дШ лЮд ШзжЯтйжмгЬ (зо ЫхдждлШк /, Ю ШиоЬажЯубЮ гЬлШбадЬхлШа йлж
бжимнШхж ЬзхзЬЫж):!)[0m } T LIBGRAFT, asking where to move the library


OLGRERR {[0;1;31m
!JЖ ШиоЬажЯубЮ [37m%s[31m ЫЬд мзсиоЬа у ЩихйбЬлШа бслр Шзц лЮд @LIB@.
ПШиШбШвщ ЫщйлЬ лж ПКЖРДС цджгШ лЮк ШиоЬажЯубЮк бслр Шзц лЮд жзжхШ ЯтвЬлЬ дШ
ШзжЯтйжмгЬ лЮд @LIB@ (зо лж звуиЬк цджгШ лЮк @LIB@ ЬхдШа @LIBFULL@).!)
[0;1m} T LIBGRAFT, error in library selection



OLRNASK {[0;1m
!JАмлу Ю Ьдлжву гЬлжджгсЭЬа лЮд литожмйШ ШиоЬажЯубЮ, орихк дШ лЮк ШввсеЬа
ЯтйЮ йлЮд аЬиШиохШ. Пжаж ЯтвЬлЬ дШ ЬхдШа лж дтж цджгШ лЮк @LIB@
(ЫщйлЬ [33m?[37m ЪаШ бШлсвжЪж лрд ШиоЬажЯЮбщд й'Шмлц лж йЮгЬхж);!) [0m} T LIBREN, asking the library's new name


OLRNNMN {[0;1;31m
!JГЬд гзжиЬхлЬ дШ гЬлжджгсйЬлЬ лЮд бЬдлиабу ШиоЬажЯубЮ!!)
[0;1m} T LIBREN, can't rename main library


OLRNERR {[0;1;31m
!JУзсиоЬа уЫЮ ШиоЬажЯубЮ г'Шмлц лж цджгШ й'Шмлц лж йЮгЬхж лЮк аЬиШиохШк.!)
[0;1m} T LIBREN, a library by that name already exists here


OLRNOK {[0;1;32m
!JЙШвщк, Ю ШиоЬажЯубЮ жджгсЭЬлШа звтжд @LIB@!)
[0;1m} T LIBREN, renamed library



ODESASK {[0;1m
!JПжажм ШиоЬхжм лЮд йчдлжгЮ зЬиаЪиШну ЯтвЬлЬ дШ ШввсеЬлЬ; ЛзжиЬхлЬ дШ
ЫщйЬлЬ бШа wildcards, у [33m?[37m ЪаШ бШлсвжЪж лЮк ШиоЬажЯубЮк @LIB@:!) [0m} T DESCR, asking for file


ODESOS {[0;1;31m!JЖ ШиоЬажЯубЮ [37m@LIB@[31m ЬхдШа "DOS-ONLY" бШа ЫЬд тоЬа зЬиаЪиШнтк ЪаШ лШ ШиоЬхШ лЮк.!)
[[0;1m} T DESCR, DOS-ONLY lib can't have descriptions


ODESERR {[0;1;31m
!JГЬд ЩитЯЮбШд ШиоЬхШ.!)
[0;1m} T DESCR, no files found


ODESFIL {[0;1;32m
АРХДИО:    [37m%s (%d Шзц %d)[32m
ПДРИВРАФЖ: [37m%s
           ├─────────────────────────────────────────┤[32m (Enter=гЮ ШввШЪу)
МДА:       [0m} T DESCR, changing description         



OLONASK {[0;1m
!JПжажм ШиоЬхжм лЮд вЬзлжгЬиу зЬиаЪиШну ЯтвЬлЬ дШ ШввсеЬлЬ; ЛзжиЬхлЬ дШ
ЫщйЬлЬ бШа wildcards, у [33m?[37m ЪаШ бШлсвжЪж лЮк ШиоЬажЯубЮк @LIB@:!) [0m} T LONG, asking for file


OLONOS {[0;1;31m!JЖ ШиоЬажЯубЮ [37m@LIB@[31m ЬхдШа "DOS-ONLY" бШа ЫЬд тоЬа зЬиаЪиШнтк ЪаШ лШ ШиоЬхШ лЮк.!)
[[0;1m} T LONG, DOS-ONLY lib can't have descriptions


OLONERR {[0;1;31m
!JГЬд ЩитЯЮбШд ШиоЬхШ.!)
[0;1m} T LONG, no files found


OLONINF {[0;1;32m
АРХДИО:         [36m%d Шзц %d} T LONG, file info (prepended to file info header)


OLONCONT {[0;1m
ЗтвЬлЬ дШ ШввсеЬлЬ лЮд вЬзлжгЬиу зЬиаЪиШну Шмлжч лжм ШиоЬхжм; ([[33mY[37m~]es=дШх / [[33mN[37m~]o=цоа) [0m} T LONG, asking whether to edit file description


OLONCND {[Enter=%c] } T LONG, default value for OLONCONT




ODELASK {[0;1m
!JГщйлЬ ждцгШлШ ШиоЬхрд зижк ЫаШЪиШну (лШ wildcards вЬалжмиЪжчд бШа ЯШ
ЬирлЮЯЬхлЬ ориайлс ЪаШ лЮд ЫаШЪиШну бсЯЬ ШиоЬхжм). ГщйлЬ [33m?[37m ЪаШ
бШлсвжЪж лЮк ШиоЬажЯубЮк @LIB@:!) [0m} T DEL, asking for file


ODELERR {[0;1;31m
!JГЬд ЩитЯЮбШд ШиоЬхШ.!)
[0;1m} T DEL, no files found


ODELNUM {[0;1;32m
!JБитЯЮбШд %d ШиоЬхШ.!)
[0;1m} T DEL, number of files found (when number>1)


ODELOS {[0;1;31m
!W[0;1;33;5m██[0;1;33m ПРОСОХЖ: !iЖ ШиоЬажЯубЮ ЬхдШа "DOS-ONLY". ТШ
ШиоЬхШ ЯШ ЫаШЪиШнжчд Шзц лжд ГИСЙО.!)
!0l[0;1m} T DEL, DOS-ONLY lib, files will be physically removed



ODELMOD {[0;1m
!JМШ ЫаШЪиспжмгЬ лж ШиоЬхж у лШ ШиоЬхШ бШа Шзц лж Ыхйбж;
[5mПРОСОХЖ:[0;1m Ю ЫаШЪиШну ЬхдШа гЮ ШдШйлитпагЮ!
([[33mY[37m~]es=дШа / [[33mN[37m~]o=цоа)!)[0m } T DEL, erase files or remove them from the library index?


ODELINF {[0;1;32m
АРХДИО:         [36m%d Шзц %d} T DEL, file info (prepended to file info header)


ODELMNU {[0;1m
!JГаШЪиШну; [[33mY[37m]es=дШа, [[33mN[37m]o=цоа, [[33mA[37m]ll=дШа йЬ цвШ:!) [0m} T DEL, per-file deletion confirmation


ODELOK {[0;1;32m
!JТж ШиоЬхж [37m%s[32m ШнШаитЯЮбЬ Шзц лЮд ШиоЬажЯубЮ (зШиШгтдЬа цгрк йлжд Ыхйбж).!)} T DEL, confirmation of file removal (not deleted from disk)


ODELOKD {[0;1;33m
!JТж ШиоЬхж [37m%s[33m ШнШаитЯЮбЬ Шзц лЮд ШиоЬажЯубЮ бШа лжд Ыхйбж.!)} T DEL, confirmation of file removal and deletion



OMOVASK {[0;1m
!JГщйлЬ ждцгШлШ ШиоЬхрд зижк ШввШЪу ШиоЬажЯубЮк (лШ wildcards вЬалжмиЪжчд бШа ЯШ
ЬирлЮЯЬхлЬ ориайлс ЪаШ лЮд гЬлШнжис бсЯЬ ШиоЬхжм). ГщйлЬ [33m?[37m ЪаШ
бШлсвжЪж лЮк ШиоЬажЯубЮк @LIB@:!) [0m} T MOVE, asking for file


OMOVERR {[0;1;31m
!JГЬд ЩитЯЮбШд ШиоЬхШ.!)
[0;1m} T MOVE, no files found


OMOVNUM {[0;1;32m
!JБитЯЮбШд %d ШиоЬхШ.!)
[0;1m} T MOVE, number of files found (when number>1)


OMOVOS {[0;1;31m
!W[0;1;33;5m██[0;1;33m ПРОСОХЖ: !iЖ ШиоЬажЯубЮ ЬхдШа "DOS-ONLY". ТШ
ШиоЬхШ ЯШ ЫаШЪиШнжчд Шзц лжд ГИСЙО.!)
!0l[0;1m} T MOVE, DOS-ONLY lib, files will be physically removed


OMOVMOD {[0;1m
!JМШ ЫаШЪиспжмгЬ лж ШиоЬхж у лШ ШиоЬхШ бШа Шзц лж Ыхйбж Шнжч лШ гЬлШбадуйжмгЬ;
[5mПРОСОХЖ:[0;1m Ю ЫаШЪиШну ЬхдШа гЮ ШдШйлитпагЮ!
([[33mY[37m~]es=дШа / [[33mN[37m~]o=цоа)!)[0m } T MOVE, erase files or remove them from the library index?


OMOVTRG {[0;1m
!JГщйлЬ лж ПКЖРДС цджгШ лЮк ШиоЬажЯубЮк йлЮд жзжхШ ЯтвЬлЬ дШ гЬлШбадуйжмгЬ
лШ ШиоЬхШ, у [33m?[37m ЪаШ дШ ЫЬхлЬ лЮд аЬиШиохШ лрд ШиоЬажЯЮбщд:!)[0m } T MOVE, asking for target


OMOVTR1 {[0;1;31m
!JГЬд тоЬа дцЮгШ дШ гЬлШбадуйЬлЬ ШиоЬхШ Шзц лЮд ШиоЬажЯубЮ @LIB@ йлжд ЬШмлц лЮк!!)
[0;1m} T MOVE, can't move files onto themselves


OMOVTR2 {[0;1;31m
!JГЬд ЩитЯЮбЬ Ю ШиоЬажЯубЮ.!)
[0;1m} T MOVE, target library not found


OMOVTR3 {[0;1;31m
!JТж ЬзхзЬЫж зицйЩШйук йШк ЫЬд йШк ЬзалитзЬа дШ лж гЬлШнтиЬлЬ ШиоЬхШ й'Шмлу лЮд ШиоЬажЯубЮ.!)
[0;1m} T MOVE, no libop access in target library


OMOVTR4 {[0;1;31m
!JЖ ШиоЬажЯубЮ ЬхдШа read-only. ГЬд гзжижчгЬ дШ гЬлШнтижмгЬ ЬбЬх ШиоЬхШ.!)
[0;1m} T MOVE, target library is read-only


OMOVINF {[0;1;32m
АРХДИО:         [36m%d Шзц %d} T MOVE, file info (prepended to file info header)


OMOVMNU {[0;1m
!JЛЬлШнжис; [[33mY[37m]es=дШа, [[33mN[37m]o=цоа, [[33mA[37m]ll=дШа йЬ цвШ:!) [0m} T MOVE, per-file move confirmation


OMOVOK {[0;1;32m
!JТж ШиоЬхж [37m%s[32m гЬлШнтиЯЮбЬ.!)} T MOVE, confirmation of file removal (not deleted from disk)


OMOVOKD {[0;1;33m
!JТж ШиоЬхж [37m%s[33m гЬлШнтиЯЮбЬ (лж ШиоЬхж йЩуйлЮбЬ Шзц лЮд зЮЪШхШ ШиоЬажЯубЮ).!)} T MOVE, confirmation of file removal (deleted from disk)


OMOVFAIL {[0;1;31m
!JСлШгШлсгЬ лЮд гЬлШбхдЮйЮ ШиоЬхрд.
Ж ШиоЬажЯубЮ йлЮд жзжхШ гЬлШнтижмгЬ лШ ШиоЬхШ тоЬа звтжд ЪЬгхйЬа.!)
[0;1m} T MOVE, target library is full, aborting


OMOVEXT {[0;1;31m
!JТж ШиоЬхж [37m%s[31m мзсиоЬа уЫЮ йлЮд сввЮ ШиоЬажЯубЮ. ГЬд лж гЬлШбаджчгЬ.!)
[0;1m} T MOVE, file already exists in target library










OCPYASK {[0;1m
!JГщйлЬ ждцгШлШ ШиоЬхрд зижк ШдлаЪиШну йЬ сввЮ ШиоЬажЯубЮ (лШ wildcards вЬалжмиЪжчд бШа ЯШ
ЬирлЮЯЬхлЬ ориайлс ЪаШ лЮд гЬлШнжис бсЯЬ ШиоЬхжм). ГщйлЬ [33m?[37m ЪаШ
бШлсвжЪж лЮк ШиоЬажЯубЮк @LIB@:!) [0m} T COPY, asking for file


OCPYNUM {[0;1;32m
!JБитЯЮбШд %d ШиоЬхШ.!)
[0;1m} T COPY, number of files found (when number>1)


OCPYERR {[0;1;31m
!JГЬд ЩитЯЮбШд ШиоЬхШ.!)
[0;1m} T COPY, no files found


OCPYTRG {[0;1m
!JГщйлЬ лж ПКЖРДС цджгШ лЮк ШиоЬажЯубЮк йлЮд жзжхШ ЯтвЬлЬ дШ ШдлаЪиспжмгЬ
лШ ШиоЬхШ, у [33m?[37m ЪаШ дШ ЫЬхЬлЬ лЮд аЬиШиохШ лрд ШиоЬажЯЮбщд:!)[0m } T COPY, asking for target


OCPYTR1 {[0;1;31m
!JГЬд тоЬа дцЮгШ дШ ШдлаЪиспЬлЬ ШиоЬхШ Шзц лЮд ШиоЬажЯубЮ @LIB@ йлжд ЬШмлц лЮк!!)
[0;1m} T COPY, can't move files onto themselves


OCPYTR2 {[0;1;31m
!JГЬд ЩитЯЮбЬ Ю ШиоЬажЯубЮ.!)
[0;1m} T COPY, target library not found


OCPYTR3 {[0;1;31m
!JТж ЬзхзЬЫж зицйЩШйук йШк ЫЬд йШк ЬзалитзЬа дШ лж ШдлаЪиспЬлЬ
ШиоЬхШ й'Шмлу лЮд ШиоЬажЯубЮ.!)
[0;1m} T COPY, no libop access in target library


OCPYTR4 {[0;1;31m
!JЖ ШиоЬажЯубЮ ЬхдШа read-only. ГЬд гзжижчгЬ дШ ШдлаЪиспжмгЬ
ЬбЬх ШиоЬхШ.!)
[0;1m} T COPY, target library is read-only


OCPYINF {[0;1;32m
АРХДИО:         [36m%d Шзц %d} T COPY, file info (prepended to file info header)


OCPYMNU {[0;1m
!JАдлаЪиШну; [[33mY[37m]es=дШа, [[33mN[37m]o=цоа, [[33mA[37m]ll=дШа йЬ цвШ:!) [0m} T COPY, per-file copy confirmation


OCPYOK {[0;1;32m
!JТж ШиоЬхж [37m%s[32m ШдлаЪиснЯЮбЬ.!)} T COPY, confirmation of file removal (not deleted from disk)


OCPYFAIL {[0;1;31m
!JСлШгШлсгЬ лЮд ШдлаЪиШну ШиоЬхрд.
Ж ШиоЬажЯубЮ йлЮд жзжхШ гЬлШнтижмгЬ лШ ШиоЬхШ тоЬа звтжд ЪЬгхйЬа.!)
[0;1m} T COPY, target library is full, aborting


OCPYEXT {[0;1;31m
!JТж ШиоЬхж [37m%s[31m мзсиоЬа уЫЮ йлЮд сввЮ ШиоЬажЯубЮ. ГЬд лж гЬлШбаджчгЬ.!)
[0;1m} T COPY, file already exists in target library


































ENTPASS {[0;1m
!WПШиШбШвщ ЫщйлЬ лж йчдЯЮгШ лЮк ШиоЬажЯубЮк (ЯШ ЩвтзЬлЬ
ШйлЬихйбжмк):!)[0m } T Enter library password


WRNGPSS {[0;1;31m
!JКмзсгШа, Шмлц лж йчдЯЮгШ ЫЬд ЬхдШа йрйлц. ПШиШбШвщ еШдШзижйзШЯуйлЬ.!)
[0;1m} T Library password is incorrect


FAILPASS {[0;1;31m
!JКмзсгШа, ЫЬд нШхдЬлШа дШ тоЬлЬ лж йрйлц йчдЯЮгШ лЮк ШиоЬажЯубЮк.
АзжблуйлЬ лж бШа еШдШЫжбагсйлЬ.!)
[0;1m} T Password entry failed









FTUNK {АЪдщйлжм лчзжм - мзуиеЬ всЯжк.} T File type detection failed



















LIBRO {[0;1;31m
!JСмЪЪдщгЮ, Шмлу Ю ЩаЩважЯубЮ ЫЬд ЬзалитзЬа бШЯцвжм Шзжйлжвтк (ЬхдШа гцдж
ШдсЪдрйЮк).!)
[0;1m} T This library is read-only


LIBFULF {[0;1;31m
!JСмЪЪдщгЮ, Шмлу Ю ШиоЬажЯубЮ ЫЬд гзжиЬх дШ ЫЬоЯЬх зЬиаййцлЬиШ ШиоЬхШ.
ГщйлЬ [33mI[31m ЪаШ дШ ЫЬхлЬ лШ циаШ лЮк ШиоЬажЯубЮк.!)
[0;1m} T This library cannot accept any more files


LIBFULB {[0;1;31m
!JСмЪЪдщгЮ, Шмлу Ю ШиоЬажЯубЮ ЫЬд гзжиЬх дШ ЫЬоЯЬх зЬиаййцлЬиШ bytes.
ГщйлЬ [33mI[31m ЪаШ дШ ЫЬхлЬ лШ циаШ лЮк ШиоЬажЯубЮк.!)
[0;1m} T The total number of bytes in this library has been exceeded


UPLWNCR {[0;1;31m
!JСмЪЪдщгЮ, Шввс ЫЬд тоЬлЬ ШибЬлтк гждсЫЬк ЪаШ дШ йлЬхвЬлЬ ШиоЬхж й'Шмлу
лЮд ШиоЬажЯубЮ. ГщйлЬ [33mI[31m ЪаШ дШ ЫЬхлЬ лак оиЬщйЬак лЮк ШиоЬажЯубЮк.!)
[0;1m} T The user can't afford an upload


SIZEWARN {[0;1;32m
!JПРОСОХЖ: ЛзжиЬхлЬ дШ йлЬхвЬлЬ гтоиа [37m%d[32m %s, гЬ ймджвабц гтЪЬЯжк
гтоиа бШа [37m%d[32m %s. ЙсЯЬ ШиоЬхж зитзЬа дШ тоЬа гтЪЬЯжк гтоиа бШа
[37m%d[32m %s. АиоЬхШ зжм зШиШЩШхджмд лШ циаШ ЫаШЪиснждлШа ШмлцгШлШ.!)
[0;1m} T Warning about total size of upload


FILESNG {ШиоЬхж} T 'files', singular
FILEPLR {ШиоЬхШ} T 'files', plural


UPLNAX {[0;1;31m
!JКмзжчгШйлЬ, лж ЬзхзЬЫж зицйЩШйук йШк ЫЬд йШк ЬзалитзЬа лЮд Шзжйлжву
ШиоЬхрд й'Шмлу лЮд ШиоЬажЯубЮ.!)
[0;1m} T Upload, user has no upload


UPLASK {[0;1m
!WГщйлЬ лж цджгШ лжм ШиоЬхжм зжм ЯтвЬлЬ дШ йлЬхвЬлЬ,
у [33m*[37m ЪаШ дШ йлЬхвЬлЬ зсдр Шзц тдШ ШиоЬхж лШмлцоиждШ:!) [0m} T Upload, ask for filename


FNERR {[0;1;31m
!JТж цджгШ зжм ЫщйШлЬ зЬиатоЬа гЮ ШзжЫЬблжчк оШиШблуиЬк. АзжЫЬблжх
оШиШблуиЬк ЬхдШа жа Ьеук (бЬнШвШхШ бШа габис ЪисггШлШ ЫЬд зШхЭжмд ицвж):!)

[33m!C%s!)
[0;1m} T Upload, unacceptable characters in filename


FDNDOS {[0;1;31m
!JТж цджгШ зжм ЫщйШлЬ ЫЬд ЬхдШа ШзжЫЬблц цджгШ ШиоЬхжм. ПитзЬа дШ
ЫщйЬлЬ гтоиа 1-8 оШиШблуиЬк, лЬвЬхШ бШа гтоиа 3 оШиШблуиЬк (xxxxxxxx.xxx).
Тж ЫЬчлЬиж лгугШ (Шзц лЮд лЬвЬхШ бШа гЬлс) ЬхдШа зижШаиЬлабц. ЛзжиЬх
дШ мзсиоЬа гцдж гхШ лЬвЬхШ йлж цджгШ ШиоЬхжм.!)
[0;1m} T Upload, not a DOS (or CP/M or TOS) filename


UPLDUP {[0;1;31m
!JКмзсгШа, мзсиоЬа уЫЮ ШиоЬхж гЬ Шмлц лж цджгШ йлЮд ШиоЬажЯубЮ.
ПШиШбШвщ еШдШЫжбагсйлЬ, у ЬаЫжзжауйлЬ лжд ШиоЬажЯЮбсиаж.!)
[0;1m} T Upload, file already exists


UPLCAN {[0;1;31m
!JАбчирйЮ Шзжйлжвук.!)
[0;1m} T Upload canceled
 

UPLCAN1 {[0;1;31m
!JАбчирйЮ Шзжйлжвук лрд мзцвжазрд ШиоЬхрд.!)
[0;1m} T Upload canceled for the rest of the files


UPLINF1 {[0;1m
ОджгШ ШиоЬхжм . . .  [32m%s[37m
ЛтЪЬЯжк  . . . . . . [32m%d %s[37m
Тчзжк ШиоЬхжм . . .  [32m!i!W%s!)[37m
!0l[0;1m} T Upload, file information (single file)


UPLINFM {[0;1m
АиоЬхж . . . . . . . [32m%d %s[37m
Титожд цджгШ  . . .  [32m%s[37m
ЛтЪЬЯжк  . . . . . . [32m%d %s[37m
Тчзжк ШиоЬхжм . . .  [32m!i!W%s!)[37m
!0l[0;1m} T Upload, file information (multiple files)


REMSNG {(ШзжгтдЬа сввж тдШ)} T Remaining, singular form

REMPLR {(Шзжгтджмд сввШ %d)} T Remaining, plural form

REMZER {(лЬвЬмлШхж ШиоЬхж)} T Remaining, no files remaining


BYTESNG {byte} T Byte, singular form

BYTEPLR {bytes} T Bytes, plural form


UPLNAG {[0;1m
!WНШдШЫщйлЬ лж цджгШ лжм ШиоЬхжм: !) [0m} T Upload, ask for name again


UPLXLNF {[0;1;31m
!JЖ ШиоЬажЯубЮ ЫЬд гзжиЬх дШ оритйЬа сввШ ШиоЬхШ. ГаШЪиснжмгЬ ШмлцгШлШ лж
зШиШзсдр бШа лмоцд ЬдШзжгЬхдШдлШ ШиоЬхШ.!)
[0;1m} T Upload, library can't fit any more files


UPLXLNB {[0;1;31m
!JЖ ШиоЬажЯубЮ ЫЬд гзжиЬх дШ оритйЬа сввШ bytes. ГаШЪиснжмгЬ ШмлцгШлШ лж
зШиШзсдр бШа лмоцд ЬдШзжгЬхдШдлШ ШиоЬхШ.!)
[0;1m} T Upload, library can't fit any more bytes


UPLXLBF {[0;1;31m
!JТж зШиШзсдр ШиоЬхж еЬзЬидсЬа лж циаж гЬЪтЯжмк ШиоЬхжм. ГаШЪиснЬлШа
ШмлцгШлШ.!)
[0;1m} T Upload, this file exceeds the size-per-file limit


UPLNCR {[0;1;31m
!JКмзжчгШйлЬ, Шввс ЫЬд тоЬлЬ ШибЬлтк гждсЫЬк ЪаШ дШ бШвчпЬлЬ лЮд Шзжйлжву
ШиоЬхжм. ГаШЪиснжмгЬ лж литожд бШа лмоцд ЬдШзжгЬхдШдлШ ШиоЬхШ.!)
[0;1m} T Upload, ran out of credits while uploading


UPLSHDS {[0;1m
!JГщйлЬ гаШ йчдлжгЮ (гтоиа 43 оШиШблуиЬк) зЬиаЪиШну лжм зШиШзсдр
ШиоЬхжм.!)

           ├─────────────────────────────────────────┤
ПЬиаЪиШну: [0m} T Upload, asking for short file description


UPLSDMT {[0;1;31m
!JКмзсгШа, ЫЬд гзжижчгЬ дШ ЬзалитпжмгЬ лЮд Шзжйлжву ШиоЬхрд орихк
зЬиаЪиШнтк.!)
[0;1m} T Upload, no empty descriptions allowed


UPLACN {[0;1;31m
!JПШиШбШвщ ЬзаЩЬЩШащйлЬ цла ЯтвЬлЬ дШ [37mЬЪбШлШвЬхпЬлЬ цвШ[31m
лШ ШиоЬхШ зжм Шзжгтджмд. ТШ ШиоЬхШ ЯШ ЫаШЪиШнжчд. Ад ЯтвЬлЬ дШ
ЬЪбШлШвЬхпЬлЬ гцдж лж литожд ШиоЬхж, ШзШдлуйлЬ [33mN[31mo (цоа). ЗШ
ЬирлЮЯЬхлЬ йчдлжгШ Шд ЯтвЬлЬ дШ биШлуйЬлЬ лж ШиоЬхж.!)

[37m!WМШ ЫаШЪиспжмгЬ лШ ШиоЬхШ зжм Шзжгтджмд; ([[33mY[37m]es=дШх /
[[33mN[37m]o=цоа) !)[0m} T Upload, abort ALL uploaded files?


UPLACR {[0;1;31m
!JПШиШбШвщ ШзШдлуйлЬ гЬ [33mY[31m у [33mN[33m.!)
[0;1m} T Upload, invalid answer to UPLACN


UPLDIZW {[0;1;32m
ЛаШ йлаЪгу, зШиШбШвщ. ДзаЯЬрищ лж ШиоЬхж...} T Upload, looking for FILE_ID.DIZ in file

UPLDIZF {[0;1m

!JБитЯЮбЬ лж ШиоЬхж [32m%s[37m гЬ лШ Ьеук зЬиаЬоцгЬдШ:!)

[0;1m!F─
[0m%s
[0;1m!F─
[0m} T Upload, found FILE_ID.DIZ or similar, displaying


UPLDIZA {[0;1m
!WЗтвЬлЬ дШ ЬайсЪжмгЬ лШ зШиШзсдр рк лЮд вЬзлжгЬиу зЬиаЪиШну лжм ШиоЬхжм йШк;
Ад ЫЬд ЯтвЬлЬ, ЯШ гзЬхлЬ йлжд ймдлсблЮ бЬагтджм ЪаШ дШ ЫщйЬлЬ Ыабу йШк
зЬиаЪиШну у дШ ШввсеЬлЬ лЮд литожмйШ
([[33mY[37m]es=дШх / [[33mN[37m]o=цоа)!) [0m} T Upload, make FILE_ID.DIZ the long description?


UPLDIZR {[0;1;31m
!JПШиШбШвщ ШзШдлуйлЬ гЬ [33mY[31m у [33mN[33m.!)
[0;1m} T Upload, wrong answer to UPLDIZA


UPLLDES {[0;1;37m

!JТщиШ зитзЬа дШ ЫщйЬлЬ лЮд вЬзлжгЬиу зЬиаЪиШну лжм ШиоЬхжм.
Тж гтЪайлж губжк лЮк зЬиаЪиШнук ЬхдШа [32m%d оШиШблуиЬк[37m.!)
!P
} T Upload, calling editor to form long description


UPLKEYS {[0;1m
!JГщйлЬ лак втеЬак бвЬаЫас зжм оШиШблЮихЭжмд Шмлц лж ШиоЬхж.
Ад ЫЬд ЪдрихЭЬлЬ лЮ оиуйЮ лрд втеЬрд бвЬаЫащд ЫщйлЬ "[33m?[0;1m".
ОлШд лЬвЬащйЬлЬ лЮд ЬайШЪрЪу лрд втеЬрд бвЬаЫащд ЫщйлЬ "[33m.[0;1m"
Шдлх ЪаШ втеЮ бвЬаЫх.!)
[0;1m} T Upload, enter keywords, intro


UPLKEY {[0;1m
КтеЮ бвЬаЫх #[32m%d[37m:[0m } T Upload, enter keywords, ask for keyword


UPLKEYC {[0;1m
!JСмдЬохйлЬ дШ ЫхдЬлЬ втеЬак бвЬаЫас. ОлШд лЬвЬащйЬлЬ ЫщйлЬ "[33m.[0;1m"
у ЫщйлЬ e[[33mX[0;1m]it ЪаШ тежЫж ЬЪбШлШвЬхзждлШк лЮд ЬайШЪрЪу
[32mцврд[37m лрд ШиоЬхрд.!)
[0;1m} T Upload, enter keywords, continue typing keywords


UPLKEYR {[0;1;31m
!JЛЮ ШзжЫЬблу втеЮ бвЬаЫх.
Оа втеЬак бвЬаЫас тожмд губжк трк [37m23[31m оШиШблуиЬк бШа гзжижчд дШ
ШзжлЬвжчдлШа Шзц АВВКИЙА ЪисггШлШ, джчгЬиШ, бШа лШ йчгЩжвШ [33m,[31m (бцггШ)
[33m'[31m (Шзцйлижнжк) бШа [33m-[31m (зШчвШ). ГЬд ЬзалитзждлШа бЬдс.!)

!JГщйлЬ [33m?[31m ЪаШ зЬиаййцлЬиЬк звЮижнжихЬк,
[33m.[0;1m Шдлх ЪаШ лЮ втеЮ бвЬаЫх ЪаШ дШ лЬвЬащйЬлЬ, у [33mХ[31m ЪаШ
тежЫж.!)
[0;1m} T Upload, enter keywords, keyword rejected


UPLKEYD {[0;1;31m
!JДоЬлЬ уЫЮ ЬайсЪЬа Шмлу лЮ втеЮ бвЬаЫх Ъа'Шмлц лж ШиоЬхж.!)
[0;1m} T Upload, enter keywords, duplicate keyword


UPLKEYH {[0;1m
!JКтеЬак бвЬаЫас ЬзаймдсзлждлШа йЬ бсЯЬ ШиоЬхж йлЮд ШиоЬажЯубЮ тлйа щйлЬ лж
ШиоЬхж дШ гзжиЬх дШ ЩиЬЯЬх ЩсйЬа лжм зЬиаЬожгтджм лжм. Оа втеЬак бвЬаЫас зжм
ЫхдЬлЬ ЬЫщ зитзЬа дШ оШиШблЮихЭжмд лж ШиоЬхж. ДвШоайлжзжауйлЬ ймдлгуйЬак,
ймдщдмгШ бШа сввЬк втеЬак зжм йзШлШвжчд ощиж, Шввс зижйзШЯуйлЬ дШ ЫщйЬлЬ
втеЬак бвЬаЫас зжм лШаиасЭжмд йлж ШиоЬхж бШа ЯШ ЩжЮЯуйжмд сввжмк оиуйлЬк дШ
лж Щижмд орихк дШ етижмд ШбиаЩщк лж цджгс лжм. АзжнчЪЬлЬ втеЬак бвЬаЫас зжм
ЬхдШа зжвч ШйШнЬхк у зжвч ймЪбЬбиагтдЬк. ПижйзШЯуйлЬ дШ ШбжвжмЯуйЬлЬ лжд
лицзж зжм тожмд ЫрЯЬх втеЬак бвЬаЫас йлШ сввШ ШиоЬхШ лЮк ШиоЬажЯубЮк ЪаШ
вцЪжмк жгжажгжинхШк бШа ЬмбжвхШк оиуйЮк.!)

!JАд зитзЬа дШ оиЮйагжзжауйЬлЬ гхШ втеЮ бвЬаЫх гЬ зжввс ймдЯЬлабс,
оиЮйагжзжауйлЬ лж бцггШ ([33m,[37m) бШа ниждлхйлЬ Ю заж йЮгШдлабу/ШйШнук
втеЮ дШ ЬгнШдхЭЬлШа зищлЮ (ЪаШ зШисЫЬаЪгШ, "america,north" у
"driver,ethernet". АзжнчЪЬлЬ лак втеЬак бвЬаЫас гЬ зжввс ймдЯЬлабс, гаШ бШа
ЫЬд ЫаЬмбжвчджмд зжвч лЮд ЬчиЬйЮ лжм ШиоЬхжм.!)

!JЛзжиЬхлЬ дШ ЫщйЬлЬ гтоиа бШа [32m@MAXKEYW@[37m втеЬак бвЬаЫас ЪаШ бсЯЬ ШиоЬхж.
Оа втеЬак бвЬаЫас ЬгнШдхЭждлШа зсдлШ гЬ габис ЪисггШлШ (гзжиЬхлЬ цгрк дШ лак
ЪиспЬлЬ гЬ бЬнШвШхШ). ЙсЯЬ втеЮ бвЬаЫх гзжиЬх дШ зЬиатоЬа гтоиа [32m23[37m
оШиШблуиЬк. ДзалиЬзлжх оШиШблуиЬк ЬхдШа жа Ьеук (ЫЬд ЬзалитзждлШа бЬдс):!)

!Cabcdefghijklmnopqrstuvwxyz 0123456789 , ' -!)

!W[0;1mКтеЬак бвЬаЫас зжм тоЬлЬ уЫЮ ЫщйЬа:[0m %s!)
[0;1m} T Upload, enter keywords, help



FILEHDR1 {[0;1m
АРХДИО:     [32m%-23.23s  [37mСТАКЗЖЙД: [32m%s %s[37m
АПОСТОКДАС: [32m%-23.23s  [37mДКЖФЗЖ:   [32m%d нжи%s[37m
ЛДВДЗОС:    [32m%d bytes[37m
} T File Header after upload, part 1 (filename, uploader and size)

FILEHDR2 {ДВЙРИЗЖЙД:  [32mАзц %s[37m
} T File Header after upload, part 2 (approved by)

FILEHDR3 {ТУПОС:      [32m%.66s[37m
ЙКДИГИА:    [32m!i!W%s!)[37m
!0lПДРИВРАФЖ:  [32m%s

%s

[0;1m} T File Header after upload, part 3 (keywords and descriptions)

TIMESNG {с} T Times, singular
TIMEPLR {тк} T Times, plural


LASTCON {[0;1m
!WЗтвЬлЬ дШ ЬайсЪжмгЬ лж зШиШзсдр ШиоЬхж; ([[33mY[37m]es=дШх,
[[33mN[37m]o=цоа у [[33mE[37m]dit=ШввШЪу йлжаоЬхрд):!) } T Upload, Final file confirmation

LASTCND {[Enter=[33m%c[37m][0m } T Upload, default answer for last confirmation



FILEINST {[0;1;33m
!JТж ШиоЬхж ШдлаЪиснЬлШа.!)
[0;1m} T Upload, installing file


NEEDSAPP {[0;1;33m
!JСШк ЬмоШиайлжчгЬ ЪаШ лЮд Шзжйлжву. Тж ШиоЬхж ЯШ ЬхдШа ЫаШЯтйагж йлжмк
мзцвжазжмк оиуйлЬк Шнжч лж ЬвтЪеЬа ж ШиоЬажЯЮбсиажк.!)
[0;1m} T Thanks for upload, file still needs human approval






LIBWLCK {[0;1;33m
!JПШиШбШвщ зЬиагтдЬлЬ, Ю ШиоЬажЯубЮ ЩихйбЬлШа йЬ оиуйЮ Шмлу лЮ йлаЪгу.!)
[0;1m} T Please stand by, library in use


LIBFLCK {[0;1;31m
!JКмзжчгШйлЬ, Шввс Ю ШиоЬажЯубЮ ЫЬд ЬвЬмЯЬищЯЮбЬ йлж оиждабц ЫасйлЮгШ зжм
зЬиагтдШгЬ. Ийрк бсла ЫЬд зсЬа бШвс. ДаЫжзжауйлЬ лжд оЬаиайлу ймйлугШлжк.!)
[0;1m} T Failed to get library lock.






FLEMPT {[0;1m
!JЖ ШиоЬажЯубЮ ЬхдШа сЫЬаШ.!)
[0;1m} T File Listing, empty library


FLNUNA {[0;1m
!JЖ ШиоЬажЯубЮ ЫЬд тоЬа гЮ ЬЪбЬбиагтдШ ШиоЬхШ.!)
[0;1m} T File Listing, no unapproved files


FLCAN {[0;1;31m
!JТЬигШлайгцк бШлШвцЪжм.!)
[0;1m} T File Listing, listing aborted


FLHDR {[0;1;32m
!CЙШлсвжЪжк ШиоЬхрд лЮк ШиоЬажЯубЮк [37m@LIB@[32m.!)

[37mОджгШ ШиоЬхжм           ЛтЪЬЯжк АзжйлжвтШк ПЬиаЪиШну
!F─
[0m} T File Listing header































FLHDRU {[0;1;32m
!CЙШлсвжЪжк гЮ ЬЪбЬбиагтдрд ШиоЬхрд лЮк ШиоЬажЯубЮк [37m@LIB@[32m.!)

[37mОджгШ ШиоЬхжм           ЛтЪЬЯжк АзжйлжвтШк ПЬиаЪиШну
!F─
[0m} T File Listing header


FLLST {[0m%-22.22s %8d %-10.10s %.36s
} T File Listing line


FLFTR {[0;1m!F─
[32m%6d[37m ШиоЬхШ        [32m%10d[37m bytes
[0;1m} T File Listing footer


FLOHDR {[0;1;32m
!CЙШлсвжЪжк ШиоЬхрд лЮк ШиоЬажЯубЮк [37m@LIB@[32m.!)

[37mЛтЪЬЯжк    ЖгЬижгЮдхШ бШа ЧиШ   ОджгШ ШиоЬхжм           
!F─
[0} T File Listing header (OSDIR)


FLOLST {[0m%9d  %-9.9s %-8.8s   %s
} T File Listing line (OSDIR)


FLOFTR {[0;1m!F─
[32m%d[37m ШиоЬхШ, [32m%d[37m bytes
[0;1m} T File Listing footer (OSDIR)


FLRHDR {[0;1;32m
!CЙШлсвжЪжк ШиоЬхрд лЮк ШиоЬажЯубЮк [37m@LIB@[32m.!)

!F─
[0m} T File Listing header (showing ready-made index file)


FLRFTR {[0;1m!F─
[0;1m} T File Listing footer (ready-made index file)







FILECACH {[0;1;33m
!WЛаШ йлаЪгу зШиШбШвщ, ШдлаЪиснр лж ШиоЬхж йлж cache ЪаШ гЬЪШвчлЬиЮ
лШочлЮлШ...!) [0;1m} T File cache, copying file to the cache.


FILECOK {ДдлсеЬа.
[0;1m} T File cache, file copied ok.



SRASK {[0;1m
!JГщйлЬ лжд циж ЪаШ лжд жзжхж ЯШ ЬиЬмдуйжмгЬ лЮд ШиоЬажЯубЮ @LIB@
([33m?[37m ЪаШ ЩжуЯЬаШ зсдр йлжмк цижмк ЬиЬчдЮк):[0m!) } T Search for files, asking for search terms


SRHELP {[0;1m
!JЛЬ лЮ ЩжуЯЬаШ Шмлук лЮк Ьдлжвук гзжиЬхлЬ дШ ЬдлжзхйЬлЬ ШиоЬхШ зжм йШк
ЬдЫаШнтижмд йлак ШиоЬажЯубЬк лЮк @BBS@. Ж тиЬмдШ ЯШ ЫаЬеШоЯЬх йлЮд ШиоЬажЯубЮ
@LIB@ Шввс бШа йЬ цйЬк ЩихйбждлШа бслр лЮк йлЮд аЬиШиохШ. ЙЬнШвШхШ бШа габис
ЯЬрижчдлШа айжЫчдШгШ.!)

!JДЫщ йШк ЭЮлЬхлЬ дШ ЫщйЬлЬ тдШд циж тиЬмдШк. О цижк гзжиЬх дШ тоЬа гхШ Шзц
лак Ьеук гжинтк:!)

!J[33mfilename[37m  !10iОджгШ ШиоЬхжм. ДзалитзждлШа бШа wildcards (зо
[33mdoc*.txt[37m). ЗШ псежмгЬ ЪаШ ШиоЬхШ гЬ Шмлц лж цджгШ. [32m*[37m!)
!0l
!J[33m/regexp/[37m  !10iОджгШ ШиоЬхжм рк unix regular expression (зо лж
[33m/^doc[0-9]{3~}/[37m ЩихйбЬа лШ ШиоЬхШ лрд жзжхрд лж цджгШ еЬбадсЬа гЬ "doc"
бШа ШбжвжмЯЬхлШа Шзц лихШ ШиаЯгЮлабс пЮнхШ). ЗШ ЩиЬЯжчд цвШ лШ ШиоЬхШ зжм
зЬиатожмд лж regular expression жзжмЫузжлЬ йлж цджгс лжмк. ОвЮ Ю
айочк лрд regular expressions ЬхдШа ЫаШЯтйагЮ. Ж лЬвабу бсЯЬлжк "[33m/[37m"
ЬхдШа зижШаиЬлабу. ВаШ зЬиаййцлЬиЬк звЮижнжихЬк зсдр йлШ regular expressions,
ЫЬхлЬ тдШ Unix manual у лак жЫЮЪхЬк оиуйЮк лЮк Ьдлжвук grep. [32m*[37m!)
!0l
!J[33m+keyword[37m  !10iГщйлЬ "ймд" бШа гаШ втеЮ бвЬаЫх ЪаШ дШ псежмгЬ ЪаШ
ШиоЬхШ гЬ Шмлу лЮ втеЮ бвЬаЫх. ЛзжиЬхлЬ дШ оиЮйагжзжауйЬлЬ wildcards бШа ЬЫщ.
[32m*[37m!)!)
!0l
!J[33m+/regexp/[37m !10iДиЬмдШ ЪаШ втеЮ бвЬаЫх ЫрйгтдЮ рк unix regular
expression. ЗШ ЩиЬЯжчд цвШ лШ ШиоЬхШ гЬ втеЬак бвЬаЫас зжм зЬиатожмд лж
regular expression зжм ЫхдЬлЬ ЬЫщ. ИйочЬа ц,ла бШа зШиШзсдр ЪаШ лШ ждцгШлШ
ШиоЬхрд рк regular expressions. [32m*[37m!)
!0l
!0l
!J[33m?word[37m     !10iГщйлЬ вШладабц ЬирлЮгШлабц бШа гхШ втеЮ ЪаШ дШ псежмгЬ ЪаШ
ШиоЬхШ гЬ Шмлу лЮ втеЮ бвЬаЫх жзжмЫузжлЬ йлЮд ЬзабЬнШвхЫШ лжмк (зо йлЮд зЬиаЪиШну у йлж
цджгШ лжм ШзжйлжвтШ). ТШ wildcards ЫЬд вЬалжмиЪжчд ЬЫщ, Шввс Ю тиЬмдШ ЬхдШа
нрдЮлабу, тлйа щйлЬ Шд, зо, псеЬлЬ ЪаШ "[33mйчйжз[37m", лж йчйлЮгШ ЯШ ЩиЬа
ц,ла ШиоЬхШ тожмд ШзжйлШвЬх Шзц лжд Sysop, у тожмд лЮд втеЮ Sysop, sysop,
СУСОП, СчйжзШк бвз йлЮд ЬзабЬнШвхЫШ лжмк.
[32m*[37m!)!)
!0l
!J[33mЖЖ/ЛЛ/ДД[37m  !10iДиЬмдШ ЩсйЬа ЮгЬижгЮдхШк. ЗШ ЩиЬЯжчд лШ ШиоЬхШ
зжм ЬхдШа дЬщлЬиШ Шзц лЮд ЮгЬижгЮдхШ зжм жихЭЬлЬ. Тж тлжк гзжиЬх дШ ЬхдШа
Ыапунаж у лЬлиШпунаж.!)
!0l
!J[33m-ЮгтиЬк[37m   !10iГщйлЬ "гЬхжд" бШа тдШд ШиаЯгц ЪаШ дШ псежмгЬ ЪаШ
ШиоЬхШ зжм ШзЬйлсвЮйШд йлЮд ШиоЬажЯубЮ лж зжвч зиад Шзц лцйЬк гтиЬк (зо
"[33m-10[37m" ЫЬходЬа лШ ШиоЬхШ зжм ШдтЩЮбШд йлЮд ШиоЬажЯубЮ лак лЬвЬмлШхЬк
10 гтиЬк).!)
!0l
[32m*[37m !JОа гжинтк тиЬмдШк зжм йЮгЬащдждлШа гЬ ШйлЬихйбж ЯШ ЬхдШа заж
ШиЪтк Шд оиЮйагжзжауйЬлЬ wildcards у regular expressions. Ж тиЬмдШ ЪаШ втеЬак
жзжмЫузжлЬ йлЮд ЬзабЬнШвхЫШ Ьдцк ШиоЬхжм ЬхдШа Ю заж ШиЪу Шз'цвЬк.!)
[0;1m} T Search for files, help


SRRXERR {[0;1;31m
!JТж regular expression "[33m%s[31m" ЫЬд улШд ШзжЫЬблц. Тж
йчйлЮгШ гШк ЬзтйлиЬпЬ лж Ьеук всЯжк: [37m%s[31m. ПШиШбШвщ еШдШЫжбагсйлЬ.!)
[0;1m} T Invalid regular expression


SRDTERR {[0;1;31m
!JЖ ЮгЬижгЮдхШ зжм ЫщйШлЬ ЫЬд улШд ШзжЫЬблу. Ж ШзжЫЬблу гжину ЪаШ ЮгЬижгЮдхЬк
ЬхдШа [37mЖЛДРА/ЛЖМАС/ДТОС[31m (зо 10/2/98).!)
[0;1m} T Search for files, invalid date specification


SRDMER1 {[0;1;31m
!JХг, гцвак тЪадЬ бсла бШбц бШа зжвч ШймдуЯайлж. НШдШЫжбагсйлЬ бШа Шд лж
зицЩвЮгШ ймдЬоайлЬх, ЬаЫжзжауйлЬ лж оЬаиайлу ймйлугШлжк.!)
[0;1m} T Search for files, search daemon exited before creating its file.


SRDMNONE {[0;1;31m
!JГЬд ЩитЯЮбЬ бШдтдШ ШиоЬхж. Ийрк псеШлЬ ЪаШ бсла мзЬиЩжвабс ймЪбЬбиагтдж у
Шзвс ШдчзШиблж. ГжбагсйлЬ еШдс.!)
[0;1m} T Search for files, no files found.


SRDMNM {[0;1;31m
!JФлсйШлЬ йлж лтвжк лрд ШзжлЬвЬйгслрд.!)
[0;1m} T Search for files, end of results list


SRTABW {[0;1;36m
Лайц вЬзлц зШиШбШвщ...
[0;1m} T Search for files, waiting for results


SRTABH {[0;1;32m
[33m## [32mОижк[37m, ШиоЬажЯубЮ бШа цджгШ ШиоЬхжм             ПЬиаЪиШну
[0;1m!F─
} T Search for files, table header


SRTABL {[0;1;33m%2d[37m [32m%s%s[37m%-*s %-28.28s
} T Search for files, table line


SRTABU { (гтоиа йлаЪгук)} T Daemon still working, page count not complete yet


SRTABF {[0;1m!F─
СЬвхЫШ: [32m%d[37m Шзц [32m%d%s[37m
[0;1m} T Search for files, table footer


SRMNU {[0;1m
!JГщйлЬ [33m1[37m-[33m%d[37m ЪаШ дШ всЩЬлЬ лж ШиоЬхж, у:!)
[[33mF[37m]orward  . . . . . ДзцгЬдЮ йЬвхЫШ   [[33mB[37m]ackward . . . ПижЮЪжчгЬдЮ йЬвхЫШ
[[33mP[37m]age jump . . . .  АвгШ йЬ йЬвхЫШ   [[33mN[37m]ew search  . . . . .  МтШ тиЬмдШ
[[33mI[37m]nfo . . . ПвЮижнжихЬк ЪаШ ШиоЬхж   e[[33mX[37m]it  . . . . . . . . . .  ДежЫжк

!JЖ ЬзавжЪу йШк ([33m?[37m ЪаШ ЩжуЯЬаШ);!) [0m} T Search for files, navigator menu


SRSMNU {[0;1m
!WЖ ЬзавжЪу йШк ([33m1[37m-[33m%d[37m,[33mF[37m,[33mB[37m,[33mP[37m,[33mN[37m,[33mI[37m,[33mX[37m ЪаШ тежЫж,
у [33m?[37m ЪаШ ЩжуЯЬаШ);!) [0m} T Search for files, navigator menu, short form


SRMNER {[0;1;31m
!JКмзсгШа, Шмлу Ю ЬзавжЪу ЫЬд ЬхдШа ЫмдШлу.!)
[0;1m} T Search for files, invalid selection for navigator menu


SRMNRN {[0;1;31m
!JКмзсгШа, Шмлу Ю ЬзавжЪу ЫЬд ЬхдШа ЫмдШлу. ГщйлЬ тдШд ШиаЯгц Шзц
[37m1[31m рк [37m%d[31m.!)
[0;1m} T Search for files, invalid file number selection


SRMNBG {[0;1;31m
!JФлсйШлЬ йлЮд Шиоу лрд ШзжлЬвЬйгслрд. ГЬд мзсиоЬа зижЮЪжчгЬдЮ йЬвхЫШ.!)
[0;1m} T Search for files, beginning of list


SRMNEN {[0;1;31m
!JФлсйШлЬ йлж лтвжк лрд ШзжлЬвЬйгслрд. ГЬд мзсиоЬа ЬзцгЬдЮ йЬвхЫШ.!)
[0;1m} T Search for files, end of list



SRMNHLP {[0;1m
!JДЫщ ЩвтзЬлЬ лШ ШзжлЬвтйгШлШ лЮк тиЬмдск йШк. ДоЬлЬ лак Ьеук
ЫмдШлцлЮлЬк:!)

!JГхдждлШк лжд ШиаЯгц лжм ШиоЬхжм зжм ЬгнШдхЭЬлШа йлЮд зищлЮ йлувЮ лжм
зхдШбШ гзжиЬхлЬ дШ всЩЬлЬ Шмлц лж ШиоЬхж. ГхдждлШк [33mI[37m бШа лжд
ШиаЯгц Ьдцк ШиоЬхжм ЩвтзЬлЬ Шзвщк лЮд звуиЮ ЬзабЬнШвхЫШ лжм ШиоЬхжм.!)

!JЛЬ лак Ьдлжвтк [33mF[37m бШа [33mB[37m гзжиЬхлЬ дШ бадЮЯЬхлЬ Ьгзицк
бШа зхйр йлжд бШлсвжЪж ШзжлЬвЬйгслрд. ЛЬ лЮд Ьдлжву [33mP[37m гзжиЬхлЬ дШ
гЬлШзЮЫуйЬлЬ йЬ цзжаШ йЬвхЫШ ЯтвЬлЬ, ЫхдждлШк лжд ШиаЯгц лЮк. Ттвжк, гЬ лЮд
Ьдлжву [33mN[37m гзжиЬхлЬ дШ ЫаЬесЪЬлЬ дтШ тиЬмдШ ЪаШ бсзжаж сввж ШиоЬхж у
биалуиаж.!)
[0;1m} Search for files, navigator help


SRMNJMA {[0;1m
!JСЬ зжаШ йЬвхЫШ ЯтвЬлЬ дШ бадЮЯжчгЬ; ([33m%d[37m-[33m%d[37m):!) [0m} T Search for files, jump to page


SRMNJMR {[0;1;31m
!JПШиШбШвщ ЫщйлЬ тдШд ШиаЯгц гЬлШеч [33m%d[31m бШа [33m%d[31m у [33mX[31m
ЪаШ гШлШхрйЮ лжм свгШлжк.!)
[0;1m} T Search for files, jump to page range error

 
SRMNINA {[0;1m
!JПжажм ШиоЬхжм лЮд ЬзабЬнШвхЫШ ЯтвЬлЬ дШ ЫЬхлЬ; ([33m%d[37m-[33m%d[37m):!) [0m} T Search for files, see file header


SRMNINR {[0;1;31m
!JПШиШбШвщ ЫщйлЬ тдШд ШиаЯгц гЬлШеч [33m%d[31m бШа [33m%d[31m у [33mX[31m
ЪаШ гШлШхрйЮ лжм свгШлжк.!)
[0;1m} T Search for files, file header range error



SRLIBJMP {[0;1;32m
!JЕЮлуйШлЬ вупЮ лжм ШиоЬхжм [37m%s[32m Шзц лЮд ШиоЬажЯубЮ
[37m%s[32m.!)
[0;1m} T Search for files, acknowledge request for download







FILINFO {[0;1;32m
ОМОЛА АРХДИОУ:  [36m%-26.26s [32mЛДВДЗОС:       [36m%s[32m
ХРОМОС КЖЦЖС:   [36m%-26.26s [32mХРДЧСЖ КЖЦЖС:  [36mПЬихзжм %d %s[32m
АПОСТОКДАС:     [36m%-26.26s [32mДВЙРИЗЖЙД АПО: [36m%s[32m
ДСТАКЖ:         [36m%s %s         [32mДКЖФЗЖ:        [36m%d %s[32m
ПДРИДХОЛДМА:    [36m!i!W%s!)[32m
!0lПДРИВРАФЖ:      [36m%s
[0;1m} T File information, first part (general information)


FILINSB {%d bytes} T File header, size in bytes
FILINSK {%d.%02d kbytes} T File header, size in kbytes
FILINSM {%d.%02d Mbytes} T File header, size in Mbytes

FILINTA {ПЬихзжм %d вЬзлс} T File header, 'approximately %d mins' (time estimation)
FILINTL {Йслр Шзц тдШ вЬзлц} T File header, 'less than %d mins' (time estimation)

MINSNG {вЬзлц} T Minutes, singular
MINPLR {вЬзлс} T Minutes, plural

CRDSNG {credit} T Credits, singular
CRDPLR {credits} T Credits, plural

TIMSNG {нжис} T Times, singular
TIMPLR {нжитк} T Times, plural


FILINFOK {[0;1;32mКДНДИС ЙКДИГИА: [36m!i!W%s!)[32m
!0l} T File Information, second part (keywords)


FILINFOD {[0;1;32m
КДПТОЛДРЖС ПДРИВРАФЖ:
[36m%s
[0;1m} T File Information, third part (long description)







DNLASK {[0;1m
!JГщйлЬ лж цджгШ лжм ШиоЬхжм у лрд ШиоЬхрд зжм ЯтвЬлЬ дШ всЩЬлЬ. ЛзжиЬхлЬ дШ оиЮйагжзжауйЬлЬ
wildcards (ЫщйлЬ [33m?[37m ЪаШ ЩжуЯЬаШ):!) [0m} T Download, ask for filename(s)


DNLNAX {[0;1;31m
!JТж ЬзхзЬЫж зицйЩШйук йШк ЫЬд йШк ЬзалитзЬа дШ всЩЬлЬ ШиоЬхШ Шзц
лЮд ШиоЬажЯубЮ [37m@LIB@[31m.!)
[0;1m} T Download, no access to library


DNLNF {[0;1;31m
!JТж ШиоЬхж "[37m%s[31m" ЫЬд ЩитЯЮбЬ йлЮд ШиоЬажЯубЮ @LIB@. НШдШЫжбагсйлЬ,
у ЫжбагсйлЬ лЮд Ьдлжву [33mF[31m Шзц лж бЬдлиабжч гЬджч лрд ШиоЬажЯЮбщд ЪаШ
дШ псеЬлЬ ЪаШ лж ШиоЬхж.!)
[0;1m} T Download, single file not found


DNLNFM {[0;1;31m
!JЖ ШиоЬажЯубЮ @LIB@ ЫЬд зЬиатоЬа бШдтдШ ШиоЬхж зжм дШ лШаиасЭЬа йлж
"[37m%s[31m". НШдШЫжбагсйлЬ, у ЫжбагсйлЬ лЮд Ьдлжву [33mF[31m Шзц
лж бЬдлиабжч гЬджч лрд ШиоЬажЯЮбщд ЪаШ дШ псеЬлЬ ЪаШ лШ ШиоЬхШ зжм йШк
ЬдЫаШнтижмд.!)
[0;1m} T Download, no files matching wildcard expression


DNLHLP {[0;1m
!JЛЬ Шмлу лЮд Ьдлжву гзжиЬхлЬ дШ всЩЬлЬ ШиоЬхШ Шзц лЮд литожмйШ ШиоЬажЯубЮ,
лЮд @LIB@. ГщйлЬ лж цджгШ лжм ШиоЬхжм зжм ЯтвЬлЬ дШ всЩЬлЬ. ЛзжиЬхлЬ дШ
оиЮйагжзжауйЬлЬ бШа unix wildcards ПШиШЫЬхЪгШлШ: лж "[33m*gif[37m" ЬзавтЪЬа
цвШ лШ ШиоЬхШ зжм лЬвЬащджмд йЬ "gif". Тж "[33mfile?.txt[37m" ЬзавтЪЬа
ШиоЬхШ цзрк file0.txt у fileA.txt. Тж "[33mAMD*[56]*[37m" лШаиасЭЬа йЬ
ШиоЬхШ цзрк лШ AMD_K5.pdf, AMD_K6.pdf, AMD5.doc, aMd_ab5cd, бвз. ТШ габис бШа
лШ бЬнШвШхШ ЪисггШлШ ЯЬрижчдлШа айжЫчдШгШ.!)
[0;1m} T Download, help on naming filenames


DNLWAIT {[0;1;32m
!JПШиШбШвщ зЬиагтдЬлЬ, ймввтЪжмгЬ лШ ШиоЬхШ зжм ЭЮлуйШлЬ...!)
[0;1m} T Download, wait for file collection


DNLSIH {[0;1m
ОджгШ ШиоЬхжм            ЛтЪЬЯжк  Хицджк  ХитрйЮ  ПЬиаЪиШну
!F─
[0;1;32m} T Download, list of matching files, header

DNLSIL {[0;1;32m%-23.23s %8d %4d:%02d %7d  %.28s
} T Download, list of matching files, table line

DNLSIF {[0;1m!F─
СчджвШ    АиоЬхШ: [32m%5d %8d %4d:%02d %7d  (зЬихзжм)
[0;1m} T Download, list of matching files, table line


DNLNCR {[0;1;31m
!JКмзсгШа, ЫЬд тоЬлЬ ШибЬлтк гждсЫЬк ЪаШ дШ зиШЪгШлжзжауйЬлЬ лЮ вупЮ.!)
[0;1m} T Download, can't pay for files


DNLFMS {[0;1;31m
!JТж ШиоЬхж [37m%s[31m лЮк ШиоЬажЯубЮк [37m@LIB@[31m вЬхзЬа, у ЬхдШа
бЬдц! ПШиШбШвщ ЬаЫжзжауйлЬ лжд оЬаиайлу ймйлугШлжк ЪаШ лж ЪЬЪждцк.!)
[0;1m} T Download, can't open file
