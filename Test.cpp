#include <iostream>
#include "myExampleTaskA.h"
// #include<fstream>
// #include<boost/date_time/posix_time/posix_time.hpp>
// #include<unistd.h>
// #include<signal.h>

using namespace std;

// #include"DataStruct.hpp"
// #include"CounterBase.hpp"
// #include"CounterBaseFuns.hpp"

void manualTest();

int main()
{
  
  manualTest();
  return 0;
  
  /*
  std::ofstream ofs("filename", ios::binary);
  DataStruct ds(35, 1);
  
  CounterBase<DataStruct> g(ds);
//   g.startCalculations();
//   sleep(10);
//   g.stopCalculations();
  g.doCalculations();
  
 
  DataStruct sd(0,0); 
  CounterBase<DataStruct>  newg(sd);
  std::ifstream ifs("filename", ios::binary);
    {
	boost::archive::text_iarchive ia(ifs);
	ia >> newg;
        newg.d();
    }

 return 0;*/
}



void manualTest(){
//   DataStruct ds(35, 1);
//   CounterBase<DataStruct> g(ds);
//   TODO: Is it possible to start the calculations from the beginning?
  BigPrimeData ds;
  myExampleTaskA g(ds, 5);
  //myExampleTaskA g; //takes default constructor of BigPrimeData
  g.setSerializationFile("sfilename",true);
  string avilableCommands =
          "avilable commands: \n"
          "help      - shows this list, \n"
          "exit      - closes test program, \n"
          "start_syn - starts calculations in main thread, \n"
          "start     - creates calculations thread, \n"
          "join      - waits for calculations thread to finish, \n"
          "stop      - stops calculations thread\n";
  cout <<avilableCommands;
  string input;
  
  while (1) {
    cin>>input;
    if (input=="exit" || input=="quit") {
      return;
    } else if (input=="start") {
      g.startCalculations();
    } else if (input=="stop"){
      g.stopCalculations();
    } else if (input=="start_syn"){
      g.doCalculations();
    } else if (input=="join"){
      g.join();
    } else {
      cout <<"command not understood: "<<input <<endl <<avilableCommands <<flush;
	}
  }
}
