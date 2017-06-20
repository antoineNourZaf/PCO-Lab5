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

/*------------------------------------------------------------------------------
 * Class OSemaphore permettant le monitoring de sa file d'attente
 * Remarque: Implémenter à l'aide QSemaphore
 *------------------------------------------------------------------------------*/
class OSemaphore {
private:
    QSemaphore *semaphore;
    const int nbPermission;
    static int compteur;     //Permet de fournir un nom unique
    const QString name;      //Nom de l'objet : MutexX, X : numéro attributé

public:
    /*------------------------------------------------------------------------------
     * Constructeur : Instancie Qsemaphore, attribution d'un nom et création d'une
     *                file d'attente dans le WaitingLogger.
     *------------------------------------------------------------------------------*/
    OSemaphore(int n = 0);

    /*------------------------------------------------------------------------------
     * Destructeur : Supprimer en mémoire le Qsemaphore ainsi que supprime la file
     *               d'attente dans le WaitingLogger.
     *------------------------------------------------------------------------------*/
    ~OSemaphore();

    /*------------------------------------------------------------------------------
     * But : Acquire comme pour QSemaphore, mais loggue l'action grâce aux methodes
     *       de WaitingLogger.
     * Paramètre : threadName - nom du thread qui effectue la demande
     *------------------------------------------------------------------------------*/
    void acquire(const QString & threadName);

    /*------------------------------------------------------------------------------
     * But : relase comme pour QSemaphore.
     * Remarque : Ici, aucun log n'est nécessaire. (pas de file d'attente)
     *------------------------------------------------------------------------------*/
    void release();

    /*------------------------------------------------------------------------------
     * But : tryAcquire comme pour QSemaphore.
     * Remarque : Ici, aucun log n'est nécessaire. (pas de file d'attente)
     *------------------------------------------------------------------------------*/
    bool tryAcquire();

};

#endif // PSEMAPHORE_H
