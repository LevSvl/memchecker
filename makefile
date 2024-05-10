# directories
TARGET = build
RPATH = D:/soft/R/R-4.4.0
RSCRIPT = ${RPATH}/bin/Rscript
VIS = D:/projects/Rprojects/vis
VISSRC = ${VIS}/vis_main.R

# files
EXECUTABLE = memchecker
VISDATAINPUT = ${VIS}/data.csv

# commands
VISRUNCOMMAND += cd ${VIS} &&  # cmd command to cd to vis dir
VISRUNCOMMAND += ${RSCRIPT} ${VISSRC} # and run vis script

# compile
CPPFLAGS += -DUNICODE
CPPFLAGS += -Wall # warnings
CPPFLAGS += -c # .cpp-> .o
CPPFLAGS += -g # debug

OBJECTS += ${TARGET}/${EXECUTABLE}.o
OBJECTS += ${TARGET}/scanrun.o 
OBJECTS += ${TARGET}/processfile.o
OBJECTS += ${TARGET}/infocollector.o
OBJECTS += ${TARGET}/vis_init.o
OBJECTS += ${VIS}/visimpl.o


# rules
${TARGET}/${EXECUTABLE}.exe: ${OBJECTS}
	g++ -Wall -o ${TARGET}/${EXECUTABLE}.exe ${OBJECTS}

${TARGET}/${EXECUTABLE}.o: main.cpp
	@if not exist ./$(TARGET) mkdir ${TARGET}
	g++ ${CPPFLAGS} -o ${TARGET}/${EXECUTABLE}.o main.cpp

${TARGET}/processfile.o: processfile.cpp
	@if not exist ./$(TARGET) mkdir ${TARGET}
	g++ ${CPPFLAGS} -o ${TARGET}/processfile.o processfile.cpp --static

${TARGET}/infocollector.o: infocollector.cpp
	@if not exist ./$(TARGET) mkdir ${TARGET}
	g++ -std=c++11 ${CPPFLAGS} -o ${TARGET}/infocollector.o infocollector.cpp --static

${TARGET}/scanrun.o: scanrun.cpp
	@if not exist ./$(TARGET) mkdir ${TARGET}
	g++ ${CPPFLAGS} -o ${TARGET}/scanrun.o scanrun.cpp --static

${TARGET}/vis_init.o: vis_init.cpp
	@if not exist ./$(TARGET) mkdir ${TARGET}
	g++ ${CPPFLAGS} -I "${TARGET}/.." -I"${VIS}" \
	-o ${TARGET}/vis_init.o vis_init.cpp --static

${VIS}/visimpl.o: ${VIS}/visimpl.cpp
	g++ ${CPPFLAGS} -I"${TARGET}/.." \
	-DRUNCOMMAND='"${VISRUNCOMMAND}"' -DVISDATAINPUT='"${VISDATAINPUT}"' \
	-o ${VIS}/visimpl.o ${VIS}/visimpl.cpp