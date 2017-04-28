
int role = 5;
int kontrol = 12;

void setup()
{

	pinMode(role, OUTPUT);
	pinMode(kontrol, INPUT);
	

}

void loop()
{

	if (digitalRead(kontrol)==LOW)
	{
		digitalWrite(role, HIGH);
	}
	else
	{
		digitalWrite(role, LOW);
	}

	delay(200);

}
