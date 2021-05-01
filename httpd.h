#ifndef SINTOTH_WEB_SERVER_HTTPD_H
#define SINTOTH_WEB_SERVER_HTTPD_H

#include <string>
#include "request/Request.h"

class httpd {
public:
    static void start();
    static std::string handle(Request request);
};


#endif //SINTOTH_WEB_SERVER_HTTPD_H
