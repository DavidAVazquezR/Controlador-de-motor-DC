#include <Keypad.h>
#include <LiquidCrystal.h>

const int buttonPin1;    
const int buttonPin2;
const int buttonPin3; 
const int buttonPin4;  
const int IN3 =11;
const int IN4 = 12;
const int motorPin = 10;    
char sentidoGiro; 
char tecla;
char valor1[1];
char valor3[3];
char valor4[4];
char valor5[5];
char pant;
int Tipo=1;
int cont;
int setState;

boolean Acele;
boolean vUp;  
boolean vDown;         
boolean buttonState1;            
boolean lastbuttonState1; 
boolean buttonState2;            
boolean lastbuttonState2;   
boolean buttonState3;           
boolean lastbuttonState3;  
boolean buttonState4;           
boolean lastbuttonState4;    
boolean motorState = LOW;    
boolean GiroMotor = HIGH; 
int reading1;
int reading2;
int reading3;
int reading4;          
float velocidad=0;
float Porcentaje;
float Tension;
float TenMax = 9;
float VelMax=80;
float VelMaxMap;
float VelMin=20;
float VelMinMap;
float Aceleracion =5;
float Desaceleracion;
float tiempo;

int Menu;

unsigned long lastDebounceTime1 = 0;    
unsigned long lastDebounceTime2 = 0;
unsigned long lastDebounceTime3 = 0;  
unsigned long lastDebounceTime4 = 0;
unsigned long debounceDelay = 50;

const int rs = A0, en = A1, d4 = A2, d5 = A3, d6 = A4, d7 = A5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);  

const byte filas = 4; //four rows
const byte columnas = 4; //three columns
char teclas[filas][columnas] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte PinsFilas[filas] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte PinsColumnas[columnas] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad
Keypad teclado = Keypad( makeKeymap(teclas), PinsFilas, PinsColumnas, filas, columnas );


void setup() {
  pinMode(motorPin, OUTPUT);
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);  
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);
  lcd.begin(16, 2);
  lcd.clear();
  Serial.begin(9600);
}

