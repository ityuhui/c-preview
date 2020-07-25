#ifndef _SIMPLE_HTTP_CLIENT_H
#define _SIMPLE_HTTP_CLIENT_H

#ifdef  __cplusplus
extern "C" {
#endif

    #define HTTP_REQUEST_GET "GET"
    #define HTTP_REQUEST_POST "POST"
    #define HTTP_REQUEST_DELETE "DELETE"
    #define HTTP_REQUEST_PATCH "PATCH"

    apiClient_t* shc_request(const char*, const char* , const sslConfig_t*, const char*);

    char* shc_get_string_from_json(const char*, const char*);

    void shc_reset_client(apiClient_t*);

#ifdef  __cplusplus
}
#endif
#endif                          /* _SIMPLE_HTTP_CLIENT_H */