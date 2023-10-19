//P6A2–Contador de Vueltas

#define Rojo 4
#define Amarillo 5
#define Verde 15
#define Button 23

int factor = 1;
int tiempo = 20;

void IRAM_ATTR ISR(){
  Serial.println("Botón presionado");
  factor++;
}

void setup() {
  pinMode(Rojo, OUTPUT);
  pinMode(Amarillo, OUTPUT);
  pinMode(Verde, OUTPUT);
  pinMode(Button, INPUT);

  attachInterrupt(digitalPinToInterrupt(Button),ISR,RISING);

  Serial.begin(115200);
}

void loop() {
  digitalWrite(Rojo, LOW);
  digitalWrite(Verde, HIGH);
  delay(factor*tiempo);
  digitalWrite(Verde, LOW);
  digitalWrite(Amarillo, HIGH);
  delay(factor*tiempo);
  digitalWrite(Amarillo, LOW);
  digitalWrite(Rojo, HIGH);
  delay(factor*tiempo);
    
  Serial.println(factor*tiempo);
}
