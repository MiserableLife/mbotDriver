#include "object.h"
#include <thread>


ImageObject::ImageObject(int sec) : period(sec)
#if HASOCV
																		, cap(0)//open the default camera
#endif
{
#if HASOCV
	if(!cap.isOpened())
	{
		std::cerr<<"Camera is not available"<<std::endl;
		exit(-1);
	}
	cap>>frame;
	image_size = frame.total() * frame.elemSize();
#else
	image_size = 640*480*3;
#endif 
	buffer = new unsigned char[image_size];

}
ImageObject::~ImageObject()
{
	delete[] buffer;
}
void 
ImageObject::addObserver(Observer *o)
{
	observers.push_back( o);
}
void 
ImageObject::removeObserver(Observer* o )
{
//	observers.erase(e);
}
void 
ImageObject::process()
{
	while(true)
	{
		update();
//		for(auto& o : observers)
		for(std::vector<Observer*>::iterator it = observers.begin(); it!= observers.end(); )
			if((*it)->sendto(buffer, image_size) == -1)//if failed sento due to disconnection, we will erase it from the list
			{
				delete *it;
				it=observers.erase(it);
			}
			else
				it++;

		std::this_thread::sleep_for(period);
	}


}
void 
ImageObject::update()
{
#if HASOCV
	cap>>frame;
	memcpy(buffer , frame.data, image_size*sizeof(unsigned char));
#endif
}








