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

/* Constantes permettant de fixer le nombre de threads reader et writer */
#define NB_READER 15
#define NB_WRITER 10

using namespace std;

/*------------------------------------------------------------------------------
 * But: Arrêt les threads en cours d'exécution
 * Remarque: Les threads sont arreté d'une façon un peu brute
 * Paramètres : 2 tableaux de pointeurs contenant les différents threads (reader,
 *              et writer)
 *------------------------------------------------------------------------------*/
void killThreads(ReaderThread** readers, WriterThread** writers){
    for (int i = 0; i < NB_READER; ++i) {
        readers[i]->terminate();
    }
    for (int i = 0; i < NB_WRITER; ++i) {
        writers[i]->terminate();
    }
}

/*------------------------------------------------------------------------------
 * But: Création, Exécution et contrôles des différents threads
 * Remarque: Afin de pouvoir tester les implémentations, il faut décommenter la
 *           ligne souhaité.
 *------------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    // Create the resource manager object
    AbstractReaderWriter *protocoleSema = new RWSemaphorePrioWriter();

    // Create & start the threads
    ReaderThread *readers[NB_READER];
    WriterThread *writers[NB_WRITER];

    // Readers
    for (int t = 0; t < NB_READER; t++) {
        readers[t] = new ReaderThread(protocoleSema);
        readers[t]->start();
    }
    // Writers
    for (int t = 0; t < NB_WRITER; t++) {
        writers[t] = new WriterThread(protocoleSema);
        writers[t]->start();
    }

    bool continuing = true;
    cout << "Start monitoring : <Enter> to continue, <q> or <esc> to exit" << endl;
    while (continuing) {
        char input = cin.get();
        if(input == '\n'){
            SynchroController::getInstance()->resume(); //Debloque le thread
        } else if (input == 'q' || input == 'Q' || input == 27) { // If key was <q>, <Q> or <esc>
            cout << "Exit the monitoring programme ! " << endl;
            killThreads(readers, writers);
            continuing = false;
        }
        cin.clear();
    }

    return 0;
}


