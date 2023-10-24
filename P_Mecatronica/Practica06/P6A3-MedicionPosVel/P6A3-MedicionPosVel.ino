// Definición de pines
#define EnM 21  // Pin para habilitar/deshabilitar el motor
#define MA 23   // Pin de control A para el puente H
#define MB 22   // Pin de control B para el puente H
#define EncA 19 // Pin A del encoder
#define EncB 18 // Pin B del encoder

int channel = 0;     
int freq = 1000;     
int resolution = 12; 
volatile long pulses = 0;  
const int PPR = 284;      

// Variables para el cálculo de velocidad
int angulo = 0;
int anguloAnterior = 0;
float velocidad_rads = 0;
float velocidad_rps = 0;
float velocidad_rpm = 0;

// Medición del tiempo
int porcentaje = 0;
unsigned long tiempoAnteriorA = 0;
unsigned long tiempoAnteriorB = 0;
unsigned long tiempoActual = 0;

// Función que se llama cada vez que el pin A del encoder tiene un flanco ascendente
void IRAM_ATTR PulsesCounter() {
  if (digitalRead(EncB) == HIGH) {
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
  //tiempoActual = millis();
}

void loop() {
  tiempoActual = millis();
  
  // Comprobación para imprimir en el monitor serial cada 100 milisegundos
  if (tiempoActual - tiempoAnteriorA == 100) {
    calcularVelocidad();
    imprimirResultados();
    tiempoAnteriorA = tiempoActual; // Actualiza el tiempo previo
    anguloAnterior = angulo; // Actualiza el ángulo previo
  }

  // Comprobación para cambiar la velocidad del motor cada 3 segundos = 3000 milisegundos
  if (tiempoActual - tiempoAnteriorB == 3000) {
    switch (porcentaje) {
      case 0:
        porcentaje += 10;
        break;
      case 10:
        porcentaje += 20;
        break;
      case 30:
        porcentaje += 20;
        break;
      case 50:
        porcentaje += 50;
        break;
      case 100:
        porcentaje = 0;
        break;
      default:
        Serial.print("Error");
        break;
    }
    tiempoAnteriorB = tiempoActual;
  }
  moverMotor();
}

void moverMotor() {  
  int porcentajeVel = (4095 * porcentaje) / 100;
  ledcWrite(channel, porcentajeVel);
  digitalWrite(MA, LOW);
  digitalWrite(MB, HIGH);
}

void calcularVelocidad() {
  
  // Calcular cambio en tiempo
  unsigned long deltaTime = (tiempoActual - tiempoAnteriorA);

  // Calcular ángulo en grados
  angulo = 360+(int(((pulses % PPR) * 360.0 / PPR)) % 360); // Ajuste para que el ángulo quede entre 0° y 359°

  // Calcular velocidad angular en radianes por segundo
  velocidad_rads = (float(angulo - anguloAnterior) * PI) / ((180*deltaTime) / 1000); // Ajuste para que la diferencia de ángulo sea en radianes

  // Convertir velocidad a rps y rpm
  velocidad_rps = velocidad_rads / (2 * PI);
  velocidad_rpm = velocidad_rps * 60;
}

void imprimirResultados(){
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
