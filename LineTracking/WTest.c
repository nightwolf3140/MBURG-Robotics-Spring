#pragma config(Sensor, S1,     leftS,          sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S3,     reflect,        sensorEV3_Ultrasonic)
#pragma config(Sensor, S4,     rightS,         sensorEV3_Color, modeEV3Color_Color)
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
		displayBigTextLine(8, "USS: %d", getUSDistance(S3)); //Ultrasonic sensor
		displayBigTextLine(10, "B: %d", getMotorEncoder(leftMotor));
		displayBigTextLine(12, "C: %d", getMotorEncoder(rightMotor));
	}
}

void linetracking(){
	if((getColorName(S1) == colorRed) || (getColorName(S4) == colorRed)){
		STP();
		playSound(soundBeepBeep);
		setLEDColor(ledRedPulse);
	}
	if((getColorName(S1) == colorGreen) || (getColorName(S4) == colorGreen)){
		STP();
		setLEDColor(ledGreen);
		sleep(2000);
		if((getColorName(S1) == colorGreen) && (getColorName(S4) == colorGreen)){
			uTurn();
			sleep(200);
			moveCM(1);
		}
		else if ((getColorName(S1)==colorGreen)&&(getColorName(S4)!=colorGreen)){
			leftPointTurn();
			sleep(200);
		}
		else if ((getColorName(S1)!=colorGreen)&&(getColorName(S4)==colorGreen)){
			rightPointTurn();
			sleep(200);
		}
	}
	if((getColorName(S1) == colorBlack) || (getColorName(S4) == colorBlack)){
		STP();
		sleep(200);
		if((getColorName(S1) == colorBlack) && (getColorName(S4) == colorBlack)){
			STP();
			findLine();
		}
		else if((getColorName(S1) == colorBlack) && (getColorName(S4) != colorBlack)){
			//leftNudge();
			findLeft();
			moveCM(1.0);
		}

		else if((getColorName(S1) != colorBlack) && (getColorName(S4) == colorBlack)){
			//rightNudge();
			findRight();
			moveCM(1.0);
		}
	}

	if((getColorName(S1) == colorWhite) && (getColorName(S4) == colorWhite)){
		setLEDColor(ledGreenPulse);
		forwards();
	}
	else{
		//playSound(soundException); //Means color sensor tripping out
		setLEDColor(ledRed);
	}

}

/*void avoidObstacle(){
	bool wall = checkObstacle();
	if(wall == true){
		STP();
	}
}
*/ //To be replaced by avoidobstacle.c
void setProperties(){ //change properties here instead of headerfile
setUTurn(435);
setSpeed(15);
setTurnSpeed(10);
setTurnValue(200);
setWheelDiamter(7.4);
setWallDist(8); //Units in CM
setLineWidthCM(4.0);//make sure to use float values
setSearchTime(6.0);
coasting(false);//autobraking
}

void init(){ //First line of code to run
clearSounds();
clearTimer(T1);
eraseDisplay();
startTask(initDis);//Boot Screen
homeArm();//Moves arm all the way up
rsMotors();
bFloatDuringInactiveMotorPWM=false; //Motor coasting
setProperties(); //config settings
sleep(2000);
stopTask(initDis);//Boot screen
eraseDisplay();
startTask(display);//Starts debugger screen
}

task main(){
	init(); //Config
	repeat(forever){
		linetracking();
		//avoidObstacle();
	}
}
