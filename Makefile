#############################################################################
# Makefile for building: polystyren_sho
# Project:  polystyren_sho.pro
#############################################################################

MAKEFILE      = Makefile


####### Compiler, tools and options

CC            = gcc
CXX           = g++

WARNLD = -Wbad-function-cast -Wstrict-prototypes -Wmissing-declarations

PROG = polystyren_sho
CFLAGS = -g -D_DEBUG
CFLAGS += -pedantic
LDFLAGS = -lsimlib -lm
WARNCFLAGS = -Wall -Wshadow -Wpointer-arith \
		-Wcast-qual -Wcast-align


####### Output directory

OBJECTS_DIR   = ./


####### Files

OBJECTS = main.o \
		objednavka.o \
		varka.o \
		silo.o \
		plnesilo.o \
		blok.o \
		output.o



####### Build rules

all: $(PROG)

$(PROG): $(OBJECTS)	
	$(CXX) $(WARNCFLAGS) $(WARNLD) $(CFLAGS)  -o $(PROG) $(OBJECTS) $(LDFLAGS)

####### Compile

main.o: main.cpp objednavka.h \
		silo.h \
		global.h \
		sklad.h \
		blok.h \
		output.h \
		logger.h \
		zariadenia.h
	$(CXX) -c $(CXXFLAGS)  -o main.o main.cpp

objednavka.o: objednavka.cpp objednavka.h \
		varka.h \
		global.h \
		zariadenia.h \
		silo.h \
		output.h
	$(CXX) -c $(CXXFLAGS) -o objednavka.o objednavka.cpp

varka.o: varka.cpp varka.h \
		zariadenia.h \
		silo.h \
		global.h \
		output.h
	$(CXX) -c $(CXXFLAGS) -o varka.o varka.cpp

silo.o: silo.cpp silo.h \
		global.h \
		zariadenia.h \
		output.h \
		plnesilo.h
	$(CXX) -c $(CXXFLAGS) -o silo.o silo.cpp

plnesilo.o: plnesilo.cpp plnesilo.h \
		global.h \
		zariadenia.h \
		silo.h \
		output.h \
		blok.h
	$(CXX) -c $(CXXFLAGS) -o plnesilo.o plnesilo.cpp

blok.o: blok.cpp blok.h \
		global.h \
		zariadenia.h \
		silo.h \
		output.h
	$(CXX) -c $(CXXFLAGS) -o blok.o blok.cpp

output.o: output.cpp output.h \
		zariadenia.h \
		silo.h \
		global.h
	$(CXX) -c $(CXXFLAGS) -o output.o output.cpp

clean:
	rm -f $(OBJECTS)

run:
	./polystyren_sho
	make plot

plot:
	cd out && gnuplot plot.plt && cd ..