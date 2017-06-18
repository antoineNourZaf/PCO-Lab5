
#include <QApplication>
#include <iostream>

#include "synchrocontroller.h"
#include "abstractreaderwriter.h"
#include "mythread.h"

#define NB_READER 4
#define NB_WRITER 4

using namespace std;

int main(int argc, char *argv[])
{

    // Create the resource manager object
    AbstractReaderWriter *protocoleSema = new ReaderWriterSemaphore();
    SynchroController *syncCtrl = SynchroController::getInstance();

    ReaderThread *readers[NB_READER];
    WriterThread *writers[NB_WRITER];

    // Create the threads

    // Start the threads

    // Readers
    for(int t = 0; t<NB_READER; t++){
        cout << "Creating the reader " << t << endl;
        readers[t] = new ReaderThread(t,protocoleSema,syncCtrl);
        readers[t]->start();
    }
    for(int t = 0; t<NB_WRITER; t++){
        cout << "Creating the writer " << t << endl;
        writers[t] = new WriterThread(t,protocoleSema,syncCtrl);
        writers[t]->start();
    }
    for(int t=0; t<NB_READER; t++) {
        readers[t]->wait();
    }

    for(int t=0; t<NB_WRITER; t++) {
        writers[t]->wait();
    }

    bool continuing = true;

    while (continuing) {
        // Wait for a key press

        // If key is <enter>
        SynchroController::getInstance()->resume();

        // If key was <esc>
        continuing = false;
    }

    // Kill the threads

    return 0;



    // Pour ceux qui voudraient développer une version graphique
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    return a.exec();
}
