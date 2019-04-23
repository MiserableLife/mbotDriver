#include "observer.h"

#include <iostream>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include "common.h"




Observer::Observer(boost::asio::io_service& io_service) 
	: socket_(io_service)
{
//std::cout<<"observer "<<this<<" with socket"<<socket_<<std::endl;
	boost::system::error_code ec;
	socket_.open(udp::v4(), ec);
	if(ec)
	{
		std::cout<<"error opening socket..."<<ec<<std::endl;
	}
//		std::shared_ptr<std::string> dum(new std::string);
//		socket_.send_to(boost::asio::buffer(*dum), remote_endpoint_);
		
}
void 
Observer::sendto(unsigned char* buffer, int len, udp::endpoint& remote_endpoint_)
{
	remote_endpoint_.port(CLIENT_READ_PORT);

	std::cout<<socket_.is_open()<<" " <<CLIENT_READ_PORT<<std::endl;

	std::cout<<"Observer("<<this<<")::send  contents : "<<buffer<<" sent..."<<std::endl;
	udp::endpoint ep = socket_.local_endpoint();
	std::cout<< " with port : "<<ep.port()<<std::endl;
	socket_.async_send_to(boost::asio::buffer(buffer, len), remote_endpoint_,
			boost::bind(&Observer::handle_send, this)
			);


}
unsigned short 
Observer::port()
{
	return socket_.local_endpoint().port();
}
void 
Observer::handle_send()
{
	std::cout<<"Observer("<<this<<") sending completed"<<std::endl;
}
