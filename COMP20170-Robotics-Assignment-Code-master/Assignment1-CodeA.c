#pragma config(Sensor, S2,     touchSensor,    sensorEV3_Touch)
#pragma config(Sensor, S3,     lightSensor,    sensorEV3_Color, modeEV3Color_Color)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//Constant Variables for the Robot
const int DEFAULT_SPEED = 30;
const int LINE_COLOUR = 5;
const int DEFAULT_TIME = 1000;
const int SHORT_DEFAULT_TIME = 100;

//Function to set the power of the robot motors to move in a straight line
void forward(int speed = DEFAULT_SPEED, int time = DEFAULT_TIME){
	//Set the power of the two motors
	motor[motorB] = speed;
	motor[motorC] = speed;

	//Wait time milliseconds
	wait1Msec(time);
}


//Function to move the robot forward in a straight line till the touch sensor
void forwardUnitilTouch(int speed){

	//Loop to keep the robot moving forward untill Touch sensor is pressed
	while (SensorValue(touchSensor) == 0){

		//Move the robot forward
		forward(speed, SHORT_DEFAULT_TIME);

	}

	//Stop the robots movement
	forward(0, DEFAULT_TIME);
}


//Function for turning L or R
void turning(char direction, int time){
	//Speed of the turn
	int speed = DEFAULT_SPEED;

	//if the direction is R/L? change the direction of the speed
	if(direction == 'L'){
		speed = speed * -1;
	}

	//Sets the motor speed for turning
	//Motors move in oppisite direction to make the robot turn
	motor[motorB] = speed;
	motor[motorC] = -speed;

	//Wait
	wait1Msec(time);

	//Stops the robot from turning
	forward(0, DEFAULT_TIME);

}

//Function to get the robot to follow a line
void followLine(bool wheelTurnModeOff, float numberOfWheelRotations){

	//Variables
	int turnspeed = DEFAULT_SPEED;
	//Sets the number of degrees at max each wheel can turn
	int degreesOfRotation = (int)(360 * numberOfWheelRotations);

	//Set the MotorEncoder to 0
	nMotorEncoder[motorC] = 0;
	nMotorEncoder[motorB] = 0;

	//While loop to loop until
	//1: The touch sensor is pressed or,
	//2: The wheelTurnMode is set to be on and one of the wheels execceds the Wheel Rotations
	while(SensorValue(touchSensor) == 0 && (wheelTurnModeOff || (nMotorEncoder[motorC] < degreesOfRotation && nMotorEncoder[motorB] < degreesOfRotation))){

		//Will track the left side of the line

		//If the colur detector see a light colour turn right onto the line
		if(SensorValue(lightSensor) != LINE_COLOUR){

			motor[motorC] = 0;
			motor[motorB] = turnspeed;
		}

		//Else on the line so turn left
		else{

			motor[motorC] = turnspeed;
			motor[motorB] = 0;
		}

	}

	//Stop the robot
	forward(0, DEFAULT_TIME);

}


//Function to have the robot search for a dark line in a zig zag method
void forwardTillLineZigZag(){



	//Variables for function
	int speed = DEFAULT_SPEED, time = SHORT_DEFAULT_TIME, maxTurns = 5;



	//When the robot finds the dark line
	while(SensorValue(lightSensor) != LINE_COLOUR){

	//For loop to turn right maxTurn time
	for(int i =0; i < maxTurns; i++){
			//Turn right
			motor[motorC] = 0;
			motor[motorB] = speed;
			wait1Msec(time);

			//If the robot is on the line return out of the function
			if(SensorValue(lightSensor) == LINE_COLOUR){
				//Stop the robot
				forward(0, DEFAULT_TIME);
				return;
			}
		}

		//For loop to turn left maxTurn time
		for(int i =0; i < maxTurns; i++){
			//Turn left
			motor[motorC] = speed;
			motor[motorB] = 0;
			wait1Msec(time);

			//If the robot is on the line return out of the function
			if(SensorValue(lightSensor) == LINE_COLOUR){
				//Stop the robot
				forward(0, DEFAULT_TIME);
				return;
			}
		}
	}



	//Stop the robot
	forward(0, DEFAULT_TIME);
}

//Function to have the robot search for a dark line in a straight line
void forwardTillLine(bool straightForward){



	//Variables for function
	int speed = DEFAULT_SPEED, time = SHORT_DEFAULT_TIME;

	if(!straightForward){
		speed = - speed;
	}

	//When the robot finds the dark line
	while(SensorValue(lightSensor) != LINE_COLOUR){

		forward(speed, time);

	}



	//Stop the robot
	forward(0, DEFAULT_TIME);
}

task main()
{
	forwardUnitilTouch(30);

	//Reverser the robot a small amount from the touched object
	forward(-DEFAULT_SPEED, 1500);

	turning('L',800);

	forwardTillLineZigZag();

	followLine(true, 0);

	forward(-DEFAULT_SPEED, 500);

	turning('L', 700);

	forward(-DEFAULT_SPEED, 800);

	forwardTillLine(false);

	forward(DEFAULT_SPEED, 300);

	forwardTillLine(true);

		turning('L', 300);

	followLine(false, 6);

	turning('L', 600);

	forwardUnitilTouch(30);

	forward(-DEFAULT_SPEED, 500);

	turning('L', 800);

	forwardUnitilTouch(30);

}
