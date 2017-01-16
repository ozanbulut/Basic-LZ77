CC = g++
Flags = -std=c++11
Objects = LZ77.o

all:out

out:$(Objects)
	$(CC) LZ77.cpp $(Flags) -o out 

%.o: %.cpp
	$(CC) $<  $(Flags)  -c

clean:
	rm -rf *.o out

