#ifndef SINTOTH_WEB_SERVER_REQUEST_H
#define SINTOTH_WEB_SERVER_REQUEST_H

#include <string>
#include "RequestMethod.hpp"
#include <vector>
#include <sstream>
#include <regex>

class Request {
private:
    std::string route;
    RequestMethod method;
    std::vector<std::string> headers;
public:
    Request(const std::string& request);
    std::string getRoute();
    RequestMethod getMethod();
    std::vector<std::string> getHeaders();
};


#endif //SINTOTH_WEB_SERVER_REQUEST_H
