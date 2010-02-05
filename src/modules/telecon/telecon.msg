LEVEL2 {}


ENTRKEY {Key required to access the teleconferences: 0} N 0 129

NORMKEY {Key required for live access: 2} N 0 129

SOPKEY {Key required for privileged access: 8} N 0 129

CHTKEY {Key required to participate in a one-on-one chat: 0} N 0 129

ICHTKEY {Key required to initiate a chat: 2} N 0 129

MSGKEY {Key required to change entry/exit messages: 2} N 0 129

ACTKEY {Key required to use action verbs: 0} N 0 129




 To limit jabber from non-live users, and from new users,
 set this option to restrict the amount of teleconference
 "statements" that can be made by a non-live user.  After
 such a user makes this many statements in the
 teleconference, he is "muted" until he logs off and logs
 back on again.

 Make this number 0 to prohibit ANY statements from non-live
 users at all.  (So that they will be allowed to listen, but
 listen only).

NPAYMX {Max times non-live users can speak per session (-1=no limit): -1} N -1 32767


 Switching channels in the teleconference can be
 particularly annoying to users on those channels because
 everyone is informed whenever somebody comes into and out
 of their channel.  The feature controlled by this option
 diminishes the effects of these conference "door-slammers".

 Most respectable users will stay on each channel for at
 least enough time to hear what is being said, so this
 feature should not bother them -- but you can adjust it if
 it does.  Set this number to 9999 to disable the feature.

MAXCHT {Number of channel changes per 15 seconds: 3} N 1 32767


 All teleconference "statements" will be limited in length
 by this option.  When users type this many characters, they
 will not be able to type any more, until they hit their
 Carriage Return key.


TINPSZ {Maximum length of a teleconference message (characters) 2047} N 1 2047


AMSGCH {Audit charges for entry/exit message changes? NO} B


MSGCHG {Charge for modifying entry/exit messages: 5} N -32767 32767


DEFCOL {Default colour for new users: WHITE} E DARKBLUE DARKGREEN DARKCYAN DARKRED DARKMAGENTA BROWN GREY DARKGREY BLUE GREEN CYAN RED MAGENTA YELLOW WHITE


DEFINT {Default interval between chat requests (minutes): 1} N 0 999


DEFACT {Actions enabled by default: YES} B