void loop() {
Inicio:

//Lectura de Boton On/Off
VelMaxMap=map(VelMax,0,100,0,255);
VelMinMap=map(VelMin,0,100,0,255);


tecla=teclado.getKey();
char tecla2=teclado.getKey();
if (tecla != NO_KEY){
  Serial.print(tecla);}
/*if (tecla == 'A')
{
  buttonPin1=tecla;
}*/

  
   reading1 = tecla;

if(tecla != NO_KEY){
  if(tecla != 'A'){
  if (reading1 != lastbuttonState1) {
    lastDebounceTime1 = millis();
  }}}

  if ((millis() - lastDebounceTime1) > debounceDelay) {
    if (reading1 != buttonState1) {
      buttonState1 = reading1;
      if (buttonState1 == HIGH) {
        motorState = !motorState;
      }
    }
  }


if (buttonState1 == HIGH && motorState == HIGH){
  
  for (int i=velocidad; i<VelMaxMap; i++)
  {
    velocidad++;
    analogWrite(motorPin,velocidad);
      delay(Aceleracion/0.25);
      Serial.println(velocidad);
    } 
 goto Siguele; 
}

if(buttonState1 == HIGH && motorState == LOW){
  if (Tipo==0){
    digitalWrite(motorPin,motorState);
    }
  else if(Tipo==1)
  {
    for (int i=velocidad ; i>0; i--)
    {
    velocidad--;
    analogWrite(motorPin,velocidad);
      delay(Desaceleracion/0.25);
    Serial.println(velocidad);
    }
   }
}
  // Permite cambiar giro y aumentar/decrementar velocidad si el motor está encendido
  if (motorState == HIGH){  


//setState=HIGH;
//resetState=digitalRead(buttonPin2);
//if(setState == HIGH && velocidad>VelMaxMap)
//{

    //setState=LOW;
      //}
 //else if(resetState==HIGH)
  //{  for (int i=velocidad ; i>0; i--)
  //{
    //velocidad--;
    //analogWrite(motorPin,velocidad);
    //setState=digitalRead(buttonPin1);
    //if(setState == HIGH)
    //{
      //break;
      //}
      //delay(12);
    //Serial.println(velocidad);
    //}
  //}
/*
int incre;
incre= VelMaxMap/255;
  Acele=HIGH;
  if (Acele== HIGH){
 for (int i=velocidad ; i<VelMaxMap; i++)
  {
    velocidad+incre;
    analogWrite(motorPin,velocidad);
    //resetState=digitalRead(buttonPin2);
    //if(resetState == HIGH)
    //{ 
    //  break;
    //  }
      delay(12);
      Serial.println(velocidad);
    }
    Acele=LOW;
  }*/

   //Hace la lectura del botón para el sentido de giro
   Siguele:
   reading2 = tecla;

if(tecla != NO_KEY){
  if(tecla != 'B'){
  if (reading2 != lastbuttonState2) {
    lastDebounceTime2 = millis();
  }}}
  if ((millis() - lastDebounceTime2) > debounceDelay) {
    if (reading2 != buttonState2) {
      buttonState2 = reading2;
      if (buttonState2 == HIGH) {
        GiroMotor = !GiroMotor;
      }
    }
  }

  // Determina el sentido de giro del motor
  if (GiroMotor == HIGH){ 
    Serial.print("Horario   ");
       digitalWrite(IN3,LOW);
       digitalWrite(IN4,HIGH);
    }
        else{
      Serial.print("Antihorario   ");
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
    }
  lastbuttonState2 = reading2;
      
      //Esrcibe el senrtido de giro en los pines de
      digitalWrite(motorPin, motorState);

   //Aumento de velocidad    
     reading3 = tecla;

if(tecla != NO_KEY){
if(tecla != 'C'){
if (reading3 != lastbuttonState3) {
    lastDebounceTime3 = millis();
  }}}

  if ((millis() - lastDebounceTime3) > debounceDelay) {
    if (reading3 != buttonState3) {
      buttonState3 = reading3;
      if (buttonState3 == HIGH && velocidad<VelMaxMap) {
        velocidad=velocidad+17;
      }
    }
  }
  lastbuttonState3 = reading3;

//Secuencia para reduccion de velocidad
  reading4 = tecla;

if(tecla != NO_KEY){
  if(tecla != 'D'){
  if (reading4 != lastbuttonState4) {
    lastDebounceTime4 = millis();
  }}}

  if ((millis() - lastDebounceTime4) > debounceDelay) {
    if (reading4 != buttonState4) {
      buttonState4 = reading4;
      if (buttonState4 == HIGH && velocidad>VelMinMap) {
  velocidad=velocidad-17;
      }
    }
  }

  lastbuttonState4 = reading4;
analogWrite (motorPin,velocidad);
Serial.println(velocidad);
    }



  //Rutina para cuando el motor está apagado
    else{
  digitalWrite(motorPin, motorState);
   reading2 = tecla;

if(tecla != NO_KEY){
  if(tecla != 'B'){
  if (reading2 != lastbuttonState2) {
    lastDebounceTime2 = millis();
  }}}

  if ((millis() - lastDebounceTime2) > debounceDelay) {

    if (reading2 != buttonState2) {
      buttonState2 = reading2;
      if (buttonState2 == HIGH) {
        Menu = !Menu;
      }
    }
  }

  // Determina el sentido de giro del motor
 /* if (Menu == HIGH){ 
    lcd.clear();
    Pantalla1();
    //while (motorState==LOW){}
    }*/
    
    //else{
    //}
  lastbuttonState2 = reading2;
      
      //Esrcibe el senrtido de giro en los pines de
      //digitalWrite(motorPin, motorState);
    }
  lastbuttonState1 = reading1;

  Porcentaje=mapfloat(velocidad,0,255,0,100);
  Tension=mapfloat(Porcentaje,0,100,0,TenMax);

//cindicional para establecer el signo dependiendo el sentido de giro
if(GiroMotor == HIGH){
  sentidoGiro = ' ';}
  else{
      sentidoGiro = '-';}

//Condicional para la pantallas listo
//Si el motor está apagado
if (motorState == LOW){
  //lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("OFF PWR= ");
  if(Tension>=10){
  lcd.setCursor(9,0);
  lcd.print(Tension,2);
  }
  else{lcd.setCursor(9,0);
  lcd.print(" ");
    lcd.setCursor(10,0);
  lcd.print(Tension,2);
    }
  lcd.setCursor(14,0);
  lcd.print(" V");
  lcd.setCursor(0,1);
  lcd.print(" Vel.= ");
  lcd.setCursor(6,1);
  lcd.print(sentidoGiro);
  if(Porcentaje== 100){
  lcd.setCursor(7,1);
  lcd.print(Porcentaje,2);
  }
  else if (Porcentaje<10){
  lcd.setCursor(7,1);
  lcd.print("  ");
  lcd.setCursor(9,1);
  lcd.print(Porcentaje,2);
    }
  else {
  lcd.setCursor(7,1);
  lcd.print(" ");
  lcd.setCursor(8,1);
  lcd.print(Porcentaje,2);
    }
  lcd.setCursor(13,1);
  lcd.print("%");
  }

 //Si el motor está encendido
  else{
    //lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" ON PWR= ");
  if(Tension>=10){
  lcd.setCursor(9,0);
  lcd.print(Tension,2);
  }
  else{lcd.setCursor(9,0);
  lcd.print(" ");
    lcd.setCursor(10,0);
  lcd.print(Tension,2);
    }
  lcd.setCursor(14,0);
  lcd.print(" V");
  lcd.setCursor(0,1);
  lcd.print(" Vel.= ");
  lcd.setCursor(6,1);
  lcd.print(sentidoGiro);
  if(Porcentaje== 100){
  lcd.setCursor(7,1);
  lcd.print(Porcentaje,2);
  }
  else if (Porcentaje<10){
  lcd.setCursor(7,1);
  lcd.print("  ");
  lcd.setCursor(9,1);
  lcd.print(Porcentaje,2);
    }
  else {
  lcd.setCursor(7,1);
  lcd.print(" ");
  lcd.setCursor(8,1);
  lcd.print(Porcentaje,2);
    }
  lcd.setCursor(13,1);
  lcd.print("%");
    } 


 //Inicialización del menú
 
 if(motorState == LOW && Menu == HIGH){
 Men:
 //lcd.clear();
  for (int i=0; i=1;i++){
 lcd.setCursor(0,0);
  lcd.print("      Menu      ");
   lcd.setCursor(0,1);
  lcd.print("1 2 3 4 5 6     ");
  
 //do{
 pant = teclado.getKey(); //se guarda en la variable tecla el caracter de la tecla presionada
 
  
 if (pant != NO_KEY)         //se evalúa si se presionó una tecla
  {
    switch(pant){  

      case 'A':
        Menu=LOW;
        goto Inicio;
      break;
      
      case '1'/*Pantalla1*/:
lcd.clear();
 int i;
 for (i=0; i=1;i++){
   // tecla = teclado.getKey(); //se guarda en la variable tecla el caracter de la tecla presionada
  lcd.setCursor(0,0);
  lcd.print("P1= Alimentacion");
  lcd.setCursor(0,1);
  lcd.print("Tension= ");
  lcd.setCursor(11,1);
  lcd.print(".");
  lcd.setCursor(14,1);
  lcd.print(" V");

  tecla = teclado.getKey(); //se guarda en la variable tecla el caracter de la tecla presionada
 
  
 if (tecla != NO_KEY)         //se evalúa si se presionó una tecla
  {
    if(tecla == 'A'){
    Menu = LOW;
    goto Inicio;
    }
        if(tecla == 'C'){
    Menu = LOW;
    goto Men;
    }
    if(tecla == 'B'  || tecla == 'D' || tecla == '*'|| tecla == '#'){    
      Serial.print("Inserte digito");
      lcd.setCursor(0,0);
      lcd.print("Caracter        ");
      lcd.setCursor(0,1);
      lcd.print("Invalido        ");
      delay(1000);
      cont=-1;
      goto leer;

      }
     
      else{ 
      leer:
    valor4[cont]=tecla;          //se guarda caracter por caracter en el arreglo valor[]
    Serial.println(valor4[cont]);    //se imprime en el puerto serie la tecla presionada

    if(cont<=1){
    lcd.setCursor((9+cont),1);
        lcd.print(valor4[cont]         );
    }
    if(cont>=2){
      lcd.setCursor((10+cont),1);
      lcd.print(valor4[cont]);
      }
    cont=cont+1;              //incrementamos la variable cont
      }
      }
        if(cont==4)          //si ya fueron presionadas 4 teclas se da el valor final a la variable
    {
      
      TenMax=(((valor4[0]-48)*10)+(valor4[1]-48)+((valor4[2]-48)*0.1)+((valor4[3]-48)*0.01));
     if( TenMax>12 ||  TenMax<3){
       lcd.setCursor(0,0);
      lcd.print("Valor           ");
      lcd.setCursor(0,1);
      lcd.print("Invalido        ");
      delay(1000);
      cont=-1;
      goto leer;
      }
      if( TenMax<=12 ||  TenMax>=3){
      //cont=0;  //resetear a 0 la variable cont    
      lcd.setCursor(9,1);
      lcd.print( TenMax);
      delay(1000);
      goto Valido;
      }
    }
 }

    Valido:
    cont=0;
    goto Men;
    break;
 
 case '2':
                                                                                           //Pantalla2();
      lcd.clear();
 for (i=0; i=1;i++){
   // tecla = teclado.getKey(); //se guarda en la variable tecla el caracter de la tecla presionada
  lcd.setCursor(0,0);
  lcd.print("P2= Vel. Maxima ");
  lcd.setCursor(0,1);
  lcd.print("Ajuste= ");
  lcd.setCursor(11,1);
  lcd.print(".");
  lcd.setCursor(14,1);
  lcd.print(" %");

  tecla = teclado.getKey(); //se guarda en la variable tecla el caracter de la tecla presionada
 
  
 if (tecla != NO_KEY)         //se evalúa si se presionó una tecla
  {
    if(tecla == 'A'){
    Menu = LOW;
    goto Inicio;
    }
    if(tecla == 'C'){
    Menu = LOW;
    goto Men;
    }
    if(tecla == 'B' || tecla == 'D' || tecla == '*'|| tecla == '#'){    
      Serial.print("Inserte digito");
      lcd.setCursor(0,0);
      lcd.print("Caracter        ");
      lcd.setCursor(0,1);
      lcd.print("Invalido        ");
      delay(1000);
      cont=-1;
      goto leer;

      }
     
      else{ 
      leer1:
    valor5[cont]=tecla;          //se guarda caracter por caracter en el arreglo valor[]
    Serial.println(valor5[cont]);    //se imprime en el puerto serie la tecla presionada

    if(cont<=2){
    lcd.setCursor((8+cont),1);
        lcd.print(valor5[cont]         );
    }
    if(cont>=3){
      lcd.setCursor((9+cont),1);
      lcd.print(valor5[cont]);
      }
    cont=cont+1;              //incrementamos la variable cont
      }
      }
        if(cont==5)          //si ya fueron presionadas 4 teclas se da el valor final a la variable
    {
      
     VelMax=((valor5[0]-48)*100)+((valor5[1]-48)*10)+(valor5[2]-48)+((valor5[3]-48)*0.1)+((valor5[4]-48)*0.01);
     if(VelMax>100 || VelMax<10){
       lcd.setCursor(0,0);
      lcd.print("Valor           ");
      lcd.setCursor(0,1);
      lcd.print("Invalido        ");
      delay(1000);
      cont=-1;
      goto leer1;
      }
      if(VelMax<=100 || VelMax>=10){
      //cont=0;  //resetear a 0 la variable cont 
      if(VelMax==100){
      lcd.setCursor(8,1);
      lcd.print(VelMax);   
      }
      else {
      lcd.setCursor(8,1);
      lcd.print(" ");
      lcd.setCursor(9,1);
      lcd.print(VelMax);   
      }
      
      delay(1000);
      goto Valido1;
      }
    }
    }


    Valido1:
    cont=0;
    goto Men;
 break;
 
  case '3':                                                                                          //Pantalla3();

  lcd.clear();

 for (i=0; i=1;i++){
   // tecla = teclado.getKey(); //se guarda en la variable tecla el caracter de la tecla presionada
  lcd.setCursor(0,0);
  lcd.print("P3= Vel. Minima ");
  lcd.setCursor(0,1);
  lcd.print("Ajuste=  ");
  lcd.setCursor(11,1);
  lcd.print(".");
  lcd.setCursor(14,1);
  lcd.print(" %");

  tecla = teclado.getKey(); //se guarda en la variable tecla el caracter de la tecla presionada
 
  
 if (tecla != NO_KEY)         //se evalúa si se presionó una tecla
  {
    if(tecla == 'A'){
    Menu = LOW;
    goto Inicio;
    }
    if(tecla == 'C'){
    Menu = LOW;
    goto Men;
    }
    if(tecla == 'B'  || tecla == 'D' || tecla == '*'|| tecla == '#'){    
      Serial.print("Inserte digito");
      lcd.setCursor(0,0);
      lcd.print("Caracter        ");
      lcd.setCursor(0,1);
      lcd.print("Invalido        ");
      delay(1000);
      cont=-1;
      goto leer2;

      }
     
      else{ 
      leer2:
    valor4[cont]=tecla;          //se guarda caracter por caracter en el arreglo valor[]
    Serial.println(valor4[cont]);    //se imprime en el puerto serie la tecla presionada

    if(cont<=1){
    lcd.setCursor((9+cont),1);
        lcd.print(valor4[cont]         );
    }
    if(cont>=2){
      lcd.setCursor((10+cont),1);
      lcd.print(valor4[cont]);
      }
    cont=cont+1;              //incrementamos la variable cont
      }
      }
        if(cont==4)          //si ya fueron presionadas 4 teclas se da el valor final a la variable
    {
      
     VelMin=(((valor4[0]-48)*10)+(valor4[1]-48)+((valor4[2]-48)*0.1)+((valor4[3]-48)*0.01));
     if(VelMin>VelMax || VelMin<0){
       lcd.setCursor(0,0);
      lcd.print("Valor           ");
      lcd.setCursor(0,1);
      lcd.print("Invalido        ");
      delay(1000);
      cont=-1;
      goto leer2;
      }
      if(VelMin<=VelMax || VelMin>=0){
      //cont=0;  //resetear a 0 la variable cont    
      lcd.setCursor(9,1);
      lcd.print(VelMin);
      delay(1000);
      goto Valido2;
      }
    }
 }

    Valido2:
    cont=0;
    goto Men;
  break;

    
   case '4':                                                                                            //Pantalla4();

 lcd.clear();

 for (i=0; i=1;i++){
   // tecla = teclado.getKey(); //se guarda en la variable tecla el caracter de la tecla presionada
  lcd.setCursor(0,0);
  lcd.print("P4= Rampa Acele.");
  lcd.setCursor(0,1);
  lcd.print("Tiempo=   ");
  lcd.setCursor(12,1);
  lcd.print(".");
  lcd.setCursor(14,1);
  lcd.print(" s");

  tecla = teclado.getKey(); //se guarda en la variable tecla el caracter de la tecla presionada
 
  
 if (tecla != NO_KEY)         //se evalúa si se presionó una tecla
  {
    if(tecla == 'A'){
    Menu = LOW;
    goto Inicio;
    }
    if(tecla == 'C'){
    Menu = LOW;
    goto Men;
    }
    if(tecla == 'B' || tecla == 'D' || tecla == '*'|| tecla == '#'){    
      Serial.print("Inserte digito");
      lcd.setCursor(0,0);
      lcd.print("Caracter        ");
      lcd.setCursor(0,1);
      lcd.print("Invalido        ");
      delay(1000);
      cont=-1;
      goto leer3;

      }
     
      else{ 
      leer3:
    valor3[cont]=tecla;          //se guarda caracter por caracter en el arreglo valor[]
    Serial.println(valor3[cont]);    //se imprime en el puerto serie la tecla presionada

    if(cont<=1){
    lcd.setCursor((10+cont),1);
        lcd.print(valor3[cont]         );
    }
    if(cont>=2){
      lcd.setCursor((11+cont),1);
      lcd.print(valor3[cont]);
      }
    cont=cont+1;              //incrementamos la variable cont
      }
      }
        if(cont==3)          //si ya fueron presionadas 4 teclas se da el valor final a la variable
    {
      
     Aceleracion=(((valor3[0]-48)*10)+(valor3[1]-48)+((valor3[2]-48)*0.1));
     if(Aceleracion>30 || Aceleracion<0){
       lcd.setCursor(0,0);
      lcd.print("Valor           ");
      lcd.setCursor(0,1);
      lcd.print("Invalido        ");
      delay(1000);
      cont=-1;
      goto leer3;
      }
      if(Aceleracion<=30 || Aceleracion>=0){
      //cont=0;  //resetear a 0 la variable cont    
      if(Aceleracion >=10){
      lcd.setCursor(10,1);
      lcd.print(Aceleracion,1); 
      }
      else{
      lcd.setCursor(10,1);
      lcd.print(" ");
      lcd.setCursor(11,1);
      lcd.print(Aceleracion,1); 
        }
      delay(1000);
      goto Valido3;
      }
    }
 }

    Valido3:
    cont=0;
    goto Men;                                                                                         
   break;                                                                                                         //Pantalla5();

case '5':

  lcd.clear();

 for (i=0; i=1;i++){
   // tecla = teclado.getKey(); //se guarda en la variable tecla el caracter de la tecla presionada
  lcd.setCursor(0,0);
  lcd.print("P5= Rampa Desac.");
  lcd.setCursor(0,1);
  lcd.print("Tiempo=   ");
  lcd.setCursor(12,1);
  lcd.print(".");
  lcd.setCursor(14,1);
  lcd.print(" s");

  tecla = teclado.getKey(); //se guarda en la variable tecla el caracter de la tecla presionada
 
  
 if (tecla != NO_KEY)         //se evalúa si se presionó una tecla
  {
    if(tecla == 'A'){
    Menu = LOW;
    goto Inicio;
    }
        if(tecla == 'C'){
    Menu = LOW;
    goto Men;
    }
    if( tecla == 'B'  || tecla == 'D' || tecla == '*'|| tecla == '#'){    
      Serial.print("Inserte digito");
      lcd.setCursor(0,0);
      lcd.print("Caracter        ");
      lcd.setCursor(0,1);
      lcd.print("Invalido        ");
      delay(1000);
      cont=-1;
      goto leer4;

      }
     
      else{ 
      leer4:
    valor3[cont]=tecla;          //se guarda caracter por caracter en el arreglo valor[]
    Serial.println(valor3[cont]);    //se imprime en el puerto serie la tecla presionada

    if(cont<=1){
    lcd.setCursor((10+cont),1);
        lcd.print(valor3[cont]         );
    }
    if(cont>=2){
      lcd.setCursor((11+cont),1);
      lcd.print(valor3[cont]);
      }
    cont=cont+1;              //incrementamos la variable cont
      }
      }
        if(cont==3)          //si ya fueron presionadas 4 teclas se da el valor final a la variable
    {
      
     Desaceleracion=(((valor3[0]-48)*10)+(valor3[1]-48)+((valor3[2]-48)*0.1));
     if(Desaceleracion>30 || Desaceleracion<0){
       lcd.setCursor(0,0);
      lcd.print("Valor           ");
      lcd.setCursor(0,1);
      lcd.print("Invalido        ");
      delay(1000);
      cont=-1;
      goto leer4;
      }
      if(Desaceleracion<=30 || Desaceleracion>=0){
      //cont=0;  //resetear a 0 la variable cont    
            if(Desaceleracion >=10){
      lcd.setCursor(10,1);
      lcd.print(Desaceleracion,1); 
      }
      else{
      lcd.setCursor(10,1);
      lcd.print(" ");
      lcd.setCursor(11,1);
      lcd.print(Desaceleracion,1); 
        }
      delay(1000);
      goto Valido4;
      //goto Men;
      }
    }
 }

    Valido4:
    cont=0;
    //Menu = LOW;
    goto Men;
break;


                                                                                                                 //Pantalla6()
case '6':

  lcd.clear();

 for (i=0; i=1;i++){
   // tecla = teclado.getKey(); //se guarda en la variable tecla el caracter de la tecla presionada
  lcd.setCursor(0,0);
  lcd.print("P6= Tipo Freno");
  lcd.setCursor(0,1);
  lcd.print("  ");
    lcd.setCursor(3,1);
  lcd.print("            ");

  tecla = teclado.getKey(); //se guarda en la variable tecla el caracter de la tecla presionada
 
  
 if (tecla != NO_KEY)         //se evalúa si se presionó una tecla
  {
    if(tecla == 'A'){
    Menu = LOW;
    goto Inicio;
    }
    if(tecla == 'C'){
    Menu = LOW;
    goto Men;
    }
    if( tecla == 'B' || tecla == 'D' || tecla == '*'|| tecla == '#' || tecla == '2' || tecla == '3'
    || tecla == '4' || tecla == '5' || tecla == '6' || tecla == '7' || tecla == '8' || tecla == '9'){    
      Serial.print("Inserte digito");
      lcd.setCursor(0,0);
      lcd.print("Caracter        ");
      lcd.setCursor(0,1);
      lcd.print("Invalido        ");
      delay(1000);
      cont=-1;
      goto leer5;
      }
     
      else{ 
      leer5:
    valor1[cont]=tecla;          //se guarda caracter por caracter en el arreglo valor[]
    Serial.println(valor1[cont]);    //se imprime en el puerto serie la tecla presionada

    lcd.setCursor(2,1);
        lcd.print(valor1[cont]         );

    cont=cont+1;              //incrementamos la variable cont
      }
      }
        if(cont==1)          //si ya fueron presionadas 4 teclas se da el valor final a la variable
    {
      
     Tipo=valor1[0]-48;
     if(Tipo == 0){
      lcd.setCursor(2,1);
      lcd.print(Tipo,1);
      lcd.setCursor(3,1);
      lcd.print(" = inercial  ");
      delay(1000);
      goto Valido5;
      }
      if(Tipo ==1){
      lcd.setCursor(2,1);
      lcd.print(Tipo,1);
      lcd.setCursor(3,1);
      lcd.print(" = rampa     ");
      delay(1000);
      goto Valido5;
      }
    }
 }

    Valido5:
    cont=0;
    //Menu = LOW;
    //goto Inicio;
    goto Men;

break;


default:
        lcd.setCursor(0,0);
      lcd.print("Caracter        ");
      lcd.setCursor(0,1);
      lcd.print("Invalido        ");
      delay(1000);
      goto Men;
  break;
    }
  }

}
}
}
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

