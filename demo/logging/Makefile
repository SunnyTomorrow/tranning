CC=g++

OBJ:=timevalue.o exactime.o logging.o logtest.o
#CPP:=$(wildcard *.cpp)
#HEAD:=$(wildcard *.h)

test:$(OBJ)
	$(CC) -o test $(OBJ)

$(OBJ):%o:%cpp
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY:clean

clean:
	rm test *.o

