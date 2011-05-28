CFLAGS=-Wall
test: Test.cpp CounterBaseFuns.hpp  CounterBase.hpp  DataStruct.hpp  SignalCatcher.o myExampleTaskA.o
	g++ Test.cpp myExampleTaskA.o SignalCatcher.o -o test -lboost_serialization -lboost_thread
myExampleTaskA.o: myExampleTaskA.h myExampleTaskA.cpp
	g++ myExampleTaskA.cpp -o myExampleTaskA.o -c
SignalCatcher.o: SignalCatcher.hpp SignalCatcher.cpp
	g++ SignalCatcher.cpp -o SignalCatcher.o -c
clean:
	rm -f *.o *~ test