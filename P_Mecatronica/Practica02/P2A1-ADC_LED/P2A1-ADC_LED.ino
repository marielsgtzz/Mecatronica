#define Pot 4 //Definir el GPIO4 como "Pot"
#define LED 15 //Definir el GPIO15 como "LED"

int val; //Definir la variable "val" como entero
double vol;

void setup() {
  pinMode(LED,OUTPUT); //Configurar el led como una salida
  Serial.begin(115200); //Iniciar comunicación serial a 115,200 baudios
}

void loop() {
  val = analogRead(Pot); //Asignar la lectura del potenciómetro a la variable "val"
  vol = (val*3.3)/4095;
  if (vol >= 2) { //Si el voltaje es mayor a 2
    digitalWrite(LED,HIGH); //Prender el LED
  }

  else{ //Si el botón no está presionado
    digitalWrite(LED,LOW); //Apagar el LED
  }
  Serial.print("ADC = "); //Imprimir "Valor: "
  Serial.print(val); //Imprimir el valor de la variable "val"
  Serial.print("bits ----- V = "); //Imprimir "Valor: "
  Serial.print(vol); //Imprimir el valor de la variable "val"
  Serial.println("Volts"); //Imprimir "Valor: "
  delay(100); //Esperar 0.1 segundos
}
