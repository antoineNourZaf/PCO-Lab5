/**
 *  PCO Labo 5 - Monitoring de concurrence
 *
 * @author Antoine NOURAZAR
 * @author Camilo PINEDA SERNA
 * @author Emmanuel SCHMID
 *
 * @file rwHoare.cpp
 *
 * Ce fichier définit les lecteurs-redacteurs implémentés par des moniteurs de Hoare,
 * avec deux priorités
 */

#include "abstractreaderwriter.h"

RWHoareWritersPrio::RWHoareWritersPrio() : nbReaders(0), writingInProgress(false), nbWritersWaiting(0)
{
}

RWHoareWritersPrio::~RWHoareWritersPrio() {
}

void RWHoareWritersPrio::lockReading(const QString& threadName) {
    SynchroController::getInstance()->pause();
    monitorIn(threadName);
    if ((writingInProgress) || (nbWritersWaiting > 0)) { // les lecteurs n'ont pas la priorité sur les rédacteurs, donc on vérifie qu'aucun rédacteur n'attend
        wait(waitReading, threadName);
        signal(waitReading, threadName);
    }
    nbReaders++;
    //Accès ressources
    ((ReadWriteLogger*) WaitingLogger::getInstance())->addResourceAccess(threadName);
    monitorOut();
}

void RWHoareWritersPrio::lockWriting(const QString& threadName) {
    SynchroController::getInstance()->pause();
    monitorIn(threadName);
    if ((nbReaders > 0) || (writingInProgress)) {
        nbWritersWaiting++; // le rédacteur attent la libération d'un rédacteur ou d'un lecteur
        wait(waitWriting, threadName);
        nbWritersWaiting--;
    }
    writingInProgress = true;
    //Accès ressources
    ((ReadWriteLogger*) WaitingLogger::getInstance())->addResourceAccess(threadName);
    monitorOut();
}

void RWHoareWritersPrio::unlockReading(const QString& threadName) {
    SynchroController::getInstance()->pause();
    monitorIn(threadName);
    nbReaders--;
    if (nbReaders == 0) { // le dernier lecteur
        signal(waitWriting, threadName); // libère la rédaction
    }
    //Fin accès ressources
    ((ReadWriteLogger*) WaitingLogger::getInstance())->removeResourceAccess(threadName);
    monitorOut();
}

void RWHoareWritersPrio::unlockWriting(const QString& threadName) {
    SynchroController::getInstance()->pause();
    monitorIn(threadName);
    writingInProgress = false;
    if (nbWritersWaiting >0) { // si d'autres rédacteurs attendent,
        signal(waitWriting, threadName); // ils ont la priorité
    }
    else {
        signal(waitReading, threadName); // sinon les lecteurs peuvent passer
    }
    //Fin accès ressources
    ((ReadWriteLogger*) WaitingLogger::getInstance())->removeResourceAccess(threadName);
    monitorOut();
}

