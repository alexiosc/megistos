LEVEL2 {}

DEFWALL {Download the graffiti wall by default? YES} B

DEFANSI {Enable ANSI directives by default? YES} B

DEFLINS {How many lines to include by default? (0=all) 0} N 0 10000

WALLFIL {blt-wall} S 12 Filename of graffiti file


LEVEL3 {}

OGVT {[0m[30;47m ┌──────────────────── [34mРмЯгхйЬак лжм Тжхожм ЪаШ Виспагж[0;30;47m ────────────────────[0;1;37;47m┐ [0m
[30;47m │                                                                          [0;1;47;37m│ [0m
[30;47m │  О лжхожк ЪаШ Ъиспагж йлШ зШбтлШ:        [0;30;46m [@"X "t] [0;47;30m       (Space ЪаШ ШввШЪу)  [0;1;47;37m│ [0m
[30;47m │                                                                          [0;1;47;37m│ [0m
[30;47m │  ANSI оищгШлШ йлжд лжхож:                [0;30;46m [@"X "t] [0;47;30m       (Space ЪаШ ШввШЪу)  [0;1;47;37m│ [0m
[30;47m │                                                                          [0;1;47;37m│ [0m
[30;47m │  ЛтЪайлжк ШиаЯгцк ЪиШггщд:               [1;37;44m@5;0;10000;0n[0;47;30m     (0..10000, 0=цвЬк)  [0;1;47;37m│ [0m
[30;47m │                                                                          [0;1;47;37m│ [0m
[30;47m │                                                                          [0;1;47;37m│ [0m
[30;47m │  Ctrl-R: БжуЯЬаШ                 [0;1;42;33m@14;"OK"b[0;47;30m▄    [0;1;41;33m@14;"Абмиж"b[0;47;30m▄  [0;1;47;37m│ [0m
[30;47m │                                   ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀     ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀  [0;1;47;37m│ [0m
[30;47m └[0;1;37;47m──────────────────────────────────────────────────────────────────────────┘ [0m} T Setup, Visual template


OGLT {[2J[0;30;47m ┌─────────────────── [34mРмЯгхйЬак лжм Тжхожм ЪаШ Виспагж[0;30;47m ─────────────────────[0;1;37;47m┐ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ [31m1[30m. О лжхожк ЪаШ Ъиспагж йлШ зШбтлШ . . . . . . . . . . . . . . . . [34m@"X "t[0;1;47;37m   │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ [31m2[30m. ANSI оищгШлШ йлжд лжхож  . . . . . . . . . . . . . . . . . . .  [34m@"X "t[0;1;47;37m   │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │ [31m3[30m. ЛтЪайлжк ШиаЯгцк ЪиШггщд  . . . . . . . . . . . . . . . . . . . [34m@5;0;10000;0n[0;1;47;37m │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m └[0;1;37;47m──────────────────────────────────────────────────────────────────────────┘ [0;1m
} T Setup QWK, Linear template


OGWALL {[0;1m
!JДдЬиЪжзжащдлШк Шмлу лЮд ЬзавжЪу, ЭЮлслЬ лЮд ЬайШЪрЪу лжм Тжхожм ЪаШ
Виспагж йлШ зШбтлШ йШк.!)
[0;1m} T Setup QWK, Linear template, enable/disable wall


OGANSI {[0;1m
!JАмлу Ю ЬзавжЪу ЬвтЪоЬа Шд ЯШ вШгЩШдЬлЬ лжд лжхож ЪаШ Ъиспагж гЬ у орихк
ANSI оищгШ. Ад ж Off-line Reader йШк гзжиЬх дШ ЫЬхеЬа "bulletins" гЬ оищгШ,
лцлЬ ЬдЬиЪжзжауйлЬ лЮд ЬзавжЪу ANSI.!)
[0;1m} T Setup QWK, Linear template, enable/disable ANSI colour


OGLINES {[0;1m
!JДЫщ имЯгхЭЬлЬ зцйЬк ЪиШггтк лжм Тжхожм ЯШ ШдлаЪиснждлШа йлж зШбтлж йШк.
ЛзжиЬхлЬ дШ ЫщйЬлЬ тдШд ШиаЯгц жзц 0 гтоиа 10.000 (ймдуЯрк ж Тжхожк тоЬа
зжвч ваЪцлЬиЬк ЪиШггтк). Ад ЫщйЬлЬ 0, цвЬк жа ЪиШггтк ЯШ гЬлШнтиждлШа
йлж зШбтлж йШк.!)
[0;1m} T Setup QWK, Linear template, number of lines


DLHDR {[0;1m
[0;1;35mТ[36mж[33mх[32mо[31mж[34mк[37m ЪаШ Ъиспагж: } T Graffiti Wall Download: header


DLDMT {[0;1;33mО лжхожк ЬхдШа ниЬйбжЩШггтджк бШа сЫЬажк.
[0;1m} T Graffiti Wall Download: Empty wall


DLNAX {[0;1;31mГЬд тоЬлЬ зицйЩШйЮ йлжд лжхож.
[0;1m} T Graffiti Wall Download: no access


DLOK {[0;1;32mДдлсеЬа.
[0;1m} T Graffiti Wall Download: ok


ULWRH {[0;1m
[0;1;35mТ[36mж[33mх[32mо[31mж[34mк[37m ЪаШ Ъиспагж: } T Graffiti Wall Upload: Command header


ULWMT {[1;31mГЬд ЩитЯЮбШд ЪиШггтк ЪаШ Ъиспагж.
[0;1m} T Graffiti Wall Upload: No lines found


ULWRT {[1;32m%s Ьзалмощк бШа жа %d ЪиШгг%s.
[0;1m} T Graffiti Wall Upload: Written all lines


ULNWR {[1;33m%s %d Шзц %d ЪиШгг%s.
[0;1m} T Reply table: Written some lines


WRTSNG {ВиснлЮбЬ} T 'Written', singular form
WRTPLR {ВиснлЮбШд} T 'Written', plural form

LINSNG {у} T 'Lines', singular form
LINPLR {тк} T 'Lines', plural form



