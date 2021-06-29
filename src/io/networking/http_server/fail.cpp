#include "fail.hpp"
#include <iostream>

namespace beast = boost::beast; // from <boost/beast.hpp>

// Report a failure
void fail(beast::error_code ec, char const* what)
{
    std::cerr << what << ": " << ec.message() << "\n";
}