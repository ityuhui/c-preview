#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "v1_storage_os_persistent_volume_source.h"



v1_storage_os_persistent_volume_source_t *v1_storage_os_persistent_volume_source_create(
    char *fs_type,
    int read_only,
    v1_object_reference_t *secret_ref,
    char *volume_name,
    char *volume_namespace
    ) {
    v1_storage_os_persistent_volume_source_t *v1_storage_os_persistent_volume_source_local_var = malloc(sizeof(v1_storage_os_persistent_volume_source_t));
    if (!v1_storage_os_persistent_volume_source_local_var) {
        return NULL;
    }
    v1_storage_os_persistent_volume_source_local_var->fs_type = fs_type;
    v1_storage_os_persistent_volume_source_local_var->read_only = read_only;
    v1_storage_os_persistent_volume_source_local_var->secret_ref = secret_ref;
    v1_storage_os_persistent_volume_source_local_var->volume_name = volume_name;
    v1_storage_os_persistent_volume_source_local_var->volume_namespace = volume_namespace;

    return v1_storage_os_persistent_volume_source_local_var;
}


void v1_storage_os_persistent_volume_source_free(v1_storage_os_persistent_volume_source_t *v1_storage_os_persistent_volume_source) {
    if(NULL == v1_storage_os_persistent_volume_source){
        return ;
    }
    listEntry_t *listEntry;
    free(v1_storage_os_persistent_volume_source->fs_type);
    v1_object_reference_free(v1_storage_os_persistent_volume_source->secret_ref);
    free(v1_storage_os_persistent_volume_source->volume_name);
    free(v1_storage_os_persistent_volume_source->volume_namespace);
    free(v1_storage_os_persistent_volume_source);
}

cJSON *v1_storage_os_persistent_volume_source_convertToJSON(v1_storage_os_persistent_volume_source_t *v1_storage_os_persistent_volume_source) {
    cJSON *item = cJSON_CreateObject();

    // v1_storage_os_persistent_volume_source->fs_type
    if(v1_storage_os_persistent_volume_source->fs_type) { 
    if(cJSON_AddStringToObject(item, "fsType", v1_storage_os_persistent_volume_source->fs_type) == NULL) {
    goto fail; //String
    }
     } 


    // v1_storage_os_persistent_volume_source->read_only
    if(v1_storage_os_persistent_volume_source->read_only) { 
    if(cJSON_AddBoolToObject(item, "readOnly", v1_storage_os_persistent_volume_source->read_only) == NULL) {
    goto fail; //Bool
    }
     } 


    // v1_storage_os_persistent_volume_source->secret_ref
    if(v1_storage_os_persistent_volume_source->secret_ref) { 
    cJSON *secret_ref_local_JSON = v1_object_reference_convertToJSON(v1_storage_os_persistent_volume_source->secret_ref);
    if(secret_ref_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "secretRef", secret_ref_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }
     } 


    // v1_storage_os_persistent_volume_source->volume_name
    if(v1_storage_os_persistent_volume_source->volume_name) { 
    if(cJSON_AddStringToObject(item, "volumeName", v1_storage_os_persistent_volume_source->volume_name) == NULL) {
    goto fail; //String
    }
     } 


    // v1_storage_os_persistent_volume_source->volume_namespace
    if(v1_storage_os_persistent_volume_source->volume_namespace) { 
    if(cJSON_AddStringToObject(item, "volumeNamespace", v1_storage_os_persistent_volume_source->volume_namespace) == NULL) {
    goto fail; //String
    }
     } 

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

v1_storage_os_persistent_volume_source_t *v1_storage_os_persistent_volume_source_parseFromJSON(cJSON *v1_storage_os_persistent_volume_sourceJSON){

    v1_storage_os_persistent_volume_source_t *v1_storage_os_persistent_volume_source_local_var = NULL;

    // v1_storage_os_persistent_volume_source->fs_type
    cJSON *fs_type = cJSON_GetObjectItemCaseSensitive(v1_storage_os_persistent_volume_sourceJSON, "fsType");
    if (fs_type) { 
    if(!cJSON_IsString(fs_type))
    {
    goto end; //String
    }
    }

    // v1_storage_os_persistent_volume_source->read_only
    cJSON *read_only = cJSON_GetObjectItemCaseSensitive(v1_storage_os_persistent_volume_sourceJSON, "readOnly");
    if (read_only) { 
    if(!cJSON_IsBool(read_only))
    {
    goto end; //Bool
    }
    }

    // v1_storage_os_persistent_volume_source->secret_ref
    cJSON *secret_ref = cJSON_GetObjectItemCaseSensitive(v1_storage_os_persistent_volume_sourceJSON, "secretRef");
    v1_object_reference_t *secret_ref_local_nonprim = NULL;
    if (secret_ref) { 
    secret_ref_local_nonprim = v1_object_reference_parseFromJSON(secret_ref); //nonprimitive
    }

    // v1_storage_os_persistent_volume_source->volume_name
    cJSON *volume_name = cJSON_GetObjectItemCaseSensitive(v1_storage_os_persistent_volume_sourceJSON, "volumeName");
    if (volume_name) { 
    if(!cJSON_IsString(volume_name))
    {
    goto end; //String
    }
    }

    // v1_storage_os_persistent_volume_source->volume_namespace
    cJSON *volume_namespace = cJSON_GetObjectItemCaseSensitive(v1_storage_os_persistent_volume_sourceJSON, "volumeNamespace");
    if (volume_namespace) { 
    if(!cJSON_IsString(volume_namespace))
    {
    goto end; //String
    }
    }


    v1_storage_os_persistent_volume_source_local_var = v1_storage_os_persistent_volume_source_create (
        fs_type ? strdup(fs_type->valuestring) : NULL,
        read_only ? read_only->valueint : 0,
        secret_ref ? secret_ref_local_nonprim : NULL,
        volume_name ? strdup(volume_name->valuestring) : NULL,
        volume_namespace ? strdup(volume_namespace->valuestring) : NULL
        );

    return v1_storage_os_persistent_volume_source_local_var;
end:
    return NULL;

}
