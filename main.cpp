#include "httpd.h"

#include "response/Response.h"

std::string httpd::handle(Request request) {
    std::string html = "<h1>hi</h1>";
    Response response(html);
    return response.generate();
}


int main() {
    httpd::start();
}