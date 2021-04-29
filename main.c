#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    printf("Starting sintoth web server!\n");

    int server_fd;
    int new_socket;
    int valread;

    struct sockaddr_in address;
    int addrlen = sizeof address;

    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("in socket");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(80);

    printf("Set port to 80\n");

    memset(address.sin_zero, '\0', sizeof address.sin_zero);

    if(bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("in bind");
        exit(EXIT_FAILURE);
    }

    // server_fd, max connections until refused connection
    if(listen(server_fd, 10)) {
        perror("in listen");
        exit(EXIT_FAILURE);
    }

    while(1) {
        if((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("while accepting");
            exit(EXIT_FAILURE);
        }

        char buffer[30000] = {0};
        read(new_socket, buffer, 30000);

        char *response_body = "hi";

        char *response_text = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: %d\n\n";

        response_text = strcat(response_text, response_body);

        char *response = (char*)malloc(strlen(response_text) * 20);
        sprintf(response, response_text, strlen(response_body));

        write(new_socket, response, strlen(response));
        close(new_socket);

        free(response);
    }
}