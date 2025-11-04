

CC = gcc
CFLAGS = -Wall -Wextra -I../include
LDFLAGS = -L../lib -lml

SRC = main.c lin_reg.c
OBJ = $(SRC:.c=.o)
TARGET = lin_reg

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



