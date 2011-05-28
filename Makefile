CFLAGS=-Wall
test: Test.cpp CounterBaseFuns.hpp  CounterBase.hpp  DataStruct.hpp  SignalCatcher.hpp
	g++ Test.cpp myExampleTaskA.cpp -o test -lboost_serialization -lboost_thread
myExampleTaskA.o: myExampleTaskA.h myExampleTaskA.cpp
	g++ myExampleTaskA.cpp -o myExampleTaskA.o -c
clean:
	rm -f *.o *~ test