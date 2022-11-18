# TODO

May change over time.

## Version 1.0.0

- Convert most of assembly language function to C.
- Thai-English menu and text message.
- Redo all dialog and text position.
- Write an error handler.
- Check for error when allocate memory, open directory, read/write file, etc.
- Two graphic card for debuging (Hercules as program display and textmode CGA as debug output)

## Version 1.0.1

- Release

## Version 2.0.0

- OpenWatcom port
- SDL port?

## Version 2.x.x

### Fix/Improvement

- Fix display super-script and sub-script will cut out top or bottom of character

### Feature

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
- Instant new page when use .PA
- Not detect Thai word order when typing `<Ctrl><U><T>`
- Insert date-time `<Ctrl><U><D>`
- Delete from cursor position to end of line

Proofing
- Spell checker/word suggestion, Thai/English, use Thai word separator dictionary
- Thesaurus (English only)

Printing
- Support HP PCL5 printer
- Support generic EPSON ESC/P, ESC/P2 printer
- Support Postscript printer
- Support ASCII Printer
- Print to file
- Can print to any port

Hardware support
- EMS/XMS
- CGA, 640x200 pixel, monochrome, require smaller sccreen font
- Wyse 700, 1280x800 pixel, monochrome, can config to display how many column (80+) like old Hercules driver, see herc_align.patch
- MDSI Genius VHR, 728x1008 pixels, monochrome, http://www.seasip.info/VintagePC/mdsi_genius.html
- SVGA
- VESA
- Thai 8 line and 25 line text mode

Interface
- Re-made menu to like Word Star 7 or modern software
- Help
- `<Alt><F1>` to display system status, remaining memory, etc.
- Better about dialog (may use bitmap picture)

Misc
- Multi Thai character encoding/converter, RW KU code, Thai EBDIC, etc.
- Change Thai encoding CW KU / CW TIS-620 by use `<Ctrl><\>` key
- Find a way to reduce memory usuage
- Multi font like CU-Writer 1.6
