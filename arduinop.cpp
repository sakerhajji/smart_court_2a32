/*#include "arduinop.h"


#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QObject>
ArduinoP::ArduinoP()
{
    data="";
    arduino_port_name="";
    arduino_is_available=false;
    serial=new QSerialPort;
}

QString ArduinoP::getarduino_port_name()
{
    return arduino_port_name;
}

QSerialPort *ArduinoP::getserial()
{
   return serial;
}
int ArduinoP::connect_arduino()
{   // recherche du port sur lequel la carte arduino identifée par  arduino_uno_vendor_id
    // est connectée
    serialbuffer="";
    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()){
           if(serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()){
               if(serial_port_info.vendorIdentifier() == arduino_uno_vendor_id && serial_port_info.productIdentifier()
                       == arduino_uno_producy_id) {
                   arduino_is_available = true;
                   arduino_port_name=serial_port_info.portName();
               } } }
        qDebug() << "arduino_port_name is :" << arduino_port_name;
        if(arduino_is_available){ // configuration de la communication ( débit...)
            serial->setPortName(arduino_port_name);
            if(serial->open(QSerialPort::ReadWrite)){
                serial->setBaudRate(QSerialPort::Baud9600); // débit : 9600 bits/s
                serial->setDataBits(QSerialPort::Data8); //Longueur des données : 8 bits,
                serial->setParity(QSerialPort::NoParity); //1 bit de parité optionnel
                serial->setStopBits(QSerialPort::OneStop); //Nombre de bits de stop : 1
                serial->setFlowControl(QSerialPort::NoFlowControl);
                return 0;
            }
            return 1;
        }
        return -1;
}

int ArduinoP::close_arduino()

{

    if(serial->isOpen()){
            serial->close();
            return 0;
        }
    return 1;


}


 QByteArray ArduinoP::read_from_arduino()
{

    if(serial->isReadable()){
        serial->waitForReadyRead(10);
         data=serial->readAll();
         return data;
    }
 }

 int ArduinoP::chercherid(int id){

     QSqlDatabase bd = QSqlDatabase::database();

         QSqlQuery query;
         query.prepare("SELECT id  FROM personnels WHERE id =:id");
  query.bindValue(":id", id);

         query.exec();
         if (query.next())
         {


              return 1;
         }
         else {
             return -1;
         }

 }
 QByteArray ArduinoP::getdata()
 {
     return data;
 }
int ArduinoP::write_to_arduino( QByteArray d)

{

    if(serial->isWritable()){
        serial->write(d);  // envoyer des donnés vers Arduino
    }else{
        qDebug() << "Couldn't write to serial!";
    }


}
*/
