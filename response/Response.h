#ifndef SINTOTH_WEB_SERVER_RESPONSE_H
#define SINTOTH_WEB_SERVER_RESPONSE_H

#include <string>
#include <vector>

class Response {
private:
    std::string html_;
    std::string content_type;
    std::vector<std::string> headers;
public:
    Response(std::string html) : html_(html) {};
    std::string getHTML();
    void setHTML(std::string html);
    std::string generate();
    std::vector<std::string> getHeaders();
    void addHeader(std::string header);
    std::string getContentType();
    void setContentType(std::string content_type);
};


#endif //SINTOTH_WEB_SERVER_RESPONSE_H
