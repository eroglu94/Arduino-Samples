/*
HC - SR04 Ping distance sensor]
VCC to arduino 5v GND to arduino GND
Echo to Arduino pin 13 Trig to Arduino pin 12
Red POS to Arduino pin 11
Green POS to Arduino pin 10
560 ohm resistor to both LED NEG and GRD power rail
More info at : http://goo.gl/kJ8Gl
Original code improvements to the Ping sketch sourced from Trollmaker.com
Some code and wiring inspired by http ://en.wikiversity.org/wiki/User:Dstaub/robotcar
*/

#include <RF24.h>
#include <nRF24L01.h>
#include <SPI.h>
int msgON[1];
int msgOFF[1]; //mesaj isminde bir dizi tanýmlýyoruz
RF24 verici(9, 10);     //kütüphane tarafýndan kullanýlacak pinleri tanýmlýyoruz
const uint64_t kanal = 0xE8E8F0F0E1LL; //kanalý tanýmlýyoruz

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

#include <dht11.h> // dht11 kütüphanesini ekliyoruz.
#define DHT11PIN 2 // DHT11PIN olarak Dijital 2"yi belirliyoruz.

#define trigPin 4
#define echoPin 3
dht11 DHT11;
int counter = 0;
int checker = 1;
bool light_checker = false;
float readings[20] = { 0 };


unsigned long previousMillis = 0;
unsigned long previousMillis_2 = 0;
unsigned long previousMillis_3 = 0;
unsigned long previousMillis_4 = 0;

void setup() {
	Serial.begin(9600);
	lcd.begin(16, 2);
	lcd.setCursor(0, 0); //Start at character 4 on line 0
	lcd.print("Ayarlamalar");
	lcd.setCursor(0, 1);
	lcd.print("Yapiliyor...");


	verici.begin();       //nrf yi baþlatýyoruz
	verici.openWritingPipe(kanal);  //kanal id sý tanýmlanýyor
	
	// ------- Quick 3 blinks of backlight  -------------
	for (int i = 0; i< 3; i++)
	{
		lcd.backlight();
		delay(250);
		lcd.noBacklight();
		delay(250);
	}
	lcd.backlight(); // finish with backlight on  
	SendMessage(msgOFF);

	Serial.println("Uygulama Baslatýldý...");

	pinMode(trigPin, OUTPUT);
	pinMode(echoPin, INPUT);

	lcd.setCursor(1, 0);
	lcd.clear();
	delay(1000);
	
	
}

void loop() {
	unsigned long currentMillis = millis();
	if (currentMillis - previousMillis >= 10)
	{
		/*save the last time you blinked the LED*/
		previousMillis = currentMillis;

		msgOFF[0] = 0;
		msgON[0] = 1;
		long duration, distance;
		digitalWrite(trigPin, LOW);  // Added this line
		delayMicroseconds(2); // Added this line
		digitalWrite(trigPin, HIGH);
		//  delayMicroseconds(1000); - Removed this line
		delayMicroseconds(10); // Added this line
		digitalWrite(trigPin, LOW);
		duration = pulseIn(echoPin, HIGH);
		distance = (duration / 2) / 29.1;

		if (distance >= 400 || distance <= 0) {
			/*Serial.println("Out of range");*/

			lcd.setCursor(0, 1);
			lcd.print("Mesafe  :");
			lcd.setCursor(10, 1);
			lcd.print("Out !!");
			
			
		}
		else {
			/*Serial.print(distance);
			Serial.println(" cm");*/
			lcd.setCursor(0, 1);
			lcd.print("Mesafe  :");

			lcd.setCursor(11, 1);
			lcd.print("   ");
			lcd.setCursor(10, 1);
			lcd.print(distance);
			lcd.setCursor(14, 1);
			lcd.print("cm");
			/*delay(50);*/
			if (distance < 65 && light_checker == false)
			{
				delay(10);
				unsigned long currentMillis_3 = millis();
				if (currentMillis_3 - previousMillis_3 >= 2000)
				{
					/*save the last time you blinked the LED*/
					previousMillis_3 = currentMillis_3;
					SendMessage(msgON);
					light_checker = true;
				}
				
				/*delay(2000);*/
			}
			else if (distance < 65 && light_checker==true )
			{
				delay(10);
				unsigned long currentMillis_3 = millis();
				if (currentMillis_3 - previousMillis_3 >= 2000)
				{
					/*save the last time you blinked the LED*/
					previousMillis_3 = currentMillis_3;

					SendMessage(msgOFF);
					light_checker = false;
				}
				
				/*delay(2000);*/
			}
		}
		

	}


	

//	unsigned long currentMillis_2 = millis();
//	if (currentMillis_2 - previousMillis_2 >= 3000)
//	{
//		/*save the last time you blinked the LED*/
//		previousMillis_2 = currentMillis_2;
//		// Bir satýr boþluk býrakýyoruz serial monitörde.
//		Serial.println();
//		// Sensörün okunup okunmadýðýný konrol ediyoruz. 
//		// chk 0 ise sorunsuz okunuyor demektir. Sorun yaþarsanýz
//		// chk deðerini serial monitörde yazdýrýp kontrol edebilirsiniz.
//		int chk = DHT11.read(DHT11PIN);
//
//		// Sensörden gelen verileri serial monitörde yazdýrýyoruz.
//
//
//		/*float temp = StableTemperature();
//		Serial.print("Sicaklik (Celcius): ");
//		Serial.println(temp, 2);
//
//
//
//		lcd.setCursor(0, 0);
//		lcd.print("Sicaklik: ");
//		lcd.setCursor(10, 0);
//		lcd.print(temp, 1);
//		lcd.setCursor(15, 0);
//		lcd.print("C");
//
//		Serial.print("Simdi: ");
//		Serial.println(light_checker);
//
//
//		Serial.print("Nem (%): ");
//		Serial.println((float)DHT11.humidity, 2);*/
//
//		// 2 saniye bekliyoruz. 2 saniyede bir veriler ekrana yazdýrýlacak.
//		Serial.println();
//
//	}
//	
}

float StableTemperature()
{
	float temp = 0;
	readings[counter] = (float)DHT11.temperature;
	if (checker == 1)
	{
		temp = DHT11.temperature;
	}
	else
	{
		for (int i = 0; i < 20; i++)
		{
			temp = temp + readings[i];
		}
		temp = temp / 20;
	}

	if (counter >= 20)
	{
		counter = -1;
		checker = 0;
	}
	counter++;
	return temp;
}

bool SendMessage(int msg[])
{
	bool status = false;
	int count = 0;
	while (!status)
	{
		count++;
		status = verici.write(msg, 1);
		if (count >= 50 && status == false)
		{
			Serial.println("***************Connection Failed******************");
			break;
		}
	}
	
	return status;
}