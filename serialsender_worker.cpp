#include "serialsender_worker.h"

SerialSender_worker::SerialSender_worker(QSerialPort *_port)
{
    port = _port;
}

SerialSender_worker::~SerialSender_worker(){

}

void SerialSender_worker::startSender(char *input, uint8_t len){
    qInfo()<<" Sender worker started ";
    buffer = new char(len);
    memcpy(buffer,input,len);
    start();
}

void SerialSender_worker::run(){

    if (buffer==nullptr){
        qDebug()<<"Empty buffer";
        return;
    }

    while(true){

        port->write(buffer);
        if(!port->waitForBytesWritten()){
            qDebug()<<"Serial Tx Timeout";
        }
        QThread::sleep(1);
    }
    free(buffer);
    buffer = nullptr;

}
