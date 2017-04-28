#include <SoftwareSerial.h>
#include  <SPI.h> 
#include "nRF24L01.h"
#include "RF24.h"     //Mod�l ile ilgili k�t�phaneleri ekliyoruz
int msgON[1];
int msgOFF[1]; //mesaj isminde bir dizi tan�ml�yoruz
RF24 verici(9, 10);     //k�t�phane taraf�ndan kullan�lacak pinleri tan�ml�yoruz
SoftwareSerial btSerial(6, 7); // RX, TX
const uint64_t kanal = 0xE8E8F0F0E1LL; //kanal� tan�ml�yoruz  
int buton = 3;      //butonun ba�l� oldu�u dijital pin

void setup(void)
{
	pinMode(buton, INPUT);
	digitalWrite(buton, LOW);
	btSerial.begin(19200);
	btSerial.println("Uygulama Baslatildi");
	verici.begin();       //nrf yi ba�lat�yoruz
	verici.openWritingPipe(kanal);  //kanal id s� tan�mlan�yor
	
}


void loop(void)
{
		msgOFF[0] = 0;
		msgON[0] = 1;
	

	char ch = btSerial.read();
	if (ch=='0')
	{
		if (SendMessage(msgOFF)==true)
		{
			btSerial.println("OFF");
		}
		
	}
	else if (ch=='1')
	{
		if (SendMessage(msgON)==true)
		{
			btSerial.println("ON");
		}
		
	}
}

bool SendMessage(int msg[])
{
	bool status = false;
	int count = 0;
	while (!status)
	{
		count++;
		status = verici.write(msg, 1);
		if (count>=20 && status==false)
		{
			btSerial.println("Connection Failed");
			break;
		}
	}
	return status;
}