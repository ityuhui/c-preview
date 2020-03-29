#include "kube_config.h"
#include "kube_config_model.h"

#define KUBE_CONFIG_DEFAULT_LOCATION "~/.kube/config"
#define K8S_TOKEN_BUF_SIZE 1024
#define K8S_AUTH_KEY "Authorization"
#define K8S_AUTH_VALUE_TEMPLATE "Bearer %s"


static int setBasePath()
{
    char *basePath = strdup();
    if(basePath){
        *pBasePath = basePath ;
    }else{
        rc = -1;
    }

}

static int setSslConfig(sslConfig_t **pSslConfig)
{
    int rc = 0;
    char *cafile;
    save2file(cafile);

    sslConfig_t *sc = sslConfig_create(clientCert,clientKey,caFile,0);
    if(sc){
        *pSslConfig = sc ;
    }else{
        rc = -1;
    }
    return rc ;
}

static int setApiKeys()
{
 list_t *apiKeys = list_create();
        if(apiKeys){
            char *keyToken = strdup(K8S_AUTH_KEY);
            char valueToken[K8S_TOKEN_BUF_SIZE];
            memset(valueToken, 0, sizeof(valueToken));
            sprintf(valueToken, K8S_AUTH_VALUE_TEMPLATE, token_out_of_cluster);

            keyValuePair_t *keyPairToken = keyValuePair_create(keyToken, valueToken);
            list_addElement(apiKeys, keyPairToken);

            *pApiKeys = apiKeys ;
        }else{
            rc = -1;
        }

}

static char *getConfigFileTakeEffect(const char *configFileName)
{
    char *_configFileName = NULL;
    if ( configFileName && configFileName[0] != '\0' ) {
        _configFileName = configFileName;
    } else {
        _configFileName = KUBE_CONFIG_DEFAULT_LOCATION;
    }
    return _configFileName;
}

static int loadKubeConfigFile(kubeconfig_t* kubeConfig, const char * configFileTakeEffect)
{
    int rc = 0;

    kubeyaml_loadkubeconfig(kubeConfig, configFileTakeEffect);

    return 0;
}

int load_kube_config(char **pBasePath, sslConfig_t **pSslConfig, list_t **pApiKeys, const char *configFileName)
{
    int rc = 0;

    char *configFileTakeEffect = getConfigFileTakeEffect(configFileName);

    kubeconfig_t* kubeconfig = calloc(1, sizeof(kubeconfig_t));
    kubeconfig->fileName = strdup(configFileTakeEffect);
    kubeyaml_loadkubeconfig(kubeconfig);

    if(){
        setBasePath();
    }

    if(){
        setSslConfig();
    }
    
    if( token_out_of_cluster ){
        setApiKeys();
    }

    return rc;
}


int free_kube_config(char *basePath, sslConfig_t *sslConfig, list_t *apiKeys)
{
    int rc = 0;

    if(basePath){
        free(basePath);
    }

    if(sslConfig){
        sslConfig_free(sslConfig);
    }

    return 0;
}

