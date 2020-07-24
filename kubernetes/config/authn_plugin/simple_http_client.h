#ifndef _SIMPLE_HTTP_CLIENT_H
#define _SIMPLE_HTTP_CLIENT_H

#ifdef  __cplusplus
extern "C" {
#endif

    apiClient_t* shc_get_request(const char* , const sslConfig_t*);

    apiClient_t* shc_post_request(const char* , const sslConfig_t*);

    char* shc_get_string_from_response_json(apiClient_t*, const char*);

#ifdef  __cplusplus
}
#endif
#endif                          /* _SIMPLE_HTTP_CLIENT_H */