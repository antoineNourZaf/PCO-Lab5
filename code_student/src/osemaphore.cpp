#include "osemaphore.h"

// TODO
OSemaphore::OSemaphore(int n) : nbPermission(n), condition(new QWaitCondition), mutex(new QMutex)
{

}


void OSemaphore::acquire(){

}

void OSemaphore::release(){

}

bool OSemaphore::tryAcquire(){

}
