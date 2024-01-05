CROSS_COMPILE ?=
CC = $(CROSS_COMPILE)gcc
CFALGS = -Wall -O2
LDFALGS = 

SRC = $(wildcard ./*.c)
OBJS = $(patsubst %.c, %.o, $(SRC))
TARGET = uhct

all: $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY : clean
clean:
	rm -rf $(OBJS) $(TARGET)
