#ifndef SERIALSENDER_WORKER_H
#define SERIALSENDER_WORKER_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QSerialPort>
#include <QDebug>

class SerialSender_worker : public QThread
{
    Q_OBJECT
public:
    explicit SerialSender_worker(QSerialPort *_port);
    ~SerialSender_worker();
    void startSender(char *input, uint8_t len);

signals:
    void waitforRespond();
private:
    void run() override;
    mutable QMutex m_mutex;
    QSerialPort *port;
    char *buffer;
};

#endif // SERIALSENDER_WORKER_H
