//La parte 1 y 2 fue hecha con Ivo Barinstein y Agustin Landeira.
// PARTE 3
// integrante: IARA ZOE PASQUARIO CRUZ
//Al ser mi numero de DNI: 45042732 y terminar en 2, se le agrega una FOTORRESISTENCIA.
//Explicación del código:

//Se definen los pines para los segmentos del display y los botones
# define A 12
# define B 13
# define C 7
# define D 8
# define E 9
# define F 11
# define G 10

//Se definen los leds
# define LED_1 6
# define LED_2 2
# define TEMPERATURA A0

//Luego definimos las constantes para los segmentos y botones
//(incluyendo el tiempo de visualización de cada número)
# define SUBE 4
# define BAJA 3
# define SWITCH 5
# define UNIDAD A4
# define DECENA A5
# define APAGADOS 0
# define TIMEDISPLAYON 10

//Aqui se declaran las variables que se van a usar:
//countdigit: almacena el número que se muestra en el display.
//sube, baja y reset:  leer el estado de los botones.
int countdigit = 0;
int sube = 1;
int subprevia = 1;
int baja = 1;
int bajaprevia = 1;
int reset = 1;
int resetprevia = 1;
int interruptor = 1;
int switch_previa = 1;
bool flagMostrar = true;
//int leerTemperatura = 0;

int leerLuminosidad = 0;
//En la función setup, se configuran los pines de entrada y salida.
// Luego se inicializan los digitos UNIDAD y DECENA como apagados,y se
//muestra el número "0" en la pantalla al comienzo.
void setup()
{
    pinMode(3, INPUT_PULLUP);
    pinMode(4, INPUT_PULLUP);
  	pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(13, OUTPUT);
    pinMode(LED_1, OUTPUT);
    pinMode(LED_2, OUTPUT);
    pinMode(UNIDAD, OUTPUT);
    pinMode(DECENA, OUTPUT);
    digitalWrite(UNIDAD,0);
    digitalWrite(DECENA,0);
    printDigit(0);

    Serial.begin(9600);
}

//En la función loop, se lee si se presionó uno de los botones:
void loop()
{
   int pressed = keypress();
    interruptor = digitalRead(SWITCH);
    leerLuminosidad = analogRead(TEMPERATURA);

    calcularLuminosidad(leerLuminosidad);

    if (pressed == SUBE && interruptor == 1) {
        if (switch_previa == 0) {
            switch_previa = 1;
            countdigit = 0;
        }

        flagMostrar = true;
        Serial.println("Aumentar");
        countdigit++;

        if (countdigit > 99) {
            countdigit = 0;
        }
    } else if (pressed == BAJA && interruptor == 1) {
        if (switch_previa == 0) {
            switch_previa = 1;
            countdigit = 0;
        }
        flagMostrar = true;
        Serial.println("Restar");
        countdigit--;

        if (countdigit < 0) {
            countdigit = 99;
        }
        switch_previa = 1;
    }

    if (pressed == SUBE && interruptor == 0) {
        if (switch_previa == 1) {
            switch_previa = 0;
            countdigit = 0;
            flagMostrar = false;
        }

        if (switch_previa == 0) {
            countdigit++;
        }

        if (esPrimo(countdigit) == 1) {
            flagMostrar = true;
            Serial.println("\nEs primo");
        } else {
            Serial.println("\nNo es primo");
            flagMostrar = false;
        }
    } else if (pressed == BAJA && interruptor == 0) {
        if (switch_previa == 1) {
            switch_previa = 0;
            countdigit = 0;
            flagMostrar = false;
        }

        if (switch_previa == 0) {
            countdigit--;
        }

        if (esPrimo(countdigit) == 1) {
            flagMostrar = true;
            Serial.println("\nEs primo");
        } else {
            Serial.println("\nNo es primo");
            flagMostrar = false;
        }
    }

    if (flagMostrar) {
        printCount(countdigit);
        delay(TIMEDISPLAYON);
    } else {
        apagar();
        delay(TIMEDISPLAYON);
    }
}

int keypress() {
    sube = digitalRead(SUBE);
    baja = digitalRead(BAJA);

    if (sube == 1) {
        subprevia = 1;
    }
    if (baja == 1) {
        bajaprevia = 1;
    }

    if (sube == 0 && sube != subprevia) {
        subprevia = sube;
        return SUBE;
    }

    if (baja == 0 && baja != bajaprevia) {
        bajaprevia = baja;
        return BAJA;
    }
    return 0;
}
 


//Luego se muestra el número actual en la pantalla usando
//la función printCounty, introduciendose un delay antes de mostrar el número siguiente.
void printCount(int count)
{
    prendeDigito(APAGADOS); // apago los dos
    printDigit(count/10);
    prendeDigito(DECENA);
    prendeDigito(APAGADOS);
    printDigit(count - 10*((int)count/10));
    prendeDigito(UNIDAD);


}

//La función prendeDigito enciende uno de los dígitos
//del display (UNIDAD o DECENA) y apaga el otro
void prendeDigito(int digito)
{

    if (digito == UNIDAD)
    {
        digitalWrite(UNIDAD,LOW); // pongo el unidad en 0(enciende)
        digitalWrite(DECENA,HIGH);// pongo el comun en 1(no enciende)
        delay(TIMEDISPLAYON);

    }
    else if (digito == DECENA)
    {

        digitalWrite(DECENA,LOW);
        digitalWrite(UNIDAD,HIGH);
        delay(TIMEDISPLAYON);
    }
    else
    {
        digitalWrite(DECENA,HIGH); // no prende ninguno de los dos
        digitalWrite(UNIDAD,HIGH);
    }

}

