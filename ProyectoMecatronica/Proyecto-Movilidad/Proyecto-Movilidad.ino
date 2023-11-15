//Conexion Bluetooth
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT; // Definimos la conexion Bluetooth
char comandoMov;
String comando;
// Pantalla LCD
#include <Wire.h> // Incluye la librería Wire, que permite la comunicación I2C
#include <LiquidCrystal_I2C.h> // Incluye la librería LiquidCrystal_I2C, que permite controlar pantallas LCD con interfaz I2C

LiquidCrystal_I2C lcd(0x27, 16, 2); // Crea un objeto lcd de la clase LiquidCrystal_I2C, con la dirección I2C 0x27 y especifica que la pantalla tiene 16 columnas y 2 filas

//Puertos Motores
#define ENA1 14
#define InB2 27 //MB
#define InA2 26 //MA
#define InB1 25 //MB
#define InA1 33 //MA
#define ENA2 32

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
  pinMode(ENA1, OUTPUT);
  pinMode(InA1, OUTPUT);
  pinMode(InB1, OUTPUT);
  pinMode(ENA2, OUTPUT);
  pinMode(InA2, OUTPUT);
  pinMode(InB2, OUTPUT);

  SerialBT.begin("PlacaMMP");
  lcd.init();   // Inicializa el LCD
  lcd.backlight();   // Enciende la retroiluminación del LCD
  lcd.setCursor(0,1);   // Establece la posición del cursor en la columna 0, fila 1
  lcd.print("HOLA");


}
void loop() {
  if (SerialBT.available()) {
    comandoMov = SerialBT.read(); //Lectura del dispositivo Bt

    Serial.println(comandoMov);
    lcd.setCursor(0,1);   // Establece la posición del cursor en la columna 0, fila 1

    if(comandoMov=='1' || comandoMov=='5'){
      Serial.println("ADELANTE");
      lcd.clear(); // Limpia el contenido de la pantalla LCD
      lcd.print("ADELANTE"); // Imprime el primer nombre en la fila 0
      adelante();
    } else if(comandoMov=='3' || comandoMov=='6'){
      Serial.println("ATRAS");
      lcd.clear();
      lcd.print("ATRAS"); 
      atras();
    } else if(comandoMov=='2' || comandoMov=='8'){
      Serial.println("DERECHA");
      lcd.clear();
      lcd.print("DERECHA"); 
      derecha();
    } else if(comandoMov=='4' || comandoMov=='0'){
      Serial.println("IZQUIERDA");
      lcd.clear();
      lcd.print("IZQUIERDA"); 
      izquierda();
    } else {
      Serial.println("DETENIDO");
      lcd.clear(); 
      lcd.print("DETENIDO"); 
      detenido();
    }
    delay(20);
  }
  
  
}

void adelante(){
  digitalWrite(InA1, LOW);
  digitalWrite(InB1, HIGH);

  digitalWrite(InA2, LOW);
  digitalWrite(InB2, HIGH);

  delay(1000);
}

void atras(){
  digitalWrite(InA1, HIGH);
  digitalWrite(InB1, LOW);

  digitalWrite(InA2, HIGH);
  digitalWrite(InB2, LOW);

  Serial.println("ATRAS");

  delay(1000);
}

void derecha(){
  digitalWrite(InA1, HIGH);
  digitalWrite(InB1, LOW);

  digitalWrite(InA2, LOW);
  digitalWrite(InB2, LOW);

  Serial.println("DERECHA");

  delay(1000);
}

void izquierda(){
  digitalWrite(InA1, LOW);
  digitalWrite(InB1, LOW);

  digitalWrite(InA2, HIGH);
  digitalWrite(InB2, LOW);

  Serial.println("IZQUIERDA");

  delay(1000);
}

void detenido(){
  digitalWrite(InA1, LOW);
  digitalWrite(InB1, LOW);

  digitalWrite(InA2, LOW);
  digitalWrite(InB2, LOW);

  Serial.println("ALTO");

  delay(1000);
}