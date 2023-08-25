#define LED 15 //Definir el PIN 15 como "LED"

void setup() {
  pinMode(LED,OUTPUT);

}

void loop() {
  digitalWrite(LED,HIGH); //Mandar una señal
  delay(500); //Dejar pasar medio segundo
  digitalWrite(LED,LOW);
  delay(500);
}
