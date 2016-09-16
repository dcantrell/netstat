/*
 * lib/net-features.h This file contains the definitions of all kernel
 *                      dependend features.
 *
 * Version:     features.h 0.03 (1996-03-22)
 *
 * Author:      Bernd Eckenfels <net-tools@lina.inka.de>
 *              Copyright 1996 Bernd Eckenfels, Germany
 *
 * Modifications:
 *960201 {0.01} Bernd Eckenfels:        creation
 *960202 {0.02} Bernd Eckenfels:        HW and AF added
 *960322 {0.03} Bernd Eckenfels:        moved into the NET-LIB
 *980630 {0.04} Arnaldo Carvalho de Melo: changed NLS for I18N
 *
 *              This program is free software; you can redistribute it
 *              and/or  modify it under  the terms of  the GNU General
 *              Public  License as  published  by  the  Free  Software
 *              Foundation;  either  version 2 of the License, or  (at
 *              your option) any later version.
 */

/*
 *    This needs to be included AFTER the KErnel Header Files
 *      one of the FEATURE_ should be defined to get the Feature Variable
 *      definition included
 */

#ifndef _NET_FEATURES_H
#define _NET_FEATURES_H

/* detect the present features */

#if defined (SIOCADDRTOLD) || defined (RTF_IRTT)	/* route */
#define HAVE_NEW_ADDRT 1
#endif

#ifdef RTF_IRTT			/* route */
#define HAVE_RTF_IRTT 1
#endif

#ifdef RTF_REJECT		/* route */
#define HAVE_RTF_REJECT 1
#endif

/* compose the feature information string */

#if defined (FEATURE_ARP) || defined (FEATURE_ROUTE) || defined (FEATURE_NETSTAT)
static char *Features =

/* ---------------------------------------------------- */
#ifdef FEATURE_ROUTE

#if HAVE_NEW_ADDRT
"+"
#else
"-"
#endif
"NEW_ADDRT "

#if HAVE_RTF_IRTT
"+"
#else
"-"
#endif
"RTF_IRTT "

#if HAVE_RTF_REJECT
"+"
#else
"-"
#endif
"RTF_REJECT "

#endif				/* FEATURE_ROUTE */
/* ---------------------------------------------------- */


/* ---------------------------------------------------- */
#ifdef FEATURE_NETSTAT

#if HAVE_NEW_ADDRT
"+"
#else
"-"
#endif
"NEW_ADDRT "

#if HAVE_RTF_IRTT
"+"
#else
"-"
#endif
"RTF_IRTT "

#if HAVE_RTF_REJECT
"+"
#else
"-"
#endif
"RTF_REJECT "

"+"
"FW_MASQUERADE "

#endif				/* FEATURE_NETSTAT */
/* ---------------------------------------------------- */


#if I18N
"+I18N"
#else
"-I18N"
#endif				/* I18N */

#if HAVE_SELINUX
" +SELINUX"
#endif

"\nAF: "
#ifdef DFLT_AF
"(" DFLT_AF ")"
#endif

" +"
"UNIX "
"+"
"INET "
#if HAVE_AFINET6
"+"
#else
"-"
#endif
"INET6 "
"+"
"IPX "
"+"
"AX25 "
"+"
"NETROM "
"+"
"X25 "
"+"
"ATALK "
"+"
"ECONET "
"+"
"ROSE "
"+"
"BLUETOOTH"

"\nHW: "

#ifdef DFLT_HW
"(" DFLT_HW ")"
#endif

" +"
"ETHER "
"+"
"ARC "
"+"
"SLIP "
"+"
"PPP "
"+"
"TUNNEL "
"+"
"TR "
"+"
"AX25 "

"+"
"NETROM "

"+"
"X25 "

"+"
"FR "

"+"
"ROSE "

"+"
"ASH "

#if HAVE_HWSIT
"+"
#else
"-"
#endif
"SIT "

"+"
"FDDI "

"+"
"HIPPI "

#if HAVE_HWHDLCLAPB
"+"
#else
"-"
#endif
"HDLC/LAPB "

"+"
"EUI64 "
;


#endif				/* FEATURE_* */

#endif				/* _NET_FEATURES_H */
/* End of features.h */
