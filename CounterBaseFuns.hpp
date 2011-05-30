#include "SignalCatcher.h"
#include <boost/bind.hpp>
using namespace std;


template<class Data>
CounterBase<Data>::CounterBase(const Data& startData, long savePeriod)
: data(startData), deltat_(boost::posix_time::seconds(savePeriod))
{}

template<class Data>
CounterBase<Data>::CounterBase(long savePeriod)
: data(Data()), deltat_(boost::posix_time::seconds(savePeriod))
{}

template<class Data>
void CounterBase<Data>::startCalculations()
{
  stop = false;
  cout<<"startCalculations() => attempting to start calculation thread" <<endl;
  thrd = boost::thread(boost::bind(&CounterBase<Data>::doCalculations,this));
}

template<class Data>
void CounterBase<Data>::join()
{
        cout << "join() - attempting to join threads"<<endl;
	if (thrd.joinable()){
		thrd.join();
		cout <<"join() - threads joined"<<endl;
	} else {
		cout <<"join() - thread not joinable"<<endl;
	}
}

template<class Data>
void CounterBase<Data>::stopCalculations()
{
  cout <<"stopCalculations() => calculations scheduled to stop"<<endl;
  stop=true;
  join();
}



template<class Data>
void CounterBase<Data>::doCalculations()
{
  cout <<"doCalculations() => calculations are started" <<endl << flush;
   
/**********************************************************/
/*Tą funkcję modyfikujesz przede wszystkim. W tym momencie*/
/*wywołuje ona trwającą 26 sekund (testtime) pętlę while. */
/*Wnętrze pętli while co deltat_ sekund robi backup, a    */
/*przy każdej iteracji wywołuje funkcję liczącą.          */
/*Twoje zadanie: zamiast wywoływać whila funkcja ma odplić*/
/*dwa wątki: jeden, który będzie wywoływał pętlę while z  */
/*tymi samymi bebechami, ale innym warunkiem, a drugi,    */
/*który będzie czekał na polecenie użytkownika zmieniające*/
/*warunek pętli z true na false. Nie wiem, czy w c++ są   */
/*takie listenery jak w Javie, ale jakiś sposób na pewno  */
/*znajdziesz.                                             */
/**********************************************************/
 boost::posix_time::ptime lastupdate = boost::posix_time::microsec_clock::local_time();

 boost::posix_time::time_duration testtime(boost::posix_time::seconds(26));
 boost::posix_time::ptime start = boost::posix_time::microsec_clock::local_time();

 signal(SIGINT, catch_int);
 signal(SIGTSTP, catch_tstp);
 signal(SIGCONT, catch_cont);
 signal(SIGTERM, catch_term);
 signal(SIGUSR1, catch_usr1);

 while (!SIGINT_sent && !stop)
// while((boost::posix_time::microsec_clock::local_time() - start) < testtime)
 {
  if ((boost::posix_time::microsec_clock::local_time() - lastupdate) > deltat_) 
  {
   this->Save();
   lastupdate = boost::posix_time::microsec_clock::local_time();
//   cout << data.x << endl;
  }

  if (!SIGTSTP_sent)
  {
   this->Calculate();
  }
  
  if (SIGUSR1_sent)
  {
    this->Save();
    SIGUSR1_sent = 0;
  }
  
 }
 
 if (SIGINT_sent)
 {
  this->Save();
  cout << "Calculations stopped." << endl;
//  this->d();
 }
}

/*Serializacja, zapis i odczyt, nic ciekawego, powinno działać*/
template<class Data>
void CounterBase<Data>::Save()
{
    std::ofstream ofs(serializationFilePath.c_str(), std::ios::binary);
    {
        boost::mutex::scoped_lock(serializationMutex);
        boost::archive::text_oarchive oa(ofs);
        oa << *this;
    }
}

template<class Data>
bool CounterBase<Data>::Load()
{
    bool success = false;
    std::ifstream ifs(serializationFilePath.c_str(), std::ios::binary);
    if (ifs.is_open()) {
        try {
            boost::mutex::scoped_lock(serializationMutex);
            boost::archive::text_iarchive ia(ifs);
            ia >> *this;
            success=true;
        } catch (boost::archive::archive_exception ex) {
            cout << "Load(): failed to load file '" << serializationFilePath << "'\n"
                    << "because boost::archive::archive_exception was caught: \n"
                    << ex.what() << endl;
        }
    } else { // !ifs.is_open()
        cout << "Load(): failed to load file '" << serializationFilePath << "'\n"
                << "file probably desn't exist or is not readable" << endl;
    }
    return success;
}
/*Ta funkcja w gotowym projekcie będzie abstrakcyjna, ale na razie nie chciałem się chrzanić z dziedziczeniem*/
template<class Data>
void CounterBase<Data>::Calculate()
{
//  task specific => deleted
//  data.x++;
//  if(data.x > 30) data.x = 0;*/
}


template<class Data>
void CounterBase<Data>::setSerializationFile(string filePath, bool load){
    serializationFilePath = filePath;
    if (load)
        Load();
}
