#include <SoftwareSerial.h>

SoftwareSerial mySerial(6, 7); // RX, TX
String isim = "HC 05";
int sifre = 1234;
String uart = "19200,0,0";

void setup() {
  Serial.begin(9600);
  Serial.println("HC-05 Modul Ayarlaniyor...");
  Serial.println("Lutfen 10 sn icinde HC-05 modulun uzerindeki butona basili tutarak baglanti yapiniz.");
  for(int i=10;i>=0;i--)
  {
    Serial.println(i);
    delay(1000);
    }
  mySerial.begin(38400);
  
  mySerial.print("AT+NAME=");
  mySerial.println(isim);
  Serial.print("Isim ayarlandi: ");
  Serial.println(isim);
  delay(1000);
  mySerial.print("AT+PSWD=");
  mySerial.println(sifre);
  Serial.print("Sifre ayarlandi: ");
  Serial.println(sifre);
  delay(1000);
  mySerial.print("AT+UART=");
  mySerial.println(uart);
  Serial.print("Baud rate ayarlandi: ");
  Serial.println(uart);
  delay(2000);
  Serial.println("Islem tamamlandi.");
}

void loop()

{

}
