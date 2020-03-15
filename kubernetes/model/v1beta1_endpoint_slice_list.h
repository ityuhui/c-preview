/*
 * v1beta1_endpoint_slice_list.h
 *
 * EndpointSliceList represents a list of endpoint slices
 */

#ifndef _v1beta1_endpoint_slice_list_H_
#define _v1beta1_endpoint_slice_list_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "v1_list_meta.h"
#include "v1beta1_endpoint_slice.h"



typedef struct v1beta1_endpoint_slice_list_t {
    char *api_version; // string
    list_t *items; //nonprimitive container
    char *kind; // string
    struct v1_list_meta_t *metadata; //model

} v1beta1_endpoint_slice_list_t;

v1beta1_endpoint_slice_list_t *v1beta1_endpoint_slice_list_create(
    char *api_version,
    list_t *items,
    char *kind,
    v1_list_meta_t *metadata
);

void v1beta1_endpoint_slice_list_free(v1beta1_endpoint_slice_list_t *v1beta1_endpoint_slice_list);

v1beta1_endpoint_slice_list_t *v1beta1_endpoint_slice_list_parseFromJSON(cJSON *v1beta1_endpoint_slice_listJSON);

cJSON *v1beta1_endpoint_slice_list_convertToJSON(v1beta1_endpoint_slice_list_t *v1beta1_endpoint_slice_list);

#endif /* _v1beta1_endpoint_slice_list_H_ */