int Pantalla1(){
lcd.clear();
 int i;
 for (i=0; i=1;i++){
   // tecla = teclado.getKey(); //se guarda en la variable tecla el caracter de la tecla presionada
  lcd.setCursor(0,0);
  lcd.print("P1= Alimentacion");
  lcd.setCursor(0,1);
  lcd.print("Tension= ");
  lcd.setCursor(11,1);
  lcd.print(".");
  lcd.setCursor(14,1);
  lcd.print(" V");

  tecla = teclado.getKey(); //se guarda en la variable tecla el caracter de la tecla presionada
 
  
 if (tecla != NO_KEY)         //se evalúa si se presionó una tecla
  {
    if(tecla == 'A' || tecla == 'B' || tecla == 'C' || tecla == 'D' || tecla == '*'|| tecla == '#'){    
      Serial.print("Inserte digito");
      lcd.setCursor(0,0);
      lcd.print("Caracter        ");
      lcd.setCursor(0,1);
      lcd.print("Invalido        ");
      delay(1000);
      cont=-1;
      goto leer;

      }
     
      else{ 
      leer:
    valor4[cont]=tecla;          //se guarda caracter por caracter en el arreglo valor[]
    Serial.println(valor4[cont]);    //se imprime en el puerto serie la tecla presionada

    if(cont<=1){
    lcd.setCursor((9+cont),1);
        lcd.print(valor4[cont]         );
    }
    if(cont>=2){
      lcd.setCursor((10+cont),1);
      lcd.print(valor4[cont]);
      }
    cont=cont+1;              //incrementamos la variable cont
      }
      }
        if(cont==4)          //si ya fueron presionadas 4 teclas se da el valor final a la variable
    {
      
      TenMax=(((valor4[0]-48)*10)+(valor4[1]-48)+((valor4[2]-48)*0.1)+((valor4[3]-48)*0.01));
     if( TenMax>12 ||  TenMax<3){
       lcd.setCursor(0,0);
      lcd.print("Valor           ");
      lcd.setCursor(0,1);
      lcd.print("Invalido        ");
      delay(1000);
      cont=-1;
      goto leer;
      }
      if( TenMax<=12 ||  TenMax>=3){
      //cont=0;  //resetear a 0 la variable cont    
      lcd.setCursor(9,1);
      lcd.print( TenMax);
      delay(1000);
      goto Valido;
      }
    }
 }

    Valido:
    cont=0;
  }
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

