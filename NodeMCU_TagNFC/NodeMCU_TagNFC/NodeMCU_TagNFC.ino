/*
 Name:		NodeMCU_TagNFC.ino
 Created:	13/12/2018 21:35:46
 Author:	Ariel
*/

#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>        // Controlador LCD
//#include <avr/wdt.h>                  // watch dog


#include <Wire.h>
#include <string.h>  //Borrar
#include <PN532_I2C.h>                // Comunicacion I2C para el modulo NFC		     
#include <PN532.h>                    // Funciones del modulo NFC 
#include <NfcAdapter.h>               // Automatizacion de las funciones del modulo NFC
#include <SoftwareSerial.h>

// Copiar el objeto Serial a una variable relacionada con el dispositivo
HardwareSerial &Pc = Serial;            // Para Debugg 

// Clases: 
SoftwareSerial MCU(4, 5); //Rx || Tx   // Puerto serie para NodeMCU 
PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c); // Pasa el argumento "interface (i2c o spi)" a la clase NfcAdapter. 
LiquidCrystal_I2C lcd(0x3F, 16, 2);     // Entrega los argumentos: direcci�n y dimensiones a la funcion lcd.

										// Configuración:
void setup(void) {

	//int ok;  // Varriable axuliaar para chequar estado. 

	Pc.begin(115200);
	MCU.begin(9600);
	lcd.init();

	my_lcd("Iniciando", 0, 0, false);
	delay(1000);

	// Iniciar Modulo NFC: 
	nfc.begin();            // Solicitar version del firmware al modulo

							/*ok= nfc.begin();
							if(ok == 1)   { //  reiniciar el sistema.
							Serial.println("\nNo conectado!");
							}
							// Debugg
							Serial.print("\nok= "); Serial.println(ok);
							*/
	my_lcd("NFC ACTIVO", 3, 1, false);
	delay(1000);
}

void loop(void) {
	// leer tag's:
	read_ndef();
}

/* Mensajes LCD: */
void my_lcd(String ms, byte co, byte fi, bool clr) {

	lcd.home();
	lcd.backlight();
	if (clr == true) {  // limpiear pantalla 
		lcd.clear();
	}

	lcd.setCursor(co, fi);
	lcd.print(ms);
}

/* leer Etiqueta simplificado */
void read_ndef() {
	//Mensaje lcd
	my_lcd("Esperando..", 0, 0, true);

	// Obtener UID si existe un Tag presente.  
	if (nfc.tagPresent())
	{
		my_lcd("Tag detectado", 0, 0, true);
		NfcTag tag = nfc.read();
		String uiid = tag.getUidString();  // obtener uid llamando a la funcion getuidstring.
		tag.print();                       // tag. print imprime info de la etiqueta y mensajes NDEF q contiene.
										   // Elimiar el debbug serial de tag.print

		my_lcd(uiid, 0, 1, false);         // Mostrar UID en pantalla. 

		/*Enviar Datos a NodeMCU*/
		MCU.print(uiid);                   // Envia UID a Node MCU
		MCU.print("\n");

		MCU.flush();
		Serial.flush();                    // Limpia el bufer serial
	}
	// Espera 1 segundo antes de volver a leer 
	delay(1000);
}

/* Escrbir en formato NDEF. */
void ndef_write() {

	my_lcd("Acercar etiqueta NFC", 0, 0, true);

	// Obtener UID si existe un Tag presente.  
	if (nfc.tagPresent())
	{
		NdefMessage message = NdefMessage();
		message.addTextRecord("Ariel.Torres");  // Mensaje para etiqueta nfc
												// message.addTextRecord("Autorizado");
												//message.addUriRecord("");
												//message.addTextRecord("");

		boolean success = nfc.write(message);
		if (success) {
			lcd.clear();
			lcd.print("Listo! prueba leer con android");
			for (int positionCounter = 0; positionCounter < 17; positionCounter++) {
				// scroll one position left:
				lcd.scrollDisplayLeft();
				// wait a bit:
				delay(200);
			}
		}
		else {
			Pc.println("Write failed");
			my_lcd("Error !", 0, 0, true);
		}
	}
}