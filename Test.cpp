#include<iostream>
#include<fstream>
#include<boost/archive/text_oarchive.hpp>
#include<boost/archive/text_iarchive.hpp>
#include<boost/serialization/split_member.hpp>
#include<boost/date_time/posix_time/posix_time.hpp>
#include<unistd.h>
#include<signal.h>

using namespace std;

#include"DataStruct.hpp"
#include"CounterBase.hpp"
#include"CounterBaseFuns.hpp"

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
  DataStruct ds(35, 1);
  CounterBase<DataStruct> g(ds);
  g.setSerializationFile("sfilename",false);
  string avilableCommands = "avilable commands: \nhelp, exit, start_syn, start, stop\n";
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
    } else {
      cout <<"command not understood: "<<input <<endl <<avilableCommands <<flush;
	}
  }
}
