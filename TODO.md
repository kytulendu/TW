#TODO
May change over time.

##Version 1.0.0
- Convert most of assembly language function to C.
- Redo all dialog and text position.
- Thai-English menu and text message.
- Detect ATT400 internal plasma monitor for old portable and laptop that have CGA 640x400 mode.
Like Compaq Portable III, GridCase 286, GridCase 386.

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
- Spell checker/word suggestion, Thai/English, use Thai word separator dictionary
- Thesaurus (English only)

Interface
- Re-made menu to like WS7 or modern software
- Heelllppp!!!!
- `<Alt><F1>` system status, remaining memory, etc.
- Better about dialog (may use picture)

Misc
- Multi Thai character encoding/converter, RW KU code, Thai EBDIC, etc.
- Change Thai encoding CW KU / CW TIS-620 by use `<Ctrl><\>`

