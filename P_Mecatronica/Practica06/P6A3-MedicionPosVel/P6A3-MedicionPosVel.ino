// P6A3-MedicionPosVel

#include <Arduino.h>

// Definición de pines
#define EnM 21  // Pin para habilitar/deshabilitar el motor
#define MA 23   // Pin de control A para el puente H
#define MB 22   // Pin de control B para el puente H
#define EncA 19 // Pin A del encoder
#define EncB 18 // Pin B del encoder

int channel = 0;     // Canal PWM que se usará
int freq = 1000;     // Frecuencia de la señal PWM
int resolution = 12; // Resolución de la señal PWM
volatile long pulses = 0;  // Cuenta de pulsos del encoder
const int PPR = 64;      // Pulsos por revolución del eje de salida del reductor

int factor = 1;
int tiempo = 20;
int buttonstate;

// Función que se llama cada vez que el pin A del encoder tiene un flanco ascendente
void IRAM_ATTR PulsesCounter() {
  if(digitalRead(EncB) == HIGH){
    pulses++;
  } else {
    pulses--;
  }
}

unsigned long prevTime = micros(); // Variable para almacenar el tiempo previo en microsegundos

void enviarComandoMotor(int velocidad) {
  analogWrite(MA, velocidad);
  analogWrite(MB, 0);
}

void calcularVelocidad() {
  unsigned long currentTime = micros();
  long currentPulses = pulses;

  long deltaPulses = currentPulses - pulses;
  unsigned long deltaTime = currentTime - prevTime;

  float deltaTimeSeconds = float(deltaTime) / 1000000.0;

  float velocidad_rads = (deltaPulses * 2 * PI) / (PPR * deltaTimeSeconds);

  float velocidad_rps = velocidad_rads / (2 * PI);
  float velocidad_rpm = velocidad_rps * 60;

  pulses = currentPulses; // Actualiza el valor de pulsos
  prevTime = currentTime; // Actualiza el tiempo previo
}

void imprimirResultados() {
  // Calcular ángulo en grados
  float angulo = (pulses % PPR) * 360.0 / PPR;

  // Calcular velocidad angular en radianes por segundo
  float velocidad_rads = (pulses * 2 * PI) / (PPR * (micros() - prevTime) / 1000000.0);

  // Convertir velocidad a rps y rpm
  float velocidad_rps = velocidad_rads / (2 * PI);
  float velocidad_rpm = velocidad_rps * 60;

  // Imprimir resultados en el monitor serial
  Serial.print("Pulsos: ");
  Serial.print(pulses);
  Serial.print(" --- Ángulo: ");
  Serial.print(angulo);
  Serial.print("° --- W: ");
  Serial.print(velocidad_rps);
  Serial.print(" [rps] --- ");
  Serial.print(velocidad_rpm);
  Serial.print(" [rpm] --- ");
  Serial.print(velocidad_rads);
  Serial.println(" [rad/s]");
}

void setup() {
  pinMode(MA, OUTPUT);
  pinMode(MB, OUTPUT);
  pinMode(EncA, INPUT);
  pinMode(EncB, INPUT);

  attachInterrupt(digitalPinToInterrupt(EncA), PulsesCounter, RISING);

  Serial.begin(115200);
}

void loop() {
  
  unsigned long tiempoActual = micros();

  if (tiempoActual - prevTime >= 100000) {
    // Etapa 1: Girar al 10%
    enviarComandoMotor(25);
    calcularVelocidad();
    imprimirResultados();

    // Etapa 2: Girar al 30%
    enviarComandoMotor(76);
    calcularVelocidad();
    imprimirResultados();

    // Etapa 3: Girar al 50%
    enviarComandoMotor(128);
    calcularVelocidad();
    imprimirResultados();

    // Etapa 4: Girar al 100%
    enviarComandoMotor(255);
    calcularVelocidad();
    imprimirResultados();

    // Etapa 5: Girar al 0%
    enviarComandoMotor(0);
    calcularVelocidad();
    imprimirResultados();

    prevTime = tiempoActual; // Actualiza el tiempo previo
  }
}
