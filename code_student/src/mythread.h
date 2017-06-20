/**
 *  PCO Labo 5 - Monitoring de concurrence
 *
 * @author Antoine NOURAZAR
 * @author Camilo PINEDA SERNA
 * @author Emmanuel SCHMID
 *
 * @file mythread.h
 *
 * Cette classe va être instanciée plusieurs fois, une par lecteur et rédacteur qui seront en concurrence pour la ressource partagée.
 * Ils contieennent un pointeur sur un AbstractReaderWriter, qui seront en vrai une des dérivations de cette classe abstraite
 * par exemple implémentation avec HOARE et priorité égale).
 *
 * MyThread est dérivée deux fois, une pour les lecteurs, une pour les rédacteurs.
 */
#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include "abstractreaderwriter.h"
#include "synchrocontroller.h"

class MyThread : public QThread {
protected:
    AbstractReaderWriter *readerWriter;
    static int compteur; // pour numéroter les threads

public:
    MyThread(AbstractReaderWriter *protocole);

};

/**
 * @brief The ReaderThread class pour les threads de lecture
 */
class ReaderThread : public MyThread {
public:
    ReaderThread(AbstractReaderWriter* protcole);
    void run();
};

/**
 * @brief The WriterThread class pour les threads d'écriture
 */
class WriterThread : public MyThread {
public:
    WriterThread(AbstractReaderWriter* protcole);
    void run();
};

#endif // MYTHREAD_H
