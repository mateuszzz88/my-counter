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
        ar & _data;
    }

    boost::posix_time::time_duration deltat_;
    volatile bool stop;
    volatile bool finished;
    boost::thread thrd;
    string serializationFilePath;
    boost::mutex serializationMutex;
    Data _data;
    mutable boost::mutex dataAccessMutex;

    boost::signal<void () > signalStarted;
    boost::signal<void () > signalStopped;
    boost::signal<void () > signalFinished;
    boost::signal<void () > signalStepDone;
    boost::signal<void () > signalSaved;

public:
    /**
     * @param startData  - initial data
     * @param serialPeriod - period (in seconds) of saving state of calculations
     */
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
    /**
     * sets finished state to given argument; for use in void Calculate()
     * @param finished
     */
    void setFinished(bool finished = true);
    /**
     * Checks whether calculations are finished or not
     * @return true if finished
     */
    bool isFinished() const;

    /**
     * Functions to add callbacks in events of:
     * * starting calculations (real start, not scheduling)
     * * stopping calculations (real)
     * * calculations finished
     * * single step of calculations finished
     * * data being saved to disk
     * @param slot callback function void funName()
     * @return signals::connection object that can be used to break connection
     */
    boost::signals::connection addSlotStarted(void (*slot)());
    boost::signals::connection addSlotStopped(void (*slot)());
    boost::signals::connection addSlotFinished(void (*slot)());
    boost::signals::connection addSlotStepDone(void (*slot)());
    boost::signals::connection addSlotSaved(void (*slot)());
    Data getDataCopy() const;
protected:

    /**
     * For use in Calculate(), gives access to data structure
     * @return
     */
    Data& data();

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
