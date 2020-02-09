#include "tcp_server.h"
#include <iostream>
#include <vector>
#include <thread>





	
/*
void 
Session::do_write(std::size_t length)
{
	auto self(shared_from_this());
boost::asio::async_write(socket_, boost::asio::buffer(data_, length),
			[this, self](boost::system::error_code ec, std::size_t )
			{
				if(!ec)
					do_read();
			});
	std::cout<<"Session ref count : " << self.use_count()<<" do_write()"<<std::endl;

}
*/
  
TcpServer::TcpServer(boost::asio::io_service& io_service, short port)
	: acceptor_(io_service, tcp::endpoint(tcp::v4(), port)), io(PERIOD), socket_(io_service)
{
	std::thread t(&ImageObject::process, &io);
	t.detach();
	do_accept();
}

void 
TcpServer::do_accept()//just accept and make a session
{
	acceptor_.async_accept(socket_,
			[this](boost::system::error_code ec)//lambda handler
			{
			std::cout<<"accept called!"<<std::endl;
			std::cout<<"client addr : "<<socket_.remote_endpoint().address()<<" port : "<<socket_.remote_endpoint().port()<<std::endl;
				if(!ec)
				{
				std::cout<<"no err"<<std::endl;
					Observer* o = new Observer(std::move(socket_));
					int result = o->handshake();
					if(result)
					{
						io.addObserver(o);
					}
					else
						delete o;

				//std::make_shared<Session>(std::move(socket))->start();
				}
				do_accept();//accept for next connection
			});

}







