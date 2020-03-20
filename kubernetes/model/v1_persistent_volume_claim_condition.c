#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "v1_persistent_volume_claim_condition.h"



v1_persistent_volume_claim_condition_t *v1_persistent_volume_claim_condition_create(
    char *last_probe_time,
    char *last_transition_time,
    char *message,
    char *reason,
    char *status,
    char *type
    ) {
    v1_persistent_volume_claim_condition_t *v1_persistent_volume_claim_condition_local_var = malloc(sizeof(v1_persistent_volume_claim_condition_t));
    if (!v1_persistent_volume_claim_condition_local_var) {
        return NULL;
    }
    v1_persistent_volume_claim_condition_local_var->last_probe_time = last_probe_time;
    v1_persistent_volume_claim_condition_local_var->last_transition_time = last_transition_time;
    v1_persistent_volume_claim_condition_local_var->message = message;
    v1_persistent_volume_claim_condition_local_var->reason = reason;
    v1_persistent_volume_claim_condition_local_var->status = status;
    v1_persistent_volume_claim_condition_local_var->type = type;

    return v1_persistent_volume_claim_condition_local_var;
}


void v1_persistent_volume_claim_condition_free(v1_persistent_volume_claim_condition_t *v1_persistent_volume_claim_condition) {
    if(NULL == v1_persistent_volume_claim_condition){
        return ;
    }
    listEntry_t *listEntry;
    free(v1_persistent_volume_claim_condition->last_probe_time);
    free(v1_persistent_volume_claim_condition->last_transition_time);
    free(v1_persistent_volume_claim_condition->message);
    free(v1_persistent_volume_claim_condition->reason);
    free(v1_persistent_volume_claim_condition->status);
    free(v1_persistent_volume_claim_condition->type);
    free(v1_persistent_volume_claim_condition);
}

cJSON *v1_persistent_volume_claim_condition_convertToJSON(v1_persistent_volume_claim_condition_t *v1_persistent_volume_claim_condition) {
    cJSON *item = cJSON_CreateObject();

    // v1_persistent_volume_claim_condition->last_probe_time
    if(v1_persistent_volume_claim_condition->last_probe_time) { 
    if(cJSON_AddStringToObject(item, "lastProbeTime", v1_persistent_volume_claim_condition->last_probe_time) == NULL) {
    goto fail; //Date-Time
    }
     } 


    // v1_persistent_volume_claim_condition->last_transition_time
    if(v1_persistent_volume_claim_condition->last_transition_time) { 
    if(cJSON_AddStringToObject(item, "lastTransitionTime", v1_persistent_volume_claim_condition->last_transition_time) == NULL) {
    goto fail; //Date-Time
    }
     } 


    // v1_persistent_volume_claim_condition->message
    if(v1_persistent_volume_claim_condition->message) { 
    if(cJSON_AddStringToObject(item, "message", v1_persistent_volume_claim_condition->message) == NULL) {
    goto fail; //String
    }
     } 


    // v1_persistent_volume_claim_condition->reason
    if(v1_persistent_volume_claim_condition->reason) { 
    if(cJSON_AddStringToObject(item, "reason", v1_persistent_volume_claim_condition->reason) == NULL) {
    goto fail; //String
    }
     } 


    // v1_persistent_volume_claim_condition->status
    if (!v1_persistent_volume_claim_condition->status) {
        goto fail;
    }
    
    if(cJSON_AddStringToObject(item, "status", v1_persistent_volume_claim_condition->status) == NULL) {
    goto fail; //String
    }


    // v1_persistent_volume_claim_condition->type
    if (!v1_persistent_volume_claim_condition->type) {
        goto fail;
    }
    
    if(cJSON_AddStringToObject(item, "type", v1_persistent_volume_claim_condition->type) == NULL) {
    goto fail; //String
    }

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

v1_persistent_volume_claim_condition_t *v1_persistent_volume_claim_condition_parseFromJSON(cJSON *v1_persistent_volume_claim_conditionJSON){

    v1_persistent_volume_claim_condition_t *v1_persistent_volume_claim_condition_local_var = NULL;

    // v1_persistent_volume_claim_condition->last_probe_time
    cJSON *last_probe_time = cJSON_GetObjectItemCaseSensitive(v1_persistent_volume_claim_conditionJSON, "lastProbeTime");
    if (last_probe_time) { 
    if(!cJSON_IsString(last_probe_time))
    {
    goto end; //DateTime
    }
    }

    // v1_persistent_volume_claim_condition->last_transition_time
    cJSON *last_transition_time = cJSON_GetObjectItemCaseSensitive(v1_persistent_volume_claim_conditionJSON, "lastTransitionTime");
    if (last_transition_time) { 
    if(!cJSON_IsString(last_transition_time))
    {
    goto end; //DateTime
    }
    }

    // v1_persistent_volume_claim_condition->message
    cJSON *message = cJSON_GetObjectItemCaseSensitive(v1_persistent_volume_claim_conditionJSON, "message");
    if (message) { 
    if(!cJSON_IsString(message))
    {
    goto end; //String
    }
    }

    // v1_persistent_volume_claim_condition->reason
    cJSON *reason = cJSON_GetObjectItemCaseSensitive(v1_persistent_volume_claim_conditionJSON, "reason");
    if (reason) { 
    if(!cJSON_IsString(reason))
    {
    goto end; //String
    }
    }

    // v1_persistent_volume_claim_condition->status
    cJSON *status = cJSON_GetObjectItemCaseSensitive(v1_persistent_volume_claim_conditionJSON, "status");
    if (!status) {
        goto end;
    }

    
    if(!cJSON_IsString(status))
    {
    goto end; //String
    }

    // v1_persistent_volume_claim_condition->type
    cJSON *type = cJSON_GetObjectItemCaseSensitive(v1_persistent_volume_claim_conditionJSON, "type");
    if (!type) {
        goto end;
    }

    
    if(!cJSON_IsString(type))
    {
    goto end; //String
    }


    v1_persistent_volume_claim_condition_local_var = v1_persistent_volume_claim_condition_create (
        last_probe_time ? strdup(last_probe_time->valuestring) : NULL,
        last_transition_time ? strdup(last_transition_time->valuestring) : NULL,
        message ? strdup(message->valuestring) : NULL,
        reason ? strdup(reason->valuestring) : NULL,
        strdup(status->valuestring),
        strdup(type->valuestring)
        );

    return v1_persistent_volume_claim_condition_local_var;
end:
    return NULL;

}
