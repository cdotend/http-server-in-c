#ifndef mainserver_h
#define mainserver_h

#include <winsock2.h>

struct Server{


    int domain;
    int service;
    int protocol;
    u_long ui;
    int port;
    int backlog;

    int sock;

    struct sockaddr_in address;

    void(*launch)(struct Server *server);

};

struct Server server_constructor(int domain, int service, int protocol, u_long ui, int port, int backlog, void(*launch)(struct Server *server));

#endif /* mainserver_h */