OBJS	= Main.o Street.o Apartment.o Flat.o
SOURCE	= Main.cpp Street.cpp Apartment.cpp Flat.cpp
HEADER	= Street.h Apartment.h Flat.h
OUT	= networkmap
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

Main.o: Main.cpp
	$(CC) $(FLAGS) Main.cpp -std=c++11

Street.o: Street.cpp
	$(CC) $(FLAGS) Street.cpp -std=c++11

Apartment.o: Apartment.cpp
	$(CC) $(FLAGS) Apartment.cpp -std=c++11

Flat.o: Flat.cpp
	$(CC) $(FLAGS) Flat.cpp -std=c++11


clean:
	rm -f $(OBJS) $(OUT)