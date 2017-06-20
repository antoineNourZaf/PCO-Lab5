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
    AbstractReaderWriter *protocoleSema = new ReaderWriterSemaphoreEqualPrio();

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


