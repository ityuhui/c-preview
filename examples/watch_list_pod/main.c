#include <kube_config.h>
#include <apiClient.h>
#include <CoreV1API.h>
#include <malloc.h>
#include <stdio.h>
#include <errno.h>

#define JSON_ARRAY_DELIM "\n"

void watch_pod_handler(void* data, long* pDataLen)
{
    char *raw_data= (char *)data;
    if (!raw_data || '\0' == raw_data[0]) {
        return;
    }

    char *token = NULL;
    token = strtok(raw_data, JSON_ARRAY_DELIM);
    while (token) {
        printf("%s\n", token);

        malloc();
        *pDataLen = *pDataLen - len;

        token = strtok(NULL, JSON_ARRAY_DELIM);
    }

    return;


    /*long dataLen = *pDataLen;
    for (int i = 0; i < dataLen; i++) {
        printf("data[%d]=%c\n", i, ((char *)data)[i]);
    }

    printf("\n");
    */
    //printf("%s\n", (char*)data);
    printf("dataLen=%ld, strlen(data)=%ld\n", *pDataLen, strlen((char*)data));

    free((char *)data);
    *pDataLen = 0;

    
    

    /*
    cJSON* cjson = cJSON_Parse((char *)data);
    if (cjson == NULL) {
        fprintf(stderr, "Cannot create a json object\n");
        return;
    }
    cJSON_Print(cjson);
    */
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
