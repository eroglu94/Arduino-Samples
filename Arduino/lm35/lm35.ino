float temp;
int temp_pin = 0;

void setup()
{

	Serial.begin(9600);

}

void loop()
{
	
	temp = analogRead(temp_pin);
	temp = temp * 0.48828125;
	Serial.print("Temperature= ");
	Serial.print(temp);
	Serial.print(" C");
	Serial.println();
	delay(1000);
}
