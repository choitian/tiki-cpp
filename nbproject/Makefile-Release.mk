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
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/tools/syntax/Grammar.o \
	${OBJECTDIR}/tools/syntax/LookaheadLR.o \
	${OBJECTDIR}/tools/syntax/State.o \
	${OBJECTDIR}/util/commons.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1 \
	${TESTDIR}/TestFiles/f2 \
	${TESTDIR}/TestFiles/f3

# Test Object Files
TESTOBJECTFILES= \
	${TESTDIR}/Test001/Test001.o \
	${TESTDIR}/Test002/Test002.o \
	${TESTDIR}/TestTiki/TestTiki.o

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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tiki-cpp

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tiki-cpp: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tiki-cpp ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/tools/syntax/Grammar.o: tools/syntax/Grammar.cpp
	${MKDIR} -p ${OBJECTDIR}/tools/syntax
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tools/syntax/Grammar.o tools/syntax/Grammar.cpp

${OBJECTDIR}/tools/syntax/LookaheadLR.o: tools/syntax/LookaheadLR.cpp
	${MKDIR} -p ${OBJECTDIR}/tools/syntax
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tools/syntax/LookaheadLR.o tools/syntax/LookaheadLR.cpp

${OBJECTDIR}/tools/syntax/State.o: tools/syntax/State.cpp
	${MKDIR} -p ${OBJECTDIR}/tools/syntax
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tools/syntax/State.o tools/syntax/State.cpp

${OBJECTDIR}/util/commons.o: util/commons.cpp
	${MKDIR} -p ${OBJECTDIR}/util
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/util/commons.o util/commons.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-tests-subprojects .build-conf ${TESTFILES}
.build-tests-subprojects:

${TESTDIR}/TestFiles/f1: ${TESTDIR}/Test001/Test001.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS}   

${TESTDIR}/TestFiles/f2: ${TESTDIR}/Test002/Test002.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f2 $^ ${LDLIBSOPTIONS}   

${TESTDIR}/TestFiles/f3: ${TESTDIR}/TestTiki/TestTiki.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f3 $^ ${LDLIBSOPTIONS}   


${TESTDIR}/Test001/Test001.o: Test001/Test001.cpp 
	${MKDIR} -p ${TESTDIR}/Test001
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/Test001/Test001.o Test001/Test001.cpp


${TESTDIR}/Test002/Test002.o: Test002/Test002.cpp 
	${MKDIR} -p ${TESTDIR}/Test002
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/Test002/Test002.o Test002/Test002.cpp


${TESTDIR}/TestTiki/TestTiki.o: TestTiki/TestTiki.cpp 
	${MKDIR} -p ${TESTDIR}/TestTiki
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/TestTiki/TestTiki.o TestTiki/TestTiki.cpp


${OBJECTDIR}/main_nomain.o: ${OBJECTDIR}/main.o main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/main.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main_nomain.o main.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/main.o ${OBJECTDIR}/main_nomain.o;\
	fi

${OBJECTDIR}/tools/syntax/Grammar_nomain.o: ${OBJECTDIR}/tools/syntax/Grammar.o tools/syntax/Grammar.cpp 
	${MKDIR} -p ${OBJECTDIR}/tools/syntax
	@NMOUTPUT=`${NM} ${OBJECTDIR}/tools/syntax/Grammar.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tools/syntax/Grammar_nomain.o tools/syntax/Grammar.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/tools/syntax/Grammar.o ${OBJECTDIR}/tools/syntax/Grammar_nomain.o;\
	fi

${OBJECTDIR}/tools/syntax/LookaheadLR_nomain.o: ${OBJECTDIR}/tools/syntax/LookaheadLR.o tools/syntax/LookaheadLR.cpp 
	${MKDIR} -p ${OBJECTDIR}/tools/syntax
	@NMOUTPUT=`${NM} ${OBJECTDIR}/tools/syntax/LookaheadLR.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tools/syntax/LookaheadLR_nomain.o tools/syntax/LookaheadLR.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/tools/syntax/LookaheadLR.o ${OBJECTDIR}/tools/syntax/LookaheadLR_nomain.o;\
	fi

${OBJECTDIR}/tools/syntax/State_nomain.o: ${OBJECTDIR}/tools/syntax/State.o tools/syntax/State.cpp 
	${MKDIR} -p ${OBJECTDIR}/tools/syntax
	@NMOUTPUT=`${NM} ${OBJECTDIR}/tools/syntax/State.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tools/syntax/State_nomain.o tools/syntax/State.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/tools/syntax/State.o ${OBJECTDIR}/tools/syntax/State_nomain.o;\
	fi

${OBJECTDIR}/util/commons_nomain.o: ${OBJECTDIR}/util/commons.o util/commons.cpp 
	${MKDIR} -p ${OBJECTDIR}/util
	@NMOUTPUT=`${NM} ${OBJECTDIR}/util/commons.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O2 -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/util/commons_nomain.o util/commons.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/util/commons.o ${OBJECTDIR}/util/commons_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	    ${TESTDIR}/TestFiles/f2 || true; \
	    ${TESTDIR}/TestFiles/f3 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
