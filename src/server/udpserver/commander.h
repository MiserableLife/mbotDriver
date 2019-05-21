#pragma once

#include "common.h"


enum
{
	MAX_DEGREE = 70,
	MIN_DEGREE = -MAX_DEGREE,
	MAX_SPEED = 50,
	MIN_SPEED = -MAX_DEGREE
};
enum
{
	UNIT_SPEED=5,
	UNIT_ROTATE=5
};
enum
{
	BACK=0x10,
	GO=0x1,
	RIGHT=0xF0,
	LEFT=	0x0F,
	CLEAR=0x77
};



class Commander
{
protected:
	int speed;
	bool run;
	
	double wheel_degree;
	char speed_changed;
	char wheel_changed;

public:
	Commander();
	virtual int start();
	virtual int handle()=0;
	
	virtual int command(int key);

};

class PlaneCommander : public Commander
{
public:


	virtual int handle();

};


class MbotCommander : public Commander
{
public:
	char* make_command(short leftspeed, short rightspeed);

	virtual int handle();

};
