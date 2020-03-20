#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "v1_fc_volume_source.h"



v1_fc_volume_source_t *v1_fc_volume_source_create(
    char *fs_type,
    int lun,
    int read_only,
    list_t *target_ww_ns,
    list_t *wwids
    ) {
    v1_fc_volume_source_t *v1_fc_volume_source_local_var = malloc(sizeof(v1_fc_volume_source_t));
    if (!v1_fc_volume_source_local_var) {
        return NULL;
    }
    v1_fc_volume_source_local_var->fs_type = fs_type;
    v1_fc_volume_source_local_var->lun = lun;
    v1_fc_volume_source_local_var->read_only = read_only;
    v1_fc_volume_source_local_var->target_ww_ns = target_ww_ns;
    v1_fc_volume_source_local_var->wwids = wwids;

    return v1_fc_volume_source_local_var;
}


void v1_fc_volume_source_free(v1_fc_volume_source_t *v1_fc_volume_source) {
    if(NULL == v1_fc_volume_source){
        return ;
    }
    listEntry_t *listEntry;
    free(v1_fc_volume_source->fs_type);
    list_ForEach(listEntry, v1_fc_volume_source->target_ww_ns) {
        free(listEntry->data);
    }
    list_free(v1_fc_volume_source->target_ww_ns);
    list_ForEach(listEntry, v1_fc_volume_source->wwids) {
        free(listEntry->data);
    }
    list_free(v1_fc_volume_source->wwids);
    free(v1_fc_volume_source);
}

cJSON *v1_fc_volume_source_convertToJSON(v1_fc_volume_source_t *v1_fc_volume_source) {
    cJSON *item = cJSON_CreateObject();

    // v1_fc_volume_source->fs_type
    if(v1_fc_volume_source->fs_type) { 
    if(cJSON_AddStringToObject(item, "fsType", v1_fc_volume_source->fs_type) == NULL) {
    goto fail; //String
    }
     } 


    // v1_fc_volume_source->lun
    if(v1_fc_volume_source->lun) { 
    if(cJSON_AddNumberToObject(item, "lun", v1_fc_volume_source->lun) == NULL) {
    goto fail; //Numeric
    }
     } 


    // v1_fc_volume_source->read_only
    if(v1_fc_volume_source->read_only) { 
    if(cJSON_AddBoolToObject(item, "readOnly", v1_fc_volume_source->read_only) == NULL) {
    goto fail; //Bool
    }
     } 


    // v1_fc_volume_source->target_ww_ns
    if(v1_fc_volume_source->target_ww_ns) { 
    cJSON *target_ww_ns = cJSON_AddArrayToObject(item, "targetWWNs");
    if(target_ww_ns == NULL) {
        goto fail; //primitive container
    }

    listEntry_t *target_ww_nsListEntry;
    list_ForEach(target_ww_nsListEntry, v1_fc_volume_source->target_ww_ns) {
    if(cJSON_AddStringToObject(target_ww_ns, "", (char*)target_ww_nsListEntry->data) == NULL)
    {
        goto fail;
    }
    }
     } 


    // v1_fc_volume_source->wwids
    if(v1_fc_volume_source->wwids) { 
    cJSON *wwids = cJSON_AddArrayToObject(item, "wwids");
    if(wwids == NULL) {
        goto fail; //primitive container
    }

    listEntry_t *wwidsListEntry;
    list_ForEach(wwidsListEntry, v1_fc_volume_source->wwids) {
    if(cJSON_AddStringToObject(wwids, "", (char*)wwidsListEntry->data) == NULL)
    {
        goto fail;
    }
    }
     } 

    return item;
fail:
    if (item) {
        cJSON_Delete(item);
    }
    return NULL;
}

v1_fc_volume_source_t *v1_fc_volume_source_parseFromJSON(cJSON *v1_fc_volume_sourceJSON){

    v1_fc_volume_source_t *v1_fc_volume_source_local_var = NULL;

    // v1_fc_volume_source->fs_type
    cJSON *fs_type = cJSON_GetObjectItemCaseSensitive(v1_fc_volume_sourceJSON, "fsType");
    if (fs_type) { 
    if(!cJSON_IsString(fs_type))
    {
    goto end; //String
    }
    }

    // v1_fc_volume_source->lun
    cJSON *lun = cJSON_GetObjectItemCaseSensitive(v1_fc_volume_sourceJSON, "lun");
    if (lun) { 
    if(!cJSON_IsNumber(lun))
    {
    goto end; //Numeric
    }
    }

    // v1_fc_volume_source->read_only
    cJSON *read_only = cJSON_GetObjectItemCaseSensitive(v1_fc_volume_sourceJSON, "readOnly");
    if (read_only) { 
    if(!cJSON_IsBool(read_only))
    {
    goto end; //Bool
    }
    }

    // v1_fc_volume_source->target_ww_ns
    cJSON *target_ww_ns = cJSON_GetObjectItemCaseSensitive(v1_fc_volume_sourceJSON, "targetWWNs");
    list_t *target_ww_nsList;
    if (target_ww_ns) { 
    cJSON *target_ww_ns_local;
    if(!cJSON_IsArray(target_ww_ns)) {
        goto end;//primitive container
    }
    target_ww_nsList = list_create();

    cJSON_ArrayForEach(target_ww_ns_local, target_ww_ns)
    {
        if(!cJSON_IsString(target_ww_ns_local))
        {
            goto end;
        }
        list_addElement(target_ww_nsList , strdup(target_ww_ns_local->valuestring));
    }
    }

    // v1_fc_volume_source->wwids
    cJSON *wwids = cJSON_GetObjectItemCaseSensitive(v1_fc_volume_sourceJSON, "wwids");
    list_t *wwidsList;
    if (wwids) { 
    cJSON *wwids_local;
    if(!cJSON_IsArray(wwids)) {
        goto end;//primitive container
    }
    wwidsList = list_create();

    cJSON_ArrayForEach(wwids_local, wwids)
    {
        if(!cJSON_IsString(wwids_local))
        {
            goto end;
        }
        list_addElement(wwidsList , strdup(wwids_local->valuestring));
    }
    }


    v1_fc_volume_source_local_var = v1_fc_volume_source_create (
        fs_type ? strdup(fs_type->valuestring) : NULL,
        lun ? lun->valuedouble : 0,
        read_only ? read_only->valueint : 0,
        target_ww_ns ? target_ww_nsList : NULL,
        wwids ? wwidsList : NULL
        );

    return v1_fc_volume_source_local_var;
end:
    return NULL;

}
