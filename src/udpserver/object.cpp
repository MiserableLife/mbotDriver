#include "object.h"
#include <thread>




ImageObject::ImageObject(int sec) : period(sec), cap(0)//open the default camera
{
	if(!cap.isOpened())
	{
		std::cerr<<"Camera is not available"<<std::endl;
		exit(-1);
	}
	cap>>frame;
	image_size = frame.total() * frame.elemSize();
	buffer = new unsigned char[image_size];

}
ImageObject::~ImageObject()
{
	delete[] buffer;
}
void 
ImageObject::addObserver(udp::endpoint* e,  Observer *o)
{
	observers[e] = o;
}
void 
ImageObject::removeObserver(udp::endpoint* e )
{
	observers.erase(e);
}
void 
ImageObject::process()
{
	while(true)
	{
		update();
		for(auto& o : observers)
			o.second->sendto(buffer, image_size, *o.first);

		std::this_thread::sleep_for(period);
	}


}
void 
ImageObject::update()
{
	cap>>frame;
	memcpy(buffer , frame.data, image_size*sizeof(unsigned char));
}








