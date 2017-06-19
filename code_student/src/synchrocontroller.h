#ifndef SYNCHROCONTROLLER_H
#define SYNCHROCONTROLLER_H

#include <QSemaphore>

class SynchroController
{
    QSemaphore* semaphore;
    SynchroController();
public:
    static SynchroController *getInstance();

    void pause();

    void resume();
};

#endif // SYNCHROCONTROLLER_H
