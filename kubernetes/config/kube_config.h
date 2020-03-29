#ifndef _KUBE_CONFIG_H
#define _KUBE_CONFIG_H

#ifdef  __cplusplus
extern "C" {
#endif

/*
 * load_kube_config
 *
 * Description:
 *
 * Load kubernetes cluster configuration from the file defined by configFileName
 * or default location: ~/.kube/config
 *
 * Return:
 *
 *   0     Success
 *  -1     Failed
 *
 * Parameter:
 *
 * IN
 *
 * configFileName : kubernetes cluster configuration file name
 *
 * OUT
 *
 * pBasePath: the pointer to API server address
 * pSslConfig: the pointer to SSL configuration for client
 * pApiKeys: the pointer to API tokens for client
 * The memory will be allocated in the function load_kube_config
 * 
 */
int load_kube_config(char** pBasePath, sslConfig_t** pSslConfig, list_t** pApiKeys, const char* configFileName);


/*
 * free_kube_config
 *
 * Description:
 *
 * Help function to free the memory for kubernetes cluster configuration
 *
 * Return:
 *
 *  0     Success
 * -1     Failed
 * 
 * Parameter:
 *
 * IN
 *
 * basePath: API server address
 * sslConfig: SSL configuration for client
 * apiKeys: API tokens for client
 *
 */
int free_kube_config(char* basePath, sslConfig_t* sslConfig, list_t* apiKeys);


#ifdef  __cplusplus
}
#endif


#endif /* _KUBE_CONFIG_H */
