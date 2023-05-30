#include<Arduino.h>
 const int xPin=2;
 const int yPin=3;
 const int zPin=13;

 void setup()
{

	pinMode(xPin, INPUT);
	pinMode(yPin, INPUT);
	pinMode(zPin, OUTPUT);

	Serial.begin(9600);
}

void loop()
{
	int x=digitalRead(xPin);
	int y=digitalRead(yPin);
	int z=x^y;
	digitalWrite(zPin, z);
}

