#include "shutdownthread.h"

ShutdownThread::ShutdownThread()
{

}

ShutdownThread::~ShutdownThread()
{

}

void ShutdownThread::run()
{
    // countdown and shutdown at end of countdown
    // compare current date/time with scheduled sd date/time
    while(this->shutdown)
    {
        if (QDateTime::currentDateTime().secsTo(this->shutdownTime) <= 0)
        {
            // time to shutdown
            QProcess::startDetached("C:\\Windows\\System32\\notepad.exe");
            //QProcess::startDetached("C:\\Windows\\System32\\shutdown.exe /s /f /t 0");
            return;
        }

        QThread::sleep(1); // wait 1 second in between each check to avoid using too much resources
    }

    /* Return to exit thread. If program gets this far,
     * user has chosen not to shutdown system so process
     * needs to exit. */
    return;
}

QDateTime ShutdownThread::getDateTime() const
{
    return this->shutdownTime;
}

void ShutdownThread::cancelShutdown()
{
    this->shutdown = false;
    return;
}

void ShutdownThread::setDateTime(QDateTime time)
{
    this->shutdown = true;
    this->shutdownTime = time;
    return;
}
