#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "v1beta1_self_subject_rules_review.h"



v1beta1_self_subject_rules_review_t *v1beta1_self_subject_rules_review_create(
    char *api_version,
    char *kind,
    v1_object_meta_t *metadata,
    v1beta1_self_subject_rules_review_spec_t *spec,
    v1beta1_subject_rules_review_status_t *status
    ) {
    v1beta1_self_subject_rules_review_t *v1beta1_self_subject_rules_review_local_var = malloc(sizeof(v1beta1_self_subject_rules_review_t));
    if (!v1beta1_self_subject_rules_review_local_var) {
        return NULL;
    }
    v1beta1_self_subject_rules_review_local_var->api_version = api_version;
    v1beta1_self_subject_rules_review_local_var->kind = kind;
    v1beta1_self_subject_rules_review_local_var->metadata = metadata;
    v1beta1_self_subject_rules_review_local_var->spec = spec;
    v1beta1_self_subject_rules_review_local_var->status = status;

    return v1beta1_self_subject_rules_review_local_var;
}


void v1beta1_self_subject_rules_review_free(v1beta1_self_subject_rules_review_t *v1beta1_self_subject_rules_review) {
    if(NULL == v1beta1_self_subject_rules_review){
        return ;
    }
    listEntry_t *listEntry;
    free(v1beta1_self_subject_rules_review->api_version);
    free(v1beta1_self_subject_rules_review->kind);
    v1_object_meta_free(v1beta1_self_subject_rules_review->metadata);
    v1beta1_self_subject_rules_review_spec_free(v1beta1_self_subject_rules_review->spec);
    v1beta1_subject_rules_review_status_free(v1beta1_self_subject_rules_review->status);
    free(v1beta1_self_subject_rules_review);
}

cJSON *v1beta1_self_subject_rules_review_convertToJSON(v1beta1_self_subject_rules_review_t *v1beta1_self_subject_rules_review) {
    cJSON *item = cJSON_CreateObject();

    // v1beta1_self_subject_rules_review->api_version
    if(v1beta1_self_subject_rules_review->api_version) { 
    if(cJSON_AddStringToObject(item, "apiVersion", v1beta1_self_subject_rules_review->api_version) == NULL) {
    goto fail; //String
    }
     } 


    // v1beta1_self_subject_rules_review->kind
    if(v1beta1_self_subject_rules_review->kind) { 
    if(cJSON_AddStringToObject(item, "kind", v1beta1_self_subject_rules_review->kind) == NULL) {
    goto fail; //String
    }
     } 


    // v1beta1_self_subject_rules_review->metadata
    if(v1beta1_self_subject_rules_review->metadata) { 
    cJSON *metadata_local_JSON = v1_object_meta_convertToJSON(v1beta1_self_subject_rules_review->metadata);
    if(metadata_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "metadata", metadata_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }
     } 


    // v1beta1_self_subject_rules_review->spec
    if (!v1beta1_self_subject_rules_review->spec) {
        goto fail;
    }
    
    cJSON *spec_local_JSON = v1beta1_self_subject_rules_review_spec_convertToJSON(v1beta1_self_subject_rules_review->spec);
    if(spec_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "spec", spec_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }


    // v1beta1_self_subject_rules_review->status
    if(v1beta1_self_subject_rules_review->status) { 
    cJSON *status_local_JSON = v1beta1_subject_rules_review_status_convertToJSON(v1beta1_self_subject_rules_review->status);
    if(status_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "status", status_local_JSON);
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

v1beta1_self_subject_rules_review_t *v1beta1_self_subject_rules_review_parseFromJSON(cJSON *v1beta1_self_subject_rules_reviewJSON){

    v1beta1_self_subject_rules_review_t *v1beta1_self_subject_rules_review_local_var = NULL;

    // v1beta1_self_subject_rules_review->api_version
    cJSON *api_version = cJSON_GetObjectItemCaseSensitive(v1beta1_self_subject_rules_reviewJSON, "apiVersion");
    if (api_version) { 
    if(!cJSON_IsString(api_version))
    {
    goto end; //String
    }
    }

    // v1beta1_self_subject_rules_review->kind
    cJSON *kind = cJSON_GetObjectItemCaseSensitive(v1beta1_self_subject_rules_reviewJSON, "kind");
    if (kind) { 
    if(!cJSON_IsString(kind))
    {
    goto end; //String
    }
    }

    // v1beta1_self_subject_rules_review->metadata
    cJSON *metadata = cJSON_GetObjectItemCaseSensitive(v1beta1_self_subject_rules_reviewJSON, "metadata");
    v1_object_meta_t *metadata_local_nonprim = NULL;
    if (metadata) { 
    metadata_local_nonprim = v1_object_meta_parseFromJSON(metadata); //nonprimitive
    }

    // v1beta1_self_subject_rules_review->spec
    cJSON *spec = cJSON_GetObjectItemCaseSensitive(v1beta1_self_subject_rules_reviewJSON, "spec");
    if (!spec) {
        goto end;
    }

    v1beta1_self_subject_rules_review_spec_t *spec_local_nonprim = NULL;
    
    spec_local_nonprim = v1beta1_self_subject_rules_review_spec_parseFromJSON(spec); //nonprimitive

    // v1beta1_self_subject_rules_review->status
    cJSON *status = cJSON_GetObjectItemCaseSensitive(v1beta1_self_subject_rules_reviewJSON, "status");
    v1beta1_subject_rules_review_status_t *status_local_nonprim = NULL;
    if (status) { 
    status_local_nonprim = v1beta1_subject_rules_review_status_parseFromJSON(status); //nonprimitive
    }


    v1beta1_self_subject_rules_review_local_var = v1beta1_self_subject_rules_review_create (
        api_version ? strdup(api_version->valuestring) : NULL,
        kind ? strdup(kind->valuestring) : NULL,
        metadata ? metadata_local_nonprim : NULL,
        spec_local_nonprim,
        status ? status_local_nonprim : NULL
        );

    return v1beta1_self_subject_rules_review_local_var;
end:
    return NULL;

}
