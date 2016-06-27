/*library tested 30 NOVEMBER
  Made by Deep Goel and Kartik Gupta
*/
#ifndef  MOTOR_H
#define  MOTOR_H
//
//(imp) motor will be considered cw if dir1 is HIGH and DIR2 is LOW
//


#ifndef COUNT_CONST 
#define COUNT_CONST 3

#endif //for COUNT_CONST
class Motor 
{
//    private:
		
	
	public:
// Variables
		
		int dir1_pin;					//stores pin no of direction1
		int dir2_pin;					//stores pin no of direction2
		int pwm_pin;					//stores pin no of pwm pin
		int dir1;		                //stores value of DIR1PIN as 1 or 0
		int dir2;                      //stores value of DIR2PIN as 1 or 0
		int pwm;						//pwm: Stores the pwm value given to the motor
		int mean_speed;					//mean_speed : The value to which motor moves when speed=100%
		float speed;					//speed		: Speed of the motor in percentage of meanspeed
		int damping;                 //to be changed later by trial
		
// Functions
     public:	
		Motor();						//constructor
		Motor(int Dir1,int Dir2,int Pwm);	//constructor with attachments of pins
		void attachMotor(int Dir1,int Dir2,int Pwm); //attachments of pins
		void moveMotor(int Pwm);			//+ve for CW and -ve for CCW.
        void moveMotor(int Dir1,int Dir2,int Pwm); // dir1 and dir2 can be 1 or 0,pwm can only be +ve for CW
		void stopMotor();				//By default stop motor will lock motor
        void lockMotor();				//To lock the motor
		void freeMotor();				//Free the motor
		void setMeanSpeed(int Speed);	//Sets the meanspeed with which motor moves when speed=100%	
		void setMotorSpeed(int Speed);		//+ve for CW and -ve for CCW. Speed in percentage of meanspeed
		void setMotorSpeed(int Dir1,int Dir2,int Speed); // dir1 and dir2 can be 1 or 0
		void changePWM(int Pwm);		//Just to change the PWM in whatever direction the motor was moving
		void changeSpeed(int Speed);	//Just to change the speed (In percentage) not the direction
		int getDirection();             //+1 for cw and -1 for ccw and 0 for free or locked
		int isFree();                  //+1 for free and 0 for not free
		int isLocked();                //+1 for locked and 0 for not locked
		int getSpeed();                // returns speed in % of mean speed
		int getPWM();                  // returns +ve for CW and -ve for CCW.
	    void startSmoothly(int Speed);   //+ve for CW and -ve for CCW.
		void stopSmoothly();
};		
#endif
