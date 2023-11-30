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
#define ENA1 14 //Encoder (2 derecha, 1 izquierda)
#define InB2 27 //MB
#define InA2 26 //MA
#define InB1 25 //MB
#define InA1 33 //MA
#define ENA2 32
#define EncA1 4 // Pin A del encoder 1
#define EncA2 15 // Pin A del encoder 2
#define EncB1 2 // Pin B del encoder 1  
#define EncB2 16 // Pin B del encoder 2

//variables para el pwm de los encoders ya que no podemos usar analog Write 
int channel0=0;
int channel1=1;
int freq=255;
int resolution=8;

//Variables
int luzDetectadaIzq;
int luzDetectadaDer;
int duracionUltrasonico;
int distanciaUltrasonico;
bool infra1, infra2, infra3, infra4;
volatile long pulsesDer = 0;
volatile long pulsesIzq = 0;
bool evitarObstaculo = false;

// Variables globales para el control de tiempo
unsigned long tiempoActual;
unsigned long tiempoInicioAtras;
unsigned long tiempoInicioGiro;
bool enMovimientoAtras = false;
bool enGiro = false;

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
  pinMode(ENA1, OUTPUT);
  pinMode(InA1, OUTPUT);
  pinMode(InB1, OUTPUT);
  pinMode(ENA2, OUTPUT);
  pinMode(InA2, OUTPUT);
  pinMode(InB2, OUTPUT);
  pinMode(EncA1, INPUT); // Configuración del encoder
  pinMode(EncB1, INPUT);
  pinMode(EncA2, INPUT); 
  pinMode(EncB2, INPUT);
  lcd.init();   // Inicializa el LCD
  lcd.backlight();   // Enciende la retroiluminación del LCD

  //2 canales para el pwm, definimos 2 canales para el ena1 y 2 para mandarles 2 pwm a cada encoder de los motoredictores
  ledcSetup(channel0,freq,resolution);
  ledcAttachPin(ENA1,channel0);
  ledcSetup(channel1,freq,resolution);
  ledcAttachPin(ENA2,channel1);

}
void loop()
 {
  luzDetectadaIzq = analogRead(fotoresistorIzq);
  luzDetectadaDer = analogRead(fotoresistorDer);
  Ultrasonico();
  attachInterrupt(digitalPinToInterrupt(EncA1), Encoder_izquierdo, RISING);
  attachInterrupt(digitalPinToInterrupt(EncA2), Encoder_derecho, RISING);
  monitorSerialPulsos();
  Fotoresistor();
  Obstaculos();
  Serial.println();
  
  // Detección de obstáculos
  bool hayObstaculoEnfrente = (distanciaUltrasonico < 12); 
  bool hayObstaculoIzq = !infra1;
  bool hayObstaculoDer = !infra4;
  bool hayObstaculo = hayObstaculoEnfrente || hayObstaculoIzq || hayObstaculoDer;
  lcd.setCursor(8,0); 
  if(hayObstaculo){
    lcd.print("O:T");
  } else {
    lcd.print("O:F");
  }
  
  tiempoActual = millis();
  if (hayObstaculo || evitarObstaculo ) {
    evitarObstaculo = true;
    // Inicia movimiento hacia atrás si se detecta un obstáculo y no está en movimiento
    if (!enMovimientoAtras && !enGiro) {
      detenido();
      tiempoInicioAtras = millis();
      enMovimientoAtras = true;
    }

    if (enMovimientoAtras && (tiempoActual - tiempoInicioAtras > 750)) {
      atras();
      if (!enGiro) {
        tiempoInicioGiro = millis();  // Inicia el tiempo del giro después de moverse hacia atrás
        enGiro = true;
      }
      enMovimientoAtras = false;
    }

    if (enGiro && (tiempoActual - tiempoInicioGiro > 750)) {  
      // if (enGiro) {  
        if (hayObstaculoIzq) {
            derecha();
        } else if (hayObstaculoDer){
            izquierda(); 
        } else {
          if (luzDetectadaIzq > luzDetectadaDer) {
            izquierda(); 
          } else {
            derecha();
          }
        }
    }

    if (tiempoActual - tiempoInicioGiro > 750) {  // Duración del giro, ajustar según sea necesario
        enGiro = false;
        evitarObstaculo = false;
        adelante();
    }

  //   // Se mueve hacia atrás por un tiempo determinado
  //  if (enMovimientoAtras && (tiempoActual - tiempoInicioAtras > 750)) {
  //     atras();
  //     if (!enGiro) {
  //       tiempoInicioGiro = millis();  // Inicia el tiempo del giro después de moverse hacia atrás
  //       enGiro = true;
  //     }
  //     enMovimientoAtras = false;
  //   }

  //   // Inicia giro después de moverse hacia atrás
  //   if (enGiro && (tiempoActual - tiempoInicioGiro > 1500)) {  
  //     if (hayObstaculoIzq) {
  //       izquierda();
  //     } else {
  //       derecha();
  //     }
  //     enGiro = false;
  //     evitarObstaculo = false;
  //   }
  } else {// Seguir la luz

    if(luzDetectadaIzq==4095 && luzDetectadaDer==4095){
        detenido(); //Ya llegó a la fuente de luz
    } else {
        int diff = abs(luzDetectadaIzq-luzDetectadaDer);
        // Mueve los motores según la lectura de los LDR
        if(diff<=300){
          adelante();
        } else if (luzDetectadaIzq < luzDetectadaDer){
          derecha();
        } else if (luzDetectadaIzq > luzDetectadaDer) {
          izquierda();
        } else {
          detenido();
        }
    }
  }
  
  
}

