# TODO

May change over time.

## Version 1.0.0

- Convert EGAVGA.ASM to C, old assembly language code still in repo.
- Thai-English menu and text message.
- Redo all dialog and text position.
- Write an error handler.
- Check for error when allocate memory, open directory, read/write file, etc.
- Two graphic card for debuging (Hercules as program display and text mode CGA as debug output)

## Version 2.0.0

- OpenWatcom port
- SDL port?

## Version 2.x.x

### Bug fix

- Fix display super-script and sub-script will cut out top or bottom of character

### Feature

**Editing**
- Typographic alignment : left `<Ctrl><O><H>`, right `<Ctrl><O><K>`, and justified `<Ctrl><O><J>`
- Clipboard, copy to clipboard `<Ctrl><[>`, past from clipboard `<Ctrl><]>`
- Multi layer undo like modern editor `<Ctrl><U>`
- Editing more than 2 files
- Not count line that is dot command
- Instant new page when use .PA
- Not detect Thai word order when typing `<Ctrl><O><T>`
- Insert date-time `<Ctrl><Q><D>`
- `<Ctrl><Q><N>` (RW) delete all text
- Can type `kho khuat (ฃ)`, `kho khon (ฅ)`, `lak khang yao (ๅ)`
- Add secondary `<ALT><Fn>` key to insert print control menu (F2-F8)
- Change Thai encoding Kaset-CW/TIS-620 by `<Ctrl><\>`

**Block**
- Use `<Shift><Arrow Key>` to select word (blocks)
- Block select clear formatting
- Column block selection, toggle using `<Ctrl><K><O>` or `<Ctrl><K><N>` (RW),
change size by `<Ctrl><K><+>` (RW) `<Ctrl><K><->` (RW), move by `<Ctrl><K><>>` (RW) `<Ctrl><K><<>` (RW)
- Table creation using column block selection `<Ctrl><K><D>` or `<Ctrl><Q><T>` (RW)
and delete table in block `<Ctrl><Q><U>` (RW)
- Calculate sum of numbers in column block selection `<Ctrl><K><T>` or `<Ctrl><K><M>` (RW)
result can have decimal point or sign depending on the numbers in selection
- Sort text in block `<Ctrl><K><Z>` (RW)

**Interface**
- Online help
- `<Alt><F1>` to display system status, remaining memory and free disk space
- `<Ctrl><O><S>` to toggle display soft space
- `<Ctrl><O><D>` (RW) to toggle display control code
- `<Ctrl><O><M>` to toggle display menu
- `<Ctrl><O><P>` (RW) to set line per page
- Better about dialog (may use bitmap picture)
- Add font editor to menu, when exit the font editor reload the font and redraw screen
- Display Thai character encoding on menu
- `<Ctrl><K><Q>` (RW) to exit program
- `<Ctrl><K><O>` to open file?
- `<Ctrl><J><D>` to change directory?

**Proofing**
- New Thai word separator algorithm by dictionary and by rule (like old one if not enough memory), load dictionary to EMS
- Spell checker/word suggestion, Thai/English, use Thai word separator dictionary
- Thesaurus (English only)

**Printing**
- Support HP PCL5 printer
- Support generic EPSON ESC/P, ESC/P2 printer
- Support Postscript printer
- Support HPGL-compatible plotter?
- Support ASCII Printer
- Print to file
- Can print to any port
- Can print without saving by temporary save document to `.TMP` file at `%TEMP%` and delete it when finish printing

**Hardware support**
- EMS
- CGA, 640x200 pixel, monochrome, require smaller screen font
- Wyse 700, 1280x800 pixel, monochrome, can config to display how many column (80+) like old Hercules driver, see herc_align.patch
- MDSI Genius VHR, 728x1008 pixels, monochrome, http://www.seasip.info/VintagePC/mdsi_genius.html
- SVGA
- VESA
- Thai 8 line text mode

**Misc**
- Multi Thai character encoding/converter/Thai word processing software importer
- Multi font like CU-Writer 1.6, using `<Ctrl><P><n>`?
- Math equations support like CU-Writer 1.6?
- Bitmap graphic support using CWW file format?
- Option at end of file support like CU-Writer 1.6?
