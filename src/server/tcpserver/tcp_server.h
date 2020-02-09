#pragma onece

#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <ctime>
#include <string>
#include <iostream>
#include "common.h"
#include "logger.h"
#include "object.h"

using boost::asio::ip::tcp;



class TcpServer
{
public:
  TcpServer(boost::asio::io_service& io_service, short port);

private:
	void do_accept();//just accept and make a session

  void handle_receive(const boost::system::error_code& error,
      std::size_t /*bytes_transferred*/);
  
  void handle_send(boost::array<char,128>& /*message*/,
      const boost::system::error_code& /*error*/,
      std::size_t /*bytes_transferred*/);

	ImageObject io;

	tcp::socket socket_;
/*
  tcp::endpoint remote_endpoint_;
  boost::array<char, 128> recv_buffer_;
	boost::asio::io_service& io_service_;
*/
	
	tcp::acceptor acceptor_;
};



