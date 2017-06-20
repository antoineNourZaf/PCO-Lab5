/**
 *  PCO Labo 5 - Monitoring de concurrence
 *
 * @author Antoine NOURAZAR
 * @author Camilo PINEDA SERNA
 * @author Emmanuel SCHMID
 *
 * @file mythread.h
 *
 * Voici notre implementation du laboratoire :
 *
 * Le but est d'avoir divers treads qui implémentent différents protocoles de lecteurs-redacteurs.
 * Nous avons voulu implémenter une version avec priorité aux rédacteurs
 * et une avec priorité égale pour les lecteurs comme pour les rédacteurs.
 *
 * Chacun de ses protocoles peut être implémenté grâce à différents objets de synchronisation :
 * Sémpahores, moniteur de Hoare et moniteur de Mesa.
 *
 * La classe AbstractReaderWriter va être dérivée pour chacun des protocoles implémenté avec chacun des objets de synchronisation.
 * Dans cette dernière sont définits tous les protocoles (comme ReaderWriterSemaphoreEqualPrio).
 * Leur implémentation est dans le fichier readerwriter.cpp
 *
 * Nous devons également "wrapper" les objets de synchronisation offerts par le langage.
 * Ainsi, QSemaphore, QMutex et QWaitCondition deviennent OSemaphore, OMutex et OWaitCondition.
 * Ces derniers vont être monitorés, c'est-à-dire qu'en plus de fonctionner comme objets de synchronisation
 * ils permettront d'afficher des messages et d'interagir avec l'utilisateur.
 * Cette interaction et monitoring se fait grâce aux classes WaitingLogger et SynchroController.
 *
 */
#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include "abstractreaderwriter.h"
#include "synchrocontroller.h"

class MyThread : public QThread {
protected:
    AbstractReaderWriter *readerWriter;
    static int compteur;

public:

    MyThread(AbstractReaderWriter *protocole);

};


class ReaderThread : public MyThread {
public:

    ReaderThread(AbstractReaderWriter* protcole);
    void run();
};

class WriterThread : public MyThread {
public:

    WriterThread(AbstractReaderWriter* protcole);
    void run();
};

#endif // MYTHREAD_H
