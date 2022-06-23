// C++ code
//
#include<LiquidCrystal.h>
#include<Servo.h>

#define BASE_MILI_SEGUNDOS 1000 

LiquidCrystal lcd(2, 3, 4 ,5 ,6 ,7);

void aumentoHoras (int bot);
int aumentoMinutos (int bot);
int aumentoSegundos (int bot);
int segundos =54;
int minutos =59;
int horas =23;

bool botonHor (int bot);
bool botonMin (int bot);
bool botonSeg (int bot);
int seg (int s);


Servo hora;
Servo minuto;
Servo segundo;


void setup()
{
  pinMode (13, INPUT);
  pinMode (12, INPUT);
  pinMode (8, INPUT);
  
  hora.attach (11);
  minuto.attach (10);
  segundo.attach (9);
  
  Serial.begin(9600);
  
  lcd.begin(16,2);
  
  
}

  unsigned long millisAntes =0;


void loop()
{
  hora.write (0);
  minuto.write (0);
  segundo.write (0);
      
  unsigned long millisAhora = millis();
  
  // los botones se conectan a las entradas analogicas para
  //  que sea mas vicible y prolijo el circuito
  int botonSegundos = digitalRead (A2);
  int botonMinutos = digitalRead (A1);
  int botonHoras = digitalRead (A0);
  // se condicionan los servomotores de 180° a 60min o 24h
  int servoSeg = map (segundos, 0,59,0,180);
  int servoMin = map (minutos, 0,59,0,180);
  int servoHor = map (horas, 0,23,0,180);
  int valorA0 = analogRead(A0);
  
  
  	
  	segundo.write(servoSeg);
  	minuto.write (servoMin);
  	hora.write (servoHor);
  			
  
  lcd.setCursor (4,0);  // inicio en 1ra linea y celda 4 (5ta)
  lcd.print("Horario");
  
  if (millisAhora - millisAntes >= 1000) {
          
    lcd.setCursor (4,1);  // imprime en 2da linea y celda 4 (5ta)
    segundos++;
      
   if(segundos >59){
    minutos++;
    segundos =0;
  }
   
   if(minutos >59){
    horas++;
    minutos =0;
  }
    
  if(horas >23){
    horas =0; 
  }
      
  if(horas <10){
    lcd.print ("0");
    lcd.print (horas);
	lcd.print (":");
  }
  else{
    lcd.print (horas);
	lcd.print (":");
  }
  if(minutos <10){
    lcd.print ("0");
    lcd.print (minutos);
 	lcd.print (":");
  }
  else{
    lcd.print (minutos);
 	lcd.print (":");
  } 
    
  if(segundos <10){
    lcd.print ("0");
	lcd.print (segundos);
  }
  else {
    	lcd.print (segundos);
  }
       
        millisAntes = millisAhora;
  }
  
  // suma los pulsadores horas-minutos-segundos
  horas = horas + botonHor (botonHoras);
  minutos = minutos + botonMin (botonMinutos);
  segundos = segundos + botonSeg (botonSegundos);
  
      
    delay (150); // para Tinker
	
  Serial.print (digitalRead(A0));
  Serial.print (" / ");
  Serial.print (digitalRead(A1));
  Serial.print (" / ");
  Serial.println (digitalRead(A2));


}

// Funcion que Suma boton minutos

bool botonMin (int bot) {
  int res;
  
  if (bot) {
   res++;
  	return res;
  }
}
// Funcion que Suma boton horas
bool botonHor (int bot) {
  int res;
  
  if (bot) {
   res++;
  	return res;
  }
}

// Funcion que Suma boton segundos
bool botonSeg (int bot) {
  int res;
  
  if (bot) {
   res++;
  	return res;
  }
}





