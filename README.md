Thai Writer
===========

Descriptions
------------

Thai Writer is a word processor that run from Free-DOS,
M$-DOS, DR-DOS, Novell-DOS or any DOS compatible OSs.
Base on CU-Writer 1.41 by Chulalongkorn University.

My current goal is restructure, re-format, clean up, add comment,
make self document code to the source code for easy to understand what the code do
while make the software not change much from CU-Writer 1.41.

Next is port to OpenWATCOM.

System Requirement
------------------
  * IBM PC or Compatible with 8086 or 8088 CPU, 512 KB RAM or better
  * DOS 3.3 or better
  * Hercules, EGA, VGA, MCGA or AT&T 400 (Graphic card in AT&T PC 6300/Olivetti M24)
  * One or two 5.25" 360Kb floppy disk drive
  * Free hard drive space 700Kb (Optional)
  * 9 pin or 24 pin Dot-Matrix printer (Optional)

License
-------
CU-Writer 1.41 is in [public domain](http://unlicense.org/),
so is this software, but some source code is in other license,
please see source code for detail.

Download
--------
All downloads is in my Google drive, which can be found [here](http://goo.gl/aMYPds)
Include all version of CU-Writer, both DOS and Win16 version that I can find.

Compiling the source code
-------------------------
1. To build this source code you need

   - Borland Turbo C 2.01 or Turbo C++ 1.01 - 3.0 or Borland C++ 2.0 - 5.02
   - OpenWatcom 1.9 or any version of Turbo Assembler

2. Set PATH to Turbo C(++) and (Turbo Assembler) set OpenWatcom environment
3. Change directory to C:\TW\SRC
4. Run MAKE.BAT
5. Binary will go to C:\TW\

Note
----
If you use Turbo Assembler or Borland C++ or the C compilier is in directory
other than C:\TC, you need to edit makefile.

Turbo C 1.5 can compile this code. you must delete -v commandline
in makefile.mak in order to compile with Turbo C 1.5 but TWFONT can't link.

The source code use Thai Industrial Standard 620-2533 (TIS-620)
for character encoding.

Information about CU-Writer
---------------------------
[CU-Writer(in Thai)](http://th.wikipedia.org/wiki/%E0%B8%8B%E0%B8%B5%E0%B8%A2%E0%B8%B9%E0%B9%84%E0%B8%A3%E0%B9%80%E0%B8%95%E0%B8%AD%E0%B8%A3%E0%B9%8C)

CU-Writer developers
--------------------

`สถาบันบริการคอมพิวเตอร์ จุฬาลงกรณ์มหาวิทยาลัย และ ภาควิชาวิศวกรรมคอมพิวเตอร์ คณะวิศวกรรมศาสตร์ จุฬาลงกรณ์มหาวิทยาลัย`

`Computer Service Centre and Faculty of Engineering, Chulalongkorn University`

`สำนวน หิรัญวงษ์		Sumnuan Hirunwong`

`ไกรศร เลียนษี		Kraisorn  Liansee`

`ดำเกิง ธรรมเถกิงกิจ`

`ทศพล อภิกุลวณิช		Thotsapol Aphikulvanich`

`ธณัฎฐ์ จิระกาล		Tanat Chirakarn`

`ประสาท โตปิตุมาตุคุณ	Prasart Topitumatukhun`

`ลักษณ์ชัย ลือชัยชนะกุล`

`วิทยา วงศ์อนวัช		Wittaya Wonganawat`

`สุทธิพงษ์ คนาคกร		Suttipong Kanakakorn`

`สุบรรณ เย็นใจชน		Subun Yenjaichon`

`สุวพจน์ จันทโรจนวงศ์`

...

Thai Writer developer
---------------------
Khral MacCharrver / Khral Steelforge aka. Kytulendu Rrit

Credits
-------
Stone Soup Group for [Fractint](http://www.fractint.org/) 20.0 source code that help me to write some graphic function
Bresenham's line algorithm by [Alois Zingl](http://members.chello.at/~easyfilter/bresenham.html)
