CC = clang++
CFLAGS = -Wall #-std=c99 -g -pg
SOURCES = main.cpp character.cpp node.cpp route.cpp skilltree.cpp
OBJS = $(patsubst %.c,%.o,$(SOURCES))
HEADERS = character.h node.h route.h skilltree.h
	
main:	$(OBJS)
	$(CC) $(CFLAGS) -o main $(OBJS) -lcurl

$(OBJS): $(HEADERS)

.PHONY: clean
clean:
	rm  main