#ifndef HTTP_SERVER_FAIL_HEADER_INCLUDED
#define HTTP_SERVER_FAIL_HEADER_INCLUDED
#include <boost/beast/core.hpp>

void fail(boost::beast::error_code ec, char const* what);

#endif