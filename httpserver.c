#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h> // write
#include <string.h> // memset
#include <stdlib.h> // atoi
#include <stdbool.h> // true, false
#include "request.h"
#define BUFFER_SIZE 4096


int main(int argc, char** argv) {
    char* port = "8080";
    printf("port: %s\n", port);

    //server configuration and overhead
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(port));
    server_addr.sin_addr.s_addr = INADDR_ANY;
    socklen_t addrlen = sizeof(server_addr);

    //create socket of type SOCK_STREAM, in ip domain AF_INET in Protocol domain (IPv4)
    int server_sockd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sockd<0){
        perror("error creating socket");
    }

    //avoid address already in use errrr
    int enable = 1;
    int optval = setsockopt(server_sockd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable));
    optval = bind(server_sockd, (struct sockaddr *) &server_addr, addrlen);
    optval = listen(server_sockd, 5);
    if (optval<0){
        return EXIT_FAILURE;
    }

    //create storage for client address
    struct sockaddr client_addr;
    socklen_t client_addrlen;

    //main thread
    while (true){
        printf("waiting for client..\n");
        int client_fd = accept(server_sockd, &client_addr, &client_addrlen);
        printf("client: %d accepted\n", client_fd);
        char buf[BUFFER_SIZE];
        char buf2[BUFFER_SIZE];
        Request req;
        //maybe append req structures to main hash table or something
        //uid by client file descriptor 
        //redo below to read from next buffer to get payload
        ssize_t bytesRead = recv(client_fd, buf, BUFFER_SIZE, 0);
        printf("%ld bytes received\n", bytesRead);
        req = parseRequest(buf);
        printf("Method: %s\r\nResource: %s\r\nContent length: %ld\r\n\r\n", req.method, req.resource, req.content_length);
        bytesRead = recv(client_fd, buf2, BUFFER_SIZE, 0);
        printf("%ld bytes received\n", bytesRead);
    }
    return EXIT_SUCCESS;
}