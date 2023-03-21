int m =1; //Motor Vector
int uTurn = 340;
int vpointTurn = 170;

//throw functions below
void rsMotors(){
	resetMotorEncoder(motorB);
	resetMotorEncoder(motorC);
}

void Go(char direction){
	int speed=5*m;
	if ((direction)=='f'){
		rsMotors();
		setMotorTarget(motorB,m,speed);
		setMotorTarget(motorC,m,speed);
	}
	if ((direction)=='b'){
		m=-1;
		setMotorTarget(motorB,m,speed);
		setMotorTarget(motorC,m,speed);
	}
}

void uturn(){
	rsMotors();
	setMotorTarget(motorB,uTurn,50);
	setMotorTarget(motorC,-uTurn,50);
}

void pointTurn(char direction){
	if ((direction)=='l'){ //Turn Left
		rsMotors();
		setMotorTarget(motorB,vpointTurn,30);
		setMotorTarget(motorC,-vpointTurn,30);
	}

	if ((direction)=='r'){//Turn right
		rsMotors();
		setMotorTarget(motorB,-vpointTurn,30);
		setMotorTarget(motorC,vpointTurn,30);
	}
}

void stp(){
	rsMotors();
	setMotorTarget(motorB,0,0);
	setMotorTarget(motorC,0,0);
}
