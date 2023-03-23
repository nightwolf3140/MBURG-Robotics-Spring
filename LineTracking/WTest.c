#pragma config(Sensor, S1,     leftS,         sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S2,     rightS,          sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S3,     reflect,        sensorEV3_Color)
#pragma config(Sensor, S4,     sonarSensor,    sensorEV3_Ultrasonic)
#pragma config(Motor,  motorA,          armMotor,      tmotorEV3_Medium, PIDControl, encoder)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Large, PIDControl, reversed, driveLeft, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Large, PIDControl, reversed, driveRight, encoder)
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
		displayBigTextLine(8, "USS: %d", getUSDistance(S4)); //Ultrasonic sensor
		displayBigTextLine(10, "B: %d", getMotorEncoder(leftMotor));
		displayBigTextLine(12, "C %d", getMotorEncoder(rightMotor));
	}
}

void linetracking(){
	if((getColorName(S1) == colorRed) || (getColorName(S2) == colorRed)){
		STP();
		playSound(soundBeepBeep);
	}
	if((getColorName(S1) == colorGreen) && (getColorName(S2) == colorGreen)){
		uTurn();
	}
	else if ((getColorName(S1)==colorGreen)&&(getColorName(S2)!=colorGreen)){
		moveCM(lineWidthCM);
		sleep(1000);
		leftPointTurn();
	}
	else if ((getColorName(S1)!=colorGreen)&&(getColorName(S2)==colorGreen)){
		moveCM(lineWidthCM);
		sleep(1000);
		rightPointTurn();
	}
	if((getColorName(S1) == colorBlack) && (getColorName(S2) == colorBlack)){
		moveCM(lineWidthCM);
	}
	else if((getColorName(S1) == colorBlack) && (getColorName(S2) != colorBlack)){
		leftNudge();
	}

	else if((getColorName(S1) != colorBlack) && (getColorName(S2) == colorBlack)){
		rightNudge();
	}

	if((getColorName(S1) == colorWhite) && (getColorName(S2) == colorWhite)){
		forwards();
	}

}

void avoidObstacle(){
	bool wall = checkObstacle();
	if(wall == true){
		STP();
	}
}

task main(){
	init(); //Config
	startTask(display);
	repeat(forever){
		linetracking();
		//avoidObstacle();
	}
}
