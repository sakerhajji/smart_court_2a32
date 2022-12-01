#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd (0x27,16,2);
#define PIN_LED_B 9
#define PIN_LED_G 10
#define PIN_LED_R 11
#define PIN_LED_connect 2 // Le numéro de la broche sur laquelle la lampe 1 
#define PIN_buzzer 3
#define PIN_blueR 8
#define pas  10 // incrément de l'intensité
char data; // variable contenant le caractère lu
String printt ; // variable contenant les chaine lu
int x, y ;


void setup()
{
    // Configure la broche 11 sur laquelle est reliée notre LED  en sortie
    //pinMode(PIN_LED1,OUTPUT);
//La LED reliée à la broche 11 est intialisé à l'état LOW
    digitalWrite(PIN_LED_connect,LOW);
    // Configure la broche 13 sur laquelle est reliée notre LED  en sortie
    pinMode(PIN_LED_connect,OUTPUT);
    pinMode(PIN_buzzer,OUTPUT);
    pinMode(PIN_LED_R,OUTPUT);
    pinMode(PIN_LED_B,OUTPUT);
    pinMode(PIN_LED_G,OUTPUT);
    pinMode(PIN_blueR,INPUT_PULLUP);
    Serial.begin(9600); //Permet d'initialiser le moniteur série à 9600 bauds
    lcd.init() ;
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print("Samrt court ");
    lcd.setCursor(0,1);
    lcd.print("Hajji Saker ");
    x=0;
    y=0;

}



void loop()
{
    lcd.scrollDisplayLeft();
    delay(250);

    if (digitalRead(PIN_blueR) == LOW)
    {
        Serial.write('H');
        digitalWrite(PIN_LED_connect, HIGH);
        x=1;
        delay (500);

    }
    if (digitalRead(PIN_blueR) == HIGH)
    {
        digitalWrite(PIN_LED_connect, LOW);

    }
    if (x==1&&y==1)
    {
        lcd.init() ;
        lcd.backlight();
        lcd.setCursor(0,0);
        lcd.print(" Attention !!!!" );
        digitalWrite(PIN_buzzer, HIGH);
        digitalWrite(PIN_LED_R,HIGH);

    }
    else
    {
        digitalWrite(PIN_buzzer, LOW);

        digitalWrite(PIN_LED_R,LOW);
    }

    if (Serial.available())
    {
        //Si un message a été reçu  faire ceci
        data=Serial.read();
        // controler la lampe 1 reliée à la broche 13
        //récuperer le caractère reçu
        if(data=='1') //si le caractère lu est égale à 1
        {
            digitalWrite(PIN_LED_connect,HIGH); // alumer la lampe
            Serial.write('1'); //envoyer le nouvel état de la lampe
            lcd.init() ;
            lcd.backlight();
            lcd.setCursor(0,0);
            lcd.print("Lampe on ");
        }
        else if(data=='0') //si le caractère lu est égale à 0

        {
            digitalWrite(PIN_LED_connect,LOW); //éteindre la lampe
            Serial.write('0'); //envoyer le nouvel état de la lampe
            lcd.init() ;
            lcd.backlight();
            lcd.setCursor(0,0);
            lcd.print("Lampe off ");

        }
        else if (data=='3')
        {
            digitalWrite(PIN_LED_connect,HIGH);
            delay(1000);
            y=1;
        }

        else if (data=='4')
        {

            printt=Serial.readString();
            lcd.init() ;
            lcd.backlight();
            lcd.setCursor(0,0);
            lcd.print("cas ete rapporte" );
            lcd.setCursor(0,1);
            lcd.print("num:"+printt);
            digitalWrite(PIN_LED_R,HIGH);
            digitalWrite(PIN_LED_B,HIGH);
            //digitalWrite(PIN_LED_G,HIGH);
            delay(500);
            digitalWrite(PIN_LED_R,LOW);
            delay(500);
            digitalWrite(PIN_LED_B,LOW);
            x=0;
        }
         else if(data=='5')
        {
          lcd.init() ;
            lcd.backlight();
            lcd.setCursor(0,0);
            lcd.print("created by" );
            lcd.setCursor(0,1);
            lcd.print("Hajji Saker 2A32");
        }
           else if(data=='6')
        {
          lcd.init() ;
            lcd.backlight();
            lcd.setCursor(0,0);
            lcd.print(" Bienvenue " );
            
        }
    }
    
}
