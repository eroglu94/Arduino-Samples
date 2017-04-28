void setup() {
	Serial.begin(9600);
	delay(50);
	pinMode(8, OUTPUT);
}

void loop() {
	if (Serial.available())
	{
		char x = Serial.read();
		Serial.write(x); // echo everything

		if (x == '1')
		{
			digitalWrite(13, HIGH);

			delay(1000);
			digitalWrite(13, LOW);

			delay(1000);
		}
	}

}