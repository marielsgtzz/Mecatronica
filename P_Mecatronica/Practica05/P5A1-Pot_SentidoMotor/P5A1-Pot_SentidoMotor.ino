// Definición de pines
#define EnM 13       // Pin para habilitar/deshabilitar el motor
#define MA 12        // Pin de control A para el puente H
#define MB 14        // Pin de control B para el puente H
#define Pot 4        // Pin para el Potenciometro

int channel = 0;     // Canal PWM que se usará
int freq = 1000;     // Frecuencia de la señal PWM
int resolution = 12; // Resolución de la señal PWM
int val;             // Para almacenar la lectura bruta del potenciómetro
double vol;          // Para almacenar el valor leído del potenciómetro como un valor de voltaje
String modoGiro;

void setup() {
  pinMode(EnM, OUTPUT);  // Configura el pin EnM como salida
  pinMode(MA, OUTPUT);   // Configura el pin MA como salida
  pinMode(MB, OUTPUT);   // Configura el pin MB como salida

  // Configura el PWM
  ledcSetup(channel, freq, resolution);

  // Asocia el canal PWM al pin EnM
  ledcAttachPin(EnM, channel);

  // Inicia la comunicación serie a 115200 baudios
  Serial.begin(115200);
}

void loop() {

  val = analogRead(Pot); //Asignar la lectura del potenciómetro a la variable "val"
  
  //La ESP32 tienen una resolución de 12 bits, el valor que leen varía entre 0 y 4095. 
  //El voltaje máximo que puede leer el ADC es 3.3V, entonces un valor de 4095 en el ADC corresponde a 3.3V.
  vol = (val*3.3)/4095; 

  if (0 <= vol < 1.32) { //el motor girará en sentido levógiro
    modoGiro = "Levogiro";
    ledcWrite(channel, 1000);     // Establece el valor PWM en 1000
    digitalWrite(MA, LOW);       // Establece el pin MA en BAJO
    digitalWrite(MB, HIGH);      // Establece el pin MB en ALTO
  } else if (1.32 <= vol < 1.98) { //el motor se quedará detenido
    modoGiro = "Detenido";
    ledcWrite(channel, 0);       // Establece el valor PWM en 0
    digitalWrite(MA, LOW);      // Establece el pin MA en ALTO
    digitalWrite(MB, LOW);       // Establece el pin MB en BAJO
  } else { //el motor girará en sentido dextrogiro si se recibe un voltaje entre 1.98 y 3.3 V, 
    modoGiro = "Dextrogiro";
    ledcWrite(channel, 1000);      // Establece el valor PWM en 1000
    digitalWrite(MA, HIGH);       // Establece el pin MA en ALTO
    digitalWrite(MB, LOW);        // Establece el pin MB en BAJO
  }

  Serial.print("Voltaje: "+vol+" V --- "+modoGiro); 
  delay(200); //Esperar 0.2 segundos

}
