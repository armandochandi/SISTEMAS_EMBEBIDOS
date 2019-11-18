/*
 * UNIVERSIDAD TÉCNICA DEL NORTE 
 * FICA-CIERCOM
 * Nombre: Chandi Bryan 
 * Fecha: 18-11-2019
 * TEMA: CNN - obtener valores asertados  
 */
#include "matriz_entrenamiento.h"
float datos_prueba[5]={6.2,2.9,4.3,1.3,2}; //6,2  2,9 4,3 1,3
int respuesta; //respuesta de prediccion 

void setup() {
 Serial.begin(9600); //inicializacion serial 
}

void loop() {
  cnn(3,5,120); //declaracion valor cnn: etiquetas, tamaño de columnas y tamaño de filas 
  delay(5000);
  //Serial.println();//validacion de prediccion acertada D=acertada y S=no acertada - detalles de valores 
}

int knn (int k,int etiquetas, int tam_col, int tam_fil){ //valores knn 
  int col; 
  int fil;
  int i=0;
  int j; 
  int etiqueta;
  float aux;
  float aux_eti;
  float sumatoria=0; // sumatoria de la elevación al cuadrado de cada col
  float distancia=0; // raiz de sumatoria
  
  /*matriz de k-vecinos
  |1|2|3| -> numero de vecinos
  |2|1|1| -> asginacion del vecino por etiqueta
  |0.1|0.2|0.3| -> distancia
  */
 float matriz_k[3][k];
 
  /* etiquetas
  |1|2|3| -> etiquetas que existe dentro de la base de datos
  |2|1|0| -> conteo de etiquetas dentro de los k-vecinos
   */
 int matriz_etiq[2][etiquetas];
  // asignar numero de vecinos y enceramos asignación de etiqueta
  //2 es el numero de vecinos 
  
   for(;i<k;i++){
      matriz_k[0][i]=i+1.0;
      matriz_k[1][i]=0;
      matriz_k[2][i]=3000.0+i;
    /*
     |1|2|3|
     |0|0|0|
     |3000|3001|3002|
     */
    }
   // asignar etiquetas y enceramos su contador
   for(i=0;i<etiquetas;i++){
    matriz_etiq[0][i]=i+1;
    matriz_etiq[1][i]=0;
    /*
     |1|2|3| 
     |0|0|0|
     */
    }
    /*PASOS PARA K-NN
     * Leer cada fila de la matriz de entrenamiento
     * distancia entre la fila de la matriz con la nueva instancia (vector de prueba)
     * ordenar la matriz matriz_k (determinar los k vecinos de menor distancia), matriz_k resultados de las diatancias con vector de prueba 
     * contar las etiquetas en la matriz_k y asignar en matriz etiquetas
     * eligo al mayor número de matriz etiquetas
     * retorno la etiqueta resultante
     * 
     */

     for(fil=0;fil<tam_fil;fil++){
         for(col=0;col<tam_col-1;col++){ // menos 1 por ultima columna es etiqueta
             sumatoria=sumatoria+pow(matriz[fil][col]-datos_prueba[col],2);
          }
             distancia=sqrt(sumatoria);
             // comparación de nuevo dato con solo la distacia mayor almacenada en matriz_k
              if(distancia<matriz_k[2][k-1]){
                 matriz_k[2][k-1]=distancia;
                 matriz_k[1][k-1]=matriz[fil][tam_col-1];
                 //ordenar por metodo burbuja
                 for (i=0;i<k;i++){
                     for(j=i+1;j<k;j++){
                          if(matriz_k[2][i]>matriz_k[2][j]){
                            //distancia
                             aux=matriz_k[2][i];
                             matriz_k[2][i]=matriz_k[2][j];
                             matriz_k[2][j]=aux;
                             // etiqueta
                              aux_eti=matriz_k[1][i];
                             matriz_k[1][i]=matriz_k[1][j];
                             matriz_k[1][j]=aux_eti;
                            } //end if
                      } //end for
                  }
                 //fin ordenamiento 
              } 
              //fin condicion de numero menor
              sumatoria=0;
        }
        // fin de lectura de matriz
        // contar por columna, cuantos vecinos hay por etiqueta
        for(i=0;i<etiquetas;i++){
          for(j=0;j<k;j++){
              if(matriz_etiq[0][i]==matriz_k[1][j]){
                 matriz_etiq[1][i]++;
                }
            }
          }

         // buscar la etiqueta con mayor numero de vecinos

        for(i=0;i<etiquetas-1;i++){
            if(matriz_etiq[1][i]<matriz_etiq[1][i+1])
               etiqueta=matriz_etiq[0][i+1];
            else
              etiqueta=matriz_etiq[0][i];
          }
        
        return etiqueta;    
     }

