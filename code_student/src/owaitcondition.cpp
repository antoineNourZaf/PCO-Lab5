/**
 *  PCO Labo 5 - Monitoring de concurrence
 *
 * @author Antoine NOURAZAR
 * @author Camilo PINEDA SERNA
 * @author Emmanuel SCHMID
 *
 * @file owaitcondition.cpp
 *
 * Ce fichier définit la classe OWaitCondition.
 * Les méthodes font appelle aux méthodes du singleton WaitingLogger
 *
 */
#include "owaitcondition.h"

int OWaitCondition::compteur=0;

OWaitCondition::OWaitCondition() : qCond(new QWaitCondition()), name("WaitCondition" + QString::number(compteur))
{
    WaitingLogger::getInstance()->creatQueueObject(this->name);
    compteur++;
}

OWaitCondition::~OWaitCondition(){
    delete qCond;
     WaitingLogger::getInstance()->rmQueueObject(this->name);
}

bool OWaitCondition::wait(OMutex *lockedMutex,const QString& threadName) {
    /* Si le mutex en paramètre est null inutile d'aller plus loin */
    if (lockedMutex == nullptr)
        return false;

    WaitingLogger::getInstance()->addWaiting(threadName,name);
    bool status = qCond->wait(lockedMutex->getMutex());
    WaitingLogger::getInstance()->removeWaiting(threadName,name);
    return status;
}

void OWaitCondition::wakeOne() {
    qCond->wakeOne();
}

void OWaitCondition::wakeAll() {
    qCond->wakeAll();
}

