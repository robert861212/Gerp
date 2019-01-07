CC = clang++
CFLAGS = -Wall -Wextra -c -std=c++11 -O2
DEPS = DirNode.h FSTree.h LinkedList.h Index.h
 
 %.o: %.cpp $(DEPS)
	$(CC) -o $@ $< $(CFLAGS)

gerp: main.o DirNode.o FSTree.o LinkedList.o Index.o
	$(CC) -o gerp main.o DirNode.o FSTree.o LinkedList.o Index.o

clean:
	rm -f *.o core* *~ gerp