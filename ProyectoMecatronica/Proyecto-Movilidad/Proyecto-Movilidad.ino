//Conexion Bluetooth
#include "BluetoothSerial.h"
// Pantalla LCD
#include <Wire.h> // Incluye la librería Wire, que permite la comunicación I2C
#include <LiquidCrystal_I2C.h> // Incluye la librería LiquidCrystal_I2C, que permite controlar pantallas LCD con interfaz I2C

LiquidCrystal_I2C lcd(0x27, 16, 2); // Crea un objeto lcd de la clase LiquidCrystal_I2C, con la dirección I2C 0x27 y especifica que la pantalla tiene 16 columnas y 2 filas


#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT; // Definimos la conexion Bluetooth
char comandoMov;
String comando;

//Puertos
#define ENA1 14
#define InB2 27 //MB
#define InA2 26 //MA
#define InB1 25 //MB
#define InA1 33 //MA
#define ENA2 32

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
  lcd.setCursor(0,0);   // Establece la posición del cursor en la columna 0, fila 1
  lcd.print("HOLA!");
}
void loop() {
  if (SerialBT.available()) {
    comandoMov = SerialBT.read(); //Lectura del dispositivo Bt
    Serial.println(comandoMov);
    lcd.setCursor(0,0);   

    //Los ifs incluyen dos condiciones ya que en el control remoto de BT hay dos opciones de keypad (cada una con números distintos)
    if(comandoMov=='1' || comandoMov=='5'){ //triangulo
      Serial.println("ADELANTE");
      adelante();
      lcd.clear(); // Limpia el contenido de la pantalla LCD
      lcd.print("ADELANTE"); // Imprime el primer nombre en la fila 0

    } else if(comandoMov=='3' || comandoMov=='6'){ //circulo
      Serial.println("ATRAS");
      atras();
      lcd.clear();
      lcd.print("ATRAS"); 

    } else if(comandoMov=='2' || comandoMov=='8'){ //tacha
      Serial.println("DERECHA");
      derecha();
      lcd.clear();
      lcd.print("DERECHA"); 

    } else if(comandoMov=='4' || comandoMov=='9' ){ //cuadrado
      Serial.println("IZQUIERDA");
      izquierda();
      lcd.clear();
      lcd.print("IZQUIERDA"); 

    } else if (comandoMov=='0' ) { //boton de start
      Serial.println("DETENIDO");
      detenido();
      lcd.clear(); 
      lcd.print("DETENIDO"); 
    }
    delay(20);
  } 
}

//Metodos que mueven los motores del robot en una direccion en concreto
void adelante()
{
  digitalWrite(ENA1,HIGH);
  digitalWrite(InA1, LOW);
  digitalWrite(InB1, HIGH);

  digitalWrite(ENA2,HIGH);
  digitalWrite(InA2, LOW);
  digitalWrite(InB2, HIGH);
}

 void atras()
 {
   digitalWrite(ENA1,HIGH);
   digitalWrite(InA1, HIGH);
   digitalWrite(InB1, LOW);

   digitalWrite(ENA2,HIGH);
   digitalWrite(InA2, HIGH);
   digitalWrite(InB2, LOW);
 }

 void derecha(){
   digitalWrite(ENA1, HIGH);
   digitalWrite(InA1, LOW);
   digitalWrite(InB1, HIGH);

   digitalWrite(ENA2, HIGH);
   digitalWrite(InA2, LOW);
   digitalWrite(InB2, LOW);

 }

void izquierda()
{
  digitalWrite(ENA1, HIGH);
  digitalWrite(InA1, LOW);
  digitalWrite(InB1, LOW);

  digitalWrite(ENA2, HIGH);
  digitalWrite(InA2, LOW);
  digitalWrite(InB2, HIGH);

}

void detenido()
{
  digitalWrite(ENA1, LOW);
  digitalWrite(InA1, LOW);
  digitalWrite(InB1, LOW);

  digitalWrite(ENA2,LOW);
  digitalWrite(InA2, LOW);
  digitalWrite(InB2, LOW);

 }