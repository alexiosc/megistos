LEVEL3 {}

VISUAL {[0;30;47m 旼컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 [34mDialog Box[0;30;47m 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�[0;1;37;47m� [0m
[30;47m �                                                                          [0;1;47;37m� [0m
[30;47m �  This is a string field      [1;44;37m@80;40;0s[0;1;47;37m  � [0m
[30;47m �                                                                          [0;1;47;37m� [0m
[30;47m �  Another string field        [1;44;37m@40;40;1s[0;1;47;37m  � [0m
[30;47m �                                                                          [0;1;47;37m� [0m
[30;47m �  Password entry field        [1;44;37m@8;8;2s[0;1;47;37m                                  � [0m
[30;47m �                                                                          [0;1;47;37m� [0m
[30;47m �  Number entry field #1       [1;37;44m@10;1;32767;0n[0;47;30m                     (1-32767)[0;1;47;37m  � [0m
[30;47m �                                                                          [0;1;47;37m� [0m
[30;47m �  Number entry field #2       [1;37;44m@10;1;32767;1n[0;47;30m                     (1-32767)[0;1;47;37m  � [0m
[30;47m �                                                                          [0;1;47;37m� [0m
[30;47m �  Computer make and model     [0;30;46m @13;"IBM PC 8086|IBM AT 80286|IBM i386|IBM i486|IBM P5|Amiga 500|Amiga 600|Amiga 1200|Amiga (other)|Atari ST|Atari Falcon"l [0;47;30m      (Space,+,- to change)[0;1;47;37m  � [0m
[30;47m �                                                                          [0;1;47;37m� [0m
[30;47m �  Useless check box           [0;30;46m [@"X "t] [0;47;30m                    (Space to toggle)  [0;1;47;37m� [0m
[30;47m �                                                                          [0;1;47;37m� [0m
[30;47m �  Ctrl-Q: Cancel  Ctrl-S: Ok                                              [0;1;47;37m� [0m
[30;47m �  Ctrl-L: Redraw  Ctrl-X: Line    [0;1;42;33m@14;"OK"b[0;47;30m�    [0;1;41;33m@14;"Cancel"b[0;47;30m�  [0;1;47;37m� [0m
[30;47m �  Ctrl-R: Help                     賽賽賽賽賽賽賽賽     賽賽賽賽賽賽賽賽  [0;1;47;37m� [0m
[30;47m �[0;1;37;47m컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴� [0m} T Visual template example


LINEAR {[2J[0;30;47m 旼컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�[0;1;37;47m� [0m
[30;47m � Linear data entry session                                                [0;1;47;37m� [0m
[30;47m � 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴 [0;1;47;37m� [0m
[30;47m � [31m1[30m. String field:                [34m@80;40;0s [0;1;47;37m� [0m
[30;47m � [31m2[30m. Another string field:        [34m@40;40;1s [0;1;47;37m� [0m
[30;47m � [31m3[30m. Password:                    [34m@8;8;2s                                 [0;1;47;37m� [0m
[30;47m � [31m4[30m. Number entry field #1:       [34m@10;1;32767;0n                               [0;1;47;37m� [0m
[30;47m � [31m5[30m. Number entry field #2:       [34m@10;1;32767;1n                               [0;1;47;37m� [0m
[30;47m � [31m6[30m. Computer make and model:     [34m@13;"IBM PC 8086|IBM AT 80286|IBM i386|IBM i486|IBM P5|Amiga 500|Amiga 600|Amiga 1200|Amiga (other)|Atari ST|Atari Falcon"l                            [0;1;47;37m� [0m
[30;47m � [31m7[30m. Useless feature:             [34m@"X "t                                      [0;1;47;37m� [0m
[30;47m �                                                                          [0;1;47;37m� [0m
[30;47m � [31m0[30m. Done.@14;"0OK"b                                                                 [0;1;47;37m� [0m
[30;47m � [31mX[30m. Cancel.@14;"XCancel"b                                                               [0;1;47;37m� [0m
[30;47m �[0;1;37;47m컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴� [0m
} T Linear template example


FIELD1 {[0;1m
!WThis field does this and that and it's important for this and that
reason. Enter up to 80 characters for this field.!)
} T Linear prompt #1


FIELD2 {[0;1m
!WThis should provide help on this field, only the field doesn't really DO
anything. Enter up to 40 characters for this field.!)
} T Linear prompt #2


FIELD3 {[0;1m
!WEnter up to 8 characters for this password field (asterisks will echo).!)
} T Linear prompt #3


FIELD4 {[0;1m
!WA general-purpose numeric field (left-justified)!)
} T Linear prompt #4


FIELD5 {[0;1m
!WA general-purpose numeric field (right-flushed)!)
} T Linear prompt #4


FIELD6 {} T Linear prompt #5

FIELD7 {} T Linear prompt #5
