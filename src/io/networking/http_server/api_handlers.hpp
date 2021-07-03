#ifndef HTTP_SERVER_API_HANDLER_HEADER_INCLUDED
#define HTTP_SERVER_API_HANDLER_HEADER_INCLUDED
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>

bool isAPITarget(const boost::beast::string_view &target);
std::string handleAPIGetRequest(const boost::beast::string_view &target);
std::string handleAPIPostRequest(const boost::beast::string_view &target, const boost::beast::string_view &body);

#endif
