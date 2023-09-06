// Usaremos la librería math.h para calcular la tangente inversa de a y b
#include<math.h>
#include <Servo.h> //Incluir biblioteca del servo

#define X 33
#define Y 32
#define Z 25
#define servoPin 23 //Declarar el pin 23 como "servoPin"

// Variables que usamos para pedir las coordenadas y transformarlas a g
float Xval, Yval, Zval;
float Xg,Yg,Zg;

// Valores de referencia obtenidos en bits de manera experimental
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

Servo miservo;

void setup() {
  Serial.begin(115200);
  miservo.attach(servoPin); //establecer ue el servo está en el pin 23
}

void loop() {
  // Lee los valores de cada coordenada
  Xval = analogRead(X);
  Yval = analogRead(Y);
  Zval = analogRead(Z);

  // Mapea los valores leídos con base en la referencia
  Xg = map(Xval,X_min,X_max,100,-100);
  Xg = Xg/100;
  Yg = map(Yval,Y_min,Y_max,-100,100);
  Yg = Yg/100;
  Zg = map(Zval,Z_min,Z_max,-100,100);
  Zg = Zg/100;

  // Imprime las coordenadas en g
  Serial.print("X: ");
  Serial.print(Xg);
  Serial.print(" Y: ");
  Serial.print(Yg);
  Serial.print(" Z: ");
  Serial.println(Zg);

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
  miservo.write(c); //Hacer que el servo se mueva al ángulo equivalente

  // Imprime los ángulos de roll y pitch
  Serial.print("Roll: ");
  Serial.print(a);
  Serial.print("° ----- Pitch: ");
  Serial.print(b);
  Serial.print("° ----- Servo: ");
  Serial.print(c);
  Serial.println("°");

  // Enviamos el ángulo al servo
  // ???
  
}
