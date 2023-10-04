CC = gcc
CFLAGS = -Wall

TARGET = lab6
SRC = lab6.c

all: $(TARGET)

$(TARGET): $(SRC)
  $(CC) $(CFLAGS) -O $(TARGET) $(SRC)

clean:
  rm -f $(TARGET)
