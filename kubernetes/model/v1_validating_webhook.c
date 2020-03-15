#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "v1_validating_webhook.h"



v1_validating_webhook_t *v1_validating_webhook_create(
    list_t *admission_review_versions,
    admissionregistration_v1_webhook_client_config_t *client_config,
    char *failure_policy,
    char *match_policy,
    char *name,
    v1_label_selector_t *namespace_selector,
    v1_label_selector_t *object_selector,
    list_t *rules,
    char *side_effects,
    int timeout_seconds
    ) {
    v1_validating_webhook_t *v1_validating_webhook_local_var = malloc(sizeof(v1_validating_webhook_t));
    if (!v1_validating_webhook_local_var) {
        return NULL;
    }
    v1_validating_webhook_local_var->admission_review_versions = admission_review_versions;
    v1_validating_webhook_local_var->client_config = client_config;
    v1_validating_webhook_local_var->failure_policy = failure_policy;
    v1_validating_webhook_local_var->match_policy = match_policy;
    v1_validating_webhook_local_var->name = name;
    v1_validating_webhook_local_var->namespace_selector = namespace_selector;
    v1_validating_webhook_local_var->object_selector = object_selector;
    v1_validating_webhook_local_var->rules = rules;
    v1_validating_webhook_local_var->side_effects = side_effects;
    v1_validating_webhook_local_var->timeout_seconds = timeout_seconds;

    return v1_validating_webhook_local_var;
}


void v1_validating_webhook_free(v1_validating_webhook_t *v1_validating_webhook) {
    listEntry_t *listEntry;
    list_ForEach(listEntry, v1_validating_webhook->admission_review_versions) {
        free(listEntry->data);
    }
    list_free(v1_validating_webhook->admission_review_versions);
    admissionregistration_v1_webhook_client_config_free(v1_validating_webhook->client_config);
    free(v1_validating_webhook->failure_policy);
    free(v1_validating_webhook->match_policy);
    free(v1_validating_webhook->name);
    v1_label_selector_free(v1_validating_webhook->namespace_selector);
    v1_label_selector_free(v1_validating_webhook->object_selector);
    list_ForEach(listEntry, v1_validating_webhook->rules) {
        v1_rule_with_operations_free(listEntry->data);
    }
    list_free(v1_validating_webhook->rules);
    free(v1_validating_webhook->side_effects);
    free(v1_validating_webhook);
}

