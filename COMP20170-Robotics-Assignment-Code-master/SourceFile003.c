#pragma config(Sensor, S2,     touchSensor,    sensorEV3_Touch)
#pragma config(Sensor, S3,     lightSensor,    sensorEV3_Color, modeEV3Color_Color)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

const int DEFAULT_SPEED = 30;
const int LINE_COLOUR = 5;

void forward(int speed = DEFAULT_SPEED, int time = 1000){
	motor[motorB] = speed;
	motor[motorC] = speed;

	wait1Msec(time);
}


void forwardUnitilTouch(int speed){

	//Loop to keep the robot moving forward untill Touch sensor is pressed
	while (SensorValue(touchSensor) == 0){

		//Move the robot forward
		forward(speed, 100);

	}





	//Stop the robots movement
	forward(0, 1000);
}

//Function for turning
void turning(char direction, int time){
	//Speed of the turn
	int speed = DEFAULT_SPEED;

	//if the direction is R/L? change the direction of the speed
	if(direction == 'L'){
		speed = speed * -1;
	}

	//Sets the motor speed for turning
	motor[motorB] = speed;
	motor[motorC] = -speed;

	wait1Msec(time);

	//Stops the robot from turning
	forward(0, 1000);


}

void followLine(){

	//
	int turnspeed = DEFAULT_SPEED, numberOfWheelRotations = 7;

	//Set the MotorEncoder to 0
	nMotorEncoder[motorC] = 0;
	nMotorEncoder[motorB] = 0;

	//While loop to loop until one of the wheels execceds the Wheel Rotations
	//nMotorEncoder[motorC] < numberOfWheelRotations * 360 && nMotorEncoder[motorB] < numberOfWheelRotations * 360
	while(SensorValue(touchSensor) == 0){

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
	forward(0, 1000);

}

void forwardTillLine(){
	//Move robot forward
	//forward(DEFAULT_SPEED, 1000);

int speed = 30, time = 100;

	//When the robot finds the dark line
	while(SensorValue(lightSensor) != LINE_COLOUR){
		for(int i =0; i < 5; i++){
			motor[motorC] = 0;
			motor[motorB] = speed;
			wait1Msec(time);
			if(SensorValue(lightSensor) == LINE_COLOUR){
				//Stop the robot
				forward(0, 1000);
				return;
			}
		}
		for(int i =0; i < 5; i++){
			motor[motorC] = speed;
			motor[motorB] = 0;
			wait1Msec(time);
			if(SensorValue(lightSensor) == LINE_COLOUR){
				//Stop the robot
				forward(0, 1000);
				return;
			}
		}
	}

	//Stop the robot
	forward(0, 1000);
}

task main()
{
	forwardUnitilTouch(30);

	//Reverser the robot a small amount from the touched object
	forward(-DEFAULT_SPEED, 1300);

	turning('L',700);

	forwardTillLine();

	followLine();

	forward(-DEFAULT_SPEED, 500);



}
