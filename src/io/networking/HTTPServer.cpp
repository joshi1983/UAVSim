#include "HTTPServer.hpp"

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/strand.hpp>
#include <boost/config.hpp>
#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>
#include "http_server/session.hpp"
#include "http_server/listener.hpp"
#include "../config/Config.hpp"

namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>


//------------------------------------------------------------------------------

void runServer(unsigned short port, std::string docPath)
{
    auto const address = net::ip::make_address("0.0.0.0");
    auto const doc_root = std::make_shared<std::string>(docPath.c_str());
    auto const threads = std::max<int>(1, 1);

    // The io_context is required for all I/O
    net::io_context ioc{threads};

    // Create and launch a listening port
    std::make_shared<listener>(
        ioc,
        tcp::endpoint{address, port},
        doc_root)->run();

    // Run the I/O service on the requested number of threads
    std::vector<std::thread> v;
    v.reserve(threads - 1);
    for(auto i = threads - 1; i > 0; --i)
        v.emplace_back(
        [&ioc]
        {
            ioc.run();
        });
    std::cout << "running HTTP server available at http://localhost:" << port << std::endl;
    ioc.run();
}

unsigned short getHttpServerPort()
{
	return UAVSimConfig::config.getDefaultedInt("/httpServer/port", 8080);
}

void startHttpServer(std::string docPath, DefaultAnimation & animation)
{
    // call runHttpServer in a separate thread.
    new std::thread(&runServer, getHttpServerPort(), docPath);
}
