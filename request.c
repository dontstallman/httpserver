#include "request.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h> // write
#include <string.h> // memset
#include <stdlib.h> // atoi
#include <stdbool.h> // true, false
#define BUFFER_SIZE 4096

int main(int argc, char** argv){
    char example_url[] = "PUT /ABCDEFabcdef012345XYZxyz-mm HTTP/1.1\r\nContent-Length: 460\r\n\r\nfrfrfrffff rrrr";
    char example_url2[] = "GET /ABCDEFabcdef012345XYZxyz-mm HTTP/1.1\r\n\r\n";
    Request example_request = processRequest(example_url);
    printf("Method: %s\nResource: %s\nContent-length: %ld\n", example_request.method, example_request.resource, example_request.content_length);
}