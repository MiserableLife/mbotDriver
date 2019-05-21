#include "commander.h"
#include <thread>
#include <iostream>
#include <cmath>

Commander::Commander() : speed(0), wheel_degree(0), run(false)
{
}
int 
Commander::start()
{
	if(run)
		return run;

	run=true;
	std::thread t{
		[this]()
		{


			while(run)
			{
				handle();
				wheel_changed=0;
				speed_changed=0;
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}
		
		}
	
	};
	t.detach();

	return 0;


}
	
int 
Commander::command(int key)
{
	switch(key)
	{
	case KEY_RIGHT:
		wheel_changed++;
		break;
	case KEY_LEFT:
		wheel_changed--;
		break;
	case KEY_DOWN:
		speed_changed--;
		break;
	case KEY_UP:
		speed_changed++;
		break;
	default:
		std::cout<<"invalid key came! key : "<< key<<std::endl;

	}
	return 0;
	
}




int 
PlaneCommander::handle()
{

	if(wheel_changed>0)
		wheel_degree += UNIT_ROTATE;
	else if(wheel_changed<0)
		wheel_degree -= UNIT_ROTATE;
	else
		wheel_degree ? wheel_degree -= wheel_degree/std::abs(wheel_degree) * UNIT_ROTATE : 
			wheel_degree=0;
	if(speed_changed > 0)
		speed += UNIT_SPEED;
	else if(speed_changed < 0 )
		speed -= UNIT_SPEED;
	else
		 speed ? speed -= speed/std::abs(speed) * UNIT_SPEED :
		 speed=	0;

	if(wheel_degree < MIN_DEGREE)
		wheel_degree = MIN_DEGREE;
	else if(wheel_degree > MAX_DEGREE)
		wheel_degree = MAX_DEGREE;
	if(speed < MIN_SPEED)
		speed = MIN_SPEED;
	else if(speed > MAX_SPEED)
		speed = MAX_SPEED;

	std::cout<<" wheel degree : "<<wheel_degree << " speed : "<<speed<<std::endl;

	return 0;
}	




/*  
 *  0xff 0x55 len [len bytes]
 * ff 55 7 0 2 5 [leftspeed(2byte)] [rightspeed(2byte)]; wheel 7byte
 * ff 55 len 0 2 10 port [speed(2byte)]; speed [ i think it controls only one wheel ] 
 * ff 55 len idx action device port slot data a
 * 0  1  2   3   4      5      6    7    8
 *  */
#define LEFTSPEED(x) *(short*)(x + 6)
#define RIGHTSPEED(x) *(short*)(x + 8)
static const double pi = std::acos(-1);
char* 
MbotCommander::make_command(short leftspeed, short rightspeed)
{
	char* command = new char[11]{ (char)0xff,(char)0x55,
															7,//len
															0,
															2,
															5,0
															};
	LEFTSPEED(command) = leftspeed;
	RIGHTSPEED(command) = rightspeed;
	return command;
}
int 
MbotCommander::handle()
{
	if(wheel_changed>0)
		wheel_degree += UNIT_ROTATE;
	else if(wheel_changed<0)
		wheel_degree -= UNIT_ROTATE;
	else
		wheel_degree = wheel_degree/wheel_degree * UNIT_ROTATE;
	if(speed_changed > 0)
		speed += UNIT_SPEED;
	else if(speed_changed < 0 )
		speed -= UNIT_SPEED;
	else
		speed = speed/speed * UNIT_SPEED;

	if(wheel_degree < MIN_DEGREE)
		wheel_degree = MIN_DEGREE;
	else if(wheel_degree > MAX_DEGREE)
		wheel_degree = MAX_DEGREE;
	if(speed < MIN_SPEED)
		speed = MIN_SPEED;
	else if(speed > MAX_SPEED)
		speed = MAX_SPEED;

	std::unique_ptr<char> cmd {  make_command(speed - 
			10/std::tan( (0.5-wheel_degree/180)*pi )
			, speed) };
	
	

	std::cout<<" wheel degree : "<<wheel_degree <<"(a : "<< 
		(0.5-wheel_degree/180)*pi 
		<<")  speed : "<<speed<<std::endl;

	return 0;
}

