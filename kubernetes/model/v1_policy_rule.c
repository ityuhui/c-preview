#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "v1_policy_rule.h"



v1_policy_rule_t *v1_policy_rule_create(
    list_t *api_groups,
    list_t *non_resource_ur_ls,
    list_t *resource_names,
    list_t *resources,
    list_t *verbs
    ) {
    v1_policy_rule_t *v1_policy_rule_local_var = malloc(sizeof(v1_policy_rule_t));
    if (!v1_policy_rule_local_var) {
        return NULL;
    }
    v1_policy_rule_local_var->api_groups = api_groups;
    v1_policy_rule_local_var->non_resource_ur_ls = non_resource_ur_ls;
    v1_policy_rule_local_var->resource_names = resource_names;
    v1_policy_rule_local_var->resources = resources;
    v1_policy_rule_local_var->verbs = verbs;

    return v1_policy_rule_local_var;
}


void v1_policy_rule_free(v1_policy_rule_t *v1_policy_rule) {
    listEntry_t *listEntry;
    list_ForEach(listEntry, v1_policy_rule->api_groups) {
        free(listEntry->data);
    }
    list_free(v1_policy_rule->api_groups);
    list_ForEach(listEntry, v1_policy_rule->non_resource_ur_ls) {
        free(listEntry->data);
    }
    list_free(v1_policy_rule->non_resource_ur_ls);
    list_ForEach(listEntry, v1_policy_rule->resource_names) {
        free(listEntry->data);
    }
    list_free(v1_policy_rule->resource_names);
    list_ForEach(listEntry, v1_policy_rule->resources) {
        free(listEntry->data);
    }
    list_free(v1_policy_rule->resources);
    list_ForEach(listEntry, v1_policy_rule->verbs) {
        free(listEntry->data);
    }
    list_free(v1_policy_rule->verbs);
    free(v1_policy_rule);
}

