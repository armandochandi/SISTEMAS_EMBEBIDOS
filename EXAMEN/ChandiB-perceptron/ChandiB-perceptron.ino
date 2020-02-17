 #include "matriz_entrenamiento.h"
/*
 * ********************       UNIVERSIDAD TÉCNICA DEL NORTE           *******************
 * ********************               FICA-CIERCOM                    *******************
 * ********************           SISTEMAS EMBEBIDOS                  *******************
 * EXAMEN FINAL
 * Nombre: Chandi Bryan
 * Tema: PERCEPTRON
 */
//funcionamiento de una neurona
//cada dato es un dato de ingreso a la neurona (conjunto es perceptron)
/*************DATOS DE ENTRADA***********/
//de 602 datos de entrada se determinaron 120 datos para prueba al azar 
/*****HUMEDAD/pm10/pm2.5/UV/ETIQUETA***(la temperatura no se tomo en cuenta ya que despues de los analisis en R resulto ser una variable poco relevante)*/

//la etiqueta es 1=aire no contaminado o 0= aire contaminado

/**************PASOS********************/
//1: los datos ingresan fila por fila como una neurona de entrada, se guardan en variable
//2: funcion de activacion transfroma el valor en uno nuevo para determinar calidad del aire 
//en funcion de la relacion con la sumatoria de datos de entrada, es decir compara la sumatoria de la fila y la relaciona con un intervalo
float dato_prueba[]={75,12.17,10.57,6.2};
int pred[120]; //valor de la prediccion 
int fil,col;//recorres matriz de entrenamiento 
int sumatoria[120];//almacenar suma de cada fila en cada posicion
int i=0; //contador
float sumatoriaDato; //evaluacion de dato de prueba 
//a cada variable se le da un peso (impacto sobre la neurona) para el paso a funcion de activacion (umbral), los pesos se asiganron de acuerdo a la evaluacion de importancia
//mostrada con ayuda de Rstudio
float p0=0.7; //humedad
float p1=0.87; //pm10
float p2=0.36; //pm2.5
float p3=0.5; //uv
float umbral;
float sum_umbral=0;
float interacciones=0;
float cont=0; //contador de interacciones correctas
void setup() {
Serial.begin(9600);
}
void loop() {
delay(250);
for(;interacciones<0.1;interacciones=interacciones+0.01){
  Serial.println("*****************************************************************");
  Serial.print("Interaccion: "); Serial.println(interacciones*100);
//sumatoria de cada cadena de datos sin etiquetas
for(fil=0;fil<120;fil++){ //numero de datos de entrada   
    sumatoria[fil]=((matriz[fil][0]*(p0+interacciones))+(matriz[fil][1]*(p1+interacciones))+(matriz[fil][2]*(p2+interacciones))+(matriz[fil][3]*(p3+interacciones/10))); //ecuacion 
    sum_umbral=sumatoria[fil]+sum_umbral;
}
//Serial.println(sum_umbral/120);//umbral de datos si el dato de entrada rebasa el umbral es aire contaminado, si es menor es aire no contaminado
//sumatoriaDato=((dato_prueba[0]*p0)+(dato_prueba[1]*p1)+(dato_prueba[2]*p2)+(dato_prueba[3]*p3));
//if(sumatoriaDato<(sum_umbral)/120){ //prediccion 
//  Serial.println("Aire no contaminado"); //1
//  pred=1;
//  }else{
//  Serial.println("Aire contaminado"); //0
//  pred=0;
//  }
  Serial.println("Pesos de cada variable");
  Serial.print("HUM/p0  : "); Serial.println(p0+interacciones);
  Serial.print("PM10/p1 : "); Serial.println(p1+interacciones);
  Serial.print("PM2.5/p2: "); Serial.println(p2+interacciones);
  Serial.print("UV/p3   : "); Serial.println(p3+interacciones);
  for(fil=0;fil<120;fil++){
    sumatoria[fil]=((matriz[fil][0]*p0)+(matriz[fil][1]*p1)+(matriz[fil][2]*p2)+(matriz[fil][3]*p3)); //sumatoria por fila
    if(sumatoria[fil]<(sum_umbral)/120){
      pred[fil]=1;
      }else if(sumatoria[fil]>(sum_umbral)/120){
      pred[fil]=0;
      }}
      for(fil=0;fil<120;fil++){
      if(matriz[fil][4]==pred[fil]){
      cont++;
      }
    }
Serial.print("Eficiencia:"); Serial.print((cont/12)*10); Serial.println("%");
sum_umbral=0;
cont=0;
}
interacciones=0;
}
