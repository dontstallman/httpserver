CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Wshadow
TARGET = httpserver

all: $(TARGET)

$(TARGET): $(TARGET).o
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).o
$(TARGET).o: $(TARGET).c
	$(CC) $(CFLAGS) -c $(TARGET).c

clean: 
	rm -f $(TARGET) $(TARGET).o
