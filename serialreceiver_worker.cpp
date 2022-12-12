#include "serialreceiver_worker.h"

SerialReceiver_worker::SerialReceiver_worker(QSerialPort *_port)
{
   port = _port;
}

SerialReceiver_worker::~SerialReceiver_worker(){

}

void SerialReceiver_worker::startReceiver(){
    const QMutexLocker locker(&m_mutex);
    running = true;
    start();

}

void SerialReceiver_worker::receiver_thread(){

    while(running){

        if(port->waitForReadyRead(10)){

            QByteArray rec_data = port->readAll();
            emit newData(rec_data);

        }
    }
}


void SerialReceiver_worker::stopReceiver(){
    const QMutexLocker locker(&m_mutex);
    running = false;
}

void SerialReceiver_worker::run(){
    qInfo()<<" Receiver worker started ";
    receiver_thread();
}

void SerialReceiver_worker::protocol_checker(QByteArray data){

    for (auto ch :data){

        if (escape_found){

            if(ch==STX){
                 stx_found=true;
            }else if(ch==ETX){
                 break;
            }else{
                if (stx_found){
                    qDebug()<<QString::number(ch,16); // passing ch to Queue (other threading) or signals ByteArray
                }
            }
            escape_found=false;

        }else{

            if(ch==DLX){
                escape_found=true;
            }else{
                if (stx_found){
                    qDebug()<<QString::number(ch,16);  // passing ch to Queue (other threading) or signals ByteArray
                }
            }
        }
    }
}
