#ifndef _AUTHN_PLUGIN_UTIL_H
#define _AUTHN_PLUGIN_UTIL_H

#include "../../include/apiClient.h"

#ifdef  __cplusplus
extern "C" {
#endif

    #define HTTP_REQUEST_GET "GET"
    #define HTTP_REQUEST_POST "POST"
    #define HTTP_REQUEST_DELETE "DELETE"
    #define HTTP_REQUEST_PATCH "PATCH"

    typedef enum shc_http_rc_t {
        HTTP_RC_OK = 200,
        HTTP_RC_UNAUTHORIZED = 400
    } shc_http_rc_t;

/*
 * shc_request
 *
 * Description:
 *
 * Issue a http(s) request
 *
 * Return:
 *
 *  apiClient_t *   :   http client
 *  NULL     :   Failed to create http client
 *
 * Parameter:
 *
 * IN:
 * data: raw data of SSL/TLS certificate or key
 *
 * OUT:
 * None
 *
 */
    int shc_request(char** p_http_response, int* p_http_response_length, char *request_type, const char *url, sslConfig_t* sc, list_t* apiKeys, list_t* contentType, char* post_data);

/*
 * shc_get_string_from_json
 *
 * Description:
 *
 * Get a string value form json by a key
 *
 * Return:
 *
 *  char *   :   File name of created temporary file
 *  NULL     :   Failed to create temporary file
 *
 * Parameter:
 *
 * IN:
 * data: raw data of SSL/TLS certificate or key
 *
 * OUT:
 * None
 *
 */
    char* shc_get_string_from_json(const char *json_string, const char *key);

#ifdef  __cplusplus
}
#endif
#endif                          /* _AUTHN_PLUGIN_UTIL_H */