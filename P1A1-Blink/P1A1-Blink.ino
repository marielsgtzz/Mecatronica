#define LED 15 //Define el GPIO15 como "LED"

void setup() {
  pinMode(LED,OUTPUT); //Configura el LED como una salida
}

void loop() {
  digitalWrite(LED,HIGH); //Manda una señal para encender el LED
  delay(500); //Espera medio segundo
  digitalWrite(LED,LOW); //Apaga el LED
  delay(500); //Espera medio segundo
}