void evitarObstaculoEnfrente(bool hayObstaculoIzq,bool hayObstaculoDer){
  atras();
  if(hayObstaculoIzq){
    derecha();
    adelante();
    izquierda();
    adelante();
  } else {
    izquierda();
    adelante();
    derecha();
    adelante();
  }
}

void monitorSerialPulsos(){
  Serial.print("Pulsos_Enc_Izq:"+String(pulsesIzq)+" | Pulsos_Enc_Der:"+String(pulsesDer)+" | ");  
}

void Fotoresistor()
{
  luzDetectadaIzq = analogRead(fotoresistorIzq);
  luzDetectadaDer = analogRead(fotoresistorDer);
  lcd.setCursor(0,1);
  lcd.print("I:" + String(luzDetectadaIzq) + " | D:" + String(luzDetectadaDer));
  delay(100);
  Serial.print("LDR_Izq:"+String(luzDetectadaIzq)+" | LDR_Der:"+String(luzDetectadaDer)+" |");
  //milis(25);
}

void Ultrasonico(){
  //Para limpiar de señales anteriores
  digitalWrite(trigPin, LOW);
  delayMicroseconds(100);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duracionUltrasonico = pulseIn(echoPin,HIGH); //mide la duración del pulso entrante en echoPin. 
  //Esta duración es el tiempo que tarda el eco en regresar al sensor después de ser rebotar en un objeto.

  distanciaUltrasonico = 0.0343 * duracionUltrasonico / 2; //Calcula la distancia al objeto utilizando la velocidad del sonido (343 m/s = 0.0343 cm/ms) y la duración del eco. 
  //Se divide por 2 porque el eco viaja ida y vuelta desde el sensor hasta el objeto.

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
  if(digitalRead(EncB1)==HIGH){
      pulsesIzq++;
  } else {
    pulsesIzq--;
  }  
}

void Encoder_derecho() {
  if (digitalRead(EncB2) == HIGH) {
    pulsesDer++;
  } else {
    pulsesDer--;
  }
}

void adelante() {
  ledcWrite(channel0, 80);
  digitalWrite(InA1, LOW);
  digitalWrite(InB1, HIGH);
  ledcWrite(channel1, 80);
  digitalWrite(InA2, LOW);
  digitalWrite(InB2, HIGH);
}

void atras() {
  ledcWrite(channel0, 80);
  digitalWrite(InA1, HIGH);
  digitalWrite(InB1, LOW);
  ledcWrite(channel1, 80);
  digitalWrite(InA2, HIGH);
  digitalWrite(InB2, LOW);
}

void derecha() {
  ledcWrite(channel0, 70);
  digitalWrite(InA1, LOW);
  digitalWrite(InB1, HIGH);
  ledcWrite(channel1, 70);
  digitalWrite(InA2, HIGH);
  digitalWrite(InB2, LOW);
}

void izquierda() {
  ledcWrite(channel0, 70);
  digitalWrite(InA1, HIGH);
  digitalWrite(InB1, LOW);
  ledcWrite(channel1, 70);
  digitalWrite(InA2, LOW);
  digitalWrite(InB2, HIGH);
}


void detenido()
{
  ledcWrite(channel0, 0);
  digitalWrite(ENA1, LOW);
  digitalWrite(InA1, LOW);
  digitalWrite(InB1, LOW);

  ledcWrite(channel1, 0);
  digitalWrite(ENA2,LOW);
  digitalWrite(InA2, LOW);
  digitalWrite(InB2, LOW);
 }