// #####################################################################################################################
// ######################################### SET ONE STEPPER ###########################################################
// ##################################################################################################################### 
// Variables
boolean rotateInDeg = true;
int delaySteps = 1000;
// Outputs
#define Output_LED 13
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

	pinMode(Output_LED, OUTPUT);

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
		digitalWrite(Output_LED, HIGH);
		int Serial_Data = Serial.readStringUntil('\n').toInt();
		Serial_Data < 0 ? setDirection(false) : setDirection(true);   
        setStepper(abs(Serial_Data), delaySteps, rotateInDeg);
		digitalWrite(Output_LED, LOW);
	}
	else
	{
		Serial.flush();
	}
}

void setDirection(boolean dirPos)
{
	if (dirPos)
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
	/*
	If deg is true, the stepper will rotate the given rounds in degrees, not in steps.

	The stepper rotates 5.625 degrees per full step and 64 steps per one revolution on the internal shaft.
	
	The gear ratio is about  63.68395:1, so there are 4076 steps per full rotation.

	I run the stepper in half-step control, this means a control sequence of 8.

	The final result for the one revolution on the outer shaft is 509,5 steps. This means, that one degree is 1.4153 steps
	*/
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