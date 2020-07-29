#ifndef _AUTHN_PLUGIN_UTIL_H
#define _AUTHN_PLUGIN_UTIL_H

#define HTTP_REQUEST_GET "GET"
#define HTTP_REQUEST_POST "POST"
#define HTTP_REQUEST_DELETE "DELETE"
#define HTTP_REQUEST_PATCH "PATCH"

#ifdef  __cplusplus
extern "C" {
#endif

#include "../../include/apiClient.h"

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
    int shc_request(char** p_http_response, int* p_http_response_length, char *request_type, const char *url, sslConfig_t* sc, list_t* , char* post_data);

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

/*
 * shc_reset_client
 *
 * Description:
 *
 * Reset a http client before next calling
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
    void shc_reset_client(apiClient_t*);

#ifdef  __cplusplus
}
#endif
#endif                          /* _AUTHN_PLUGIN_UTIL_H */