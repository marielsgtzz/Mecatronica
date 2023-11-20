// Pantalla LCD
#include <Wire.h> // Incluye la librería Wire, que permite la comunicación I2C
#include <LiquidCrystal_I2C.h> // Incluye la librería LiquidCrystal_I2C, que permite controlar pantallas LCD con interfaz I2C

LiquidCrystal_I2C lcd(0x27, 16, 2); // Crea un objeto lcd de la clase LiquidCrystal_I2C, con la dirección I2C 0x27 y especifica que la pantalla tiene 16 columnas y 2 filas

//Para definir la izquierda y la derecha es viendo el robot desde atrás de la pila
//Puertos
#define fotoresistorIzq 34 //Fotoresistores
#define fotoresistorDer 35 
#define echoPin 12 //Ultrasonico
#define trigPin 13
#define infrarojo1 5 //Infrarojos de izquierda a derecha
#define infrarojo2 17
#define infrarojo3 18
#define infrarojo4 19
//Variables
int luzDetectadaIzq;
int luzDetectadaDer;
int duracionUltrasonico;
int distanciaUltrasonico;
bool infra1, infra2, infra3, infra4;

void setup() {
  Serial.begin(115200);

  pinMode(fotoresistorIzq, INPUT); // Configuracion fotoresistencias como entrada
  pinMode(fotoresistorDer, INPUT); 
  pinMode(trigPin, OUTPUT); // Configuracion del utrasonico
  pinMode(echoPin, INPUT);
  pinMode (infrarojo1, INPUT); // Configuracion de sensores infrarojos
  pinMode (infrarojo2, INPUT);
  pinMode (infrarojo3, INPUT);
  pinMode (infrarojo4, INPUT);
  lcd.init();   // Inicializa el LCD
  lcd.backlight();   // Enciende la retroiluminación del LCD
}
void loop() {
  luzDetectadaIzq = analogRead(fotoresistorIzq);
  luzDetectadaDer = analogRead(fotoresistorDer);
  Fotoresistor(luzDetectadaIzq,luzDetectadaDer);
  Ultrasonico();
  Obstaculos();
  Serial.println();
}

void monitorSerial(){
  //Serial.print("Pulsos_Enc_Izq:"+String(XXX)+" | Pulsos_Enc_Der:"+ String(XXX)+" | ); 
}

void Fotoresistor(int fotoResistorIzq, int fotoResistorDer){
  lcd.setCursor(0,1);
  lcd.print("I:" + String(luzDetectadaIzq) + " | D:" + String(luzDetectadaDer));
  delay(1000);

  Serial.print("LDR_Izq:"+String(luzDetectadaIzq)+" | LDR_Der:"+String(luzDetectadaDer)+" |");

  delay(250);
}

void Ultrasonico(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(1000);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duracionUltrasonico = pulseIn(echoPin,HIGH);

  distanciaUltrasonico = 0.0343 * duracionUltrasonico * 0.5;

  lcd.setCursor(11,0); 
  lcd.print("L:"+String(distanciaUltrasonico));
  Serial.print("Distancia:"+String(distanciaUltrasonico)+" | ");
}

void Obstaculos(){
  //lectura de sensores inflarojos
  infra1 = digitalRead(infrarojo1);
  infra2 = digitalRead(infrarojo2);
  infra3 = digitalRead(infrarojo3);
  infra4 = digitalRead(infrarojo4);

  bool infra[] = {infra1, infra2, infra3, infra4};
  int obstaculo[] = {0, 0, 0, 0};

  for(int i=0;i<4;i++){
    if(!infra[i]){
      obstaculo[i] = 1;
    }
  }
  
  Serial.print("Obst:"+String(obstaculo[0])+" "+String(obstaculo[1])+" "+String(obstaculo[2])+" "+String(obstaculo[3])+" | ");
  lcd.setCursor(0,0);   // Establece la posición del cursor en la columna 0, fila 0
  lcd.print(String(obstaculo[0])+" "+String(obstaculo[1])+" "+String(obstaculo[2])+" "+String(obstaculo[3]));
}

void Encoder_izquierdo(){

}

void Encoder_derecho(){

}