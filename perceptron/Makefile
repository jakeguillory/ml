

CC = gcc
CFLAGS = -Wall -Wextra -I../include
LDFLAGS = -L../lib -lml

SRC = main.c perceptron.c
OBJ = $(SRC:.c=.o)
TARGET = perceptron

ifeq ($(MODE),debug)
  CFLAGS += -g
else
  CFLAGS += -O2
endif

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)



