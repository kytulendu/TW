@ECHO OFF
CD ..
DEL *.EXE
CD SRC
CD COMMON
ECHO Building Common library.
MAKE
ECHO Done!
CD ..
CD SCUW
CD THAISYLS
ECHO Building Thai Syllable Separation library.
MAKE
ECHO Done!
CD..
ECHO Building Editor.
MAKE
ECHO Done!
CD ..
CD SCUP
ECHO Building Printer.
MAKE
ECHO Done!
CD ..
CD SCUF
ECHO Building Font Editor.
MAKE
ECHO Done!
CD ..
