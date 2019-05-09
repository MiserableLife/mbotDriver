#include "udp_server.h"
#include <iostream>
#include <vector>
#include <thread>



UdpServer::UdpServer(boost::asio::io_service& io_service)
    : socket_(io_service, udp::endpoint(udp::v4(), COMMAND_PORT)), io_service_(io_service)
{
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
		if(cmd == "right")
		{
		}
		else if(cmd=="left")
		{
		}
		else if(cmd == "go")
		{
		}
		else if(cmd == "back")
		{

		}
		else
		{
			cmd = "nop";
		}
		std::cout<<cmd<<" has came!"<<std::endl;
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


