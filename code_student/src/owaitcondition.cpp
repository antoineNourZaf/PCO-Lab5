#include "owaitcondition.h"

OWaitCondition::OWaitCondition()
{

}

bool OWaitCondition::wait(OMutex *lockedMutex) {

    if (lockedMutex == nullptr)
        return false;


}

OWaitCondition::wakeOne() {
    //To Do
}

OWaitCondition::wakeAll() {
    //TODO
}

