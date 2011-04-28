template<class Data>
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
 time_t lastupdate = time(NULL);

 long testtime = 26;
 time_t start = time(NULL);

 while((time(NULL) - start) < testtime)
 {
  if ((time(NULL) - lastupdate) > deltat_) 
  {
   this->Save();
   lastupdate = time(NULL);
   cout << wynik_.x << endl;
  }
  this->Calculate();
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
