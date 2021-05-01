#include "httpd.h"

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
#include <iostream>

std::string readFile(std::string filename) {
    std::ifstream input_stream(filename);
    std::stringstream buffer;
    buffer << input_stream.rdbuf();
    return buffer.str();
}

char* append(char* source, char* text) {
    std::string source_string(source);
    std::string text_string(text);
    source_string.append(text_string);
    return strdup(source_string.c_str());
}

void httpd::start() {
    int server_fd;
    int new_socket;
    int valread;

    char* response_text;
    char* response_body;

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

    while (true) {
        if ((new_socket = accept(server_fd, (struct sockaddr *) &address, (socklen_t *) &addrlen)) < 0) {
            perror("while accepting");
            exit(EXIT_FAILURE);
        }

        char buffer[30000] = {0};
        read(new_socket, buffer, 30000);

        response_text = strdup("HTTP/1.1 200 OK\nContent-Type: text/html\nServer: sintoth-web-server\nContent-Length: ");

        response_body = strdup(readFile("../html/working.html").c_str());

        response_text = append(response_text, strdup(std::to_string(strlen(response_body)).c_str()));
        response_text = append(response_text, strdup("\n\n"));
        response_text = append(response_text, response_body);


        std::cout << response_text << "\n";

        write(new_socket, response_text, strlen(response_text));

        close(new_socket);
    }
}

