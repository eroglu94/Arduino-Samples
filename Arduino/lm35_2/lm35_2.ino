float temp;
int temp_pin = 1;

void setup()
{

	Serial.begin(9600);
	pinMode(2, OUTPUT);
	pinMode(3, OUTPUT);
	pinMode(4, OUTPUT);



	digitalWrite(2, LOW);
	digitalWrite(3, LOW);
	digitalWrite(4, LOW);
}

void loop()
{

	temp = analogRead(temp_pin);
	temp = temp * 0.48828125;
	Serial.print("Temperature= ");
	Serial.print(temp);
	Serial.print(" C");
	Serial.println();


	if (temp <= 28)
	{
		digitalWrite(2, HIGH);
		digitalWrite(3, LOW);
		digitalWrite(4, LOW);
	}
	else if (temp > 28 && temp<30)
	{
		digitalWrite(2, HIGH);
		digitalWrite(3, HIGH);
		digitalWrite(4, LOW);
	}
	else if (temp>=30)
	{
		digitalWrite(2, HIGH);
		digitalWrite(3, HIGH);
		digitalWrite(4, HIGH);
	}





	delay(1000);
}
