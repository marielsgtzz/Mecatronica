#include "BluetoothSerial.h"
#define LED1 4
#define LED2 5
#define LED3 21

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT; // Definimos la conexion Bluetooth
char dato; //Variable de entrada (se instancia con el input del Bt)
const char c1 = 'a';
const char c2 = 'b';
const char c3 = 'c';
const char c4 = 'd';

//Banderas para definir si se tiene que prender o no el led. 
//Si esta en true significa que actualmente el foco esta apagado y que al mandar su caracter se debe de prender
boolean car1 = true;
boolean car2 = true;
boolean car3 = true;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("PlacaMariel"); //Nombre bluetooth de la placa
  //Define a los LEDs
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
}

void loop() {
  if (SerialBT.available()) {
    dato = SerialBT.read(); //Lectura del dispositivo Bt

    //Segun el character que se ingreso en el Bt 
    switch (dato) {
      case c1: //Si el input fue el primer caracter 
        if(car1){ //Checa si esta apagado el LED o no (si lo esta, la bandera va a decir true)
          digitalWrite(LED1,HIGH);//Enciende el led
          Serial.println("Se encendio el LED 1");
          SerialBT.println("Se encendio el LED 1");
          car1 = false; //Cambia la bandera para informar que esta encendido el led y tocaria apagarlo
        }else{
          digitalWrite(LED1,LOW);//Apaga el led
          Serial.println("Se apago el LED 1");
          SerialBT.println("Se apago el LED 1");
          car1 = true;//Cambia la bandera para informar que esta apagado el led y tocaria encenderlo
        }
        break;
        
      case c2://Si el input fue el segundo caracter 
        if(car2){
            digitalWrite(LED2,HIGH);//Enciende el led
            Serial.println("Se encendio el LED 2");
            SerialBT.println("Se encendio el LED 2");
            car2 = false;

          }else{
            digitalWrite(LED2,LOW);//Apaga el led
            Serial.println("Se apago el LED 2");
            SerialBT.println("Se apago el LED 2");
            car2 = true;
          }
          break;

          
      case c3://Si el input fue el tercer caracter 
        if(car3){
          digitalWrite(LED3,HIGH);//Enciende el led
          Serial.println("Se encendio el LED 3");
          SerialBT.println("Se encendio el LED 3");
          car3 = false;

        }else{
          digitalWrite(LED3,LOW);//Apaga el led
          Serial.println("Se apago el LED 3");
          SerialBT.println("Se apago el LED 3");
          car3 = true;
        }
        break;
        
      case c4://Si el input fue el cuarto caracter 
          //Apaga los leds
          digitalWrite(LED1,LOW);
          digitalWrite(LED2,LOW);
          digitalWrite(LED3,LOW);
          Serial.println("Se apagaron los LEDs");
          SerialBT.println("Se apagaron los LEDs");
          
          //Cambia la bandera de los 3 leds para informar que ahora estan apagados y tocaria encenderlos
          car1 = true;
          car2 = true;
          car3 = true;
    
          break;
    }
  }

  delay(20);

}
