TARGET = kp9
CC = gcc
CFLAGS = -std=c99 -pedantic -Wall
LDFLAGS =

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))
HEADERS = $(wildcard *.h)

all : $(TARGET)

$(TARGET) : $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(TARGET)
	
%.o : %.c $(HEADERS)
	$(CC) -c $< -o $@

clean : 
	rm $(TARGET) $(OBJ)