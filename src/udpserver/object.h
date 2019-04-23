#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "observer.h"
#include <unordered_map>
#include <chrono>
#include <vector>
#include <boost/array.hpp>

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
	std::unordered_map<udp::endpoint*, Observer*> observers;
	std::chrono::seconds period;
	boost::array<char,128> buffer;

public:
	ImageObject(int sec);
	void addObserver(udp::endpoint* e,  Observer *o);
	void removeObserver(udp::endpoint* e );
	void process();
	void update();

};





#endif

