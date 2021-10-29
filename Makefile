CC=gcc
CFLAGS=-Wall -O3 -Werror -fstack-protector-strong
TARGET=occurrences


.PHONY: $(TARGET)
all: $(TARGET)

$(TARGET): $(TARGET).o
	$(CC) -o $(TARGET) $(TARGET).o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f *.o $(TARGET)
