OBJS	= Restaurant.o Restaurant2.o Barista.o Cashier.o Customer.o Queue.o Main.o Employee.o
SOURCE	= Restaurant.cpp Restaurant2.cpp Barista.cpp Cashier.cpp Customer.cpp Queue.cpp Main.cpp Employee.cpp
HEADER	= Restaurant.h Restaurant2.h Barista.h Cashier.h Customer.h Queue.h Employee.h
OUT	= Assignment3
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

Restaurant.o: Restaurant.cpp
	$(CC) $(FLAGS) Restaurant.cpp -std=c++11

Restaurant2.o: Restaurant2.cpp
	$(CC) $(FLAGS) Restaurant2.cpp -std=c++11

Barista.o: Barista.cpp
	$(CC) $(FLAGS) Barista.cpp -std=c++11

Cashier.o: Cashier.cpp
	$(CC) $(FLAGS) Cashier.cpp -std=c++11

Customer.o: Customer.cpp
	$(CC) $(FLAGS) Customer.cpp -std=c++11

Queue.o: Queue.cpp
	$(CC) $(FLAGS) Queue.cpp -std=c++11

Main.o: Main.cpp
	$(CC) $(FLAGS) Main.cpp -std=c++11

Employee.o: Employee.cpp
	$(CC) $(FLAGS) Employee.cpp -std=c++11


clean:
	rm -f $(OBJS) $(OUT)