//INICIO DE CNN
void cnn (int etiquetas, int tam_col, int tam_fil){
  int i;
  int j;
  int l;
  float sumatoriapot=0; //guarda el valor de cada potencia
  float raiz_s=0; //variable para raiz de la sumatoria 
  float centroid=0;
  float matriz_raices[j][l];
  float matriz_predic[j][1]; //etiquetas predecidas 
/*  
 *   centroides -> promedio
 *                 promedio por columna y por etiqueta
 *                 almaceno vectores 
 *                 knn entre vectores y matriz de entrenamiento
 */
//primero encerar matriz 
 float centroides [etiquetas][tam_col]; //etiquetas = 3 , tam_col = 4
 for(i=0;i<etiquetas;i++){ //for lento que recoore filas 
   for(j=0;j<tam_col;j++){ //for lento que recorre columnas 
     centroides[i][j]=0; //valores de los centroides en cero 
    }
  }
   Serial.println("CENTROIDES");
   for(l=0;l<etiquetas;l++){ //etiquetas = 3 es el valor de filas donde se guardaran los promedios para el calculo de centroides 
     for(i=0;i<tam_col-1;i++){
       for(j=(40*l);j<40*(l+1);j++){ //recorre los 40 primeros para sacar el valor de los etiqueta 1  
          centroid=centroid+matriz[j][i];
        }
          centroides[l][i]=centroid/40; //obtener promedio de los valores con etiqueta 1 
          Serial.print(centroides[l][i],4); //valor promedio de centroides l=filas = 3 debido al numero de etiquetas, i=columnas 4 de acuerdo a etiqueta 
          Serial.print(','); 
          centroid=0;
      }
          Serial.print("  Etiqueta "); Serial.print(l+1); // identificativo de etiqueta en la fila de datos centrode 
          Serial.println(' ');
          
   }
   for(l=0;l<etiquetas;l++){
   //j recorre filas , i recorre columnas 
   for(j=0;j<tam_fil;j++){ //se recorre todas las filas 
    for(i=0;i<tam_col-1;i++){ //se recoorre de columna en columna, -1 porque el ultimo es la etiqueta 
      sumatoriapot=sumatoriapot+pow(matriz[j][i]-centroides[l][i],2); //suma de potencias 
      }
      raiz_s=sqrt(sumatoriapot);
      matriz_raices[tam_fil][l]=raiz_s; //datos se guardan en matriz de j filas y l columnas, en este caso 3 
    }}
    for(j=0;j<=tam_fil;j++){ //recorrido comparativo entre valores de matriz_raices 
    if(matriz_raices[j][1]< matriz_raices[j][l+1] && matriz_raices[j][1]<matriz_raices[j][l+2]){ //comparacion entre valores raices de potencia 
      matriz_predic[j][1]=1;
    }else if(matriz_raices[j][1+1]<matriz_raices[j][l] && matriz_raices[j][1+1]<matriz_raices[j][l+2]){
         matriz_predic[j][1]=2;
        }else if(matriz_raices[j][1+2]<matriz_raices[j][l] && matriz_raices[j][1+2]<matriz_raices[j][l+1]){
           matriz_predic[j][1]=3;
        }
      }
   for(j=0;j<=tam_fil;j++){ //for recorre filas 
    if(matriz_predic[j][1]== respuesta ){
      Serial.print("Dato "); Serial.print(j); Serial.print("-");Serial.println("D");
      }else{
        Serial.print("Dato "); Serial.print(j);Serial.print("-"); Serial.println("S"); //va al source 
        }
    }
   Serial.println(' '); // espacio para siguiente impresion de datos
}
     
