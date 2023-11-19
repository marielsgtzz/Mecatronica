// Pantalla LCD
#include <Wire.h> // Incluye la librería Wire, que permite la comunicación I2C
#include <LiquidCrystal_I2C.h> // Incluye la librería LiquidCrystal_I2C, que permite controlar pantallas LCD con interfaz I2C

LiquidCrystal_I2C lcd(0x27, 16, 2); // Crea un objeto lcd de la clase LiquidCrystal_I2C, con la dirección I2C 0x27 y especifica que la pantalla tiene 16 columnas y 2 filas

//Puertos
#define fotoresistorIzq 34 //Fotoresistores
#define fotoresistorDer 35 

//Variables
int luzDetectadaIzq;
int luzDetectadaDer;

void setup() {
  Serial.begin(115200);

  pinMode(fotoresistorIzq, INPUT); // Configura el pin de la fotoresistencia como entrada
  pinMode(fotoresistorDer, INPUT); 

  lcd.init();   // Inicializa el LCD
  lcd.backlight();   // Enciende la retroiluminación del LCD
  lcd.setCursor(0,0);   // Establece la posición del cursor en la columna 0, fila 1
  lcd.print("HOLA!");
}
void loop() {
  luzDetectadaIzq = analogRead(fotoresistorIzq);
  luzDetectadaDer = analogRead(fotoresistorDer);

  Serial.print("Luz detectada por el fotoresistor Izq: ");
  Serial.print(luzDetectadaIzq); 
  Serial.print("|| ");
  Serial.print("Luz detectada por el fotoresistor Der: ");
  Serial.print(luzDetectadaDer); 
  Serial.println();
  delay(250);
}

void Fotoresistor(){

}

void Ultrasonico(){

}

void Obstaculos(){

}

void Encoder_izquierdo(){

}

void Encoder_derecho(){

}