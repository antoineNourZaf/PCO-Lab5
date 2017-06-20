/**
 *  PCO Labo 5 - Monitoring de concurrence
 *
 * @author Antoine NOURAZAR
 * @author Camilo PINEDA SERNA
 * @author Emmanuel SCHMID
 *
 * @file owaitcondition.h
 *
 * Cette classe redéclare une Wait Condition, augmentés de methodes de logging
 * Elle utilise la classe QWaitCondition
 *
 */
#ifndef PWAITCONDITION_H
#define PWAITCONDITION_H

#include <QWaitCondition>
#include "omutex.h"

/*------------------------------------------------------------------------------
 * Class OWaitCondition permettant le monitoring de sa file d'attente
 * Remarque: Implémenter à l'aide QWaitCondition
 *------------------------------------------------------------------------------*/
class OWaitCondition
{
private:
    QWaitCondition* qCond;
    static int compteur;   //Permet de fournir un nom unique (numéro)
    const QString name;    //Nom de l'objet : WaitConditionX, X : numéro attributé

public:
    /*------------------------------------------------------------------------------
     * Constructeur : Instancie QwaitCondition, attribution d'un nom et création d'une
     *                file d'attente dans le WaitingLogger.
     *------------------------------------------------------------------------------*/
    OWaitCondition();
    /*------------------------------------------------------------------------------
     * Destructeur : Supprimer en mémoire la QwaitCondition ainsi que supprime la file
     *               d'attente dans le WaitingLogger.
     *------------------------------------------------------------------------------*/
    ~OWaitCondition();

    /*------------------------------------------------------------------------------
     * But : wait comme pour QwaitCondition, mais loggue l'action grâce aux methodes
     *       de WaitingLogger.
     * Paramètre : OMutex * lockedMutex - Mutex qui doit être relacher (correspont
     *             au mutex implemnté par nos soins)
     *             threadName - nom du thread qui effectue la demande
     *------------------------------------------------------------------------------*/
    bool wait(OMutex *lockedMutex,const QString& threadName);

    /*------------------------------------------------------------------------------
     * But : wakeAll comme pour QwaitCondition.
     * Remarque : Ici, aucun log n'est nécessaire. (pas de file d'attente)
     *------------------------------------------------------------------------------*/
    void wakeAll();

    /*------------------------------------------------------------------------------
     * But : wakeOne comme pour QwaitCondition.
     * Remarque : Ici, aucun log n'est nécessaire. (pas de file d'attente)
     *------------------------------------------------------------------------------*/
    void wakeOne();

};

#endif // PWAITCONDITION_H
