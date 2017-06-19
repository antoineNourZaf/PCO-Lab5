/**
 *  PCO Labo 5 - Monitoring de concurrence
 *
 * @author Antoine NOURAZAR
 * @author Camilo PINEDA SERNA
 * @author Emmanuel SCHMID
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

#define NB_READER 4
#define NB_WRITER 4



using namespace std;

int main(int argc, char *argv[])
{
    // Create the resource manager object
    static SynchroController *syncCtrl = SynchroController::getInstance();
    AbstractReaderWriter *protocoleSema = new ReaderWriterSemaphoreEqualPrio(syncCtrl);

    ReaderThread *readers[NB_READER];
    WriterThread *writers[NB_WRITER];

    // Create & start the threads

    //Readers
    for (int t = 0; t < NB_READER; t++) {

        cout << "Creating the reader " << t << endl;
        readers[t] = new ReaderThread(t,protocoleSema,syncCtrl,"Lecter " + t);
        readers[t]->start();
    }

    //Writers
    for (int t = 0; t < NB_WRITER; t++) {

        cout << "Creating the writer " << t << endl;
        writers[t] = new WriterThread(t,protocoleSema,syncCtrl,"Writer " + t);
        writers[t]->start();
    }

    bool continuing = true;

    while (continuing) {
        cout << "Press <Enter> to continue monitor or <q> to exit" << endl;

        if(cin.get() == '\n'){
            SynchroController::getInstance()->resume();
        } else if (cin.get() == 'q' || cin.get() == 'Q' || cin.get() == 27) { // If key was <esc>
            continuing = false;
        }
    }

    for (int t = 0; t < NB_READER; t++) {
        readers[t]->wait();
    }

    for(int t = 0; t < NB_WRITER; t++) {
        writers[t]->wait();
    }

    // Kill the threads
    for (int i = 0; i < NB_READER; ++i) {
        //a little bit violent but it's fine
        readers[i]->terminate();
    }

    for (int i = 0; i < NB_WRITER; ++i) {
        writers[i]->terminate();
    }

    return 0;



    // Pour ceux qui voudraient développer une version graphique
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    return a.exec();
}
