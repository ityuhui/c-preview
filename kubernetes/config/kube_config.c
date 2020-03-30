#include "kube_config.h"
#include "kube_config_yaml.h"

#define KUBE_CONFIG_ENV_NAME "KUBECONFIG"
#define KUBE_CONFIG_DEFAULT_LOCATION "~/.kube/config"
#define K8S_TOKEN_BUF_SIZE 1024
#define K8S_AUTH_KEY "Authorization"
#define K8S_AUTH_VALUE_TEMPLATE "Bearer %s"


static int setBasePath(char ** pBasePath, char *basePath)
{
    int rc = 0;
    char *_basePath = strdup(basePath);
    if(_basePath){
        *pBasePath = _basePath ;
    }else{
        rc = -1;
    }
    return rc;

}

static char * kubeconfig_mk_tempfile(const char * b64data)
{
    int decoded_bytes = 0;
    char *b64decode = base64decode(b64data, strlen(b64data),&decoded_bytes);
    return b64decode;
}

static void kubeconfig_rm_tempfile(const char *filename)
{

}
static void unsetSslConfig(sslConfig_t * sslConfig)
{
    if (!sslConfig) {
        return;
    }

    if (sslConfig->clientCertFile) {
        kubeconfig_rm_tempfile(sslConfig->clientCertFile);
    }
    if (sslConfig->clientKeyFile) {
        kubeconfig_rm_tempfile(sslConfig->clientKeyFile);
    }
    if (sslConfig->CACertFile) {
        kubeconfig_rm_tempfile(sslConfig->CACertFile);
    }

}

static int setSslConfig(sslConfig_t **pSslConfig, kubeconfig_cluster_t *cluster, kubeconfig_user_t *user)
{
    int rc = 0;
    char *client_cert_file = NULL;
    char *client_key_file = NULL;
    char *ca_file = NULL;
    int insecure_skip_tls_verify = 1;

    if (user) {
        if ( user->client_certificate_data ) {
            client_cert_file = kubeconfig_mktempfile(user->client_certificate_data);
        }
        if ( user->client_key_data ) {
            client_key_file = kubeconfig_mktempfile(user->client_key_data);
        }
        insecure_skip_tls_verify = user->insecure_skip_tls_verify;
    }

    if (cluster) {
        if ( (0 == insecure_skip_tls_verify) &&
             (cluster->certificate_authority_data) ) {
            ca_file = mktempfile(cluster->certificate_authority_data);
        }
    }

    sslConfig_t *sc = sslConfig_create(client_cert_file, client_key_file, ca_file, insecure_skip_tls_verify);
    if (sc) {
        *pSslConfig = sc ;
    } else {
        rc = -1;
    }
    return rc;
}

static int setApiKeys(list_t ** pApiKeys, kubeconfig_user_t *user)
{
    int rc = 0;
    list_t *apiKeys = list_create();
    if ( apiKeys ){
        
        /* under development for the token based authentication */

        /*
        char *keyToken = strdup(K8S_AUTH_KEY);
        char valueToken[K8S_TOKEN_BUF_SIZE];
        memset(valueToken, 0, sizeof(valueToken));
        sprintf(valueToken, K8S_AUTH_VALUE_TEMPLATE, token_out_of_cluster);
        keyValuePair_t *keyPairToken = keyValuePair_create(keyToken, valueToken);
        list_addElement(apiKeys, keyPairToken);
        */

        *pApiKeys = apiKeys ;
    }else{
        rc = -1;
    }
    return rc;
}

static char *getConfigFileTakeEffect(const char *configFileName)
{
    char *_configFileName = NULL;
    if (configFileName && configFileName[0] != '\0') {
        _configFileName = configFileName;
    } else {
        _configFileName = getenv(KUBE_CONFIG_ENV_NAME);
        if (NULL == _configFileName) {
            _configFileName = KUBE_CONFIG_DEFAULT_LOCATION;
        }
    }
    return _configFileName;
}

