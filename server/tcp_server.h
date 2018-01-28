#ifndef PROJECT_TCP_SERVER_H
#define PROJECT_TCP_SERVER_H


#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include "tcp_connection.h"
#include "chat_room.h"

using boost::asio::ip::tcp;

class chat_server
{
public:
    chat_server(boost::asio::io_service& io_service,
                const tcp::endpoint& endpoint)
            : io_service_(io_service),
              acceptor_(io_service, endpoint)
    {
        start_accept();
    }

    void start_accept()
    {
        chat_session_ptr new_session(new chat_session(io_service_, room_));
        acceptor_.async_accept(new_session->socket(),
                               boost::bind(&chat_server::handle_accept, this, new_session,
                                           boost::asio::placeholders::error));
    }

    void handle_accept(chat_session_ptr session,
                       const boost::system::error_code& error)
    {
        if (!error)
        {
            session->start();
        }

        start_accept();
    }

private:
    boost::asio::io_service& io_service_;
    tcp::acceptor acceptor_;
    chat_room room_;
};

typedef boost::shared_ptr<chat_server> chat_server_ptr;

#endif //PROJECT_TCP_SERVER_H
