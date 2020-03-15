/*
 * v1_deployment_spec.h
 *
 * DeploymentSpec is the specification of the desired behavior of the Deployment.
 */

#ifndef _v1_deployment_spec_H_
#define _v1_deployment_spec_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "v1_deployment_strategy.h"
#include "v1_label_selector.h"
#include "v1_pod_template_spec.h"



typedef struct v1_deployment_spec_t {
    int min_ready_seconds; //numeric
    int paused; //boolean
    int progress_deadline_seconds; //numeric
    int replicas; //numeric
    int revision_history_limit; //numeric
    struct v1_label_selector_t *selector; //model
    struct v1_deployment_strategy_t *strategy; //model
    struct v1_pod_template_spec_t *template; //model

} v1_deployment_spec_t;

v1_deployment_spec_t *v1_deployment_spec_create(
    int min_ready_seconds,
    int paused,
    int progress_deadline_seconds,
    int replicas,
    int revision_history_limit,
    v1_label_selector_t *selector,
    v1_deployment_strategy_t *strategy,
    v1_pod_template_spec_t *template
);

void v1_deployment_spec_free(v1_deployment_spec_t *v1_deployment_spec);

v1_deployment_spec_t *v1_deployment_spec_parseFromJSON(cJSON *v1_deployment_specJSON);

cJSON *v1_deployment_spec_convertToJSON(v1_deployment_spec_t *v1_deployment_spec);

#endif /* _v1_deployment_spec_H_ */

