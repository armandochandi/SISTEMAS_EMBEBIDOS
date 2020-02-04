/*
        UNIVERSIDAD TÉCNICA DEL NORTE
              FICA-CIERCOM
            SISTEMAS EMBEBIDOS
 Integrantes:
 Cauja Maria José
 Chandi Bryan
 Nazate Marisol
 Valencia Fernando 
 
Realizar una interfaz que permita presentar un juego de la anterior consola ATARI. Para ello, su
palanca para dar movimiento al juego debe ser realizada por un arduino, botones y/o sensores. En
clases se realizara una exposicion del mismo.

*/
import ddf.minim.*; //incorporar sonido 
import processing.serial.*; //control para comunicacion serial
Serial myPort;
PImage car1;
PImage pista01;
PImage pista02;
PImage bandera;
PImage exp;
PImage linea;
int y_linea=600;
int car=0;
int score=0;
int obstaculos=3; //el primer nivel empieza con 3 obstaculos 
int x=0;//mover carro en x
int y=0;//mover carro en y 
boolean entrada=false;
int val;
int randx,randy;
Minim sonido;//archivo de sonido 
AudioPlayer play1;
void setup(){
size(600,600);
sonido=new Minim(this);
play1=sonido.loadFile("sonido.mp3");
background(255);
myPort=new Serial(this,"COM3",9600);
myPort.bufferUntil('\n');
exp=loadImage("exp.png");
exp.resize(50,70);
car1=loadImage("car1.png");
car1.resize(50,70);
pista01=loadImage("pista01.jpg");
pista01.resize(100,200);
pista02=loadImage("pista02.jpg");
pista02.resize(100,200);
bandera=loadImage("bandera.jpg");
bandera.resize(120,120);

delay(500);
}
void draw(){
//pistas
image(pista01,0,400);
image(pista01,0,200);
image(pista01,0,0);

image(pista02,300,400);
image(pista02,300,200);
image(pista02,300,0);

image(bandera,440,100);
//semaforo
fill(128,128,128);
rect(480,255,50,125);
//rojo
fill(#8B0000);
ellipse(505,280,30,30);//rojo apagado
fill(#9B870C);
ellipse(505,315,30,30);//amarillo apagado
fill(0,255,0);
ellipse(505,350,30,30);//verde


//recorrido del carro hacia adelante 
if(y_linea>0){ 
noStroke();
fill(255);
rect(170+x-1,y_linea-1,50,70);
y_linea=y_linea-1; //velocidad va aumentando 1
image(car1,170+x,y_linea);
}else{
y_linea=600;
fill(0);
obstaculos();
noStroke();
fill(255);
rect(100,0,200,70);
}
//movimiento del carro hacia derecha e izquierda
if(myPort.available()>0){
String valor= myPort.readStringUntil('\n');
if(valor!=null){
val=int(trim(valor));//valor entero de la entrada analogica 
}
println(val);
if(val==0){ //mover a la izquierda 
noStroke();
fill(255);
rect(170+x-1,y_linea-1,50,70); //dibuja un rectangulo blanco donde antes estaba el carro 
x=x-3;
image(car1,170+x,y_linea);
}else if(val==1){ //mover a la derecha 
  noStroke();
fill(255);
rect(170+x-1,y_linea-1,50,70);
x=x+3;
image(car1,170+x,y_linea);
}
play1.play();
}

}
void obstaculos(){
stroke(0);
strokeWeight(4);
randx=int (random(105,280));
randy=int (random(70,450));
rect(randx,randy,20,20);
}
