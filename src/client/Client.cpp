#include <iostream>
#include <boost/bind.hpp>

#include "Client.h"
int 
Client::handshake()
{
	return 1;
}


Client::Client(boost::asio::io_service& io, const tcp::endpoint& e, std::function<void(unsigned char*)>& h) : 
//	io_service(io), 
	socket(io), 
	cmd_sock(io),
	handler(h)
{
	cmd_sock.open(udp::v4());
	tcp::resolver resolver(io);
	boost::asio::connect(socket, resolver.resolve(e));

	int result = handshake();
	if(result)
	{
		socket.async_read_some(boost::asio::buffer(recv_buf, IMAGE_SIZE), 
														boost::bind(&Client::handle_recv, this, 
															boost::asio::placeholders::error,
															boost::asio::placeholders::bytes_transferred));
	}

}
void 
Client::handle_recv(boost::system::system_error ec, std::size_t len)
{
	static int pos{0};
	if(pos + len > IMAGE_SIZE)
	{
		assert(!"what!? it cannot be....");
	}
	else if(pos+len == IMAGE_SIZE)
	{
		pos =0; 
		std::cout<<"image[0] : "<<(int)image[0]<<std::endl;
	}
	else
	{
		memcpy(image + pos, recv_buf, len);
		pos += len;
	}
	handler(image);

	socket.async_read_some(boost::asio::buffer(recv_buf, IMAGE_SIZE),
														boost::bind(&Client::handle_recv, this, 
															boost::asio::placeholders::error,
															boost::asio::placeholders::bytes_transferred));

}

void 
Client::send_cmd(const std::string& cmd, const udp::endpoint& e)
{
	cmd_sock.send_to(boost::asio::buffer(cmd), e);
}
void
Client::send_cmd(const int& cmd, const udp::endpoint& e)
{
	cmd_sock.send_to(boost::asio::buffer((char*)&cmd , sizeof(int)), e);
}



