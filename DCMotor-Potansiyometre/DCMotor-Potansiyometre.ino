int motorPin = 3;

int pot = A0;
int deger = 0;

void setup()
{
	Serial.begin(9600);
	pinMode(motorPin, OUTPUT);
	pinMode(pot, INPUT);
}

void loop()
{
	deger = analogRead(pot);
	deger = map(deger, 0, 1023, 0, 255);

	analogWrite(motorPin, deger);
	Serial.println(deger);
	delay(100);


}