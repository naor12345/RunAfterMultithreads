prototype: prototype.cpp frame.cpp threadpool
	g++ -o prototype frame.cpp -g -std=c++11 -lpthread

clean:
	rm -rf prototype
