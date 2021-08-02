#ifndef LISTENER_HEADER_INCLUDED
#define LISTENER_HEADER_INCLUDED
#include <memory>
#include <boost/beast/core.hpp>

// Accepts incoming connections and launches the sessions
class listener : public std::enable_shared_from_this<listener>
{
    boost::asio::io_context& ioc_;
    boost::asio::ip::tcp::acceptor acceptor_;
    std::shared_ptr<std::string const> doc_root_;

public:
    listener(
        boost::asio::io_context& ioc,
        boost::asio::ip::tcp::endpoint endpoint,
        std::shared_ptr<std::string const> const& doc_root);
    void run();

private:
    void do_accept();

    void on_accept(boost::beast::error_code ec, boost::asio::ip::tcp::socket socket);
};

#endif
