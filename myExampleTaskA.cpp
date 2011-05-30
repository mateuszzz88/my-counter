/* 
 * File:   myExampleTaskA.cpp
 * Author: mateuszzz
 * 
 * Created on 28 maj 2011, 15:21
 */


#include "myExampleTaskA.h"
#include <math.h>

template <>
void CounterBase<BigPrimeData>::Calculate() {
    long long beingChecked = data.lastChecked + 1;
    bool isPrime = true;
    for (int i=2; i<=sqrt(beingChecked); ++i){
        if (beingChecked%i==0){
            isPrime = false;
            break;
        }
    }
    data.lastChecked = beingChecked;
    if (isPrime) {
        data.lastFound = beingChecked;
    }
    //TODO when to end?
    //Answer: Kiedy skończy się zakres long long
    //Przykładowo:
    //if (beingChecked == 9223372036854775806) stop = true;
}

