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
		leftPointTurn();
	}
	else if ((getColorName(S1)!=colorGreen)&&(getColorName(S2)==colorGreen)){
		rightPointTurn();
	}
	if((getColorName(S1) == colorBlack) && (getColorName(S2) == colorBlack)){
		moveCM(lineWidthCM);
		findLeft();
	}
	else if((getColorName(S1) == colorBlack) && (getColorName(S2) != colorBlack)){
		//leftNudge();
		findLeft();
	}

	else if((getColorName(S1) != colorBlack) && (getColorName(S2) == colorBlack)){
		//rightNudge();
			findRight();
	}

	if((getColorName(S1) == colorWhite) && (getColorName(S2) == colorWhite)){
		forwards(6);
	}

}

void avoidObstacle(){
	bool wall = checkObstacle();
	if(wall == true){
		STP();
	}
}

void setProperties(){ //change properties here instead of headerfile
setUTurn(340);
setSpeed(10);
setTurnSpeed(10);
setTurnValue(170);
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
		linetracking();
		//avoidObstacle();
	}
}
