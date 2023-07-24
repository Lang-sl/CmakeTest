#include "TimeThread.h"


TimeThread::TimeThread(QObject* parent) : QThread(parent)
{
    m_elapsedTimer.start();
    auth = 0;
    //setAutoDelete(true);
}


void TimeThread::run()
{
    //mutex.lock();
    while (true)
    {
        qint64 elapsed = m_elapsedTimer.elapsed();
        QString timeString = QString::asprintf("%02d:%02d:%02d", int(elapsed / 3600000),
            int((elapsed / 60000) % 60), int((elapsed / 1000) % 60));
        emit timeChanged(timeString);
        sleep(1);
        if (((elapsed / 10000) % 60) > 0 && auth == 0)
        {
            authRemind();
            break;
        }
    }
    //mutex.unlock();
}

void TimeThread::setAuthTrue()
{
    auth = true;
}


