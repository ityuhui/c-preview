#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "v1beta2_deployment_condition.h"



v1beta2_deployment_condition_t *v1beta2_deployment_condition_create(
    char *last_transition_time,
    char *last_update_time,
    char *message,
    char *reason,
    char *status,
    char *type
    ) {
    v1beta2_deployment_condition_t *v1beta2_deployment_condition_local_var = malloc(sizeof(v1beta2_deployment_condition_t));
    if (!v1beta2_deployment_condition_local_var) {
        return NULL;
    }
    v1beta2_deployment_condition_local_var->last_transition_time = last_transition_time;
    v1beta2_deployment_condition_local_var->last_update_time = last_update_time;
    v1beta2_deployment_condition_local_var->message = message;
    v1beta2_deployment_condition_local_var->reason = reason;
    v1beta2_deployment_condition_local_var->status = status;
    v1beta2_deployment_condition_local_var->type = type;

    return v1beta2_deployment_condition_local_var;
}


void v1beta2_deployment_condition_free(v1beta2_deployment_condition_t *v1beta2_deployment_condition) {
    if(NULL == v1beta2_deployment_condition){
        return ;
    }
    listEntry_t *listEntry;
    free(v1beta2_deployment_condition->last_transition_time);
    free(v1beta2_deployment_condition->last_update_time);
    free(v1beta2_deployment_condition->message);
    free(v1beta2_deployment_condition->reason);
    free(v1beta2_deployment_condition->status);
    free(v1beta2_deployment_condition->type);
    free(v1beta2_deployment_condition);
}

cJSON *v1beta2_deployment_condition_convertToJSON(v1beta2_deployment_condition_t *v1beta2_deployment_condition) {
    cJSON *item = cJSON_CreateObject();

    // v1beta2_deployment_condition->last_transition_time
    if(v1beta2_deployment_condition->last_transition_time) { 
    if(cJSON_AddStringToObject(item, "lastTransitionTime", v1beta2_deployment_condition->last_transition_time) == NULL) {
    goto fail; //Date-Time
    }
     } 


    // v1beta2_deployment_condition->last_update_time
    if(v1beta2_deployment_condition->last_update_time) { 
    if(cJSON_AddStringToObject(item, "lastUpdateTime", v1beta2_deployment_condition->last_update_time) == NULL) {
    goto fail; //Date-Time
    }
     } 


    // v1beta2_deployment_condition->message
    if(v1beta2_deployment_condition->message) { 
    if(cJSON_AddStringToObject(item, "message", v1beta2_deployment_condition->message) == NULL) {
    goto fail; //String
    }
     } 


    // v1beta2_deployment_condition->reason
    if(v1beta2_deployment_condition->reason) { 
    if(cJSON_AddStringToObject(item, "reason", v1beta2_deployment_condition->reason) == NULL) {
    goto fail; //String
    }
     } 


    // v1beta2_deployment_condition->status
    if (!v1beta2_deployment_condition->status) {
        goto fail;
    }
    
    if(cJSON_AddStringToObject(item, "status", v1beta2_deployment_condition->status) == NULL) {
    goto fail; //String
    }


    // v1beta2_deployment_condition->type
    if (!v1beta2_deployment_condition->type) {
        goto fail;
    }
    
    if(cJSON_AddStringToObject(item, "type", v1beta2_deployment_condition->type) == NULL) {
    goto fail; //String
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

v1beta2_deployment_condition_t *v1beta2_deployment_condition_parseFromJSON(cJSON *v1beta2_deployment_conditionJSON){

    v1beta2_deployment_condition_t *v1beta2_deployment_condition_local_var = NULL;

    // v1beta2_deployment_condition->last_transition_time
    cJSON *last_transition_time = cJSON_GetObjectItemCaseSensitive(v1beta2_deployment_conditionJSON, "lastTransitionTime");
    if (last_transition_time) { 
    if(!cJSON_IsString(last_transition_time))
    {
    goto end; //DateTime
    }
    }

    // v1beta2_deployment_condition->last_update_time
    cJSON *last_update_time = cJSON_GetObjectItemCaseSensitive(v1beta2_deployment_conditionJSON, "lastUpdateTime");
    if (last_update_time) { 
    if(!cJSON_IsString(last_update_time))
    {
    goto end; //DateTime
    }
    }

    // v1beta2_deployment_condition->message
    cJSON *message = cJSON_GetObjectItemCaseSensitive(v1beta2_deployment_conditionJSON, "message");
    if (message) { 
    if(!cJSON_IsString(message))
    {
    goto end; //String
    }
    }

    // v1beta2_deployment_condition->reason
    cJSON *reason = cJSON_GetObjectItemCaseSensitive(v1beta2_deployment_conditionJSON, "reason");
    if (reason) { 
    if(!cJSON_IsString(reason))
    {
    goto end; //String
    }
    }

    // v1beta2_deployment_condition->status
    cJSON *status = cJSON_GetObjectItemCaseSensitive(v1beta2_deployment_conditionJSON, "status");
    if (!status) {
        goto end;
    }

    
    if(!cJSON_IsString(status))
    {
    goto end; //String
    }

    // v1beta2_deployment_condition->type
    cJSON *type = cJSON_GetObjectItemCaseSensitive(v1beta2_deployment_conditionJSON, "type");
    if (!type) {
        goto end;
    }

    
    if(!cJSON_IsString(type))
    {
    goto end; //String
    }


    v1beta2_deployment_condition_local_var = v1beta2_deployment_condition_create (
        last_transition_time ? strdup(last_transition_time->valuestring) : NULL,
        last_update_time ? strdup(last_update_time->valuestring) : NULL,
        message ? strdup(message->valuestring) : NULL,
        reason ? strdup(reason->valuestring) : NULL,
        strdup(status->valuestring),
        strdup(type->valuestring)
        );

    return v1beta2_deployment_condition_local_var;
end:
    return NULL;

}
