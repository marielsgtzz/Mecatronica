#define EncA 19
#define EncB 18
#define ResetButton 5 // Asumiendo pin 5 para un botón de reinicio, cambia si es necesario

volatile long pulses = 0; // volatile porque se cambia dentro de un ISR

void IRAM_ATTR PulsesCounter(){
  if(digitalRead(EncB)==HIGH){
    pulses++;
  } else {
    pulses--;
  }
}

void setup() {
  pinMode(EncA, INPUT);
  pinMode(EncB, INPUT);
  pinMode(ResetButton, INPUT_PULLUP); // Asumiendo que el botón se conecta a tierra al presionarse

  attachInterrupt(digitalPinToInterrupt(EncA), PulsesCounter, RISING);

  Serial.begin(115200);
}

void loop() {
  // Verificar si se presiona el botón de reinicio
  if (digitalRead(ResetButton) == LOW) {
    pulses = 0; // Reinicia el conteo de pulsos
    delay(1000); // Retardo para antirebote
  }
  printValues();
  delay(100); // Agregar un retardo para reducir la frecuencia de impresiones seriales
}

void printValues(){
  Serial.print("Pulsos: ");
  Serial.println(pulses);
}