static kubeconfig_context_t * kubeconfig_get_current_context(kubeconfig_context_t** contexts, int contexts_count, const char *current_context_str)
{
    kubeconfig_context_t *current_context = NULL;

    if (NULL == contexts || 
        NULL == current_context_str) {
        return NULL;
    }

    int i = 0;
    for (i = 0; i < contexts_count; i++) {
        if (0 == strcmp(contexts[i]->name, current_context_str)) {
            current_context = contexts[i];
            break;
        }
    }

    return current_context;
}

static kubeconfig_cluster_t * kubeconfig_get_current_cluster(kubeconfig_cluster_t ** clusters, int clusters_count, const char *cluster_name)
{
    kubeconfig_cluster_t *current_cluster = NULL;

    if ( NULL == clusters || 
        NULL == cluster_name) {
        return NULL;
    }

    int i = 0;
    for (i = 0; i < clusters_count;i++) {
        if ( 0 == strcmp(clusters[i]->name, cluster_name)) {
            current_cluster = clusters[i];
            break;
        }
    }

    return current_cluster;
}

static kubeconfig_user_t* kubeconfig_get_current_user(kubeconfig_user_t **users, int users_count, const char* user_name)
{
    kubeconfig_user_t* current_user = NULL;

    if ( NULL == users ||
        NULL == user_name) {
        return NULL;
    }

    int i = 0;
    for (i = 0; i < users_count; i++) {
        if (0 == strcmp(users[i]->name, user_name)) {
            current_user = users[i];
            break;
        }
    }

    return current_user;
}

static kubeconfig_user_t * kubeconfig_get_current_user(kubeconfig_t* kubeconfig)
{
    return kubeconfig->users[0];
}

int load_kube_config(char **pBasePath, sslConfig_t **pSslConfig, list_t **pApiKeys, const char *configFileName)
{
    int rc = 0;

    kubeconfig_context_t* current_context = NULL;
    kubeconfig_cluster_t *current_cluster = NULL;
    kubeconfig_user_t *current_user = NULL;

    char *configFileTakeEffect = getConfigFileTakeEffect(configFileName);
    kubeconfig_t* kubeconfig = calloc(1, sizeof(kubeconfig_t));
    kubeconfig->fileName = strdup(configFileTakeEffect);
    rc = kubeyaml_load_kubeconfig(kubeconfig);
    if ( 0 == rc ) {
        current_context = kubeconfig_get_current_context(kubeconfig->contexts, kubeconfig->contexts_count, kubeconfig->current_context);
        if (current_context) {
            current_cluster = kubeconfig_get_current_cluster(kubeconfig->clusters,kubeconfig->clusters_count, current_context->cluster);
            current_user = kubeconfig_get_current_user(kubeconfig->users, kubeconfig->users_count, current_context->user);
        } else {
            fprintf(stderr, "Cannot get the current user and cluster information for kubeconfig.\n");
            return -1;
        }
    } else {
        fprintf(stderr, "Cannot load the kubeconfig %s\n", configFileTakeEffect);
        return -1;
    }

    if(current_cluster && current_cluster->server ){
        setBasePath(pBasePath,current_cluster->server);
    }

    if( current_cluster || current_user ){
        setSslConfig(pSslConfig, current_cluster, current_user);
    }
    
    if(current_user){
        setApiKeys(pApiKeys, current_user);
    }

    kubeyaml_free_kubeconfig(kubeconfig);
    kubeconfig = NULL;

    return rc;
}


int free_kube_config(char* basePath, sslConfig_t* sslConfig, list_t* apiKeys)
{
    int rc = 0;

    if (basePath) {
        free(basePath);
    }

    if (sslConfig) {
        unsetSslConfig(sslConfig);
        sslConfig_free(sslConfig);
    }

    if (apiKeys) {
        list_free(apiKeys);
    }

    return 0;
}

