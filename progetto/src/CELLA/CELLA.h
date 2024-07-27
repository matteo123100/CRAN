#ifndef CELLA_CELLA_H_
#define CELLA_CELLA_H_
#include <omnetpp.h>
#include "../MESSAGGIO/pacchetto_m.h"
using namespace omnetpp;

class CELLA: public cSimpleModule {
    simsignal_t delaySignal;
protected:
   virtual void initialize();
   virtual void handleMessage(cMessage *msg);
};

#endif /* CELLA_CELLA_H_ */
