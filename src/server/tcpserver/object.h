#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "observer.h"
#include <unordered_map>
#include <chrono>
#include <vector>
#include <boost/array.hpp>

#define HASOCV 0
#if HASOCV
#include <opencv2/opencv.hpp>
#endif


class Object
{
private:
public:
	virtual void process()=0;
	virtual void update()=0;

};


class ImageObject : public Object
{
private:
	std::vector<Observer*> observers;
	std::chrono::seconds period;
#if HASOCV
	cv::VideoCapture cap;
	cv::Mat frame;
#endif
	int image_size;

	unsigned char *buffer;
//	boost::array<char,128> buffer;

public:
	ImageObject(int sec);
	~ImageObject();
	void addObserver( Observer *o);
	void removeObserver(Observer* o );
	virtual void process();
	virtual void update();

};
/*
class mBotObject : public Object
{
private:
	enum{COMMAND_BACK=-2, COMMAND_LEFT, COMMAND_NOP, COMMAND_RIGHT, COMMAND_GO};
	int cmd;
public:
	void setCommand(int c)
	{
		cmd = c;
	}
	int getCommand()
	{
		return cmd;
	}
	virtual void process()
	{
		while(true)
		{
			update();
			cmd 


			

		}
	}
	virtual void update()
	{
	}


};
*/




#endif

