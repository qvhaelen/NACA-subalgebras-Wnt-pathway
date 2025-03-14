CC=g++
CFLAGS= -c  -O3
LDFLAGS= 

objects := $(patsubst %.cc,%.o,$(wildcard *.cc))


all: main_routine_algebra

main_routine_algebra: $(objects)
	$(CC)  -o main_routine_algebra $(objects)

%.o: %.cc
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o 
