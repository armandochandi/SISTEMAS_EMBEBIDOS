/*
 * TOMA DE DATOS DE JOYSTICK 
 */

int x;        // variable para almacenar valor leido del eje X
void setup(){
  Serial.begin(9600);
}
void loop(){
delay(30);
  x = analogRead(A0);     // lectura de valor de eje x
  if (x >= 0 && x < 480){         // si X esta en la zona izquierda
    Serial.println("0");   
  } 
 else if (x > 520 && x <= 1023){          // si X esta en la zona derecha
    Serial.println("1");  
  }     
}
