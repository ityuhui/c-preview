#include <kube_config.h>
#include <apiClient.h>
#include <CoreV1API.h>
#include <malloc.h>
#include <stdio.h>
#include <errno.h>

void process_one_watch_event(const char *wevent_string)
{
    static char fname[] = "process_one_watch_event()";

    if (!wevent_string) {
        return;
    }
    printf("event:\n%s\n\n", wevent_string);

    cJSON *wevent_json_obj = cJSON_Parse(wevent_string);
    if (!wevent_json_obj) {
        fprintf(stderr, "%s: Cannot create JSON from string.[%s].\n", fname, cJSON_GetErrorPtr());
        goto end;
    }
    cJSON *json_value = cJSON_GetObjectItem(wevent_json_obj, OIDC_ID_TOKEN_EXP);
    if (!json_value || json_value->type != cJSON_Number) {
        fprintf(stderr, "%s: Cannot get expiration time in id token.\n", fname);
        goto end;
    }

}

void my_watch_pod_handler(list_t* watch_event_list)
{
    if (!watch_event_list) {
        return;
    }

    listEntry_t* listEntry = NULL;
    list_ForEach(listEntry, watch_event_list) {
        char *list_item = listEntry->data;
        process_one_watch_event(list_item);
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

    apiClient->watch_func = my_watch_pod_handler;
    watch_list_pod(apiClient);

    apiClient_free(apiClient);
    apiClient = NULL;
    free_client_config(basePath, sslConfig, apiKeys);
    basePath = NULL;
    sslConfig = NULL;
    apiKeys = NULL;

    return 0;
}
