#include <QCoreApplication>
#include "serialhandler.h"
#include <QSerialPort>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    /*
    Serialhandler handler;

    handler.serialInit("/dev/ttyUSB0");
    QString tset= "HELLO WORLD";

    handler.send_to_INS((char *)tset.toStdString().c_str(),(uint8_t)tset.length());
    */

    /*
    QSerialPort port;
    port.setPortName("/dev/ttyUSB0");
    port.setBaudRate(QSerialPort::Baud115200);
    port.setDataBits(QSerialPort::Data8);
    port.setStopBits(QSerialPort::OneStop);
    port.setParity(QSerialPort::NoParity);

    SerialReceiver_worker worker(&port);



    worker.startReceiver();
*/

    char dlx =0x10;
    char stx = 0x02;
    char etx = 0x03;

    char data[]= {dlx,stx, 0x1 ,0x2,0x3,0x4,0x5,0x6,0x7,dlx,etx};

    bool escape_found, stx_found;

    escape_found= false;
    stx_found = false;
    for (auto ch :data){

        if (escape_found){

            if(ch==stx){
                 stx_found=true;
            }else if(ch==etx){
                 break;
            }else{
                if (stx_found){
                    qDebug()<<QString::number(ch,16);
                }
            }
            escape_found=false;

        }else{

            if(ch==dlx){
                escape_found=true;
            }else{
                if (stx_found){
                    qDebug()<<QString::number(ch,16);
                }
            }
        }
    }



    return a.exec();
}
