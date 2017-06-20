/**
 *  PCO Labo 5 - Monitoring de concurrence
 *
 * @author Antoine NOURAZAR
 * @author Camilo PINEDA SERNA
 * @author Emmanuel SCHMID
 *
 * @file omutex.h
 *
 * Ce fichier définit le classe omutex.
 * Cet objet de synchronisation sera augmenté de méthodes de logging (add/remove-RessourceAcces)
 *
 */
#ifndef PMUTEX_H
#define PMUTEX_H

#include <QMutex>
#include "waitinglogger.h"
#include "mythread.h"

class OMutex {
private:
    const QString name = "Mutex";
    QMutex mutex;

public:

    OMutex();
    ~OMutex();
    void lock(const QString& threadName);
    bool tryLock();
    void unlock();
};

#endif // PMUTEX_H
