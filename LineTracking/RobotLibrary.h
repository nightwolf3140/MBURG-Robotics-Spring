int m = 1; //Motor Vector
int uTurn = 340;
int vpointTurn = 170;
int speed = 5*m;
int turnSpeed = 15*m;
int lineWidthCM = 1.8;
float WheelDiamterCM = 5.6; //Stock ev3

//throw functions below
void rsMotors(){
	resetMotorEncoder(motorB);
	resetMotorEncoder(motorC);
}

void forwards(){ //default
	rsMotors();
	motor[motorB] = speed;
	motor[motorC] = speed;
}
void forwards(int x){ //controled speed
	rsMotors();
	motor[motorB] = x;
	motor[motorC] = x;
}

void uturn(){
	rsMotors();
	setMotorTarget(motorB,uTurn,50);
	setMotorTarget(motorC,-uTurn,50);
}

void leftPointTurn(){
	rsMotors();
	setMotorTarget(motorB,vpointTurn,turnSpeed);
	setMotorTarget(motorC,-vpointTurn,turnSpeed);
}

void rightPointTurn(){
	rsMotors();
	setMotorTarget(motorB,-vpointTurn,turnSpeed);
	setMotorTarget(motorC,vpointTurn,turnSpeed);
}

void STP(){
	rsMotors();
	motor[motorB] = 0;
	motor[motorC] = 0;
}

/*float convertEncoderToCM(int encoderCounts){
	return(encoderCounts / 360.0)*(WheelDiamterCM * PI);
}*/

float convertCMToDegrees(int CM){
	return(CM/(WheelDiamterCM*PI)*360);
}

void moveCM(int cm){
	float x;
	rsMotors();
	x=convertCMToDegrees(cm);
	setMotorTarget(motorB, x, speed);
	setMotorTarget(motorC, x, speed);
	waitUntilMotorStop(motorB);
}

void leftNudge(){
	STP();
	rsMotors();
	setMotorTarget(motorC, 25, 15);
	waitUntilMotorStop(motorC);
}

void rightNudge(){
	STP();
	rsMotors();
	setMotorTarget(motorB, 25, 15);
	waitUntilMotorStop(motorB);
}
//setproperties

void setUTurn(int x){
	uTurn=x;
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
