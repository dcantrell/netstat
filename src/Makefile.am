#
# Makefile.am
# automake template for netstat/src/
# Author:  David Cantrell <david.l.cantrell@gmail.com>
#

bin_PROGRAMS = netstat

netstat_SOURCES = netstat.c statistics.c proc.c af.c unix.c util.c \
                  sockets.c getroute.c interface.c hw.c loopback.c \
                  nstrcmp.c irda.c eui64.c ib.c x25.c x25_gr.c x25_sr.c \
                  rose.c ether.c fddi.c hippi.c arcnet.c econet.c slip.c \
                  ppp.c tunnel.c ax25.c ax25_gr.c netrom.c netrom_gr.c \
                  ash.c hdlclapb.c frame.c ec_hw.c ddp_gr.c inet.c \
                  inet_gr.c ipx.c ipx_gr.c ddp.c masq_info.c

CFLAGS += -Wall -Wunused

if ENABLE_SELINUX
CFLAGS += -DHAVE_SELINUX
endif

if ENABLE_IPV6
CFLAGS += -DHAVE_AFINET6
endif

if ENABLE_BLUETOOTH
CFLAGS += -DHAVE_AFBLUETOOTH
endif
