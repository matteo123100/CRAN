#ifndef BBU_BBU_H_
#define BBU_BBU_H_
#include <omnetpp.h>
#include <vector>
#include "../MESSAGGIO/pacchetto_m.h"
using namespace omnetpp;

class BBU: public cSimpleModule {
    int M;
    bool busy;
    int spazio_occupato;
    simsignal_t queueingTime;
    simtime_t lastPacketSendTime;
protected:
   virtual void initialize();
   virtual void handleMessage(cMessage *msg);
};

#endif /* BBU_BBU_H_ */
