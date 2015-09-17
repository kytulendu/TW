@ECHO OFF
ECHO. >> LOG.LOG
ECHO =============================================================================== >> LOG.LOG
ECHO. >> LOG.LOG
CD ..
DEL *.EXE
CD SRC
CD COMMON
ECHO Building Common library.
MAKE >> ..\LOG.LOG
ECHO Done!
CD ..
CD SCUW
CD THAISYLS
ECHO Building Thai Syllable Separation library.
MAKE >> ..\..\LOG.LOG
ECHO Done!
CD..
ECHO Building Editor.
MAKE >> ..\LOG.LOG
ECHO Done!
CD ..
CD SCUP
ECHO Building Printer.
MAKE >> ..\LOG.LOG
ECHO Done!
CD ..
CD SCUF
ECHO Building Font Editor.
MAKE >> ..\LOG.LOG
ECHO Done!
CD ..
