#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "v1_controller_revision_list.h"



v1_controller_revision_list_t *v1_controller_revision_list_create(
    char *api_version,
    list_t *items,
    char *kind,
    v1_list_meta_t *metadata
    ) {
    v1_controller_revision_list_t *v1_controller_revision_list_local_var = malloc(sizeof(v1_controller_revision_list_t));
    if (!v1_controller_revision_list_local_var) {
        return NULL;
    }
    v1_controller_revision_list_local_var->api_version = api_version;
    v1_controller_revision_list_local_var->items = items;
    v1_controller_revision_list_local_var->kind = kind;
    v1_controller_revision_list_local_var->metadata = metadata;

    return v1_controller_revision_list_local_var;
}


void v1_controller_revision_list_free(v1_controller_revision_list_t *v1_controller_revision_list) {
    listEntry_t *listEntry;
    free(v1_controller_revision_list->api_version);
    list_ForEach(listEntry, v1_controller_revision_list->items) {
        v1_controller_revision_free(listEntry->data);
    }
    list_free(v1_controller_revision_list->items);
    free(v1_controller_revision_list->kind);
    v1_list_meta_free(v1_controller_revision_list->metadata);
    free(v1_controller_revision_list);
}

cJSON *v1_controller_revision_list_convertToJSON(v1_controller_revision_list_t *v1_controller_revision_list) {
    cJSON *item = cJSON_CreateObject();

    // v1_controller_revision_list->api_version
    if(v1_controller_revision_list->api_version) { 
    if(cJSON_AddStringToObject(item, "apiVersion", v1_controller_revision_list->api_version) == NULL) {
    goto fail; //String
    }
     } 


    // v1_controller_revision_list->items
    if (!v1_controller_revision_list->items) {
        goto fail;
    }
    
    cJSON *items = cJSON_AddArrayToObject(item, "items");
    if(items == NULL) {
    goto fail; //nonprimitive container
    }

    listEntry_t *itemsListEntry;
    if (v1_controller_revision_list->items) {
    list_ForEach(itemsListEntry, v1_controller_revision_list->items) {
    cJSON *itemLocal = v1_controller_revision_convertToJSON(itemsListEntry->data);
    if(itemLocal == NULL) {
    goto fail;
    }
    cJSON_AddItemToArray(items, itemLocal);
    }
    }


    // v1_controller_revision_list->kind
    if(v1_controller_revision_list->kind) { 
    if(cJSON_AddStringToObject(item, "kind", v1_controller_revision_list->kind) == NULL) {
    goto fail; //String
    }
     } 


    // v1_controller_revision_list->metadata
    if(v1_controller_revision_list->metadata) { 
    cJSON *metadata_local_JSON = v1_list_meta_convertToJSON(v1_controller_revision_list->metadata);
    if(metadata_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "metadata", metadata_local_JSON);
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

v1_controller_revision_list_t *v1_controller_revision_list_parseFromJSON(cJSON *v1_controller_revision_listJSON){

    v1_controller_revision_list_t *v1_controller_revision_list_local_var = NULL;

    // v1_controller_revision_list->api_version
    cJSON *api_version = cJSON_GetObjectItemCaseSensitive(v1_controller_revision_listJSON, "apiVersion");
    if (api_version) { 
    if(!cJSON_IsString(api_version))
    {
    goto end; //String
    }
    }

    // v1_controller_revision_list->items
    cJSON *items = cJSON_GetObjectItemCaseSensitive(v1_controller_revision_listJSON, "items");
    if (!items) {
        goto end;
    }

    list_t *itemsList;
    
    cJSON *items_local_nonprimitive;
    if(!cJSON_IsArray(items)){
        goto end; //nonprimitive container
    }

    itemsList = list_create();

    cJSON_ArrayForEach(items_local_nonprimitive,items )
    {
        if(!cJSON_IsObject(items_local_nonprimitive)){
            goto end;
        }
        v1_controller_revision_t *itemsItem = v1_controller_revision_parseFromJSON(items_local_nonprimitive);

        list_addElement(itemsList, itemsItem);
    }

    // v1_controller_revision_list->kind
    cJSON *kind = cJSON_GetObjectItemCaseSensitive(v1_controller_revision_listJSON, "kind");
    if (kind) { 
    if(!cJSON_IsString(kind))
    {
    goto end; //String
    }
    }

    // v1_controller_revision_list->metadata
    cJSON *metadata = cJSON_GetObjectItemCaseSensitive(v1_controller_revision_listJSON, "metadata");
    v1_list_meta_t *metadata_local_nonprim = NULL;
    if (metadata) { 
    metadata_local_nonprim = v1_list_meta_parseFromJSON(metadata); //nonprimitive
    }


    v1_controller_revision_list_local_var = v1_controller_revision_list_create (
        api_version ? strdup(api_version->valuestring) : NULL,
        itemsList,
        kind ? strdup(kind->valuestring) : NULL,
        metadata ? metadata_local_nonprim : NULL
        );

    return v1_controller_revision_list_local_var;
end:
    return NULL;

}
