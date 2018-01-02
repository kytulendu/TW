# Change log

## Thai Write 1.0.0
Change from CU Writer 1.41

### Improvement
- Can change directory by select directory in openfile dialog like CU Writer 1.5 or newer.
- Speed-up in some graphic routine.
- When use with Hercules graphic card, editor can display 90 column or 80 column.
- Add No splash screen song argument.
- Return to original text mode after exit graphic mode.
- Change SCUF the color of cursor for select character for edit to yellow, more visibly on monochrome monitor.

### Fix
- Fix memory leak in SCUW on open file routine.
- Correct AT&T 400 line display detection, idea from https://github.com/MobyGamer/TOPBENCH/blob/master/TOPB_DET.PAS.
- Fix when line longer than MAXCOL, type in that line, the edit window will display at line 1 instead of line 5 by increase max column from 266 to 1024.
- Fix when use delete character to end of line function key it insert special character instread.

### Misc
- Rename *.PRN to *.P9

### Source Code
- Less compile warnings and bugs.
- Remove the evil gotos.
- Less code bloat.
- Convert some assembly language function to C.
- Add zip backup batch file, use with Info-Zip.
- Directly program CRT controller to set graphic/text mode in Hercules Graphic Card Driver, just for fun =P.
