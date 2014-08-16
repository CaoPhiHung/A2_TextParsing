CXXFLAGS = -Wall -g

EXEC = main

OBJS = character.o skilltree.o node.o skills.o

.PHONY: all
all: $(EXEC)

$(EXEC): $(EXEC).cpp $(OBJS) -lcurl 

skilltree.o: node.h character.h skills.h skilltree.h
node.o: node.h
character.o: node.h character.h
skills.o: node.h skills.h

.PHONY: clean
clean:
	$(RM) *.o *~ core a.out $(EXEC)