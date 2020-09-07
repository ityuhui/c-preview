#include <kube_config.h>
#include <apiClient.h>
#include <CoreV1API.h>
#include <malloc.h>
#include <stdio.h>
#include <errno.h>

#define WATCH_EVENT_KEY_TYPE "type"
#define WATCH_EVENT_KEY_OBJECT "object"

void process_one_watch_event(const char *wevent_string)
{
    static char fname[] = "process_one_watch_event()";

    if (!wevent_string) {
        return;
    }
    printf("watch event raw string:\n%s\n\n", wevent_string);

    cJSON *wevent_json_obj = cJSON_Parse(wevent_string);
    if (!wevent_json_obj) {
        fprintf(stderr, "%s: Cannot create JSON from string.[%s].\n", fname, cJSON_GetErrorPtr());
        goto end;
    }
    cJSON *json_value_type = cJSON_GetObjectItem(wevent_json_obj, WATCH_EVENT_KEY_TYPE);
    if (!json_value_type || json_value_type->type != cJSON_String) {
        fprintf(stderr, "%s: Cannot get type in watch event.\n", fname);
        goto end;
    }
    char *type = strdup(json_value_type->valuestring);
    printf("type: %s\n", type);

    cJSON *json_value_object = cJSON_GetObjectItem(wevent_json_obj, WATCH_EVENT_KEY_OBJECT);
    if (!json_value_object || json_value_object->type != cJSON_Object) {
        fprintf(stderr, "%s: Cannot get object in watch event.\n", fname);
        goto end;
    }
    v1_pod_t *pod = v1_pod_parseFromJSON(json_value_object);
    if (!pod) {
        fprintf(stderr, "%s: Cannot get pod from watch event object.\n", fname);
        goto end;
    }
    printf("pod:\n\tname: %s\n", pod->metadata->name);

end:
    if (pod) {
        v1_pod_free(pod);
        pod = NULL;
    }
    if (type) {
        free(type);
        type = NULL;
    }
    if (wevent_json_obj) {
        cJSON_Delete(wevent_json_obj);
        wevent_json_obj = NULL;
    }
}

void watch_list_pod(apiClient_t * apiClient)
{
    apiClient->watch_func = process_one_watch_event;
    CoreV1API_listNamespacedPod(apiClient, "default",    /*namespace */
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

    watch_list_pod(apiClient);

    apiClient_free(apiClient);
    apiClient = NULL;
    free_client_config(basePath, sslConfig, apiKeys);
    basePath = NULL;
    sslConfig = NULL;
    apiKeys = NULL;

    return 0;
}
