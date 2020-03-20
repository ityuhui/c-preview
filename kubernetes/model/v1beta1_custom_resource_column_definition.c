#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "v1beta1_custom_resource_column_definition.h"



v1beta1_custom_resource_column_definition_t *v1beta1_custom_resource_column_definition_create(
    char *json_path,
    char *description,
    char *format,
    char *name,
    int priority,
    char *type
    ) {
    v1beta1_custom_resource_column_definition_t *v1beta1_custom_resource_column_definition_local_var = malloc(sizeof(v1beta1_custom_resource_column_definition_t));
    if (!v1beta1_custom_resource_column_definition_local_var) {
        return NULL;
    }
    v1beta1_custom_resource_column_definition_local_var->json_path = json_path;
    v1beta1_custom_resource_column_definition_local_var->description = description;
    v1beta1_custom_resource_column_definition_local_var->format = format;
    v1beta1_custom_resource_column_definition_local_var->name = name;
    v1beta1_custom_resource_column_definition_local_var->priority = priority;
    v1beta1_custom_resource_column_definition_local_var->type = type;

    return v1beta1_custom_resource_column_definition_local_var;
}


void v1beta1_custom_resource_column_definition_free(v1beta1_custom_resource_column_definition_t *v1beta1_custom_resource_column_definition) {
    if(NULL == v1beta1_custom_resource_column_definition){
        return ;
    }
    listEntry_t *listEntry;
    free(v1beta1_custom_resource_column_definition->json_path);
    free(v1beta1_custom_resource_column_definition->description);
    free(v1beta1_custom_resource_column_definition->format);
    free(v1beta1_custom_resource_column_definition->name);
    free(v1beta1_custom_resource_column_definition->type);
    free(v1beta1_custom_resource_column_definition);
}

cJSON *v1beta1_custom_resource_column_definition_convertToJSON(v1beta1_custom_resource_column_definition_t *v1beta1_custom_resource_column_definition) {
    cJSON *item = cJSON_CreateObject();

    // v1beta1_custom_resource_column_definition->json_path
    if (!v1beta1_custom_resource_column_definition->json_path) {
        goto fail;
    }
    
    if(cJSON_AddStringToObject(item, "JSONPath", v1beta1_custom_resource_column_definition->json_path) == NULL) {
    goto fail; //String
    }


    // v1beta1_custom_resource_column_definition->description
    if(v1beta1_custom_resource_column_definition->description) { 
    if(cJSON_AddStringToObject(item, "description", v1beta1_custom_resource_column_definition->description) == NULL) {
    goto fail; //String
    }
     } 


    // v1beta1_custom_resource_column_definition->format
    if(v1beta1_custom_resource_column_definition->format) { 
    if(cJSON_AddStringToObject(item, "format", v1beta1_custom_resource_column_definition->format) == NULL) {
    goto fail; //String
    }
     } 


    // v1beta1_custom_resource_column_definition->name
    if (!v1beta1_custom_resource_column_definition->name) {
        goto fail;
    }
    
    if(cJSON_AddStringToObject(item, "name", v1beta1_custom_resource_column_definition->name) == NULL) {
    goto fail; //String
    }


    // v1beta1_custom_resource_column_definition->priority
    if(v1beta1_custom_resource_column_definition->priority) { 
    if(cJSON_AddNumberToObject(item, "priority", v1beta1_custom_resource_column_definition->priority) == NULL) {
    goto fail; //Numeric
    }
     } 


    // v1beta1_custom_resource_column_definition->type
    if (!v1beta1_custom_resource_column_definition->type) {
        goto fail;
    }
    
    if(cJSON_AddStringToObject(item, "type", v1beta1_custom_resource_column_definition->type) == NULL) {
    goto fail; //String
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

v1beta1_custom_resource_column_definition_t *v1beta1_custom_resource_column_definition_parseFromJSON(cJSON *v1beta1_custom_resource_column_definitionJSON){

    v1beta1_custom_resource_column_definition_t *v1beta1_custom_resource_column_definition_local_var = NULL;

    // v1beta1_custom_resource_column_definition->json_path
    cJSON *json_path = cJSON_GetObjectItemCaseSensitive(v1beta1_custom_resource_column_definitionJSON, "JSONPath");
    if (!json_path) {
        goto end;
    }

    
    if(!cJSON_IsString(json_path))
    {
    goto end; //String
    }

    // v1beta1_custom_resource_column_definition->description
    cJSON *description = cJSON_GetObjectItemCaseSensitive(v1beta1_custom_resource_column_definitionJSON, "description");
    if (description) { 
    if(!cJSON_IsString(description))
    {
    goto end; //String
    }
    }

    // v1beta1_custom_resource_column_definition->format
    cJSON *format = cJSON_GetObjectItemCaseSensitive(v1beta1_custom_resource_column_definitionJSON, "format");
    if (format) { 
    if(!cJSON_IsString(format))
    {
    goto end; //String
    }
    }

    // v1beta1_custom_resource_column_definition->name
    cJSON *name = cJSON_GetObjectItemCaseSensitive(v1beta1_custom_resource_column_definitionJSON, "name");
    if (!name) {
        goto end;
    }

    
    if(!cJSON_IsString(name))
    {
    goto end; //String
    }

    // v1beta1_custom_resource_column_definition->priority
    cJSON *priority = cJSON_GetObjectItemCaseSensitive(v1beta1_custom_resource_column_definitionJSON, "priority");
    if (priority) { 
    if(!cJSON_IsNumber(priority))
    {
    goto end; //Numeric
    }
    }

    // v1beta1_custom_resource_column_definition->type
    cJSON *type = cJSON_GetObjectItemCaseSensitive(v1beta1_custom_resource_column_definitionJSON, "type");
    if (!type) {
        goto end;
    }

    
    if(!cJSON_IsString(type))
    {
    goto end; //String
    }


    v1beta1_custom_resource_column_definition_local_var = v1beta1_custom_resource_column_definition_create (
        strdup(json_path->valuestring),
        description ? strdup(description->valuestring) : NULL,
        format ? strdup(format->valuestring) : NULL,
        strdup(name->valuestring),
        priority ? priority->valuedouble : 0,
        strdup(type->valuestring)
        );

    return v1beta1_custom_resource_column_definition_local_var;
end:
    return NULL;

}
