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

    // Create the threads

    // Start the threads

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
    char key;
    cin >> key;
    while (continuing) {
        cout << "Press <Enter> to continue monitor or <esc> to exit" << endl;

        // Wait for a key press
        cin >> key;

        if(cin.get() == '\n'){
            SynchroController::getInstance()->resume();
        } else {
            // If key was <esc>
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

    return 0;



    // Pour ceux qui voudraient développer une version graphique
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    return a.exec();
}
