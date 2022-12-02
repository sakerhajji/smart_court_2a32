#ifndef ARDUINO_H
#define ARDUINO_H
#include<QtSerialPort/QSerialPort>
#include<QtSerialPort/QSerialPortInfo>
#include<QString>

class arduino
{
public:
    arduino();

    int connect_arduino();// permet la cnx pc arduinà
    int close_arduino();// permet de fermer la cnx
    //int write_to_arduino(QByteArray);//send data to arduino
    QByteArray read_from_arduino_avocat();// recevoir des donnes from arduino
    QSerialPort* getserial();// accesseur
    QString getarduino_port_name();

private:
    QSerialPort * serial; // objet gathering des info exp: vitesse  et des fncts ect ect

    static const quint16 arduino_uno_vendor_id=9025;
    static const quint16 arduino_uno_producy_id=67;
    QString arduino_port_name;
    bool arduino_is_available;
    QByteArray dataaAV ;// contient les donnes lus depuis arduino












};

#endif // ARDUINO_H
