#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include <boost/asio.hpp>
using boost::asio::ip::udp;

class Observer
{
private:
	udp::socket socket_;

	
public:
	Observer(boost::asio::io_service& io_service);

	void sendto(boost::array<char,128>& buffer, udp::endpoint& e);

	unsigned short port();

	void handle_send();
};


#endif
