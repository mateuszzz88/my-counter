#ifndef COUNTERBASE_HPP
#define COUNTERBASE_HPP

#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/signal.hpp>
#include <iostream>
#include <fstream>
using namespace std;


/*Deklaracja klasy, na razie nie jest abstrakcyjna, ale będzie, póki co lepiej się w to nie bawić
 * bo tak jest łatwiej testować*/

/** 
 * Data - klasa do przechowywania wynikow; 
 *        musi implementować metodę serialize oraz komplet konstruktorów.
 */
template<class Data>
class CounterBase : public boost::signals::trackable {
private:
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & data;
    }

    boost::posix_time::time_duration deltat_;
    volatile bool stop;
    volatile bool finished;
    boost::thread thrd;
    string serializationFilePath;
    boost::mutex serializationMutex;

    boost::signal<void () > signalStarted;
    boost::signal<void () > signalStopped;
    boost::signal<void () > signalFinished;
    boost::signal<void () > signalStepDone;
    boost::signal<void () > signalSaved;

public:
    CounterBase(const Data& startData, long serialPeriod = 5);
    CounterBase(long serialPeriod = 5);

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
    void operator () () {
        doCalculations();
    }

    /**
     * Sets file to use for serialization
     * @param filePath - path to serialization file
     * @param load - if true, load state from file
     */
    void setSerializationFile(string filePath, bool load = true);
    void setFinished(bool finished);
    bool isFinished() const;

    boost::signals::connection addSlotStarted(void (*slot)());
    boost::signals::connection addSlotStopped(void (*slot)());
    boost::signals::connection addSlotFinished(void (*slot)());
    boost::signals::connection addSlotStepDone(void (*slot)());
    boost::signals::connection addSlotSaved(void (*slot)());


    //  void d() {std::cout << data.x << endl;}
protected:

    Data data;
    /**
     * Saves class state to file
     */
    void Save();
    /**
     * Loads class state from file
     * @return true if load successful
     */
    bool Load();

    /** 
     * Does single step calculation. 
     * Main task of user is to reimplement this class. 
     * If given task can't be divided into series of identical steps, 
     * doCalculations() should be reimplemented (together with periodic calls to @Save())
     */
    virtual void Calculate();
};


#endif //COUNTERBASE_HPP
