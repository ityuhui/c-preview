#ifndef _KUBE_CONFIG_UTIL_H
#define _KUBE_CONFIG_UTIL_H

#ifdef  __cplusplus
extern "C" {
#endif

/*
 * kubeconfig_mk_cert_key_tempfile
 *
 * Description:
 *
 * Create a temporary file to persist SSL/TLS certificate or key
 *
 * Return:
 *
 *  char *   :   File name of created temporary file
 *  NULL     :   Failed to create temporary file
 *
 * Parameter:
 *
 * IN:
 * data: raw data of SSL/TLS certificate or key
 *
 * OUT:
 * None
 *
 */
    char* kubeconfig_mk_cert_key_tempfile(const char *data);

/*
 * unsetSslConfig
 *
 * Description:
 *
 * unset the SSL configuration
 *
 * Return:
 * 
 * None
 *
 * Parameter:
 *
 * IN:
 * sslConfig: The SSL configuration
 *
 * OUT:
 * None
 *
 */
    void unsetSslConfig(sslConfig_t* sslConfig);

#ifdef  __cplusplus
}
#endif
#endif                          /* _KUBE_CONFIG_UTIL_H */