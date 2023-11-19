
#define LedRojo1 5
#define LedRojo2 4
#define LedVerde 3
#define btn 2

int switchState = 0;

void setup() {
  pinMode(btn, INPUT); //Switch button

  //LEDS
  pinMode(LedRojo1, OUTPUT);
  pinMode(LedRojo2, OUTPUT);
  pinMode(LedVerde, OUTPUT);

}

void loop() {
  switchState = digitalRead(btn); //HIGH cuando hay voltaje (se le da click al btn) o LOW de lo contrario
      digitalWrite(LedVerde, HIGH);

  if(switchState == LOW){ //no se ha presionado el boton
    digitalWrite(LedVerde, HIGH);
    digitalWrite(LedRojo1, LOW);
    digitalWrite(LedRojo2, LOW);
  } else {
    digitalWrite(LedVerde, LOW);
    digitalWrite(LedRojo1, HIGH);
    digitalWrite(LedRojo2, LOW);
    delay(250); //espera un cuarto de segundo
    digitalWrite(LedRojo1, LOW);
    digitalWrite(LedRojo2, HIGH);
    delay(250);
  }
}
