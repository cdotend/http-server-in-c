#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "mainserver.h"

void launch(struct Server *server){

    char buffer[30000];
    char *hello = "HTTP/1.1 200 OK\r\n"
    "Server: Apache/2.4.63 (Win32)\r\n"
    "Last-Modified: Wed, 23 Jan 2025 19:15:56 GMT\r\n"
    "Content-Type: text/html\r\n"
    "Connection: Closed\r\n"
    "\r\n"
    "<html><body><h1>I am Gay!</h1></body></html>";

    int address_length;
    int new_sock;
    printf("===== WAITING FOR CONNECTION =====\n");
     
    while(1){
        address_length = sizeof(server -> address);
        new_sock = accept(server->sock, (struct sockaddr *) &server->address, &address_length);
        if (new_sock < 0) {

            perror("accept failed...");
            continue;

        }
        
        memset(buffer, 0, sizeof(buffer));
        int bytes_read = recv(new_sock, buffer, sizeof(buffer) - 1, 0);
        if (bytes_read > 0){
            buffer[bytes_read] = '\0';
            printf("Received:\n%s\n", buffer);
        }else if (bytes_read == 0){
            printf("Client disconnected.\n");
        }else {
            perror("recv failed");
        }

        send(new_sock, hello, strlen(hello), 0);
        close(new_sock);
    }


}

int main() {

    WSADATA wsaData; 

    if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0){

        printf("WSAStartup failed...\n");
        return 1;

    } 

    struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 8080, 10, launch);
    server.launch(&server);

    WSACleanup();
    return 0;

}

    