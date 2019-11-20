# Build and Run Shell.c

#compiler
CC = gcc

#compiler flags
# -g to add debugging info, -Wall turns on compiler warnings
CFLAGS = -g -Wall

#The build target executable
TARGET = shell

all:$(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:
	$(RM) $(TARGET) $(TARGET).o
