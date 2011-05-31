#include "myExampleTaskA.h"
#include <math.h>

// 3 implement worker class's Calculate function
template <>
void CounterBase<BigPrimeData>::Calculate()
{
    // 3c. inspect and modify data property in any way necessary to complete task
    long long beingChecked = data().lastChecked + 1;
    bool isPrime = true;
    for (int i = 2; i <= sqrt(beingChecked); ++i) {
        if (beingChecked % i == 0) {
            isPrime = false;
            break;
        }
    }
    data().lastChecked = beingChecked;
    if (isPrime) {
        *(data().lastFound) = beingChecked;
    }

    //sleep() is needed only for presentational purposes - allows to
    // predict outcome of calculations after given time.
    boost::this_thread::sleep(boost::posix_time::milliseconds(100));
    
    // 3a when final outcome is achieved, call setFinished(true) to notify
    // all interested about finished task and stop calculation loop.
    // This step is optional, calculations can be expected to be stopped manually.
    if (data().lastChecked >= data().maxChecked)
        setFinished(true);
}

