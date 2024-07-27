#include "AS.h"

Define_Module(AS);
void AS::initialize() {
    // create a message to start the generation of packets to send
    cMessage *msg = new cMessage("init");
    scheduleAt(simTime(), msg);
}

void AS::handleMessage(cMessage *msg){
    int lognormal_test = getParentModule()->par("lognormal_test").intValue();
    if (msg->isSelfMessage()){
        // creation of the packet
        Packet* pacchetto= new Packet("pacchetto");

        // initialization of the packet
        double size;
        if (lognormal_test == 0){   // exponential distribution of S
            double meanS = 1/par("lamdaS").doubleValue();
            size = exponential(meanS,0);
        } else { // lognormal distribution of S
            double meanS = par("mediaS").doubleValue();
            double varS = 0.8325546111576977;   // varS is the standard deviation
            size = lognormal(meanS, varS,0);
        }
        pacchetto->setSize(size);
        int N = par("N");
        int cella = intuniform(0,N - 1,2);
        pacchetto->setCell(cella);
        pacchetto->setTimestamp(simTime());

        // send the packet to the BBU
        send(pacchetto,"out");
    }

    // set up the next generation time
    simtime_t time;
    double meanT = 1 / par("lamdaT").doubleValue();
    time = exponential(meanT,1);

    // schedule the creation of a new packet
    scheduleAt(simTime() + time, msg);
}
