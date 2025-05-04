#include "mainserver.h"
#include <stdio.h>
#include <stdlib.h>

struct Server server_constructor(int domain, int service, int protocol, u_long ui, int port, int backlog, void(*launch)(struct Server *server)) {

    struct Server server;

    server.domain = domain;
    server.service = service;
    server.protocol = protocol;
    server.ui = ui;
    server.port = port;
    server.backlog = backlog;
    server.launch = launch;

    server.address.sin_family = domain;
    server.address.sin_port = htons(port);
    server.address.sin_addr.s_addr = htonl(ui);
    server.sock = socket(domain, service, protocol);
    
    // Test for socket connection
    if (server.sock == 0){

        perror("Failed to connect socket...\n");
        exit(1);

    }
    
    //Test for socket binding
    if (bind(server.sock, (struct sockaddr *)&server.address, sizeof(server.address)) < 0) {

        perror("Failed to bind socket...");
        exit(1);

    }

    //Test for socket listening
    if (listen(server.sock, server.backlog) < 0){

        perror("Failed to start listening...");
        exit(1);

    }
    
    printf("Server is running...\n");
    return server;
}