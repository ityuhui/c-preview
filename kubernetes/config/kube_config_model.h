#ifndef _KUBE_CONFIG_MODEL_H
#define _KUBE_CONFIG_MODEL_H

#include "../include/keyValuePair.h"

#ifdef  __cplusplus
extern "C" {
#endif

    typedef enum ExecCredential_type_t {
        EXEC_CREDENTIAL_TYPE_TOKEN = 1,
        EXEC_CREDENTIAL_TYPE_CLIENT_CERT
    } ExecCredential_type_t;

    typedef struct ExecCredential_status_t {
        ExecCredential_type_t type;
        union {
            struct {
                char *token;
            };
            struct {
                char *clientCertificateData;
                char *clientKeyData;
            };
        };
    } ExecCredential_status_t;

    typedef struct ExecCredential_t {
        char *apiVersion;
        char *kind;
        ExecCredential_status_t *status;
    } ExecCredential_t;

    typedef enum kubeconfig_property_type_t {
        KUBECONFIG_PROPERTY_TYPE_CONTEXT = 1,
        KUBECONFIG_PROPERTY_TYPE_CLUSTER,
        KUBECONFIG_PROPERTY_TYPE_USER,
        KUBECONFIG_PROPERTY_TYPE_USER_EXEC,
        KUBECONFIG_PROPERTY_TYPE_USER_AUTH_PROVIDER
    } kubeconfig_property_type_t;

    typedef struct kubeconfig_property_t {
        kubeconfig_property_type_t type;
        char *name;
        union {
            struct {            /* context */
                char *cluster;
                char *user;
            };
            struct {            /* cluster */
                char *server;
                char *certificate_authority_data;
            };
            struct {            /* user */
                char *token;
                char *client_certificate_data;
                char *client_key_data;
                struct kubeconfig_property_t *auth_provider;
                struct kubeconfig_property_t *exec;
                int insecure_skip_tls_verify;
                char *username;
                char *password;
            };
            struct {            /* user exec */
                char *command;
                char *apiVersion;
                keyValuePair_t **envs;
                int envs_count;
                char **args;
                int args_count;
            };
            struct {            /* user auth provider */
                char *id_token;
                char *cmd_path;
                char *access_token;
                char *expires_on;
                char *expiry;
                char *idp_certificate_authority_data;
            };
        };
    } kubeconfig_property_t;

    typedef struct kubeconfig_t {
        char *fileName;
        char *apiVersion;
        char *preferences;
        char *kind;
        char *current_context;
        kubeconfig_property_t **contexts;
        int contexts_count;
        kubeconfig_property_t **clusters;
        int clusters_count;
        kubeconfig_property_t **users;
        int users_count;
    } kubeconfig_t;

    ExecCredential_t *exec_credential_create();
    void exec_credential_free(ExecCredential_t *);

    ExecCredential_status_t *exec_credential_status_create();
    void exec_credential_status_free(ExecCredential_status_t *);

    kubeconfig_property_t *kubeconfig_property_create(kubeconfig_property_type_t type);
    void kubeconfig_property_free(kubeconfig_property_t * property);

    kubeconfig_property_t **kubeconfig_properties_create(int contexts_count, kubeconfig_property_type_t type);
    void kubeconfig_properties_free(kubeconfig_property_t ** properties, int properties_count);

    kubeconfig_t *kubeconfig_create();
    void kubeconfig_free(kubeconfig_t * kubeconfig);

#ifdef  __cplusplus
}
#endif
#endif                          /* _KUBE_CONFIG_MODEL_H */
