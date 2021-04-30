#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

int main(int argc, char const *argv[]) {
    printf("Starting sintoth web server!\n");

    int server_fd;
    int new_socket;
    int valread;

    char* response_text;
    char* response_body;

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

        response_body = "hii";
        response_text = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: ";
        int response_body_length = strlen(response_body);

        char response_body_length_string[12];
        sprintf(response_body_length_string, "%d", response_body_length);

        response_text = concat(response_text, response_body_length_string);
        response_text = concat(response_text, "\n\n");

        char* response_text_with_body = concat(response_text, response_body);
        printf(response_text_with_body);
        printf("\n");

        write(new_socket, response_text_with_body, strlen(response_text_with_body));
        close(new_socket);
    }
}