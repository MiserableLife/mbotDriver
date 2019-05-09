#pragma once

#include <boost/asio.hpp>
#include "common.h"
using boost::asio::ip::tcp;
using boost::asio::ip::udp;

class Client
{
private:
//	boost::asio::io_service& io_service;
	unsigned char recv_buf[IMAGE_SIZE];
	unsigned char image[IMAGE_SIZE];
	tcp::socket socket;
	udp::socket cmd_sock;
	std::function<void(unsigned char*)> handler;


	int handshake();
public:
	Client(boost::asio::io_service& io_context, const tcp::endpoint& e, std::function<void(unsigned char*)>& h);
	void handle_recv(boost::system::system_error ec, std::size_t len);
	void send_cmd(const std::string& cmd, const udp::endpoint& e);
	void send_cmd(const int& cmd, const udp::endpoint& e);

	



};
