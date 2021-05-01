#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <fstream>
#include <sstream>

std::string readFile(std::string filename) {
    std::ifstream input_stream(filename);
    std::stringstream buffer;
    buffer << input_stream.rdbuf();
    return buffer.str();
}

int httpd_start() {
    int server_fd;
    int new_socket;
    int valread;

    std::string response_text;
    std::string response_body;

    struct sockaddr_in address;
    int addrlen = sizeof address;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("in socket");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(80);

    printf("Set port to 80\n");

    memset(address.sin_zero, '\0', sizeof address.sin_zero);

    if (bind(server_fd, (struct sockaddr *) &address, sizeof(address)) < 0) {
        perror("in bind");
        exit(EXIT_FAILURE);
    }

    // server_fd, max connections until refused connection
    if (listen(server_fd, 10)) {
        perror("in listen");
        exit(EXIT_FAILURE);
    }

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *) &address, (socklen_t *) &addrlen)) < 0) {
            perror("while accepting");
            exit(EXIT_FAILURE);
        }

        char buffer[30000] = {0};
        read(new_socket, buffer, 30000);

        response_text = "HTTP/1.1 200 OK\nContent-Type: text/html\nServer: sintoth-web-server\nContent-Length: ";

        response_body = readFile("../html/working.html");

        response_text.append(std::to_string(response_body.length()));
        response_text.append("\n\n");  // Before the request content starts, HTTP protocol requires to empty lines
        response_text.append(response_body);

        write(new_socket, &response_text, response_text.length());
        close(new_socket);
    }
}


int main() {
    httpd_start();
}