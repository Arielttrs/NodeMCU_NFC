/*
 Name:		NODEMCU_SQL.ino
 Created:	16/02/2019 3:31:40
 Author:	Ariel
*/


/* Comunicación Serial entre ATmega328 y NodeMCU V1.0:
*
*  - Interpretación del UID, se envia una cadena de 4 bytes correspondiente
*    al UID de un Tag NFC.
*  - Comunicación con base de datos (Post y Get).
*  - Envio de respuestas al Atmega328
*/


// Copia del Objeto Serial en variable adecuada al 
// dispositivo con el que se comunica. 
HardwareSerial &Atmega = Serial1;  // Puerto Serial_1

								   /*
								   //Puerto Serial Virtual:
								   #include<SoftwareSerial.h>         // Puerto serie virtual
								   SoftwareSerial MCU(D6, D7);        // Rx || Tx.
								   */
// Configuracioón inicial: 
void setup()
{
	// iniciar comunicación serial:
	Atmega.begin(9600);            // Comunicaciones Micro-NodeMCU
    Serial.begin(38400);           // Debugg NodeMCU
	delay(100);			     	   // Esperar un tiempo para reibir
}

/*Recibir UID*/
String uid_in()
{
	Serial.flush();
	String uiid = "";              // Guarda el UID
	if (Atmega.available())
	{
		Serial.println("Mensaje recibido!");
		char fin = Atmega.read();
		while (fin != '\n')
		{uiid = uiid + fin;
		 fin = Atmega.read();}
	}
	else
	{return "0";}
}


// Programa:
void loop()
{
	String UID = uid_in();
	//DEBUGG: 
	Serial.print("UID: \n");
	Serial.print(UID);

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

