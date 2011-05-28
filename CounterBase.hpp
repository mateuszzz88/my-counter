#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>


/*Deklaracja klasy, na razie nie jest abstrakcyjna, ale będzie, póki co lepiej się w to nie bawić
 * bo tak jest łatwiej testować*/

/** 
 * Data - klasa do przechowywania wynikow; 
 *        musi implementować metodę serialize oraz komplet konstruktorów.
 */
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
  boost::posix_time::time_duration deltat_;
  bool stop;
  boost::thread thrd; 
  
 
 public:
  CounterBase(const Data& start):         wynik_(start), deltat_(boost::posix_time::seconds(5)) {};
  CounterBase(const Data* start):         wynik_(start), deltat_(boost::posix_time::seconds(5)) {};
  CounterBase(const Data& start, long t): wynik_(start), deltat_(boost::posix_time::seconds(t)) {};
  CounterBase(const Data* start, long t): wynik_(start), deltat_(boost::posix_time::seconds(t)) {};
  CounterBase(long t):                                   deltat_(boost::posix_time::seconds(t)) {}
 
  CounterBase(): deltat_(boost::posix_time::seconds(5)) {};
  
  /**
   * Starts calculations thread. 
   * Encapsulates doCalculations();
   */
  void startCalculations();  
  
  /** 
   * Stops calculations; blocks until stopped;
   */
  void stopCalculations(); 
  
  /** 
   * Blocks current thread until calculations are finished;
   */
  void join();
  
  /** 
   * Starts calculations in synchronous mode (in the same thread).
   * If possible, only void Calculate() should be reimplemented
   */
  virtual void doCalculations();
  
  /** 
   * See @doCalculations()
   */
  void operator () (){
    doCalculations();
  }
  
  
  void d() {cout << wynik_.x << endl;} 
 protected:
  /**
   * Saves class state to file
   */
  void Save();
  /**
   * Loads class state from file
   */
  void Load();
  

  /** 
   * Does single step calculation. 
   * Main task of user is to reimplement this class. 
   * If given task can't be divided into series of identical steps, 
   * doCalculations() should be reimplemented (together with periodic calls to @Save())
   */
  virtual void Calculate(); 
};
