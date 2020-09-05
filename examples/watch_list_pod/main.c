#include <kube_config.h>
#include <apiClient.h>
#include <CoreV1API.h>
#include <malloc.h>
#include <stdio.h>
#include <errno.h>

#define JSON_ARRAY_DELIM "\r\n"

int convert_to_json_array(char *json_string, list_t *json_array)
{
    if (!json_string || '\0' == json_string[0]) {
        return -1;
    }
    printf("strlen(json_string)=%ld\n", strlen(json_string));
    //printf("json_string=%s\n", json_string);

    int rc = 0;
    char* json_string_dup = strndup(json_string, strlen(json_string));

    char* token = NULL;
    token = strtok(json_string_dup, JSON_ARRAY_DELIM);
    while (token) {
        cJSON* cjson = cJSON_Parse(token);
        if (cjson == NULL) {
            fprintf(stderr, "Cannot create a json object\n");
            rc = false;
            goto end;
        }
        token = strtok(NULL, JSON_ARRAY_DELIM);
    }

end:
    if (json_string_dup) {
        free(json_string_dup);
        json_string_dup = NULL;
    }
    return rc;
}

void watch_pod_handler(void** pdata, long* pDataLen)
{
    char *data = *(char **)pdata;
    //printf("Debug--begin-----------\n");
    //printf("%s\n", data);
    printf("dataLen=%ld, strlen(data)=%ld\n", *pDataLen, strlen(data));
    //printf("Debug--end-------------\n");

    int rc = convert_to_json_array(data);
    if (0 == rc) {
        printf("%s\n", data);
        free(data);
        *pdata = NULL;
        *pDataLen = 0;
    } else {
        fprintf(stderr, "Not a valid json array\n");
    }    

}

void watch_list_pod(apiClient_t * apiClient)
{
    v1_pod_list_t *pod_list = NULL;
    pod_list = CoreV1API_listNamespacedPod(apiClient, "default",    /*namespace */
                                           NULL,    /* pretty */
                                           0,   /* allowWatchBookmarks */
                                           NULL,    /* continue */
                                           NULL,    /* fieldSelector */
                                           NULL,    /* labelSelector */
                                           0,   /* limit */
                                           NULL,    /* resourceVersion */
                                           0,   /* timeoutSeconds */
                                           1    /* watch */
        );
    printf("The return code of HTTP request=%ld\n", apiClient->response_code);
}

int main(int argc, char *argv[])
{
    char *basePath = NULL;
    sslConfig_t *sslConfig = NULL;
    list_t *apiKeys = NULL;
    int rc = load_kube_config(&basePath, &sslConfig, &apiKeys, NULL);   /* NULL means loading configuration from $HOME/.kube/config */
    if (rc != 0) {
        printf("Cannot load kubernetes configuration.\n");
        return -1;
    }
    apiClient_t *apiClient = apiClient_create_with_base_path(basePath, sslConfig, apiKeys);
    if (!apiClient) {
        printf("Cannot create a kubernetes client.\n");
        return -1;
    }

    apiClient->watch_func = watch_pod_handler;
    watch_list_pod(apiClient);

    apiClient_free(apiClient);
    apiClient = NULL;
    free_client_config(basePath, sslConfig, apiKeys);
    basePath = NULL;
    sslConfig = NULL;
    apiKeys = NULL;

    return 0;
}
