#include "authn_plugin.h"
#include "simple_http_client.h"

static time_t get_token_expiration_time(const char *token_string)
{
    if (!token_string) {
        return 0;
    }
    char* string = strdup(token_string);
    if (!string) {
        return 0;
    }

    char* p = NULL:
    p = strtok(string, "."); /* jwt header */
    if (!p) {
        goto error;
    }
    p = strtok(NULL, ".");  /* jwt payload */
    if (!p) {
        goto error;
    }
    base64decode(p);

    char *pay_load = get_jwt_payload(token_string);
    
    get_token_expiration_time

    

    freejwt(&jwt);
    free(string)
    return 0;
error:
    free(string);
    return -1;
}

char* get_token(kubeconfig_property_t* auth_provider)
{
    return auth_provider->id_token;
}

bool is_expired(kubeconfig_property_t* auth_provider)
{
    if (!auth_provider->id_token) {
        return true;
    }

    time_t exp_time = get_token_expiration_time(auth_provider->id_token);
    if (exp_time < time(NULL) ) {
        return true;
    }

    return false;
}

int refresh(kubeconfig_property_t* auth_provider)
{
    http_request();

    if (auth_provider->id_token) {
        free(auth_provider->id_token);
        auth_provider->id_token = NULL;
    }
    auth_provider->id_token = strdup("new_id_token");
    if (auth_provider->refresh_token) {
        free(auth_provider->refresh_token);
        auth_provider->refresh_token = NULL;
    }
    auth_provider->refresh_token = strdup("new_id_token");

    return 0;
}


