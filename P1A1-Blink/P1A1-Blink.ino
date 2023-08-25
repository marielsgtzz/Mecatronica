#define LED 15 //Definir el GPIO15 como "LED"

void setup() {
  pinMode(LED,OUTPUT); //Configurar el LED como una salida
}

void loop() {
  digitalWrite(LED,HIGH); //Manda una señal para encender el LED
  delay(500); //Esperar medio segundo
  digitalWrite(LED,LOW); //Apagar el LED
  delay(500); //Esperar medio segundo
}
