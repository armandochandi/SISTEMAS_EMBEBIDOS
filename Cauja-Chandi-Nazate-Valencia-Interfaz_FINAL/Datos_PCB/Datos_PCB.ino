/*
 * UNIVERSIDAD TÉCNICA DEL NORTE 
 * FICA-CIERCOM
 * SISTEMAS EMBEBIDOS
 * DATOS OBTENIDOS DESDE PCB
 */
//#include <NTPClient.h> //importamos la librería del cliente NTP
//#include <ESP8266WiFi.h> //librería necesaria para la conexión wifi
//#include <WiFiUdp.h> // importamos librería UDP para comunicar con NTP
//// datos para conectarnos a nuestra red wifi
//const char *ssid     = "LADY";
//const char *password = "Dx13016br+";
//WiFiUDP ntpUDP;
//NTPClient timeClient(ntpUDP, "0.south-america.pool.ntp.org",-18000,6000);
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
  Serial.begin(115200); // Inicializamos comunicación serie.
//  WiFi.begin(ssid, password); //se establece la coneccion wifi
//  while ( WiFi.status() != WL_CONNECTED ) {
//    delay ( 500 );
//    Serial.print ( "." );
//  }
//  timeClient.begin(); 
  dht.begin();
  pinMode(2,INPUT); //entrada digital MQ7
  pinMode(aire,OUTPUT); //leds indicadores
  pinMode(diox,OUTPUT);
  pinMode(butano,OUTPUT);
  Serial.println("CONDICIONES DEL AIRE");
  delay(50);
}
void loop() {
  String datos= "";
    // Esperamos 0.5 segundos entre medidas
  delay(200);
//  timeClient.update(); //sincronizamos con el server NTP
//  Serial.print(timeClient.getFormattedTime());
//  Serial.print(' ');
//  Serial.print("|");
//  
  float h = dht.readHumidity();// Lectura de humedad relativa
  float t = dht.readTemperature(); // Lectura de temperatura en grados centígrados (por defecto)
  /*if (isnan(h) || isnan(t)) { // Comprobamos si ha habido algún error en la lectura
    Serial.println("Error obteniendo los datos del sensor DHT11");
    return;
  }*/
  //Serial.print("Humedad= ");
  datos+=String(h);
 // Serial.print("%");
 
  datos+=","+String(t);
  //Serial.print("*C")
  
   //MQ7
   limite=mux.read(7);
   valor=digitalRead(14);
   float CO = map(limite,0,1023,30.0,100.0); //medicion porcentaje
   datos+=","+String(CO);
   //MQ135
   mq135=mux.read(6);
   float CO2 = map(mq135,0,1023,10.0,100.0); //medicion porcentaje
   datos+=","+String(CO2);
   //sensor UV
   uvNivel=mux.read(4);
   refNivel=mux.read(5);
   float salida = 3.3 / refNivel * uvNivel;
   float uvIntensity = map(salida,0.99, 2.8 ,2.0, 15.0); //Convertir el voltaje a un nivel de intensidad UV
   //Serial.print("UV= ");
   datos+=","+String(uvIntensity/10);
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
Serial.println(datos);
}
