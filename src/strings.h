#ifndef STRINGS_H_
#define STRINGS_H_

/* Emacs style mode select: -*- C++ -*- *
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*
* Description: System Information program.
* Author: bejiitas_wrath <johncartwright302@gmail.com>
* Created at: Thu Oct 12 23:11:06 EST 2006
* Computer: deusexmachina
* System: Linux deusexmachina 2.6.27-14
*
* Copyright See COPYING file that comes with this distribution.
*
********************************************************************/

/* * I got the idea for this from sdldoom. Very nice indeed. */

enum { VERSION = 176 };
#define SYSINFO "Sysinfo version v%i.%i"

const char *p = "System Information Program";
char ver[128];

void print_menu() {
	printf("\tSysinfo. %s\n\n", p);

	printf("1 - Kernel Information.\n2 - Memory & processes.\n");
	printf("3 - CDROM Information.\n4 - View list of sound cards.\n");
	printf("5 - View Real Time Clock Information.\n");
	printf("6 - View motherboard and BIOS information.\n");
	printf("7 - View information about your Xorg display.\n");
	printf("8 - View information about your IP addresses.\n");
	printf("9 - View user information easily.\n");

	sprintf (ver, SYSINFO, VERSION / 100, VERSION % 100);

	printf("\n%s, by John Cartwright 2007.\nsysinfo comes with ", ver);
	printf("ABSOLUTELY NO WARRANTY. This\n is open source software,");
	printf("and you are welcome to \nredistribute it under certain ");
	printf("conditions as \noutlined in the GNU Public License.\n\n");
	exit(0);
}

#endif
