#ifndef v1_event_source_TEST
#define v1_event_source_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define v1_event_source_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/v1_event_source.h"
v1_event_source_t* instantiate_v1_event_source(int include_optional);



v1_event_source_t* instantiate_v1_event_source(int include_optional) {
  v1_event_source_t* v1_event_source = NULL;
  if (include_optional) {
    v1_event_source = v1_event_source_create(
      "0",
      "0"
    );
  } else {
    v1_event_source = v1_event_source_create(
      "0",
      "0"
    );
  }

  return v1_event_source;
}


#ifdef v1_event_source_MAIN

void test_v1_event_source(int include_optional) {
    v1_event_source_t* v1_event_source_1 = instantiate_v1_event_source(include_optional);

	cJSON* jsonv1_event_source_1 = v1_event_source_convertToJSON(v1_event_source_1);
	printf("v1_event_source :\n%s\n", cJSON_Print(jsonv1_event_source_1));
	v1_event_source_t* v1_event_source_2 = v1_event_source_parseFromJSON(jsonv1_event_source_1);
	cJSON* jsonv1_event_source_2 = v1_event_source_convertToJSON(v1_event_source_2);
	printf("repeating v1_event_source:\n%s\n", cJSON_Print(jsonv1_event_source_2));
}

int main() {
  test_v1_event_source(1);
  test_v1_event_source(0);

  printf("Hello world \n");
  return 0;
}

#endif // v1_event_source_MAIN
#endif // v1_event_source_TEST
