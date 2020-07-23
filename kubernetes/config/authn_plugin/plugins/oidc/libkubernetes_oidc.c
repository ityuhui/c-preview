#include "authn_plugin.h"
#include "simple_http_client.h"
#include "binary.h"
#include "cJSON.h"

#define OIDC_ID_TOKEN_DELIM "."
#define OIDC_ID_TOKEN_EXP "exp"
#define OIDC_CONFIGURATION_URL_TEMPLATE "%s/.well-known/openid-configuration"
#define OIDC_TOKEN_ENDPOINT "token_endpoint"

static time_t get_token_expiration_time(const char *token_string)
{
    static char fname[] = "get_token_expiration_time()";

    time_t expiration_time = 0;

    if (!token_string) {
        return 0;
    }
    char *dup_token_string = strdup(token_string);
    if (!dup_token_string) {
        return 0;
    }

    char *p = NULL:
    p = strtok(dup_token_string, OIDC_ID_TOKEN_DELIM); /* jwt header */
    if (!p) {
        goto end;
    }
    p = strtok(NULL, OIDC_ID_TOKEN_DELIM);  /* jwt part2 */
    if (!p) {
        goto end;
    }

    int decoded_bytes = 0;
    char* b64decode = base64decode(p, strlen(p), &decoded_bytes);
    if (!b64decode || 0 == decoded_bytes) {
        fprintf(stderr, "%s: Base64 decodes failed.\n", fname);
        goto end;
    }

    cJSON *payload_JSON = cJSON_Parse(b64decode);
    if (!payload_JSON) {
        fprintf(stderr, "%s: Cannot create JSON from string.[%s].\n", fname, cJSON_GetErrorPtr());
        goto end;
    }
    json_value = cJSON_GetObjectItem(payload_JSON, OIDC_ID_TOKEN_EXP);
    if (!json_value || json_value->type != cJSON_Number) {
        fprintf(stderr, "%s: Cannot get expiration time in id token.\n", fname);
        goto end;
    }
    expiration_time = json_value->valueint;

end:
    if (payload_JSON) {
        cJSON_Delete(payload_JSON);
        payload_JSON = NULL;
    }
    if (b64decode) {
        free(b64decode);
        b64decode = NULL;
    }
    if (dup_token_string) {
        free(dup_token_string);
        dup_token_string = NULL;
    }
    return expiration_time;
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

char *get_token_endpoint(const char *idp_issuer_url, const sslConfig_t *sc)
{
    static char fname[] = "get_token_endpoint()";

    if (!token_endpoint || 
        token_endpoint_buffer_size < 1 ||
        !idp_issuer_url ||
        !sc) {
        return NULL;
    }

    char oidc_configuration_url[];
    snprintf(oidc_configuration_url, sizeof(oidc_configuration_url), OIDC_CONFIGURATION_URL_TEMPLATE, idp_issuer_url);

    if ( 0 == shc_get_request(oidc_configuration_url, sc)) {
        return shc_get_value_from_response(OIDC_TOKEN_ENDPOINT);
    } else {
        return NULL;
    }
}

static int refresh_oidc_token(kubeconfig_property_t *auth_provider, const char *token_endpoint, const sslConfig_t *sc)
{
    if (!auth_provider ||
        !token_endpoint ||
        !sc) {
        return -1;
    }

    char oidc_return[];
    if (0 == shc_post_request(token_endpoint, sc)) {
        shc_parse_from_response(oidc_return, sizeof(oidc_return), "");
        if () {
            if (auth_provider->id_token) {
                free(auth_provider->id_token);
                auth_provider->id_token = NULL;
            }
            auth_provider->id_token = strdup(oidc_return);
        }
        shc_parse_from_response(oidc_return, sizeof(oidc_return), "");
        if () {
            if (auth_provider->refresh_token) {
                free(auth_provider->refresh_token);
                auth_provider->refresh_token = NULL;
            }
            auth_provider->refresh_token = strdup(oidc_return);
        }
    } else {
        return -1;
    }

    return 0;
}

int refresh(kubeconfig_property_t* auth_provider)
{
    int rc = 0;

    sslConfig_t *sc = NULL;
    if (auth_provider->idp_certificate_authority_data) {
        sc = sslConfig_create(NULL, NULL, auth_provider->idp_certificate_authority_data, 0);
    } else {
        sc = sslConfig_create(NULL, NULL, NULL, 1);
    }
    if (!sc) {
        return -1;
    }

    char *token_endpoint = get_token_endpoint(auth_provider->idp_issuer_url, sc);
    if (!token_endpoint) {
        rc = -1;
        goto end;
    }
    rc = refresh_oidc_token(auth_provider, token_endpoint, sc);
    if (-1 == rc) {
        goto end;
    }

end:
    if (token_endpoint) {
        free(token_endpoint);
        token_endpoint = NULL;
    }
    if (sc) {
        sslConfig_free(sc);
        sc = NULL;
    }
    
    return rc;
}


