#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#include "../stringUtils.hpp"

using namespace std;
namespace beast = boost::beast;     // from <boost/beast.hpp>
namespace http = beast::http;       // from <boost/beast/http.hpp>
namespace net = boost::asio;        // from <boost/asio.hpp>
using tcp = net::ip::tcp;           // from <boost/asio/ip/tcp.hpp>

bool parseUrl(const string& url, string & protocol, string & domain, string & port, string & requestPath)
{
    string path,x,query;
    int offset = 0;
    size_t pos1,pos2,pos3,pos4;
    x = trim(url);
    offset = offset==0 && x.compare(0, 8, "https://")==0 ? 8 : offset;
    offset = offset==0 && x.compare(0, 7, "http://" )==0 ? 7 : offset;
    pos1 = x.find_first_of('/', offset+1 );
    path = pos1==string::npos ? "" : x.substr(pos1);
    domain = string( x.begin()+offset, pos1 != string::npos ? x.begin()+pos1 : x.end() );
    path = (pos2 = path.find("#"))!=string::npos ? path.substr(0,pos2) : path;
    port = (pos3 = domain.find(":"))!=string::npos ? domain.substr(pos3+1) : "";
    domain = domain.substr(0, pos3!=string::npos ? pos3 : domain.length());
    protocol = offset > 0 ? x.substr(0,offset-3) : "";
    query = (pos4 = path.find("?"))!=string::npos ? path.substr(pos4+1) : "";
    path = pos4!=string::npos ? path.substr(0,pos4) : path;
    requestPath = path;
    if (query != "")
        requestPath += string("?") + query;
    if (port == "")
    {
        if (protocol == "http")
            port = "80";
        else
            port = "443";
    }
    return true;
}

void downloadToFile(const std::string & url, const std::string & filename)
{
    string port = "80";
    string host = "www.technocrazed.com";
    string target = "/wp-content/uploads/2015/12/beautiful-wallpaper-download-13.jpg";
    string protocol;
    if (!parseUrl(url, protocol, host, port, target))
    {
        cerr << "Unable to download from URL because it is invalid.  URL: " << url << endl;
        throw exception();
    }
    cout << "protocol = " << protocol << endl;
    cout << "port = " << port << endl;
    cout << "host = " << host << endl;
    cout << "target = " << target << endl;

    const int version = 10;
     // The io_context is required for all I/O
        net::io_context ioc;
        // These objects perform our I/O
        tcp::resolver resolver(ioc);
        beast::tcp_stream stream(ioc);
  // Look up the domain name
        auto const results = resolver.resolve(host, port);
        //socket_.set_verify_mode(boost::asio::ssl::context::verify_none);

        // Make the connection on the IP address we get from a lookup
        stream.connect(results);

 // Set up an HTTP GET request message
        http::request<http::string_body> req{http::verb::get, target, version};
        req.set(http::field::host, host);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

        // Send the HTTP request to the remote host
        http::write(stream, req);

        // This buffer is used for reading and must be persisted
        beast::flat_buffer buffer;

         // Declare a container to hold the response
        http::response<http::dynamic_body> res;

        // Receive the HTTP response
        http::read(stream, buffer, res);

        // Write the message to standard out
        std::cout << res << std::endl;

        // Gracefully close the socket
        beast::error_code ec;
        stream.socket().shutdown(tcp::socket::shutdown_both, ec);

        // not_connected happens sometimes
        // so don't bother reporting it.
        //
        if(ec && ec != beast::errc::not_connected)
            throw beast::system_error{ec};

	//URLDownloadToFile(NULL, url.c_str(), filename.c_str(), 0, NULL);
}
