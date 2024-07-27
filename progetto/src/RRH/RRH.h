#ifndef RRH_RRH_H_
#define RRH_RRH_H_
#include <omnetpp.h>
using namespace omnetpp;
#include "../MESSAGGIO/pacchetto_m.h"
class RRH : public cSimpleModule{
    bool busy;
    int spazio_occupato;
    simtime_t lastPacketSendTime;

protected:
   virtual void initialize();
   virtual void handleMessage(cMessage *msg);
};

#endif /* RRH_RRH_H_ */
