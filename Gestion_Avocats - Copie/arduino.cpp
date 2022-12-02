#include "arduino.h"
#include<QDebug>
#include "avocat.h"

arduino::arduino()
{
    dataaAV="";
    arduino_port_name="COM6";
    arduino_is_available=false;
    serial=new QSerialPort;
}
QString arduino::getarduino_port_name()
{
    return arduino_port_name;
}
QSerialPort *arduino::getserial()
{
   return serial;
}

int arduino:: connect_arduino()
{

    foreach(const QSerialPortInfo &serial_port_info, QSerialPortInfo ::availablePorts())
    {
        if (serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier())
        {
            if ( serial_port_info.vendorIdentifier()== arduino_uno_vendor_id && serial_port_info.productIdentifier() == arduino_uno_producy_id)
            {

             arduino_is_available= true ;
             arduino_port_name= serial_port_info.portName();
      } } }
    qDebug() <<" arduino_port_name is : "<< arduino_port_name;

 if ( arduino_is_available)
 {
   // configuration de la comm.

     serial->setPortName(arduino_port_name);

if ( serial->open(QSerialPort :: ReadWrite))
{

    serial->setBaudRate(QSerialPort :: Baud9600); // debit egal à 9600
    serial->setDataBits(QSerialPort :: Data8); // longeur des  donnes est de 8 bits
    serial->setParity(QSerialPort :: NoParity); // bit de parite optionnel
    serial->setStopBits(QSerialPort :: OneStop); // nbr de bits de stop est de 1
    serial->setFlowControl(QSerialPort :: NoFlowControl);


 return 0 ;
}
return 1 ;
}
 return -1;
}

int arduino :: close_arduino()
{

if ( serial ->isOpen())
{
   serial->close();
   return 0;
}  return 1 ;


}

QByteArray arduino::read_from_arduino_avocat()
{
    QByteArray b=NULL;
    if(serial->isReadable()){
         dataaAV=serial->readAll(); //récupérer les données reçues
         return dataaAV;
    }
    return b;
 }











