/**
 *  PCO Labo 5 - Monitoring de concurrence
 *
 * @author Antoine NOURAZAR
 * @author Camilo PINEDA SERNA
 * @author Emmanuel SCHMID
 *
 * Voici notre implementation du laboratoire :
 */
#include <QApplication>
#include <iostream>

#include "mythread.h"

#define NB_READER 3
#define NB_WRITER 0

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

        cout << "Creating/Starting the reader " << t << endl;
        readers[t] = new ReaderThread(t,protocoleSema,syncCtrl, "Reader" + QString::number(t));
        readers[t]->start();
    }

    //Writers
    for (int t = 0; t < NB_WRITER; t++) {

        cout << "Creating/Starting the writer " << t << endl;
        writers[t] = new WriterThread(t,protocoleSema,syncCtrl,"Writer" + QString::number(t));
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

    /* Attente de la fin de l'exécution des différents threads */
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
