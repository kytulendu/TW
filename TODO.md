#TODO
May change over time.

##Version 1.0.0
- Bugs fix
- Remove unused stuff
- More Comment
- Cleanup
- Removal of gotos in rdfiletospace function in SCUW\BLOCK.C.
- Convert most of assembly language function to C.
- Redo all dialog and text position.

##Version 1.0.1
- Release

## Version 2.0.0
- OpenWatcom port?
- SDL port?

## Version 2.1.0
- Some re-factoring/re-architect
- Rework main loop

## Version 2.x.x

###Fix/Improvement
- Fix display super-script and sub-script will cut out top or bottom of character
- check for error when allocate memory, open directory, read/write file, etc.
- write an error handler.

###Hardware support
- EMS/XMS
- Mouse support for select menu and select text
- Colors?
- CGA, 640x200 pixel, monochrome
- Wyse 700, 1280x800 pixel, monochrome, can config to display how many column (80+) like old Hercules driver, see herc_align.patch
- SVGA
- VESA

###Printer
- Support HP PCL5 printer
- Support generic EPSON ESC/P, ESC/P2 printer
- Support Postscript printer
- Support ASCII Printer
- Print to file
- Can print to any port

###Feature

Editing
- New English word wrap algorithm based on Knuth's algorithm (use in TeX)?
- New Thai word separator algorithm by dictionary and by rule (like old one if not enough memory), CTTEX, load dictionary to EMS/XMS
- Typographic alignment : left, Center, right, and justified
- Use `<Shift><Arrow Key>` to select word (blocks)
- Use `<Ctrl><B>` for bold character, `<Ctrl><I>` for italic character, `<Ctrl><U>` for underline character?
- Clipboard
- Multi layer undo like modern editor
- Block select clear formatting
- Editing more than 2 files
- Not count line that is dot command
- Instant new page when use .PA ?
- Not detect Thai word order when typing `<Ctrl><U><T>`
- Insert date-time `<Ctrl><U><D>`
- Delete from cursor position to end of line

Proofing
- Hyphenation
- Spell checker/word suggestion, Thai/English, use Thai word separator dictionary
- Thesaurus (English only)

Interface
- Re-made menu to like WS7 or modern software
- Thai-English menu but likely all English menu
- Heelllppp!!!!
- `<Alt><F1>` system status, remaining memory, etc.
- Better about dialog (may use picture)
- More beautiful UI?

Misc
- Multi Thai character encoding/converter, RW KU code, Thai EBDIC, etc.
- Change Thai encoding CW KU / CW TIS-620 by use `<Ctrl><\>`
- Invert character
- Double-high character?
- Strike through character
- Print a character over other character
