#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "v2alpha1_cron_job_spec.h"



v2alpha1_cron_job_spec_t *v2alpha1_cron_job_spec_create(
    char *concurrency_policy,
    int failed_jobs_history_limit,
    v2alpha1_job_template_spec_t *job_template,
    char *schedule,
    long starting_deadline_seconds,
    int successful_jobs_history_limit,
    int suspend
    ) {
    v2alpha1_cron_job_spec_t *v2alpha1_cron_job_spec_local_var = malloc(sizeof(v2alpha1_cron_job_spec_t));
    if (!v2alpha1_cron_job_spec_local_var) {
        return NULL;
    }
    v2alpha1_cron_job_spec_local_var->concurrency_policy = concurrency_policy;
    v2alpha1_cron_job_spec_local_var->failed_jobs_history_limit = failed_jobs_history_limit;
    v2alpha1_cron_job_spec_local_var->job_template = job_template;
    v2alpha1_cron_job_spec_local_var->schedule = schedule;
    v2alpha1_cron_job_spec_local_var->starting_deadline_seconds = starting_deadline_seconds;
    v2alpha1_cron_job_spec_local_var->successful_jobs_history_limit = successful_jobs_history_limit;
    v2alpha1_cron_job_spec_local_var->suspend = suspend;

    return v2alpha1_cron_job_spec_local_var;
}


void v2alpha1_cron_job_spec_free(v2alpha1_cron_job_spec_t *v2alpha1_cron_job_spec) {
    if(NULL == v2alpha1_cron_job_spec){
        return ;
    }
    listEntry_t *listEntry;
    free(v2alpha1_cron_job_spec->concurrency_policy);
    v2alpha1_job_template_spec_free(v2alpha1_cron_job_spec->job_template);
    free(v2alpha1_cron_job_spec->schedule);
    free(v2alpha1_cron_job_spec);
}

