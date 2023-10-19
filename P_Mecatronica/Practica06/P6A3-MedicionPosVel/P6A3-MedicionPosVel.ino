// P6A3-MedicionPosVel

// Definición de pines y variables
#define motorPin1 ?  // Pin de control del motor
#define motorPin2 ?  // Otro pin de control del motor
#define encoderPinA ? // Pin de señal del encoder A
#define encoderPinB ? // Pin de señal del encoder B
#define Rojo ?
#define Amarillo ?
#define Verde ?
#define Button ?

int factor = 1;
int tiempo = 20;
int buttonstate;

const int PPR = 1920; // Define el valor de pulsos por revolución del encoder

long pulses = 0;
unsigned long prevTime = micros(); // Variable para almacenar el tiempo previo en microsegundos

void enviarComandoMotor(int velocidad) {
  analogWrite(motorPin1, velocidad);
  analogWrite(motorPin2, 0);
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
  pinMode(Rojo, OUTPUT);
  pinMode(Amarillo, OUTPUT);
  pinMode(Verde, OUTPUT);
  pinMode(Button, INPUT);

  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);

  attachInterrupt(digitalPinToInterrupt(encoderPinA), PulsesCounter, RISING);

  Serial.begin(115200);
}

void loop() {
  digitalWrite(Rojo, LOW);
  digitalWrite(Verde, HIGH);
  delay(factor*tiempo);
  digitalWrite(Verde, LOW);
  digitalWrite(Amarillo, HIGH);
  delay(factor*tiempo);
  digitalWrite(Amarillo, LOW);
  digitalWrite(Rojo, HIGH);
  delay(factor*tiempo);

  buttonstate = digitalRead(Button);

  if (buttonstate){
    Serial.println("Botón presionado");
    factor++;
    digitalWrite(ButLed,HIGH);
    delay(tiempo);
    digitalWrite(ButLed,LOW);
    delay(tiempo);
  }

  Serial.println(factor*tiempo);

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

void IRAM_ATTR PulsesCounter() {
  if(digitalRead(encoderPinB) == HIGH) {
    pulses++;
  } else {
    pulses--;
  }
}
