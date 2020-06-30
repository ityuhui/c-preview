#ifndef extensions_v1beta1_allowed_host_path_TEST
#define extensions_v1beta1_allowed_host_path_TEST

// the following is to include only the main from the first c file
#ifndef TEST_MAIN
#define TEST_MAIN
#define extensions_v1beta1_allowed_host_path_MAIN
#endif // TEST_MAIN

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../external/cJSON.h"

#include "../model/extensions_v1beta1_allowed_host_path.h"
extensions_v1beta1_allowed_host_path_t* instantiate_extensions_v1beta1_allowed_host_path(int include_optional);



extensions_v1beta1_allowed_host_path_t* instantiate_extensions_v1beta1_allowed_host_path(int include_optional) {
  extensions_v1beta1_allowed_host_path_t* extensions_v1beta1_allowed_host_path = NULL;
  if (include_optional) {
    extensions_v1beta1_allowed_host_path = extensions_v1beta1_allowed_host_path_create(
      "0",
      1
    );
  } else {
    extensions_v1beta1_allowed_host_path = extensions_v1beta1_allowed_host_path_create(
      "0",
      1
    );
  }

  return extensions_v1beta1_allowed_host_path;
}


#ifdef extensions_v1beta1_allowed_host_path_MAIN

void test_extensions_v1beta1_allowed_host_path(int include_optional) {
    extensions_v1beta1_allowed_host_path_t* extensions_v1beta1_allowed_host_path_1 = instantiate_extensions_v1beta1_allowed_host_path(include_optional);

	cJSON* jsonextensions_v1beta1_allowed_host_path_1 = extensions_v1beta1_allowed_host_path_convertToJSON(extensions_v1beta1_allowed_host_path_1);
	printf("extensions_v1beta1_allowed_host_path :\n%s\n", cJSON_Print(jsonextensions_v1beta1_allowed_host_path_1));
	extensions_v1beta1_allowed_host_path_t* extensions_v1beta1_allowed_host_path_2 = extensions_v1beta1_allowed_host_path_parseFromJSON(jsonextensions_v1beta1_allowed_host_path_1);
	cJSON* jsonextensions_v1beta1_allowed_host_path_2 = extensions_v1beta1_allowed_host_path_convertToJSON(extensions_v1beta1_allowed_host_path_2);
	printf("repeating extensions_v1beta1_allowed_host_path:\n%s\n", cJSON_Print(jsonextensions_v1beta1_allowed_host_path_2));
}

int main() {
  test_extensions_v1beta1_allowed_host_path(1);
  test_extensions_v1beta1_allowed_host_path(0);

  printf("Hello world \n");
  return 0;
}

#endif // extensions_v1beta1_allowed_host_path_MAIN
#endif // extensions_v1beta1_allowed_host_path_TEST
