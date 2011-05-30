/* 
 * File:   myExampleTaskA.h
 *
 * class shows example usage of MyCounter
 */
#ifndef MYEXAMPLETASKA_H
#define	MYEXAMPLETASKA_H

#include "MyCounter.hpp"


// 1. First create structure to store calculation data
// In simple cases primitive types will do just fine

struct BigPrimeData {
    // 1a. Create as many fields as You like
    long long lastChecked;
    long long lastFound;

    // 1b. If default constructors are not enough, create your own.
    // In simple cases shouldn't be necessary.

    BigPrimeData() :
    lastChecked(2),
    lastFound(2)
    {}

    /**
     * Copy constructor - will be used!
     */
    BigPrimeData(const BigPrimeData & other) :
    lastChecked(other.lastChecked),
    lastFound(other.lastFound)
    {}

    /**
     * Function used in serialization proces;
     * It's sufficient to list all structure's fields in format:
     * ar & fieldName1;
     * ar & fieldName2;
     */
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & lastChecked;
        ar & lastFound;
    }
};

// 2. Now create worker class, derivate as shown

// 2a reimplement Calculate if task can be divided into sequential steps
template <>
void CounterBase<BigPrimeData>::Calculate();

// 2b typedef for easer usage
typedef CounterBase<BigPrimeData> myExampleTaskA;
    

#endif	/* MYEXAMPLETASKA_H */

