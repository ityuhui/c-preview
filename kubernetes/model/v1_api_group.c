#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "v1_api_group.h"



v1_api_group_t *v1_api_group_create(
    char *api_version,
    char *kind,
    char *name,
    v1_group_version_for_discovery_t *preferred_version,
    list_t *server_address_by_client_cid_rs,
    list_t *versions
    ) {
    v1_api_group_t *v1_api_group_local_var = malloc(sizeof(v1_api_group_t));
    if (!v1_api_group_local_var) {
        return NULL;
    }
    v1_api_group_local_var->api_version = api_version;
    v1_api_group_local_var->kind = kind;
    v1_api_group_local_var->name = name;
    v1_api_group_local_var->preferred_version = preferred_version;
    v1_api_group_local_var->server_address_by_client_cid_rs = server_address_by_client_cid_rs;
    v1_api_group_local_var->versions = versions;

    return v1_api_group_local_var;
}


void v1_api_group_free(v1_api_group_t *v1_api_group) {
    listEntry_t *listEntry;
    free(v1_api_group->api_version);
    free(v1_api_group->kind);
    free(v1_api_group->name);
    v1_group_version_for_discovery_free(v1_api_group->preferred_version);
    list_ForEach(listEntry, v1_api_group->server_address_by_client_cid_rs) {
        v1_server_address_by_client_cidr_free(listEntry->data);
    }
    list_free(v1_api_group->server_address_by_client_cid_rs);
    list_ForEach(listEntry, v1_api_group->versions) {
        v1_group_version_for_discovery_free(listEntry->data);
    }
    list_free(v1_api_group->versions);
    free(v1_api_group);
}

