#include "serialhandler.h"

Serialhandler::Serialhandler(QObject *parent)
    : QObject{parent}
{
    ser_receiver = new SerialReceiver_worker(&port);
    ser_sender  = new SerialSender_worker(&port);
    connect(ser_receiver,&QThread::finished,ser_receiver,&QObject::deleteLater);
    connect(ser_sender,&QThread::finished,ser_sender,&QObject::deleteLater);
    connect(ser_receiver,&SerialReceiver_worker::newData,this,&Serialhandler::print);


}

Serialhandler::~Serialhandler(){
    port.close();
    ser_receiver->quit();
    ser_receiver->wait();
    ser_sender->quit();
    ser_sender->wait();

}

void Serialhandler::serialInit(QString portname){

    port.setPortName(portname);
    port.setBaudRate(QSerialPort::Baud115200);
    port.setDataBits(QSerialPort::Data8);
    port.setStopBits(QSerialPort::OneStop);
    port.setParity(QSerialPort::NoParity);

    if(!port.open(QIODevice::ReadWrite)){
        qCritical()<<"Can't Open Port";
      }
    port.moveToThread(&port_thread);

    ser_receiver->startReceiver();

}

void Serialhandler::print(QByteArray data){
    qDebug()<<data;
}

void Serialhandler::send_to_INS(char *data, uint8_t len){

    ser_sender->startSender(data,len);
}
