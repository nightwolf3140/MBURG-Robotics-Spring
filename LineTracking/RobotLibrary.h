int m = 1; //Motor Vector
int uTurnValue = 340;
int vpointTurn = 170; //point turn value
int speed = 5;
int turnSpeed = 15;//speed times direction (positive/negative)
int lineWidthCM = 1.8; //distance of tape line
float WheelDiamterCM = 7.4; //Stock ev3
int WallDistCM = 8;
int searchTime = 2;


//throw functions below
void rsMotors(){
	resetMotorEncoder(motorB);
	resetMotorEncoder(motorC);
}

/*void forwards(){ //default
	rsMotors();
	//setMultipleMotors(speed, motorB, motorC);
	motor[motorB] = speed;
	motor[motorC] = speed;
}*/
void forwards(int x){ //controled speed
	rsMotors();
	//setMultipleMotors(x, motorB, motorC);
	motor[motorB] = x;
	motor[motorC] = x;
}

void uTurn(){
	rsMotors();
	setMotorTarget(motorB,uTurnValue,50);
	setMotorTarget(motorC,-uTurnValue,50);
}


void STP(){ //kinda irelivant with stopAllMotors();
	rsMotors();
	motor[motorB] = 0;
	motor[motorC] = 0;
}

/*float convertEncoderToCM(int encoderCounts){
	return(encoderCounts / 360.0)*(WheelDiamterCM * PI);
}*/

/*float convertCMToDegrees(float y){ //converts CM imput to wheel degrees
	return y/(WheelDiamterCM*PI)*360;
}*/
float convertCMToDegrees(float y){ //converts CM imput to wheel degrees
	return y/(PI*WheelDiamterCM)*360.0;
}

void moveCM(float y){ //move given distance in CM
	float x=convertCMToDegrees(y);
	rsMotors();
	//int x = 84;
	setMotorTarget(motorB, x, speed);
	setMotorTarget(motorC, x, speed);
	waitUntilMotorStop(motorC);
}
void leftPointTurn(){
	moveCM(lineWidthCM);
	sleep(1000);
	rsMotors();
	setMotorTarget(motorB,-vpointTurn,turnSpeed);
	setMotorTarget(motorC,vpointTurn,turnSpeed);
	waitUntilMotorStop(motorC);
	sleep(200);

}

void rightPointTurn(){
	moveCM(lineWidthCM);
	sleep(1000);
	rsMotors();
	setMotorTarget(motorB,vpointTurn,turnSpeed);
	setMotorTarget(motorC,-vpointTurn,turnSpeed);
	waitUntilMotorStop(motorC);
	sleep(200);
}

/*void leftNudge(){
	STP();
	rsMotors();
	setMotorTarget(motorC, 10, 10);
	waitUntilMotorStop(motorC);
}

void rightNudge(){
	STP();
	rsMotors();
	setMotorTarget(motorB, 10, 10);
	waitUntilMotorStop(motorB);
}*/

bool checkObstacle(){
	bool wall;
	if(getUSDistance(S4) > WallDistCM){
		wall = true;
		return wall;
	}
	else{
		wall = false;
		return wall;
	}
}

void searchRight(){
	motor[motorB] = turnSpeed;
	motor[motorC] = -turnSpeed;
}

void searchLeft(){
	motor[motorB] = -turnSpeed;
	motor[motorC] = turnSpeed;
}


/*void findLine(){
	clearTimer(T1);
	if((time1[T1] < searchTime) && (getColorName(S2) == colorWhite)){
		searchRight();
	}
	else if ((time1[T1] < searchTime) && (getColorName(S1) == colorWhite)){
		STP();
		sleep(200);
		searchLeft();
	}
}*/

void findLeft(){
	clearTimer(T1);
	STP();
	while((getColorName(S1) != colorWhite) && (getColorName(S2)== colorWhite)){
		searchLeft();
	}
	STP();
}
void findRight(){
	clearTimer(T1);
	STP();
	while((getColorName(S1) == colorWhite) && (getColorName(S2) != colorWhite)){
		searchRight();
	}
	STP();
}
//setproperties

void setUTurn(int x){
	uTurnValue=x;
}

void setSpeed(int x){
	speed=x;
}

void setTurnSpeed(int x){
	turnSpeed=x;
}

void setTurnValue(int x){
	vpointTurn=x;
}

void setWheelDiamter(float x){
	WheelDiamterCM=x;
}

void setWallDist(float x){
	WallDistCM=x;
}
