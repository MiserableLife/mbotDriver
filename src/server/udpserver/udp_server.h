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
#include "commander.h"

using boost::asio::ip::udp;





class UdpServer
{
public:
  UdpServer(boost::asio::io_service& io_service);
	~UdpServer();
private:
  void start_receive();

  void handle_receive(const boost::system::error_code& error,
      std::size_t /*bytes_transferred*/);
  
  void handle_send(boost::array<char,128>& /*message*/,
      const boost::system::error_code& /*error*/,
      std::size_t /*bytes_transferred*/);

  udp::socket socket_;
  udp::endpoint remote_endpoint_;
  boost::array<char, 128> recv_buffer_;
	boost::asio::io_service& io_service_;
	Commander* commander;
};



