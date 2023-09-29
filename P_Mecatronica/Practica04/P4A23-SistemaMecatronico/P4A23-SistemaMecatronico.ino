#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#define servoPin 23
#define X 14
#define Y 12
#define Z 13

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo elServo;

// Valores de referencia del ADXL335 obtenidos experimentalmente
float X_min = 1509;
float X_max = 2359;
float Y_min = 1490;
float Y_max = 2347;
float Z_min = 1507;
float Z_max = 2375;

void setup() {
  Serial.begin(115200);
  
  // Inicializa la pantalla LCD
  lcd.init();
  lcd.backlight();
  
  // Inicializa el servo
  elServo.attach(servoPin);
  
  // TODO: Inicializar el ADXL335
}

void loop() {
  // Lee el ángulo de rotación (Roll) del ADXL335
  float rollAngle = readADXL335();
  
  // Procesa el ángulo leído y determina el ángulo del servo
  int servoAngle = processAngle(rollAngle);
  
  // Controla el servo
  elServo.write(servoAngle);
  
  // Muestra la información en la pantalla LCD
  lcd.setCursor(0, 0);
  lcd.print("Sist.Mecatronico");
  lcd.setCursor(0, 1);
  lcd.print("Angulo: ");
  lcd.print((int)angle);
  lcd.print("°");
  
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
    return -angle;
  } else if (angle == 0) {
    return 90;
  } else if (angle >= 1 && angle <= 89) {
    return angle + 90;
  } else {
    return 180;
  }
}

float readADXL335() {
  float Xval = analogRead(X);
  float Yval = analogRead(Y);
  float Zval = analogRead(Z);

  // Convertir los valores leídos a g
  float Xg = map(Xval, X_min, X_max, -1, 1);
  float Yg = map(Yval, Y_min, Y_max, -1, 1);
  float Zg = map(Zval, Z_min, Z_max, -1, 1);

  // Calcular el ángulo de roll usando la arco tangente
  float roll = atan2(Yg, sqrt(Xg*Xg + Zg*Zg)) * 180.0 / PI;

  return roll;
}
