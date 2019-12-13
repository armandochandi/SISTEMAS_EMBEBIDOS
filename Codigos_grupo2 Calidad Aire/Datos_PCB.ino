/*
 * UNIVERSIDAD TÉCNICA DEL NORTE 
 * FICA-CIERCOM
 * SISTEMAS EMBEBIDOS
 * DATOS OBTENIDOS DESDE PCB
 */
#include "Type4051Mux.h" //libreria para lectura de mux
#include <DHT.h>
#define DHTPIN 13 // Definimos el pin digital donde se conecta el sensor
#define DHTTYPE DHT11 // Dependiendo del tipo de sensor
DHT dht(DHTPIN, DHTTYPE); // Inicializamos el sensor DHT11
int valor;
float limite;
float mq135;
int uvNivel, refNivel; 
int dato;
Type4051Mux mux(A0, INPUT, ANALOG, 1, 3, 15); //pines para control del canal 

//LEDS INDICADORES
int aire=4,diox=5,butano=16;
//interrupcion 
int var=LOW;
void setup() {
  Serial.begin(9600); // Inicializamos comunicación serie.
  pinMode(2,INPUT); //entrada digital MQ7
  pinMode(aire,OUTPUT); //leds indicadores
  pinMode(diox,OUTPUT);
  pinMode(butano,OUTPUT);
  Serial.println("CONDICIONES DEL AIRE");
  Serial.println(' ');
  dht.begin();
  delay(50);
}
void loop() {
    // Esperamos 5 segundos entre medidas
  delay(500);
  // Leemos la humedad relativa
  float h = dht.readHumidity();
  // Leemos la temperatura en grados centígrados (por defecto)
  float t = dht.readTemperature(); 
  // Comprobamos si ha habido algún error en la lectura
  if (isnan(h) || isnan(t)) {
    Serial.println("Error obteniendo los datos del sensor DHT11");
    return;
  }
  float humedad=map(h,0,1023,20.0,90.0); //calibracion de humedad % y temperatura *C
  float temp=map(t,0,1023,20.0,50.0);;
  //Serial.print("Humedad= ");
  Serial.print(humedad); 
  //Serial.print("%");
  Serial.print(' ');
  Serial.print("|");
  Serial.print(' ');
  //Serial.print("*C= ");
  Serial.print(temp);
  Serial.print(' ');
  Serial.print("|");
  //Serial.print(' ');
   //MQ7
   limite=mux.read(7);
   valor=digitalRead(14);
   //limite=analogRead(1);
   //Serial.print("%CO=");
   float CO = map(limite,0,1023,300.0,2000.0); //medicion ppm
   Serial.print(' ');
   Serial.print(CO);
   Serial.print(' ');
   Serial.print("|");

   //MQ135
   mq135=mux.read(6);
   //mq135=analogRead(0);
   float CO2 = map(mq135,0,1023,10.0,1000.0); //medicion en ppm
   //Serial.print("ppmCO2= ");
   Serial.print(' ');
   Serial.print(CO2);
   Serial.print(' ');
   Serial.print("|");
   //sensor UV
   uvNivel=mux.read(4);
   refNivel=mux.read(5);
   //uvNivel=analogRead(2);
   //refNivel=analogRead(3);
   float salida = 3.3 / refNivel * uvNivel;
   float uvIntensity = map(salida,0.99, 2.8 ,2.0, 15.0); //Convertir el voltaje a un nivel de intensidad UV
   //Serial.print("UV= ");
   Serial.print(' ');
   Serial.println(uvIntensity/10);
   Serial.print(' ');
    if(CO2>0 && CO2<55){
   // Serial.println("Aire normal");
    digitalWrite(aire,HIGH);
    digitalWrite(diox,LOW);
    digitalWrite(butano,LOW);  
    delay(100);  
    }else if(CO2>56 && CO2<150){
    //Serial.println("Aire con CO2");
    digitalWrite(aire,LOW);
    digitalWrite(diox,HIGH);
    digitalWrite(butano,LOW); 
    delay(100);  
      }else if(CO2>151 && CO2<399){
    //Serial.println("Dioxido de carbono");
    digitalWrite(aire,LOW);
    digitalWrite(diox,HIGH);
    digitalWrite(butano,LOW); 
    delay(100);
          }else if(CO2>400){
    //Serial.println("GAS PROPANO Y BUTANO");
    digitalWrite(aire,LOW);
    digitalWrite(diox,LOW);
    digitalWrite(butano,HIGH); 
    delay(100); 
          }

}
