#include "Request.h"

/**
*
    Request(std::string request);
    std::string getRoute();
    RequestMethod getMethod();
    std::vector<std::string> getHeaders();
*/

Request::Request(const std::string& request) {
    std::stringstream request_stream(request);
    std::string segment;
    std::string buffer;

    while(std::getline(request_stream, segment, '\n')) {
        if(segment.rfind("GET", 0) == 0) {
            this->method = RequestMethod::GET;
            buffer = std::regex_replace(segment, std::regex("\\GET "), "");
            buffer = std::regex_replace(buffer, std::regex(" HTTP\\/([0-9]\\.[0-9])"), "");
            this->route = buffer;
        } else {
            this->headers.push_back(segment);
        }
    }
}

std::string Request::getRoute() {
    return this->route;
}

RequestMethod Request::getMethod() {
    return this->method;
}

std::vector<std::string> Request::getHeaders() {
    return this->headers;
}