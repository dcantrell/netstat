/* Copyright 1998 by Andi Kleen. Subject to the GPL. */
/* $Id: util.c,v 1.4 1998/11/17 15:17:02 freitag Exp $ */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include <unistd.h>

#include "util.h"

int kernel_version(void)
{
    struct utsname uts;
    int major, minor, patch=0;

    if (uname(&uts) < 0)
	return -1;
    if (sscanf(uts.release, "%d.%d.%d", &major, &minor, &patch) < 2)
	return -1;
    return KRELEASE(major, minor, patch);
}

long ticks_per_second(void)
{
    return sysconf(_SC_CLK_TCK);
}

/* Like strncpy but make sure the resulting string is always 0 terminated. */
char *safe_strncpy(char *dst, const char *src, size_t size)
{
    dst[size-1] = '\0';
    return strncpy(dst,src,size-1);
}
