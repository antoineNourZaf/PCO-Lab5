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

/*------------------------------------------------------------------------------
 * Class MyThread herite de QThread
 * Remarque: Cette classe n'est jamais instancié, elle permet l'héritage d'autre
 *           classe (ReaderThread, WriterThread)
 *------------------------------------------------------------------------------*/
class MyThread : public QThread {
protected:
    /* Tout les threads doivent avoir un protocole : paradigme Lecteur-Redacteur */
    AbstractReaderWriter *readerWriter;
    static int compteur; //Permet de fournir au thread un nom unique

public:
    /*------------------------------------------------------------------------------
     * But : Constructeur
     * Remarque: Ce super-constructeur est appelé lors de chaque instanciation de
     *           thread, puisque tout les threads doivent possèder un protocole.
     *------------------------------------------------------------------------------*/
    MyThread(AbstractReaderWriter *protocole);
};

/*------------------------------------------------------------------------------
 * Class ReaderThread herite de MyThread
 * Remarque: Ces threads représent les lecteurs (consulation d'une donnée)
 *------------------------------------------------------------------------------*/
class ReaderThread : public MyThread {
public:
    ReaderThread(AbstractReaderWriter* protcole);
    void run();
};

/*------------------------------------------------------------------------------
 * Class WriterThread herite de MyThread
 * Remarque: Ces threads représent les redacteurs (enregistrement d'une donnée)
 *------------------------------------------------------------------------------*/
class WriterThread : public MyThread {
public:
    WriterThread(AbstractReaderWriter* protcole);
    void run();
};

#endif // MYTHREAD_H
