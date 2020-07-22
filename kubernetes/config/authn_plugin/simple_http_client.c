#include "simple_http_client.h"

#define HTTP_REQUEST_GET "GET"
    HTTP_REQUEST_POST,
    HTTP_REQUEST_DELETE,
    HTTP_REQUEST_PATCH
} http_request_type_t;

int shc_get_request(const char *url, const sslConfig_t *sc)
{
    return http_request(HTTP_REQUEST_GET, url, sc);
}

int shc_post_request(const char *url, const sslConfig_t *sc)
{
    return http_request(HTTP_REQUEST_POST, url, sc);
}

static int http_request(http_request_type_t type, const char *url, const sslConfig_t *sc)
{

}