/*
 * lib/hw.c   This file contains the top-level part of the hardware
 *              support functions module.
 *
 * Version:     $Id: hw.c,v 1.19 2008/10/03 01:52:04 ecki Exp $
 *
 * Maintainer:  Bernd 'eckes' Eckenfels, <net-tools@lina.inka.de>
 *
 * Author:      Fred N. van Kempen, <waltje@uwalt.nl.mugnet.org>
 *              Copyright 1993 MicroWalt Corporation
 *
 *980701 {1.21}  Arnaldo C. Melo       GNU gettext instead of catgets
 *
 *              This program is free software; you can redistribute it
 *              and/or  modify it under  the terms of  the GNU General
 *              Public  License as  published  by  the  Free  Software
 *              Foundation;  either  version 2 of the License, or  (at
 *              your option) any later version.
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <net/if_arp.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include "config.h"
#include "net-support.h"
#include "pathnames.h"
#include "intl.h"

extern struct hwtype unspec_hwtype;
extern struct hwtype loop_hwtype;

extern struct hwtype slip_hwtype;
extern struct hwtype cslip_hwtype;
extern struct hwtype slip6_hwtype;
extern struct hwtype cslip6_hwtype;
extern struct hwtype adaptive_hwtype;

extern struct hwtype ether_hwtype;
extern struct hwtype fddi_hwtype;
extern struct hwtype hippi_hwtype;

extern struct hwtype ax25_hwtype;
extern struct hwtype rose_hwtype;
extern struct hwtype netrom_hwtype;
extern struct hwtype x25_hwtype;
extern struct hwtype tunnel_hwtype;

extern struct hwtype ash_hwtype;

extern struct hwtype ppp_hwtype;

extern struct hwtype arcnet_hwtype;

extern struct hwtype dlci_hwtype;
extern struct hwtype frad_hwtype;

extern struct hwtype hdlc_hwtype;
extern struct hwtype lapb_hwtype;

extern struct hwtype sit_hwtype;

extern struct hwtype irda_hwtype;

extern struct hwtype ec_hwtype;

extern struct hwtype ib_hwtype;

extern struct hwtype eui64_hwtype;

static const struct hwtype * const hwtypes[] =
{

    &loop_hwtype,

    &slip_hwtype,
    &cslip_hwtype,
    &slip6_hwtype,
    &cslip6_hwtype,
    &adaptive_hwtype,
    &ash_hwtype,
    &ether_hwtype,
    &ax25_hwtype,
    &netrom_hwtype,
    &rose_hwtype,
    &tunnel_hwtype,
    &ppp_hwtype,
    &hdlc_hwtype,
    &lapb_hwtype,
    &arcnet_hwtype,
    &dlci_hwtype,
    &frad_hwtype,
#if HAVE_HWSIT
    &sit_hwtype,
#endif
    &fddi_hwtype,
    &hippi_hwtype,
    &irda_hwtype,
    &ec_hwtype,
    &x25_hwtype,
    &ib_hwtype,
    &eui64_hwtype,
    &unspec_hwtype,
    NULL
};

static short sVhwinit = 0;

static void hwinit(void)
{
    loop_hwtype.title = _("Local Loopback");
    unspec_hwtype.title = _("UNSPEC");
    slip_hwtype.title = _("Serial Line IP");
    cslip_hwtype.title = _("VJ Serial Line IP");
    slip6_hwtype.title = _("6-bit Serial Line IP");
    cslip6_hwtype.title = _("VJ 6-bit Serial Line IP");
    adaptive_hwtype.title = _("Adaptive Serial Line IP");
    ether_hwtype.title = _("Ethernet");
    ash_hwtype.title = _("Ash");
    fddi_hwtype.title = _("Fiber Distributed Data Interface");
    hippi_hwtype.title = _("HIPPI");
    ax25_hwtype.title = _("AMPR AX.25");
    rose_hwtype.title = _("AMPR ROSE");
    netrom_hwtype.title = _("AMPR NET/ROM");
    x25_hwtype.title = _("generic X.25");
    tunnel_hwtype.title = _("IPIP Tunnel");
    ppp_hwtype.title = _("Point-to-Point Protocol");
    hdlc_hwtype.title = _("(Cisco)-HDLC");
    lapb_hwtype.title = _("LAPB");
    arcnet_hwtype.title = _("ARCnet");
    dlci_hwtype.title = _("Frame Relay DLCI");
    frad_hwtype.title = _("Frame Relay Access Device");
#if HAVE_HWSIT
    sit_hwtype.title = _("IPv6-in-IPv4");
#endif
    irda_hwtype.title = _("IrLAP");
    ec_hwtype.title = _("Econet");
    ib_hwtype.title = _("InfiniBand");
    eui64_hwtype.title = _("Generic EUI-64");
    sVhwinit = 1;
}

/* Check our hardware type table for this type. */
const struct hwtype *get_hwtype(const char *name)
{
    const struct hwtype * const *hwp;

    if (!sVhwinit)
	hwinit();

    hwp = hwtypes;
    while (*hwp != NULL) {
	if (!strcmp((*hwp)->name, name))
	    return (*hwp);
	hwp++;
    }
    return (NULL);
}


/* Check our hardware type table for this type. */
const struct hwtype *get_hwntype(int type)
{
    const struct hwtype * const *hwp;

    if (!sVhwinit)
	hwinit();

    hwp = hwtypes;
    while (*hwp != NULL) {
	if ((*hwp)->type == type)
	    return (*hwp);
	hwp++;
    }
    return (NULL);
}

/* type: 0=all, 1=ARPable */
void print_hwlist(int type) {
    int count = 0;
    const char * txt;
    const struct hwtype * const *hwp;

    if (!sVhwinit)
	hwinit();

    hwp = hwtypes;
    while (*hwp != NULL) {
	if (((type == 1) && ((*hwp)->alen == 0)) || ((*hwp)->type == -1)) {
		hwp++; continue;
	}
	if ((count % 3) == 0) fprintf(stderr,count?"\n    ":"    ");
        txt = (*hwp)->name; if (!txt) txt = "..";
	fprintf(stderr,"%s (%s) ",txt,(*hwp)->title);
	count++;
	hwp++;
    }
    fprintf(stderr,"\n");
}

/* return 1 if address is all zeros */
int hw_null_address(const struct hwtype *hw, void *ap)
{
    unsigned int i;
    unsigned char *address = (unsigned char *)ap;
    for (i = 0; i < hw->alen; i++)
	if (address[i])
	    return 0;
    return 1;
}
