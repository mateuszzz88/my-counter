#include <boost/test/minimal.hpp>
#include "myExampleTaskA.h"

int callsStepDone = 0;
int callsFinished = 0;
int callsStarted  = 0;
int callsStopped  = 0;
int callsSaved    = 0;

void slotStepDone() {
    ++callsStepDone;
}
void slotFinished() {
    ++callsFinished;
}
void slotStarted() {
    ++callsStarted;
}
void slotStopped() {
    ++callsStopped;
}
void slotSaved() {
    ++callsSaved;
}

int test_main( int, char *[] )
{
    myExampleTaskA g; //takes default constructor of BigPrimeData
    g.addSlotFinished(slotFinished);
    g.addSlotStepDone(slotStepDone);
    g.addSlotStarted(slotStarted);
    g.addSlotStopped(slotStopped);
    g.addSlotSaved(slotSaved);

    g.setSerializationFile("unittestdata", false);

    BigPrimeData d = g.getDataCopy();

    // assert initally everything is as expected
    BOOST_REQUIRE(callsStepDone == 0);
    BOOST_REQUIRE(callsFinished == 0);
    BOOST_REQUIRE(callsStarted == 0);
    BOOST_REQUIRE(callsStopped == 0);
    BOOST_REQUIRE(callsSaved == 0);
    BOOST_REQUIRE(!g.isFinished());

    // now start and let it check four next numbers (3,4,5,6)
    g.startCalculations();
    boost::this_thread::sleep(boost::posix_time::milliseconds(350));
    g.stopCalculations();
    BOOST_CHECK(callsStarted == 1);
    BOOST_CHECK(callsStopped == 1);
    BOOST_CHECK(!g.isFinished());
    d = g.getDataCopy();
    BOOST_CHECK(d.lastChecked==6);
    BOOST_CHECK(d.lastFound==5);
    BOOST_CHECK(callsStepDone==4);
    BOOST_CHECK(callsSaved==1);


    //create new calculation thread, this time load data
    callsStepDone = callsStarted = callsStopped = 0;
    myExampleTaskA h;
    h.addSlotFinished(slotFinished);
    h.addSlotStepDone(slotStepDone);
    h.addSlotStarted(slotStarted);
    h.addSlotStopped(slotStopped);
    h.addSlotSaved(slotSaved);
    h.setSerializationFile("unittestdata", true); //loading data

    //assert data is the same
    BigPrimeData d2 = h.getDataCopy();
    BOOST_CHECK(d.lastChecked==d2.lastChecked);
    BOOST_CHECK(d.lastFound==d2.lastFound);
    
    h.startCalculations();
    h.join();
    BOOST_CHECK(h.isFinished());
    BOOST_CHECK(callsStarted == 1);
    BOOST_CHECK(callsFinished    == 1);
    BigPrimeData d3 = h.getDataCopy();
    BOOST_CHECK(d3.lastChecked==100);
    BOOST_CHECK(d3.lastFound==97);


    return 0;
}
