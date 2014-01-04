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
* Author: bejiitas_wrath <johncartwright302@hotmail.com>
* Created at: Thu Oct 12 23:11:06 EST 2006
* Computer: deusexmachina
* System: Linux deusexmachina 2.6.27-14
*
* Copyright See COPYING file that comes with this distribution.
*
********************************************************************/

#include <linux/unistd.h>       /* for _syscallX macros/related stuff */
#include <linux/kernel.h>       /* for struct sysinfo */
#include <sys/sysinfo.h>        /* For the sysinfo struct. */
#include <syscall.h>
#include <sys/utsname.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "sysinfo.h"
#include "strings.h"

int main(int argc, char **argv)
{
	struct utsname uname_pointer;
	char* myarg1 = argv[1];
	static char Args[256];
	char buf[256];

	if (!argc or !myarg1)
		print_menu();

	if (argc > 1 and strncmp(argv[1], "1", BUF) == 0) {
/*
* The utsname function:
*/
		uname(&uname_pointer);
		if (strlen (uname_pointer.domainname) < 7 or
		    strncmp(uname_pointer.domainname, "(none)", 10) == 0) {
			printf ("System name : %s \n"		\
				"Nodename    : %s \n"		\
				"Release     : %s \n"		\
				"Version     : %s \n"		\
				"Machine     : %s \n\n",
				uname_pointer.sysname,
				uname_pointer.nodename,
				uname_pointer.release,
				uname_pointer.version,
				uname_pointer.machine
				);
		} else {
			printf ("System name : %s \n"		\
				"Nodename    : %s \n"		\
				"Release     : %s \n"		\
				"Version     : %s \n"		\
				"Machine     : %s \n"		\
				"Domain Name : %s \n\n",
				uname_pointer.sysname,
				uname_pointer.nodename,
				uname_pointer.release,
				uname_pointer.version,
				uname_pointer.machine,
				uname_pointer.domainname
			);
		}
	}

	if (argc > 1 and strncmp(argv[1], "2", BUF) == 0) {
		printf("\t\tSystem information.\n");

		/* This code from:
		 * http://stackoverflow.com/questions/14345937/sysinfo-returns-incorrect-value-for-freeram-even-with-mem-unit
		 */
		/* Conversion constants. */
		const long minute = 60;
		const long hour = minute * 60;
		const long day = hour * 24;
		const double megabyte = 1024 * 1024;

		/* Obtain system statistics. */
		struct sysinfo si;
		sysinfo (&si);

		/* Summarize interesting values. */
		printf ("System uptime : %ld days, %ld:%02ld:%02ld\n", 
		    si.uptime / day, (si.uptime % day) / hour, 
		    (si.uptime % hour) / minute, si.uptime % minute);
		printf ("Total RAM   : %5.1f MB\n", si.totalram / megabyte);
		printf ("Free RAM   : %5.1f MB\n", si.freeram / megabyte);
		printf ("Number of running processes : %d\n", si.procs);

		/* Print the number of CPU cores available. */
		system("echo \"The computer has $(cat /proc/cpuinfo | grep CPU | wc -l) core(s).\"");
		system("echo \"The CPU is running at: $(cat /sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq) HZ.\"");

	}

	if (argc > 1 and strncmp(argv[1], "3", BUF) == 0) {
		printf("\t\tCdrom drive information.\n");


//		kernel("/proc/sys/dev/cdrom/info", 5);

		strncpy(Args, "/proc/sys/dev/cdrom/info", 24);
		sprintf(buf, "cat %s\n", Args);
		fflush(stdout);
		system(buf);

	}

	if (argc > 1 and strncmp(argv[1], "4", BUF) == 0) {
		printf("\t\tSound Card information.\n");
//		kernel("/proc/asound/cards", 3);

		strncpy(Args, "/proc/asound/cards", 19);
		sprintf(buf, "cat %s\n", Args);
		fflush(stdout);
		system(buf);
	}

	if (argc > 1 and strncmp(argv[1], "5", BUF) == 0) {
		printf("\t\tReal Time Clock information.\n");
//		kernel("/proc/driver/rtc", 3);

		strncpy(Args, "/proc/driver/rtc", 16);
		sprintf(buf, "cat %s\n", Args);
		fflush(stdout);
		system(buf);

	}

	if (argc > 1 and strncmp(argv[1], "6", BUF) == 0) {

		printf("\t\tMotherboard & BIOS information.\n");
		printf("--BIOS date: ");
		kernel("/sys/class/dmi/id/bios_date", 3);
		printf("--BIOS vendor: ");
		kernel("/sys/class/dmi/id/bios_vendor", 3);
		printf("--Motherboard name: ");
		kernel("/sys/class/dmi/id/board_name", 3);
		printf("--Motherboard vendor: ");
		kernel("/sys/class/dmi/id/board_vendor", 3);
	}

	if (argc > 1 and strncmp(argv[1], "7", BUF) == 0) {
		printf("\t\tXorg information.\n");
		system("echo \"The screen is set to these$(xdpyinfo  | grep 'dimensions:').\"");
		system("echo \"The fonts are set to this$(xdpyinfo  | grep 'resolution:').\"");

	}

	return 0;
}
