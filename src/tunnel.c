/*
 *    Tunnel.c, Alan Cox 1995.
 *
 */

#include "config.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <net/if_arp.h>
#include <linux/if_ether.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include "net-support.h"
#include "pathnames.h"

extern struct hwtype ether_hwtype;

static const char *pr_tunnel(const char *ptr)
{
    return ("");
}


static int in_tunnel(char *bufp, struct sockaddr_storage *sasp)
{
    return (-1);
}


struct hwtype tunnel_hwtype =
{
    "tunnel", NULL, /*"IPIP Tunnel", */ ARPHRD_TUNNEL, 0,
    pr_tunnel, in_tunnel, NULL, 0
};
