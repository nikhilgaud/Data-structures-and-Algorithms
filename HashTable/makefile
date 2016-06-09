CC = g++
CFLAGS = -g -std=c++11 -Wall -W -Werror -pedantic -D HASH_TABLE_SIZE=10
LDFLAGS = 

hash5: hash.o hash_function.o main.o
	$(CC) $(LDFLAGS) $^ -o $@ 

main.o: main.cpp hash.h
	$(CC) $(CFLAGS) -c $<

hash.o: hash.cpp hash.h 
	$(CC) $(CFLAGS) -c $<

hash_function.o: hash_function.cpp hash.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o hash5