cJSON *v2alpha1_cron_job_spec_convertToJSON(v2alpha1_cron_job_spec_t *v2alpha1_cron_job_spec) {
    cJSON *item = cJSON_CreateObject();

    // v2alpha1_cron_job_spec->concurrency_policy
    if(v2alpha1_cron_job_spec->concurrency_policy) { 
    if(cJSON_AddStringToObject(item, "concurrencyPolicy", v2alpha1_cron_job_spec->concurrency_policy) == NULL) {
    goto fail; //String
    }
     } 


    // v2alpha1_cron_job_spec->failed_jobs_history_limit
    if(v2alpha1_cron_job_spec->failed_jobs_history_limit) { 
    if(cJSON_AddNumberToObject(item, "failedJobsHistoryLimit", v2alpha1_cron_job_spec->failed_jobs_history_limit) == NULL) {
    goto fail; //Numeric
    }
     } 


    // v2alpha1_cron_job_spec->job_template
    if (!v2alpha1_cron_job_spec->job_template) {
        goto fail;
    }
    
    cJSON *job_template_local_JSON = v2alpha1_job_template_spec_convertToJSON(v2alpha1_cron_job_spec->job_template);
    if(job_template_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "jobTemplate", job_template_local_JSON);
    if(item->child == NULL) {
    goto fail;
    }


    // v2alpha1_cron_job_spec->schedule
    if (!v2alpha1_cron_job_spec->schedule) {
        goto fail;
    }
    
    if(cJSON_AddStringToObject(item, "schedule", v2alpha1_cron_job_spec->schedule) == NULL) {
    goto fail; //String
    }


    // v2alpha1_cron_job_spec->starting_deadline_seconds
    if(v2alpha1_cron_job_spec->starting_deadline_seconds) { 
    if(cJSON_AddNumberToObject(item, "startingDeadlineSeconds", v2alpha1_cron_job_spec->starting_deadline_seconds) == NULL) {
    goto fail; //Numeric
    }
     } 


    // v2alpha1_cron_job_spec->successful_jobs_history_limit
    if(v2alpha1_cron_job_spec->successful_jobs_history_limit) { 
    if(cJSON_AddNumberToObject(item, "successfulJobsHistoryLimit", v2alpha1_cron_job_spec->successful_jobs_history_limit) == NULL) {
    goto fail; //Numeric
    }
     } 


    // v2alpha1_cron_job_spec->suspend
    if(v2alpha1_cron_job_spec->suspend) { 
    if(cJSON_AddBoolToObject(item, "suspend", v2alpha1_cron_job_spec->suspend) == NULL) {
    goto fail; //Bool
    }
     } 

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

v2alpha1_cron_job_spec_t *v2alpha1_cron_job_spec_parseFromJSON(cJSON *v2alpha1_cron_job_specJSON){

    v2alpha1_cron_job_spec_t *v2alpha1_cron_job_spec_local_var = NULL;

    // v2alpha1_cron_job_spec->concurrency_policy
    cJSON *concurrency_policy = cJSON_GetObjectItemCaseSensitive(v2alpha1_cron_job_specJSON, "concurrencyPolicy");
    if (concurrency_policy) { 
    if(!cJSON_IsString(concurrency_policy))
    {
    goto end; //String
    }
    }

    // v2alpha1_cron_job_spec->failed_jobs_history_limit
    cJSON *failed_jobs_history_limit = cJSON_GetObjectItemCaseSensitive(v2alpha1_cron_job_specJSON, "failedJobsHistoryLimit");
    if (failed_jobs_history_limit) { 
    if(!cJSON_IsNumber(failed_jobs_history_limit))
    {
    goto end; //Numeric
    }
    }

    // v2alpha1_cron_job_spec->job_template
    cJSON *job_template = cJSON_GetObjectItemCaseSensitive(v2alpha1_cron_job_specJSON, "jobTemplate");
    if (!job_template) {
        goto end;
    }

    v2alpha1_job_template_spec_t *job_template_local_nonprim = NULL;
    
    job_template_local_nonprim = v2alpha1_job_template_spec_parseFromJSON(job_template); //nonprimitive

    // v2alpha1_cron_job_spec->schedule
    cJSON *schedule = cJSON_GetObjectItemCaseSensitive(v2alpha1_cron_job_specJSON, "schedule");
    if (!schedule) {
        goto end;
    }

    
    if(!cJSON_IsString(schedule))
    {
    goto end; //String
    }

    // v2alpha1_cron_job_spec->starting_deadline_seconds
    cJSON *starting_deadline_seconds = cJSON_GetObjectItemCaseSensitive(v2alpha1_cron_job_specJSON, "startingDeadlineSeconds");
    if (starting_deadline_seconds) { 
    if(!cJSON_IsNumber(starting_deadline_seconds))
    {
    goto end; //Numeric
    }
    }

    // v2alpha1_cron_job_spec->successful_jobs_history_limit
    cJSON *successful_jobs_history_limit = cJSON_GetObjectItemCaseSensitive(v2alpha1_cron_job_specJSON, "successfulJobsHistoryLimit");
    if (successful_jobs_history_limit) { 
    if(!cJSON_IsNumber(successful_jobs_history_limit))
    {
    goto end; //Numeric
    }
    }

    // v2alpha1_cron_job_spec->suspend
    cJSON *suspend = cJSON_GetObjectItemCaseSensitive(v2alpha1_cron_job_specJSON, "suspend");
    if (suspend) { 
    if(!cJSON_IsBool(suspend))
    {
    goto end; //Bool
    }
    }


    v2alpha1_cron_job_spec_local_var = v2alpha1_cron_job_spec_create (
        concurrency_policy ? strdup(concurrency_policy->valuestring) : NULL,
        failed_jobs_history_limit ? failed_jobs_history_limit->valuedouble : 0,
        job_template_local_nonprim,
        strdup(schedule->valuestring),
        starting_deadline_seconds ? starting_deadline_seconds->valuedouble : 0,
        successful_jobs_history_limit ? successful_jobs_history_limit->valuedouble : 0,
        suspend ? suspend->valueint : 0
        );

    return v2alpha1_cron_job_spec_local_var;
end:
    return NULL;

}