cJSON *v1_validating_webhook_convertToJSON(v1_validating_webhook_t *v1_validating_webhook) {
    cJSON *item = cJSON_CreateObject();

    // v1_validating_webhook->admission_review_versions
    if (!v1_validating_webhook->admission_review_versions) {
        goto fail;
    }
    
    cJSON *admission_review_versions = cJSON_AddArrayToObject(item, "admissionReviewVersions");
    if(admission_review_versions == NULL) {
        goto fail; //primitive container
    }

    listEntry_t *admission_review_versionsListEntry;
    list_ForEach(admission_review_versionsListEntry, v1_validating_webhook->admission_review_versions) {
    if(cJSON_AddStringToObject(admission_review_versions, "", (char*)admission_review_versionsListEntry->data) == NULL)
    {
        goto fail;
    }
    }


    // v1_validating_webhook->client_config
    if (!v1_validating_webhook->client_config) {
        goto fail;
    }
    
    cJSON *client_config_local_JSON = admissionregistration_v1_webhook_client_config_convertToJSON(v1_validating_webhook->client_config);
    if(client_config_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "clientConfig", client_config_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }


    // v1_validating_webhook->failure_policy
    if(v1_validating_webhook->failure_policy) { 
    if(cJSON_AddStringToObject(item, "failurePolicy", v1_validating_webhook->failure_policy) == NULL) {
    goto fail; //String
    }
     } 


    // v1_validating_webhook->match_policy
    if(v1_validating_webhook->match_policy) { 
    if(cJSON_AddStringToObject(item, "matchPolicy", v1_validating_webhook->match_policy) == NULL) {
    goto fail; //String
    }
     } 


    // v1_validating_webhook->name
    if (!v1_validating_webhook->name) {
        goto fail;
    }
    
    if(cJSON_AddStringToObject(item, "name", v1_validating_webhook->name) == NULL) {
    goto fail; //String
    }


    // v1_validating_webhook->namespace_selector
    if(v1_validating_webhook->namespace_selector) { 
    cJSON *namespace_selector_local_JSON = v1_label_selector_convertToJSON(v1_validating_webhook->namespace_selector);
    if(namespace_selector_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "namespaceSelector", namespace_selector_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }
     } 


    // v1_validating_webhook->object_selector
    if(v1_validating_webhook->object_selector) { 
    cJSON *object_selector_local_JSON = v1_label_selector_convertToJSON(v1_validating_webhook->object_selector);
    if(object_selector_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "objectSelector", object_selector_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }
     } 


    // v1_validating_webhook->rules
    if(v1_validating_webhook->rules) { 
    cJSON *rules = cJSON_AddArrayToObject(item, "rules");
    if(rules == NULL) {
    goto fail; //nonprimitive container
    }

    listEntry_t *rulesListEntry;
    if (v1_validating_webhook->rules) {
    list_ForEach(rulesListEntry, v1_validating_webhook->rules) {
    cJSON *itemLocal = v1_rule_with_operations_convertToJSON(rulesListEntry->data);
    if(itemLocal == NULL) {
    goto fail;
    }
    cJSON_AddItemToArray(rules, itemLocal);
    }
    }
     } 


    // v1_validating_webhook->side_effects
    if (!v1_validating_webhook->side_effects) {
        goto fail;
    }
    
    if(cJSON_AddStringToObject(item, "sideEffects", v1_validating_webhook->side_effects) == NULL) {
    goto fail; //String
    }


    // v1_validating_webhook->timeout_seconds
    if(v1_validating_webhook->timeout_seconds) { 
    if(cJSON_AddNumberToObject(item, "timeoutSeconds", v1_validating_webhook->timeout_seconds) == NULL) {
    goto fail; //Numeric
    }
     } 

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

v1_validating_webhook_t *v1_validating_webhook_parseFromJSON(cJSON *v1_validating_webhookJSON){

    v1_validating_webhook_t *v1_validating_webhook_local_var = NULL;

    // v1_validating_webhook->admission_review_versions
    cJSON *admission_review_versions = cJSON_GetObjectItemCaseSensitive(v1_validating_webhookJSON, "admissionReviewVersions");
    if (!admission_review_versions) {
        goto end;
    }

    list_t *admission_review_versionsList;
    
    cJSON *admission_review_versions_local;
    if(!cJSON_IsArray(admission_review_versions)) {
        goto end;//primitive container
    }
    admission_review_versionsList = list_create();

    cJSON_ArrayForEach(admission_review_versions_local, admission_review_versions)
    {
        if(!cJSON_IsString(admission_review_versions_local))
        {
            goto end;
        }
        list_addElement(admission_review_versionsList , strdup(admission_review_versions_local->valuestring));
    }

    // v1_validating_webhook->client_config
    cJSON *client_config = cJSON_GetObjectItemCaseSensitive(v1_validating_webhookJSON, "clientConfig");
    if (!client_config) {
        goto end;
    }

    admissionregistration_v1_webhook_client_config_t *client_config_local_nonprim = NULL;
    
    client_config_local_nonprim = admissionregistration_v1_webhook_client_config_parseFromJSON(client_config); //nonprimitive

    // v1_validating_webhook->failure_policy
    cJSON *failure_policy = cJSON_GetObjectItemCaseSensitive(v1_validating_webhookJSON, "failurePolicy");
    if (failure_policy) { 
    if(!cJSON_IsString(failure_policy))
    {
    goto end; //String
    }
    }

    // v1_validating_webhook->match_policy
    cJSON *match_policy = cJSON_GetObjectItemCaseSensitive(v1_validating_webhookJSON, "matchPolicy");
    if (match_policy) { 
    if(!cJSON_IsString(match_policy))
    {
    goto end; //String
    }
    }

    // v1_validating_webhook->name
    cJSON *name = cJSON_GetObjectItemCaseSensitive(v1_validating_webhookJSON, "name");
    if (!name) {
        goto end;
    }

    
    if(!cJSON_IsString(name))
    {
    goto end; //String
    }

    // v1_validating_webhook->namespace_selector
    cJSON *namespace_selector = cJSON_GetObjectItemCaseSensitive(v1_validating_webhookJSON, "namespaceSelector");
    v1_label_selector_t *namespace_selector_local_nonprim = NULL;
    if (namespace_selector) { 
    namespace_selector_local_nonprim = v1_label_selector_parseFromJSON(namespace_selector); //nonprimitive
    }

    // v1_validating_webhook->object_selector
    cJSON *object_selector = cJSON_GetObjectItemCaseSensitive(v1_validating_webhookJSON, "objectSelector");
    v1_label_selector_t *object_selector_local_nonprim = NULL;
    if (object_selector) { 
    object_selector_local_nonprim = v1_label_selector_parseFromJSON(object_selector); //nonprimitive
    }

    // v1_validating_webhook->rules
    cJSON *rules = cJSON_GetObjectItemCaseSensitive(v1_validating_webhookJSON, "rules");
    list_t *rulesList;
    if (rules) { 
    cJSON *rules_local_nonprimitive;
    if(!cJSON_IsArray(rules)){
        goto end; //nonprimitive container
    }

    rulesList = list_create();

    cJSON_ArrayForEach(rules_local_nonprimitive,rules )
    {
        if(!cJSON_IsObject(rules_local_nonprimitive)){
            goto end;
        }
        v1_rule_with_operations_t *rulesItem = v1_rule_with_operations_parseFromJSON(rules_local_nonprimitive);

        list_addElement(rulesList, rulesItem);
    }
    }

    // v1_validating_webhook->side_effects
    cJSON *side_effects = cJSON_GetObjectItemCaseSensitive(v1_validating_webhookJSON, "sideEffects");
    if (!side_effects) {
        goto end;
    }

    
    if(!cJSON_IsString(side_effects))
    {
    goto end; //String
    }

    // v1_validating_webhook->timeout_seconds
    cJSON *timeout_seconds = cJSON_GetObjectItemCaseSensitive(v1_validating_webhookJSON, "timeoutSeconds");
    if (timeout_seconds) { 
    if(!cJSON_IsNumber(timeout_seconds))
    {
    goto end; //Numeric
    }
    }


    v1_validating_webhook_local_var = v1_validating_webhook_create (
        admission_review_versionsList,
        client_config_local_nonprim,
        failure_policy ? strdup(failure_policy->valuestring) : NULL,
        match_policy ? strdup(match_policy->valuestring) : NULL,
        strdup(name->valuestring),
        namespace_selector ? namespace_selector_local_nonprim : NULL,
        object_selector ? object_selector_local_nonprim : NULL,
        rules ? rulesList : NULL,
        strdup(side_effects->valuestring),
        timeout_seconds ? timeout_seconds->valuedouble : 0
        );

    return v1_validating_webhook_local_var;
end:
    return NULL;

}
