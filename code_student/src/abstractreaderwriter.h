/**
 *  PCO Labo 5 - Monitoring de concurrence
 *
 * @author Antoine NOURAZAR
 * @author Camilo PINEDA SERNA
 * @author Emmanuel SCHMID
 *
 * @file abstractreaderwriter.h
 *
 * Cette classe définit les lecteurs-rédacteurs utilisés dans les threads. Ils héritent tous de la classe AbstractReaderWriter,
 * pour redéfinir les méthodes lock/unlock-reading/writing. Chacune de ces quatre méthodes sera implémentée dans les fichiers
 * rwHoare/Mesa/Semaphore.cpp selon deux priorités : égale entre lecteurs et redacteurs ainsi que priorité aux rédacteurs.
 *
 */

#ifndef ABSTRACTREADERWRITER_H
#define ABSTRACTREADERWRITER_H

#include "synchrocontroller.h"
#include "waitinglogger.h"
#include "osemaphore.h"
#include "ohoaremonitor.h"

/**
 * @brief The AbstractReaderWriter class, mêre de tous les lecteurs-redacteurs
 */
class AbstractReaderWriter {
public:
    /**
     * @brief lockReading appelée par les threads lorsqu'ils veulent un accès en lecture
     * @param name le nom du thread qui appelle la méthode
     */
    virtual void lockReading(const QString& name)   = 0;

    /**
     * @brief lockWriting appelée par les threads l'orsqu'ils veulent un accès en écriture
     * @param name le nom du thread qui appelle la méthode
     */
    virtual void lockWriting(const QString& name)   = 0;

    /**
     * @brief unlockReading appelée par les threads à la fin de la lecture, pour libéréer l'accès à la ressource
     * @param name le nom du thread qui appelle la méthode
     */
    virtual void unlockReading(const QString& name) = 0;

    /**
     * @brief unlockWriting appelée par les threads à la fin de l'écriture, pour libérer l'accsè à la ressource
     * @param name le nom du thread qui appelle la méthode
     */
    virtual void unlockWriting(const QString& name) = 0;
};

// **************************************************
// *                  Priorité egale
// ***************************************************

/**
 * @brief The ReaderWriterSemaphoreEqualPrio class
 * implémentation par sémaphore, avec une priorité égale pour les lecteurs comme pour les rédacteurs.
 */
class ReaderWriterSemaphoreEqualPrio : public AbstractReaderWriter {
protected:
    int nbReader;
    OSemaphore* mutex; // accès à la nbReaders
    OSemaphore* fifo; // file d'attente pour tout le monde
    OSemaphore* writer; // le premier lecteur bloque les rédacteurs ET un rédacteur bloque tt le monde

public:

    ReaderWriterSemaphoreEqualPrio();
    virtual ~ReaderWriterSemaphoreEqualPrio();
    virtual void lockReading(const QString& name);
    virtual void lockWriting(const QString& name);
    virtual void unlockReading(const QString& name);
    virtual void unlockWriting(const QString& name);
};

// **************************************************
// *             Redacteurs prioritaire
// **************************************************

/**
 * @brief The ReaderWriterSemaphoreWritersPrio class
 * implémentation par sémaphore, avec une priorité aux rédacteurs
 */
class RWSemaphorePrioWriter : public AbstractReaderWriter {
protected:
    OSemaphore* mutexReaders;
    OSemaphore* mutexWriters;
    OSemaphore* writer;
    OSemaphore* reader;
    OSemaphore* mutex;
    int nbReaders, nbWriters;

public:
    RWSemaphorePrioWriter();
    virtual ~RWSemaphorePrioWriter();
    virtual void lockReading(const QString& name);
    virtual void lockWriting(const QString& name);
    virtual void unlockReading(const QString& name);
    virtual void unlockWriting(const QString& name);
};


/**
 * @brief The ReaderWriterHoarWritersPrio class
 */
class ReaderWriterHoareWritersPrio : public AbstractReaderWriter, public OHoareMonitor {
protected:
    Condition waitWriting;
    Condition waitReading;
    int nbReaders;
    bool writingInProgress;
    int nbWritersWaiting;

public:
    ReaderWriterHoareWritersPrio();
    ~ReaderWriterHoareWritersPrio();

    virtual void lockReading(const QString& name);
    virtual void lockWriting(const QString& name);
    virtual void unlockReading(const QString& name);
    virtual void unlockWriting(const QString& name);
};




#endif // ABSTRACTREADERWRITER_H
