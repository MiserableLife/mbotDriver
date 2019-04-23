#include "udp_server.h"
#include <iostream>
#include <vector>
#include <thread>



UdpServer::UdpServer(boost::asio::io_service& io_service)
    : socket_(io_service, udp::endpoint(udp::v4(), SERVER_PORT)), io_service_(io_service), io(PERIOD)
{
	std::thread t(&ImageObject::process,&io);
	t.detach();	
  start_receive();
}

void
UdpServer::start_receive()
{
  socket_.async_receive_from(//listen in the backgound for a new request. when request comes, ioservice object will invoke handle_recieve ( callback) 
      boost::asio::buffer(recv_buffer_), remote_endpoint_,
      boost::bind(&UdpServer::handle_receive, this,
      boost::asio::placeholders::error,
      boost::asio::placeholders::bytes_transferred));
}

void 
UdpServer::handle_receive(const boost::system::error_code& error,
		std::size_t /*bytes_transferred*/len)
{
	if (!error || error == boost::asio::error::message_size)
	{
		std::string cmd {recv_buffer_.data()};
		if(cmd.length() > len)
			cmd.resize(len);
		std::cout<<cmd<<" has came ! len : " <<len<<std::endl ;
		if(cmd == "register")
		{
			boost::asio::ip::address client_addr=remote_endpoint_.address();
			unsigned short client_port = remote_endpoint_.port();
			std::cout<<"client addr : "<<client_addr<<" client port : "<<client_port<<std::endl;
			io.addObserver( new udp::endpoint(remote_endpoint_), 
					new Observer(io_service_) );
			/*
			unsigned short p = o.port();
			memcpy(buffer.data(), &p, sizeof(unsigned short));
			std::cout<<std::hex<<(unsigned char)buffer[0]<<(unsigned char)buffer[1]<<std::endl;
			socket_.async_send_to(boost::asio::buffer(buffer), remote_endpoint_,
				boost::bind(&UdpServer::handle_send, this, buffer,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));

*/

		}
		else if(cmd == "right")
		{
			std::cout<<"AddRef"<<std::endl;
		}
		else if(cmd=="left")
		{
			std::cout<<"Release"<<std::endl;
		}
//		boost::shared_ptr<std::string> message(
//				new std::string(make_daytime_string()));

//		socket_.async_send_to(boost::asio::buffer(*message), remote_endpoint_,
//				boost::bind(&UdpServer::handle_send, this, message,
//					boost::asio::placeholders::error,
//					boost::asio::placeholders::bytes_transferred));

		start_receive();
	}
}

void 
UdpServer::handle_send(boost::array<char,128>& /*message*/,
		const boost::system::error_code& /*error*/,
		std::size_t /*bytes_transferred*/)
{
}


