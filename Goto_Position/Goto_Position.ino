// #####################################################################################################################
// ######################################### SET ONE STEPPER ###########################################################
// ##################################################################################################################### 
// Variables
int Current_Position = 0;
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

// ##################################################################################################################### 
// ######################################### SETUP #####################################################################
// ##################################################################################################################### 
void setup() 
{
	Serial.begin(9600);

	pinMode(Output_LED, OUTPUT);

	pinMode(Output_Const_IN1, OUTPUT);
	pinMode(Output_Const_IN2, OUTPUT);
	pinMode(Output_Const_IN3, OUTPUT);
	pinMode(Output_Const_IN4, OUTPUT);
}
// ##################################################################################################################### 
// ######################################### LOOP ######################################################################
// ##################################################################################################################### 
void loop() 
{
	// Loop is not required in this example
}
// ##################################################################################################################### 
// ######################################### SERIAL EVENT ##############################################################
// ##################################################################################################################### 
void serialEvent()
{
	if (Serial.available())
	{
		// Set LED
		digitalWrite(Output_LED, HIGH);

		// Read data and go to degree
		gotoDegree(Serial.readStringUntil('\n').toInt());

		// Set LED
		digitalWrite(Output_LED, LOW);
	}
	else
	{
		Serial.flush();
	}
}
// ##################################################################################################################### 
// ######################################### GOTO DEGREE ###############################################################
// ##################################################################################################################### 
void gotoDegree(int Parameter_Degrees)
{
	// Set maximum/minimum
	if (Parameter_Degrees < 0)
		Parameter_Degrees = 0;
	if (Parameter_Degrees > 359)
		Parameter_Degrees = 359;
	// Get the distance between the current and the target position
	int Distance = abs(abs(Parameter_Degrees) - abs(Current_Position));
	// Set direction
	if (abs(Parameter_Degrees) - abs(Current_Position) > abs(Current_Position) - abs(Parameter_Degrees))
		setDirection(true);
	else
		setDirection(false);
	// Goto position
	setStepper(Distance, 1000, true);
	// Set new current positio
	Current_Position = Parameter_Degrees;
}
// ##################################################################################################################### 
// ######################################### SET DIRECTION #############################################################
// ##################################################################################################################### 
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
// ##################################################################################################################### 
// ######################################### SET STEPPER ###############################################################
// ##################################################################################################################### 
void setStepper(int Parameter_Rounds, int Parameter_Delay, boolean Parameter_Degrees)
{
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
// ##################################################################################################################### 
// ######################################### END OF CODE ###############################################################
// ##################################################################################################################### 