/**
 *  PCO Labo 5 - Monitoring de concurrence
 *
 * @author Antoine NOURAZAR
 * @author Camilo PINEDA SERNA
 * @author Emmanuel SCHMID
 *
 * @file osemaphore.h
 *
 * Cette classe rédécalre l'objet de synchronisation sémaphore,
 * en ajoutant les fonctionnalités de logging. Elle utilise QSemaphore.
 *
 */
#ifndef PSEMAPHORE_H
#define PSEMAPHORE_H

#include <QSemaphore>
#include "waitinglogger.h"

class OSemaphore {
private:
    static int compteur;
    const QString name;
    QSemaphore *semaphore;
    const int nbPermission;

public:
    OSemaphore(int n = 0);
    ~OSemaphore();

    /**
     * @brief acquire comme pour QSemaphore, mais loggue l'action
     * grâce aux methodes de WaitingLogger
     * @param threadName
     */
    void acquire(const QString & threadName);
    void release();
    bool tryAcquire();

};

#endif // PSEMAPHORE_H
