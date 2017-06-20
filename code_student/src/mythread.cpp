/**
 *  PCO Labo 5 - Monitoring de concurrence
 *
 * @author Antoine NOURAZAR
 * @author Camilo PINEDA SERNA
 * @author Emmanuel SCHMID
 *
 * @file mythread.cpp
 *
 * Ce fichier définit les classes MyThread et ses deux dérivés de lecture et d'écriture
 * L'action des threads sera d'accéder à la ressource (en lecture ou écriture) puis
 * d'attendre quelques secondes (entre 0 et 5), puis de quitter la ressource.
 *
 */

#include "mythread.h"
#include <iostream>

using namespace std;

int MyThread::compteur = 0;

/*-------------------------------------------------
 * Implémentation MyThread
 * ------------------------------------------------*/

MyThread::MyThread( AbstractReaderWriter *protocole)
{
    this->readerWriter = protocole;
    compteur++;
}

/*-------------------------------------------------
 * Implémentation ReaderThread
 * ------------------------------------------------*/
ReaderThread::ReaderThread(AbstractReaderWriter* protocole) : MyThread(protocole) {
    QThread::setObjectName("Reader" + QString::number(compteur));
}

void ReaderThread::run() {
    while (true) {
        readerWriter->lockReading(QThread::objectName());
        cout << "Task " << objectName().toStdString() << endl;
        /* Permet de mettre en attente le threads un petit instant */
        usleep((int)((float)50000*rand()/(RAND_MAX+1.0)));
        readerWriter->unlockReading(QThread::objectName());
    }
}

/*-------------------------------------------------
 * Implémentation WriterThread
 * ------------------------------------------------*/

WriterThread::WriterThread(AbstractReaderWriter* protocole) : MyThread(protocole) {
    QThread::setObjectName("Writer" + QString::number(compteur));
}

void WriterThread::run() {
    while (true) {
        readerWriter->lockWriting(QThread::objectName());
        cout << "Task " << objectName().toStdString() << endl;
        /* Permet de mettre en attente le threads un petit instant */
        usleep((int)((float)50000*rand()/(RAND_MAX+1.0)));
        readerWriter->unlockWriting(QThread::objectName());
    }
}
