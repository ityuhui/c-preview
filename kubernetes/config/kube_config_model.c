#include "kube_config_model.h"

kubeconfig_auth_provider_t *kubeconfig_auth_provider_create()
{
    kubeconfig_auth_provider_t *provider = calloc(1, sizeof(kubeconfig_auth_provider_t));
    return provider;
}

void kubeconfig_auth_provider_free(kubeconfig_auth_provider_t * provider)
{
    if (!provider) {
        return;
    }

    if (provider->name) {
        free(provider->name);
    }
    if (provider->id_token) {
        free(provider->id_token);
    }
    if (provider->cmd_path) {
        free(provider->cmd_path);
    }
    if (provider->access_token) {
        free(provider->access_token);
    }
    if (provider->expires_on) {
        free(provider->expires_on);
    }
    if (provider->expiry) {
        free(provider->expiry);
    }
    if (provider->idp_certificate_authority_data) {
        free(provider->idp_certificate_authority_data);
    }
}

kubeconfig_exec_t *kubeconfig_exec_create()
{
    kubeconfig_exec_t *exec = calloc(1, sizeof(kubeconfig_exec_t));
    return exec;
}

void kubeconfig_exec_free(kubeconfig_exec_t * exec)
{
    if (!exec) {
        return;
    }

    if (exec->command) {
        free(exec->command);
    }
}

kubeconfig_cluster_t *kubeconfig_cluster_create()
{
    kubeconfig_cluster_t *cluster = calloc(1, sizeof(kubeconfig_cluster_t));
    return cluster;
}

void kubeconfig_cluster_free(kubeconfig_cluster_t * cluster)
{
    if (!cluster) {
        return;
    }

    if (cluster->name) {
        free(cluster->name);
    }
    if (cluster->server) {
        free(cluster->server);
    }
    if (cluster->certificate_authority_data) {
        free(cluster->certificate_authority_data);
    }
}

kubeconfig_user_t *kubeconfig_user_create()
{
    kubeconfig_user_t *user = calloc(1, sizeof(kubeconfig_user_t));
    return user;
}

void kubeconfig_user_free(kubeconfig_user_t * user)
{
    if (!user) {
        return;
    }

    if (user->name) {
        free(user->name);
    }
    if (user->client_certificate_data) {
        free(user->client_certificate_data);
    }
    if (user->client_key_data) {
        free(user->client_key_data);
    }
    if (user->username) {
        free(user->username);
    }
    if (user->password) {
        free(user->password);
    }
    if (user->auth_provider) {
        kubeconfig_auth_provider_free(user->auth_provider);
    }
    if (user->exec) {
        kubeconfig_exec_free(user->exec);
    }
}

kubeconfig_context_t *kubeconfig_context_create()
{
    kubeconfig_context_t *context = calloc(1, sizeof(kubeconfig_context_t));
    return context;
}

void kubeconfig_context_free(kubeconfig_context_t * context)
{
    if (!context) {
        return;
    }

    if (context->name) {
        free(context->name);
    }
    if (context->cluster) {
        free(context->cluster);
    }
    if (context->user) {
        free(context->user);
    }
}

kubeconfig_t *kubeconfig_create()
{
    kubeconfig_t *config = calloc(1, sizeof(kubeconfig_t));
    return config;
}

static void kubeconfig_clusters_free(kubeconfig_cluster_t ** clusters, int cluster_count)
{
    if (!clusters) {
        return;
    }

    int i = 0;
    for (i = 0; i < cluster_count; i++) {
        if (clusters[i]) {
            kubeconfig_cluster_free(clusters[i]);
            clusters[i] = NULL;
        }
    }
    free(clusters);
}

static void kubeconfig_users_free(kubeconfig_user_t ** users, int users_count)
{
    if (!users) {
        return;
    }

    int i = 0;
    for (i = 0; i < users_count; i++) {
        if (users[i]) {
            kubeconfig_user_free(users[i]);
            users[i] = NULL;
        }
    }
    free(users);
}

static void kubeconfig_contexts_free(kubeconfig_context_t ** contexts, int context_count)
{
    if (!contexts) {
        return;
    }

    int i = 0;
    for (i = 0; i < context_count; i++) {
        if (contexts[i]) {
            kubeconfig_context_free(contexts[i]);
            contexts[i] = NULL;
        }
    }
    free(contexts);
}

void kubeconfig_free(kubeconfig_t * kubeconfig)
{
    if (!kubeconfig) {
        return;
    }

    if (kubeconfig->fileName) {
        free(kubeconfig->fileName);
    }
    if (kubeconfig->apiVersion) {
        free(kubeconfig->apiVersion);
    }
    if (kubeconfig->kind) {
        free(kubeconfig->kind);
    }
    if (kubeconfig->preferences) {
        free(kubeconfig->preferences);
    }
    if (kubeconfig->current_context) {
        free(kubeconfig->current_context);
    }
    if (kubeconfig->clusters) {
        kubeconfig_clusters_free(kubeconfig->clusters, kubeconfig->clusters_count);
    }
    if (kubeconfig->users) {
        kubeconfig_users_free(kubeconfig->users, kubeconfig->users_count);
    }
    if (kubeconfig->contexts) {
        kubeconfig_contexts_free(kubeconfig->contexts, kubeconfig->contexts_count);
    }

}
