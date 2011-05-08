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



int main()
{
  std::ofstream ofs("filename", ios::binary);
  DataStruct ds(35, 1);
  
  CounterBase<DataStruct> g(ds);
  g.doCalculations();
  
 
  DataStruct sd(0,0); 
  CounterBase<DataStruct>  newg(sd);
  std::ifstream ifs("filename", ios::binary);
    {
	boost::archive::text_iarchive ia(ifs);
	ia >> newg;
        newg.d();
    }

 return 0;
}