cJSON *v1_api_group_convertToJSON(v1_api_group_t *v1_api_group) {
    cJSON *item = cJSON_CreateObject();

    // v1_api_group->api_version
    if(v1_api_group->api_version) { 
    if(cJSON_AddStringToObject(item, "apiVersion", v1_api_group->api_version) == NULL) {
    goto fail; //String
    }
     } 


    // v1_api_group->kind
    if(v1_api_group->kind) { 
    if(cJSON_AddStringToObject(item, "kind", v1_api_group->kind) == NULL) {
    goto fail; //String
    }
     } 


    // v1_api_group->name
    if (!v1_api_group->name) {
        goto fail;
    }
    
    if(cJSON_AddStringToObject(item, "name", v1_api_group->name) == NULL) {
    goto fail; //String
    }


    // v1_api_group->preferred_version
    if(v1_api_group->preferred_version) { 
    cJSON *preferred_version_local_JSON = v1_group_version_for_discovery_convertToJSON(v1_api_group->preferred_version);
    if(preferred_version_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "preferredVersion", preferred_version_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }
     } 


    // v1_api_group->server_address_by_client_cid_rs
    if(v1_api_group->server_address_by_client_cid_rs) { 
    cJSON *server_address_by_client_cid_rs = cJSON_AddArrayToObject(item, "serverAddressByClientCIDRs");
    if(server_address_by_client_cid_rs == NULL) {
    goto fail; //nonprimitive container
    }

    listEntry_t *server_address_by_client_cid_rsListEntry;
    if (v1_api_group->server_address_by_client_cid_rs) {
    list_ForEach(server_address_by_client_cid_rsListEntry, v1_api_group->server_address_by_client_cid_rs) {
    cJSON *itemLocal = v1_server_address_by_client_cidr_convertToJSON(server_address_by_client_cid_rsListEntry->data);
    if(itemLocal == NULL) {
    goto fail;
    }
    cJSON_AddItemToArray(server_address_by_client_cid_rs, itemLocal);
    }
    }
     } 


    // v1_api_group->versions
    if (!v1_api_group->versions) {
        goto fail;
    }
    
    cJSON *versions = cJSON_AddArrayToObject(item, "versions");
    if(versions == NULL) {
    goto fail; //nonprimitive container
    }

    listEntry_t *versionsListEntry;
    if (v1_api_group->versions) {
    list_ForEach(versionsListEntry, v1_api_group->versions) {
    cJSON *itemLocal = v1_group_version_for_discovery_convertToJSON(versionsListEntry->data);
    if(itemLocal == NULL) {
    goto fail;
    }
    cJSON_AddItemToArray(versions, itemLocal);
    }
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

v1_api_group_t *v1_api_group_parseFromJSON(cJSON *v1_api_groupJSON){

    v1_api_group_t *v1_api_group_local_var = NULL;

    // v1_api_group->api_version
    cJSON *api_version = cJSON_GetObjectItemCaseSensitive(v1_api_groupJSON, "apiVersion");
    if (api_version) { 
    if(!cJSON_IsString(api_version))
    {
    goto end; //String
    }
    }

    // v1_api_group->kind
    cJSON *kind = cJSON_GetObjectItemCaseSensitive(v1_api_groupJSON, "kind");
    if (kind) { 
    if(!cJSON_IsString(kind))
    {
    goto end; //String
    }
    }

    // v1_api_group->name
    cJSON *name = cJSON_GetObjectItemCaseSensitive(v1_api_groupJSON, "name");
    if (!name) {
        goto end;
    }

    
    if(!cJSON_IsString(name))
    {
    goto end; //String
    }

    // v1_api_group->preferred_version
    cJSON *preferred_version = cJSON_GetObjectItemCaseSensitive(v1_api_groupJSON, "preferredVersion");
    v1_group_version_for_discovery_t *preferred_version_local_nonprim = NULL;
    if (preferred_version) { 
    preferred_version_local_nonprim = v1_group_version_for_discovery_parseFromJSON(preferred_version); //nonprimitive
    }

    // v1_api_group->server_address_by_client_cid_rs
    cJSON *server_address_by_client_cid_rs = cJSON_GetObjectItemCaseSensitive(v1_api_groupJSON, "serverAddressByClientCIDRs");
    list_t *server_address_by_client_cid_rsList;
    if (server_address_by_client_cid_rs) { 
    cJSON *server_address_by_client_cid_rs_local_nonprimitive;
    if(!cJSON_IsArray(server_address_by_client_cid_rs)){
        goto end; //nonprimitive container
    }

    server_address_by_client_cid_rsList = list_create();

    cJSON_ArrayForEach(server_address_by_client_cid_rs_local_nonprimitive,server_address_by_client_cid_rs )
    {
        if(!cJSON_IsObject(server_address_by_client_cid_rs_local_nonprimitive)){
            goto end;
        }
        v1_server_address_by_client_cidr_t *server_address_by_client_cid_rsItem = v1_server_address_by_client_cidr_parseFromJSON(server_address_by_client_cid_rs_local_nonprimitive);

        list_addElement(server_address_by_client_cid_rsList, server_address_by_client_cid_rsItem);
    }
    }

    // v1_api_group->versions
    cJSON *versions = cJSON_GetObjectItemCaseSensitive(v1_api_groupJSON, "versions");
    if (!versions) {
        goto end;
    }

    list_t *versionsList;
    
    cJSON *versions_local_nonprimitive;
    if(!cJSON_IsArray(versions)){
        goto end; //nonprimitive container
    }

    versionsList = list_create();

    cJSON_ArrayForEach(versions_local_nonprimitive,versions )
    {
        if(!cJSON_IsObject(versions_local_nonprimitive)){
            goto end;
        }
        v1_group_version_for_discovery_t *versionsItem = v1_group_version_for_discovery_parseFromJSON(versions_local_nonprimitive);

        list_addElement(versionsList, versionsItem);
    }


    v1_api_group_local_var = v1_api_group_create (
        api_version ? strdup(api_version->valuestring) : NULL,
        kind ? strdup(kind->valuestring) : NULL,
        strdup(name->valuestring),
        preferred_version ? preferred_version_local_nonprim : NULL,
        server_address_by_client_cid_rs ? server_address_by_client_cid_rsList : NULL,
        versionsList
        );

    return v1_api_group_local_var;
end:
    return NULL;

}
