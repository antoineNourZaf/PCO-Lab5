/**
 *  PCO Labo 5 - Monitoring de concurrence
 *
 * @author Antoine NOURAZAR
 * @author Camilo PINEDA SERNA
 * @author Emmanuel SCHMID
 *
 * @file ohoaremonitor.cpp
 *
 * Ce fichier définit le classe OHoareMonitor.
 */

#include "ohoaremonitor.h"

int OHoareMonitor::compteur=0;

OHoareMonitor::Condition::Condition() :
    waitingSem(new OSemaphore(0)), nbWaiting(0)
{

}

OHoareMonitor::OHoareMonitor() :
    monitorMutex(new OSemaphore(1)), monitorSignal(new OSemaphore(0)), monitorNbSignal(0), name("HoareMonitor" + QString::number(compteur))
{
    WaitingLogger::getInstance()->creatQueueObject(this->name);
    compteur++;
}

OHoareMonitor::~OHoareMonitor() {
    delete monitorSignal;
    delete monitorMutex;
    WaitingLogger::getInstance()->rmQueueObject(this->name);
}

void OHoareMonitor::monitorIn(const QString& threadName) {
    if(!monitorMutex->tryAcquire()){
        WaitingLogger::getInstance()->addWaiting(threadName,name);
        monitorMutex->acquire(threadName);
        WaitingLogger::getInstance()->removeWaiting(threadName,name);
    }
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
    WaitingLogger::getInstance()->addWaiting(threadName,name);
    cond.nbWaiting++;
    if (monitorNbSignal > 0) {
        monitorSignal->release();
    }
    else {
        monitorMutex->release();
    }
    WaitingLogger::getInstance()->removeWaiting(threadName,name);
    if(!cond.waitingSem->tryAcquire()){
        WaitingLogger::getInstance()->addWaiting(threadName,name);
        cond.waitingSem->acquire(threadName);
        WaitingLogger::getInstance()->removeWaiting(threadName,name);
    }
    cond.nbWaiting--;
}

void OHoareMonitor::signal(Condition &cond, const QString& threadName) {
    if (cond.nbWaiting > 0) {
        monitorNbSignal++;
        cond.waitingSem->release();
        monitorSignal->acquire(threadName);
        monitorNbSignal--;
    }
}
