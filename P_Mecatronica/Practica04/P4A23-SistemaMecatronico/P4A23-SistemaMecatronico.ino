#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#define servoPin 23
#define X 14
#define Y 12
#define Z 13
// Variables que usamos para pedir las coordenadas y transformarlas a g
float Xval, Yval, Zval;
float Xg,Yg,Zg;
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo elServo;

// Valores de referencia del ADXL335 obtenidos experimentalmente
float X_min = 1509;
float X_max = 2359;
float Y_min = 1490;
float Y_max = 2347;
float Z_min = 1507;
float Z_max = 2375;

// Variables para los ángulos de roll (a), pitch (b) y el movimiento del servo (c)
float a;
float b;
float c;
float d;

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
  elServo.write(servoPin, servoAngle);  // Modificado para usar dos argumentos
  
  // Muestra la información en la pantalla LCD
  lcd.setCursor(0, 0);
  lcd.print("Sist.Mecatronico");
  lcd.setCursor(0, 1);
  lcd.print("Angulo: ");
  lcd.print((int)rollAngle);  // Modificado para usar rollAngle
  lcd.print("°");
  
  delay(500);
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

 // Mapea los valores leídos con base en la referencia
  Xg = map(Xval,X_min,X_max,100,-100);
  Xg = Xg/100;
  Yg = map(Yval,Y_min,Y_max,-100,100);
  Yg = Yg/100;
  Zg = map(Zval,Z_min,Z_max,-100,100);
  Zg = Zg/100;
  
  //Para que se impriman más despacio los resultados
  delay(50);

  // Calcula los ángulos de roll y pitch 
  a = atan((Yg)/sqrt(pow(Xg,2) + pow(Zg,2)));
  b = atan((Xg)/sqrt(pow(Yg,2) + pow(Zg,2)));

  /*Calculamos el ángulo en que se moverá el servo con base en el ángulo de roll
     y los datos de la tabla "Lógica del Movimiento" en el reporte
     
     Observamos que es una ecuación lineal con pendiente = 90/180 = 1/2 = 0.5
     Ajustamos para la diferencia y nuesta ecuación es y = 0.5*x + 45*/

  d = a*100; //factor de aumento x100 para que el cambio sea visible en el servo, puesto que los valores de a son muy pequeños (de -1 a 1 aprox.)
  c = d*.5 + 45;

  return c;
}
