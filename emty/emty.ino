void setup()
{

  /* add setup code here */

}

void loop()
{

	if (digitalRead(7)==LOW)
	{
		digitalWrite(7, HIGH);
	}
	else
	{
		delay(100);
	}

}
