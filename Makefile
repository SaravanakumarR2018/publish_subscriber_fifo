blocking_fifo: blockingqueue.cpp fifo.hpp
	g++ -std=c++11 -pthread blockingqueue.cpp -o blocking_fifo
	./blocking_fifo

nonblocking_fifo: fifo.hpp nonblockingqueue.cpp
	g++ -std=c++11 -pthread nonblockingqueue.cpp -o nonblocking_fifo
	./nonblocking_fifo
	

clean:
	rm -f *.o blocking_fifo nonblocking_fifo

