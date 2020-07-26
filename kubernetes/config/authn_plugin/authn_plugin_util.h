#ifndef _AUTHN_PLUGIN_UTIL_H
#define _AUTHN_PLUGIN_UTIL_H

#define HTTP_REQUEST_GET "GET"
#define HTTP_REQUEST_POST "POST"
#define HTTP_REQUEST_DELETE "DELETE"
#define HTTP_REQUEST_PATCH "PATCH"

#ifdef  __cplusplus
extern "C" {
#endif

    apiClient_t* shc_request(const char*, const char* , const sslConfig_t*, const list_t*, const char*);

    char* shc_get_string_from_json(const char*, const char*);

    void shc_reset_client(apiClient_t*);

#ifdef  __cplusplus
}
#endif
#endif                          /* _AUTHN_PLUGIN_UTIL_H */