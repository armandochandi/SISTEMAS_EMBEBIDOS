//KERNEL DENSITY ESTIMATION
int data[449]={374,550,547,535,323,361,499,540,323,323,323,324,324,324,324,535,462,324,472,526,432,494,324,324,324,326,324,324,324,324,324,524,369,521,323,323,369,413,452,324,427,446,456,469,506,414,1185,1418,1124,1061,1228,868,452,727,733,366,401,346,336,334,336,344,341,449,738,599,499,339,351,572,908,735,409,329,329,692,333,344,349,379,808,544,770,830,579,404,539,1105,552,1190,376,361,413,411,383,366,855,1027,346,629,346,803,968,334,680,424,329,329,329,329,329,328,632,627,527,324,324,605,602,592,324,324,324,324,324,324,324,323,323,579,527,580,384,323,369,572,441,442,324,376,324,323,324,323,333,323,323,323,324,324,323,323,323,323,323,323,326,565,391,403,403,394,672,376,371,364,359,353,351,348,346,348,348,348,346,554,775,813,521,522,507,516,506,476,451,1122,439,426,446,442,427,1242,670,391,381,374,1160,590,359,354,1031,349,348,346,346,344,627,344,663,339,341,339,339,336,336,793,379,466,334,334,334,534,334,333,735,333,333,333,333,333,333,331,331,331,692,331,331,436,331,331,434,331,331,331,331,474,331,331,331,329,331,331,331,331,620,329,329,329,643,643,329,329,329,329,396,329,329,329,329,625,329,329,328,619,328,328,328,328,615,328,328,328,328,328,329,328,328,328,328,562,328,328,328,328,328,524,328,409,328,326,446,328,328,459,328,461,328,331,356,331,331,331,329,329,329,353,349,386,831,341,336,959,384,501,376,369,893,363,359,894,354,351,848,348,346,344,788,640,336,336,334,336,449,333,333,333,331,484,329,329,329,329,431,329,329,328,647,394,326,324,634,324,414,324,540,324,587,324,324,324,324,379,324,324,324,324,527,324,324,324,607,459,324,324,469,324,324,324,323,323,323,323,572,321,462,321,321,323,323,584,584,346,346,323,323,506,323,323,323,323,321,323,323,321,575,534,575,574,323,575,323,323,323,570,344,323,323,323,452,569,323,323,321,321,319,567,321,321,341,321,393,321,321,393,373,343,321,321,321};

int d =(sizeof(data)/sizeof(data[0]));//lingitud del vector de datos 
float datosn[449]; //vector para guardar los nuevos
float h=0.05;//ancho de banda, es el promedio de los valores, es decir el valor ideal esperado en la toma de datos //parametro de suavizado 
float a; 
int i=0;
float f=1/(d*h);
void setup(){
 Serial.begin(115200);
}
void loop(){
delay(1500);
float a=f*h;
for(;i<d;i++){ //sumatoria de datos
datosn[i]=a*((data[0]-data[i])/h);
Serial.print(data[i]);
Serial.print(' ');
Serial.println(datosn[i]);
}
}
