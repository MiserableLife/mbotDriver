#include "observer.h"

#include <iostream>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include "common.h"
#include "MBotPacket.h"



Observer::Observer(tcp::socket socket) 
	: socket_(std::move(socket))
{
	
}
int
Observer::handshake()
{
	return 1; // always return true 
}
void 
Observer::handle_cmd(const boost::system::error_code& ec, std::size_t length)
{
	std::string cmd = cmd_buffer;

	socket_.async_read_some(boost::asio::buffer(cmd_buffer,cmd_max_length), 
			boost::bind(&Observer::handle_cmd, this,
      boost::asio::placeholders::error,
      boost::asio::placeholders::bytes_transferred));



}

int 
Observer::sendto(unsigned char* buffer, unsigned int len)
{
	static int i{};
	buffer[0]=i++;
	int size{};
	try
	{
		size = socket_.send(boost::asio::buffer(buffer, len));
	}
	catch(boost::system::system_error ec)
	{
		std::cout<<ec.what()<<std::endl;
		std::cout<<ec.code().value()<<std::endl;
		if(ec.code().value() == EPIPE)
			return -1;

	}
	std::cout<<"send to called! ( "<<size<<" ) "<<std::endl;
	return 0;
//	std::cout<< "To  : "<<remote_endpoint_.address()<<" with port : "<<remote_endpoint_.port()<<std::endl;


}/*
unsigned short 
Observer::port()
{
	return socket_.local_endpoint().port();
}*/
void 
Observer::handle_send()
{
	std::cout<<"Observer("<<this<<") sending completed"<<std::endl;
}
