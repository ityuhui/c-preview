#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "v1beta1_self_subject_access_review_spec.h"



v1beta1_self_subject_access_review_spec_t *v1beta1_self_subject_access_review_spec_create(
    v1beta1_non_resource_attributes_t *non_resource_attributes,
    v1beta1_resource_attributes_t *resource_attributes
    ) {
    v1beta1_self_subject_access_review_spec_t *v1beta1_self_subject_access_review_spec_local_var = malloc(sizeof(v1beta1_self_subject_access_review_spec_t));
    if (!v1beta1_self_subject_access_review_spec_local_var) {
        return NULL;
    }
    v1beta1_self_subject_access_review_spec_local_var->non_resource_attributes = non_resource_attributes;
    v1beta1_self_subject_access_review_spec_local_var->resource_attributes = resource_attributes;

    return v1beta1_self_subject_access_review_spec_local_var;
}


void v1beta1_self_subject_access_review_spec_free(v1beta1_self_subject_access_review_spec_t *v1beta1_self_subject_access_review_spec) {
    if(NULL == v1beta1_self_subject_access_review_spec){
        return ;
    }
    listEntry_t *listEntry;
    v1beta1_non_resource_attributes_free(v1beta1_self_subject_access_review_spec->non_resource_attributes);
    v1beta1_resource_attributes_free(v1beta1_self_subject_access_review_spec->resource_attributes);
    free(v1beta1_self_subject_access_review_spec);
}

cJSON *v1beta1_self_subject_access_review_spec_convertToJSON(v1beta1_self_subject_access_review_spec_t *v1beta1_self_subject_access_review_spec) {
    cJSON *item = cJSON_CreateObject();

    // v1beta1_self_subject_access_review_spec->non_resource_attributes
    if(v1beta1_self_subject_access_review_spec->non_resource_attributes) { 
    cJSON *non_resource_attributes_local_JSON = v1beta1_non_resource_attributes_convertToJSON(v1beta1_self_subject_access_review_spec->non_resource_attributes);
    if(non_resource_attributes_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "nonResourceAttributes", non_resource_attributes_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }
     } 


    // v1beta1_self_subject_access_review_spec->resource_attributes
    if(v1beta1_self_subject_access_review_spec->resource_attributes) { 
    cJSON *resource_attributes_local_JSON = v1beta1_resource_attributes_convertToJSON(v1beta1_self_subject_access_review_spec->resource_attributes);
    if(resource_attributes_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "resourceAttributes", resource_attributes_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }
     } 

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

v1beta1_self_subject_access_review_spec_t *v1beta1_self_subject_access_review_spec_parseFromJSON(cJSON *v1beta1_self_subject_access_review_specJSON){

    v1beta1_self_subject_access_review_spec_t *v1beta1_self_subject_access_review_spec_local_var = NULL;

    // v1beta1_self_subject_access_review_spec->non_resource_attributes
    cJSON *non_resource_attributes = cJSON_GetObjectItemCaseSensitive(v1beta1_self_subject_access_review_specJSON, "nonResourceAttributes");
    v1beta1_non_resource_attributes_t *non_resource_attributes_local_nonprim = NULL;
    if (non_resource_attributes) { 
    non_resource_attributes_local_nonprim = v1beta1_non_resource_attributes_parseFromJSON(non_resource_attributes); //nonprimitive
    }

    // v1beta1_self_subject_access_review_spec->resource_attributes
    cJSON *resource_attributes = cJSON_GetObjectItemCaseSensitive(v1beta1_self_subject_access_review_specJSON, "resourceAttributes");
    v1beta1_resource_attributes_t *resource_attributes_local_nonprim = NULL;
    if (resource_attributes) { 
    resource_attributes_local_nonprim = v1beta1_resource_attributes_parseFromJSON(resource_attributes); //nonprimitive
    }


    v1beta1_self_subject_access_review_spec_local_var = v1beta1_self_subject_access_review_spec_create (
        non_resource_attributes ? non_resource_attributes_local_nonprim : NULL,
        resource_attributes ? resource_attributes_local_nonprim : NULL
        );

    return v1beta1_self_subject_access_review_spec_local_var;
end:
    return NULL;

}
