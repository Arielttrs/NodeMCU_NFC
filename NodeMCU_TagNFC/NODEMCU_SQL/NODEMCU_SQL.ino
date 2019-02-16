/*
 Name:		NODEMCU_SQL.ino
 Created:	16/02/2019 3:31:40
 Author:	Ariel
*/


/* Comunicación Serial entre ATmega328 y NodeMCU V1.0:
*
*  - Interpretación del UID
*  - Comunicación con base de datos (Post y Get).
*  - Envio de respuestas al Atmega328
*/


/*
*
*  COMNUNICACÓN SERIAL ENTRE ARDUINO UNO Y NODE MCU
*  - Se envia una cadeda de 4 bytes correspondiente
*    al UID de un Tag NFC.
*
*   ¡RECEPTOR!
*  Fecha: 27/11/2018
*/

// Copia del Objeto Serial en variable adecuada al 
// dispositivo con el que se comunica. 
HardwareSerial &Atmega = Serial;   // Puerto Serial_1

								   /*
								   //Puerto Serial Virtual:
								   #include<SoftwareSerial.h>         // Puerto serie virtual
								   SoftwareSerial MCU(D6, D7);        // Rx || Tx.
								   */

								   // Configuracioón inicial: 
void setup()
{
	// inicial puerto serial
	Atmega.begin(38400);           // Comunicaciones
    Serial1.begin(9600);            // Debugg.
								   //Esperar un tiempo para reibir
	delay(100);
}

/*Recibir UID*/
void UID()
{
	Serial.flush();
	String uid = "";   // Guarda el UID
	if (Atmega.available())
	{
		char nul = Atmega.read();
		while (nul != '\n')
		{uid = uid + nul;
		 nul = Atmega.read();}
	}
	else
	{return;}
}


// Programa:
void loop()
{
	/*Serial.flush();
	// String recibido:
	String dato = "";

	// Leer el buffer serial
	if (Atmega.available())
	{
	// Detectar fin de la linea:
	char fin = Atmega.read();
	while (fin != '\n')
	{
	dato = dato + fin;
	fin = Atmega.read();
	}
	}

	else
	{
	return;
	}

	//delay(500);
	// imprimir mensaje recibido:

	Serial.print("\nRecibido: "); Serial.println(String(dato));
	Serial.flush();
	delay(500);*/
}

