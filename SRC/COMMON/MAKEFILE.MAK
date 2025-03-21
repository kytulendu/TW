#
# makefile for common object file
#

!include "..\CONFIG.MAK"

CCFLAGS1 = $(CCFLAGS) -I$(INCLUDEPATH)

PROJECT: EGAVGA.OBJ HERC.OBJ ATT400.OBJ ACOMMON.OBJ CCOMMON.OBJ\
        GRDETECT.OBJ CWGRPHC.OBJ CWEGRPH.OBJ CWAGRPH.OBJ \
        EKBD.OBJ CSCRN.OBJ FILEUTIL.OBJ DIR.OBJ SOUND.OBJ CUSONG.OBJ \
        GETSTR.OBJ TUTIL1.OBJ KBD.OBJ

EGAVGA.OBJ: EGAVGA.ASM
    $(ASM) $(ASMFLAGS) EGAVGA.ASM

HERC.OBJ: HERC.ASM
    $(ASM) $(ASMFLAGS) HERC.ASM

ATT400.OBJ: ATT400.ASM
    $(ASM) $(ASMFLAGS) ATT400.ASM

ACOMMON.OBJ: ACOMMON.ASM
    $(ASM) $(ASMFLAGS) ACOMMON.ASM

CCOMMON.OBJ: CCOMMON.C
    $(CC) $(CCFLAGS1) CCOMMON.C

GRDETECT.OBJ: GRDETECT.C GRDETECT.H
    $(CC) $(CCFLAGS1) GRDETECT.C

CWGRPHC.OBJ: CWGRPHC.C CWGRPHC.H GRDETECT.H
    $(CC) $(CCFLAGS1) CWGRPHC.C

CWEGRPH.OBJ: CWEGRPH.C CWGRPHC.H
    $(CC) $(CCFLAGS1) -Ox CWEGRPH.C

CWAGRPH.OBJ: CWAGRPH.C CWGRPHC.H
    $(CC) $(CCFLAGS1) -Ox CWAGRPH.C

EKBD.OBJ: EKBD.C
    $(CC) $(CCFLAGS1) EKBD.C

CSCRN.OBJ: CSCRN.C
    $(CC) $(CCFLAGS1) -Ox CSCRN.C

FILEUTIL.OBJ: FILEUTIL.C
    $(CC) $(CCFLAGS1) FILEUTIL.C

DIR.OBJ: DIR.C
    $(CC) $(CCFLAGS1) DIR.C

SOUND.OBJ: SOUND.C
    $(CC) $(CCFLAGS1) SOUND.C

CUSONG.OBJ: CUSONG.C
    $(CC) $(CCFLAGS1) CUSONG.C

GETSTR.OBJ: GETSTR.C
    $(CC) $(CCFLAGS1) GETSTR.C

TUTIL1.OBJ: TUTIL1.C
    $(CC) $(CCFLAGS1) TUTIL1.C

KBD.OBJ: KBD.C
    $(CC) $(CCFLAGS1) KBD.C
