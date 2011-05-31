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

    BigPrimeData d = g.getData();

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
    d = g.getData();
    BOOST_CHECK(d.lastChecked==6);
    BOOST_CHECK(d.lastFound==5);

    return 0;
}
