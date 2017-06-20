/**
 *  PCO Labo 5 - Monitoring de concurrence
 *
 * @author Antoine NOURAZAR
 * @author Camilo PINEDA SERNA
 * @author Emmanuel SCHMID
 *
 * @file omutex.cpp
 *
 * Ce fichier définit le classe Omutex.
 */

#include "omutex.h"
#include "waitinglogger.h"

int OMutex::compteur=0;

OMutex::OMutex() : mutex(new QMutex()),name("Mutex" + QString::number(compteur))
{
    WaitingLogger::getInstance()->creatQueueObject(this->name);
    compteur++;
}

OMutex::~OMutex(){
    delete mutex;
    WaitingLogger::getInstance()->rmQueueObject(this->name);
}

void OMutex::lock(const QString& threadName){
    /* Si on arrive pas à lock, alors il y a une file d'attente */
    if(!tryLock()){
        WaitingLogger::getInstance()->addWaiting(threadName,name);
        mutex->lock();
        /* Une fois passé le lock, le thread ne se trouve plus dans
           la file d'attente */
        WaitingLogger::getInstance()->removeWaiting(threadName,name);
    }
}

bool OMutex::tryLock(){
    return mutex->tryLock();
}

void OMutex::unlock(){
    mutex->unlock();
}

QMutex* OMutex::getMutex(){
    return mutex;
}
