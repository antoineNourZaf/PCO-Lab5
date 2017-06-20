/**
 *  PCO Labo 5 - Monitoring de concurrence
 *
 * @author Antoine NOURAZAR
 * @author Camilo PINEDA SERNA
 * @author Emmanuel SCHMID
 *
 * @file omutex.h
 *
 * Ce fichier déclare le classe omutex.
 * Cet objet de synchronisation sera augmenté de méthodes de logging (add/remove-RessourceAcces).
 * Nous n'avons pas voulu implémenté un mutex homemade, nous sommes parties sur un Qmutex
 * existant auquel nous avons ajouté les loggs.
 *
 */

#ifndef PMUTEX_H
#define PMUTEX_H

#include <QMutex>
#include "waitinglogger.h"
/*------------------------------------------------------------------------------
 * Class OMutex permettant le monitoring de sa file d'attente
 * Remarque: Implémenter à l'aide Qmutex
 *------------------------------------------------------------------------------*/
class OMutex {
private:
    const QString name;     //Nom de l'objet : MutexX, X : numéro attributé
    static int compteur;    //Permet de fournir un nom unique
    QMutex* mutex;

public:
    /*------------------------------------------------------------------------------
     * Constructeur : Instancie Qmutex, attribution d'un nom et création d'une
     *                file d'attente dans le WaitingLogger.
     *------------------------------------------------------------------------------*/
    OMutex();

    /*------------------------------------------------------------------------------
     * Destructeur : Supprimer en mémoire le Qmutex ainsi que supprime la file
     *               d'attente dans le WaitingLogger.
     *------------------------------------------------------------------------------*/
    ~OMutex();

    /*------------------------------------------------------------------------------
     * Getter : Permet de récuper le mutex. Utiliser : OwaitCondition.wait()
     *------------------------------------------------------------------------------*/
    QMutex* getMutex();

    /*------------------------------------------------------------------------------
     * But : lock comme pour Qmutex lock(), mais fait appel aux méthodes de
     *       WaitingLogger pour logguer.
     * Paramètre : threadName - nom du thread qui effectue la demande
     *------------------------------------------------------------------------------*/
    void lock(const QString& threadName);

    /*------------------------------------------------------------------------------
     * But : unlock comme pour Qmutex unlock().
     * Remarque : Ici, aucun log n'est nécessaire. (pas de file d'attente)
     *------------------------------------------------------------------------------*/
    void unlock();

    /*------------------------------------------------------------------------------
     * But : trylock comme pour Qmutex trylock().
     * Remarque : Ici, aucun log n'est nécessaire. (pas de file d'attente)
     *------------------------------------------------------------------------------*/
    bool tryLock();
};

#endif // PMUTEX_H
