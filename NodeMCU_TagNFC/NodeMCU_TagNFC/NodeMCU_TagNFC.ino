/*
 Name:		NodeMCU_TagNFC.ino
 Created:	13/12/2018 21:35:46
 Author:	Ariel
*/

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
}

// the loop function runs over and over again until power down or reset
void loop() {
	Serial.println("hola"); 
	delay(5000);
}
