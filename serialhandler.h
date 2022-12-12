#ifndef SERIALHANDLER_H
#define SERIALHANDLER_H

#include <QObject>
#include <QDebug>
#include "serialreceiver_worker.h"
#include "serialsender_worker.h"

class Serialhandler : public QObject
{
    Q_OBJECT
public:
    explicit Serialhandler(QObject *parent = nullptr);
    ~Serialhandler();
    void serialInit(QString portname);
    void send_to_INS(char *data, uint8_t len);
    void read_INS_message();
    void proc_INS_message();

public slots:
    void print(QByteArray data);
   // void startWaiting_for_respond();
private:

    QSerialPort port;
    SerialReceiver_worker *ser_receiver;
    SerialSender_worker *ser_sender;
    QThread port_thread;
};

#endif // SERIALHANDLER_H
