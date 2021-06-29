#ifndef PATH_CAT_HEADER_INCLUDED
#define PATH_CAT_HEADER_INCLUDED
#include <string>
#include <boost/beast/core.hpp>

std::string path_cat(boost::beast::string_view base, boost::beast::string_view path);

#endif