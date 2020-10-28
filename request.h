//table lookup for preprocessor is hash search of table 
//install(s,t) -> records s text and its replacement text t
//lookup (s) searches for a s in the tbale and returns a pointer to where it was found 
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h> // write
#include <string.h> // memset
#include <stdlib.h> // atoi
#include <stdbool.h> // true, false
#define BUFFER_SIZE 4096
//typedef enum Method {GET, PUT, HEAD} Method;

typedef struct request {
    //request is borne out of call to accept, does not include file descriptor maintained by running server thread 
    //request method, resource, content headers 
    char* method;
    char* resource;
    ssize_t content_length;
    ssize_t curr_content_length;
    char* buffer[BUFFER_SIZE];
    bool full_buffer_flag;
} Request;

// struct request parseRequest2(char* buf){
//     char* actionString = NULL;
//     char* ;
//     actionString = strtok_r(buf, "\r\n", actionString_ptr)
// }

struct request parseRequest(char* buf){
    //parserequest has no interaction with socket communication layer and instead parses a Request and fits it into a struct
    //data stream is in buffer

    char* tok1 = NULL;
    char* tok1_ctxt;
    Request request;
    printf("buf before: %c\n", buf[5]);
    tok1 = strtok_r(buf, "\r\n", &tok1_ctxt);
    printf("buf after: %s\n", buf);
    //tok1 should be GET /filename HTTPS\1.1   |   /r/n | Content-Length: 460 |\r\n\r\n and next tok1 should be 
    while (tok1 != NULL){
        char* tok2 = NULL;
        char* tok2_ctxt;
        tok2 = strtok_r(tok1, " ", &tok2_ctxt);
        while (tok2 != NULL){
            if (request.resource != NULL && request.method != NULL){
                printf("request and resource are null\n");
                if (!strcmp(tok2, "Content-Length:")){
                    printf("here\n");
                    request.content_length = atoi(strtok_r(NULL, " ", &tok2_ctxt));
                }
                else{
                    //error, break or GET request and no content length header 
                }
            }
            else{
                if (!strcmp(tok2, "GET") || !strcmp(tok2, "PUT") || !strcmp(tok2, "HEAD")){
                    request.method = tok2;
                    printf("method: %s\n", tok2);
                    request.resource = strtok_r(NULL, " ", &tok2_ctxt);
                    if (request.resource!=NULL) {
                        printf("resource: %s\n", request.resource);
                        tok2 = strtok_r(NULL, " ", &tok2_ctxt);
                        if (!strcmp(tok2, "HTTP/1.1")) {
                            printf("HTTP Version: %s\r\n", tok2);
                        }
                    }
                    else{
                        //no resource specified
                    }
                }   
            }
            tok2 = strtok_r(NULL, " ", &tok2_ctxt);
        }
        tok1 = strtok_r(NULL, "\r\n", &tok1_ctxt);
        printf("tok1: %s\n", tok1);
        //empty token, like in a GET request, could return as NULL or empty so check
    }
    printf("we never get here\n");
    return request;
}
//parseRequest->get partial amount of data in recv->call write->if more bytes left to be read, iterate through recv again

    
