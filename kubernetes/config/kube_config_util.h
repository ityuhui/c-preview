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
 * kubeconfig_rm_tempfile
 *
 * Description:
 *
 * Delete the temporary file
 *
 * Return:
 * 
 * None
 *
 * Parameter:
 *
 * IN:
 * filename: The file name of temporary file
 *
 * OUT:
 * None
 *
 */
    void kubeconfig_rm_tempfile(const char *filename);

#ifdef  __cplusplus
}
#endif
#endif                          /* _KUBE_CONFIG_UTIL_H */