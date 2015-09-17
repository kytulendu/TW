@ECHO OFF
CD ..
DEL TW.EXE
CD SRC
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
