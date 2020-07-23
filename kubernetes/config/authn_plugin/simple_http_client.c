#include "simple_http_client.h"

#define HTTP_REQUEST_GET "GET"
#define HTTP_REQUEST_POST "POST"
#define HTTP_REQUEST_DELETE "DELETE"
#define HTTP_REQUEST_PATCH "PATCH"

int shc_get_request(const char *url, const sslConfig_t *sc)
{
    return http_request(HTTP_REQUEST_GET, url, sc);
}

int shc_post_request(const char *url, const sslConfig_t *sc)
{
    return http_request(HTTP_REQUEST_POST, url, sc);
}

static int http_request(const char *type, const char *url, const sslConfig_t *sc)
{
    static char fname[] = "http_request()";

    int rc = 0;

    apiClient_t *http_client = apiClient_create_with_base_path(url, sc, NULL);
    if (!http_client) {
        fprintf(stderr, "%s: Cannot create http client. [%s].\n", fname, strerror(errno));
        return -1;
    }
    apiClient_invoke(http_client, NULL, NULL, NULL, NULL, NULL, NULL, NULL, type);

    switch (http_client->response_code) {
    case 200:
        break;
    case 400:
        printf("%s: %s\n", "Unauthorized", fname);
        rc = -1;
        goto end;
    default:
        printf("%s response_code=%d\n", fname, http_client->response_code);
        rc = -1;
        goto end;
    }

end:
    if (http_client->dataReceived) {
        free(http_client->dataReceived);
        http_client->dataReceived = NULL;
        http_client->dataReceivedLen = 0;
    }

    if (http_client) {
        apiClient_free(http_client);
        http_client = NULL;
    }

    return rc;
}