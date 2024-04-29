# directories
TARGET = build
#VIS = vis
VIS = D:/projects/Rprojects/vis
# files
EXECUTABLE = memchecker

# compile
CPPFLAGS += -DUNICODE

${TARGET}/${EXECUTABLE}.exe: ${TARGET}/${EXECUTABLE}.o ${TARGET}/scanrun.o ${TARGET}/processfile.o ${TARGET}/infocollector.o ${VIS}/sourceCpp_11.dll
	g++ -Wall -o ${TARGET}/${EXECUTABLE}.exe ${TARGET}/${EXECUTABLE}.o ${TARGET}/scanrun.o ${TARGET}/processfile.o ${TARGET}/infocollector.o

${TARGET}/${EXECUTABLE}.o: main.cpp
	@if not exist ./$(TARGET) mkdir ${TARGET}
	g++ ${CPPFLAGS} -Wall -c -g -o ${TARGET}/${EXECUTABLE}.o main.cpp

${TARGET}/processfile.o: processfile.cpp
	@if not exist ./$(TARGET) mkdir ${TARGET}
	g++ ${CPPFLAGS} -Wall -c -g -o ${TARGET}/processfile.o processfile.cpp --static

${TARGET}/infocollector.o: infocollector.cpp
	@if not exist ./$(TARGET) mkdir ${TARGET}
	g++ ${CPPFLAGS} -Wall -c -g -o ${TARGET}/infocollector.o infocollector.cpp --static

${TARGET}/scanrun.o: scanrun.cpp
	@if not exist ./$(TARGET) mkdir ${TARGET}
	g++ ${CPPFLAGS} -DRUNCOMMAND='"${VISRUNCOMMAND}"' -Wall -c -g -o ${TARGET}/scanrun.o scanrun.cpp --static




RPATH = D:/soft/R/R-4.4.0
RTOOLS = c:/rtools44
RAPIPFLAGS += -DNDEBUG

RAPIINCLUDE += -I"${RPATH}/include"
RAPIINCLUDE += -I"${RPATH}/library/Rcpp/include"
RAPIINCLUDE += -I"${VIS}/include"
RAPIINCLUDE += -I"${RTOOLS}/x86_64-w64-mingw32.static.posix/include" #?

RAPIOBJECTS = ${VIS}/rapi.o ${TARGET}/infocollector.o
RAPILIBS += -L${RTOOLS}/x86_64-w64-mingw32.static.posix/lib 
RAPILIBS += -L${RTOOLS}/x86_64-w64-mingw32.static.posix/lib/x64 
RAPILIBS += -L${RPATH}/bin/x64

${VIS}/sourceCpp_11.dll: ${RAPIOBJECTS}
	 g++ -std=gnu++17 -Wall -shared -s -static-libgcc -o ${VIS}/sourceCpp_11.dll ${RAPIOBJECTS} ${RAPILIBS} -lR

${VIS}/rapi.o: ${VIS}/rapi.cpp
	g++ -std=gnu++17 -I"${RTOOLS}/x86_64-w64-mingw32.static.posix/include" -I"${RPATH}/library/Rcpp/include" -I"${VIS}/include" -I"${RPATH}/include" -O2 -Wall  -mfpmath=sse -msse2 -mstackrealign -c ${VIS}/rapi.cpp -o ${VIS}/rapi.o
#	g++ -std=gnu++17 ${PIINCLUDE} -O2 -Wall  -mfpmath=sse -msse2 -mstackrealign -c ${VIS}/rapi.cpp -o ${VIS}/rapi.o
	
VISSRC = ${VIS}/vis_main.R
RSCRIPT = ${RPATH}/bin/Rscript
VISRUNCOMMAND = ${RSCRIPT} ${VISSRC} 
# D:\soft\R\R-4.4.0\bin\Rscript vis_main.R