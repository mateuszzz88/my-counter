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
  /** 
   * mutex used by join() function.
   * If locked, it means calculations are in progress.
   * TODO find better way to join threads
   */
  boost::mutex mutexFinish; 
  

  Data wynik_;
  boost::posix_time::time_duration deltat_;
  bool stop;
//   boost::thread thrd; //problemy z przypisywaniem?
  
 
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
  void operator () (){
    doCalculations();
  }
  
  
  void d() {cout << wynik_.x << endl;} 
 protected:
  void Save();
  void Load();
  

  /** 
   * Does single step calculation.
   */
  virtual void Calculate(); 
};
