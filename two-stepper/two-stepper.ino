// #####################################################################################################################
// ######################################### SET TWO STEPPER ###########################################################
// ##################################################################################################################### 
// Variables
boolean rotateInDeg = true;
int delaySteps = 1000;
// Outputs
#define led	13
// Constant outputs for stepper 1
const byte stepper1ConstIn1 = 2; 
const byte stepper1ConstIn2 = 3; 
const byte stepper1ConstIn3 = 4; 
const byte stepper1ConstIn4 = 5; 
// Constant outputs for stepper 2
const byte stepper2ConstIn1 = 6; 
const byte stepper2ConstIn2 = 7; 
const byte stepper2ConstIn3 = 8; 
const byte stepper2ConstIn4 = 9; 
// Variable outputs for stepper 1	 
byte stepper1In1 = stepper1ConstIn1; 
byte stepper1In2 = stepper1ConstIn2; 
byte stepper1In3 = stepper1ConstIn3; 
byte stepper1In4 = stepper1ConstIn4;	 
// Variable outputs for stepper 2	 
byte stepper2In1 = stepper2ConstIn1; 
byte stepper2In2 = stepper2ConstIn2; 
byte stepper2In3 = stepper2ConstIn3; 
byte stepper2In4 = stepper2ConstIn4;

void setup() 
{
	Serial.begin(9600);

	pinMode(led, OUTPUT);

	pinMode(stepper1ConstIn1, OUTPUT);
	pinMode(stepper1ConstIn2, OUTPUT);
	pinMode(stepper1ConstIn3, OUTPUT);
	pinMode(stepper1ConstIn4, OUTPUT);

	pinMode(stepper2ConstIn1, OUTPUT);
	pinMode(stepper2ConstIn2, OUTPUT);
	pinMode(stepper2ConstIn3, OUTPUT);
	pinMode(stepper2ConstIn4, OUTPUT);
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
		int Serial_Data = Serial.readStringUntil('\n').toInt();
		Serial_Data < 0 ? setDirection(false) : setDirection(true);
        setStepper(abs(Serial_Data), delaySteps, rotateInDeg);
		digitalWrite(led, LOW);
	}
	else
	{
		Serial.flush();
	}
}

void setDirection(boolean positive)
{
	if (positive)
 	{
 		stepper1In1 = stepper1ConstIn1; 
 		stepper1In2 = stepper1ConstIn2; 
 		stepper1In3 = stepper1ConstIn3; 
 		stepper1In4 = stepper1ConstIn4; 

 		stepper2In1 = stepper2ConstIn1; 
 		stepper2In2 = stepper2ConstIn2; 
 		stepper2In3 = stepper2ConstIn3; 
 		stepper2In4 = stepper2ConstIn4; 
 	}
 	else
 	{
 		stepper1In1 = stepper1ConstIn4; 
 		stepper1In2 = stepper1ConstIn3; 
 		stepper1In3 = stepper1ConstIn2; 
 		stepper1In4 = stepper1ConstIn1;  

 		stepper2In1 = stepper2ConstIn4; 
 		stepper2In2 = stepper2ConstIn3; 
 		stepper2In3 = stepper2ConstIn2; 
 		stepper2In4 = stepper2ConstIn1; 
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
        digitalWrite(stepper1In1, HIGH);
        digitalWrite(stepper1In4, LOW);
        digitalWrite(stepper2In1, HIGH);
        digitalWrite(stepper2In4, LOW);
        delayMicroseconds(d3lay);

        digitalWrite(stepper1In1, HIGH);  
        digitalWrite(stepper1In2, HIGH);  
        digitalWrite(stepper2In1, HIGH);  
        digitalWrite(stepper2In2, HIGH);  
        delayMicroseconds(d3lay);

        digitalWrite(stepper1In1, LOW);   
        digitalWrite(stepper1In2, HIGH); 	
        digitalWrite(stepper2In1, LOW);   
        digitalWrite(stepper2In2, HIGH); 															 
        delayMicroseconds(d3lay);

        digitalWrite(stepper1In2, HIGH);  
        digitalWrite(stepper1In3, HIGH); 		
        digitalWrite(stepper2In2, HIGH);  
        digitalWrite(stepper2In3, HIGH); 									 
        delayMicroseconds(d3lay);

        digitalWrite(stepper1In2, LOW);	 
        digitalWrite(stepper1In3, HIGH); 	
        digitalWrite(stepper2In2, LOW);	 
        digitalWrite(stepper2In3, HIGH);														 
        delayMicroseconds(d3lay);

        digitalWrite(stepper1In3, HIGH); 													 
        digitalWrite(stepper1In4, HIGH); 	
        digitalWrite(stepper2In3, HIGH); 													 
        digitalWrite(stepper2In4, HIGH); 												 
        delayMicroseconds(d3lay);

        digitalWrite(stepper1In3, LOW); 
        digitalWrite(stepper1In4, HIGH); 
        digitalWrite(stepper2In3, LOW); 
        digitalWrite(stepper2In4, HIGH);  
        delayMicroseconds(d3lay);

        digitalWrite(stepper1In1, HIGH);
        digitalWrite(stepper1In4, HIGH);
        digitalWrite(stepper2In1, HIGH);
        digitalWrite(stepper2In4, HIGH);
        delayMicroseconds(d3lay);
	}    

	// Disable all outputs
	digitalWrite(stepper1In1, LOW);
	digitalWrite(stepper1In2, LOW);
	digitalWrite(stepper1In3, LOW);
	digitalWrite(stepper1In4, LOW);

	digitalWrite(stepper2In1, LOW);
	digitalWrite(stepper2In2, LOW);
	digitalWrite(stepper2In3, LOW);
	digitalWrite(stepper2In4, LOW);
}