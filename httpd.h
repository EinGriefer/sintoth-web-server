#ifndef SINTOTH_WEB_SERVER_HTTPD_H
#define SINTOTH_WEB_SERVER_HTTPD_H

#include <string>

class httpd {
public:
    static void start();
    static std::string handle();
};


#endif //SINTOTH_WEB_SERVER_HTTPD_H
