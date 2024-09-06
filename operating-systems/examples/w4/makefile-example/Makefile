# example Makefile

# V1
#DecomProg: myMainProg.o myStructure.o myHelloFunctions.o # main build target
#	gcc myMainProg.o myStructure.o myHelloFunctions.o -o DecomProg
#
#myMainProg.o: myMainProg.c myStructure.h myHelloFunctions.h # automotically looks for the respective build rules
#	gcc -c myMainProg.c -o myMainProg.o
#
#myStructure.o: myStructure.c myStructure.h
#	gcc -c myStructure.c -o myStructure.o
#
#myHelloFunctions.o: myHelloFunctions.c myHelloFunctions.h
#	gcc -c myHelloFunctions.c -o myHelloFunctions.o
#
#clean:
#	rm -rf myMainProg.o myStructure.o myHelloFunctions.o DecomProg
#
#rebuild:
#	rm -rf myMainProg.o myStructure.o myHelloFunctions.o DecomProg
#	make

# V2
#DecomProg: myMainProg.o myStructure.o myHelloFunctions.o # main build target
#	gcc -g myMainProg.o myStructure.o myHelloFunctions.o -o DecomProg
#
#myMainProg.o: myStructure.h myHelloFunctions.h # automotically looks for the respective build rules
#	gcc -g -c myMainProg.c
#
#clean:
#	rm -rf myMainProg.o myStructure.o myHelloFunctions.o DecomProg
#
#rebuild:
#	rm -rf myMainProg.o myStructure.o myHelloFunctions.o DecomProg
#	make

# V3
#CXX = gcc
#CXXFLAGS = -g
#OBJECTS = myMainProg.o myStructure.o myHelloFunctions.o
#EXEC = DecomProg
#
#${EXEC}: ${OBJECTS} # main build target
#	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}
#
# manual dependency list
#myMainProg.o: myStructure.h myHelloFunctions.h
#
#clean:
#	rm -rf ${OBJECTS} ${EXEC}
#
#rebuild:
#	make clean
#	make

# V4
CXX = gcc
CXXFLAGS = -g -MMD
OBJECTS = myMainProg.o myStructure.o myHelloFunctions.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = DecomProg

${EXEC}: ${OBJECTS} # main build target
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm -rf ${OBJECTS} ${DEPENDS} ${EXEC}

rebuild:
	make clean
	make
