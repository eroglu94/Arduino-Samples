
#include <SoftwareSerial.h>
#define trigPin 6 //Sensörün Echo pini Arduinonun 13. pinine baðlanýr
#define echoPin 5 //Sensorün Trig pini Arduinonun 12. pinine baðlanýr
int count = 0;
SoftwareSerial mySerial(10, 11); // RX, TX
void setup() {
	mySerial.begin(9600);
	delay(50);
	pinMode(trigPin, OUTPUT); //13. yani trigpini çýkýþ olarak ayarlýyoruz
	pinMode(echoPin, INPUT); //12. yani echoPini giriþ olarak ayarlýyoruz
}

void loop() {

	long duration, distance;
	digitalWrite(trigPin, LOW);
	delayMicroseconds(2);
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);
	duration = pulseIn(echoPin, HIGH);
	distance = (duration / 2) / 29.1;
	
	if (distance < 99)
	{

		mySerial.println(distance);

	}

	delay(50);

	//counter++;
	//Serial.print("Arduino counter: ");
	//Serial.println(counter);
	//delay(500); // wait half a sec
}
