#ifndef v1_custom_resource_subresources_TEST
#define v1_custom_resource_subresources_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define v1_custom_resource_subresources_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/v1_custom_resource_subresources.h"
v1_custom_resource_subresources_t* instantiate_v1_custom_resource_subresources(int include_optional);

#include "test_v1_custom_resource_subresource_scale.c"


v1_custom_resource_subresources_t* instantiate_v1_custom_resource_subresources(int include_optional) {
  v1_custom_resource_subresources_t* v1_custom_resource_subresources = NULL;
  if (include_optional) {
    v1_custom_resource_subresources = v1_custom_resource_subresources_create(
       // false, not to have infinite recursion
      instantiate_v1_custom_resource_subresource_scale(0),
      0
    );
  } else {
    v1_custom_resource_subresources = v1_custom_resource_subresources_create(
      NULL,
      0
    );
  }

  return v1_custom_resource_subresources;
}


#ifdef v1_custom_resource_subresources_MAIN

void test_v1_custom_resource_subresources(int include_optional) {
    v1_custom_resource_subresources_t* v1_custom_resource_subresources_1 = instantiate_v1_custom_resource_subresources(include_optional);

	cJSON* jsonv1_custom_resource_subresources_1 = v1_custom_resource_subresources_convertToJSON(v1_custom_resource_subresources_1);
	printf("v1_custom_resource_subresources :\n%s\n", cJSON_Print(jsonv1_custom_resource_subresources_1));
	v1_custom_resource_subresources_t* v1_custom_resource_subresources_2 = v1_custom_resource_subresources_parseFromJSON(jsonv1_custom_resource_subresources_1);
	cJSON* jsonv1_custom_resource_subresources_2 = v1_custom_resource_subresources_convertToJSON(v1_custom_resource_subresources_2);
	printf("repeating v1_custom_resource_subresources:\n%s\n", cJSON_Print(jsonv1_custom_resource_subresources_2));
}

int main() {
  test_v1_custom_resource_subresources(1);
  test_v1_custom_resource_subresources(0);

  printf("Hello world \n");
  return 0;
}

#endif // v1_custom_resource_subresources_MAIN
#endif // v1_custom_resource_subresources_TEST
