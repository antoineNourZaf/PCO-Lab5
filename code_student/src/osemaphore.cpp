/**
 *  PCO Labo 5 - Monitoring de concurrence
 *
 * @author Antoine NOURAZAR
 * @author Camilo PINEDA SERNA
 * @author Emmanuel SCHMID
 *
 * @file osemaphore.cpp
 *
 * Ce fichier définit la classe OSemaphore
 *
 */
#include "osemaphore.h"
#include "mythread.h"
#include <iostream>

int OSemaphore::compteur=0;

OSemaphore::OSemaphore(int n):name("Semaphore" + QString::number(compteur)),semaphore(new QSemaphore(n)), nbPermission(n)
{
    compteur++;
    WaitingLogger::getInstance()->creatQueueObject(this->name);
}

OSemaphore::~OSemaphore(){
    delete semaphore;
     WaitingLogger::getInstance()->rmQueueObject(this->name);
}


void OSemaphore::acquire(const QString& threadName){
    if(!tryAcquire()){
        WaitingLogger::getInstance()->addWaiting(threadName,name);
        semaphore->acquire();
        WaitingLogger::getInstance()->removeWaiting(threadName,name);
    }
}

void OSemaphore::release(){
    semaphore->release();
}

bool OSemaphore::tryAcquire(){
    return semaphore->tryAcquire();
}
