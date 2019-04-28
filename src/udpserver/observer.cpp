#include "observer.h"

#include <iostream>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include "common.h"
#include "MBotPacket.h"



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
Observer::sendto(unsigned char* buffer, unsigned int len, udp::endpoint& remote_endpoint_)
{
	static int id{};
	remote_endpoint_.port(CLIENT_READ_PORT);

	std::cout<<socket_.is_open()<<" " <<CLIENT_READ_PORT<<std::endl;

	std::cout<<"Observer("<<this<<")::send  contents : "<<buffer<<" sent..."<<std::endl;
	udp::endpoint ep = socket_.local_endpoint();
	std::cout<< " with my  port : "<<ep.port()<<std::endl;
	static unsigned char fragment[FRAGMENT_SIZE];
	std::cout<<"LEN_PAYLOAD : "<<LEN_PAYLOAD<<std::endl;
	unsigned int len_payload = (unsigned int)LEN_PAYLOAD;
	std::cout<<"len_payload : "<<len_payload<<std::endl;
	unsigned int num_fragment = len / len_payload;
	std::cout<<"num_fragment : "<<num_fragment<<std::endl;

/*
 * udp packet only can send 16bit length ( 2^16 byte length), so we should fragment in case of exceeding it. 
	< id(s), seq#(b), num_seq(b), payload  >. 
	in client, higher id packet is assembled faster than lower id packet, lower id packet is dropped. 

*/
	MBotPacket packet(buffer, len);
	FRAGMENT * fr = (FRAGMENT*)fragment;
	fr->id = id++;
	fr->len = len;
	unsigned char seq{0};
	for(; seq< num_fragment-1; seq++)
	{
		fr->seq = seq;
		packet.fragment(seq, len, fragment);
		socket_.send_to(boost::asio::buffer(fragment, FRAGMENT_SIZE), remote_endpoint_
			);
	}
	fr->seq = seq;
	packet.fragment(seq, FRAGMENT_SIZE, fragment);
	socket_.send_to(boost::asio::buffer(fragment, len%(LEN_PAYLOAD+1)), remote_endpoint_);

	std::cout<< "To  : "<<remote_endpoint_.address()<<" with port : "<<remote_endpoint_.port()<<std::endl;


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
