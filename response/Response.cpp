#include "Response.hpp"

#include <utility>

std::string Response::getHTML() {
    return this->html_;
}

void Response::setHTML(std::string html) {
    this->html_ = std::move(html);
}

/*
 *  HTTP/1.1 200 OK
    Content-Type: text/html
    Server: sintoth-web-server
    Content-Length: 3

    hi
 */
std::string Response::generate() {
    std::string response = "";
    response.append("HTTP/1.1 200 OK\n");
    if(this->content_type.empty()) {
        response.append("Content-Type: text/html\n");
    } else {
        response.append("Content-Type: " + content_type + "\n");
    }
    response.append("Server: sintoth-web-server\n");
    response.append("Content-Length: " + std::to_string(this->html_.length()) + "\n");
    for(const std::string& header : this->headers) response.append(header + "\n");
    response.append("\n\n");
    response.append(this->html_);
    return response;
}

std::vector<std::string> Response::getHeaders() {
    return this->headers;
}

void Response::addHeader(std::string header) {
    this->headers.push_back(header);
}

std::string Response::getContentType() {
    return this->content_type;
}

void Response::setContentType(std::string content_type) {
    this->content_type = content_type;
}