#pragma config(Sensor, S1,     leftS,          sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S2,     ScoopSensor,    sensorEV3_Color)
#pragma config(Sensor, S3,     ultrs,          sensorEV3_Ultrasonic)
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
	Justin Oh

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


void findBall()
{
repeat(forever)
	{
	if(SensorValue(S2) < 30){
		forwards();
		}
	if(SensorValue(S3) < 17)
		{
		STP();
		moveCM(-3);
		rightPointTurn();
		}
		else
		{
		forwards();
		while((getColorName(s1)!=colorBlack && (getColorName(S4)!= colorBlack))
			{
				moveCM(2);
				if(SensorValue(S3)<17)
				{
					STP();
					moveCM(-3);
					rightPointTurn()
				}
				uTurn();

			}

		}
	}
}




void rescueRoom(){//code here
	findBall();
}


void setProperties(){ //change properties here instead of headerfile
setUTurn(435);
setSpeed(10);
setTurnSpeed(10);
setTurnValue(230);//was 200
setWheelDiamter(7.4);
setWallDist(8); //Units in CM
setLineWidthCM(6.0);//make sure to use float values
setSearchTime(3.5);
coasting(false);//autobraking
}

void init(){ //First line of code to run
clearSounds();
clearTimer(T1);
eraseDisplay();
startTask(initDis);//Boot Screen
resetMotorEncoder(motorA);
storeArm();//Moves arm all the way up
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
	armDown();
	repeat(forever){
		rescueRoom();
	}
}
