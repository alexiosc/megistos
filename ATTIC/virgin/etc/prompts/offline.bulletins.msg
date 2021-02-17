LEVEL2 {}

DEFBLT {Include Bulletin index packets by default? YES} B

DEFANSI {ANSI colours by default? YES} B

BLTIDFN {blt-list} S 12 Bulletin list file name, as used in QWK


LEVEL3 {}

OBVT {[0m[30;47m ┌─────────────────── [34mРмЯгхйЬак лжм АдШЪдрйлЮихжм АиЯирд[0;30;47m ───────────────────[0;1;37;47m┐ [0m
[30;47m │                                                                          [0;1;47;37m│ [0m
[30;47m │  ЙШлсвжЪжк сиЯирд йЬ бсЯЬ зШбтлж:        [0;30;46m [@"X "t] [0;47;30m       (Space ЪаШ ШввШЪу)  [0;1;47;37m│ [0m
[30;47m │                                                                          [0;1;47;37m│ [0m
[30;47m │  ANSI оищгШлШ йлжд бШлсвжЪж;             [0;30;46m [@"X "t] [0;47;30m       (Space ЪаШ ШввШЪу)  [0;1;47;37m│ [0m
[30;47m │                                                                          [0;1;47;37m│ [0m
[30;47m │                                                                          [0;1;47;37m│ [0m
[30;47m │  Ctrl-R: БжуЯЬаШ                 [0;1;42;33m@14;"OK"b[0;47;30m▄    [0;1;41;33m@14;"Абмиж"b[0;47;30m▄  [0;1;47;37m│ [0m
[30;47m │                                   ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀     ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀  [0;1;47;37m│ [0m
[30;47m └[0;1;37;47m──────────────────────────────────────────────────────────────────────────┘ [0m} T Setup, Visual template


OBLT {[2J[0;30;47m ┌─────────────────── [34mРмЯгхйЬак лжм АдШЪдрйлЮихжм АиЯирд[0;30;47m ───────────────────[0;1;37;47m┐ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ [31m1[30m. ЙШлсвжЪжк сиЯирд йЬ бсЯЬ зШбтлж . . . . . . . . . . . . . . . . [34m@"X "t[0;1;47;37m   │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ [31m2[30m. ANSI оищгШлШ йлжд бШлсвжЪж . . . . . . . . . . . . . . . . . .  [34m@"X "t[0;1;47;37m   │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m └[0;1;37;47m──────────────────────────────────────────────────────────────────────────┘ [0;1m
} T Setup QWK, Linear template


OBINDEX {[0;1m
!JДдЬиЪжзжащдлШк Шмлу лЮд ЬзавжЪу, ЭЮлслЬ лЮд ЬайШЪрЪу Ьдцк бШлШвцЪжм
лрд сиЯирд лЮк @BBS@ йЬ бсЯЬ зШбтлж йШк. АбцгШ бШа гЬ лЮд Ьдлжву ШзЬдЬиЪжзжаЮгтдЮ,
гзжиЬхлЬ дШ ЭЮлуйЬлЬ Шмлц лжд бШлсвжЪж цзжлЬ лжд ЯтвЬлЬ йлтвдждлШк тдШ off-line
гудмгШ зижк [33mMailer[37m гЬ лЮ втеЮ [33mBLT-LIST[37m йлж ЯтгШ лжм
гЮдчгШлжк.!)
[0;1m} T Setup QWK, Linear template, enable/disable bulletin index


OBANSI {[0;1m
!JДдЬиЪжзжащдлШк Шмлу лЮд ЬзавжЪу, имЯгхЭЬлЬ бШлс зцйжд ж бШлсвжЪжк
лрд сиЯирд ЯШ зЬиавШгЩсдЬа ANSI Ьдлжвтк ЪаШ оищгШлШ. Ад ж Off-line Reader
йШк ЫЬд мзжйлЮихЭЬа ANSI оищгШлШ цлШд ЫаШЩсЭЬа bulletins, ШзЬдЬиЪжзжауйлЬ
лЮд ЬзавжЪу Шмлу.!)
[0;1m} T Setup QWK, Linear template, ANSI colour in bulletin index


OBDL {[0;1m
АдШЪдрйлуиаж сиЯирд: } T Download, index


OBDLMK {[32mГЮгажмиЪЬхлШа бШлсвжЪжк сиЯирд.
[0;1m} T Download, making index


OBDLMT {[33mГЬд мзсиожмд сиЯиШ йлж ШдШЪдрйлуиаж
[0;1m} T Download, no articles found


OBDLPR {[0;1;36m
                                        ▄▄
                             ██████████ ██ ███████
                             ██      ██ ██      ██
                             ██      ██ ██      ██
                             ███████ ██ ██████████
                                     ▀▀               [37m
                                A C R O B A S E

                              АМАВМЧСТЖРИО АРЗРЧМ
[32m
                      ЙШлсвжЪжк сиЯирд лжм АдШЪдрйлЮихжм.


ГЮгажмиЪуЯЮбЬ йлак [37m%s[32m лЮд [37m%s[32m.

} T Bulletin index: preamble


OBDLFT {[0;1;32m

ВаШ дШ ЭЮлуйЬлЬ тдШ сиЯиж, йлЬхвлЬ тдШ бЬдц гудмгШ зижк [37mMailer[32m,
гЬ ЯтгШ [37mBLT-REQ club/name[32m, цзжм "club" ЬхдШа лж цджгШ лжм club
йлж жзжхж ЩихйбЬлШа лжж сиЯиж бШа "name" ЬхдШа лж цджгШ лжм сиЯижм, цзрк
ЬгнШдхЭЬлШа йлЮд ЫЬчлЬиЮ йлувЮ лжм зШиШзсдр зхдШбШ (зо, ЪаШ дШ ЭЮлуйЬлЬ
лж сиЯиж 42.blt Шзц лж club Acro, ЯШ ЪиспЬлЬ BLT-REQ Acro/42.blt).
ПижйтелЬ: лж йчйлЮгШ ЯЬриЬх лШ габис бШа бЬнШвШхШ ЪисггШлШ ЫаШнжиЬлабс
йлШ ждцгШлШ лрд ШиоЬхрд.
} T Bulletin list: footer, instructions on how to request bulletins


OBDLUB {[0;1;36mАхлЮйЮ сиЯижм [37m%s/%s[36m: [31mГЬд ЩитЯЮбЬ лж сиЯиж.
[0;1m} T Bulletins Download: Error in bulletin request, unknown bulletin


OBDLOK {[0;1;36mАхлЮйЮ сиЯижм [37m%s/%s[36m: [32mАдлаЪиснлЮбЬ рк [37m%s[32m.
[0;1m} T Bulletins Download: Bulletin request accepted


OBDLIO {[0;1;36mАхлЮйЮ сиЯижм [37m%s/%s[36m: [31mКсЯжк ЬЪЪиШнук/ШдсЪдрйЮк.
[0;1m} T Bulletins Download: I/O error while copying


OBDLCR {                                    ПРОСОХЖ

Тж зШицд сиЯиж вунЯЮбЬ Шзц лЮд @BBS@. ДзалитзЬлШа Ю ШдсЪдрйу лжм, Ьн'цйжд
Ю зШижчйШ зШиШлуиЮйЮ ЫЬд ШнШаиЬЯЬх. Тж сиЯиж ШзжлЬвЬх здЬмгШлабу аЫажблЮйхШ
лЮк @BBS@ йчгнрдШ гЬ лж бШлШйлШлабц/йчгЩШйЮ гЬ лж оиуйлЮ. (c) @BBS@

-------------------------------------------------------------------------------

[0m} T Bulletins Download: bulletin header / copyright notice






OBUPL {[0;1;32m
!JАалуйЬак зижк лж АдШЪдрйлуиаж:!)
!F─
[0;1m} T Bulletins upload: header


OBULIDOK {[0;1;36mBLT-LIST: [32mАхлЮйЮ бШлШвцЪжм сиЯирд ЫЬблу.
[0;1m} T Bulletins Upload: Bulletin list request ok


OBULIDNN {[0;1;36mBLT-LIST: [32mГЬд оиЬаШЭцлШд (зШхидЬлЬ бШлсвжЪж сиЯирд йЬ бсЯЬ зШбтлж).
[0;1m} T Bulletins Upload: Bulletin list request not needed


OBULRR {[0;1;36mBLT-REQ %s: [31mКсЯжк йчдлШеЮк.
[0;1m} T Bulletins Upload: Error in bulletin request


OBULUC {[0;1;36mBLT-REQ %s/%s: [31mГЬд ЩитЯЮбЬ лж club.
[0;1m} T Bulletins Upload: Error in bulletin request, unknown club


OBULUB {[0;1;36mBLT-REQ %s/%s: [31mГЬд ЩитЯЮбЬ лж сиЯиж.
[0;1m} T Bulletins Upload: Error in bulletin request, unknown bulletin


OBULOK {[0;1;36mBLT-REQ %s: [32mГЬблц.
[0;1m} T Bulletins Upload: Bulletin request accepted


OBULEND {[0;1;32m!F─
} T Bulletins Upload: end of upload
