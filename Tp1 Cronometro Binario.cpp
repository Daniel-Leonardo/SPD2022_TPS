/*
 *	Trabajo Práctico 1: Cronómetro Binario
 *
 *	Al iniciar la simulacion, todos los led deben comenzar apagados, 
 *  cada un seg se va enciendo el led correspondiente.
 *	
 *	Ejemplo: 
 *	El numero 15 (0000001111)
 *	Al pasar al numero 16 (0000010000). 
 *	Los 0 representan los led apagados y los 1 los led encendidos). 
 *      
 *	Al presionarse el boton START, debe iniciar el cronometro.
 *	Al volver presionarlo se pausa la secuencia.
 *  (Como si se hubiese presionado pausa).
 *	Al presionarse el boton RESET, el cronometro vuelve a "Cero" 0
 *
 */

//  Defines
#define BOTON_START 2
#define BOTON_RESET 3
#define PRIMER_LED 4
#define ULTIMO_LED 13
#define BASE_MILI_SEGUNDOS 1000 
#define MAX_SEGUNDOS 1023 

// Funciones
void numeroAbinario (int numero, int numBinario[]);
bool tiempoTranscurrido (unsigned int cicloTiempo);
void chekLED (int numBinario[]);
void numeroAmostrar (int segundos, int numBinario[]);
void resetNumeroBin (int numBinario[]);

void setup () {
    Serial.begin (9600);
    pinMode (2, INPUT); // Boton de Stop/Play
    pinMode (3, INPUT); // Boton de Reset
    pinMode (4, OUTPUT);
    pinMode (5, OUTPUT);
    pinMode (6, OUTPUT);
    pinMode (7, OUTPUT);
    pinMode (8, OUTPUT);
    pinMode (9, OUTPUT);
    pinMode (10, OUTPUT);
    pinMode (11, OUTPUT);
    pinMode (12, OUTPUT);
    pinMode (13, OUTPUT);
  
}

int numBinario [10] ; //= {0,0,0,0,0,0,0,0,0,0};
int botonInicioAntes = 0;
int botonResetAntes = 0;
int stop = 0;
int contadorSeg = 0;
unsigned long millisAntes;

bool enStop = true; //  Flag

void loop () {
  int botonInicio = digitalRead (BOTON_START);
  int botonReset = digitalRead (BOTON_RESET);

  if (botonInicio == 1 && botonInicioAntes == 0) {
  	enStop = !enStop;
    if (enStop == 1) {
      stop = millis () - millisAntes;
    } 
    else {
      millisAntes = millis () - stop;
    }
  }
  
  if (botonReset == 1 && botonResetAntes == 0) {
    contadorSeg = 0;
    resetNumeroBin (numBinario);
    chekLED (numBinario);
    millisAntes = millis ();
  }
   
  if (enStop == 0 && tiempoTranscurrido (BASE_MILI_SEGUNDOS)) {
    contadorSeg++; 
    if (contadorSeg < MAX_SEGUNDOS + 1) {
      numeroAbinario (contadorSeg, numBinario);
      chekLED (numBinario);
      numeroAmostrar (contadorSeg, numBinario); 
    } 
    else
    {
         if (contadorSeg == MAX_SEGUNDOS + 1) {
         resetNumeroBin (numBinario);
         chekLED (numBinario); 
        }  
    }
  }
  
  botonInicioAntes = botonInicio;
  botonResetAntes = botonReset;
   delay (10); // * solo para Tinkercad
}
 

 // Funcion que convierte a binario
void numeroAbinario (int numero, int numBinario[]) { 
  for (int i = 9; i >= 0; i--) {
    if (numero < 1) {
      break;
    }
    numBinario[i] = numero % 2;
    numero = numero / 2;
  }
}

// Funcion para el tiempo transcurrido
bool tiempoTranscurrido (unsigned int cicloTiempo) {
  unsigned long millisAhora = millis ();
  
  if (millisAhora - millisAntes >= cicloTiempo) {
    millisAntes = millisAhora;
  	return true;
  }
  return false;
}

// Funcion de control de leds
void chekLED (int numBinario[]) {
  int contador = 0;
  for (int i = ULTIMO_LED; i >= PRIMER_LED; i--) {
    int estado = numBinario[contador];
    digitalWrite (i, estado);
    contador++;
  }
}

// Numero a mostrar en el monitor
void numeroAmostrar (int segundos, int numBinario[]) {
  Serial.print ("Segundo :");
  Serial.print (segundos);
  Serial.print ("  * Binario :");

  for (int i = 0; i < 10; i++) {
    Serial.print (numBinario[i]);
  }
  Serial.println ("");
}

void resetNumeroBin (int numBinario[]) {
  for (int i = 0; i < 10; i++) {
    numBinario[i] = 0;
  }
}
