CXXFLAGS = -Wall -g

EXEC = main

OBJS = skilltree.o node.o

.PHONY: all
all: $(EXEC)

$(EXEC): $(EXEC).cpp $(OBJS) -lcurl 

node.o: node.h
skilltree.o: node.h skilltree.h

.PHONY: clean
clean:
	$(RM) *.o *~ core a.out $(EXEC)