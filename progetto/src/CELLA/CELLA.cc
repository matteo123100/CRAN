#include "CELLA.h"

Define_Module(CELLA);
void CELLA::initialize() {
    // register the signal to measure the end-to-end delay of a packet
    delaySignal = registerSignal("delay");
}

void CELLA::handleMessage(cMessage *msg){
    // receive and cast the packet
    Packet* pacchetto = check_and_cast<Packet*>(msg);

    // calculate the end-to-end delay
    simtime_t diff = simTime() - pacchetto->getTimestamp();
    emit(delaySignal,diff);

    // delete the incoming packet
    delete msg;
}
