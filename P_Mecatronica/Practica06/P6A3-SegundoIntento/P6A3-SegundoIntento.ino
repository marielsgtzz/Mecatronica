//P6A2–Contador de Vueltas
//enviar una señal al motor para que gire a una velocidad constante máxima
//en sentido dextrógiro por 3 segundos, se detenga por 2 y gire en
//sentido levógiro a velocidad constante máxima durante 3 segundos y enseguida, se quede detenido por 2

//El puente H va a estar leyendo la señal del encoder la cual emite pulsos en ambos sentidos de giro

//El progama cuenta las vueltas que está realizando y muestra en el monitor serial qué tipo de giro es y cuántas vueltas van
//(Sentido dextrogiro - negativas) (Sentido levogiro - positivas)

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

int porcentaje = 0;
unsigned long tiempoAnteriorA = 0;
unsigned long tiempoAnteriorB = 0;
unsigned long tiempoActual = 0;

void IRAM_ATTR PulsesCounter() {
  if (digitalRead(EncB) == HIGH) {
    pulses++;
  } else {
    pulses--;
  }
}

void setup() {
  pinMode(EnM, OUTPUT);
  pinMode(MA, OUTPUT);
  pinMode(MB, OUTPUT);
  pinMode(EncA, INPUT);
  pinMode(EncB, INPUT);
  attachInterrupt(digitalPinToInterrupt(EncA), PulsesCounter, RISING);
  ledcSetup(channel, freq, resolution);
  ledcAttachPin(EnM, channel);
  Serial.begin(115200);
  tiempoActual = millis(); // Usa directamente millis() para el tiempo en milisegundos
}

void loop() {
  tiempoActual = millis();
  // Comprobación para imprimir en el monitor serial cada 100 ms
  if (tiempoActual - tiempoAnteriorA == 100) {
    Serial.print("Pulsos:");
    Serial.print(pulses);
    Serial.print(" || ");
    Serial.print("%");
    Serial.print(porcentaje);
    Serial.print("\n");
    tiempoAnteriorA = tiempoActual;
    
  }

  // Comprobación para cambiar la velocidad del motor cada 3 segundos
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
