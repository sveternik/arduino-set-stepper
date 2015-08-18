// ############################################################################################################################
// ######################################### SET ONE STEPPER ##################################################################
// ############################################################################################################################
// Variables
boolean Rotate_In_Degrees = true;
int Delay_Of_Steps = 1000;
// Outputs
#define Output_LED	13
// Constant outputs for stepper
const byte Output_Const_IN1 = 2; 
const byte Output_Const_IN2 = 3; 
const byte Output_Const_IN3 = 4; 
const byte Output_Const_IN4 = 5; 
// Variable outputs for stepper	 
byte Output_IN1 = Output_Const_IN1; 
byte Output_IN2 = Output_Const_IN2; 
byte Output_IN3 = Output_Const_IN3; 
byte Output_IN4 = Output_Const_IN4;	 

// ############################################################################################################################
// ######################################### SETUP ############################################################################
// ############################################################################################################################
void setup() 
{
	Serial.begin(9600);

	pinMode(Output_LED, OUTPUT);

	pinMode(Output_Const_IN1, OUTPUT);
	pinMode(Output_Const_IN2, OUTPUT);
	pinMode(Output_Const_IN3, OUTPUT);
	pinMode(Output_Const_IN4, OUTPUT);
}
// ############################################################################################################################
// ######################################### LOOP #############################################################################
// ############################################################################################################################
void loop() 
{
	// Loop is not required in this example
}
// ############################################################################################################################
// ######################################### SERIAL EVENT #####################################################################
// ############################################################################################################################
void serialEvent()
{
	if (Serial.available())
	{
		// Set LED
		digitalWrite(Output_LED, HIGH);

		// Read data
		int Serial_Data = Serial.readStringUntil('\n').toInt();

		// Set direction (negative = left, positive = right)
		Serial_Data < 0 ? setDirection(false) : setDirection(true);

        // Set steps         
        setStepper(abs(Serial_Data), Delay_Of_Steps, Rotate_In_Degrees);

		// Set LED
		digitalWrite(Output_LED, LOW);
	}
	else
	{
		Serial.flush();
	}
}
// ############################################################################################################################
// ######################################### SET DIRECTION ####################################################################
// ############################################################################################################################
void setDirection(boolean Parameter_Positive)
{
	if (Parameter_Positive)
 	{
 		Output_IN1 = Output_Const_IN1; 
 		Output_IN2 = Output_Const_IN2; 
 		Output_IN3 = Output_Const_IN3; 
 		Output_IN4 = Output_Const_IN4; 
 	}
 	else
 	{
 		Output_IN1 = Output_Const_IN4; 
 		Output_IN2 = Output_Const_IN3; 
 		Output_IN3 = Output_Const_IN2; 
 		Output_IN4 = Output_Const_IN1; 
 	}
}
// ############################################################################################################################
// ######################################### SET STEPPER ######################################################################
// ############################################################################################################################
void setStepper(int Parameter_Rounds, int Parameter_Delay, boolean Parameter_Degrees)
{
	/*
	If Parameter_Degrees is true, the stepper will rotate the given Parameter_Rounds in degrees, not in steps.

	The stepper rotates 5.625 degrees per full step and 64 steps per one revolution on the internal shaft.
	
	The gear ratio is about  63.68395:1, so there are 4076 steps per full rotation.

	I run the stepper in half-step control, this means a control sequence of 8.

	The final result for the one revolution on the outer shaft is 509,5 steps. This means, that one degree is 1.4153 steps
	*/
	if (Parameter_Degrees)
	{
		Parameter_Rounds = round(Parameter_Rounds * 1.4153);
	}

	for (int X = 0; X < Parameter_Rounds; X++)
	{
        digitalWrite(Output_IN1, HIGH);
        digitalWrite(Output_IN4, LOW);
        delayMicroseconds(Parameter_Delay);

        digitalWrite(Output_IN1, HIGH);  
        digitalWrite(Output_IN2, HIGH);  
        delayMicroseconds(Parameter_Delay);

        digitalWrite(Output_IN1, LOW);   
        digitalWrite(Output_IN2, HIGH); 															 
        delayMicroseconds(Parameter_Delay);

        digitalWrite(Output_IN2, HIGH);  
        digitalWrite(Output_IN3, HIGH); 										 
        delayMicroseconds(Parameter_Delay);

        digitalWrite(Output_IN2, LOW);	 
        digitalWrite(Output_IN3, HIGH); 															 
        delayMicroseconds(Parameter_Delay);

        digitalWrite(Output_IN3, HIGH); 													 
        digitalWrite(Output_IN4, HIGH); 													 
        delayMicroseconds(Parameter_Delay);

        digitalWrite(Output_IN3, LOW); 
        digitalWrite(Output_IN4, HIGH);  
        delayMicroseconds(Parameter_Delay);

        digitalWrite(Output_IN1, HIGH);
        digitalWrite(Output_IN4, HIGH);
        delayMicroseconds(Parameter_Delay);
	}    

	// Disable all outputs
	digitalWrite(Output_IN1, LOW);
	digitalWrite(Output_IN2, LOW);
	digitalWrite(Output_IN3, LOW);
	digitalWrite(Output_IN4, LOW);
}
// ############################################################################################################################
// ######################################### END OF CODE ######################################################################
// ############################################################################################################################