cJSON *v1_policy_rule_convertToJSON(v1_policy_rule_t *v1_policy_rule) {
    cJSON *item = cJSON_CreateObject();

    // v1_policy_rule->api_groups
    if(v1_policy_rule->api_groups) { 
    cJSON *api_groups = cJSON_AddArrayToObject(item, "apiGroups");
    if(api_groups == NULL) {
        goto fail; //primitive container
    }

    listEntry_t *api_groupsListEntry;
    list_ForEach(api_groupsListEntry, v1_policy_rule->api_groups) {
    if(cJSON_AddStringToObject(api_groups, "", (char*)api_groupsListEntry->data) == NULL)
    {
        goto fail;
    }
    }
     } 


    // v1_policy_rule->non_resource_ur_ls
    if(v1_policy_rule->non_resource_ur_ls) { 
    cJSON *non_resource_ur_ls = cJSON_AddArrayToObject(item, "nonResourceURLs");
    if(non_resource_ur_ls == NULL) {
        goto fail; //primitive container
    }

    listEntry_t *non_resource_ur_lsListEntry;
    list_ForEach(non_resource_ur_lsListEntry, v1_policy_rule->non_resource_ur_ls) {
    if(cJSON_AddStringToObject(non_resource_ur_ls, "", (char*)non_resource_ur_lsListEntry->data) == NULL)
    {
        goto fail;
    }
    }
     } 


    // v1_policy_rule->resource_names
    if(v1_policy_rule->resource_names) { 
    cJSON *resource_names = cJSON_AddArrayToObject(item, "resourceNames");
    if(resource_names == NULL) {
        goto fail; //primitive container
    }

    listEntry_t *resource_namesListEntry;
    list_ForEach(resource_namesListEntry, v1_policy_rule->resource_names) {
    if(cJSON_AddStringToObject(resource_names, "", (char*)resource_namesListEntry->data) == NULL)
    {
        goto fail;
    }
    }
     } 


    // v1_policy_rule->resources
    if(v1_policy_rule->resources) { 
    cJSON *resources = cJSON_AddArrayToObject(item, "resources");
    if(resources == NULL) {
        goto fail; //primitive container
    }

    listEntry_t *resourcesListEntry;
    list_ForEach(resourcesListEntry, v1_policy_rule->resources) {
    if(cJSON_AddStringToObject(resources, "", (char*)resourcesListEntry->data) == NULL)
    {
        goto fail;
    }
    }
     } 


    // v1_policy_rule->verbs
    if (!v1_policy_rule->verbs) {
        goto fail;
    }
    
    cJSON *verbs = cJSON_AddArrayToObject(item, "verbs");
    if(verbs == NULL) {
        goto fail; //primitive container
    }

    listEntry_t *verbsListEntry;
    list_ForEach(verbsListEntry, v1_policy_rule->verbs) {
    if(cJSON_AddStringToObject(verbs, "", (char*)verbsListEntry->data) == NULL)
    {
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

v1_policy_rule_t *v1_policy_rule_parseFromJSON(cJSON *v1_policy_ruleJSON){

    v1_policy_rule_t *v1_policy_rule_local_var = NULL;

    // v1_policy_rule->api_groups
    cJSON *api_groups = cJSON_GetObjectItemCaseSensitive(v1_policy_ruleJSON, "apiGroups");
    list_t *api_groupsList;
    if (api_groups) { 
    cJSON *api_groups_local;
    if(!cJSON_IsArray(api_groups)) {
        goto end;//primitive container
    }
    api_groupsList = list_create();

    cJSON_ArrayForEach(api_groups_local, api_groups)
    {
        if(!cJSON_IsString(api_groups_local))
        {
            goto end;
        }
        list_addElement(api_groupsList , strdup(api_groups_local->valuestring));
    }
    }

    // v1_policy_rule->non_resource_ur_ls
    cJSON *non_resource_ur_ls = cJSON_GetObjectItemCaseSensitive(v1_policy_ruleJSON, "nonResourceURLs");
    list_t *non_resource_ur_lsList;
    if (non_resource_ur_ls) { 
    cJSON *non_resource_ur_ls_local;
    if(!cJSON_IsArray(non_resource_ur_ls)) {
        goto end;//primitive container
    }
    non_resource_ur_lsList = list_create();

    cJSON_ArrayForEach(non_resource_ur_ls_local, non_resource_ur_ls)
    {
        if(!cJSON_IsString(non_resource_ur_ls_local))
        {
            goto end;
        }
        list_addElement(non_resource_ur_lsList , strdup(non_resource_ur_ls_local->valuestring));
    }
    }

    // v1_policy_rule->resource_names
    cJSON *resource_names = cJSON_GetObjectItemCaseSensitive(v1_policy_ruleJSON, "resourceNames");
    list_t *resource_namesList;
    if (resource_names) { 
    cJSON *resource_names_local;
    if(!cJSON_IsArray(resource_names)) {
        goto end;//primitive container
    }
    resource_namesList = list_create();

    cJSON_ArrayForEach(resource_names_local, resource_names)
    {
        if(!cJSON_IsString(resource_names_local))
        {
            goto end;
        }
        list_addElement(resource_namesList , strdup(resource_names_local->valuestring));
    }
    }

    // v1_policy_rule->resources
    cJSON *resources = cJSON_GetObjectItemCaseSensitive(v1_policy_ruleJSON, "resources");
    list_t *resourcesList;
    if (resources) { 
    cJSON *resources_local;
    if(!cJSON_IsArray(resources)) {
        goto end;//primitive container
    }
    resourcesList = list_create();

    cJSON_ArrayForEach(resources_local, resources)
    {
        if(!cJSON_IsString(resources_local))
        {
            goto end;
        }
        list_addElement(resourcesList , strdup(resources_local->valuestring));
    }
    }

    // v1_policy_rule->verbs
    cJSON *verbs = cJSON_GetObjectItemCaseSensitive(v1_policy_ruleJSON, "verbs");
    if (!verbs) {
        goto end;
    }

    list_t *verbsList;
    
    cJSON *verbs_local;
    if(!cJSON_IsArray(verbs)) {
        goto end;//primitive container
    }
    verbsList = list_create();

    cJSON_ArrayForEach(verbs_local, verbs)
    {
        if(!cJSON_IsString(verbs_local))
        {
            goto end;
        }
        list_addElement(verbsList , strdup(verbs_local->valuestring));
    }


    v1_policy_rule_local_var = v1_policy_rule_create (
        api_groups ? api_groupsList : NULL,
        non_resource_ur_ls ? non_resource_ur_lsList : NULL,
        resource_names ? resource_namesList : NULL,
        resources ? resourcesList : NULL,
        verbsList
        );

    return v1_policy_rule_local_var;
end:
    return NULL;

}