int Pantalla2(){
  lcd.clear();
 int i;
 for (i=0; i=1;i++){
   // tecla = teclado.getKey(); //se guarda en la variable tecla el caracter de la tecla presionada
  lcd.setCursor(0,0);
  lcd.print("P2= Vel. Maxima ");
  lcd.setCursor(0,1);
  lcd.print("Ajuste= ");
  lcd.setCursor(11,1);
  lcd.print(".");
  lcd.setCursor(14,1);
  lcd.print(" %");

  tecla = teclado.getKey(); //se guarda en la variable tecla el caracter de la tecla presionada
 
  
 if (tecla != NO_KEY)         //se evalúa si se presionó una tecla
  {
    if(tecla == 'A' || tecla == 'B' || tecla == 'C' || tecla == 'D' || tecla == '*'|| tecla == '#'){    
      Serial.print("Inserte digito");
      lcd.setCursor(0,0);
      lcd.print("Caracter        ");
      lcd.setCursor(0,1);
      lcd.print("Invalido        ");
      delay(1000);
      cont=-1;
      goto leer;

      }
     
      else{ 
      leer:
    valor5[cont]=tecla;          //se guarda caracter por caracter en el arreglo valor[]
    Serial.println(valor5[cont]);    //se imprime en el puerto serie la tecla presionada

    if(cont<=2){
    lcd.setCursor((8+cont),1);
        lcd.print(valor5[cont]         );
    }
    if(cont>=3){
      lcd.setCursor((9+cont),1);
      lcd.print(valor5[cont]);
      }
    cont=cont+1;              //incrementamos la variable cont
      }
      }
        if(cont==5)          //si ya fueron presionadas 4 teclas se da el valor final a la variable
    {
      
     VelMax=((valor5[0]-48)*100)+((valor5[1]-48)*10)+(valor5[2]-48)+((valor5[3]-48)*0.1)+((valor5[4]-48)*0.01);
     if(VelMax>100 || VelMax<10){
       lcd.setCursor(0,0);
      lcd.print("Valor           ");
      lcd.setCursor(0,1);
      lcd.print("Invalido        ");
      delay(1000);
      cont=-1;
      goto leer;
      }
      if(VelMax<=100 || VelMax>=10){
      //cont=0;  //resetear a 0 la variable cont    
      lcd.setCursor(9,1);
      lcd.print(VelMax);
      delay(1000);
      goto Valido;
      }
    }
 }

    Valido:
    cont=0;
  }
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
  
