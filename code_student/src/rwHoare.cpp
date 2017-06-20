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

ReaderWriterHoareWritersPrio::ReaderWriterHoareWritersPrio() : nbReaders(0), writingInProgress(false), nbWritersWaiting(0)
{

}

ReaderWriterHoareWritersPrio::~ReaderWriterHoareWritersPrio() {

}

void ReaderWriterHoareWritersPrio::lockReading(const QString& threadName) {
    monitorIn(threadName);
    if ((writingInProgress) || (nbWritersWaiting > 0)) { // les lecteurs n'ont pas la priorité sur les rédacteurs, donc on vérifie qu'aucun rédacteur n'attend
        wait(waitReading, threadName);
        signal(waitReading, threadName);
    }
    nbReaders++;
    monitorOut();
    //Accès ressources
    ((ReadWriteLogger*) WaitingLogger::getInstance())->addResourceAccess(threadName);
}

void ReaderWriterHoareWritersPrio::lockWriting(const QString& threadName) {
    monitorIn(threadName);
    if ((nbReaders > 0) || (writingInProgress)) {
        nbWritersWaiting++; // le rédacteur attent la libération d'un rédacteur ou d'un lecteur
        wait(waitWriting, threadName);
        nbWritersWaiting--;
    }
    writingInProgress = true;
    monitorOut();
    //Accès ressources
    ((ReadWriteLogger*) WaitingLogger::getInstance())->addResourceAccess(threadName);
}

void ReaderWriterHoareWritersPrio::unlockReading(const QString& threadName) {
    //Fin accès ressources
    ((ReadWriteLogger*) WaitingLogger::getInstance())->removeResourceAccess(threadName);

    monitorIn(threadName);
    nbReaders--;
    if (nbReaders == 0) { // le dernier lecteur
        signal(waitWriting, threadName); // libère la rédaction
    }
    monitorOut();
}

void ReaderWriterHoareWritersPrio::unlockWriting(const QString& threadName) {
    //Fin accès ressources
    ((ReadWriteLogger*) WaitingLogger::getInstance())->removeResourceAccess(threadName);
    monitorIn(threadName);
    writingInProgress = false;
    if (nbWritersWaiting >0) { // si d'autres rédacteurs attendent,
        signal(waitWriting, threadName); // ils ont la priorité
    }
    else {
        signal(waitReading, threadName); // sinon les lecteurs peuvent passer
    }
    monitorOut();
}

