#include "httpd.h"

#include "response/Response.h"
#include <iostream>

std::string httpd::handle(Request request) {
    std::cout << "URL: " << request.getRoute() << "\n";
    std::string html = "<h1>Test</h1>";
    Response response(html);
    return response.generate();
}

int main() {
    httpd::start();
}