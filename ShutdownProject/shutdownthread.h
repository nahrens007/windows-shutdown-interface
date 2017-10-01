#ifndef SHUTDOWNTHREAD_H
#define SHUTDOWNTHREAD_H

#include <QThread>
#include <QDateTime>
#include <QProcess> // needed for shut down command

class ShutdownThread : public QThread
{
    Q_OBJECT

public:
    ShutdownThread();
    ~ShutdownThread();
    QDateTime getDateTime() const;
    void cancelShutdown();
    void setDateTime(QDateTime time);

private:
    QDateTime shutdownTime;
    bool shutdown; // should the process still shutdown the PC

protected:
    void run();

};

#endif // SHUTDOWNTHREAD_H
