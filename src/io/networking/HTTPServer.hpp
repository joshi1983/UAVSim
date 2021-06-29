#ifndef UAV_HTTP_SERVER_HEADER_INCLUDED
#define UAV_HTTP_SERVER_HEADER_INCLUDED
#include <string>
#include "../../models/animation/DefaultAnimation.hpp"

void startHttpServer(unsigned short port, std::string docRoot, DefaultAnimation & animation);

#endif
