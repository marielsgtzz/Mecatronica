#define LEDR1 23
#define LEDA1 22
#define LEDV1 01

#define LEDR2 4
#define LEDA2 2
#define LEDV2 15

void setup() {
  pinMode(LEDR1,OUTPUT);
  pinMode(LEDA1,OUTPUT);
  pinMode(LEDV1,OUTPUT);
  pinMode(LEDR2,OUTPUT);
  pinMode(LEDA2,OUTPUT);
  pinMode(LEDV2,OUTPUT);
  Serial.begin(115200);
}

void loop() {
    digitalWrite(LEDR1,HIGH);
    digitalWrite(LEDV2,HIGH);
    delay(5000);
    digitalWrite(LEDV2,LOW);
    digitalWrite(LEDA2,HIGH);
    delay(1000);
    digitalWrite(LEDR1,LOW);
    digitalWrite(LEDA2,LOW);
    digitalWrite(LEDV1,HIGH);
    digitalWrite(LEDR2,HIGH);
    delay(5000);
    digitalWrite(LEDV1,LOW);
    digitalWrite(LEDA1,HIGH);
    delay(1000);
    digitalWrite(LEDA1,LOW);
    digitalWrite(LEDR2,LOW);
}
