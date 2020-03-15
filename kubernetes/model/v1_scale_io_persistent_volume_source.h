/*
 * v1_scale_io_persistent_volume_source.h
 *
 * ScaleIOPersistentVolumeSource represents a persistent ScaleIO volume
 */

#ifndef _v1_scale_io_persistent_volume_source_H_
#define _v1_scale_io_persistent_volume_source_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "v1_secret_reference.h"



typedef struct v1_scale_io_persistent_volume_source_t {
    char *fs_type; // string
    char *gateway; // string
    char *protection_domain; // string
    int read_only; //boolean
    struct v1_secret_reference_t *secret_ref; //model
    int ssl_enabled; //boolean
    char *storage_mode; // string
    char *storage_pool; // string
    char *system; // string
    char *volume_name; // string

} v1_scale_io_persistent_volume_source_t;

v1_scale_io_persistent_volume_source_t *v1_scale_io_persistent_volume_source_create(
    char *fs_type,
    char *gateway,
    char *protection_domain,
    int read_only,
    v1_secret_reference_t *secret_ref,
    int ssl_enabled,
    char *storage_mode,
    char *storage_pool,
    char *system,
    char *volume_name
);

void v1_scale_io_persistent_volume_source_free(v1_scale_io_persistent_volume_source_t *v1_scale_io_persistent_volume_source);

v1_scale_io_persistent_volume_source_t *v1_scale_io_persistent_volume_source_parseFromJSON(cJSON *v1_scale_io_persistent_volume_sourceJSON);

cJSON *v1_scale_io_persistent_volume_source_convertToJSON(v1_scale_io_persistent_volume_source_t *v1_scale_io_persistent_volume_source);

#endif /* _v1_scale_io_persistent_volume_source_H_ */

