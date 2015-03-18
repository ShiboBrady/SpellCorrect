CC=g++

CFLAGS=-Wall -g

BIN=libecho.a

INCLUDE=echo

SRC=src

OBJS=Cond.o Exception.o Mutex.o PollPoller.o Rio.o TcpServer.o TcpConnection.o Threadpool.o Timer.o InetAddress.o Queue.o Socket.o Thread.o

STARD=-std=c++0x

$(BIN):$(OBJS)
	ar -crv -o $@ $^
	chmod 0777 $@
	rm -f *.o
	cp -r $(BIN) ../lib/
	rm -f $(BIN)

%.o:%.cpp
	$(CC) $(CFLAGS) -c $< -o $@ $(STARD)

Queue.o:Queue.hpp
	$(CC) $(CFLAGS) -c $^ -o $@ $(STARD)
