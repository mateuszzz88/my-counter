#ifndef COUNTERBASEFUNS
#define COUNTERBASEFUNS
#include "SignalCatcher.h"
#include "CounterBase.hpp"
#include <boost/bind.hpp>
#include <boost/thread.hpp>
using namespace std;

template<class Data>
CounterBase<Data>::CounterBase(const Data& startData, long savePeriod)
: _data(startData), deltat_(boost::posix_time::seconds(savePeriod)),
stop(false), finished(false) {
}

template<class Data>
CounterBase<Data>::CounterBase(long savePeriod)
: _data(Data()), deltat_(boost::posix_time::seconds(savePeriod)),
stop(false), finished(false) {
}

template<class Data>
void CounterBase<Data>::startCalculations() {
    stop = false;
    finished = false;
    cout << "startCalculations() => attempting to start calculation thread" << endl;
    thrd = boost::thread(boost::bind(&CounterBase<Data>::doCalculations, this));
}

template<class Data>
void CounterBase<Data>::join() {
    cout << "join() - attempting to join threads" << endl;
    if (thrd.joinable()) {
        thrd.join();
        cout << "join() - threads joined" << endl;
    } else {
        cout << "join() - thread not joinable" << endl;
    }
}

template<class Data>
void CounterBase<Data>::stopCalculations() {
    cout << "stopCalculations() => calculations scheduled to stop" << endl;
    stop = true;
    join();
}

template<class Data>
void CounterBase<Data>::doCalculations() {
    try {
        cout << "doCalculations() => calculations are started" << endl << flush;
        signalStarted();
        boost::posix_time::ptime lastupdate = boost::posix_time::microsec_clock::local_time();

        signal(SIGTSTP, catch_tstp);
        signal(SIGINT, catch_int);
        signal(SIGCONT, catch_cont);
        signal(SIGTERM, catch_term);
        signal(SIGUSR1, catch_usr1);


        while (!stop && !isFinished() && !SIGINTorTERM_sent) {
            if ((boost::posix_time::microsec_clock::local_time() - lastupdate) > deltat_) {
                this->Save();
                lastupdate = boost::posix_time::microsec_clock::local_time();
            }
            if (!SIGTSTP_sent)
            {
              this->Calculate();
            }

            if (SIGUSR1_sent)
            {
              this->Save();
              sleep(100);
              SIGUSR1_sent=0;
            }
            signalStepDone();
        }

        this->Save();
        cout << "Calculations stopped." << endl;
        if (isFinished()) {
            signalFinished();
        } else if (stop) {
            signalStopped();
        }
    } catch (const std::exception& ex) {
        cout << "Caught std::exception in CouterBase class: "<<endl
                <<ex.what() <<endl
                <<"Abandoning calculations."<<endl;
    } catch (...) {
        cout << "Caught nonstandard exception in CouterBase class."<<endl
                <<"Abandoning calculations."<<endl;
    }
}

template<class Data>
void CounterBase<Data>::Save() {
    std::ofstream ofs(serializationFilePath.c_str(), std::ios::binary);
    {
        boost::mutex::scoped_lock(serializationMutex);
        boost::archive::text_oarchive oa(ofs);
        oa << *this;
    }
    signalSaved();
}

template<class Data>
bool CounterBase<Data>::Load() {
    bool success = false;
    std::ifstream ifs(serializationFilePath.c_str(), std::ios::binary);
    if (ifs.is_open()) {
        try {
            boost::mutex::scoped_lock(serializationMutex);
            boost::archive::text_iarchive ia(ifs);
            ia >> *this;
            success = true;
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

template<class Data>
void CounterBase<Data>::Calculate() {
    cout << ("CounterBase<Data>::Calculate() should be reimplemented in specialized template!");
}

template<class Data>
void CounterBase<Data>::setSerializationFile(string filePath, bool load) {
    serializationFilePath = filePath;
    if (load)
        Load();
}

template<class Data>
void CounterBase<Data>::setFinished(bool finished) {
    this->finished = finished;
}

template<class Data>
bool CounterBase<Data>::isFinished() const {
    return finished;
}

template<class Data>
boost::signals::connection CounterBase<Data>::addSlotFinished(void(*slot)()) {
    return signalFinished.connect(boost::bind(slot));
}

template<class Data>
boost::signals::connection CounterBase<Data>::addSlotStarted(void(*slot)()) {
    return signalStarted.connect(boost::bind(slot));
}

template<class Data>
boost::signals::connection CounterBase<Data>::addSlotStopped(void(*slot)()) {
    return signalStopped.connect(boost::bind(slot));
}

template<class Data>
boost::signals::connection CounterBase<Data>::addSlotSaved(void(*slot)()) {
    return signalSaved.connect(boost::bind(slot));
}

template<class Data>
boost::signals::connection CounterBase<Data>::addSlotStepDone(void(*slot)()) {
    return signalStepDone.connect(boost::bind(slot));
}

template<class Data>
Data CounterBase<Data>::getDataCopy() const {
    dataAccessMutex.lock();
    Data ret = _data;
    dataAccessMutex.unlock();
    return ret;
}

template<class Data>
Data& CounterBase<Data>::data() {
    boost::mutex::scoped_lock sc(dataAccessMutex);
    return _data;
}

#endif //COUNTERBASEFUNS
