/*Deklaracja klasy, na razie nie jest abstrakcyjna, ale będzie, póki co lepiej się w to nie bawić
 * bo tak jest łatwiej testować*/
template<class Data>
class CounterBase
{
 private:
  friend class boost::serialization::access;
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
   ar & wynik_;
  }     

  Data wynik_;
  long deltat_;
  
 
 public:
  CounterBase(const Data& start):         wynik_(start), deltat_(5) {};
  CounterBase(const Data* start):         wynik_(start), deltat_(5) {};
  CounterBase(const Data& start, long t): wynik_(start), deltat_(t) {};
  CounterBase(const Data* start, long t): wynik_(start), deltat_(t) {};
  CounterBase(long t):                                   deltat_(t) {}
 
  CounterBase(): deltat_(5) {};
  
  void doCalculations();
  void d() {cout << wynik_.x << endl;} 
 protected:
  void Save();
  void Load();
  virtual void Calculate(); 
};
