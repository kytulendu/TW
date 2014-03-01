Thai Writer
===========

Descriptions
============

Thai Writer is a word processor that run from Free-DOS,
M$-DOS, DR-DOS, Novell-DOS or any DOS compatible OSs.
Base on CU-Writer 1.41.

License
=======

CU-Writer 1.41 is in [public domain](http://unlicense.org/),
so this software is released in to public domain too.

Download
========
All downloads is in my Google drive, which can be found [here](https://drive.google.com/folderview?id=0B0EZlcQoXgS1TlMxRF9EYkM4MVk&usp=sharing)
Include all version of CU-Writer, both DOS and Win16 version that I can find.

Compiling the source code
=========================

1. To build this source code you need

   - Turbo C 2.01 or Borland/Turbo C++ 1.01 or better
   - OpenWatcom 1.9 or any version of Turbo Assembler

2. Set PATH to Turbo C(++) and (Turbo Assembler) set OpenWatcom environment
3. Change directory to C:\TW\SRC
4. Run MAKE.BAT
5. Binary will go to C:\TW\

Note
====

If you use Turbo Assembler or the C compilier is in other than C:\TC
you need to edit makefile.

Turbo C 1.5 can compile this code. you must delete -v commandline
in makefile.mak in order to compile with Turbo C 1.5 but TWFONT can't link.

The source code use Thai Industrial Standard 620-2533 (TIS-620)
for character encoding.

Information about CU-Writer
===========================

[CU-Writer(Thai)](http://th.wikipedia.org/wiki/%E0%B8%8B%E0%B8%B5%E0%B8%A2%E0%B8%B9%E0%B9%84%E0%B8%A3%E0%B9%80%E0%B8%95%E0%B8%AD%E0%B8%A3%E0%B9%8C)

ผู้พัฒนาซียูไรเตอร์
===========
สถาบันบริการคอมพิวเตอร์ จุฬาลงกรณ์มหาวิทยาลัย และ ภาควิชาวิศวกรรมคอมพิวเตอร์ คณะวิศวกรรมศาสตร์ จุฬาลงกรณ์มหาวิทยาลัย

สำนวน หิรัญวงษ์

ไกรศร เลียนษี
ดำเกิง ธรรมเถกิงกิจ
ทศพล อภิกุลวณิช
ธณัฎฐ์ จิระกาล
ประสาท โตปิตุมาตุคุณ
ลักษณ์ชัย ลือชัยชนะกุล
วิทยา วงศ์อนวัช
สุทธิพงษ์ คนาคกร
สุบรรณ เย็นใจชน
สุวพจน์ จันทโรจนวงศ์

Thai Writer developer(s)
========================

Khral MacCharrver / Khral Steelforge (Kytulendu Rrit)

Credits
=======
Stone Soup Group for [Fractint](http://www.fractint.org/) 20.0 source code that help me to write some graphic function
Bresenham's line algorithm by [Alois Zingl, Vienna, Austria](http://members.chello.at/~easyfilter/bresenham.html)
