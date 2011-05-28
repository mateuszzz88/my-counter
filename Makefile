CFLAGS=-Wall
test: Test.cpp CounterBaseFuns.hpp  CounterBase.hpp  DataStruct.hpp  SignalCatcher.hpp
	g++ Test.cpp -o test -lboost_serialization -lboost_thread
clean:
	rm -f *.o *~ test