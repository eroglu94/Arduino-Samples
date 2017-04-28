int motorPin = 3;
int hiz = 0;

void setup()
{
	pinMode(motorPin, OUTPUT);
}

void loop()
{
	for (hiz = 0; hiz <= 100; hiz++)
	{
		analogWrite(motorPin, hiz);
		delay(20);
	}
	for (hiz = 100; hiz >= 0; hiz--)
	{
		analogWrite(motorPin, hiz);
		delay(20);
	}
}