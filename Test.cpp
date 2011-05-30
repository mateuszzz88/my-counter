#include <iostream>
#include <boost/bind.hpp>
#include "myExampleTaskA.h"
// #include<fstream>
// #include<boost/date_time/posix_time/posix_time.hpp>
// #include<unistd.h>
// #include<signal.h>

using namespace std;

// #include"DataStruct.hpp"
// #include"CounterBase.hpp"
// #include"CounterBaseFuns.hpp"

void manualTest();

void onSignalStepDone()
{
    cout << "." << flush;
}

int main()
{

    manualTest();
    return 0;
}

void manualTest()
{
    BigPrimeData ds;
    myExampleTaskA g(ds, 5);
    //myExampleTaskA g; //takes default constructor of BigPrimeData
    g.setSerializationFile("sfilename", true);
    //  g.addSlotStepDone(boost::bind(onSignalStepDone)); //TODO why doesn't work??
    //  g.addSlotStepDone(onSignalStepDone);
    string avilableCommands =
            "avilable commands: \n"
            "help      - shows this list, \n"
            "exit      - closes test program, \n"
            "start_syn - starts calculations in main thread, \n"
            "start     - creates calculations thread, \n"
            "join      - waits for calculations thread to finish, \n"
            "stop      - stops calculations thread\n";
    cout << avilableCommands;
    string input;

    while (1) {
        cin >> input;
        if (input == "exit" || input == "quit") {
            return;
        } else if (input == "start") {
            g.startCalculations();
        } else if (input == "stop") {
            g.stopCalculations();
        } else if (input == "start_syn") {
            g.doCalculations();
        } else if (input == "join") {
            g.join();
        } else {
            cout << "command not understood: " << input << endl << avilableCommands << flush;
        }
    }
}
