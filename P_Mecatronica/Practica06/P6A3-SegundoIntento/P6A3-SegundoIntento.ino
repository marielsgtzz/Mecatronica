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

int channel = 0;     // Canal PWM que se usará
int freq = 1000;     // Frecuencia de la señal PWM
int resolution = 12; // Resolución de la señal PWM --> Vel máxima es 4095 
volatile long pulses = 0;  // Cuenta de pulsos del encoder
const int PPR = 284;      // Pulsos por revolución del eje de salida del reductor

int porcentaje = 0;

// Función que se llama cada vez que el pin A del encoder tiene un flanco ascendente
void IRAM_ATTR PulsesCounter() {
  if(digitalRead(EncB)==HIGH){
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

void loop() {
  switch(porcentaje){
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
  
  int porcentajeVel = (4095 * porcentaje) / 100;
  // Girar a la izquierda durante 3 segundos
  ledcWrite(channel, porcentajeVel);
  //analogWrite(EnM, 255);  // Velocidad máxima
  digitalWrite(MA, LOW);
  digitalWrite(MB, HIGH);
  

  Serial.print("Pulsos:");
  Serial.print(pulses);
  Serial.print(" || ");

  Serial.print("%");
  Serial.print(porcentaje);
  Serial.print("\n");


  delay(3000);

}
