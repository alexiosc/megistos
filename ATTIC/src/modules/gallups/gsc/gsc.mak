#
# Borland C++ IDE generated makefile
# Generated 21/09/2000 at 1:26:05 �� 
#
.AUTODEPEND


#
# Borland C++ tools
#
IMPLIB  = Implib
BCCDOS  = Bcc +BccDos.cfg 
TLINK   = TLink
TLIB    = TLib
TASM    = Tasm
#
# IDE macros
#


#
# Options
#
IDE_LinkFLAGSDOS =  -LE:\APPS\BC50\LIB
IDE_BFLAGS = 
LinkerLocalOptsAtDOS_gscdexe =  -c -Tde
ResLocalOptsAtDOS_gscdexe = 
BLocalOptsAtDOS_gscdexe = 
CompInheritOptsAt_gscdexe = -IE:\APPS\BC50\INCLUDE -D__GSC__
LinkerInheritOptsAt_gscdexe = -x
LinkerOptsAt_gscdexe = $(LinkerLocalOptsAtDOS_gscdexe)
ResOptsAt_gscdexe = $(ResLocalOptsAtDOS_gscdexe)
BOptsAt_gscdexe = $(BLocalOptsAtDOS_gscdexe)

#
# Dependency List
#
Dep_gsc = \
   gsc.exe

gsc : BccDos.cfg $(Dep_gsc)
  echo MakeNode

Dep_gscdexe = \
   gsc.h\
   gallups.h\
   io.obj\
   gsc.obj\
   compiler.obj\
   analyze.obj

gsc.exe : $(Dep_gscdexe)
  $(TLINK)   @&&|
 /v $(IDE_LinkFLAGSDOS) $(LinkerOptsAt_gscdexe) $(LinkerInheritOptsAt_gscdexe) +
E:\APPS\BC50\LIB\c0c.obj+
io.obj+
gsc.obj+
compiler.obj+
analyze.obj
$<,$*
E:\APPS\BC50\LIB\emu.lib+
E:\APPS\BC50\LIB\mathc.lib+
E:\APPS\BC50\LIB\cc.lib

|

io.obj :  io.c
  $(BCCDOS) -P- -c @&&|
 $(CompOptsAt_gscdexe) $(CompInheritOptsAt_gscdexe) -o$@ io.c
|

gsc.obj :  gsc.c
  $(BCCDOS) -P- -c @&&|
 $(CompOptsAt_gscdexe) $(CompInheritOptsAt_gscdexe) -o$@ gsc.c
|

compiler.obj :  compiler.c
  $(BCCDOS) -P- -c @&&|
 $(CompOptsAt_gscdexe) $(CompInheritOptsAt_gscdexe) -o$@ compiler.c
|

analyze.obj :  analyze.c
  $(BCCDOS) -P- -c @&&|
 $(CompOptsAt_gscdexe) $(CompInheritOptsAt_gscdexe) -o$@ analyze.c
|

# Compiler configuration file
BccDos.cfg : 
   Copy &&|
-W-
-w
-R
-v
-vi
-H
-H=gsc.csm
-mc
-f
| $@


