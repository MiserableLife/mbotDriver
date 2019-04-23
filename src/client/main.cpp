


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

using boost::asio::ip::udp;

#define READ_PORT 921023

static void recv_print(boost::asio::io_service *io_service )
{
  boost::array<char, 128> recv_buf;
	udp::socket socket(*io_service);
	udp::endpoint sender_endpoint;
//	udp::endpoint recv_endpoint();
	socket.open(udp::v4());
	socket.bind(udp::endpoint(udp::v4(), READ_PORT	) );
//	socket.connect(*recv_endpoint);
//	std::cout<<"recv_print start , socket isopen? "<<socket.is_open()<<std::endl;
	while(true)
	{
		int len = socket.receive_from(  boost::asio::buffer(recv_buf), sender_endpoint);
		std::cout<<std::endl<<"msg received! size : "<< len <<std::endl;
		std::cout<<*(unsigned short*)recv_buf.data()<<std::endl;
		std::cout<<"cmd> ";

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
    udp::resolver::query query(udp::v4(), argv[1], "daytime");
    udp::endpoint receiver_endpoint = *resolver.resolve(query);

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
