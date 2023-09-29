// Incluye la librería Wire, que permite la comunicación I2C
#include <Wire.h>

// Incluye la librería LiquidCrystal_I2C, que permite controlar pantallas LCD con interfaz I2C
#include <LiquidCrystal_I2C.h>

// Crea un objeto lcd de la clase LiquidCrystal_I2C
// con la dirección I2C 0x27 y especifica que la pantalla tiene 16 columnas y 2 filas
LiquidCrystal_I2C lcd(0x27, 16, 2);

// La función setup() se ejecuta una vez al inicio del programa
void setup(){
  lcd.init();   // Inicializa el LCD

  
  lcd.backlight();   // Enciende la retroiluminación del LCD

  // La siguiente línea está comentada. Si se descomentara, apagaría la retroiluminación del LCD
  //lcd.noBacklight();
  
  // Llama a la función textoRebota() que hará que el texto se desplace (rebote) en la pantalla
  textoRebota();

  // Las siguientes lineas de codigo son para que se queden los nombres en posicion estatica despues de que "entraron" 
  lcd.setCursor(0,0);   // Establece la posición del cursor en la columna 0, fila 0
  lcd.print("Mariel Gtz Z"); // Imprime el primer nombre en la fila 0
  lcd.setCursor(0,1);   // Establece la posición del cursor en la columna 0, fila 1
  lcd.print("Danya G."); // Imprime el segundo nombre en la fila 1
  
  delay(1000);   // Espera 1000 milisegundos (1 segundo)
}
//No requerimos de esta funcion en esta actividad
void loop(){
  
}

// Define una función personalizada llamada textoRebota() que hace que el texto "Entre" del lado derecho hasta el extremo izquierdo
void textoRebota(){
  for(int i=16; i>0;i--){
    lcd.setCursor(i,0); // Establece la posición del cursor en la columna i, fila 0
    lcd.print("Mariel Gtz Z");
    lcd.setCursor(i,1); // Establece la posición del cursor en la columna i, fila 1
    lcd.print("Danya G.");
    
    delay(200); // Espera 200 milisegundos
    
    lcd.clear(); // Limpia el contenido de la pantalla LCD
  }
}
