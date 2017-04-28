/* Sweep
by BARRAGAN <http://barraganstudio.com>
This example code is in the public domain.

modified 8 Nov 2013
by Scott Fitzgerald
http://www.arduino.cc/en/Tutorial/Sweep
*/


#include <Servo.h>
int pot = A0;
int deger = 0;

Servo myservo;  // create servo object to control a servo

void setup() {
	Serial.begin(9600);
	myservo.attach(9);  // attaches the servo on pin 9 to the servo object
	pinMode(pot, INPUT);
}

void loop() {

	deger = analogRead(pot);
	deger = map(deger, 0, 1023, 1, 179);
	
	Serial.print(deger);
	Serial.print(" - ");
	Serial.println(myservo.read());
	if (myservo.read() != deger)
	{

		myservo.write(deger);

	}
	delay(50);


}
