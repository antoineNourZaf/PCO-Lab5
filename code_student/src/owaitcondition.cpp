#include "owaitcondition.h"

OWaitCondition::OWaitCondition()
{

}

bool OWaitCondition::wait(OMutex *lockedMutex) {

    if (lockedMutex == nullptr)
        return false;

    lockedMutex->unlock();
    //juste to skip warning
    return true;
}

void OWaitCondition::wakeOne() {

}

void OWaitCondition::wakeAll() {
    //TODO
}

