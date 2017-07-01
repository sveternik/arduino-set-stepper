// #####################################################################################################################
// ######################################### GOTO POSITION #############################################################
// ##################################################################################################################### 
// Variables
int currentPos = 0;
// Outputs
#define led	13
// Constant outputs for stepper
const byte stepperConstIn1 = 2; 
const byte stepperConstIn2 = 3; 
const byte stepperConstIn3 = 4; 
const byte stepperConstIn4 = 5; 
// Variable outputs for stepper	 
byte stepperIn1 = stepperConstIn1; 
byte stepperIn2 = stepperConstIn2; 
byte stepperIn3 = stepperConstIn3; 
byte stepperIn4 = stepperConstIn4;	 

void setup() 
{
	Serial.begin(9600);

	pinMode(led, OUTPUT);

	pinMode(stepperConstIn1, OUTPUT);
	pinMode(stepperConstIn2, OUTPUT);
	pinMode(stepperConstIn3, OUTPUT);
	pinMode(stepperConstIn4, OUTPUT);
}

void loop() 
{
	// Loop is not required in this example
}

void serialEvent()
{
	if (Serial.available())
	{
		digitalWrite(led, HIGH);
		gotoDegree(Serial.readStringUntil('\n').toInt());
		digitalWrite(led, LOW);
	}
	else
	{
		Serial.flush();
	}
}

void gotoDegree(int deg)
{
	// Set maximum/minimum
	if (deg < 0)
		deg = 0;
	if (deg > 359)
		deg = 359;
	// Get the distance between the current and the target position
	int Distance = abs(abs(deg) - abs(currentPos));
	// Set direction
	if (abs(deg) - abs(currentPos) > abs(currentPos) - abs(deg))
		setDirection(true);
	else
		setDirection(false);
	// Goto position
	setStepper(Distance, 1000, true);
	// Set new current positio
	currentPos = deg;
}

void setDirection(boolean positive)
{
	if (positive)
 	{
 		stepperIn1 = stepperConstIn1; 
 		stepperIn2 = stepperConstIn2; 
 		stepperIn3 = stepperConstIn3; 
 		stepperIn4 = stepperConstIn4; 
 	}
 	else
 	{
 		stepperIn1 = stepperConstIn4; 
 		stepperIn2 = stepperConstIn3; 
 		stepperIn3 = stepperConstIn2; 
 		stepperIn4 = stepperConstIn1; 
 	}
}

void setStepper(int rounds, int d3lay, boolean deg)
{
	if (deg)
	{
		rounds = round(rounds * 1.4153);
	}

	for (int X = 0; X < rounds; X++)
	{
        digitalWrite(stepperIn1, HIGH);
        digitalWrite(stepperIn4, LOW);
        delayMicroseconds(d3lay);

        digitalWrite(stepperIn1, HIGH);  
        digitalWrite(stepperIn2, HIGH);  
        delayMicroseconds(d3lay);

        digitalWrite(stepperIn1, LOW);   
        digitalWrite(stepperIn2, HIGH); 															 
        delayMicroseconds(d3lay);

        digitalWrite(stepperIn2, HIGH);  
        digitalWrite(stepperIn3, HIGH); 										 
        delayMicroseconds(d3lay);

        digitalWrite(stepperIn2, LOW);	 
        digitalWrite(stepperIn3, HIGH); 															 
        delayMicroseconds(d3lay);

        digitalWrite(stepperIn3, HIGH); 													 
        digitalWrite(stepperIn4, HIGH); 													 
        delayMicroseconds(d3lay);

        digitalWrite(stepperIn3, LOW); 
        digitalWrite(stepperIn4, HIGH);  
        delayMicroseconds(d3lay);

        digitalWrite(stepperIn1, HIGH);
        digitalWrite(stepperIn4, HIGH);
        delayMicroseconds(d3lay);
	}    

	// Disable all outputs
	digitalWrite(stepperIn1, LOW);
	digitalWrite(stepperIn2, LOW);
	digitalWrite(stepperIn3, LOW);
	digitalWrite(stepperIn4, LOW);
}