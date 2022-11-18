Thai Write
==========

![Thai Write](screen.png)

Descriptions
------------
Thai Write is a word processor that run on Free-DOS,
M$-DOS, DR-DOS, Novell-DOS or any DOS compatible OSs.
Base on [CU Writer](http://th.wikipedia.org/wiki/%E0%B8%8B%E0%B8%B5%E0%B8%A2%E0%B8%B9%E0%B9%84%E0%B8%A3%E0%B9%80%E0%B8%95%E0%B8%AD%E0%B8%A3%E0%B9%8C) 1.41 which is a clone of WordStar,
by Computer Service Center and Faculty of Engineering, Chulalongkorn University.

The original source code for CU Writer is found found on a ftp server
ftp://ftp.cs.washington.edu/pub/thaisys/software/dos/cu-writer/
and also on [here](https://github.com/kytulendu/CW141).

My current goal is restructure, re-format, clean up, add comment,
make self document code to the source code for easy to understand what the code do
while make the software not change much from CU Writer 1.41.

Next is port to OpenWATCOM.

System Requirement
------------------
System requirement may change in the future.

  * IBM PC or Compatible, 8086 or 8088 CPU, 512 KB RAM or better
  * DOS 3.3 or better
  * Hercules, EGA, VGA, MCGA or AT&T 400 (Graphic card in AT&T PC 6300/Olivetti M24, Compaq Portable III)
  * Two 5.25" 360KB or one 5.25" 1.2MB or one 3.5" 720KB or one 3.5" 1.44MB floppy disk drive.
  * 700KB free hard drive space (Optional)
  * 9 pin or 24 pin Dot-Matrix printer (Optional)

Download
--------
All downloads can be found [here](https://github.com/kytulendu/TW/releases).

Compiling the source code
-------------------------
This code have been build using Borland C++ 3.1 and OpenWatcom 1.9.

1. To build this source code you need

   - Borland Turbo C 1.5 - 2.01 or Turbo C++ 1.0/1.01 - 3.0
     or Borland C++ 2.0 - 5.02
   - OpenWatcom 1.9 or any version of Turbo Assembler

2. Set PATH to Turbo C(++) and (Turbo Assembler) set OpenWatcom environment
3. Change directory to C:\TW\SRC
4. Run MAKE.BAT
5. Binary will go to C:\TW\

Available preprocessor

1. -DWANT_TO_USE_GRAPH Enable unfinished graphic cupport.
2. -DEDA_VERSION for compile special version for use with ATi EGA Wonder?
(detect as EGA but display Hercules graphic mode)
3. -DCW_VERSION for compile with CU-Writer 1.41 version information.
4. -DCUSTOM_FONT

Note
----
If you use Turbo C/C++ or Turbo Assembler or Borland C++ or the C compilier is
in directory other than C:\BC, you need to edit makefile.

The source code use Thai Industrial Standard 620-2533 (TIS-620) for character encoding.

CU Writer developers
--------------------
From CU-Writer 1.2 manual and CU-Writer 1.41 source code.

* สถาบันบริการคอมพิวเตอร์ จุฬาลงกรณ์มหาวิทยาลัย และ ภาควิชาวิศวกรรมคอมพิวเตอร์ คณะวิศวกรรมศาสตร์ จุฬาลงกรณ์มหาวิทยาลัย
(Computer Service Centre and Faculty of Engineering, Chulalongkorn University)
* สำนวน หิรัญวงษ์
(Sumnuan Hirunwong)
* ไกรศร เลียนษี
(Kraisorn  Liansee)
* ดำเกิง ธรรมเถกิงกิจ
* ทศพล อภิกุลวณิช
(Thotsapol Aphikulvanich)
* ธณัฎฐ์ จิระกาล
(Tanat Chirakarn)
* ประสาท โตปิตุมาตุคุณ
(Prasart Topitumatukhun)
* ลักษณ์ชัย ลือชัยชนะกุล
* วิชัย ปฏิภาภรณ์
(Wichai Patipaporn)
* วิทยา วงศ์อนวัช
(Wittaya Wonganawat)
* สุทธิพงษ์ คนาคกร
(Suttipong Kanakakorn)
* สุบรรณ เย็นใจชน
(Subun Yenjaichon)
* สุวพจน์ จันทโรจนวงศ์

If you know any one who is in CU-Writer project that isn't in this list,
please in inform me. :)

Thai Write developer
--------------------
Khralkatorrix

Credits
-------
Stone Soup Group's [Fractint](http://www.fractint.org/) 20.0 source code
that help me to studies how to do graphic in DOS.

Bresenham's line algorithm by [Alois Zingl](http://members.chello.at/~easyfilter/bresenham.html)

License
-------

    Thai Write, A DOS word processor.
    Copyright (C) 2014-2022 Khralkatorrix <https://github.com/kytulendu>.

    CU Writer
    Copyright (C) 1989-1993 Chulalongkorn University.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

Although, CU Writer 1.41 is in [public domain](http://unlicense.org/)
as described in [Wikipedia]((http://th.wikipedia.org/wiki/%E0%B8%8B%E0%B8%B5%E0%B8%A2%E0%B8%B9%E0%B9%84%E0%B8%A3%E0%B9%80%E0%B8%95%E0%B8%AD%E0%B8%A3%E0%B9%8C)),
but I'd like to add copyright for Chulalongkorn University anyway.

Thai Write is released under [GPL v3](http://www.gnu.org/licenses/gpl-2.0.html),
some source code is in other license, please see source code for detail.
