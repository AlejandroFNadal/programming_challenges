include ../Makefile.inc

GEN_EXE = sig_receiver sig_receiver_ej1
	
LINUX_EXE = signalfd_sigval

EXE = ${GEN_EXE} ${LINUX_EXE}

all : ${EXE}

allgen : ${GEN_EXE}

#
# The following example programs make use of signal() (instead of the
# preferred sigaction()) to establish signal handlers.
# By default, signal() on Linux follows the BSD semantics, establishing 
# a reliable signal handler. This is because _BSD_SOURCE is enabled
# bt default in <features.h>. However, in ../Makefile.inc, we define 
# CFLAGS to include _XOPEN_SOURCE, and this has the effect of disabling
# _BSD_SOURCE. To ensure that we get the default (BSD) semantics
# we here explicitly define _BSD_SOURCE when compiling these programs.
#

sig_receiver : sig_receiver.c
	${CC} -D_BSD_SOURCE -o $@ sig_receiver.c ${CFLAGS} ${IMPL_LDLIBS}


${EXE} : ${TLPI_LIB}		# True as a rough approximation
