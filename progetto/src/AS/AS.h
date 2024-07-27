#ifndef AS_AS_H_
#define AS_AS_H_

#include <omnetpp.h>
#include "../MESSAGGIO/pacchetto_m.h"
using namespace omnetpp;

class AS : public cSimpleModule {
    protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif /* AS_AS_H_ */
