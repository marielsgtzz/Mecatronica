#define LEDR1 23 //Define el GPI23 como "LEDR1"
#define LEDA1 22 //Define el GPI22 como "LEDA1"
#define LEDV1 01 //Define el GPI01 como "LEDV1"

#define LEDR2 4 //Define el GPI4 como "LEDR2"
#define LEDA2 2 //Define el GPI2 como "LEDA2"
#define LEDV2 15 //Define el GPI15 como "LEDV2"

void setup() {
  pinMode(LEDR1,OUTPUT); //Configura el LED rojo 1 como una salida
  pinMode(LEDA1,OUTPUT); //Configura el LED amarillo 1 como una salida
  pinMode(LEDV1,OUTPUT); //Configura el LED verde 1 como una salida
  pinMode(LEDR2,OUTPUT); //Configura el LED rojo 2 como una salida
  pinMode(LEDA2,OUTPUT); //Configura el LED amarillo 2 como una salida
  pinMode(LEDV2,OUTPUT); //Configura el LED verde 2 como una salida
  Serial.begin(115200); //Establece comunicación serial a 115,200 baudios
}

void loop() {
    digitalWrite(LEDR1,HIGH); //prender el led rojo 1
    digitalWrite(LEDV2,HIGH); //prender el led verde 2
    delay(5000); //esperar 5 segundos
    digitalWrite(LEDV2,LOW); //apagar el led verde 2
    digitalWrite(LEDA2,HIGH); //prender el led amarillo 2
    delay(1000); //esperar 1 segundo
    digitalWrite(LEDR1,LOW); //apagar el led rojo 1
    digitalWrite(LEDA2,LOW); //apagar el led amarillo 2
    digitalWrite(LEDV1,HIGH); //prender el led verde 1
    digitalWrite(LEDR2,HIGH); //prender el led rojo 2
    delay(5000); //esperar 5 segundos
    digitalWrite(LEDV1,LOW); //apagar el led verde 1
    digitalWrite(LEDA1,HIGH); //prender el led amarillo 1
    delay(1000); //esperar 1 segundo
    digitalWrite(LEDA1,LOW); //apagar el led amarillo 1
    digitalWrite(LEDR2,LOW); //apagar el led rojo 2
}
