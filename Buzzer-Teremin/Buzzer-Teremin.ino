int buzzerPin = 12;
int LDRPin = 0;

void setup()
{
}

void loop()
{
	int deger = analogRead(LDRPin);
	int pitch = 200 + deger / 4;
	tone(buzzerPin, pitch);
}