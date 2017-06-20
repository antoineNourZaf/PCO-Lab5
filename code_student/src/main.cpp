/**
 *  PCO Labo 5 - Monitoring de concurrence
 *
 * @author Antoine NOURAZAR
 * @author Camilo PINEDA SERNA
 * @author Emmanuel SCHMID
 *
 * @file main.cpp
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
#include <QApplication>
#include <iostream>

#include "mythread.h"

#define NB_READER 1
#define NB_WRITER 20

using namespace std;

// Kill the threads
void killThreads(ReaderThread** readers, WriterThread** writers){
    for (int i = 0; i < NB_READER; ++i) {
        //a little bit violent but it's fine
        readers[i]->terminate();
    }

    for (int i = 0; i < NB_WRITER; ++i) {
        writers[i]->terminate();
    }
}

int main(int argc, char *argv[])
{
    ReaderThread *readers[NB_READER];
    WriterThread *writers[NB_WRITER];

    // Create the resource manager object
    AbstractReaderWriter *protocoleSema = new RWHoareWritersPrio();

    // Create & start the threads
    //Readers
    for (int t = 0; t < NB_READER; t++) {
        readers[t] = new ReaderThread(protocoleSema);
        readers[t]->start();
    }
    //Writers
    for (int t = 0; t < NB_WRITER; t++) {
        writers[t] = new WriterThread(protocoleSema);
        writers[t]->start();
    }

    bool continuing = true;
    cout << "Start monitoring "<<endl;
    while (continuing) {
        char input = cin.get();
        if(input == '\n'){
            SynchroController::getInstance()->resume(); 
        } else if (input == 'q' || input == 'Q' || input == 27) { // If key was <esc>
            cout << "Exit the monitoring programme ! " << endl;
            killThreads(readers, writers);
            continuing = false;
        }
        cin.clear();
    }

    /* Attente de la fin de l'exécution des différents threads */
    for (int t = 0; t < NB_READER; t++) {
        readers[t]->wait();
    }

    for(int t = 0; t < NB_WRITER; t++) {
        writers[t]->wait();
    }

    return 0;
}


