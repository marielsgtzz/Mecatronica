#include <Servo.h> //Incluir biblioteca del servo
#define Pot 4 //Definir el GPIO4 como "Pot"
#define servoPin 22 //Declarar el pin 22 como "servoPin"

Servo miservo; //definir miservo como objeto de la biblioteca servo
int val;
int ang;

void setup() {
  miservo.attach(servoPin); //establecer ue el servo está en el pin 22
}

void loop() {
  val = analogRead(Pot); //Asignar la lectura del potenciòmetro a la variable "val"
  ang = map(val,0,4095,0,180);
  miservo.write(ang); //Hacer que el servo se mueva al ángulo equivalente
  Serial.print("ADC = "); //Imprimir "Valor: "
  Serial.print(val); //Imprimir el valor de la variable "val"
  Serial.print("bits ----- Theta = "); //Imprimir "Valor: "
  Serial.print(ang); //Imprimir el valor de la variable "val"
  Serial.println("°"); //Imprimir "Valor: "
  delay(100); //Esperar 0.1 segundos
}
