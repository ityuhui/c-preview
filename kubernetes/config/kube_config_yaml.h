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
extern int kubeyaml_load_kubeconfig(kubeconfig_t * kubeconfig);


/*
 * kubeyaml_free_kubeconfig
 *
 *
 * Description:
 *
 * Free the memory for the struct kubeconfig_t
 *
 *
 * Return:
 *
 * None
 * 
 * 
 * Parameter:
 *
 * IN:
 * kubeconfig: The pointer to the kubernetes cluster configuration 
 *
 * OUT:
 * None
 *
 */

extern void kubeyaml_free_kubeconfig(kubeconfig_t * kubeconfig);

#ifdef  __cplusplus
}
#endif                          /* __cplusplus  */
#endif                          /* _KUBE_CONFIG_YAML_H */
