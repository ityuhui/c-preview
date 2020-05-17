#ifndef _EXEC_PROVIDER_H
#define _EXEC_PROVIDER_H

#include "kube_config_model.h"

#ifdef  __cplusplus
extern "C" {
#endif

    /*
     * kubeconfig_exec_run
     *
     *
     * Description:
     *
     *
     * Load kubernetes cluster configuration from service account
     * files inside a pod
     *
     *
     * Return:
     *
     *   0     Success
     *  -1     Failed
     *
     *
     * Parameter:
     *
     *
     * IN:

     * None
     *
     *
     * OUT:
     *
     * pBasePath: The pointer to API server address
     * pSslConfig: The pointer to SSL configuration for client
     * pApiKeys: The pointer to API tokens for client
     *
     * The memory will be allocated inside this function. User
     * should call free_client_config to free the memory after
     * these parameters are not used.
     *
     */

    int kube_exec_and_get_result(ExecCredential_t * exec_credential, const kubeconfig_property_t * exec);

#ifdef  __cplusplus
}
#endif
#endif                          /* _EXEC_PROVIDER_H */
