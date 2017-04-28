#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX
int led1 = 7;
int led2 = 6;
int led3 = 5;
int led4 = 4;
int temp_pin = 1;
float temp;

unsigned long previousMillis = 0;

void setup()
{
	pinMode(led1, OUTPUT);
	digitalWrite(led1, LOW);
	mySerial.begin(9600);
	mySerial.println("Uygulama Baslatildi");
}

void loop()
{


	char ch = mySerial.read();
	if (ch == '0')
	{
		
		digitalWrite(led1, LOW);
		mySerial.println("0000");
	}
	if (ch=='1')
	{
		digitalWrite(led1, HIGH);
		mySerial.println("1111");
	}

	delay(20);
	
}