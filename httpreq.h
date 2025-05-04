#ifndef httpreq_h
#define httpreq_h

enum HTTPMethods{
    GET,
    POST,
    PUT,
    HEAD,
    PATCH,
    DELETE,
    CONNECT,
    OPTIONS,
    TRACE
};

typedef struct HTTPReq{
    int Method;
    char *URI;
    float HTTPVersion;
    /* int Header; */ //char Header;
};

struct HTTPReq http_request_constructor(char *request_string);

#endif