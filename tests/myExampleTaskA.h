/* 
 * File:   myExampleTaskA.h
 *
 * class shows example usage of MyCounter
 */
#ifndef MYEXAMPLETASKA_H
#define	MYEXAMPLETASKA_H

#include "../CounterBase/MyCounter.hpp"


// 1. First create structure to store calculation data
// In simple cases primitive types will do just fine

struct BigPrimeData {
    typedef long long VLong;
    // 1a. Create as many fields as You like, pointers are only slightly trickier
    VLong lastChecked;
    VLong *lastFound;
    VLong maxChecked;

    // 1b. If default constructors are not enough, create your own.
    // In simple cases shouldn't be necessary.

    BigPrimeData() :
    lastChecked(2),
    lastFound(new VLong(2)),
    maxChecked(100)
    {}

    /**
     * Copy constructor - will be used!
     */
    BigPrimeData(const BigPrimeData & other) :
    lastChecked(other.lastChecked),
    lastFound(new VLong(*other.lastFound)),
    maxChecked(other.maxChecked)
    {}

    /**
     * Function used in serialization proces;
     * It's sufficient to list all structure's fields in format:
     * ar & fieldName1;
     * ar & fieldName2;
     * ar & *pointer1;
     */
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & lastChecked;
        ar & *lastFound;
        ar & maxChecked;
    }
};

// 2. Now create worker class, derivate as shown

// 2a reimplement Calculate if task can be divided into sequential steps
template <>
void CounterBase<BigPrimeData>::Calculate();

// 2b typedef for easer usage
typedef CounterBase<BigPrimeData> myExampleTaskA;
    

#endif	/* MYEXAMPLETASKA_H */

