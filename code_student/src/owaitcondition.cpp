#include "owaitcondition.h"
#include "waitinglogger.h"

OWaitCondition::OWaitCondition(WaitingLogger* waitingLogger)
{
    logger = waitingLogger;
}

bool OWaitCondition::wait(OMutex *lockedMutex, const QString& threadName) {

    if (lockedMutex == nullptr)
        return false;

    logger->addWaiting(threadName, name);

    bool ret = qCond.wait(lockedMutex); // FIXME : il demande un second paramètre, mais y'en a un par défaut normalement.....
    logger->removeWaiting(threadName, name);


     return ret; // FIXME

}

void OWaitCondition::wakeOne(const QString& threadName) { // TODO : faut monitorer ? sinon virez le threadName
    logger->removeWaiting(threadName, name);
    qCond.wakeOne();

}

void OWaitCondition::wakeAll() {
    // TODO logger
    qCond.wakeAll();
}

