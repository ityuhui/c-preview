/*
 * v1alpha1_role_binding.h
 *
 * RoleBinding references a role, but does not contain it.  It can reference a Role in the same namespace or a ClusterRole in the global namespace. It adds who information via Subjects and namespace information by which namespace it exists in.  RoleBindings in a given namespace only have effect in that namespace. Deprecated in v1.17 in favor of rbac.authorization.k8s.io/v1 RoleBinding, and will no longer be served in v1.20.
 */

#ifndef _v1alpha1_role_binding_H_
#define _v1alpha1_role_binding_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "rbac_v1alpha1_subject.h"
#include "v1_object_meta.h"
#include "v1alpha1_role_ref.h"



typedef struct v1alpha1_role_binding_t {
    char *api_version; // string
    char *kind; // string
    struct v1_object_meta_t *metadata; //model
    struct v1alpha1_role_ref_t *role_ref; //model
    list_t *subjects; //nonprimitive container

} v1alpha1_role_binding_t;

v1alpha1_role_binding_t *v1alpha1_role_binding_create(
    char *api_version,
    char *kind,
    v1_object_meta_t *metadata,
    v1alpha1_role_ref_t *role_ref,
    list_t *subjects
);

void v1alpha1_role_binding_free(v1alpha1_role_binding_t *v1alpha1_role_binding);

v1alpha1_role_binding_t *v1alpha1_role_binding_parseFromJSON(cJSON *v1alpha1_role_bindingJSON);

cJSON *v1alpha1_role_binding_convertToJSON(v1alpha1_role_binding_t *v1alpha1_role_binding);

#endif /* _v1alpha1_role_binding_H_ */

