#TODO

##Version 1.0

###Fix/Improvement
- Bugs fix
- Remove unused stuff
- More Comment
- Convert some assembly language function to C
- Remove gotos in rdfiletospace function in SCUW\BLOCK.C

##Version 1.1
- Final version

## Version 2.0
- OpenWatcom port
- Refactoring/re-architech

## Version 2.x

###Fix/Improvement
- Fix display super-script and sub-script will cut out top or bottom of character
- check when allocate memory, open directory, read/write file, etc.
- write an error handlerer.

###Hardware support
- EMS/XMS
- Mouse support for select menu and select text
- Primitive GUI
- Colors graphic?
- CGA, 640x200 pixel, monochrome
- Hercules, can config to display 80 or 90 column
- Wyse 700, 1280x800 pixel, monochrome, can config to display how many column (80+) like old Hercules driver, see herc_align.patch
- IBM8514, 640x480 pixel, 256 colors
- SVGA
- VESA

###Printer
- Support generic HP PCL5e, EPSON ESC/P, ESC/P2 printer
- HP LASER Compatible

###Feature
- Re-made menu to like WS7 or modern software
- Thai-English menu but likely all english menu
- New English word wrap algorithm from TeX aka. Knuth's algorithm
- New Thai word separator algorithm by dictionary and by rule, CTTEX, load dictionary to EMS/XMS
- Hyphenation, Thesaurus (English only), spell checker/word suggestion, Thai/English, use Thai word separator dictionary
- Typographic alignment : Center, left, right, flush left, ragged right and justified
- Heelllppp!!!!
- Column block, can change it's size
- Block select clear formating
- Use Shift+Arrow key to select word (blocks)
- Convert to use with MacThai and WinThai (insert soft hypen between words, require better word separator algorithm)
- Multi Thai character encoding/converter, RW KU code, Thai EBDIC, etc.
- Change Thai encoding CW KU / CW TIS-620 by use `<Ctrl><\>`
- Invert character
- Double-hight character?
- Insert date-time `<Ctrl><U><D>`
- Not count line that is dot command
- Not detect Thai word order when typing `<Ctrl><U><T>`
- Instant new page when use .PA
- Undo like modern editor
- Print a character over other character
- Picture support, print
- Print while editing
- Editing more than 2 files
- Clipboard
- `<Alt><F1>` system status, remaining memory, etc.
- Better about dialog (may use picture)
- Some other feature of Word RAMA and later version of CW and CWW
