LEVEL2 {}

DEFATT {Default action for inclusion of attachments? NO} E NO YES ASK

DEFREQ {Default action for requested files? YES} E NO YES ASK

DEFHDR {Include full headers for messages by default? YES} B

OMCEML {EMail} S 16 Area name for email

ALLNAM {ALL} S 25 Name for 'All' recipients

UPDQSC {Update last read quickscan pointers after packet download? YES} B

USEPASS {Use password field for storing longer message subjects? YES} B

FIXETA {If using GREEKQWK, translate lower case accented eta? YES} B

ETAXLT {Character to translate lower case accented eta to: n} C

PRGIND {Use progress indicator while building packets? YES} B



LEVEL3 {}

ADMNAM {Слтважк ХШгцЫиШбШк, Sysop} S 60 Sysop's name as stored in CONTROL.DAT


OMMENU {[2J[0m[47;1;37m ┌─────────────────────────────────────────────────────────────────────────[0;30;47m┐ [40m
[47;1;37m │  [0;47;30m           ПижлагуйЬак ЖвЬближдабжч лШомЫижгЬхжм бШа Clubs           [0;47;30m  │ [40m
[47;1;37m │  [0;47;30m─────────────────────────────────────────────────────────────────────  [0;47;30m│ [40m
[47;1;37m │                                                                         [0;47;30m│ [40m
[47;1;37m │  [0;31;47mC[30mlubs included in packet  . . .  Clubs зжм зЬиавШгЩсдждлШа йлж зШбтлж  [30m│ [40m
[47;1;37m │  [0;31;47mS[30metup preferences  . . . . . . . . . . . . . . .  РчЯгайЮ зижлагуйЬрд  [30m│ [40m
[47;1;37m │                                                                         [0;47;30m│ [40m
[47;1;37m │ [0;30;47me[31mX[30mit  . . . . . . . . . . . . . . . . . . . . . . . . . . . . . ДежЫжк  [30m│ [40m
[47;1;37m └[0;30;47m─────────────────────────────────────────────────────────────────────────┘ [0;1m

РчЯгайЮ зижлагуйЬрд ЖвЬближдабжч лШомЫижгЬхжм бШа Clubs
ПШиШбШвщ ЫщйлЬ лЮд ЬзавжЪу йШк: [0m} T Setup, menu footer


OMSHORT {[0;1m
!WГщйлЬ лЮд ЬзавжЪу йШк, [33mX[37m ЪаШ тежЫж у [33m?[37m ЪаШ лж гЬджч: [0m!)} T Setup, short menu


OMERR {[0;1;31m
!JКмзсгШа, ЫЬд мзсиоЬа Ю ЬзавжЪу "%c".!)
[0;1m} T Setup, wrong selection


OMVT {[0m[30;47m ┌──────────────── [34mРмЯгхйЬак ЫЮгажмиЪхШк зШбтлжм гЮдмгслрд[0;30;47m ─────────────────[0;1;37;47m┐ [0m
[30;47m │                                                                          [0;1;47;37m│ [0m
[30;47m │  СмдЮггтдШ ШиоЬхШ йлж зШбтлж;    [0;30;46m @16;"Ооа|МШа|ЙШлцзад ДищлЮйЮк"l [0;47;30m  (Space ЪаШ ШввШЪу)  [0;1;47;37m│ [0m
[30;47m │                                                                          [0;1;47;37m│ [0m
[30;47m │  ТШ ШиоЬхШ зжм тоЬлЬ ЭЮлуйЬа;    [0;30;46m @16;"Ооа|МШа|ЙШлцзад ДищлЮйЮк"l [0;47;30m  (Space ЪаШ ШввШЪу)  [0;1;47;37m│ [0m
[30;47m │                                                                          [0;1;47;37m│ [0m
[30;47m │  ПвуиЮк header йлШ гЮдчгШлШ;     [0;30;46m [@"X "t] [0;47;30m               (Space ЪаШ ШввШЪу)  [0;1;47;37m│ [0m
[30;47m │                                                                          [0;1;47;37m│ [0m
[30;47m │  Ctrl-O: БжуЯЬаШ ЪаШ зЬЫхж                                               [0;1;47;37m│ [0m
[30;47m │  Ctrl-R: БжуЯЬаШ ЪаШ звублиШ     [0;1;42;33m@14;"OK"b[0;47;30m▄    [0;1;41;33m@14;"Абмиж"b[0;47;30m▄  [0;1;47;37m│ [0m
[30;47m │                                   ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀     ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀  [0;1;47;37m│ [0m
[30;47m └[0;1;37;47m──────────────────────────────────────────────────────────────────────────┘ [0m} T Setup, Visual template


OMVTN {Ооа} T Setup, string for NO
OMVTY {МШа} T Setup, string for YES
OMVTA {ЙШлцзад ДищлЮйЮк} T Setup, string for ASK



OMLT {[2J[0;30;47m ┌──────────────── [34mРмЯгхйЬак ЫЮгажмиЪхШк зШбтлжм гЮдмгслрд[0;30;47m ─────────────────[0;1;37;47m┐ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ [31m1[30m. СмдЮггтдШ ШиоЬхШ йлж зШбтлж . . . . . . . . .  [34m@16;"Ооа|МШа|ЙШлцзад ДищлЮйЮк"l[0;1;47;37m       │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ [31m2[30m. ПицЪиШггШ ШзжймгзхЬйЮк . . . . . . . . . . . . [34m@16;"Ооа|МШа|ЙШлцзад ДищлЮйЮк"l[0;1;47;37m       │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ [31m3[30m. ПвуиЮк header йлШ гЮдчгШлШ  . . . . . . . . .  [34m@"X "t[0;1;47;37m                    │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m └[0;1;37;47m──────────────────────────────────────────────────────────────────────────┘ [0;1m
} T Setup QWK, Linear template


OMLTATT {[0;1m
!JЙсзжаШ Шзц лШ гЮдчгШлШ лжм ЖвЬближдабжч ТШомЫижгЬхжм бШа лрд Clubs тожмд
ймдЮггтдШ ШиоЬхШ, лШ жзжхШ лж йчйлЮгШ йШк зижлитзЬа дШ всЩЬлЬ цлШд ЬхйлЬ
on-line. Амлу Ю ЬзавжЪу йШк ЫхдЬа лЮд ЬмбШаихШ дШ ШзжнШйхйЬлЬ ла ЯШ бсдЬлЬ гЬ
лмоцд ймдЮггтдШ ШиоЬхШ. ЛзжижчгЬ дШ гЮд лШ ЬайсЪжмгЬ бШЯцвжм йлж зШбтлж йШк
(гзжиЬхлЬ ШиЪцлЬиШ дШ лШ ЭЮлуйЬлЬ Шзц лжд Mailer), у дШ ЬайсЪжмгЬ цвШ лШ ШиоЬхШ.
ЛзжиЬхлЬ ЬзхйЮк дШ ЭЮлуйЬлЬ Шзц лж йчйлЮгШ дШ йШк ирлуйЬа Шд ЯтвЬлЬ дШ
ЬайсЪЬлЬ бсЯЬ ШиоЬхж еЬориайлс, цлШд ЫЮгажмиЪЬхлЬ лж зШбтлж гЮдмгслрд йШк.!)

!JАд ЫЬд гзжиЬхлЬ дШ ШзжнШйхйЬлЬ, ЫщйлЬ "цоа" ЬЫщ. Амлц гЬащдЬа лжд цЪбж лрд
зШбтлрд йШк.!)
[0;1m} T Setup QWK, Linear template, set attachment policy


OMLTREQ {[0;1m
!JАмлу Ю ЬзавжЪу ЫжмвЬчЬа цзрк бШа Ю зижЮЪжчгЬдЮ, Шввс гзжиЬхлЬ дШ ЬвтЪеЬлЬ
лЮд ймгзЬианжис лжм Mailer зижк лШ ШиоЬхШ зжм тоЬлЬ ЭЮлуйЬа гтйр лжм off-line
reader йШк (зЬиаййцлЬиЬк звЮижнжихЬк ЪаШ лак ШалуйЬак ШиоЬхрд йлак жЫЮЪхЬк
оиуйЮк лжм Mailer).!)

!JАд ЫЬд гзжиЬхлЬ дШ ШзжнШйхйЬлЬ, ЫщйлЬ "дШа" ЬЫщ. ВЬдабс, цлШд ЭЮлслЬ тдШ
ШиоЬхж, ЯтвЬлЬ дШ лж всЩЬлЬ йлж ЬзцгЬдж зШбтлж йШк.!)
[0;1m} T Setup QWK, Linear template, set request policy


OMLTHDR {[0;1m
!JЖ ЬзабЬнШвхЫШ лрд гЮдмгслрд цзрк лЮд ЩвтзЬлЬ йлж ЖвЬближдабц ТШомЫижгЬхж
бШа лак ДаЫабтк ПЬиажотк зижйнтиЬа зжввтк звЮижнжихЬк жа жзжхЬк ЫЬд гзжижчд
дШ ШзжЯЮбЬмЯжчд йлЮд зжвч зЬиажиайгтдЮ ЬзабЬнШвхЫШ лрд QWK гЮдмгслрд.
ДдЬиЪжзжащдлШк Шмлу лЮд ЬзавжЪу, ж Mailer ЯШ лжзжЯЬлЬх лЮд звуиЮ ЬзабЬнШвхЫШ
бсЯЬ гЮдчгШлжк Шгтйрк зиад Шзц лж гудмгШ. Амлц ЯШ йШк ЬзалитзЬа дШ ЫЬхлЬ
лж звуиЬк ЯтгШ лЮк ймЭулЮйЮк (лж QWK зирлцбжвж бцЩЬа лШ ЯтгШлШ), лжд ШиаЯгц
ШзШдлуйЬрд, бвз.!)

!JАд ЫЬд гзжиЬхлЬ дШ ШзжнШйхйЬлЬ, ЬдЬиЪжзжауйлЬ лЮд ЬзавжЪу.!)
[0;1m} T Setup QWK, Linear template, full header inclusion


OMSOK {[0;1;32m
!JОа зижлагуйЬак йШк ШзжЯЮбЬчЯЮбШд Ьзалмощк.!)
[0;1m} T Setup QWK, changes stored successfully


OMSCAN {[0;1;31m
!JОа ШввШЪтк йШк гШлШащЯЮбШд.!)
[0;1m} T Setup QWK, changes aborted



OMCMNU {[0;1m
   [33mV[37miew  . . . ДгнсдайЮ лрд зЬиавШгЩШджгтдрд Club
   [33m+[37m  . . . . . . . . . . . .  ПижйЯтйлЬ тдШ Club
   [33m-[37m . . . . . . . . . . . . . АнШаитйлЬ тдШ Club
   [33mR[37meset  . . . . . . АввШЪу лЬвЬмлШхжм гЮдчгШлжк
   [33mF[37mrom quickscan  . . . .  Озрк бШа лж Quickscan
   [33mT[37mo quickscan . . . . . . . ДдЮгтирйЮ Quickscan
[0;1m} T Club config, menu


OMCMNUS {[0;1m
!WГщйлЬ лЮд ЬзавжЪу йШк ([33mV[37m,[33m+[37m,[33m-[37m,[33mR[37m,[33mF[37m,[33mT[37m,[33m?[37m ЪаШ ЩжуЯЬаШ, у [33mX[37m ЪаШ лтвжк:!)[0m } T Club config, short menu



OMCHLP {[0;1m
!JДЫщ гзжиЬхлЬ дШ жихйЬлЬ зжаШ clubs ЯШ зЬиавШгЩсдждлШа йлШ зШбтлШ гЮдмгслрд йШк.
Ад тоЬлЬ уЫЮ жихйЬа бсзжаШ clubs ЪаШ лж on-line Quickscan, лцлЬ етиЬлЬ уЫЮ
лЮд вЬалжмиЪхШ лЮк ЩсйЮк й'Шмлц лж йЮгЬхж.!)

!JАиоабс цвШ лШ Clubs зЬиавШгЩсдждлШа йлж зШбтлж йШк (бШа йлж quickscan лрд
clubs -- лЮд on-line ШдсЪдрйЮ, ЫЮвШЫу), Шввс гзжиЬхлЬ дШ
ШнШаитйЬлЬ тдШ ЫхдждлШк "[33m-/ОджгШClub[37m", у дШ зижйЯтйЬлЬ тдШ
ЫхдждлШк "[33m+/ОджгШClub[37m". ВаШ дШ ЫЬхлЬ тдШ бШлсвжЪж цврд лрд Clubs
гзжиЬхлЬ дШ ЫщйЬлЬ "[33m+?[37m". ВаШ дШ ймгзЬиавсЩЬлЬ цвШ лШ Clubs ЫщйлЬ
"[33m+ALL[37m" бШа ЪаШ дШ лШ ЫаШЪиспЬлЬ цвШ, "[33m-ALL[37m".
ВаШ дШ ЯЬриЮЯжчд цвШ лШ гЮдчгШлШ Ьдцк Club уЫЮ ЫаШЩШйгтдШ ЫщйлЬ
"[33m+/OджгШClub[37m" Ычж нжитк. ГЮвШЫу, Шд ЫщйЬлЬ "[33m+ALL +ALL[37m",
лж йчйлЮгШ ЯШ ЯЬриуйЬа цвШ лШ гЮдчгШлШ цврд лрд Clubs уЫЮ ЫаШЩШйгтдШ.
Длйа, лЮд ЬзцгЬдЮ нжис зжм ЯШ всЩЬлЬ зШбтлж, ЯШ ЫаШЩсйЬлЬ гцдж дтШ
гЮдчгШлШ.!)

!JТж йчйлЮгШ "ЯмгслШа" лж лЬвЬмлШхж гудмгШ бсЯЬ Club зжм тоЬлЬ всЩЬа йЬ зШбтлж QWK.
ЛзжиЬхлЬ дШ ШввсеЬлЬ лжд ШиаЯгц Шмлц гЬ лЮд Ьдлжву [33mR[37m. Амлу Ю ЫмдШлцлЮлШ мзсиоЬа
ЪаШ вцЪжмк ШиоЬажЯтлЮйЮк бШа ЪаШ дШ бШвчпЬа жиайгтдЬк ШймдуЯайлЬк ШдсЪбЬк. [31mПижйтелЬ[37m,
ШввсЭждлШк лжд ШиаЯгц Шмлц орихк дШ етиЬлЬ ла бсдЬлЬ гзжиЬх дШ ЫажЪбщйЬлЬ бШлс зжвч лж зШбтлж йШк,
у дШ осйЬлЬ гЮдчгШлШ зжм ЫЬд тоЬлЬ ШбцгЮ всЩЬа.!)

!JАд тоЬлЬ уЫЮ ЫаШгжинщйЬа тдШ йчджвж clubs йлж Quickscan, гзжиЬхлЬ дШ лж
ШдлвуйЬлЬ гЬ лЮд Ьдлжву [33mF[37m. Ж Ьдлжву Шмлу жихЭЬа цла лШ clubs зжм ЯШ
вШгЩсдЬлЬ йлШ зШбтлШ йШк ЯШ ЬхдШа хЫаШ гЬ Шмлс зжм ЬхоШлЬ йлж Quickscan йШк
цлШд ЫщйШлЬ лЮд Ьдлжву. ЛзжиЬхлЬ дШ бсдЬлЬ бШа лж ШдлхЯЬлж, дШ йлЬхвЬлЬ ЫЮвШЫу
лак ЬЫщ имЯгхйЬак йШк йлж Quickscan, гЬ лЮд Ьдлжву [33mT[33m.!)
[0;1m} T Club config, help


OMCHLP2 {[0;1m

!JЛаШ бШа Шмлу ЬхдШа Ю зищлЮ нжис зжм ЫаШгжинщдЬлЬ лж зШбтлж гЮдмгслрд йШк,
цвШ лШ clubs зЬиавШгЩсдждлШа ШмлцгШлШ Шзц лж йчйлЮгШ. Тж зищлж зШбтлж йШк ЯШ
зЬиатоЬа гцдж цйШ гЮдчгШлШ ЪиШнлжчд Шз'Шмлу лЮ йлаЪгу бШа гЬлс (гзжиЬх ЫЮвШЫу
бШа дШ гЮд зЬиатоЬа бШЯцвжм гЮдчгШлШ). ЛзжиЬхлЬ ЬвЬчЯЬиШ дШ ШввсеЬлЬ лШ
clubs зжм ЯШ зЬиавШгЩсдждлШа йлШ зШбтлШ йШк. ВаШ зЬиаййцлЬиЬк звЮижнжихЬк,
ЫщйлЬ [33m?[37m йлж зШиШбслр гЬджч.!)
[0;1m} T Club config, help for users who already have a quickscan setup



OMCLH {[0;1;32m
Оа Ьеук зЬиажотк гЮдмгслрд зЬиавШгЩсдждлШа йлШ зШбтлШ йШк:

[37mПЬиажоу            Слж Quickscan   ТЬвЬмлШхж гудмгШ
!F─
[0m} T Club config, club list header


OMCL {%-16s        %3s              %6d
} T Club config, club list line


OMCLYES {МШа} T Club config, club list, 'yes'
OMCLNO  {Ооа} T Club config, club list, 'no'


OMCLF {[0;1m!F─
} T Club config, club list footer


OMCADD {[0;1m
!WГщйлЬ Club зжм ЯШ ймгзЬиавсЩЬлЬ йлШ зШбтлШ йШк,
у [33mALL[37m ЪаШ цвШ ([33m?[37m ЪаШ бШлсвжЪж):!)[0m } T Club config, add club


OMCCR {[0;1;31m
!JГЬд мзсиоЬа Шмлц лж Club.!)
} T Club config, add, unknown club


OMCDEL {[0;1m
!WГщйлЬ Club зжм ЯШ ЬеШаитйЬлЬ Шзц лШ зШбтлШ гЮдмгслрд йШк, у
[33mALL[37m ЪаШ цвШ лШ clubs ([33m?[37m ЪаШ бШлсвжЪж):!)[0m } T Club config, delete club


OMCDR {[0;1;31m
!JГЬд мзсиоЬа лтлжаж Club йлжд бШлсвжЪж лрд ШдаодЬмжгтдрд Club.!)
} T Club config, delete, unknown club


OMCRES {[0;1m
!WГщйлЬ Club лжм жзжхжм ЯШ ШввсеЬлЬ лж лЬвЬмлШхж ЫаШЩШйгтдж гудмгШ,
[33mEMAIL[37m ЪаШ лж ЖвЬближдабц ТШомЫижгЬхж,
у [33mALL[37m ЪаШ цвШ лШ clubs ([33m?[37m ЪаШ бШлсвжЪж):!)[0m } T Club config, reset club


OMCRR {[0;1;31m
!JГЬд мзсиоЬа лтлжаж Club йлжд бШлсвжЪж лрд ШдаодЬмжгтдрд Club.!)
} T Club config, reset, unknown club


OMCRN {[0;1m
!JГщйлЬ лжд ШиаЯгц лжм лЬвЬмлШхжм гЮдчгШлжк зжм ЯШ ЯЬриЬхлШа ЫаШЩШйгтдж. Ад
ЫщйЬлЬ ШидЮлабц ШиаЯгц, ж ШиаЯгцк гЮдмгслрд лжм club зижйлхЯЬлШа йлжд ШиаЯгц
йШк. Длйа, Шд тдШ club тоЬа 100 гЮдчгШлШ бШа ЫщйЬлЬ -10, лж лЬвЬмлШхж гудмгШ
ЯШ ЬхдШа лж 90. Амлу ЬхдШа Ю [33mгцдЮ[37m йрйлу гтЯжЫжк ЪаШ дШ ШввсеЬлЬ лж
лЬвЬмлШхж ЫаШЩШйгтдж гудмгШ Шд гЬлШЩсввЬлЬ [33mцвШ[37m лШ clubs.!)

!WАиаЯгцк лЬвЬмлШхжм гЮдчгШлжк; ([33m%d[37m - [33m%d[37m, [33mX[37m ЪаШ тежЫж)!)[0m } T Club config, reset, asking for number


OMCRNR {[0;1;31m
!JАиаЯгцк Ьблцк жихрд.!)
[0;1m} T Club config, reset, number out of bounds


OMCFC {[0;1m
!JАмлу Ю Ьдлжву ЯШ гЬлШлитпЬа лЮд ЫаШгцинрйЮ лрд зШбтлжм гЮдмгслрд йШк йЬ ШдлхЪиШнж лЮк ЫаШгцинрйЮк ЪиуЪжиЮк
ШдходЬмйЮк. ГЮвШЫу, йлж зШбтлж йШк ЯШ зЬиавШгЩсдждлШа ШбиаЩщк лШ хЫаШ clubs зжм ЫаШЩсЭЬлЬ бШа йлж Quickscan,
бШа гЬ лжмк хЫажмк ШиаЯгжчк лЬвЬмлШхрд гЮдмгслрд.!)

!WМШ зижориуйжмгЬ; ([[33mY[37m]es=дШх / [[33mN[37m]o=цоа)!)[0m } T Club config, From Quickscan, confirm?


OMCFCR {[0;1;31m
!JПШиШбШвщ ШзШдлуйлЬ гЬ [33mY[31m у [33mN[31m.!)
[0;1m} T Club config, From Quickscan, invalid choice


OMCFOK {[0;1;32m
!JЙШвщк, йлж зШбтлж йШк ЯШ зЬиавШгЩсдждлШа звтжд ШбиаЩщк жа хЫаЬк зЬиажотк зжм зЬиавШгЩсдждлШа бШа
йлЮд ЪиуЪжиЮ ШдходЬмйЮ.!)
[0;1m} T Club config, From Quickscan, done


OMCFCAN {[0;1;31m
!JАбмищЯЮбЬ.!)
[0;1m} T Club config, From Quickscan, aborted


OMCTC {[0;1m
!JАмлу Ю Ьдлжву ЯШ гЬлШлитпЬа лЮд ЫаШгцинрйЮ лЮк ЪиуЪжиЮк ШдходЬмйЮк йЬ ШдлхЪиШнж лЮк ЫаШгцинрйЮк лжм
зШбтлжм гЮдмгслрд йШк. ГЮвШЫу, йлж Quickscan ЯШ ЫаШЩсЭЬлЬ ШбиаЩщк лШ хЫаШ clubs зжм вШгЩсдЬлЬ бШа йлШ зШбтлШ йШк,
бШа гЬ лжмк хЫажмк ШиаЯгжчк лЬвЬмлШхрд гЮдмгслрд.!)

!WМШ зижориуйжмгЬ; ([[33mY[37m]es=дШх / [[33mN[37m]o=цоа)!)[0m } T Club config, To Quickscan, confirm?


OMCTCR {[0;1;31m
!JПШиШбШвщ ШзШдлуйлЬ гЬ [33mY[31m у [33mN[31m.!)
[0;1m} T Club config, To Quickscan, invalid choice


OMCTOK {[0;1;32m
!JЙШвщк, йлЮд ЪиуЪжиЮ ШдходЬмйЮ ЯШ зЬиавШгЩсдждлШа звтжд ШбиаЩщк жа хЫаЬк зЬиажотк зжм зЬиавШгЩсдждлШа бШа
йлШ зШбтлШ гЮдмгслрд йШк.!)
[0;1m} T Club config, To Quickscan, done


OMCTCAN {[0;1;31m
!JАбмищЯЮбЬ.!)
[0;1m} T Club config, To Quickscan, aborted






OMDLHD {[0;1m                                                                 ЛЮдчгШлШ
Club             ПЬиаЪиШну                                  Смджвабс  ВаШ Ьйск
!F─
[0;1m} T Quickscan table: Header


OMDLEM {[0;1;32mE-Mail           ЖвЬближдабц ТШомЫижгЬхж                    [37m} T Quickscan table: Email line


OMDLT1 {[0;1;32m%-16.16s %-42.42s [37m} T Quickscan table: SIG name and description


OMDLIND0 {[s [0;30;40m[K[u} T Keyword scan, work indicator, begin

OMDLIND1 {[u[0m|[30m[K} T Keyword scan, work indicator, frame 1
OMDLIND2 {[u[0m/[30m[K} T Keyword scan, work indicator, frame 2
OMDLIND3 {[u[0m-[30m[K} T Keyword scan, work indicator, frame 3
OMDLIND4 {[u[0m\[30m[K} T Keyword scan, work indicator, frame 4
OMDLIND5 {[u[0m|[30m[K} T Keyword scan, work indicator, frame 5
OMDLIND6 {[u[0m/[30m[K} T Keyword scan, work indicator, frame 6
OMDLIND7 {[u[0m-[30m[K} T Keyword scan, work indicator, frame 7
OMDLIND8 {[u[0m\[30m[K} T Keyword scan, work indicator, frame 8

OMDLINDE {[u[0;1m[K} T Keyword scan, work indicator, end


OMDLT2 {[0;1;33m%7d   %7d
} T Quickscan table: Number of messages found in SIG


MSGSTOT {[0;1m
БитЯЮбШд ймджвабс:   [33m%4d[37m %s.
[0;1m} T Quickscan table: Total number of messages


MSGS4U {[0;1mВаШ Ьйск:            [33m%4d[37m %s.
[0;1m} T Quickscan table: Number of messages for you


MSGSAT {[0;1mЛЬ ймдЮггтдШ ШиоЬхШ: [33m%4d[37m %s.
[0;1m} T Quickscan table: Number of messages with attached files


MSGSNG {гудмгШ} S 'Message', singular
MSGPLR {гЮдчгШлШ} S 'Messages', plural


QWKCOPY {[0;1m[2J[0;1m
ДайШЪрЪу ШиоЬхрд йлж зШбтлж гЮдмгслрд йШк...
[0;1m} T Copying attached/requested files


QWKCPPPN {[0;1;32m
АиоЬхШ лрд жзжхрд Ю вупЮ ЬхоЬ ШдШЩвЮЯЬх:
[0;1m} T Dumping previously postponed files into your packet


QWKCPATT {[0;1;32m
АиоЬхШ ймдЮггтдШ йЬ дтШ гЮдчгШлШ:
[0;1m} T Dumping attached files into your packet


QWKCPREQ {[0;1;32m
СмдЮггтдШ ШиоЬхШ зжм тоЬлЬ ЭЮлуйЬа:
[0;1m} T Dumping requested files into your packet


QWKCPOTH {[0;1;32m
АввШ ШиоЬхШ:
[0;1m} T Dumping all other files into your packet


ATTLEFT {[0;1;33m
!WПижЬаЫжзжхЮйЮ: !iЕЮлуйШлЬ лЮд ЬайШЪрЪу бсзжажм ШиоЬхжм у ШиоЬхрд йлж
зШбтлж гЮдмгслрд йШк, Шввс тоЬлЬ жихйЬа цла лШ ШиоЬхШ Шмлс [37mЫЬд ЯШ ЬайсЪждлШа
зжлт[33m йлШ зШбтлШ йШк! ВаШ дШ всЩЬлЬ ц,ла ШиоЬхШ тожмд ЭЮлЮЯЬх йлж ЬзцгЬдж
зШбтлж йШк, зЮЪШхдЬлЬ йлак имЯгхйЬак бШа ШввселЬ лЮд ЬзавжЪу "АиоЬхШ зжм
тоЬлЬ ЭЮлуйЬа" йЬ "МШа" у "ЙШлцзад ЬищлЮйЮк".!)
!0l[0;1m} T Warning, requested files found but insertion of requests is off


QWKCPHD {[0;1;32m
ОджгШ         ПЬиажоу           ЛтЪЬЯжк
!F─
[0;1m} T File copy: Header


QWKCPTB {
[A[0;1m%-12s  %-16s  %7d  [s} T File copy: Filename, area, and size


QWKCPAC {[0;1m!W[u[KДайШЪрЪу; ([33mY[37m/[33mN[37m/[33mA[37m/[33mO[37m/[33mP[37m/[33mM[37m, [33m?[37m=ЩжуЯЬаШ)!) [0m} T File copy: Copy the file?


QWKCPER {[u} T File copy: bad choice in QWKCPAC menu


QWKASKH {[0;1m
!JТж йчйлЮгШ йШк ирлсЬа Шд ЯтвЬлЬ дШ ЬайсЪЬа лж зШиШзсдр ШиоЬхж йлж зШбтлж гЮдмгслрд йШк.
Амлц ймгЩШхдЬа ЪаШлх ЭЮлуйШлЬ ЬайШЪрЪу "ЙШлцзад ДищлЮйЮк" ЬхлЬ лрд ймдЮггтдрд йЬ гЮдчгШлШ
ШиоЬхрд, ЬхлЬ лрд ШиоЬхрд зжм тоЬлЬ ЭЮлуйЬа гтйр лжм off-line reader йШк.!)

!JЛзжиЬхлЬ дШ бсдЬлЬ лШ Ьеук:!)

!J!4l[[33mY[37m]es. МШа, ЬайШЪрЪу лжм ШиоЬхжм йлж зШбтлж.!)
!0l
!J!4l[[33mN[37m]o. Ооа, лж ШиоЬхж ЫЬд ЯШ ЬайШоЯЬх йлж зШбтлж бШа ЫЬд ЯШ
йШк еШдШзШижмйаШйлЬх Ьблцк ба Шд лж ЭЮлуйЬлЬ.!)
!0l
!J!4l[[33mA[37m]ll. ОвШ лШ ШиоЬхШ ЬайсЪждлШа йлж зШбтлж йШк орихк сввЬк
ЬирлуйЬак. (айжЫмдШгЬх гЬ зжввс [33mY[37m)!)
!0l
!J!4lN[[33mO[37m]ne. ЙШдтдШ ШиоЬхж ЫЬд ЬайсЪЬлШа йлж зШбтлж йШк орихк
сввЬк ЬирлуйЬак (айжЫмдШгЬх гЬ зжввс [33mN[37m).!)
!0l
!J!4l[[33mP[37m]ostpone. АдШЩжву вупЮк. Тж ШиоЬхж ЫЬд ЬайсЪЬлШа йлж зШбтлж,
Шввс ЯШ йШк еШдШзижлШЯЬх ЪаШ вупЮ йлж ЬзцгЬдж зШбтлж гЮдмгслрд.!)
!0l
!J!4l[[33mM[37m]essage. ЛудмгШ. ДгнШдхЭЬлШа Ю ЬзабЬнШвхЫШ лжм гЮдчгШлжк йлж жзжхж ЬхдШа
ймдЮггтдж лж ШиоЬхж. Амлц йШк ЬзалитзЬа дШ ЫЬхлЬ ла зЬихзжм ЬхдШа лж ШиоЬхж бШа дШ зисеЬлЬ ШдсвжЪШ.!)
!0l
[0;1m} T File copy: Help on deciding what to do with the file


QWKCPNF {[u[0;1;31m[KГЬд ЩитЯЮбЬ.
[0;1m} T File copy: Requested file not found


QWKCPAP {[u[0;1;31m[KГЬд тоЬа ЬЪбиаЯЬх ШбцгШ.
[0;1m} T File copy: Can't copy unapproved files


QWKCPNA {[u[0;1;31m[KГЬд йШк ЬзалитзЬлШа Ю вупЮ лжм.
[0;1m} T File copy: This file is not available to you


QWKCPCP {[u[0;1;5;33mАдлаЪиснЬлШа...[40;30m[K} T File copy: copying...


QWKCPIO {[u[0;1;31m[KКсЯжк бШлс лЮд ШдлаЪиШну!
[0;1m} T File copy: I/O error while copying


QWKCPOK {[u[0;1;32m[KАдлаЪиШну Ьзалмоук.
[0;1m} T File copy: Copied ok


QWKCPPO {[u[0;1;33m[KЖ вупЮ ШдШЩсввЬлШа.
[0;1m} T File copy: File skipped, request postponed


QWKCPCA {[u[0;1;33m[KЖ вупЮ гШлШащдЬлШа.
[0;1m} T File copy: File skipped, request cancelled


QWKCPHH {[0;1m
!JДзабЬнШвхЫШ лжм гЮдчгШлжк йлж жзжхж ЬхдШа ймдЮггтдж лж ШиоЬхж:!)
[0;1m} T File copy: File header preview, header


QWKCPHF {} T File copy: File header preview, footer


MSGHDR1 {
%s/%d  %s
ЖЛ/МИА: %-38.38s  %31.31s
АПО:    %-42.42s  %s
ПРОС:   %s%-48.48s  %21.21s
ЗДЛА:   %-54.54s  %15.15s
} T Message header, top part


MSGHDR2 {АРХДИО: %-52s  %17s
} T Message header, optional file attachment part


MSGHDR3 {───────────────────────────────────────────────────────────────────────────────

} T Message header, bottom part


MHFORU {} T Message header, message for you (clubs only)


MHALL {Овжмк} T Message header, string for 'All'


MHDAY0 {ЙмиаШбу} T Message header, string for Sunday
MHDAY1 {ГЬмлтиШ} T Message header, string for Monday
MHDAY2 {ТихлЮ} T Message header, string for Tuesday
MHDAY3 {ТЬлсилЮ} T Message header, string for Wednesday
MHDAY4 {ПтгзлЮ} T Message header, string for Thursday
MHDAY5 {ПШиШйбЬму} T Message header, string for Friday
MHDAY6 {СсЩЩШлж} T Message header, string for Saturday


MHJAN {ИШджмШихжм} T Message header, string for January
MHFEB {ФЬЩижмШихжм} T Message header, string for February
MHMAR {ЛШилхжм} T Message header, string for March
MHAPR {Азиавхжм} T Message header, string for April
MHMAY {ЛШфжм} T Message header, string for May
MHJUN {Ижмдхжм} T Message header, string for June
MHJUL {Ижмвхжм} T Message header, string for July
MHAUG {АмЪжчйлжм} T Message header, string for August
MHSEP {СЬзлЬгЩихжм} T Message header, string for September
MHOCT {ОблрЩихжм} T Message header, string for October
MHNOV {МжЬгЩихжм} T Message header, string for November
MHDEC {ГЬбЬгЩихжм} T Message header, string for December

MHPERIOD {ПЬиажЫабц, Шдс %d Югти%s} T Message header, string for 'periodic'

MHXMPT {ЛЮ ЫаШЪиспагж} T Message header, string for 'exempt'

MHRRR {ЕЮлуЯЮбЬ ШзцЫЬаеЮ ШдсЪдрйЮк} T Message header, string for 'return receipt requested'
        
MHTMRD {ГаШЩсйлЮбЬ %d нжи%s} T Message header, string for 'read x times'

MHNREP {%d %s} T Message header, string for 'x replies'

MHNDNL {ДвунЯЮ %d нжи%s} T Message header, string for 'downloaded x times'


TIMSNG {с} T 'Times', singular form
TIMPLR {тк} T 'Times', plural form

REPSNG {ШзсдлЮйЮ} T 'Reply', singular form
REPPLR {ШзШдлуйЬак} T 'Replies', plural form

DAYSNG {Ш} T Days, singular form
DAYPLR {Ьк} T Days, plural form


ATTNOT1 {
───────────────────────────────────────────────────────────────────────────────

Амлц лж гудмгШ тоЬа ймдЮггтдж ШиоЬхж гЬ цджгШ %s бШа гтЪЬЯжк
%d bytes.

Тж ШиоЬхж ГДМ зЬиавШгЩсдЬлШа йлж зШбтлж гЮдмгслрд йШк.
СлЬхвлЬ тдШ бЬдц гудЮгШ гЬ зШиШвузлЮ %s бШа ЯтгШ
REQUEST %s/%ld ЪаШ дШ лж всЩЬлЬ йлж ЬзцгЬдж зШбтлж йШк.
} T Message text: File attachment not included in your packet


ATTNOT2 {
───────────────────────────────────────────────────────────────────────────────

Амлц лж гудмгШ тоЬа ймдЮггтдж ШиоЬхж гЬ цджгШ %s бШа гтЪЬЯжк
%d bytes.
} T Message text: File attachment included in your packet


ATTNOT3 {
───────────────────────────────────────────────────────────────────────────────

Амлц лж гудмгШ тоЬа ймдЮггтдж ШиоЬхж гЬ цджгШ %s бШа гтЪЬЯжк
%d bytes.

Ад лж ШиоЬхж ЫЬд зЬиавШгЩсдЬлШа йлж зШбтлж гЮдмгслрд йШк,
йлЬхвлЬ тдШ бЬдц гудЮгШ гЬ зШиШвузлЮ %s бШа ЯтгШ
REQUEST %s/%ld ЪаШ дШ лж всЩЬлЬ йлж ЬзцгЬдж зШбтлж йШк.
} T Message text: File attachment optionally included


ATTNOT4 {
───────────────────────────────────────────────────────────────────────────────

Амлц лж гудмгШ тоЬа ймдЮггтдж ШиоЬхж гЬ цджгШ %s бШа гтЪЬЯжк
%d bytes, Шввс лж ЬзхзЬЫж зицйЩШйук йШк йЬ Шмлц лж club ЫЬд
йШк ЬзалитзЬа дШ лж всЩЬлЬ.
} T Message text: File attachment not available to you


ATTNOT5 {
───────────────────────────────────────────────────────────────────────────────

Амлц лж гудмгШ тоЬа ймдЮггтдж ШиоЬхж гЬ цджгШ %s бШа гтЪЬЯжк
%d bytes, Шввс ж жиЪШдрлук лжм club ЫЬд лж тоЬа ШбцгШ ЬЪбихдЬа.
} T Message text: File attachment not approved


ATTNOT6 {
───────────────────────────────────────────────────────────────────────────────

Амлц лж  гудмгШ ЬхоЬ  тдШ ймдЮггтдж  ШиоЬхж, Шввс  лж ШиоЬхж  ЫЬд
ЩитЯЮбЬ йлж club. ПШиШбШвжчгЬ ЬаЫжзжауйлЬ лжд ХЬаиайлу СмйлугШлжк
ЪаШ лж ЪЬЪждцк.
} T Message text: File not found or couldn't be opened


RRRINJ {[0;1m***

!JТж гтвжк [32m%s[37m гцвак зЬиатвШЩЬ лж гЮдмгс йШк
йЬ зШбтлж QWK бШа ЫЮгажмиЪуЯЮбЬ ШзцЫЬаеЮ зШиШвШЩук.!)
} T Return Receipt notification for receipt recipient



NOMSGS {[0;1;31m
!JТж зШбтлж ЫЬд нШхдЬлШа дШ зЬиатоЬа ШиоЬхШ ШзШдлуйЬрд (.MSG).
ФмйажвжЪабс, тдШ зШбтлж ШзШдлуйЬрд зитзЬа дШ зЬиатоЬа тдШ ШиоЬхж
гЬ цджгШ [37m%s.MSG[31m у [37m%s.MSG[31m (гЬ габис у бЬнШвШхШ ЪисггШлШ).!)
[0;1m} T Unable to find a .MSG file in the reply packet


BADID {[0;1;31m
!JТж зШбтлж ШзШдлуйЬщд йШк зижжихЭЬлШа ЪаШ ЩсйЮ гЬ лжд брЫабц "[37m%s[31m".
ТШ зШбтлШ лЮк @BBS@ зитзЬа дШ ЬхдШа йниШЪайгтдШ гЬ лжд брЫабц
"[37m%s[31m". ГЬд гзжижчгЬ дШ ЫЬолжчгЬ Шмлц лж зШбтлж.!)
[0;1m} T Reply packet is stamped with the wrong BBS ID.


REPHD {[0;1;32m
Пижк       Club             ЙШлсйлШйЮ
!F─
} T Reply table: Header


REPTB {[0;1m%-10.10s %-16.16s } T Reply table: Recipient and SIG


REPTBALL {Овжмк} T Reply table: string for 'All'


REPTBIN {[31mЛЮ ЬдЬиЪц (ЫаШЪЬЪиШггтдж;) гудмгШ.
[0;1m} T Reply table: message is inactive (erased?)


REPTBNR {[31mГЬд тоЬа жиайлЬх зШиШвузлЮк.
[0;1m} T Reply table: no recipient specified


REPTBUU {[31mАЪдрйлжк зШиШвузлЮк "%s".
[0;1m} T Reply table: unknown recipient


REPTBMF {[31mЙШбжйоЮгШлайгтдж гудмгШ!
[0;1m} T Reply table: malformed message


REPTBOK {[32mАзжЯЮбЬчЯЮбЬ.
[0;1m} T Reply table: Message saved


REPTBAS {[33mАзжЯЮбЬчЯЮбЬ, гЬ цджгШ ШзжйлжвтШ "%s".
[0;1m} T Reply table: Saved, sender user-ID corrected


REPTBRR {[32mАзжЯЮбЬчЯЮбЬ бШа ЭЮлуЯЮбЬ ШзцЫЬаеЮ зШиШвШЩук.
[0;1m} T Reply table: Saved, return receipt requested


REPTBUS {[31mАЪдрйлж club (хйрк дШ йЩуйлЮбЬ зицйнШлШ).
[0;1m} T Reply table: Unknown SIG number


REPTB2B {[31mТж гудмгШ ЬхдШа гЬЪШвчлЬиж Шзц %d bytes.
[0;1m} T Reply table: Message too big


REPTBAG {[31mДоЬлЬ еШдШйлЬхвЬа Шмлц лж гудмгШ.
[0;1m} T Reply table: This message has already been uploaded


REPTBAE {[31mЛудмгШ зижк цвжмк йлж E-Mail.
[0;1m} T Reply table: E-Mail message to ALL


REPTBES {[31mПижйрзабц гудмгШ йЬ club.
[0;1m} T Reply table: Recipient-only message in a SIG


REPTBPR {[31mГЮгцйаж гудмгШ гЬ ШхлЮйЮ ШзцЫЬаеЮк зШиШвШЩук.
[0;1m} T Reply table: Public message with return receipt


REPTBCR {[31mГЬд тоЬлЬ ШибЬлс credits.
[0;1m} T Reply table: Not enough credits to save


REPTBNA {[31mТж ЬзхзЬЫж ШйнШвЬхШк йШк ЫЬд лж ЬзалитзЬа.
[0;1m} T Reply table: Club security restriction


REPTBCN {[33mАбмищЯЮбЬ.
[0;1m} T Reply table: Message cancelled


DIRADD {[36mADD %s: } T Reply table: ADD directive


DIRDROP {[36mDROP %s: } T Reply table: DROP directive


DIRRESET {[36mRESET %s: } T Reply table: RESET directive


DIRRQST {[36mREQUEST %s: } T Reply table: REQUEST directive


DIRDONE {[32mГЬблц.
[0;1m} T Reply table: Directive processed


DIRFOR {[36m%s: [32mЗШ лж ЬзЬеЬиЪШйлжчгЬ йЬ вхЪж.
[0;1m} T Reply table: Directive is foreign, will be processed in a bit


DIRERR1 {[31mКсЯжк йлЮд Ьдлжву.
[0;1m} T Reply table: Error in directive


DIRERR2 {[31mКсЯжк ЬЪЪиШнук/ШдсЪдрйЮк
[0;1m} T Reply table: I/O Error in directive


DIRRQUS {[31mАЪдрйлж club.
[0;1m} T Reply table: REQUEST/ADD/DROP, unknown club


DIRCANT {[31mГЬд ЬзалитзЬлШа.
[0;1m} T Reply table: Can't manipulate E-Mail


DIRCNTR {[31mПитзЬа дШ тоЬа зижЮЪЮЯЬх ADD.
[0;1m} T Reply table: Must ADD before RESETting


DIRNFND {[31mГЬд ЩитЯЮбЬ Ю ЬзайчдШпЮ.
[0;1m} T Reply table: REQUESTed attachment not found


DIRNNEED {[33mГЬд оиЬаШЭцлШд.
[0;1m} T Reply table: No need to do that


NOCFMSG {[31mГЬд гзжищ дШ ЬзЬеЬиЪШйлщ гЮдчгШлШ "CONFIG".
[0;1m} T Reply table: Can't process CONFIG messages


ENDUL {[0;1;32m!F─
%d[37m Шзц [32m%d[37m %s ШзжЯЮбЬчЯЮбШд Ьзалмощк.
[0;1m} T Reply table: Footer


ASKCLUB {[0;1m
!JПШиШбШвщ ЫщйлЬ лж цджгШ лжм club йлж жзжхж дШ зижрЯуйжмгЬ
лж гудмгс йШк, у [33mEmail[37m ЪаШ дШ лж йлЬхвжмгЬ йлж ЖвЬближдабц
ТШомЫижгЬхж (зижк Ьйск Шд ЬхдШа зижк цвжмк), у [33mX[37m ЪаШ ШбчирйЮ лжм
гЮдчгШлжк:[0m!) } T Re-enter club name


ASKCLBR {[0;1;31m
!JСмЪЪдщгЮ, ЫЬд мзсиоЬа Шмлц лж club. НШдШЫжбагсйлЬ.!)
[0;1m} T Unknown club name


ASKERCP {[0;1m
!JПШиШбШвщ ЫщйлЬ лж цджгШ лжм зШиШвузлЮ,
у [33mX[37m ЪаШ гШлШхрйЮ Шзжйлжвук гЮдчгШлжк:[0m!) } T Re-enter ID of unknown E-Mail message recipient


ASKSRCP {[0;1m
!JПШиШбШвщ ЫщйлЬ лж цджгШ лжм зШиШвузлЮ,
[33mALL[37m ЪаШ Шзжйлжву гЮдчгШлжк йЬ ОКОУС,
у [33mX[37m ЪаШ ШбчирйЮ гЮдчгШлжк:[0m!) } T Re-enter ID of unknown SIG message recipient


UNKUSR {[0;1;31m
!JАмлц лж пЬмЫщдмгж ЫЬд мзсиоЬа йлЮд ЩсйЮ. ПШиШбШвщ еШдШзижйзШЯуйлЬ...!)
[0;1m} T Unknown user ID, please re-enter


EMLALL {[0;1;31m
КмзсгШа, Шввс ЫЬд гзжиЬхлЬ дШ йлЬхвЬлЬ гудмгШ ЖвЬближдабжч ТШомЫижгЬхжм
зижк цвжмк.
[0;1m} T Can't supply "ALL" as E-Mail recipient


ASKEORS {[0;1m
!JГЬд гзжиЬхлЬ дШ тоЬлЬ зижйрзабц гудмгШ гтйШ йЬ тдШ club. ЗтвЬлЬ:!)

[[33mE[37m]mail:  дШ зижрЯЮЯЬх йлж ЖвЬближдабц ТШомЫижгЬхж,
[[33mP[37m]ublic: дШ ЪхдЬа ЫЮгцйаж бШа дШ зШиШгЬхдЬа йлж club, у
[[33mC[37m]ancel: дШ ШбмирЯЬх;

!JПШиШбШвщ ЫщйлЬ тдШ ЪисггШ ([33mE[37m,[33mP[37m,[33mC[37m):!) [0m} T E-Mail message in a SIG: Make it private or public?


ASKRORS {[0;1m
!JГЬд гзжиЬхлЬ дШ всЩЬлЬ ШзцЫЬаеЮ зШиШвШЩук ЪаШ ЫЮгцйаж гудмгШ. ЗтвЬлЬ:!)

[[33mE[37m]mail:  дШ зижрЯЮЯЬх лж гудмгШ йлж ЖвЬближдабц ТШомЫижгЬхж,
[[33mP[37m]ublic: дШ гЬхдЬа ЫЮгцйаж бШа дШ ШбмирЯЬх Ю ШхлЮйЮ ШзцЫЬаеЮк, у
[[33mC[37m]ancel дШ ШбмирЯЬх;

!JПШиШбШвщ ЫщйлЬ тдШ ЪисггШ ([33mE[37m,[33mP[37m,[33mC[37m):!) [0m} T Public return receipt: Make it private or cancel?


ASKDUPL {[0;1m

!JДоЬлЬ еШдШйлЬхвЬа Шмлц лж гудмгШ йлЮ ЩсйЮ. АзШдлуйлЬ бШлШнШлабс йлЮд
зШиШбслр ЬищлЮйЮ Шд лж гудмгШ тоЬа йЩЮйлЬх Шзц лЮ ЩсйЮ бШа ЯтвЬлЬ дШ лж
еШдШйлЬхвЬлЬ.!)

!WЗтвЬлЬ дШ ЫЬолжчгЬ лж гудмгШ жчлрк у свврк; ([[33mY[31m]es=дШх / [[33mN[31m]o=цоа) [0m!)} T Duplicate message; accept it anyway?


ASKDUPD {[Enter=[33mN[37m][0m } T ASKDUPL default answer


ASKERR {[0;1;31m
!JКмзсгШа, ЫЬд мзсиоЬа Шмлу Ю ЬзавжЪу.!)
[0;1m} T Unknown option error for ASKxxxx menus


SIGINJ {[0;1m***

!JТж гтвжк [32m%s[37m гцвак йШк тйлЬавЬ гудмгШ гЬ ЯтгШ "[32m%s[37m"
йлж club [32/%s[37m гтйр лжм Off-line Mailer.
ЛзжиЬхлЬ дШ лж ЫаШЩсйЬлЬ ЫхдждлШк Шзц лж бЬдлиабц гЬджч:!)

([33mE[37m)mail = ЮвЬближдабц лШомЫижгЬхж
([33mR[37m)ead  = ШдсЪдрйЮ
([33mT[37m)o    = зицк Ьйск

!J'H ЪиснждлШк [33m/GO ERT[37m Шзц жзжмЫузжлЬ йлЮд ЩсйЮ.!)
[0;1m} T Injected: You just got a SIG message through the Mailer


EMLINJ {[0;1m***

!JТж гтвжк [32m%s[37m гцвак йШк тйлЬавЬ гудмгШ гЬ ЯтгШ "[32m%s[37m"
йлж ЖвЬближдабц ТШомЫижгЬхж гтйр лжм Off-line Mailer.
ЛзжиЬхлЬ дШ лж ЫаШЩсйЬлЬ ЫхдждлШк Шзц лж бЬдлиабц гЬджч:!)

([33mE[37m)mail = ЮвЬближдабц лШомЫижгЬхж
([33mR[37m)ead  = ШдсЪдрйЮ
([33mT[37m)o    = зицк Ьйск

!J'H ЪиснждлШк [33m/GO ERT[37m Шзц жзжмЫузжлЬ йлЮд ЩсйЮ.!)
[0;1m} T Injected: You just got an E-Mail message through the Mailer


RQMUNS {[0;1;31m
!JОа зШиШбслр ЬаЫабтк ШалуйЬак ЫЬд ШдШЪдрихйлЮбШд:!)
[0;1;32m
Пижк       Club             ЙШлсйлШйЮ
!F─
[0;1m} T The following requests were not satisfied


RQMTAB {[0;1m%-10.10s %-16.16s [36m%s: [31mЖ Ьдлжву ЫЬд ШдШЪдрихйлЮбЬ.
[0;1m} T Unsatisfied request table row


ENDRQM {[0;1;32m!F─
[0;1m} T End of unsatisfied request table
