



CC = gcc
CFLAGS = -Wall -Wextra -I../include
AR = ar rcs

SRC = random.c
OBJ = $(SRC:.c=.o)
TARGET = libml.a

ifeq ($(MODE),debug)
  CFLAGS += -g
else
  CFLAGS += -O2
endif

all: $(TARGET)

$(TARGET): $(OBJ)
	$(AR) $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