int Pantalla3(){
  lcd.clear();
 int i;
 for (i=0; i=1;i++){
   // tecla = teclado.getKey(); //se guarda en la variable tecla el caracter de la tecla presionada
  lcd.setCursor(0,0);
  lcd.print("P3= Vel. Minima ");
  lcd.setCursor(0,1);
  lcd.print("Ajuste=  ");
  lcd.setCursor(11,1);
  lcd.print(".");
  lcd.setCursor(14,1);
  lcd.print(" %");

  tecla = teclado.getKey(); //se guarda en la variable tecla el caracter de la tecla presionada
 
  
 if (tecla != NO_KEY)         //se evalúa si se presionó una tecla
  {
    if(tecla == 'A' || tecla == 'B' || tecla == 'C' || tecla == 'D' || tecla == '*'|| tecla == '#'){    
      Serial.print("Inserte digito");
      lcd.setCursor(0,0);
      lcd.print("Caracter        ");
      lcd.setCursor(0,1);
      lcd.print("Invalido        ");
      delay(1000);
      cont=-1;
      goto leer2;

      }
     
      else{ 
      leer2:
    valor4[cont]=tecla;          //se guarda caracter por caracter en el arreglo valor[]
    Serial.println(valor4[cont]);    //se imprime en el puerto serie la tecla presionada

    if(cont<=1){
    lcd.setCursor((9+cont),1);
        lcd.print(valor4[cont]         );
    }
    if(cont>=2){
      lcd.setCursor((10+cont),1);
      lcd.print(valor4[cont]);
      }
    cont=cont+1;              //incrementamos la variable cont
      }
      }
        if(cont==4)          //si ya fueron presionadas 4 teclas se da el valor final a la variable
    {
      
     VelMin=(((valor4[0]-48)*10)+(valor4[1]-48)+((valor4[2]-48)*0.1)+((valor4[3]-48)*0.01));
     if(VelMin>VelMax || VelMin<0){
       lcd.setCursor(0,0);
      lcd.print("Valor           ");
      lcd.setCursor(0,1);
      lcd.print("Invalido        ");
      delay(1000);
      cont=-1;
      goto leer2;
      }
      if(VelMin<=VelMax || VelMin>=0){
      //cont=0;  //resetear a 0 la variable cont    
      lcd.setCursor(9,1);
      lcd.print(VelMin);
      delay(1000);
      goto Valido2;
      }
    }
 }

    Valido2:
    cont=0;
  }
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
  
