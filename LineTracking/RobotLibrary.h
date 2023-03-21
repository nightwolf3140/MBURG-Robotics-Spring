int m =1; //Motor Vector
//int uTurn = ?;
//int pointTurn = ?;

void move(char direction){
	if(direction) == 'f'{
		m=1;
	}
	if(direction) == 'b'{
		m=1;
	}
}

void uTurn(){
	rsMotors();
	//setMotorTarget(motorB, 

}

void rsMotors(){
	resetMotorEncoder(motorB);
	resetMotorEncoder(motorC);
}
void pointTurn(char direction){
	
	if(direction) == 'l'{ //Turn Left
		rsMotors();
	}
	
	if(direction) == 'r'{//Turn right
		rsMotors();
	}
}
