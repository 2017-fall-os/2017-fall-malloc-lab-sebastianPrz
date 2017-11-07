CFLAGS	= -g
CC	= gcc
OBJ	= myAllocatorTest1 test1

all: $(OBJ)

myAllocatorTest1: myAllocator.o myAllocatorTest1.o
	$(CC) $(CFLAGS) -o $@ $^

test1: myAllocator.o myMalloc.o test1.o
	$(CC) $(CFLAGS) -o $@ $^

allocTest: myAllocator.o allocTest.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f *.o $(OBJ) 

