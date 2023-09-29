#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
// TODO: Incluir la biblioteca para el ADXL335

BluetoothSerial SerialBT;
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myservo;

const int ADXL335_pin = ...;  // Definir el pin al que está conectado el ADXL335
const int servoPin = ...;    // Definir el pin al que está conectado el servo

void setup() {
  Serial.begin(115200);
  
  // Inicializa el Bluetooth
  SerialBT.begin("PlacaMariel");
  
  // Inicializa la pantalla LCD
  lcd.init();
  lcd.backlight();
  
  // Inicializa el servo
  myservo.attach(servoPin);
  
  // TODO: Inicializar el ADXL335
}

void loop() {
  // Lee el ángulo de rotación (Roll) del ADXL335
  float angle = readADXL335();
  
  // Procesa el ángulo leído y determina el ángulo del servo
  int servoAngle = processAngle(angle);
  
  // Controla el servo
  myservo.write(servoAngle);
  
  // Muestra la información en la pantalla LCD
  lcd.setCursor(0, 0);
  lcd.print("Sist.Mecatronico");
  lcd.setCursor(0, 1);
  lcd.print("Angulo: ");
  lcd.print((int)angle);
  lcd.print("*");
  
  delay(500);
}

float readADXL335() {
  // TODO: Leer el ángulo del ADXL335 y devolverlo
  return 0;  // Placeholder
}

int processAngle(float angle) {
  if (angle == -90) {
    return 0;
  } else if (angle >= -89 && angle <= -1) {
    return angle + 90;
  } else if (angle == 0) {
    return 90;
  } else if (angle >= 1 && angle <= 89) {
    return angle + 90;
  } else {
    return 180;
  }
}
