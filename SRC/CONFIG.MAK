# Compiler configuration

# Assembler
#======================================

# Watcom Assembler
ASM = WASMR
ASMFLAGS = -zq -wx -ml

# Borland Turbo Assembler
#ASM = TASM
#ASMFLAGS = /w2/z/zi/mx

# C Compilier
#======================================

# Borland C++
CC = BCC
CCFLAGS = -c -w -ml -d -f- -K
INCLUDEPATH = C:\BC\INCLUDE;..\COMMON

# Borland Turbo C or C++
#CC = TCC
#CCFLAGS = -c -w -ml -d -f- -K
#INCLUDEPATH = C:\TC\INCLUDE;..\COMMON

#======================================

LINKER = TLINK
LINKERFLAGS = /x/d/c

# Unused yet
LIBPATH = C:\BC\LIB