CHATCOL1 {Fallback colour #1 for chats: GREEN} E DARKBLUE DARKGREEN DARKCYAN DARKRED DARKMAGENTA BROWN GREY DARKGREY BLUE GREEN CYAN RED MAGENTA YELLOW WHITE


CHATCOL2 {Fallback colour #2 for chats: YELLOW} E DARKBLUE DARKGREEN DARKCYAN DARKRED DARKMAGENTA BROWN GREY DARKGREY BLUE GREEN CYAN RED MAGENTA YELLOW WHITE


LEVEL3 {}

 This message greets every user when they enter the
 teleconference.

INTRO {[2J[0;1;5;33;41mТЮвЬймджгавхЬк лЮк @BBS@[0;1m[K

[0;1m} T Welcome Message


DENIED {[0;1;31m
!JСмЪЪдщгЮ, лж ЬзхзЬЫж зицйЩШйук йШк ЫЬд йШк ЬзалитзЬа лЮд ЬхйжЫж йлак лЮвЬймджгавхЬк.!)
[0;1m} T Non-live access denied


ENTRBCH {[0;1;31m
!JТж бШдсва йлж жзжхж ЩиайбцйШйлЬ зижЮЪжмгтдрк ЫЬд мзсиоЬа звтжд.
СШк гЬлШнтижмгЬ йлж бЬдлиабц бШдсва.!)
[0;1m} T Previous channel does not exist, returning to MAIN


NOTALK {[0;1;31m
!JСмЪЪдщгЮ, зижбЬагтджм дШ ЬвШоайлжзжауйжмгЬ лЮд заЯШду бШлсоиЮйЮ лжм ймйлугШлжк
Шзц бШбцЩжмвжмк, ЫЬд гзжиЬхлЬ дШ гавуйЬлЬ йлак лЮвЬймджгавхЬк. Ад ЪхдЬлЬ ба
ЬйЬхк ймдЫижгЮлук, Шмлц лж зицЩвЮгШ ЯШ ЬбвЬхпЬа.!)
[0;1m} T Non-live users can't talk at all


NLVTALK {[0;1;33m
!JПижбЬагтджм дШ ЬвШоайлжзжауйжмгЬ лЮд заЯШду бШлсоиЮйЮ лжм ймйлугШлжк
Шзц бШбцЩжмвжмк, гзжиЬхлЬ дШ гавуйЬлЬ гтоиа [37m%d нжи%s[33m. Ад ЪхдЬлЬ
ба ЬйЬхк ймдЫижгЮлук, Шмлц лж зицЩвЮгШ ЯШ ЬбвЬхпЬа.!)
[0;1m} T Non-live users can speak N times


TIMSNG {с} T Times, singular form
TIMPLR {тк} T Times, plural form


NLVNAX {[0;1;31m
!JЕЮлжчгЬ ймЪЪдщгЮ, Шввс ЫЬд гзжиЬхлЬ дШ гавуйЬлЬ сввж йлак
лЮвЬймджгавхЬк Шмлу лЮ нжис. СШк ЯмгхЭжмгЬ цла жа ймдЫижгЮлтк гШк
тожмд звуиЮ ЬвЬмЯЬихШ йлж йчйлЮгШ.!)
[0;1m} T Non-live user can't talk any more


ASKHLP {[0;1m!JГщйлЬ [33m?[37m Шд оиЬасЭЬйлЬ ЩжуЯЬаШ...!)
[0;1m} T How to get help


LEAVE {[0;1m
!JДежЫжк Шзц лак ТЮвЬймджгавхЬк.!)
[0;1m} T Leaving the teleconference module


PROMPT1 {[0;1m:[0;%sm} T Teleconference prompt

PROMPT2 {[0;1m*[0;%sm} T Teleconference prompt, readonly access

PROMPT3 {[0;1;5m%d[0;1m:[0;%sm} T Teleconference prompt, countdown to read-only access


MAINTOPIC {} S 59 Main channel topic (optional)


SICHYPR {[0;1;35m
!JБихйбЬйлЬ йлж зижйрзабц йШк бШдсва.!)
[0;1m} T Show info, you are in your own private channel


SICHPRO {[0;1;35m
!JБихйбЬйлЬ йлж бШдсва %s [33m%s[35m.!)
[0;1m} T Show info, you are in someone else's private channel

OFMALE {лжм} T Of, male version

OFFEM {лЮк} T Of, female version


SICHMAIN {[0;1;35m
!JБихйбЬйлЬ йлж бЬдлиабц бШдсва.!)
[0;1m} T Teleconference you are in the main channel


SICHCLUB {[0;1;35m
!JБихйбЬйлЬ йлж бШдсва лжм club [33m%s[35m.!)
[0;1m} T Show info, you are in a club channel


SICHTMP {[0;1;35m
!JБихйбЬйлЬ йлж бШдсва [33m%s[35m.!)
[0;1m} T Show info, you are in a temporary channel


SITOPIC {[0;1;35m!JЗтгШ бШдШважч: "[33m%s[35m"!)
[0;1m} T Show info, channel topic


SIU0 {[0;1;31m!JГЬд мзсиоЬа бШдЬхк сввжк йЬ Шмлц лж бШдсва Шмлу лЮ йлаЪгу.!)
[0;1m} T Show info, no other users in channel


SIU1 {[0;1m!J%s [33m%s[37m ЬхдШа йЬ Шмлц лж бШдсва гШЭх йШк.!)
[0;1m} T Show info, one other user in channel


SEXM1 {О} T Male article (start of sentence), if applicable
SEXF1 {Ж} T Female article (start of sentence), if applicable

SEXM2 {ж} T Male article (middle of sentence), if applicable
SEXF2 {Ю} T Female article (middle of sentence), if applicable


SIUN1 {[0;1m!J%s [33m%s[37m} T Show info, N users here, first one


SIUN2 {, %s [33m%s[37m} T Show info, N users here, i-th one


SIUN3 { бШа %s [33m%s[37m ЬхдШа йЬ Шмлц лж бШдсва гШЭх йШк.!)
[0;1m} T Show info, N users here, last one


TDELIM {[0;1m■■■
} T Teleconference line delimiter


TFROM {!W[0;%smАзц %s: %s!)
[0;1m} T Teleconference, public message from user


TFROMP {!W[0;%smАзц %s (зижйрзабц): %s!)
[0;1m} T Teleconference, private message from user


TFROMT {!W[0;%smАзц %s (зицк %s): %s!)
[0;1m} T Teleconference, public message from user to other user


TFROM2U {!W[0;%smАзц %s (зицк Ьйск): %s!)
[0;1m} T Teleconference, public message from a user to you


TSENT {[0;1;32m!W--- ЛЬлШЫцЯЮбЬ ---!)
[0;1m} T Teleconference, message sent


TSENTP {[0;1;32m!W--- ЛЬлШЫцЯЮбЬ гцдж зижк %s ---!)
[0;1m} T Teleconference, private message sent 


TSENTT {[0;1;32m!W--- ЛЬлШЫцЯЮбЬ ЫЮгцйаШ зижк %s ---!)
[0;1m} T Teleconference, public message sent to user


TWHYU {[0;1;31m
!JГЬд гзжиЬхлЬ дШ ШзЬмЯчдЬлЬ лж вцЪж йлжд ЬШмлц йШк!!)
[0;1m} T can't send public message to self


ENTEXTS {!J[0;%sm%s!)
[0;1m} T Entry/exit string template


ENTTLC {!J[0;1;36m%s [33m%s[36m гцвак гзубЬ йЬ Шмлц лж бШдсва.!)
[0;1m} T A user just entered this channel


LFTTLC {!J[0;1;36m%s [33m%s[36m гцвак тнмЪЬ Шзц лак лЮвЬймджгавхЬк.!)
[0;1m} T A user just left the telefonference module


LFTCHN {!J[0;1;36m%s [33m%s[36m гцвак зуЪЬ йЬ бсзжаж сввж бШдсва.!)
[0;1m} T A user just went to another channel


ENTCHN {!J[0;1;36m%s [33m%s[36m гцвак уиЯЬ Шзц бсзжаж сввж бШдсва.!)
[0;1m} T A user just came from another channel


INVIS {[0;1;31m
!JГЬд гзжиЬхлЬ дШ лж бсдЬлЬ Шмлц цйж ЬхйлЬ ШциШлжк.!)
[0;1m} T Can't do that while invisible


TLCHELP {[0;1m!JСлак лЮвЬймджгавхЬк, ц,ла ЪиснЬлЬ лж ЫаШЩсЭжмд цвжа цйжа ЬхдШа йлж хЫаж
бШдсва гЬ Ьйск. ЛзжиЬхлЬ дШ оиЮйагжзжауйЬлЬ гЬиабтк ЬаЫабтк Ьдлжвтк цзрк:!)

!0l/<пЬмЫщдмгж> <бЬхгЬдж>   !i!WАзжйлжву гЮдчгШлжк йЬ тдШ гцдж гтвжк.!)
!0l\<пЬмЫщдмгж> <бЬхгЬдж>   !i!WАзжйлжву ЫЮгцйажм гЮдчгШлжк зижк бсзжаж гтвжк.!)
!0l><пЬмЫщдмгж> <бЬхгЬдж>   !i!WТж хЫаж.!)
!0lCHAT <пЬмЫщдмгж>         !i!WПицйбвЮйЮ у ШзжЫжоу зижйрзабук ймджгавхШк гЬ тдШ сввж гтвжк.!)
!0l/S у /SCAN               !i!WЙШлсвжЪжк оиЮйлщд йлак лЮвЬймджгавхЬк.!)
!0lEDIT                     !i!WАввШЪу лрд зижйрзабщд йШк зШиШгтлирд.!)
!0l/J <пЬмЫщдмгж>           !i!WПЮЪШхдЬлЬ йлж бШдсва лжм оиуйлЮ. Ж Ьдлжву
[33m/J[37m ЬхдШа айжЫчдШгЮ гЬ лЮд Ьдлжву [33mJOIN[37m.!)
!0l/J у JOIN                !i!WЛзШхдЬлЬ у ЩЪШхдЬлЬ Шзц лж зижйрзабц йШк бШдсва.!)
!0lINVITE <пЬмЫщдмгж>       !i!WПицйбвЮйЮ оиуйлЮ дШ тиЯЬа йлж зижйрзабц йШк бШдсва!)
!0lUNINVITE <пЬмЫщдмгж>     !i!WАийЮ лЮк зШиШзсдр зицйбвЮйЮк (ЫЬд гзжиЬх дШ твЯЬа)!)
!0l(UN)INVITE ALL           !i!WОзрк лШ зШиШзсдр Шввс ЪаШ цвжмк лжмк оиуйлЬк!)
!0lTOPIC <ЯтгШ>             !i!WОиайгцк ЯтгШлжк ймджгавхШк!)
!0lACTION ON/OFF/LIST/?     !i!WДдЬиЪжзжхЮйЮ/АзЬдЬиЪжзжхЮйЮ лрд иЮгслрд у ЩжуЯЬаШ!)
!0lFORGET <пЬмЫщдмгж>       !i!WАЪдцЮйЮ Ьдцк ЬджовЮлабжч оиуйлЮ!)
!0lREMEMBER <пЬмЫщдмгж>     !i!WАдШаиЬхлЬ лЮд зШиШзсдр ЬзавжЪу йШк!)
!0lTINGO/POKER/BJ HELP      !i!WПвЮижнжихЬк ЪаШ лШ Tingo, Poker, & Blackjack!)
!0lX                        !i!WДежЫжк Шзц лак лЮвЬймджгавхЬк!)
!0l[0;1m
} T Help on teleconference commands


HLPWHIS {[0;1m
!JЖ йчдлШеЮ лЮк Ьдлжвук WHISPER ЬхдШа:!)

[33mWHISPER TO <ЦЬмЫщдмгж> <бЬхгЬдж>   [37m  у
[33m/ <ЦЬмЫщдмгж> <бЬхгЬдж>[37m

!JГхдждлШк Шмлу лЮд Ьдлжву, лж гудмгс йШк ЯШ ШзжйлШвЬх зижйрзабс йлжд
оиуйлЮ лжм жзжхжм лж пЬмЫщдмгж тоЬлЬ ЫщйЬа, Ьнцйжд Шмлцк ЬхдШа йлж хЫаж
бШдсва гЬ Ьйск.!)

!JСЮгЬащйлЬ цла ЫЬд ЬхдШа ШдсЪбЮ дШ ЫщйЬлЬ лж звуиЬк пЬмЫщдмгж Ьдцк оиуйлЮ:
Шибжчд лШ зищлШ ЪисггШлс лжм. ВаШ зШисЫЬаЪгШ, лж пЬмЫщдмгж "sys" ШдШнтиЬлШа
йлжд Sysop. Ад мзсиожмд сдр лжм Ьдцк пЬмЫрдчгжм зжм еЬбаджчд гЬ "sys", лцлЬ
лж йчйлЮгШ ЯШ йШк ирлуйЬа зжаж ЬдджжчйШлЬ.!)
[0;1m} T Help on whispering


HLPSAY {[0;1m
!JЖ йчдлШеЮ лЮк Ьдлжвук SAY ЬхдШа:!)

[33mSAY TO <ЦЬмЫщдмгж> <бЬхгЬдж>   [37m  у
[33m\ <ЦЬмЫщдмгж> <бЬхгЬдж>

!JГхдждлШк Шмлу лЮд Ьдлжву, лж гудмгс йШк ЯШ ШзжйлШвЬх ЫЮгцйаШ зижк лжд
оиуйлЮ лжм жзжхжм лж пЬмЫщдмгж тоЬлЬ ЫщйЬа, Ьнцйжд Шмлцк ЬхдШа йлж хЫаж
бШдсва гЬ Ьйск. Ж Ьдлжву SAY оиЮйагЬчЬа ЪаШ дШ ШзжлЬхдЬлЬ лжд вцЪж йЬ
бсзжажд ймЪбЬбиагтдж ймджгавЮлу йШк.!)

!JСЮгЬащйлЬ цла ЫЬд ЬхдШа ШдсЪбЮ дШ ЫщйЬлЬ лж звуиЬк пЬмЫщдмгж Ьдцк оиуйлЮ:
Шибжчд лШ зищлШ ЪисггШлс лжм. ВаШ зШисЫЬаЪгШ, лж пЬмЫщдмгж "sys" ШдШнтиЬлШа
йлжд Sysop. Ад мзсиожмд сдр лжм Ьдцк пЬмЫрдчгжм зжм еЬбаджчд гЬ "sys", лцлЬ
лж йчйлЮгШ ЯШ йШк ирлуйЬа зжаж ЬдджжчйШлЬ.!)
[0;1m} T Help on saying something to a user


UIDNINT {[0;1;31m
!JКмзсгШа, Шмлц лж гтвжк ЫЬд ЩихйбЬлШа лщиШ йлак лЮвЬймджгавхЬк.!)
[0;1m} T User does not exist or is not in teleconferences


UIDNINC {[0;1;31m
!JКмзсгШа, Шмлц лж гтвжк ЫЬд ЩихйбЬлШа йлж бШдсва.!)

[0;1m} T User does not exist or is not in current channel





ENTEDIT {!J[0;1;36m%s [33m%s[36m гзубЬ йлж гЬджч зижйрзабщд зижлагуйЬрд.!)
[0;1m} T A user just entered the preferences menu


UEDITVT {[0;30;47m ┌───────────────────────── [34mПижйрзабтк зижлагуйЬак[0;30;47m ─────────────────────────[0;1;37;47m┐ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │  АввШЪу бЬагтджм ЬайцЫжм/ЬецЫжм: 10 гждсЫЬк Шдс бЬхгЬдж.                 [0;1;47;37m│ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │  ЙЬхгЬдж ЬайцЫжм  . . . . . .  [1;44;37m@79;38;0s[0;1;47m  │ [0m
[30;47m │  ЙЬхгЬдж ЬецЫжм  . . . . . . . [1;44;37m@79;38;0s[0;1;47m  │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │  Аиоабц ЯтгШ бШдШважч . . . .  [1;44;37m@63;38;0s[0;1;47m  │ [0m
[30;47m │  Аиоабу бШлсйлШйЮ бШдШважч . . [0;30;46m @16;"ЙвЬайлц йЬ цвжмк|Аджаолц йЬ цвжмк|Лцдж ЪаШ ЯЬШлтк"l [0;30;47m    (space ЪаШ ШввШЪу)  [0;1;47m│ [0m
[30;47m │  Аиоабц бШдсва  . . . . . . .  [0;30;46m @16;"ЙЬдлиабц бШдсва|Пижйрзабц бШдсва"l [0;30;47m    (space ЪаШ ШввШЪу)  [0;1;47m│ [0m
[30;47m │  Хицджк гЬлШеч chat requests . [1;37;44m@3;0;999;0n[0;47;30m                      (0-999 вЬзлс)  [0;1;47m│ [0m
[30;47m │  ДаЫабс иугШлШ ЬдЬиЪс . . . .  [0;30;46m [@"X "t] [0;47;30m                 (space ЪаШ ШввШЪу)  [0;1;47m│ [0m
[30;47m │                                                                          [0;1;47;37m│ [0m
[30;47m │  Тж оищгШ йШк  . . . . . . . . [0;30;46m @18;"Сбжчиж гзвЬ (1)|Сбжчиж зисйадж (2)|Сбжчиж ЪШвсЭаж (3)|Сбжчиж бцббадж (4)|Сбжчиж грЩ (5)|ЙШнт (6)|ВбихЭж (7)|Сбжчиж ВбихЭж (8)|ЛзвЬ (9)|Писйадж (10)|ВШвсЭаж (11)|Йцббадж (12)|ЛрЩ (13)|Йхлиадж (14)|Айзиж (15)"l [0;30;47m  (space ЪаШ ШввШЪу)  [0;1;47m│ [0m
[30;47m │     [0;37;40m▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀[1;47m      │ [0m
[30;47m │     [0;34;40m   01  [32m02  [36m03  [31m04  [35m05  [33m06  [37m07  [1;30m08  [34m09  [32m10  [36m11  [31m12  [35m13  [33m14  [37m15  [47m      │ [0m
[30;47m │     [0;37;40m▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄[1;47m      │ [0m
[30;47m │  Ctrl-R ЪаШ ЩжуЯЬаШ              [0;1;42;33m@14;"OK"b[0;47;30m▄    [0;1;41;33m@14;"Cancel"b[0;47;30m▄  [0;1;47;37m│ [0m
[30;47m │                                   ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀     ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀  [0;1;47;37m│ [0m
[30;47m └[0;1;37;47m──────────────────────────────────────────────────────────────────────────┘ [0m} T Preference edit visual template


CHANST1 {ЙвЬайлц йЬ цвжмк} T Channel status 1, closed to all
CHANST2 {Аджаолц йЬ цвжмк} T Channel status 2, open to all
CHANST3 {Лцдж ЪаШ ЯЬШлтк} T Channel status 3, read-only

DEFCHAN1 {ЙЬдлиабц бШдсва} T Default channel 1, main
DEFCHAN2 {Пижйрзабц бШдсва} T Default channel 2, private

COLOUR1 {Сбжчиж гзвЬ (1)} T Colour 1, dark blue
COLOUR2 {Сбжчиж зисйадж (2)} T Colour 2, dark green
COLOUR3 {Сбжчиж ЪШвсЭаж (3)} T Colour 3, dark cyan
COLOUR4 {Сбжчиж бцббадж (4)} T Colour 4, dark red
COLOUR5 {Сбжчиж грЩ (5)} T Colour 5, dark magenta
COLOUR6 {ЙШнт (6)} T Colour 6, brown
COLOUR7 {ВбихЭж (7)} T Colour 7, gray
COLOUR8 {Сбжчиж ВбихЭж (8)} T Colour 8, dark gray
COLOUR9 {ЛзвЬ (9)} T Colour 9, blue
COLOUR10 {Писйадж (10)} T Colour 10, green
COLOUR11 {ВШвсЭаж (11)} T Colour 11, cyan
COLOUR12 {Йцббадж (12)} T Colour 12, red
COLOUR13 {ЛрЩ (13)} T Colour 13, magenta
COLOUR14 {Йхлиадж (14)} T Colour 14, yellow
COLOUR15 {Айзиж (15)} T Colour 15, white



UEDITLT {[2J[0;30;47m ┌───────────────────────── [34mПижйрзабтк зижлагуйЬак[0;30;47m ─────────────────────────[0;1;37;47m┐ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │  АввШЪу бЬагтджм ЬайцЫжм/ЬецЫжм: 10 гждсЫЬк Шдс бЬхгЬдж.                 [0;1;47;37m│ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │  [31m1[30m. ЙЬхгЬдж ЬайцЫжм  . . . . . .  [34m@79;38;0s[0;1;47m │ [0m
[30;47m │  [31m2[30m. ЙЬхгЬдж ЬецЫжм  . . . . . . . [34m@79;38;0s[0;1;47m │ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │  [31m3[30m. Аиоабц ЯтгШ бШдШважч . . . .  [34m@63;38;0s[0;1;47m │ [0m
[30;47m │  [31m4[30m. Аиоабу бШлсйлШйЮ бШдШважч . . [34m@16;"ЙвЬайлц йЬ цвжмк|Аджаолц йЬ цвжмк|Лцдж ЪаШ ЯЬШлтк"l                       [0;1;47m│ [0m
[30;47m │  [31m5[30m. Аиоабц бШдсва  . . . . . . .  [34m@16;"ЙЬдлиабц бШдсва|Пижйрзабц бШдсва"l                       [0;1;47m│ [0m
[30;47m │  [31m6[30m. Хицджк гЬлШеч chat requests . [34m@3;0;999;0n вЬзлс                              [0;1;47m│ [0m
[30;47m │  [31m7[30m. ДаЫабс иугШлШ ЬдЬиЪс . . . .  [34m@"X "t                                    [0;1;47m│ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m │  [31m8[30m. Тж оищгШ йШк  . . . . . . . . [34m@18;"Сбжчиж гзвЬ (1)|Сбжчиж зисйадж (2)|Сбжчиж ЪШвсЭаж (3)|Сбжчиж бцббадж (4)|Сбжчиж грЩ (5)|ЙШнт (6)|ВбихЭж (7)|Сбжчиж ВбихЭж (8)|ЛзвЬ (9)|Писйадж (10)|ВШвсЭаж (11)|Йцббадж (12)|ЛрЩ (13)|Йхлиадж (14)|Айзиж (15)"l[34m                     [0;1;47m│ [0m
[30;47m │                                                                          [1;37m│ [0m
[30;47m └[0;1;37;47m──────────────────────────────────────────────────────────────────────────┘ [0;1m
} T Preference edit linear template


UEDITLT1 {[0;1m
!JГщйлЬ лж дтж йШк бЬхгЬдж ЬайцЫжм.
Тж бЬхгЬдж ЬайцЫжм ЬгнШдхЭЬлШа гЬ лж оищгШ йШк Шдлх ЪаШ лЮд ймдЮЯайгтдЮ ШдШбжхдрйЮ ЬайцЫжм.
Ж ШввШЪу лжм гЮдчгШлжк ЬайцЫжм бжйлхЭЬа 10 гждсЫЬк.
ЗШ оиЬрЯЬхлЬ ЪаШ лЮд ШввШЪу гЬ лЮд тежЫц йШк Шзц лЮд зЬиажоу зижйрзабщд зижлагуйЬрд.!)
[0;1m} T Preference edit, field 1


UEDITLT2 {[0;1m
!JГщйлЬ лж дтж йШк бЬхгЬдж ЬецЫжм.
Тж бЬхгЬдж ЬецЫжм ЬгнШдхЭЬлШа гЬ лж оищгШ йШк Шдлх ЪаШ лЮд ймдЮЯайгтдЮ ШдШбжхдрйЮ ЬецЫжм.
Ж ШввШЪу лжм гЮдчгШлжк ЬецЫжм бжйлхЭЬа 10 гждсЫЬк.
ЗШ оиЬрЯЬхлЬ ЪаШ лЮд ШввШЪу гЬ лЮд тежЫц йШк Шзц лЮд зЬиажоу зижйрзабщд зижлагуйЬрд.!)
[0;1m} T Preference edit, field 2


UEDITLT3 {[0;1m
!JГщйлЬ лж дтж йШк Шиоабц ЯтгШ бШдШважч.
Тж ЯтгШ Шмлц ЯШ ЬхдШа лж ЯтгШ лжм зижйрзабжч йШк бШдШважч Шгтйрк гцвак ймдЫЬЯЬхлЬ йлЮд @BBS@.
ЛзжиЬхлЬ нмйабс дШ лж ШввсеЬлЬ Шдс зсйШ йлаЪгу. Амлу Ю ичЯгайЮ Шзвщк ЬвтЪоЬа лж Шиоабц ЯтгШ.!)
[0;1m} T Preference edit, field 3


UEDITLT4 {[0;1m
!JДЫщ жихЭЬлЬ лЮд Шиоабу бШлсйлШйЮ лжм зижйрзабжч йШк бШдШважч йШк.
ЛзжиЬхлЬ дШ бсдЬлЬ лж бШдсва йШк зижйЩсйагж Шзц цвжмк лжмк оиуйлЬк (Шдлхйлжаож лЮк Ьдлжвук [33minvite all[37m).
ЛзжиЬхлЬ ЬзхйЮк дШ бвЬхйЬлЬ йЬ цвжмк лж бШдсва йШк (цзрк гЬ лЮд Ьдлжву [33muninvite all[37m).
Ттвжк, гзжиЬхлЬ дШ бсдЬлЬ лж бШдсва йШк "read-only": жа оиуйлЬк зжм гзШхджмд гтйШ ЫЬд ЯШ гзжижчд дШ гавуйжмд,
гтоиа дШ лжмк ЫщйЬлЬ лж ЫабШхргШ гЬ лЮд Ьдлжву [33munsquelch[37m. Амлц ЬхдШа оиуйагж ЪаШ ЬзхйЮгЬк ймджгавхЬк у
сввЬк ЬбЫЮвщйЬак цзжм мзсиоЬа ШбижШлуиаж. Амлу Ю ичЯгайЮ ЬзЮиЬсЭЬа гцдж лЮд Шиоабу бШлсйлШйЮ лжм бШдШважч йШк.
ЛзжиЬхлЬ дШ ШввсеЬлЬ лЮд бШлсйлШйу лжм Шдс зсйШ йлаЪгу гЬ лак ШдлхйлжаоЬк Ьдлжвтк.!)
[0;1m} T Preference edit, field 4


UEDITLT5 {[0;1m
!JЛЬ Шмлу лЮд Ьдлжву жихЭЬлЬ зжаж ЯШ ЬхдШа лж Шиоабц йШк бШдсва.
ЛзжиЬхлЬ дШ жихйЬлЬ ЬхлЬ лж бЬдлиабц бШдсва, ЬхлЬ лж зижйрзабц йШк бШдсва рк ШнЬлЮихШ.!)
[0;1m} T Preference edit, field 5


UEDITLT6 {[0;1m
!JЛЬиабжх оиуйлЬк ЬхдШа ШибЬлс ЬджовЮлабжх йлак ШалуйЬак зижйрзабук ймджвхШк
зжм бсджмд. ЛЬ Шмлу лЮ ичЯгайЮ жихЭЬлЬ бсЯЬ зцйЮ щиШ ЯШ гзжижчд дШ йШк бШвжчд
йЬ зижйрзабу ймджвхШ (chat). ГщйлЬ гхШ оиждабу ЫасибЬаШ Шзц 0 рк 999 вЬзлс. Ад
ЫщйЬлЬ 0, лцлЬ ЫЬд ЯШ мзсиоЬа циаж йлжд ШиаЯгц лрд ШалуйЬрд зжм ЯШ
вШгЩсдЬлЬ.!)
[0;1m} T Preference edit, field 6


UEDITLT7 {[0;1m
!JДЫщ жихЭЬлЬ Шд ЯтвЬлЬ лШ ЬаЫабс иугШлШ дШ ЬхдШа ЬдЬиЪс у цоа. ЛзжиЬхлЬ дШ
ЬдЬиЪжзжауйЬлЬ у дШ ШзЬдЬиЪжзжауйЬлЬ лШ ЬаЫабс иугШлШ бШлс ЩжчвЮйЮ йлак лЮвЬймджгавхЬк
(Ьдлжву [33mACTION[37m). ДЫщ имЯгхЭЬлЬ лЮд Шиоабу бШлсйлШйЮ лрд ЬаЫабщд иЮгслрд.!)
[0;1m} T Preference edit, field 7


UEDITLT8 {[0;1m
!JЛЬ Шмлу лЮд Ьдлжву жихЭЬлЬ лж "оищгШ" йШк.
ЙсЯЬ оиуйлЮк лрд лЮвЬймджгаващд гзжиЬх дШ тоЬа тдШ Шзц лШ 15 ЫмдШлс
оищгШлШ. Тж зижйрзабц йШк оищгШ ЬзЮиЬсЭЬа лЮд ЬгнсдайЮ цврд лрд гЮдмгслрд Шзц Ьйск,
бШа ЫхдЬа зижйрзабц лцдж йЬ Шмлс зжм втлЬ. Узсиожмд лШ Ьеук ЫаШЯтйагШ оищгШлШ
(Шд ЪхдЬлШа, зижйзШЯуйлЬ дШ ШзжнчЪЬлЬ лмоцд ЫмйЫасбиалШ оищгШлШ):!)

[0;34mСбжчиж гзвЬ (1)         [32mСбжчиж зисйадж (2)       [36mСбжчиж ЪШвсЭаж (3)
[31mСбжчиж бцббадж (4)      [35mСбжчиж грЩ (5)           [33mЙШнт (6)
[0mВбихЭж (7)              [1;30mСбжчиж ВбихЭж (8)        [34mЛзвЬ (9)
[32mПисйадж (10)            [36mВШвсЭаж (11)             [31mЙцббадж (12)
[35mЛрЩ (13)                [33mЙхлиадж (14)             [37mАйзиж (15)

[0;1m} T Preference edit, field 7





MSGNAX {[0;1;31m
!JКмзсгШа, лж ЬзхзЬЫж зицйЩШйук йШк ЫЬд ЬзалитзЬа лЮд ШввШЪу лрд гЮдмгслрд ЬайцЫжм/ЬецЫжм.!)
[0;1m} T Preference edit, can't change entry/exit messages (access denied)


MSGNCRE {[0;1;31m
!JКмзсгШа, ЫЬд тоЬлЬ ШибЬлтк гждсЫЬк ЪаШ дШ ШввсеЬлЬ лж гудмгШ ЬайцЫжм йШк.!)
[0;1m} T Preference edit, can't change entry message (no credits)


MSGNCRX {[0;1;31m
!JКмзсгШа, ЫЬд тоЬлЬ ШибЬлтк гждсЫЬк ЪаШ дШ ШввсеЬлЬ лж гудмгШ ЬецЫжм йШк.!)
[0;1m} T Preference edit, can't change entry message (no credits)


MSGCHE {[0;1;32m
!JАввсеШлЬ лж гудмгШ ЬайцЫжм йШк, бШа оиЬрЯубШлЬ 10 гждсЫЬк.!)
[0;1m} T Preference edit, changed entry message


MSGCHX {[0;1;32m
!JАввсеШлЬ лж гудмгШ ЬецЫжм йШк, бШа оиЬрЯубШлЬ 10 гждсЫЬк.!)
[0;1m} T Preference edit, changed exit message


EDITOK {[0;1;32m
!JОа ШввШЪтк ШзжЯЮбЬчЯЮбШд.!)
[0;1m} T Preference edit, record updated


EDITCAN {[0;1;33m
!JОа ШввШЪтк ШбмищЯЮбШд.!)
[0;1m} T Preference edit, changes cancelled


SCANHDR {[0;1;32m
ХиуйлЮк    ЙШдсва
!F─
[0;1m} T Scan channels, header


SCANTAB1A {[0;1m%-10s !i!W} T Scan channels, table entry, 1st part, this user
SCANTAB1B {[0;37m%-10s[1m !i!W} T Scan channels, table entry, 1st part, other user


SCANTHSCH {[0;1m} T Scan channels, channel where this user is present
SCANOTHCH {[0;37m} T Scan channels, other channels

SCANPRVM {Слжм %s} T Scan channels, 'in user's private channel', male user

SCANPRVF {СлЮк %s} T Scan channels, 'in user's private channel', female user

SCANCLUB {Слж club %s} T Scan channels, 'in club xxx's channel'

SCANOTHR {%s} T Scan channels, in other channel


SCANTPC {: %s} T Scan channels, channel topic


SCANUNL { (ГЬд ЬгнШдхЭЬлШа)} T Scan channels, unlisted channel (sysop's eyes only)


SCANCHTM {СмджгавЬх гЬ лжд %s} T Scan channels, user chatting with male user

SCANCHTF {СмджгавЬх гЬ лЮд %s} T Scan channels, user chatting with female user


SCANRO { (ЗЬШлук)} T Scan channels, user is read-only


SCANACC {[36mДхйлЬ %s бШдсва } T Scan channels, show access
SCANAX2 {[35mДхдШа %s бШдсва } T Scan channels, show access to owner of channel

SCANIM {ЬмзицйЫЬблжк йлж} T Scan channels, invited, male version
SCANIF {ЬмзицйЫЬблЮ йлж} T Scan channels, invited, female version

SCANRM {ЬмзицйЫЬблжк рк ЯЬШлук йлж} T Scan channels, invited read-only, male version
SCANRF {ЬмзицйЫЬблЮ рк ЯЬШлук йлж} T Scan channels, invited read-only, female version

SCANUM {ШзжбвЬайгтджк Шзц лж} T Scan channels, uninvited, male version
SCANUF {ШзжбвЬайгтджк Шзц лж} T Scan channels, uninvited, female version

SCANINVM {лжм [37m%s[36m.} T Scan channels, invitation, male user

SCANINVF {лЮк [37m%s[36m.} T Scan channels, invitation, female user

SCANINVC {лжм club [37m%s[36m.} T Scan channels, invitation, club

SCANINVO {[37m%s[36m.} T Scan channels, invitation, other

SCANINVY {йШк.} T Scan channels, invitation, your channel


SCANTAB2A {(%s)
} T Scan channels, table entry, 2nd part #1


SCANTAB2B {%s (%s): %s
} T Scan channels, table entry 3


SCANTABE {!0i!)
} T Scan channels, table entry, end


SCANFTR {[0;1;32m!F─
[0;1m} T Scan channels, footer


JOINHLP {[0;1m
!JВаШ дШ зслЬ йЬ бсзжаж сввж бШдсва, ЫщйлЬ лЮд Ьдлжву [33mJOIN
<бШдсва>[37m, у Шзвщк [33m/J <бШдсва>[37m, цзжм [33m<бШдсва>[37m ЬхдШа
лж цджгШ лжм бШдШважч йлж жзжхж ЯтвЬлЬ дШ гЬлШнЬиЯЬхлЬ.!)

!JГхдждлШк Шзвщк [33mJOIN[37m у [33m/J[37m, гЬлШнтиЬйлЬ йлж зижйрзабц
йШк бШдсва. Ад ЩихйбЬйлЬ уЫЮ ЬбЬх, гЬлШнтиЬйлЬ йлж бЬдлиабц бШдсва, йШд дШ
ЬхоШлЬ ЫщйЬа лЮд Ьдлжву [33mMAIN[37m.!)
[0;1m} T Help on JOIN command


UNKCLUB {[0;1;31m
!JКмзсгШа, ЫЬд мзсиоЬа Шмлц лж club.!)
[0;1m} T Unknown club


NAXCLUB {[0;1;31m
!JКмзсгШа, ЫЬд мзсиоЬа Шмлц лж club.!)
[0;1m} T No access to club


UNKCHAN {[0;1;31m
!JГЬд мзсиоЬа Шмлц лж бШдсва.!)
[0;1m} T Non-existant channel


CHNAX {[0;1;31m
!JКмзсгШа, ЫЬд тоЬлЬ зицйЩШйЮ йЬ Шмлц лж бШдсва.!)
[0;1m} T No access to channel


SAMECHAN {[0;1;31m
!JДхйлЬ уЫЮ й'Шмлц лж бШдсва.!)
[0;1m} T You are already in this channel


UNLSTON {[0;1m
!JТж бШдсва йлж жзжхж ЩихйбЬйлЬ ЫЬд ЯШ ЬгнШдхЭЬлШа звтжд йЬ сввжмк
оиуйлЬк.!)
[0;1m} T UNLIST feature enabled


UNLSTOFF {[0;1m
!JОа сввжа оиуйлЬк гзжижчд звтжд дШ Ыжмд йЬ зжаж бШдсва ЩихйбЬйлЬ.!)
[0;1m} T UNLIST feature disabled



INVHELP {[0;1m!JЛЬ лЮд Ьдлжву [33mINVITE[37m (у [33m/I[37m ЪаШ
ймдлжгхШ) гзжиЬхлЬ дШ бШвтйЬлЬ тдШд у цвжмк лжмк оиуйлЬк йлж зижйрзабц йШк
бШдсва. ЛзжиЬхлЬ дШ ЫщйЬлЬ лЮд Ьдлжву жзжмЫузжлЬ йлак лЮвЬймджгавхЬк (Ьблцк
лжм chat нмйабс), Шввс Ю зицйбвЮйЮ айочЬа ЛОМО ЪаШ лж зижйрзабц йШк бШдсва.
Ж Ьдлжву ймдлсййЬлШа рк Ьеук:!)

!0lINVITE <пЬмЫщдмгж>       !i!WПицйбвЮйЮ лжм <пЬмЫрдчгжм> йлж бШдсва йШк.!)
!0lINVITE ALL               !i!WПицйбвЮйЮ цврд йлж бШдсва йШк.!)
!0l
!JЖ Ьдлжву [33mINVITE ALL[37m ШджхЪЬа лж бШдсва йЬ цвжмк лжмк оиуйлЬк зжм
ЬхдШа лщиШ йлак лЮвЬймджгавхЬк у зжм ЯШ гзжмд ШиЪцлЬиШ. ГЬд йлтвдЬлШа
ЬаЫжзжхЮйЮ зицйбвЮйЮк йЬ бШдтдШ оиуйлЮ.!) 
[0;1m} T INVITE, help


IUNKUSR {[0;1;31m
!JКмзсгШа, лж гтвжк "[37m%s[31m" ЫЬд ЬхдШа Шмлу лЮ йлаЪгу йлЮ ЩсйЮ.!)
[0;1m} T INVITE, unknown user


INOKALL {[0;1;35;5m
!JОвжа[0;1;35m ЬхдШа зижйбЬбвЮгтджа йлж бШдсва йШк.
ВаШ дШ ШбмищйЬлЬ лЮд зицйбвЮйЮ ЫщйлЬ "[33muninvite all[35m".!)
[0;1m} T INVITE, all users are now welcome to your channel


IWHYU {[0;1;31m
!JПжацк ж вцЪжк дШ зижйбШвтйЬлЬ лжд ЬШмлц йШк;!)
[0;1m} T INVITE, why invite yourself?


IRECIP {[0;1m■■■
[35m!J%s [37m%s[35m йШк зижйбсвЬйЬ йлж зижйрзабц %s бШдсва.!)
[0;1m} T INVITE, message sent to invited party


IRECHE {О} T INVITE, male article (if applicable)

IRECSHE {Ж} T INVITE, female article (if applicable)


IRECHIS {лжм} T INVITE, "his" string (as in "his channel")

IRECHER {лЮк} T INVITE, "her" string (as in "her channel")


IJOIN {[0;1m
!JГщйлЬ "[33mjoin %s[37m" ЪаШ дШ зслЬ йЬ Шмлц лж бШдсва.!)
[0;1m} T INVITE, instructions on how to JOIN user


ISENDR {[0;1;35m
!JПижйбШвтйШлЬ %s [33m%s[35m йлж зижйрзабц йШк бШдсва.!)
[0;1m} T INVITE, you have invited a user to your private channel

ISNDM {лжд} T INVITE, male article (if applicable)

ISNFF {лЮд} T INVITE, female article (if applicable)


INVWRN {[0;1m
!W[31;5m██[0;1;31m  ПРОСОХЖ: !iГЬд ЩихйбЬйлЬ йлж зижжйрзабц йШк
бШдсва. Ж зицйбвЮйЮ айочЬа [37mЛОМО[31m ЪаШ лж зижйрзабц йШк бШдсва.!)
!0l[0;1m} T INVITE, warning: you're not in your private channel


UNVALL {[0;1;35;5mЙШдЬхк[0;1;35m сввжк ЫЬд гзжиЬх дШ гзЬх йлж бШдсва йШк.[0;1m

ВаШ дШ ЫащеЬлЬ бсзжажд уЫЮ зШицдлШ зитзЬа
дШ ЫщйЬлЬ "[33mUninvite <пЬмЫщдмгж>[0;1m".
} T Teleconference global invite is now off



UNVHELP {[0;1m!JЛЬ лЮд Ьдлжву [33mUNINVITE[37m (у [33m/U[37m ЪаШ
ймдлжгхШ) гзжиЬхлЬ дШ ШзжбвЬхйЬлЬ тдШд у цвжмк лжмк оиуйлЬк йлж зижйрзабц йШк
бШдсва. ЛзжиЬхлЬ дШ ЫщйЬлЬ лЮд Ьдлжву жзжмЫузжлЬ йлак лЮвЬймджгавхЬк (Ьблцк
лжм chat нмйабс). Ж Ьдлжву ймдлсййЬлШа рк Ьеук:!)

!0lUNINVITE <пЬмЫщдмгж>     !i!WАзжбвЬайгцк лжм <пЬмЫрдчгжм> Шзц лж бШдсва йШк.
Ад ж оиуйлЮк ЬхдШа уЫЮ йлж бШдсва йШк, нЬчЪЬа ШмлцгШлШ.!)
!0l
UNINVITE ALL                 !i!WЙвЬхйагж лжм бШдШважч йШк.!)
!0l

!JЖ Ьдлжву [33mUNINVITE ALL[37m бвЬхдЬа лж бШдсва ЪаШ цвжмк лжмк оиуйлЬк
зжм ЬхдШа лщиШ йлак лЮвЬймджгавхЬк у зжм ЯШ гзжмд ШиЪцлЬиШ. ГЬд йлтвдЬлШа
ЬаЫжзжхЮйЮ зицйбвЮйЮк йЬ бШдтдШ оиуйлЮ. Тж йчйлЮгШ ЫЬд ЯШ ЫащеЬа Шзц лж
бШдсва йШк оиуйлЬк зжм уЫЮ ЩихйбждлШа ЬбЬх у зжм тожмд зижйбвЮЯЬх
зижйрзабс.!)
[0;1m} T UNINVITE, help


UUNKUSR {[0;1;31m
!JКмзсгШа, лж гтвжк "[37m%s[31m" ЫЬд ЬхдШа Шмлу лЮ йлаЪгу йлЮ ЩсйЮ.!)
[0;1m} T UNINVITE, unknown user


UNOKALL {[0;1;35;5m
!JТж зижйрзабц бШдсва йШк ЬхдШа звтжд бвЬайлц ЪаШ цвжмк Ьблцк Шзц лжмк
зШицдлЬк бШа лжмк оиуйлЬк зжм тожмд зижйбвЮЯЬх зижйрзабс йлж бШдсва йШк.!)
[0;1m} T UNINVITE, your channel is now private


UWHYU {[0;1;31m
!JДхдШа ШЫчдШлж дШ ШзжбвЬхйЬлЬ лжд ЬШмлц йШк Шзц лж зижйрзабц йШк бШдсва!!)
[0;1m} T UNINVITE, can't uninvite yourself!


URECIP {[0;1m■■■
[35m!J%s [37m%s[35m йШк ШзтбвЬайЬ Шзц лж зижйрзабц %s бШдсва.!)
[0;1m} T UNINVITE, message sent to uninvited party


URECHE {О} T UNINVITE, male article (if applicable)

URECSHE {Ж} T UNINVITE, female article (if applicable)


URECHIS {лжм} T UNINVITE, "his" string (as in "his channel")

URECHER {лЮк} T UNINVITE, "her" string (as in "her channel")


USENDR {[0;1;31m
!JАзжбвЬхйШлЬ %s [33m%s[31m Шзц лж зижйрзабц йШк бШдсва.!)
[0;1m} T UNINVITE, you have invited a user to your private channel

USNDM {лжд} T UNINVITE, male article (if applicable)

USNFF {лЮд} T UNINVITE, female article (if applicable)

UOTHER {[0;1;31m
!J%s [37m%s[31m гцвак ЬбЫащоЯЮбЬ Шзц лж бШдсва.!)
[0;1m} T UNINVITE, message sent to other users of the channel


DROPMAIN {[0;1;33m
!JДзайлижну йлж бЬдлиабц бШдсва.!)
[0;1m} T Dropping to main channel


DISCDROP {[0;1m■■■
[36m!J%s [33m%s[36m гцвак ШзжймдЫтЯЮбЬ.!)
[0;1m} T Owner of channel disconnected (dropping to MAIN)


ROHELP {[0;1m!JЛЬ лЮд Ьдлжву [33mREADONLY[37m (у [33m/RO[37m ЪаШ
ймдлжгхШ) гзжиЬхлЬ дШ бШвтйЬлЬ рк ЯЬШлтк тдШд у цвжмк лжмк оиуйлЬк йлж зижйрзабц йШк
бШдсва. Оа оиуйлЬк ЯЬШлтк гзжижчд дШ зШиШйлжчд йЬ гхШ ймЭулЮйЮ Шввс ЫЬд
тожмд ЫабШхргШ вцЪжм. Амлц ЬхдШа оиуйагж ЪаШ ЬзхйЮгЬк ймЭЮлуйЬак бвз.
ЛзжиЬхлЬ дШ ЫщйЬлЬ лЮд Ьдлжву жзжмЫузжлЬ йлак лЮвЬймджгавхЬк (Ьблцк
лжм chat нмйабс), Шввс Ю зицйбвЮйЮ айочЬа ЛОМО ЪаШ лж зижйрзабц йШк бШдсва.
Ж Ьдлжву ймдлсййЬлШа рк Ьеук:!)

!0lREADONLY <пЬмЫщдмгж>     !i!WПицйбвЮйЮ лжм <пЬмЫрдчгжм> рк ЯЬШлу йлж бШдсва йШк.!)
!0lREADONLY ALL             !i!WПицйбвЮйЮ цврд йлж бШдсва йШк.!)
!0l
!JЖ Ьдлжву [33mREADONLY ALL[37m ШджхЪЬа лж бШдсва йЬ цвжмк лжмк оиуйлЬк зжм
ЬхдШа лщиШ йлак лЮвЬймджгавхЬк у зжм ЯШ гзжмд ШиЪцлЬиШ. Ойжа гзжмд йлж
бШдсва ЯШ ЬхдШа ЯЬШлтк. ВаШ дШ ЬзалитпЬлЬ йЬ бсзжажд дШ гавуйЬа Шнжч гзЬа
йлж бШдсва йШк, оиЮйагжзжауйлЬ лЮд Ьдлжву [33mUNSQUELCH <пЬмЫщдмгж>[37m. ЛЬ лЮд Ьдлжву
[33mUNSQUELCH <пЬмЫщдмгж>[37m ж оиуйлЮк осдЬа зсва лж ЫабШхргШ вцЪжм. Ж
Ьдлжву READONLY ALL ЫЬд йлтвдЬа ЬаЫжзжхЮйЮ зицйбвЮйЮк йЬ бШдтдШ оиуйлЮ.!) 
[0;1m} T READONLY, help


RUNKUSR {[0;1;31m
!JКмзсгШа, лж гтвжк "[37m%s[31m" ЫЬд ЬхдШа Шмлу лЮ йлаЪгу йлЮ ЩсйЮ.!)
[0;1m} T READONLY, unknown user


ROOKALL {[0;1;35;5m
!JОвжа[0;1;35m ЬхдШа зижйбЬбвЮгтджа йлж бШдсва йШк рк ЯЬШлтк.
ВаШ дШ ШбмищйЬлЬ лЮд зицйбвЮйЮ ЫщйлЬ "[33muninvite all[35m".
ВаШ дШ ЬзалитпЬлЬ лжд вцЪж йЬ цвжмк цйжмк гзжмд йлж бШдсва йШк, ЫщйлЬ
[33minvite all[37m.!)
[0;1m} T READONLY, all users are now welcome to your channel


RWHYU {[0;1;31m
!JПжацк ж вцЪжк дШ зижйбШвтйЬлЬ лжд ЬШмлц йШк (зцйж гсввжд дШ лжм
ШнШаитйЬлЬ лж вцЪж);!)
[0;1m} T READONLY, why invite yourself?


RRECIP {[0;1■■■
[35m!J%s [37m%s[35m йШк зижйбсвЬйЬ йлж (рк ЯЬШлу) зижйрзабц %s бШдсва.!)
[0;1m} T READONLY, message sent to invited party


RRECHE {О} T READONLY, male article (if applicable)

RRECSHE {Ж} T READONLY, female article (if applicable)


RRECHIS {лжм} T READONLY, "his" string (as in "his channel")

RRECHER {лЮк} T READONLY, "her" string (as in "her channel")


RJOIN {[0;1m
!JГщйлЬ "[33mjoin %s[37m" ЪаШ дШ зслЬ йЬ Шмлц лж бШдсва.!)
[0;1m} T READONLY, instructions on how to JOIN user


RSENDR {[0;1;35m
!JПижйбШвтйШлЬ %s [33m%s[35m рк ЯЬШлу йлж зижйрзабц йШк бШдсва.!)
[0;1m} T READONLY, you have invited a spectator to your private channel

RSNDM {лжд} T READONLY, male article (if applicable)

RSNFF {лЮд} T READONLY, female article (if applicable)


SQHELP {[0;1m!JЛЬ лЮд Ьдлжву [33mSQUELCH <пЬмЫщдмгж>[37m гзжиЬхлЬ дШ
ШнШаитйЬлЬ лж ЫабШхргШ вцЪжм Шзц лж оиуйлЮ гЬ лж пЬмЫщдмгж зжм жихйШлЬ.
ЛзжиЬхлЬ дШ лж бсдЬлЬ Шмлц гцдж йлж зижйрзабц йШк бШдсва бШа йЬ бШдсваШ зжм
лмоцд зижЬЫиЬчЬлЬ. ВаШ дШ еШдШЫщйЬлЬ лж ЫабШхргШ вцЪжм йЬ тдШ оиуйлЮ,
оиЮйагжзжауйлЬ лЮд Ьдлжву [33mUNSQUELCH <пЬмЫщдмгж>[37m.!)
[0;1m} T SQUELCH, help


SQNOAX {[0;1;31m
!JКмзсгШа, гцдж ж зижЬЫиЬчрд лЮк ймЭулЮйЮк гзжиЬх дШ лж бсдЬа Шмлц.!)
[0;1m} T SQUELCH/UNSQUELCH, can't squelch/unsquelch a user


QUNKUSR {[0;1;31m
!JКмзсгШа, лж гтвжк "[37m%s[31m" ЫЬд ЬхдШа Шмлу лЮ йлаЪгу йлЮ бШдсва йШк.!)
[0;1m} T SQUELCH/UNSQUELCH, unknown user


SQUMOD {[0;1;36m
!JЛцвак йлЬиуйШлЬ Шзц %s [37m%s[36m лж ЫабШхргШ жгавхШк.!)
[0;1m} T SQUELCH, notification sent to 'squelcher'


SQUMODM {О зижЬЫиЬчрд} T SQUELCH/UNSQUELCH, moderator, male article

SQUMODF {Ж зижЬЫиЬчжмйШ} T SQUELCH/UNSQUELCH, moderator, female article


SQUMALE {лжд} T SQUELCH/UNSQUELCH, male (un)squelchee, article

SQUFEM {лЮд} T SQUELCH/UNSQUELCH, female (un)squelchee, article


SQUYOU {[0;1m■■■
[31m!J[31m%s лЮк ймЭЮлуйЬрк гцвак йШк ШнШхиЬйЬ лж ЫабШхргШ вцЪжм.
ГЬд гзжиЬхлЬ звтжд дШ гавуйЬлЬ йЬ Шмлц лж бШдсва гтоиа дШ ШиЯЬх ж
зЬиажиайгцк.!)
[0;1m} T SQUELCH, notification sent to 'squelchee'


SQUOTHR {[0;1m■■■
[33m!J%s лЮк ймЭЮлуйЬрк гцвак йлтиЮйЬ Шзц %s [37m%s[33m лж ЫабШхргШ
жгавхШк.!)
[0;1m} T SQUELCH, the moderator just squelched someone


USQHELP {[0;1m!JЛЬ лЮд Ьдлжву [33mUNSQUELCH <пЬмЫщдмгж>[37m гзжиЬхлЬ дШ
ЬзалитпЬлЬ йлжд жиайЯтдлШ оиуйлЮ лж ЫабШхргШ вцЪжм зжм лжм ЬхоЬ ШнШаиЬЯЬх
ЪаШ бсзжаж вцЪж. ЛзжиЬхлЬ дШ лж бсдЬлЬ Шмлц гцдж йлж зижйрзабц йШк бШдсва
бШа йЬ бШдсваШ зжм лмоцд зижЬЫиЬчЬлЬ. Ж Ьдлжву Шмлу оиЮйагЬчЬа бШа ЪаШ дШ
ЫщйЬа лж ЫабШхргШ вцЪжм йЬ бсзжаж ЯЬШлу лжм бШдШважч (Щв. Ьдлжву
[33mREADONLY[37m).!)
[0;1m} T UNSQUELCH, help


USQMOD {[0;1;36m
!JЛцвак уиШлЬ Шзц %s [37m%s[36m лЮд йлтиЮйЮ жгавхШк.!)
[0;1m} T UNSQUELCH, notification sent to 'unsquelcher'.


USQYOU {[0;1m■■■
[32m!J%s лЮк ймЭЮлуйЬрк уиЬ лЮ йлтиЮйЮ лжм ЫабШащгШлжк жгавхШк
зжм йШк ЬхоЬ ЬзаЩсввЬа бШа гзжиЬхлЬ дШ гавуйЬлЬ зсва.!)
[0;1m} T UNSQUELCH, notification sent to 'unsquelchee'


USQOTHR {[0;1m■■■
[33m!J%s лЮк ймЭЮлуйЬрк гцвак уиЬ лЮ йлтиЮйЮ жгавхШк зжм ЬхоЬ ЬзаЩсввЬа й%s
[37m%s[33m.!)
[0;1m} T UNSQUELCH, the moderator just unsquelched someone


TLKSQU {[0;1;31m
!JКмзсгШа, ЫЬд тоЬлЬ ЫабШхргШ вцЪжм йЬ Шмлц лж бШдсва. ОлаЫузжлЬ ЪиснЬлЬ
[5mГДМ[0;1;31m гЬлШЫхЫЬлШа йлжмк сввжмк оиуйлЬк.!)
[0;1m} T User is squelched, can't talk


TOPNAX {[0;1;31m
!JГЬд гзжиЬхлЬ дШ ШввсеЬлЬ лж ЯтгШ Шмлжч лжм бШдШважч.!)
[0;1m} T TOPIC, can't change this channel's topic


TOPCLR {[0;1;35m
!JТж ЯтгШ лжм бШдШважч ЫаШЪиснлЮбЬ. ВаШ дШ жихйЬлЬ дтж ЯтгШ, ЫщйлЬ
[33mTOPIC <ЯтгШ>[35m.!)
[0;1m} T TOPIC, channel topic deleted.


TOPM {О} T TOPIC, male moderator

TOPF {Ж} T TOPIC, female moderator


TOPNEW {[0;1m■■■
[35m!J%s [37m%s[35m циайЬ лж ЯтгШ Шмлжч лжм бШдШважч рк: "[37m%s[35m".!)
[0;1m} T TOPIC, notification of new channel topic


TOPMOD {[0;1;35m
!JТж ЯтгШ лжм бШдШважч ЬхдШа звтжд "[37m%s[35m".!)
[0;1m} T TOPIC, acknowledgement of new topic



CHTHELP {[0;1m!JЖ Ьдлжву [33mCHAT <пЬмЫщдмгж>[37m йШк ЬзалитзЬа дШ
ймджгавуйЬлЬ зижйрзабс гЬ бсзжаж сввж гтвжк. О оиуйлЮк лжм жзжхжм лж
пЬмЫщдмгж жихЭЬлЬ ЫЬд оиЬасЭЬлШа дШ ЬхдШа йлж бШдсва йШк, Шд бШа зитзЬа дШ
гЮд ймджгавЬх уЫЮ зижйрзабс. Ж хЫаШ Ьдлжву оиЮйагЬчЬа бШа ЪаШ дШ ШзжЫЬоЯЬхлЬ
лЮд зицйбвЮйЮ зижйрзабук ймджгавхШк Ьдцк сввжм гтвжмк. ЛзжиЬхлЬ дШ имЯгхйЬлЬ
лж оиждабц ЫасйлЮгШ гЬлШеч ЬайЬиоцгЬдрд зижйбвуйЬрд йЬ chat гЬ лЮд Ьдлжву
[33mEDIT[37m.!)
[0;1m} T CHAT, Help


CHTNAX {[0;1;31m
!JКмзсгШа, лж ЬзхзЬЫж зицйЩШйук йШк ЫЬд йШк ЬзалитзЬа дШ гавуйЬлЬ йЬ
зижйрзабу ймджгавхШ гЬ сввж гтвжк.!)
[0;1m} T CHAT, user doesn't have the key required to chat


CHTNIN {[0;1;31m
!JКмзсгШа, лж ЬзхзЬЫж зицйЩШйук йШк ЫЬд йШк ЬзалитзЬа дШ зижйбШвтйЬлЬ сввж
гтвжк йЬ зижйрзабу ймджгавхШ.!)
[0;1m} T CHAT, user doesn't have the key required to initiate a chat


CHTONX {[0;1;31m
!JКмзсгШа, лж ЬзхзЬЫж зицйЩШйЮк лжм гтвжмк [37m%s[31m ЫЬд ЬзалитзЬа дШ
гавуйЬа йЬ зижйрзабу ймджгавхШ.!)
[0;1m} T CHAT, other user can't participate in a chat


CHTUID {[0;1;31m
!JСмЪЪдщгЮ, лж "[37m%s[31m" ЫЬд лШаиасЭЬа йЬ бШдтдШд зШицдлШ йлак
лЮвЬймджгавхЬк.!)
[0;1m} T CHAT, Unknown user


CHTSLF {[0;1;31m
!JЖ Ьдлжву Шмлу ЬхдШа оиуйагЮ ЪаШ зижйрзабу ймджгавхШ гЬ сввШ гтвЮ, цоа ЪаШ
ЫаШвжЪайгц!!)
[0;1m} T CHAT, can't chat with yourself


CHTM {О} T CHAT, male article
CHTF {Ж} T CHAT, female article


CHTALR {[0;1;31m
!JСмЪЪдщгЮ, %s [33m%s[31m ЩихйбЬлШа уЫЮ йЬ зижйрзабу ймджгавхШ.!)
[0;1m} T CHAT, user is already chatting


CHTNOT1 {[0;1m■■■
[35m!J%s [37m%s[35m гцвак сиоайЬ зижйрзабу ймджгавхШ гЬ бсзжаж сввж
гтвжк.!)
[0;1m} T CHAT, user just started chatting with someone


CHTNOT2 {[0;1m■■■
[35m!J%s [37m%s[35m гцвак сиоайЬ зижйрзабу ймджгавхШ гЬ %s [37m%s[35m.!)
[0;1m} T CHAT, user just started chatting with someone on the same channel


CHTWITHM {лжд} T CHAT, object user, male article (for CHTNOT2)
CHTWITHF {лЮд} T CHAT, object user, female article (for CHTNOT2)


CHTACC {[0;1m■■■
[35m!J%s [37m%s[35m гцвак ШзжЫтоЯЮбЬ лЮд
зицйбвЮйу йШк йЬ зижйрзабу ймджгавхШ.!)
[0;1m} T CHAT, user just accepted your invitation to a chat


CHTENT {[0;1m
╔════════════════════════════════╗
║ [0;1;33m ДМАРНЖ ПРОСЧПИЙЖС СУМОЛИКИАС [0;1m ║
╚════════════════════════════════╝
!JГщйлЬ e[[33mX[0;1m]it йЬ гаШ бЬду ЪиШггу ЪаШ дШ ЬзайлитпЬлЬ йлак
лЮвЬймджгавхЬк.!)

} T CHAT, entering chat mode


CHTFRQ {[0;1;31m
!J%s [37m%s[31m тоЬа уЫЮ бвЮЯЬх йЬ зижйрзабу ймджгавхШ.
ПШиШбШвщ ЫжбагсйлЬ еШдс гЬлс Шзц [37m%d[31m %s.!)
[0;1m} T CHAT, that user has already been invited to a chat


CHTMINS {вЬзлц} T CHAT, minutes, singular
CHTMINP {вЬзлс} T CHAT, minutes, plural


CHTREQ {[0;1m■■■
[35m!J%s [37m%s[35m йШк ЭЮлс дШ ШиохйЬлЬ гШЭх %s зижйрзабу ймджгавхШ.
ГщйлЬ "[33mchat %s[35m" ЬШд ЯтвЬлЬ дШ ШзжЫЬоЯЬхлЬ лЮд зицйбвЮйЮ.!)
[0;1m} T CHAT, incoming invitation to a chat


CHTHIS {лжм} CHAT, 'his', male version
CHTHER {лЮк} CHAT, 'her', male version


CHTROK {[0;1;35m
!J%s [37m%s[35m ЬаЫжзжауЯЮбЬ ЪаШ лЮд зицйбвЮйу йШк.!)
[0;1m} T CHAT, chat request has been sent


CHTEXT {[0;1;35m

!JДежЫжк Шзц лЮд зижйрзабу ймджгавхШ.!)
[0;1m} T CHAT, exiting chat mode


CHTUNOT {[0;1;31m
!JТж гтвжк [37m%s[33m ЬхдШа ШзШйожвЮгтдж бШа ЫЬд гзжиЬх дШ
ЬаЫжзжаЮЯЬх. ЗШ зитзЬа дШ ЬзШдШвсЩЬлЬ лЮд зицйбвЮйу йШк ШиЪцлЬиШ.!)
[0;1m} T CHAT, user is BUSY, cannot be invited


ENTCHT {!J[0;1;36m%s [33m%s[36m гцвак ЬзтйлиЬпЬ Шзц зижйрзабу ймджгавхШ.!)
[0;1m} T A user just entered this channel, leaving a chat


CH2OFT {[0;1;31m
!JКмзсгШа, ЪаШ дШ гЮд ЬджовжчдлШа жа сввжа оиуйлЬк ЫЬд гзжижчгЬ дШ ЬзалитпжмгЬ
лцйж ймодтк ШввШЪтк бШдШващд у ЬайцЫжмк/ЬецЫжмк Шзц лак лЮвЬймджгавхЬк.
ГжбагсйлЬ зсва йЬ вхЪШ ЫЬмлЬицвЬзлШ.!)
[0;1m} T User changes channels too often


UNNOT {[0;1;33m
!JТж гтвжк [37m%s[33m ЬхдШа ШзШйожвЮгтдж бШа ЫЬд гзжиЬх дШ
ЬаЫжзжаЮЯЬх.!)
[0;1m} T User is BUSY, can't be notified


SVNOMM {О} T Substitution var ARTNOM/OTHNOM, male
SVNOMF {Ж} T Substitution var ARTNOM/OTHNOM, female

SVGENM {лжм} T Substitution var ARTGEN/OTHGEN, male
SVGENF {лЮк} T Substitution var ARTGEN/OTHGEN, female

SVDATM {Тжд} T Substitution var ARTDAT/OTHDAT, male
SVDATF {ТЮд} T Substitution var ARTDAT/OTHDAT, female

SVACCM {лжд} T Substitution var ARTACC/OTHACC, male
SVACCF {лЮд} T Substitution var ARTACC/OTHACC, female


ACTHLP {[0;1m
!JЛтйр лрд ЬаЫабщд иЮгслрд гзжиЬхлЬ дШ бсдЬлЬ зжввс зисЪгШлШ заж ШвЮЯадс
бШа гЬ зЬиаййцлЬиж... Ясиижк. Оа ЫмдШлтк зШисгЬлижа ЬхдШа:!)

!0lACTION ON (/A ON)      !i!WДдЬиЪжзжхЮйЮ лрд ЬаЫабщд иЮгслрд.!)
!0lACTION OFF (/A OFF)    !i!WАзЬдЬиЪжзжхЮйЮ лрд ЬаЫабщд иЮгслрд.!)
!0lACTION LIST (/A LIST)  !i!WДгнсдайЮ цврд лрд ЬаЫабщд иЮгслрд.!)
!0l
!JОлШд тоЬлЬ лШ иугШлШ ЬдЬиЪс гзжиЬхлЬ дШ оиЮйагжзжауйЬлЬ втеЬак цзрк:
[33mhug[37m, [33msmile[37m, [33mlaugh[37m, [33mkiss[37m,
[33mgrin[37m, [33mkick[37m, [33mpunch[37m, [33mfrown[37m,
[33myell[37m, [33mcry[37m бвз.!)

!JЛЬиабс иугШлШ гзжижчд дШ ЫтождлШа ШдлабЬхгЬдж, гЬиабс сввШ цоа. ДШд ЪаШ
зШисЫЬаЪгШ ЯтвЬлЬ дШ навуйЬлЬ бсзжажд гзжиЬхлЬ дШ ЫщйЬлЬ лЮд Ьдлжву
"[33mkiss <пЬмЫщдмгж>[37m". Ад ЯтвЬлЬ дШ гЮд Ыжмд жа сввжа лж навх йШк
гзжиЬхлЬ дШ лж бсдЬлЬ гмйлабс ЫхдждлШк "[33mkiss <пЬмЫщдмгж>
secretly[37m".!)

!JДШд ЬхйлЬ йЬ бШву ЫасЯЬйЮ бШа ЯтвЬлЬ дШ ШЪбШвасйЬлЬ цвжмк цйжмк ЬхдШа йлж
хЫаж бШдсва гЬ Ьйск гзжиЬхлЬ дШ лж бсдЬлЬ ЫхдждлШк "[33mhug all[37m".
ДзхйЮк цлШд тоЬлЬ ЬдЬиЪжзжауйЬа лШ ЬаЫабс иугШлШ гзжиЬхлЬ дШ бсдЬлЬ лак
зисеЬак йШк заж зШиШйлШлабтк ЫхдждлШк тдШ иугШ зиад. Ад, зо, ЬхйлЬ
ЬбдЬмиайгтджк бШа ЯтвЬлЬ дШ зЬхлЬ йЬ цвжмк лжмк сввжмк дШ бсджмд ЮймохШ
гзжиЬхлЬ дШ ЪиспЬлЬ "[33myell бсдлЬ ЮймохШ![32m".!)
[0;1m} Actions, Help


ACTNAX {[0;1;31m
!JКмзсгШа, лж ЬзхзЬЫж зицйЩШйук йШк ЫЬд йШк ЬзалитзЬа дШ
оиЮйагжзжауйЬлЬ лШ ЬаЫабс иугШлШ.!)
[0;1m} T Actions, User doesn't have access to actions


ACTON {[0;1;32m!JДдЬиЪжзжауйШлЬ лШ ЬаЫабс иугШлШ!
(ЫщйлЬ "[33maction ?[32m" ЪаШ ЩжуЯЬаШ).!)
[0;1m} T Actions, Actions enabled


ACTOFF {[0;1;33m!JАзЬдЬиЪжзжауйШлЬ лШ ЬаЫабс иугШлШ.!)
[0;1m} T Actions, Actions disabled


ACTLST {[0;1;33m
admire[37m . . .  ЗШмгсЭр[36m   [33mapologise[37m . ЭЮлщ ймЪЪдщгЮ   [33mask[37m . . . . . . .  ирлщ
[33mbeg[37m . . . .  ЬбвазШищ   [33mbless[37m  . . . . . . ЬмвжЪщ   [33mblush[37m  . . .  бжббадхЭр
[33mbow[37m  . .  мзжбвхджгШа   [33mburp[37m  . . . . . . итЩжгШа   [33mcaress[37m  . . . . оШфЫЬчр
[33mchant[37m . . . . . псввр   [33mcheer[37m  . . . . . ЬзЬмнЮгщ   [33mclap[37m . . . . оЬаижбижлщ
[33mcomfort[37m  . ШдШбжмнхЭр   [33mcough[37m . . . . . . .  Щуор   [33mcry[37m . . . . . . . бвШхр
[33mcurse[37m . .  бШлШиатгШа   [33mdance[37m  . . . . . . ожиЬчр   [33mdeaf[37m . . .  бжмнШхджгШа
[33mdemand[37m . . . . ШзШалщ   [33mdream[37m . . . . ждЬаиЬчжгШа   [33mfaint[37m . . . .  вазжЯмгщ
[33mfrown[37m . . бШлйжмнасЭр   [33mgiggle[37m . . . . . оШоШдхЭр   [33mglare[37m  . . ШЪиажбжалсЭр
[33mgroan[37m  . . . .  ЩжЪЪщ   [33mhandshake[37m . . йнхЪЪр отиа   [33mhide[37m . . . . . бичЩжгШа
[33mhit[37m . . . . . . олмзщ   [33mhug[37m  . . . . .  ШЪбШвасЭр   [33mhum[37m . . .  йаЪжлиШЪжмЫщ
[33mkick[37m . . . . . бврлйщ   [33mkiss[37m  . . . . . . .  навщ   [33mlaugh[37m  . . . . . . ЪЬвщ
[33mlook[37m  . . . . бжалсЭр   [33mmassage[37m  . . . . .  лихЩр   [33mmoan[37m  . . . . ЪбиадасЭр
[33mnod[37m  . . . .  ймгнрдщ   [33mnotice[37m  . . . .  зШиШлЮищ   [33mnudge[37m  . . . . йбжмдлср
[33morder[37m . .  зШиШЪЪтвдр   [33mpinch[37m  . . . . . . лйагзщ   [33mponder[37m  . . ймввжЪжчгШа
[33mpray[37m . .  зижйЬчожгШа   [33mpunch[37m . . . .  ЪиждЯжбжзщ   [33mquestion[37m . . . ШдШбихдр
[33mrequest[37m . . . .  ЭЮлщ   [33mshiver[37m . . . . . .  литгр   [33mshoot[37m . . . .  змижЩжвщ
[33mshout[37m  . . . . нрдсЭр   [33mshrug[37m . . . . .  ШЫаШнжищ   [33msigh[37m . . . . ШдШйлЬдсЭр
[33msing[37m  . . .  лиШЪжмЫщ   [33mslap[37m . . . . . оШйлжмбхЭр   [33mslay[37m  . . . .  йнШЪасЭр
[33msmack[37m  . . навщ ЮоЮис   [33msmile[37m . . . . .  оШгжЪЬвщ   [33msneeze[37m . .  нлШидхЭжгШа
[33msniff[37m . . . .  гмихЭр   [33mstrip[37m  . . . . . ЪЫчджгШа   [33mtease[37m . . . .  зЬаисЭр
[33mthink[37m  . .  йбтнлжгШа   [33mtickle[37m  . . . . . ЪШиЪШвщ   [33mwait[37m . . . . . ШдШгтдр
[33mwave[37m  . . . . оШаиЬлщ   [33mwhip[37m . . . . .  гШйлаЪщдр   [33mwhistle[37m . . .  йнмихЭр
[33mwink[37m . .  бвЬхдр гсла   [33myawn[37m  . . .  оШйгжмиатгШа   [33myell[37m . . . .  жмивасЭр
[0;1m} T Teleconference action word list header


FMTUSER {[0;1m!J%s!)
[0;1m} T Actions, 'user' string format (response to issuing user)


FMTUSEC {[0;1m!J%s ЙШа гцдж ЪаШ @OTHACC@ @OTHUID@!!)
[0;1m} T Actions, 'user' string format if SECRETLY specified


FMTSMPL {[0;1m■■■
!W@USRCOL@%s!)
[0;1m} T Actions, 'simple' string format


FMTOTHR {[0;1m■■■
!W@USRCOL@%s!)
[0;1m} T Actions, 'other' string format


FMTALL {[0;1m■■■
!W@USRCOL@%s!)
[0;1m} T Actions, 'all' string format


FMTTRGT {[0;1m■■■
!W@USRCOL@%s!)
[0;1m} T Actions, 'target' string format


FMTSCRT {[0;1m■■■
!W@USRCOL@%s!)
[0;1m} T Actions, 'secret' string format


FMTADVB {[0;1m■■■
!W@USRCOL@@ARTNOM@ @USERID@ %s: %s!)
[0;1m} T Actions, 'adverb' string format


FMTGNRC {[0;1m■■■
!W@USRCOL@%s %s!)
[0;1m} T Actions, 'generic' string format


VERBSENT {[0;1;32m!W--- Тж ЬаЫабц иугШ гЬлШЫцЯЮбЬ ---!)
[0;1m} T Actions, action verb sent


VERBNMT {[0;1;31m
!JТж ЬаЫабц иугШ "[37m%s[31m" зитзЬа жзрйЫузжлЬ дШ ШбжвжмЯЬхлШа
Шзц гхШ нисйЮ.!)
[0;1m} T Actions, verb needs more input


VERBNOBJ {[0;1;31m
!JЙШа йЬ зжажд ЯтвЬлЬ дШ лж бсдЬлЬ Шмлц;!)
[0;1m} T Actions, verb needs an object


VERBUID {[0;1;31m
!JТж гтвжк "[37m%s[31m" ЫЬд ЩихйбЬлШа Шмлу лЮ йлаЪгу йлж бШдсва.!)
[0;1m} T Actions, unknown object/target user


VERBNAS {[0;1;31m
!JГЬд гзжиЬхлЬ дШ лж бсдЬлЬ Шмлц гмйлабс йЬ цвжмк лШмлцоиждШ!!)
[0;1m} T Actions, can't specify both ALL and SECRETLY


STGALL1 {ALL} T Actions, string that stands for 'ALL' (1st of 2 synonyms)
STGALL2 {EVERYONE} T Actions, string that stands for 'ALL' (2nd of 2 synonyms)

STGSEC1 {SECRETLY} T Actions, string that stands for 'SECRETLY' (1st of 2 synonyms)
STGSEC2 {SECRETLY} T Actions, string that stands for 'SECRETLY' (2nd of 2 synonyms)


PINTABL1 {[0;1m
!JТШ ШбцвжмЯШ "plugins" ЬхдШа ЫаШЯтйагШ:!)

[0;1m} T Plugins, list of plugins, header


PINTABL2 {[0;1;33m%-15s  !i!W[32m%s!)
!0l} T Plugins, list of plugins, table


PINTABL3 {[0;1m
!JГщйлЬ лж цджгШ Ьдцк "plugin" ШбжвжмЯжчгЬдж Шзц "[33mHELP[37m"
ЪаШ дШ зсиЬлЬ ЩжуЯЬаШ ЪаШ бсзжаШ ймЪбЬбиагтдЮ ЬнШигжЪу. ПШиШЫЬхЪгШлжк осиад,
Шд ЯтвШлЬ ЩжуЯЬаШ ЪаШ лж мзжйчйлЮгШ "CHESS", ЯШ ЫхдШлЬ "[33mCHESS
HELP[37m".!)
[0;1m} T  Plugins, list of plugins, footer


PINNONE {[0;1;31m
!JКмзсгШа, ЫЬд мзсиоЬа бШдтдШ "plugin" ЫаШЯтйагж й'Ьйск.!)
[0;1m} T Plugins, no plugins available (to you)


PINNAX {[0;1;31m
!JКмзсгШа, ЫЬд тоЬлЬ зицйЩШйЮ йлж plugin "[33m%s[31m".!)
[0;1m} T Plugins, users doesn't have access to plugin


PINALR {[0;1;31m
!JКмзсгШа, литоЬлЬ уЫЮ лж plugin "[33m%s[31m". Пиад еЬбадуйЬлЬ дтж plugin
зитзЬа дШ лЬигШлхйЬлЬ лж литожд. ГщйлЬ "[33m%s help[31m" ЪаШ зЬиаййцлЬиЬк
звЮижнжихЬк.!)
[0;1m} T Plugins, user is already running a plugin.


