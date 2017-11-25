/*
 * Copyright 2003,2005,2006 Bernhard Walle <bernhard@bwalle.de>
 * Copyright 2010 Florian Rivoal <frivoal@gmail.com>
 * -------------------------------------------------------------------------------------------------
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License as published by the Free
 *  Software Foundation; either version 2 of the License, or (at your option)
 *  any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 675 Mass
 * Ave, Cambridge, MA 02139, USA.
 *
 * -------------------------------------------------------------------------------------------------
 */
#ifndef NET_H
#define NET_H

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#include <stdio.h>
#include <sys/param.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>

#define INTERFACE_NAME_LENGTH 33

/* This structure stays the INFO variables */
typedef struct DataStats {
    double rx_bytes;
    double tx_bytes;
} DataStats;

typedef struct {
  double backup_in;
  double backup_out;
  double cur_in;
  double cur_out;
  int correct_interface;
  struct timeval prev_time;
  DataStats stats;
  char old_if_name[INTERFACE_NAME_LENGTH];
  char if_name[INTERFACE_NAME_LENGTH];
  char file_rx_bytes[PATH_MAX];
  char file_tx_bytes[PATH_MAX];
  char file_operstate[PATH_MAX];
} netdata;

/**
 * Initializes the netload plugin. Used to set up inital values.
 * This function must be called after each change of the network interface.
 * @param   device      The network device, e.g. <code>ippp0</code> for ISDN on
 * Linux.
 * @return  <code>true</code> if no error occurs, <code>false</code> otherwise.
 * If there's an error, the error message may be set
 */
int init_netload(netdata *data, const char *device);

/**
 * Gets the current netload. You must call init_netload() once before you use
 * this function!
 * @param in        Input load in byte/s.
 * @param out       Output load in byte/s.
 * @param tot       Total load in byte/s.
 */
void get_current_netload(netdata *data, unsigned long *in, unsigned long *out,
                         unsigned long *tot);

/* 
 * Checks if the interface is exists and is up
 *
 * @param data Object
 * 
 * Returns TRUE if found and up, FALSE otherwise 
 */
int check_interface(netdata*);

#endif /* NET_H */
