#ifndef IFACE_H_
#define IFACE_H_

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

/*
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/if_link.h>
*/

int iface(void) {

        char line[500]; // Read with fgets().
        char ip_address[500]; // Obviously more space than necessary, just illustrating here.
        int hw_type;
        int flags;
        char mac_address[500];
        char mask[500];
        char device[500];

        FILE *fp = fopen("/proc/net/arp", "r");
        fgets(line, sizeof(line), fp);    // Skip the first line (column headers).
        while(fgets(line, sizeof(line), fp))
        {
            // Read the data.
                sscanf(line, "%s 0x%x 0x%x %s %s %s\n",
                  ip_address,
                  &hw_type,
                  &flags,
                  mac_address,
                  mask,
                  device);

            printf("IP: %s \n", ip_address);
            printf("MAC: %s \n", mac_address);
            printf("Dev: %s \n", device);
            printf("HW Type: %u \n", hw_type);
            printf("Mask: %s \n", mask);
        }
        fclose(fp);
        return 0;
}

#endif
