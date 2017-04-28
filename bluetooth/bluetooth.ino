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
	pinMode(led2, OUTPUT);
	pinMode(led3, OUTPUT);
	pinMode(led4, OUTPUT);
	mySerial.begin(9600);
	mySerial.println("Uygulama Baslatildi");
}

void loop()
{
	unsigned long currentMillis = millis();

	if (currentMillis - previousMillis >= 3000)
	{
		// save the last time you blinked the LED
		previousMillis = currentMillis;


		temp = analogRead(temp_pin);
		temp = temp*0.48828125;
		
		mySerial.print("Temperature = ");
		mySerial.print(temp);
		mySerial.print(" C");
		mySerial.println();

	}

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