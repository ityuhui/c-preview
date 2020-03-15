/*
 * v1_stateful_set_status.h
 *
 * StatefulSetStatus represents the current state of a StatefulSet.
 */

#ifndef _v1_stateful_set_status_H_
#define _v1_stateful_set_status_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "v1_stateful_set_condition.h"



typedef struct v1_stateful_set_status_t {
    int collision_count; //numeric
    list_t *conditions; //nonprimitive container
    int current_replicas; //numeric
    char *current_revision; // string
    long observed_generation; //numeric
    int ready_replicas; //numeric
    int replicas; //numeric
    char *update_revision; // string
    int updated_replicas; //numeric

} v1_stateful_set_status_t;

v1_stateful_set_status_t *v1_stateful_set_status_create(
    int collision_count,
    list_t *conditions,
    int current_replicas,
    char *current_revision,
    long observed_generation,
    int ready_replicas,
    int replicas,
    char *update_revision,
    int updated_replicas
);

void v1_stateful_set_status_free(v1_stateful_set_status_t *v1_stateful_set_status);

v1_stateful_set_status_t *v1_stateful_set_status_parseFromJSON(cJSON *v1_stateful_set_statusJSON);

cJSON *v1_stateful_set_status_convertToJSON(v1_stateful_set_status_t *v1_stateful_set_status);

#endif /* _v1_stateful_set_status_H_ */

