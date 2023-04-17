/**
@file sysinfo.cpp
*/

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

//#include <linux/unistd.h>       /* for _syscallX macros/related stuff */
#include <linux/kernel.h>       /* for struct sysinfo */
#include <sys/sysinfo.h>        /* For the sysinfo struct. */
#include <syscall.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <sys/statvfs.h>

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/extensions/Xinerama.h>
#include <pwd.h>

#include "sysinfo.h"
#include "strings.h"
#include "iface.h"

int main(int argc, char **argv)
{
	struct utsname uname_pointer;
	char* myarg1 = argv[1];

	int statvfs(const char *path, struct statvfs *buf);
	int fstatvfs(int fd, struct statvfs *buf);

	if (!argc or !myarg1) {
		print_menu();

		//testing();
	}

	if (argc > 1 and strncmp(argv[1], "1", BUF) == 0) {
/* * The utsname function: */
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
		printf ("Amount of swap space remaining: %ld\n", si.freeswap);
		printf ("Total amount of swap space: %ld\n", si.totalswap);

        printf("This system has %d processors configured and %d processors \
            available.\n", get_nprocs_conf(), get_nprocs());
	}

	if (argc > 1 and strncmp(argv[1], "3", BUF) == 0) {
		printf("\t\tDisk space information.\n");

		const unsigned int GB = (1024 * 1024) * 1024;
		struct statvfs buffer;
		//int ret = statvfs("/", &buffer);

        const double total = (double)(buffer.f_blocks * buffer.f_frsize) / GB;
        const double available = (double)(buffer.f_bfree * buffer.f_frsize) / GB;
        const double used = total - available;
        const double usedPercentage = (double)(used / total) * (double)100;
		printf("Disk space on / in Gigabytes.\n\n");
        printf("Total: %f --> %.0f GB.\n", total, total);
        printf("Available: %f --> %.0f GB.\n", available, available);
        printf("Used: %f --> %.1f GB.\n", used, used);
        printf("Used Percentage: %f --> %.0f %%\n", usedPercentage, usedPercentage);

	}

	if (argc > 1 and strncmp(argv[1], "4", BUF) == 0) {
		printf("\t\tSound Card information.\n");

		kernel("/proc/asound/cards", 3);
	}

	if (argc > 1 and strncmp(argv[1], "5", BUF) == 0) {
		printf("\t\tReal Time Clock information.\n");
		kernel("/proc/driver/rtc", 3);
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
		Display *d;
		int i, n;
		Display *display = XOpenDisplay(NULL);
		d = XOpenDisplay (NULL);
		if (!d) {
			printf ("display is null!\n");
			return 1;
		}

		int screenCount = ScreenCount(display);

		n = ScreenCount (d);
		printf ("screen count: %d; default screen: %d\n", n, DefaultScreen (d));
		for (i = 0; i < n; i++)
			printf ("[screen %d] width=%d height=%d\n", i, DisplayWidth (d, i), DisplayHeight (d, i));

		if (XineramaIsActive (d)) {

			XineramaScreenInfo *screens;
			int num_screens;

			screens = XineramaQueryScreens (d, &num_screens);
			printf ("There are %d monitor(s) connected to your computer.\n", num_screens);

			for (i = 0; i < num_screens; i++)
				printf ("[screen %d] x_org=%hd y_org=%hd width=%hd height=%hd\n", i, screens[i].x_org, screens[i].y_org, screens[i].width, screens[i].height);

		} else {
			printf ("Xinerama is NOT active.\n");
		}

		XCloseDisplay(display);
	}

	if (argc > 1 and strncmp(argv[1], "8", BUF) == 0) {
		printf("\t\tIP information.\n");
                iface();
	}

	if (argc > 1 and strncmp(argv[1], "9", BUF) == 0) {

	        struct passwd *passwd;
	        passwd = getpwuid ( getuid());

	        fprintf(stdout, "\t\tUser information.\n\n");
            	fprintf(stdout, "The Login Name is: %s\n", passwd->pw_name);
	        fprintf(stdout, "The Login shell is: %s\n", passwd->pw_shell);
	        fprintf(stdout, "The Login /home is: %s\n", passwd->pw_dir);
	        fprintf(stdout, "The user information is: %s\n", passwd->pw_gecos);
        }
	return 0;
}


