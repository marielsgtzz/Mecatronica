//Conexion Bluetooth
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT; // Definimos la conexion Bluetooth
char comandoMov;

// //Puertos
// #define ENA1 14
// #define ENA2 32
// #define InA1 33 //MA
// #define InB1 25 //MB
// #define InA2 26 //MA
// #define InB2 27 //MB
// //Conexiones Puente H
// #define EnMIzq          //Pin para habilitar/deshabilitar el motor izquierdo (el del centro)
// #define MAIzq 12        // Pin de control A para el puente H del motor izquierdo (primero de la derecha)
// #define MBIzq 14        // Pin de control B para el puente H del motor izquierdo (tercero de la derecha)

// #define EnMDer          // Pin para habilitar/deshabilitar el motor derecho
// #define MADer 12        // Pin de control A para el puente H del motor derecho
// #define MBDer 14        // Pin de control B para el puente H del motor derecho


// #define EncAIzq 19      // Pin A del encoder del motor izquierdo
// #define EncBIzq 18      // Pin B del encoder del motor izquierdo


// #define EncADer 19      // Pin A del encoder del motor derecho
// #define EncBDer 18      // Pin B del encoder del motor derecho

void setup() {
  Serial.begin(115200);
  // pinMode(ENA1, OUTPUT);
  // pinMode(InA1, OUTPUT);
  // pinMode(InB1, OUTPUT);
  // pinMode(ENA2, OUTPUT);
  // pinMode(InA2, OUTPUT);
  // pinMode(InB2, OUTPUT);

  SerialBT.begin("PlacaMMP");

}

void loop() {
  if (SerialBT.available()) {
    comandoMov = SerialBT.read(); //Lectura del dispositivo Bt

    // Serial.println(dato);
    // SerialBT.println(dato);

    if(comandoMov=='1' || comandoMov=='5'){
      Serial.println("ADELANTE");
    } else if(comandoMov=='3' || comandoMov=='6'){
      Serial.println("ATRAS");
    } else if(comandoMov=='2' || comandoMov=='8'){
      Serial.println("DERECHA");
    } else if(comandoMov=='4' || comandoMov=='0'){
      Serial.println("IZQUIERDA");
    } else {
      Serial.println("DETENIDO");
    }
    delay(20);
    }

  

}

// void adelante(){
//   digitalWrite(InA1, LOW);
//   digitalWrite(InB1, HIGH);

//   digitalWrite(InA2, LOW);
//   digitalWrite(InB2, HIGH);

//   Serial.println("ADELANTE");

//   delay(1000);
// }

// void atras(){
//   digitalWrite(InA1, HIGH);
//   digitalWrite(InB1, LOW);

//   digitalWrite(InA2, HIGH);
//   digitalWrite(InB2, LOW);

//   Serial.println("ATRAS");

//   delay(1000);
// }

// void derecha(){
//   digitalWrite(InA1, HIGH);
//   digitalWrite(InB1, LOW);

//   digitalWrite(InA2, LOW);
//   digitalWrite(InB2, LOW);

//   Serial.println("DERECHA");

//   delay(1000);
// }

// void izquierda(){
//   digitalWrite(InA1, LOW);
//   digitalWrite(InB1, LOW);

//   digitalWrite(InA2, HIGH);
//   digitalWrite(InB2, LOW);

//   Serial.println("IZQUIERDA");

//   delay(1000);
// }

// void detenido(){
//   digitalWrite(InA1, LOW);
//   digitalWrite(InB1, LOW);

//   digitalWrite(InA2, LOW);
//   digitalWrite(InB2, LOW);

//   Serial.println("ALTO");

//   delay(1000);
// }