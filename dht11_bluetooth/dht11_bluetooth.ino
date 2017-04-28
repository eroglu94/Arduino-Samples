#include <dht11.h>
#include <SoftwareSerial.h>

#define trigPin 13
#define echoPin 12

SoftwareSerial mySerial(10, 11); // RX, TX
int led1 = 7;
int led2 = 6;
int led3 = 5;
int led4 = 4;

int pirPin = 8;
int val;


dht11 DHT11;
int DHT11PIN = 2;

unsigned long previousMillis = 0;

void setup()
{
	pinMode(led1, OUTPUT);
	pinMode(led2, OUTPUT);
	pinMode(led3, OUTPUT);
	pinMode(led4, OUTPUT);
	pinMode(pirPin, INPUT);

	pinMode(trigPin, OUTPUT);
	pinMode(echoPin, INPUT);

	mySerial.begin(9600);
	mySerial.println("Uygulama Baslatildi");
}

void loop()
{
	MotionSensor();
	
}

void HavaDurumu()
{
	//Sensörden gelen bilgi olup olmadýðýný kontrol eder, chk 0 ise sorun var demek
	int chk = DHT11.read(DHT11PIN);


	unsigned long currentMillis = millis();
	if (currentMillis - previousMillis >= 3000)
	{
		/*save the last time you blinked the LED*/
		previousMillis = currentMillis;

		mySerial.print("Nem (%): ");
		mySerial.println((float)DHT11.humidity, 2);

		mySerial.print("Sicaklik : ");
		mySerial.print((float)DHT11.temperature, 2);
		mySerial.println(" C");

		mySerial.print("Dew Point: ");
		mySerial.println(DHT11.dewPoint(), 2);

		mySerial.println("____________________________");



	}
}

void LEDControl()
{
	char ch = mySerial.read();
	if (ch == '1')
	{
		digitalWrite(led1, !digitalRead(led1));
		if (digitalRead(led1) == HIGH)
		{
			mySerial.println("LED 1 yandi");
		}
		else
		{
			mySerial.println("LED 1 sondu");
		}
	}
	if (ch == '2')
	{
		digitalWrite(led2, !digitalRead(led2));
		if (digitalRead(led2) == HIGH)
		{
			mySerial.println("LED 2 yandi");
		}
		else
		{
			mySerial.println("LED 2 sondu");
		}
	}
	if (ch == '3')
	{
		digitalWrite(led3, !digitalRead(led3));
		if (digitalRead(led3) == HIGH)
		{
			mySerial.println("LED 3 yandi");
		}
		else
		{
			mySerial.println("LED 3 sondu");
		}
	}
	if (ch == '4')
	{
		digitalWrite(led4, !digitalRead(led4));
		if (digitalRead(led4) == HIGH)
		{
			mySerial.println("LED 4 yandi");
		}
		else
		{
			mySerial.println("LED 4 sondu");
		}
	}
	if (ch == '5')
	{
		digitalWrite(led1, LOW);
		digitalWrite(led2, LOW);
		digitalWrite(led3, LOW);
		digitalWrite(led4, LOW);
		mySerial.println("Tum LED'ler sondu");
	}
	if (ch == '6')
	{
		digitalWrite(led1, HIGH);
		digitalWrite(led2, HIGH);
		digitalWrite(led3, HIGH);
		digitalWrite(led4, HIGH);
		mySerial.println("Tum LED'ler yandi");
	}
}

void SonicSensor()
{
	long duration, distance;
	digitalWrite(trigPin, LOW);  // Added this line
	delayMicroseconds(2); // Added this line
	digitalWrite(trigPin, HIGH);
	//  delayMicroseconds(1000); - Removed this line
	delayMicroseconds(10); // Added this line
	digitalWrite(trigPin, LOW);
	duration = pulseIn(echoPin, HIGH);
	distance = (duration / 2) / 29.1;
	
	if (distance < 10 || distance >3000)
	{
		/*mySerial.println("No Object");*/
	}
	else
	{
		mySerial.println(distance);
	}

	
	delay(100);
	
}

void MotionSensor()
{
	val = digitalRead(pirPin); //read state of the PIR
	
	if (val == LOW) {
		Serial.println("No motion"); //if the value read is low, there was no motion
		digitalWrite(led4, LOW);
	}
	else if(val==HIGH) {
		Serial.println("Motion!"); //if the value read was high, there was motion
		digitalWrite(led4, HIGH);
		delay(3000);
	}
	digitalWrite(led4, LOW);
	delay(100);
}