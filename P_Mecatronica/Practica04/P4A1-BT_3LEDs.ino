#include "BluetoothSerial.h"
#define LED1 4
#define LED2 5
#define LED3 21

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
char dato;
char caracter_1 = 'a';
char caracter_2 = 'b';
char caracter_3 = 'c';
char caracter_4 = 'd';
boolean car1 = false;
boolean car2 = false;
boolean car3 = false;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("PlacaMariel"); //Nombre bluetooth de la placa
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
}

void loop() {
  if (SerialBT.available()) {
    dato = SerialBT.read();
    
    switch (dato) {
      case caracter_1:
        if(car1){
          digitalWrite(LED1,HIGH);
          Serial.println("Se encendio el LED 1");
          SerialBT.println("Se encendio el LED 1");
        }else{
          digitalWrite(LED1,LOW);
          Serial.println("Se apago el LED 1");
          SerialBT.println("Se apago el LED 1");
        }
        
      case caracter_2:
        if(car2){
            digitalWrite(LED2,HIGH);
            Serial.println("Se encendio el LED 2");
            SerialBT.println("Se encendio el LED 2");
          }else{
            digitalWrite(LED2,LOW);
            Serial.println("Se apago el LED 2");
            SerialBT.println("Se apago el LED 2");
          }
          
      case caracter_3:
        if(car3){
          digitalWrite(LED3,HIGH);
          Serial.println("Se encendio el LED 3");
          SerialBT.println("Se encendio el LED 3");
        }else{
          digitalWrite(LED3,LOW);
          Serial.println("Se apago el LED 3");
          SerialBT.println("Se apago el LED 3");
        }
        
        case caracter_4:
          digitalWrite(LED1,LOW);
          digitalWrite(LED2,LOW);
          digitalWrite(LED3,LOW);
          Serial.println("Se apagaron los LEDs");
          SerialBT.println("Se apagaron los LEDs");    

    }
  }

  delay(20);

}
