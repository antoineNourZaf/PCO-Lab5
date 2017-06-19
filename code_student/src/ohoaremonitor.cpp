#include "ohoaremonitor.h"

OHoareMonitor::Condition::Condition() :
    waitingSem(new OSemaphore(0)), nbWaiting(0)
{

}

OHoareMonitor::OHoareMonitor() :
    monitorMutex(new OSemaphore(1)), monitorSignal(new OSemaphore(0)), monitorNbSignal(0)
{

}

OHoareMonitor::~OHoareMonitor() {
    delete monitorSignal;
    delete monitorMutex;
}

void OHoareMonitor::monitorIn(const QString& threadName) {
    monitorMutex->acquire(threadName);
}


void OHoareMonitor::monitorOut() {
    if (monitorNbSignal > 0) {
        monitorSignal->release();
    }
    else {
        monitorMutex->release();
    }
}

void OHoareMonitor::wait(Condition &cond, const QString& threadName) {
    cond.nbWaiting++;

}

void OHoareMonitor::signal(Condition &cond, const QString& threadName) {

}
