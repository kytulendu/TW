# Change log

## Thai Write 1.0.0
Change from CU Writer 1.41

### Fix/Improvement
- Fix memory leak in SCUW on open file routine.
- Correctly AT&T 6300/Olivetti M24 detection, idea from https://github.com/MobyGamer/TOPBENCH/blob/master/TOPB_DET.PAS.
- Fix when line longer than MAXCOL, type in that line, the edit window will display at line 1 instead of line 5 by increase max column from 266 to 1024.
- Can change directory by select directory in openfile dialog like CU Writer 1.5 or newer.
- Change SCUF the color of cursor for select character for edit to yellow, more visibly on monochrome monitor.
- Speed-up in some graphic routine.
- When use with Hercules graphic card, editor have 90 column instead of 80 column.
- Add No splash screen song argument.

### Misc
- Rename *.PRN to *.P9

### Source Code
- Less warnings and bugs..
- Less code bloat
- Convert some assembly language function to C.
- Add zip backup batch file, use with Info-Zip.
- Directly program CRT controller to set graphic/text mode in Hercules Graphic Card Driver, just for fun =P.

-DWANT_TO_USE_GRAPH and -DCUSTOM_FONT
