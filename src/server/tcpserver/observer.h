#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include <boost/asio.hpp>
using boost::asio::ip::tcp;

class Observer
{
private:
	tcp::socket socket_;

	enum{cmd_max_length=1024};
	char cmd_buffer[cmd_max_length];

	
public:
	Observer(tcp::socket socket);
	void handle_cmd(const boost::system::error_code& ec, std::size_t length);

	int handshake();
	int sendto(unsigned char* buffer, unsigned int len);


	void handle_send();
};


#endif