//En la funcion printDigit se definen los patrones de
//segmentos para cada dígito del 0 al 9 y se encienden  los
// segmentos del display según el dígito que se quiera mostrar.

void printDigit(int digit)
{
    apagar();
    switch(digit)
    {

    case 0:
        digitalWrite(A, HIGH);
        digitalWrite(B, HIGH);
        digitalWrite(C, HIGH);
        digitalWrite(D, HIGH);
        digitalWrite(E, HIGH);
        digitalWrite(F, HIGH);

        break;
    case 1:
        digitalWrite(B, HIGH);
        digitalWrite(C, HIGH);
        break;

    case 2:
        digitalWrite(A, HIGH);
        digitalWrite(B, HIGH);
        digitalWrite(D, HIGH);
        digitalWrite(E, HIGH);
        digitalWrite(G, HIGH);
        break;
        break;

    case 3:
        digitalWrite(A, HIGH);
        digitalWrite(B, HIGH);
        digitalWrite(C, HIGH);
        digitalWrite(D, HIGH);
        digitalWrite(G, HIGH);
        break;

    case 4:
        digitalWrite(B,HIGH);
        digitalWrite(C,HIGH);
        digitalWrite(F,HIGH);
        digitalWrite(G,HIGH);
        break;

    case 5:
        digitalWrite(A, HIGH);
        digitalWrite(C, HIGH);
        digitalWrite(D, HIGH);
        digitalWrite(F, HIGH);
        digitalWrite(G, HIGH);
        break;

    case 6:
        digitalWrite(C, HIGH);
        digitalWrite(D, HIGH);
        digitalWrite(E, HIGH);
        digitalWrite(F, HIGH);
        digitalWrite(G, HIGH);
        break;

    case 7:
        digitalWrite(A, HIGH);
        digitalWrite(B, HIGH);
        digitalWrite(C, HIGH);
        break;

    case 8:
        digitalWrite(A, HIGH);
        digitalWrite(B, HIGH);
        digitalWrite(C, HIGH);
        digitalWrite(D, HIGH);
        digitalWrite(E, HIGH);
        digitalWrite(F, HIGH);
        digitalWrite(G, HIGH);
        break;

    case 9:
        digitalWrite(A, HIGH);
        digitalWrite(B, HIGH);
        digitalWrite(C, HIGH);
        digitalWrite(D, HIGH);

        digitalWrite(F, HIGH);
        digitalWrite(G, HIGH);
        break;


        break;
    }
}
//La función apagarse utiliza para apagar todos los segmentos
//antes de mostrar un nuevo dígito en la pantalla
void apagar()
{

    digitalWrite(A,LOW);
    digitalWrite(B,LOW);
    digitalWrite(C,LOW);
    digitalWrite(D,LOW);
    digitalWrite(E,LOW);
    digitalWrite(F,LOW);
    digitalWrite(G,LOW);

}

int esPrimo(int numero)
{
    int retorno = 1;
    /*
    El número 4 es un caso especial, pues al dividirlo entre
    2 el resultado es 2, y el ciclo nunca se cumple, indicando que
    el 4 SÍ es primo, pero realmente NO lo es, así que si el número es 4
    inmediatamente indicamos que no es primo (regresando 0)
    Nota: solo es para el 4, los demás funcionan bien
    */
    if (numero == 0 || numero == 1 || numero == 4)
    {
        retorno = 0;
    }

    for (int x = 2; x < numero / 2; x++)
    {
        // Si es divisible por cualquiera de estos números, no
        // es primo
        if (numero % x == 0)
        {
            retorno = 0;
        }
    }
    // Si no se pudo dividir por ninguno de los de arriba, sí es primo
    return retorno;
}
//SE COMENTO LA FUNCION DE CALCULAR TEMPERATURA, AGREGADA EN LA PARTE 2.

//La función calcularTemperaturacontrola los LED según la temperatura 
//leída y ajusta los LED_1 y LED_2 según el valor de la temperatura.
/*void calcularTemperatura(int temperaturaLeida)
{
	//Si es menor a 20 grados celcius
    if(temperaturaLeida < 20)
    {
      //se prende el led 1
        digitalWrite(LED_1,HIGH);
      // y se apaga el led 2
        digitalWrite(LED_2,LOW);
    }
    else //sino es menor a 20 grados
    {
      //se prende el led 2
        digitalWrite(LED_2,HIGH);
      //y se apaga el led 1
        digitalWrite(LED_1,LOW);
    }
}*/

//Cree una funcion que mide el umbral y valor de luminosidad.

void calcularLuminosidad(int valorLuminosidad)
{
  //Se agrego el valor del umbral ( umbralLuminoso) en la función 
  // para que se defina un nivel de referencia que determina cuando se deben encender los  LED1 y LED2
  //en función de la lectura del sensor de luminosidad (que es valorLuminosidad)
  
    // Define un umbral de luminosidad en este caso en 1000
    int umbralLuminoso = 1000;  
	
  //Se verifica si el valor del sensor de luminosidad es menor que el umbral
  //Si esta condición es verdadera, significa que la luminosidad es baja (led azul) y se enciende el LED_1.
    if (valorLuminosidad < umbralLuminoso)
    {
        digitalWrite(LED_1, HIGH);
        digitalWrite(LED_2, LOW);
    }
    else //sino se enciende el led rojo, ya que la luminosidad es alta (LED2)
    {
        digitalWrite(LED_1, LOW);
        digitalWrite(LED_2, HIGH);
    }
}

