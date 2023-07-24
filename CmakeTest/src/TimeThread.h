#pragma once
#pragma execution_character_set("utf-8")

#include <QThread>
#include <QElapsedTimer>
#include <QRunnable>
#include <QMutex>

class TimeThread : public QThread, public QRunnable
{
	Q_OBJECT
public:
	explicit TimeThread(QObject* parent = nullptr);

	void run() override;

	void setAuthTrue();

signals:
	void timeChanged(const QString& time);
	void authRemind();

private:
	QElapsedTimer m_elapsedTimer;
	QMutex mutex;
	bool auth;
};

