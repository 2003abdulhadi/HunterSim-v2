OBJS	= Banshee.o Building.o Bullies.o Control.o Evidence.o Ghost.o Hunter.o main.o Phantom.o Poltergeist.o Room.o View.o
SOURCE	= Banshee.cc Building.cc Bullies.cc Control.cc Evidence.cc Ghost.cc Hunter.cc main.cc Phantom.cc Poltergeist.cc Room.cc View.cc
HEADER	= Banshee.h Building.h Bullies.h Control.h defs.h Evidence.h Ghost.h Hunter.h Phantom.h Poltergeist.h Room.h View.h
OUT	= HunterSim-v2
CC	 = g++
FLAGS	 = -g3 -c -Wall
LFLAGS	 = -lpthread

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

Banshee.o: Banshee.cc
	$(CC) $(FLAGS) Banshee.cc 

Building.o: Building.cc
	$(CC) $(FLAGS) Building.cc 

Bullies.o: Bullies.cc
	$(CC) $(FLAGS) Bullies.cc 

Control.o: Control.cc
	$(CC) $(FLAGS) Control.cc 

Evidence.o: Evidence.cc
	$(CC) $(FLAGS) Evidence.cc 

Ghost.o: Ghost.cc
	$(CC) $(FLAGS) Ghost.cc 

Hunter.o: Hunter.cc
	$(CC) $(FLAGS) Hunter.cc 

main.o: main.cc
	$(CC) $(FLAGS) main.cc 

Phantom.o: Phantom.cc
	$(CC) $(FLAGS) Phantom.cc 

Poltergeist.o: Poltergeist.cc
	$(CC) $(FLAGS) Poltergeist.cc 

Room.o: Room.cc
	$(CC) $(FLAGS) Room.cc 

View.o: View.cc
	$(CC) $(FLAGS) View.cc


clean:
	rm -f $(OBJS) $(OUT)

debug: $(OUT)
	valgrind $(OUT)

valgrind: $(OUT)
	valgrind $(OUT)

valgrind_leakcheck: $(OUT)
	valgrind --leak-check=full $(OUT)

valgrind_extreme: $(OUT)
	valgrind --leak-check=full --show-leak-kinds=all --leak-resolution=high --track-origins=yes --vgdb=yes $(OUT)