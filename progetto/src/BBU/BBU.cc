#include "BBU.h"

Define_Module(BBU);
void BBU::initialize() {
    // at the beginning, the queue on the BBU is empty and it's not sending packets
    busy = false;
    spazio_occupato = 0;

    M = par("M");

    // register the signal to measure the time spent on BBU queue
    queueingTime = registerSignal("queueingTime");
}

void BBU::handleMessage(cMessage *msg) {
    // get the packet from the AS and cast it to the Packet format
    Packet* pacchetto = check_and_cast<Packet*>(msg);

    int dest = pacchetto->getCell();
    double size = pacchetto->getSize();

    // check the type of sending mode
    int test = getParentModule()->par("test").intValue();
    if(test == 1) { // compression mode
        // reduce the size of the packet before sending it
        size = size - size * (getParentModule()->par("Percentuale_compressione").intValue())/100;
    }

    if(msg->isSelfMessage()) {
        // if I receive a message from myself, it means that is a packet that has ended is sending time
        // and needs to be sent to the RRH specified by "dest"
        send(pacchetto, "out", dest);

        // free a place in the queue
        spazio_occupato--;

        // busy is a control variable for incoming packets. If it is false, there are no packet in output
        // so a new packet can be sent
        if(spazio_occupato == 0)
            busy = false;
    } else {
        if(busy) {
            // if the BBU is sending a packet, schedule the sending after the end of the transmission
            // of the previous packet
            simtime_t delay = lastPacketSendTime + size / M;    // lastPacketSendTime is the timestamp for the end of the transmission of the previous packet

            // the queueing time for an incoming packet is the difference between the end of the
            // transmission of the previous packet and the time that the incoming packet has arrived
            simtime_t qt = lastPacketSendTime - simTime();
            emit(queueingTime, lastPacketSendTime - simTime());

            // send the packet and update the last send
            scheduleAt(delay, pacchetto);
            lastPacketSendTime = delay;
        } else {
            // if there aren't packets in queue, the BBU can send a packet after size / M seconds
            busy = true;
            simtime_t send_time = size / M;

            // the queueing time is 0, because the packet is sent immediately
            simtime_t qt = 0;
            emit(queueingTime, 0);

            // send the packet and update the last send
            scheduleAt(simTime() + send_time, pacchetto);
            lastPacketSendTime = simTime() + send_time;
        }
        // the BBU is sending a packet, so I need to update the counter
        spazio_occupato++;
    }
}
