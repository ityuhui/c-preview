#ifndef _KUBE_CONFIG_YAML_H
#define _KUBE_CONFIG_YAML_H

#include "kube_config_model.h"

#ifdef  __cplusplus
extern "C" {

#endif                          /* __cplusplus */

/*
 * kubeyaml_load_kubeconfig
 *
 * Description:
 *
 * Load the kubeconfig file specified by kubeconfig->fileName
 * and get the kuberntes configuration for other fields of kubeconfig.
 *
 * Return:
 *
 *   0     Success
 *  -1     Failed
 *
 * Parameter:
 *
 * IN:
 * kubeconfig->fileName: kubernetes cluster configuration file name
 *
 * OUT:
 * kubeconfig: kubernetes cluster configuration
 */
    int kubeyaml_load_kubeconfig(kubeconfig_t * kubeconfig);

/*
 * kubeyaml_parse_exec_crendentail
 *
 * Description:
 *
 * parse the string to get the data fields of kubeconfig exec result.
 *
 * Return:
 *
 *   0     Success
 *  -1     Failed
 *
 * Parameter:
 *
 * IN:
 * exec_credential_string: raw string of kubeconfig exec result
 * exec_credential_string_length: the length of exec_credential_string
 *
 * OUT:
 * exec_credential: data structure of kubeconfig exec result
 */
    int kubeyaml_parse_exec_crendentail(ExecCredential_t * exec_credential, const char *exec_credential_string);

#ifdef  __cplusplus
}
#endif                          /* __cplusplus  */
#endif                          /* _KUBE_CONFIG_YAML_H */
