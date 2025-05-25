include ../Makefile.inc

GEN_EXE = t_stat_with_nanosec 

LINUX_EXE = large_file

EXE = ${GEN_EXE} ${LINUX_EXE}

all : ${EXE}

allgen : ${GEN_EXE}


clean :
	${RM} ${EXE} *.o

showall : 
	@ echo ${EXE}

${EXE} : ${TLPI_LIB}            # True as a rough approximation

