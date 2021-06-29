#ifndef MIME_TYPES_HEADER_INCLUDED
#define MIME_TYPES_HEADER_INCLUDED
#include <boost/beast/core.hpp>

boost::beast::string_view mime_type(boost::beast::string_view path);

#endif
