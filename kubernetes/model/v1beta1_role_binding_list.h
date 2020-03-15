/*
 * v1beta1_role_binding_list.h
 *
 * RoleBindingList is a collection of RoleBindings Deprecated in v1.17 in favor of rbac.authorization.k8s.io/v1 RoleBindingList, and will no longer be served in v1.20.
 */

#ifndef _v1beta1_role_binding_list_H_
#define _v1beta1_role_binding_list_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "v1_list_meta.h"
#include "v1beta1_role_binding.h"



typedef struct v1beta1_role_binding_list_t {
    char *api_version; // string
    list_t *items; //nonprimitive container
    char *kind; // string
    struct v1_list_meta_t *metadata; //model

} v1beta1_role_binding_list_t;

v1beta1_role_binding_list_t *v1beta1_role_binding_list_create(
    char *api_version,
    list_t *items,
    char *kind,
    v1_list_meta_t *metadata
);

void v1beta1_role_binding_list_free(v1beta1_role_binding_list_t *v1beta1_role_binding_list);

v1beta1_role_binding_list_t *v1beta1_role_binding_list_parseFromJSON(cJSON *v1beta1_role_binding_listJSON);

cJSON *v1beta1_role_binding_list_convertToJSON(v1beta1_role_binding_list_t *v1beta1_role_binding_list);

#endif /* _v1beta1_role_binding_list_H_ */