int Pantalla4(){
  lcd.clear();
 int i;
 for (i=0; i=1;i++){
   // tecla = teclado.getKey(); //se guarda en la variable tecla el caracter de la tecla presionada
  lcd.setCursor(0,0);
  lcd.print("P4= Rampa Acele.");
  lcd.setCursor(0,1);
  lcd.print("Tiempo=   ");
  lcd.setCursor(12,1);
  lcd.print(".");
  lcd.setCursor(14,1);
  lcd.print(" s");

  tecla = teclado.getKey(); //se guarda en la variable tecla el caracter de la tecla presionada
 
  
 if (tecla != NO_KEY)         //se evalúa si se presionó una tecla
  {
    if(tecla == 'A' || tecla == 'B' || tecla == 'C' || tecla == 'D' || tecla == '*'|| tecla == '#'){    
      Serial.print("Inserte digito");
      lcd.setCursor(0,0);
      lcd.print("Caracter        ");
      lcd.setCursor(0,1);
      lcd.print("Invalido        ");
      delay(1000);
      cont=-1;
      goto leer3;

      }
     
      else{ 
      leer3:
    valor3[cont]=tecla;          //se guarda caracter por caracter en el arreglo valor[]
    Serial.println(valor3[cont]);    //se imprime en el puerto serie la tecla presionada

    if(cont<=1){
    lcd.setCursor((10+cont),1);
        lcd.print(valor3[cont]         );
    }
    if(cont>=2){
      lcd.setCursor((11+cont),1);
      lcd.print(valor3[cont]);
      }
    cont=cont+1;              //incrementamos la variable cont
      }
      }
        if(cont==3)          //si ya fueron presionadas 4 teclas se da el valor final a la variable
    {
      
     Aceleracion=(((valor3[0]-48)*10)+(valor3[1]-48)+((valor3[2]-48)*0.1));
     if(Aceleracion>30 || Aceleracion<0){
       lcd.setCursor(0,0);
      lcd.print("Valor           ");
      lcd.setCursor(0,1);
      lcd.print("Invalido        ");
      delay(1000);
      cont=-1;
      goto leer3;
      }
      if(Aceleracion<=30 || Aceleracion>=0){
      //cont=0;  //resetear a 0 la variable cont    
      lcd.setCursor(10,1);
      lcd.print(Aceleracion,1);
      delay(1000);
      goto Valido3;
      }
    }
 }

    Valido3:
    cont=0;
  }
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
  
