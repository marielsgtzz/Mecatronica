// P6A3-MedicionPosVel

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
const int PPR = 284;      // Pulsos por revolución del eje de salida del reductor

// Variables para el cálculo de velocidad
float angulo;
float velocidad_rads;
float velocidad_rps;
float velocidad_rpm;


// Medición del tiempo
unsigned long tiempoAnterior = micros(); // Variable para almacenar el tiempo previo en microsegundos
unsigned long tiempoActual = 0; // Se actualiza al calcular la velocidad
unsigned long tiempoCambioVelocidad = 3000000; // 3 segundos en microsegundos
unsigned long tiempoCalculo = 100000; // 100 milisegundos en microsegundos

// Función que se llama cada vez que el pin A del encoder tiene un flanco ascendente
void IRAM_ATTR PulsesCounter() {
  if(digitalRead(EncB) == HIGH){
    pulses++;
  } else {
    pulses--;
  }
}

void setup() {
  // Configuración de pines de salida
  pinMode(EnM, OUTPUT);
  pinMode(MA, OUTPUT);
  pinMode(MB, OUTPUT);

  // Configuración de pines de entrada para el encoder
  pinMode(EncA, INPUT);
  pinMode(EncB, INPUT);

  // Interrupción para contar pulsos del encoder
  attachInterrupt(digitalPinToInterrupt(EncA), PulsesCounter, RISING);

  // Configura el PWM
  ledcSetup(channel, freq, resolution);
  ledcAttachPin(EnM, channel);
  
  // Iniciar la comunicación serial
  Serial.begin(115200);
}

int etapa = 1;

void loop() {
  tiempoActual = micros();
  
  // Cambio de velocidad cada 3 segundos
  if (tiempoActual - tiempoAnterior >= tiempoCambioVelocidad) {
    switch(etapa) {
      case 1:
        // Etapa 1: Girar al 10%
        enviarComandoMotor(25);
        break;
      case 2:
        // Etapa 2: Girar al 30%
        enviarComandoMotor(76);
        break;
      case 3:
        // Etapa 3: Girar al 50%
        enviarComandoMotor(128);
        break;
      case 4:
        // Etapa 4: Girar al 100%
        enviarComandoMotor(255);
        break;
      case 5:
        // Etapa 5: Girar al 0%
        enviarComandoMotor(0);
        break;
    }

    etapa++; // Avanzar a la siguiente etapa

    if(etapa > 5) {
      etapa = 1; // Reiniciar si ya se completaron todas las etapas
    }

    tiempoAnterior = tiempoActual; // Actualiza el tiempo previo
  }

  // Cálculo de velocidad cada 100 milisegundos
  if (tiempoActual - tiempoAnterior >= tiempoCalculo) {
    calcularVelocidad();
    imprimirResultados();
    tiempoAnterior = tiempoActual; // Actualiza el tiempo previo
  }
}

void enviarComandoMotor(int porcentaje) {
  // Giro levógiro
  int velocidad = 255*porcentaje/100;
  ledcWrite(channel, 2000);
  analogWrite(MA, 0);
  analogWrite(MB, velocidad);
}

void calcularVelocidad() {
  tiempoActual = micros();
  long currentPulses = pulses;

  long deltaPulses = currentPulses - pulses;
  unsigned long deltaTime = tiempoActual - tiempoAnterior;

  float deltaTimeSeconds = float(deltaTime) / 1000000.0;

  // Calcular ángulo en grados
  angulo = (pulses % PPR) * 360.0 / PPR;

  // Calcular velocidad angular en radianes por segundo
  velocidad_rads = (pulses * 2 * PI) / (PPR * (micros() - tiempoAnterior) / 1000000.0);

  // Convertir velocidad a rps y rpm
  velocidad_rps = velocidad_rads / (2 * PI);
  velocidad_rpm = velocidad_rps * 60;

  pulses = currentPulses; // Actualiza el valor de pulsos
  tiempoAnterior = tiempoActual; // Actualiza el tiempo previo
}

void imprimirResultados() {  // Imprimir resultados en el monitor serial
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
