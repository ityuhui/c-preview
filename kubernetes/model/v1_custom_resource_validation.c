#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "v1_custom_resource_validation.h"



v1_custom_resource_validation_t *v1_custom_resource_validation_create(
    v1_json_schema_props_t *open_apiv3_schema
    ) {
    v1_custom_resource_validation_t *v1_custom_resource_validation_local_var = malloc(sizeof(v1_custom_resource_validation_t));
    if (!v1_custom_resource_validation_local_var) {
        return NULL;
    }
    v1_custom_resource_validation_local_var->open_apiv3_schema = open_apiv3_schema;

    return v1_custom_resource_validation_local_var;
}


void v1_custom_resource_validation_free(v1_custom_resource_validation_t *v1_custom_resource_validation) {
    listEntry_t *listEntry;
    v1_json_schema_props_free(v1_custom_resource_validation->open_apiv3_schema);
    free(v1_custom_resource_validation);
}

cJSON *v1_custom_resource_validation_convertToJSON(v1_custom_resource_validation_t *v1_custom_resource_validation) {
    cJSON *item = cJSON_CreateObject();

    // v1_custom_resource_validation->open_apiv3_schema
    if(v1_custom_resource_validation->open_apiv3_schema) { 
    cJSON *open_apiv3_schema_local_JSON = v1_json_schema_props_convertToJSON(v1_custom_resource_validation->open_apiv3_schema);
    if(open_apiv3_schema_local_JSON == NULL) {
    goto fail; //model
    }
    cJSON_AddItemToObject(item, "openAPIV3Schema", open_apiv3_schema_local_JSON);
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

v1_custom_resource_validation_t *v1_custom_resource_validation_parseFromJSON(cJSON *v1_custom_resource_validationJSON){

    v1_custom_resource_validation_t *v1_custom_resource_validation_local_var = NULL;

    // v1_custom_resource_validation->open_apiv3_schema
    cJSON *open_apiv3_schema = cJSON_GetObjectItemCaseSensitive(v1_custom_resource_validationJSON, "openAPIV3Schema");
    v1_json_schema_props_t *open_apiv3_schema_local_nonprim = NULL;
    if (open_apiv3_schema) { 
    open_apiv3_schema_local_nonprim = v1_json_schema_props_parseFromJSON(open_apiv3_schema); //nonprimitive
    }


    v1_custom_resource_validation_local_var = v1_custom_resource_validation_create (
        open_apiv3_schema ? open_apiv3_schema_local_nonprim : NULL
        );

    return v1_custom_resource_validation_local_var;
end:
    return NULL;

}
