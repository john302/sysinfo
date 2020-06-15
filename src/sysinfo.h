#ifndef SYSINFO_H_
#define SYSINFO_H_

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

#define BUF 0x05

/*
 * Function prototypes. Sexy... And unlike on the show '24', function
 * prototypes have nothing to to with hard disk sectors!
 */

void kernel(char,int);

/*
 *  @brief  /proc file opener
 *  @param  File  An output stream.
 *  @param  len  A string length.
 *  @return  none.
 *  @pre  @a len must be a non-NULL int.
 * I hope this little function is not offending anyone. it is the only
 * way I could think to have a single function that would be able to 
 * load the different files quickly and without fuss. And it works just
 * fine, and that is what matters in the end.
 */

struct _kern1 {
	char *File;
	int len;
	char Kyo[40];
} *kern1 = (struct _kern1 *) 0x80;

void kernel(const char *File, int len)
{
	FILE *f;
	char Kyo[40];

	if (len > 10 or len < 2)
		return;

	f = fopen(File, "r");
	if(!f) {
		printf ("Sorry, I cannot open: %s.\n", File);
		printf("Please check your permissions with\n"	\
			"your supervisor. The feature may not\n"	\
			"be compiled and\\or enabled in your\n"		\
			"kernel version. Or a scsi device, eg,\n"	\
			"a USB drive may not be attached.\n");
		return;
	} else {
/* Based on sample code from:
 * www.koders.com/c/fid84CFEFBF311605F963CB04E0F84A2F52A8120F33.aspx
 * Specifically the section on parsing the /proc/version.
 */
		while (feof(f) != 1) {
			fgets(Kyo, len, f);
/*
 * This function is fast, owing to this i feel. especially with gcc 
 * 4.3.2 & glibc 2.5+. it is faster than using: printf (Kyo);
 */
			fprintf (stdout, "%s", Kyo);
			fflush(stdout);
		}
	}
	fclose(f);
}

#endif /* sysinfo.h */

