import controlP5.*;
import processing.serial.*;
import meter.*;
Serial puerto;
ControlP5 cp5;//constructor 
PImage fondo1;
PFont f,aut; //fuente
int i=0;
float valor,valor1,valor2,valor3,valor4,valor5,valor6;
String dato;
Table table;
Meter m;
int value;
void setup(){
background(255);
size(1000, 700);

//crear tabla paraguardar datos
table = new Table();
  table.addColumn("HUM");
  table.addColumn("TEM");
  table.addColumn("NOX");
  table.addColumn("CO");
  table.addColumn("UV");
  table.addColumn("LABEL");
//fondo
fondo1=loadImage("fondo1.jpg");
fondo1.resize(1000, 700);
image(fondo1,0,0);

//medidor 
m=new Meter(this,50,160);
m.setMeterWidth(350);
m.setTitle("Estado del clima Puro vs Contaminado");
//String[] scaleLabels = {"10","20", "30", "40", "50", "60", "70", "80", "90","100"};//escaa
//m.setScaleLabels(scaleLabels);
m.setTitleFontSize(15);
m.setTitleFontName("Times new Roman bold");
m.setDisplayDigitalMeterValue(true);
//texto titulo
f = createFont("Impact",26,true);
textFont(f,30);
fill(0);
text("SISTEMA DE CONTROL DE CALIDAD DEL AIRE",230,40);

//autores
aut=createFont("Garamond",26,true);
textFont(aut,15);
fill(0);
text("Autores: Cauja María José, Chandi Armando, Nazate Marisol, Valencia Fernando",240,670);
text("7mo CIERCOM",420,690);

//Botones
cp5 = new ControlP5(this);
  cp5.addButton("CONECTAR")
    .setPosition(375, 580)//posicion
    .setSize(100, 50) //tamaño
    .setCaptionLabel("DESCONECTADO")// cambiar el nombre del boton
    .setColorBackground(color(200, 0, 0))
    ;
  cp5.addButton("GUARDAR")
    .setPosition(500, 580)//posicion
    .setSize(100, 50) //tamaño
    .setCaptionLabel("GUARDAR")// cambiar el nombre del boton
    .setColorBackground(color(0, 200, 0))
    ; 
//indicadores
  cp5.addSlider("HUM")
    .setPosition(450, 150)//elegir posicion
    .setSize(500, 25) //elegir tamaño
    .setRange(0, 100) //rango 
    .setValue(0)
    .setColorActive(color(0, 26, 255  ))
    .setColorBackground(color(0, 255, 0))
    .setColorForeground(color(0, 26, 255  ))    
    ;

  cp5.addSlider("TEM")
    .setPosition(450, 200)//elegir posicion
    .setSize(500,25) //elegir tamaño
    .setRange(0, 100) //rango
    .setValue(0)
    .setColorActive(color(200, 0, 0))
    .setColorBackground(color(236, 112, 99))
    .setColorForeground(color(200, 0, 0))
    ;
  cp5.addSlider("CO")
    .setPosition(450, 250)//elegir posicion
    .setSize(500, 25) //elegir tamaño
    .setRange(0, 100) //%
    .setValue(0)
    //.setColorActive(color(44, 62, 80))
    //.setColorBackground(color(93, 109, 126))
    .setColorForeground(color(44, 62, 80)) 
    ;
  cp5.addSlider("NOX")
    .setPosition(450, 300)//elegir posicion
    .setSize(500, 25) //elegir tamaño
    .setRange(0, 100) //rango
    .setValue(0)
    .setColorActive(color(97, 106, 107 ))
    .setColorBackground(color(204, 209, 209))
    .setColorForeground(color(97, 106, 107)) 
    ;
  cp5.addSlider("UV")
    .setPosition(450, 350)//elegir posicion
    .setSize(500, 25) //elegir tamaño
    .setRange(0, 15) //rango
    .setValue(0)
    .setColorActive(color(132, 0, 255  ))
    .setColorBackground(color(187, 143, 206 ))
    .setColorForeground(color(132, 0, 255  )) 
    ;
}
void draw(){
  interpretacion();
  m.updateMeter(value*50);
  if(i==1){
  if(puerto.available()>1){
  leer();
  }
  }
}
public void CONECTAR() { //conectar el esp8266
  i=1-i;
  if (i==1) {
    puerto= new Serial(this, "COM5", 115200);
    cp5.getController("CONECTAR").setCaptionLabel("CONECTADO");
    cp5.getController("CONECTAR").setColorBackground(color(0, 200, 0));//boton activado
    cp5.getController("HUM").setValue(0);
    cp5.getController("TEM").setValue(0);
    cp5.getController("NOX").setValue(0);
    cp5.getController("CO").setValue(0);
    cp5.getController("UV").setValue(0);


  } else {
    puerto.stop();
    cp5.getController("CONECTAR").setCaptionLabel("DESCONECTADO");
    cp5.getController("CONECTAR").setColorBackground(color(200, 0, 0));
  }
}
//public void GUARDAR() {  //guardar datos de lectura en un archivo .csv
//  cp5.getController("GUARDAR").setColorBackground(color(0,200,0));
//TableRow newRow = table.addRow();
//  for (int i=0; i<10; i++ ) {
//    newRow.setInt("HUM", valor1);
//    newRow.setInt("TEM", valor2);
//    newRow.setInt("NOX", valor3);
//    newRow.setInt("CO", valor4);
//    newRow.setInt("UV", valor5);
//    newRow.setInt("LABEL", valor6);
//    saveTable(table, "values/lectura.csv");
//  }
//}
void leer(){
if(puerto.available()>0){
String trama=puerto.readString();
println(trama);
String valores[]=split(trama,',');
if(valores.length<=6){
valor1=float(valores[0]);
println(valor1);
valor2=float(valores[1]);
valor3=float(valores[2]);
valor4=float(valores[3]);
valor5=float(valores[4]);
     //humedad
    cp5.getController("HUM").setValue(valor1); 
    if(valor1>0 && valor1<100){
      cp5.getController("HUM").setColorForeground(color(220)); }
    //temperatura
    cp5.getController("TEM").setValue(valor2);
    if(valor2>0 && valor2<100){
      cp5.getController("TEM").setColorForeground(color(220));}
    //CO
    cp5.getController("CO").setValue(valor3);
    if(valor3>0 && valor3<100){
      cp5.getController("CO").setColorForeground(color(220));}
    //NOX
    cp5.getController("NOX").setValue(valor4);
    if(valor4>0 && valor4<100){
      cp5.getController("NOX").setColorForeground(color(220));}
    //UV
     cp5.getController("UV").setValue(valor5);
    if(valor5>0 && valor5<100){
      cp5.getController("UV").setColorForeground(color(220));}

  }
}}
void interpretacion(){
  if(valor3>50 && valor3<80 && valor4>50 && valor4<80){
  value=3;//parcialmente contaminado
  }else if (valor3>80 && valor4>80){
  value=4;//contaminado
  }else{
  value=1; //aire puro
  }
}
