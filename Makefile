CC=gcc
CFLAGS=-Wall -g -static

TARGET=cc2

OBJS=cc2.o tokenize.o parse.o generate.o

.SUFFIXES : .c .o

all : $(TARGET)

$(TARGET) : Makefile $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS)

.c.o : $<
	$(CC) -c $< $(CFLAGS)

test : $(TARGET)
	./test.sh

clean :
	rm $(OBJS) $(TARGET) test test.s

.PHONY : clean test
