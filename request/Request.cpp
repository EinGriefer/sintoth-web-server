#include "Request.hpp"

/**
*
    Request(std::string request);
    std::string getRoute();
    RequestMethod getMethod();
    std::vector<std::string> getHeaders();
*/

bool replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

Request::Request(const std::string& request) {
    std::stringstream request_stream(request);
    std::string segment;
    std::string buffer;

    while(std::getline(request_stream, segment, '\n')) {
        if(segment.rfind("GET", 0) == 0) {
            this->method = RequestMethod::GET;
            replace(segment, "GET ", "");
            replace(segment, " HTTP/1.1", "");
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