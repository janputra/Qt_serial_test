#ifndef SERIALRECEIVER_WORKER_H
#define SERIALRECEIVER_WORKER_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QSerialPort>
#include <QDebug>

class SerialReceiver_worker : public QThread
{
    Q_OBJECT
public:
    explicit SerialReceiver_worker(QSerialPort *_port);
    ~SerialReceiver_worker();
    void startReceiver();
    void stopReceiver();

signals:
    void newData(QByteArray data);

private:
    void run() override;
    bool isRunning();
    bool running = false;
    mutable QMutex m_mutex;
    void receiver_thread();
    QSerialPort *port;

    void protocol_checker(QByteArray data);
    bool escape_found,stx_found;

    enum{
        STX= 0x02,
        ETX= 0x03,
        DLX= 0x10
    };

};

#endif // SERIALRECEIVER_WORKER_H
