/* 
 * File:   myExampleTaskA.cpp
 * Author: mateuszzz
 * 
 * Created on 28 maj 2011, 15:21
 */


#include "myExampleTaskA.h"
#include <math.h>

void myExampleTaskA::Calculate(){
    long long beingChecked = data.lastChecked + 1;
    bool isPrime = true;
    for (int i=2; i<=sqrt(beingChecked); i++){
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
}

