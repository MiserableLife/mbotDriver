#include "object.h"



ImageObject::ImageObject(int sec) : period(sec)
{
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
			o.second->sendto(buffer, *o.first);

		std::this_thread::sleep_for(period);
	}


}
void 
ImageObject::update()
{
}








