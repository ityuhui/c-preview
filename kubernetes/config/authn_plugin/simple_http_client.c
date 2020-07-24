#include "simple_http_client.h"

#define HTTP_REQUEST_GET "GET"
#define HTTP_REQUEST_POST "POST"
#define HTTP_REQUEST_DELETE "DELETE"
#define HTTP_REQUEST_PATCH "PATCH"

apiClient_t* shc_get_request(const char *url, const sslConfig_t *sc)
{
    return http_request(HTTP_REQUEST_GET, url, sc);
}

apiClient_t* shc_post_request(const char *url, const sslConfig_t *sc, const char *post_data)
{
    return http_request(HTTP_REQUEST_POST, url, sc, post_data);
}

static apiClient_t* http_request(const char *type, const char *url, const sslConfig_t *sc, const char *post_data)
{
    static char fname[] = "http_request()";

    apiClient_t *http_client = apiClient_create_with_base_path(url, sc, NULL);
    if (!http_client) {
        fprintf(stderr, "%s: Cannot create http client. [%s].\n", fname, strerror(errno));
        return NULL;
    }
    apiClient_invoke(http_client, NULL, NULL, NULL, NULL, NULL, NULL, post_data, type);

    switch (http_client->response_code) {
    case 200:
        return http_client;
        break;
    case 400:
        printf("%s: %s\n", "Unauthorized", fname);
        break;
    default:
        printf("%s response_code=%d\n", fname, http_client->response_code);
        break;
    }

    if (http_client) {
        apiClient_free(http_client);
        http_client = NULL;
    }
    return NULL;
}

char* shc_get_string_from_response_json(apiClient_t* http_client, const char* key)
{
    static char fname[] = "shc_get_string_from_response_json()";

    if (!http_client ||
        !http_client->dataReceived) {
        return NULL;
    }

    cJSON *json = cJSON_Parse(http_client->dataReceived);
    if (!json) {
        fprintf(stderr, "%s: Cannot create JSON from string.[%s].\n", fname, cJSON_GetErrorPtr());
        goto error;
    }
    value = cJSON_GetObjectItem(json, key);
    if (!value) {
        fprintf(stderr, "%s: Cannot get the value for %s.\n", fname, key);
        goto error;
    }
    if (!value->type != cJSON_String &&
        !value->type != cJSON_Object) {
        fprintf(stderr, "%s: The value for %s is invalid.\n", fname, key);
        goto error;
    }
    return strdup(value->valuestring);

error:
    if (json) {
        cJSON_Delete(json);
        json = NULL;
    }
    return NULL;
}