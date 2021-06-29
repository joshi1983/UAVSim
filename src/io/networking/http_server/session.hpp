#ifndef HTTP_SERVER_SESSION_HEADER_INCLUDED
#define HTTP_SERVER_SESSION_HEADER_INCLUDED
#include <memory>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>

// Handles an HTTP server connection
class session : public std::enable_shared_from_this<session>
{
    struct send_lambda
    {
        session& self_;

        explicit send_lambda(session& self);

        template<bool isRequest, class Body, class Fields>
        void
        operator()(boost::beast::http::message<isRequest, Body, Fields>&& msg) const;
    };

    boost::beast::tcp_stream stream_;
    boost::beast::flat_buffer buffer_;
    std::shared_ptr<std::string const> doc_root_;
    boost::beast::http::request<boost::beast::http::string_body> req_;
    std::shared_ptr<void> res_;
    send_lambda lambda_;

public:
    // Take ownership of the stream
    session(
        boost::asio::ip::tcp::socket&& socket,
        std::shared_ptr<std::string const> const& doc_root);
    // Start the asynchronous operation
    void run();

    void do_read();

    void on_read(
        boost::beast::error_code ec,
        std::size_t bytes_transferred);

    void on_write(
        bool close,
        boost::beast::error_code ec,
        std::size_t bytes_transferred);
    void do_close();
};

#endif
