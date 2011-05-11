#include "SignalCatcher.hpp"

template<class Data>
/** 
 * Funkcja rozpoczynająca obliczenia
 * TODO: wątek obliczeń.
 */
void CounterBase<Data>::doCalculations()
{
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

 while (!SIGINT_sent)
// while((boost::posix_time::microsec_clock::local_time() - start) < testtime)
 {
  if ((boost::posix_time::microsec_clock::local_time() - lastupdate) > deltat_) 
  {
   this->Save();
   lastupdate = boost::posix_time::microsec_clock::local_time();
   cout << wynik_.x << endl;
  }
  this->Calculate();
 }
 
 if (SIGINT_sent)
 {
  this->Save();
  this->d();
 }
}
/*Serializacja, zapis i odczyt, nic ciekawego, powinno działać*/
template<class Data>
void CounterBase<Data>::Save()
{
  
  std::ofstream ofs("filename", ios::binary);
  {
   boost::archive::text_oarchive oa(ofs);
   oa << *this;
  }
}

template<class Data>
void CounterBase<Data>::Load()
{
  std::ifstream ifs("filename", ios::binary);
  { 
   boost::archive::text_iarchive ia(ifs);
   ia >> *this;
  }
}
/*Ta funkcja w gotowym projekcie będzie abstrakcyjna, ale na razie nie chciałem się chrzanić z dziedziczeniem*/
template<class Data>
void CounterBase<Data>::Calculate()
{
  wynik_.x++;
  if(wynik_.x > 30) wynik_.x = 0;
}
