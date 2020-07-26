#include "authn_plugin.h"
#include "authn_plugin_util.h"
#include "kube_config_util.h"
#include "binary.h"
#include "cJSON.h"

#define OIDC_ID_TOKEN_DELIM "."
#define OIDC_ID_TOKEN_EXP "exp"
#define OIDC_CONFIGURATION_URL_TEMPLATE "%s/.well-known/openid-configuration"
#define OIDC_TOKEN_ENDPOINT "token_endpoint"
#define OIDC_ID_TOKEN "id_token"
#define OIDC_REFRESH_TOKEN "refresh_token"

#define REFRESH_TOKEN_CONTENT_TYPE "application/x-www-form-urlencoded"
#define REFRESH_TOKEN_CREDENTIAL_TEMPLATE "Basic %s:%s"
#define REFRESH_TOKEN_POST_DATA_TEMPLATE "refresh_token=%s&grant_type=refresh_token"

#define OIDC_CONFIGURATION_URL_BUFFER_SIZE 1024
#define REFRESH_TOKEN_CREDENTIAL_BUFFER_SIZE 1024
#define REFRESH_TOKEN_POST_DATA_BUFFER_SIZE 1024

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

    char oidc_configuration_url[OIDC_CONFIGURATION_URL_BUFFER_SIZE];
    memset(oidc_configuration_url,sizeof(oidc_configuration_url), 0);
    snprintf(oidc_configuration_url, sizeof(oidc_configuration_url), OIDC_CONFIGURATION_URL_TEMPLATE, idp_issuer_url);

    apiClient_t *http_client = shc_request(HTTP_REQUEST_GET,oidc_configuration_url, sc, NULL);
    if (!http_client) {
        return NULL;
    }
    if (200 != http_client->response_code) {
        goto end;
    }
    
    char *token_endpoint = shc_get_string_from_json(http_client->dataReceived,OIDC_TOKEN_ENDPOINT);
    shc_reset_client(http_client);
end:
    if (http_client) {
        apiClient_free(http_client);
        http_client = NULL;
    }
    return token_endpoint;
}

static int refresh_oidc_token(kubeconfig_property_t *auth_provider, const char *token_endpoint, const sslConfig_t *sc)
{
    static char fname[] = "refresh_oidc_token()";

    int rc = 0;

    if (!auth_provider ||
        !token_endpoint ||
        !sc) {
        return -1;
    }

    list_t* content_type = list_create();
    list_addElement(content_type, REFRESH_TOKEN_CONTENT_TYPE);

    char refresh_token_credential[REFRESH_TOKEN_CREDENTIAL_BUFFER_SIZE];
    memset(refresh_token_credential,sizeof(refresh_token_credential), 0);
    snprintf(refresh_token_credential, sizeof(refresh_token_credential), REFRESH_TOKEN_CREDENTIAL_TEMPLATE, auth_provider->client_id, auth_provider->client_secret);

    char refresh_token_post_data[REFRESH_TOKEN_POST_DATA_BUFFER_SIZE];
    memset(refresh_token_post_data, sizeof(refresh_token_post_data), 0);
    snprintf(refresh_token_post_data, sizeof(refresh_token_post_data), REFRESH_TOKEN_POST_DATA_TEMPLATE, auth_provider->refresh_token);

    apiClient_t* http_client = shc_request(HTTP_REQUEST_POST, token_endpoint, sc, content_type, refresh_token_post_data);
    if (!http_client) {
        rc = -1;
        goto end;
    }
    if (200 != http_client->response_code) {
        rc = -1;
        goto end;
    }

    char *new_id_token= shc_get_string_from_json(http_client->dataReceived, OIDC_ID_TOKEN);
    if (new_id_token) {
        if (auth_provider->id_token) {
            free(auth_provider->id_token);
            auth_provider->id_token = NULL;
        }
        auth_provider->id_token = new_id_token;
    } else {
        rc = -1;
        goto end;
    }

    char *new_refresh_token= shc_get_string_from_json(http_client->dataReceived, OIDC_REFRESH_TOKEN);
    if (new_refresh_token) {
        if (auth_provider->refresh_token) {
            free(auth_provider->refresh_token);
            auth_provider->refresh_token = NULL;
        }
        auth_provider->refresh_token = new_refresh_token;
    } else {
        rc = -1;
        goto end;
    }

    shc_reset_client(http_client);

end:
    list_free(content_type);
    if (http_client) {
        apiClient_free(http_client);
        http_client = NULL;
    }
    return rc;
}

int refresh(kubeconfig_property_t* auth_provider)
{
    int rc = 0;

    sslConfig_t *sc = NULL;
    if (auth_provider->idp_certificate_authority_data) {
        char *idp_certificate_file = kubeconfig_mk_cert_key_tempfile(user->idp_certificate_authority_data);
        sc = sslConfig_create(NULL, NULL, idp_certificate_file, 0);
        free(idp_certificate_file);
        idp_certificate_file = NULL;
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


