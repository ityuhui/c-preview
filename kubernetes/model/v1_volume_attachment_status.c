#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "v1_volume_attachment_status.h"



v1_volume_attachment_status_t *v1_volume_attachment_status_create(
    v1_volume_error_t *attach_error,
    int attached,
    list_t* attachment_metadata,
    v1_volume_error_t *detach_error
    ) {
    v1_volume_attachment_status_t *v1_volume_attachment_status_local_var = malloc(sizeof(v1_volume_attachment_status_t));
    if (!v1_volume_attachment_status_local_var) {
        return NULL;
    }
    v1_volume_attachment_status_local_var->attach_error = attach_error;
    v1_volume_attachment_status_local_var->attached = attached;
    v1_volume_attachment_status_local_var->attachment_metadata = attachment_metadata;
    v1_volume_attachment_status_local_var->detach_error = detach_error;

    return v1_volume_attachment_status_local_var;
}


void v1_volume_attachment_status_free(v1_volume_attachment_status_t *v1_volume_attachment_status) {
    listEntry_t *listEntry;
    v1_volume_error_free(v1_volume_attachment_status->attach_error);
    list_ForEach(listEntry, v1_volume_attachment_status->attachment_metadata) {
        keyValuePair_t *localKeyValue = (keyValuePair_t*) listEntry->data;
        free (localKeyValue->key);
        free (localKeyValue->value);
    }
    list_free(v1_volume_attachment_status->attachment_metadata);
    v1_volume_error_free(v1_volume_attachment_status->detach_error);
    free(v1_volume_attachment_status);
}

cJSON *v1_volume_attachment_status_convertToJSON(v1_volume_attachment_status_t *v1_volume_attachment_status) {
    cJSON *item = cJSON_CreateObject();

    // v1_volume_attachment_status->attach_error
    if(v1_volume_attachment_status->attach_error) { 
    cJSON *attach_error_local_JSON = v1_volume_error_convertToJSON(v1_volume_attachment_status->attach_error);
    if(attach_error_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "attachError", attach_error_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }
     } 


    // v1_volume_attachment_status->attached
    if (!v1_volume_attachment_status->attached) {
        goto fail;
    }
    
    if(cJSON_AddBoolToObject(item, "attached", v1_volume_attachment_status->attached) == NULL) {
    goto fail; //Bool
    }


    // v1_volume_attachment_status->attachment_metadata
    if(v1_volume_attachment_status->attachment_metadata) { 
    cJSON *attachment_metadata = cJSON_AddObjectToObject(item, "attachmentMetadata");
    if(attachment_metadata == NULL) {
        goto fail; //primitive map container
    }
    cJSON *localMapObject = attachment_metadata;
    listEntry_t *attachment_metadataListEntry;
    if (v1_volume_attachment_status->attachment_metadata) {
    list_ForEach(attachment_metadataListEntry, v1_volume_attachment_status->attachment_metadata) {
        keyValuePair_t *localKeyValue = (keyValuePair_t*)attachment_metadataListEntry->data;
        if(cJSON_AddStringToObject(localMapObject, localKeyValue->key, (char*)localKeyValue->value) == NULL)
        {
            goto fail;
        }
    }
    }
     } 


    // v1_volume_attachment_status->detach_error
    if(v1_volume_attachment_status->detach_error) { 
    cJSON *detach_error_local_JSON = v1_volume_error_convertToJSON(v1_volume_attachment_status->detach_error);
    if(detach_error_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "detachError", detach_error_local_JSON);
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

v1_volume_attachment_status_t *v1_volume_attachment_status_parseFromJSON(cJSON *v1_volume_attachment_statusJSON){

    v1_volume_attachment_status_t *v1_volume_attachment_status_local_var = NULL;

    // v1_volume_attachment_status->attach_error
    cJSON *attach_error = cJSON_GetObjectItemCaseSensitive(v1_volume_attachment_statusJSON, "attachError");
    v1_volume_error_t *attach_error_local_nonprim = NULL;
    if (attach_error) { 
    attach_error_local_nonprim = v1_volume_error_parseFromJSON(attach_error); //nonprimitive
    }

    // v1_volume_attachment_status->attached
    cJSON *attached = cJSON_GetObjectItemCaseSensitive(v1_volume_attachment_statusJSON, "attached");
    if (!attached) {
        goto end;
    }

    
    if(!cJSON_IsBool(attached))
    {
    goto end; //Bool
    }

    // v1_volume_attachment_status->attachment_metadata
    cJSON *attachment_metadata = cJSON_GetObjectItemCaseSensitive(v1_volume_attachment_statusJSON, "attachmentMetadata");
    list_t *attachment_metadataList;
    if (attachment_metadata) { 
    cJSON *attachment_metadata_local_map;
    if(!cJSON_IsObject(attachment_metadata)) {
        goto end;//primitive map container
    }
    attachment_metadataList = list_create();
    keyValuePair_t *localMapKeyPair;
    cJSON_ArrayForEach(attachment_metadata_local_map, attachment_metadata)
    {
		cJSON *localMapObject = attachment_metadata_local_map;
        if(!cJSON_IsString(localMapObject))
        {
            goto end;
        }
        localMapKeyPair = keyValuePair_create(strdup(localMapObject->string),strdup(localMapObject->valuestring));
        list_addElement(attachment_metadataList , localMapKeyPair);
    }
    }

    // v1_volume_attachment_status->detach_error
    cJSON *detach_error = cJSON_GetObjectItemCaseSensitive(v1_volume_attachment_statusJSON, "detachError");
    v1_volume_error_t *detach_error_local_nonprim = NULL;
    if (detach_error) { 
    detach_error_local_nonprim = v1_volume_error_parseFromJSON(detach_error); //nonprimitive
    }


    v1_volume_attachment_status_local_var = v1_volume_attachment_status_create (
        attach_error ? attach_error_local_nonprim : NULL,
        attached->valueint,
        attachment_metadata ? attachment_metadataList : NULL,
        detach_error ? detach_error_local_nonprim : NULL
        );

    return v1_volume_attachment_status_local_var;
end:
    return NULL;

}
