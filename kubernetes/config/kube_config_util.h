#ifndef _KUBE_CONFIG_UTIL_H
#define _KUBE_CONFIG_UTIL_H

#ifdef  __cplusplus
extern "C" {
#endif

char* kubeconfig_mk_cert_key_tempfile(const char*);

void kubeconfig_rm_tempfile(const char*);

#ifdef  __cplusplus
}
#endif
#endif                          /* _KUBE_CONFIG_UTIL_H */