int Pantalla5(){
  lcd.clear();
 int i;
 for (i=0; i=1;i++){
   // tecla = teclado.getKey(); //se guarda en la variable tecla el caracter de la tecla presionada
  lcd.setCursor(0,0);
  lcd.print("P5= Rampa Desac.");
  lcd.setCursor(0,1);
  lcd.print("Tiempo=   ");
  lcd.setCursor(12,1);
  lcd.print(".");
  lcd.setCursor(14,1);
  lcd.print(" s");

  tecla = teclado.getKey(); //se guarda en la variable tecla el caracter de la tecla presionada
 
  
 if (tecla != NO_KEY)         //se evalúa si se presionó una tecla
  {
    if(tecla == 'A' || tecla == 'B' || tecla == 'C' || tecla == 'D' || tecla == '*'|| tecla == '#'){    
      Serial.print("Inserte digito");
      lcd.setCursor(0,0);
      lcd.print("Caracter        ");
      lcd.setCursor(0,1);
      lcd.print("Invalido        ");
      delay(1000);
      cont=-1;
      goto leer4;

      }
     
      else{ 
      leer4:
    valor3[cont]=tecla;          //se guarda caracter por caracter en el arreglo valor[]
    Serial.println(valor3[cont]);    //se imprime en el puerto serie la tecla presionada

    if(cont<=1){
    lcd.setCursor((10+cont),1);
        lcd.print(valor3[cont]         );
    }
    if(cont>=2){
      lcd.setCursor((11+cont),1);
      lcd.print(valor3[cont]);
      }
    cont=cont+1;              //incrementamos la variable cont
      }
      }
        if(cont==3)          //si ya fueron presionadas 4 teclas se da el valor final a la variable
    {
      
     Desaceleracion=(((valor3[0]-48)*10)+(valor3[1]-48)+((valor3[2]-48)*0.1));
     if(Desaceleracion>30 || Desaceleracion<0){
       lcd.setCursor(0,0);
      lcd.print("Valor           ");
      lcd.setCursor(0,1);
      lcd.print("Invalido        ");
      delay(1000);
      cont=-1;
      goto leer4;
      }
      if(Desaceleracion<=30 || Desaceleracion>=0){
      //cont=0;  //resetear a 0 la variable cont    
      lcd.setCursor(10,1);
      lcd.print(Desaceleracion,1);
      delay(1000);
      goto Valido4;
      }
    }
 }

    Valido4:
    cont=0;
  }
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
    float mapfloat (float x, float in_min, float in_max, float out_min, float out_max){
      return (x - in_min) * (out_max - out_min) / (in_max -in_min) + out_min;
      }
