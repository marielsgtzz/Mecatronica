#define BOTON 2
#define LED 15

bool estadoBTN;

void setup() {
  pinMode(BOTON,INPUT);
  pinMode(LED,OUTPUT);
  Serial.begin(115200);

}

void loop() {
  estadoBTN = digitalRead(BOTON);

  if (estadoBTN == true) {
    Serial.println("Presionado");
    digitalWrite(LED,HIGH);
    delay(125);
    digitalWrite(LED,LOW);
    delay(125);
  }

  else{
    Serial.println("Sin presionar");
    digitalWrite(LED,HIGH);
    delay(500);
    digitalWrite(LED,LOW);
    delay(500);
  }
}
