#define BOTON 2 //Define el GPIO2 como "BOTON")
#define LED 15 //Define el GPIO15 como "LED")

bool estadoBTN; //Declara la variable "estadoBTN" como booleano (binario)

void setup() {
  pinMode(BOTON,INPUT); //Configura el botón como una entrada
  pinMode(LED,OUTPUT); //Configura el led como una salida
  Serial.begin(115200); //Establece comunicación serial a 115,200 baudios

}

void loop() {
  estadoBTN = digitalRead(BOTON); //Designa a la variable "estadoBTN" la lectura del botón

  if (estadoBTN == true) { //Si el botón está presionado
    Serial.println("Presionado"); //Imprime "Presionado"
    digitalWrite(LED,HIGH); //Enciende el LED
    delay(125); //Espera un cuarto de segundo
    digitalWrite(LED,LOW); //Apaga el LED
    delay(125); //Espera un cuarto de segundo
  }

  else{ //Si el botón no está presionado
    Serial.println("Sin presionar"); //Imprime "Sin presionar"
    digitalWrite(LED,HIGH); //Enciende el LED
    delay(500); //Espera medio segundo
    digitalWrite(LED,LOW); //Apaga el LED
    delay(500); //Espera medio segundo
  }
}
