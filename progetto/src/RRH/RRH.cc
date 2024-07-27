#include "RRH.h"

Define_Module(RRH);
void RRH::initialize() {
    // at the beginning the queue is empty and the RRH is not sending packets
    busy = false;
    spazio_occupato = 0;
}

void RRH::handleMessage(cMessage *msg){
    int test = getParentModule()->par("test").intValue();

    // receive and cast the packet
    Packet* pacchetto = check_and_cast<Packet*>(msg);

    // checking the modality of sending by the BBU
    if(test == 0) { // no compression
        // forward the packet directly to the cell
        send(pacchetto,"out_packet");
    }
    if(test == 1){  // compression
        // get the compression ratio and set the decompression time
        int percentuale_compressione = getParentModule()->par("Percentuale_compressione").intValue();
        double tempo_decompressione = ((double)percentuale_compressione/100) * 0.05;

        // if the percentage is 0, the RRH work as the no compression mode
        if(percentuale_compressione == 0){
            send(pacchetto, "out_packet");
        }else{
            if(msg->isSelfMessage()){
                // if I receive a message from myself, it means that the decompression
                // stage is terminated and I can send the packet to the cell.
                // The queue is managed in the same way as the BBU.
                send(pacchetto, "out_packet");
                spazio_occupato--;
                if(spazio_occupato == 0)
                    busy = false;
            }else{
                if(busy){
                    // if the RRH is sending a packet, schedule the incoming packet
                    // after the end of the previous transmission + the decompression time
                    simtime_t delay = lastPacketSendTime + tempo_decompressione;
                    scheduleAt(delay, pacchetto);
                    lastPacketSendTime = delay;
                }else{
                    // if the RRH is not sending a packet, schedule the incoming packet
                    // after the decompression time
                    busy = true;
                    scheduleAt(simTime() + tempo_decompressione, pacchetto);
                    lastPacketSendTime = simTime() + tempo_decompressione;
                }
                spazio_occupato++;
            }
        }
    }
}
