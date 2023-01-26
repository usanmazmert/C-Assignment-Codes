OBJS	= Main.o PrimaryTree.o AvlTree.o PrimaryTreeNode.o AvlTreeNode.o LLRBT.o LLRBTNode.o
SOURCE	= Main.cpp PrimaryTree.cpp AvlTree.cpp PrimaryTreeNode.cpp AvlTreeNode.cpp LLRBT.cpp LLRBTNode.cpp
HEADER	= PrimaryTree.h AvlTree.h PrimaryTreeNode.h AvlTreeNode.h LLRBT.h LLRBTNode.h
OUT	= webstore
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

Main.o: Main.cpp
	$(CC) $(FLAGS) Main.cpp -std=c++11

PrimaryTree.o: PrimaryTree.cpp
	$(CC) $(FLAGS) PrimaryTree.cpp -std=c++11

AvlTree.o: AvlTree.cpp
	$(CC) $(FLAGS) AvlTree.cpp -std=c++11

PrimaryTreeNode.o: PrimaryTreeNode.cpp
	$(CC) $(FLAGS) PrimaryTreeNode.cpp -std=c++11

AvlTreeNode.o: AvlTreeNode.cpp
	$(CC) $(FLAGS) AvlTreeNode.cpp -std=c++11

LLRBT.o: LLRBT.cpp
	$(CC) $(FLAGS) LLRBT.cpp -std=c++11

LLRBTNode.o: LLRBTNode.cpp
	$(CC) $(FLAGS) LLRBTNode.cpp -std=c++11


clean:
	rm -f $(OBJS) $(OUT)