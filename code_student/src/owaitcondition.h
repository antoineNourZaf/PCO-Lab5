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

class OWaitCondition
{
private:
    QWaitCondition* qCond;
    static int compteur;
    const QString name;
public:

    OWaitCondition();
    ~OWaitCondition();

    bool wait(OMutex *lockedMutex,const QString& threadName);

    void wakeAll();

    void wakeOne();

};

#endif // PWAITCONDITION_H
