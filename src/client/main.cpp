


//
// client.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2016 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <unordered_map>
#include <thread>
#include "common.h"
#include "MBotPacket.h"
using boost::asio::ip::udp;



static void recv_print(boost::asio::io_service *io_service )
{
  unsigned char recv_buf[FRAGMENT_SIZE];
	udp::socket socket(*io_service);
	udp::endpoint sender_endpoint;
//	udp::endpoint recv_endpoint();
	socket.open(udp::v4());
	socket.bind( udp::endpoint(udp::v4(), CLIENT_READ_PORT	) );
//	socket.connect(*recv_endpoint);
	std::cout<<"recv_print start , socket isopen? "<<socket.is_open()<<std::endl;
	std::cout<<"Open port : "<<socket.local_endpoint().port()<<std::endl;
	FRAGMENT *fr{};
	std::unordered_map<int,MBotPacket> frmap;
	static int packet_next_id{};

	while(true)
	{
		int len = socket.receive_from(  boost::asio::buffer(recv_buf, FRAGMENT_SIZE),
			 															sender_endpoint);
		fr = (FRAGMENT*)recv_buf;

		MBotPacket& packet = frmap[fr->id];
		packet.add(fr, len);
//		std::cout<<"id ["<<fr->id<<"] , seq : "<<fr->seq<<" came!"<<std::endl;
		if(packet.assemble())
		{
			std::cout<<"id ["<<fr->id<<"] packet assembled!"<<std::endl;
			if(packet_next_id < fr->id )
			{
				std::cout<<"it comes faster than "<<packet_next_id<<"! , fixed to"<<fr->id<<std::endl;
				packet_next_id = fr->id + 1;
				//process
			}
			else if(packet_next_id > fr->id)
			{
				std::cout<<"it assembled too late! we are currently wating "<<packet_next_id<<", so drop "<<std::endl;

			}
			else
				packet_next_id ++; //&& process
			

		}
		
//		std::cout<<std::endl<<"msg received! size : "<< len <<std::endl;
		std::cout<<*(unsigned short*)recv_buf<<std::endl;

	}

}

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Usage: client <host>" << std::endl;
      return 1;
    }

    boost::asio::io_service io_service;

    udp::resolver resolver(io_service);
//    udp::resolver::query query(udp::v4(), argv[1], "daytime");
//    udp::endpoint receiver_endpoint(boost::asio::ip::make_address(argv[1]), SERVER_PORT); //= *resolver.resolve(query);
    udp::endpoint receiver_endpoint(boost::asio::ip::address::from_string(argv[1]), SERVER_PORT); //= *resolver.resolve(query);
		std::cout<<"SERVER_PORT : "<<SERVER_PORT<<std::endl;

    udp::socket socket(io_service);
    socket.open(udp::v4());

    boost::array<char, 128> send_buf {"register"};
    socket.send_to(boost::asio::buffer(send_buf), receiver_endpoint);
		std::cout<<"remote port : "<<receiver_endpoint.port()<<std::endl;
		std::cout<<"mylocal port : "<<socket.local_endpoint().port()<<std::endl;

    boost::array<char, 128> recv_buf;
    udp::endpoint sender_endpoint;

		std::thread t(recv_print,&io_service);
		t.detach();
		std::string cmd;
		while(true)
		{
			std::cin>>cmd;

//    boost::array<char, 128> send_buf {"register"};
			std::cout<<cmd<<" has been sent !"<<std::endl;
			socket.send_to(boost::asio::buffer(cmd), receiver_endpoint);
		}
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
