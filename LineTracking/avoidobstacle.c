#pragma config(Sensor, S1,     leftS,          sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S2,     rightS,         sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S3,     reflect,        sensorEV3_Color)
#pragma config(Sensor, S4,     sonarSensor,    sensorEV3_Ultrasonic)
#pragma config(Motor,  motorA,          armMotor,      tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Large, PIDControl, driveRight, encoder)
#pragma config(Motor,  motorD,           ,             tmotorEV3_Large, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "RobotLibrary.h" //Code Library

/*

	Credits:

	William Sellery
	Frederick Wu
	Justin

*/
task display(){//Onboard Debugger system
	repeat(forever){
		displayCenteredTextLine(1, "Onboard Debugger");
		displayBigTextLine(3, "LCS: %d", getColorName(leftS)); //left sensor
		displayBigTextLine(6, "RCS: %d", getColorName(rightS)); //Right sensor
		//displayBigTextLine(8, "USS: %d", getUSDistance(S3)); //Ultrasonic sensor
		displayBigTextLine(10, "B: %d", getMotorEncoder(leftMotor));
		displayBigTextLine(12, "C %d", getMotorEncoder(rightMotor));
	}
}

void moveforward(int x){
	resetMotorEncoder(motorB);
	resetMotorEncoder(motorC);
	setMotorTarget(motorB,x,10);
	setMotorTarget(motorC,x,10);
	waitUntilMotorStop(motorC);
}

void avoidObstacle(){
	bool wall = checkObstacle();
	if(wall == true){
		STP();
		leftPointTurn();
		repeat(7){
				moveCM(1);
				if ((getColorName(S1)==colorBlack)||(getColorName(S2)==colorBlack)){
					return;
				}
		}
		rightPointTurn();
		repeat(3){
			repeat(14){
				moveCM(1);
				if ((getColorName(S1)==colorBlack)||(getColorName(S2)==colorBlack)){
					return;
				}
			}
			rightPointTurn();
		}
	}
}

void setProperties(){ //change properties here instead of headerfile
setUTurn(340);
setSpeed(15);
setTurnSpeed(10);
setTurnValue(190);
setWheelDiamter(7.4);
setWallDist(8); //Units in CM
}

void init(){ //First line of code to run
clearSounds();
clearTimer(T1);
eraseDisplay();
rsMotors();
bFloatDuringInactiveMotorPWM=false; //Motor coasting
setProperties(); //config settings
}

task main(){
	init(); //Config
	startTask(display);
	repeat(forever){
		avoidObstacle();
	}
}
