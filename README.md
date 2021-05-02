# sintoth-web-server
The sintoth web server (httpd) 

## How to use

Include httpd.h and define the method handle:

```cpp
std::string httpd::handle(Request request) {
    return "";
}
```

The method returns the HTTP response. I recommend to use the class Response to generate it. The parameter request is used to get the URL and more information about the request. 

Example code:

```cpp
std::string httpd::handle(Request request) {
    std::cout << "URL: " << request.getRoute() << "\n";
    std::string html = "<h1>hi</h1>";
    Response response(html);
    return response.generate();
}
```

This would log the URL and display "hi".

Your main method should look like this, if you want to start the server there:
```cpp
int main() {
    httpd::start();
}
```
