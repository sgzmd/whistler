#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=arm-linux-gnueabi-as

# Macros
CND_PLATFORM=GNU_Arm-Linux-x86
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
#OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}
OBJECTDIR=${CND_BUILDDIR}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/lib/gpio/gpio.o \
	${OBJECTDIR}/lib/RF24/compatibility.o \
	${OBJECTDIR}/lib/spi/spi.o \
	${OBJECTDIR}/lib/RF24/RF24.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rf24bb

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rf24bb: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rf24bb ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/lib/gpio/gpio.o: lib/gpio/gpio.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/gpio
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/gpio/gpio.o lib/gpio/gpio.cpp

${OBJECTDIR}/lib/RF24/compatibility.o: lib/RF24/compatibility.c 
	${MKDIR} -p ${OBJECTDIR}/lib/RF24
	${RM} $@.d
	$(COMPILE.c) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/RF24/compatibility.o lib/RF24/compatibility.c

${OBJECTDIR}/lib/spi/spi.o: lib/spi/spi.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/spi
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/spi/spi.o lib/spi/spi.cpp

${OBJECTDIR}/lib/RF24/RF24.o: lib/RF24/RF24.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib/RF24
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/lib/RF24/RF24.o lib/RF24/RF24.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/rf24bb

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
