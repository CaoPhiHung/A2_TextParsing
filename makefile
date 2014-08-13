CC = clang++
CFLAGS = -Wall #-std=c99 -g -pg
SOURCES = main.cpp
OBJS = $(patsubst %.c,%.o,$(SOURCES))
HEADERS = 
	
pacman:	$(OBJS)
	$(CC) $(CFLAGS) -o main $(OBJS) -lcurl

$(OBJS): $(HEADERS)

.PHONY: clean
clean:
	rm  main