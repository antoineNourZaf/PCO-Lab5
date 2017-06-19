#include "synchrocontroller.h"

SynchroController::SynchroController()
{
    semaphore = new QSemaphore();
}


SynchroController *SynchroController::getInstance()
{
    static SynchroController *instance = new SynchroController();
    return instance;
}

void SynchroController::pause()
{
    semaphore->acquire();
}

void SynchroController::resume()
{
    semaphore->release();
}
