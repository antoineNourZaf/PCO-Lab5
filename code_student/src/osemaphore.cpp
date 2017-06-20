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

OSemaphore::OSemaphore(int n): semaphore(new QSemaphore(n)),nbPermission(n),name("Semaphore" + QString::number(compteur))
{
    compteur++;
    WaitingLogger::getInstance()->creatQueueObject(this->name);
}

OSemaphore::~OSemaphore(){
    delete semaphore;
    WaitingLogger::getInstance()->rmQueueObject(this->name);
}

void OSemaphore::acquire(const QString& threadName){
    /* Si on arrive pas à acquire, alors il y a une file d'attente */
    if(!tryAcquire()){
        WaitingLogger::getInstance()->addWaiting(threadName,name);
        semaphore->acquire();
        /* Une fois passé le acquire, le thread ne se trouve plus dans
           la file d'attente */
        WaitingLogger::getInstance()->removeWaiting(threadName,name);
    }
}

void OSemaphore::release(){
    semaphore->release();
}

bool OSemaphore::tryAcquire(){
    return semaphore->tryAcquire();
}
